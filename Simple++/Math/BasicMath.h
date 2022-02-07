/**
 * @file		Math\BasicMath.h.
 *
 * @brief 	Declares the basic mathematics class
 * @author	Clément Gerber
 * @date		08/07/2016 (DMY)
 */
#pragma once

#include "../BuildConfig.h"

 //If we are on windows, include it to avoid problems
#if defined WIN32 && defined ENABLE_WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif

#if defined min
#undef min
#endif

#if defined max
#undef max
#endif

#include <random>
#include <algorithm>

#include "../BuildConfig.h"
#include "../SimpleLog.h"
#include "Logical.h"
#include "Compare.h"

namespace Math {

	template<intmax_t Numerator, intmax_t Denumerator = 1>
	struct Ratio {
		static_assert( Denumerator != 0, "Denominator cannot be zero." );
		static_assert( -INTMAX_MAX <= Numerator, "Numerator too negative." );
		static_assert( -INTMAX_MAX <= Numerator, "Denominator too negative." );

		static constexpr intmax_t g = gcd(Numerator, Denumerator);

		static constexpr intmax_t num = ( g == 0 ) ? 0 : ( sign(Numerator) * sign(Denumerator) * abs(Numerator) / g );
		static constexpr intmax_t den = ( g == 0 ) ? 0 : ( abs(Denumerator) / g );

		template<intmax_t Numerator2, intmax_t Denumerator2>
		inline bool operator==(const Ratio< Numerator2, Denumerator2>& r) const {
			return Numerator == Numerator2 && Denumerator == Denumerator2;
		}

		typedef Ratio<num, den> type;
	};

	template<typename FakeType>
	class BasicMathT {
	public:
		/**
		 * @brief 	get the value of e ( exponential )
		 * @returns	e.
		 */
		template<typename T = double>
		MATH_FUNC_QUALIFIER static constexpr T e();

		/** @brief	get the value of PI. */
		template<typename T = double>
		MATH_FUNC_QUALIFIER static constexpr T pi();


		/**
		 * @brief 	get the modulus of a number (work with floats)
		 * @param 	x	Number to be divided.
		 * @param 	d	Divider to be used.
		 * @returns	modulus.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T modulus(const T& x, const T& d);
		MATH_FUNC_QUALIFIER static float modulus(const float& x, const float& d);
		MATH_FUNC_QUALIFIER static double modulus(const double& x, const double& d);

		/**
		 * @brief 	get a Random number between min and max
		 * @param 	min	Minimal value.
		 * @param 	max	Maximal value.
		 * @returns	value between min and max.
		 */
		template<typename T = float>
		MATH_FUNC_QUALIFIER static T random(const T& min, const T& max);
		MATH_FUNC_QUALIFIER static unsigned long long random(unsigned long long min, unsigned long long max);
		MATH_FUNC_QUALIFIER static int random(int min, int max);


		/**
		 * @brief 	get a random value between 0.0 and 1.0
		 * @returns	Random number between 0.0 and 1.0.
		 */
		template<typename T = float>
		MATH_FUNC_QUALIFIER static T randomF();

		/**
		 * @brief 	get a random value number between 0 and randomMax();
		 * @returns	Random number between 0 and randomMax();
		 */
		template<typename T = unsigned int>
		MATH_FUNC_QUALIFIER static T random();

		/**
		 * @brief 	get the maximum value possible of the random number generator
		 * @returns	max of random.
		 */
		template<typename T = unsigned int>
		MATH_FUNC_QUALIFIER static T randomMax();

