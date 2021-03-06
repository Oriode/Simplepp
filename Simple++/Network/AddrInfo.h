#pragma once

///@file AddrInfo.h
///@author Cl�ment Gerber
///@date 10/04/16 (DMY)


#include "BasicNetwork.h"



namespace Network {


	///@brief Representing a struct addrinfo, all the info of an address without the "list" side ai_next is not used. This class can be down casted freely to struct addrinfo. Warning when using this class, you may prefer using Address Class which is more safer.
	class AddrInfo : public addrinfo {
	public:
		///@brief Create an AddrInfo from a SockType and an IpFamily
		///@param sockType Type of the socket used for this connection (TCP or UDP)
		///@param ipFamily The IP family used for this connection (IPv4, IPv6 or both)
		AddrInfo( SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );

		///@brief Constructor from a IP, Service, SockType and IpFamily
		///@param address to connect to (IP or domain name)
		///@param service Service to be used.
		///@param sockType SockType
		///@param ipFamily IpFamily
		AddrInfo( const StringASCII & address, const StringASCII & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );

		///@brief Constructor from a IP, Service, SockType and IpFamily
		///@param address to connect to (IP or domain name)
		///@param service Service to be used.
		///@param hints Hints to be used (sockType, ipFamily, flags, protocol) 
		AddrInfo( const StringASCII & address, const StringASCII & service, const AddrInfo & hints );

		///@brief Copy constructor
		///@param addrInfo object to copy
		AddrInfo( const AddrInfo & addrInfo );


		///@brief move constructor
		///@param addrInfo object to be moved from
		AddrInfo( AddrInfo && addrInfo );


		///@brief Copy constructor with an another SockType, IpFamily and port
		///@param addrInfo object to copy
		AddrInfo( const AddrInfo & addrInfo, SockType sockType, IpFamily ipFamily, unsigned short port );


		///@brief Copy constructor from an old-school struct addrinfo
		///@param addrInfo old-school struct addrinfo
		AddrInfo( const struct addrinfo & addrInfo );

		///@brief destructor
		~AddrInfo();

		///@brief get the old-school struct addrinfo inside this type.
		///@return the old-school struct addrinfo structure. 
		const struct addrinfo * getAddrInfoStruct() const;


		///@brief set the struct sockaddr contained inside this object
		///@param sockAddr struct sockaddr to set (can be NULL)
		///@param sockAddrLen size of the sockAddr in bytes
		void setSockAddr( const struct sockaddr * sockAddr, size_t sockAddrLen );


		///@brief set the inside address
		///@param ip IP to look for
		///@param service Service to look for ("http", 80, ...)
		///@param ipFamily IPv4, IPv6 or Undefined to look for the two
		//void setAddress(const StringASCII & ip, const StringASCII & service, IpFamily ipFamily = IpFamily::Undefined);


		///@brief copy operator
		///@param addrInfo other object to copy
		///@return this object as a reference
		AddrInfo & operator = ( const AddrInfo & addrInfo );


		///@brief copy operator from a old-school struct addrinfo
		///@param addrInfo struct addrinfo to copy
		///@return this object as a reference
		AddrInfo & operator = ( const struct addrinfo & addrInfo );



		///@brief move operator
		///@param addrInfo from which to move
		///@return reference of this
		AddrInfo & operator = ( AddrInfo && addrInfo );

		///@brief get the struct sockaddr of this object
		const struct sockaddr * getSockAddr() const;


		///@brief set the struct sockaddr to a new one filled with 0
		///@param newSize size in bytes of the new sockaddr
		void newSockAddr( size_t newSize );


		///@brief set the sockaddr port from an another sockaddr
		///@param sockaddr struct sockaddr where to copy the port
		void setPort( const struct sockaddr * sockAddr );


		///@brief get the length in bytes of the struct sockaddr
		///@return length in bytes of the sockaddr
		size_t getSockAddrLen() const;


		///@brief get the IP family
		///@return IP family
		IpFamily getIpFamily( const std::string & ip );


		///@brief get the port
		///@return port if the struct sockaddr * is not NULL, 0 else
		unsigned short getPort() const;


		///@brief get the IP family
		///@return the IP family
		IpFamily getIpFamily() const;


		///@brief get the IP�family as a StringASCII
		///@return IP family as a string
		const StringASCII & getIpFamilyS() const;

		///@brief get the Protocol
		///@return Protocol
		int getProtocol() const;


		///@brief get the SockType (UDP or TCP)
		///@return SockType
		SockType getSockType() const;


		///@brief get the SockType as a StringASCII
		///@return SockType as a StringASCII
		const StringASCII & getSockTypeS() const;

		///@brief set flags
		///@param flags Flags to set
		void setFlags( int flags );

		///@brief get Flags
		///@return Flags
		int getFlags() const;

		///@brief add a Flag to this object
		///@flags Flag to add
		void addFlag( Flags flags );


		///@brief set the CanonName of this object
		///@param name CanonName to set
		void setCanonName( const StringASCII & name );


		///@brief alias of getnameinfo() and cast the result to a StringASCII
		///@param sockAddr SockAddr from which to get the name
		///@param sockAddrLen length in bytes of the struct sockaddr
		///@return StringASCII representing the struct sockaddr
		static StringASCII getNameInfo( const struct sockaddr & sockAddr, size_t sockAddrLen );

		///@brief alias of getnameinfo() of the  struct sockaddr inside the struct addrinfo
		///@param addrInfo getnameinfo() will be executed to the struct sockaddr inside
		///@return StringASCII
		static StringASCII getNameInfo( const struct addrinfo & addrInfo );



		///@brief getnameinfo() on the struct sockaddr inside this object
		///@return StringASCII representing the struct sockaddr
		StringASCII getNameInfo() const;


		///@brief get the port a struct sockaddr as an unsigned short
		///@return Port as unsigned short
		static unsigned short getPort( const struct sockaddr & sockAddr );


		///@brief set the sockaddr port 
		///@param port Port as an unsigned short
		void setPort( unsigned short port );


		///@brief set the IP family of this addrinfo (this won't change the struct sockaddr and may corrupt this object)
		///@param ipFamily IP Family to set
		void setIpFamily( IpFamily ipFamily );

		///@brief set the Protocol of this (this won't change the struct sockaddr and may corrupt this object)
		///@param protocol Protocol
		void setProtocol( int protocol );

		///@brief set the SockType (TCP or UDP) (this won't change the struct sockaddr and may corrupt this object)
		///@param sockType
		void setSockType( SockType sockType );

	protected:
		enum ctor { null };
		AddrInfo( ctor );

	};

}



