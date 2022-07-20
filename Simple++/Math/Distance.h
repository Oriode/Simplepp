/**
 * @file		Math\DistanceFunc.h.
 *
 * @brief		Declares the basic distanceable class
 * @author	Clément Gerber
 * @date		??
 */
#pragma once

#include "BasicMath.h"
#include "../Utility.h"

namespace Math {

	namespace Compare {

		/** @brief	Defines a distance. */
		typedef double Distance;

		class DistanceFunc {
		public:
			/**
			 * @brief 	Function to get the distance between two elements.
			 * @param 	x	First Element.
			 * @param 	y	Second Element.
			 * @returns	Distance between the two.
			 */
			template<typename T>
			Distance getDistance( const T & x, const T & y ) const;
		};

		template<typename T>
		inline Distance DistanceFunc::getDistance(const T& x, const T& y) const {
			return Math::abs(y - x);
		}
	}
}