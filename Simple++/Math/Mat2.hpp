namespace Math {

	template<typename T>
	const Mat2<T> Mat2<T>::identity = Mat2<T>( 1 );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T>::Mat2( const T & v ) {
		const T Zero( 0 );

		this -> column[0].x = v;
		this -> column[0].y = Zero;

		this -> column[1].x = Zero;
		this -> column[1].y = v;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T>::Mat2( const T & v11, const T & v21,
									   const T & v12, const T & v22 ) {
		this -> column[0].x = v11;
		this -> column[0].y = v12;

		this -> column[1].x = v21;
		this -> column[1].y = v22;
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T>::Mat2( const Mat2<U> & m ) {
		*this = m;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T>::Mat2( const U( &m )[4] ) {
		*this = m;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T>::Mat2( void ) {

	}



	template<typename T >
	MATH_FUNC_QUALIFIER const Vec2<T> & Mat2<T>::operator[]( unsigned int index ) const {
		return this -> column[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> & Mat2<T>::operator[]( unsigned int index ) {
		return this -> column[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T>::Mat2( const ColType & col0, const ColType & col1 ) {
		this -> column[0] = col0;
		this -> column[1] = col1;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T Mat2<T>::getDeterminant() const {
		return this -> column[0][0] * this -> column[1][1] - this -> column[1][0] * this -> column[0][1];
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> Mat2<T>::inverse() const {
		const T & S00 = this -> column[0][0];
		const T & S01 = this -> column[0][1];

		const T & S10 = this -> column[1][0];
		const T & S11 = this -> column[1][1];

		T determinant = getDeterminant();

		return inverse(
			+S11 / determinant,
			-S10 / determinant,
			-S01 / determinant,
			+S00 / determinant );
	}

	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator*=( const Mat2<U> & m ) {
		return ( *this = *this * m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator*=( const Vec2<U> & v ) {
		this -> column[0] *= v.x;
		this -> column[1] *= v.y;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator*=( const U & v ) {
		this -> column[0] *= v;
		this -> column[1] *= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator/=( const Mat2<U> & m ) {
		return ( *this = *this / m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator/=( const Vec2<U> & v ) {
		this -> column[0] /= v.x;
		this -> column[1] /= v.y;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator/=( const U & v ) {
		this -> column[0] /= v;
		this -> column[1] /= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator+=( const Mat2<U> & m ) {
		this -> column[0] += m[0];
		this -> column[1] += m[1];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator+=( const Vec2<U> & v ) {
		this -> column[0] += v.x;
		this -> column[1] += v.y;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator+=( const U & v ) {
		this -> column[0] += v;
		this -> column[1] += v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator-=( const Mat2<U> & m ) {
		this -> column[0] -= m[0];
		this -> column[1] -= m[1];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator-=( const Vec2<U> & v ) {
		this -> column[0] -= v.x;
		this -> column[1] -= v.y;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator-=( const U & v ) {
		this -> column[0] -= v;
		this -> column[1] -= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator>>=( const Mat2<U> & m ) {
		this -> column[0] >>= m[0];
		this -> column[1] >>= m[1];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator>>=( const U & v ) {
		this -> column[0] >>= v;
		this -> column[1] >>= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator<<=( const Mat2<U> & m ) {
		this -> column[0] <<= m[0];
		this -> column[1] <<= m[1];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator<<=( const U & v ) {
		this -> column[0] <<= v;
		this -> column[1] <<= v;
		return *this;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator++() {
		this -> column[0]++;
		this -> column[1]++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator--() {
		this -> column[0]--;
		this -> column[1]--;
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> Mat2<T>::operator-() const {
		return Mat2( -this -> column[0], -this -> column[1] );
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator=( const Mat2<U> & m ) {
		this -> column[0] = m[0];
		this -> column[1] = m[1];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator=( const U( &m )[4] ) {
		this -> column[0].x = m[0];
		this -> column[0].y = m[2];

		this -> column[1].x = m[1];
		this -> column[1].y = m[3];
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> & Mat2<T>::operator=( const T & v ) {
		this -> column[0] = v;
		this -> column[1] = v;
	}


	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::operator==( const Mat2<U> & m ) const {
		return _logicalOperatorAND( Math::Logical::Equal(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::operator!=( const Mat2<U> & m ) const {
		return _logicalOperatorOR( Math::Logical::NotEqual(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::operator<( const Mat2<U> & m ) const {
		return _logicalOperatorAND( Math::Logical::Less(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::operator<=( const Mat2<U> & m ) const {
		return _logicalOperatorAND( Math::Logical::LessOrEqual(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::operator>( const Mat2<U> & m ) const {
		return _logicalOperatorAND( Math::Logical::Greater(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::operator>=( const Mat2<U> & m ) const {
		return _logicalOperatorAND( Math::Logical::GreaterOrEqual(), m );
	}




	template<typename T>
	template<typename Compare, typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::_logicalOperatorOR( Compare & func, const Mat2<U> & m ) const {
		return func( this -> column[0], m[0] ) || func( this -> column[1], m[1] );
	}

	template<typename T>
	template<typename Compare, typename U>
	MATH_FUNC_QUALIFIER bool Mat2<T>::_logicalOperatorAND( Compare & func, const Mat2<U> & m )const {
		return func( this -> column[0], m[0] ) && func( this -> column[1], m[1] );
	}





	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator*( const Mat2<T> & m1, const Mat2<T> & m2 ) {
		Mat2<T> newMat;

		newMat[0].x = m1[0].x * m2[0].x + m1[1].x * m2[0].y;
		newMat[0].y = m1[0].y * m2[0].x + m1[1].y * m2[0].y;

		newMat[1].x = m1[0].x * m2[1].x + m1[1].x * m2[1].y;
		newMat[1].y = m1[0].y * m2[1].x + m1[1].y * m2[1].y;

		return newMat;
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator*( const Mat2<T> & m, const U & v ) {
		return Mat2<T>( m[0] * v, m[1] * v );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator*( const U & v, const Mat2<T> & m ) {
		return Mat2<T>( v * m[0], v * m[1] );
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER typename Mat2<T>::ColType operator*( const Mat2<T> & m, const Vec2<U> & v ) {
		return typename Mat2<T>::ColType( m[0][0] * v.x + m[1][0] * v.y,
										  m[0][1] * v.x + m[1][1] * v.y );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER typename Mat2<T>::ColType operator*( const Vec2<U> & v, const Mat2<T> & m ) {
		return typename Mat2<T>::ColType( m[0][0] * v.x + m[0][1] * v.y,
										  m[1][0] * v.x + m[1][1] * v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator/( const Mat2<T> & m1, const Mat2<T> & m2 ) {
		return m1 * m2.inverse();
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator/( const Mat2<T> & m, const U & v ) {
		return Mat2<T>( m[0] / v, m[1] / v );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator/( const U & v, const Mat2<T> & m ) {
		return Mat2<T>( v / m[0], v / m[1] );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator+( const Mat2<T> & m1, const Mat2<T> & m2 ) {
		return Mat2<T>( m1[0] + m2[0], m1[1] + m2[1] );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator+( const Mat2<T> & m, const U & v ) {
		return Mat2<T>( m[0] + v, m[1] + v );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator+( const U & v, const Mat2<T> & m ) {
		return Mat2<T>( v + m[0], v + m[1] );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator-( const Mat2<T> & m1, const Mat2<T> & m2 ) {
		return Mat2<T>( m1[0] - m2[0], m1[1] - m2[1] );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator-( const Mat2<T> & m, const U & v ) {
		return Mat2<T>( m[0] - v, m[1] - v );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator-( const U & v, const Mat2<T> & m ) {
		return Mat2<T>( v - m[0], v - m[1] );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator >> ( const Mat2<T> & m1, const Mat2<T> & m2 ) {
		return Mat2<T>( m1[0] >> m2[0], m1[1] >> m2[1] );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator >> ( const Mat2<T> & m, const U & v ) {
		return Mat2<T>( m[0] >> v, m[1] >> v );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator >> ( const U & v, const Mat2<T> & m ) {
		return Mat2<T>( v >> m[0], v >> m[1] );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat2<T> operator<<( const Mat2<T> & m1, const Mat2<T> & m2 ) {
		return Mat2<T>( m1[0] << m2[0], m1[1] << m2[1] );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator<<( const Mat2<T> & m, const U & v ) {
		return Mat2<T>( m[0] << v, m[1] << v );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Mat2<T> operator<<( const U & v, const Mat2<T> & m ) {
		return Mat2<T>( v << m[0], v << m[1] );
	}


	template<typename T /*= float*/>
	template<typename C /*=char*/>
	MATH_FUNC_QUALIFIER Mat2<T>::operator BasicString<C>() const {
		return toString();
	}


	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Mat2<T> & v ) {
		stream << '[' << v[0].x << '\t' << v[1].x << ']' << '\n';
		stream << '[' << v[0].y << '\t' << v[1].y << ']' << '\n';
		return stream;
	}


	template<typename T /*= float*/>
	template<typename C /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<C> Mat2<T>::toString() const {
		BasicString<C> newString;
		newString.reserve( 180 );
		newString << C( '[' ) << this -> column[0].x << C( '\t' ) << this -> column[1].x << C( ']' ) << C( '\n' );
		newString << C( '[' ) << this -> column[0].y << C( '\t' ) << this -> column[1].y << C( ']' ) << C( '\n' );
		return newString;
	}

	template<typename T, typename C>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<( BasicString<C> & string, const Mat2<T> & v ) {
		string << C( '[' ) << v[0].x << C( '\t' ) << v[1].x << C( ']' ) << C( '\n' );
		string << C( '[' ) << v[0].y << C( '\t' ) << v[1].y << C( ']' ) << C( '\n' );
		return string;
	}


}


