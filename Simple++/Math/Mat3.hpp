namespace Math {

	template<typename T>
	const Mat3<T> Mat3<T>::identity = Mat3<T>( 1 );

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T>::Mat3( const T & v ) {
		const T Zero( 0 );


		this -> column[0].x = v;
		this -> column[0].y = Zero;
		this -> column[0].z = Zero;

		this -> column[1].x = Zero;
		this -> column[1].y = v;
		this -> column[1].z = Zero;

		this -> column[2].x = Zero;
		this -> column[2].y = Zero;
		this -> column[2].z = v;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T>::Mat3( const T & v11, const T & v21, const T & v31,
									   const T & v12, const T & v22, const T & v32,
									   const T & v13, const T & v23, const T & v33 ) {
		this -> column[0].x = v11;
		this -> column[0].y = v12;
		this -> column[0].z = v13;

		this -> column[1].x = v21;
		this -> column[1].y = v22;
		this -> column[1].z = v23;

		this -> column[2].x = v31;
		this -> column[2].y = v32;
		this -> column[2].z = v33;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T>::Mat3( const Mat3<U> & m ) {
		*this = m;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T>::Mat3( const U( &m )[9] ) {
		*this = m;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T>::Mat3( void ) {

	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T>::Mat3( const ColType & col0, const ColType & col1, const ColType & col2 ) {
		this -> column[0] = col0;
		this -> column[1] = col1;
		this -> column[2] = col2;
	}


	template<typename T >
	MATH_FUNC_QUALIFIER const Vec3<T> & Mat3<T>::operator[]( unsigned int index ) const {
		return this -> column[index];
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Mat3<T>::operator[]( unsigned int index ) {
		return this -> column[index];
	}




	template<typename T>
	MATH_FUNC_QUALIFIER T Mat3<T>::getDeterminant() const {
		const T & S00 = this -> column[0][0];
		const T & S01 = this -> column[0][1];
		const T & S02 = this -> column[0][2];

		const T & S10 = this -> column[1][0];
		const T & S11 = this -> column[1][1];
		const T & S12 = this -> column[1][2];

		const T & S20 = this -> column[2][0];
		const T & S21 = this -> column[2][1];
		const T & S22 = this -> column[2][2];

		return S00 * ( S11 * S22 - S21 * S12 )
			+ S01 * ( S12 * S20 - S22 * S10 )
			+ S02 * ( S10 * S21 - S20 * S11 );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> Mat3<T>::inverse() const {
		const T & S00 = this -> column[0][0];
		const T & S01 = this -> column[0][1];
		const T & S02 = this -> column[0][2];

		const T & S10 = this -> column[1][0];
		const T & S11 = this -> column[1][1];
		const T & S12 = this -> column[1][2];

		const T & S20 = this -> column[2][0];
		const T & S21 = this -> column[2][1];
		const T & S22 = this -> column[2][2];

		Mat3<T> inverse(
			S11 * S22 - S21 * S12, S12 * S20 - S22 * S10, S10 * S21 - S20 * S11,
			S02 * S21 - S01 * S22, S00 * S22 - S02 * S20, S01 * S20 - S00 * S21,
			S12 * S01 - S11 * S02, S10 * S02 - S12 * S00, S11 * S00 - S10 * S01 );

		T determinant = S00 * inverse[0][0]
			+ S01 * inverse[1][0]
			+ S02 * inverse[3][0];

		inverse /= determinant;
		return inverse;
	}

	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator*=( const Mat3<U> & m ) {
		return ( *this = *this * m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator*=( const Vec3<U> & v ) {
		this -> column[0] *= v.x;
		this -> column[1] *= v.y;
		this -> column[2] *= v.z;
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator*=( const T & v ) {
		this -> column[0] *= v;
		this -> column[1] *= v;
		this -> column[2] *= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator/=( const Mat3<U> & m ) {
		return ( *this = *this / m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator/=( const Vec3<U> & v ) {
		this -> column[0] /= v.x;
		this -> column[1] /= v.y;
		this -> column[2] /= v.z;
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator/=( const T & v ) {
		this -> column[0] /= v;
		this -> column[1] /= v;
		this -> column[2] /= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator+=( const Mat3<U> & m ) {
		this -> column[0] += m[0];
		this -> column[1] += m[1];
		this -> column[2] += m[2];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator+=( const Vec3<U> & v ) {
		this -> column[0] += v.x;
		this -> column[1] += v.y;
		this -> column[2] += v.z;
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator+=( const T & v ) {
		this -> column[0] += v;
		this -> column[1] += v;
		this -> column[2] += v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator-=( const Mat3<U> & m ) {
		this -> column[0] -= m[0];
		this -> column[1] -= m[1];
		this -> column[2] -= m[2];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator-=( const Vec3<U> & v ) {
		this -> column[0] -= v.x;
		this -> column[1] -= v.y;
		this -> column[2] -= v.z;
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator-=( const T & v ) {
		this -> column[0] -= v;
		this -> column[1] -= v;
		this -> column[2] -= v;
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator>>=( const Mat3<U> & m ) {
		this -> column[0] >>= m[0];
		this -> column[1] >>= m[1];
		this -> column[2] >>= m[2];
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator>>=( const T & v ) {
		this -> column[0] >>= v;
		this -> column[1] >>= v;
		this -> column[2] >>= v;
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator<<=( const Mat3<U> & m ) {
		this -> column[0] <<= m[0];
		this -> column[1] <<= m[1];
		this -> column[2] <<= m[2];
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator<<=( const T & v ) {
		this -> column[0] <<= v;
		this -> column[1] <<= v;
		this -> column[2] <<= v;
		return *this;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator++() {
		this -> column[0]++;
		this -> column[1]++;
		this -> column[2]++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator--() {
		this -> column[0]--;
		this -> column[1]--;
		this -> column[2]--;
		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T>  Mat3<T>::operator-() const {
		return Mat3<T>(-this -> column[0], -this-> column[1], -this -> column[2]);
	}

	/************************************************************************/
	/* Assign                                                               */
	/************************************************************************/
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator=( const Mat3<U> & m ) {
		this -> column[0] = m[0];
		this -> column[1] = m[1];
		this -> column[2] = m[2];
		return *this;
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator=( const U( &m )[9] ) {
		this -> column[0].x = m[0];
		this -> column[0].y = m[3];
		this -> column[0].z = m[6];

		this -> column[1].x = m[1];
		this -> column[1].y = m[4];
		this -> column[1].z = m[7];

		this -> column[2].x = m[2];
		this -> column[2].y = m[5];
		this -> column[2].z = m[8];

		return *this;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> & Mat3<T>::operator=( const T & v ) {
		this -> column[0] = v;
		this -> column[1] = v;
		this -> column[2] = v;
	}

	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::operator==( const Mat3<U> & m ) const {
		return AND( Math::Logical::Equal(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::operator!=( const Mat3<U> & m ) const {
		return OR( Math::Logical::NotEqual(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::operator<( const Mat3<U> & m ) const {
		return AND( Math::Logical::Less(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::operator<=( const Mat3<U> & m ) const {
		return AND( Math::Logical::LessOrEqual(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::operator>( const Mat3<U> & m ) const {
		return AND( Math::Logical::Greater(), m );
	}
	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::operator>=( const Mat3<U> & m ) const {
		return AND( Math::Logical::GreaterOrEqual(), m );
	}




	template<typename T>
	template<typename Compare, typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::OR( Compare & func, const Mat3<U> & m ) const {
		return func( this -> column[0], m[0] ) || func( this -> column[1], m[1] ) || func( this -> column[2], m[2] );
	}

	template<typename T>
	template<typename Compare, typename U>
	MATH_FUNC_QUALIFIER bool Mat3<T>::AND( Compare & func, const Mat3<U> & m )const {
		return func( this -> column[0], m[0] ) && func( this -> column[1], m[1] ) && func( this -> column[2], m[2] );
	}





	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		Mat3<T> newMat;

		newMat[0].x = m1[0].x * m2[0].x + m1[1].x * m2[0].y + m1[2].x * m2[0].z;
		newMat[0].y = m1[0].y * m2[0].x + m1[1].y * m2[0].y + m1[2].y * m2[0].z;
		newMat[0].z = m1[0].z * m2[0].x + m1[1].z * m2[0].y + m1[2].z * m2[0].z;

		newMat[1].x = m1[0].x * m2[1].x + m1[1].x * m2[1].y + m1[2].x * m2[1].z;
		newMat[1].y = m1[0].y * m2[1].x + m1[1].y * m2[1].y + m1[2].y * m2[1].z;
		newMat[1].z = m1[0].z * m2[1].x + m1[1].z * m2[1].y + m1[2].z * m2[1].z;

		newMat[2].x = m1[0].x * m2[2].x + m1[1].x * m2[2].y + m1[2].x * m2[2].z;
		newMat[2].y = m1[0].y * m2[2].x + m1[1].y * m2[2].y + m1[2].y * m2[2].z;
		newMat[2].z = m1[0].z * m2[2].x + m1[1].z * m2[2].y + m1[2].z * m2[2].z;

		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] * v, m[1] * v, m[2] * v );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator*( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v * m[0], v * m[1], v * m[2] );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER typename Mat3<T>::ColType operator*( const Mat3<T> & m, const Vec3<U> & v ) {
		return typename Mat3<T>::ColType( m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
										  m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
										  m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z );
	}
	template<typename T, typename U>
	MATH_FUNC_QUALIFIER typename Mat3<T>::ColType operator*( const Vec3<U> & v, const Mat3<T> & m ) {
		return typename Mat3<T>::ColType( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
										  m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
										  m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		return m1 * m2.inverse();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] / v, m[1] / v, m[2] / v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator/( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v / m[0], v / m[1], v / m[2] );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		return Mat3<T>( m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] + v, m[1] + v, m[2] + v );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator+( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v + m[0], v + m[1], v + m[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		return Mat3<T>( m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] - v, m[1] - v, m[2] - v );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator-( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v - m[0], v - m[1], v - m[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		return Mat3<T>( m1[0] >> m2[0], m1[1] >> m2[1], m1[2] >> m2[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] >> v, m[1] >> v, m[2] >> v );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator >> ( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v >> m[0], v >> m[1], v >> m[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		return Mat3<T>( m1[0] << m2[0], m1[1] << m2[1], m1[2] << m2[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] << v, m[1] << v, m[2] << v );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator<<( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v << m[0], v << m[1], v << m[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator%( const Mat3<T> & m1, const Mat3<T> & m2 ) {
		return Mat3<T>( m1[0] % m2[0], m1[1] % m2[1], m1[2] % m2[2] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator%( const Mat3<T> & m, const T & v ) {
		return Mat3<T>( m[0] % v, m[1] % v, m[2] % v );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> operator%( const T & v, const Mat3<T> & m ) {
		return Mat3<T>( v % m[0], v % m[1], v % m[2] );
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat3<T>::operator BasicString<U>() const {
		return toString();
	}




	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Mat3<T> & v ) {
		stream << '[' << v[0].x << '\t' << v[1].x << '\t' << v[2].x << ']' << '\n';
		stream << '[' << v[0].y << '\t' << v[1].y << '\t' << v[2].y << ']' << '\n';
		stream << '[' << v[0].z << '\t' << v[1].z << '\t' << v[2].z << ']' << '\n';
		return stream;
	}


	template<typename T /*= float*/>
	template<typename C /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<C> Mat3<T>::toString() const {
		BasicString<C> newString;
		newString.reserve( 180 );
		newString << C( '[' ) << this -> column[0].x << C( '\t' ) << this -> column[1].x << C( '\t' ) << this -> column[2].x << C( ']' ) << C( '\n' );
		newString << C( '[' ) << this -> column[0].y << C( '\t' ) << this -> column[1].y << C( '\t' ) << this -> column[2].y << C( ']' ) << C( '\n' );
		newString << C( '[' ) << this -> column[0].z << C( '\t' ) << this -> column[1].z << C( '\t' ) << this -> column[2].z << C( ']' ) << C( '\n' );
		return newString;
	}

	template<typename T, typename C>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<( BasicString<C> & string, const Mat3<T> & v ) {
		string << C( '[' ) << v[0].x << C( '\t' ) << v[1].x << C( '\t' ) << v[2].x << C( ']' ) << C( '\n' );
		string << C( '[' ) << v[0].y << C( '\t' ) << v[1].y << C( '\t' ) << v[2].y << C( ']' ) << C( '\n' );
		string << C( '[' ) << v[0].z << C( '\t' ) << v[1].z << C( '\t' ) << v[2].z << C( ']' ) << C( '\n' );
		return string;
	}


}


