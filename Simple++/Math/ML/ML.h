#pragma once

#include "DeepNeuralNetwork.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbOut>
		Vector<Data<T, NbFeatures, NbOut>> generateData(const Size nbData, const T& noise = T(0.1), int verbose = 1);

		template<typename T, Size NbFeatures, Size NbOut>
		Vector<Data<T, NbFeatures, NbOut>> generateData(const Size nbData, const T& noise, int verbose) {
			static const ActivationFunc::Sigmoid activationFunc;

			Vector<Data<T, NbFeatures, NbOut>> dataVector(nbData);

			Mat<T> paramMat(NbFeatures + Size(1), NbOut);
			paramMat.randomF();

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				Data<T, NbFeatures, NbOut> newData;
				newData.setFeaturesRandom();
				dataVector.setValueI(i, newData);
			}

			for ( Size i(0); i < dataVector.getSize(); i++ ) {
				Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(i));

				for ( Size j(0); j < data.getNbOut(); j++ ) {
					const StaticTable<T, NbFeatures + Size(1)>& paramTable(*StaticTable<T, NbFeatures + Size(1)>::reinterpret(paramMat.getDataM(j)));
					const T y(Neuron<T, NbFeatures, ActivationFunc::Sigmoid>::computeY(data.getFeatures(), paramTable, activationFunc));
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