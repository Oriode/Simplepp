namespace Network {

	template<typename T>
	bool NetworkT<T>::mIsInit = false;

	template<typename T>
	bool NetworkT<T>::init() {

		if ( NetworkT<T>::mIsInit ) return true;
	#if defined WIN32
		WSADATA wsaData;

		if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 ) {
			error( "WSAStartup failed !" );
			WSACleanup();
			return false;
		}
	#endif
		return true;
		NetworkT<T>::mIsInit = true;

	}

	template<typename T>
	void NetworkT<T>::close() {

		if ( !NetworkT<T>::mIsInit ) return;
	#if defined WIN32
		WSACleanup();
	#endif
		NetworkT<T>::mIsInit = false;

	}

}

