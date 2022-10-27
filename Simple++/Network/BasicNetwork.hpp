namespace Network {

	template<typename T>
	bool NetworkObjectT<T>::mIsInit = false;

	template<typename T>
	bool NetworkObjectT<T>::init() {

		if ( NetworkObjectT<T>::mIsInit ) return true;
	#if defined WIN32
		WSADATA wsaData;

		if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 ) {
			ERROR_SPP( "WSAStartup failed !" );
			WSACleanup();
			return false;
		}
	#endif
		return true;
		NetworkObjectT<T>::mIsInit = true;

	}

	template<typename T>
	void NetworkObjectT<T>::close() {

		if ( !NetworkObjectT<T>::mIsInit ) return;
	#if defined WIN32
		WSACleanup();
	#endif
		NetworkObjectT<T>::mIsInit = false;

	}

}

