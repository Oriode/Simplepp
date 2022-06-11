#pragma once

#include "../../Time/Time.h"
#include "../Interval.h"
#include "LearningRate.h"
#include "ActivationFunc.h"
#include "NeuralLayer.h"

namespace Math {

	namespace ML {

		class Model {
		public:
			constexpr Model() {};

			///@brief Number of layers of the network.
			static constexpr Size nbLayers = 2;

			///@brief Table [nbLayers][2] representing for each layer the number of input (features) and output (neurons). The number of input of a layer should fit the number of output of the previous one.
			static constexpr Size m[ 2 ][ 2 ] = { 
				{2,2},	// {NbIn, NbOut}
				{2,2}	// {NbIn, NbOut}
			};

			///@brief Type of the activation function of the hidden layers.
			typedef Math::ML::ActivationFunc::ReLU HiddenActivationFunc;
			///@brief Type of the activation function of the last layer.
			typedef Math::ML::ActivationFunc::Linear ActivationFunc;
		};

		template<typename T, typename M = Model>
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
			const NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>* getLayer() const;
			template<Size I>
			NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>* getLayer();

			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval);
			const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& computeForwardPropagation(const Size dataI);
			void computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const;

			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);

			const Size getEpoch() const;

			void setParamRandom();

			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const LearningRateFunc & learningRateFunc, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Time::Duration<Time::MilliSecond> & saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc);

			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void updateModel(const LearningRateFunc& learningRateFunc = LearningRateFunc(0.01), const T& learningRateFactor = T(1.0));

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

			template<Size I = Size(0), typename LearningRateFunc = LearningRate::Constant<T>>
			void _updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor);

			template<Size I = Size(0)>
			void _constructNeuralLayer();

			template<Size I = Size(0)>
			void _destructNeuralLayer();

			template<Size I = Size(0)>
			constexpr bool _checkModel() const;

			template<Size I = Size(0)>
			void _setNbData();

			template<Size I = Size(0)>
			void _setParamRandom();

			StaticTable<void*, M::nbLayers> layerTable;

			Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>> dataVector;
			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector;
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> expectedYVector;

			bool bNeedForwardPropagation;

			typename M::HiddenActivationFunc hiddenActivationFunc;
			typename M::ActivationFunc activationFunc;

			Size epoch;
			T learningRateFactor;
		};

		template<typename T, typename M>
		inline DeepNeuralNetwork<T, M>::DeepNeuralNetwork() :
			bNeedForwardPropagation(true),
			epoch(0),
			learningRateFactor(1.0)
		{
			static_assert( Utility::isBase<Model, M>::value, "Model type unknown." );
			static_assert( Utility::isBase<ActivationFunc::BasicActivationFunc, M::ActivationFunc>::value, "Model ActivationFunc type unknown." );
			static_assert( Utility::isBase<ActivationFunc::BasicActivationFunc, M::HiddenActivationFunc>::value, "Model HiddenActivationFunc type unknown." );
			static_assert( M::nbLayers > Size(0), "Model error, nbLayers cannot be 0." );
			_checkModel<Size(1)>();
			_constructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M>
		inline DeepNeuralNetwork<T, M>::~DeepNeuralNetwork() {
			_destructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) {
			this->dataVector.push(data);
			this->featureVector.push(data.getFeatures());
			this->expectedYVector.push(data.getOuts());
			_setNbData<Size(0)>();
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data(dataVector.getValueI(dataI));
				this->dataVector.push(data);
				this->featureVector.push(data.getFeatures());
				this->expectedYVector.push(data.getOuts());
			}
			_setNbData<Size(0)>();
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M>
		inline const Size DeepNeuralNetwork<T, M>::getNbData() const {
			return this->dataVector.getSize();
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval) {
			if ( this->bNeedForwardPropagation ) {
				for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
					computeForwardPropagation(dataI);
				}
				this->bNeedForwardPropagation = false;
			}
		}

		template<typename T, typename M>
		inline const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& DeepNeuralNetwork<T, M>::computeForwardPropagation(const Size dataI) {
			_computeForwardPropagation<Size(0)>(dataI);
			this->bNeedForwardPropagation = false;
			return getLayer< M::nbLayers - Size(1)>()->getOuts(dataI);
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const {
			const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(data.getFeatures());
			StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(data.getOuts());
			_computeForwardPropagation<Size(0)>(featureTable, outTable);
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			return _computeBackPropagation<M::nbLayers - Size(1)>(dataIInterval);
		}

		template<typename T, typename M>
		inline const Size DeepNeuralNetwork<T, M>::getEpoch() const {
			return this->epoch;
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::setParamRandom() {
			_setParamRandom<Size(0)>();
		}

		template<typename T, typename M>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::optimize(const LearningRateFunc& learningRateFunc, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration, int verbose) {
			return optimize(Interval<Size>(Size(0), getNbData()), learningRateFunc, nbIterations, saveDuration, verbose);
		}

		template<typename T, typename M>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration, int verbose) {
			class GetPercent {
			public:
				GetPercent(const Size nbIterations) :
					nbIterations(nbIterations) {}

				Size operator()(const Size iterationI) const {
					return Size(T(iterationI + Size(1)) / T(this->nbIterations - Size(1)) * T(100));
				}

				const Size nbIterations;
			};

			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting gradient descent with % iterations over % data...", nbIterations, dataIInterval.toString()));
			}

			const GetPercent getPercent(nbIterations);

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLastLog(timePointBegin.getValue());

			if ( getEpoch() == Size(0) ) {
				Log::startStep("Starting from epoch #0, randomizing params...");
				setParamRandom();
				this->learningRateFactor = T(1.0);
				Log::endStep("Done.");
			}

			T lastCost(computeCostQuadratic());

			if ( verbose > 0 ) {
				Log::displayLog(String::format("Initial quadratic cost : %.", lastCost));
			}

			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				optimize(dataIInterval, learningRateFunc);

				T newCost(computeCostQuadratic());
				if ( newCost > lastCost ) {
					this->learningRateFactor /= T(2.0);

					if ( verbose > 1 ) {
						Log::displayWarning(String::format("[%/%] epoch #% : New cost higher than the previous one.", getPercent(iterationI), getEpoch()));
					}
				}
				lastCost = newCost;

				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				if ( timePointNow - timePointLastLog > saveDuration ) {
					timePointLastLog.setValue(timePointNow.getValue());
					if ( verbose > 1 ) {
						Log::displayLog(String::format("[%/%] epoch #% : Finished loop with cost of % and a coeficient of determination of %%.", getPercent(iterationI), getEpoch(), computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)), Log::MessageColor::DarkWhite);
					}
				}
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)));
				// Log::displayLog(this->paramMat.toString());
			}
		}

		template<typename T, typename M>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc) {
			computeForwardPropagation(dataIInterval);
			computeBackPropagation(dataIInterval);
			updateModel(learningRateFunc, this->learningRateFactor);
		}

		template<typename T, typename M>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor) {
			_updateModel<Size(0)>(learningRateFunc, learningRateFactor);
			this->epoch++;
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M>
		inline T DeepNeuralNetwork<T, M>::computeCostLog(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCostLog(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M>
		inline T DeepNeuralNetwork<T, M>::computeCostLog() {
			return computeCostLog(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M>
		inline T DeepNeuralNetwork<T, M>::computeCostQuadratic(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCostQuadratic(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M>
		inline T DeepNeuralNetwork<T, M>::computeCostQuadratic() {
			return computeCostQuadratic(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M>
		inline T DeepNeuralNetwork<T, M>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCoefficientOfDetermination(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M>
		inline T DeepNeuralNetwork<T, M>::computeCoefficientOfDetermination() {
			return computeCoefficientOfDetermination(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M>
		template<Size I>
		inline const NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>* DeepNeuralNetwork<T, M>::getLayer() const {
			return const_cast< DeepNeuralNetwork<T, M> * >( this )->getLayer<I>();
		}

		template<typename T, typename M>
		template<Size I>
		inline NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>* DeepNeuralNetwork<T, M>::getLayer() {
			return reinterpret_cast< NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>* >( this->layerTable[ I ] );
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_computeForwardPropagation(const Size dataI) {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I == M::nbLayers - Size(1) ) {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(dataI, this->activationFunc);
				} else {
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(dataI, this->hiddenActivationFunc);
				}

				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_computeForwardPropagation(const StaticTable<T, M::m[ I ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTableFinal) const {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I < M::nbLayers - Size(1) ) {
					StaticTable<T, M::m[ I ][ 1 ]> outTable;
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(featureTable, outTable, this->hiddenActivationFunc);
					return _computeForwardPropagation(outTable, outTableFinal);
				} else {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(featureTable, outTableFinal, this->activationFunc);
				}
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			if constexpr ( I >= Size(0) ) {
				NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>* neuralLayer(getLayer<I>());

				// Compute dZx
				if constexpr ( I == M::nbLayers - Size(1) ) {
					neuralLayer->computeDeltasLast(dataIInterval, this->expectedYVector);
				} else {
					neuralLayer->computeDeltas<M::m[I + Size(1)][0], M::m[I + Size(1)][1], M::HiddenActivationFunc>(dataIInterval, *getLayer<I + Size(1)>(), this->hiddenActivationFunc);
				}

				neuralLayer->computeBackPropagation(dataIInterval);
			}
			if constexpr ( I > Size(0) ) {
				return _computeBackPropagation<I - Size(1)>(dataIInterval);
			}
		}

		template<typename T, typename M>
		template<Size I, typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::_updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor) {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->updateModel<LearningRateFunc>(learningRateFunc, learningRateFactor, this->epoch);

				return _updateModel<I + Size(1)>(learningRateFunc, learningRateFactor);
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_constructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				const Vector<StaticTable<T, M::m[ I ][ 0 ]>>* inVector;
				if constexpr ( I == Size(0) ) {
					inVector = &this->featureVector;
				} else {
					inVector = &getLayer<I - Size(1)>()->getOutVector();
				}
				this->layerTable[ I ] = reinterpret_cast< void* >( new NeuralLayer<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ]>(inVector) );
				_constructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_destructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				delete getLayer<I>();

				return _destructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline constexpr bool DeepNeuralNetwork<T, M>::_checkModel() const {
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

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_setNbData() {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->setNbData(getNbData());
				_setNbData<I + Size(1)>();
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_setParamRandom() {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->setParamRandom();
				_setParamRandom<I + Size(1)>();
			}
		}

	}

}