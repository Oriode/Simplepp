#pragma once

#include <algorithm>
#include <random>

//If we are on windows, include it to avoid problems
#ifdef WIN32
#include <windows.h>
#undef min
#undef max
#endif



#include "BuildConfig.h"
#include "Math/Operations.h"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/Mat3.h"
#include "Math/Mat4.h"
#include "Math/BoundingBox2D.h"
#include "Math/Rectangle.h"
#include "Math/Line.h"

namespace Math {

	/************************************************************************/
	/* Constants                                                            */
	/************************************************************************/
	template<typename T = double>
	constexpr T e(){
		return T(2.7182818);
	};

	template<typename T = double>
	constexpr T pi() {
		return T(3.14159265359);
	};
	

	MATH_FUNC_QUALIFIER float random(float min, float max);
	MATH_FUNC_QUALIFIER int random(int min, int max);
	MATH_FUNC_QUALIFIER unsigned int random(unsigned int min, unsigned int max);

	template<typename T>
	MATH_FUNC_QUALIFIER T randomF();

	template<typename T = unsigned int>
	MATH_FUNC_QUALIFIER T random();


	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> getNormalMat( const Mat4<T> & mat );


	/************************************************************************/
	/* Local Space Scale                                                    */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleX( Mat4<T> * mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleY( Mat4<T> * mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleZ( Mat4<T> * mat, const T & z);
	
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleX( const Mat4<T> & mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleY( const Mat4<T> & mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleZ( const Mat4<T> & mat, const T & z);
	
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const T & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y);

	/************************************************************************/
	/* INVERTED Local Space scale                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleXInv(Mat4<T> * mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleYInv(Mat4<T> * mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleZInv(Mat4<T> * mat, const T & z);


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleXInv(const Mat4<T> & mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleYInv(const Mat4<T> & mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleZInv(const Mat4<T> & mat, const T & z);


	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(Mat4<T> * mat, const Vec3<T> & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(Mat4<T> * mat, const T & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(Mat4<T> * mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv(const Mat4<T> & mat, const Vec3<T> & s);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv(const Mat4<T> & mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv(const Mat4<T> & mat, const T & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(const Mat4<T> & mat, Mat4<T> * resultMat, const T & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(Mat4<T> * mat, const Vec2<T> & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(Mat4<T> * mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv(const Mat4<T> & mat, const Vec2<T> & s);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv(const Mat4<T> & mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & s);
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y);





	/************************************************************************/
	/* Local Space Translations                                             */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void translateX(Mat4<T> * mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateY(Mat4<T> * mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZ(Mat4<T> * mat, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateX(const Mat4<T> & mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateY(const Mat4<T> & mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZ(const Mat4<T> & mat, const T & z);


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const T & x, const T & y , const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y , const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y );

	/************************************************************************/
	/* INVERTED Local Space Translations                                    */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void translateXInv(Mat4<T> * mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateYInv(Mat4<T> * mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZInv(Mat4<T> * mat, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateXInv(const Mat4<T> & mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateYInv(const Mat4<T> & mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZInv(const Mat4<T> & mat, const T & z);

	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(Mat4<T> * mat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(Mat4<T> * mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv(const Mat4<T> & mat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv(const Mat4<T> & mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(Mat4<T> * mat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(Mat4<T> * mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv(const Mat4<T> & mat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv(const Mat4<T> & mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y);


	
	/************************************************************************/
	/* World Space Translation                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void translateXWS(Mat4<T> * mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateYWS(Mat4<T> * mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZWS(Mat4<T> * mat, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateXWS(const Mat4<T> & mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateYWS(const Mat4<T> & mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZWS(const Mat4<T> & mat, const T & z);



	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(Mat4<T> * mat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(Mat4<T> * mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS(const Mat4<T> & mat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS(const Mat4<T> & mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(Mat4<T> * mat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(Mat4<T> * mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS(const Mat4<T> & mat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS(const Mat4<T> & mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y);

	/************************************************************************/
	/* World Space Set Translation                                          */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionX(Mat4<T> * mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionY(Mat4<T> * mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionZ(Mat4<T> * mat, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionX(const Mat4<T> & mat, const T & x);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionY(const Mat4<T> & mat, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionZ(const Mat4<T> & mat, const T & z);



	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(Mat4<T> * mat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(Mat4<T> * mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition(const Mat4<T> & mat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition(const Mat4<T> & mat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(Mat4<T> * mat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(Mat4<T> * mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition(const Mat4<T> & mat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition(const Mat4<T> & mat, const T & x, const T & y);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition(const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y);



	/************************************************************************/
	/* Local Space Rotation                                                 */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized(const Mat4<T> & m, const T & angle, const T & x, const T & y, const T & z);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized(const Mat4<T> & m, const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void rotateNormalized(Mat4<T> * m, const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized(const Mat4<T> & m, Mat4<T> * resultMat, const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized(const T & angle, const Vec3<T> & v);

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate(const Mat4<T> & m, const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate(const Mat4<T> & m, const T & angle);
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate(Mat4<T> * m, const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate(Mat4<T> * m, const T & angle);
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate(const Mat4<T> & m, Mat4<T> * resultMat, const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate(const Mat4<T> & m, Mat4<T> * resultMat, const T & angle);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate(const T & angle, const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate(const T & angle);




	


	


	template<typename T>
	MATH_FUNC_QUALIFIER const T length(const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER const T length(const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER const T length(const Vec4<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleSurface(const Vec3<T> & v1, const Vec3<T> & v2, const Vec3<T> & v3);
	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleDot(const Vec3<T> & v1, const Vec3<T> & v2, const Vec3<T> & v3);



	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> perspective( const T & fovy, const T & aspect, const T & near, const T & far );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAt( const Vec3<T> & position, const Vec3<T> & target, const Vec3<T> & up );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAtNormalized( const Vec3<T> & position, const Vec3<T> & orientation, const Vec3<T> & up );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAt( const Vec3<T> & position, const Vec3<T> & target);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAtNormalized( const Vec3<T> & position, const Vec3<T> & orientation);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> ortho( const T & left,  const T & right,  const T & bottom,  const T & top,  const T & zNear,  const T & zFar);
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> ortho( const T & left, const T & right, const T & bottom, const T & top);

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr int sign(const T & i);

	template<typename T>
	MATH_FUNC_QUALIFIER T min(const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER T min(const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER T max(const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER T max(const Vec2<T> & v);

	template<typename T>
	MATH_FUNC_QUALIFIER T radians(const T & degres);
	template<typename T>
	MATH_FUNC_QUALIFIER T degres(const T & radians);

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> sqrt(const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> sqrt(const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> sqrt(const Vec4<T> & v);

	template<typename T>
	MATH_FUNC_QUALIFIER T inverseSqrt(const T & data);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> inverseSqrt(const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> inverseSqrt(const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> inverseSqrt(const Vec4<T> & v);

	template<typename T>
	MATH_FUNC_QUALIFIER T dot(const Vec2<T> & v1, const Vec2<T> & v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T dot(const Vec3<T> & v1, const Vec3<T> & v2);
	template<typename T>
	MATH_FUNC_QUALIFIER T dot(const Vec4<T> & v1, const Vec4<T> & v2);

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> cross(const Vec2<T> & v1, const Vec2<T> & v2);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> cross(const Vec3<T> & v1, const Vec3<T> & v2);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> cross(const Vec4<T> & v1, const Vec4<T> & v2);

	template<typename T>
	MATH_FUNC_QUALIFIER T normalize(const T & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> normalize(const Vec2<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> normalize(const Vec3<T> & v);
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> normalize(const Vec4<T> & v);

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> right(const Vec3<T> & v);

	template<typename T>
	MATH_FUNC_QUALIFIER T pow(const T & v, double e);

	template<typename T>
	MATH_FUNC_QUALIFIER T clamp(const T & v, const T & min, const T & max);


	///@brief Clip a line from p0 to p1 against this rectangle
	///@see https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm#Example_C.2FC.2B.2B_implementation
	///@param l Line to be clipped
	///@param r Rectangle
	///@return true if a part of the line was inside the rectangle, false instead.
	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp(Line<T> * l, const Rectangle<T> & r);



	///@brief Get the fractional part of a float
	///@param x Floating number
	///@return the Fractional part of the specified number
	template<typename T>
	MATH_FUNC_QUALIFIER T fpart(const T & x);

	///@brief Truncate a number
	///@param x Number to truncate
	///@return Truncated number
	template<typename T>
	MATH_FUNC_QUALIFIER T trunc(const T & x);



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
	using std::max;
	using std::min;
	using std::ceil;
	using std::floor;
	using std::exp;
	using std::round;

	/************************************************************************/
	/* FULL Template                                                        */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T abs(const T & v);

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T pow(const T & v, int e);
	MATH_FUNC_QUALIFIER constexpr intmax_t gcd(intmax_t M, intmax_t N);

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr int sign(const T & i);


	template<intmax_t Numerator, intmax_t Denumerator = 1>
	struct Ratio {
		static_assert( Denumerator != 0,		"Denominator cannot be zero." );
		static_assert( -INTMAX_MAX <= Numerator,	"Numerator too negative." );
		static_assert( -INTMAX_MAX <= Numerator,	"Denominator too negative." );

		static constexpr intmax_t num = sign(Numerator) * sign(Denumerator) * abs(Numerator) / gcd(Numerator, Denumerator);
		static constexpr intmax_t den = abs(Denumerator) / gcd(Numerator, Denumerator);

		typedef Ratio<num, den> type;
	};






}




#include "Math.hpp"








