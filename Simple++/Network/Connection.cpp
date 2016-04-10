#include "Connection.h"


namespace Network {

	Connection::Connection(const AddrInfo & addrInfo) : Address(addrInfo),
		mSocket(0),
		mIsCreated(false),
		mIsListening(false)
	{
		
	}

	Connection::Connection(SockType sockType, IpFamily ipFamily) :
		mSocket(0),
		mIsCreated(false),
		mIsListening(false)
	{
		setSockType(sockType);
		setIpFamily(ipFamily);
	}


	Connection & Connection::operator=(const Connection & socket){
		close();
		Address::operator=(socket);
		this -> mSocket = socket.mSocket;
		this -> mIsCreated = socket.mIsCreated;
		this -> mIsListening = socket.mIsListening;
		return *this;
	}

	Connection & Connection::operator=(const AddrInfo & addrInfo){
		close();
		Address::operator=((AddrInfo)addrInfo);
		setIpPortUpdated(false);
		return *this;
	}

	Connection::~Connection(){
		close();
	}



	bool Connection::listen(int maxClients){
		if (!Network::init()) return false;

		if (this -> mIsCreated) close();

		if ((this -> mSocket = ListenStatic(*this, maxClients)) == SOCKET_ERROR){
			error("Unable to bind ip " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());
			return false;
		}

		log("Listening on " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with " + getSockTypeS());
		//log("Binded on " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());

		this -> mIsListening = (getSockType() == SockType::TCP);
		this -> mIsCreated = true;
		return true;


	}


	SOCKET Connection::ListenStatic(const AddrInfo & addrInfo, int maxClients){
		SOCKET newSocket = socket((int)addrInfo.getIpFamily(), (int)addrInfo.getSockType(), (int)addrInfo.getProtocol());
		if (newSocket == INVALID_SOCKET){
			return INVALID_SOCKET;
		}

		if (bind(newSocket, addrInfo.getSockAddr(), (int)addrInfo.getSockAddrLen()) == SOCKET_ERROR){
			closesocket(newSocket);
			return INVALID_SOCKET;
		}

		if (addrInfo.getSockType() == SockType::TCP){
			if (::listen(newSocket, maxClients) == SOCKET_ERROR){
				closesocket(newSocket);
				return INVALID_SOCKET;
			}
		}
		
		return newSocket;
	}

	bool Connection::listen(const String & ip, const String & service, int maxClients){
		return _listen(ip.toCString(), service.toCString(), maxClients);
	}

	bool Connection::listen(const String & ip, unsigned short port, int maxClients /*= 100*/){
		return _listen(ip.toCString(), std::to_string(port).c_str(), maxClients);
	}

	bool Connection::listen(unsigned short port, int maxClients /*= 100*/){
		return _listen(NULL, std::to_string(port).c_str(), maxClients);
	}

	bool Connection::listen(const AddrInfo & addrInfo, unsigned short port, int maxClients /*= 100*/){
		if (!Network::init()) return false;

		if (this -> mIsCreated) close();

		AddrInfo thisAddrInfo(addrInfo);
		thisAddrInfo.setIpFamily(getIpFamily());
		thisAddrInfo.setSockType(getSockType());
		thisAddrInfo.setSockAddrPort(port);

		if (!_tryListen(thisAddrInfo, maxClients)){
			error("Unable to bind ip " + thisAddrInfo.getIpFamilyS() + " : " + thisAddrInfo.getNameInfo() + " on port " + std::to_string(thisAddrInfo.getPort()) + " with protocol " + thisAddrInfo.getSockTypeS());
			return false;
		}

		log("Listening on " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with " + getSockTypeS());
		//log("Binded on " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());

		this -> mIsListening = (getSockType() == SockType::TCP);
		this -> mIsCreated = true;
		return true;
	}

	bool Connection::listen(const Address & address, unsigned short port, int maxClients /*= 100*/){
		return listen((AddrInfo)address, port, maxClients);
	}

	bool Connection::_listen(const char * ip, const char * service, int maxClients /*= 100*/){
		if (!Network::init()) return false;

		if (this -> mIsCreated) close();


		struct addrinfo * addrResults;
		if (getaddrinfo(ip, service, getAddrInfoStruct(), &addrResults)){
			error(String("Unable to retrieve address info on address  ") + ip + "@" + service);
			return false;
		}

		if (!_tryListen(addrResults, maxClients)){
			error("Unable to bind on " + getIpFamilyS() + " : " + ip + " on port " + service + " with Protocol " + getSockTypeS());
			return false;
		}

		//freeing the automatically allocated AddrInfos
		freeaddrinfo(addrResults);

		//log("Binded on " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());
		log("Listening on " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with " + getSockTypeS());

		this -> mIsListening = (getSockType() == SockType::TCP);
		this -> mIsCreated = true;
		return true;
	}


	bool Connection::connect(){
		if (!Network::init()) return false;

		if (this -> mIsCreated) close();


		if (!_tryConnect(*this)){
			error("Unable to connect to host " + getIpFamilyS() + " : " + getNameInfo() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());
			return false;
		}

		log("Connected to " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());

		this -> mIsCreated = true;
		return true;
	}


	SOCKET Connection::ConnectStatic(const AddrInfo & addrInfo){
		SOCKET newSocket = socket((int)addrInfo.getIpFamily(), (int)addrInfo.getSockType(), (int)addrInfo.getProtocol());
		if (newSocket == INVALID_SOCKET){
			return INVALID_SOCKET;
		}
		if (addrInfo.getSockType() == SockType::TCP){
			if (::connect(newSocket, addrInfo.getSockAddr(), (int)addrInfo.getSockAddrLen()) == SOCKET_ERROR){
				closesocket(newSocket);
				return INVALID_SOCKET;
			}
		}
		
		return newSocket;
	}

	bool Connection::connect(const String & ip, const String & service){
		return _connect(ip.toCString(), service.toCString());
	}

	bool Connection::connect(const String & ip, unsigned short port){
		return _connect(ip.toCString(), String::toString(port).toCString());
	}


	bool Connection::connect(const AddrInfo & addrInfo, unsigned short port){
		if (!Network::init()) return false;

		if (this -> mIsCreated) close();


		AddrInfo thisAddrInfo(addrInfo, getSockType(), getIpFamily(), port);


		if (!_tryConnect(thisAddrInfo)){
			error(String("Unable to connect to host ") << thisAddrInfo.getIpFamilyS() << " : " << thisAddrInfo.getNameInfo() << " on port " << thisAddrInfo.getPort() << " with protocol " + thisAddrInfo.getSockTypeS());
			return false;
		}
		log(String("Connected to ") << getIpFamilyS() << " : " << getIp() << " on port " << getPort() << " with protocol " << getSockTypeS());

		this -> mIsCreated = true;
		return true;
	}


	bool Connection::connect(const Address & address, unsigned short port){
		return connect((AddrInfo)address, port);
	}


	bool Connection::_connect(const char * ip, const char * service){
		if (!Network::init()) return false;

		if (this -> mIsCreated) close();



		struct addrinfo * addrResults;
		if (getaddrinfo(ip, service, getAddrInfoStruct(), &addrResults)){
			error(String("Unable to retrieve address info on address  ") << ip << "@" << service);
			return false;
		}

		if (!_tryConnect(addrResults)){
			error(String("Unable to connect to host ") << getIpFamilyS() << " : " << ip << " on port " << service << " with Protocol " << getSockTypeS());
			return false;
		}

		//freeing the automatically allocated AddrInfos
		freeaddrinfo(addrResults);

		log("Connected to " + getIpFamilyS() + " : " + getIp() + " on port " + std::to_string(getPort()) + " with protocol " + getSockTypeS());

		this -> mIsCreated = true;
		return true;
	}


	bool Connection::_tryConnect(const struct addrinfo * addrResults){
		Vector<const AddrInfo *> addrInfoVector;
		for (const struct addrinfo * AI = addrResults; AI != NULL; AI = AI -> ai_next)
			addrInfoVector.push((AddrInfo*)AI);
		return _tryConnect(addrInfoVector);
	}

	bool Connection::_tryConnect(const Vector<const AddrInfo *> & addrInfoVector){
		for (auto i = addrInfoVector.getBegin(); i != addrInfoVector.getEnd(); i++) {
			//Only support IPv4 or IPv6
			if (((*i) -> getIpFamily() != IpFamily::IPv4) && ((*i) -> getIpFamily() != IpFamily::IPv6))
				continue;

			return _tryConnect(*(*i));
		}
		return false;

	}

	bool Connection::_tryConnect(const AddrInfo & addrInfo){
		if (addrInfo.getIpFamily() == IpFamily::Undefined){
			AddrInfo addrInfoV4(addrInfo);
			addrInfoV4.setIpFamily(IpFamily::IPv4);

			SOCKET newSocket = ConnectStatic(addrInfoV4);
			if (newSocket != SOCKET_ERROR){
				this -> mSocket = newSocket;
				*this = addrInfo;
				return true;
			}

			AddrInfo addrInfoV6(addrInfo);
			addrInfoV6.setIpFamily(IpFamily::IPv6);

			newSocket = ConnectStatic(addrInfoV6);
			if (newSocket != SOCKET_ERROR){
				this -> mSocket = newSocket;
				*this = addrInfo;
				return true;
			}
		} else {
			SOCKET newSocket = ConnectStatic(addrInfo);
			if (newSocket != SOCKET_ERROR){
				this -> mSocket = newSocket;
				*this = addrInfo;
				return true;
			}
		}
		return false;
	}



	bool Connection::_tryListen(const struct addrinfo * addrResults, int maxClients){
		Vector<const AddrInfo *> addrInfoVector;
		for (const struct addrinfo * AI = addrResults; AI != NULL; AI = AI -> ai_next)
			addrInfoVector.push((AddrInfo*)AI);
		return _tryListen(addrInfoVector, maxClients);
	}

	bool Connection::_tryListen(const Vector<const AddrInfo *> & addrInfoVector, int maxClients){
		for (auto i = addrInfoVector.getBegin(); i != addrInfoVector.getEnd(); i++) {
			//Only support IPv4 or IPv6
			if (((*i) -> getIpFamily() != IpFamily::IPv4) && ((*i) -> getIpFamily() != IpFamily::IPv6))
				continue;

			return _tryListen(*(*i), maxClients);
		}
		return false;

	}

	bool Connection::_tryListen(const AddrInfo & addrInfo, int maxClients){
		if (addrInfo.getIpFamily() == IpFamily::Undefined){
			AddrInfo addrInfoV4(addrInfo);
			addrInfoV4.setIpFamily(IpFamily::IPv4);

			SOCKET newSocket = ConnectStatic(addrInfoV4);
			if (newSocket != SOCKET_ERROR){
				this -> mSocket = newSocket;
				*this = addrInfo;
				return true;
			}

			AddrInfo addrInfoV6(addrInfo);
			addrInfoV6.setIpFamily(IpFamily::IPv6);

			newSocket = ListenStatic(addrInfoV6, maxClients);
			if (newSocket != SOCKET_ERROR){
				this -> mSocket = newSocket;
				*this = addrInfo;
				return true;
			}
		}
		else {
			SOCKET newSocket = ListenStatic(addrInfo, maxClients);
			if (newSocket != SOCKET_ERROR){
				this -> mSocket = newSocket;
				*this = addrInfo;
				return true;
			}
		}
		return false;
	}











	
	void Connection::close(){
		if (this -> mIsCreated)
			closesocket(this -> mSocket);

		this -> mIsCreated = false;
		this -> mIsListening = false;
	}

	



	bool Connection::Send(const char * buffer, int size){
		if (getSockType() == SockType::TCP){
			if (send(this -> mSocket, buffer, size, 0) == SOCKET_ERROR){
				error("Unable to send TCP data.");
				return false;
			}
		} else if (getSockType() == SockType::UDP) {
			if (sendto(this -> mSocket, buffer, size, 0, getSockAddr(), (int)getSockAddrLen()) == SOCKET_ERROR){
				error("Unable to send UDP data.");
				return false;
			}
		}
		return true;
	}

	bool Connection::Accept(Connection * clientSocket){
		if (!this -> mIsCreated) {
			error("Socket not binded.");
			return false;
		}

		if (!this -> mIsListening){
			error("This socket is not able to accept anything, he is not listening.");
			return false;
		}


		clientSocket -> newSockAddr(sizeof(SOCKADDR_STORAGE));
		SOCKET clientSock;
		clientSock = accept(this -> mSocket, clientSocket -> ai_addr, (int*)&clientSocket -> ai_addrlen);

		if (clientSock == INVALID_SOCKET){
			error("Unable to accept new client");
			return false;
		}
		auto sockAddr = clientSocket -> getSockAddr();
		debug(
			if ( sockAddr )
			log(String::toString(AddrInfo::getPort(*sockAddr)).toCString());
			);

		clientSocket -> mSocket = clientSock;
		clientSocket -> mIsCreated = true;
		clientSocket -> setIpFamily(getIpFamily());
		clientSocket -> setSockType(getSockType());
		clientSocket -> setPort(getPort());
		clientSocket -> setSockAddrPort(getSockAddr());
		if ( sockAddr ) clientSocket -> setIp(getNameInfo(*sockAddr, clientSocket -> getSockAddrLen()));
		clientSocket -> setIpPortUpdated(true);

		return true;
	}


	SOCKET Connection::getSocket() const{
		return this -> mSocket;
	}


	int Connection::Receive(char * buffer, int maxSize){
		int amountRead = recv(this -> mSocket, buffer, maxSize, 0);
		if (amountRead <= 0){
			if (amountRead == SOCKET_ERROR){
				error("Error while receiving !");
			}
			return 0;
		}
		return amountRead;
	}

	Connection * Connection::ReceiveFrom(char * buffer, int * size, Address * addressFrom){
		//cast in order to resolve access problem
		Connection * castedAddress = (Connection*)addressFrom;
		castedAddress -> newSockAddr(sizeof(SOCKADDR_STORAGE));
		int amountRead = recvfrom(this -> mSocket, buffer, *size, 0, castedAddress -> ai_addr, (int*)&castedAddress -> ai_addrlen);
		if (amountRead <= 0){
			if (amountRead == SOCKET_ERROR){
				error("Error while ReceiveFrom.");
			}
			return 0;
		}
		castedAddress -> setSockAddrPort(getSockAddr());

		return this;
	}

	void Connection::setAddrInfo(const AddrInfo & addrInfo){
		*this = addrInfo;
	}

	bool Connection::SendTo(char * buffer, int size, const Address & addressTo){
		//cast in order to resolve access problem
		const Connection * castedAddress = (const Connection*)&addressTo;
		if (sendto(this -> mSocket, buffer, size, 0, castedAddress -> getSockAddr(), (int)castedAddress  -> getSockAddrLen()) == SOCKET_ERROR){
			error("Unable to send UDP data.");
			return false;
		}
		return true;
	}







}










