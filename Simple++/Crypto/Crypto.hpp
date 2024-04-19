#include "Crypto.h"
namespace Crypto {

	template<typename T>
	Vector<char> HMACSha256(const Vector<char>& keyBinary, const Vector<char>& dataBinary) {
		Vector<char> binaryOutput;
		binaryOutput.reserve(EVP_MAX_MD_SIZE);
		
		char* it(binaryOutput.getData());
		if ( !HMACSha256<T>(keyBinary, dataBinary, &it) ) {
			return binaryOutput;
		}

		Size outputSize(it - binaryOutput.getBegin());
		binaryOutput.resize(outputSize);

		return binaryOutput;
	}

	template<typename T>
	bool HMACSha256(const Vector<char>& keyBinary, const Vector<char>& dataBinary, char** itP) {
		
		// EVP_MAX_MD_SIZE

		/*HMAC_CTX * context(HMAC_CTX_new());
		if ( !context ) {
			ERROR_SPP("Error while initializing the HMAC context.");
			return false;
		}*/

		char*& it(*itP);

		const EVP_MD* cypher(EVP_sha256());

		unsigned int length;
		bool bResult(HMAC(cypher, reinterpret_cast< const void* >( keyBinary.getData() ), int(keyBinary.getSize()),
					 dataBinary.getData(), dataBinary.getSize(),
					 it, &length));

		if ( !bResult ) {
			logSSL();
			return false;
		}

		it += length;

		// HMAC_CTX_free(context);

		return true;
	}

	template<typename T>
	Vector<char> digestSha256(const Vector<char>& dataBinary) {
		Vector<char> binaryOutput;
		binaryOutput.reserve(EVP_MAX_MD_SIZE);

		char* it(binaryOutput.getData());
		if ( !digestSha256<T>(dataBinary, &it) ) {
			return binaryOutput;
		}

		Size outputSize(it - binaryOutput.getBegin());
		binaryOutput.resize(outputSize);

		return binaryOutput;
	}

	template<typename T>
	bool digestSha256(const Vector<char>& dataBinary, char** itP) {
		char*& it(*itP);

		const EVP_MD* cypher(EVP_sha256());

		unsigned int length;
		bool bResult(EVP_Digest(reinterpret_cast< const void* >( dataBinary.getData() ), dataBinary.getSize(),
					 it, &length, cypher, NULL));

		if ( !bResult ) {
			logSSL();
			return false;
		}

		it += length;

		return true;
	}

}