namespace Math {

	template<typename T>
	const Vec2<T> Vec2<T>::null = Vec2<T>( 0 );


	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec2<T>::_logicalOperatorOR( Compare func, const Vec2<T> & v ) const {
		return func( this -> x, v.x ) || func( this -> y, v.y );

	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec2<T>::_logicalOperatorAND( Compare func, const Vec2<T> & v ) const {
		return func( this -> x, v.x ) && func( this  -> y, v.y );
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::_MathOperator( Compare func, const T & v ) {
		func( this -> x, v );
		func( this -> y, v );
		return *this;
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::_MathOperator( Compare func, const Vec2<T> & v ) {
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
	MATH_FUNC_QUALIFIER T & Vec2<T>::operator[]( unsigned int index ) {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec2<T>::operator[]( unsigned int index ) const {
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec2<T>::operator>=( const Vec2<T> & v ) const {
		return _logicalOperatorAND( Math::Logical::GreaterOrEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec2<T>::operator>( const Vec2<T> & v ) const {
		return _logicalOperatorAND( Math::Logical::Greater(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec2<T>::operator<=( const Vec2<T> & v ) const {
		return _logicalOperatorAND( Math::Logical::LessOrEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec2<T>::operator<( const Vec2<T> & v ) const {
		return _logicalOperatorAND( Math::Logical::Less(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec2<T>::operator!=( const Vec2<T> & v ) const {
		return _logicalOperatorOR( Math::Logical::NotEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec2<T>::operator==( const Vec2<T> & v ) const {
		return _logicalOperatorAND( Math::Logical::Equal(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const T & x, const T & y ) {
		this -> x = x;
		this -> y = y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const Vec2<T> & v ) {
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const Vec2<U> & v ) {
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const T & v ) {
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( const U & v ) {
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T>::Vec2( void ) {

	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator-=( const T & v ) {
		return _MathOperator( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator-=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::SubEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> Vec2<T>::operator-() const {
		return Vec2<T>( -this -> x, -this -> y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator+=( const T & v ) {
		return _MathOperator( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator+=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::AddEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator*=( const T & v ) {
		return _MathOperator( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator*=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::MulEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator/=( const T & v ) {
		return _MathOperator( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator/=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::DivEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator>>=( const T & v ) {
		return _MathOperator( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator>>=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::BinaryShiftRightEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator<<=( const T & v ) {
		return _MathOperator( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator<<=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::BinaryShiftLeftEqual(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const T & v ) {
		return _MathOperator( Math::Operations::Assign(), v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const Vec2<T> & v ) {
		return _MathOperator( Math::Operations::Assign(), v );
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const U & v ) {
		const T newValue( v );
		return *this = newValue;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator=( const Vec2<U> & v ) {
		this -> x = T( v.x );
		this -> y = T( v.y );
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator++() {
		this -> x++;
		this -> y++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Vec2<T>::operator--() {
		this -> x--;
		this -> y--;
		return *this;
	}


	template<typename T /*= float*/>
	template<typename U /*= char*/>
	MATH_FUNC_QUALIFIER BasicString<U> Vec2<T>::toString() const {
		BasicString<U> newString;
		newString.reserve( 40 );
		newString << U( '[' ) << this -> x << U( '\t' ) << this -> y << U( ']' );
		return newString;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x + v2.x, v1.y + v2.y );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const U & v2 ) {
		return Vec2<T>( v1.x + v2, v1.y + v2 );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const U & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 + v2.x, v1 + v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x - v2.x, v1.y - v2.y );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const U & v2 ) {
		return Vec2<T>( v1.x - v2, v1.y - v2 );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const U & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 - v2.x, v1 - v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x / v2.x, v1.y / v2.y );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const U & v2 ) {
		return Vec2<T>( v1.x / v2, v1.y / v2 );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const U & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 / v2.x, v1 / v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x * v2.x, v1.y * v2.y );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const U & v2 ) {
		return Vec2<T>( v1.x * v2, v1.y * v2 );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const U & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 * v2.x, v1 * v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x >> v2.x, v1.y >> v2.y );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const U & v2 ) {
		return Vec2<T>( v1.x >> v2, v1.y >> v2 );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const U & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 >> v2.x, v1 >> v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.x << v2.x, v1.y << v2.y );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const U & v2 ) {
		return Vec2<T>( v1.x << v2, v1.y << v2 );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const U & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1 << v2.x, v1 << v2.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Vec2<T> & v ) {
		stream << '[' << v.x << '\t' << v.y << ']';
		return stream;
	}


	template<typename T, typename U>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<( BasicString<U> & string, const Vec2<T> & v ) {
		string << U( '[' ) << v.x << U( '\t' ) << v.y << U( ']' );
		return string;
	}

}
