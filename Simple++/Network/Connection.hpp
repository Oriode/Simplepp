#include "Connection.h"
namespace Network {

	template<typename T>
	ConnectionT<T>::ConnectionT( const Address & address ) :
		Address( address ),
		mSocket( SOCKET(-1) ),
		mIsListening( false ) {

	}
	/*


	ConnectionT<T>::ConnectionT(const StringASCII & ip, const StringASCII & service, SockType sockType / *= SockType::TCP* /, IpFamily ipFamily / *= IpFamily::Undefined* /) :
		Address(ip, service, sockType, ipFamily),
		mSocket(0),
		mIsListening(false)
	{

	}

	ConnectionT<T>::ConnectionT(const Address & address) :
		Address(address),
		mSocket(0),
		mIsListening(false)
	{

	}*/

	template<typename T>
	ConnectionT<T>::ConnectionT( ctor ) : Address( ctor::null ) {

	}

	template<typename T>
	inline bool ConnectionT<T>::_connect() {

		if ( !_tryConnect(this) ) {
			ERROR_SPP(StringASCII("Unable to connect to host ") << getIpFamilyS() << " : " + getNameInfo() << " on port " + getPort() << " with protocol " << getSockTypeS());
			return false;
		}

		return true;
	}

	template<typename T>
	inline bool ConnectionT<T>::_connect(const Address& address) {
		setAddess(address);
		return _connect();
	}


	template<typename T>
	ConnectionT<T>::ConnectionT( ConnectionT<T> && connection ) :
		Address( ctor::null ) {
		*this = Utility::toRValue( connection );
	}

	template<typename T>
	ConnectionT<T>::ConnectionT() :
		Address( ctor::null ),
		mSocket( SOCKET(-1) ),
		mIsListening( false ) {

	}

	/*
		ConnectionT<T> & ConnectionT<T>::operator=(const AddrInfo & addrInfo) {
			close();
			Address::operator=(addrInfo);
			return *this;
		}*/

	template<typename T>
	ConnectionT<T>::~ConnectionT() {
		close();
	}


	template<typename T>
	const Address & ConnectionT<T>::getAddress() const {
		return *this;
	}

	template<typename T>
	void ConnectionT<T>::setAddess( const Address & address ) {
		close();
		Address::operator=( address );
	}

	template<typename T>
	bool ConnectionT<T>::listen( int maxClients ) {
		if ( !_init() ) {
			return false;
		}

		if ( isConnected() ) {
			close();
		}

		if ( !_tryListen( this, maxClients ) ) {
			ERROR_SPP( StringASCII( "Unable to bind ip " ) << getIpFamilyS() << " : " + getNameInfo() << " on port " << getPort() << " with protocol " << getSockTypeS() );
			return false;
		}

		this -> mIsListening = ( getSockType() == SockType::TCP );
		return true;
	}



	template<typename T>
	SOCKET ConnectionT<T>::listenStatic( const AddrInfo & addrInfo, int maxClients ) {
		SOCKET newSocket = ::socket( ( int ) addrInfo.getIpFamily(), ( int ) addrInfo.getSockType(), ( int ) addrInfo.getProtocol() );
		if ( newSocket == INVALID_SOCKET ) {
			return SOCKET_ERROR;
		}

		if ( ::bind( newSocket, addrInfo.getSockAddr(), ( int ) addrInfo.getSockAddrLen() ) == SOCKET_ERROR ) {
			closesocket( newSocket );
			return SOCKET_ERROR;
		}

		if ( addrInfo.getSockType() == SockType::TCP ) {
			if ( ::listen( newSocket, maxClients ) == SOCKET_ERROR ) {
				closesocket( newSocket );
				return SOCKET_ERROR;
			}
		}

		VERBOSE_SPP(StringASCII("New Socket ") << newSocket << " listening on " << addrInfo.getIpFamilyS() + " : " << addrInfo.getIp() << " on port " << addrInfo.getPort() << " with protocol " << addrInfo.getSockTypeS());

		return newSocket;
	}

	template<typename T>
	bool ConnectionT<T>::listen( const StringASCII & ip, const StringASCII & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/, int maxClients /*= 100*/ ) {
		return _listen( ip.getData(), service.getData(), sockType, ipFamily, maxClients );
	}

