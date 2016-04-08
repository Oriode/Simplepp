#include "Address.h"


namespace Network {

	Address::Address(SockType sockType, IpFamily ipFamily) : AddrInfo(sockType, ipFamily),
	mPort(0),
	mUpdated(false)
	{
		
	}

	Address::Address(const AddrInfo & addrInfo) : AddrInfo(addrInfo),
		mPort(0),
		mUpdated(false)
	{
		setNext(NULL);
		_update();
	}

	Address::Address(const ADDRINFO & addrInfo) : AddrInfo(addrInfo),
		mPort(0),
		mUpdated(false)
	{
		setNext(NULL);
		_update();

	}


	Address::~Address(){
	}


	void Address::setIp(const std::string ip){
		this->mIp = ip;
	}

	const std::string & Address::getIp() {
		_update();
		return this->mIp;
	}

	unsigned short Address::getPort() {
		_update();
		return this->mPort;
	}

	void Address::setPort(unsigned short port){
		this->mPort = port;
	}



	

	Address & Address::operator=(const AddrInfo & addrInfo){
		*((AddrInfo *)this) = addrInfo;
		setNext(NULL);
		_update();
		return *this;
	}

	Address & Address::operator=(const Address & address){
		AddrInfo::operator=(address);
		this->mIp = address.mIp;
		this->mPort = address.mPort;
		this->mUpdated = address.mUpdated;
		return *this;

	}

	void Address::_update(){
		if (this->mUpdated) return;
		setPort(getPort(getSockAddr()));
		setIp(getNameInfo(getSockAddr(), getSockAddrLen()));
		this->mUpdated = true;
	}

	void Address::setIpPortUpdated(bool value){
		this->mUpdated = true;
	}



}


