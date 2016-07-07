#pragma once

#include "Vector.h"
#include "String.h"

namespace Regex {

	template<typename T>
	bool match( const BasicString<T> & str, const BasicString<T> & regExp );


};

#include "Regex.hpp"
