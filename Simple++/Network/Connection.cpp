#include "Connection.h"


namespace Network {


	Connection::Connection( const Address & address ) :
		Address( address ),
		mSocket( 0 ),
		mIsCreated( false ),
		mIsListening( false ) {

	}
	/*


	Connection::Connection(const StringASCII & ip, const StringASCII & service, SockType sockType / *= SockType::TCP* /, IpFamily ipFamily / *= IpFamily::Undefined* /) :
		Address(ip, service, sockType, ipFamily),
		mSocket(0),
		mIsCreated(false),
		mIsListening(false)
	{

	}

	Connection::Connection(const Address & address) :
		Address(address),
		mSocket(0),
		mIsCreated(false),
		mIsListening(false)
	{

	}*/


	Connection::Connection( ctor ) : Address( ctor::null ) {

	}



	Connection::Connection( Connection && connection ) :
		Address( ctor::null ) {
		*this = Utility::toRValue( connection );
	}

	Connection::Connection() :
		Address( ctor::null ),
		mSocket( 0 ),
		mIsCreated( false ),
		mIsListening( false ) {

	}

	/*
		Connection & Connection::operator=(const AddrInfo & addrInfo) {
			close();
			Address::operator=(addrInfo);
			return *this;
		}*/

	Connection::~Connection() {
		close();
	}



	const Address & Connection::getAddress() const {
		return *this;
	}

	void Connection::setAddess( const Address & address ) {
		close();
		Address::operator=( address );
	}

	bool Connection::listen( int maxClients ) {
		if ( !Network::init() ) return false;

		if ( this -> mIsCreated ) {
			close();
			warn( "The connection was already open. Closing the old one." );
		}

		if ( !_tryListen( this, maxClients ) ) {
			error( StringASCII( "Unable to bind ip " ) << getIpFamilyS() << " : " + getNameInfo() << " on port " << getPort() << " with protocol " << getSockTypeS() );
			return false;
		}

		log( StringASCII( "Socket " ) << this -> mSocket << " listening on " << getIpFamilyS() << " : " << getIp() << " on port " << getPort() << " with " << getSockTypeS() );

		this -> mIsListening = ( getSockType() == SockType::TCP );
		this -> mIsCreated = true;
		return true;
	}




	SOCKET Connection::listenStatic( const AddrInfo & addrInfo, int maxClients ) {
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

		return newSocket;
	}

	bool Connection::listen( const StringASCII & ip, const StringASCII & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/, int maxClients /*= 100*/ ) {
		return _listen( ip.getData(), service.getData(), sockType, ipFamily, maxClients );
	}

	bool Connection::listen( const StringASCII & ip, unsigned short port, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/, int maxClients /*= 100*/ ) {
		return _listen( ip.getData(), StringASCII( port ).getData(), sockType, ipFamily, maxClients );
	}

	bool Connection::listen( unsigned short port, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/, int maxClients /*= 100*/ ) {
		return _listen( NULL, StringASCII( port ).getData(), sockType, ipFamily, maxClients );
	}

	bool Connection::listen( const Address & address, int maxClients /*= 100*/ ) {
		setAddess( address );
		return listen( maxClients );
	}

	bool Connection::_listen( const char * ip, const char * service, SockType sockType, IpFamily ipFamily, int maxClients /*= 100*/ ) {
		if ( !Network::init() ) return false;

		if ( this -> mIsCreated ) {
			close();
			warn( "The connection was already open. Closing the old one." );
		}

		setSockType( sockType );
		setIpFamily( ipFamily );

		struct addrinfo * addrResults;
		if ( getaddrinfo( ip, service, getAddrInfoStruct(), &addrResults ) ) {
			error( StringASCII( "Unable to retrieve address info on address  " ) << ip << "@" << service );
			return false;
		}

		if ( !_tryListen( addrResults, maxClients ) ) {
			error( StringASCII( "Unable to bind on " ) << getIpFamilyS() + " : " << ip << " on port " << service << " with Protocol " << getSockTypeS() );
			freeaddrinfo( addrResults );
			return false;
		}
		freeaddrinfo( addrResults );
		log( StringASCII( "Socket " ) << this -> mSocket << " listening on " << getIpFamilyS() << " : " << getIp() << " on port " << getPort() << " with " << getSockTypeS() );

		this -> mIsListening = ( getSockType() == SockType::TCP );
		this -> mIsCreated = true;
		return true;
	}


