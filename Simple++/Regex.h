/**
 * @file	Regex.h.
 *
 * @brief 	Declares some static methods for using regex.
 */

#pragma once

#include "Vector.h"
#include "String.h"

namespace Regex {


	/**
	 * @brief	 Check if a String is matching an regex.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	str   	The string to test.
	 * @param	regExp	The regex string
	 *
	 * @returns	True if it succeeds, false if it fails.
	 */
	template<typename T>
	bool match( const BasicString<T> & str, const BasicString<T> & regExp );


};

#include "Regex.hpp"
