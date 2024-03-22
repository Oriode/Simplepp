#include "Vec2.h"
namespace Math {

	template<typename T>
	const Vec2<T> Vec2<T>::null = Vec2<T>( 0 );


	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec2<T>::OR( Compare & func, const Vec2<T> & v ) const {
		return func( this -> x, v.x ) || func( this -> y, v.y );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec2<T>::OR( Compare & func, const T & v ) const {
		return func( this -> x, v ) || func( this -> y, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec2<T>::AND( Compare & func, const Vec2<T> & v ) const {
		return func( this -> x, v.x ) && func( this  -> y, v.y );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec2<T>::AND( Compare & func, const T & v ) const {
		return func( this -> x, v ) && func( this  -> y, v );
	}

	template<typename T>
	template<typename Functor>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::apply(Functor& func, const T & v ) {
		func( this -> x, v );
		func( this -> y, v );
		return *this;
	}
	template<typename T>
	template<typename Functor>
	MATH_FUNC_QUALIFIER Vec2<T>& Vec2<T>::apply(Functor& func) {
		func(this -> x);
		func(this -> y);
		return *this;
	}
	template<typename T>
	template<typename Functor>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::apply(Functor& func, const Vec2<T> & v ) {
		func( this -> x, v.x );
		func( this -> y, v.y );
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void Vec2<T>::inverse() {
		this -> x = T( 1 ) / x;
		this -> y = T( 1 ) / y;
	}

	template<typename T>
	constexpr Size Vec2<T>::getSize() const {
		return Size(2);
	}

	template<typename T>
	const T* Vec2<T>::getData() const {
		return this->values;
	}

	template<typename T>
	Vec2<T>& Vec2<T>::fill(const T& v) {
		this->x = v;
		this->y = v;

		return *this;
	}

	template<typename T>
	Vec2<T>& Vec2<T>::zeros() {
		return fill(T(0));
	}

	template<typename T>
	Vec2<T>& Vec2<T>::ones() {
		return fill(T(1));
	}

	template<typename T>
	Vec2<T>& Vec2<T>::randomF() {
		this->x = Math::randomF();
		this->y = Math::randomF();

		return *this;
	}

	template<typename T>
	Vec2<T>& Vec2<T>::random(const T& min, const T& max) {
		this->x = Math::random(min, max);
		this->y = Math::random(min, max);

		return *this;
	}

	template<typename T>
	template<typename S>
	inline bool Vec2<T>::fromJSON(const JSON::NodeT<S>* node) {
		if ( node->getNbChildren() != Size(2) ) {
			return false;
		}

		if ( !JSON::fromJSON<S>(node, &this->x) ) {
			return false;
		}
		if ( !JSON::fromJSON<S>(node, &this->y) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename S>
	inline JSON::NodeT<S>* Vec2<T>::toJSON() const {
		JSON::NodeArrayT<S>* nodeArray(new JSON::NodeArrayT<S>());

		nodeArray->addChild(JSON::toJSON<S>(this->x));
		nodeArray->addChild(JSON::toJSON<S>(this->y));

		return nodeArray;
	}

	template<typename T>
	template<typename Stream>
	bool Vec2<T>::read( Stream * stream, int verbose ) {
		if ( !IO::read( stream, &this->x, verbose - 1 ) ) {
			return false;
		}
		if ( !IO::read( stream, &this->y, verbose - 1 ) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool Vec2<T>::write(Stream* stream) const {
		if ( !IO::write(stream, &this->x) ) {
			return false;
		}
		if ( !IO::write(stream, &this->y) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T & Vec2<T>::operator[](Size index ) {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec2<T>::operator[](Size index ) const {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const T & x, const T & y ) : x( x ), y( y ) {
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const Vec2<U> & v ) : x( v.x ), y( v.y ) {
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const T & v ) : x( v ), y( v ) {
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( void ) {
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const U( &v )[2] ) : x( T(v[0]) ), y( T(v[1]) ) {
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator-=( const T & v ) {
		return apply( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator-=( const Vec2<U> & v ) {
		return apply( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> Vec2<T>::operator-() const {
		return apply(Math::Operations::MinusUnary());
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator+=( const T & v ) {
		return apply( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator+=( const Vec2<U> & v ) {
		return apply( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator*=( const T & v ) {
		return apply( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator*=( const Vec2<U> & v ) {
		return apply( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator/=( const T & v ) {
		return apply( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator/=( const Vec2<U> & v ) {
		return apply( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator>>=( const T & v ) {
		return apply( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator>>=( const Vec2<U> & v ) {
		return apply( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator<<=( const T & v ) {
		return apply( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator<<=( const Vec2<U> & v ) {
		return apply( Math::Operations::BinaryShiftLeftEqual(), v );
	}




	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const T & v ) {
		return apply( Math::Operations::Assign(), v );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const Vec2<U> & v ) {
		this -> x = T( v.x );
		this -> y = T( v.y );
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const U( &v )[2] ) {
		this -> x = T( v[0] );
		this -> y = T( v[1] );
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator++() {
		return apply(Math::Operations::Increment());
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator--() {
		return apply(Math::Operations::Decrement());
	}


	template<typename T /*= float*/>
	template<typename S /*= String*/>
	MATH_FUNC_QUALIFIER S Vec2<T>::toString() const {
		S newString;
		newString.reserve( 40 );
		newString << S::ElemType( '[' ) << this -> x << S::ElemType( '\t' ) << this -> y << S::ElemType( ']' );
		return newString;
	}

	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.AND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec2<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec2<T> & v2 ) {
		return v2.AND( Math::Logical::Equal(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.OR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec2<T> & v1, const T & v2 ) {
		return v1.OR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec2<T> & v2 ) {
		return v2.OR( Math::Logical::NotEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.AND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec2<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec2<T> & v2 ) {
		return v2.AND( Math::Logical::GreaterOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.AND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec2<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec2<T> & v2 ) {
		return v2.AND( Math::Logical::LessOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.AND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec2<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec2<T> & v2 ) {
		return v2.AND( Math::Logical::Greater(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.AND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec2<T> & v1, const T & v2 ) {
		return v1.AND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec2<T> & v2 ) {
		return v2.AND( Math::Logical::Less(), v1 );
	}
	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x + v2.x, v1.y + v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x + v2, v1.y + v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 + v2.x, v1 + v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x - v2.x, v1.y - v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x - v2, v1.y - v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 - v2.x, v1 - v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x / v2.x, v1.y / v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x / v2, v1.y / v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 / v2.x, v1 / v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x * v2.x, v1.y * v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x * v2, v1.y * v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 * v2.x, v1 * v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x >> v2.x, v1.y >> v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x >> v2, v1.y >> v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 >> v2.x, v1 >> v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x << v2.x, v1.y << v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x << v2, v1.y << v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 << v2.x, v1 << v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x % v2.x, v1.y % v2.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const Vec2<T> & v1, const T & v2 ) {
		return Vec2<T>( v1.x % v2, v1.y % v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const T & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 % v2.x, v1 % v2.y );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T>::operator BasicString<U>() const {
		return toString<U>();
	}

}
