#pragma once

#include "../../IO/BasicIO.h"

#include "../BasicMath.h"
#include "../Mat.h"

namespace Math {

	namespace ML {

		namespace Optimizer {

			template<typename T>
			class BasicOptimizer {
			public:
				void init(const Size nbParams, const Size nbNeurons){ static_assert( false, "BasicOptimizer::init() should be overriden." ); }
				const T operator()(const Size epochNum, const Size neuronI, const Size paramI, const T & lastParam, const T & grad, const T & learningRateFactor) { static_assert( false, "BasicOptimizer::operator() should be overriden." ); }
				void reset(){ static_assert( false, "BasicOptimizer::reset() should be overriden." ); }
			};

			template<typename T>
			class Constant : public BasicOptimizer<T> {
			public:
				Constant(const T & learningRate = T(0.01)) :
					learningRate(learningRate)
				{}

				void init(const Size nbParams, const Size nbNeurons) {

				}

				const T & operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T & learningRateFactor) {
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
				Exp(const T& learningRate = T(0.01)) :
					learningRate(learningRate)
				{}

				void init(const Size nbParams, const Size nbNeurons) {

				}

				const T operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T& learningRateFactor) {
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
				Linear(const T& learningRate = T(0.01)) :
					learningRate(learningRate)
				{}

				void init(const Size nbParams, const Size nbNeurons) {

				}

				const T operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T& learningRateFactor) {
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

			template<typename T>
			class Adam : public BasicOptimizer<T>, public IO::BasicIO {
			public:
				Adam(const T& learningRate = T(0.001), const T& beta1 = T(0.9), const T& beta2 = T(0.999), const T& epsilon = T(0.000000001)) :
					learningRate(learningRate),
					beta1(beta1),
					beta2(beta2),
					epsilon(epsilon)
				{}

				void init(const Size nbParams, const Size nbNeurons) {
					this->gradAggregadeMat.resize(nbNeurons, nbParams);
					this->gradSumMat.resize(nbNeurons, nbParams);
				}

				const T& operator()(const Size epochNum, const Size neuronI, const Size paramI, const T& lastParam, const T& grad, const T& learningRateFactor) {
					T& gradAggregate(this->gradAggregadeMat.getValueI(neuronI, paramI));
					T& gradSum(this->gradSumMat.getValueI(neuronI, paramI));

					gradAggregate = this->beta1 * gradAggregate + ( T(1) - this->beta1 ) * grad;
					gradSum = this->beta2 * gradSum + ( T(1) - this->beta2 ) * grad * grad;

					const T biasCorrectedGradAggregate(gradAggregate / ( T(1) - this->beta1 ));
					const T biasCorrectedGradSum(gradSum / ( T(1) - this->beta2 ));

					return lastParam - biasCorrectedGradAggregate * ( ( this->learningRate * learningRateFactor ) / ( Math::sqrt(biasCorrectedGradSum) + this->epsilon ) );
				}

				void reset() {
					this->gradAggregadeMat.zeros();
					this->gradSumMat.zeros();
				}

				/**
				 * @brief 	read from a file stream
				 * @param [in,out]	stream	stream used to read load this object.
				 * @returns	boolean to know if the operation is a success of not.
				 */
				template<typename Stream>
				bool read(Stream* stream) {
					if ( !IO::read(stream, &this->learningRate) ) {
						return false;
					}
					if ( !IO::read(stream, &this->beta1) ) {
						return false;
					}
					if ( !IO::read(stream, &this->beta2) ) {
						return false;
					}
					if ( !IO::read(stream, &this->epsilon) ) {
						return false;
					}
					if ( !IO::read(stream, &this->gradAggregadeMat) ) {
						return false;
					}
					if ( !IO::read(stream, &this->gradSumMat) ) {
						return false;
					}
					return true;
				}

				/**
				 * @brief 	write this object as binary into a file stream
				 * @param [in,out]	stream	stream used to write this object.
				 * @returns	boolean to know if the operation is a success of not.
				 */
				template<typename Stream>
				bool write(Stream* stream) const {
					if ( !IO::write(stream, &this->learningRate) ) {
						return false;
					}
					if ( !IO::write(stream, &this->beta1) ) {
						return false;
					}
					if ( !IO::write(stream, &this->beta2) ) {
						return false;
					}
					if ( !IO::write(stream, &this->epsilon) ) {
						return false;
					}
					if ( !IO::write(stream, &this->gradAggregadeMat) ) {
						return false;
					}
					if ( !IO::write(stream, &this->gradSumMat) ) {
						return false;
					}
					return true;
				}

			private:
				T learningRate;
				T beta1;
				T beta2;
				T epsilon;

				Mat<T> gradAggregadeMat;
				Mat<T> gradSumMat;
			};

		}

	}

}