	template<typename T>
	bool ConnectionT<T>::listen( const StringASCII & ip, unsigned short port, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/, int maxClients /*= 100*/ ) {
		return _listen( ip.getData(), StringASCII( port ).getData(), sockType, ipFamily, maxClients );
	}

	template<typename T>
	bool ConnectionT<T>::listen( unsigned short port, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/, int maxClients /*= 100*/ ) {
		return _listen( NULL, StringASCII( port ).getData(), sockType, ipFamily, maxClients );
	}

	template<typename T>
	bool ConnectionT<T>::listen( const Address & address, int maxClients /*= 100*/ ) {
		setAddess( address );
		return listen( maxClients );
	}

	template<typename T>
	bool ConnectionT<T>::_listen( const char * ip, const char * service, SockType sockType, IpFamily ipFamily, int maxClients /*= 100*/ ) {
		if ( !_init() ) {
			return false;
		}

		setSockType( sockType );
		setIpFamily( ipFamily );

		addrinfo * addrResults(NULL);
		SOCKET addrErr(::getaddrinfo(ip, service, getAddrInfoStruct(), &addrResults));
		if ( addrErr ) {
			if ( addrResults ) {
				freeaddrinfo(addrResults);
			}
			ERROR_SPP( StringASCII( "SOCKET error " ) << addrErr << " : Unable to retrieve address info on address " << ip << "@" << service );
			return false;
		}

		if ( !_tryListen( addrResults, maxClients ) ) {
			ERROR_SPP( StringASCII( "Unable to bind on " ) << getIpFamilyS() + " : " << ip << " on port " << service << " with Protocol " << getSockTypeS() );
			freeaddrinfo( addrResults );
			return false;
		}
		freeaddrinfo( addrResults );
		VERBOSE_SPP( StringASCII( "Socket " ) << this -> mSocket << " listening on " << getIpFamilyS() << " : " << getIp() << " on port " << getPort() << " with " << getSockTypeS() );

		this -> mIsListening = ( getSockType() == SockType::TCP );
		return true;
	}

	template<typename T>
	bool ConnectionT<T>::connect() {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		return _connect();
	}

	template<typename T>
	bool ConnectionT<T>::connect( const StringASCII & ip, const StringASCII & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/ ) {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		return _connect( ip.toCString(), service, sockType, ipFamily );
	}

	template<typename T>
	bool ConnectionT<T>::connect( const StringASCII & ip, unsigned short port, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/ ) {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		return _connect( ip.toCString(), StringASCII::toString(port), sockType, ipFamily);
	}

	template<typename T>
	inline bool ConnectionT<T>::reconnect() {

		if ( isConnected() ) {
			close();
		}

		if ( !_reconnect() ) {
			return false;
		}

		return true;
	}

	template<typename T>
	SOCKET ConnectionT<T>::connectStatic( const AddrInfo & addrInfo ) {
		SOCKET newSocket = ::socket( ( int ) addrInfo.getIpFamily(), ( int ) addrInfo.getSockType(), ( int ) addrInfo.getProtocol() );
		if ( newSocket == INVALID_SOCKET ) {
			return SOCKET_ERROR;
		}
		if ( addrInfo.getSockType() == SockType::TCP ) {
			if ( ::connect( newSocket, addrInfo.getSockAddr(), ( int ) addrInfo.getSockAddrLen() ) == SOCKET_ERROR ) {
				closesocket( newSocket );
				return SOCKET_ERROR;
			}
		}

		VERBOSE_SPP(StringASCII("New Socket ") << newSocket << " connected to " << addrInfo.getIpFamilyS() + " : " << addrInfo.getIp() << " on port " << addrInfo.getPort() << " with protocol " << addrInfo.getSockTypeS());

		return newSocket;
	}

	template<typename T>
	bool ConnectionT<T>::isConnected() const {
		return this -> mSocket != SOCKET(-1);
	}

	template<typename T>
	bool ConnectionT<T>::connect( const Address & address ) {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		return _connect(address);
	}



