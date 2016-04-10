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
	class Server : private Connection {
	public:
		Server(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		~Server();


		bool listen(unsigned short port, int maxClients = 100);
		bool listen(const std::string & ip, const std::string & service, int maxClients = 100);
		bool listen(const std::string & ip, unsigned int port, int maxClients = 100);
		bool listen(const AddrInfo & addrInfo, unsigned short port, int maxClients = 100);

		typename Vector<Connection * >::Size getNumSocket() const;

		bool Accept(Connection * clientSocket);
		bool Accept(unsigned int socketIndex, Connection * clientSocket);

		bool close();


		bool ReceiveFrom(char * buffer, int size, Address * addressFrom);

		using Connection::getPort;
		using Connection::getIp;

	private:
		void updateFdSet();
		bool _listen(const char * ip, const char * service, int maxClients = 100);
		bool _tryListen(const struct addrinfo * addrResults, int maxClients);
		bool _tryListen(const Vector<const AddrInfo *> & addrInfoVector, int maxClients);
		bool _tryListen(const AddrInfo & addrInfo, int maxClients);
		bool _tryListen(Connection * socket, int maxClients);

		Connection * _select();

		bool mIsBinded;
		Vector<Connection * > mSocketVector;
		fd_set mFdSet;
		fd_set mFdSetLastSelect;
	};


}


