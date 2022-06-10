#pragma once

#include "DeepNeuralNetwork.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbOut, Size NbLayers = Size(1), typename ActivationFunc = ActivationFunc::Linear>
		Vector<Data<T, NbFeatures, NbOut>> generateData(const Size nbData, const T& noise = T(0.1), int verbose = 1);

		template<typename T, Size NbFeatures, Size NbOut, Size NbLayers, typename ActivationFunc>
		Vector<Data<T, NbFeatures, NbOut>> generateData(const Size nbData, const T& noise, int verbose) {
			const ActivationFunc activationFunc;

			Vector<Data<T, NbFeatures, NbOut>> dataVector(nbData);

			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				Data<T, NbFeatures, NbOut> newData;
				newData.setFeaturesRandom();
				dataVector.setValueI(dataI, newData);
			}

			// First layer.
			{
				Mat<T> paramMat(NbFeatures + Size(1), NbOut);
				paramMat.randomF();

				for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
					Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(dataI));

					for ( Size outI(0); outI < data.getNbOut(); outI++ ) {
						const StaticTable<T, NbFeatures + Size(1)>& paramTable(*StaticTable<T, NbFeatures + Size(1)>::reinterpret(paramMat.getDataM(outI)));

						const T y(Neuron<T, NbFeatures, ActivationFunc>::computeY(data.getFeatures(), paramTable, activationFunc));
						const T noiseFactor(Math::random(-noise, noise));
						const T yNoise(y * ( T(1) + noiseFactor ));

						data.setOut(outI, yNoise);
					}
				}
			}

			// Other layers.
			for ( Size layerI(1); layerI < NbLayers; layerI++ ) {
				Mat<T> paramMat(NbOut, NbOut);
				paramMat.randomF();

				for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
					Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(dataI));
					const StaticTable<T, NbOut> featureTable(data.getOuts());

					for ( Size outI(0); outI < NbOut; outI++ ) {
						const StaticTable<T, NbOut + Size(1)>& paramTable(*StaticTable<T, NbOut + Size(1)>::reinterpret(paramMat.getDataM(outI)));

						const T y(Neuron<T, NbOut, ActivationFunc>::computeY(featureTable, paramTable, activationFunc));
						const T noiseFactor(Math::random(-noise, noise));
						const T yNoise(y * ( T(1) + noiseFactor ));

						data.setOut(outI, yNoise);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::displayLog(String::format("Generated % data [% => %] with %/% noise over % layers.", nbData, NbFeatures, NbOut, noise * T(100), NbLayers));
			}

			return dataVector;
		}

	}

}