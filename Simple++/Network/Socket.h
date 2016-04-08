#pragma once


#include "Network.h"
#include "AddrInfo.h"
#include "Address.h"
#include "../Vector.h"
#include "../String.h"


namespace Network {

	class Socket : public Address{
	public:
		Socket(SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		Socket(const AddrInfo & addrInfo);
		~Socket();


		Socket & operator =(const Socket & socket);
		Socket & operator =(const AddrInfo & addrInfo);
		void setAddrInfo(const AddrInfo & addrInfo);

		
		using AddrInfo::getSockAddrLen;
		using AddrInfo::getIpFamily;
		using AddrInfo::getIpFamilyS;
		using AddrInfo::getSockType;
		using AddrInfo::getSockTypeS;
		using AddrInfo::getSockAddr;



		bool Listen(int maxClients = 100);
		static SOCKET ListenStatic(const AddrInfo & addrInfo, int maxClients = 100);
		bool Listen(const AddrInfo & addrInfo, unsigned short port, int maxClients = 100);
		bool Listen(const Address & address, unsigned short port, int maxClients = 100);
		bool Listen(const String & ip, const String & service, int maxClients = 100);
		bool Listen(const String & ip, unsigned short port, int maxClients = 100);
		bool Listen(unsigned short port, int maxClients = 100);


		bool Connect();
		static SOCKET ConnectStatic(const AddrInfo & addrInfo);
		bool Connect(const AddrInfo & addrInfo, unsigned short port);
		bool Connect(const Address & address, unsigned short port);
		bool Connect(const String & ip, const String & service);
		bool Connect(const String & ip, unsigned short port);


		bool Accept(Socket * clientSocket);
		bool Send(const char * buffer, int size);
		int Receive(char * buffer, int maxSize);

		Socket * ReceiveFrom(char * buffer, int * maxSize, Address * addressFrom);
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
		bool _tryConnect(const ADDRINFO * addrResults);
		bool _tryConnect(const Vector<const AddrInfo *> & addrInfoVector);
		bool _tryConnect(const AddrInfo & addrInfo);
		bool _tryListen(const ADDRINFO * addrResults, int maxClients);
		bool _tryListen(const Vector<const AddrInfo *> & addrInfoVector, int maxClients);
		bool _tryListen(const AddrInfo & addrInfo, int maxClients);




		SOCKET mSocket;
		bool mIsCreated;
		bool mIsListening;


		

	};




}




