#pragma once

#include "Logical.h"
#include "Operations.h"
#include "../String.h"
#include "../JSON/Node.h"

namespace Math {


	template<typename T = float>
	class Vec2 : public IO::BasicIO, public JSON::Jsonable {
	public:
		typedef T Type;

		MATH_FUNC_QUALIFIER Vec2( void );
		MATH_FUNC_QUALIFIER Vec2( const T & v );
		MATH_FUNC_QUALIFIER Vec2( const T & x, const T & y );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2( const Vec2<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2( const U( &v )[2] );


		template<typename U = char>
		MATH_FUNC_QUALIFIER operator BasicString<U>() const;

		MATH_FUNC_QUALIFIER T & operator[](Size index );
		MATH_FUNC_QUALIFIER const T & operator[](Size index ) const;


		/************************************************************************/
		/* Arithmetic                                                           */
		/************************************************************************/
		template<typename Functor>
		MATH_FUNC_QUALIFIER Vec2<T>& apply(Functor& func, const Vec2<T>& v);
		template<typename Functor>
		MATH_FUNC_QUALIFIER Vec2<T>& apply(Functor& func, const T& v);
		template<typename Functor>
		MATH_FUNC_QUALIFIER Vec2<T>& apply(Functor& func);

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator*=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator*=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator/=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator/=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator+=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator+=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator-=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator-=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator>>=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator>>=( const T & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator<<=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Vec2<T> & operator++();
		MATH_FUNC_QUALIFIER Vec2<T> & operator--();
		MATH_FUNC_QUALIFIER Vec2<T> operator-() const;

		/************************************************************************/
		/* Assignments                                                          */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Vec2<T> & operator=( const T & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator=( const Vec2<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator=( const U( &v )[2] );

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		MATH_FUNC_QUALIFIER void inverse();

		template<typename S = String>
		MATH_FUNC_QUALIFIER S toString() const;

		constexpr Size getSize() const;

		const T* getData() const;

		/**
		 * @brief 	Fill the complete vector with the specified value.
		 * @param 	v	Value to be copied in the whole vector.
		 */
		Vec2<T>& fill(const T& v);

		Vec2<T>& zeros();
		Vec2<T>& ones();
		Vec2<T>& randomF();
		Vec2<T>& random(const T& min, const T& max);

		///@brief Read a JSON object and set this to the read values.
		///@param nodeArray Pointer to the JSON object to be read.
		///@return true if success, false otherwise.
		template<typename S = UTF8String>
		bool fromJSON(const JSON::BasicNodeT<S>* node);

		///@brief Write this object to a Json object
		///@param o Json node to write to.
		template<typename S = UTF8String>
		JSON::BasicNodeT<S>* toJSON() const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write(Stream* stream) const;


		union {
			struct { T r, g; };
			struct { T x, y; };
			struct { T values[2]; };
			struct { T begin, end; };
		};

		static const Vec2<T> null;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const Vec2<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool AND( Compare & func, const T & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const Vec2<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool OR( Compare & func, const T & v )const;
	};


	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec2<T> & v1, const T & v2 );


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const T & v1, const Vec2<T> & v2 );


	typedef Vec2<MATH_FLOAT_DEFAULT> vec2;
	typedef Vec2<float> vec2f;
	typedef Vec2<double> vec2d;
	typedef Vec2<char> vec2c;
	typedef Vec2<unsigned char> vec2uc;
	typedef Vec2<int> vec2i;
	typedef Vec2<unsigned int> vec2ui;
	typedef Vec2<long int> vec2l;
	typedef Vec2<unsigned long int> vec2ul;


}




#include "Vec2.hpp"
