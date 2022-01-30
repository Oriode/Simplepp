#pragma once

#include <openssl/hmac.h>

#include "../String.h"

#include "SSL.h"

namespace Crypto {

	template<typename T>
	BasicString<T> HMACSha256(const BasicString<T>& keyStr, const BasicString<T>& messageStr);

	template<typename T>
	bool HMACSha256(const BasicString<T>& keyStr, const BasicString<T>& messageStr, typename BasicString<T>::ElemType * outputIt, Size* outputLength);

}

#include "Crypto.hpp"