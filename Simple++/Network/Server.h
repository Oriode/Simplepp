#pragma once

///@file Server.h
///@author Cl�ment Gerber
///@date 10/04/16 (DMY)

#include <algorithm>
#include "BasicNetwork.h"
#include "Connection.h"
#include "../Vector.h"
#include "../Math.h"

namespace Network {

	///@brief Represent a listening server who can handle multiple protocol or ip family
	class Server {
	public:
		///@brief Create a new Server
		Server();


		///@brief destructor
		~Server();

		///@brief Add a listen address to this server
		///@param port Port onto listen.
		///@param sockType TCP or UDP
		///@param ipFamily IPv4, IPV6 or Undefined for both
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );

		///@brief Add a listen address to this server
		///@param address Address as String (IP or domain name)
		///@param service to look for.
		///@param sockType TCP or UDP
		///@param ipFamily IPv4, IPV6 or Undefined for both
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( const String & address, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );


		///@brief Add a listen address to this server
		///@param address Address as String (IP or domain name)
		///@param port Port onto listen.
		///@param sockType TCP or UDP
		///@param ipFamily IPv4, IPV6 or Undefined for both
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( const String & address, unsigned int port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );


		///@brief Add a listen address to this server
		///@param addrInfo Address to be binded
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( const Address & addrInfo, int maxClients = 100 );


		///@brief get the number of connection this server has
		///@return Actual number of connections of this server.
		typename Vector<Connection * >::Size getNumConnections() const;


		///@brief get the maximum number of connections a server can have.
		///@return maximum number of connections of a server.
		static size_t getMaximumNbConnections();


		///@brief Accept a new Client from one of the connections (only when listening on TCP)
		///@param clientSocket Object to be filled with the incoming client (the object has to be allocated)
		///@return true if success else false
		bool accept( Connection * clientSocket );


		///@brief close all the connections
		///@return true if success else false
		bool close();



		///@brief Wait to receive a message from one of the connections
		///@param buffer to be filled with the new message.
		///@param maxSize Maximum size of the message in bytes
		///@param addressFrom Address to be filled with the incoming sender (the object has to be already allocated)
		///@return number of bytes read
		int receive( char * buffer, int maxSize, Address * addressFrom );

	private:
		void updateFdSet();
		bool _listen( const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );
		bool _tryListen( const struct addrinfo * addrResults, int maxClients );
		bool _tryListen( AddrInfo * addrInfo, int maxClients );
		bool _tryListen( Connection * socket, int maxClients );

		Connection * _select();

		bool mIsBinded;
		Vector<Connection * > mSocketVector;
		fd_set mFdSet;
		fd_set mFdSetTmp;
	};


}


