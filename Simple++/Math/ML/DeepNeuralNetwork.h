#pragma once

#include "ActivationFunc.h"
#include "NeuralLayer.h"

namespace Math {

	namespace ML {

		template<typename T>
		class Model {
		public:
			static constexpr Size nbLayers = 2;
			static constexpr Size m[ 2 ][ 2 ] = { {2,2}, {2,2} };
		};

		template<typename T, typename M = Model<T>, typename ActivationFunc = Math::ML::ActivationFunc::Sigmoid>
		class DeepNeuralNetwork {
		public:
			static constexpr Size NbFeatures = M::m[ 0 ][ 0 ];
			static constexpr Size NbOut = M::m[ M::nbLayers - Size(1) ][ 1 ];

			DeepNeuralNetwork();
			~DeepNeuralNetwork();

			void addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data);
			void addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector);

			const Size getNbData() const;

			template<Size I>
			const NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* getLayer() const;
			template<Size I>
			NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* getLayer();

			const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& computeForwardPropagation(const Size dataI);

			void computeBackPropagation();

			void optimize(const T& learningRate = T(0.01), const Size nbIterations = Size(1000), int verbose = 2);

			void updateModel(const T& learningRate = T(0.01));

			T computeCost() const;
			T computeCostQuadratic() const;
			T computeCoefficientOfDetermination() const;

		private:
			template<Size I = Size(0)>
			void _computeForwardPropagation(const Size dataI);

			template<Size I = M::nbLayers>
			void _computeBackPropagation();

			template<Size I = Size(0)>
			void _updateModel(const T& learningRate = T(0.01));

			template<Size I = Size(0)>
			void _constructNeuralLayer();

			template<Size I = Size(0)>
			void _destructNeuralLayer();

			template<Size I = Size(0)>
			constexpr bool _checkModel() const;

			template<Size I = Size(0)>
			void _addData();

