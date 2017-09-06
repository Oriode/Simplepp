#include "Address.h"


namespace Network {

	Address::Address(SockType sockType, IpFamily ipFamily) : 
		AddrInfo(sockType, ipFamily)
	{
		
	}

	Address::Address(const AddrInfo & addrInfo) : 
		AddrInfo(addrInfo)
	{
		_update();
	}

	Address::Address(const struct addrinfo & addrInfo) : 
		AddrInfo(addrInfo)
	{
		_update();

	}


	Address::Address(const StringASCII & ip, const StringASCII & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/) : 
		AddrInfo(ip, service, sockType, ipFamily)
	{
		_update();
	}

	Address::Address(const StringASCII & ip, const StringASCII & service, const AddrInfo & hints) :
		AddrInfo(ip, service, hints)
	{
		_update();
	}

	Address::Address(ctor) : AddrInfo(ctor::null) {

	}

	Address::Address(const Address & address) : 
		AddrInfo(address)
	{
		_update();
	}

	Address::Address(Address && address) : 
		AddrInfo(ctor::null)
	{
		*this = Utility::toRValue(address);
	}

	Address::~Address() {
	}



	const StringASCII & Address::getIp() {
		return this -> mIp;
	}

	Address & Address::operator=(Address && address) {
		AddrInfo::operator=(Utility::toRValue(address));
		this -> mIp = Utility::toRValue(address.mIp);
		this -> mPort = Utility::toRValue(address.mPort);
		return *this;
	}

	unsigned short Address::getPort() {
		return this -> mPort;
	}





	Address & Address::operator=(const AddrInfo & addrInfo){
		AddrInfo::operator=(addrInfo);
		_update();
		return *this;
	}

	Address & Address::operator=(const Address & address){
		AddrInfo::operator=(address);
		this -> mIp = address.mIp;
		this -> mPort = address.mPort;
		return *this;

	}

	void Address::_update(){
		const sockaddr * sockAddr = getSockAddr();
		if ( sockAddr ) {
			this -> mPort = getPort(*sockAddr);
			this -> mIp = getNameInfo(*sockAddr, getSockAddrLen());
		}
	}





}


