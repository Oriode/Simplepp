#pragma once

#include "../../IO/IO.h"
#include "../../Vector.h"
#include "../Math.h"
#include "../Mat.h"

#include "Data.h"

namespace Math {

	namespace ML {

		template<typename T>
		class LinearRegression : public IO::BasicIO {
		public:
			LinearRegression(const Size nbFeatures, const Size nbParams);

			void addData(const Data<T>& data);
			template<typename C, Size NbFeatures, Size NbOut>
			void addData(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ NbOut ]);
			void addData(const Vector<Data<T>>& dataVector);

			const Size getNbFeatures() const;
			const Size getNbParams() const;

			T computeY(const Size m, const Size n) const;
			T computeCost() const;
			T computeCoeficientOfDetermination() const;
			T computeGrad(const Size m, const Size n) const;
			void computeGradM(Mat<T>& m) const;

			void gradientDescent(const T& learningRate = T(0.01), const Size nbIterations = Size(100), int verbose = 2);

			static void setXMat(Mat<T>& x, const Vector<Data<T>>& dataVector, const Size nbParams);
			static void setParamMat(Mat<T>& paramMat, const Size nbParams, const Size nbOut);
			static T computeY(const Vector<Data<T>>& dataVector, const Mat<T>& paramMat, const Size m, const Size n);

		private:
			void _updateXMat();

			Size nbFeatures;
			Size nbOut;
			Size nbParams;

			Vector<Data<T>> dataVector;
			Mat<T> paramMat;		// Matrix of parameters of size [NbParams, 1].
			Mat<T> xMat;			// Matrix of input features of size [NbData, NbParams].

			bool bIsXMatUpdated;
		};

		template<typename T>
		Vector<Data<T>> generateData(const Size nbData, const Size nbFeatures, const Size nbOut, const Size nbParams, const T & noise = T(0.1), int verbose = 1);

		template<typename T>
		inline LinearRegression<T>::LinearRegression(const Size nbFeatures, const Size nbParams) :
			nbFeatures(nbFeatures),
			nbOut(Size(1)),
			nbParams(nbParams),
			paramMat(nbParams, Size(1)),
			bIsXMatUpdated(false)
		{
			assert(this->nbFeatures <= this->nbParams);

			setParamMat(this->paramMat, this->nbParams, this->nbOut);
		}

		template<typename T>
		inline void LinearRegression<T>::addData(const Data<T>&data) {
			assert(this->nbFeatures == data.getNbFeatures());
			assert(this->nbOut == data.getNbOut());
			this->dataVector.push(data);

			this->bIsXMatUpdated = false;
		}

