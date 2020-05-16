namespace Graphic {

	template<typename T> const ColorRGBA<T> ColorRGBA<T>::black = ColorRGBA<T>( T( 0 ), T( 0 ), T( 0 ), Color<T>::getMax() );
	template<typename T> const ColorRGBA<T> ColorRGBA<T>::white = ColorRGBA<T>( Color<T>::getMax(), Color<T>::getMax(), Color<T>::getMax(), Color<T>::getMax() );
	template<typename T> const ColorRGBA<T> ColorRGBA<T>::red = ColorRGBA<T>( Color<T>::getMax(), T( 0 ), T( 0 ), Color<T>::getMax() );
	template<typename T> const ColorRGBA<T> ColorRGBA<T>::green = ColorRGBA<T>( T( 0 ), Color<T>::getMax(), T( 0 ), Color<T>::getMax() );
	template<typename T> const ColorRGBA<T> ColorRGBA<T>::blue = ColorRGBA<T>( T( 0 ), T( 0 ), Color<T>::getMax(), Color<T>::getMax() );

	template<typename T> const Format ColorRGBA<T>::format = Format::RGBA;

	template<typename T>
	template<typename U>
	void ColorRGBA<T>::_castFromR( const U & l ) {
		this -> r = l;
		this -> g = l;
		this -> b = l;
		this -> a = getMax();
	}

	template<typename T>
	template<typename U>
	void ColorRGBA<T>::_castFromRGB( const U & r, const U & g, const U & b ) {
		this -> r = r;
		this -> g = g;
		this -> b = b;
		this -> a = getMax();
	}

	
	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const U & r, const U & g, const U & b ) {
		_castFromRGB( r, g, b );
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const U & r, const U & g, const U & b, const U & a ) : Math::Vec4<T>(r, g, b , a) {
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const unsigned char & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const unsigned short & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const unsigned int & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const unsigned long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const unsigned long long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const char & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const short & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const int & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const long long & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const float & l ) {
		_castFromR( l );
	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( const double & l ) {
		_castFromR( l );
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const ColorR<U> & c ) {
		_castFromR( c.r );
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const Math::Vec3<U> & v ) {
		_castFromRGB( v.r, v.g, v.b );
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const ColorRGB<U> & v ) {
		_castFromRGB( v.r, v.g, v.b );
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const Math::Vec4<U> & v ) : Math::Vec4<T>(v) {
		
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::ColorRGBA( const ColorRGBA<U> & v ) : Math::Vec4<T>( v ) {

	}

	template<typename T>
	ColorRGBA<T>::ColorRGBA( void ) {
	}


	template<typename T>
	template<typename U>
	ColorRGBA<T>::operator ColorR<U>() const {
		return ColorR<U>( getLightness() );
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T>::operator ColorRGB<U>() const {
		return ColorRGB<U>( this -> r, this -> g, this -> b );
	}

	template<typename T>
	T ColorRGBA<T>::getLightness() const {
		return ColorRGB<T>(*this).getLightness();
	}

	template<typename T>
	const T & ColorRGBA<T>::getRed() const {
		return this -> r;
	}

	template<typename T>
	const T & ColorRGBA<T>::getGreen() const {
		return this -> g;
	}

	template<typename T>
	const T & ColorRGBA<T>::getBlue() const {
		return this -> b;
	}

	template<typename T>
	const T & ColorRGBA<T>::getAlpha() const {
		return this -> a;
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T> & ColorRGBA<T>::operator=( const ColorRGB<U> & c ) {
		_castFromRGB( c.r, c.g, c.b );
		return *this;
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T> & ColorRGBA<T>::operator=( const Math::Vec3<U> & c ) {
		_castFromRGB( c.r, c.g, c.b );
		return *this;
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T> & ColorRGBA<T>::operator=( const ColorRGBA<U> & c ) {
		this -> r = c.r;
		this -> g = c.g;
		this -> b = c.b;
		this -> a = c.a;
		return *this;
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T> & ColorRGBA<T>::operator=( const Math::Vec4<U> & c ) {
		this -> r = c.r;
		this -> g = c.g;
		this -> b = c.b;
		this -> a = c.a;
		return *this;
	}

	template<typename T>
	template<typename U>
	ColorRGBA<T> & ColorRGBA<T>::operator=( const ColorR<U> & c ) {
		_castFromR( c.r );
		return *this;
	}


	template<typename T>
	template<typename C /*= char*/>
	ColorRGBA<T>::operator BasicString<C>() const {
		return toString<C>();
	}



	template<typename T>
	template<typename C /*= char*/>
	BasicString<C> ColorRGBA<T>::toString() const {
		BasicString<C> newString;
		newString.reserve( 20 );
		newString << BasicString<C>("RGBA(") << this -> r << C('\t') << this -> g << C( '\t' ) << this -> b << C( '\t' ) << this -> a << C( ')' );
		return newString;
	}

	template<typename T>
	template<typename C /*= char*/>
	BasicString<C> ColorRGBA<T>::toHex() const {
		BasicString<C> newString;
		newString.reserve( 8 );
		newString << C( '#' ) << BasicString<C>::toString<16>( this -> r ) << BasicString<C>::toString<16>( this -> g ) << BasicString<C>::toString<16>( this -> b ) << BasicString<C>::toString<16>( this -> a );
		return newString;
	}


	template<typename T>
	template<typename U>
	ColorRGBA<U> ColorRGBA<T>::toType() const {
		ColorRGBA<U> colorResult;
		ColorRGBA<T>::castComponent( colorResult.r, this -> r );
		ColorRGBA<T>::castComponent( colorResult.g, this -> g );
		ColorRGBA<T>::castComponent( colorResult.b, this -> b );
		ColorRGBA<T>::castComponent( colorResult.a, this -> a );
		return colorResult;
	}

	template<typename T>
	ColorRGBA<T> ColorRGBA<T>::RGBAtoHSLA() const {
		ColorRGB<T> colorHSL = ColorRGB<T>( *this ).RGBtoHSL();
		return ColorRGBA<T>( colorHSL.r, colorHSL.g, colorHSL.b, this -> a );
	}


	template<typename T>
	ColorRGBA<T> ColorRGBA<T>::HSLAtoRGBA() const {
		ColorRGB<T> colorRGB = ColorRGB<T>( *this ).RGBtoHSL();
		return ColorRGBA<T>( colorRGB.r, colorRGB.g, colorRGB.b, this -> a );
	}

}
