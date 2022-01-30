namespace Crypto {

	template<typename T>
	BasicString<T> HMACSha256(const BasicString<T>& keyStr, const BasicString<T>& messageStr) {

		

	}

	template<typename T>
	bool HMACSha256(const BasicString<T>& keyStr, const BasicString<T>& messageStr, typename BasicString<T>::ElemType* outputIt, Size* outputLength) {
		
		// EVP_MAX_MD_SIZE

		/*HMAC_CTX * context(HMAC_CTX_new());
		if ( !context ) {
			error("Error while initializing the HMAC context.");
			return false;
		}*/

		const EVP_MD* cypher(EVP_sha256());

		unsigned int length;
		if ( !HMAC(cypher, reinterpret_cast<const void *>(keyStr.toCString()), int(keyStr.getSize()), reinterpret_cast< const unsigned char* >( messageStr.toCString() ), messageStr.getSize(), reinterpret_cast< unsigned char* >( outputIt ), &length) ) {
			error(String::format("Error while SHA256 hashing the data \"%\".", messageStr));
			logSSL();
			return false;
		}
		*outputLength = length;

		// HMAC_CTX_free(context);

		return true;
	}

}