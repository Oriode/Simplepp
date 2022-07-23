#pragma once

#include "../../Thread.h"
#include "../../Mutex.h"
#include "../../Time/Time.h"
#include "../../IO/BasicIO.h"
#include "../../IO/IO.h"
#include "../Interval.h"

#include "Model.h"
#include "Optimizer.h"
#include "ActivationFunc.h"
#include "NeuralLayerMT.h"
#include "NeuralLayerMT.h"

namespace Math {

	namespace ML {

		template<typename T = double, typename M = Model::BasicModel, typename OptimizerFunc = Optimizer::Adam<T>, Size NbThreads = Size(1)>
		class DeepNeuralNetwork : public IO::BasicIO {
		public:
			class GetPercent {
			public:
				GetPercent(const Size nbIterations) :
					nbIterations(nbIterations) {}

				Size operator()(const Size iterationI) const {
					return Size(T(iterationI + Size(1)) / T(this->nbIterations) * T(100));
				}

			private:
				const Size nbIterations;
			};

			static constexpr Size NbFeatures = M::m[ 0 ][ 0 ];
			static constexpr Size NbOut = M::m[ M::nbLayers - Size(1) ][ 1 ];

			DeepNeuralNetwork(const OptimizerFunc & optimizerFunc = OptimizerFunc(), const OS::Path& filePath = OS::Path());
			~DeepNeuralNetwork();

			void addData(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable);
			void addData(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector);
			void addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data);
			void addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector);
			void clearData();

