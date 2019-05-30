/**
 * @file		Math\Line.h.
 *
 * @brief		Declares the line class
 * @author	Clément Gerber
 * @date		25/05/2016 (DMY)
 */
#pragma once

#include "Vec2.h"

namespace Math {
	/** @brief	Class representing a line */
	template<typename T>
	class Line {
	public:
		/**
		 * @brief 	Constructor with two points
		 * @param 	p0	Point 1.
		 * @param 	p1	Point 2.
		 */
		Line( const Vec2<T> & p0, const Vec2<T> & p1 );

		/**
		 * @brief 	Constructor with two points
		 * @param 	x0	X Coordinate of the First point.
		 * @param 	y0	Y Coordinate of the First point.
		 * @param 	x1	X Coordinate of the Second point.
		 * @param 	y1	Y Coordinate of the Second point.
		 */
		Line( const T & x0, const T & y0, const T & x1, const T & y1 );

		/** @brief	Empty constructor, not initialized */
		Line();

		/**
		 * @brief 	get the First point
		 * @returns	Point.
		 */
		const Vec2<T> & getP0() const;

		/**
		 * @brief 	get the Second point
		 * @returns	Point.
		 */
		const Vec2<T> & getP1() const;

		/**
		 * @brief 	set the First point.
		 * @param 	p	Point.
		 */
		void setP0( const Vec2<T> & p );

		/**
		 * @brief 	set the Second point.
		 * @param 	p	Point.
		 */
		void setP1( const Vec2<T> & p );

	private:
		Vec2<T> p0;
		Vec2<T> p1;
	};
}

#include "Line.hpp"