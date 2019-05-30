/**
 * @file		Math\Compare.h.
 *
 * @brief 	Declares the compare class
 * @author	Clément Gerber
 * @date		???
 */
#pragma once

#include "BasicComparable.h"

namespace Math {

	namespace Compare {
		/**
		 * @brief 	Used to compare Two elements of type T
		 * @param 	x	First Element.
		 * @param 	y	Second Element.
		 * @returns	Equal (x == y), Less (x < y) or Greater (x > y)
		 */
		template<typename T> inline static Value compare( const T & x, const T & y );

		/** @brief	Class Template for doing Compare. */
		class Template {
		public:
			template<typename T> inline Value operator() ( const T & x, const T & y ) const;
		};

		/** @brief	Private, do not use it */
		template<typename T> inline static Value _compare( const T & x, const T & y, ... );
		/** @brief	Private, do not use it */
		template<typename T> inline static Value _compare( const T & x, const T & y, const BasicComparable * );
	}
}

#include "Compare.hpp"