#pragma once

#include "../../Thread.h"
#include "NeuralLayer.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads = Size(16)>
		class NeuralLayerMT : public NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc> {
		public:
			NeuralLayerMT(const Vector<StaticTable<T, NbFeatures>>* inTableVector, const OptimizerFunc& optimizerFunc);

			constexpr Size getNbThreads() const;

			void setNbData(const Size nbData);

			using NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation;
			template<typename ActivationFunc>
			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const ActivationFunc& activationFunc);
			template<typename ActivationFunc>
			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbFeatures>>& featureTableVector, Vector<StaticTable<T, NbNeurons>>& outTableVector, const ActivationFunc& activationFunc) const;

			template<typename ActivationFunc>
			void _runComputeForwardPropagation(const Math::Interval<Size>* dataIInterval, const Vector<StaticTable<T, NbFeatures>>* featureTableVector, Vector<StaticTable<T, NbNeurons>>* outTableVector, const ActivationFunc* activationFunc);

			void test(const int * i);

			static void createIntervalTable(const Math::Interval<Size>& interval, StaticTable<Math::Interval<Size>, NbThreads>& outTable);

		private:
			StaticTable<Math::Interval<Size>, NbThreads> neuronIIntervalTable;
			StaticTable<Math::Interval<Size>, NbThreads> dataIIntervalTable;
		};

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		inline NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::NeuralLayerMT(const Vector<StaticTable<T, NbFeatures>>* inTableVector, const OptimizerFunc& optimizerFunc) :
			NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>(inTableVector, optimizerFunc)
		{
			static_assert( NbNeurons % NbThreads == Size(0), "NbNeurons is not a multiple of NbThreads" );

			for ( Size i(0); i < getNbThreads(); i++ ) {
				neuronIIntervalTable[ i ].setBegin(getNbNeurons() / getNbThreads() * i);
				neuronIIntervalTable[ i ].setEnd(getNbNeurons() / getNbThreads() * (i + Size(1)));
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		inline constexpr Size NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::getNbThreads() const {
			return NbThreads;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::setNbData(const Size nbData) {
			NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setNbData(nbData);

			NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::createIntervalTable(Math::Interval<Size>(Size(0), nbData), this->dataIIntervalTable);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::test(const int * i) {
			
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::createIntervalTable(const Math::Interval<Size>& interval, StaticTable<Math::Interval<Size>, NbThreads>& outTable) {
			Vector<Math::Interval<Size>> intervalVector(interval.split(NbThreads));

			Size i(0);
			for ( ; i < intervalVector.getSize(); i++ ) {
				outTable[ i ] = intervalVector.getValueI(i);
			}
			for ( ; i < NbThreads; i++ ) {
				outTable[ i ] = Math::Interval<Size>(Size(0), Size(0));
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		template<typename ActivationFunc>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const ActivationFunc& activationFunc) {
			computeForwardPropagation(dataIInterval, getInVector(), getOutVector(), activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		template<typename ActivationFunc>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbFeatures>>& featureTableVector, Vector<StaticTable<T, NbNeurons>>& outTableVector, const ActivationFunc& activationFunc) const {
			if constexpr ( NbThreads <= Size(1) ) {
				return NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(dataIInterval, featureTableVector, outTableVector, activationFunc);
			} else {
				StaticTable<std::thread, NbThreads> threadTable;
				for ( Size i(0); i < getNbThreads(); i++ ) {
					threadTable[ i ] = std::thread(&NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::_runComputeForwardPropagation< ActivationFunc>,
												   const_cast< NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads> * >( this ),
												   &this->dataIIntervalTable[i],
												   &featureTableVector,
												   &outTableVector,
												   &activationFunc);
				}
				for ( Size i(0); i < getNbThreads(); i++ ) {
					threadTable[ i ].join();
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		template<typename ActivationFunc>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::_runComputeForwardPropagation(const Math::Interval<Size>* dataIInterval, const Vector<StaticTable<T, NbFeatures>>* featureTableVector, Vector<StaticTable<T, NbNeurons>>* outTableVector, const ActivationFunc* activationFunc) {
			NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(*dataIInterval, *featureTableVector, *outTableVector, *activationFunc);
		}

	}

}