#pragma once

#include "NeuralLayer.h"

namespace Math {

	namespace ML {

		template<typename T>
		class Model {
		public:
			static constexpr Size nbLayers = 2;
			static constexpr Size m[ 2 ][ 2 ] = { {2,2}, {2,2} };
		};

		template<typename T, typename M = Model<T>, typename Func = Math::Operations::Identity>
		class DeepNeuralNetwork {
		public:
			DeepNeuralNetwork();

			void addData(const Data<T>& data);

			const Size getNbData() const;

			template<Size I>
			NeuralLayer<T, M::m[I][0], M::m[ I ][ 1 ], Func>* getLayer();

			const StaticTable<T, M::m[M::nbLayers - Size(1)][1]>& computeForwardPropagation(const Size dataI);

			T computeBackPropagation(const T& learningRate = T(0.01)) const;

		private:
			template<Size I>
			void _computeForwardPropagation(const Size dataI);

			template<Size I>
			void _constructNeuralLayer();

			template<Size I>
			constexpr bool _checkModel() const;

			template<Size I>
			void _addData();

			StaticTable<void*, M::nbLayers> layerTable;

			Vector<Data<T>> dataVector;
			Vector<StaticTable<T, M::m[0][0]>> featureVector;
			Vector<StaticTable<T, M::m[M::nbLayers - Size(1)][1]>> expectedYVector;
		};

		template<typename T, typename M, typename Func>
		inline DeepNeuralNetwork<T, M, Func>::DeepNeuralNetwork()
		{
			static_assert( Utility::isBase<Model<T>, M>::value, "Model type unknown." );
			static_assert( M::nbLayers > Size(0), "Model error, nbLayers cannot be 0." );
			_checkModel<Size(1)>();
			_constructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M, typename Func>
		inline void DeepNeuralNetwork<T, M, Func>::addData(const Data<T>& data) {
			assert(data.getNbFeatures() == M::m[ 0 ][ 0 ]);

			StaticTable<T, M::m[ 0 ][ 0 ]> newFeatureTable;
			Utility::copy(newFeatureTable.getData(), data.getFeatures().getData(), newFeatureTable.getSize());

			StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]> newExpectedYTable;
			Utility::copy(newExpectedYTable.getData(), data.getOuts().getData(), newExpectedYTable.getSize());

			this->dataVector.push(data);
			this->featureVector.push(newFeatureTable);
			this->expectedYVector.push(newExpectedYTable);
			_addData<Size(0)>();
		}

		template<typename T, typename M, typename Func>
		inline const Size DeepNeuralNetwork<T, M, Func>::getNbData() const {
			return this->dataVector.getSize();
		}

		template<typename T, typename M, typename Func>
		inline const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& DeepNeuralNetwork<T, M, Func>::computeForwardPropagation(const Size dataI) {

			NeuralLayer<T, M::m[ 0 ][ 0 ], M::m[ 0 ][ 1 ], Func>* neuralLayer(getLayer<0>());
			for ( Size i(0); i < neuralLayer->getNbOut(); i++ ) {
				const StaticTable<T, M::m[ 0 ][ 0 ]>& featureVector(this->featureVector.getValueI(dataI));
				const T v(neuralLayer->computeY(i, featureVector));
				neuralLayer->setOut(i, dataI, v);
			}

			_computeForwardPropagation<Size(1)>(dataI);
			return getLayer< M::nbLayers - Size(1)>()->getOuts(dataI);
		}

		template<typename T, typename M, typename Func>
		inline T DeepNeuralNetwork<T, M, Func>::computeBackPropagation(const T& learningRate) const {
			NeuralLayer<T, M::m[ M::nbLayers - Size(1) ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ], Func>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			for ( Size i(0); i < this->dataVector.getSize(); i++ ) {
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(neuralLayer->getOuts(i));
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& expectedYTable(this->expectedYVector.getValueI(i));
				StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& deltaVecTable(neuralLayer->getDeltas(i));
				for ( Size j(0); j < outTable.getSize(); j++ ) {
					deltaVecTable[ j ] = outTable[ j ] - expectedYTable[j];
				}
			}

			for ( Size i(0); i < neuralLayer->getNbFeatures(); i++ ) {
				for ( Size j(0); j < neuralLayer->getNbOut(); j++ ) {
					T ySum(0);

					for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
						const StaticTable < T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& delta(neuralLayer->getDeltas(dataI));
						const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 0 ]>& inTable(neuralLayer->getIns(dataI));

						ySum += inTable[i] * delta;
					}
					ySum /= T(this->dataVector.getSize());
					neuralLayer->setParam(j, i, neuralLayer->getParam(j, i) + learningRate * ySum);
				}
			}
			for ( Size i(neuralLayer->getNbFeatures()); i < neuralLayer->getNbParams(); i++ ) {
				for ( Size j(0); j < neuralLayer->getNbOut(); j++ ) {
					T ySum(0);

					for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
						const StaticTable < T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& delta(neuralLayer->getDeltas(dataI));

						ySum += delta;
					}
					ySum /= T(this->dataVector.getSize());
					neuralLayer->setParam(j, i, neuralLayer->getParam(j, i) + learningRate * ySum);
				}
			}
			// TODO: Finish.
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], Func>* DeepNeuralNetwork<T, M, Func>::getLayer() {
			return reinterpret_cast< NeuralLayer<T, M::m[I][0], M::m[I][1], Func>* >( this->layerTable[I] );
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_computeForwardPropagation(const Size dataI) {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], Func>* neuralLayer(getLayer<I>());
				NeuralLayer<T, M::m[ I - Size(1)][0], M::m[I - Size(1)][1], Func>* lastNeuralLayer(getLayer<I - Size(1)>());
				for ( Size i(0); i < neuralLayer->getNbOut(); i++ ) {
					const StaticTable<T, M::m[ I - Size(1) ][ 1 ]>& featureVector(lastNeuralLayer->getOuts(dataI));
					const T v(neuralLayer->computeY(i, featureVector));
					neuralLayer->setOut(i, dataI, v);
				}
			
				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_constructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				const Vector<StaticTable<T, M::m[ I ][ 0 ]>>* inVector;
				if constexpr ( I == Size(0) ) {
					inVector = &this->featureVector;
				} else {
					inVector = &getLayer<I - Size(1)>()->getInVector();
				}
				this->layerTable[ I ] = reinterpret_cast< void* >( new NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], Func>(inVector) );
				_constructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline constexpr bool DeepNeuralNetwork<T, M, Func>::_checkModel() const {
			if constexpr ( I < M::nbLayers ) {

				if ( M::m[ I - Size(1) ][ 1 ] != M::m[ I ][ 0 ] ) {
					Log::displayError(String::format("Layer % output != layer % input.", I - Size(1), I));
					return false;
				}

				return _checkModel<I + Size(1)>();
			} else {
				return true;
			}
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_addData() {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], Func>* neuralLayer(getLayer<I>());
				neuralLayer->addData();
				_addData<I + Size(1)>();
			}
		}

	}

}