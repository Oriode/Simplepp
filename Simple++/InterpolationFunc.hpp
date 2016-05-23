#pragma once

namespace Graphic {


	namespace InterpolationFunc {
		class Linear {
		public:
			template<typename C> inline C operator()(const C & c1, const C & c2, float x) const {
				return C(c1 * ( 1.0f - x ) + c2 * x);
			}



		};
		class Cubic {
		public:
			template<typename C> inline C operator()(const C & c1, const C & c2, float x) const {
				x = -2.0f * ( x * x * x ) + 3.0f * ( x * x );
				return C(c1 * ( 1.0f - x ) + c2 * x);
			}

		};
	}

}
