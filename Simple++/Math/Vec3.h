#pragma once

#include "Vec2.h"



namespace Math {

	template<typename T = float>
	class Vec3 {
	public:
		MATH_FUNC_QUALIFIER Vec3( void );
		MATH_FUNC_QUALIFIER Vec3( const T & v );
		MATH_FUNC_QUALIFIER Vec3( const T & x, const T & y, const T & z );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3( const Vec3<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3( const Vec2<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3( const U( &v )[3] );
		MATH_FUNC_QUALIFIER Vec3( const Vec2<T> & v, const T & z );


		template<typename U = char>
		MATH_FUNC_QUALIFIER operator BasicString<U>() const;

		MATH_FUNC_QUALIFIER operator Vec2<T>() const;


		/************************************************************************/
		/* Swizzle                                                              */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Vec2<T> xy() const;


		MATH_FUNC_QUALIFIER T & operator[]( unsigned int index );
		MATH_FUNC_QUALIFIER const T & operator[]( unsigned int index ) const;


		/************************************************************************/
		/* Arithmetic                                                             */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator*=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec3<T> & operator*=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator/=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec3<T> & operator/=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator+=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec3<T> & operator+=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator-=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec3<T> & operator-=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator>>=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec3<T> & operator>>=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator<<=( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec3<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Vec3<T> & operator++();
		MATH_FUNC_QUALIFIER Vec3<T> & operator--();
		MATH_FUNC_QUALIFIER Vec3<T> operator-() const;


		/************************************************************************/
		/* Assignments                                                          */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Vec3<T> & operator=( const T & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator=( const Vec3<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator=( const Vec2<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec3<T> & operator=( const U( &v )[3] );


		MATH_FUNC_QUALIFIER void inverse();

		template<typename U = char>
		MATH_FUNC_QUALIFIER BasicString<U> toString() const;


		union {
			struct { T r, g, b; };
			struct { T h, s, l; };
			struct { T x, y, z; };
			struct { T values[3]; };
		};

		static const Vec3<T> null;


		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare & func, const Vec3<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare & func, const T & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare & func, const Vec3<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare & func, const T & v )const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec3<T> & _MathOperator( Compare & func, const Vec3<T> & v );
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec3<T> & _MathOperator( Compare & func, const T & v );

	};



	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec3<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec3<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec3<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec3<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec3<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec3<T> & v1, const T & v2 );


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const T & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const Vec3<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const Vec3<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const T & v1, const Vec3<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const Vec3<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const T & v1, const Vec3<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const Vec3<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const T & v1, const Vec3<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator >> ( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator >> ( const Vec3<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator >> ( const T & v1, const Vec3<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const Vec3<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const T & v1, const Vec3<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator%( const Vec3<T> & v1, const Vec3<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator%( const Vec3<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator%( const T & v1, const Vec3<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Vec3<T> & v );

	template<typename T, typename U = char>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<( BasicString<U> & stream, const Vec3<T> & v );

	typedef Vec3<MATH_FLOAT_DEFAULT> vec3;
	typedef Vec3<float> vec3f;
	typedef Vec3<double> vec3fd;
	typedef Vec3<char> vec3c;
	typedef Vec3<unsigned char> vec3uc;
	typedef Vec3<int> vec3i;
	typedef Vec3<unsigned int> vec3ui;
	typedef Vec3<long> vec3l;
	typedef Vec3<unsigned long> vec3ul;
}



#include "Vec3.hpp"
