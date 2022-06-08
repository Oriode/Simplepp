#pragma once

#include "Neuron.h"

namespace Math {

	namespace ML {

		template<typename T, typename Func>
		class NeuralLayer {
		public:
			NeuralLayer(const Size nbFeatures, const Size nbNeurons, const Vector<Vec<T>>* inVector);

			~NeuralLayer();

			constexpr Size getNbFeatures() const;
			constexpr Size getNbOut() const;
			constexpr Size getNbParams() const;

			void addData();

			const Vec<T>& getIns(const Size dataI) const;
			const Vec<T>& getParams(const Size neuronI) const;
			const Vec<T>& getGrads(const Size neuronI) const;
			Vec<T>& getGrads(const Size neuronI);
			const Vec<T>& getOuts(const Size dataI) const;
			Vec<T>& getDeltas(const Size dataI);

			const Vector< Vec<T>>& getInVector() const;
			const Vector< Vec<T>>& getOutVector() const;
			Vector< Vec<T>>& getOutVector();
			const Vector<Vec<T>>& getDeltaVector() const;
			Vector<Vec<T>>& getDeltaVector();

			const Func& getActivationFunc(const Size neuronI) const;

			T computeY(const Size neuronI, const Size dataI) const;
			T computeY(const Size neuronI, const Vec<T>& featureTable) const;
			T computeGrad(const Size neuronI, const Size paramI) const;
			void setOut(const Size neuronI, const Size dataI, const T& v);
			const T& getOut(const Size neuronI, const Size dataI);

			const T& getParam(const Size neuronI, const Size paramI) const;
			T& getParam(const Size neuronI, const Size paramI);

			void setParam(const Size neuronI, const Size paramI, const T& v);

			const T& getGrad(const Size neuronI, const Size paramI) const;
			T& getGrad(const Size neuronI, const Size paramI);

			void setGrad(const Size neuronI, const Size paramI, const T& v);

			const Neuron<T, Func>& getNeuron(const Size neuronI) const;
			Neuron<T, Func>& getNeuron(const Size neuronI);

		private:
			const Size nbFeatures;
			const Size nbNeurons;

			const Vector<Vec<T>>* inVector;
			Vector<Vec<T>> outVector;
			Vector<Vec<T>> deltaVector;

			Vec<Neuron<T, Func> *> neuronTable;
		};

		template<typename T, typename Func>
		inline NeuralLayer<T, Func>::NeuralLayer(const Size nbFeatures, const Size nbNeurons, const Vector<Vec<T>>* inVector) :
			nbFeatures(nbFeatures),
			nbNeurons(nbNeurons),
			inVector(inVector),
			neuronTable(nbNeurons)
		{
			for ( Size i(0); i < this->neuronTable.getSize(); i++ ) {
				this->neuronTable[ i ] = new Neuron<T, Func>(getNbFeatures());
			}
		}

		template<typename T, typename Func>
		inline NeuralLayer<T, Func>::~NeuralLayer() {
			for ( Size i(0); i < this->neuronTable.getSize(); i++ ) {
				delete this->neuronTable[ i ];
			}
		}

		template<typename T, typename Func>
		inline constexpr Size NeuralLayer<T, Func>::getNbFeatures() const {
			return this->nbFeatures;
		}

		template<typename T, typename Func>
		inline constexpr Size NeuralLayer<T, Func>::getNbOut() const {
			return this->nbNeurons;
		}

		template<typename T, typename Func>
		inline constexpr Size NeuralLayer<T, Func>::getNbParams() const {
			return this->nbFeatures + Size(1);
		}

		template<typename T, typename Func>
		inline void NeuralLayer<T, Func>::addData() {
			this->outVector.push(Vec<T>(this->nbNeurons));
			this->deltaVector.push(Vec<T>(this->nbNeurons));
		}

		template<typename T, typename Func>
		inline const Vec<T>& NeuralLayer<T, Func>::getIns(const Size dataI) const {
			return this->inVector->getValueI(dataI);
		}

		template<typename T, typename Func>
		inline const Vec<T>& NeuralLayer<T, Func>::getParams(const Size neuronI) const {
			return getNeuron(neuronI).getParams();
		}

		template<typename T, typename Func>
		inline const Vec<T>& NeuralLayer<T, Func>::getGrads(const Size neuronI) const {
			return getNeuron(neuronI).getGrads();
		}