	bool Connection::connect() {
		if ( !Network::init() ) return false;

		if ( this -> mIsCreated ) {
			close();
		}

		if ( !_tryConnect( this ) ) {
			error( StringASCII( "Unable to connect to host " ) << getIpFamilyS() << " : " + getNameInfo() << " on port " + getPort() << " with protocol " << getSockTypeS() );
			return false;
		}

		log( StringASCII( "Socket " ) << this -> mSocket << " connected to " << getIpFamilyS() + " : " << getIp() << " on port " << getPort() << " with protocol " << getSockTypeS() );

		this -> mIsCreated = true;
		return true;
	}


	bool Connection::connect( const StringASCII & ip, const StringASCII & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/ ) {
		return _connect( ip.toCString(), service.toCString(), sockType, ipFamily );
	}

	bool Connection::connect( const StringASCII & ip, unsigned short port, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/ ) {
		return _connect( ip.toCString(), StringASCII( port ).toCString(), sockType, ipFamily );
	}

	SOCKET Connection::connectStatic( const AddrInfo & addrInfo ) {
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

		return newSocket;
	}


	bool Connection::isConnected() const {
		return this -> mIsCreated;
	}

	bool Connection::connect( const Address & address ) {
		setAddess( address );
		return connect();
	}




	bool Connection::_connect( const char * ip, const char * service, SockType sockType, IpFamily ipFamily ) {
		if ( !Network::init() ) return false;

		if ( this -> mIsCreated ) {
			close();
			warn( "The connection was already open. Closing the old one." );
		}

		setSockType( sockType );
		setIpFamily( ipFamily );

		struct addrinfo * addrResults;
		if ( ::getaddrinfo( ip, service, getAddrInfoStruct(), &addrResults ) ) {
			error( StringASCII( "Unable to retrieve address info on address  " ) << ip << "@" << service );
			return false;
		}

		if ( !_tryConnect( addrResults ) ) {
			error( StringASCII( "Unable to connect to host " ) << ( ( AddrInfo ) ( *addrResults ) ).getIpFamilyS() << " : " << ip << " on port " << service << " with Protocol " << ( ( AddrInfo ) ( *addrResults ) ).getSockTypeS() );
			freeaddrinfo( addrResults );
			return false;
		}

		//freeing the automatically allocated AddrInfos
		freeaddrinfo( addrResults );

		log( StringASCII( "Socket " ) << this -> mSocket << " connected to " << getIpFamilyS() + " : " << getIp() << " on port " << getPort() << " with protocol " << getSockTypeS() );

		this -> mIsCreated = true;
		return true;
	}


	bool Connection::_tryConnect( const struct addrinfo * addrResults ) {
		for ( const struct addrinfo * AI = addrResults; AI != NULL; AI = AI -> ai_next ) {
			AddrInfo * addrInfo = ( AddrInfo* ) AI;

			return _tryConnect( addrInfo );

		}
		return false;
	}


