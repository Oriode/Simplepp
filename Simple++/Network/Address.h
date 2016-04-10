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

		using AddrInfo::getNameInfo;
		using AddrInfo::getPort;
		using AddrInfo::getSockAddrLen;
		using AddrInfo::getIpFamily;
		using AddrInfo::getIpFamilyS;
		using AddrInfo::getSockType;
		using AddrInfo::getSockTypeS;
		using AddrInfo::getSockAddr;


		///@brief get the port as unsigned short (this function use buffered values)
		///@return Port as unsigned short
		unsigned short getPort();


		///@brief get the IP as a String (this function use buffered values)
		///@return IP as String
		const String & getIp();


	protected:
		void setIp(const String & ip);
		void setPort(unsigned short port);

		void setIpPortUpdated(bool value);
	private:
		void _update();

		String mIp;
		unsigned short mPort;

		bool mUpdated;

	};
}


