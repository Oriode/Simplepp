#include "Server.h"


namespace Network {

	Server::Server(SockType sockType, IpFamily ipFamily) : Connection(sockType, ipFamily),
		mIsBinded(false)
	{

	}


	Server::~Server(){
		close();
	}



	bool Server::listen(unsigned short port, int maxClients){
		return _listen(NULL, std::to_string(port).c_str(), maxClients);
	}


	bool Server::listen(const std::string & ip, const std::string & service, int maxClients){
		return _listen(ip.c_str(), service.c_str(), maxClients);
	}

	bool Server::listen(const std::string & ip, unsigned int port, int maxClients){
		return _listen(ip.c_str(), std::to_string(port).c_str(), maxClients);
	}

	bool Server::listen(const AddrInfo & addrInfo, unsigned short port, int maxClients /*= 100*/){
		if (!Network::init()) return false;

		if (this -> mIsBinded) close();

		AddrInfo thisAddrInfo(addrInfo);
		thisAddrInfo.setIpFamily(getIpFamily());
		thisAddrInfo.setSockType(getSockType());
		thisAddrInfo.setSockAddrPort(port);

		if (((int) _tryListen(thisAddrInfo, maxClients)) == SOCKET_ERROR){
			error("Unable to bind ip " + thisAddrInfo.getIpFamilyS() + " : " + thisAddrInfo.getNameInfo() + " on port " + std::to_string(thisAddrInfo.getPort()) + " with protocol " + thisAddrInfo.getSockTypeS());
			return false;
		}
		updateFdSet();

		//Update the port and the ip of this connection
		setPort(this -> mSocketVector[0] -> getPort());
		setIp(this -> mSocketVector[0] -> getIp());
		setIpPortUpdated(true);

		this -> mIsBinded = true;
		return true;
	}

	bool Server::_listen(const char * ip, const char * service, int maxClients /*= 100*/){
		if (this -> mIsBinded) return false;

		if (!Network::init()) return false;

		addFlag(Flags::Passive);
		addFlag(Flags::NumericHost);

		struct addrinfo * addrResults;
		if (getaddrinfo(ip, service, getAddrInfoStruct(), &addrResults)){
			error(std::string("Unable to retreive address info on address  ") + ip + "@" + service);
			return false;
		}

		if (_tryListen(addrResults, maxClients) == false){
			error("Unable to bind on " + getIpFamilyS() + " : " + ip + " on port " + service + " with Protocol " + getSockTypeS());
			return false;
		}

		//freeing the automatically allocated AddrInfos
		freeaddrinfo(addrResults);

		updateFdSet();

		//Update the port and the ip of this connection
		setPort(this -> mSocketVector[0] -> getPort());
		setIp(this -> mSocketVector[0] -> getIp());
		setIpPortUpdated(true);

		this -> mIsBinded = true;
		return true;
	}


	bool Server::_tryListen(const struct addrinfo * addrResults, int maxClients){
		Vector<const AddrInfo *> addrInfoVector;
		for (const struct addrinfo * AI = addrResults; AI != NULL; AI = AI -> ai_next)
			addrInfoVector.push((AddrInfo*)AI);
		return _tryListen(addrInfoVector, maxClients);
	}

	bool Server::_tryListen(const Vector<const AddrInfo *> & addrInfoVector, int maxClients){
		bool result = false;
		for (auto i = addrInfoVector.getBegin(); i != addrInfoVector.getEnd(); i++) {
			
			if (this -> mSocketVector.getSize() >= FD_SETSIZE) {
				warn("getaddrinfo returned more addresses than we could use.\n");
				break;
			}
			
			//Only support IPv4 or IPv6
			if (((*i) -> getIpFamily() != IpFamily::IPv4) && ((*i) -> getIpFamily() != IpFamily::IPv6))
				continue;

			result = _tryListen(*(*i), maxClients) || result;
		}
		return result;
	}

	bool Server::_tryListen(const AddrInfo & addrInfo, int maxClients){
		if (addrInfo.getIpFamily() == IpFamily::Undefined){
			AddrInfo addrInfoV4(addrInfo);
			addrInfoV4.setIpFamily(IpFamily::IPv4);

			bool result1 = _tryListen(new Connection(addrInfoV4), maxClients);

			AddrInfo addrInfoV6(addrInfo);
			addrInfoV6.setIpFamily(IpFamily::IPv6);

			bool result2 = _tryListen(new Connection(addrInfoV6), maxClients);
			return result2 || result1;
		} else {
			return _tryListen(new Connection(addrInfo), maxClients);
		}
		return false;
	}


	bool Server::_tryListen(Connection * socket, int maxClients){
		if (this -> mSocketVector.getSize() >= FD_SETSIZE) {
			warn("getaddrinfo returned more addresses than we could use.\n");
			return false;
		}

		if (socket -> listen(maxClients)){
			this -> mSocketVector.push(socket);
			return true;
		}
		return false;
	}











	bool Server::close(){
		if (!this -> mIsBinded) return false;


		for (unsigned int i = 0; i < this -> mSocketVector.getSize(); i++){
			this -> mSocketVector[i] -> close();
			delete this -> mSocketVector[i];
		}
		this -> mSocketVector.clear();

		this -> mIsBinded = false;

		return true;
	}

	bool Server::Accept(Connection * clientSocket){
		if (getNumSocket() == 1)
			return Accept(0, clientSocket);

		Connection * selectedSocket = _select();
		if (selectedSocket)
			return selectedSocket -> Accept(clientSocket);
		 else 
			return false;

	}

	bool Server::Accept(unsigned int socketIndex, Connection * clientSocket){
		return this -> mSocketVector[socketIndex] -> Accept(clientSocket);
	}

	void Server::updateFdSet(){
		this -> mFdSet.fd_count = (u_int) Math::min<Vector<Connection * >::Size>(this -> mSocketVector.getSize(), 64);
		for (unsigned int i = 0; i < this -> mSocketVector.getSize() && i < 64; i++){
			this -> mFdSet.fd_array[i] = this -> mSocketVector[i] -> getSocket();
		}

		this -> mFdSetLastSelect.fd_count = 0;
	}

	typename Vector<Connection * >::Size Server::getNumSocket() const{
		return this -> mSocketVector.getSize();
	}

	Connection * Server::_select(){
		if (this -> mFdSetLastSelect.fd_count == 0){
			FD_ZERO(&this -> mFdSetLastSelect);
			for (unsigned int i = 0; i < this -> mFdSet.fd_count; i++){
				FD_SET(this -> mFdSet.fd_array[i], &this -> mFdSetLastSelect);
			}

			if (select((int)getNumSocket(), &this -> mFdSet, 0, 0, 0) == SOCKET_ERROR){
				error("Select failed !");
				return NULL;
			}
		}

		if (this -> mFdSetLastSelect.fd_count != 0){
			SOCKET activeSocket = this -> mFdSetLastSelect.fd_array[this -> mFdSetLastSelect.fd_count - 1];
			this -> mFdSetLastSelect.fd_count--;

			for (auto i = this -> mSocketVector.begin(); i != this -> mSocketVector.end(); i++){
				if ((*i) -> getSocket() == activeSocket){
					return (*i);
				}
			}
		}
		return NULL;
	}

	bool Server::ReceiveFrom(char * buffer, int size, Address * addressFrom){
		Connection * selectedSocket = _select();
		if (selectedSocket)
			return selectedSocket -> ReceiveFrom(buffer, &size, addressFrom) != NULL;
		else 
			return false;
	}












}


