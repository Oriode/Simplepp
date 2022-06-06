#pragma once

#include "Neurode.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		class NeuralLayer {
		public:
			NeuralLayer();

			constexpr Size getNbFeatures() const;
			constexpr Size getNbOut() const;
			constexpr Size getNbParams() const;

			StaticTable<T, NbFeatures>& getFeatures();

			T computeY(const Size neurodeI, const Size dataI) const;
			T computeGrad(const Size neurodeI, const Size paramI) const;

			const T& getParam(const Size neurodeI, const Size paramI) const;
			T& getParam(const Size neurodeI, const Size paramI);

		private:
			StaticTable<T, NbFeatures> featureTable;

			StaticTable<Neurode<T, NbFeatures, NbFeatures + 1, Func>, NbNeurode> neurodeTable;
		};

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline NeuralLayer<T, NbFeatures, NbNeurode, Func>::NeuralLayer() {
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurode, Func>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurode, Func>::getNbOut() const {
			return NbNeurode;
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline constexpr Size NeuralLayer<T, NbFeatures, NbNeurode, Func>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline StaticTable<T, NbFeatures>& NeuralLayer<T, NbFeatures, NbNeurode, Func>::getFeatures() {
			return this->featureTable;
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurode, Func>::computeY(const Size neurodeI, const Size dataI) const {
			return this->neurodeTable[ neurodeI ].computeY(dataI);
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline T NeuralLayer<T, NbFeatures, NbNeurode, Func>::computeGrad(const Size neurodeI, const Size paramI) const {
			return this->neurodeTable[ neurodeI ].computeGrad(paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline const T& NeuralLayer<T, NbFeatures, NbNeurode, Func>::getParam(const Size neurodeI, const Size paramI) const {
			return const_cast< NeuralLayer<T, NbFeatures, NbNeurode, Func> * >( this )->getParam(neurodeI, paramI);
		}

		template<typename T, Size NbFeatures, Size NbNeurode, typename Func>
		inline T& NeuralLayer<T, NbFeatures, NbNeurode, Func>::getParam(const Size neurodeI, const Size paramI) {
			return this->neurodeTable[ neurodeI ].getParam(paramI);
		}

	}

}