			void normalizeFeature();
			void normalizeFeature(const Math::Interval<Size>& dataIInterval);
			void normalizeOut();
			void normalizeOut(const Math::Interval<Size>& dataIInterval);
			void normalizeFeature(StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable) const;
			void normalizeFeature(Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector) const;
			void unnormalizeFeature(StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable) const;
			void unnormalizeFeature(Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector) const;
			void normalizeOut(StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) const;
			void normalizeOut(Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const;
			void unnormalizeOut(StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) const;
			void unnormalizeOut(Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const;

			static Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> createFeatureVector(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector);
			static Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> createOutVector(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector);

			const Size getNbData() const;
			constexpr Size getNbLayers() const;
			constexpr Size getNbParams() const;

			const OS::Path& getFilePath() const;
			void setFilePath(const OS::Path& filePath);

			bool saveToFile(const OS::Path& filePath, int verbose = 1) const;
			bool loadFromFile(const OS::Path& filePath, int verbose = 1);

			bool saveToFile(int verbose = 1) const;
			bool loadFromFile(int verbose = 1);

			template<Size I>
			const NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* getLayer() const;
			template<Size I>
			NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* getLayer();

			void computeForwardPropagation();
			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval);
			void computeForwardPropagationS(const Size dataIBegin);
			void computeForwardPropagation(const Size dataI);
			void computeForwardPropagation(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) const;
			void computeForwardPropagation(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const;
			void computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const;

			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);
			void computeBackPropagationS(const Size dataIBegin);

			const Size getEpoch() const;
			void setEpoch(const Size epochNum);

			void setLearningRateFactor(const T& learningRateFactor);
			const T& getLearningRateFactor() const;

			void copyParamMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork);
			void copyGradMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork);
			void copyOptimizerFunc(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork);
			template<Size I>
			void setParamMat(const Mat<T>& paramMat);
			template<Size I>
			void setGradMat(const Mat<T>& gradMat);

			void resetParams();
			void resetOptimizerFunc();
			void resetAll();

			void computeGrad(const Math::Interval<Size>& dataIInterval);
			void computeGradS(const Size dataIBegin);

			static Vector<Math::Interval<Size>> createDataIntervalVector(const Math::Interval<Size>& dataIInterval);

			void optimize(const Math::Interval<Size>& dataIInterval);
			void optimizeStochastic(const Vector<Math::Interval<Size>>& dataIIntervalVector);
			void optimizeStochastic(const Math::Interval<Size>& dataIInterval, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(1000), const Math::Interval<Size>& statsDataIInterval = Math::Interval<Size>(Size(0), Size(1000)), int verbose = 2);
			void optimizeCluster(const Math::Interval<Size>& dataIInterval, const Size nbIterations, const Size nbSearchThreads = Size(16), const Time::Duration<Time::MilliSecond>& saveDuration = Time::Duration<Time::MilliSecond>(30000), const Math::Interval<Size>& statsDataIInterval = Math::Interval<Size>(Size(0), Size(10000)), int verbose = 2);

			void updateModel(const T& learningRateFactor = T(1.0));
			void updateModel(const Vector<DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>*>& deepNeuralNetworkVector, const T& learningRateFactor = T(1.0));

			T computeCostLogF(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const;
			T computeCostLog(const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const;
			T computeCostLog(const Math::Interval<Size>& dataIInterval);
			T computeCostLog();
			T computeMeanSquaredErrorF(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const;
			T computeMeanSquaredError(const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const;
			T computeMeanSquaredError(const Math::Interval<Size>& dataIInterval);
			T computeMeanSquaredError();
			T computeCoefficientOfDeterminationF(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const;
			T computeCoefficientOfDetermination(const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const;
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval);
			T computeCoefficientOfDetermination();

			StaticTable<T, M::m[ 0 ][ 0 ]> computeFeatureImportance(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const;
			StaticTable<T, M::m[ 0 ][ 0 ]> computeFeatureImportance(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector) const;
			StaticTable<T, M::m[ 0 ][ 0 ]> computeFeatureImportance(const Math::Interval<Size>& dataIInterval);
			StaticTable<T, M::m[ 0 ][ 0 ]> computeFeatureImportance();

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
			void _computeForwardPropagation(const Math::Interval<Size>& dataIInterval);

			template<Size I = Size(0)>
			void _computeForwardPropagationS(const Size dataIBegin);

			template<Size I = Size(0)>
			void _computeForwardPropagation(const StaticTable<T, M::m[ I ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]> & outTableFinal) const;

			template<Size I = Size(0)>
			void _computeForwardPropagation(const Vector<StaticTable<T, M::m[ I ][ 0 ]>>& featureTableVector, Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVectorFinal) const;

			template<Size I = M::nbLayers>
			void _computeBackPropagation(const Math::Interval<Size> & dataIInterval);

			template<Size I = M::nbLayers>
			void _computeBackPropagationS(const Size dataIBegin);

			template<Size I = Size(0)>
			void _updateModel(const T& learningRateFactor);

			template<Size I = Size(0)>
			void _constructNeuralLayer(const OptimizerFunc& optimizerFunc);

			template<Size I = Size(0)>
			void _destructNeuralLayer();

			template<Size I = Size(0)>
			constexpr bool _checkModel() const;

			template<Size I = Size(0)>
			void _setNbData();

			template<Size I = Size(0)>
			void _resetParams();

			template<Size I = Size(0)>
			void _resetOptimizerFunc();

			///@brief Set the average for each layer of every paramMat.
			template<Size I = Size(0)>
			void _setParamMatMean(const Vector<DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>*>& deepNeuralNetworkVector);

			///@brief Set the average for each layer of every gradMat.
			template<Size I = Size(0)>
			void _setGradMatMean(const Vector<DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>*>& deepNeuralNetworkVector);

			template<Size I = Size(0)>
			void _copyParamMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork);

			template<Size I = Size(0)>
			void _copyGradMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork);

			template<Size I = Size(0)>
			void _copyOptimizerFunc(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork);

			template<Size I = Size(0)>
			constexpr Size _getNbParams() const;

			template<Size I, typename Stream>
			bool _write(Stream* stream) const;

			template<Size I, typename Stream>
			bool _read(Stream* stream);

			void resetNormalizeTable();

			T normalizeFeature(const T& x, const Math::Interval<T>& v) const;
			T unnormalizeFeature(const T& x, const Math::Interval<T>& v) const;

			T normalizeOut(const T& x, const Math::Interval<T>& v) const;
			T unnormalizeOut(const T& x, const Math::Interval<T>& v) const;

			void setData(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector);

			void checkNbDataNbParamsRatio(const Math::Interval<Size>& dataIInterval, int verbose = 1) const;

			StaticTable<void*, M::nbLayers> layerTable;

			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector;
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> expectedYVector;

			bool bNeedForwardPropagation;

			typename M::HiddenActivationFunc hiddenActivationFunc;
			typename M::ActivationFunc activationFunc;

			Size epochNum;
			T learningRateFactor;

			StaticTable<Math::Interval<T>, M::m[ 0 ][ 0 ]> normalizeFeatureTable;		// Used to compute the z-score. [mean, standard deviation].
			StaticTable<Math::Interval<T>, M::m[ M::nbLayers - Size(1) ][ 1 ]> normalizeOutTable;

			Mutex optimizeMutex;

			OS::Path filePath;
		};

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::DeepNeuralNetwork(const OptimizerFunc& optimizerFunc, const OS::Path& filePath) :
			bNeedForwardPropagation(true),
			epochNum(0),
			learningRateFactor(1.0),
			filePath(filePath)
		{
			static_assert( Utility::isBase<Model::BasicModel, M>::value, "Model type unknown." );
			static_assert( Utility::isBase<ActivationFunc::BasicActivationFunc, M::ActivationFunc>::value, "Model ActivationFunc type unknown." );
			static_assert( Utility::isBase<ActivationFunc::BasicActivationFunc, M::HiddenActivationFunc>::value, "Model HiddenActivationFunc type unknown." );
			static_assert( M::nbLayers > Size(0), "Model error, nbLayers cannot be 0." );
			_checkModel<Size(1)>();
			_constructNeuralLayer<Size(0)>(optimizerFunc);

			bool bIsLoaded(false);
			if ( this->filePath.getSize() ) {
				if ( loadFromFile(this->filePath, int(1)) ) {
					bIsLoaded = true;
				}
			}

			if ( !bIsLoaded ) {
				resetNormalizeTable();
			}

		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::~DeepNeuralNetwork() {
			_destructNeuralLayer<Size(0)>();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::addData(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) {
			this->optimizeMutex.lock();
			{
				this->featureVector.push(featureTable);
				normalizeFeature(this->featureVector.getLast());
				this->expectedYVector.push(outTable);
				normalizeOut(this->featureVector.getLast());
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::addData(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) {
			assert(featureTableVector.getSize() == outTableVector.getSize());
			this->optimizeMutex.lock();
			{
				Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureTableVectorCpy(featureTableVector);
				Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outTableVectorCpy(outTableVector);

				normalizeFeature(featureTableVectorCpy);
				normalizeOut(outTableVectorCpy);

				this->featureVector.concat(featureTableVector);
				this->expectedYVector.concat(outTableVector);
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::setData(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) {
			assert(featureTableVector.getSize() == outTableVector.getSize());
			this->optimizeMutex.lock();
			{
				this->featureVector = featureTableVector;
				this->expectedYVector = outTableVector;
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::checkNbDataNbParamsRatio(const Math::Interval<Size>& dataIInterval, int verbose) const {
			const T nbDataNbParamsRatio(T(dataIInterval.getSize()) / T(getNbParams()));

			if ( nbDataNbParamsRatio < T(1.0) ) {
				if ( verbose > -1 ) { Log::displayError(String::format("NbData (%) / NbParams (%) = %", dataIInterval.getSize(), getNbParams(), nbDataNbParamsRatio)); }
			} else if ( nbDataNbParamsRatio < T(2.0) ) {
				if ( verbose > -1 ) { Log::displayWarning(String::format("NbData (%) / NbParams (%) = %", dataIInterval.getSize(), getNbParams(), nbDataNbParamsRatio)); }
			} else {
				if ( verbose > 0 ) { Log::displaySuccess(String::format("NbData (%) / NbParams (%) = %", dataIInterval.getSize(), getNbParams(), nbDataNbParamsRatio)); }
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::addData(const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) {
			addData(data.getFeatures(), data.getOuts());
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::addData(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector(DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createFeatureVector(dataVector));
			const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outVector(DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createOutVector(dataVector));
			return addData(featureVector, outVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::clearData() {
			this->optimizeMutex.lock();
			{
				this->featureVector.clear();
				this->expectedYVector.clear();
				resetNormalizeTable();
				_setNbData<Size(0)>();
				this->bNeedForwardPropagation = true;
			}
			this->optimizeMutex.unlock();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeFeature() {
			normalizeFeature(Math::Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeFeature(const Math::Interval<Size>& dataIInterval) {

			assert(this->featureVector.getSize());

			// unnormalize first.
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				unnormalizeFeature(this->featureVector.getValueI(dataI));
			}

			//// Recompute the mean.
			//for ( Size featureI(0); featureI < this->normalizeFeatureTable.getSize(); featureI++ ) {
			//	this->normalizeFeatureTable[ featureI ].x = T(0);
			//}

			//for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
			//	StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(this->featureVector.getValueI(dataI));

			//	for ( Size featureI(0); featureI < featureTable.getSize(); featureI++ ) {
			//		T& v(featureTable[ featureI ]);
			//		Math::Interval<T>& i(this->normalizeFeatureTable[ featureI ]);

			//		i.x += v;
			//	}
			//}

			//const T sizeInverse(T(1) / T(dataIInterval.getSize()));
			//for ( Size featureI(0); featureI < this->normalizeFeatureTable.getSize(); featureI++ ) {
			//	this->normalizeFeatureTable[ featureI ].x *= sizeInverse;
			//}

			//// Recompute the standard deviation
			//for ( Size featureI(0); featureI < this->normalizeFeatureTable.getSize(); featureI++ ) {
			//	this->normalizeFeatureTable[ featureI ].y = T(0);
			//}

			//for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
			//	StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(this->featureVector.getValueI(dataI));

			//	for ( Size featureI(0); featureI < featureTable.getSize(); featureI++ ) {
			//		T& v(featureTable[ featureI ]);
			//		Math::Interval<T>& i(this->normalizeFeatureTable[ featureI ]);

			//		const T delta(v - i.x);
			//		i.y += delta * delta;
			//	}
			//}

			//for ( Size featureI(0); featureI < this->normalizeFeatureTable.getSize(); featureI++ ) {
			//	Math::Interval<T>& i(this->normalizeFeatureTable[ featureI ]);
			//	i.y = Math::sqrt(i.y * sizeInverse);
			//}

			const StaticTable<T, M::m[ 0 ][ 0 ]>& firstFeatureTable(this->featureVector.getValueI(dataIInterval.getBegin()));
			for ( Size outI(0); outI < this->normalizeFeatureTable.getSize(); outI++ ) {
				const T& x(firstFeatureTable[ outI ]);
				this->normalizeFeatureTable[ outI ].setBegin(x);
				this->normalizeFeatureTable[ outI ].setEnd(x);
			}

			for ( Size dataI(dataIInterval.getBegin() + Size(1)); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(this->featureVector.getValueI(dataI));

				for ( Size outI(0); outI < this->normalizeFeatureTable.getSize(); outI++ ) {
					const T& x(featureTable[ outI ]);

					if ( x < this->normalizeFeatureTable[ outI ].getBegin() ) {
						this->normalizeFeatureTable[ outI ].setBegin(x);
					} else if ( x > this->normalizeFeatureTable[ outI ].getEnd() ) {
						this->normalizeFeatureTable[ outI ].setEnd(x);
					}
				}
			}

			// Normalize
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				normalizeFeature(this->featureVector.getValueI(dataI));
			}

			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeOut() {
			normalizeOut(Math::Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeOut(const Math::Interval<Size>& dataIInterval) {

			assert(this->expectedYVector.getSize());

			// unnormalize first.
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				unnormalizeOut(this->expectedYVector.getValueI(dataI));
			}

			// Compute the min/max
			const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& firstExpectedYTable(this->expectedYVector.getValueI(dataIInterval.getBegin()));
			for ( Size outI(0); outI < this->normalizeOutTable.getSize(); outI++ ) {
				const T& expectedY(firstExpectedYTable[ outI ]);
				this->normalizeOutTable[ outI ].setBegin(expectedY);
				this->normalizeOutTable[ outI ].setEnd(expectedY);
			}

			for ( Size dataI(dataIInterval.getBegin() + Size(1)); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& expectedYTable(this->expectedYVector.getValueI(dataI));

				for ( Size outI(0); outI < this->normalizeOutTable.getSize(); outI++ ) {
					const T& expectedY(expectedYTable[ outI ]);

					if ( expectedY < this->normalizeOutTable[ outI ].getBegin() ) {
						this->normalizeOutTable[ outI ].setBegin(expectedY);
					} else if ( expectedY > this->normalizeOutTable[ outI ].getEnd() ) {
						this->normalizeOutTable[ outI ].setEnd(expectedY);
					}
				}
			}

			// Normalize
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				normalizeOut(this->expectedYVector.getValueI(dataI));
			}

			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeFeature(StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable) const {
			for ( Size featureI(0); featureI < featureTable.getSize(); featureI++ ) {
				T& v(featureTable[ featureI ]);

				v = normalizeFeature(v, this->normalizeFeatureTable[ featureI ]);

				/*if ( Utility::isNan(v) ) {
					Log::displayError(String::format("Normalization has generated an NaN : %, %.", v, this->normalizeFeatureTable[ featureI ].toString()));
				}*/
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeFeature(Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector) const {
			for ( Size dataI(0); dataI < featureTableVector.getSize(); dataI++ ) {
				normalizeFeature(featureTableVector.getValueI(dataI));
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::unnormalizeFeature(StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable) const {
			for ( Size featureI(0); featureI < featureTable.getSize(); featureI++ ) {
				T& v(featureTable[ featureI ]);

				v = unnormalizeFeature(v, this->normalizeFeatureTable[ featureI ]);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::unnormalizeFeature(Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector) const {
			for ( Size dataI(0); dataI < featureTableVector.getSize(); dataI++ ) {
				unnormalizeFeature(featureTableVector.getValueI(dataI));
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeOut(StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) const {
			for ( Size outI(0); outI < outTable.getSize(); outI++ ) {
				T& v(outTable[ outI ]);

				v = normalizeOut(v, this->normalizeOutTable[ outI ]);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeOut(Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const {
			for ( Size dataI(0); dataI < outTableVector.getSize(); dataI++ ) {
				normalizeOut(outTableVector.getValueI(dataI));
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::unnormalizeOut(StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) const {
			for ( Size outI(0); outI < outTable.getSize(); outI++ ) {
				T& v(outTable[ outI ]);

				v = unnormalizeOut(v, this->normalizeOutTable[ outI ]);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::unnormalizeOut(Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const {
			for ( Size dataI(0); dataI < outTableVector.getSize(); dataI++ ) {
				unnormalizeOut(outTableVector.getValueI(dataI));
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createFeatureVector(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureVector;
			featureVector.resize(dataVector.getSize());

			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data(dataVector.getValueI(dataI));
				featureVector.setValueI(dataI, data.getFeatures());
			}

			return featureVector;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createOutVector(const Vector<Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>>& dataVector) {
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outVector;
			outVector.resize(dataVector.getSize());

			for ( Size dataI(0); dataI < dataVector.getSize(); dataI++ ) {
				const Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data(dataVector.getValueI(dataI));
				outVector.setValueI(dataI, data.getOuts());
			}

			return outVector;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline const Size DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getNbData() const {
			return this->featureVector.getSize();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline constexpr Size DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getNbLayers() const {
			return M::nbLayers;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline constexpr Size DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getNbParams() const {
			return _getNbParams<Size(0)>();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline const OS::Path& DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getFilePath() const {
			return this->filePath;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::setFilePath(const OS::Path& filePath) {
			this->filePath = filePath;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::saveToFile(const OS::Path& filePath, int verbose) const {
			if ( !IO::write(filePath, this) ) {
				if ( verbose > -1 ) { Log::displayWarning(String::format("Unable to save the DeepNeuralNetwork to the file \"%\".", filePath)); }
				return false;
			}
			if ( verbose > 0 ) { Log::displayLog(String::format("Saved the DeepNeuralNetwork to the file \"%\".", filePath)); }
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::loadFromFile(const OS::Path& filePath, int verbose) {
			if ( !IO::read(filePath, this) ) {
				if ( verbose > -1 ) { Log::displayWarning(String::format("Unable to load the DeepNeuralNetwork from the file \"%\".", filePath)); }
				return false;
			}
			if ( verbose > 0 ) { Log::displayLog(String::format("Loaded the DeepNeuralNetwork from the file \"%\".", filePath)); }
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::saveToFile(int verbose) const {
			if ( this->filePath.getSize() ) {
				if ( !saveToFile(this->filePath, verbose) ) {
					return false;
				}
			}
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::loadFromFile(int verbose) {
			if ( this->filePath.getSize() ) {
				if ( !loadFromFile(this->filePath, verbose) ) {
					return false;
				}
			}
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagation() {
			if ( this->bNeedForwardPropagation ) {
				computeForwardPropagation(Math::Interval<Size>(Size(0), getNbData()));
				this->bNeedForwardPropagation = false;
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval) {
			_computeForwardPropagation<Size(0)>(dataIInterval);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagationS(const Size dataIBegin) {
			_computeForwardPropagationS<Size(0)>(dataIBegin);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagation(const Size dataI) {
			_computeForwardPropagation<Size(0)>(dataI);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagation(const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable) const {
			StaticTable<T, M::m[ 0 ][ 0 ]> featureTableNormalized(featureTable);
			normalizeFeature(featureTableNormalized);
			_computeForwardPropagation<Size(0)>(featureTableNormalized, outTable);
			unnormalizeOut(outTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagation(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const {
			outTableVector.resize(featureTableVector.getSize());

			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureTableVectorNormalized(featureTableVector);
			normalizeFeature(featureTableVectorNormalized);
			_computeForwardPropagation<Size(0)>(featureTableVectorNormalized, outTableVector);
			unnormalizeOut(outTableVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeForwardPropagation(Data<T, M::m[ 0 ][ 0 ], M::m[ M::nbLayers - Size(1) ][ 1 ]>& data) const {
			const StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(data.getFeatures());
			StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTable(data.getOuts());
			computeForwardPropagation(featureTable, outTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			_computeBackPropagation<M::nbLayers - Size(1)>(dataIInterval);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeBackPropagationS(const Size dataIBegin) {
			_computeBackPropagationS<M::nbLayers - Size(1)>(dataIBegin);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline const Size DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getEpoch() const {
			return this->epochNum;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::setEpoch(const Size epochNum) {
			this->epochNum = epochNum;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::setLearningRateFactor(const T& learningRateFactor) {
			this->learningRateFactor = learningRateFactor;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline const T& DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getLearningRateFactor() const {
			return this->learningRateFactor;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::copyParamMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork) {
			_copyParamMat<Size(0)>(deepNeuralNetwork);
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::copyGradMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork) {
			_copyGradMat<Size(0)>(deepNeuralNetwork);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::copyOptimizerFunc(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork) {
			_copyOptimizerFunc<Size(0)>(deepNeuralNetwork);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::resetParams() {
			_resetParams<Size(0)>();
			setLearningRateFactor(T(1.0));
			setEpoch(Size(0));
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::resetOptimizerFunc() {
			_resetOptimizerFunc<Size(0)>();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::resetAll() {
			resetParams();
			clearData();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::setParamMat(const Mat<T>& paramMat) {
			getLayer<I>()->setParamMat(paramMat);
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::setGradMat(const Mat<T>& gradMat) {
			getLayer<I>()->setGradMat(gradMat);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::optimize(const Math::Interval<Size>& dataIInterval) {
			computeGrad(dataIInterval);
			updateModel(getLearningRateFactor());
			setEpoch(getEpoch() + Size(1));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::optimizeStochastic(const Vector<Math::Interval<Size>>& dataIIntervalVector) {
			for ( Size i(0); i < dataIIntervalVector.getSize(); i++ ) {
				const Math::Interval<Size>& dataIInterval(dataIIntervalVector.getValueI(i));
				assert(dataIInterval.getSize() == M::dataChunkSize);
				computeGradS(dataIInterval.getBegin());
				updateModel(getLearningRateFactor());
			}
			setEpoch(getEpoch() + Size(1));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::optimizeStochastic(const Math::Interval<Size>& dataIInterval, const Size nbIterations, const Time::Duration<Time::MilliSecond>& saveDuration, const Math::Interval<Size>& statsDataIInterval, int verbose) {

			const GetPercent getPercent(nbIterations);

			if ( verbose > 0 ) { Log::startStep(String::format("Starting stochastic optimisation with % iterations over % data...", nbIterations, dataIInterval.toString())); }

			checkNbDataNbParamsRatio(dataIInterval, verbose);

			if ( getEpoch() == Size(0) ) {
				if ( verbose > 0 ) { Log::startStep("Starting from epochNum #0, reseting params..."); }
				resetParams();
				if ( verbose > 0 ) { Log::endStep("Done."); }
			} else {
				if ( verbose > 0 ) { Log::displayLog(String::format("Resuming from epoch #%.", getEpoch())); }
			}

			const Math::Interval<Size> statsDataIIntervalSafe(statsDataIInterval.getBegin(), Math::min(statsDataIInterval.getEnd(), getNbData()));
			T lastMSE(computeMeanSquaredError(statsDataIIntervalSafe));
			T lastCOD(computeCoefficientOfDetermination(statsDataIIntervalSafe) * T(100));
			if ( verbose > 0 ) { Log::displayLog(String::format("Initial MSE of % and coeficient of determination of %%.", lastMSE, lastCOD)); }

			// Compute the interval sizes.
			Vector<Math::Interval<Size>> dataIIntervalVector(DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createDataIntervalVector(dataIInterval));

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLast(timePointBegin.getValue());

			if ( verbose > 0 ) { Log::startStep(String::format("Starting gradient descent loop with % iterations and a break every %s...", nbIterations, float(saveDuration.getValue()) * float(0.001))); }

			this->optimizeMutex.lock();

			// Run
			for ( Size iterationI(0); iterationI < nbIterations; iterationI++ ) {

				// Optimize !
				optimizeStochastic(dataIIntervalVector);

				// Saving
				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				const Time::Duration<Time::MilliSecond> elapsedDuration(timePointNow - timePointLast);
				if ( elapsedDuration > saveDuration ) {

					saveToFile(verbose);

					const T newMSE(computeMeanSquaredError(statsDataIIntervalSafe));
					const T deltaMSE(newMSE - lastMSE);
					lastMSE = newMSE;
					const T newCOD(computeCoefficientOfDetermination(statsDataIIntervalSafe) * T(100));
					const T deltaCOD(newCOD - lastCOD);
					lastCOD = newCOD;

					/*if ( deltaMSE > T(0) ) {
						break;
					}*/

					if ( verbose > 1 ) { Log::displayLog(String::format("[%/%][ElapsedTime: %s][epochNum #%] : Finished loop with a MSE of % (%) and a coeficient of determination of %/% (%%).",
														 getPercent(iterationI),
														 float(elapsedDuration.getValue()) * float(0.001),
														 getEpoch(),
														 lastMSE,
														 deltaMSE,
														 lastCOD,
														 deltaCOD), Log::MessageColor::DarkWhite); }

					timePointLast.setValue(timePointNow.getValue());
				}
			}

			this->optimizeMutex.unlock();

			Time::Duration<Time::MilliSecond> totalElapsedDuration(Time::getTime<Time::MilliSecond>() - timePointBegin);
			if ( verbose > 0 ) { Log::endStep(String::format("Done in %s.", float(totalElapsedDuration.getValue()) * float(0.001))); }

			saveToFile(verbose);

			if ( verbose > 0 ) { Log::endStepSuccess(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeMeanSquaredError(statsDataIIntervalSafe), computeCoefficientOfDetermination(statsDataIIntervalSafe) * T(100))); }
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::optimizeCluster(const Math::Interval<Size>& dataIInterval, const Size nbIterations, const Size nbSearchThreads, const Time::Duration<Time::MilliSecond>& saveDuration, const Math::Interval<Size>& statsDataIInterval, int verbose) {

			class SearchThread : public DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>, public Thread {
			public:
				SearchThread(const OptimizerFunc& optimizerFunc) :
					DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>(optimizerFunc)
				{}

				void init() {
					this->dataIIntervalVector = DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createDataIntervalVector(Math::Interval<Size>(Size(0), getNbData()));
				}

				void run() override {
					for ( Size i(0); i < this->dataIIntervalVector.getSize(); i++ ) {
						const Math::Interval<Size>& dataIInterval(this->dataIIntervalVector.getValueI(i));

						{
							assert(dataIInterval.getSize() == M::dataChunkSize);
							computeGradS(dataIInterval.getBegin());
							updateModel(getLearningRateFactor());
						}

					}
				}

			private:
				Vector<Math::Interval<Size>> dataIIntervalVector;
				Size intervalI;
			};

			// using SearchThread = SearchThread<T, M, OptimizerFunc, NbThreads>;
			const GetPercent getPercent(nbIterations);

			if ( verbose > 0 ) { Log::startStep(String::format("Starting clustered gradient descent with % iterations over % data...", nbIterations, dataIInterval.toString())); }

			checkNbDataNbParamsRatio(dataIInterval, verbose);

			// Creating the threads
			Vector<SearchThread*> searchThreadVector(nbSearchThreads);
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				searchThreadVector.setValueI(i, new SearchThread(OptimizerFunc()));
			}

			if ( verbose > 0 ) { Log::startStep("Dispatching data to the threads..."); }

			this->optimizeMutex.lock();

			// Dispatch data into Clusters.
			Vector<Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>> featureTableVectorVector(searchThreadVector.getSize());
			Vector<Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>> outTableVectorVector(searchThreadVector.getSize());
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector(featureTableVectorVector.getValueI(i));
				Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector(outTableVectorVector.getValueI(i));

				featureTableVector.reserve(dataIInterval.getSize() / searchThreadVector.getSize() + Size(1));
				outTableVector.reserve(dataIInterval.getSize() / searchThreadVector.getSize() + Size(1));
			}
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const Size searchThreadI(dataI% searchThreadVector.getSize());
				SearchThread* searchThread(searchThreadVector.getValueI(searchThreadI));

				Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector(featureTableVectorVector.getValueI(searchThreadI));
				Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector(outTableVectorVector.getValueI(searchThreadI));

				featureTableVector.push(this->featureVector.getValueI(dataI));
				outTableVector.push(this->expectedYVector.getValueI(dataI));
			}
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				SearchThread* searchThread(searchThreadVector.getValueI(i));
				const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector(featureTableVectorVector.getValueI(i));
				const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector(outTableVectorVector.getValueI(i));

				searchThread->addData(featureTableVector, outTableVector);
			}

			this->optimizeMutex.unlock();

			if ( verbose > 0 ) { Log::endStep("Done."); }

			if ( getEpoch() == Size(0) ) {
				if ( verbose > 0 ) { Log::startStep("Starting from epochNum #0, randomizing params..."); }
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->resetParams();
					searchThread->copyOptimizerFunc(*this);
				}
				if ( verbose > 0 ) { Log::endStep("Done."); }
			} else {
				if ( verbose > 0 ) { Log::startStep(String::format("Resuming from epoch #%. Copying params to the threads...", getEpoch())); }
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->copyParamMat(*this);
					searchThread->copyOptimizerFunc(*this);
					searchThread->setLearningRateFactor(getLearningRateFactor());
					searchThread->setEpoch(getEpoch());
				}
				if ( verbose > 0 ) { Log::endStep("Done."); }
			}

			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				SearchThread* searchThread(searchThreadVector.getValueI(i));
				searchThread->init();
			}

			const Math::Interval<Size> statsDataIIntervalSafe(statsDataIInterval.getBegin(), Math::min(statsDataIInterval.getEnd(), getNbData()));
			T lastMSE(computeMeanSquaredError(statsDataIIntervalSafe));
			T lastCOD(computeCoefficientOfDetermination(statsDataIIntervalSafe)* T(100));
			if ( verbose > 0 ) { Log::displayLog(String::format("Initial MSE of % and coeficient of determination of %%.", lastMSE, lastCOD)); }

			if ( verbose > 0 ) { Log::startStep(String::format("Starting gradient descent loop with % iterations and a break every % ms...", nbIterations, float(saveDuration.getValue()) * float(0.001))); }

			Time::TimePointMS timePointBegin(Time::getTime<Time::MilliSecond>());
			Time::TimePointMS timePointLast(timePointBegin.getValue());

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

				// updateModel(searchThreadVector, getLearningRateFactor());
				_setParamMatMean<Size(0)>(searchThreadVector);
				for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
					SearchThread* searchThread(searchThreadVector.getValueI(i));
					searchThread->copyParamMat(*this);
				}

				setEpoch(getEpoch() + Size(1));
				copyOptimizerFunc(*searchThreadVector.getFirst());

				Time::TimePointMS timePointNow(Time::getTime<Time::MilliSecond>());
				const Time::Duration<Time::MilliSecond> elapsedDuration(timePointNow - timePointLast);
				if ( elapsedDuration > saveDuration ) {
					saveToFile(verbose);

					const T newMSE(computeMeanSquaredError(statsDataIIntervalSafe));
					const T deltaMSE(newMSE - lastMSE);
					lastMSE = newMSE;
					const T newCOD(computeCoefficientOfDetermination(statsDataIIntervalSafe) * T(100));
					const T deltaCOD(newCOD - lastCOD);
					lastCOD = newCOD;

					if ( deltaMSE > T(0) ) {
						// setLearningRateFactor(getLearningRateFactor() * T(0.5));
						for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
							SearchThread* searchThread(searchThreadVector.getValueI(i));
							searchThread->setLearningRateFactor(getLearningRateFactor());
						}
					}

					if ( verbose > 1 ) {
						Log::displayLog(String::format("[%/%][ElapsedTime: %s][epochNum #%][LearningRateFactor: %] : Finished loop with a MSE of % (%) and a coeficient of determination of %/% (%%).",
										getPercent(iterationI),
										float(elapsedDuration.getValue()) * float(0.001),
										getEpoch(),
										getLearningRateFactor(),
										lastMSE,
										deltaMSE,
										lastCOD,
										deltaCOD), Log::MessageColor::DarkWhite);
					}

					timePointLast.setValue(timePointNow.getValue());
				}
			}

			Time::Duration<Time::MilliSecond> totalElapsedDuration(Time::getTime<Time::MilliSecond>() - timePointBegin);
			if ( verbose > 0 ) { Log::endStep(String::format("Done in %s.", float(totalElapsedDuration.getValue()) * float(0.001))); }

			saveToFile(verbose);

			// Deleting the threads.
			for ( Size i(0); i < searchThreadVector.getSize(); i++ ) {
				delete searchThreadVector.getValueI(i);
			}

			if ( verbose > 0 ) { Log::endStepSuccess(String::format("Finished with a cost of % and a coeficient of determination of %%.", computeMeanSquaredError(statsDataIIntervalSafe), computeCoefficientOfDetermination(statsDataIIntervalSafe) * T(100))); }
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeGrad(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			computeBackPropagation(dataIInterval);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeGradS(const Size dataIBegin) {
			computeForwardPropagationS(dataIBegin);
			computeBackPropagationS(dataIBegin);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline Vector<Math::Interval<Size>> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::createDataIntervalVector(const Math::Interval<Size>& dataIInterval) {
			Vector<Math::Interval<Size>> dataIntervalVector;

			constexpr Size intervalSize(M::dataChunkSize);

			for ( Size i(dataIInterval.getBegin() + intervalSize); i < dataIInterval.getEnd(); i += intervalSize ) {
				Math::Interval<Size> newInterval(i - intervalSize, i);
				dataIntervalVector.push(newInterval);
			}

			return dataIntervalVector;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::updateModel(const T& learningRateFactor) {
			_updateModel<Size(0)>(learningRateFactor);
			this->bNeedForwardPropagation = true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::updateModel(const Vector<DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>*>& deepNeuralNetworkVector, const T& learningRateFactor) {
			for ( Size i(0); i < deepNeuralNetworkVector.getSize(); i++ ) {
				DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>* deepNeuralNetwork(deepNeuralNetworkVector.getValueI(i));

				copyGradMat(*deepNeuralNetwork);
				updateModel(learningRateFactor);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCostLogF(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTable, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTable) const {
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outTable(featureTable.getSize());
			computeForwardPropagation(featureTable, outTable);
			return getLayer<M::nbLayers - Size(1)>()->computeCostLog(Math::Interval<Size>(Size(0), featureTable.getSize()), outTable, expectedOutTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCostLog(const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTable, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTable) const {
			return getLayer<M::nbLayers - Size(1)>()->computeCostLog(Math::Interval<Size>(Size(0), outTable.getSize()), outTable, expectedOutTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCostLog(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCostLog(dataIInterval, getLayer<M::nbLayers - Size(1)>()->getOutVector(), this->expectedYVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCostLog() {
			return computeCostLog(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeMeanSquaredErrorF(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTable, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTable) const {
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outTable(featureTable.getSize());
			computeForwardPropagation(featureTable, outTable);
			return getLayer<M::nbLayers - Size(1)>()->computeMeanSquaredError(Math::Interval<Size>(Size(0), featureTable.getSize()), outTable, expectedOutTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeMeanSquaredError(const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTable, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTable) const {
			return getLayer<M::nbLayers - Size(1)>()->computeMeanSquaredError(Math::Interval<Size>(Size(0), outTable.getSize()), outTable, expectedOutTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeMeanSquaredError(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeMeanSquaredError(dataIInterval, getLayer<M::nbLayers - Size(1)>()->getOutVector(), this->expectedYVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeMeanSquaredError() {
			return computeMeanSquaredError(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCoefficientOfDeterminationF(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTableVector) const {
			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outTableVector(featureTableVector.getSize());
			computeForwardPropagation(featureTableVector, outTableVector);
			return getLayer<M::nbLayers - Size(1)>()->computeCoefficientOfDetermination(Math::Interval<Size>(Size(0), featureTableVector.getSize()), outTableVector, expectedOutTableVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCoefficientOfDetermination(const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTable, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& expectedOutTable) const {
			return getLayer<M::nbLayers - Size(1)>()->computeCoefficientOfDetermination(Math::Interval<Size>(Size(0), outTable.getSize()), outTable, expectedOutTable);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			return getLayer<M::nbLayers - Size(1)>()->computeCoefficientOfDetermination(dataIInterval, getLayer<M::nbLayers - Size(1)>()->getOutVector(), this->expectedYVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeCoefficientOfDetermination() {
			return computeCoefficientOfDetermination(Interval<Size>(Size(0), getNbData()));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline StaticTable<T, M::m[ 0 ][ 0 ]> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeFeatureImportance(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector) const {
			StaticTable<T, M::m[ 0 ][ 0 ]> featureImportanceTable;

			Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>> outTableVector(featureTableVector.getSize());
			computeFeatureImportanceF(featureTable, outTableVector);

			return computeFeatureImportance(featureTableVector, outTableVector);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline StaticTable<T, M::m[ 0 ][ 0 ]> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeFeatureImportance(const Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>& featureTableVector, const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector) const {
			StaticTable<T, M::m[ 0 ][ 0 ]> featureImportanceTable;

			const T baseMeanSquaredError(computeMeanSquaredErrorF(featureTableVector, outTableVector));

			Vector<StaticTable<T, M::m[ 0 ][ 0 ]>> featureTableVectorCpy(featureTableVector.getSize());

			for ( Size featureI(0); featureI < M::m[ 0 ][ 0 ]; featureI++ ) {
				Utility::copy(featureTableVectorCpy.getData(), featureTableVector.getData(), featureTableVector.getSize());

				Math::Interval<T> featureMinMax(featureTableVectorCpy.getFirst()[ featureI ], featureTableVectorCpy.getFirst()[ featureI ]);
				for ( Size dataI(1); dataI < featureTableVectorCpy.getSize(); dataI++ ) {
					StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(featureTableVectorCpy.getValueI(dataI));
					const T& v(featureTable[ featureI ]);

					if ( v < featureMinMax.getBegin() ) {
						featureMinMax.setBegin(v);
					} else if ( v > featureMinMax.getEnd() ) {
						featureMinMax.setEnd(v);
					}
				}

				for ( Size dataI(0); dataI < featureTableVectorCpy.getSize(); dataI++ ) {
					StaticTable<T, M::m[ 0 ][ 0 ]>& featureTable(featureTableVectorCpy.getValueI(dataI));

					featureTable[ featureI ] = featureMinMax.unscale(Math::randomF());
				}

				const T featureMeanSquaredError(computeMeanSquaredErrorF(featureTableVectorCpy, outTableVector));

				const T featureImportance(T(1) - baseMeanSquaredError / featureMeanSquaredError);

				featureImportanceTable[ featureI ] = featureImportance;
			}

			return featureImportanceTable;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline StaticTable<T, M::m[ 0 ][ 0 ]> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeFeatureImportance(const Math::Interval<Size>& dataIInterval) {
			computeForwardPropagation(dataIInterval);
			const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector(getLayer < M::nbLayers - Size(1) >()->getOutVector());

			return computeFeatureImportance(Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>(this->featureVector.getIterator(dataIInterval.getBegin()), this->featureVector.getIterator(dataIInterval.getEnd())),
											Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>(outTableVector.getIterator(dataIInterval.getBegin()), outTableVector.getIterator(dataIInterval.getEnd())));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline StaticTable<T, M::m[ 0 ][ 0 ]> DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::computeFeatureImportance() {
			computeForwardPropagation();
			const Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVector(getLayer< M::nbLayers - Size(1) >()->getOutVector());

			return computeFeatureImportance(Vector<StaticTable<T, M::m[ 0 ][ 0 ]>>(this->featureVector),
											Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>(outTableVector));
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::resetNormalizeTable() {
			for ( Size featureI(0); featureI < this->normalizeFeatureTable.getSize(); featureI++ ) {
				Math::Interval<T>& i(this->normalizeFeatureTable.getValueI(featureI));
				i.x = T(0.0);
				i.y = T(1.0);
			}

			for ( Size outI(0); outI < this->normalizeOutTable.getSize(); outI++ ) {
				Math::Interval<T>& i(this->normalizeOutTable.getValueI(outI));
				i.x = T(0.0);
				i.y = T(1.0);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeFeature(const T& x, const Math::Interval<T>& v) const {
			// return ( x - v.x ) / v.y;
			return v.scale(x);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::unnormalizeFeature(const T& x, const Math::Interval<T>& v) const {
			// return x * v.y + v.x;
			return v.unscale(x);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::normalizeOut(const T& x, const Math::Interval<T>& v) const {
			return v.scale(x);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		inline T DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::unnormalizeOut(const T& x, const Math::Interval<T>& v) const {
			return v.unscale(x);
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline const NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getLayer() const {
			return const_cast< DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads> * >( this )->getLayer<I>();
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::getLayer() {
			return reinterpret_cast< NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* >( this->layerTable[ I ] );
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<typename Stream>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::read(Stream* stream) {
			Size nbLayers;
			if ( !IO::read(stream, &nbLayers) ) {
				return false;
			}
			if ( nbLayers != getNbLayers() ) {
				Log::displayError(String::format("Trying to read a DeepNeuralNetwork of the wrong number of layers : this[ % ] != read[ % ].", getNbLayers(), nbLayers));
				return false;
			}
			if ( !_read<Size(0)>(stream) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->featureVector) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->expectedYVector) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->hiddenActivationFunc) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->activationFunc) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->epochNum) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->learningRateFactor) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->normalizeFeatureTable) ) {
				resetAll();
				return false;
			}
			if ( !IO::read(stream, &this->normalizeOutTable) ) {
				resetAll();
				return false;
			}
			_setNbData<Size(0)>();
			this->bNeedForwardPropagation = true;
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<typename Stream>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::write(Stream* stream) const {
			const Size nbLayers(getNbLayers());
			if ( !IO::write(stream, &nbLayers) ) {
				return false;
			}
			if ( !_write<Size(0)>(stream) ) {
				return false;
			}
			if ( !IO::write(stream, &this->featureVector) ) {
				return false;
			}
			if ( !IO::write(stream, &this->expectedYVector) ) {
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
			if ( !IO::write(stream, &this->normalizeFeatureTable) ) {
				return false;
			}
			if ( !IO::write(stream, &this->normalizeOutTable) ) {
				return false;
			}
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeForwardPropagation(const Size dataI) {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I == M::nbLayers - Size(1) ) {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(dataI, this->activationFunc);
				} else {
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(dataI, this->hiddenActivationFunc);
				}

				_computeForwardPropagation<I + Size(1)>(dataI);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeForwardPropagation(const Math::Interval<Size>& dataIInterval) {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I == M::nbLayers - Size(1) ) {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(dataIInterval, this->activationFunc);
				} else {
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(dataIInterval, this->hiddenActivationFunc);
				}

				_computeForwardPropagation<I + Size(1)>(dataIInterval);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeForwardPropagationS(const Size dataIBegin) {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I == M::nbLayers - Size(1) ) {
					getLayer<I>()->computeForwardPropagationS<M::ActivationFunc, M::dataChunkSize>(dataIBegin, this->activationFunc);
				} else {
					getLayer<I>()->computeForwardPropagationS<M::HiddenActivationFunc, M::dataChunkSize>(dataIBegin, this->hiddenActivationFunc);
				}

				_computeForwardPropagationS<I + Size(1)>(dataIBegin);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeForwardPropagation(const StaticTable<T, M::m[ I ][ 0 ]>& featureTable, StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>& outTableFinal) const {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I < M::nbLayers - Size(1) ) {
					StaticTable<T, M::m[ I ][ 1 ]> outTable;
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(featureTable, outTable, this->hiddenActivationFunc);
					return _computeForwardPropagation<I + Size(1)>(outTable, outTableFinal);
				} else {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(featureTable, outTableFinal, this->activationFunc);
				}
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeForwardPropagation(const Vector<StaticTable<T, M::m[ I ][ 0 ]>>& featureTableVector, Vector<StaticTable<T, M::m[ M::nbLayers - Size(1) ][ 1 ]>>& outTableVectorFinal) const {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I < M::nbLayers - Size(1) ) {
					Vector<StaticTable<T, M::m[ I ][ 1 ]>> outTableVector(outTableVectorFinal.getSize());
					getLayer<I>()->computeForwardPropagation<M::HiddenActivationFunc>(Math::Interval<Size>(Size(0), featureTableVector.getSize()), featureTableVector, outTableVector, this->hiddenActivationFunc);
					return _computeForwardPropagation<I + Size(1)>(outTableVector, outTableVectorFinal);
				} else {
					getLayer<I>()->computeForwardPropagation<M::ActivationFunc>(Math::Interval<Size>(Size(0), featureTableVector.getSize()), featureTableVector, outTableVectorFinal, this->activationFunc);
				}
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			if constexpr ( I >= Size(0) ) {
				NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* neuralLayer(getLayer<I>());

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

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_computeBackPropagationS(const Size dataIBegin) {
			if constexpr ( I >= Size(0) ) {
				NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>* neuralLayer(getLayer<I>());

				// Compute dZx
				if constexpr ( I == M::nbLayers - Size(1) ) {
					neuralLayer->computeDeltasLastS<M::dataChunkSize>(dataIBegin, this->expectedYVector);
				} else {
					neuralLayer->computeDeltasS<M::m[ I + Size(1) ][ 0 ], M::m[ I + Size(1) ][ 1 ], M::HiddenActivationFunc, M::dataChunkSize>(dataIBegin, *getLayer<I + Size(1)>(), this->hiddenActivationFunc);
				}

				neuralLayer->computeBackPropagationS<M::dataChunkSize>(dataIBegin);
			}
			if constexpr ( I > Size(0) ) {
				return _computeBackPropagationS<I - Size(1)>(dataIBegin);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_updateModel(const T& learningRateFactor) {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->updateModel(learningRateFactor, this->epochNum);

				return _updateModel<I + Size(1)>(learningRateFactor);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_constructNeuralLayer(const OptimizerFunc& optimizerFunc) {
			if constexpr ( I < M::nbLayers ) {
				const Vector<StaticTable<T, M::m[ I ][ 0 ]>>* inVector;
				if constexpr ( I == Size(0) ) {
					inVector = &this->featureVector;
				} else {
					inVector = &getLayer<I - Size(1)>()->getOutVector();
				}
				this->layerTable[ I ] = reinterpret_cast< void* >( new NeuralLayerMT<T, M::m[ I ][ 0 ], M::m[ I ][ 1 ], OptimizerFunc, NbThreads>(inVector, optimizerFunc) );
				_constructNeuralLayer<I + Size(1)>(optimizerFunc);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_destructNeuralLayer() {
			if constexpr ( I < M::nbLayers ) {
				delete getLayer<I>();

				return _destructNeuralLayer<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline constexpr bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_checkModel() const {
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

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_setNbData() {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->setNbData(getNbData());
				_setNbData<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_resetParams() {
			if constexpr ( I < M::nbLayers ) {
				if constexpr ( I == M::nbLayers - Size(1) ) {
					getLayer<I>()->resetParams<M::ActivationFunc>(this->activationFunc);
				} else {
					getLayer<I>()->resetParams<M::HiddenActivationFunc>(this->hiddenActivationFunc);
				}
				_resetParams<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_resetOptimizerFunc() {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->resetOptimizerFunc();
				_resetOptimizerFunc<I + Size(1)>();
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_setParamMatMean(const Vector<DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>*>& deepNeuralNetworkVector) {
			if constexpr ( I < M::nbLayers ) {
				Mat<T> paramMatSum(M::m[ I ][ 1 ], M::m[ I ][ 0 ] + Size(1));

				paramMatSum.zeros();

				for ( Size i(0); i < deepNeuralNetworkVector.getSize(); i++ ) {
					const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>* deepNeuralNetwork(deepNeuralNetworkVector.getValueI(i));
					paramMatSum += deepNeuralNetwork->getLayer<I>()->getParamMat();
				}

				paramMatSum /= T(deepNeuralNetworkVector.getSize());

				setParamMat<I>(paramMatSum);

				_setParamMatMean<I + Size(1)>(deepNeuralNetworkVector);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_setGradMatMean(const Vector<DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>*>& deepNeuralNetworkVector) {
			if constexpr ( I < M::nbLayers ) {
				Mat<T> gradMatSum(M::m[ I ][ 1 ], M::m[ I ][ 0 ] + Size(1));

				gradMatSum.zeros();

				for ( Size i(0); i < deepNeuralNetworkVector.getSize(); i++ ) {
					const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>* deepNeuralNetwork(deepNeuralNetworkVector.getValueI(i));
					gradMatSum += deepNeuralNetwork->getLayer<I>()->getParamMat();
				}

				gradMatSum /= T(deepNeuralNetworkVector.getSize());

				setGradMat<I>(gradMatSum);

				_setGradMatMean<I + Size(1)>(deepNeuralNetworkVector);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_copyParamMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork) {
			if constexpr ( I < M::nbLayers ) {
				setParamMat<I>(deepNeuralNetwork.getLayer<I>()->getParamMat());
				// getLayer<I>()->resetOptimizerFunc();
				_copyParamMat<I + Size(1)>(deepNeuralNetwork);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_copyGradMat(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork) {
			if constexpr ( I < M::nbLayers ) {
				setGradMat<I>(deepNeuralNetwork.getLayer<I>()->getGradMat());
				_copyGradMat<I + Size(1)>(deepNeuralNetwork);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline void DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_copyOptimizerFunc(const DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>& deepNeuralNetwork) {
			if constexpr ( I < M::nbLayers ) {
				getLayer<I>()->setOptimizerFunc(deepNeuralNetwork.getLayer<I>()->getOptimizerFunc());
				_copyOptimizerFunc<I + Size(1)>(deepNeuralNetwork);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I>
		inline constexpr Size DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_getNbParams() const {
			if constexpr ( I < M::nbLayers ) {
				return getLayer<I>()->getNbParams() + _getNbParams<I + Size(1)>();
			} else {
				return Size(0);
			}
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I, typename Stream>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_write(Stream* stream) const {
			if constexpr ( I < M::nbLayers ) {
				if ( !IO::write(stream, getLayer<I>()) ) {
					return false;
				}

				return _write<I + Size(1)>(stream);
			}
			return true;
		}

		template<typename T, typename M, typename OptimizerFunc, Size NbThreads>
		template<Size I, typename Stream>
		inline bool DeepNeuralNetwork<T, M, OptimizerFunc, NbThreads>::_read(Stream* stream) {
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