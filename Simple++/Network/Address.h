#pragma once

#include "AddrInfo.h"

namespace Network {

	class Address : protected AddrInfo {
	public:
		Address(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		Address(const AddrInfo & addrInfo);
		Address(const ADDRINFO & addrInfo);
		~Address();

		Address & operator=(const AddrInfo & addrInfo);
		Address & operator=(const Address & address);

		using AddrInfo::getNameInfo;
		using AddrInfo::getPort;

		unsigned short getPort() ;
		const std::string & getIp() ;



		
	protected:
		void setIp(const std::string);
		void setPort(unsigned short port);

		void setIpPortUpdated(bool value);
	private:
		void _update();

		std::string mIp;
		unsigned short mPort;

		bool mUpdated;

	};
}


