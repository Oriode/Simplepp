

namespace Math {


	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T e() {
		return T( 2.7182818 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T pi() {
		return T( 3.14159265359 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T random( const T & min, const T & max ) {
		static std::random_device _randomDevice;
		static T randomMax( _randomDevice.max() );
		T range( max - min );
		T rng( _randomDevice() );

		return rng * range / randomMax + min;
	}

	MATH_FUNC_QUALIFIER int random( int min, int max ) {
		static std::random_device _randomDevice;
		static unsigned long long randomMax( _randomDevice.max() );
		unsigned long long range( static_cast< unsigned long long >( max ) - static_cast< unsigned long long >( min ) );
		unsigned long long rng( _randomDevice() );
		return int( rng * range / randomMax ) + min;
	}

	MATH_FUNC_QUALIFIER unsigned int random( unsigned int min, unsigned int max ) {
		static std::random_device _randomDevice;
		static unsigned long long randomMax( _randomDevice.max() );
		unsigned long long range( max - min );
		unsigned long long rng( _randomDevice() );
		return unsigned int( rng * range / randomMax ) + min;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T random() {
		static std::random_device _randomDevice;
		return T( _randomDevice() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T randomF() {
		static std::random_device _randomDevice;
		return T( _randomDevice() ) / T( _randomDevice.max() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T randomMax() {
		static std::random_device _randomDevice;
		return T( _randomDevice.max() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const T & x, const T & y ) {
		return ( y < x ) ? y : x;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const T & x, const T & y ) {
		return ( y > x ) ? y : x;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T pow( const T & v, double e ) {
		return std::pow( v, e );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T abs( const T & v ) {
		return ( v < T( 0 ) ) ? -v : v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T pow( const T & v, int e ) {
		return ( e == int( 0 ) ) ? T( 1 ) : v * pow( v, e - int( 1 ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T gcd( const T & M, const T & N ) {
		return ( N == 0 ) ? M : gcd( N, M % N );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER constexpr int sign( const T & i ) {
		return i < T( 0 ) ? -1 : 1;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T clamp( const T & v, const T & min, const T & max ) {
		_assert( min <= max );
		if ( v > max ) return max;
		else if ( v < min ) return min;
		else return v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T fpart( const T & x ) {
		if ( x < T( 0 ) ) return -( Math::trunc( x ) - x );
		else return x - Math::trunc( x );
	}





	template<typename T>
	MATH_FUNC_QUALIFIER T trunc( const T & x ) {
		return x;
	}

	template<>
	MATH_FUNC_QUALIFIER float trunc( const float & x ) {
		return float( int( x ) );
	}

	template<>
	MATH_FUNC_QUALIFIER double trunc( const double & x ) {
		return double( long( x ) );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T radians( const T & degres ) {
		return degres * T( 0.0174532925 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T degree( const T & radians ) {
		return radians * T( 57.2957795786 );
	}


	template<intmax_t Numerator, intmax_t Denumerator = 1>
	struct Ratio {
		static_assert( Denumerator != 0, "Denominator cannot be zero." );
		static_assert( -INTMAX_MAX <= Numerator, "Numerator too negative." );
		static_assert( -INTMAX_MAX <= Numerator, "Denominator too negative." );

		static constexpr intmax_t g = gcd( Numerator, Denumerator );

		static constexpr intmax_t num = ( g == 0 ) ? 0 : ( sign( Numerator ) * sign( Denumerator ) * abs( Numerator ) / g );
		static constexpr intmax_t den = ( g == 0 ) ? 0 : ( abs( Denumerator ) / g );

		typedef Ratio<num, den> type;
	};

	template<typename T>
	MATH_FUNC_QUALIFIER T sincn( const T & x ) {
		if ( x == T( 0 ) )
			return T( 1 );
		else
			return ( sin( pi() * x ) ) / ( pi() * x );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sinc( const T & x ) {
		if ( x == T( 0 ) )
			return T( 1 );
		else
			return sin( x ) / x;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T modulus( const T & x, const T & d ) {
		return x % d;
	}
	MATH_FUNC_QUALIFIER float modulus( const float & x, const float & d ) {
		float r( x );
		if ( r > d ) {
			do { r -= d; } while ( r > d );
		} else if ( r < float( 0 ) ) {
			while ( r < float( 0 ) ) r += d;
		}
		return r;
	}
	MATH_FUNC_QUALIFIER double modulus( const double & x, const double & d ) {
		double r( x );
		if ( x > d ) {
			do { r -= d; } while ( r > d );
		} else if ( r < double( 0 ) ) {
			while ( r < double( 0 ) ) r += d;
		}
		return r;
	}


}



