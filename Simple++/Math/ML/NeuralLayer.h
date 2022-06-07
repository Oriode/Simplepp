#pragma once

#include "Neurode.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		class NeuralLayer {
		public:
			NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inVector);

			constexpr Size getNbFeatures() const;
			constexpr Size getNbOut() const;
			constexpr Size getNbParams() const;

			void addData();

			const StaticTable<T, NbFeatures>& getIns(const Size dataI) const;
			const StaticTable<T, NbFeatures + Size(1)>& getParams(const Size neurodeI) const;
			const StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neurodeI) const;
			StaticTable<T, NbFeatures + Size(1)>& getGrads(const Size neurodeI);
			const StaticTable<T, NbNeurodes>& getOuts(const Size dataI) const;
			StaticTable<T, NbNeurodes>& getDeltas(const Size dataI);

			const Vector< StaticTable<T, NbFeatures>>& getInVector() const;
			const Vector< StaticTable<T, NbNeurodes>>& getOutVector() const;
			Vector< StaticTable<T, NbNeurodes>>& getOutVector();
			const Vector<StaticTable<T, NbNeurodes>>& getDeltaVector() const;
			Vector<StaticTable<T, NbNeurodes>>& getDeltaVector();

			const Func& getActivationFunc(const Size neurodeI) const;

			T computeY(const Size neurodeI, const Size dataI) const;
			T computeY(const Size neurodeI, const StaticTable<T, NbFeatures>& featureTable) const;
			T computeGrad(const Size neurodeI, const Size paramI) const;
			void setOut(const Size neurodeI, const Size dataI, const T& v);
			const T& getOut(const Size neurodeI, const Size dataI);

			const T& getParam(const Size neurodeI, const Size paramI) const;
			T& getParam(const Size neurodeI, const Size paramI);

			void setParam(const Size neurodeI, const Size paramI, const T& v);

			const T& getGrad(const Size neurodeI, const Size paramI) const;
			T& getGrad(const Size neurodeI, const Size paramI);

			void setGrad(const Size neurodeI, const Size paramI, const T& v);

		private:
			const Vector<StaticTable<T, NbFeatures>>* inVector;
			Vector<StaticTable<T, NbNeurodes>> outVector;
			Vector<StaticTable<T, NbNeurodes>> deltaVector;

			StaticTable<Neurode<T, NbFeatures, Func>, NbNeurodes> neurodeTable;
		};

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline NeuralLayer<T, NbFeatures, NbNeurodes, Func>::NeuralLayer(const Vector<StaticTable<T, NbFeatures>>* inVector) :
			inVector(inVector)
		{
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getNbOut() const {
			return NbNeurodes;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurodes, Func>::addData() {
			this->outVector.push(StaticTable<T, NbNeurodes>());
			this->deltaVector.push(StaticTable<T, NbNeurodes>());
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const StaticTable<T, NbFeatures>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getIns(const Size dataI) const {
			return this->inVector->getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getParams(const Size neurodeI) const {
			return this->neurodeTable[ neurodeI ].getParams();
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getGrads(const Size neurodeI) const {
			return this->neurodeTable[ neurodeI ].getGrads();
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline StaticTable<T, NbFeatures + Size(1)>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getGrads(const Size neurodeI) {
			return this->neurodeTable[ neurodeI ].getGrads();
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const StaticTable<T, NbNeurodes>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getOuts(const Size dataI) const {
			return this->outVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline StaticTable<T, NbNeurodes>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getDeltas(const Size dataI) {
			return this->deltaVector.getValueI(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const Vector<StaticTable<T, NbFeatures>>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getInVector() const {
			return *this->inVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const Vector<StaticTable<T, NbNeurodes>>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getOutVector() const {
			return this->outVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline Vector<StaticTable<T, NbNeurodes>>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getOutVector() {
			return this->outVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const Vector<StaticTable<T, NbNeurodes>>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getDeltaVector() const {
			return this->deltaVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline Vector<StaticTable<T, NbNeurodes>>& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getDeltaVector() {
			return this->deltaVector;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const Func& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getActivationFunc(const Size neurodeI) const {
			return this->neurodeTable[ neurodeI ].getActivationFunc();
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurodes, Func>::computeY(const Size neurodeI, const Size dataI) const {
			return this->neurodeTable[ neurodeI ].computeY(getIns(dataI));
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurodes, Func>::computeY(const Size neurodeI, const StaticTable<T, NbFeatures>& featureTable) const {
			return this->neurodeTable[ neurodeI ].computeY(featureTable);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurodes, Func>::computeGrad(const Size neurodeI, const Size paramI) const {
			return this->neurodeTable[ neurodeI ].computeGrad(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurodes, Func>::setOut(const Size neurodeI, const Size dataI, const T& v) {
			this->outVector.getValueI(dataI)[ neurodeI ] = v;
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getOut(const Size neurodeI, const Size dataI) {
			return this->outVector.getValueI(dataI)[ neurodeI ];
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getParam(const Size neurodeI, const Size paramI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurodes, Func> * >( this )->getParam(neurodeI, paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline T& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getParam(const Size neurodeI, const Size paramI) {
			return this->neurodeTable[ neurodeI ].getParam(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurodes, Func>::setParam(const Size neurodeI, const Size paramI, const T& v) {
			this->neurodeTable[ neurodeI ].setParam(paramI, v);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getGrad(const Size neurodeI, const Size paramI) const {
			return this->neurodeTable[ neurodeI ].getGrad(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline T& NeuralLayer<T, NbFeatures, NbNeurodes, Func>::getGrad(const Size neurodeI, const Size paramI) {
			return this->neurodeTable[ neurodeI ].getGrad(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurodes, typename Func>
		inline void NeuralLayer<T, NbFeatures, NbNeurodes, Func>::setGrad(const Size neurodeI, const Size paramI, const T& v) {
			this->neurodeTable[ neurodeI ].setGrad(paramI, v);
		}

	}

}