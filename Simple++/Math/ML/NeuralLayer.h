#pragma once

#include "../../IO/BasicIO.h"
#include "../Interval.h"
#include "Optimizer.h"
#include "ActivationFunc.h"
#include "Neuron.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		class NeuralLayer : public IO::BasicIO {
		public:
			NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inTableVector, const OptimizerFunc & optimizerFunc);
			NeuralLayer(const NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>& neuralLayer);

			NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>& operator=(const NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>& neuralLayer);

			void setParamMat(const Mat<T>& paramMat);
			void setGradMat(const Mat<T>& gradMat);
			void setInTableVector(const Vector<StaticTable<T, NbFeatures>>* inTableVector);

			static constexpr Size getNbFeatures() {
				return NbFeatures;
			}
			static constexpr Size getNbNeurons() {
				return NbNeurons;
			}
			static constexpr Size getNbNeuronParams() {
				return NbFeatures + Size(1);
			}
			static constexpr Size getNbParams() {
				return getNbNeuronParams() * getNbNeurons();
			}

			const Size getNbData() const;

			void setNbData(const Size nbData);

			const StaticTable<T, NbFeatures>& getIns(const Size dataI) const;
			const StaticTable<T, NbFeatures + Size(1)>& getParams(const Size neuronI) const;
			StaticTable<T, NbFeatures + Size(1)>& getParams(const Size neuronI);
			const StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neuronI) const;
			StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neuronI);
			const StaticTable<T, NbNeurons>& getOuts(const Size dataI) const;
			StaticTable<T, NbNeurons>& getOuts(const Size dataI);
			const StaticTable<T, NbNeurons>& getDeltas(const Size dataI) const;
			StaticTable<T, NbNeurons>& getDeltas(const Size dataI);

			const Vector< StaticTable<T, NbFeatures>>& getInVector() const;
			const Vector< StaticTable<T, NbNeurons>>& getOutVector() const;
			Vector< StaticTable<T, NbNeurons>>& getOutVector();
			const Vector<StaticTable<T, NbNeurons>>& getDeltaVector() const;
			Vector<StaticTable<T, NbNeurons>>& getDeltaVector();

			// const ActivationFunc& getActivationFunc() const;

			template<typename ActivationFunc>
			T computeY(const Size neuronI, const Size dataI, const ActivationFunc & activationFunc) const;

			template<typename ActivationFunc>
			T computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable, const ActivationFunc& activationFunc) const;

			const T& getOut(const Size neuronI, const Size dataI) const;
			const T& getParam(const Size neuronI, const Size paramI) const;
			const T& getGrad(const Size neuronI, const Size paramI) const;

			void setGrad(const Size neuronI, const Size paramI, const T& v);
			void setParam(const Size neuronI, const Size paramI, const T& v);
			void setOut(const Size neuronI, const Size dataI, const T& v);

			// const Neuron<T, NbFeatures, ActivationFunc>& getNeuron(const Size neuronI) const;
			// Neuron<T, NbFeatures, ActivationFunc>& getNeuron(const Size neuronI);

			const Mat<T>& getParamMat() const;
			Mat<T>& getParamMat();

			const Mat<T>& getGradMat() const;
			Mat<T>& getGradMat();

			const StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& getParamTableTable() const;
			StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& getParamTableTable();

			const StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& getGradTableTable() const;
			StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& getGradTableTable();

			const OptimizerFunc& getOptimizerFunc() const;
			void setOptimizerFunc(const OptimizerFunc& optimizerFunc);

			template<typename ActivationFunc>
			void resetParams(const ActivationFunc& activationFunc);
			void resetOptimizerFunc();

			/************************************************************************/
			/* ================         Forward Propagation        ================ */
			/************************************************************************/

			template<typename ActivationFunc>
			const StaticTable<T, NbNeurons>& computeForwardPropagation(const Size dataI, const ActivationFunc& activationFunc);
			template<typename ActivationFunc>
			void computeForwardPropagation(const StaticTable<T, NbFeatures> & featureTable, StaticTable<T, NbNeurons> & outTable, const ActivationFunc& activationFunc) const;
			template<typename ActivationFunc>
			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const ActivationFunc& activationFunc);
			template<typename ActivationFunc>
			void computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbFeatures>>& featureTableVector, Vector<StaticTable<T, NbNeurons>>& outTableVector, const ActivationFunc& activationFunc) const;
			template<typename ActivationFunc, Size NbData>
			void computeForwardPropagationS(const Size dataIBegin, const ActivationFunc& activationFunc);
			template<typename ActivationFunc, Size NbData>
			void computeForwardPropagationS(const StaticTable<StaticTable<T, NbFeatures>, NbData>& featureTableTable, StaticTable<StaticTable<T, NbNeurons>, NbData>& outTableTable, const ActivationFunc& activationFunc) const;


			/************************************************************************/
			/* ================           Compute Deltas           ================ */
			/************************************************************************/

			void computeDeltasLast(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector);
			template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc>
			void computeDeltas(const Math::Interval<Size>& dataIInterval, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext, OptimizerFunc>& nextNeuralLayer, const ActivationFunc& activationFunc);
			template<Size NbData>
			void computeDeltasLastS(const Size dataIBegin, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector);
			template<Size NbData>
			void computeDeltasLastS(const StaticTable<StaticTable<T, NbNeurons>, NbData>& outTableTable, const StaticTable<StaticTable<T, NbNeurons>, NbData>& expectedOutTableTable, StaticTable<StaticTable<T, NbNeurons>, NbData> & deltaTableTable) const;
			template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc, Size NbData>
			void computeDeltasS(const Size dataIBegin, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext, OptimizerFunc>& nextNeuralLayer, const ActivationFunc& activationFunc);
			template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc, Size NbData>
			void computeDeltasS(const StaticTable<StaticTable<T, NbNeurons>, NbData>& outTableTable,
								const StaticTable<StaticTable<T, NbNeuronsNext>, NbData> & nextDeltaTableTable,
								const StaticTable<StaticTable<T, NbFeaturesNext + Size(1)>, NbNeuronsNext> & nextParamTable,
								StaticTable<StaticTable<T, NbNeurons>, NbData>& deltaTableTable,
								const ActivationFunc& activationFunc) const;

			/************************************************************************/
			/* ================          Back Propagation          ================ */
			/************************************************************************/

			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);
			template<Size NbData>
			void computeBackPropagationS(const Size dataIBegin);
			template<Size NbData>
			void computeBackPropagationS(const StaticTable<StaticTable<T, NbFeatures>, NbData> & inTableTable, const StaticTable<StaticTable<T, NbNeurons>, NbData> & deltaTableTable, StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& gradTableTable);



			void updateModel(const T & learningRateFactor, const Size epochNum);

			T computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& outTableVector, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;
			T computeMeanSquaredError(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& outTableVector, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& outTableVector, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;

			StaticTable<T, NbNeurons> computeMeanTable(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;

			T computeNeuronWeight(const Size neuronI) const;

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
			const Vector<StaticTable<T, NbFeatures>>* inTableVector;		// Matrix of input of size [NbData, NbFeatures]
			Vector<StaticTable<T, NbNeurons>> outTableVector;				// Matrix of output of size [NbData, NbNeurons]
			Vector<StaticTable<T, NbNeurons>> deltaTableVector;				// Matrix of deltas of size [NbData, NbFeatures]

			Mat<T> paramMat;	// Matrix of params of size [NbNeurons, NbFeatures + 1]
			Mat<T> gradMat;		// Matrix of params of size [NbNeurons, NbFeatures + 1]

			StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& paramTableTable;		// Reference to paramMat
			StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& gradTableTable;		// Reference to gradMat

			OptimizerFunc optimizerFunc;

			// StaticTable<Neuron<T, NbFeatures, ActivationFunc>, NbNeurons> neuronTable;
		};

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inTableVector, const OptimizerFunc& optimizerFunc) :
			inTableVector(inTableVector),
			paramMat(NbNeurons, NbFeatures + Size(1)),
			gradMat(NbNeurons, NbFeatures + Size(1)),
			paramTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( paramMat.getData() )),
			gradTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( gradMat.getData() )),
			optimizerFunc(optimizerFunc)
		{
			static_assert( Utility::isBase<Optimizer::BasicOptimizer<T>, OptimizerFunc>::value, "OptimizerFunc type unknown." );
			this->optimizerFunc.init(getNbNeuronParams(), getNbNeurons());
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::NeuralLayer(const NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>& neuralLayer) :
			inTableVector(neuralLayer.inTableVector),
			outTableVector(neuralLayer.outTableVector),
			deltaTableVector(neuralLayer.deltaTableVector),
			paramMat(neuralLayer.paramMat),
			gradMat(neuralLayer.gradMat),
			paramTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( paramMat.getData() )),
			gradTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( gradMat.getData() )),
			optimizerFunc(neuralLayer.optimizerFunc)
		{
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::operator=(const NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>& neuralLayer) {
			this->inTableVector = neuralLayer.inTableVector;
			this->outTableVector = neuralLayer.outTableVector;
			this->deltaTableVector = neuralLayer.deltaTableVector;
			this->paramMat = neuralLayer.paramMat;
			this->gradMat = neuralLayer.gradMat;
			this->optimizerFunc = neuralLayer.optimizerFunc;

			return *this;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setParamMat(const Mat<T>& paramMat) {
			assert(paramMat.getSizeM() == getNbNeurons());
			assert(paramMat.getSizeN() == getNbFeatures() + Size(1));

			this->paramMat = paramMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setGradMat(const Mat<T>& gradMat) {
			assert(paramMat.getSizeM() == getNbNeurons());
			assert(paramMat.getSizeN() == getNbFeatures() + Size(1));

			this->gradMat = gradMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setInTableVector(const Vector<StaticTable<T, NbFeatures>>* inTableVector) {
			this->inTableVector = inTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Size NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getNbData() const {
			return this->outTableVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setNbData(const Size nbData) {
			this->outTableVector.resize(nbData);
			this->deltaTableVector.resize(nbData);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<T, NbFeatures>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getIns(const Size dataI) const {
			return this->inTableVector->getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParams(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc> * >( this )->getParams(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParams(const Size neuronI) {
			// return *StaticTable<T, NbFeatures + Size(1)>::reinterpret(this->paramMat.getDataM(neuronI));
			return this->paramTableTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGrads(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc> * >( this )->getGrads(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGrads(const Size neuronI) {
			// return *StaticTable<T, NbFeatures + Size(1)>::reinterpret(this->gradMat.getDataM(neuronI));
			return this->gradTableTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getOuts(const Size dataI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc> * >( this )->getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getOuts(const Size dataI) {
			return this->outTableVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getDeltas(const Size dataI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc> * >( this )->getDeltas(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getDeltas(const Size dataI) {
			return this->deltaTableVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Vector<StaticTable<T, NbFeatures>>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getInVector() const {
			return *this->inTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getOutVector() const {
			return this->outTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getOutVector() {
			return this->outTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getDeltaVector() const {
			return this->deltaTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getDeltaVector() {
			return this->deltaTableVector;
		}

		/*template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const ActivationFunc& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getActivationFunc() const {
			return this->activationFunc;
		}*/

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeY(const Size neuronI, const Size dataI, const ActivationFunc& activationFunc) const {
			return computeY(neuronI, getIns(dataI), activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable, const ActivationFunc& activationFunc) const {
			return Neuron<T, NbFeatures, ActivationFunc>::computeY(featureTable, getParams(neuronI), activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setOut(const Size neuronI, const Size dataI, const T& v) {
			this->outTableVector.getValueI(dataI)[ neuronI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getOut(const Size neuronI, const Size dataI) const {
			return this->outTableVector.getValueI(dataI)[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParam(const Size neuronI, const Size paramI) const {
			return getParams(neuronI)[ paramI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setParam(const Size neuronI, const Size paramI, const T& v) {
			getParams(neuronI)[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGrad(const Size neuronI, const Size paramI) const {
			return getGrads(neuronI)[ paramI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setGrad(const Size neuronI, const Size paramI, const T& v) {
			getGrads(neuronI)[ paramI ] = v;
		}

		/*template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Neuron<T, NbFeatures, ActivationFunc>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getNeuron(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc> * >( this )->getNeuron(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline Neuron<T, NbFeatures, ActivationFunc>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getNeuron(const Size neuronI) {
			return this->neuronTable[ neuronI ];
		}*/

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParamMat() const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>* >( this )->getParamMat();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParamMat() {
			return this->paramMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGradMat() const {
			return this->gradMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGradMat() {
			return this->gradMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParamTableTable() const {
			return this->paramTableTable;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getParamTableTable() {
			return this->paramTableTable;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGradTableTable() const {
			return this->gradTableTable;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getGradTableTable() {
			return this->gradTableTable;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline const OptimizerFunc& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::getOptimizerFunc() const {
			return this->optimizerFunc;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::setOptimizerFunc(const OptimizerFunc& optimizerFunc) {
			this->optimizerFunc = optimizerFunc;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::resetOptimizerFunc() {
			this->optimizerFunc.reset();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::resetParams(const ActivationFunc& activationFunc) {
			this->paramMat.randomF();

			struct InterpolationFunc {
				inline T operator()(const T& x) const {
					T _x(x - T(0.5));
					return T(3.0) * ( x * x * x ) + T(0.25) * x + T(0.5);
				}
			};

			static const InterpolationFunc interpolationFunc;

			// Use a square root func to converge params to 0.5.
			/*for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				StaticTable<T, NbFeatures + Size(1)>& paramTable(getParams(neuronI));
				for ( Size paramI(0); paramI < getNbNeuronParams(); paramI++ ) {
					paramTable[ paramI ] = interpolationFunc(paramTable[ paramI ]);
				}
			}*/

			/*for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				StaticTable<T, NbFeatures + Size(1)>& paramTable(getParams(neuronI));
				const T neuronWeight(computeNeuronWeight(neuronI));

				for ( Size paramI(0); paramI < getNbNeuronParams(); paramI++ ) {
					paramTable[ paramI ] /= neuronWeight;
				}
			}*/

			const T weightFactor(activationFunc.weightInit<T>(getNbFeatures(), getNbNeurons(), getNbData()));
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				StaticTable<T, NbFeatures + Size(1)>& paramTable(getParams(neuronI));

				for ( Size paramI(0); paramI < getNbNeuronParams(); paramI++ ) {
					paramTable[ paramI ] = (paramTable[ paramI ] * T(2.0) - T(1.0)) * weightFactor;
				}
			}

			resetOptimizerFunc();
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(const Size dataI, const ActivationFunc& activationFunc) {
			computeForwardPropagation(getIns(dataI), getOuts(dataI), activationFunc);

			return getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const ActivationFunc& activationFunc) {
			computeForwardPropagation(dataIInterval, getInVector(), getOutVector(), activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbFeatures>>& featureTableVector, Vector<StaticTable<T, NbNeurons>>& outTableVector, const ActivationFunc& activationFunc) const {
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbFeatures>& featureTable(featureTableVector.getValueI(dataI));
				StaticTable<T, NbNeurons>& outTable(outTableVector.getValueI(dataI));
				computeForwardPropagation(featureTable, outTable, activationFunc);
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc, Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagationS(const Size dataIBegin, const ActivationFunc& activationFunc) {
			computeForwardPropagationS(*reinterpret_cast< const StaticTable<StaticTable<T, NbFeatures>, NbData> * >( getInVector().getData() + dataIBegin ),
									   *reinterpret_cast< StaticTable<StaticTable<T, NbNeurons>, NbData> * >( getOutVector().getData() + dataIBegin ),
									   activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc, Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagationS(const StaticTable<StaticTable<T, NbFeatures>, NbData>& featureTableTable, StaticTable<StaticTable<T, NbNeurons>, NbData>& outTableTable, const ActivationFunc& activationFunc) const {
			for ( Size dataI(0); dataI < NbData; dataI++ ) {
				computeForwardPropagation(featureTableTable[ dataI ], outTableTable[ dataI ], activationFunc);
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeForwardPropagation(const StaticTable<T, NbFeatures>& featureTable, StaticTable<T, NbNeurons>& outTable, const ActivationFunc& activationFunc) const {
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				const T y(computeY(neuronI, featureTable, activationFunc));
				outTable[ neuronI ] = y;
				/*if ( Utility::isNan(y) ) {
					Log::displayError(String::format("computeForwardPropagation is NaN : % * %.", getParams(neuronI).toString(), featureTable.toString()));
				}*/
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			const T sizeInverse(T(1) / T(dataIInterval.getSize()));

			for ( Size featureI(0); featureI < getNbFeatures(); featureI++ ) {
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

					T dotSum(0);
					for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
						dotSum += getIns(dataI)[ featureI ] * getDeltas(dataI)[ neuronI ];
					}

					dotSum *= sizeInverse;
					setGrad(neuronI, featureI, dotSum);
				}
			}
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

				T dotSum(0);
				for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
					dotSum += getDeltas(dataI)[ neuronI ];
				}

				dotSum *= sizeInverse;
				setGrad(neuronI, getNbFeatures(), dotSum);
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeDeltasLast(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) {
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				StaticTable<T, NbNeurons>& deltaVecTable(getDeltas(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					deltaVecTable[ neuronI ] = outTable[ neuronI ] - expectedYTable[ neuronI ];
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::updateModel(const T& learningRateFactor, const Size epochNum) {
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				for ( Size paramI(0); paramI < getNbNeuronParams(); paramI++ ) {
					const T& grad(getGrads(neuronI)[ paramI ]);
					T& param(getParams(neuronI)[ paramI ]);
					param = this->optimizerFunc(epochNum, neuronI, paramI, param, grad, learningRateFactor);
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename Stream>
		inline bool NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::read(Stream* stream) {
			Size nbFeatures;
			Size nbNeurons;
			if ( !IO::read(stream, &nbFeatures) ) {
				return false;
			}
			if ( !IO::read(stream, &nbNeurons) ) {
				return false;
			}
			if ( nbFeatures != getNbFeatures() || nbNeurons != getNbNeurons() ) {
				Log::displayError(String::format("Trying to read a NeuralLayer of the wrong size : this[ % x % ] != read[ % x % ].", getNbFeatures(), getNbNeurons(), nbFeatures, nbNeurons));
				return false;
			}
			if ( !IO::read(stream, &this->paramMat) ) {
				return false;
			}
			if ( !IO::read(stream, &this->optimizerFunc) ) {
				return false;
			}
			return true;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<typename Stream>
		inline bool NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::write(Stream* stream) const {
			const Size nbFeatures(getNbFeatures());
			const Size nbNeurons(getNbNeurons());
			if ( !IO::write(stream, &nbFeatures) ) {
				return false;
			}
			if ( !IO::write(stream, &nbNeurons) ) {
				return false;
			}
			if ( !IO::write(stream, &this->paramMat) ) {
				return false;
			}
			if ( !IO::write(stream, &this->optimizerFunc) ) {
				return false;
			}
			return true;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& outTableVector, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			T costSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(outTableVector.getValueI(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T& expectedY(expectedYTable[ neuronI ]);
					const T& y(outTable[ neuronI ]);
					costSum += expectedY * Math::log(y) + ( T(1) - expectedY ) * Math::log(T(1) - y);
				}
			}

			return -costSum / T(dataIInterval.getSize());
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeMeanSquaredError(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& outTableVector, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			T costSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(outTableVector.getValueI(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T delta(expectedYTable[ neuronI ] - outTable[ neuronI ]);
					costSum += delta * delta;
					/*if ( Utility::isNan(costSum) ) {
						Log::displayError(String::format("computeMeanSquaredError value is NaN : expectedYTable[ neuronI ] = %, outTable[ neuronI ] = %.", expectedYTable[ neuronI ], outTable[ neuronI ]));
					}*/
				}
			}

			return Math::sqrt(costSum) / T(dataIInterval.getSize());
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& outTableVector, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			StaticTable<T, NbNeurons> meanExpectedTable(computeMeanTable(dataIInterval, expectedOutTableVector));

			T errSum(0);
			T meanSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& expectedTable(expectedOutTableVector.getValueI(dataI));
				const StaticTable<T, NbNeurons>& outTable(outTableVector.getValueI(dataI));

				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T y(outTable[ neuronI ]);
					const T expectedY(expectedTable[ neuronI ]);
					const T err(expectedY - y);
					const T mean(expectedY - meanExpectedTable[ neuronI ]);

					errSum += err * err;
					meanSum += mean * mean;
				}
			}

			return T(1) - errSum / meanSum;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline StaticTable<T, NbNeurons> NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeMeanTable(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			StaticTable<T, NbNeurons> outTable;

			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				outTable[ neuronI ] = T(0);
			}

			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& inTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					outTable[ neuronI ] += inTable[ neuronI ];
				}
			}

			const T sizeInverse(T(1) / T(dataIInterval.getSize()));
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				outTable[ neuronI ] *= sizeInverse;
			}

			return outTable;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeNeuronWeight(const Size neuronI) const {
			StaticTable<T, NbFeatures + Size(1)> paramTable(getParams(neuronI));

			T weight(0);
			for ( Size paramI(0); paramI < getNbNeuronParams(); paramI++ ) {
				weight += paramTable[ paramI ];
			}

			return weight;
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeDeltas(const Math::Interval<Size>& dataIInterval, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext, OptimizerFunc>& nextNeuralLayer, const ActivationFunc& activationFunc) {
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeuronsNext>& nextDeltaVecTable(nextNeuralLayer.getDeltas(dataI));
				StaticTable<T, NbNeurons>& deltaVecTable(getDeltas(dataI));

				for ( Size neuronI(0); neuronI < deltaVecTable.getSize(); neuronI++ ) {
					T dotSum(0);
					for ( Size nextNeuronI(0); nextNeuronI < nextDeltaVecTable.getSize(); nextNeuronI++ ) {
						const StaticTable<T, NbFeaturesNext + Size(1)>& paramTable(nextNeuralLayer.getParams(nextNeuronI));
						dotSum += paramTable[ neuronI ] * nextDeltaVecTable[ nextNeuronI ];
					}
					deltaVecTable[ neuronI ] = dotSum * activationFunc.grad(outTable[ neuronI ]);
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeDeltasLastS(const Size dataIBegin, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) {
			computeDeltasLastS(*reinterpret_cast< const StaticTable<StaticTable<T, NbNeurons>, NbData> * >( getOutVector().getData() + dataIBegin ),
							   *reinterpret_cast< const StaticTable<StaticTable<T, NbNeurons>, NbData> * >( expectedOutTableVector.getData() + dataIBegin ),
							   *reinterpret_cast< StaticTable<StaticTable<T, NbNeurons>, NbData> * >( getDeltaVector().getData() + dataIBegin ));
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeDeltasLastS(const StaticTable<StaticTable<T, NbNeurons>, NbData>& outTableTable, const StaticTable<StaticTable<T, NbNeurons>, NbData>& expectedOutTableTable, StaticTable<StaticTable<T, NbNeurons>, NbData>& deltaTableTable) const {
			for ( Size dataI(0); dataI < NbData; dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(outTableTable[dataI]);
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableTable[dataI]);
				StaticTable<T, NbNeurons>& deltaTable(deltaTableTable[dataI]);

				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					deltaTable[ neuronI ] = outTable[ neuronI ] - expectedYTable[ neuronI ];
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc, Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeDeltasS(const Size dataIBegin, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext, OptimizerFunc>& nextNeuralLayer, const ActivationFunc& activationFunc) {
			computeDeltasS<NbFeaturesNext, NbNeuronsNext, ActivationFunc, NbData>(*reinterpret_cast< const StaticTable<StaticTable<T, NbNeurons>, NbData> * >( getOutVector().getData() + dataIBegin ),
						   *reinterpret_cast< const StaticTable<StaticTable<T, NbNeuronsNext>, NbData> * >( nextNeuralLayer.getDeltaVector().getData() + dataIBegin ),
						   nextNeuralLayer.getParamTableTable(),
						   *reinterpret_cast< StaticTable<StaticTable<T, NbNeurons>, NbData> * >( getDeltaVector().getData() + dataIBegin ),
						   activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc, Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeDeltasS(const StaticTable<StaticTable<T, NbNeurons>, NbData>& outTableTable, const StaticTable<StaticTable<T, NbNeuronsNext>, NbData>& nextDeltaTableTable, const StaticTable<StaticTable<T, NbFeaturesNext + Size(1)>, NbNeuronsNext>& nextParamTable, StaticTable<StaticTable<T, NbNeurons>, NbData>& deltaTableTable, const ActivationFunc& activationFunc) const {
			for ( Size dataI(0); dataI < NbData; dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(outTableTable[ dataI ]);
				const StaticTable<T, NbNeuronsNext>& nextDeltaTable(nextDeltaTableTable[dataI]);
				StaticTable<T, NbNeurons>& deltaTable(deltaTableTable[dataI]);

				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					T dotSum(0);
					for ( Size nextNeuronI(0); nextNeuronI < NbNeuronsNext; nextNeuronI++ ) {
						const StaticTable<T, NbFeaturesNext + Size(1)>& paramTable(nextParamTable[nextNeuronI]);
						dotSum += paramTable[ neuronI ] * nextDeltaTable[ nextNeuronI ];
					}
					deltaTable[ neuronI ] = dotSum * activationFunc.grad(outTable[ neuronI ]);
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeBackPropagationS(const Size dataIBegin) {
			computeBackPropagationS(*reinterpret_cast< const StaticTable<StaticTable<T, NbFeatures>, NbData> * >( getInVector().getData() + dataIBegin ),
									*reinterpret_cast< const StaticTable<StaticTable<T, NbNeurons>, NbData> * >( getDeltaVector().getData() + dataIBegin ),
									getGradTableTable());
		}

		template<typename T, Size NbFeatures, Size NbNeurons, typename OptimizerFunc>
		template<Size NbData>
		inline void NeuralLayer<T, NbFeatures, NbNeurons, OptimizerFunc>::computeBackPropagationS(const StaticTable<StaticTable<T, NbFeatures>, NbData>& inTableTable, const StaticTable<StaticTable<T, NbNeurons>, NbData>& deltaTableTable, StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>& gradTableTable) {
			constexpr T sizeInverse(T(1) / T(NbData));

			for ( Size featureI(0); featureI < getNbFeatures(); featureI++ ) {
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

					T dotSum(0);
					for ( Size dataI(0); dataI < NbData; dataI++ ) {
						dotSum += inTableTable[dataI][ featureI ] * deltaTableTable[dataI][ neuronI ];
					}

					dotSum *= sizeInverse;
					gradTableTable[ neuronI ][ featureI ] = dotSum;
				}
			}
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

				T dotSum(0);
				for ( Size dataI(0); dataI < NbData; dataI++ ) {
					dotSum += deltaTableTable[dataI][ neuronI ];
				}

				dotSum *= sizeInverse;
				gradTableTable[ neuronI ][ getNbFeatures() ] = dotSum;
			}
		}

	}

}