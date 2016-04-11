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
		Connection();
		Connection(const String & ip, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		Connection(const AddrInfo & addrInfo);
		Connection(const Address & address);
		Connection(Connection && connection);


		~Connection();


		Connection & operator =(Connection && socket);
		Connection & operator =(const AddrInfo & addrInfo);

		

		bool listen(int maxClients = 100);
		bool listen(const AddrInfo & addrInfo, int maxClients = 100);
		bool listen(const String & ip, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);
		bool listen(const String & ip, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);
		bool listen(unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);


		bool connect();
		bool connect(const AddrInfo & addrInfo);
		bool connect(const String & ip, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		bool connect(const String & ip, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);


		bool accept(Connection * clientSocket);
		bool send(const char * buffer, int size);
		int receive(char * buffer, int maxSize);

		Connection * receiveFrom(char * buffer, int * maxSize, Address * addressFrom);
		bool sendTo(char * buffer, int size, const Address & address);


		void close();

		SOCKET getSocket() const;


		static SOCKET listenStatic(const AddrInfo & addrInfo, int maxClients = 100);
		static SOCKET connectStatic(const AddrInfo & addrInfo);


	protected:
		Connection(ctor);

		using AddrInfo::setFlags;
		using AddrInfo::getFlags;
		using AddrInfo::addFlag;
		using AddrInfo::setIpFamily;


	private:
		bool _connect(const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		bool _listen(const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100);
		bool _tryConnect(const struct addrinfo * addrResults);
		bool _tryConnect(AddrInfo * addrInfo);
		bool _tryListen(const struct addrinfo * addrResults, int maxClients);
		bool _tryListen(AddrInfo * addrInfo, int maxClients);




		SOCKET mSocket;
		bool mIsCreated;
		bool mIsListening;
	};




}




