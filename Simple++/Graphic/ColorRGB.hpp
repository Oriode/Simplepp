namespace Graphic {

	template<typename T> const ColorRGB<T> ColorRGB<T>::black = ColorRGB<T>( T( 0 ), T( 0 ), T( 0 ) );
	template<typename T> const ColorRGB<T> ColorRGB<T>::white = ColorRGB<T>( Color<T>::getMax(), Color<T>::getMax(), Color<T>::getMax() );
	template<typename T> const ColorRGB<T> ColorRGB<T>::red = ColorRGB<T>( Color<T>::getMax(), T( 0 ), T( 0 ) );
	template<typename T> const ColorRGB<T> ColorRGB<T>::green = ColorRGB<T>( T( 0 ), Color<T>::getMax(), T( 0 ) );
	template<typename T> const ColorRGB<T> ColorRGB<T>::blue = ColorRGB<T>( T( 0 ), T( 0 ), Color<T>::getMax() );

	template<typename T>
	template<typename U>
	void ColorRGB<T>::_castFromR( const U & l ) {
		this -> r = l;
		this -> g = l;
		this -> b = l;
	}


	template<typename T>
	template<typename U>
	ColorRGB<T>::ColorRGB( const Math::Vec3<U> & v ) : Math::Vec3<T>( v ) {
	}
	template<typename T>
	template<typename U>
	ColorRGB<T>::ColorRGB( const U & r, const U & g, const U & b ) : Math::Vec3<T>(r, g, b) {
	}
	template<typename T>
	template<typename U>
	ColorRGB<T>::ColorRGB( const ColorRGB<U> & c ) : Math::Vec3<T>( c ) {
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const unsigned char & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const unsigned short & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const unsigned int & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const unsigned long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const unsigned long long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const char & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const short & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const int & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const long long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const float & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( const double & l ) {
		_castFromR( l );
	}

	template<typename T>
	template<typename U>
	ColorRGB<T>::ColorRGB( const ColorR<U> & c ) {
		_castFromR( c.r );
	}

	template<typename T>
	ColorRGB<T>::ColorRGB( void ) {
	}


	template<typename T>
	template<typename U>
	ColorRGB<T>::operator ColorR<U>() const {
		return ColorR<U>( getLightness() );
	}

	template<typename T>
	T ColorRGB<T>::getLightness() const {
		typedef typename Color<T>::SumType Sum;

		Math::Vec2<T> minMax = Math::getMinMax( *this );

		Sum sum( ( Sum( minMax.x ) + Sum( minMax.y ) ) / Sum( 2 ) );
		return sum;
	}

	template<typename T>
	const T & ColorRGB<T>::getRed() const {
		return this -> r;
	}

	template<typename T>
	const T & ColorRGB<T>::getGreen() const {
		return this -> g;
	}

	template<typename T>
	const T & ColorRGB<T>::getBlue() const {
		return this -> b;
	}


	template<typename T>
	template<typename U>
	ColorRGB<T> & ColorRGB<T>::operator=( const ColorRGB<U> & c ) {
		this -> r = c.r;
		this -> g = c.g;
		this -> b = c.b;
		return *this;
	}

	template<typename T>
	template<typename U>
	ColorRGB<T> & ColorRGB<T>::operator=( const Math::Vec3<U> & c ) {
		this -> r = c.r;
		this -> g = c.g;
		this -> b = c.b;
		return *this;
	}


	template<typename T>
	template<typename U>
	ColorRGB<T> & ColorRGB<T>::operator=( const ColorR<U> & c ) {
		_castFromR( c.r );
		return *this;
	}


	template<typename T>
	template<typename C /*= char*/>
	ColorRGB<T>::operator BasicString<C>() const {
		return toString<C>();
	}



	template<typename T>
	template<typename C /*= char*/>
	BasicString<C> ColorRGB<T>::toString() const {
		BasicString<C> newString;
		newString.reserve( 20 );
		newString << BasicString<C>("RGB(") << this -> r << C('\t') << this -> g << C( '\t' ) << this -> b << C( ')' );
		return newString;
	}

	template<typename T>
	template<typename C /*= char*/>
	BasicString<C> ColorRGB<T>::toHex() const {
		BasicString<C> newString;
		newString.reserve( 6 );
		newString << C( '#' ) << BasicString<C>::toString<16>( this -> r ) << BasicString<C>::toString<16>( this -> g ) << BasicString<C>::toString<16>( this -> b );
		return newString;
	}


	template<typename T>
	template<typename U>
	ColorRGB<U> ColorRGB<T>::toType() const {
		ColorRGB<U> colorResult;
		ColorRGB<T>::castComponent( colorResult.r, this -> r );
		ColorRGB<T>::castComponent( colorResult.g, this -> g );
		ColorRGB<T>::castComponent( colorResult.b, this -> b );
		return colorResult;
	}

	template<typename T>
	ColorRGB<T> ColorRGB<T>::RGBtoHSL() const {
		typedef typename Color<T>::KernelType U;
		U min;

		U rCasted( this -> r );
		U gCasted( this -> g );
		U bCasted( this -> b );

		constexpr U max( ColorRGB<T>::getMax() );
		constexpr U maxBy6( max / U( 6 ) );

		ColorRGB<T> hsl;

		if ( rCasted > gCasted ) {
			if ( gCasted < bCasted )
				min = ( gCasted );
			else
				min = ( bCasted );

			if ( rCasted > bCasted ) {
				auto delta (rCasted - min);
				if ( delta == U( 0 ) ) {
					hsl.h = U( 0 );
					hsl.s = U( 0 );
					hsl.l = ( rCasted + min ) / U( 2 );
				} else {
					hsl.h = ( ( maxBy6 * ( gCasted - bCasted ) / ( delta ) ) );
					if ( hsl.h < U( 0 ) ) hsl.h += max;
					U lightness2( rCasted + min );
					hsl.l = ( lightness2 ) / U( 2 );
					hsl.s = delta * max / ( max - Math::abs( lightness2 - max ) );
				}	
			} else {
				auto delta( bCasted - min );
				if ( delta == U( 0 ) ) {
					hsl.h = U( 0 );
					hsl.s = U( 0 );
					hsl.l = ( bCasted + min ) / U( 2 );
				} else {
					hsl.h = ( ( maxBy6 * ( rCasted - gCasted ) / ( delta ) + U( maxBy6 * U( 4 ) ) ) );
					U lightness2( bCasted + min );
					hsl.l = ( lightness2 ) / U( 2 );
					hsl.s = delta * max / ( max - Math::abs( lightness2 - max ) );
				}
			}
		} else {
			if ( rCasted < bCasted )
				min = ( rCasted );
			else
				min = ( bCasted );

			if ( gCasted > bCasted ) {
				auto delta( gCasted - min );
				if ( delta == U( 0 ) ) {
					hsl.h = U( 0 );
					hsl.s = U( 0 );
					hsl.l = ( gCasted + min ) / U( 2 );
				} else {
					hsl.h = ( ( maxBy6 * ( bCasted - rCasted ) / ( delta ) + U( maxBy6 * U( 2 ) ) ) );
					U lightness2( gCasted + min );
					hsl.l = ( lightness2 ) / U( 2 );
					hsl.s = delta * max / ( max - Math::abs( lightness2 - max ) );
				}
			} else {
				auto delta( bCasted - min );
				if ( delta == U( 0 ) ) {
					hsl.h = U( 0 );
					hsl.s = U( 0 );
					hsl.l = ( bCasted + min ) / U( 2 );
				} else {
					hsl.h = ( ( maxBy6 * ( rCasted - gCasted ) / ( delta ) + U( maxBy6 * U( 4 ) ) ) );
					U lightness2( bCasted + min );
					hsl.l = ( lightness2 ) / U( 2 );
					hsl.s = delta * max / ( max - Math::abs( lightness2 - max ) );
				}
			}
		}
		return hsl;
	}


	template<typename T>
	ColorRGB<T> ColorRGB<T>::HSLtoRGB() const {
		//http://www.rapidtables.com/convert/color/hsl-to-rgb.htm
		typedef typename Color<T>::KernelType U;

		constexpr U max( ColorRGB<T>::getMax() );
		constexpr U maxBy6( max / U( 6 ) );
		constexpr U max2( max * U( 2 ) );

		U hCasted( this -> h );
		U sCasted( this -> s );
		U lCasted( this -> l );

		ColorRGB<T> rgb;


		U C( ( max - Math::abs( U( 2 ) * lCasted - max ) ) * sCasted / max );
		U X( ( max - Math::abs( Math::modulus( hCasted * U( 6 ), max2 ) - max ) ) * C / max );
		U m( lCasted - C / U( 2 ) );

		if ( hCasted < maxBy6 ) {
			rgb.r = C + m;
			rgb.g = X + m;
			rgb.b = m;
		} else if ( hCasted < U( 2 ) * maxBy6 ) {
			rgb.r = X + m;
			rgb.g = C + m;
			rgb.b = m;
		} else if( hCasted < U( 3 ) * maxBy6 ) {
			rgb.r = m;
			rgb.g = C + m;
			rgb.b = X + m;
		} else if ( hCasted < U( 4 ) * maxBy6 ) {
			rgb.r = m;
			rgb.g = X + m;
			rgb.b = C + m;
		} else if ( hCasted < U( 5 ) * maxBy6 ) {
			rgb.r = X + m;
			rgb.g = m;
			rgb.b = C + m;
		} else {
			rgb.r = C + m;
			rgb.g = m;
			rgb.b = X + m;
		} 

		return rgb;

	}

}
