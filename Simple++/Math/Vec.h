#pragma once

#include "../Log.h"
#include "../Utility.h"
#include "../String.h"

#include "BasicMath.h"
#include "../BasicVector.h"

namespace Math {

	template<typename T, bool Static = false>
	class Vec : public BasicVector<T, Static> {
	public:
		template<typename C>
		friend class Mat;

		/************************************************************************/
		/* ================             CONSTRUCTOR            ================ */
		/************************************************************************/

		Vec();
		Vec(const Size size);
		//template<typename V>
		//Vec(const V& v);
		template<typename C, Size N>
		Vec(const C(&v)[ N ]);
		template<typename C>
		Vec(const Table<C>& v);
		Vec(const Vec<T, Static>& v);
		Vec(BasicVector<T, Static>&& v);

		~Vec();

		/************************************************************************/
		/* ================            COPY OPERATOR           ================ */
		/************************************************************************/

		template<typename C, Size N>
		Vec<T, Static>& operator=(const C(&v)[ N ]);
		template<typename C>
		Vec<T, Static>& operator=(const Table<C>& v);
		Vec<T, Static>& operator=(const Vec<T, Static>& v);
		//template<typename V>
		//Vec<T, Static>& operator=(const V& v);
		Vec<T, Static>& operator=(BasicVector<T, Static>&& v);

		/************************************************************************/
		/* ================             ARITHMETIC             ================ */
		/************************************************************************/

		template<typename Functor, typename C>
		Vec<T, Static>& apply(Functor & functor, const Table<C>& v);
		template<typename Functor>
		Vec<T, Static>& apply(Functor& functor, const T& s);
		template<typename Functor>
		Vec<T, Static>& apply(Functor& functor);

		template<typename C>
		Vec<T, Static> & operator+=(const Table<C>& v);
		Vec<T, Static>& operator+=(const T& s);

		template<typename C>
		Vec<T, Static>& operator-=(const Table<C>& v);
		Vec<T, Static>& operator-=(const T& s);

		template<typename C>
		Vec<T, Static>& operator*=(const Table<C>& v);
		Vec<T, Static>& operator*=(const T& s);

		template<typename C>
		Vec<T, Static>& operator/=(const Table<C>& v);
		Vec<T, Static>& operator/=(const T& s);

		template<typename C>
		Vec<T, Static>& operator%=(const Table<C>& v);
		Vec<T, Static>& operator%=(const T& s);

		Vec<T, Static>& operator++();
		Vec<T, Static>& operator--();
		Vec<T, Static> operator-();

		/************************************************************************/
		/* ================              LOGICAL               ================ */
		/************************************************************************/

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		void zeros();
		void ones();
		void randomF();

		template<typename S = String>
		S toString() const;

	protected:
		Vec(const Size size, T* dataTable);
	};

	template<typename T>
	using SVec = Vec<T, true>;

	/************************************************************************/
	/* ================             ARITHMETIC             ================ */
	/************************************************************************/

