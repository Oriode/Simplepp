/**
 * @file		Math\BasicComparable.h.
 *
 * @brief		Declares the basic comparable class
 * @author	Clément Gerber
 * @date		??
 */

#pragma once

namespace Math {

	namespace Compare {

		enum class Value : unsigned int {
			Equal,
			Less,
			Greater
		};

		class BasicComparable {
		public:
			/**
			 * @brief 	Function to compare two elements
			 * @param 	x	First Element.
			 * @param 	y	Second Element.
			 * @returns	Equal (x == y), Less (x < y) or Greater (x > y)
			 */
			static Math::Compare::Value compare( const BasicComparable & x, const BasicComparable & y );
		};
	}
}


#include "BasicComparable.hpp"
