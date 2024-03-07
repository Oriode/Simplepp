#pragma once

#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "HTTPClient.h"

namespace Network {

	enum class HTTPError : unsigned char {
		None = 0x0,
		NetworkException = 0x1,
		InterruptedException = 0x2,
		GeneratingRequestException = 0x3,
		UnexpectedResponseException = 0x4,
		Undefined = 0xFF
	};

	template<typename T>
	class HTTPMessageT {
	public:
		HTTPMessageT() = default;

		///@brief	Construct a HTTPRequest from the message.
		///@return	true if the message was successfully converted to a HTTPRequest.
		virtual HTTPResponse * send( HTTPClient * httpClient, int verbose = 0 ) const;

		///@brief	Read the message from a HTTPResponse.
		///@return	true if the message was successfully read from the HTTPResponse.
		virtual typename HTTPError fromResponse( const HTTPResponse* httpResponse, int verbose = 0 );

		virtual String toString() const;
		virtual const String & getName() const;
	};

	using HTTPMessage = HTTPMessageT<int>;

	template<typename T>
	inline HTTPResponse * HTTPMessageT<T>::send( HTTPClient* httpClient, int verbose ) const {
		return NULL;
	}

	template<typename T>
	inline typename HTTPError HTTPMessageT<T>::fromResponse( const HTTPResponse* httpResponse, int verbose ) {
		return HTTPError::Undefined;
	}

	template<typename T>
	inline String HTTPMessageT<T>::toString() const {
		return String::null;
	}

	template<typename T>
	inline const String& HTTPMessageT<T>::getName() const {
		return String::null;
	}

}