namespace Network {

	template<typename T>
	AddressT<T>::AddressT( SockType sockType, IpFamily ipFamily ) :
		AddrInfo( sockType, ipFamily ) {
	}

	template<typename T>
	AddressT<T>::AddressT( const AddrInfo & addrInfo ) :
		AddrInfo( addrInfo ) {
		_update();
	}

	template<typename T>
	AddressT<T>::AddressT( const addrinfo & addrInfo ) :
		AddrInfo( addrInfo ) {
		_update();
	}

	template<typename T>
	AddressT<T>::AddressT( const StringASCII & ip, const StringASCII & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/ ) :
		AddrInfo( ip, service, sockType, ipFamily ) {
		_update();
	}

	template<typename T>
	AddressT<T>::AddressT( const StringASCII & ip, const StringASCII & service, const AddrInfo & hints ) :
		AddrInfo( ip, service, hints ) {
		_update();
	}

	template<typename T>
	AddressT<T>::AddressT( ctor ) : AddrInfo( ctor::null ) {

	}

	template<typename T>
	AddressT<T>::AddressT( const AddressT<T> & address ) :
		AddrInfo( address ) {
		_update();
	}

	template<typename T>
	AddressT<T>::AddressT( AddressT<T> && address ) :
		AddrInfo( ctor::null ) {
		*this = Utility::toRValue( address );
	}

	template<typename T>
	AddressT<T>::~AddressT() {}


	template<typename T>
	const StringASCII & AddressT<T>::getIp() {
		return this -> mIp;
	}

	template<typename T>
	AddressT<T> & AddressT<T>::operator=( AddressT<T> && address ) {
		AddrInfo::operator=( Utility::toRValue( address ) );
		this -> mIp = Utility::toRValue( address.mIp );
		this -> mPort = Utility::toRValue( address.mPort );
		return *this;
	}

	template<typename T>
	unsigned short AddressT<T>::getPort() {
		return this -> mPort;
	}

	template<typename T>
	AddressT<T> & AddressT<T>::operator=( const AddrInfo & addrInfo ) {
		AddrInfo::operator=( addrInfo );
		_update();
		return *this;
	}

	template<typename T>
	AddressT<T> & AddressT<T>::operator=( const AddressT<T> & address ) {
		AddrInfo::operator=( address );
		this -> mIp = address.mIp;
		this -> mPort = address.mPort;
		return *this;

	}

	template<typename T>
	void AddressT<T>::_update() {
		const sockaddr * sockAddr = getSockAddr();
		if ( sockAddr ) {
			this -> mPort = getPort( *sockAddr );
			this -> mIp = getNameInfo( *sockAddr, getSockAddrLen() );
		}
	}





}


