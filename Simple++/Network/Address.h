/**
 * @file		Network\AddressT.h.
 *
 * @brief		Declares the address class
 * @author	Clément Gerber
 * @date		10/04/16 (DMY)
 */
#pragma once

#include "AddrInfo.h"

 /** @brief	. */
namespace Network {


	/** @brief	Extended and safer version of AddrInfo */
	template<typename T>
	class AddressT : protected AddrInfo {
	public:
		/**
		 * @brief		Constructor from a SockType and an IpFamily
		 *
		 * @param		sockType SockType of this AddressT (TCP or UDP).
		 * @param		ipFamily IpFamily to set (IPv4, IPv6 or Undefined).
		 */
		AddressT( SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );


		/**
		 * @brief		Constructor from a IP, Service, SockType and IpFamily
		 *
		 * @param		address 	to connect to (IP or domain name)
		 * @param		service 	Service to be used.
		 * @param		sockType	(Optional) SockType.
		 * @param		ipFamily	(Optional) IpFamily.
		 */
		AddressT( const StringASCII & address, const StringASCII & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );

		/**
		 * @brief		Constructor from a IP, Service, SockType and IpFamily
		 *
		 * @param		address	to connect to (IP or domain name)
		 * @param		service	Service to be used.
		 * @param		hints  	Hints to be used (sockType, ipFamily, flags, protocol)
		 */
		AddressT( const StringASCII & address, const StringASCII & service, const AddrInfo & hints );

		/**
		 * @brief		copy constructor to up cast
		 *
		 * @param		addrInfo	.
		 */
		AddressT( const AddrInfo & addrInfo );


		/**
		 * @brief		copy constructor
		 *
		 * @param		address	object to copy.
		 */
		AddressT( const AddressT<T> & address );

		/**
		 * @brief		move constructor
		 *
		 * @param [in,out]	address	Object to move from.
		 */
		AddressT( AddressT<T> && address );

		/**
		 * @brief		copy constructor from an old-school addrinfo
		 *
		 * @param		addrInfo	addrinfo to copy.
		 */
		AddressT( const addrinfo & addrInfo );

		/** @brief	destructor */
		~AddressT();

		/**
		 * @brief		copy operator from an AddrInfo
		 *
		 * @param		addrInfo	AddrInfo Object to copy.
		 *
		 * @returns	A shallow copy of this object.
		 */
		AddressT<T> & operator=( const AddrInfo & addrInfo );


		/**
		 * @brief		copy operator
		 *
		 * @param		address	Object to copy.
		 *
		 * @returns	A shallow copy of this object.
		 */
		AddressT<T> & operator=( const AddressT<T> & address );


		/**
		 * @brief		move operator
		 *
		 * @param [in,out]	address	object to move from.
		 *
		 * @returns	reference to this.
		 */
		AddressT<T> & operator = ( AddressT<T> && address );

		/** @brief	Information describing the address information get name */
		using AddrInfo::getNameInfo;
		/** @brief	The address information get port */
		using AddrInfo::getPort;
		/** @brief	Length of the address information get sock address */
		using AddrInfo::getSockAddrLen;
		/** @brief	The address information get IP family */
		using AddrInfo::getIpFamily;
		/** @brief	The address information get IP family s */
		using AddrInfo::getIpFamilyS;
		/** @brief	Type of the address information get sock */
		using AddrInfo::getSockType;
		/** @brief	The address information get sock type s */
		using AddrInfo::getSockTypeS;
		/** @brief	The address information get sock address */
		using AddrInfo::getSockAddr;


		/** @brief	Type of the address information set sock */
		using AddrInfo::setSockType;
		/** @brief	The address information set port */
		using AddrInfo::setPort;


		/**
		 * @brief		get the port as unsigned short (this function use buffered values)
		 *
		 * @returns	Port as unsigned short.
		 */
		unsigned short getPort();


		/**
		 * @brief		get the IP as a StringASCII (this function use buffered values)
		 *
		 * @returns	IP as StringASCII.
		 */
		const StringASCII & getIp();

	protected:
		/**
		 * @brief		Uninitialized Constructor.
		 *
		 * @param		ctor Special parameter for accessing this constructor.
		 */
		AddressT( ctor );

		/** @brief	Updates this object */
		void _update();
	private:
		/** @brief	The IP */
		StringASCII mIp;
		unsigned short mPort;


	};

	using Address = AddressT<int>;

}


#include "Address.hpp"


