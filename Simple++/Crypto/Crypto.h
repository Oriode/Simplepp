#pragma once

#include <openssl/hmac.h>

#include "../String.h"

#include "SSL.h"

namespace Crypto {

	template<typename T>
	Vector<char> HMACSha256(const Vector<char>& keyBinary, const Vector<char>& dataBinary);

	template<typename T>
	bool HMACSha256(const Vector<char> & keyBinary, const Vector<char> & dataBinary, char ** itP);

	template<typename T>
	Vector<char> digestSha256(const Vector<char>& dataBinary);

	template<typename T>
	bool digestSha256(const Vector<char>& dataBinary, char** itP);

}

#include "Crypto.hpp"