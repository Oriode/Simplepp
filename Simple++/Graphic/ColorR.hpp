namespace Graphic {


	template<typename T> const ColorR<T> ColorR<T>::black = ColorR<T>( T( 0 ));
	template<typename T> const ColorR<T> ColorR<T>::white = ColorR<T>( Color<T>::getMax());
	template<typename T> const ColorR<T> ColorR<T>::red = ColorR<T>( Color<T>::getMax());
	template<typename T> const ColorR<T> ColorR<T>::green = ColorR<T>( T( 0 ) );
	template<typename T> const ColorR<T> ColorR<T>::blue = ColorR<T>( T( 0 ) );

	template<typename T> const Format ColorR<T>::format = Format::R;


	template<typename T>
	ColorR<T>::ColorR() {

	}

	template<typename T>
	ColorR<T>::ColorR( const unsigned char & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const unsigned short & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const unsigned int & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const unsigned long int & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const unsigned long long int & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const char & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const short & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const int & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const long int & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const long long int & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const float & r ) : r( r ) {
	}
	template<typename T>
	ColorR<T>::ColorR( const double & r ) : r(r) {
	}



	template<typename T>
	template<typename U>
	ColorR<T>::ColorR( const ColorR<U> & color ) {
		castComponent( this -> r, color.r );
	}



	template<typename T>
	template<typename S /*= String*/>
	S ColorR<T>::toString() const {
		S newString;
		newString.reserve( 20 );
		newString << S::ElemType( 'R' ) << S::ElemType( '(' ) << this -> r << S::ElemType( ')' );
		return newString;
	}

	template<typename T>
	template<typename S /*= String*/>
	S ColorR<T>::toHex() const {
		S newString;
		newString.reserve( 4 );
		newString << S::ElemType( '#' ) << S::toString<16>( this -> r );
		return newString;
	}

	template<typename T>
	ColorR<T>::operator T() const {
		return this -> r;
	}

	template<typename T>
	template<typename C /*= char*/>
	ColorR<T>::operator BasicString<C>() const {
		return toString<BasicString<C>>();
	}

	template<typename T>
	template<typename U>
	ColorR<T> & ColorR<T>::operator=( const ColorR<U> & color ) {
		this -> r = color.r;
		return *this;
	}



	template<typename T>
	ColorR<T> & ColorR<T>::operator+=( const T & color ) {
		this -> r += color;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator-=( const T & color ) {
		this -> r -= color;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator*=( const T & color ) {
		this -> r *= color;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator/=( const T & color ) {
		this -> r /= color;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator%=( const T & color ) {
		this -> r %= color;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator<<=( const T & color ) {
		this -> r <<= color;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator>>=( const T & color ) {
		this -> r >>= color;
		return *this;
	}




	template<typename T>
	ColorR<T> & ColorR<T>::operator+=( const ColorR<T> & color ) {
		this -> r += color.r;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator-=( const ColorR<T> & color ) {
		this -> r -= color.r;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator*=( const ColorR<T> & color ) {
		this -> r *= color.r;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator/=( const ColorR<T> & color ) {
		this -> r /= color.r;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator%=( const ColorR<T> & color ) {
		this -> r %= color.r;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator<<=( const ColorR<T> & color ) {
		this -> r <<= color.r;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator>>=( const ColorR<T> & color ) {
		this -> r >>= color.r;
		return *this;
	}

	template<typename T>
	ColorR<T> & ColorR<T>::operator++() {
		this -> r++;
		return *this;
	}
	template<typename T>
	ColorR<T> & ColorR<T>::operator--() {
		this -> r--;
		return *this;
	}
	template<typename T>
	ColorR<T> ColorR<T>::operator-() const {
		return -this -> r;
	}



	template<typename T>
	template<typename U>
	ColorR<U> ColorR<T>::toType() const {
		ColorR<U> colorResult;
		ColorR<T>::castComponent( colorResult.r, this -> r );
		return colorResult;
	}


	template<typename T>
	const T & ColorR<T>::getLightness() const {
		return this -> r;
	}

	template<typename T>
	const T & ColorR<T>::getRed() const {
		return this -> r;
	}





	template<typename T>
	bool operator==( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ( c1.r == c2.r );
	}
	template<typename T>
	bool operator==( const ColorR<T> & c1, const T & c2 ) {
		return ( c1.r == c2 );
	}
	template<typename T>
	bool operator==( const T & c1, const ColorR<T> & c2 ) {
		return ( c1 == c2.r );
	}

	template<typename T>
	bool operator>=( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ( c1.r >= c2.r );
	}
	template<typename T>
	bool operator>=( const ColorR<T> & c1, const T & c2 ) {
		return ( c1.r >= c2 );
	}
	template<typename T>
	bool operator>=( const T & c1, const ColorR<T> & c2 ) {
		return ( c1 >= c2.r );
	}

	template<typename T>
	bool operator<=( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ( c1.r <= c2.r );
	}
	template<typename T>
	bool operator<=( const ColorR<T> & c1, const T & c2 ) {
		return ( c1.r <= c2 );
	}
	template<typename T>
	bool operator<=( const T & c1, const ColorR<T> & c2 ) {
		return ( c1 <= c2.r );
	}

	template<typename T>
	bool operator>( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ( c1.r > c2.r );
	}
	template<typename T>
	bool operator>( const ColorR<T> & c1, const T & c2 ) {
		return ( c1.r > c2 );
	}
	template<typename T>
	bool operator>( const T & c1, const ColorR<T> & c2 ) {
		return ( c1 > c2.r );
	}


	template<typename T>
	bool operator<( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ( c1.r < c2.r );
	}
	template<typename T>
	bool operator<( const ColorR<T> & c1, const T & c2 ) {
		return ( c1.r < c2 );
	}
	template<typename T>
	bool operator<( const T & c1, const ColorR<T> & c2 ) {
		return ( c1 < c2.r );
	}

	template<typename T>
	bool operator!=( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ( c1.r != c2.r );
	}
	template<typename T>
	bool operator!=( const ColorR<T> & c1, const T & c2 ) {
		return ( c1.r != c2 );
	}
	template<typename T>
	bool operator!=( const T & c1, const ColorR<T> & c2 ) {
		return ( c1 != c2.r );
	}


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	ColorR<T> operator+( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r + c2.r );
	}
	template<typename T>
	ColorR<T> operator+( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r + c2 );
	}
	template<typename T>
	ColorR<T> operator+( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 + c2.r );
	}

	template<typename T>
	ColorR<T> operator-( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r - c2.r );
	}
	template<typename T>
	ColorR<T> operator-( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r - c2 );
	}
	template<typename T>
	ColorR<T> operator-( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 - c2.r );
	}

	template<typename T>
	ColorR<T> operator/( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r / c2.r );
	}
	template<typename T>
	ColorR<T> operator/( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r / c2 );
	}
	template<typename T>
	ColorR<T> operator/( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 / c2.r );
	}

	template<typename T>
	ColorR<T> operator*( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r * c2.r );
	}
	template<typename T>
	ColorR<T> operator*( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r * c2 );
	}
	template<typename T>
	ColorR<T> operator*( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 * c2.r );
	}

	template<typename T>
	ColorR<T> operator%( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r % c2.r );
	}
	template<typename T>
	ColorR<T> operator%( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r % c2 );
	}
	template<typename T>
	ColorR<T> operator%( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 % c2.r );
	}

	template<typename T>
	ColorR<T> operator >> ( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r >> c2.r );
	}
	template<typename T>
	ColorR<T> operator >> ( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r >> c2 );
	}
	template<typename T>
	ColorR<T> operator >> ( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 >> c2.r );
	}

	template<typename T>
	ColorR<T> operator<<( const ColorR<T> & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1.r << c2.r );
	}
	template<typename T>
	ColorR<T> operator<<( const ColorR<T> & c1, const T & c2 ) {
		return ColorR<T>( c1.r << c2 );
	}
	template<typename T>
	ColorR<T> operator<<( const T & c1, const ColorR<T> & c2 ) {
		return ColorR<T>( c1 << c2.r );
	}


}
