#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>

#if defined DEBUG

#define logSSL( ... ); Crypto::SSLObject::displayErrors( TEXT( __FILE__ ), __LINE__ );

#else

#define logSSL();

#endif

namespace Crypto {

	template<typename T>
	class SSLObjectT {
	public:
		SSLObjectT();

		static bool init();
		static void close();

		static void displayErrors(const TCHAR* fileName = NULL, unsigned int lineNumber = 0);

		static StringASCII getErrorStr(const int errorCode);

		///@brief Get the current error code or 0 if none.
		///@return Error code or 0 if none.
		static int getError();

	private:
		static bool isInitialized;

		SSL* ssl;
	};

	using SSLObject = SSLObjectT<int>;

}

#include "SSL.hpp"