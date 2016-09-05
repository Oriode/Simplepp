#pragma once

#include <ostream>

#include "Vec4.h"
#include "Operations.h"

namespace Math {



	template<typename T = float>
	class Mat4 {
	public:
		typedef Vec4<T> colType;

		MATH_FUNC_QUALIFIER Mat4( void );


		MATH_FUNC_QUALIFIER Mat4( const Mat4<T> & m );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat4( const Mat4<U> & m );

		MATH_FUNC_QUALIFIER Mat4( const T & v );
		MATH_FUNC_QUALIFIER Mat4( const T & v11, const T & v21, const T & v31, const T & v41,
								  const T & v12, const T & v22, const T & v32, const T & v42,
								  const T & v13, const T & v23, const T & v33, const T & v43,
								  const T & v14, const T & v24, const T & v34, const T & v44 );
		MATH_FUNC_QUALIFIER Mat4( const T * datas );
		MATH_FUNC_QUALIFIER Mat4( const colType & col0, const colType & col1, const colType & col2, const colType & col3 );


		MATH_FUNC_QUALIFIER Vec4<T> & operator[]( unsigned int index );
		MATH_FUNC_QUALIFIER const Vec4<T> & operator[]( unsigned int index ) const;


		/************************************************************************/
		/* Multiply                                                             */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat4<T> & operator*=( const Mat4<T> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator*=( const colType & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator*=( const T & v );

		/************************************************************************/
		/* Divide                                                               */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Mat4<T> & operator/=( const Mat4<T> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator/=( const colType & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator/=( const T & v );


		/************************************************************************/
		/* Add                                                                  */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat4<T> & operator+=( const Mat4<T> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator+=( const colType & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator+=( const T & v );


		/************************************************************************/
		/* Minus                                                                */
		/************************************************************************/

		MATH_FUNC_QUALIFIER Mat4<T> & operator-=( const Mat4<T> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator-=( const colType & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator-=( const T & v );

		/************************************************************************/
		/* Others                                                               */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Mat4<T> & operator>>=( const Mat4<T> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator>>=( const T & v );

		MATH_FUNC_QUALIFIER Mat4<T> & operator<<=( const Mat4<T> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Mat4<T> & operator++();
		MATH_FUNC_QUALIFIER Mat4<T> & operator--();

		MATH_FUNC_QUALIFIER Mat4<T> & operator=( const Mat4<T> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator=( const Mat4<U> & m );

		MATH_FUNC_QUALIFIER Mat4<T> & operator=( const T & v );

		MATH_FUNC_QUALIFIER bool operator==( const Mat4<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator!=( const Mat4<T> & m ) const;

		MATH_FUNC_QUALIFIER bool operator<( const Mat4<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator<=( const Mat4<T> & m ) const;

		MATH_FUNC_QUALIFIER bool operator>( const Mat4<T> & m ) const;
		MATH_FUNC_QUALIFIER bool operator>=( const Mat4<T> & m ) const;

		MATH_FUNC_QUALIFIER Mat4<T> inverse() const;

		template<typename C = char>
		MATH_FUNC_QUALIFIER BasicString<C> toString() const;

		MATH_FUNC_QUALIFIER T getDeterminant() const;

		union {
			struct {
				colType column1;
				colType column2;
				colType column3;
				colType column4;
			};
			struct { colType column[4]; };

		};

		static const Mat4<T> identity;

	private:
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare func, const Mat4<T> & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare func, const Mat4<T> & v ) const;
	};

	template<typename T>
	const Mat4<T> Mat4<T>::identity = Mat4<T>( 1 );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*( const Mat4<T> & m1, const Mat4<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator*( const Mat4<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator*( const U & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::colType operator*( const typename Mat4<T>::colType & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::colType operator*( const Mat4<T> & m, const typename Mat4<T>::colType & v );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::colType operator*( const Mat4<T> & m, const typename Mat3<T>::colType & v );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/( const Mat4<T> & m1, const Mat4<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator/( const Mat4<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator/( const U & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+( const Mat4<T> & m1, const Mat4<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator+( const Mat4<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator+( const U & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-( const Mat4<T> & m1, const Mat4<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator-( const Mat4<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator-( const U & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator >> ( const Mat4<T> & m1, const Mat4<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator >> ( const Mat4<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator >> ( const U & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<( const Mat4<T> & m1, const Mat4<T> & m2 );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<( const Mat4<T> & m, const U & v );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<( const U & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Mat4<T> & v );

	template<typename T, typename C = char>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<( BasicString<C> & stream, const Mat4<T> & v );

	typedef Mat4<MATH_FLOAT_DEFAULT> mat4;
	typedef Mat4<float> mat4f;
	typedef Mat4<double> mat4d;
	typedef Mat4<char> mat4c;
	typedef Mat4<unsigned char> mat4uc;
	typedef Mat4<int> mat4i;
	typedef Mat4<unsigned int> mat4ui;
	typedef Mat4<long> mat4l;
	typedef Mat4<unsigned long> mat4ul;

}


#include "Mat4.hpp"
