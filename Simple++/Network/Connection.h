#pragma once


///@file Connection.h
///@author Cl�ment Gerber
///@date 10/04/16 (DMY)

#include "BasicNetwork.h"
#include "AddrInfo.h"
#include "Address.h"
#include "../Vector.h"
#include "../String.h"



namespace Network {

	///@brief Connection/Socket Class
	class Connection : public Address {
	public:
		///@brief create a connection not initialized
		Connection();


		///@brief Create a connection already initialized
		///@param address address as a String (ip or domain name)
		///@param service Service or port as a string
		///@param sockType TCP or UDP
		///@param ipFamily IPv4 or IPv6 or Undefined for testing the two
		//Connection(const String & address, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);
		//Connection(const AddrInfo & addrInfo);


		///@brief Constructor from an address
		///@param address Address to asign to this connection
		Connection( const Address & address );





		///@brief Move constructor
		///@param connection Object to be moved from.
		Connection( Connection && connection );

		///@brief destructor
		~Connection();


		///brief move operator
		///@param connection Object to be moved from.
		///@return reference to this
		Connection & operator =( Connection && socket );


		//Connection & operator =(const AddrInfo & addrInfo);


		///@brief get the Address of this connection
		///@return Address of this connection
		const Address & getAddress() const;



		///@brief set the Address of this connection (this will close the connection)
		///@param address New Address of this connection.
		void setAddess( const Address & address );


		///@brief Listen for clients /!\ The connection can only listen on one address/port at a time
		///@param maxClients Maximum number of clients accepted
		///@return true if success else false (Only for TCP)
		bool listen( int maxClients = 100 );


		///@brief Listen for clients on a selected Address /!\ The connection can only listen on one address/port at a time
		///@param addrInfo Address to be binded
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( const Address & address, int maxClients = 100 );


		///@brief Listen for clients on a selected address/service
		///@param address address as a String (ip or domain name)
		///@param service Service or port as a string
		///@param sockType TCP or UDP
		///@param ipFamily IPv4 or IPv6 or Undefined for testing the two
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( const String & address, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );


		///@brief Listen for clients on a selected address/port
		///@param address address as a String (ip or domain name)
		///@param port port
		///@param sockType TCP or UDP
		///@param ipFamily IPv4 or IPv6 or Undefined for testing the two
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( const String & address, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );



		///@brief Listen for clients on a selected port
		///@param port port
		///@param sockType TCP or UDP
		///@param ipFamily IPv4 or IPv6 or Undefined for testing the two
		///@param maxClients Maximum number of clients accepted (Only for TCP)
		///@return true if success else false
		bool listen( unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );


		///@brief Connect to UDP or TCP server
		///@return true if success else false
		bool connect();


		///@brief Connect to a specified Address
		///@param addrInfo Address to connect to.
		///@return true if success else false
		bool connect( const Address & address );


		///@brief Connect to a specified address/service
		///@param address address as a String (ip or domain name)
		///@param service Service or port as a string
		///@param sockType TCP or UDP
		///@param ipFamily IPv4 or IPv6 or Undefined for testing the two
		///@return true if success else false
		bool connect( const String & address, const String & service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );


		///@brief Connect to a specified address/port
		///@param address address as a String (ip or domain name)
		///@param port port
		///@param sockType TCP or UDP
		///@param ipFamily IPv4 or IPv6 or Undefined for testing the two
		///@return true if success else false
		bool connect( const String & address, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );


		///@brief Accept a new client (only when listening on TCP). This is a blocking method.
		///@param out clientSocket Pointer to a Connection object that will be filled when a client connect (the object has to be already allocated)
		///@return true when a new client has connected.
		bool accept( Connection * clientSocket );


		///@brief Send data to the connection (after a connect)
		///@param buffer Data buffer to be sent
		///@param size size of the data buffer
		///@return true if success else false
		bool send( const char * buffer, int size );


		///@brief Wait for data from the connection (usually used for TCP transaction)
		///@param buffer Data buffer where to store the read bytes
		///@param maxSize Maximum size of the buffer
		///@return number of bytes read
		int receive( char * buffer, int maxSize );

		///@brief Wait for data from the connection and retrieve the address of the sender. (usually used for UDP transaction)
		///@param buffer Data buffer where to store the read bytes
		///@param maxSize Maximum size of the buffer
		///@param out addressFrom Address Object to be filled with the address of sender. (the object has to be already allocated)
		///@return number of bytes read
		int receive( char * buffer, int maxSize, Address * addressFrom );


		///@brief Send data to an address 
		///@param buffer Data buffer to be sent
		///@param size size of the data buffer
		///@param address Address to send to
		///@return true if success else false
		bool send( char * buffer, int size, const Address & address );


		///@brief close the connection
		void close();

		///@brief get the SOCKET (unrecommended)
		///return SOCKET of this connection (0 if not connected)
		SOCKET getSocket() const;

		///@brief Retrieve if the connection is connected or not.
		///@return if connected or not.
		bool isConnected() const;

		///@brief listen and return the Socket created
		///@param addrInfo Address to listen on.
		///@param maxClients Maximum number of clients
		///@return SOCKET created
		static SOCKET listenStatic( const AddrInfo & addrInfo, int maxClients = 100 );

		///@brief connect and return the Socket created
		///@param addrInfo Address to connect on.
		///@return SOCKET created
		static SOCKET connectStatic( const AddrInfo & addrInfo );

	protected:
		Connection( ctor );

		using AddrInfo::setFlags;
		using AddrInfo::getFlags;
		using AddrInfo::addFlag;

	private:
		bool _connect( const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined );
		bool _listen( const char * ip, const char * service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined, int maxClients = 100 );
		bool _tryConnect( const struct addrinfo * addrResults );
		bool _tryConnect( AddrInfo * addrInfo );
		bool _tryListen( const struct addrinfo * addrResults, int maxClients );
		bool _tryListen( AddrInfo * addrInfo, int maxClients );




		SOCKET mSocket;
		bool mIsCreated;
		bool mIsListening;
	};




}




