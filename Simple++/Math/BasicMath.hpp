

namespace Math {

	template<typename FakeType>
	std::random_device BasicMathT<FakeType>::_randomDevice;

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T BasicMathT<FakeType>::e() {
		return T( 2.7182818 );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T BasicMathT<FakeType>::pi() {
		return T( 3.14159265359 );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::modulus(const T& x, const T& d) {
		return x % d;
	}

	template<typename FakeType>
	MATH_FUNC_QUALIFIER float BasicMathT<FakeType>::modulus(const float& x, const float& d) {
		float r(x);
		if ( r > d ) {
			do { r -= d; } while ( r > d );
		} else if ( r < float(0) ) {
			while ( r < float(0) ) r += d;
		}
		return r;
	}

	template<typename FakeType>
	MATH_FUNC_QUALIFIER double BasicMathT<FakeType>::modulus(const double& x, const double& d) {
		double r(x);
		if ( x > d ) {
			do { r -= d; } while ( r > d );
		} else if ( r < double(0) ) {
			while ( r < double(0) ) r += d;
		}
		return r;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::random( const T & min, const T & max ) {
		static T randomMax(BasicMathT<FakeType>::_randomDevice.max() );
		T range( max - min );
		T rng(BasicMathT<FakeType>::_randomDevice() );

		return rng * range / randomMax + min;
	}

	template<typename FakeType>
	MATH_FUNC_QUALIFIER int BasicMathT<FakeType>::random( int min, int max ) {
		static unsigned long long int randomMax(BasicMathT<FakeType>::_randomDevice.max() );
		unsigned long long int range( static_cast< unsigned long long int >( max ) - static_cast< unsigned long long int >( min ) );
		unsigned long long int rng(BasicMathT<FakeType>::_randomDevice() );
		return int( rng * range / randomMax ) + min;
	}

	template<typename FakeType>
	MATH_FUNC_QUALIFIER unsigned long long int BasicMathT<FakeType>::random(unsigned long long int min, unsigned long long int max ) {
		static unsigned long long int randomMax(BasicMathT<FakeType>::_randomDevice.max() );
		unsigned long long int range( max - min );
		unsigned long long int rng(BasicMathT<FakeType>::_randomDevice() );
		return static_cast<unsigned long long int>( rng * range / randomMax ) + min;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::random() {
		return T(BasicMathT<FakeType>::_randomDevice() );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::randomF() {
		return T(BasicMathT<FakeType>::_randomDevice() ) / T(BasicMathT<FakeType>::_randomDevice.max() );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::randomMax() {
		return T(BasicMathT<FakeType>::_randomDevice.max() );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER const T & BasicMathT<FakeType>::min( const T & x, const T & y ) {
		return ( y < x ) ? y : x;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER const T & BasicMathT<FakeType>::max( const T & x, const T & y ) {
		return ( y > x ) ? y : x;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::pow( const T & v, double e ) {
		return std::pow( v, e );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T BasicMathT<FakeType>::abs( const T & v ) {
		return ( v < T( 0 ) ) ? -v : v;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T BasicMathT<FakeType>::pow( const T & v, unsigned int e ) {
		return ( e == static_cast<unsigned int>( 0 ) ) ? T( 1 ) : v * pow( v, e - static_cast<unsigned int>( 1 ) );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr T BasicMathT<FakeType>::gcd( const T & M, const T & N ) {
		return ( N == 0 ) ? M : gcd( N, M % N );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER constexpr int BasicMathT<FakeType>::sign( const T & i ) {
		return i < T( 0 ) ? -1 : 1;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::clamp( const T & v, const T & min, const T & max ) {
		_ASSERT_SPP( min <= max );
		if ( v > max ) return max;
		else if ( v < min ) return min;
		else return v;
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::fpart( const T & x ) {
		if ( x < T( 0 ) ) return -( Math::trunc( x ) - x );
		else return x - Math::trunc( x );
	}




	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::trunc( const T & x ) {
		return x;
	}

	template<typename FakeType>
	MATH_FUNC_QUALIFIER float BasicMathT<FakeType>::trunc( const float & x ) {
		return static_cast<float>( static_cast<int>( x ) );
	}

	template<typename FakeType>
	MATH_FUNC_QUALIFIER double BasicMathT<FakeType>::trunc( const double & x ) {
		return static_cast<double>( static_cast<long int>( x ) );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::radians( const T & degres ) {
		return degres * T( 0.0174532925 );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::degree( const T & radians ) {
		return radians * T( 57.2957795786 );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::sincn( const T & x ) {
		if ( x == T( 0 ) )
			return T( 1 );
		else
			return ( sin( pi() * x ) ) / ( pi() * x );
	}

	template<typename FakeType>
	template<typename T>
	MATH_FUNC_QUALIFIER T BasicMathT<FakeType>::sinc( const T & x ) {
		if ( x == T( 0 ) )
			return T( 1 );
		else
			return sin( x ) / x;
	}


}



