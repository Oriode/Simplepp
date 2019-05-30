/**
 * @file		Math\BasicDistanceable.h.
 *
 * @brief		Declares the basic distanceable class
 * @author	Clément Gerber
 * @date		??
 */
#pragma once

namespace Math {

	namespace Compare {

		/** @brief	Defines a distance. */
		typedef size_t Distance;

		class BasicDistanceable {
		public:
			/**
			 * @brief 	Function to get the distance between two elements.
			 * @param 	x	First Element.
			 * @param 	y	Second Element.
			 * @returns	Distance between the two.
			 */
			static Distance getDistance( const BasicDistanceable & x, const BasicDistanceable & y );
		};
	}
}