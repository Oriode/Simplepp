/**
 * @file		Network\ConnectionT<T>.h.
 *
 * @brief 		Declares the connection class
 * @author	Clément Gerber
 * @date		10/04/16 (DMY)
 */

#pragma once

#include "BasicNetwork.h"
#include "AddrInfo.h"
#include "Address.h"
#include "../Vector.h"
#include "../String.h"



 /** @brief	. */
namespace Network {

	/** @brief	ConnectionT<T>/Socket Class */
	template<typename T>
	class ConnectionT : public Address {
	public:
		/** @brief	Create a connection not initialized. */
		ConnectionT();

		/**
		 * @brief 	Create a connection already initialized
		 * @param 	address 	address as a StringASCII (ip or domain name)
		 * @param 	service 	Service or port as a string.
		 * @param 	sockType	(Optional) TCP or UDP.
		 * @param 	ipFamily	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 */
		 //ConnectionT( const StringASCII & address, const StringASCII & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );
		 //ConnectionT(const AddrInfo & addrInfo);

		 /**
		  * @brief 	Constructor from an address
		  *
		  * @param 	address	Address to asign to this connection.
		  */
		ConnectionT( const Address & address );

		/**
		 * @brief 	Move constructor
		 *
		 * @param [in,out]	connection	Object to be moved from.
		 */
		ConnectionT( ConnectionT<T> && connection );

		/** @brief	destructor */
		~ConnectionT();

		/**
		 * @brief 	brief move operator
		 *
		 * @param [in,out]	socket	Object to be moved from.
		 *
		 * @returns	reference to this.
		 */
		ConnectionT<T> & operator =( ConnectionT<T> && socket );
		//ConnectionT<T> & operator =(const AddrInfo & addrInfo);

		/**
		 * @brief 	get the Address of this connection
		 *
		 * @returns	Address of this connection.
		 */
		const Address & getAddress() const;

		/**
		 * @brief 	set the Address of this connection (this will close the connection)
		 *
		 * @param 	address	New Address of this connection.
		 */
		void setAddess( const Address & address );

		/**
		 * @brief 	Listen for clients /!\ The connection can only listen on one address/port at a time
		 *
		 * @param 	maxClients	(Optional) Maximum number of clients accepted.
		 *
		 * @returns	true if success else false (Only for TCP)
		 */
		bool listen( int maxClients = 100 );

		/**
		 * @brief 	Listen for clients on a selected Address /!\ The connection can only listen on one address/port at a time
		 *
		 * @param 	address   	Address to be binded.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( const Address & address, int maxClients = 100 );

		/**
		 * @brief 	Listen for clients on a selected address/service
		 *
		 * @param 	address   	address as a StringASCII (ip or domain name)
		 * @param 	service   	Service or port as a string.
		 * @param 	sockType  	(Optional) TCP or UDP.
		 * @param 	ipFamily  	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( const StringASCII & address, const StringASCII & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		/**
		 * @brief 	Listen for clients on a selected address/port
		 *
		 * @param 	address   	address as a StringASCII (ip or domain name)
		 * @param 	port	  	port.
		 * @param 	sockType  	(Optional) TCP or UDP.
		 * @param 	ipFamily  	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( const StringASCII & address, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		/**
		 * @brief 	Listen for clients on a selected port
		 *
		 * @param 	port	  	port.
		 * @param 	sockType  	(Optional) TCP or UDP.
		 * @param 	ipFamily  	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );


		/**
		 * @brief 	Connect to UDP or TCP server
		 *
		 * @returns	true if success else false.
		 */
		bool connect();


		/**
		 * @brief 	Connect to a specified Address
		 *
		 * @param 	address	Address to connect to.
		 *
		 * @returns	true if success else false.
		 */
		bool connect( const Address & address );


		/**
		 * @brief 	Connect to a specified address/service
		 *
		 * @param 	address 	address as a StringASCII (ip or domain name)
		 * @param 	service 	Service or port as a string.
		 * @param 	sockType	(Optional) TCP or UDP.
		 * @param 	ipFamily	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 *
		 * @returns	true if success else false.
		 */
		bool connect( const StringASCII & address, const StringASCII & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );


		/**
		 * @brief 	Connect to a specified address/port
		 *
		 * @param 	address 	address as a StringASCII (ip or domain name)
		 * @param 	port		port.
		 * @param 	sockType	(Optional) TCP or UDP.
		 * @param 	ipFamily	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 *
		 * @returns	true if success else false.
		 */
		bool connect( const StringASCII & address, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );


		/**
		 * @brief 	Accept a new client (only when listening on TCP). This is a blocking method.
		 *
		 * @param [in,out]	clientSocket	clientSocket Pointer to a ConnectionT<T> object that will be filled when a client connect (the object has to be already allocated)
		 *
		 * @returns	true when a new client has connected.
		 */
		bool accept( ConnectionT<T> * clientSocket );


