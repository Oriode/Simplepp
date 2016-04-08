#pragma once

#include <string>
#include "Network.h"


namespace Network {

	class AddrInfo : public ADDRINFO {
	public:
		AddrInfo(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		AddrInfo(const AddrInfo & addrInfo);
		AddrInfo(const ADDRINFO & addrInfo);
		~AddrInfo();


		const ADDRINFO * getADDRINFO() const;
		const AddrInfo & getAddrInfo() const;

		void setSockAddr(const struct sockaddr * sockAddr, size_t sockAddrLen);


		AddrInfo & operator = (const AddrInfo & addrInfo);
		AddrInfo & operator = (const ADDRINFO & addrInfo);


		const struct sockaddr * getSockAddr() const;
		void newSockAddr(size_t newSize);


		void setSockAddrPort(unsigned short port);
		void setSockAddrPort(const struct sockaddr * sockAddr);

		size_t getSockAddrLen() const;
		void setIpFamily(IpFamily ipFamily);
		IpFamily getIpFamily(const std::string & ip);
		IpFamily getIpFamily() const;
		std::string getIpFamilyS() const;

		int getProtocol() const;
		void setProtocol(int protocol);

		void setSockType(SockType sockType);
		SockType getSockType() const;
		std::string getSockTypeS() const;
		void setFlags(int flags);

		int getFlags() const;

		void addFlag(Flags flags);

		void setNext(ADDRINFO * next);

		void setCanonName(const std::string & name);

		static std::string getNameInfo(const sockaddr * sockAddr, size_t sockAddrLen);
		static std::string getNameInfo(const ADDRINFO & addrInfo);
		std::string getNameInfo() const;
		static unsigned short getPort(const struct sockaddr * sockAddr);
		unsigned short getPort() const;
	};

}



