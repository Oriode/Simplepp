namespace Network {

	template<typename T>
	ServerT<T>::ServerT() :
		mIsBinded( false ) {

	}

	template<typename T>
	ServerT<T>::~ServerT() {
		close();
	}


	template<typename T>
	bool ServerT<T>::listen( unsigned short port, SockType sockType, IpFamily ipFamily, int maxClients ) {
		return _listen( NULL, StringASCII( port ).getData(), sockType, ipFamily, maxClients );
	}

	template<typename T>
	bool ServerT<T>::listen( const StringASCII & address, const StringASCII & service, SockType sockType, IpFamily ipFamily, int maxClients ) {
		return _listen( address.getData(), service.getData(), sockType, ipFamily, maxClients );
	}

	template<typename T>
	bool ServerT<T>::listen( const StringASCII & address, unsigned int port, SockType sockType, IpFamily ipFamily, int maxClients ) {
		return _listen( address.getData(), StringASCII( port ).getData(), sockType, ipFamily, maxClients );
	}

	template<typename T>
	bool ServerT<T>::listen( const Address & address, int maxClients /*= 100*/ ) {
		if ( !Network::init() ) return false;

		AddrInfo thisAddrInfo( *( ( AddrInfo * ) &address ) );
		if ( ( ( int ) _tryListen( &thisAddrInfo, maxClients ) ) == SOCKET_ERROR ) {
			error( StringASCII( "Unable to bind ip " ) << thisAddrInfo.getIpFamilyS() << " : " << thisAddrInfo.getNameInfo() << " on port " << thisAddrInfo.getPort() << " with protocol " << thisAddrInfo.getSockTypeS() );
			return false;
		}
		updateFdSet();

		this -> mIsBinded = true;
		return true;
	}

	template<typename T>
	bool ServerT<T>::_listen( const char * ip, const char * service, SockType sockType, IpFamily ipFamily, int maxClients /*= 100*/ ) {
		if ( !Network::init() ) return false;

		AddrInfo hints( sockType, ipFamily );
		hints.addFlag( Flags::Passive );
		hints.addFlag( Flags::NumericHost );

		addrinfo * addrResults;
		if ( ::getaddrinfo( ip, service, hints.getAddrInfoStruct(), &addrResults ) ) {
			error( StringASCII( "Unable to retreive address info on address  " ) << ip << "@" << service );
			return false;
		}

		if ( _tryListen( addrResults, maxClients ) == false ) {
			error( StringASCII( "Unable to bind on " ) << ( ( AddrInfo ) ( *addrResults ) ).getIpFamilyS() << " : " << ip << " on port " << service << " with Protocol " << ( ( AddrInfo ) ( *addrResults ) ).getSockTypeS() );
			freeaddrinfo( addrResults );
			return false;
		}
		freeaddrinfo( addrResults );
		updateFdSet();


		this -> mIsBinded = true;
		return true;
	}

	template<typename T>
	bool ServerT<T>::_tryListen( const addrinfo * addrResults, int maxClients ) {
		Vector<const AddrInfo *> addrInfoVector;

		bool result = false;
		for ( const addrinfo * AI = addrResults; AI != NULL; AI = AI -> ai_next ) {
			AddrInfo * addrInfo = ( AddrInfo * ) AI;
			addrInfoVector.push( addrInfo );

			if ( this -> mSocketVector.getSize() >= FD_SETSIZE ) {
				warn( "getaddrinfo returned more addresses than we could use.\n" );
				break;
			}

			result = _tryListen( addrInfo, maxClients ) || result;

		}
		return result;
	}


	template<typename T>
	bool ServerT<T>::_tryListen( AddrInfo * addrInfo, int maxClients ) {
		if ( addrInfo -> getIpFamily() == IpFamily::Undefined ) {
			addrInfo -> setIpFamily( IpFamily::IPv6 );

			bool result2 = _tryListen( new Connection( *addrInfo ), maxClients );

			addrInfo -> setIpFamily( IpFamily::IPv4 );

			bool result1 = _tryListen( new Connection( *addrInfo ), maxClients );

			return result2 || result1;
		} else {
			return _tryListen( new Connection( *addrInfo ), maxClients );
		}
		return false;
	}

	template<typename T>
	bool ServerT<T>::_tryListen( Connection * socket, int maxClients ) {
		if ( this -> mSocketVector.getSize() >= FD_SETSIZE ) {
			warn( "getaddrinfo returned more addresses than we could use.\n" );
			return false;
		}

		if ( socket -> listen( maxClients ) ) {
			this -> mSocketVector.push( socket );
			return true;
		}
		delete socket;
		return false;
	}




	template<typename T>
	bool ServerT<T>::close() {
		if ( !this -> mIsBinded ) return false;

		for ( unsigned int i = 0; i < this -> mSocketVector.getSize(); i++ ) {
			this -> mSocketVector[ i ] -> close();
			delete this -> mSocketVector[ i ];
		}
		this -> mSocketVector.clear();

		this -> mIsBinded = false;

		return true;
	}

	template<typename T>
	bool ServerT<T>::accept( Connection * clientSocket ) {
		if ( getNumConnections() == 1 )
			return this -> mSocketVector[ 0 ] -> accept( clientSocket );

		Connection * selectedSocket = _select();
		if ( selectedSocket )
			return selectedSocket -> accept( clientSocket );
		else
			return false;

	}


	template<typename T>
	void ServerT<T>::updateFdSet() {
		this -> mFdSet.fd_count = ( u_int ) Math::min<Vector<Connection * >::Size>( this -> mSocketVector.getSize(), FD_SETSIZE );
		for ( unsigned int i = 0; i < this -> mFdSet.fd_count; i++ ) {
			this -> mFdSet.fd_array[ i ] = this -> mSocketVector[ i ] -> getSocket();
		}
	}

	template<typename T>
	typename Vector<Connection * >::Size ServerT<T>::getNumConnections() const {
		return this -> mSocketVector.getSize();
	}

	template<typename T>
	size_t ServerT<T>::getMaximumNbConnections() {
		return FD_SETSIZE;
	}

	template<typename T>
	Connection * ServerT<T>::_select() {
		if ( this -> mFdSet.fd_count > 0 ) {
			memcpy( &this -> mFdSetTmp, &this -> mFdSet, sizeof( fd_set ) );
			if ( ::select( ( int ) getNumConnections(), &this -> mFdSetTmp, 0, 0, 0 ) == SOCKET_ERROR ) {
				error( "Select failed !" );
				return NULL;
			}

			while ( this -> mFdSetTmp.fd_count > 0 ) {
				this -> mFdSetTmp.fd_count--;
				SOCKET activeSocket = this -> mFdSetTmp.fd_array[ this -> mFdSetTmp.fd_count ];

				for ( auto i = this -> mSocketVector.begin(); i != this -> mSocketVector.end(); i++ ) {
					if ( ( *i ) -> getSocket() == activeSocket ) {
						return ( *i );
					}
				}
			}
		}
		return NULL;
	}

	template<typename T>
	int ServerT<T>::receive( char * buffer, int maxSize, Address * addressFrom ) {
		Connection * selectedSocket = _select();
		if ( selectedSocket )
			return selectedSocket -> receive( buffer, maxSize, addressFrom );
		else
			return 0;
	}












}


