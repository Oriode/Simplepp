#pragma once

#include <algorithm>

#include "Network.h"
#include "Socket.h"
#include "../Vector.h"
#include "../Math.h"

namespace Network {

	class MultiConnectionsServer : private Socket {
	public:
		MultiConnectionsServer(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		~MultiConnectionsServer();


		bool Listen(unsigned short port, int maxClients = 100);
		bool Listen(const std::string & ip, const std::string & service, int maxClients = 100);
		bool Listen(const std::string & ip, unsigned int port, int maxClients = 100);
		bool Listen(const AddrInfo & addrInfo, unsigned short port, int maxClients = 100);

		size_t getNumSocket() const;

		bool Accept(Socket * clientSocket);
		bool Accept(unsigned int socketIndex, Socket * clientSocket);

		bool close();


		bool ReceiveFrom(char * buffer, int size, Address * addressFrom);

		using Socket::getPort;
		using Socket::getIp;

	private:
		void updateFdSet();
		bool _listen(const char * ip, const char * service, int maxClients = 100);
		bool _tryListen(const ADDRINFO * addrResults, int maxClients);
		bool _tryListen(const Vector<const AddrInfo *> & addrInfoVector, int maxClients);
		bool _tryListen(const AddrInfo & addrInfo, int maxClients);
		bool _tryListen(Socket * socket, int maxClients);

		Socket * _select();

		bool mIsBinded;
		Vector<Socket * > mSocketVector;
		fd_set mFdSet;
		fd_set mFdSetLastSelect;
	};


}


