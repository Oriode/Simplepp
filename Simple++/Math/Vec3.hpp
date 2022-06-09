#include "Vec3.h"
namespace Math {

	template<typename T>
	const Vec3<T> Vec3<T>::null = Vec3<T>( 0 );


	

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::OR( Compare & func, const Vec3<T> & v ) const {
		return func( this -> x, v.x ) || func( this -> y, v.y ) || func( this -> z, v.z );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::OR( Compare & func, const T & v ) const {
		return func( this -> x, v ) || func( this -> y, v ) || func( this -> z, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::AND( Compare & func, const Vec3<T> & v ) const {
		return func( this -> x, v.x ) && func( this  -> y, v.y ) && func( this  -> z, v.z );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::AND( Compare & func, const T & v ) const {
		return func( this -> x, v ) && func( this  -> y, v ) && func( this  -> z, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::apply( Compare & func, const T & v ) {
		func( this -> x, v );
		func( this -> y, v );
		func( this -> z, v );
		return *this;
	}
	template<typename T>
	template<typename Compare>
	inline MATH_FUNC_QUALIFIER Vec3<T>& Vec3<T>::apply(Compare& func) {
		func(this -> x);
		func(this -> y);
		func(this -> z);
		return *this;
	}
	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::apply( Compare & func, const Vec3<T> & v ) {
		func( this -> x, v.x );
		func( this -> y, v.y );
		func( this -> z, v.z );
		return *this;
	}








	template<typename T>
	MATH_FUNC_QUALIFIER void Vec3<T>::inverse() {
		this -> x = T( 1 ) / x;
		this -> y = T( 1 ) / y;
		this -> z = T( 1 ) / z;
	}

	template<typename T>
	inline constexpr Size Vec3<T>::getSize() const {
		return Size(3);
	}

	template<typename T>
	inline const T* Vec3<T>::getData() const {
		return this->values;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const T & x, const T & y, const T & z ) {
		this -> x = x;
		this -> y = y;
		this -> z = z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> Vec3<T>::xy() const {
		return Vec2<T>( this -> x, this -> y );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator-=( const T & v ) {
		return apply( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator-=( const Vec3<U> & v ) {
		return apply( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator+=( const T & v ) {
		return apply( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator+=( const Vec3<U> & v ) {
		return apply( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator/=( const T & v ) {
		return apply( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator/=( const Vec3<U> & v ) {
		return apply( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator*=( const T & v ) {
		return apply( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator*=( const Vec3<U> & v ) {
		return apply( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator>>=( const T & v ) {
		return apply( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator>>=( const Vec3<U> & v ) {
		return apply( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator<<=( const T & v ) {
		return apply( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator<<=( const Vec3<U> & v ) {
		return apply( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator++() {
		return apply(Math::Operations::Increment());
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator--() {
		return apply(Math::Operations::Decrement());
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> Vec3<T>::operator-() const {
		return apply(Math::Operations::MinusUnary());
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T & Vec3<T>::operator[](Size index ) {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec3<T>::operator[](Size index ) const {
		return this -> values[index];
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec2<U> & v ) : z(0) {
		*this = v;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const U( &v )[3] ) : x( v[0] ), y( v[1] ), z( v[2] ) {
	}
	
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec2<T> & v, const T & z ) {
		*this = v;
		this -> z = z;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const Vec2<U> & v ) {
		this -> x = v.x;
		this -> y = v.y;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const T & v ) {
		return apply( Math::Operations::Assign(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const Vec3<U> & v ) {
		this -> x = T( v.x );
		this -> y = T( v.y );
		this -> z = T( v.z );
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const U( &v )[3] ) {
		this -> x = T( v[0] );
		this -> y = T( v[1] );
		this -> z = T( v[2] );
		return *this;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const T & v ) {
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec3<U> & v ) {
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( void ) {
	}

	


	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.AND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec3<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec3<T> & v2 ) {
		return v2.AND( Math::Logical::Equal(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.OR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec3<T> & v1, const T & v2 ) {
		return v1.OR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec3<T> & v2 ) {
		return v2.OR( Math::Logical::NotEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.AND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec3<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec3<T> & v2 ) {
		return v2.AND( Math::Logical::GreaterOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.AND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec3<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec3<T> & v2 ) {
		return v2.AND( Math::Logical::LessOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.AND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec3<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec3<T> & v2 ) {
		return v2.AND( Math::Logical::Greater(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.AND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec3<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec3<T> & v2 ) {
		return v2.AND( Math::Logical::Less(), v1 );
	}
	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x + v2, v1.y + v2, v1.z + v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 + v2.x, v1 + v2.y, v1 + v2.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x - v2, v1.y - v2, v1.z - v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 - v2.x, v1 - v2.y, v1 - v2.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x / v2, v1.y / v2, v1.z / v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 / v2.x, v1 / v2.y, v1 / v2.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x * v2, v1.y * v2, v1.z * v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 * v2.x, v1 * v2.y, v1 * v2.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator >> ( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator >> ( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x >> v2, v1.y >> v2, v1.z >> v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator >> ( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 >> v2.x, v1 >> v2.y, v1 >> v2.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x << v2.x, v1.y << v2.y, v1.z << v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x << v2, v1.y << v2, v1.z << v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 << v2.x, v1 << v2.y, v1 << v2.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator%( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.x % v2.x, v1.y % v2.y, v1.z % v2.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator%( const Vec3<T> & v1, const T & v2 ) {
		return Vec3<T>( v1.x % v2, v1.y % v2, v1.z % v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator%( const T & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1 % v2.x, v1 % v2.y, v1 % v2.z );
	}

	template<typename T /*= float*/>
	template<typename S /*=String*/>
	MATH_FUNC_QUALIFIER S Vec3<T>::toString() const {
		S newString;
		newString.reserve( 60 );
		newString << S::ElemType( '[' ) << this -> x << S::ElemType( '\t' ) << this -> y << S::ElemType( '\t' ) << this -> z << S::ElemType( ']' );
		return newString;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::operator BasicString<U>() const {
		return toString<BasicString<U>>();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::operator Vec2<T>() const {
		return xy();
	}


}
