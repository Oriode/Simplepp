#pragma once

#include "../SimpleLog.h"
#include "../Utility.h"

#include "../BasicVector.h"
#include "Vec2.h"

namespace Math {

	template<typename T>
	class Vec : public BasicVector<T> {
	public:
		Vec(const Size size);
		template<typename V>
		Vec(const V& v);
		template<typename C, Size N>
		Vec(const C(&v)[ N ]);
		template<typename C>
		Vec(const BasicVector<C>& v);
		Vec(Vec<T>&& v);

		~Vec();

		/************************************************************************/
		/* ================            COPY OPERATOR           ================ */
		/************************************************************************/

		template<typename C, Size N>
		Vec<T>& operator=(const C(&v)[ N ]);
		template<typename C>
		Vec<T>& operator=(const BasicVector<C>& v);
		template<typename V>
		Vec<T>& operator=(const V& v);
		Vec<T>& operator=(Vec<T>&& v);

		/************************************************************************/
		/* ================             ARITHMETIC             ================ */
		/************************************************************************/

		template<typename V>
		Vec<T> & operator+=(const V& v);
		Vec<T>& operator+=(const T& s);

		template<typename V>
		Vec<T>& operator-=(const V& v);
		Vec<T>& operator-=(const T& s);

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		void zeros();
		void ones();
		void randomF();
		T sum() const;
		T mean() const;
		T standardDeviation() const;

	private:
	};

	/************************************************************************/
	/* ================             ARITHMETIC             ================ */
	/************************************************************************/

	template<typename T>
	Vec<T> operator+(const Vec<T>& v1, const Vec<T> & v2);

	template<typename T>
	Vec<T> operator+(const Vec<T>& v, const T& s);

	template<typename T>
	Vec<T> operator+(const T& s, const Vec<T>& v);

	template<typename T, typename V>
	Vec<T> operator+(const Vec<T>& v1, const V& v2);

	template<typename T, typename V>
	Vec<T> operator+(const V& v1, const Vec<T>& v2);


















	template<typename T>
	inline Vec<T>::Vec(const Size size) :
		BasicVector<T>(size)
	{}

	template<typename T>
	inline Vec<T>::Vec(Vec<T>&& v) :
		BasicVector<T>(Utility::toRValue(v))
	{
	}

	template<typename T>
	inline Vec<T>::~Vec() {

	}

	template<typename T>
	inline void Vec<T>::zeros() {
		fill(T(0));
	}

	template<typename T>
	inline void Vec<T>::ones() {
		fill(T(1));
	}

	template<typename T>
	inline void Vec<T>::randomF() {
		for ( Size i(0); i < this->size; i++ ) {
			this->dataTable[ i ] = Math::randomF();
		}
	}

	template<typename T>
	inline T Vec<T>::sum() const {
		T sumValue(0);
		for ( Size i(0); i < this->size; i++ ) {
			sumValue += this->dataTable[ i ];
		}
		return sumValue;
	}

	template<typename T>
	inline T Vec<T>::mean() const {
		return sum() / T(this->size);
	}

	template<typename T>
	inline T Vec<T>::standardDeviation() const {
		if ( this->size == Size(0) ) {
			return T(0);
		} else {
			T minV(this->dataTable[ 0 ]);
			T maxV(this->dataTable[ 0 ]);

			for ( Size i(1); i < this->size; i++ ) {
				const T& v(this->dataTable[ i ]);

				if ( v < minV ) {
					minV = v;
				} else if ( v > maxV ) {
					maxV = v;
				}
			}

			return maxV - minV;
		}
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator=(Vec<T>&& v) {
		BasicVector<T>::operator=(Utility::toRValue(v));

		return *this;
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator+=(const T& s) {
		for ( Size i(0); i < this->size; i++ ) {
			this->dataTable[ i ] += s;
		}

		return *this;
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator-=(const T& s) {
		for ( Size i(0); i < this->size; i++ ) {
			this->dataTable[ i ] -= s;
		}

		return *this;
	}

	template<typename T>
	template<typename V>
	inline Vec<T>& Vec<T>::operator+=(const V& v) {
		Size minSize(Math::min(getSize(), v.getSize()));
		for ( Size i(0); i < minSize; i++ ) {
			this->dataTable[ i ] += v[ i ];
		}

		return *this;
	}

	template<typename T>
	template<typename V>
	inline Vec<T>& Vec<T>::operator-=(const V& v) {
		Size minSize(Math::min(getSize(), v.getSize()));
		for ( Size i(0); i < minSize; i++ ) {
			this->dataTable[ i ] -= v[ i ];
		}

		return *this;
	}

	template<typename T>
	template<typename V>
	inline Vec<T>::Vec(const V& v) :
		BasicVector<T>(v.getSize())
	{
		for ( Size i(0); i < this->size; i++ ) {
			this->dataTable[ i ] = v[ i ];
		}
	}

	template<typename T>
	template<typename C, Size N>
	inline Vec<T>::Vec(const C(&v)[ N ]) :
		BasicVector<T>(v)
	{
	}

	template<typename T>
	template<typename C>
	inline Vec<T>::Vec(const BasicVector<C>& v) :
		BasicVector<T>(v)
	{
	}

	template<typename T>
	template<typename C, Size N>
	inline Vec<T>& Vec<T>::operator=(const C(&v)[ N ]) {
		BasicVector<T>::operator=(v);

		return *this;
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator=(const BasicVector<C>& v) {
		BasicVector<T>::operator=(v);

		return *this;
	}

	template<typename T>
	template<typename V>
	inline Vec<T>& Vec<T>::operator=(const V& v) {
		resizeNoCopy(v.getSize());
		Utility::copy(this->dataTable, v.getData(), this->size);

		return *this;
	}

	template<typename T>
	Vec<T> operator+(const Vec<T>& v1, const Vec<T>& v2) {
		_assert(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = v1[ i ] + v2[ i ];
		}
		return r;
	}

	template<typename T>
	Vec<T> operator+(const Vec<T>& v, const T& s) {
		Vec<T> r(v.getSize());
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = v[ i ] + s;
		}
		return r;
	}

	template<typename T>
	Vec<T> operator+(const T& s, const Vec<T>& v) {
		Vec<T> r(v.getSize());
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = v[ i ] + s;
		}
		return r;
	}

	template<typename T, typename V>
	Vec<T> operator+(const Vec<T>& v1, const V& v2) {
		_assert(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = v1[ i ] + v2[ i ];
		}
		return r;
	}

	template<typename T, typename V>
	Vec<T> operator+(const V& v1, const Vec<T>& v2) {
		_assert(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = v1[ i ] + v2[ i ];
		}
		return r;
	}

}

#include "Vec.hpp"