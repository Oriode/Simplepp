#include "Network.h"

namespace Network {

	bool Network::mIsInit = false;


	bool Network::init(){

		if (Network::mIsInit) return true;
#ifdef WIN32
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
			error("WSAStartup failed !");
			WSACleanup();
			return false;
		}
#endif
		return true;
		Network::mIsInit = true;

	}





	void Network::close(){

		if (!Network::mIsInit) return;
#ifdef WIN32
		WSACleanup();
#endif
		Network::mIsInit = false;

	}

}

