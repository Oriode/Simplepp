#include "HTTPClient.h"
namespace Network {


	template<typename T>
	inline HTTPClientT<T>::HTTPClientT( typename UrlT<T>::Sheme sheme, const StringASCII& hostname, const Size bufferSize ) :
		request( HTTPRequestT<T>::Verb::Unknown, sheme, hostname ),
		bWasConnected( false ),
		receiveBuffer( new char[ bufferSize ] ),
		bufferSize( bufferSize ) { }

	template<typename T>
	inline HTTPClientT<T>::HTTPClientT( const UrlT<T>& url, const Size bufferSize ) :
		request( HTTPRequestT<T>::Verb::Unknown, url ),
		bWasConnected( false ),
		receiveBuffer( new char[ bufferSize ] ),
		bufferSize( bufferSize ) { }

	template<typename T>
	inline HTTPClientT<T>::~HTTPClientT() {
		delete[] this->receiveBuffer;
	}

	template<typename T>
	inline HTTPParam* HTTPClientT<T>::setHeaderParam( const StringASCII& paramName, const StringASCII& paramValue ) {
		return this->request.setHeaderParam( paramName, paramValue );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( typename HTTPRequestT<T>::Verb verb, const UrlT<T>& url, int verbose ) {
		this->request.setVerb( verb );
		this->request.setUrl( url );

		return _query( this->request, verbose );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( typename HTTPRequestT<T>::Verb verb, const StringASCII& path, const Vector<HTTPParam>& urlParamVector, int verbose ) {
		this->request.setVerb( verb );
		this->request.setPath( path );
		this->request.setUrlParams( urlParamVector );

		return _query( this->request, verbose );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( const HTTPRequestT<T>& request, int verbose ) {
		return _query( request, verbose );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( const HTTPRequestT<T>* request, int verbose ) {
		return _query( *request, verbose );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::GET( const StringASCII& path, const Vector<HTTPParam>& urlParamVector, int verbose ) {
		this->request.setVerb( HTTPRequestT<T>::Verb::GET );
		this->request.setPath( path );
		this->request.setUrlParams( urlParamVector );

		return _query( this->request, verbose );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::POST( const StringASCII& path, const Vector<HTTPParam>& urlParamVector, typename HTTPQueryT<T>::ContentType contentType, const StringASCII& contentStr, int verbose ) {
		this->request.setVerb( HTTPRequestT<T>::Verb::POST );
		this->request.setPath( path );
		this->request.setUrlParams( urlParamVector );
		this->request.setContentType( contentType );
		this->request.setContent( contentStr );

		return _query( this->request, verbose );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::PUT( const StringASCII& path, const Vector<HTTPParam>& urlParamVector, typename HTTPQueryT<T>::ContentType contentType, const StringASCII& contentStr, int verbose ) {
		this->request.setVerb( HTTPRequestT<T>::Verb::PUT );
		this->request.setPath( path );
		this->request.setUrlParams( urlParamVector );
		this->request.setContentType( contentType );
		this->request.setContent( contentStr );

		return _query( this->request, verbose );
	}

	template<typename T>
	inline const HTTPResponseT<T>* HTTPClientT<T>::getLastResponse() const {
		return &this->response;
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::_query( const typename HTTPRequestT<T>& request, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( "HTTPClient::query", String::format( "Sending: %...", request.getUrl().formatWOParams()) ); }

		if ( request.getUrl().getSheme() == UrlT<T>::Sheme::HTTPS ) {

			this->sendBuffer.clear();
			request.formatQuery( &this->sendBuffer );

			// Try sending directly as we are in keep alive.
			if ( !this->bWasConnected ) {
				if ( !this->connection.connect( request.getUrl().getHostname(), unsigned short( 443 ), Network::SockType::TCP ) ) {
					if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Failed to connect to %.", request.getUrl().getHostname() ) ); }
					return NULL;
				}
				this->bWasConnected = true;
			} else {
				if ( verbose > 1 ) { Log::displayLog( "HTTPClient::query", String::format( "Already connected to %, skipping connection.", request.getUrl().getHostname() ) ); }
			}

			if ( !this->connection.isConnected() || !this->connection.send( this->sendBuffer.toCString(), int( this->sendBuffer.getSize() ) ) ) {
				if ( !this->connection.reconnect() ) {
					if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Failed to reconnect to %.", request.getUrl().getHostname() ) ); }
					return NULL;
				}
				if ( !this->connection.send( this->sendBuffer.toCString(), int( this->sendBuffer.getSize() ) ) ) {
					if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Failed to send to %.", request.getUrl().getHostname() ) ); }
					return NULL;
				}
			}

			int maxSizeReceive( int( this->bufferSize ) );
			const StringASCII::ElemType* parseIt( this->receiveBuffer );
			int totalReceivedLength( connection.receive( this->receiveBuffer, maxSizeReceive ) );

			if ( totalReceivedLength <= int( 0 ) ) {
				if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Received nothing." ) ); }
				return NULL;
			}

			// We receive something, let's try parse the title and the header.
			if ( !this->response.parseQueryTitle( &parseIt, StringASCII::IsEndIterator( this->receiveBuffer + totalReceivedLength ), verbose - 1 ) ) {
				if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Failed to parse the title." ) ); }
				return NULL;
			}
			if ( !this->response.parseQueryHeader( &parseIt, StringASCII::IsEndIterator( this->receiveBuffer + totalReceivedLength ), verbose - 1 ) ) {
				if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Failed to parse the header." ) ); }
				return NULL;
			}

			// Now we have the title and the header. Let's check for the Content-Length.
			static const StringASCII contentLengthParamName( "Content-Length" );
			HTTPParam* contentSizeParam( this->response.getHeaderParam( contentLengthParamName ) );


			int contentLength;
			if ( contentSizeParam ) {
				contentLength = contentSizeParam->getValue().toInt();
			} else {
				contentLength = Size( 0 );
			}

			if ( verbose > 1 ) { Log::displayLog( "HTTPClient::query", String::format( "Content-Length: %", contentLength ) ); }

			if ( contentLength > this->bufferSize ) {
				if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Buffer overflow. Received % bytes but can store only %.", contentLength, this->bufferSize ) ); }
				return NULL;
			}

			maxSizeReceive = contentLength + static_cast< int >( parseIt - this->receiveBuffer );

			while ( totalReceivedLength < maxSizeReceive ) {
				int receivedLength( connection.receive( this->receiveBuffer + totalReceivedLength, maxSizeReceive - totalReceivedLength ) );

				if ( receivedLength <= int( 0 ) ) {
					if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Received nothing." ) ); }
					return NULL;
				}

				totalReceivedLength += receivedLength;
			}

			DEBUG_SPP( *( this->receiveBuffer + totalReceivedLength ) = StringASCII::ElemType( '\n' ) );

			if ( !this->response.parseQueryContent( &parseIt, StringASCII::IsEndIterator( this->receiveBuffer + totalReceivedLength ), verbose - 1 ) ) {
				if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Failed to parse the content." ) ); }
				return NULL;
			}

			if ( verbose > 0 ) { Log::endStepSuccess( "HTTPClient::query", String::format( "Success." ) ); }

			return &this->response;
		} else {
			if ( verbose > 0 ) { Log::endStepFailure( "HTTPClient::query", String::format( "Unsuported query type %.", UrlT<T>::getShemeStr( request.getUrl().getSheme() ) ) ); }
			return NULL;
		}


	}

}