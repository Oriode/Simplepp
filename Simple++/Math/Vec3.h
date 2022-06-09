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


		MATH_FUNC_QUALIFIER T & operator[](Size index );
		MATH_FUNC_QUALIFIER const T & operator[](Size index ) const;


		/************************************************************************/
		/* Arithmetic                                                             */
		/************************************************************************/
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec3<T>& apply(Compare& func, const Vec3<T>& v);
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec3<T>& apply(Compare& func, const T& v);
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec3<T>& apply(Compare& func);

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

		template<typename S = String>
		MATH_FUNC_QUALIFIER S toString() const;

		constexpr Size getSize() const;

		const T* getData() const;


		union {
			struct { T r, g, b; };
			struct { T h, s, l; };
			struct { T x, y, z; };
			struct { T values[3]; };
		};

		static const Vec3<T> null;


		template<typename Compare>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const Vec3<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const T & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const Vec3<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const T & v )const;

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

	typedef Vec3<MATH_FLOAT_DEFAULT> vec3;
	typedef Vec3<float> vec3f;
	typedef Vec3<double> vec3fd;
	typedef Vec3<char> vec3c;
	typedef Vec3<unsigned char> vec3uc;
	typedef Vec3<int> vec3i;
	typedef Vec3<unsigned int> vec3ui;
	typedef Vec3<long int> vec3l;
	typedef Vec3<unsigned long int> vec3ul;
}



#include "Vec3.hpp"