	template<typename T, typename Functor>
	Vec<T> apply(Functor & functor, const Vec<T>& v1, const Vec<T>& v2);
	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const Vec<T>& v, const T& s);
	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const T& s, const Vec<T>& v);
	template<typename T, typename Functor, typename C>
	Vec<T> apply(Functor& functor, const Vec<T>& v1, const Table<C>& v2);
	template<typename T, typename Functor, typename C>
	Vec<T> apply(Functor& functor, const Table<C>& v1, const Vec<T>& v2);
	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const Vec<T>& v);

	template<typename T, bool Static>
	Vec<T, Static> operator+(const Vec<T, Static>& v1, const Vec<T, Static> & v2);
	template<typename T, bool Static>
	Vec<T, Static> operator+(const Vec<T, Static>& v, const T& s);
	template<typename T, bool Static>
	Vec<T, Static> operator+(const T& s, const Vec<T, Static>& v);
	/*template<typename T, typename V>
	Vec<T, Static> operator+(const Vec<T, Static>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T, Static> operator+(const V& v1, const Vec<T, Static>& v2);*/

	template<typename T, bool Static>
	Vec<T, Static> operator-(const Vec<T, Static>& v1, const Vec<T, Static>& v2);
	template<typename T, bool Static>
	Vec<T, Static> operator-(const Vec<T, Static>& v, const T& s);
	template<typename T, bool Static>
	Vec<T, Static> operator-(const T& s, const Vec<T, Static>& v);
	/*template<typename T, typename V>
	Vec<T, Static> operator-(const Vec<T, Static>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T, Static> operator-(const V& v1, const Vec<T, Static>& v2);*/

	template<typename T, bool Static>
	Vec<T, Static> operator*(const Vec<T, Static>& v1, const Vec<T, Static>& v2);
	template<typename T, bool Static>
	Vec<T, Static> operator*(const Vec<T, Static>& v, const T& s);
	template<typename T, bool Static>
	Vec<T, Static> operator*(const T& s, const Vec<T, Static>& v);
	/*template<typename T, typename V>
	Vec<T, Static> operator*(const Vec<T, Static>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T, Static> operator*(const V& v1, const Vec<T, Static>& v2);*/

	template<typename T, bool Static>
	Vec<T, Static> operator/(const Vec<T, Static>& v1, const Vec<T, Static>& v2);
	template<typename T, bool Static>
	Vec<T, Static> operator/(const Vec<T, Static>& v, const T& s);
	template<typename T, bool Static>
	Vec<T, Static> operator/(const T& s, const Vec<T, Static>& v);
	/*template<typename T, typename V>
	Vec<T, Static> operator/(const Vec<T, Static>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T, Static> operator/(const V& v1, const Vec<T, Static>& v2);*/


















	template<typename T, bool Static>
	inline Vec<T, Static>::Vec() :
	{}

	template<typename T, bool Static>
	inline Vec<T, Static>::Vec(const Size size) :
		BasicVector<T, Static>(size)
	{}

	template<typename T, bool Static>
	inline Vec<T, Static>::Vec(BasicVector<T, Static>&& v) :
		BasicVector<T, Static>(Utility::toRValue(v))
	{
	}

	template<typename T, bool Static>
	inline Vec<T, Static>::~Vec() {

	}

	template<typename T, bool Static>
	inline void Vec<T, Static>::zeros() {
		fill(T(0));
	}

	template<typename T, bool Static>
	inline void Vec<T, Static>::ones() {
		fill(T(1));
	}

	template<typename T, bool Static>
	inline void Vec<T, Static>::randomF() {
		for ( Size i(0); i < this->size; i++ ) {
			this->dataTable[ i ] = Math::randomF();
		}
	}

	template<typename T, bool Static>
	inline Vec<T, Static>::Vec(const Size size, T* dataTable) :
		BasicVector<T, Static>(size, dataTable)
	{}

	template<typename T, bool Static>
	template<typename S>
	inline S Vec<T, Static>::toString() const {
		S outputStr;

		outputStr << S::ElemType('[');
		outputStr << S::ElemType(' ');

		for ( Size i(0); i < this->size; i++ ) {
			if ( i > Size(0) ) {
				outputStr << S::ElemType(',');
				outputStr << S::ElemType(' ');
			}
			outputStr << this->dataTable[ i ];
		}

		outputStr << S::ElemType(' ');
		outputStr << S::ElemType(']');

		return outputStr;
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator=(BasicVector<T, Static>&& v) {
		BasicVector<T, Static>::operator=(Utility::toRValue(v));

		return *this;
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator+=(const T& s) {
		return apply(Math::Operations::AddEqual(), s);
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator-=(const T& s) {
		return apply(Math::Operations::SubEqual(), s);
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator*=(const T& s) {
		return apply(Math::Operations::MulEqual(), s);
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator/=(const T& s) {
		return apply(Math::Operations::DivEqual(), s);
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator%=(const T& s) {
		return apply(Math::Operations::ModulusEqual(), s);
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator++() {
		return apply(Math::Operations::Increment());
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator--() {
		return apply(Math::Operations::Decrement());
	}

	template<typename T, bool Static>
	inline Vec<T, Static> Vec<T, Static>::operator-() {
		return ::Math::apply(Math::Operations::MinusUnary(), *this);
	}

	template<typename T, bool Static>
	template<typename Functor, typename C>
	inline Vec<T, Static>& Vec<T, Static>::apply(Functor& functor, const Table<C>& v) {
		BasicVector<T, Static>::apply(functor, v);

		return *this;
	}

	template<typename T, bool Static>
	template<typename Functor>
	inline Vec<T, Static>& Vec<T, Static>::apply(Functor& functor, const T& s) {
		BasicVector<T, Static>::apply(functor, s);

		return *this;
	}

	template<typename T, bool Static>
	template<typename Functor>
	inline Vec<T, Static>& Vec<T, Static>::apply(Functor& functor) {
		BasicVector<T, Static>::apply(functor);

		return *this;
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>& Vec<T, Static>::operator+=(const Table<C>& v) {
		return apply(Math::Operations::AddEqual(), v);
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>& Vec<T, Static>::operator-=(const Table<C>& v) {
		return apply(Math::Operations::SubEqual(), v);
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>& Vec<T, Static>::operator*=(const Table<C>& v) {
		return apply(Math::Operations::MulEqual(), v);
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>& Vec<T, Static>::operator/=(const Table<C>& v) {
		return apply(Math::Operations::DivEqual(), v);
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>& Vec<T, Static>::operator%=(const Table<C>& v) {
		return apply(Math::Operations::ModulusEqual(), v);
	}

	//template<typename T, bool Static>
	//template<typename V>
	//inline Vec<T, Static>::Vec(const V& v) :
	//	BasicVector<T, Static>(v.getSize())
	//{
	//	for ( Size i(0); i < this->size; i++ ) {
	//		this->dataTable[ i ] = v[ i ];
	//	}
	//}

	template<typename T, bool Static>
	template<typename C, Size N>
	inline Vec<T, Static>::Vec(const C(&v)[ N ]) :
		BasicVector<T, Static>(v)
	{
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>::Vec(const Table<C>& v) :
		BasicVector<T, Static>(v)
	{
	}

	template<typename T, bool Static>
	inline Vec<T, Static>::Vec(const Vec<T, Static>& v) :
		BasicVector<T, Static>(v)
	{}

	template<typename T, bool Static>
	template<typename C, Size N>
	inline Vec<T, Static>& Vec<T, Static>::operator=(const C(&v)[ N ]) {
		BasicVector<T, Static>::operator=(v);

		return *this;
	}

	template<typename T, bool Static>
	template<typename C>
	inline Vec<T, Static>& Vec<T, Static>::operator=(const Table<C>& v) {
		BasicVector<T, Static>::operator=(v);

		return *this;
	}

	template<typename T, bool Static>
	inline Vec<T, Static>& Vec<T, Static>::operator=(const Vec<T, Static>& v) {
		BasicVector<T, Static>::operator=(v);

		return *this;
	}

	/*template<typename T, bool Static>
	template<typename V>
	inline Vec<T, Static>& Vec<T, Static>::operator=(const V& v) {
		resizeNoCopy(v.getSize());
		Utility::copy(this->dataTable, v.getData(), this->size);

		return *this;
	}*/

	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const Vec<T>& v1, const Vec<T>& v2) {
		_assert(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(v1[ i ], v2[ i ]);
		}
		return r;
	}

	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const Vec<T>& v, const T& s) {
		Vec<T> r(v.getSize());
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(v[ i ], s);
		}
		return r;
	}

	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const T& s, const Vec<T>& v) {
		Vec<T> r(v.getSize());
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(s, v[ i ]);
		}
		return r;
	}

	template<typename T, typename Functor, typename C>
	Vec<T> apply(Functor& functor, const Vec<T>& v1, const BasicVector<C>& v2) {
		_assert(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(v1[ i ], v2[ i ]);
		}
		return r;
	}

	template<typename T, typename Functor, typename C>
	Vec<T> apply(Functor& functor, const BasicVector<C>& v1, const Vec<T>& v2) {
		_assert(v1.getSize() == v2.getSize());
		Vec<T, Static> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(v1[ i ], v2[ i ]);
		}
		return r;
	}

	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const Vec<T>& v) {
		Vec<T> r(v.getSize());
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(v[ i ]);
		}
		return r;
	}

	template<typename T, bool Static>
	Vec<T, Static> operator+(const Vec<T, Static>& v1, const Vec<T, Static>& v2) {
		return apply(Math::Operations::Add(), v1, v2);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator+(const Vec<T, Static>& v, const T& s) {
		return apply(Math::Operations::Add(), v, s);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator+(const T& s, const Vec<T, Static>& v) {
		return apply(Math::Operations::Add(), s, v);
	}

	/*template<typename T, typename V>
	Vec<T> operator+(const Vec<T>& v1, const V& v2) {
		return apply(Math::Operations::Add(), v1, v2);
	}

	template<typename T, typename V>
	Vec<T> operator+(const V& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Add(), v1, v2);
	}*/

	template<typename T, bool Static>
	Vec<T, Static> operator-(const Vec<T, Static>& v1, const Vec<T, Static>& v2) {
		return apply(Math::Operations::Sub(), v1, v2);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator-(const Vec<T, Static>& v, const T& s) {
		return apply(Math::Operations::Sub(), v, s);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator-(const T& s, const Vec<T, Static>& v) {
		return apply(Math::Operations::Sub(), s, v);
	}

	/*template<typename T, typename V>
	Vec<T> operator-(const Vec<T>& v1, const V& v2) {
		return apply(Math::Operations::Sub(), v1, v2);
	}

	template<typename T, typename V>
	Vec<T> operator-(const V& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Sub(), v1, v2);
	}*/

	template<typename T, bool Static>
	Vec<T, Static> operator*(const Vec<T, Static>& v1, const Vec<T, Static>& v2) {
		return apply(Math::Operations::Mul(), v1, v2);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator*(const Vec<T, Static>& v, const T& s) {
		return apply(Math::Operations::Mul(), v, s);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator*(const T& s, const Vec<T, Static>& v) {
		return apply(Math::Operations::Mul(), s, v);
	}

	/*template<typename T, typename V>
	Vec<T> operator*(const Vec<T>& v1, const V& v2) {
		return apply(Math::Operations::Mul(), v1, v2);
	}

	template<typename T, typename V>
	Vec<T> operator*(const V& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Mul(), v1, v2);
	}*/

	template<typename T, bool Static>
	Vec<T, Static> operator/(const Vec<T, Static>& v1, const Vec<T, Static>& v2) {
		return apply(Math::Operations::Div(), v1, v2);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator/(const Vec<T, Static>& v, const T& s) {
		return apply(Math::Operations::Div(), v, s);
	}

	template<typename T, bool Static>
	Vec<T, Static> operator/(const T& s, const Vec<T, Static>& v) {
		return apply(Math::Operations::Div(), s, v);
	}

	/*template<typename T, typename V>
	Vec<T> operator/(const Vec<T>& v1, const V& v2) {
		return apply(Math::Operations::Div(), v1, v2);
	}

	template<typename T, typename V>
	Vec<T> operator/(const V& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Div(), v1, v2);
	}*/

}

#include "Vec.hpp"