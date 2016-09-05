#pragma once

#include "../BuildConfig.h"
#include "Vec3.h"
#include "Operations.h"


namespace Math {

	template<typename T = float>
	class Mat3 {
	public:
		typedef Vec3<T> colType;


		MATH_FUNC_QUALIFIER Mat3( void );

		MATH_FUNC_QUALIFIER Mat3( const Mat3<T> & m );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat3( const Mat3<U> & m );

		MATH_FUNC_QUALIFIER Mat3( const T & v );
		MATH_FUNC_QUALIFIER Mat3( const T & v11, const T & v21, const T & v31,
								  const T & v12, const T & v22, const T & v32,
								  const T & v13, const T & v23, const T & v33 );
		MATH_FUNC_QUALIFIER Mat3( const colType & col0, const colType & col1, const colType & col2 );

		MATH_FUNC_QUALIFIER Vec3<T> & operator[]( unsigned int index );
		MATH_FUNC_QUALIFIER const Vec3<T> & operator[]( unsigned int index ) const;


		/************************************************************************/
		/* Multiply                                                             */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat3<T> & operator*=( const Mat3<T> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator*=( const colType & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator*=( const T & v );

		/************************************************************************/
		/* Divide                                                               */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Mat3<T> & operator/=( const Mat3<T> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator/=( const colType & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator/=( const T & v );


		/************************************************************************/
		/* Add                                                                  */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat3<T> & operator+=( const Mat3<T> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator+=( const colType & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator+=( const T & v );


		/************************************************************************/
		/* Minus                                                                */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat3<T> & operator-=( const Mat3<T> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator-=( const colType & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator-=( const T & v );

		/************************************************************************/
		/* Others                                                               */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Mat3<T> & operator>>=( const Mat3<T> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator>>=( const T & v );

		MATH_FUNC_QUALIFIER Mat3<T> & operator<<=( const Mat3<T> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Mat3<T> & operator++();
		MATH_FUNC_QUALIFIER Mat3<T> & operator--();

		MATH_FUNC_QUALIFIER Mat3<T> & operator=( const Mat3<T> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator=( const Mat3<U> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator=( const T & v );

		MATH_FUNC_QUALIFIER bool operator==( const Mat3<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator!=( const Mat3<T> & m ) const;

		MATH_FUNC_QUALIFIER bool operator<( const Mat3<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator<=( const Mat3<T> & m ) const;

		MATH_FUNC_QUALIFIER bool operator>( const Mat3<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator>=( const Mat3<T> & m ) const;



		MATH_FUNC_QUALIFIER Mat3<T> inverse() const;

		template<typename C = char>
		MATH_FUNC_QUALIFIER BasicString<C> toString() const;

		MATH_FUNC_QUALIFIER T getDeterminant() const;

		Vec3<T> column[3];

	private:
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare func, const Mat3<T> & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare func, const Mat3<T> & v ) const;
	};

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const Mat3<T> & m1, const Mat3<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const Mat3<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const U & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat3<T>::colType operator*( const typename Mat3<T>::colType & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat3<T>::colType operator*( const Mat3<T> & m, const typename Mat3<T>::colType & v );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const Mat3<T> & m1, const Mat3<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const Mat3<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const U & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const Mat3<T> & m1, const Mat3<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const Mat3<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const U & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const Mat3<T> & m1, const Mat3<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const Mat3<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const U & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const Mat3<T> & m1, const Mat3<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const Mat3<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const U & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const Mat3<T> & m1, const Mat3<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const Mat3<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const U & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Mat3<T> & v );

	template<typename T, typename C = char>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<( BasicString<C> & stream, const Mat3<T> & v );

	typedef Mat3<MATH_FLOAT_DEFAULT> mat3;
	typedef Mat3<float> mat3f;
	typedef Mat3<double> mat3d;
	typedef Mat3<char> mat3c;
	typedef Mat3<unsigned char> mat3uc;
	typedef Mat3<int> mat3i;
	typedef Mat3<unsigned int> mat3ui;
	typedef Mat3<long> mat3l;
	typedef Mat3<unsigned long> mat3ul;
}


#include "Mat3.hpp"
