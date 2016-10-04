namespace Math {

	template<typename T>
	const Vec3<T> Vec3<T>::null = Vec3<T>( 0 );


	

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::_logicalOperatorOR( Compare & func, const Vec3<T> & v ) const {
		return func( this -> x, v.x ) || func( this -> y, v.y ) || func( this -> z, v.z );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::_logicalOperatorOR( Compare & func, const T & v ) const {
		return func( this -> x, v ) || func( this -> y, v ) || func( this -> z, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::_logicalOperatorAND( Compare & func, const Vec3<T> & v ) const {
		return func( this -> x, v.x ) && func( this  -> y, v.y ) && func( this  -> z, v.z );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::_logicalOperatorAND( Compare & func, const T & v ) const {
		return func( this -> x, v ) && func( this  -> y, v ) && func( this  -> z, v );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::_MathOperator( Compare & func, const T & v ) {
		func( this -> x, v );
		func( this -> y, v );
		func( this -> z, v );
		return *this;
	}
	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::_MathOperator( Compare & func, const Vec3<T> & v ) {
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
		return _MathOperator( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator-=( const Vec3<U> & v ) {
		return _MathOperator( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator+=( const T & v ) {
		return _MathOperator( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator+=( const Vec3<U> & v ) {
		return _MathOperator( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator/=( const T & v ) {
		return _MathOperator( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator/=( const Vec3<U> & v ) {
		return _MathOperator( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator*=( const T & v ) {
		return _MathOperator( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator*=( const Vec3<U> & v ) {
		return _MathOperator( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator>>=( const T & v ) {
		return _MathOperator( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator>>=( const Vec3<U> & v ) {
		return _MathOperator( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator<<=( const T & v ) {
		return _MathOperator( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator<<=( const Vec3<U> & v ) {
		return _MathOperator( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator++() {
		this -> x++;
		this -> y++;
		this -> z++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator--() {
		this -> x--;
		this -> y--;
		this -> z--;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> Vec3<T>::operator-() const {
		return Vec3<T>( -this -> x, -this -> y, -this -> z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T & Vec3<T>::operator[]( unsigned int index ) {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec3<T>::operator[]( unsigned int index ) const {
		return this -> values[index];
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec2<U> & v ) : z(0) {
		*this = v;
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
		return _MathOperator( Math::Operations::Assign(), v );
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
		return v1._logicalOperatorAND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec3<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Equal(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec3<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::Equal(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1._logicalOperatorOR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec3<T> & v1, const T & v2 ) {
		return v1._logicalOperatorOR( Math::Logical::NotEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec3<T> & v2 ) {
		return v2._logicalOperatorOR( Math::Logical::NotEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec3<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::GreaterOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec3<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::GreaterOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec3<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::LessOrEqual(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec3<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::LessOrEqual(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec3<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Greater(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec3<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::Greater(), v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec3<T> & v1, const T & v2 ) {
		return v1._logicalOperatorAND( Math::Logical::Less(), v2 );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec3<T> & v2 ) {
		return v2._logicalOperatorAND( Math::Logical::Less(), v1 );
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

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Vec3<T> & v ) {
		stream << '[' << v.x << '\t' << v.y << '\t' << v.z << ']';
		return stream;
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<( BasicString<U> & string, const Vec3<T> & v ) {
		string << U( '[' ) << v.x << U( '\t' ) << v.y << U( '\t' ) << v.z << U( ']' );
		return string;
	}

	template<typename T /*= float*/>
	template<typename U /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<U> Vec3<T>::toString() const {
		BasicString<U> newString;
		newString.reserve( 60 );
		newString << U( '[' ) << this -> x << U( '\t' ) << this -> y << U( '\t' ) << this -> z << U( ']' );
		return newString;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::operator BasicString<U>() const {
		return toString<U>();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::operator Vec2<T>() const {
		return xy();
	}


}