	template<typename T>
	bool ConnectionT<T>::_connect(const StringASCII& ip, const StringASCII& service, SockType sockType, IpFamily ipFamily ) {

		setSockType( sockType );
		setIpFamily( ipFamily );

		addrinfo * addrResults(NULL);
		SOCKET addrErr(::getaddrinfo(ip.toCString(), service.toCString(), getAddrInfoStruct(), &addrResults));
		if ( addrErr ) {
			if ( addrResults ) {
				freeaddrinfo(addrResults);
			}
			ERROR_SPP(StringASCII("SOCKET error ") << addrErr << " : Unable to retrieve address info on address " << ip << "@" << service);
			return false;
		}

		if ( !_tryConnect( addrResults ) ) {
			ERROR_SPP( StringASCII( "Unable to connect to host " ) << ( ( AddrInfo ) ( *addrResults ) ).getIpFamilyS() << " : " << ip << " on port " << service << " with Protocol " << ( ( AddrInfo ) ( *addrResults ) ).getSockTypeS() );
			freeaddrinfo( addrResults );
			return false;
		}

		//freeing the automatically allocated AddrInfos
		freeaddrinfo( addrResults );

		VERBOSE_SPP( StringASCII( "Socket " ) << this -> mSocket << " connected to " << getIpFamilyS() + " : " << getIp() << " on port " << getPort() << " with protocol " << getSockTypeS() );

		return true;
	}

	template<typename T>
	inline bool ConnectionT<T>::_reconnect() {
		SOCKET newSocket = connectStatic(*this);
		if ( newSocket != SOCKET_ERROR ) {
			this -> mSocket = newSocket;
			return true;
		}

		return false;
	}

	template<typename T>
	inline bool ConnectionT<T>::_init() {
		if ( !NetworkObject::init() ) return false;

		if ( isConnected() ) {
			close();
			WARNING_SPP("The connection was already open. Closing the old one.");
		}

		return true;
	}

	template<typename T>
	bool ConnectionT<T>::_tryConnect( const addrinfo * addrResults ) {

		for ( const addrinfo * AI = addrResults; AI != NULL; AI = AI -> ai_next ) {
			AddrInfo * addrInfo = ( AddrInfo * ) AI;

			if (_tryConnect(addrInfo)){
				return true;
			}

		}
		return false;
	}

