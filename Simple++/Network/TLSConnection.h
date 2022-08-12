#pragma once

#include "../Crypto/SSL.h"
#include "Connection.h"

namespace Network {

	template<typename T>
	class TLSConnectionT : protected ConnectionT<T> {
	public:
		/** @brief	Create a connection not initialized. */
		TLSConnectionT();

		/**
		  * @brief 	Constructor from an address
		  *
		  * @param 	address	Address to asign to this connection.
		  */
		TLSConnectionT(const Address& address);

		/**
		 * @brief 	Move constructor
		 *
		 * @param [in,out]	connection	Object to be moved from.
		 */
		TLSConnectionT(TLSConnectionT<T>&& connection);

		/** @brief	destructor */
		~TLSConnectionT();

		/**
		 * @brief 	brief move operator
		 *
		 * @param [in,out]	connection	Object to be moved from.
		 *
		 * @returns	reference to this.
		 */
		TLSConnectionT<T>& operator =(TLSConnectionT<T>&& connection);

		using ConnectionT<T>::getIp;
		using ConnectionT<T>::isConnected;

		/**
		 * @brief 	set the Address of this connection (this will close the connection)
		 *
		 * @param 	address	New Address of this connection.
		 */
		void setAddess(const Address& address);

		/**
		 * @brief 	Connect to UDP or TCP server
		 *
		 * @returns	true if success else false.
		 */
		bool connect();


		/**
		 * @brief 	Connect to a specified Address
		 *
		 * @param 	address	Address to connect to.
		 *
		 * @returns	true if success else false.
		 */
		bool connect(const Address& address);


		/**
		 * @brief 	Connect to a specified address/service
		 *
		 * @param 	address 	address as a StringASCII (ip or domain name)
		 * @param 	service 	Service or port as a string.
		 * @param 	sockType	(Optional) TCP or UDP.
		 * @param 	ipFamily	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 *
		 * @returns	true if success else false.
		 */
		bool connect(const StringASCII& address, const StringASCII& service, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);


		/**
		 * @brief 	Connect to a specified address/port
		 *
		 * @param 	address 	address as a StringASCII (ip or domain name)
		 * @param 	port		port.
		 * @param 	sockType	(Optional) TCP or UDP.
		 * @param 	ipFamily	(Optional) IPv4 or IPv6 or Undefined for testing the two.
		 *
		 * @returns	true if success else false.
		 */
		bool connect(const StringASCII& address, unsigned short port, SockType sockType = SockType::TCP, IpFamily ipFamily = IpFamily::Undefined);

		bool reconnect();

		/**
		 * @brief 	Send data to the connection (after a connect)
		 *
		 * @param 	buffer	Data buffer to be sent.
		 * @param 	size  	size of the data buffer.
		 *
		 * @returns	true if success else false.
		 */
		bool send(const char* buffer, int size);

		/**
		 * @brief 	Wait for data from the connection (usually used for TCP transaction)
		 *
		 * @param [in,out]	buffer 	Data buffer where to store the read bytes.
		 * @param 		  	maxSize	Maximum size of the buffer.
		 *
		 * @returns	number of bytes read.
		 */
		int receive(char* buffer, int maxSize);

		/** @brief	close the connection */
		void close();

		static int sniCallback(SSL* ssl, int* al, void* arg);

	protected:
		///@brief Should be called before every connect/listen. Ensure networking is enabled and the socket initialy closed.
		///@return True if succeed, False otherwise.
		bool _init();
	private:
		bool _initSSL();
		bool _setSniHostname(const StringASCII& hostname);
		bool _sslConnect();

		SSL* ssl;

		StringASCII hostname;
	};

	using TLSConnection = TLSConnectionT<int>;

	template<typename T>
	inline TLSConnectionT<T>::TLSConnectionT() {}

	template<typename T>
	inline TLSConnectionT<T>::TLSConnectionT(const Address& address) :
		ConnectionT<T>(address),
		ssl(NULL)
	{}

	template<typename T>
	inline TLSConnectionT<T>::TLSConnectionT(TLSConnectionT<T> && connection) :
		ConnectionT<T>(Utility::toRValue(connection)),
		ssl(Utility::toRValue(connection.ssl))
	{}

	template<typename T>
	inline TLSConnectionT<T>::~TLSConnectionT() {
		close();
	}

