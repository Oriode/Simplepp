#pragma once

#include "../Mutex.h"
#include "../Thread.h"
#include "../List.h"
#include "../Network/HTTPMessage.h"
#include "../Notify.h"

#include "HTTPClient.h"
#include "ClientQueryHandler.h"
#include "Query.h"


namespace Network {

	///@brief	Async version of the Client
	template<typename T>
	class HTTPClientAsyncT : public Thread {
	public:
		HTTPClientAsyncT( typename UrlT<T>::Sheme type, const StringASCII & hostname, int verbose = 0 );
		~HTTPClientAsyncT();

		///@brief	Add a new query to the stack to be handled.
		///			The client will be automaticaly started to handle the query stack and stopped when needed.
		void addQuery( BasicQuery * query );

		///@brief	If the client is running or in the process of starting.
		bool isRunning() const;

		///@brief	Clear the whole qeue.
		void clearQueue();

		///@brief	Set a header param to the underlying HTTPClient.
		HTTPParam* setHeaderParam( const StringASCII & paramName, const StringASCII & paramValue );

		///@brief	Wait the client to handle all the current stack.
		void waitAllQueries();

	protected:
		virtual void run() override;

		Mutex httpClientMutex;
		HTTPClient httpClient;

	private:
		bool handleQueryList();
		typename HTTPError sendQuery( BasicQuery * query, int verbose = 0 );

		Time::Duration<Time::MilliSecond> errorWaitTime{ 1000 };

		List<BasicQuery*> queryStack;

		Mutex handlersMutex;
		Mutex queryMutex;

		bool bShouldStopMainLoop{ false };

		int verbose{ 0 };
	};

	using HTTPClientAsync = HTTPClientAsyncT<int>;

	template<typename T>
	inline HTTPClientAsyncT<T>::HTTPClientAsyncT( typename UrlT<T>::Sheme type, const StringASCII& hostname, int verbose ) :
		httpClient( type, hostname ),
		verbose( verbose ) { }

	template<typename T>
	inline HTTPClientAsyncT<T>::~HTTPClientAsyncT() {

		this->queryMutex.lock();
		{
			this->bShouldStopMainLoop = true;
		}
		this->queryMutex.unlock();

		join();

		clearQueue();
	}

	template<typename T>
	inline void HTTPClientAsyncT<T>::addQuery( BasicQuery* query ) {
		bool bRunning( false );
		this->queryMutex.lock();
		{
			bRunning = this->queryStack.getSize() != Size( 0 );
			this->queryStack.push( query );
		}
		this->queryMutex.unlock();

		if ( !bRunning ) {
			join();
			start();
		}
	}

	template<typename T>
	inline bool HTTPClientAsyncT<T>::isRunning() const {
		bool bRunning( false );
		this->queryMutex.lock();
		{
			bRunning = this->queryStack.getSize() != Size( 0 );
		}
		this->queryMutex.unlock();

		return bRunning;
	}

	template<typename T>
	inline void HTTPClientAsyncT<T>::clearQueue() {
		this->queryMutex.lock();
		{
			while ( this->queryStack.getSize() != Size( 0 ) ) {
				BasicQuery * query( this->queryStack.popBegin() );
				query->setError( HTTPError::InterruptedException );
			}
		}
		this->queryMutex.unlock();
	}

	template<typename T>
	inline HTTPParam* HTTPClientAsyncT<T>::setHeaderParam( const StringASCII& paramName, const StringASCII& paramValue ) {
		HTTPParam* httpParam( NULL );
		this->httpClientMutex.lock();
		{
			httpParam = this->httpClient.setHeaderParam( paramName, paramValue );
		}
		this->httpClientMutex.unlock();
		return httpParam;
	}

	template<typename T>
	inline void HTTPClientAsyncT<T>::waitAllQueries() {
		join();
	}

	template<typename T>
	inline void HTTPClientAsyncT<T>::run() {
		handleQueryList();

		// If ended for any reason with remaning queries. Stop them.
		clearQueue();
	}

	template<typename T>
	inline bool HTTPClientAsyncT<T>::handleQueryList() {
		while ( true ) {
			this->queryMutex.lock();
			{

				// If should stop.
				if ( this->bShouldStopMainLoop ) {
					this->queryMutex.unlock();
					return false;
				}

				if ( this->queryStack.getSize() == Size( 0 ) ) {

					// If there are no queries to handle, exit.
					this->queryMutex.unlock();
					return true;
				} else {
					this->queryMutex.unlock();
				}
			}

			// For each message in the stack.
			while ( true ) {
				BasicQuery* query( NULL );
				this->queryMutex.lock();
				{

					if ( this->bShouldStopMainLoop ) {
						this->queryMutex.unlock();
						break;
					}

					if ( this->queryStack.getSize() == Size( 0 ) ) {
						this->queryMutex.unlock();
						break;
					}

					query = this->queryStack.popBegin();
					this->queryMutex.unlock();
				}

				HTTPError error( sendQuery( query, this->verbose ) );

				// If the query has failed.
				if ( error != HTTPError::None ) {

					// If the query is set to auto retry on network error.
					if ( ( error == HTTPError::NetworkException && query->isNetworkExceptionAutoRetry() ) || ( error == HTTPError::UnexpectedResponseException && query->isUnexpectedExceptionAutoRetry() ) ) {
						// Push back the failed query to retry.
						this->queryMutex.lock();
						{
							this->queryStack.pushBegin( query );
						}
						this->queryMutex.unlock();

						// We had an error, wait for a bit before trying again.
						Time::sleep( this->errorWaitTime );

						break;
					}

					return true;
				}
			}
		}

	}
	template<typename T>
	inline typename HTTPError HTTPClientAsyncT<T>::sendQuery( BasicQuery* query, int verbose ) {
		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Sendind % => %", query->getQueryMessage()->getName(), query->getResponseMessage()->getName() ) ); }

		HTTPRequestT<T> request;

		this->httpClientMutex.lock();
		query->setMessageSent();
		HTTPResponseT<T>* httpResponse( query->send( &this->httpClient, verbose - 1 ) );
		this->httpClientMutex.unlock();

		// Create the request from the message.
		if ( !httpResponse ) {
			query->setError( HTTPError::NetworkException );
			if ( verbose > 0 ) { Log::endStepFailure( __func__, "NetworkException" ); }
			return query->getError();
		}

		if ( typename HTTPError e( query->getResponseMessage()->fromResponse( httpResponse, verbose - 1 ) ); e != HTTPError::None ) {
			query->setError( e );
			if ( verbose > 0 ) { Log::endStepFailure( __func__, "Failed" ); }
			return query->getError();
		}

		query->setError( HTTPError::None );

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, "Success." ); }

		return query->getError();
	}
}

