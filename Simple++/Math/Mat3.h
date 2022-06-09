#pragma once

#include "../BuildConfig.h"
#include "Vec3.h"
#include "Operations.h"


namespace Math {

	template<typename T = float>
	class Mat3 {
	public:
		typedef Vec3<T> ColType;


		MATH_FUNC_QUALIFIER Mat3( void );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3( const Mat3<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3( const U( &m )[9] );

		MATH_FUNC_QUALIFIER Mat3( const T & v );
		MATH_FUNC_QUALIFIER Mat3( const T & v11, const T & v21, const T & v31,
								  const T & v12, const T & v22, const T & v32,
								  const T & v13, const T & v23, const T & v33 );
		MATH_FUNC_QUALIFIER Mat3( const ColType & col0, const ColType & col1, const ColType & col2 );

		MATH_FUNC_QUALIFIER Vec3<T> & operator[](Size index );
		MATH_FUNC_QUALIFIER const Vec3<T> & operator[](Size index ) const;

		template<typename U>
		MATH_FUNC_QUALIFIER operator BasicString<U>() const;

		/************************************************************************/
		/* Arithmetic                                                           */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator*=( const Mat3<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator*=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator*=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator/=( const Mat3<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator/=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator/=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator+=( const Mat3<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator+=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator+=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator-=( const Mat3<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator-=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Mat3<T> & operator-=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator>>=( const Mat3<U> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator>>=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator<<=( const Mat3<U> & m );
		MATH_FUNC_QUALIFIER Mat3<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Mat3<T> & operator++();
		MATH_FUNC_QUALIFIER Mat3<T> & operator--();
		MATH_FUNC_QUALIFIER Mat3<T> operator-() const;


		/************************************************************************/
		/* Assign                                                               */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator=( const Mat3<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat3<T> & operator=( const U( &m )[9] );
		MATH_FUNC_QUALIFIER Mat3<T> & operator=( const T & v );


		/************************************************************************/
		/* Logical                                                              */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator==( const Mat3<U> & m ) const;
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator!=( const Mat3<U> & m ) const;

		template<typename U>
		MATH_FUNC_QUALIFIER bool operator<( const Mat3<U> & m ) const;
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator<=( const Mat3<U> & m ) const;

		template<typename U>
		MATH_FUNC_QUALIFIER bool operator>( const Mat3<U> & m ) const;
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator>=( const Mat3<U> & m ) const;



		MATH_FUNC_QUALIFIER Mat3<T> inverse() const;

		template<typename S = String>
		MATH_FUNC_QUALIFIER S toString() const;

		MATH_FUNC_QUALIFIER T getDeterminant() const;

		union {
			struct {
				ColType column1;
				ColType column2;
				ColType column3;
			};
			struct { ColType column[3]; };

		};

		static const Mat3<T> identity;
	private:
		template<typename Compare, typename U>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const Mat3<U> & v ) const;

		template<typename Compare, typename U>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const Mat3<U> & v ) const;
	};

	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const T & v, const Mat3<T> & m );

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER typename Mat3<T>::ColType operator*( const Vec3<U> & v, const Mat3<T> & m );
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER typename Mat3<T>::ColType operator*( const Mat3<T> & m, const Vec3<U> & v );


	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const T & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const T & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const T & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const T & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const T & v, const Mat3<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator%( const Mat3<T> & m1, const Mat3<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator%( const Mat3<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator%( const T & v, const Mat3<T> & m );

	typedef Mat3<MATH_FLOAT_DEFAULT> mat3;
	typedef Mat3<float> mat3f;
	typedef Mat3<double> mat3d;
	typedef Mat3<char> mat3c;
	typedef Mat3<unsigned char> mat3uc;
	typedef Mat3<int> mat3i;
	typedef Mat3<unsigned int> mat3ui;
	typedef Mat3<long int> mat3l;
	typedef Mat3<unsigned long int> mat3ul;
}


#include "Mat3.hpp"