	template<typename T>
	bool ConnectionT<T>::_tryConnect( AddrInfo * addrInfo ) {
		if ( addrInfo -> getIpFamily() == IpFamily::Undefined ) {
			addrInfo -> setIpFamily( IpFamily::IPv6 );
			SOCKET newSocket = connectStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				if ( addrInfo != this ) setAddess( *addrInfo );
				this -> mSocket = newSocket;
				return true;
			}

			addrInfo -> setIpFamily( IpFamily::IPv4 );
			newSocket = connectStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				if ( addrInfo != this ) setAddess( *addrInfo );
				this -> mSocket = newSocket;
				return true;
			}
		} else {
			SOCKET newSocket = connectStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				if ( addrInfo != this ) setAddess( *addrInfo );
				this -> mSocket = newSocket;
				return true;
			}
		}
		return false;
	}


	template<typename T>
	bool ConnectionT<T>::_tryListen( const addrinfo * addrResults, int maxClients ) {

		for ( auto AI = addrResults; AI != NULL; AI = AI -> ai_next ) {
			AddrInfo * addrInfo = ( AddrInfo * ) AI;
			if ( _tryListen(addrInfo, maxClients) ) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	bool ConnectionT<T>::_tryListen( AddrInfo * addrInfo, int maxClients ) {
		if ( addrInfo -> getIpFamily() == IpFamily::Undefined ) {
			addrInfo -> setIpFamily( IpFamily::IPv6 );

			SOCKET newSocket = listenStatic( *addrInfo, maxClients );
			if ( newSocket != SOCKET_ERROR ) {
				if ( addrInfo != this ) setAddess( *addrInfo );
				this -> mSocket = newSocket;
				return true;
			}

			addrInfo -> setIpFamily( IpFamily::IPv4 );

			newSocket = listenStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				if ( addrInfo != this ) setAddess( *addrInfo );
				this -> mSocket = newSocket;
				return true;
			}
		} else {
			SOCKET newSocket = listenStatic( *addrInfo, maxClients );
			if ( newSocket != SOCKET_ERROR ) {
				if ( addrInfo != this ) setAddess( *addrInfo );
				this -> mSocket = newSocket;
				return true;
			}
		}
		return false;
	}











	template<typename T>
	void ConnectionT<T>::close() {
		if ( isConnected() ) {
			closesocket(this -> mSocket);
			VERBOSE_SPP(StringASCII::format("Closed socket %.", this->mSocket));
			this -> mSocket = SOCKET(-1);
		}

		this -> mIsListening = false;
	}




	template<typename T>
	bool ConnectionT<T>::send( const char * buffer, int size ) {
		if ( getSockType() == SockType::TCP ) {
			if ( ::send( this -> mSocket, buffer, size, 0 ) == SOCKET_ERROR ) {
				ERROR_SPP( "Unable to send TCP data." );
				return false;
			}
		} else if ( getSockType() == SockType::UDP ) {
			if ( ::sendto( this -> mSocket, buffer, size, 0, getSockAddr(), ( int ) getSockAddrLen() ) == SOCKET_ERROR ) {
				ERROR_SPP( "Unable to send UDP data." );
				return false;
			}
		}
		return true;
	}

	template<typename T>
	bool ConnectionT<T>::accept( ConnectionT<T> * clientSocket ) {
		if ( !isConnected() ) {
			ERROR_SPP( "Socket not binded." );
			return false;
		}

		if ( !this -> mIsListening ) {
			ERROR_SPP( "This socket is not able to accept anything, he is not listening." );
			return false;
		}


		clientSocket -> newSockAddr( sizeof( SOCKADDR_STORAGE ) );
		SOCKET clientSock;
		socklen_t sockLen = ( socklen_t ) clientSocket -> ai_addrlen;
		clientSock = ::accept( this -> mSocket, clientSocket -> ai_addr, &sockLen );
		//accept ONLY set the address (ip) in ai_addr
		clientSocket -> ai_addrlen = sockLen;

		if ( clientSock == INVALID_SOCKET ) {
			ERROR_SPP( "Unable to accept new client" );
			return false;
		}

		clientSocket -> mSocket = clientSock;
		clientSocket -> setIpFamily( getIpFamily() );
		clientSocket -> setSockType( getSockType() );
		clientSocket -> setPort( getSockAddr() );
		clientSocket -> _update();

		VERBOSE_SPP( StringASCII( "Socket " ) << this -> mSocket << " has accepted a new client " << clientSocket -> getIpFamilyS() << " : " << clientSocket -> getIp() );


		return true;
	}

	template<typename T>
	SOCKET ConnectionT<T>::getSocket() const {
		return this -> mSocket;
	}

	template<typename T>
	int ConnectionT<T>::receive( char * buffer, int maxSize ) {
		int amountRead = ::recv( this -> mSocket, buffer, maxSize, 0 );
		if ( amountRead < 0 ) {
			if ( amountRead == SOCKET_ERROR ) {
				ERROR_SPP( "Error while receiving !" );
				return amountRead;
			}
			return 0;
		}
		return amountRead;
	}

	template<typename T>
	int ConnectionT<T>::receive( char * buffer, int maxSize, Address * addressFrom ) {
		//cast in order to resolve access problem
		ConnectionT<T> * castedAddress = ( ConnectionT<T> * ) addressFrom;
		castedAddress -> newSockAddr( sizeof( SOCKADDR_STORAGE ) );
		int amountRead = ::recvfrom( this -> mSocket, buffer, maxSize, 0, castedAddress -> ai_addr, ( int * ) &castedAddress -> ai_addrlen );
		if ( amountRead <= 0 ) {
			if ( amountRead == SOCKET_ERROR ) {
				ERROR_SPP( "Error while ReceiveFrom." );
			}
			return 0;
		}
		castedAddress -> setPort( getSockAddr() );
		return amountRead;
	}

	template<typename T>
	ConnectionT<T> & ConnectionT<T>::operator=( ConnectionT<T> && socket ) {
		Address::operator=( Utility::toRValue( socket ) );
		this -> mSocket = Utility::toRValue( socket.mSocket );
		this -> mIsListening = Utility::toRValue( socket.mIsListening );
		return *this;
	}

	template<typename T>
	bool ConnectionT<T>::send( char * buffer, int size, const Address & addressTo ) {
		//cast in order to resolve access problem
		const ConnectionT<T> * castedAddress = ( const ConnectionT<T> * ) & addressTo;
		if ( ::sendto( this -> mSocket, buffer, size, 0, castedAddress -> getSockAddr(), ( int ) castedAddress  -> getSockAddrLen() ) == SOCKET_ERROR ) {
			ERROR_SPP( "Unable to send UDP data." );
			return false;
		}
		return true;
	}







}










