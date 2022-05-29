#pragma once

#include "Vec3.h"


namespace Math {

	template<typename T = float>
	class Vec4 {
	public:
		typedef T Type;

		MATH_FUNC_QUALIFIER Vec4( void );
		MATH_FUNC_QUALIFIER Vec4( const T & v );
		MATH_FUNC_QUALIFIER Vec4( const T & x, const T & y, const T & z, const T & w );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4( const Vec4<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4( const U( &v )[4] );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4( const Vec3<U> & v );
		MATH_FUNC_QUALIFIER Vec4( const Vec3<T> & v, const T & w );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec4( const Vec2<T> & v, const T & z, const T & w );


		template<typename U = char>
		MATH_FUNC_QUALIFIER operator BasicString<U>() const;

		MATH_FUNC_QUALIFIER operator Vec2<T>() const;
		MATH_FUNC_QUALIFIER operator Vec3<T>() const;


		MATH_FUNC_QUALIFIER T & operator[](Size index );
		MATH_FUNC_QUALIFIER const T & operator[](Size index ) const;


		/************************************************************************/
		/* Swizzle                                                              */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Vec3<T> xyz() const;
		MATH_FUNC_QUALIFIER Vec2<T> xy() const;


		/************************************************************************/
		/* Arithmetic                                                             */
		/************************************************************************/

		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec4<T>& apply(Compare& func, const Vec4<T>& v);
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec4<T>& apply(Compare& func, const T& v);
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec4<T>& apply(Compare& func);

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator*=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator*=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator/=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator/=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator+=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator+=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator-=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator-=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator>>=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator>>=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator<<=( const Vec4<U>  & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Vec4<T> & operator++();
		MATH_FUNC_QUALIFIER Vec4<T> & operator--();
		MATH_FUNC_QUALIFIER Vec4<T> operator-() const;


		/************************************************************************/
		/* Assignments                                                          */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator=( const Vec4<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator=( const U( &v )[4] );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator=( const Vec3<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec4<T> & operator=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec4<T> & operator=( const T & v );


		MATH_FUNC_QUALIFIER void inverse();

		template<typename U = char>
		MATH_FUNC_QUALIFIER BasicString<U> toString() const;

		constexpr Size getSize() const;

		const T* getData() const;

		union {
			struct { T r, g, b, a; };
			struct { T h, s, l, a; };
			struct { T x, y, z, w; };
			struct { T values[4]; };
		};

		static const Vec4<T> null;


		template<typename Compare>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const Vec4<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const T & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const Vec4<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const T & v )const;

	};



	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec4<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec4<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec4<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec4<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec4<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec4<T> & v1, const T & v2 );


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+( const T & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+( const Vec4<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-( const Vec4<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-( const T & v1, const Vec4<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*( const Vec4<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*( const T & v1, const Vec4<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/( const Vec4<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/( const T & v1, const Vec4<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator >> ( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator >> ( const Vec4<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator >> ( const T & v1, const Vec4<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<( const Vec4<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<( const T & v1, const Vec4<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator%( const Vec4<T> & v1, const Vec4<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator%( const Vec4<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator%( const T & v1, const Vec4<T> & v2 );



	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Vec4<T> & v );

	template<typename T, typename U = char>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<( BasicString<U> & stream, const Vec4<T> & v );

	typedef Vec4<MATH_FLOAT_DEFAULT> vec4;
	typedef Vec4<float> vec4f;
	typedef Vec4<double> vec4d;
	typedef Vec4<char> vec4c;
	typedef Vec4<unsigned char> vec4uc;
	typedef Vec4<int> vec4i;
	typedef Vec4<unsigned int> vec4ui;
	typedef Vec4<long int> vec4l;
	typedef Vec4<unsigned long int> vec4ul;

}


#include "Vec4.hpp"
