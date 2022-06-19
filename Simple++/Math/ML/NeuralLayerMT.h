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

			template<typename ActivationFunc>
			const StaticTable<T, NbNeurons>& computeForwardPropagation(const Size dataI, const ActivationFunc& activationFunc);
			template<typename ActivationFunc>
			void computeForwardPropagation(const StaticTable<T, NbFeatures>& featureTable, StaticTable<T, NbNeurons>& outTable, const ActivationFunc& activationFunc) const;

			template<typename ActivationFunc>
			void _runComputeForwardPropagation(const StaticTable<T, NbFeatures>* featureTable, StaticTable<T, NbNeurons>* outTable, const ActivationFunc* activationFunc, const Math::Interval<Size> * neuronIInterval);

			void test(const int * i);

		private:
			StaticTable<Math::Interval<Size>, NbThreads> neuronIIntervalTable;
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
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::test(const int * i) {
			
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		template<typename ActivationFunc>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::_runComputeForwardPropagation(const StaticTable<T, NbFeatures>* featureTable, StaticTable<T, NbNeurons>* outTable, const ActivationFunc* activationFunc, const Math::Interval<Size>* neuronIInterval) {
			for ( Size neuronI(neuronIInterval->getBegin()); neuronI < neuronIInterval->getEnd(); neuronI++ ) {
				const T y(computeY(neuronI, *featureTable, *activationFunc));
				(*outTable)[ neuronI ] = y;
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		template<typename ActivationFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::computeForwardPropagation(const Size dataI, const ActivationFunc& activationFunc) {
			computeForwardPropagation(getIns(dataI), getOuts(dataI), activationFunc);
			return getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc, Size NbThreads>
		template<typename ActivationFunc>
		inline void NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::computeForwardPropagation(const StaticTable<T, NbFeatures>& featureTable, StaticTable<T, NbNeurons>& outTable, const ActivationFunc& activationFunc) const {
			if constexpr ( NbThreads == Size(1) ) {
				return NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(featureTable, outTable, activationFunc);
			} else {
				StaticTable<std::thread, NbThreads> threadTable;
				for ( Size i(0); i < getNbThreads(); i++ ) {
					threadTable[ i ] = std::thread(&NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads>::_runComputeForwardPropagation< ActivationFunc>,
												   const_cast< NeuralLayerMT<T, NbFeatures, NbNeurons, OptimizerFunc, NbThreads> * >( this ),
												   &featureTable,
												   &outTable,
												   &activationFunc,
												   &this->neuronIIntervalTable[i]);
				}
				for ( Size i(0); i < getNbThreads(); i++ ) {
					threadTable[ i ].join();
				}
			}
		}

	}

}