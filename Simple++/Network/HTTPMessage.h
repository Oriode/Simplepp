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
		virtual bool toRequest( HTTPRequest* httpRequest ) const;

		///@brief	Read the message from a HTTPResponse.
		///@return	true if the message was successfully read from the HTTPResponse.
		virtual bool fromResponse( const HTTPResponse* httpResponse );

	};

	using HTTPMessage = HTTPMessageT<int>;

	template<typename T>
	inline bool HTTPMessageT<T>::toRequest( HTTPRequest* httpRequest ) const {
		return false;
	}

	template<typename T>
	inline bool HTTPMessageT<T>::fromResponse( const HTTPResponse* httpResponse ) {
		return false;
	}

}