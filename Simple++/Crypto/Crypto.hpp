#include "Crypto.h"
namespace Crypto {

	template<typename T>
	Vector<unsigned char> HMACSha256(const Vector<unsigned char>& keyBinary, const Vector<unsigned char>& dataBinary) {
		Vector<unsigned char> binaryOutput;
		binaryOutput.reserve(EVP_MAX_MD_SIZE);
		
		unsigned char* it(binaryOutput.getData());
		if ( !HMACSha256<T>(keyBinary, dataBinary, &it) ) {
			return binaryOutput;
		}

		Size outputSize(it - binaryOutput.getBegin());
		binaryOutput.resize(outputSize);

		return binaryOutput;
	}

	template<typename T>
	bool HMACSha256(const Vector<unsigned char>& keyBinary, const Vector<unsigned char>& dataBinary, unsigned char** itP) {
		
		// EVP_MAX_MD_SIZE

		/*HMAC_CTX * context(HMAC_CTX_new());
		if ( !context ) {
			error("Error while initializing the HMAC context.");
			return false;
		}*/

		unsigned char*& it(*itP);

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
	Vector<unsigned char> digestSha256(const Vector<unsigned char>& dataBinary) {
		Vector<unsigned char> binaryOutput;
		binaryOutput.reserve(EVP_MAX_MD_SIZE);

		unsigned char* it(binaryOutput.getData());
		if ( !digestSha256<T>(dataBinary, &it) ) {
			return binaryOutput;
		}

		Size outputSize(it - binaryOutput.getBegin());
		binaryOutput.resize(outputSize);

		return binaryOutput;
	}

	template<typename T>
	bool digestSha256(const Vector<unsigned char>& dataBinary, unsigned char** itP) {
		unsigned char*& it(*itP);

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