	template<typename T>
	inline TLSConnectionT<T>& TLSConnectionT<T>::operator=(TLSConnectionT<T>&& connection) {
		ConnectionT<T>::operator=(Utility::toRValue(connection));
		this->ssl = Utility::toRValue(connection.ssl);
		return *this;
	}

	template<typename T>
	inline void TLSConnectionT<T>::setAddess(const Address& address) {
		close();
		Address::operator=(address);
	}

	template<typename T>
	inline bool TLSConnectionT<T>::connect() {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		if ( !ConnectionT<T>::_connect() ) {
			return false;
		}
		if ( !_initSSL() ) {
			return false;
		}
		if ( !_sslConnect() ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::connect(const Address& address) {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		if ( !ConnectionT<T>::_connect(address) ) {
			return false;
		}
		if ( !_initSSL() ) {
			return false;
		}
		if ( !_setSniHostname(address) ) {
			return false;
		}
		if ( !_sslConnect() ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::connect(const StringASCII& address, const StringASCII& service, SockType sockType, IpFamily ipFamily) {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		if ( !ConnectionT<T>::_connect(address, service, sockType, ipFamily) ) {
			return false;
		}
		if ( !_initSSL() ) {
			return false;
		}
		if ( !_setSniHostname(address) ) {
			return false;
		}
		if ( !_sslConnect() ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::connect(const StringASCII& address, unsigned short port, SockType sockType, IpFamily ipFamily) {
		if ( !_init() ) {
			return false;
		}
		if ( isConnected() ) {
			close();
		}
		if ( !ConnectionT<T>::_connect(address, StringASCII::toString(port), sockType, ipFamily) ) {
			return false;
		}
		if ( !_initSSL() ) {
			return false;
		}
		if ( !_setSniHostname(address) ) {
			return false;
		}
		if ( !_sslConnect() ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::reconnect() {

		if ( isConnected() ) {
			close();
		}

		if ( !ConnectionT<T>::_reconnect() ) {
			return false;
		}

		if ( !_initSSL() ) {
			return false;
		}

		if ( !_sslConnect() ) {
			return false;
		}

		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::send(const char* buffer, int size) {
		int length(SSL_write(this->ssl, buffer, size));
		if ( length != size ) {
			logSSL();
			return false;
		}
		return true;
	}

	template<typename T>
	inline int TLSConnectionT<T>::receive(char* buffer, int maxSize) {
		int length(SSL_read(this->ssl, buffer, maxSize));
		if ( length < 0 ) {
			logSSL();
		}
		return length;
	}

	template<typename T>
	inline void TLSConnectionT<T>::close() {
		if ( this->ssl ) {
			SSL_shutdown(this->ssl);
			SSL_free(this->ssl);

			this->ssl = NULL;
		}
		ConnectionT<T>::close();
	}

	template<typename T>
	inline int TLSConnectionT<T>::sniCallback(SSL* ssl, int* al, void* arg) {
		return SSL_TLSEXT_ERR_OK;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::_init() {
		if ( !NetworkObject::init() ) return false;
		if ( !Crypto::SSLObject::init() ) return false;

		if ( isConnected() ) {
			close();
			warn("The connection was already open. Closing the old one.");
		}

		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::_initSSL() {
		if ( !this->ssl ) {
			SSL_CTX* sslContext(SSL_CTX_new(TLS_method()));
			SSL_CTX_set_tlsext_servername_callback(sslContext, TLSConnectionT<T>::sniCallback);
			if ( !sslContext ) {
				logSSL();
				return false;
			}
			this->ssl = SSL_new(sslContext);
			if ( !this->ssl ) {
				logSSL();
				return false;
			}
		}
		
		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::_setSniHostname(const StringASCII& hostname) {

		this->hostname = hostname;

		return true;
	}

	template<typename T>
	inline bool TLSConnectionT<T>::_sslConnect() {

		SSL_set_tlsext_host_name(this->ssl, hostname.toCString());

		if ( !SSL_set_fd(this->ssl, int(getSocket())) ) {
			logSSL();
			return false;
		}

		int errorCode(SSL_connect(this->ssl));
		if ( errorCode < 1 ) {
			logSSL();
			return false;
		}

		verbose(StringASCII::format("Success creating the SSL cypher %.", StringASCII(SSL_get_cipher(this->ssl))));

		return true;
	}

}