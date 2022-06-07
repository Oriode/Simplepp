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

		template<typename T, Size NbFeatures, typename Func = Math::Operations::Identity>
		class Neurode : public IO::BasicIO {
		public:
			Neurode(const Func & activationFunc = Func());

			constexpr Size getNbFeatures() const;
			constexpr Size getNbParams() const;
			const Size getNbData() const;

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
			static T computeY(const StaticTable<T, NbFeatures> & featureTable, const StaticTable<T, NbFeatures + Size(1)>& paramTable, const Func & activationFunc);

		private:
			StaticTable<T, NbFeatures + Size(1)> paramTable;		// Table of parameters of size [NbFeatures + Size(1)].
			StaticTable<T, NbFeatures + Size(1)> gradTable;			// Table of gradient of size [NbFeatures + Size(1)].

			const Func activationFunc;
		};

		template<typename T, Size NbFeatures, typename Func>
		inline Neurode<T, NbFeatures, Func>::Neurode(const Func& activationFunc) :
			activationFunc(activationFunc)
		{
			setParamTable(this->paramTable);
		}

		template<typename T, Size NbFeatures, typename Func>
		inline constexpr Size Neurode<T, NbFeatures, Func>::getNbFeatures() const {
			return NbFeatures;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline constexpr Size Neurode<T, NbFeatures, Func>::getNbParams() const {
			return NbFeatures + Size(1);
		}

		template<typename T, Size NbFeatures, typename Func>
		inline const Size Neurode<T, NbFeatures, Func>::getNbData() const {
			return this->inputVector.getSize();
		}

		template<typename T, Size NbFeatures, typename Func>
		inline const StaticTable<T, NbFeatures + Size(1)>& Neurode<T, NbFeatures, Func>::getParams() const {
			return this->paramTable;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline StaticTable<T, NbFeatures + Size(1)>& Neurode<T, NbFeatures, Func>::getParams() {
			return this->paramTable;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline const StaticTable<T, NbFeatures + Size(1)>& Neurode<T, NbFeatures, Func>::getGrads() const {
			return this->gradTable;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline StaticTable<T, NbFeatures + Size(1)>& Neurode<T, NbFeatures, Func>::getGrads() {
			return this->gradTable;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline const T& Neurode<T, NbFeatures, Func>::getParam(const Size paramI) const {
			return const_cast< Neurode<T, NbFeatures, Func> * >( this )->getParam(paramI);
		}

		template<typename T, Size NbFeatures, typename Func>
		inline T& Neurode<T, NbFeatures, Func>::getParam(const Size paramI) {
			return this->paramTable[paramI];
		}

		template<typename T, Size NbFeatures, typename Func>
		inline void Neurode<T, NbFeatures, Func>::setParam(const Size paramI, const T& v) {
			this->paramTable[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline const T& Neurode<T, NbFeatures, Func>::getGrad(const Size paramI) const {
			return this->gradTable[ paramI ];
		}

		template<typename T, Size NbFeatures, typename Func>
		inline T& Neurode<T, NbFeatures, Func>::getGrad(const Size paramI) {
			return this->gradTable[ paramI ];
		}

		template<typename T, Size NbFeatures, typename Func>
		inline void Neurode<T, NbFeatures, Func>::setGrad(const Size paramI, const T& v) {
			this->gradTable[ paramI ] = v;
		}

		template<typename T, Size NbFeatures, typename Func>
		inline T Neurode<T, NbFeatures, Func>::computeY(const StaticTable<T, NbFeatures>& featureTable) const {
			return Neurode<T, NbFeatures, Func>::computeY(featureTable, this->paramTable, this->activationFunc);
		}

		template<typename T, Size NbFeatures, typename Func>
		inline void Neurode<T, NbFeatures, Func>::setParamTable(StaticTable<T, NbFeatures + Size(1)>& paramTable) {
			for ( Size i(0); i < NbFeatures + Size(1); i++ ) {
				paramTable[ i ] = Math::randomF();
			}
		}

		template<typename T, Size NbFeatures, typename Func>
		inline T Neurode<T, NbFeatures, Func>::computeY(const StaticTable<T, NbFeatures>& featureTable, const StaticTable<T, NbFeatures + Size(1)>& paramTable, const Func& activationFunc) {
			T y(0);
			for ( Size i(0); i < NbFeatures; i++ ) {
				y += featureTable[ i ] * paramTable[ i ];
			}
			y += paramTable[ NbFeatures ];
			return activationFunc(y);
		}

	}

}