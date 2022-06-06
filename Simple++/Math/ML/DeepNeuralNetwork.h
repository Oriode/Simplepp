#pragma once

#include "NeuralLayer.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbOut, typename Func>
		class DeepNeuralNetwork {
		public:
			DeepNeuralNetwork(const Size nbLayers);

			const Size getNbData() const;

			T computeGrad(const StaticTable<T, NbOut> & forwardPropagation, const Size layerI, const Size neurodeI, const Size paramI) const;

		private:
			const Size nbLayers;

			NeuralLayer<T, NbFeatures, NbFeatures, Func> layer1;
			NeuralLayer<T, NbFeatures, NbOut, Func> layer2;

			Vector<Data<T>> dataVector;
		};

		template<typename T, Size NbFeatures, Size NbOut, typename Func>
		inline DeepNeuralNetwork<T, NbFeatures, NbOut, Func>::DeepNeuralNetwork(const Size nbLayers) :
			nbLayers(nbLayers)
		{}

		template<typename T, Size NbFeatures, Size NbOut, typename Func>
		inline const Size DeepNeuralNetwork<T, NbFeatures, NbOut, Func>::getNbData() const {
			return this->dataVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbOut, typename Func>
		inline T DeepNeuralNetwork<T, NbFeatures, NbOut, Func>::computeGrad(const StaticTable<T, NbOut>& forwardPropagation, const Size layerI, const Size neurodeI, const Size paramI) const {
			assert(this->nbLayers > layerI);

			Vec<T> dVec(this->dataVector.getSize());

			// If we are computing the last layer.
			if ( layerI + Size(1) == this->nbLayers ) {
				T ySum(0);

				if ( paramI < this->layer2.getNbFeatures() ) {
					for ( Size i(0); i < getNbData(); i++ ) {
						const StaticTable<T, NbFeatures>& dataX(getFeatures(i));
						const T& dataY(getOut(i));

						const T y(computeY(i) - dataY);
						ySum += dataX[ paramI ] * y;
					}
				} else {
					for ( Size i(0); i < this->inputVector.getSize(); i++ ) {
						const T& dataY(getOut(i));

						const T y(computeY(i) - dataY);
						ySum += y;
					}
				}
			}
		}

	}

}