		template<typename T, typename Func>
		inline Vec<T>& NeuralLayer<T, Func>::getGrads(const Size neuronI) {
			return getNeuron(neuronI).getGrads();
		}

		template<typename T, typename Func>
		inline const Vec<T>& NeuralLayer<T, Func>::getOuts(const Size dataI) const {
			return this->outVector.getValueI(dataI);
		}

		template<typename T, typename Func>
		inline Vec<T>& NeuralLayer<T, Func>::getDeltas(const Size dataI) {
			return this->deltaVector.getValueI(dataI);
		}

		template<typename T, typename Func>
		inline const Vector<Vec<T>>& NeuralLayer<T, Func>::getInVector() const {
			return *this->inVector;
		}

		template<typename T, typename Func>
		inline const Vector<Vec<T>>& NeuralLayer<T, Func>::getOutVector() const {
			return this->outVector;
		}

		template<typename T, typename Func>
		inline Vector<Vec<T>>& NeuralLayer<T, Func>::getOutVector() {
			return this->outVector;
		}

		template<typename T, typename Func>
		inline const Vector<Vec<T>>& NeuralLayer<T, Func>::getDeltaVector() const {
			return this->deltaVector;
		}

		template<typename T, typename Func>
		inline Vector<Vec<T>>& NeuralLayer<T, Func>::getDeltaVector() {
			return this->deltaVector;
		}

		template<typename T, typename Func>
		inline const Func& NeuralLayer<T, Func>::getActivationFunc(const Size neuronI) const {
			return getNeuron(neuronI).getActivationFunc();
		}

		template<typename T, typename Func>
		inline T NeuralLayer<T, Func>::computeY(const Size neuronI, const Size dataI) const {
			return getNeuron(neuronI).computeY(getIns(dataI));
		}

		template<typename T, typename Func>
		inline T NeuralLayer<T, Func>::computeY(const Size neuronI, const Vec<T>& featureTable) const {
			return getNeuron(neuronI).computeY(featureTable);
		}

		template<typename T, typename Func>
		inline T NeuralLayer<T, Func>::computeGrad(const Size neuronI, const Size paramI) const {
			return getNeuron(neuronI).computeGrad(paramI);
		}

		template<typename T, typename Func>
		inline void NeuralLayer<T, Func>::setOut(const Size neuronI, const Size dataI, const T& v) {
			this->outVector.getValueI(dataI)[ neuronI ] = v;
		}

		template<typename T, typename Func>
		inline const T& NeuralLayer<T, Func>::getOut(const Size neuronI, const Size dataI) {
			return this->outVector.getValueI(dataI)[ neuronI ];
		}

		template<typename T, typename Func>
		inline const T& NeuralLayer<T, Func>::getParam(const Size neuronI, const Size paramI) const {
			return const_cast< NeuralLayer<T, Func> * >( this )->getParam(neuronI, paramI);
		}

		template<typename T, typename Func>
		inline T& NeuralLayer<T, Func>::getParam(const Size neuronI, const Size paramI) {
			return getNeuron(neuronI).getParam(paramI);
		}

		template<typename T, typename Func>
		inline void NeuralLayer<T, Func>::setParam(const Size neuronI, const Size paramI, const T& v) {
			getNeuron(neuronI).setParam(paramI, v);
		}

		template<typename T, typename Func>
		inline const T& NeuralLayer<T, Func>::getGrad(const Size neuronI, const Size paramI) const {
			return getNeuron(neuronI).getGrad(paramI);
		}

		template<typename T, typename Func>
		inline T& NeuralLayer<T, Func>::getGrad(const Size neuronI, const Size paramI) {
			return getNeuron(neuronI).getGrad(paramI);
		}

		template<typename T, typename Func>
		inline void NeuralLayer<T, Func>::setGrad(const Size neuronI, const Size paramI, const T& v) {
			getNeuron(neuronI).setGrad(paramI, v);
		}

		template<typename T, typename Func>
		inline const Neuron<T, Func>& NeuralLayer<T, Func>::getNeuron(const Size neuronI) const {
			return const_cast< NeuralLayer<T, Func> * >( this )->getNeuron(neuronI);
		}

		template<typename T, typename Func>
		inline Neuron<T, Func>& NeuralLayer<T, Func>::getNeuron(const Size neuronI) {
			return *this->neuronTable[ neuronI ];
		}

	}

}