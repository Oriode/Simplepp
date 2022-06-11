#pragma once

#include "../BasicMath.h"

namespace Math {

	namespace ML {

		namespace LearningRate {

			template<typename T>
			class BasicLearningRate {
			public:
				BasicLearningRate(const T& v) :
					v(v) {}

				const T operator()(const Size epochNum) const { static_assert( true, "BasicLearningRate::operator() should be overriden." ); }

			protected:
				T v;
			};

			template<typename T>
			class Constant : public BasicLearningRate<T> {
			public:
				Constant(const T & v) :
					BasicLearningRate<T>(v) {}

				const T & operator()(const Size epochNum) const { return this->v; }
			};

			template<typename T>
			class Exp : public BasicLearningRate<T> {
			public:
				Exp(const T& v) :
					BasicLearningRate<T>(v) {}

				const T operator()(const Size epochNum) const {
					return this->v * (T(1.0) + Math::pow(T(10.0), T(epochNum) / T(1000.0)));
				}
			};

			template<typename T>
			class Linear : public BasicLearningRate<T> {
			public:
				Linear(const T& v) :
					BasicLearningRate<T>(v) {}

				const T operator()(const Size epochNum) const {
					if ( epochNum < Size(10) ) {
						return this->v;
					} else {
						const T x(T(epochNum) - T(10.0));
						return this->v * ( T(1.0) + x / T(10.0) );
					}
				}
			};

		}

	}

}