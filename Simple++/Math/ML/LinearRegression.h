#pragma once

#include "../../IO/IO.h"
#include "../../Vector.h"
#include "../Math.h"
#include "../Mat.h"

#include "ActivationFunc.h"
#include "Data.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbOut>
		class LinearRegression : public IO::BasicIO {
		public:
			LinearRegression();

			void addData(const Data<T, NbFeatures, NbOut>& data);
			template<typename C>
			void addData(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ NbOut ]);
			void addData(const Vector<Data<T, NbFeatures, NbOut>>& dataVector);

			constexpr Size getNbFeatures() const;
			constexpr Size getNbParams() const;
			constexpr Size getNbOut() const;

			const Size getNbData() const;

			T computeY(const Size dataI, const Size outI) const;
			T computeCost() const;
			T computeCoefficientOfDetermination() const;
			T computeGrad(const Mat<T> & outMat, const Size paramI, const Size outI) const;
			void computeGradM(const Mat<T>& outMat, Mat<T>& m) const;

			void gradientDescent(const T& learningRate = T(0.01), const Size nbIterations = Size(100), int verbose = 2);

			static void setXMat(Mat<T>& x, const Vector<Data<T, NbFeatures, NbOut>>& dataVector);
			static void setParamMat(Mat<T>& paramMat);
			static T computeY(const Vector<Data<T, NbFeatures, NbOut>>& dataVector, const Mat<T>& paramMat, const Size dataI, const Size outI);

		private:
			void _updateXMat();

			Vector<Data<T, NbFeatures, NbOut>> dataVector;
			Mat<T> paramMat;		// Matrix of parameters of size [NbParams, NbOut].
			Mat<T> xMat;			// Matrix of input features of size [NbData, NbParams].

			bool bIsXMatUpdated;
		};

		template<typename T, Size NbFeatures, Size NbOut>
		Vector<Data<T, NbFeatures, NbOut>> generateData(const Size nbData, const T & noise = T(0.1), int verbose = 1);

		template<typename T, Size NbFeatures, Size NbOut>
		inline LinearRegression<T, NbFeatures, NbOut>::LinearRegression() :
			paramMat(NbFeatures + Size(1), NbOut),
			bIsXMatUpdated(false)
		{
			setParamMat(this->paramMat);
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::addData(const Data<T, NbFeatures, NbOut>&data) {

			if ( data.getNbFeatures() != getNbFeatures() ) {
				Log::displayError(String::format("Unable to add a data to the ML system. Number of features missmatch % (data) != % (system).", data.getNbFeatures(), getNbFeatures()));
				return;
			}
			if ( data.getNbOut() != getNbOut() ) {
				Log::displayError(String::format("Unable to add a data to the ML system. Number of out missmatch % (data) != % (system).", data.getNbOut(), getNbOut()));
				return;
			}

			this->dataVector.push(data);
			this->bIsXMatUpdated = false;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::addData(const Vector<Data<T, NbFeatures, NbOut>>& dataVector) {
			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				const Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(i));

				addData(data);
			}
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline constexpr Size LinearRegression<T, NbFeatures, NbOut>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline constexpr Size LinearRegression<T, NbFeatures, NbOut>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline constexpr Size LinearRegression<T, NbFeatures, NbOut>::getNbOut() const {
			return NbOut;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline const Size LinearRegression<T, NbFeatures, NbOut>::getNbData() const {
			return this->dataVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T LinearRegression<T, NbFeatures, NbOut>::computeY(const Size dataI, const Size outI) const {
			return LinearRegression<T, NbFeatures, NbOut>::computeY(this->dataVector, this->paramMat, dataI, outI);
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T LinearRegression<T, NbFeatures, NbOut>::computeCost() const {
			const T nbDataT(T(this->dataVector.getSize() * Size(2)));

			T ySum(0);
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T, NbFeatures, NbOut>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < getNbOut(); j++ ) {
					const T y(computeY(i, j) - data.getOut(j));
					ySum += y * y;
				}

			}

			return ySum / nbDataT;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T LinearRegression<T, NbFeatures, NbOut>::computeCoefficientOfDetermination() const {

			StaticTable<T, NbOut> meanVec;
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] = T(0);
			}
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T, NbFeatures, NbOut>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					meanVec[ j ] += data.getOut(j);
				}
			}
			const T sizeInverse(T(1) / T(getNbData()));
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] *= sizeInverse;
			}

			T errSum(0);
			T meanSum(0);
			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const Data<T, NbFeatures, NbOut>& data(this->dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					const T y(computeY(i, j));
					const T err(data.getOut(j) - y);
					const T mean(data.getOut(j) - meanVec[j]);

					errSum += err * err;
					meanSum += mean * mean;
				}
			}

			return T(1) - errSum / meanSum;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T LinearRegression<T, NbFeatures, NbOut>::computeGrad(const Mat<T>& outMat, const Size paramI, const Size outI) const {
			assert(outMat.getSizeM() == getNbData());
			assert(outMat.getSizeN() == getNbOut());
			assert(getNbParams() > paramI);
			assert(getNbOut() > outI);

			const T nbDataT(getNbData());

			T ySum(0);

			if ( paramI < getNbFeatures() ) {
				for ( Size dataI(0); dataI < this->dataVector.getSize(); dataI++ ) {
					const Data<T, NbFeatures, NbOut>& data(this->dataVector.getValueI(dataI));

					const T y(outMat.getValueI(dataI, outI) - data.getOut(outI));
					ySum += data.getFeature(paramI) * y;
				}
			} else {
				for ( Size dataI(0); dataI < this->dataVector.getSize(); dataI++ ) {
					const Data<T, NbFeatures, NbOut>& data(this->dataVector.getValueI(dataI));

					const T y(outMat.getValueI(dataI, outI) - data.getOut(outI));
					ySum += y;
				}
			}

			return ySum / nbDataT;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::computeGradM(const Mat<T>& outMat, Mat<T>& m) const {
			assert(this->nbParam == m.getSizeM());
			assert(this->NbOut == m.getSizeN());

			for ( Size i(0); i < m.getSizeM(); i++ ) {
				for ( Size j(0); j < m.getSizeN(); j++ ) {
					m.setValueI(i, j, computeGrad(outMat, i, j));
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::gradientDescent(const T& learningRate, const Size nbIterations, int verbose) {

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

			Mat<T> outMat(getNbData(), getNbOut());

			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				// Forward propagation.
				for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
					for ( Size outI(0); outI < getNbOut(); outI++ ) {
						outMat.setValueI(dataI, outI, computeY(dataI, outI));
					}
				}

				// Back propagation.
				for ( Size i(0); i < getNbParams(); i++ ) {
					for ( Size j(0); j < getNbOut(); j++ ) {
						T& param(this->paramMat.getValueI(i, j));

						param = param - learningRate * computeGrad(outMat, i, j);
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
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCost(), computeCoefficientOfDetermination() * T(100)));
				Log::displayLog(this->paramMat.toString());
			}
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::setXMat(Mat<T>& x, const Vector<Data<T, NbFeatures, NbOut>>& dataVector) {

			const Size newM(dataVector.getSize());
			constexpr Size newN(NbFeatures + Size(1));

			x.resizeNoCopy(newM, newN);

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				const Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbFeatures(); j++ ) {
					x.setValueI(i, j, data.getFeature(j));
				}
				for ( Size j(data.getNbFeatures()); j < newN; j++ ) {
					x.setValueI(i, j, T(1));
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::setParamMat(Mat<T>& paramMat) {
			paramMat.resizeNoCopy(NbFeatures + Size(1), NbOut);
			paramMat.randomF();
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T LinearRegression<T, NbFeatures, NbOut>::computeY(const Vector<Data<T, NbFeatures, NbOut>>& dataVector, const Mat<T>& paramMat, const Size dataI, const Size outI) {
			assert(dataVector.getSize() > dataI);
			assert(paramMat.getSizeN() > outI);

			const StaticTable<T, NbFeatures>& featureTable(dataVector.getValueI(dataI).getFeatures());

			T y(0);
			for ( Size paramI(0); paramI < featureTable.getSize(); paramI++ ) {
				const T& feature(featureTable[ paramI ]);
				const T& param(paramMat.getValueI(paramI, outI));

				y += feature * param;
			}
			for ( Size paramI(featureTable.getSize()); paramI < paramMat.getSizeM(); paramI++ ) {
				const T& param(paramMat.getValueI(paramI, outI));

				y += param;
			}
			return y;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void LinearRegression<T, NbFeatures, NbOut>::_updateXMat() {
			if ( !this->bIsXMatUpdated ) {
				setXMat(this->xMat, this->dataVector);

				this->bIsXMatUpdated = true;
			}
		}

		template<typename T, Size NbFeatures, Size NbOut>
		template<typename C>
		inline void LinearRegression<T, NbFeatures, NbOut>::addData(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ NbOut ]) {
			addData(Data<T, NbFeatures, NbOut>(featureTable, outTable));
		}

		template<typename T, Size NbFeatures, Size NbOut>
		Vector<Data<T, NbFeatures, NbOut>> generateData(const Size nbData, const T& noise, int verbose) {
			Vector<Data<T, NbFeatures, NbOut>> dataVector;
			dataVector.resize(nbData);

			static const ActivationFunc::Sigmoid activationFunc;

			Mat<T> paramMat;
			LinearRegression<T, NbFeatures, NbOut>::setParamMat(paramMat);

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				Data<T, NbFeatures, NbOut> newData;
				newData.setFeaturesRandom();
				dataVector.setValueI(i, newData);
			}

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					const T y(activationFunc(LinearRegression<T, NbFeatures, NbOut>::computeY(dataVector, paramMat, i, j)));
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