		template<typename T>
		inline void LinearRegression<T>::addData(const Vector<Data<T>>& dataVector) {
			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				const Data<T>& data(dataVector.getValueI(i));

				if ( data.getNbFeatures() != this->nbFeatures ) {
					Log::displayError(String::format("Unable to add a data to the ML system. Number of features missmatch % (data) != % (system).", data.getNbFeatures(), this->nbFeatures));
					continue;
				}
				if ( data.getNbOut() != this->nbOut ) {
					Log::displayError(String::format("Unable to add a data to the ML system. Number of out missmatch % (data) != % (system).", data.getNbOut(), this->nbOut));
					continue;
				}
				this->dataVector.push(data);
			}
		}

		template<typename T>
		inline const Size LinearRegression<T>::getNbFeatures() const {
			return this->nbFeatures;
		}

		template<typename T>
		inline const Size LinearRegression<T>::getNbParams() const {
			return this->nbParams;
		}

		template<typename T>
		inline T LinearRegression<T>::computeY(const Size m, const Size n) const {
			return LinearRegression<T>::computeY(this->dataVector, this->paramMat, m, n);
		}

		template<typename T>
		inline T LinearRegression<T>::computeCost() const {
			const T nbDataT(T(this->dataVector.getSize() * Size(2)));

			T ySum(0);
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < this->nbOut; j++ ) {
					const T y(computeY(i, j) - data.getOut(j));
					ySum += y * y;
				}

			}

			return ySum / nbDataT;
		}

		template<typename T>
		inline T LinearRegression<T>::computeCoeficientOfDetermination() const {

			Vec<T> meanVec(this->nbOut);
			meanVec.zeros();
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					meanVec.setValueI(j, meanVec.getValueI(j) + data.getOut(j));
				}
			}
			meanVec /= T(this->dataVector.getSize());

			T errSum(0);
			T meanSum(0);
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					const T y(computeY(i, j));
					const T err(data.getOut(j) - y);
					const T mean(data.getOut(j) - meanVec.getValueI(j));

					errSum += err * err;
					meanSum += mean * mean;
				}
			}

			return T(1) - errSum / meanSum;
		}

		template<typename T>
		inline T LinearRegression<T>::computeGrad(const Size m, const Size n) const {
			assert(this->nbParams > m);
			assert(this->nbOut > n);

			const T nbDataT(T(this->dataVector.getSize()));

			T ySum(0);

			if ( m < this->nbFeatures ) {
				for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
					const Data<T>& data(this->dataVector.getValueI(i));

					const T y(computeY(i, n) - data.getOut(n));
					ySum += data.getFeature(m) * y;
				}
			} else {
				for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
					const Data<T>& data(this->dataVector.getValueI(i));

					const T y(computeY(i, n) - data.getOut(n));
					ySum += y;
				}
			}

			return ySum / nbDataT;
		}

		template<typename T>
		inline void LinearRegression<T>::computeGradM(Mat<T>& m) const {
			assert(this->nbParam == m.getSizeM());
			assert(this->NbOut == m.getSizeN());

			for ( Size i(0); i < m.getSizeM(); i++ ) {
				for ( Size j(0); j < m.getSizeN(); j++ ) {
					m.setValueI(i, j, computeGrad(i, j));
				}
			}
		}

		template<typename T>
		inline void LinearRegression<T>::gradientDescent(const T& learningRate, const Size nbIterations, int verbose) {

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
				for ( Size i(0); i < this->paramMat.getSizeM(); i++ ) {
					for ( Size j(0); j < this->paramMat.getSizeN(); j++ ) {
						T& param(this->paramMat.getValueI(i, j));

						param = param - learningRate * computeGrad(i, j);
					}
				}

				if ( verbose > 1 ) {
					if ( (iterationI + Size(1)) % nbIterationsLog == Size(0) ) {
						Size progression(T(iterationI + Size(1)) / T(nbIterations - Size(1)) * T(100));
						Log::displayLog(String::format("[%/%] Finished loop with cost of %.", progression, computeCost()), Log::MessageColor::DarkWhite);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCost(), computeCoeficientOfDetermination() * T(100)));
				Log::displayLog(this->paramMat.toString());
			}
		}

		template<typename T>
		inline void LinearRegression<T>::setXMat(Mat<T>& x, const Vector<Data<T>>& dataVector, const Size nbParams) {

			const Size newM(dataVector.getSize());
			const Size newN(NbParams);

			x.resizeNoCopy(newM, newN);

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				const Data<T>& data(dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbFeatures(); j++ ) {
					x.setValueI(i, j, data.getFeature(j));
				}
				for ( Size j(data.getNbFeatures()); j < nbParams; j++ ) {
					x.setValueI(i, j, T(1));
				}
			}
		}

		template<typename T>
		inline void LinearRegression<T>::setParamMat(Mat<T>& paramMat, const Size nbParams, const Size nbOut) {
			paramMat.resizeNoCopy(nbParams, nbOut);
			paramMat.randomF();
		}

		template<typename T>
		inline T LinearRegression<T>::computeY(const Vector<Data<T>>& dataVector, const Mat<T>& paramMat, const Size m, const Size n) {
			assert(dataVector.getSize() > m);
			assert(paramMat.getSizeN() > n);

			const BasicVector<T>& featureTable(dataVector.getValueI(m).getFeatures());

			T y(0);
			for ( Size i(0); i < featureTable.getSize(); i++ ) {
				const T& feature(featureTable.getValueI(i));
				const T& param(paramMat.getValueI(i, n));

				y += feature * param;
			}
			for ( Size i(featureTable.getSize()); i < paramMat.getSizeM(); i++ ) {
				const T& param(paramMat.getValueI(i, n));

				y += param;
			}
			return y;
		}

		template<typename T>
		inline void LinearRegression<T>::_updateXMat() {
			if ( !this->bIsXMatUpdated ) {
				setXMat(this->xMat, this->dataVector, this->nbParams);

				this->bIsXMatUpdated = true;
			}
		}

		template<typename T>
		template<typename C, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T>::addData(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ NbOut ]) {
			assert(this->nbFeatures == NbFeatures);
			assert(this->nbOut = NbOut);
			addData(Data<T>(featureTable, outTable));
		}

		template<typename T>
		Vector<Data<T>> generateData(const Size nbData, const Size nbFeatures, const Size nbOut, const Size nbParams, const T& noise, int verbose) {
			Vector<Data<T>> dataVector;
			dataVector.resize(nbData);

			Mat<T> paramMat;
			LinearRegression<T>::setParamMat(paramMat, nbParams, nbOut);

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				Data<T> newData(nbFeatures, nbOut);
				newData.setFeaturesRandom();
				dataVector.setValueI(i, newData);
			}

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				Data<T>& data(dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					const T y(LinearRegression<T>::computeY(dataVector, paramMat, i, j));
					const T noiseFactor(Math::random(-noise, noise));
					data.setOut(j, y * ( T(1) + noiseFactor ));
				}
			}

			if ( verbose > 0 ) {
				Log::displayLog(String::format("Generated % data with %/% noise and the paramMat : %", nbData, noise * T(100), paramMat.toString()));
			}

			return dataVector;
		}

	}

}