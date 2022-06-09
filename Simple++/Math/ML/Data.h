#pragma once

#include "../../StaticTable.h"
#include "../../IO/BasicIO.h"
#include "../../BasicVector.h"

namespace Math {

	namespace ML {

		template<typename T, Size NbFeatures, Size NbOut>
		class Data : public IO::BasicIO {
		public:
			Data();
			template<typename C>
			Data(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ NbOut ]);
			Data(const Data<T, NbFeatures, NbOut>& data);
			Data(Data<T, NbFeatures, NbOut>&& data);

			Data<T, NbFeatures, NbOut>& operator=(const Data<T, NbFeatures, NbOut>& data);
			Data<T, NbFeatures, NbOut>& operator=(Data<T, NbFeatures, NbOut>&& data);

			void setFeature(const Size i, const T & v);
			void setOut(const Size i, const T & v);

			const T& getFeature(const Size i) const;
			T& getFeature(const Size i);

			const T& getOut(const Size i) const;
			T& getOut(const Size i);

			const StaticTable<T, NbFeatures>& getFeatures() const;
			StaticTable<T, NbFeatures>& getFeatures();

			const StaticTable<T, NbOut>& getOuts() const;
			StaticTable<T, NbOut>& getOuts();

			constexpr Size getNbFeatures() const;
			constexpr Size getNbOut() const;

			void setFeaturesRandom(const T& min = T(-1), const T& max = T(1));

		private:
			StaticTable<T, NbFeatures> featureTable;
			StaticTable<T, NbOut> outTable;
		};

		template<typename T, Size NbFeatures, Size NbOut>
		inline Data<T, NbFeatures, NbOut>::Data() {}

		template<typename T, Size NbFeatures, Size NbOut>
		inline Data<T, NbFeatures, NbOut>::Data(const Data<T, NbFeatures, NbOut>& data) :
			featureTable(data.featureTable),
			outTable(data.outTable)
		{}

		template<typename T, Size NbFeatures, Size NbOut>
		inline Data<T, NbFeatures, NbOut>::Data(Data<T, NbFeatures, NbOut> && data) :
			featureTable(Utility::toRValue(data.featureTable)),
			outTable(Utility::toRValue(data.outTable))
		{}

		template<typename T, Size NbFeatures, Size NbOut>
		inline Data<T, NbFeatures, NbOut>& Data<T, NbFeatures, NbOut>::operator=(const Data<T, NbFeatures, NbOut>&data) {
			this->featureTable = data.featureTable;
			this->outTable = data.outTable;

			return *this;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline Data<T, NbFeatures, NbOut>& Data<T, NbFeatures, NbOut>::operator=(Data<T, NbFeatures, NbOut>&& data) {
			this->featureTable = Utility::toRValue(data.featureTable);
			this->outTable = Utility::toRValue(data.outTable);

			return *this;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void Data<T, NbFeatures, NbOut>::setFeature(const Size i, const T& v) {
			this->featureTable[i] = v;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void Data<T, NbFeatures, NbOut>::setOut(const Size i, const T& v) {
			this->outTable[i] = v;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline const T& Data<T, NbFeatures, NbOut>::getFeature(const Size i) const {
			return const_cast< Data<T, NbFeatures, NbOut> * >( this )->getFeature(i);
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T& Data<T, NbFeatures, NbOut>::getFeature(const Size i) {
			return this->featureTable[i];
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline const T& Data<T, NbFeatures, NbOut>::getOut(const Size i) const {
			return const_cast< Data<T, NbFeatures, NbOut> * >( this )->getOut(i);
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline T& Data<T, NbFeatures, NbOut>::getOut(const Size i) {
			return this->outTable[i];
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline const StaticTable<T, NbFeatures>& Data<T, NbFeatures, NbOut>::getFeatures() const {
			return const_cast< Data<T, NbFeatures, NbOut> * >( this )->getFeatures();
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline StaticTable<T, NbFeatures>& Data<T, NbFeatures, NbOut>::getFeatures() {
			return this->featureTable;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline const StaticTable<T, NbOut>& Data<T, NbFeatures, NbOut>::getOuts() const {
			return const_cast< Data<T, NbFeatures, NbOut> * >( this )->getOuts();
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline StaticTable<T, NbOut>& Data<T, NbFeatures, NbOut>::getOuts() {
			return this->outTable;
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline constexpr Size Data<T, NbFeatures, NbOut>::getNbFeatures() const {
			return this->featureTable.getSize();
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline constexpr Size Data<T, NbFeatures, NbOut>::getNbOut() const {
			return this->outTable.getSize();
		}

		template<typename T, Size NbFeatures, Size NbOut>
		inline void Data<T, NbFeatures, NbOut>::setFeaturesRandom(const T& min, const T& max) {
			for ( Size i(0); i < this->featureTable.getSize(); i++ ) {
				this->featureTable[i] = Math::random(min, max);
			}
		}

		template<typename T, Size NbFeatures, Size NbOut>
		template<typename C>
		inline Data<T, NbFeatures, NbOut>::Data(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ NbOut ]) :
			featureTable(featureTable),
			outTable(outTable)
		{}

	}

}