			StaticTable<void*, M::nbLayers> layerTable;

			Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>> dataVector;
			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector;
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> expectedYVector;
		};

		template<typename T, typename M, typename ActivationFunc>
		inline DeepNeuralNetwork<T, M, ActivationFunc>::DeepNeuralNetwork() {
			static_assert( Utility::isBase<Model<T>, M>::value, "Model type unknown." );
			static_assert( M::nbLayers > Size(0), "Model error, nbLayers cannot be 0." );
			_checkModel<Size(1)>();
			_constructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M, typename ActivationFunc>
		inline DeepNeuralNetwork<T, M, ActivationFunc>::~DeepNeuralNetwork() {
			_destructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) {
			this->dataVector.push(data);
			this->featureVector.push(data.getFeatures());
			this->expectedYVector.push(data.getOuts());
			_addData<Size(0)>();
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				addData(dataVector.getValueI(dataI));
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		inline const Size DeepNeuralNetwork<T, M, ActivationFunc>::getNbData() const {
			return this->dataVector.getSize();
		}

		template<typename T, typename M, typename ActivationFunc>
		inline const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& DeepNeuralNetwork<T, M, ActivationFunc>::computeForwardPropagation(const Size dataI) {
			_computeForwardPropagation<Size(0)>(dataI);
			return getLayer< Size(0)>()->getOuts(dataI);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::computeBackPropagation() {
			return _computeBackPropagation<M::nbLayers - Size(1)>();
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::optimize(const T& learningRate, const Size nbIterations, int verbose) {
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
				for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
					computeForwardPropagation(dataI);
				}
				computeBackPropagation();
				updateModel(learningRate);

				if ( verbose > 1 ) {
					if ( ( iterationI + Size(1) ) % nbIterationsLog == Size(0) ) {
						Size progression(T(iterationI + Size(1)) / T(nbIterations - Size(1)) * T(100));
						Log::displayLog(String::format("[%/%] Finished loop with cost of %.", progression, computeCostQuadratic()), Log::MessageColor::DarkWhite);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCostQuadratic(), computeCoefficientOfDetermination() * T(100)));
				// Log::displayLog(this->paramMat.toString());
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::updateModel(const T& learningRate) {
			return _updateModel<Size(0)>(learningRate);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCost() const {
			const NeuralLayer<T, M::m[ M::nbLayers - Size(1) ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ], ActivationFunc>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			T ySum(0);
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(neuralLayer->getOuts(dataI));
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& expectedYTable(this->expectedYVector.getValueI(dataI));
				for ( Size outI(0); outI < neuralLayer->getNbNeurons(); outI++ ) {
					const T& expectedY(expectedYTable[ outI ]);
					const T& y(outTable[ outI ]);
					if constexpr ( false ) {
						Log::displayLog(String::format("computeCost(): outTable[%][%] = %", dataI, outI, outTable[ outI ]));
					}
					ySum += expectedY * Math::log(y) + ( T(1) - expectedY ) * Math::log(T(1) - y);
				}
			}

			return -ySum / T(getNbData());
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCostQuadratic() const {
			const NeuralLayer<T, M::m[ M::nbLayers - Size(1) ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ], ActivationFunc>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			T ySum(0);
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(neuralLayer->getOuts(dataI));
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& expectedYTable(this->expectedYVector.getValueI(dataI));
				for ( Size outI(0); outI < neuralLayer->getNbNeurons(); outI++ ) {
					const T& expectedY(expectedYTable[ outI ]);
					const T& y(outTable[ outI ]);
					const T delta(expectedY - y);
					ySum += delta * delta;
				}
			}

			return ySum / T(getNbData() * Size(2));
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCoefficientOfDetermination() const {
			const NeuralLayer<T, M::m[ M::nbLayers - Size(1) ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ], ActivationFunc>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			StaticTable<T, M::m[M::nbLayers - Size(1)][1]> meanVec;
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] = T(0);
			}
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& expectedTable(this->expectedYVector.getValueI(dataI));

				for ( Size outI(0); outI < meanVec.getSize(); outI++ ) {
					meanVec[outI] += expectedTable[ outI ];
				}
			}
			const T sizeInverse(T(1) / T(getNbData()));
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] *= sizeInverse;
			}

			T errSum(0);
			T meanSum(0);
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& expectedTable(this->expectedYVector.getValueI(dataI));
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(neuralLayer->getOuts(dataI));

				for ( Size outI(0); outI < outTable.getSize(); outI++ ) {
					const T y(outTable[outI]);
					const T expectedY(expectedTable[ outI ]);
					const T err(expectedY - y);
					const T mean(expectedY - meanVec[outI]);

					errSum += err * err;
					meanSum += mean * mean;
				}
			}

			return T(1) - errSum / meanSum;
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline const NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* DeepNeuralNetwork<T, M, ActivationFunc>::getLayer() const {
			return const_cast< DeepNeuralNetwork<T, M, ActivationFunc> * >( this )->getLayer<I>();
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* DeepNeuralNetwork<T, M, ActivationFunc>::getLayer() {
			return reinterpret_cast< NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* >( this->layerTable[ I ] );
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_computeForwardPropagation(const Size dataI) {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* neuralLayer(getLayer<I>());
				neuralLayer->computeForwardPropagation(dataI);

				if constexpr ( I == M::nbLayers - Size(1) && false ) {
					const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(neuralLayer->getOuts(dataI));
					for ( Size outI(0); outI < neuralLayer->getNbNeurons(); outI++ ) {
						Log::displayLog(String::format("_computeForwardPropagation(): outTable[%][%] = %", dataI, outI, outTable[ outI ]));
					}
				}

				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_computeBackPropagation() {
			if constexpr ( I >= Size(0) ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* neuralLayer(getLayer<I>());

				// Compute dZx
				if constexpr ( I == M::nbLayers - Size(1) ) {
					neuralLayer->computeDeltasLast(this->expectedYVector);
				} else {
					neuralLayer->computeDeltas(*getLayer<I + Size(1)>());
				}

				neuralLayer->computeBackPropagation();
			}
			if constexpr ( I > Size(0) ) {
				return _computeBackPropagation<I - Size(1)>();
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_updateModel(const T& learningRate) {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* neuralLayer(getLayer<I>());

				neuralLayer->updateModel(learningRate);

				return _updateModel<I + Size(1)>(learningRate);
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_constructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				const Vector<StaticTable<T, M::m[ I ][ 0 ]>>* inVector;
				if constexpr ( I == Size(0) ) {
					inVector = &this->featureVector;
				} else {
					inVector = &getLayer<I - Size(1)>()->getOutVector();
				}
				this->layerTable[ I ] = reinterpret_cast< void* >( new NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>(inVector) );
				_constructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_destructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				delete getLayer<I>();

				return _destructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline constexpr bool DeepNeuralNetwork<T, M, ActivationFunc>::_checkModel() const {
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

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_addData() {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* neuralLayer(getLayer<I>());
				neuralLayer->addData();
				_addData<I + Size(1)>();
			}
		}

	}

}