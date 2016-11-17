///@file BasicMath.h
///@brief Basic mathematical methods
///@author Cl�ment Gerber
///@date 08/07/2016 (DMY) 

#pragma once

//If we are on windows, include it to avoid problems
#ifdef WIN32
#include <windows.h>
#undef min
#undef max
#endif

#include <random>
#include <algorithm>

#include "../BuildConfig.h"
#include "../SimpleLog.h"
#include "Logical.h"
#include "Compare.h"

namespace Math {

	///@brief get the value of e
	///@return e
	template<typename T = double>
	MATH_FUNC_QUALIFIER constexpr T e();

	///@brief get the value of PI
	///return PI
	template<typename T = double>
	MATH_FUNC_QUALIFIER constexpr T pi();


	///@brief get the modulus of a number (work with floats)
	///@param x Number to be divided
	///@param d Divider to be used
	///@return modulus
	template<typename T>
	MATH_FUNC_QUALIFIER T modulus( const T & x, const T & d );
	MATH_FUNC_QUALIFIER float modulus( const float & x, const float & d );
	MATH_FUNC_QUALIFIER double modulus( const double & x, const double & d );

	///@brief get a Random number between min and max
	///@param min Minimal value
	///@param max Maximal value
	///@return value between min and max
	template<typename T = float>
	MATH_FUNC_QUALIFIER T random( const T & min, const T & max );
	MATH_FUNC_QUALIFIER unsigned long long random( unsigned long long min, unsigned long long max );
	MATH_FUNC_QUALIFIER int random( int min, int max );


	///@brief get a random value between 0.0 and 1.0
	///@return Random number between 0.0 and 1.0
	template<typename T>
	MATH_FUNC_QUALIFIER T randomF();

	///@brief get a random value number between 0 and randomMax();
	///@return Random number between 0 and randomMax();
	template<typename T = unsigned int>
	MATH_FUNC_QUALIFIER T random();

	///@brief get the maximum value possible of the random number generator
	///@return max of random
	template<typename T = unsigned int>
	MATH_FUNC_QUALIFIER T randomMax();

	///@brief compute the number power another one
	///@param v number to elevate
	///@param e power to use
	///@return result
	template<typename T>
	MATH_FUNC_QUALIFIER T pow( const T & v, double e );

	///@brief compute the number power another one
	///@param v number to elevate
	///@param e power to use
	///@return result
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T pow( const T & v, int e );

	///@brief Clamp a number between to others (assert(min <= max))
	///@param v Value to be clamped
	///@param min minimal value
	///@param max maximal value
	///@return result
	template<typename T>
	MATH_FUNC_QUALIFIER T clamp( const T & v, const T & min, const T & max );

	///@brief Get the fractional part of a float
	///@param x Floating number
	///@return the Fractional part of the specified number
	template<typename T>
	MATH_FUNC_QUALIFIER T fpart( const T & x );

	///@brief Truncate a number
	///@param x Number to truncate
	///@return Truncated number
	template<typename T>
	MATH_FUNC_QUALIFIER T trunc( const T & x );

	///@brief Get the minimal between two elements
	///@param x first object
	///@param y second object
	///@return minimal between x and y
	template<typename T>
	MATH_FUNC_QUALIFIER T min( const T & x, const T & y );

	///@brief Get the minimal between two elements
	///@param x first object
	///@param y second object
	///@return minimal between x and y
	template<typename T>
	MATH_FUNC_QUALIFIER T max( const T & x, const T & y );

	///@brief Get the absolute value of a number
	///@param v Value to be used
	///@return absolute value of v
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T abs( const T & v );

	///@brief Get the greater common divisor of two numbers
	///@param M First number
	///@param N Second Number
	///@return greater common divisor
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T gcd( const T & M, const T & N );

	///@brief get the sign of a number
	///@param i Number to get the sign
	///@return 1 or -1
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr int sign( const T & i );

	///@brief Convert an angle from degree to radians
	///@param degree angle
	///@return radian angle
	template<typename T>
	MATH_FUNC_QUALIFIER T radians( const T & degree );

	///@brief Convert an angle from radian to degree
	///@param radian angle
	///@return degree angle
	template<typename T>
	MATH_FUNC_QUALIFIER T degree( const T & radians );


	///@brief Get the Cardinal Sine Normalized of a number
	///@see https://en.wikipedia.org/wiki/Sinc_function
	///@param x number
	///@return Cardinal Sine Normalized
	template<typename T>
	MATH_FUNC_QUALIFIER T sincn( const T & x );



	///@brief Get the Cardinal Sine unnormalized of a number
	///@see https://en.wikipedia.org/wiki/Sinc_function
	///@param x number
	///@return Cardinal Sine unnormalized
	template<typename T>
	MATH_FUNC_QUALIFIER T sinc( const T & x );

	/************************************************************************/
	/* STD OVERRIDE                                                         */
	/************************************************************************/
	using std::cos;
	using std::acos;
	using std::sin;
	using std::asin;
	using std::tan;
	using std::atan;
	using std::sqrt;
	using std::ceil;
	using std::floor;
	using std::exp;
	using std::round;
}


#include "BasicMath.hpp"
