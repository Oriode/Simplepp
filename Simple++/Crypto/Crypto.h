#pragma once

#include <openssl/hmac.h>

#include "../String.h"

#include "SSL.h"

namespace Crypto {

	template<typename T>
	Vector<unsigned char> HMACSha256(const Vector<unsigned char>& keyBinary, const Vector<unsigned char>& dataBinary);

	template<typename T>
	bool HMACSha256(const Vector<unsigned char> & keyBinary, const Vector<unsigned char> & dataBinary, unsigned char ** itP);

	template<typename T>
	Vector<unsigned char> digestSha256(const Vector<unsigned char>& dataBinary);

	template<typename T>
	bool digestSha256(const Vector<unsigned char>& dataBinary, unsigned char** itP);

}

#include "Crypto.hpp"