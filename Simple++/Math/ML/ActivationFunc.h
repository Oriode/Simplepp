#pragma once

#include "../BasicMath.h"

namespace Math {

	namespace ML {

		namespace ActivationFunc {

			struct Linear {
				template<typename T> inline const T & operator()(const T& x) const { return x; }
				template<typename T> inline T grad(const T& a) const { return T(1); }
			};

			struct Sigmoid {
				template<typename T> inline T operator()(const T& x) const { return T(1) / ( T(1) + Math::exp(-x) ); }
				template<typename T> inline T grad(const T& a) const { return a * ( T(1) - a ); }
			};

			struct ReLU {
				template<typename T> inline T operator()(const T& x) const { return (x > T(0)) ? x : T(0); }
				template<typename T> inline T grad(const T& a) const { return (a > T(0)) ? T(1) : T(0); }
			};

		}

	}

}