		/**
		 * @brief 	compute the number power another one
		 * @param 	v	number to elevate.
		 * @param 	e	power to use.
		 * @returns	result.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T pow(const T& v, double e);

		/**
		 * @brief 	compute the number power another one
		 * @param 	v	number to elevate.
		 * @param 	e	power to use.
		 * @returns	result.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static constexpr T pow(const T& v, int e);

		/**
		 * @brief 	Clamp a number between to others (assert(min <= max))
		 * @param 	v  	Value to be clamped.
		 * @param 	min	minimal value.
		 * @param 	max	maximal value.
		 * @returns	result.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T clamp(const T& v, const T& min, const T& max);

		/**
		 * @brief 	Get the fractional part of a float
		 * @param 	x	Floating number.
		 * @returns	the Fractional part of the specified number.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T fpart(const T& x);

		/**
		 * @brief 	Truncate a number
		 * @param 	x	Number to truncate.
		 * @returns	Truncated number.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T trunc(const T& x);
		MATH_FUNC_QUALIFIER static float trunc(const float& x);
		MATH_FUNC_QUALIFIER static double trunc(const double& x);

		/**
		 * @brief 	Get the minimal between two elements
		 * @param 	x	first object.
		 * @param 	y	second object.
		 * @returns	minimal between x and y.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T min(const T& x, const T& y);

		/**
		 * @brief 	Get the minimal between two elements
		 * @param 	x	first object.
		 * @param 	y	second object.
		 * @returns	minimal between x and y.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T max(const T& x, const T& y);

		/**
		 * @brief 	Get the absolute value of a number
		 * @param 	v	Value to be used.
		 * @returns	absolute value of v.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static constexpr T abs(const T& v);

		/**
		 * @brief 	Get the greater common divisor of two numbers
		 * @param 	M	First number.
		 * @param 	N	Second Number.
		 * @returns	greater common divisor.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static constexpr T gcd(const T& M, const T& N);

		/**
		 * @brief 	get the sign of a number
		 * @param 	i	Number to get the sign.
		 * @returns	1 or -1.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static constexpr int sign(const T& i);

		/**
		 * @brief 	Convert an angle from degree to radians
		 * @param 	degree	angle.
		 * @returns	radian angle.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T radians(const T& degree);

		/**
		 * @brief 	Convert an angle from radian to degree
		 * @returns	degree angle.
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T degree(const T& radians);


		/**
		 * @brief 	Get the Cardinal Sine Normalized of a number
		 * @param 	x	number.
		 * @returns	Cardinal Sine Normalized.
		 * @sa	https://en.wikipedia.org/wiki/Sinc_function
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T sincn(const T& x);



		/**
		 * @brief 	Get the Cardinal Sine unnormalized of a number
		 * @param 	x	number.
		 * @returns	Cardinal Sine unnormalized.
		 * @sa	https://en.wikipedia.org/wiki/Sinc_function
		 */
		template<typename T>
		MATH_FUNC_QUALIFIER static T sinc(const T& x);

	private:
		static std::random_device _randomDevice;

	};

	using BasicMath = BasicMathT<int>;

	/************************************************************************/
	/* BasicMath                                                            */
	/************************************************************************/
	template<typename T = double>
	MATH_FUNC_QUALIFIER constexpr T e() { return BasicMath::e<T>(); }
	template<typename T = double>
	MATH_FUNC_QUALIFIER constexpr T pi() { return BasicMath::pi<T>(); }
	template<typename T>
	MATH_FUNC_QUALIFIER T modulus(const T& x, const T& d) { return BasicMath::modulus<T>(x, d); }
	template<typename T = float>
	MATH_FUNC_QUALIFIER T random(const T& min, const T& max) { return BasicMath::random<T>(min, max); }
	template<typename T = float>
	MATH_FUNC_QUALIFIER T randomF() { return BasicMath::randomF<T>(); }
	template<typename T = unsigned int>
	MATH_FUNC_QUALIFIER T random() { return BasicMath::random<T>(); }
	template<typename T = unsigned int>
	MATH_FUNC_QUALIFIER T randomMax() { return BasicMath::randomMax<T>(); }
	template<typename T>
	MATH_FUNC_QUALIFIER T pow(const T& v, double e) { return BasicMath::pow<T>(v, e); }
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T pow(const T& v, int e) { return BasicMath::pow<T>(v, e); }
	template<typename T>
	MATH_FUNC_QUALIFIER T clamp(const T& v, const T& min, const T& max) { return BasicMath::clamp<T>(v, min, max); }
	template<typename T>
	MATH_FUNC_QUALIFIER T fpart(const T& x) { return BasicMath::fpart<T>(x); }
	template<typename T>
	MATH_FUNC_QUALIFIER T trunc(const T& x) { return BasicMath::trunc<T>(x); }
	template<typename T>
	MATH_FUNC_QUALIFIER T min(const T& x, const T& y) { return BasicMath::min<T>(x, y); }
	template<typename T>
	MATH_FUNC_QUALIFIER T max(const T& x, const T& y) { return BasicMath::max<T>(x, y); }
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T abs(const T& v) { return BasicMath::abs<T>(v); }
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T gcd(const T& M, const T& N) { return BasicMath::gcd<T>(M, N); }
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T sign(const T& i) { return BasicMath::sign<T>(i); }
	template<typename T>
	MATH_FUNC_QUALIFIER T radians(const T& degree) { return BasicMath::radians<T>(degree); }
	template<typename T>
	MATH_FUNC_QUALIFIER T degree(const T& radians) { return BasicMath::degree<T>(radians); }
	template<typename T>
	MATH_FUNC_QUALIFIER T sincn(const T& x) { return BasicMath::sincn<T>(x); }
	template<typename T>
	MATH_FUNC_QUALIFIER T sinc(const T& x) { return BasicMath::sinc<T>(x); }

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