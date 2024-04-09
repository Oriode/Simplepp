#pragma once

#include "Simple++/Mutex.h"
#include "Simple++/Time/TimePoint.h"
#include "ClientQueryHandler.h"
#include "Simple++/Network/HTTPMessage.h"
#include "Simple++/Notify.h"

namespace Network {

	///@brief	Base class representing a query for a answer/response communication.
	///			The query can have an handler to be called after being handled.
	///			Can be waited for a synchrone use.
	///			Can be set up with differents behaviors in cases of errors.
	template<typename T>
	class BasicQueryT {
	public:
		///@brief	Constructor using a queryMessage.
		BasicQueryT( const HTTPMessage* queryMessage, HTTPMessage* responseMessage, ClientQueryHandler* handler = NULL );

		///@brief	Get the query message.
		const HTTPMessage* getQueryMessage() const;

		///@brief	Get the response message.
		const HTTPMessage* getResponseMessage() const;
		HTTPMessage* getResponseMessage();

		///@brief	Wait until a new answer is received, can be an error and the message will be NULL.
		void waitUntilAnswer();

		///@brief	Set the handler to be called after the query has been treated.
		///@param	Handler to be set and called after the query has been handled. With success, or not.
		void setHandler( ClientQueryHandler* handler );

		///@brief	Manually call the handler if any.
		void callHandler();

		void setNetworkErrorAutoRetry( bool bNetworkErrorAutoRetry );
		bool isNetworkExceptionAutoRetry() const;

		void setUnexpectedAutoRetry( bool bUnexpectedAutoRetry );
		bool isUnexpectedExceptionAutoRetry() const;

		void setTimeOut( const Time::Duration<Time::MilliSecond>& timeOut );
		const Time::Duration<Time::MilliSecond>& getTimeOut() const;


		///@brief	Get the last Response state.
		HTTPError getError() const;

		///@brief	Set the message as sent.
		void setMessageSent();

		///@brief	Send the query.
		HTTPResponseT<T>* send( HTTPClient* httpClient, int verbose = 0 ) const;

		///@brief	Set the return type after the query has been treated, and call the handler accordingly.
		void setError( typename HTTPError httpError );

	private:


		const HTTPMessage* queryMessage{ NULL };				//	Memory managed.
		HTTPMessage* responseMessage{ NULL };				//	Memory managed.
		ClientQueryHandler* handler{ NULL };				//	Not memory managed.

		Mutex queryMutex;

		Time::TimePoint<Time::MilliSecond> queryTimePoint;
		Time::TimePoint<Time::MilliSecond> responseTimePoint;

		Time::Duration<Time::MilliSecond> timeOut{ 5000 };

		HTTPError receivedError{ HTTPError::Undefined };

		Notify answerNotify;

		bool bNetworkErrorAutoRetry{ false };		// If the query should be retried automatically if a network error occured.
		bool bUnexpectedAutoRetry{ false };			// If the query should be retried automatically if an unexpected answer was received.
	};

	using BasicQuery = BasicQueryT<int>;

	template<typename T>
	BasicQueryT<T>::BasicQueryT( const HTTPMessage* queryMessage, HTTPMessage* responseMessage, ClientQueryHandler* handler ) :
		queryMessage( queryMessage ),
		responseMessage( responseMessage ),
		handler( handler ) { }

	template<typename T>
	const HTTPMessage* Network::BasicQueryT<T>::getQueryMessage() const {
		return this->queryMessage;
	}

	template<typename T>
	inline const HTTPMessage* BasicQueryT<T>::getResponseMessage() const {
		return this->responseMessage;
	}

	template<typename T>
	inline HTTPMessage* BasicQueryT<T>::getResponseMessage() {
		return this->responseMessage;
	}

	template<typename T>
	inline void BasicQueryT<T>::setError( typename HTTPError httpError ) {
		this->queryMutex.lock();
		{
			this->responseTimePoint = Time::getTime<Time::MilliSecond>();
			this->receivedError = httpError;
		}
		this->queryMutex.unlock();

		this->answerNotify.notify();

		callHandler();
	}

	template<typename T>
	inline void BasicQueryT<T>::setMessageSent() {
		this->queryMutex.lock();
		{
			this->responseTimePoint.setValue( 0 );
			this->queryTimePoint = Time::getTime<Time::MilliSecond>();
			this->receivedError = HTTPError::None;
		}
		this->queryMutex.unlock();
	}

	template<typename T>
	inline void BasicQueryT<T>::waitUntilAnswer() {
		this->queryMutex.lock();
		{
			if ( this->responseTimePoint.getValue() != 0 ) {
				this->queryMutex.unlock();
				return;
			}
		}
		this->queryMutex.unlock();

		this->answerNotify.wait();
	}

	template<typename T>
	inline void BasicQueryT<T>::setHandler( ClientQueryHandler* handler ) {
		this->handler = handler;
	}

	template<typename T>
	inline void BasicQueryT<T>::callHandler() {
		if ( this->handler ) {
			this->handler->onAnswer( this->queryMessage, this->responseMessage, this->receivedError );
		}
	}

	template<typename T>
	void BasicQueryT<T>::setNetworkErrorAutoRetry( bool bNetworkErrorAutoRetry ) {
		this->bNetworkErrorAutoRetry = bNetworkErrorAutoRetry;
	}

	template<typename T>
	bool BasicQueryT<T>::isNetworkExceptionAutoRetry() const {
		return this->bNetworkErrorAutoRetry;
	}

	template<typename T>
	void BasicQueryT<T>::setUnexpectedAutoRetry( bool bUnexpectedAutoRetry ) {
		this->bUnexpectedAutoRetry = bUnexpectedAutoRetry;
	}

	template<typename T>
	bool BasicQueryT<T>::isUnexpectedExceptionAutoRetry() const {
		return this->bUnexpectedAutoRetry;
	}

	template<typename T>
	inline void BasicQueryT<T>::setTimeOut( const Time::Duration<Time::MilliSecond>& timeOut ) {
		this->timeOut = timeOut;
	}

	template<typename T>
	inline const Time::Duration<Time::MilliSecond>& BasicQueryT<T>::getTimeOut() const {
		return this->timeOut;
	}

	template<typename T>
	inline HTTPResponseT<T>* BasicQueryT<T>::send( HTTPClient* httpClient, int verbose ) const {
		return getQueryMessage()->send( httpClient, verbose - 1 );
	}

	template<typename T>
	inline HTTPError BasicQueryT<T>::getError() const {
		return this->receivedError;
	}


}