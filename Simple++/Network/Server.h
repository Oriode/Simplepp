#pragma once

///@file Server.h
///@author Clément Gerber
///@date 10/04/16 (DMY)

#include <algorithm>
#include "Network.h"
#include "Connection.h"
#include "../Vector.h"
#include "../Math.h"

namespace Network {

	///@brief Represent a listening server who can handle multiple protocol or ip family
	class Server {
	public:
		Server();
		~Server();


		bool listen(unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);
		bool listen(const String & ip, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);
		bool listen(const String & ip, unsigned int port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined,int maxClients = 100);
		bool listen(const AddrInfo & addrInfo, int maxClients = 100);

		typename Vector<Connection * >::Size getNumSocket() const;

		bool accept(Connection * clientSocket);
		bool accept(unsigned int socketIndex, Connection * clientSocket);

		bool close();

		bool receiveFrom(char * buffer, int size, Address * addressFrom);

	private:
		void updateFdSet();
		bool _listen(const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);
		bool _tryListen(const struct addrinfo * addrResults, int maxClients);
		bool _tryListen(AddrInfo * addrInfo, int maxClients);
		bool _tryListen(Connection * socket, int maxClients);

		Connection * _select();

		bool mIsBinded;
		Vector<Connection * > mSocketVector;
		fd_set mFdSet;
		fd_set mFdSetTmp;
	};


}


