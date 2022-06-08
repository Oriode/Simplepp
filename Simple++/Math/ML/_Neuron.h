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

		template<typename T, typename Func>
		class Neuron : public IO::BasicIO {
		public:
			Neuron(const Size nbFeatures, const Func & activationFunc = Func());

			void setActivationFunc( const Func& activationFunc = Func());

			const Func& getActivationFunc() const;

			constexpr Size getNbFeatures() const;
			constexpr Size getNbParams() const;
			const Size getNbData() const;

			const Vec<T>& getParams() const;
			Vec<T>& getParams();

			const Vec<T>& getGrads() const;
			Vec<T>& getGrads();

			const T& getParam(const Size paramI) const;
			T& getParam(const Size paramI);

			void setParam(const Size paramI, const T& v);

			const T& getGrad(const Size paramI) const;
			T& getGrad(const Size paramI);

			void setGrad(const Size paramI, const T& v);

			T computeY(const Vec<T>& featureTable) const;

			static void setParamTable(Vec<T> & paramTable);
			static T computeY(const Vec<T> & featureTable, const Vec<T>& paramTable, const Func & activationFunc);

		private:
			const Size nbFeatures;

			Vec<T> paramTable;		// Table of parameters of size [NbFeatures + Size(1)].
			Vec<T> gradTable;		// Table of gradient of size [NbFeatures + Size(1)].

			const Func activationFunc;
		};

		template<typename T, typename Func>
		inline Neuron<T, Func>::Neuron(const Size nbFeatures, const Func& activationFunc) :
			nbFeatures(nbFeatures),
			paramTable(nbFeatures + Size(1)),
			gradTable(nbFeatures + Size(1)),
			activationFunc(activationFunc)
		{
			setParamTable(this->paramTable);
		}

		template<typename T, typename Func>
		inline void Neuron<T, Func>::setActivationFunc(const Func& activationFunc) {
			this->activationFunc = activationFunc;
		}

		template<typename T, typename Func>
		inline const Func& Neuron<T, Func>::getActivationFunc() const {
			return this->activationFunc;
		}

		template<typename T, typename Func>
		inline constexpr Size Neuron<T, Func>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, typename Func>
		inline constexpr Size Neuron<T, Func>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, typename Func>
		inline const Size Neuron<T, Func>::getNbData() const {
			return this->inputVector.getSize();
		}

		template<typename T, typename Func>
		inline const Vec<T>& Neuron<T, Func>::getParams() const {
			return this->paramTable;
		}

		template<typename T, typename Func>
		inline Vec<T>& Neuron<T, Func>::getParams() {
			return this->paramTable;
		}

		template<typename T, typename Func>
		inline const Vec<T>& Neuron<T, Func>::getGrads() const {
			return this->gradTable;
		}

		template<typename T, typename Func>
		inline Vec<T>& Neuron<T, Func>::getGrads() {
			return this->gradTable;
		}

		template<typename T, typename Func>
		inline const T& Neuron<T, Func>::getParam(const Size paramI) const {
			return const_cast< Neuron<T, Func> * >( this )->getParam(paramI);
		}

		template<typename T, typename Func>
		inline T& Neuron<T, Func>::getParam(const Size paramI) {
			return this->paramTable[paramI];
		}

		template<typename T, typename Func>
		inline void Neuron<T, Func>::setParam(const Size paramI, const T& v) {
			this->paramTable[ paramI ] = v;
		}

		template<typename T, typename Func>
		inline const T& Neuron<T, Func>::getGrad(const Size paramI) const {
			return this->gradTable[ paramI ];
		}

		template<typename T, typename Func>
		inline T& Neuron<T, Func>::getGrad(const Size paramI) {
			return this->gradTable[ paramI ];
		}

		template<typename T, typename Func>
		inline void Neuron<T, Func>::setGrad(const Size paramI, const T& v) {
			this->gradTable[ paramI ] = v;
		}

		template<typename T, typename Func>
		inline T Neuron<T, Func>::computeY(const Vec<T>& featureTable) const {
			return Neuron<T, Func>::computeY(featureTable, this->paramTable, this->activationFunc);
		}

		template<typename T, typename Func>
		inline void Neuron<T, Func>::setParamTable(Vec<T>& paramTable) {
			for ( Size i(0); i < paramTable.getSize(); i++ ) {
				paramTable[ i ] = Math::randomF();
			}
		}

		template<typename T, typename Func>
		inline T Neuron<T, Func>::computeY(const Vec<T>& featureTable, const Vec<T>& paramTable, const Func& activationFunc) {
			assert(featureTable.getSize() + Size(1) == paramTable.getSize());

			T y(0);
			for ( Size i(0); i < featureTable.getSize(); i++ ) {
				y += featureTable[ i ] * paramTable[ i ];
			}
			y += paramTable[ featureTable.getSize() ];
			return activationFunc(y);
		}

	}

}