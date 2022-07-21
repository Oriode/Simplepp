///@file Math.h
///@brief Main Math file with all the math includes
///@author Clément Gerber
///@date ??/??/2015 (DMY) 

#pragma once

#include <xmmintrin.h>
#include <immintrin.h>

#include "../BuildConfig.h"
#include "Operations.h"
#include "Vec.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Tensor.h"
#include "BoundingBox2D.h"
#include "Rectangle.h"
#include "Line.h"
#include "BasicMath.h"
#include "Transformations.h"
#include "InterpolationFunc.hpp"

namespace Math {

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER const T length(const Vec<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER const T distance(const T & v1, const T & v2);
	template<typename T>
	MATH_FUNC_QUALIFIER const T distance(const Vec3<T>& v1, const Vec3<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER const T distance(const Vec2<T>& v1, const Vec2<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER const T distance(const Vec4<T>& v1, const Vec4<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER const T distance(const Vec<T>& v1, const Vec<T>& v2);


	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> min( const Vec2<T> & v, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> min(const Vec2<T>& v1, const Vec2<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> min( const Vec3<T> & v, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> min( const Vec3<T> & v1, const Vec3<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> min( const Vec4<T> & v, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> min(const Vec4<T>& v1, const Vec4<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T min(const Vec<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> min(const Vec<T>& v, const T& x);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> min(const Vec<T>& v1, const Vec<T>& v2);

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> max( const Vec2<T> & v, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> max(const Vec2<T>& v1, const Vec2<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> max( const Vec3<T> & v, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> max(const Vec3<T>& v1, const Vec3<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> max( const Vec4<T> & v, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> max(const Vec4<T>& v1, const Vec4<T>& v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T max(const Vec<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> max(const Vec<T>& v, const T& x);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> max(const Vec<T>& v1, const Vec<T>& v2);

	///@brief get the min and the max values of a Vec3
	///@param v Vector of 3 values
	///@return ( min , max )
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> getMinMax( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> getMinMax(const Vec4<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> getMinMax(const Vec<T>& v);
	

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> abs( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> abs( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> abs( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> abs(const Vec<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> sqrt( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> sqrt( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> sqrt( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> sqrt(const Vec<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER T inverseSqrt( const T & data );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> inverseSqrt( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> inverseSqrt( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> inverseSqrt( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> inverseSqrt(const Vec<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER T dot(const T* v1, const T* v2, const Size n);
	template<typename T>
	MATH_FUNC_QUALIFIER T dot(const Vec<T>& v1, const Vec<T>& v2);

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> cross( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> cross( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> cross( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> cross(const Vec<T>& v1, const Vec<T>& v2);

	template<typename T>
	MATH_FUNC_QUALIFIER T normalize( const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> normalize( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> normalize( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> normalize( const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> normalize(const Vec<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleSurface( const Vec3<T> & v1, const Vec3<T> & v2, const Vec3<T> & v3 );
	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleDot( const Vec3<T> & v1, const Vec3<T> & v2, const Vec3<T> & v3 );


	///@brief Clip a line from p0 to p1 against this rectangle
	///@see https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm#Example_C.2FC.2B.2B_implementation
	///@param l Line to be clipped
	///@param r Rectangle
	///@return true if a part of the line was inside the rectangle, false instead.
	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp( Line<T> * l, const Rectangle<T> & r );

	///@brief Clamp a point inside a rectangle
	///@param p Point to be clamped
	///@param r Rectangle
	///@return true of the point was inside, false instead.
	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp( Vec2<T> * p, const Rectangle<T> & r );

	template<typename T>
	MATH_FUNC_QUALIFIER T sum(const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER T sum(const Vec3<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T sum(const Vec4<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T sum(const Vec<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T sum(const Mat<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER T mean(const Vec2<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T mean(const Vec3<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T mean(const Vec4<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T mean(const Vec<T>& v);

	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation(const Vec2<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation(const Vec3<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation(const Vec4<T>& v);
	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation(const Vec<T>& v);

}




#include "Math.hpp"








