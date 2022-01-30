namespace Crypto {

	template<typename T>
	bool SSLObjectT<T>::isInitialized = false;

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