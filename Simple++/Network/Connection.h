#pragma once


///@file Connection.h
///@author Clément Gerber
///@date 10/04/16 (DMY)

#include "Network.h"
#include "AddrInfo.h"
#include "Address.h"
#include "../Vector.h"
#include "../String.h"


namespace Network {

	///@brief Connection/Socket Class
	class Connection : public Address {
	public:
		Connection(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		Connection(const AddrInfo & addrInfo);
		~Connection();


		Connection & operator =(const Connection & socket);
		Connection & operator =(const AddrInfo & addrInfo);
		void setAddrInfo(const AddrInfo & addrInfo);

		

		bool listen(int maxClients = 100);
		static SOCKET ListenStatic(const AddrInfo & addrInfo, int maxClients = 100);
		bool listen(const AddrInfo & addrInfo, unsigned short port, int maxClients = 100);
		bool listen(const Address & address, unsigned short port, int maxClients = 100);
		bool listen(const String & ip, const String & service, int maxClients = 100);
		bool listen(const String & ip, unsigned short port, int maxClients = 100);
		bool listen(unsigned short port, int maxClients = 100);


		bool connect();
		static SOCKET ConnectStatic(const AddrInfo & addrInfo);
		bool connect(const AddrInfo & addrInfo, unsigned short port);
		bool connect(const Address & address, unsigned short port);
		bool connect(const String & ip, const String & service);
		bool connect(const String & ip, unsigned short port);


		bool Accept(Connection * clientSocket);
		bool Send(const char * buffer, int size);
		int Receive(char * buffer, int maxSize);

		Connection * ReceiveFrom(char * buffer, int * maxSize, Address * addressFrom);
		bool SendTo(char * buffer, int size, const Address & address);


		void close();

		SOCKET getSocket() const;


	protected:
		using AddrInfo::setFlags;
		using AddrInfo::getFlags;
		using AddrInfo::addFlag;
		using AddrInfo::setIpFamily;
		using AddrInfo::setSockType;


	private:
		bool _connect(const char * ip, const char * service);
		bool _listen(const char * ip, const char * service, int maxClients = 100);
		bool _tryConnect(const struct addrinfo * addrResults);
		bool _tryConnect(const Vector<const AddrInfo *> & addrInfoVector);
		bool _tryConnect(const AddrInfo & addrInfo);
		bool _tryListen(const struct addrinfo * addrResults, int maxClients);
		bool _tryListen(const Vector<const AddrInfo *> & addrInfoVector, int maxClients);
		bool _tryListen(const AddrInfo & addrInfo, int maxClients);




		SOCKET mSocket;
		bool mIsCreated;
		bool mIsListening;
	};




}




