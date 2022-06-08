#pragma once

#include "Neuron.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		class NeuralLayer {
		public:
			NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inVector);

			constexpr Size getNbFeatures() const;
			constexpr Size getNbOut() const;
			constexpr Size getNbParams() const;

			void addData();

			const StaticTable<T, NbFeatures>& getIns(const Size dataI) const;
			const StaticTable<T, NbFeatures + Size(1)>& getParams(const Size neuronI) const;
			const StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neuronI) const;
			StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neuronI);
			const StaticTable<T, NbNeurons>& getOuts(const Size dataI) const;
			StaticTable<T, NbNeurons>& getDeltas(const Size dataI);

			const Vector< StaticTable<T, NbFeatures>>& getInVector() const;
			const Vector< StaticTable<T, NbNeurons>>& getOutVector() const;
			Vector< StaticTable<T, NbNeurons>>& getOutVector();
			const Vector<StaticTable<T, NbNeurons>>& getDeltaVector() const;
			Vector<StaticTable<T, NbNeurons>>& getDeltaVector();

			const Func& getActivationFunc(const Size neuronI) const;

			T computeY(const Size neuronI, const Size dataI) const;
			T computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable) const;
			T computeGrad(const Size neuronI, const Size paramI) const;

			const T& getOut(const Size neuronI, const Size dataI) const;
			const T& getParam(const Size neuronI, const Size paramI) const;
			const T& getGrad(const Size neuronI, const Size paramI) const;

			void setGrad(const Size neuronI, const Size paramI, const T& v);
			void setParam(const Size neuronI, const Size paramI, const T& v);
			void setOut(const Size neuronI, const Size dataI, const T& v);

			const Neuron<T, NbFeatures, Func>& getNeuron(const Size neuronI) const;
			Neuron<T, NbFeatures, Func>& getNeuron(const Size neuronI);

		private:
			const Vector<StaticTable<T, NbFeatures>>* inVector;
			Vector<StaticTable<T, NbNeurons>> outVector;
			Vector<StaticTable<T, NbNeurons>> deltaVector;

			StaticTable<Neuron<T, NbFeatures, Func>, NbNeurons> neuronTable;
		};

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline NeuralLayer<T, NbFeatures, NbNeurons, Func>::NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inVector) :
			inVector(inVector)
		{
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons, Func>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons, Func>::getNbOut() const {
			return NbNeurons;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons, Func>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, Func>::addData() {
			this->outVector.push(StaticTable<T, NbNeurons>());
			this->deltaVector.push(StaticTable<T, NbNeurons>());
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const StaticTable<T, NbFeatures>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getIns(const Size dataI) const {
			return this->inVector->getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getParams(const Size neuronI) const {
			return getNeuron(neuronI).getParams();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getGrads(const Size neuronI) const {
			return getNeuron(neuronI).getGrads();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getGrads(const Size neuronI) {
			return getNeuron(neuronI).getGrads();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getOuts(const Size dataI) const {
			return this->outVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getDeltas(const Size dataI) {
			return this->deltaVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const Vector<StaticTable<T, NbFeatures>>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getInVector() const {
			return *this->inVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getOutVector() const {
			return this->outVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getOutVector() {
			return this->outVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getDeltaVector() const {
			return this->deltaVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getDeltaVector() {
			return this->deltaVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const Func& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getActivationFunc(const Size neuronI) const {
			return getNeuron(neuronI).getActivationFunc();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, Func>::computeY(const Size neuronI, const Size dataI) const {
			return getNeuron(neuronI).computeY(getIns(dataI));
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, Func>::computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable) const {
			return getNeuron(neuronI).computeY(featureTable);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, Func>::computeGrad(const Size neuronI, const Size paramI) const {
			return getNeuron(neuronI).computeGrad(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, Func>::setOut(const Size neuronI, const Size dataI, const T& v) {
			this->outVector.getValueI(dataI)[ neuronI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getOut(const Size neuronI, const Size dataI) const {
			return this->outVector.getValueI(dataI)[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getParam(const Size neuronI, const Size paramI) const {
			return getNeuron(neuronI).getParam(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, Func>::setParam(const Size neuronI, const Size paramI, const T& v) {
			getNeuron(neuronI).setParam(paramI, v);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getGrad(const Size neuronI, const Size paramI) const {
			return getNeuron(neuronI).getGrad(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, Func>::setGrad(const Size neuronI, const Size paramI, const T& v) {
			getNeuron(neuronI).setGrad(paramI, v);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline const Neuron<T, NbFeatures, Func>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getNeuron(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, Func> * >( this )->getNeuron(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename Func>
		inline Neuron<T, NbFeatures, Func>& NeuralLayer<T, NbFeatures, NbNeurons, Func>::getNeuron(const Size neuronI) {
			return this->neuronTable[ neuronI ];
		}

	}

}