#pragma once

#include "../../IO/IO.h"
#include "../../StaticTable.h"
#include "../../Vector.h"
#include "../../String.h"

#include "../Math.h"
#include "../Vec.h"

#include "Data.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, typename ActivationFunc>
		class Neuron : public IO::BasicIO {
		public:
			Neuron(const ActivationFunc & activationFunc = ActivationFunc());

			void setActivationFunc(const ActivationFunc& activationFunc = ActivationFunc());

			const ActivationFunc& getActivationFunc() const;

			constexpr Size getNbFeatures() const;
			constexpr Size getNbParams() const;

			const StaticTable<T, NbFeatures + Size(1)>& getParams() const;
			StaticTable<T, NbFeatures + Size(1)>& getParams();

			const StaticTable<T, NbFeatures + Size(1)>& getGrads() const;
			StaticTable<T, NbFeatures + Size(1)>& getGrads();

			const T& getParam(const Size paramI) const;
			T& getParam(const Size paramI);

			void setParam(const Size paramI, const T& v);

			const T& getGrad(const Size paramI) const;
			T& getGrad(const Size paramI);

			void setGrad(const Size paramI, const T& v);

			T computeY(const StaticTable<T, NbFeatures>& featureTable) const;

			static void setParamTable(StaticTable<T, NbFeatures + Size(1)> & paramTable);
			static T computeY(const StaticTable<T, NbFeatures> & featureTable, const StaticTable<T, NbFeatures + Size(1)>& paramTable, const ActivationFunc & activationFunc);

		private:
			StaticTable<T, NbFeatures + Size(1)> paramTable;		// Table of parameters of size [NbFeatures + Size(1)].
			StaticTable<T, NbFeatures + Size(1)> gradTable;			// Table of gradient of size [NbFeatures + Size(1)].

			const ActivationFunc activationFunc;
		};

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline Neuron<T, NbFeatures, ActivationFunc>::Neuron(const ActivationFunc& activationFunc) :
			activationFunc(activationFunc)
		{
			setParamTable(this->paramTable);
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline void Neuron<T, NbFeatures, ActivationFunc>::setActivationFunc(const ActivationFunc& activationFunc) {
			this->activationFunc = activationFunc;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline const ActivationFunc& Neuron<T, NbFeatures, ActivationFunc>::getActivationFunc() const {
			return this->activationFunc;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline constexpr Size Neuron<T, NbFeatures, ActivationFunc>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline constexpr Size Neuron<T, NbFeatures, ActivationFunc>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline const StaticTable<T, NbFeatures + Size(1)>& Neuron<T, NbFeatures, ActivationFunc>::getParams() const {
			return this->paramTable;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline StaticTable<T, NbFeatures + Size(1)>& Neuron<T, NbFeatures, ActivationFunc>::getParams() {
			return this->paramTable;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline const StaticTable<T, NbFeatures + Size(1)>& Neuron<T, NbFeatures, ActivationFunc>::getGrads() const {
			return this->gradTable;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline StaticTable<T, NbFeatures + Size(1)>& Neuron<T, NbFeatures, ActivationFunc>::getGrads() {
			return this->gradTable;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline const T& Neuron<T, NbFeatures, ActivationFunc>::getParam(const Size paramI) const {
			return const_cast< Neuron<T, NbFeatures, ActivationFunc> * >( this )->getParam(paramI);
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline T& Neuron<T, NbFeatures, ActivationFunc>::getParam(const Size paramI) {
			return this->paramTable[paramI];
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline void Neuron<T, NbFeatures, ActivationFunc>::setParam(const Size paramI, const T& v) {
			this->paramTable[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline const T& Neuron<T, NbFeatures, ActivationFunc>::getGrad(const Size paramI) const {
			return this->gradTable[ paramI ];
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline T& Neuron<T, NbFeatures, ActivationFunc>::getGrad(const Size paramI) {
			return this->gradTable[ paramI ];
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline void Neuron<T, NbFeatures, ActivationFunc>::setGrad(const Size paramI, const T& v) {
			this->gradTable[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline T Neuron<T, NbFeatures, ActivationFunc>::computeY(const StaticTable<T, NbFeatures>& featureTable) const {
			return Neuron<T, NbFeatures, ActivationFunc>::computeY(featureTable, this->paramTable, this->activationFunc);
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline void Neuron<T, NbFeatures, ActivationFunc>::setParamTable(StaticTable<T, NbFeatures + Size(1)>& paramTable) {
			for ( Size i(0); i < NbFeatures + Size(1); i++ ) {
				paramTable[ i ] = Math::randomF();
			}
		}

		template<typename T, Size NbFeatures, typename ActivationFunc>
		inline T Neuron<T, NbFeatures, ActivationFunc>::computeY(const StaticTable<T, NbFeatures>& featureTable, const StaticTable<T, NbFeatures + Size(1)>& paramTable, const ActivationFunc& activationFunc) {
			T y(0);
			for ( Size i(0); i < NbFeatures; i++ ) {
				y += featureTable[ i ] * paramTable[ i ];
			}
			y += paramTable[ NbFeatures ];
			return activationFunc(y);
		}

	}

}