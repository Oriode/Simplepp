#pragma once

#include "../BasicMath.h"

namespace Math {

	namespace ML {

		namespace ActivationFunc {

			struct Linear {
				template<typename T> inline const T & operator()(const T& x) const { return x; }
				template<typename T> inline T grad(const T& x, const T& a) const { return x; }
			};

			struct Sigmoid {
				template<typename T> inline T operator()(const T& x) const { return T(1) / ( T(1) + Math::exp(-x) ); }
				template<typename T> inline T grad(const T& x, const T& a) const { return x * a * ( T(1) - a ); }
			};

			struct ReLU {
				template<typename T> inline T operator()(const T& x) const { return (x > T(0)) ? x : T(0); }
			};

		}

	}

}