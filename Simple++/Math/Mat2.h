#pragma once

#include "../BuildConfig.h"
#include "Vec2.h"
#include "Operations.h"

namespace Math {

	template<typename T = float>
	class Mat2 {
	public:
		typedef Vec2<T> colType;


		MATH_FUNC_QUALIFIER Mat2( void );

		MATH_FUNC_QUALIFIER Mat2( const Mat2<T> & m );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat2( const Mat2<U> & m );

		MATH_FUNC_QUALIFIER Mat2( const T & v );
		MATH_FUNC_QUALIFIER Mat2( const T & v11, const T & v21,
								  const T & v12, const T & v22 );
		MATH_FUNC_QUALIFIER Mat2( const colType & col0, const colType & col1 );

		MATH_FUNC_QUALIFIER Vec2<T> & operator[]( unsigned int index );
		MATH_FUNC_QUALIFIER const Vec2<T> & operator[]( unsigned int index ) const;


		/************************************************************************/
		/* Multiply                                                             */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat2<T> & operator*=( const Mat2<T> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator*=( const colType & v );
		MATH_FUNC_QUALIFIER Mat2<T> & operator*=( const T & v );

		/************************************************************************/
		/* Divide                                                               */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Mat2<T> & operator/=( const Mat2<T> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator/=( const colType & v );
		MATH_FUNC_QUALIFIER Mat2<T> & operator/=( const T & v );


		/************************************************************************/
		/* Add                                                                  */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat2<T> & operator+=( const Mat2<T> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator+=( const colType & v );
		MATH_FUNC_QUALIFIER Mat2<T> & operator+=( const T & v );


		/************************************************************************/
		/* Minus                                                                */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat2<T> & operator-=( const Mat2<T> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator-=( const colType & v );
		MATH_FUNC_QUALIFIER Mat2<T> & operator-=( const T & v );

		/************************************************************************/
		/* Others                                                               */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Mat2<T> & operator>>=( const Mat2<T> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator>>=( const T & v );

		MATH_FUNC_QUALIFIER Mat2<T> & operator<<=( const Mat2<T> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Mat2<T> & operator++();
		MATH_FUNC_QUALIFIER Mat2<T> & operator--();

		MATH_FUNC_QUALIFIER Mat2<T> & operator=( const Mat2<T> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat2<T> & operator=( const Mat2<U> & m );
		MATH_FUNC_QUALIFIER Mat2<T> & operator=( const T & v );

		MATH_FUNC_QUALIFIER bool operator==( const Mat2<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator!=( const Mat2<T> & m ) const;

		MATH_FUNC_QUALIFIER bool operator<( const Mat2<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator<=( const Mat2<T> & m ) const;

		MATH_FUNC_QUALIFIER bool operator>( const Mat2<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator>=( const Mat2<T> & m ) const;


		MATH_FUNC_QUALIFIER Mat2<T> inverse() const;

		template<typename C = char>
		MATH_FUNC_QUALIFIER BasicString<C> toString() const;

		MATH_FUNC_QUALIFIER T getDeterminant() const;

		Vec2<T> column[2];

	private:
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare func, const Mat2<T> & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare func, const Mat2<T> & v ) const;
	};

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator*( const Mat2<T> & m1, const Mat2<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator*( const Mat2<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator*( const U & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat2<T>::colType operator*( const typename Mat2<T>::colType & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat2<T>::colType operator*( const Mat2<T> & m, const typename Mat2<T>::colType & v );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator/( const Mat2<T> & m1, const Mat2<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator/( const Mat2<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator/( const U & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator+( const Mat2<T> & m1, const Mat2<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator+( const Mat2<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator+( const U & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator-( const Mat2<T> & m1, const Mat2<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator-( const Mat2<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator-( const U & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator >> ( const Mat2<T> & m1, const Mat2<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator >> ( const Mat2<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator >> ( const U & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator<<( const Mat2<T> & m1, const Mat2<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator<<( const Mat2<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator<<( const U & v, const Mat2<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Mat2<T> & v );

	template<typename T, typename C = char>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<( BasicString<C> & stream, const Mat2<T> & v );

	typedef Mat2<MATH_FLOAT_DEFAULT> mat2;
	typedef Mat2<float> mat2f;
	typedef Mat2<double> mat2d;
	typedef Mat2<char> mat2c;
	typedef Mat2<unsigned char> mat2uc;
	typedef Mat2<int> mat2i;
	typedef Mat2<unsigned int> mat2ui;
	typedef Mat2<long> mat2l;
	typedef Mat2<unsigned long> mat2ul;
}


#include "Mat2.hpp"
