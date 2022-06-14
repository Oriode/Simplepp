#pragma once

#include "../../IO/BasicIO.h"
#include "../Interval.h"
#include "ActivationFunc.h"
#include "Neuron.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurons>
		class NeuralLayer : public IO::BasicIO {
		public:
			NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inTableVector);
			NeuralLayer(const NeuralLayer<T, NbFeatures, NbNeurons>& neuralLayer);

			NeuralLayer<T, NbFeatures, NbNeurons>& operator=(const NeuralLayer<T, NbFeatures, NbNeurons>& neuralLayer);

			void setParamMat(const Mat<T>& paramMat);
			void setInTableVector(const Vector<StaticTable<T, NbFeatures>>* inTableVector);

			constexpr Size getNbFeatures() const;
			constexpr Size getNbNeurons() const;
			constexpr Size getNbParams() const;

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

			void resetParams();

			template<typename ActivationFunc>
			const StaticTable<T, NbNeurons>& computeForwardPropagation(const Size dataI, const ActivationFunc& activationFunc);
			template<typename ActivationFunc>
			void computeForwardPropagation(const StaticTable<T, NbFeatures> & featureTable, StaticTable<T, NbNeurons> & outTable, const ActivationFunc& activationFunc) const;
			void computeBackPropagation(const Math::Interval<Size>& dataIInterval);

			void computeDeltasLast(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector);
			template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc>
			void computeDeltas(const Math::Interval<Size>& dataIInterval, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext>& nextNeuralLayer, const ActivationFunc& activationFunc);

			template<typename LearningRateFunc = LearningRate::Constant<T>>
			void updateModel(const LearningRateFunc& learningRateFunc, const T & learningRateFactor, const Size epochNum);

			T computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;
			T computeCostQuadratic(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;
			T computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const;

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

			// StaticTable<Neuron<T, NbFeatures, ActivationFunc>, NbNeurons> neuronTable;
		};

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline NeuralLayer<T, NbFeatures, NbNeurons>::NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inTableVector) :
			inTableVector(inTableVector),
			paramMat(NbNeurons, NbFeatures + Size(1)),
			gradMat(NbNeurons, NbFeatures + Size(1)),
			paramTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( paramMat.getData() )),
			gradTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( gradMat.getData() ))
		{
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline NeuralLayer<T, NbFeatures, NbNeurons>::NeuralLayer(const NeuralLayer<T, NbFeatures, NbNeurons>& neuralLayer) :
			inTableVector(neuralLayer.inTableVector),
			outTableVector(neuralLayer.outTableVector),
			deltaTableVector(neuralLayer.deltaTableVector),
			paramMat(neuralLayer.paramMat),
			gradMat(neuralLayer.gradMat),
			paramTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( paramMat.getData() )),
			gradTableTable(*reinterpret_cast< StaticTable<StaticTable<T, NbFeatures + Size(1)>, NbNeurons>* >( gradMat.getData() ))
		{
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline NeuralLayer<T, NbFeatures, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons>::operator=(const NeuralLayer<T, NbFeatures, NbNeurons>& neuralLayer) {
			this->inTableVector = neuralLayer.inTableVector;
			this->outTableVector = neuralLayer.outTableVector;
			this->deltaTableVector = neuralLayer.deltaTableVector;
			this->paramMat = neuralLayer.paramMat;
			this->gradMat = neuralLayer.gradMat;

			return *this;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::setParamMat(const Mat<T>& paramMat) {
			assert(paramMat.getSizeM() == getNbNeurons());
			assert(paramMat.getSizeN() == getNbFeatures() + Size(1));

			this->paramMat = paramMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::setInTableVector(const Vector<StaticTable<T, NbFeatures>>* inTableVector) {
			this->inTableVector = inTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons>::getNbNeurons() const {
			return NbNeurons;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurons>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const Size NeuralLayer<T, NbFeatures, NbNeurons>::getNbData() const {
			return this->outTableVector.getSize();
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::setNbData(const Size nbData) {
			this->outTableVector.resize(nbData);
			this->deltaTableVector.resize(nbData);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const StaticTable<T, NbFeatures>& NeuralLayer<T, NbFeatures, NbNeurons>::getIns(const Size dataI) const {
			return this->inTableVector->getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons>::getParams(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons> * >( this )->getParams(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons>::getParams(const Size neuronI) {
			// return *StaticTable<T, NbFeatures + Size(1)>::reinterpret(this->paramMat.getDataM(neuronI));
			return this->paramTableTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons>::getGrads(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons> * >( this )->getGrads(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurons>::getGrads(const Size neuronI) {
			// return *StaticTable<T, NbFeatures + Size(1)>::reinterpret(this->gradMat.getDataM(neuronI));
			return this->gradTableTable[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons>::getOuts(const Size dataI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons> * >( this )->getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons>::getOuts(const Size dataI) {
			return this->outTableVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons>::getDeltas(const Size dataI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons> * >( this )->getDeltas(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons>::getDeltas(const Size dataI) {
			return this->deltaTableVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const Vector<StaticTable<T, NbFeatures>>& NeuralLayer<T, NbFeatures, NbNeurons>::getInVector() const {
			return *this->inTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons>::getOutVector() const {
			return this->outTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons>::getOutVector() {
			return this->outTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons>::getDeltaVector() const {
			return this->deltaTableVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline Vector<StaticTable<T, NbNeurons>>& NeuralLayer<T, NbFeatures, NbNeurons>::getDeltaVector() {
			return this->deltaTableVector;
		}

		/*template<typename T, Size NbFeatures, Size NbNeurons>
		inline const ActivationFunc& NeuralLayer<T, NbFeatures, NbNeurons>::getActivationFunc() const {
			return this->activationFunc;
		}*/

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons>::computeY(const Size neuronI, const Size dataI, const ActivationFunc& activationFunc) const {
			return computeY(neuronI, getIns(dataI), activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename ActivationFunc>
		inline T NeuralLayer<T, NbFeatures, NbNeurons>::computeY(const Size neuronI, const StaticTable<T, NbFeatures>& featureTable, const ActivationFunc& activationFunc) const {
			return Neuron<T, NbFeatures, ActivationFunc>::computeY(featureTable, getParams(neuronI), activationFunc);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::setOut(const Size neuronI, const Size dataI, const T& v) {
			this->outTableVector.getValueI(dataI)[ neuronI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons>::getOut(const Size neuronI, const Size dataI) const {
			return this->outTableVector.getValueI(dataI)[ neuronI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons>::getParam(const Size neuronI, const Size paramI) const {
			return getParams(neuronI)[ paramI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::setParam(const Size neuronI, const Size paramI, const T& v) {
			getParams(neuronI)[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurons>::getGrad(const Size neuronI, const Size paramI) const {
			return getGrads(neuronI)[ paramI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::setGrad(const Size neuronI, const Size paramI, const T& v) {
			getGrads(neuronI)[ paramI ] = v;
		}

		/*template<typename T, Size NbFeatures, Size NbNeurons>
		inline const Neuron<T, NbFeatures, ActivationFunc>& NeuralLayer<T, NbFeatures, NbNeurons>::getNeuron(const Size neuronI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons> * >( this )->getNeuron(neuronI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline Neuron<T, NbFeatures, ActivationFunc>& NeuralLayer<T, NbFeatures, NbNeurons>::getNeuron(const Size neuronI) {
			return this->neuronTable[ neuronI ];
		}*/

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline const Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons>::getParamMat() const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurons>* >( this )->getParamMat();
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline Mat<T>& NeuralLayer<T, NbFeatures, NbNeurons>::getParamMat() {
			return this->paramMat;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::resetParams() {
			this->paramMat.randomF();

			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				StaticTable<T, NbFeatures + Size(1)>& paramTable(getParams(neuronI));
				const T neuronWeight(computeNeuronWeight(neuronI));

				for ( Size paramI(0); paramI < getNbParams(); paramI++ ) {
					paramTable[ paramI ] /= neuronWeight;
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename ActivationFunc>
		inline const StaticTable<T, NbNeurons>& NeuralLayer<T, NbFeatures, NbNeurons>::computeForwardPropagation(const Size dataI, const ActivationFunc& activationFunc) {
			computeForwardPropagation(getIns(dataI), getOuts(dataI), activationFunc);

			return getOuts(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::computeForwardPropagation(const StaticTable<T, NbFeatures>& featureTable, StaticTable<T, NbNeurons>& outTable, const ActivationFunc& activationFunc) const {
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				const T y(computeY(neuronI, featureTable, activationFunc));
				outTable[ neuronI ] = y;
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::computeBackPropagation(const Math::Interval<Size>& dataIInterval) {
			const T sizeInverse(T(1) / T(dataIInterval.getSize()));

			for ( Size paramI(0); paramI < getNbFeatures(); paramI++ ) {
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {

					T dotSum(0);
					for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
						dotSum += getIns(dataI)[ paramI ] * getDeltas(dataI)[ neuronI ];
					}

					dotSum *= sizeInverse;
					setGrad(neuronI, paramI, dotSum);
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

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::computeDeltasLast(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) {
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				StaticTable<T, NbNeurons>& deltaVecTable(getDeltas(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					deltaVecTable[ neuronI ] = outTable[ neuronI ] - expectedYTable[ neuronI ];
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename LearningRateFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::updateModel(const LearningRateFunc& learningRateFunc, const T& learningRateFactor, const Size epochNum) {
			static_assert( Utility::isBase<LearningRate::BasicLearningRate<T>, LearningRateFunc>::value, "LearningRateFunc type unknown." );

			const T learningRate(learningRateFunc(epochNum) * learningRateFactor);
			for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
				for ( Size paramI(0); paramI < getNbParams(); paramI++ ) {
					const T& grad(getGrads(neuronI)[ paramI ]);
					T& param(getParams(neuronI)[ paramI ]);
					param = param - learningRate * grad;
				}
			}
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename Stream>
		inline bool NeuralLayer<T, NbFeatures, NbNeurons>::read(Stream* stream) {
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
			return true;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<typename Stream>
		inline bool NeuralLayer<T, NbFeatures, NbNeurons>::write(Stream* stream) const {
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
			return true;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline T NeuralLayer<T, NbFeatures, NbNeurons>::computeCostLog(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			T costSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T& expectedY(expectedYTable[ neuronI ]);
					const T& y(outTable[ neuronI ]);
					costSum += expectedY * Math::log(y) + ( T(1) - expectedY ) * Math::log(T(1) - y);
				}
			}

			return -costSum / T(dataIInterval.getSize());
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline T NeuralLayer<T, NbFeatures, NbNeurons>::computeCostQuadratic(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			T costSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));
				const StaticTable<T, NbNeurons>& expectedYTable(expectedOutTableVector.getValueI(dataI));
				for ( Size neuronI(0); neuronI < getNbNeurons(); neuronI++ ) {
					const T delta(expectedYTable[ neuronI ] - outTable[ neuronI ]);
					costSum += delta * delta;
				}
			}

			return Math::sqrt(costSum) / T(dataIInterval.getSize());
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline T NeuralLayer<T, NbFeatures, NbNeurons>::computeCoefficientOfDetermination(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
			StaticTable<T, NbNeurons> meanExpectedTable(computeMeanTable(dataIInterval, expectedOutTableVector));

			T errSum(0);
			T meanSum(0);
			for ( Size dataI(dataIInterval.getBegin()); dataI < dataIInterval.getEnd(); dataI++ ) {
				const StaticTable<T, NbNeurons>& expectedTable(expectedOutTableVector.getValueI(dataI));
				const StaticTable<T, NbNeurons>& outTable(getOuts(dataI));

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

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline StaticTable<T, NbNeurons> NeuralLayer<T, NbFeatures, NbNeurons>::computeMeanTable(const Math::Interval<Size>& dataIInterval, const Vector<StaticTable<T, NbNeurons>>& expectedOutTableVector) const {
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

		template<typename T, Size NbFeatures, Size NbNeurons>
		inline T NeuralLayer<T, NbFeatures, NbNeurons>::computeNeuronWeight(const Size neuronI) const {
			StaticTable<T, NbFeatures + Size(1)> paramTable(getParams(neuronI));

			T weight(0);
			for ( Size paramI(0); paramI < getNbParams(); paramI++ ) {
				weight += paramTable[ paramI ];
			}

			return weight;
		}

		template<typename T, Size NbFeatures, Size NbNeurons>
		template<Size NbFeaturesNext, Size NbNeuronsNext, typename ActivationFunc>
		inline void NeuralLayer<T, NbFeatures, NbNeurons>::computeDeltas(const Math::Interval<Size>& dataIInterval, const NeuralLayer<T, NbFeaturesNext, NbNeuronsNext>& nextNeuralLayer, const ActivationFunc& activationFunc) {
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

	}

}