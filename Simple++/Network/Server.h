/**
 * @file		Network\Server.h.
 *
 * @brief 		Declares the server class
 * @author	Clément Gerber
 * @date		10/04/16 (DMY)
 */

#pragma once

#include <algorithm>
#include "BasicNetwork.h"
#include "Connection.h"
#include "../Vector.h"
#include "../Math/Math.h"

 /** @brief	. */
namespace Network {

	/** @brief	Represent a listening server who can handle multiple protocol or ip family */
	template<typename T>
	class ServerT {
	public:
		/** @brief	Create a new ServerT<T>. */
		ServerT();

		/** @brief	destructor */
		~ServerT();

		/**
		 * @brief 	Add a listen address to this server
		 *
		 * @param 	port	  	Port onto listen.
		 * @param 	sockType  	(Optional) TCP or UDP.
		 * @param 	ipFamily  	(Optional) IPv4, IPV6 or Undefined for both.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		/**
		 * @brief 	Add a listen address to this server
		 *
		 * @param 	address   	Address as StringASCII (IP or domain name)
		 * @param 	service   	to look for.
		 * @param 	sockType  	(Optional) TCP or UDP.
		 * @param 	ipFamily  	(Optional) IPv4, IPV6 or Undefined for both.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( const StringASCII & address, const StringASCII & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		/**
		 * @brief 	Add a listen address to this server
		 *
		 * @param 	address   	Address as StringASCII (IP or domain name)
		 * @param 	port	  	Port onto listen.
		 * @param 	sockType  	(Optional) TCP or UDP.
		 * @param 	ipFamily  	(Optional) IPv4, IPV6 or Undefined for both.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( const StringASCII & address, unsigned int port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		/**
		 * @brief 	Add a listen address to this server
		 *
		 * @param 	addrInfo  	Address to be binded.
		 * @param 	maxClients	(Optional) Maximum number of clients accepted (Only for TCP)
		 *
		 * @returns	true if success else false.
		 */
		bool listen( const Address & addrInfo, int maxClients = 100 );

		/**
		 * @brief 	get the number of connection this server has
		 *
		 * @returns	Actual number of connections of this server.
		 */
		Size getNumConnections() const;

		/**
		 * @brief 	get the maximum number of connections a server can have.
		 *
		 * @returns	maximum number of connections of a server.
		 */
		static size_t getMaximumNbConnections();

		/**
		 * @brief 	Accept a new Client from one of the connections (only when listening on TCP)
		 *
		 * @param [in,out]	clientSocket	Object to be filled with the incoming client (the object has to be allocated)
		 *
		 * @returns	true if success else false.
		 */
		bool accept( Connection * clientSocket );

		/**
		 * @brief 	Close all the connections.
		 *
		 * @returns	true if success else false.
		 */
		bool close();

		/**
		 * @brief 	Wait to receive a message from one of the connections
		 *
		 * @param [in,out]	buffer	   	to be filled with the new message.
		 * @param 		  	maxSize	   	Maximum size of the message in bytes.
		 * @param [in,out]	addressFrom	Address to be filled with the incoming sender (the object has to be already allocated)
		 *
		 * @returns	number of bytes read.
		 */
		int receive( char * buffer, int maxSize, Address * addressFrom );

	private:
		/** @brief	Updates the fd set */
		void updateFdSet();

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

		/**
		 * @brief 	Try listen
		 *
		 * @param [in,out]	socket	  	If non-null, the socket.
		 * @param 		  	maxClients	The maximum clients.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool _tryListen( Connection * socket, int maxClients );

		/**
		 * @brief 	Gets the select
		 *
		 * @returns	Null if it fails, else a pointer to a Connection.
		 */
		Connection * _select();

		/** @brief	True if is binded, false if not */
		bool mIsBinded;
		/** @brief	The socket vector */
		Vector<Connection * > mSocketVector;

		fd_set mFdSet;
		fd_set mFdSetTmp;
	};

	using Server = ServerT<int>;
}

#include "Server.hpp"


