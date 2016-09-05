///@file Transformations.h
///@brief Matrix 2D & 3D transformations
///@author Cl�ment Gerber
///@date 08/07/2016 (DMY) 

#pragma once



#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"





namespace Math {

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> getNormalMat( const Mat4<T> & mat );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> right( const Vec3<T> & v );

	/************************************************************************/
	/* Local Space Scale                                                    */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleX( Mat4<T> * mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleY( Mat4<T> * mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleZ( Mat4<T> * mat, const T & z );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleX( const Mat4<T> & mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleY( const Mat4<T> & mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleZ( const Mat4<T> & mat, const T & z );

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
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y );

	/************************************************************************/
	/* INVERTED Local Space scale                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleXInv( Mat4<T> * mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleYInv( Mat4<T> * mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleZInv( Mat4<T> * mat, const T & z );


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleXInv( const Mat4<T> & mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleYInv( const Mat4<T> & mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleZInv( const Mat4<T> & mat, const T & z );


	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const T & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const T & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & s );
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y );

	/************************************************************************/
	/* Local Space Translations                                             */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void translateX( Mat4<T> * mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateY( Mat4<T> * mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZ( Mat4<T> * mat, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateX( const Mat4<T> & mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateY( const Mat4<T> & mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZ( const Mat4<T> & mat, const T & z );


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
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const T & x, const T & y );
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
	MATH_FUNC_QUALIFIER void translateXInv( Mat4<T> * mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateYInv( Mat4<T> * mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZInv( Mat4<T> * mat, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateXInv( const Mat4<T> & mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateYInv( const Mat4<T> & mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZInv( const Mat4<T> & mat, const T & z );

	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y );

	/************************************************************************/
	/* World Space Translation                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER void translateXWS( Mat4<T> * mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateYWS( Mat4<T> * mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZWS( Mat4<T> * mat, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateXWS( const Mat4<T> & mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateYWS( const Mat4<T> & mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZWS( const Mat4<T> & mat, const T & z );

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y );

	/************************************************************************/
	/* World Space Set Translation                                          */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionX( Mat4<T> * mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionY( Mat4<T> * mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionZ( Mat4<T> * mat, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionX( const Mat4<T> & mat, const T & x );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionY( const Mat4<T> & mat, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionZ( const Mat4<T> & mat, const T & z );

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const T & x, const T & y );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y );


	/************************************************************************/
	/* Local Space Rotation                                                 */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const Mat4<T> & m, const T & angle, const T & x, const T & y, const T & z );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const Mat4<T> & m, const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void rotateNormalized( Mat4<T> * m, const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const Mat4<T> & m, Mat4<T> * resultMat, const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const T & angle, const Vec3<T> & v );


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const Mat4<T> & m, const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const Mat4<T> & m, const T & angle );
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( Mat4<T> * m, const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( Mat4<T> * m, const T & angle );
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( const Mat4<T> & m, Mat4<T> * resultMat, const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( const Mat4<T> & m, Mat4<T> * resultMat, const T & angle );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const T & angle, const Vec3<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const T & angle );






	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> perspective( const T & fovy, const T & aspect, const T & near, const T & far );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAt( const Vec3<T> & position, const Vec3<T> & target, const Vec3<T> & up );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAtNormalized( const Vec3<T> & position, const Vec3<T> & orientation, const Vec3<T> & up );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAt( const Vec3<T> & position, const Vec3<T> & target );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAtNormalized( const Vec3<T> & position, const Vec3<T> & orientation );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> ortho( const T & left, const T & right, const T & bottom, const T & top, const T & zNear, const T & zFar );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> ortho( const T & left, const T & right, const T & bottom, const T & top );


}


#include "Transformations.hpp"
