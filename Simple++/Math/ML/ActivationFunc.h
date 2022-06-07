#pragma once

#include "../BasicMath.h"

namespace Math {

	namespace ML {

		namespace ActivationFunc {

			struct Sigmoid {
				template<typename T> inline T operator()(const T& x) const { return T(1) / ( T(1) + Math::exp(-x) ); }
			};

		}

	}

}