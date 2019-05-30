/**
 * @file		Network\BasicNetwork.h.
 *
 * @brief		Declares the basic network class
 */

#pragma once

#if defined WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#elif defined (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#else
#error "This software is not availible on this platform."
#endif

typedef struct sockaddr_in6 SOCKADDR_IN6;


#include "../Log.h"
#include "../String.h"
#include "../Utility.h"



namespace Network {

	/** @brief	IpFamily ( IPv4 or IPv6 ) */
	enum class IpFamily : int {
		IPv4 = PF_INET,
		IPv6 = PF_INET6,
		Undefined = PF_UNSPEC
	};


	/** @brief	Type of a Socket ( TCP or UDP ) */
	enum class SockType : int {
		TCP = SOCK_STREAM,
		UDP = SOCK_DGRAM
	};

	enum class Flags : unsigned int {
		Passive = AI_PASSIVE,
		NumericHost = AI_NUMERICHOST
	};

	enum class Error : int {
		NoError = 0,
		HostNotFound = 1,
		SocketError = 2
	};


	class Network {
	public:

		static bool init();
		static void close();

	private:
		static bool mIsInit;

	};

}





