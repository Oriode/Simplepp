#include "Vec4.h"
namespace Math {

	template<typename T>
	const Vec4<T> Vec4<T>::null = Vec4<T>( 0 );

	

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec4<T>::_logicalOperatorOR( Compare & func, const Vec4<T> & v ) const {
		return func( this -> x, v.x ) || func( this -> y, v.y ) || func( this -> z, v.z ) || func( this -> w, v.w );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec4<T>::_logicalOperatorOR( Compare & func, const T & v ) const {
		return func( this -> x, v ) || func( this -> y, v ) || func( this -> z, v ) || func( this -> w, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec4<T>::_logicalOperatorAND( Compare & func, const Vec4<T> & v ) const {
		return func( this -> x, v.x ) && func( this  -> y, v.y ) && func( this  -> z, v.z ) && func( this  -> w, v.w );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec4<T>::_logicalOperatorAND( Compare & func, const T & v ) const {
		return func( this -> x, v ) && func( this  -> y, v ) && func( this  -> z, v ) && func( this  -> w, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::_MathOperator( Compare & func, const T & v ) {
		func( this -> x, v );
		func( this -> y, v );
		func( this -> z, v );
		func( this -> w, v );

		return *this;
	}
	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::_MathOperator( Compare & func, const Vec4<T> & v ) {
		func( this -> x, v.x );
		func( this -> y, v.y );
		func( this -> z, v.z );
		func( this -> w, v.w );

		return *this;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER void Vec4<T>::inverse() {
		this -> x = T( 1 ) / x;
		this -> y = T( 1 ) / y;
		this -> z = T( 1 ) / z;
		this -> w = T( 1 ) / w;
	}

	template<typename T>
	inline constexpr Size Vec4<T>::getSize() const {
		return Size(4);
	}

	template<typename T>
	inline const T* Vec4<T>::getData() const {
		return this->values;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> Vec4<T>::xyz() const {
		return Vec3<T>( this -> x, this -> y, this -> z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> Vec4<T>::xy() const {
		return Vec2<T>( this -> x, this -> y );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T & Vec4<T>::operator[]( unsigned int index ) {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec4<T>::operator[]( unsigned int index ) const {
		return this -> values[index];
	}



	
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const T & x, const T & y, const T & z, const T & w ) :
	x(x),
	y(y),
	z(z),
	w(w)
	{
		
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const Vec4<U> & v ) {
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const U( &v )[4] ) : x( v[0] ), y( v[1] ), z( v[2] ), w( v[3] ) {
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const T & v ) {
		*this = v;
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const Vec3<U> & v ) : w(v) {
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const Vec3<T> & v, const T & w ) {
		*this = v;
		this -> w = w;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const Vec2<U> & v ) : z(0), w(0) {
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( const Vec2<T> & v, const T & z, const T & w ) {
		*this = v;
		this -> z = z;
		this -> w = w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4( void ) {

	}


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator-=( const T & v ) {
		return _MathOperator( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator-=( const Vec4<U> & v ) {
		return _MathOperator( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator+=( const T & v ) {
		return _MathOperator( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator+=( const Vec4<U> & v ) {
		return _MathOperator( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator*=( const T & v ) {
		return _MathOperator( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator*=( const Vec4<U> & v ) {
		return _MathOperator( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator/=( const T & v ) {
		return _MathOperator( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator/=( const Vec4<U> & v ) {
		return _MathOperator( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator>>=( const T & v ) {
		return _MathOperator( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator>>=( const Vec4<U> & v ) {
		return _MathOperator( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator<<=( const T & v ) {
		return _MathOperator( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator<<=( const Vec4<U> & v ) {
		return _MathOperator( Math::Operations::BinaryShiftLeftEqual(), v );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator++() {
		this -> x++;
		this -> y++;
		this -> z++;
		this -> w++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator--() {
		this -> x--;
		this -> y--;
		this -> z--;
		this -> w--;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> Vec4<T>::operator-() const {
		return Vec4<T>( -this -> x, -this -> y, -this -> z, -this -> w );
	}

	/************************************************************************/
	/* Assign                                                               */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=( const T & v ) {
		return _MathOperator( Math::Operations::Assign(), v );
	}



	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=( const Vec3<U> & v ) {
		this -> x = v.x;
		this -> y = v.y;
		this -> z = v.z;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=( const Vec2<U> & v ) {
		this -> x = v.x;
		this -> y = v.y;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=( const Vec4<U> & v ) {
		this -> x = T( v.x );
		this -> y = T( v.y );
		this -> z = T( v.z );
		this -> w = T( v.w );
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=( const U( &v )[4] ) {
		this -> x = T( v[0] );
		this -> y = T( v[1] );
		this -> z = T( v[2] );
		this -> w = T( v[4] );
		return *this;
	}

	

	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec4<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec4<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::Equal(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1._logicalOperatorOR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec4<T> & v1, const T & v2 ) {
		return v1._logicalOperatorOR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec4<T> & v2 ) {
		return v2._logicalOperatorOR( Math::Logical::NotEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec4<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec4<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::GreaterOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec4<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec4<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::LessOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec4<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec4<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::Greater(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec4<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec4<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::Less(), v1 );
	}
	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator >> ( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator >> ( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x >> v2, v1.y >> v2, v1.z >> v2, v1.w >> v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator >> ( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 >> v2.x, v1 >> v2.y, v1 >> v2.z, v1 >> v2.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x << v2, v1.y << v2, v1.z << v2, v1.w << v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 << v2.x, v1 << v2.y, v1 << v2.z, v1 << v2.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator%( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator%( const Vec4<T> & v1, const T & v2 ) {
		return Vec4<T>( v1.x % v2, v1.y % v2, v1.z % v2, v1.w % v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator%( const T & v1, const Vec4<T> & v2 ) {
		return Vec4<T>( v1 % v2.x, v1 % v2.y, v1 % v2.z, v1 % v2.w );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Vec4<T> & v ) {
		stream << '[' << v.x << '\t' << v.y << '\t' << v.z << '\t' << v.w << ']';
		return stream;
	}

	template<typename T /*= float*/>
	template<typename U /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<U> Vec4<T>::toString() const {
		BasicString<U> newString;
		newString.reserve( 80 );
		newString << U( '[' ) << this -> x << U( '\t' ) << this -> y << U( '\t' ) << this -> z << U( '\t' ) << this -> w << U( ']' );
		return newString;
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<( BasicString<U> & string, const Vec4<T> & v ) {
		string << U( '[' ) << v.x << U( '\t' ) << v.y << U( '\t' ) << v.z << U( '\t' ) << v.w << ( ']' );
		return string;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::operator BasicString<U>() const {
		return toString<U>();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::operator Vec2<T>() const {
		return xy();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::operator Vec3<T>() const {
		return xyz();
	}

}
