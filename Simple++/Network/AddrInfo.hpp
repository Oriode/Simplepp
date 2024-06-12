#include "AddrInfo.h"
namespace Network {

	template<typename T>
	AddrInfoT<T>::AddrInfoT( const AddrInfoT<T>& addrInfo ) {
		this -> ai_canonname = NULL;
		this -> ai_addr = NULL;
		this -> ai_next = NULL;

		*this = addrInfo;
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( const addrinfo& addrInfo ) {
		this -> ai_canonname = NULL;
		this -> ai_addr = NULL;
		this -> ai_next = NULL;

		*this = addrInfo;
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/ ) {
		setSockType( sockType );
		setIpFamily( ipFamily );
		setFlags( 0 );
		setProtocol( 0 );
		this -> ai_addrlen = 0;

		this -> ai_canonname = NULL;
		this -> ai_addr = NULL;
		this -> ai_next = NULL;
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( const AddrInfoT<T>& addrInfo, SockType sockType, IpFamily ipFamily, unsigned short port ) {
		this -> ai_canonname = NULL;
		this -> ai_addr = NULL;
		this -> ai_next = NULL;

		this -> ai_addrlen = 0;

		*this = ( ( addrinfo ) addrInfo );
		setSockType( sockType );
		setIpFamily( ipFamily );
		setPort( port );
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( const StringASCII& ip, const StringASCII& service, SockType sockType, IpFamily ipFamily /*= IpFamily::Undefined*/ ) {
		setSockType( sockType );
		setIpFamily( ipFamily );

		addrinfo* addrResults;
		if ( getaddrinfo( ip.getData(), service.getData(), this, &addrResults ) ) {
			ERROR_SPP( StringASCII( "Unable to retrieve address info on address  " ) << ip << "@" << service );
		}

		*this = *addrResults;
		freeaddrinfo( addrResults );
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( const StringASCII& ip, const StringASCII& service, const AddrInfoT<T>& hints ) {
		addrinfo* addrResults;
		if ( getaddrinfo( ip.getData(), service.getData(), &hints, &addrResults ) ) {
			ERROR_SPP( StringASCII( "Unable to retrieve address info on address  " ) << ip << "@" << service );
		}

		*this = *addrResults;
		freeaddrinfo( addrResults );
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( AddrInfoT<T>&& addrInfo ) {
		*this = Utility::toRValue( addrInfo );
	}

	template<typename T>
	AddrInfoT<T>::AddrInfoT( ctor ) {
		this -> ai_flags = 0;
		this -> ai_family = 0;
		this -> ai_protocol = 0;
		this -> ai_socktype = 0;
		this -> ai_addrlen = size_t( 0 );
		this -> ai_canonname = NULL;
		this -> ai_addr = NULL;
		this -> ai_next = NULL;
	}

	template<typename T>
	AddrInfoT<T>::~AddrInfoT() {
		delete[] this -> ai_addr;
		delete[] this -> ai_canonname;

		delete ( AddrInfoT<T> * ) this -> ai_next;
	}

	template<typename T>
	AddrInfoT<T>& AddrInfoT<T>::operator=( const AddrInfoT<T>& addrInfo ) {
		return operator=( ( addrinfo& ) addrInfo );
	}

	template<typename T>
	AddrInfoT<T>& AddrInfoT<T>::operator=( const addrinfo& addrInfo ) {
		this -> ai_family = addrInfo.ai_family;
		this -> ai_flags = addrInfo.ai_flags;
		this -> ai_next = addrInfo.ai_next;
		this -> ai_protocol = addrInfo.ai_protocol;
		this -> ai_socktype = addrInfo.ai_socktype;

		setSockAddr( addrInfo.ai_addr, addrInfo.ai_addrlen );

		if ( addrInfo.ai_canonname != NULL ) {
			size_t textSize = StringASCII::getSize( addrInfo.ai_canonname );
			this -> ai_canonname = new char[ textSize + 1 ];
			memcpy( this -> ai_canonname, addrInfo.ai_canonname, textSize + 1 );
		} else {
			this -> ai_canonname = NULL;
		}

		this -> ai_next = NULL;
		return *this;
	}

	template<typename T>
	size_t AddrInfoT<T>::getSockAddrLen() const {
		return this -> ai_addrlen;
	}

	template<typename T>
	void AddrInfoT<T>::setIpFamily( IpFamily ipFamily ) {
		this -> ai_family = ( int ) ipFamily;
	}

	template<typename T>
	void AddrInfoT<T>::setSockType( SockType sockType ) {
		this -> ai_socktype = ( int ) sockType;
	}

	template<typename T>
	inline void AddrInfoT<T>::printAddrInfo() const {

		const addrinfo* currentAddrInfo( this );

		while ( currentAddrInfo ) {
			Log::increaseIndent();
			Log::displayLog( __func__, String::format( "ai_flags:\t%", this -> ai_flags ) );
			Log::displayLog( __func__, String::format( "ai_family:\t%", this -> ai_family ) );
			Log::displayLog( __func__, String::format( "ai_socktype:\t%", this -> ai_socktype ) );
			Log::displayLog( __func__, String::format( "ai_protocol:\t%", this -> ai_protocol ) );
			Log::displayLog( __func__, String::format( "ai_addrlen:\t%", this -> ai_addrlen ) );
			if ( this->ai_canonname ) {
				Log::displayLog( __func__, String::format( "ai_canonname:\t%", this -> ai_canonname ) );
			}
			if ( this->ai_addr ) {
				Log::increaseIndent();
				Log::displayLog( __func__, String::format( "sa_family:\t%", this -> ai_addr->sa_family ) );
				Log::displayLog( __func__, String::format( "sa_data:\t%", this ->ai_addr-> sa_data ) );
				Log::lowerIndent();
			}
			Log::lowerIndent();
			currentAddrInfo = this->ai_next;

		}
	}

	template<typename T>
	void AddrInfoT<T>::setFlags( int flags ) {
		this -> ai_flags = flags;
	}

	template<typename T>
	int AddrInfoT<T>::getFlags() const {
		return this -> ai_flags;
	}

	template<typename T>
	void AddrInfoT<T>::addFlag( Flags flags ) {
		this -> ai_flags |= ( unsigned int ) flags;
	}

	template<typename T>
	IpFamily AddrInfoT<T>::getIpFamily() const {
		return ( IpFamily ) this -> ai_family;
	}

	template<typename T>
	IpFamily AddrInfoT<T>::getIpFamily( const StringASCII& ip ) {
		for ( typename StringASCII::Iterator it( ip.getBegin() ); it != ip.getEnd(); ip.iterate( &it ) ) {
			if ( ip.getValueIt( it ) == StringASCII::ElemType( ':' ) ) return IpFamily::IPv6;
			if ( ip.getValueIt( it ) == StringASCII::ElemType( '.' ) ) return IpFamily::IPv4;
		}
		return IpFamily::Undefined;
	}

	template<typename T>
	inline StringASCII AddrInfoT<T>::getIp() const {
		const sockaddr* sockAddr = getSockAddr();
		if ( sockAddr ) {
			return getNameInfo( *sockAddr, getSockAddrLen() );
		}
		return StringASCII::null;
	}

	template<typename T>
	int AddrInfoT<T>::getProtocol() const {
		return this -> ai_protocol;
	}

	template<typename T>
	AddrInfoT<T>& AddrInfoT<T>::operator=( AddrInfoT<T>&& addrInfo ) {
		( ( addrinfo ) *this ) = ( ( addrinfo ) Utility::toRValue( addrInfo ) );
		addrInfo.ai_addr = NULL;
		addrInfo.ai_canonname = NULL;
		addrInfo.ai_next = NULL;
		return *this;
	}

	template<typename T>
	const sockaddr* AddrInfoT<T>::getSockAddr() const {
		return this -> ai_addr;
	}

	template<typename T>
	SockType AddrInfoT<T>::getSockType() const {
		return ( SockType ) this -> ai_socktype;
	}

	template<typename T>
	void AddrInfoT<T>::setCanonName( const StringASCII& name ) {
		delete[] this -> ai_canonname;
		if ( name.getSize() ) {
			this -> ai_canonname = new char[ name.getSize() + 1 ];
			memcpy( this -> ai_canonname, name.getData(), name.getSize() + 1 );
		} else {
			this -> ai_canonname = NULL;
		}
	}

	template<typename T>
	void AddrInfoT<T>::setProtocol( int protocol ) {
		this -> ai_protocol = protocol;
	}

	template<typename T>
	void AddrInfoT<T>::newSockAddr( size_t newSize ) {
		this -> ai_addrlen = newSize;
		delete[] this -> ai_addr;
		if ( newSize ) {
			this -> ai_addr = ( sockaddr* ) new char[ newSize ];
			memset( this -> ai_addr, 0, newSize );
		} else {
			this -> ai_addr = NULL;
		}
	}

	template<typename T>
	const StringASCII& AddrInfoT<T>::getSockTypeS() const {
		static const StringASCII tcp( "TCP" );
		static const StringASCII udp( "UDP" );


		return ( ( SockType ) this -> ai_socktype == SockType::TCP ? tcp : udp );
	}

	template<typename T>
	const StringASCII& AddrInfoT<T>::getIpFamilyS() const {
		static const StringASCII ipv4( "IPv4" );
		static const StringASCII ipv6( "IPv6" );
		static const StringASCII ipUndefined( "IPv4 & IPv6" );


		switch ( ( IpFamily ) this -> ai_family ) {
			case IpFamily::IPv4:
				return ipv4;
			case IpFamily::IPv6:
				return ipv6;
			case IpFamily::Undefined:
				return ipUndefined;
		}
		return StringASCII::null;
	}

	template<typename T>
	const addrinfo* AddrInfoT<T>::getAddrInfoStruct() const {
		return this;
	}

	template<typename T>
	StringASCII AddrInfoT<T>::getNameInfo( const sockaddr& sockAddr, size_t sockAddrLen ) {
		char nameBuffer[ 100 ];
		if ( getnameinfo( &sockAddr, ( socklen_t ) sockAddrLen, nameBuffer, sizeof( nameBuffer ), NULL, 0, NI_NUMERICHOST ) == SOCKET_ERROR )
			return StringASCII::null;
		else
			return StringASCII( nameBuffer );
	}

	template<typename T>
	StringASCII AddrInfoT<T>::getNameInfo( const addrinfo& addrInfo ) {
		if ( addrInfo.ai_addr )
			return getNameInfo( *addrInfo.ai_addr, addrInfo.ai_addrlen );
		else
			return StringASCII::null;
	}

	template<typename T>
	StringASCII AddrInfoT<T>::getNameInfo() const {
		return getNameInfo( *this );
	}

	template<typename T>
	unsigned short AddrInfoT<T>::getPort( const sockaddr& sockAddr ) {
		if ( sockAddr.sa_family == AF_INET )
			return ntohs( ( ( struct sockaddr_in& ) sockAddr ).sin_port );
		else
			return ntohs( ( ( struct sockaddr_in6& ) sockAddr ).sin6_port );
	}

	template<typename T>
	unsigned short AddrInfoT<T>::getPort() const {
		if ( this -> ai_addr )
			return getPort( *this -> ai_addr );
		else
			return 0;
	}

	template<typename T>
	void AddrInfoT<T>::setSockAddr( const sockaddr* sockAddr, size_t sockAddrLen ) {
		if ( sockAddr == NULL ) {
			delete[] this -> ai_addr;
			this -> ai_addr = NULL;
			this -> ai_addrlen = 0;
		} else {
			if ( this -> ai_addrlen != sockAddrLen ) {
				delete[] this -> ai_addr;
				this -> ai_addr = ( sockaddr* ) new char[ sockAddrLen ];
				this -> ai_addrlen = sockAddrLen;
			}
			memcpy( this -> ai_addr, sockAddr, sockAddrLen );
		}

	}

	template<typename T>
	void AddrInfoT<T>::setPort( unsigned short port ) {
		if ( this -> ai_addr != NULL ) {
			if ( this -> ai_addr -> sa_family == AF_INET )
				( ( struct sockaddr_in* ) this -> ai_addr ) -> sin_port = htons( port );
			else
				( ( struct sockaddr_in6* ) this -> ai_addr ) -> sin6_port = htons( port );
		}
	}

	template<typename T>
	void AddrInfoT<T>::setPort( const sockaddr* sockAddr ) {
		if ( this -> ai_addr != NULL ) {
			if ( this -> ai_addr -> sa_family == AF_INET )
				( ( struct sockaddr_in* ) this -> ai_addr ) -> sin_port = ( ( struct sockaddr_in* ) sockAddr ) -> sin_port;
			else
				( ( struct sockaddr_in6* ) this -> ai_addr ) -> sin6_port = ( ( struct sockaddr_in6* ) sockAddr ) -> sin6_port;
		}
	}

}

