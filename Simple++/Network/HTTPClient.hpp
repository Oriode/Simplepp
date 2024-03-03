#include "HTTPClient.h"
namespace Network {


	template<typename T>
	inline HTTPClientT<T>::HTTPClientT( typename UrlT<T>::Sheme sheme, const StringASCII& hostname ) :
		request( HTTPRequestT<T>::Verb::Unknown, sheme, hostname ),
		bWasConnected( false ) { }

	template<typename T>
	inline HTTPClientT<T>::HTTPClientT( const UrlT<T>& url ) :
		request( HTTPRequestT<T>::Verb::Unknown, url ),
		bWasConnected( false ) { }

	template<typename T>
	inline HTTPParam* HTTPClientT<T>::setHeaderParam( const StringASCII& paramName, const StringASCII& paramValue ) {
		return this->request.setHeaderParam( paramName, paramValue );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( typename HTTPRequestT<T>::Verb verb, const UrlT<T>& url ) {
		this->request.setVerb( verb );
		this->request.setUrl( url );

		return _query( this->request );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( typename HTTPRequestT<T>::Verb verb, const StringASCII& uri, const Vector<HTTPParam>& urlParamVector ) {
		this->request.setVerb( verb );
		this->request.setUri( uri );
		this->request.setUrlParams( urlParamVector );

		return _query( this->request );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( const HTTPRequestT<T>& request ) {
		return _query( request );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query( const HTTPRequestT<T>* request ) {
		return _query( *request );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::GET( const StringASCII& uri, const Vector<HTTPParam>& urlParamVector ) {
		this->request.setVerb( HTTPRequestT<T>::Verb::GET );
		this->request.setUri( uri );
		this->request.setUrlParams( urlParamVector );
		
		return _query( this->request );
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::POST( const StringASCII& uri, const Vector<HTTPParam>& urlParamVector, const StringASCII& contentStr ) {
		this->request.setVerb( HTTPRequestT<T>::Verb::POST );
		this->request.setUri( uri );
		this->request.setUrlParams( urlParamVector );
		this->request.setContent( contentStr );

		return _query( this->request );
	}

	template<typename T>
	inline const HTTPResponseT<T>* HTTPClientT<T>::getLastResponse() const {
		return &this->response;
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::_query( const typename HTTPRequestT<T>& request ) {
		if ( request.getEndPoint().getSheme() == UrlT<T>::Sheme::HTTPS ) {

			this->sendBuffer.clear();
			request.formatQuery( &this->sendBuffer );

			// Try sending directly as we are in keep alive.
			if ( !this->bWasConnected ) {
				if ( !this->connection.connect( request.getEndPoint().getHostname(), unsigned short( 443 ), Network::SockType::TCP ) ) {
					return NULL;
				}
				this->bWasConnected = true;
			}

			if ( !this->connection.isConnected() || !this->connection.send( this->sendBuffer.toCString(), int( this->sendBuffer.getSize() ) ) ) {
				if ( !this->connection.reconnect() ) {
					return NULL;
				}
				if ( !this->connection.send( this->sendBuffer.toCString(), int( this->sendBuffer.getSize() ) ) ) {
					return NULL;
				}
			}

			int maxSizeReceive( sizeof( this->receiveBuffer ) );
			const StringASCII::ElemType* parseIt( this->receiveBuffer );
			int totalReceivedLength( connection.receive( this->receiveBuffer, maxSizeReceive ) );

			if ( totalReceivedLength <= int( 0 ) ) {
				return NULL;
			}

			// We receive something, let's try parse the title and the header.
			if ( !this->response.parseQueryTitle( &parseIt, StringASCII::IsEndIterator( this->receiveBuffer + totalReceivedLength ) ) ) {
				return NULL;
			}
			if ( !this->response.parseQueryHeader( &parseIt, StringASCII::IsEndIterator( this->receiveBuffer + totalReceivedLength ) ) ) {
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

			maxSizeReceive = contentLength + static_cast< int >( parseIt - this->receiveBuffer );

			while ( totalReceivedLength < maxSizeReceive ) {
				int receivedLength( connection.receive( this->receiveBuffer + totalReceivedLength, maxSizeReceive - totalReceivedLength ) );

				if ( receivedLength <= int( 0 ) ) {
					return NULL;
				}

				totalReceivedLength += receivedLength;
			}

			DEBUG_SPP( *( this->receiveBuffer + totalReceivedLength ) = StringASCII::ElemType( '\n' ) );

			if ( !this->response.parseQueryContent( &parseIt, StringASCII::IsEndIterator( this->receiveBuffer + totalReceivedLength ) ) ) {
				return NULL;
			}

			return &this->response;
		} else {
			ERROR_SPP( String::format( "Unsuported query type %.", UrlT<T>::getShemeStr( request.getEndPoint().getSheme() ) ) );
			return NULL;
		}

		return NULL;
	}

}