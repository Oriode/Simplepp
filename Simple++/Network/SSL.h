#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "BasicNetwork.h"

#if defined DEBUG

#define logSSL( ... ); Network::SSLObject::displayErrors( TEXT( __FILE__ ), __LINE__ );

#else

#define logSSL();

#endif

namespace Network {

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

	template<typename T>
	inline SSLObjectT<T>::SSLObjectT() {}

	template<typename T>
	inline bool SSLObjectT<T>::init() {
		if ( !SSLObjectT<T>::isInitialized ) {
			SSL_library_init();
			// SSLeay_add_ssl_algorithms();
			SSL_load_error_strings();

			SSLObjectT<T>::isInitialized = true;
		}

		return true;
	}

	template<typename T>
	inline void SSLObjectT<T>::close() {
		if ( SSLObjectT<T>::isInitialized ) {
			ERR_free_strings();
			EVP_cleanup();

			SSLObjectT<T>::isInitialized = false;
		}
	}

	template<typename T>
	inline void SSLObjectT<T>::displayErrors(const TCHAR* fileName, unsigned int lineNumber) {
		int errorCode;
		while ( errorCode = SSLObjectT<T>::getError() ) {
			Log::callErrorHandler(getErrorStr(errorCode), Log::MessageSeverity::Error, Log::MessageColor::Red, fileName, lineNumber);
		}
	}

	template<typename T>
	inline StringASCII SSLObjectT<T>::getErrorStr(const int errorCode) {
		char* errorCStr(ERR_error_string(errorCode, NULL));
		return StringASCII(errorCStr);
	}

	template<typename T>
	inline int SSLObjectT<T>::getError() {
		return ERR_get_error();
	}

}

#include "SSL.hpp"