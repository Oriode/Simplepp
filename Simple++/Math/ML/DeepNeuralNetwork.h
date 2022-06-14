#pragma once

#include "../../Thread.h"
#include "../../Mutex.h"
#include "../../Time/Time.h"
#include "../../IO/BasicIO.h"
#include "../../IO/IO.h"
#include "../Interval.h"
#include "LearningRate.h"
#include "ActivationFunc.h"
#include "NeuralLayerMT.h"
#include "NeuralLayerMT.h"

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

		template<typename T, typename M, Size NbThreads>
		class DeepNeuralNetwork;

		template<typename T, typename M, Size NbThreads, typename LearningRateFunc>
		class SearchThread : public DeepNeuralNetwork<T, M, NbThreads>, public Thread {
		public:
			SearchThread(const LearningRateFunc& learningRateFunc, const Time::Duration<Time::MilliSecond>& runDuration, const Math::Interval<Size>& dataIInterval) :
				learningRateFunc(learningRateFunc),
				runDuration(runDuration),
				dataIInterval(dataIInterval) {}

			SearchThread(const LearningRateFunc& learningRateFunc, const Time::Duration<Time::MilliSecond>& runDuration) :
				learningRateFunc(learningRateFunc),
				runDuration(runDuration) {}

			void init(const Size nbIterations) {
				this->lastCost = computeCostQuadratic(this->dataIInterval);
			}

			void run() override {
				Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());

				while ( true ) {
					optimize(this->dataIInterval, learningRateFunc);

					T newCost(computeCostQuadratic(this->dataIInterval));
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

			const T& getCost() const {
				return this->lastCost;
			}

			bool operator<(const SearchThread& searchThread) const {
				return this->lastCost < searchThread.getCost();
			}

			void setDataIInterval(const Math::Interval<Size>& dataIInterval) {
				this->dataIInterval = dataIInterval;
			}

		private:
			const LearningRateFunc& learningRateFunc;
			const Time::Duration<Time::MilliSecond>& runDuration;
			Math::Interval<Size> dataIInterval;
			T lastCost;
		};

		template<typename T, typename M = Model, Size NbThreads = Size(1)>
		class DeepNeuralNetwork : public IO::BasicIO {
		public:
			static constexpr Size NbFeatures = M::m[ 0 ][ 0 ];
			static constexpr Size NbOut = M::m[ M::nbLayers - Size(1) ][ 1 ];

			DeepNeuralNetwork(const OS::Path & filePath = OS::Path());
			~DeepNeuralNetwork();

			void addData(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable);
			void addData(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTable, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTable);
			void addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data);
			void addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector);
			void clearData();

			const Size getNbData() const;
			constexpr Size getNbLayers() const;

			const OS::Path& getFilePath() const;
			void setFilePath(const OS::Path& filePath);

			bool saveToFile(const OS::Path& filePath) const;
			bool loadFromFile(const OS::Path& filePath);

			template<Size I>
			const NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>* getLayer() const;
			template<Size I>
			NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>* getLayer();

			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval);
			const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& computeForwardPropagation(const Size dataI);
			void computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const;

			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);

			const Size getEpoch() const;
			void setEpoch(const Size epochNum);

			void setLearningRateFactor(const T& learningRateFactor);
			const T& getLearningRateFactor() const;

			void copyParamMat(const DeepNeuralNetwork<T, M, NbThreads>& deepNeuralNetwork);
			template<Size I>
			void setParamMat(const Mat<T>& paramMat);

			void resetParams();

			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbSearchThreads = Size(16), const T& randomFactor = T(0.25), const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimizeCluster(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbSearchThreads = Size(16), const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);
			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbSearchThreads = Size(16), const T & randomFactor = T(0.25), const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), int verbose = 2);

			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void updateModel(const LearningRateFunc& learningRateFunc = LearningRateFunc(0.01), const T& learningRateFactor = T(1.0));

			T computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> & expectedYVector);
			T computeCostLog(const Math::Interval<Size>& dataIInterval);
			T computeCostLog();
			T computeCostQuadratic(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedYVector);
			T computeCostQuadratic(const Math::Interval<Size>& dataIInterval);
			T computeCostQuadratic();
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedYVector);
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval);
			T computeCoefficientOfDetermination();

			/**
			 * @brief 	read from a file stream
			 * @param [in,out]	stream	stream used to read load this object.
			 * @returns	boolean to know if the operation is a success of not.
			 */
			template<typename Stream>
			bool read(Stream* stream);

			/**
			 * @brief 	write this object as binary into a file stream
			 * @param [in,out]	stream	stream used to write this object.
			 * @returns	boolean to know if the operation is a success of not.
			 */
			template<typename Stream>
			bool write(Stream* stream) const;

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
			void _resetParams();

			///@brief Set the average for each layer of every paramMat.
			template<Size I = Size(0)>
			void _setParamMat(const Vector<DeepNeuralNetwork<T, M, NbThreads>*>& deepNeuralNetworkVector);

			template<Size I = Size(0)>
			void _copyParamMat(const DeepNeuralNetwork<T, M, NbThreads>& deepNeuralNetwork);

			template<Size I, typename Stream>
			bool _write(Stream* stream) const;

			template<Size I, typename Stream>
			bool _read(Stream* stream);

			StaticTable<void*, M::nbLayers> layerTable;

			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector;
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> expectedYVector;

			bool bNeedForwardPropagation;

			typename M::HiddenActivationFunc hiddenActivationFunc;
			typename M::ActivationFunc activationFunc;

			Size epochNum;
			T learningRateFactor;

			Mutex optimizeMutex;

			OS::Path filePath;
		};

		template<typename T, typename M, Size NbThreads>
		inline DeepNeuralNetwork<T, M, NbThreads>::DeepNeuralNetwork(const OS::Path& filePath) :
			bNeedForwardPropagation(true),
			epochNum(0),
			filePath(filePath)
		{
			static_assert( Utility::isBase<Model, M>::value, "Model type unknown." );
			static_assert( Utility::isBase<ActivationFunc::BasicActivationFunc, M::ActivationFunc>::value, "Model ActivationFunc type unknown." );
			static_assert( Utility::isBase<ActivationFunc::BasicActivationFunc, M::HiddenActivationFunc>::value, "Model HiddenActivationFunc type unknown." );
			static_assert( M::nbLayers > Size(0), "Model error, nbLayers cannot be 0." );
			_checkModel<Size(1)>();
			_constructNeuralLayer<Size(0)>();

			if ( this->filePath.getSize() ) {
				if ( !loadFromFile(this->filePath) ) {
					Log::displayError(String::format("Unable to read the DeepNeuralNetwork from \"%\".", this->filePath));
				}
			}

		}

		template<typename T, typename M, Size NbThreads>
		inline DeepNeuralNetwork<T, M, NbThreads>::~DeepNeuralNetwork() {
			_destructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::addData(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) {
			this->optimizeMutex.lock();
			{
				this->featureVector.push(featureTable);
				this->expectedYVector.push(outTable);
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::addData(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) {
			assert(featureTableVector.getSize() == outTableVector.getSize());
			this->optimizeMutex.lock();
			{
				this->featureVector.concat(featureTableVector);
				this->expectedYVector.concat(outTableVector);
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) {
			addData(data.getFeatures(), data.getOuts());
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			this->optimizeMutex.lock();
			{
				this->featureVector.reserve(this->featureVector.getSize() + dataVector.getSize());
				this->expectedYVector.reserve(this->expectedYVector.getSize() + dataVector.getSize());
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

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::clearData() {
			this->optimizeMutex.lock();
			{
				this->featureVector.clear();
				this->expectedYVector.clear();
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, Size NbThreads>
		inline const Size DeepNeuralNetwork<T, M, NbThreads>::getNbData() const {
			return this->featureVector.getSize();
		}

		template<typename T, typename M, Size NbThreads>
		inline constexpr Size DeepNeuralNetwork<T, M, NbThreads>::getNbLayers() const {
			return M::nbLayers;
		}

		template<typename T, typename M, Size NbThreads>
		inline const OS::Path& DeepNeuralNetwork<T, M, NbThreads>::getFilePath() const {
			return this->filePath;
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::setFilePath(const OS::Path& filePath) {
			this->filePath = filePath;
		}

		template<typename T, typename M, Size NbThreads>
		inline bool DeepNeuralNetwork<T, M, NbThreads>::saveToFile(const OS::Path& filePath) const {
			if ( !IO::write(filePath, this) ) {
				return false;
			}
			return true;
		}

		template<typename T, typename M, Size NbThreads>
		inline bool DeepNeuralNetwork<T, M, NbThreads>::loadFromFile(const OS::Path& filePath) {
			if ( !IO::read(filePath, this) ) {
				return false;
			}
			return true;
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval) {
			if ( this->bNeedForwardPropagation ) {
				for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
					computeForwardPropagation(dataI);
				}
				this->bNeedForwardPropagation = false;
			}
		}

		template<typename T, typename M, Size NbThreads>
		inline const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& DeepNeuralNetwork<T, M, NbThreads>::computeForwardPropagation(const Size dataI) {
			_computeForwardPropagation<Size(0)>(dataI);
			this->bNeedForwardPropagation = false;
			return getLayer< M::nbLayers - Size(1)>()->getOuts(dataI);
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const {
			const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(data.getFeatures());
			StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(data.getOuts());
			_computeForwardPropagation<Size(0)>(featureTable, outTable);
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			return _computeBackPropagation<M::nbLayers - Size(1)>(dataIInterval);
		}

		template<typename T, typename M, Size NbThreads>
		inline const Size DeepNeuralNetwork<T, M, NbThreads>::getEpoch() const {
			return this->epochNum;
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::setEpoch(const Size epochNum) {
			this->epochNum = epochNum;
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::setLearningRateFactor(const T& learningRateFactor) {
			this->learningRateFactor = learningRateFactor;
		}

		template<typename T, typename M, Size NbThreads>
		inline const T& DeepNeuralNetwork<T, M, NbThreads>::getLearningRateFactor() const {
			return this->learningRateFactor;
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::copyParamMat(const DeepNeuralNetwork<T, M, NbThreads>& deepNeuralNetwork) {
			_copyParamMat<Size(0)>(deepNeuralNetwork);
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, NbThreads>::resetParams() {
			_resetParams<Size(0)>();
			setLearningRateFactor(T(1.0));
			setEpoch(Size(0));
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::setParamMat(const Mat<T>& paramMat) {
			getLayer<I>()->setParamMat(paramMat);
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, Size NbThreads>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M, NbThreads>::optimize(const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbSearchThreads, const T& randomFactor, const Time::Duration<Time::MilliSecond>& saveDuration, int verbose) {
			return optimize(Interval<Size>(Size(0), getNbData()), learningRateFunc, nbIterations, nbSearchThreads, randomFactor, saveDuration, verbose);
		}

		template<typename T, typename M, Size NbThreads>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M, NbThreads>::optimizeCluster(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbSearchThreads, const Time::Duration<Time::MilliSecond>& saveDuration, int verbose) {
			class GetPercent {
			public:
				GetPercent(const Size nbIterations) :
					nbIterations(nbIterations) {}

				Size operator()(const Size iterationI) const {
					return Size(T(iterationI + Size(1)) / T(this->nbIterations - Size(1)) * T(100));
				}

				const Size nbIterations;
			};

			using SearchThread = SearchThread<T, M, NbThreads, LearningRateFunc>;
			const GetPercent getPercent(nbIterations);

			this->optimizeMutex.lock();

			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting clustered gradient descent with % iterations over % data...", nbIterations, dataIInterval.toString()));
			}

			// Creating the threads
			Vector<SearchThread*> searchThreadVector(nbSearchThreads);
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				searchThreadVector.setValueI(i, new SearchThread(learningRateFunc, saveDuration));
			}

			if ( verbose > 0 ) {
				Log::startStep("Copying data to the threads...");
			}

			// Dispatch data into Clusters.
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const Size searchThreadI(dataI% searchThreadVector.getSize());
				SearchThread* searchThread(searchThreadVector.getValueI(searchThreadI));
				searchThread->addData(this->featureVector.getValueI(dataI), this->expectedYVector.getValueI(dataI));
			}

			if ( verbose > 0 ) {
				Log::endStep("Done.");
			}

			if ( getEpoch() == Size(0) ) {
				if ( verbose > 0 ) {
					Log::startStep("Starting from epochNum #0, randomizing params...");
				}
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->resetParams();
				}
				if ( verbose > 0 ) {
					Log::endStep("Done.");
				}
			} else {
				if ( verbose > 0 ) {
					Log::startStep(String::format("Resuming from epoch #%. Copying params to the threads...", getEpoch()));
				}
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->copyParamMat(*this);
					searchThread->setLearningRateFactor(getLearningRateFactor());
					searchThread->setEpoch(getEpoch());
				}
				if ( verbose > 0 ) {
					Log::endStep("Done.");
				}
			}

			if ( verbose > 0 ) {
				Log::startStep("Initializing threads...");
			}

			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				SearchThread* searchThread(searchThreadVector.getValueI(i));
				searchThread->setDataIInterval(Math::Interval<Size>(Size(0), searchThread->getNbData()));
				searchThread->init(nbIterations);
			}

			if ( verbose > 0 ) {
				Log::endStep("Done.");
			}

			T lastCost(computeCostQuadratic(dataIInterval));
			if ( verbose > 0 ) {
				Log::displayLog(String::format("Initial quadratic cost : %.", lastCost));
			}

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLast(timePointBegin.getValue());

			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting gradient descent loop with % iterations and a break every % ms...", nbIterations, saveDuration.getValue()));
			}

			// Run
			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->start();
				}
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->join();
				}
				setEpoch(getEpoch() + searchThreadVector.getSize());

				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				if ( timePointNow - timePointLast > saveDuration ) {
					timePointLast.setValue(timePointNow.getValue());

					_setParamMat<Size(0)>(searchThreadVector);

					if ( this->filePath.getSize() && !saveToFile(this->filePath) ) {
						if ( verbose > -1 ) {
							Log::displayWarning(String::format("Unable to save the DeepNeuralNetwork to the file \"%\".", this->filePath));
						}
					}

					for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
						SearchThread* searchThread(searchThreadVector.getValueI(i));
						searchThread->copyParamMat(*this);
					}

					if ( verbose > 1 ) {
						Log::displayLog(String::format("[%/%] epochNum #% : Finished loop with cost of % and a coeficient of determination of %%.", getPercent(iterationI), getEpoch(), computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)), Log::MessageColor::DarkWhite);
					}
				}
			}

			this->optimizeMutex.unlock();

			if ( verbose > 0 ) {
				Log::endStep("Done.");
			}

			// Deleting the threads.
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				delete searchThreadVector.getValueI(i);
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)));
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M, NbThreads>::optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc, const Size nbIterations, const Size nbSearchThreads, const T& randomFactor, const Time::Duration<Time::MilliSecond>& saveDuration, int verbose) {
			class GetPercent {
			public:
				GetPercent(const Size nbIterations) :
					nbIterations(nbIterations) {}

				Size operator()(const Size iterationI) const {
					return Size(T(iterationI + Size(1)) / T(this->nbIterations - Size(1)) * T(100));
				}

				const Size nbIterations;
			};

			using SearchThread = SearchThread<T, M, NbThreads, LearningRateFunc>;
			const GetPercent getPercent(nbIterations);

			this->optimizeMutex.lock();

			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting optimisation with % iterations with % threads over % data...", nbIterations, nbSearchThreads, dataIInterval.toString()));
			}

			// Creating the threads
			Vector<SearchThread*> searchThreadVector(nbSearchThreads);
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				searchThreadVector.setValueI(i, new SearchThread(learningRateFunc, saveDuration, dataIInterval));
			}

			if (verbose > 0 ){
				Log::startStep("Copying data to the threads...");
			}

			// Copy data into Clusters.
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				SearchThread* searchThread(searchThreadVector.getValueI(i));
				searchThread->addData(this->featureVector, this->expectedYVector);
			}

			if ( verbose > 0 ) {
				Log::endStep("Done.");
			}

			if ( getEpoch() == Size(0) ) {
				if ( verbose > 0 ) {
					Log::startStep("Starting from epochNum #0, randomizing params...");
				}
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->resetParams();
				}
				if ( verbose > 0 ) {
					Log::endStep("Done.");
				}
			} else {
				if ( verbose > 0 ) {
					Log::startStep(String::format("Resuming from epoch #%. Copying params to the threads...", getEpoch()));
				}
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->copyParamMat(*this);
					searchThread->setLearningRateFactor(getLearningRateFactor());
					searchThread->setEpoch(getEpoch());
				}
				if ( verbose > 0 ) {
					Log::endStep("Done.");
				}
			}

			if ( verbose > 0 ) {
				Log::startStep("Initializing threads...");
			}

			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				SearchThread* searchThread(searchThreadVector.getValueI(i));
				searchThread->init(nbIterations);
			}

			if ( verbose > 0 ) {
				Log::endStep("Done.");
			}

			T lastCost(computeCostQuadratic(dataIInterval));
			if ( verbose > 0 ) {
				Log::displayLog(String::format("Initial quadratic cost : %.", lastCost));
			}

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLast(timePointBegin.getValue());

			if ( verbose > 0 ) {
				Log::startStep(String::format("Starting gradient descent loop with % iterations and a break every % ms...", nbIterations, saveDuration.getValue()));
			}

			const T randomFactorFinal(T(1) + T(searchThreadVector.getSize() - Size(1)) * randomFactor);

			// Run
			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {
				// Update learningRateFactor
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));

					const T newLearningRateFactor(getLearningRateFactor()* Math::random(T(1.0) / randomFactorFinal, randomFactorFinal));
					searchThread->setLearningRateFactor(newLearningRateFactor);
				}

				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->start();
				}

				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->join();
				}

				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				if ( timePointNow - timePointLast > saveDuration ) {
					timePointLast.setValue(timePointNow.getValue());

					typename Vector<SearchThread*>::Iterator minIt(NULL);
					T searchCost(lastCost);
					for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
						SearchThread* searchThread(searchThreadVector.getValueI(i));

						const T& searchThreadCost(searchThreadVector.getValueI(i)->getCost());

						if ( !Utility::isInf(searchThreadCost) && !Utility::isNan(searchThreadCost) ) {
							if ( searchThreadCost < searchCost ) {
								minIt = searchThreadVector.getIterator(i);
							}
						}
					}
					if ( minIt ) {
						SearchThread* minSearchThread(searchThreadVector.getValueIt(minIt));
						setLearningRateFactor(minSearchThread->getLearningRateFactor());
						copyParamMat(*minSearchThread);
						setEpoch(minSearchThread->getEpoch());
						lastCost = computeCostQuadratic(dataIInterval);
					} else {
						setLearningRateFactor(getLearningRateFactor() * T(0.1));
						if ( verbose > -1 ) {
							Log::displayWarning(String::format("[%/%] epochNum #% : No better value founded. Maybe the maximum has been founded. Cost of % and a coeficient of determination of %%.", getPercent(iterationI), getEpoch(), lastCost, computeCoefficientOfDetermination(dataIInterval) * T(100)));
						}
					}

					if ( this->filePath.getSize() && !saveToFile(this->filePath) ) {
						if ( verbose > -1 ) {
							Log::displayWarning(String::format("Unable to save the DeepNeuralNetwork to the file \"%\".", this->filePath));
						}
					}

					if ( verbose > 1 ) {
						Log::displayLog(String::format("[%/%] epochNum #% : Finished loop with cost of % and a coeficient of determination of %%.", getPercent(iterationI), getEpoch(), lastCost, computeCoefficientOfDetermination(dataIInterval) * T(100)), Log::MessageColor::DarkWhite);
					}
				}
			}

			this->optimizeMutex.unlock();

			if ( verbose > 0 ) {
				Log::endStep("Done.");
			}

			// Deleting the threads.
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				delete searchThreadVector.getValueI(i);
			}

			if ( verbose > 0 ) {
				Log::endStep(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeCostQuadratic(dataIInterval), computeCoefficientOfDetermination(dataIInterval) * T(100)));
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M, NbThreads>::optimize(const Math::Interval<Size>& dataIInterval, const LearningRateFunc& learningRateFunc) {
			this->optimizeMutex.lock();
			{
				computeForwardPropagation(dataIInterval);
				computeBackPropagation(dataIInterval);
			}
			this->optimizeMutex.unlock();

			updateModel(learningRateFunc, this->learningRateFactor);
		}

		template<typename T, typename M, Size NbThreads>
		template<typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M, NbThreads>::updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor) {
			_updateModel<Size(0)>(learningRateFunc, learningRateFactor);
			this->epochNum++;
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedYVector) {
			return getLayer<M::nbLayers - Size(1)>()->computeCostLog(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCostLog(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return computeCostLog(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCostLog() {
			return computeCostLog(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCostQuadratic(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedYVector) {
			return getLayer<M::nbLayers - Size(1)>()->computeCostQuadratic(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCostQuadratic(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return computeCostQuadratic(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCostQuadratic() {
			return computeCostQuadratic(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedYVector) {
			return getLayer<M::nbLayers - Size(1)>()->computeCoefficientOfDetermination(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return computeCoefficientOfDetermination(dataIInterval, this->expectedYVector);
		}

		template<typename T, typename M, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, NbThreads>::computeCoefficientOfDetermination() {
			return computeCoefficientOfDetermination(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline const NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>* DeepNeuralNetwork<T, M, NbThreads>::getLayer() const {
			return const_cast< DeepNeuralNetwork<T, M, NbThreads> * >( this )->getLayer<I>();
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>* DeepNeuralNetwork<T, M, NbThreads>::getLayer() {
			return reinterpret_cast< NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>* >( this->layerTable[ I ] );
		}

		template<typename T, typename M, Size NbThreads>
		template<typename Stream>
		inline bool DeepNeuralNetwork<T, M, NbThreads>::read(Stream* stream) {
			Size nbLayers;
			if ( !IO::read(stream, &nbLayers) ) {
				return false;
			}
			if ( nbLayers != getNbLayers() ) {
				Log::displayError(String::format("Trying to read a DeepNeuralNetwork of the wrong number of layers : this[ % ] != read[ % ].", getNbLayers(), nbLayers));
				return false;
			}
			if ( !IO::read(stream, &this->featureVector) ) {
				return false;
			}
			if ( !IO::read(stream, &this->expectedYVector) ) {
				return false;
			}
			if ( !_read<Size(0)>(stream) ) {
				return false;
			}
			if ( !IO::read(stream, &this->hiddenActivationFunc) ) {
				return false;
			}
			if ( !IO::read(stream, &this->activationFunc) ) {
				return false;
			}
			if ( !IO::read(stream, &this->epochNum) ) {
				return false;
			}
			if ( !IO::read(stream, &this->learningRateFactor) ) {
				return false;
			}
			_setNbData<Size(0)>();
			this->bNeedForwardPropagation = true;
			return true;
		}

		template<typename T, typename M, Size NbThreads>
		template<typename Stream>
		inline bool DeepNeuralNetwork<T, M, NbThreads>::write(Stream* stream) const {
			const Size nbLayers(getNbLayers());
			if ( !IO::write(stream, &nbLayers) ) {
				return false;
			}
			if ( !IO::write(stream, &this->featureVector) ) {
				return false;
			}
			if ( !IO::write(stream, &this->expectedYVector) ) {
				return false;
			}
			if ( !_write<Size(0)>(stream) ) {
				return false;
			}
			if ( !IO::write(stream, &this->hiddenActivationFunc) ) {
				return false;
			}
			if ( !IO::write(stream, &this->activationFunc) ) {
				return false;
			}
			if ( !IO::write(stream, &this->epochNum) ) {
				return false;
			}
			if ( !IO::write(stream, &this->learningRateFactor) ) {
				return false;
			}
			return true;
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_computeForwardPropagation(const Size dataI) {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I == M::nbLayers - Size(1) ) {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(dataI, this->activationFunc);
				} else {
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(dataI, this->hiddenActivationFunc);
				}

				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_computeForwardPropagation(const StaticTable<T, M::m[ I ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTableFinal) const {
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

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			if constexpr ( I >= Size(0) ) {
				NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>* neuralLayer(getLayer<I>());

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

		template<typename T, typename M, Size NbThreads>
		template<Size I, typename LearningRateFunc>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor) {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->updateModel<LearningRateFunc>(learningRateFunc, learningRateFactor, this->epochNum);

				return _updateModel<I + Size(1)>(learningRateFunc, learningRateFactor);
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_constructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				const Vector<StaticTable<T, M::m[ I ][ 0 ]>>* inVector;
				if constexpr ( I == Size(0) ) {
					inVector = &this->featureVector;
				} else {
					inVector = &getLayer<I - Size(1)>()->getOutVector();
				}
				this->layerTable[ I ] = reinterpret_cast< void* >( new NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], NbThreads>(inVector) );
				_constructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_destructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				delete getLayer<I>();

				return _destructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline constexpr bool DeepNeuralNetwork<T, M, NbThreads>::_checkModel() const {
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

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_setNbData() {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->setNbData(getNbData());
				_setNbData<I + Size(1)>();
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_resetParams() {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->resetParams();
				_resetParams<I + Size(1)>();
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_setParamMat(const Vector<DeepNeuralNetwork<T, M, NbThreads>*>& deepNeuralNetworkVector) {
			if constexpr ( I < M::nbLayers ) {
				Mat<T> paramMatSum(M::m[ I ][ 1 ], M::m[ I ][ 0 ] + Size(1));

				paramMatSum.zeros();

				for ( Size i(0); i < deepNeuralNetworkVector.getSize(); i++ ) {
					const DeepNeuralNetwork<T, M, NbThreads>* deepNeuralNetwork(deepNeuralNetworkVector.getValueI(i));
					paramMatSum += deepNeuralNetwork->getLayer<I>()->getParamMat();
				}

				paramMatSum /= T(deepNeuralNetworkVector.getSize());

				setParamMat<I>(paramMatSum);

				_setParamMat<I + Size(1)>(deepNeuralNetworkVector);
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, NbThreads>::_copyParamMat(const DeepNeuralNetwork<T, M, NbThreads>& deepNeuralNetwork) {
			if constexpr ( I < M::nbLayers ) {
				setParamMat<I>(deepNeuralNetwork.getLayer<I>()->getParamMat());
				_copyParamMat<I + Size(1)>(deepNeuralNetwork);
			}
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I, typename Stream>
		inline bool DeepNeuralNetwork<T, M, NbThreads>::_write(Stream* stream) const {
			if constexpr ( I < M::nbLayers ) {
				if ( !IO::write(stream, getLayer<I>()) ) {
					return false;
				}

				return _write<I + Size(1)>(stream);
			}
			return true;
		}

		template<typename T, typename M, Size NbThreads>
		template<Size I, typename Stream>
		inline bool DeepNeuralNetwork<T, M, NbThreads>::_read(Stream* stream) {
			if constexpr ( I < M::nbLayers ) {
				if ( !IO::read(stream, getLayer<I>()) ) {
					return false;
				}

				return _read<I + Size(1)>(stream);
			}
			return true;
		}

	}

}