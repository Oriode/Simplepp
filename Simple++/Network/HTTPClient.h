#pragma once

#include "../ParamContainer.h"
#include "Url.h"
#include "TLSConnection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

namespace Network {

	template<typename T>
	class HTTPClientT {
	public:
		HTTPClientT( const UrlT<T>& url );
		HTTPClientT( typename UrlT<T>::Sheme type, const StringASCII& hostname );

		HTTPParam* setHeaderParam( const StringASCII& paramName, const StringASCII& paramValue );

		HTTPResponseT<T>* query( typename HTTPRequestT<T>::Verb method, const UrlT<T>& url );
		HTTPResponseT<T>* query( const HTTPRequestT<T>& request );
		HTTPResponseT<T>* query( const HTTPRequestT<T>* request );

		HTTPResponseT<T>* GET( const StringASCII& Uri, const Vector<HTTPParam>& urlParamVector );
		HTTPResponseT<T>* POST( const StringASCII& Uri, const Vector<HTTPParam>& urlParamVector, const StringASCII& contentStr );

		const HTTPResponseT<T>* getLastResponse() const;

	private:
		HTTPResponseT<T>* _query( const typename HTTPRequestT<T>& request );

		HTTPRequestT<T> request;
		HTTPResponseT<T> response;

		TLSConnectionT<T> connection;
		bool bWasConnected;

		StringASCII sendBuffer;
		char receiveBuffer[ 1000000 ];
	};

	using HTTPClient = HTTPClientT<int>;

}

#include "HTTPClient.hpp"