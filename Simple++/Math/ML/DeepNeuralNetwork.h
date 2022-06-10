#pragma once

#include "../Interval.h"
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

			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval);
			const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& computeForwardPropagation(const Size dataI);
			void computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const;

			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);

			void optimize(const T& learningRate, const Size nbIterations, int verbose = 2);
			void optimize(const Math::Interval<Size>& dataIInterval, const T& learningRate, const Size nbIterations, int verbose = 2);
			void optimize(const Math::Interval<Size>& dataIInterval, const T& learningRate);

			void updateModel(const T& learningRate = T(0.01));

			T computeCostLog(const Math::Interval<Size>& dataIInterval);
			T computeCostLog();
			T computeCostQuadratic(const Math::Interval<Size>& dataIInterval);
			T computeCostQuadratic();
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval);
			T computeCoefficientOfDetermination();

		private:
			template<Size I = Size(0)>
			void _computeForwardPropagation(const Size dataI);

			template<Size I = Size(0)>
			void _computeForwardPropagation(const StaticTable<T, M::m[ I ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]> & outTableFinal) const;

			template<Size I = M::nbLayers>
			void _computeBackPropagation(const Math::Interval<Size> & dataIInterval);

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

			bool bNeedForwardPropagation;
		};

		template<typename T, typename M, typename ActivationFunc>
		inline DeepNeuralNetwork<T, M, ActivationFunc>::DeepNeuralNetwork() :
			bNeedForwardPropagation(true)
		{
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
			this->bNeedForwardPropagation = true;
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
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval) {
			if ( this->bNeedForwardPropagation ) {
				for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
					computeForwardPropagation(dataI);
				}
				this->bNeedForwardPropagation = false;
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		inline const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& DeepNeuralNetwork<T, M, ActivationFunc>::computeForwardPropagation(const Size dataI) {
			_computeForwardPropagation<Size(0)>(dataI);
			this->bNeedForwardPropagation = false;
			return getLayer< Size(0)>()->getOuts(dataI);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const {
			const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(data.getFeatures());
			StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(data.getOuts());
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			return _computeBackPropagation<M::nbLayers - Size(1)>(dataIInterval);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::optimize(const T& learningRate, const Size nbIterations, int verbose) {
			return optimize(Interval<Size>(Size(0), getNbData()), learningRate, nbIterations, verbose);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::optimize(const Math::Interval<Size>& dataIInterval, const T& learningRate, const Size nbIterations, int verbose) {
			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting gradient descent with % iterations over % data...", nbIterations, dataIInterval.toString()));
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
				optimize(dataIInterval, learningRate);

				if ( verbose > 1 ) {
					if ( ( iterationI + Size(1) ) % nbIterationsLog == Size(0) ) {
						Size progression(T(iterationI + Size(1)) / T(nbIterations - Size(1)) * T(100));
						Log::displayLog(String::format("[%/%] Finished loop with cost of %.", progression, computeCostQuadratic(dataIInterval)), Log::MessageColor::DarkWhite);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)));
				// Log::displayLog(this->paramMat.toString());
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::optimize(const Math::Interval<Size>& dataIInterval, const T& learningRate) {
			computeForwardPropagation(dataIInterval);
			computeBackPropagation(dataIInterval);
			updateModel(learningRate);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::updateModel(const T& learningRate) {
			_updateModel<Size(0)>(learningRate);
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCostLog(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCostLog(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCostLog() {
			return computeCostLog(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCostQuadratic(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCostQuadratic(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCostQuadratic() {
			return computeCostQuadratic(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCoefficientOfDetermination(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, typename ActivationFunc>
		inline T DeepNeuralNetwork<T, M, ActivationFunc>::computeCoefficientOfDetermination() {
			return computeCoefficientOfDetermination(Interval<Size>(Size(0), getNbData()));
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
				getLayer<I>()->computeForwardPropagation(dataI);

				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_computeForwardPropagation(const StaticTable<T, M::m[ I ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTableFinal) const {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I < M::nbLayers - Size(1) ) {
					StaticTable<T, M::m[ I ][ 1 ]> outTable;
					getLayer<I>()->computeForwardPropagation(featureTable, outTable);
					return _computeForwardPropagation(outTable, outTableFinal);
				} else {
					getLayer<I>()->computeForwardPropagation(featureTable, outTableFinal);
				}
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			if constexpr ( I >= Size(0) ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], ActivationFunc>* neuralLayer(getLayer<I>());

				// Compute dZx
				if constexpr ( I == M::nbLayers - Size(1) ) {
					neuralLayer->computeDeltasLast(dataIInterval, this->expectedYVector);
				} else {
					neuralLayer->computeDeltas(dataIInterval , *getLayer<I + Size(1)>());
				}

				neuralLayer->computeBackPropagation(dataIInterval);
			}
			if constexpr ( I > Size(0) ) {
				return _computeBackPropagation<I - Size(1)>(dataIInterval);
			}
		}

		template<typename T, typename M, typename ActivationFunc>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, ActivationFunc>::_updateModel(const T& learningRate) {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->updateModel(learningRate);

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