	bool Connection::_tryConnect( AddrInfo * addrInfo ) {
		if ( addrInfo -> getIpFamily() == IpFamily::Undefined ) {
			addrInfo -> setIpFamily( IpFamily::IPv6 );
			SOCKET newSocket = connectStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				this -> mSocket = newSocket;
				if ( addrInfo != this ) setAddess( *addrInfo );
				return true;
			}

			addrInfo -> setIpFamily( IpFamily::IPv4 );
			newSocket = connectStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				this -> mSocket = newSocket;
				if ( addrInfo != this ) setAddess( *addrInfo );
				return true;
			}
		} else {
			SOCKET newSocket = connectStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				this -> mSocket = newSocket;
				if ( addrInfo != this ) setAddess( *addrInfo );
				return true;
			}
		}
		return false;
	}



	bool Connection::_tryListen( const struct addrinfo * addrResults, int maxClients ) {
		for ( auto AI = addrResults; AI != NULL; AI = AI -> ai_next ) {
			AddrInfo * addrInfo = ( AddrInfo* ) AI;
			return _tryListen( addrInfo, maxClients );
		}
		return false;
	}

	bool Connection::_tryListen( AddrInfo * addrInfo, int maxClients ) {
		if ( addrInfo -> getIpFamily() == IpFamily::Undefined ) {
			addrInfo -> setIpFamily( IpFamily::IPv6 );

			SOCKET newSocket = listenStatic( *addrInfo, maxClients );
			if ( newSocket != SOCKET_ERROR ) {
				this -> mSocket = newSocket;
				if ( addrInfo != this ) setAddess( *addrInfo );
				return true;
			}

			addrInfo -> setIpFamily( IpFamily::IPv4 );

			newSocket = listenStatic( *addrInfo );
			if ( newSocket != SOCKET_ERROR ) {
				this -> mSocket = newSocket;
				if ( addrInfo != this ) setAddess( *addrInfo );
				return true;
			}
		} else {
			SOCKET newSocket = listenStatic( *addrInfo, maxClients );
			if ( newSocket != SOCKET_ERROR ) {
				this -> mSocket = newSocket;
				if ( addrInfo != this ) setAddess( *addrInfo );
				return true;
			}
		}
		return false;
	}












	void Connection::close() {
		if ( this -> mIsCreated )
			closesocket( this -> mSocket );

		this -> mIsCreated = false;
		this -> mIsListening = false;
	}





	bool Connection::send( const char * buffer, int size ) {
		if ( getSockType() == SockType::TCP ) {
			if ( ::send( this -> mSocket, buffer, size, 0 ) == SOCKET_ERROR ) {
				error( "Unable to send TCP data." );
				return false;
			}
		} else if ( getSockType() == SockType::UDP ) {
			if ( ::sendto( this -> mSocket, buffer, size, 0, getSockAddr(), ( int ) getSockAddrLen() ) == SOCKET_ERROR ) {
				error( "Unable to send UDP data." );
				return false;
			}
		}
		return true;
	}

	bool Connection::accept( Connection * clientSocket ) {
		if ( !this -> mIsCreated ) {
			error( "Socket not binded." );
			return false;
		}

		if ( !this -> mIsListening ) {
			error( "This socket is not able to accept anything, he is not listening." );
			return false;
		}


		clientSocket -> newSockAddr( sizeof( SOCKADDR_STORAGE ) );
		SOCKET clientSock;
		socklen_t sockLen = ( socklen_t ) clientSocket -> ai_addrlen;
		clientSock = ::accept( this -> mSocket, clientSocket -> ai_addr, &sockLen );
		//accept ONLY set the address (ip) in ai_addr
		clientSocket -> ai_addrlen = sockLen;

		if ( clientSock == INVALID_SOCKET ) {
			error( "Unable to accept new client" );
			return false;
		}

		clientSocket -> mSocket = clientSock;
		clientSocket -> mIsCreated = true;
		clientSocket -> setIpFamily( getIpFamily() );
		clientSocket -> setSockType( getSockType() );
		clientSocket -> setPort( getSockAddr() );
		clientSocket -> _update();

		log( StringASCII( "Socket " ) << this -> mSocket << " has accepted a new client " << clientSocket -> getIpFamilyS() << " : " << clientSocket -> getIp() );


		return true;
	}


	SOCKET Connection::getSocket() const {
		return this -> mSocket;
	}


	int Connection::receive( char * buffer, int maxSize ) {
		int amountRead = ::recv( this -> mSocket, buffer, maxSize, 0 );
		if ( amountRead <= 0 ) {
			if ( amountRead == SOCKET_ERROR ) {
				error( "Error while receiving !" );
			}
			return 0;
		}
		return amountRead;
	}

	int Connection::receive( char * buffer, int maxSize, Address * addressFrom ) {
		//cast in order to resolve access problem
		Connection * castedAddress = ( Connection* ) addressFrom;
		castedAddress -> newSockAddr( sizeof( SOCKADDR_STORAGE ) );
		int amountRead = ::recvfrom( this -> mSocket, buffer, maxSize, 0, castedAddress -> ai_addr, ( int* ) &castedAddress -> ai_addrlen );
		if ( amountRead <= 0 ) {
			if ( amountRead == SOCKET_ERROR ) {
				error( "Error while ReceiveFrom." );
			}
			return 0;
		}
		castedAddress -> setPort( getSockAddr() );
		return amountRead;
	}

	Connection & Connection::operator=( Connection && socket ) {
		Address::operator=( Utility::toRValue( socket ) );
		this -> mSocket = Utility::toRValue( socket.mSocket );
		this -> mIsCreated = Utility::toRValue( socket.mIsCreated );
		this -> mIsListening = Utility::toRValue( socket.mIsListening );
		return *this;
	}


	bool Connection::send( char * buffer, int size, const Address & addressTo ) {
		//cast in order to resolve access problem
		const Connection * castedAddress = ( const Connection* ) &addressTo;
		if ( ::sendto( this -> mSocket, buffer, size, 0, castedAddress -> getSockAddr(), ( int ) castedAddress  -> getSockAddrLen() ) == SOCKET_ERROR ) {
			error( "Unable to send UDP data." );
			return false;
		}
		return true;
	}







}