		/**
		 * @brief 	Send data to the connection (after a connect)
		 *
		 * @param 	buffer	Data buffer to be sent.
		 * @param 	size  	size of the data buffer.
		 *
		 * @returns	true if success else false.
		 */
		bool send( const char * buffer, int size );


		/**
		 * @brief 	Wait for data from the connection (usually used for TCP transaction)
		 *
		 * @param [in,out]	buffer 	Data buffer where to store the read bytes.
		 * @param 		  	maxSize	Maximum size of the buffer.
		 *
		 * @returns	number of bytes read.
		 */
		int receive( char * buffer, int maxSize );

		/**
		 * @brief 	Wait for data from the connection and retrieve the address of the sender. (usually used for UDP transaction)
		 *
		 * @param [in,out]	buffer	   	Data buffer where to store the read bytes.
		 * @param 		  	maxSize	   	Maximum size of the buffer.
		 * @param [in,out]	addressFrom	addressFrom Address Object to be filled with the address of sender. (the object has to be already allocated)
		 *
		 * @returns	number of bytes read.
		 */
		int receive( char * buffer, int maxSize, Address * addressFrom );


		/**
		 * @brief 	Send data to an address
		 *
		 * @param [in,out]	buffer 	Data buffer to be sent.
		 * @param 		  	size   	size of the data buffer.
		 * @param 		  	address	Address to send to.
		 *
		 * @returns	true if success else false.
		 */
		bool send( char * buffer, int size, const Address & address );


		/** @brief	close the connection */
		void close();

		/**
		 * @brief 	get the SOCKET (unrecommended)
		 * 			return SOCKET of this connection (0 if not connected)
		 *
		 * @returns	The socket.
		 */
		SOCKET getSocket() const;

		/**
		 * @brief 	Retrieve if the connection is connected or not.
		 *
		 * @returns	if connected or not.
		 */
		bool isConnected() const;

		/**
		 * @brief 	listen and return the Socket created
		 *
		 * @param 	addrInfo  	Address to listen on.
		 * @param 	maxClients	(Optional) Maximum number of clients.
		 *
		 * @returns	SOCKET created.
		 */
		static SOCKET listenStatic( const AddrInfo & addrInfo, int maxClients = 100 );

		/**
		 * @brief 	connect and return the Socket created
		 *
		 * @param 	addrInfo	Address to connect on.
		 *
		 * @returns	SOCKET created.
		 */
		static SOCKET connectStatic( const AddrInfo & addrInfo );

	protected:
		/**
		 * @brief 	Constructor
		 *
		 * @param 	parameter1	The first parameter.
		 */
		ConnectionT( ctor );

		/** @brief	The address information set flags */
		using AddrInfo::setFlags;
		/** @brief	The address information get flags */
		using AddrInfo::getFlags;
		/** @brief	The address information add flag */
		using AddrInfo::addFlag;

	private:
		/**
		 * @brief 	Connects
		 *
		 * @param 	ip			The IP.
		 * @param 	service 	The service.
		 * @param 	sockType	(Optional) Type of the sock.
		 * @param 	ipFamily	(Optional) The IP family.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _connect( const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );

		/**
		 * @brief 	Listens
		 *
		 * @param 	ip		  	The IP.
		 * @param 	service   	The service.
		 * @param 	sockType  	(Optional) Type of the sock.
		 * @param 	ipFamily  	(Optional) The IP family.
		 * @param 	maxClients	(Optional) The maximum clients.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _listen( const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		/**
		 * @brief 	Try connect
		 *
		 * @param 	addrResults	The address results.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _tryConnect( const addrinfo * addrResults );

		/**
		 * @brief 	Try connect
		 *
		 * @param [in,out]	addrInfo	If non-null, information describing the address.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _tryConnect( AddrInfo * addrInfo );

		/**
		 * @brief 	Try listen
		 *
		 * @param 	addrResults	The address results.
		 * @param 	maxClients 	The maximum clients.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _tryListen( const addrinfo * addrResults, int maxClients );

		/**
		 * @brief 	Try listen
		 *
		 * @param [in,out]	addrInfo  	If non-null, information describing the address.
		 * @param 		  	maxClients	The maximum clients.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _tryListen( AddrInfo * addrInfo, int maxClients );

		/** @brief	The socket */
		SOCKET mSocket;
		/** @brief	True if is created, false if not */
		bool mIsCreated;
		/** @brief	True if actually listenning, False otherwise. */
		bool mIsListening;
	};

	using Connection = ConnectionT<int>;

}

#include "Connection.hpp"




