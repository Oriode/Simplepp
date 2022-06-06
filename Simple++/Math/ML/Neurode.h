#pragma once

#include "../../IO/IO.h"
#include "../../StaticTable.h"
#include "../../Vector.h"
#include "../../String.h"

#include "../Math.h"
#include "../Vec.h"

#include "Data.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbParams, typename Func = Math::Operations::Identity>
		class Neurode : public IO::BasicIO {
		public:
			Neurode(const Func & activationFunc = Func());

			void addData(const StaticTable<T, NbFeatures> & featureTable, T * out);

			constexpr Size getNbFeatures() const;
			constexpr Size getNbParams() const;
			const Size getNbData() const;

			const StaticTable<T, NbFeatures>& getFeatures(const Size dataI) const;
			StaticTable<T, NbFeatures>& getFeatures(const Size dataI);

			const StaticTable<T, NbParams>& getParams() const;

			const T& getOut(const Size dataI) const;
			T& getOut(const Size dataI);

			const T& getParam(const Size paramI) const;
			T& getParam(const Size paramI);

			void setParam(const Size paramI, const T& v);

			T computeY(const Size dataI) const;
			T computeY(const StaticTable<T, NbFeatures>& featureTable) const;
			T computeCostQuadratic() const;
			T computeCost() const;
			T computeCoefficientOfDetermination() const;
			T computeGrad(const Size paramI) const;

			void gradientDescent(const T& learningRate = T(0.01), const Size nbIterations = Size(100), int verbose = 2);

			static void setParamTable(StaticTable<T, NbParams> & paramTable);
			static T computeY(const StaticTable<T, NbFeatures> & featureTable, const StaticTable<T, NbParams>& paramTable, const Func & activationFunc);

		private:
			Vector<StaticTable<T, NbFeatures>> inputVector;
			Vector<T *> outputVector;
			StaticTable<T, NbParams> paramTable;		// Table of parameters of size [NbParams].

			const Func activationFunc;
		};

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline Neurode<T, NbFeatures, NbParams, Func>::Neurode(const Func& activationFunc) :
			activationFunc(activationFunc)
		{
			assert(NbFeatures <= NbParams);

			setParamTable(this->paramTable);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline constexpr Size Neurode<T, NbFeatures, NbParams, Func>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline constexpr Size Neurode<T, NbFeatures, NbParams, Func>::getNbParams() const {
			return NbParams;
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline const Size Neurode<T, NbFeatures, NbParams, Func>::getNbData() const {
			return this->inputVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline const StaticTable<T, NbFeatures>& Neurode<T, NbFeatures, NbParams, Func>::getFeatures(const Size dataI) const {
			return const_cast< Neurode<T, NbFeatures, NbParams, Func> * >( this )->getFeatures(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline StaticTable<T, NbFeatures>& Neurode<T, NbFeatures, NbParams, Func>::getFeatures(const Size dataI) {
			return this->inputVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline const StaticTable<T, NbParams>& Neurode<T, NbFeatures, NbParams, Func>::getParams() const {
			return this->paramTable;
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline const T& Neurode<T, NbFeatures, NbParams, Func>::getOut(const Size dataI) const {
			return const_cast< Neurode<T, NbFeatures, NbParams, Func> * >( this )->getOut(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T& Neurode<T, NbFeatures, NbParams, Func>::getOut(const Size dataI) {
			return *this->outputVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline const T& Neurode<T, NbFeatures, NbParams, Func>::getParam(const Size paramI) const {
			return const_cast< Neurode<T, NbFeatures, NbParams, Func> * >( this )->getParam(paramI);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T& Neurode<T, NbFeatures, NbParams, Func>::getParam(const Size paramI) {
			return this->paramTable[paramI];
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline void Neurode<T, NbFeatures, NbParams, Func>::setParam(const Size paramI, const T& v) {
			this->paramTable[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeY(const Size dataI) const {
			return Neurode<T, NbFeatures, NbParams, Func>::computeY(getFeatures(dataI), this->paramTable, this->activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeY(const StaticTable<T, NbFeatures>& featureTable) const {
			return Neurode<T, NbFeatures, NbParams, Func>::computeY(featureTable, this->paramTable, this->activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeCostQuadratic() const {
			const T nbDataT(T(getNbData() * Size(2)));

			T ySum(0);
			for ( Size i(0); i < getNbData(); i++ ) {
				const T& dataY(getOut(i));
				const T y(computeY(i) - dataY);
				ySum += y * y;
			}

			return ySum / nbDataT;
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeCost() const {
			const T nbDataT(getNbData());

			T ySum(0);
			for ( Size i(0); i < getNbData(); i++ ) {
				const T& dataY(getOut(i));
				const T y(computeY(i));
				ySum += dataY * Math::log(y) + ( T(1) - dataY ) * Math::log(T(1) - y);
			}

			return -ySum / nbDataT;
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeCoefficientOfDetermination() const {

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

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeGrad(const Size paramI) const {
			assert(getNbParams() > paramI);

			const T nbDataT(getNbData());

			T ySum(0);

			if ( paramI < getNbFeatures() ) {
				for ( Size i(0); i < getNbData(); i++ ) {
					const StaticTable<T, NbFeatures>& dataX(getFeatures(i));
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

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline void Neurode<T, NbFeatures, NbParams, Func>::gradientDescent(const T& learningRate, const Size nbIterations, int verbose) {

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
						Log::displayLog(String::format("[%/%] Finished loop with cost of %.", progression, computeCostQuadratic()), Log::MessageColor::DarkWhite);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCostQuadratic(), computeCoefficientOfDetermination() * T(100)));
				// Log::displayLog(this->paramTable.toString());
			}
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline void Neurode<T, NbFeatures, NbParams, Func>::setParamTable(StaticTable<T, NbParams>& paramTable) {
			for ( Size i(0); i < NbParams; i++ ) {
				paramTable[ i ] = Math::randomF();
			}
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline T Neurode<T, NbFeatures, NbParams, Func>::computeY(const StaticTable<T, NbFeatures>& featureTable, const StaticTable<T, NbParams>& paramTable, const Func& activationFunc) {
			assert(NbFeatures <= NbParams);

			T y(0);
			for ( Size i(0); i < NbFeatures; i++ ) {
				y += featureTable[ i ] * paramTable[ i ];
			}
			for ( Size i(NbFeatures); i < NbParams; i++ ) {
				y += paramTable[ i ];
			}
			return activationFunc(y);
		}

		template<typename T, Size NbFeatures, Size NbParams, typename Func>
		inline void Neurode<T, NbFeatures, NbParams, Func>::addData(const StaticTable<T, NbFeatures>& featureTable, T * out) {
			this->inputVector.push(featureTable);
			this->outputVector.push(out);
		}

	}

}