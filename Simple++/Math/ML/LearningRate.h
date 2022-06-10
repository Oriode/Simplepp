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

				const T operator()(const Size epoch) const { static_assert( true, "BasicLearningRate::operator() should be overriden." ); }

			protected:
				T v;
			};

			template<typename T>
			class Constant : public BasicLearningRate<T> {
			public:
				Constant(const T & v) :
					BasicLearningRate<T>(v) {}

				const T & operator()(const Size epoch) const { return this->v; }
			};

			template<typename T>
			class Exp : public BasicLearningRate<T> {
			public:
				Exp(const T& v) :
					BasicLearningRate<T>(v) {}

				const T operator()(const Size epoch) const { return Math::exp(this->v * T(epoch + Size(1)) * T(0.01)); }
			};

			template<typename T>
			class Linear : public BasicLearningRate<T> {
			public:
				Linear(const T& v) :
					BasicLearningRate<T>(v) {}

				const T operator()(const Size epoch) const { return this->v / (T(1) + T(epoch) * T(0.1)); }
			};

		}

	}

}