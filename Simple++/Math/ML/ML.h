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

			Mat<T> paramMat(NbOut, NbFeatures + Size(1));

			// First layer.
			{
				paramMat.randomF();

				for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
					Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(dataI));

					for ( Size outI(0); outI < data.getNbOut(); outI++ ) {
						const StaticTable<T, NbFeatures + Size(1)>& paramTable(*StaticTable<T, NbFeatures + Size(1)>::reinterpret(paramMat.getDataM(outI)));
						const T y(Neuron<T, NbFeatures, ActivationFunc>::computeY(data.getFeatures(), paramTable, activationFunc));
						data.setOut(outI, y);
					}
				}
			}

			// Other layers.
			paramMat.resize(NbOut, NbOut + Size(1));

			for ( Size layerI(1); layerI < NbLayers; layerI++ ) {
				paramMat.randomF();

				for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
					Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(dataI));
					const StaticTable<T, NbOut> featureTable(data.getOuts());

					for ( Size outI(0); outI < NbOut; outI++ ) {
						const StaticTable<T, NbOut + Size(1)>& paramTable(*StaticTable<T, NbOut + Size(1)>::reinterpret(paramMat.getDataM(outI)));
						const T y(Neuron<T, NbOut, ActivationFunc>::computeY(featureTable, paramTable, activationFunc));
						data.setOut(outI, y);
					}
				}
			}

			// Compute the min/max for every out.
			StaticTable<Math::Interval<T>, NbOut> minMaxTable;

			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(dataI));

				for ( Size outI(0); outI < NbOut; outI++ ) {
					const T& v(data.getOut(outI));
					Math::Interval<T>& minMax(minMaxTable[ outI ]);

					if ( dataI == Size(0) ) {
						minMax.setBegin(v);
						minMax.setEnd(v);
					} else {
						if ( v > minMax.getEnd() ) {
							minMax.setEnd(v);
						} else if ( v < minMax.getBegin() ) {
							minMax.setBegin(v);
						}
					}
				}
			}

			// Scale and apply noise for every out.
			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				Data<T, NbFeatures, NbOut>& data(dataVector.getValueI(dataI));

				for ( Size outI(0); outI < NbOut; outI++ ) {
					const T& v(data.getOut(outI));
					Math::Interval<T>& minMax(minMaxTable[ outI ]);

					const T noiseFactor(Math::random(-noise, noise));
					const T vScaled(minMax.scale(v));
					const T yNoise(vScaled * ( T(1) + noiseFactor ));

					data.setOut(outI, yNoise);
				}
			}

			if ( verbose > 0 ) {
				Log::displayLog(String::format("Generated % data [% => %] with %/% noise over % layers.", nbData, NbFeatures, NbOut, noise * T(100), NbLayers));
			}

			return dataVector;
		}

		template<typename M, Size I = Size(0)>
		constexpr Size getNbFeatures() {
			return M::m[ I ][ 0 ];
		}

		template<typename M, Size I = M::nbLayers - Size(1)>
		constexpr Size getNbOut() {
			return M::m[ I ][ 1 ];
		}

	}

}