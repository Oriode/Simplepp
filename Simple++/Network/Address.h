#pragma once

///@file Address.h
///@author Clément Gerber
///@date 10/04/16 (DMY)



#include "AddrInfo.h"




namespace Network {


	///@brief Extended and safer version of AddrInfo
	class Address : protected AddrInfo {
	public:
		///@brief Constructor from a SockType and an IpFamily
		///@param sockType SockType of this Address (TCP or UDP)
		///@param ipFamily IpFamily to set (IPv4, IPv6 or Undefined)
		Address(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);


		///@brief Constructor from a IP, Service, SockType and IpFamily
		///@param ip IP to connect to
		///@param service Service to be used.
		///@param sockType SockType
		///@param ipFamily IpFamily
		Address(const String & ip, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);

		///@brief Constructor from a IP, Service, SockType and IpFamily
		///@param ip IP to connect to
		///@param service Service to be used.
		///@param hints Hints to be used (sockType, ipFamily, flags, protocol) 
		Address(const String & ip, const String & service, const AddrInfo & hints);

		///@brief copy constructor to up cast
		///@param addrInfo
		Address(const AddrInfo & addrInfo);


		///@brief copy constructor
		///@param address object to copy
		Address(const Address & address);

		///@brief move constructor
		///@param address Object to move from.
		Address(Address && address);

		///@brief copy constructor from an old-school struct addrinfo
		///@param addrInfo struct addrinfo to copy
		Address(const struct addrinfo & addrInfo);

		///@brief destructor
		~Address();

		///@brief copy operator from an AddrInfo
		///@param addrInfo AddrInfo Object to copy
		Address & operator=(const AddrInfo & addrInfo);


		///@brief copy operator
		///@param address Object to copy
		Address & operator=(const Address & address);


		///@brief move operator
		///@param address object to move from
		///@return reference to this
		Address & operator = (Address && address);

		using AddrInfo::getNameInfo;
		using AddrInfo::getPort;
		using AddrInfo::getSockAddrLen;
		using AddrInfo::getIpFamily;
		using AddrInfo::getIpFamilyS;
		using AddrInfo::getSockType;
		using AddrInfo::getSockTypeS;
		using AddrInfo::getSockAddr;


		using AddrInfo::setSockType;
		using AddrInfo::setPort;


		///@brief get the port as unsigned short (this function use buffered values)
		///@return Port as unsigned short
		unsigned short getPort();


		///@brief get the IP as a String (this function use buffered values)
		///@return IP as String
		const String & getIp();

	protected:
		Address(ctor);

		void _update();
	private:

		String mIp;
		unsigned short mPort;


	};
}


