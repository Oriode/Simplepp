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

		template<typename T, typename M = Model<T>, typename Func = Math::ML::ActivationFunc::Sigmoid>
		class DeepNeuralNetwork {
		public:
			static constexpr Size NbFeatures = M::m[ 0 ][ 0 ];
			static constexpr Size NbOut = M::m[ M::nbLayers - Size(1) ][ 1 ];

			DeepNeuralNetwork();

			void addData(const Data<T>& data);
			void addData(const Vector<Data<T>>& dataVector);

			const Size getNbData() const;

			template<Size I>
			const NeuralLayer<T, Func>* getLayer() const;
			template<Size I>
			NeuralLayer<T, Func>* getLayer();

			const Vec<T>& computeForwardPropagation(const Size dataI);

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
			constexpr bool _checkModel() const;

			template<Size I = Size(0)>
			void _addData();

			StaticTable<NeuralLayer<T, Func>*, M::nbLayers> layerTable;

			Vector<Data<T>> dataVector;
			Vector<Vec<T>> featureVector;
			Vector<Vec<T>> expectedYVector;
		};

		template<typename T, typename M, typename Func>
		inline DeepNeuralNetwork<T, M, Func>::DeepNeuralNetwork() {
			static_assert( Utility::isBase<Model<T>, M>::value, "Model type unknown." );
			static_assert( M::nbLayers > Size(0), "Model error, nbLayers cannot be 0." );
			_checkModel<Size(1)>();
			_constructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M, typename Func>
		inline void DeepNeuralNetwork<T, M, Func>::addData(const Data<T>& data) {
			assert(data.getNbFeatures() == M::m[ 0 ][ 0 ]);
			assert(data.getNbOut() == M::m[ M::nbLayers - Size(1) ][ 1 ]);

			Vec<T> newFeatureTable(M::m[0][0]);
			Utility::copy(newFeatureTable.getData(), data.getFeatures().getData(), newFeatureTable.getSize());

			Vec<T> newExpectedYTable(M::m[ M::nbLayers - Size(1) ][ 1 ]);
			Utility::copy(newExpectedYTable.getData(), data.getOuts().getData(), newExpectedYTable.getSize());

			this->dataVector.push(data);
			this->featureVector.push(newFeatureTable);
			this->expectedYVector.push(newExpectedYTable);
			_addData<Size(0)>();
		}

		template<typename T, typename M, typename Func>
		inline void DeepNeuralNetwork<T, M, Func>::addData(const Vector<Data<T>>& dataVector) {
			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				addData(dataVector.getValueI(dataI));
			}
		}

		template<typename T, typename M, typename Func>
		inline const Size DeepNeuralNetwork<T, M, Func>::getNbData() const {
			return this->dataVector.getSize();
		}

		template<typename T, typename M, typename Func>
		inline const Vec<T>& DeepNeuralNetwork<T, M, Func>::computeForwardPropagation(const Size dataI) {
			_computeForwardPropagation<Size(0)>(dataI);
			return getLayer< Size(0)>()->getOuts(dataI);
		}

		template<typename T, typename M, typename Func>
		inline void DeepNeuralNetwork<T, M, Func>::computeBackPropagation() {
			return _computeBackPropagation<M::nbLayers - Size(1)>();
		}

		template<typename T, typename M, typename Func>
		inline void DeepNeuralNetwork<T, M, Func>::optimize(const T& learningRate, const Size nbIterations, int verbose) {
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

		template<typename T, typename M, typename Func>
		inline void DeepNeuralNetwork<T, M, Func>::updateModel(const T& learningRate) {
			return _updateModel<Size(0)>(learningRate);
		}

		template<typename T, typename M, typename Func>
		inline T DeepNeuralNetwork<T, M, Func>::computeCost() const {
			const NeuralLayer<T, Func>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			T ySum(0);
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const Vec<T>& outTable(neuralLayer->getOuts(dataI));
				const Vec<T>& expectedYTable(this->expectedYVector.getValueI(dataI));
				for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
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

		template<typename T, typename M, typename Func>
		inline T DeepNeuralNetwork<T, M, Func>::computeCostQuadratic() const {
			const NeuralLayer<T, Func>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			T ySum(0);
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const Vec<T>& outTable(neuralLayer->getOuts(dataI));
				const Vec<T>& expectedYTable(this->expectedYVector.getValueI(dataI));
				for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
					const T& expectedY(expectedYTable[ outI ]);
					const T& y(outTable[ outI ]);
					const T delta(expectedY - y);
					ySum += delta * delta;
				}
			}

			return ySum / T(getNbData() * Size(2));
		}

		template<typename T, typename M, typename Func>
		inline T DeepNeuralNetwork<T, M, Func>::computeCoefficientOfDetermination() const {
			const NeuralLayer<T, Func>* neuralLayer(getLayer<M::nbLayers - Size(1)>());

			Vec<T> meanVec(neuralLayer->getNbOut());
			for ( Size j(0); j < meanVec.getSize(); j++ ) {
				meanVec[ j ] = T(0);
			}
			for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
				const Vec<T>& expectedTable(this->expectedYVector.getValueI(dataI));

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
				const Vec<T>& expectedTable(this->expectedYVector.getValueI(dataI));
				const Vec<T>& outTable(neuralLayer->getOuts(dataI));

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

		template<typename T, typename M, typename Func>
		template<Size I>
		inline const NeuralLayer<T, Func>* DeepNeuralNetwork<T, M, Func>::getLayer() const {
			return const_cast< DeepNeuralNetwork<T, M, Func> * >( this )->getLayer<I>();
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline NeuralLayer<T, Func>* DeepNeuralNetwork<T, M, Func>::getLayer() {
			return this->layerTable[ I ];
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_computeForwardPropagation(const Size dataI) {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, Func>* neuralLayer(getLayer<I>());
				for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
					const Vec<T>& featureTable(neuralLayer->getIns(dataI));
					const T v(neuralLayer->computeY(outI, featureTable));
					neuralLayer->setOut(outI, dataI, v);
				}

				if constexpr ( I == M::nbLayers - Size(1) && false ) {
					const Vec<T>& outTable(neuralLayer->getOuts(dataI));
					for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
						Log::displayLog(String::format("_computeForwardPropagation(): outTable[%][%] = %", dataI, outI, outTable[ outI ]));
					}
				}

				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_computeBackPropagation() {
			if constexpr ( I >= Size(0) ) {
				NeuralLayer<T, Func>* neuralLayer(getLayer<I>());

				Vector<Vec<T>>& deltaVector(neuralLayer->getDeltaVector());
				const Vector<Vec<T>>& inVector(neuralLayer->getInVector());
				const Vector<Vec<T>>& outVector(neuralLayer->getOutVector());

				const T sizeInverse(T(1) / T(getNbData()));

				// Compute dZx
				if constexpr ( I == M::nbLayers - Size(1) ) {
					for ( Size dataI(0); dataI < this->dataVector.getSize(); dataI++ ) {
						const Vec<T>& outTable(outVector.getValueI(dataI));
						const Vec<T>& expectedYTable(this->expectedYVector.getValueI(dataI));
						Vec<T>& deltaVecTable(deltaVector.getValueI(dataI));
						for ( Size outI(0); outI < outTable.getSize(); outI++ ) {
							deltaVecTable[ outI ] = outTable[ outI ] - expectedYTable[ outI ];
						}
					}
				} else {
					NeuralLayer<T, Func>* nextNeuralLayer(getLayer<I + Size(1)>());

					for ( Size dataI(0); dataI < this->dataVector.getSize(); dataI++ ) {
						const Vec<T>& outTable(outVector.getValueI(dataI));
						const Vec<T>& nextDeltaVecTable(nextNeuralLayer->getDeltas(dataI));
						Vec<T>& deltaVecTable(deltaVector.getValueI(dataI));
						for ( Size outI(0); outI < deltaVecTable.getSize(); outI++ ) {
							const Func& activationFunc(neuralLayer->getActivationFunc(outI));
							T sum(0);
							for ( Size outINext(0); outINext < nextDeltaVecTable.getSize(); outINext++ ) {
								const Vec<T>& paramTable(nextNeuralLayer->getParams(outINext));
								sum += paramTable[ outI ] * nextDeltaVecTable[ outINext ];
							}
							deltaVecTable[ outI ] = activationFunc.grad(sum, outTable[outI]);
						}
					}
				}

				for ( Size featuresI(0); featuresI < neuralLayer->getNbFeatures(); featuresI++ ) {
					for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
						T ySum(0);

						for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
							const Vec<T>& delta(deltaVector.getValueI(dataI));
							const Vec<T>& inTable(inVector.getValueI(dataI));

							ySum += inTable[ featuresI ] * delta[ outI ];
						}
						ySum *= sizeInverse;
						neuralLayer->setGrad(outI, featuresI, ySum);
					}
				}
				for ( Size paramI(neuralLayer->getNbFeatures()); paramI < neuralLayer->getNbParams(); paramI++ ) {
					for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
						T ySum(0);

						for ( Size dataI(0); dataI < getNbData(); dataI++ ) {
							const Vec<T>& delta(deltaVector.getValueI(dataI));

							ySum += delta[ outI ];
						}
						ySum *= sizeInverse;
						neuralLayer->setGrad(outI, paramI, ySum);
					}
				}
			}
			if constexpr ( I > Size(0) ) {
				return _computeBackPropagation<I - Size(1)>();
			}
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_updateModel(const T& learningRate) {
			if constexpr ( I < M::nbLayers ) {
				NeuralLayer<T, Func>* neuralLayer(getLayer<I>());

				for ( Size outI(0); outI < neuralLayer->getNbOut(); outI++ ) {
					for ( Size paramI(0); paramI < neuralLayer->getNbParams(); paramI++ ) {
						const T& grad(neuralLayer->getGrad(outI, paramI));
						neuralLayer->setParam(outI, paramI, neuralLayer->getParam(outI, paramI) - learningRate * grad);
					}
				}

				return _updateModel<I + Size(1)>(learningRate);
			}
		}

		template<typename T, typename M, typename Func>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, Func>::_constructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				const Vector<Vec<T>>* inVector;
				if constexpr ( I == Size(0) ) {
					inVector = &this->featureVector;
				} else {
					inVector = &getLayer<I - Size(1)>()->getOutVector();
				}
				this->layerTable[ I ] = new NeuralLayer<T, Func>(M::m[I][0], M::m[I][1], inVector);
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
				NeuralLayer<T, Func>* neuralLayer(getLayer<I>());
				neuralLayer->addData();
				_addData<I + Size(1)>();
			}
		}

	}

}