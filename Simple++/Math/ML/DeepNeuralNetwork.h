#pragma once

#include "../../Thread.h"
#include "../../Mutex.h"
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

			void addData(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable);
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
			void setEpoch(const Size epochNum);

			void setLearningRateFactor(const T& learningRateFactor);
			const T& getLearningRateFactor() const;

			void copyParamMat(const DeepNeuralNetwork<T, M>& deepNeuralNetwork);
			template<Size I>
			void setParamMat(const Mat<T>& paramMat);

			void setParamRandom();

			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const LearningRateFunc& learningRateFunc, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimizeCluster(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbClusters = Size(16), const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);

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

			///@brief Set the average for each layer of every paramMat.
			template<Size I = Size(0)>
			void _setParamMat(const Vector<DeepNeuralNetwork<T, M>*>& deepNeuralNetworkVector);

			template<Size I = Size(0)>
			void _copyParamMat(const DeepNeuralNetwork<T, M>& deepNeuralNetwork);

			StaticTable<void*, M::nbLayers> layerTable;

			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector;
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> expectedYVector;

			bool bNeedForwardPropagation;

			typename M::HiddenActivationFunc hiddenActivationFunc;
			typename M::ActivationFunc activationFunc;

			Size epochNum;
			T learningRateFactor;

			Mutex optimizeMutex;
		};

		template<typename T, typename M>
		inline DeepNeuralNetwork<T, M>::DeepNeuralNetwork() :
			bNeedForwardPropagation(true),
			epochNum(0),
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
		inline void DeepNeuralNetwork<T, M>::addData(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) {
			this->optimizeMutex.lock();
			{
				this->featureVector.push(featureTable);
				this->expectedYVector.push(outTable);
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) {
			addData(data.getFeatures(), data.getOuts());
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			this->optimizeMutex.lock();
			{
				for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
					const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data(dataVector.getValueI(dataI));
					this->featureVector.push(data.getFeatures());
					this->expectedYVector.push(data.getOuts());
				}
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M>
		inline const Size DeepNeuralNetwork<T, M>::getNbData() const {
			return this->featureVector.getSize();
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
			return this->epochNum;
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::setEpoch(const Size epochNum) {
			this->epochNum = epochNum;
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::setLearningRateFactor(const T& learningRateFactor) {
			this->learningRateFactor = learningRateFactor;
		}

		template<typename T, typename M>
		inline const T& DeepNeuralNetwork<T, M>::getLearningRateFactor() const {
			return this->learningRateFactor;
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::copyParamMat(const DeepNeuralNetwork<T, M>& deepNeuralNetwork) {
			_copyParamMat<Size(0)>(deepNeuralNetwork);
		}

		template<typename T, typename M>
		inline void DeepNeuralNetwork<T, M>::setParamRandom() {
			_setParamRandom<Size(0)>();
			setLearningRateFactor(T(1.0));
			setEpoch(Size(0));
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::setParamMat(const Mat<T>& paramMat) {
			getLayer<I>()->setParamMat(paramMat);
			this->bNeedForwardPropagation = true;
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

			if ( getEpoch() == Size(0) ) {
				Log::startStep("Starting from epochNum #0, randomizing params...");
				setParamRandom();
				Log::endStep("Done.");
			}

			T lastCost(computeCostQuadratic(dataIInterval));

			if ( verbose > 0 ) {
				Log::displayLog(String::format("Initial quadratic cost : %.", lastCost));
			}

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLast(timePointBegin.getValue());

			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				optimize(dataIInterval, learningRateFunc);

				T newCost(computeCostQuadratic(dataIInterval));
				if ( newCost > lastCost ) {
					setLearningRateFactor(getLearningRateFactor()* T(0.5));

					if ( verbose > 1 ) {
						Log::displayWarning(String::format("[%/%] epochNum #% : New cost higher than the previous one.", getPercent(iterationI), getEpoch()));
					}
				}
				lastCost = newCost;

				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				if ( timePointNow - timePointLast > saveDuration ) {
					timePointLast.setValue(timePointNow.getValue());
					if ( verbose > 1 ) {
						Log::displayLog(String::format("[%/%] epochNum #% : Finished loop with cost of % and a coeficient of determination of %%.", getPercent(iterationI), getEpoch(), computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)), Log::MessageColor::DarkWhite);
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
		inline void DeepNeuralNetwork<T, M>::optimizeCluster(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbClusters, const Time::Duration<Time::MilliSecond>& saveDuration, int verbose) {
			class GetPercent {
			public:
				GetPercent(const Size nbIterations) :
					nbIterations(nbIterations) {}

				Size operator()(const Size iterationI) const {
					return Size(T(iterationI + Size(1)) / T(this->nbIterations - Size(1)) * T(100));
				}

				const Size nbIterations;
			};

			class Cluster : public DeepNeuralNetwork<T, M>, public Thread {
			public:
				Cluster(const LearningRateFunc& learningRateFunc, const Time::Duration<Time::MilliSecond>& runDuration) :
					learningRateFunc(learningRateFunc),
					runDuration(runDuration) {}

				void init(const Size nbIterations) {
					this->epochTarget = getEpoch() + nbIterations;
					this->lastCost = computeCostQuadratic();
				}

				void run() override {
					const Math::Interval<Size> dataIInterval(Size(0), getNbData());
					Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());

					while ( true ) {
						optimize(dataIInterval, learningRateFunc);

						T newCost(computeCostQuadratic(dataIInterval));
						if ( newCost > this->lastCost ) {
							setLearningRateFactor(getLearningRateFactor() * T(0.5));
						}
						this->lastCost = newCost;

						Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
						if ( timePointNow - timePointBegin > this->runDuration ) {
							break;
						}
					}
				}

			private:
				const LearningRateFunc& learningRateFunc;
				const Time::Duration<Time::MilliSecond>& runDuration;
				Size epochTarget;
				T lastCost;
			};

			const GetPercent getPercent(nbIterations);

			// Creating the threads
			Vector<Cluster*> clusterVector(nbClusters);
			for ( Size i(0); i < clusterVector.getSize(); i++ ) {
				clusterVector.setValueI(i, new Cluster(learningRateFunc, saveDuration));
			}

			// Dispatch data into Clusters.
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const Size clusterI(dataI% clusterVector.getSize());
				Cluster* cluster(clusterVector.getValueI(clusterI));
				cluster->addData(this->featureVector.getValueI(dataI), this->expectedYVector.getValueI(dataI));
			}

			if ( getEpoch() == Size(0) ) {
				Log::startStep("Starting from epochNum #0, randomizing params...");
				for ( Size i(0); i < clusterVector.getSize(); i++ ) {
					Cluster* cluster(clusterVector.getValueI(i));
					cluster->setParamRandom();
				}
				Log::endStep("Done.");
			} else {
				for ( Size i(0); i < clusterVector.getSize(); i++ ) {
					Cluster* cluster(clusterVector.getValueI(i));
					cluster->copyParamMat(*this);
					cluster->setLearningRateFactor(getLearningRateFactor());
					cluster->setEpoch(getEpoch());
				}
			}

			for ( Size i(0); i < clusterVector.getSize(); i++ ) {
				Cluster* cluster(clusterVector.getValueI(i));
				cluster->init(nbIterations);
			}

			T lastCost(computeCostQuadratic(dataIInterval));
			if ( verbose > 0 ) {
				Log::displayLog(String::format("Initial quadratic cost : %.", lastCost));
			}

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLast(timePointBegin.getValue());

			// Run
			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				for ( Size i(0); i < clusterVector.getSize(); i++ ) {
					Cluster* cluster(clusterVector.getValueI(i));
					cluster->start();
				}

				for ( Size i(0); i < clusterVector.getSize(); i++ ) {
					Cluster* cluster(clusterVector.getValueI(i));
					cluster->join();
				}

				/*T newCost(computeCostQuadratic(dataIInterval));
				if ( newCost > lastCost ) {
					setLearningRateFactor(getLearningRateFactor() * T(0.5));

					for ( Size i(0); i < clusterVector.getSize(); i++ ) {
						Cluster* cluster(clusterVector.getValueI(i));
						cluster->setLearningRateFactor(getLearningRateFactor());
					}

					if ( verbose > 1 ) {
						Log::displayWarning(String::format("[%/%] epochNum #% : New cost higher than the previous one.", getPercent(iterationI), getEpoch()));
					}
				}*/
				// lastCost = newCost;
				setEpoch(getEpoch() + clusterVector.getSize());

				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				if ( timePointNow - timePointLast > saveDuration ) {
					timePointLast.setValue(timePointNow.getValue());

					_setParamMat<Size(0)>(clusterVector);

					if ( verbose > 1 ) {
						Log::displayLog(String::format("[%/%] epochNum #% : Finished loop with cost of % and a coeficient of determination of %%.", getPercent(iterationI), getEpoch(), computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)), Log::MessageColor::DarkWhite);
					}
				}
			}

			// Deleting the threads.
			for ( Size i(0); i < clusterVector.getSize(); i++ ) {
				delete clusterVector.getValueI(i);
			}
		}

		template<typename T, typename M>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc) {
			this->optimizeMutex.lock();
			{
				computeForwardPropagation(dataIInterval);
				computeBackPropagation(dataIInterval);
			}
			this->optimizeMutex.unlock();

			updateModel(learningRateFunc, this->learningRateFactor);
		}

		template<typename T, typename M>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M>::updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor) {
			_updateModel<Size(0)>(learningRateFunc, learningRateFactor);
			this->epochNum++;
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
				getLayer<I>()->updateModel<LearningRateFunc>(learningRateFunc, learningRateFactor, this->epochNum);

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

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_setParamMat(const Vector<DeepNeuralNetwork<T, M>*>& deepNeuralNetworkVector) {
			if constexpr ( I < M::nbLayers ) {
				Mat<T> paramMatSum(M::m[ I ][ 1 ], M::m[ I ][ 0 ] + Size(1));

				paramMatSum.zeros();

				for ( Size i(0); i < deepNeuralNetworkVector.getSize(); i++ ) {
					const DeepNeuralNetwork<T, M>* deepNeuralNetwork(deepNeuralNetworkVector.getValueI(i));
					paramMatSum += deepNeuralNetwork->getLayer<I>()->getParamMat();
				}

				paramMatSum /= T(deepNeuralNetworkVector.getSize());

				setParamMat<I>(paramMatSum);

				_setParamMat<I + Size(1)>(deepNeuralNetworkVector);
			}
		}

		template<typename T, typename M>
		template<Size I>
		inline void DeepNeuralNetwork<T, M>::_copyParamMat(const DeepNeuralNetwork<T, M>& deepNeuralNetwork) {
			if constexpr ( I < M::nbLayers ) {
				setParamMat<I>(deepNeuralNetwork.getLayer<I>()->getParamMat());
				_copyParamMat<I + Size(1)>(deepNeuralNetwork);
			}
		}

	}

}