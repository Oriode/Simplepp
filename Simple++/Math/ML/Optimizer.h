#pragma once

#include "../BasicMath.h"
#include "../Mat.h"

namespace Math {

	namespace ML {

		namespace Optimizer {

			template<typename T>
			class BasicOptimizer {
			public:
				void init(const Size nbParams, const Size nbNeurons){ static_assert( false, "BasicOptimizer::init() should be overriden." ); }
				const T operator()(const Size epochNum, const Size neuronI, const Size paramI, const T & lastParam, const T & grad, const T & learningRateFactor) const { static_assert( false, "BasicOptimizer::operator() should be overriden." ); }
				void reset(){ static_assert( false, "BasicOptimizer::reset() should be overriden." ); }
			};

			template<typename T>
			class Constant : public BasicOptimizer<T> {
			public:
				Constant(){}
				Constant(const T & learningRate) :
					learningRate(learningRate)
				{}

				void init(const Size nbParams, const Size nbNeurons) {

				}

				const T & operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T & learningRateFactor) const {
					return lastParam - this->learningRate * learningRateFactor * grad;
				}

				void reset() {

				}

			private:
				T learningRate;
			};

			template<typename T>
			class Exp : public BasicOptimizer<T> {
			public:
				Exp(){}
				Exp(const T& learningRate) :
					learningRate(learningRate)
				{}

				void init(const Size nbParams, const Size nbNeurons) {

				}

				const T operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T& learningRateFactor) const {
					T currentLearningRate(this->learningRate * (T(1.0) + Math::pow(T(10.0), T(epochNum) / T(1000.0))));
					return lastParam - currentLearningRate * learningRateFactor * grad;
				}

				void reset() {

				}

			private:
				T learningRate;
			};

			template<typename T>
			class Linear : public BasicOptimizer<T> {
			public:
				Linear(){}
				Linear(const T& learningRate) :
					learningRate(learningRate)
				{}

				void init(const Size nbParams, const Size nbNeurons) {

				}

				const T operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T& learningRateFactor) const {
					T currentLearningRate;
					if ( epochNum < Size(10) ) {
						currentLearningRate = this->learningRate;
					} else {
						const T x(T(epochNum) - T(10.0));
						currentLearningRate = this->learningRate * ( T(1.0) + x / T(10.0) );
					}
					return lastParam - currentLearningRate * learningRateFactor * grad;
				}

				void reset() {

				}

			private:
				T learningRate;
			};

		}

	}

}