#pragma once

#include "Vec4.h"
#include "Operations.h"

namespace Math {



	template<typename T = float>
	class Mat4 {
	public:
		typedef Vec4<T> ColType;

		MATH_FUNC_QUALIFIER Mat4( void );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4( const Mat4<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4( const U( &m )[16] );
		MATH_FUNC_QUALIFIER Mat4( const T & v );
		MATH_FUNC_QUALIFIER Mat4( const T & v11, const T & v21, const T & v31, const T & v41,
								  const T & v12, const T & v22, const T & v32, const T & v42,
								  const T & v13, const T & v23, const T & v33, const T & v43,
								  const T & v14, const T & v24, const T & v34, const T & v44 );
		MATH_FUNC_QUALIFIER Mat4( const T * datas );
		MATH_FUNC_QUALIFIER Mat4( const ColType & col0, const ColType & col1, const ColType & col2, const ColType & col3 );

		template<typename U>
		MATH_FUNC_QUALIFIER operator BasicString<U>() const;

		MATH_FUNC_QUALIFIER Vec4<T> & operator[](Size index );
		MATH_FUNC_QUALIFIER const Vec4<T> & operator[](Size index ) const;


		/************************************************************************/
		/* Arithmetic                                                           */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator*=( const Mat4<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator*=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator*=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator/=( const Mat4<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator/=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator/=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator+=( const Mat4<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator+=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator+=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator-=( const Mat4<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator-=( const Vec4<U> & v );
		MATH_FUNC_QUALIFIER Mat4<T> & operator-=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator>>=( const Mat4<U> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator>>=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator<<=( const Mat4<U> & m );
		MATH_FUNC_QUALIFIER Mat4<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Mat4<T> & operator++();
		MATH_FUNC_QUALIFIER Mat4<T> & operator--();
		MATH_FUNC_QUALIFIER Mat4<T> operator-() const;

		/************************************************************************/
		/* Assign                                                               */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator=( const Mat4<U> & m );
		template<typename U>
		MATH_FUNC_QUALIFIER Mat4<T> & operator=( const U( &m )[16] );
		MATH_FUNC_QUALIFIER Mat4<T> & operator=( const T & v );


		/************************************************************************/
		/* Logical                                                              */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator==( const Mat4<U> & m ) const;
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator!=( const Mat4<U> & m ) const;

		template<typename U>
		MATH_FUNC_QUALIFIER bool operator<( const Mat4<U> & m ) const;
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator<=( const Mat4<U> & m ) const;

		template<typename U>
		MATH_FUNC_QUALIFIER bool operator>( const Mat4<U> & m ) const;
		template<typename U>
		MATH_FUNC_QUALIFIER bool operator>=( const Mat4<U> & m ) const;


		MATH_FUNC_QUALIFIER Mat4<T> inverse() const;

		template<typename S = String>
		MATH_FUNC_QUALIFIER S toString() const;

		MATH_FUNC_QUALIFIER T getDeterminant() const;

		union {
			struct {
				ColType column1;
				ColType column2;
				ColType column3;
				ColType column4;
			};
			struct { ColType column[4]; };

		};

		static const Mat4<T> identity;
	private:
		template<typename Compare, typename U>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const Mat4<U> & v ) const;

		template<typename Compare, typename U>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const Mat4<U> & v ) const;
	};


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*( const T & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::ColType operator*( const Vec4<T> & v, const Mat4<T> & m );
	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::ColType operator*( const Mat4<T> & m, const Vec4<T> & v );
	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::ColType operator*( const Mat4<T> & m, const Vec3<T> & v );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/( const T & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+( const T & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-( const T & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator >> ( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator >> ( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator >> ( const T & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<( const T & v, const Mat4<T> & m );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator%( const Mat4<T> & m1, const Mat4<T> & m2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator%( const Mat4<T> & m, const T & v );
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator%( const T & v, const Mat4<T> & m );

	typedef Mat4<MATH_FLOAT_DEFAULT> mat4;
	typedef Mat4<float> mat4f;
	typedef Mat4<double> mat4d;
	typedef Mat4<char> mat4c;
	typedef Mat4<unsigned char> mat4uc;
	typedef Mat4<int> mat4i;
	typedef Mat4<unsigned int> mat4ui;
	typedef Mat4<long int> mat4l;
	typedef Mat4<unsigned long int> mat4ul;

}


#include "Mat4.hpp"
