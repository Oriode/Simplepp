#pragma once

#include "../BasicMath.h"

namespace Math {

	namespace ML {

		namespace ActivationFunc {

			struct BasicActivationFunc {
				template<typename T> inline const T& operator()(const T& x) const { static_assert( true, "BasicActivationFunc::operator() should be overriden." ); }
				template<typename T> inline T grad(const T& a) const { static_assert( true, "BasicActivationFunc::grad() should be overriden." ); }
			};

			struct Linear : public BasicActivationFunc {
				template<typename T> inline const T & operator()(const T& x) const { return x; }
				template<typename T> inline T grad(const T& a) const { return T(1); }
			};

			struct Sigmoid : public BasicActivationFunc {
				template<typename T> inline T operator()(const T& x) const { return T(1) / ( T(1) + Math::exp(-x) ); }
				template<typename T> inline T grad(const T& a) const { return a * ( T(1) - a ); }
			};

			struct ReLU : public BasicActivationFunc {
				template<typename T> inline T operator()(const T& x) const { return (x > T(0)) ? x : T(0); }
				template<typename T> inline T grad(const T& a) const { return (a > T(0)) ? T(1) : T(0); }
			};

		}

	}

}