#pragma once

#include "../../IO/IO.h"
#include "../../Vector.h"
#include "../../String.h"

#include "../Math.h"
#include "../Vec.h"

#include "Data.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbParams>
		class Neurode : public IO::BasicIO {
		public:
			Neurode();

			void addData(const T(&featureTable)[ NbFeatures ], T * out);

			constexpr Size getNbFeatures() const;
			constexpr Size getNbParams() const;
			const Size getNbData() const;

			const T * & getFeatures(const Size dataI) const;
			T*& getFeatures(const Size dataI);

			const T& getOut(const Size dataI) const;
			T& getOut(const Size dataI);

			const T& getParam(const Size paramI) const;
			T& getParam(const Size paramI);

			T computeY(const Size dataI) const;
			T computeCost() const;
			T computeCoefficientOfDetermination() const;
			T computeGrad(const Size paramI) const;

			void gradientDescent(const T& learningRate = T(0.01), const Size nbIterations = Size(100), int verbose = 2);

			static void setParamTable(T(&paramTable)[ NbParams ]);
			static T computeY(const T(&featureTable)[ NbFeatures ], const T(&paramTable)[ NbParams ]);

		private:
			Vector<const T *> inputVector;
			Vector<T *> outputVector;
			T paramTable[ NbParams ];		// Table of parameters of size [NbParams].
		};

		template<typename T, Size NbFeatures, Size NbParams>
		inline Neurode<T, NbFeatures, NbParams>::Neurode() {
			assert(NbFeatures <= NbParams);

			setParamTable(this->paramTable);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline constexpr Size Neurode<T, NbFeatures, NbParams>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline constexpr Size Neurode<T, NbFeatures, NbParams>::getNbParams() const {
			return NbParams;
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline const Size Neurode<T, NbFeatures, NbParams>::getNbData() const {
			return this->inputVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline const T*& Neurode<T, NbFeatures, NbParams>::getFeatures(const Size dataI) const {
			return const_cast< Neurode<T, NbFeatures, NbParams> * >( this )->getFeatures(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T*& Neurode<T, NbFeatures, NbParams>::getFeatures(const Size dataI) {
			return this->inputVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline const T& Neurode<T, NbFeatures, NbParams>::getOut(const Size dataI) const {
			return const_cast< Neurode<T, NbFeatures, NbParams> * >( this )->getOut(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T& Neurode<T, NbFeatures, NbParams>::getOut(const Size dataI) {
			return *this->outputVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline const T& Neurode<T, NbFeatures, NbParams>::getParam(const Size paramI) const {
			return const_cast< Neurode<T, NbFeatures, NbParams> * >( this )->getParam(paramI);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T& Neurode<T, NbFeatures, NbParams>::getParam(const Size paramI) {
			return this->paramTable[paramI];
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T Neurode<T, NbFeatures, NbParams>::computeY(const Size dataI) const {
			return Neurode<T, NbFeatures, NbParams>::computeY(getFeatures(dataI), this->paramTable);
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T Neurode<T, NbFeatures, NbParams>::computeCost() const {
			const T nbDataT(T(getNbData() * Size(2)));

			T ySum(0);
			for ( Size i(0); i < getNbData(); i++ ) {
				const T& dataY(getOut(i));
				const T y(computeY(i) - dataY);
			}

			return ySum / nbDataT;
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T Neurode<T, NbFeatures, NbParams>::computeCoefficientOfDetermination() const {

			T dataMean(0);
			for ( Size i(0); i < getNbData(); i++ ) {
				const T& dataY(getOut(i));
				dataMean += dataY;
			}
			dataMean /= T(getNbData());

			T errSum(0);
			T meanSum(0);
			for ( Size i(0); i < getNbData(); i++ ) {
				const T& dataY(getOut(i));

				const T y(computeY(i));
				const T err(dataY - y);
				const T mean(dataY - dataMean);

				errSum += err * err;
				meanSum += mean * mean;
			}

			return T(1) - errSum / meanSum;
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T Neurode<T, NbFeatures, NbParams>::computeGrad(const Size paramI) const {
			assert(this->NbParams > paramI);

			const T nbDataT(T(getNbData()));

			T ySum(0);

			if ( m < this->NbFeatures ) {
				for ( Size i(0); i < getNbData(); i++ ) {
					const T * & dataX(getFeatures(i));
					const T& dataY(getOut(i));

					const T y(computeY(i) - dataY);
					ySum += dataX[paramI] * y;
				}
			} else {
				for ( Size i(0); i < this->inputVector.getSize(); i++ ) {
					const T& dataY(getOut(i));

					const T y(computeY(i) - dataY);
					ySum += y;
				}
			}

			return ySum / nbDataT;
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline void Neurode<T, NbFeatures, NbParams>::gradientDescent(const T& learningRate, const Size nbIterations, int verbose) {

			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting gradient descent with % iterations...", nbIterations));
			}

			Size nbIterationsLog;
			if ( verbose > 1 ) {
				if ( nbIterations > Size(100) ) {
					nbIterationsLog = nbIterations / Size(100);
				} else if ( nbIterations > Size(10) ) {
					nbIterationsLog = nbIterations / Size(10);
				} else {
					nbIterationsLog = nbIterations;
				}
			}

			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				for ( Size i(0); i < NbParams; i++ ) {
					T& param(getParam(i));
					param = param - learningRate * computeGrad(i);
				}

				if ( verbose > 1 ) {
					if ( ( iterationI + Size(1) ) % nbIterationsLog == Size(0) ) {
						Size progression(T(iterationI + Size(1)) / T(nbIterations - Size(1)) * T(100));
						Log::displayLog(String::format("[%/%] Finished loop with cost of %.", progression, computeCost()), Log::MessageColor::DarkWhite);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCost(), computeCoefficientOfDetermination() * T(100)));
				Log::displayLog(this->paramTable.toString());
			}
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline void Neurode<T, NbFeatures, NbParams>::setParamTable(T(&paramTable)[ NbParams ]) {
			for ( Size i(0); i < NbParams; i++ ) {
				paramTable[ i ] = Math::randomF();
			}
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline T Neurode<T, NbFeatures, NbParams>::computeY(const T(&featureTable)[ NbFeatures ], const T(&paramTable)[ NbParams ]) {
			assert(NbFeatures <= NbParams);

			T y(0);
			for ( Size i(0); i < NbFeatures; i++ ) {
				y += featureTable[ i ] * paramTable[ i ];
			}
			for ( Size i(NbFeatures); i < NbParams; i++ ) {
				y += paramTable[ i ];
			}
			return y;
		}

		template<typename T, Size NbFeatures, Size NbParams>
		inline void Neurode<T, NbFeatures, NbParams>::addData(const T(&featureTable)[ NbFeatures ], T * out) {
			this->inputVector.push(featureTable);
			this->outputVector.push(out);
		}

	}

}