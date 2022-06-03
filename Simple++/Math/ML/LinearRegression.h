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

			const Size getNbFeatures() const;
			const Size getNbParams() const;

			T computeY(const Size m, const Size n) const;
			T computeCost() const;
			T computeCoeficientOfDetermination() const;
			T computeGrad(const Size m, const Size n) const;
			void computeGradM(Mat<T>& m) const;

			void gradientDescent(const T& learningRate = T(0.01), const Size nbIterations = Size(100));

			static void setXMat(Mat<T>& x, const Vector<Data<T>>& dataVector, const Size nbParams);
			static void setParamMat(Mat<T>& paramMat, const Size nbParams, const Size nbOut);

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
		Vector<Data<T>> generateData(const Size nbFeatures, const Size nbOut, const Size nbParams);

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
		inline const Size LinearRegression<T>::getNbFeatures() const {
			return this->nbFeatures;
		}

		template<typename T>
		inline const Size LinearRegression<T>::getNbParams() const {
			return this->nbParams;
		}

		template<typename T>
		inline T LinearRegression<T>::computeY(const Size m, const Size n) const {
			assert(this->dataVector.getSize() > m);
			assert(this->NbOut > n);

			const BasicVector<T>& featureTable(this->dataVector.getValueI(m).getFeatures());

			T y(0);
			for ( Size i(0); i < featureTable.getSize(); i++ ) {
				const T& feature(featureTable.getValueI(i));
				const T& param(this->paramMat.getValueI(i, n));

				y += feature * param;
			}
			for ( Size i(featureTable.getSize()); i < this->paramMat.getSizeM(); i++ ) {
				const T& param(this->paramMat.getValueI(i, n));

				y += param;
			}
			return y;
		}

		template<typename T>
		inline T LinearRegression<T>::computeCost() const {
			const T nbDataT(T(this->dataVector.getSize() * Size(2)));

			T ySum(0);
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < this->nbOut; j++ ) {
					const T y(computeY(i, j) - data.getOuts().getValueI(j));
				}

				ySum += y * y;
			}

			return T(1) / nbDataT * ySum;
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
			assert(this->nbParam > m);
			assert(this->NbOut > n);

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

			return T(1) / nbDataT * ySum;
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
		inline void LinearRegression<T>::gradientDescent(const T& learningRate, const Size nbIterations) {

			Log::startStep(String::format("Starting gradient descent with % iterations...", nbIterations));

			for ( Size iterationI(0); iterationI < nbIterations; i++ ) {
				for ( Size i(0); i < this->paramMat.getSizeM(); i++ ) {
					for ( Size j(0); j < this->paramMat.getSizeN(); j++ ) {
						T& param(this->paramMat.getValueI(i, j));

						param = param - learningRate * computeGrad(i, j);
					}
				}
			}

			Log::endStep(String::format("Finished with a cost of %.", computeCost()));
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

	}

}