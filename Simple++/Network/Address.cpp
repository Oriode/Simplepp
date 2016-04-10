#include "Address.h"


namespace Network {

	Address::Address(SockType sockType, IpFamily ipFamily) : 
		AddrInfo(sockType, ipFamily),
		mPort(0)
	{
		
	}

	Address::Address(const AddrInfo & addrInfo) : 
		AddrInfo(addrInfo),
		mPort(0)
	{
		_update();
	}

	Address::Address(const struct addrinfo & addrInfo) : 
		AddrInfo(addrInfo),
		mPort(0)
	{
		_update();

	}


	Address::Address(const String & ip, const String & service, SockType sockType /*= SockType::TCP*/, IpFamily ipFamily /*= IpFamily::Undefined*/) : 
		AddrInfo(ip, service, sockType, ipFamily),
		mPort(0)
	{
		_update();

	}

	Address::Address(const String & ip, const String & service, const AddrInfo & hints) :
		AddrInfo(ip, service, hints),
		mPort(0) 
	{
		_update();

	}

	Address::~Address() {
	}


	void Address::setIp(const String & ip){
		this -> mIp = ip;
	}

	const String & Address::getIp() {
		if ( !this -> mUpdated )
			_update();
		return this -> mIp;
	}

	unsigned short Address::getPort() {
		if ( !this -> mUpdated )
			_update();
		return this -> mPort;
	}

	void Address::setPort(unsigned short port){
		this -> mPort = port;
	}



	Address & Address::operator=(const AddrInfo & addrInfo){
		*((AddrInfo *)this) = addrInfo;
		setNext(NULL);
		this -> mUpdated = false;
		return *this;
	}

	Address & Address::operator=(const Address & address){
		AddrInfo::operator=(address);
		this -> mIp = address.mIp;
		this -> mPort = address.mPort;
		this -> mUpdated = address.mUpdated;
		return *this;

	}

	void Address::_update(){
		const sockaddr * sockAddr = getSockAddr();
		if ( sockAddr ) {
			setPort(getPort(*sockAddr));
			setIp(getNameInfo(*sockAddr, getSockAddrLen()));
		}
		this -> mUpdated = true;
	}

	void Address::setIpPortUpdated(bool value){
		this -> mUpdated = true;
	}



}


