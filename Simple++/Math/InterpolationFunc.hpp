#pragma once

namespace Math {


	namespace InterpolationFunc {
		class Linear {
		public:
			template<typename T> inline T operator()( const T & x ) const {
				return x;
			}
		};
		class Cubic {
		public:
			template<typename T> inline T operator()( const T & x ) const {
				T x2(x * x);
				return T(-2.0) * ( x2 * x ) + T(3.0f) * ( x2 );
			}
		};
	}

}
