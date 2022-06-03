#pragma once

#include "../../IO/BasicIO.h"
#include "../../IO/SimpleIO.h"
#include "../../BasicVector.h"

namespace Math {

	namespace ML {

		template<typename T>
		class Data : public IO::BasicIO {
		public:
			Data();
			Data(const Size nbFeatures, const Size nbOut);
			template<typename C, Size NbFeatures, Size nbOut>
			Data(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ nbOut ]);
			Data(const Data<T>& data);
			Data(Data<T>&& data);

			Data<T>& operator=(const Data<T>& data);
			Data<T>& operator=(Data<T>&& data);

			void setFeature(const Size i, const T & v);
			void setOut(const Size i, const T & v);

			const T& getFeature(const Size i) const;
			T& getFeature(const Size i);

			const T& getOut(const Size i) const;
			T& getOut(const Size i);

			const BasicVector<T>& getFeatures() const;
			BasicVector<T>& getFeatures();

			const BasicVector<T>& getOuts() const;
			BasicVector<T>& getOuts();

			const Size getNbFeatures() const;
			const Size getNbOut() const;

			void setFeaturesRandom(const T& min = T(-1), const T& max = T(1));

		private:
			BasicVector<T> featureTable;
			BasicVector<T> outTable;
		};

		template<typename T>
		inline Data<T>::Data() {}

		template<typename T>
		inline Data<T>::Data(const Size nbFeatures, const Size nbOut) :
			featureTable(nbFeatures),
			outTable(nbOut)
		{}

		template<typename T>
		inline Data<T>::Data(const Data<T>& data) :
			featureTable(data.featureTable),
			outTable(data.outTable)
		{}

		template<typename T>
		inline Data<T>::Data(Data<T> && data) :
			featureTable(Utility::toRValue(data.featureTable)),
			outTable(Utility::toRValue(data.outTable))
		{}

		template<typename T>
		inline Data<T>& Data<T>::operator=(const Data<T>&data) {
			this->featureTable = data.featureTable;
			this->outTable = data.outTable;

			return *this;
		}

		template<typename T>
		inline Data<T>& Data<T>::operator=(Data<T>&& data) {
			this->featureTable = Utility::toRValue(data.featureTable);
			this->outTable = Utility::toRValue(data.outTable);

			return *this;
		}

		template<typename T>
		inline void Data<T>::setFeature(const Size i, const T& v) {
			this->featureTable.setValueI(i, v);
		}

		template<typename T>
		inline void Data<T>::setOut(const Size i, const T& v) {
			this->outTable.setValueI(i, v);
		}

		template<typename T>
		inline const T& Data<T>::getFeature(const Size i) const {
			return const_cast< Data<T> * >( this )->getFeature(i);
		}

		template<typename T>
		inline T& Data<T>::getFeature(const Size i) {
			return this->featureTable.getValueI(i);
		}

		template<typename T>
		inline const T& Data<T>::getOut(const Size i) const {
			return const_cast< Data<T> * >( this )->getOut(i);
		}

		template<typename T>
		inline T& Data<T>::getOut(const Size i) {
			return this->outTable.getValueI(i);
		}

		template<typename T>
		inline const BasicVector<T>& Data<T>::getFeatures() const {
			return const_cast< Data<T> * >( this )->getFeatures();
		}

		template<typename T>
		inline BasicVector<T>& Data<T>::getFeatures() {
			return this->featureTable;
		}

		template<typename T>
		inline const BasicVector<T>& Data<T>::getOuts() const {
			return const_cast< Data<T> * >( this )->getOuts();
		}

		template<typename T>
		inline BasicVector<T>& Data<T>::getOuts() {
			return this->outTable;
		}

		template<typename T>
		inline const Size Data<T>::getNbFeatures() const {
			return this->featureTable.getSize();
		}

		template<typename T>
		inline const Size Data<T>::getNbOut() const {
			return this->outTable.getSize();
		}

		template<typename T>
		inline void Data<T>::setFeaturesRandom(const T& min, const T& max) {
			for ( Size i(0); i < this->featureTable.getSize(); i++ ) {
				this->featureTable.setValueI(i, Math::random(min, max));
			}
		}

		template<typename T>
		template<typename C, Size NbFeatures, Size nbOut>
		inline Data<T>::Data(const C(&featureTable)[ NbFeatures ], const C(&outTable)[ nbOut ]) :
			featureTable(featureTable),
			outTable(outTable)
		{}

	}

}