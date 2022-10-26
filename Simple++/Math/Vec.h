#pragma once

#include "../Log.h"
#include "../Utility.h"
#include "../String.h"
#include "../JSON/Node.h"

#include "BasicMath.h"
#include "../BasicVector.h"

namespace Math {

	template<typename T>
	class Vec : public BasicVector<T>, public JSON::Jsonable {
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
		Vec(const Vec<T>& v);
		template<typename C>
		Vec(const C* dataTable, const Size size);
		Vec(BasicVector<T>&& v);

		~Vec();

		/************************************************************************/
		/* ================            COPY OPERATOR           ================ */
		/************************************************************************/

		template<typename C, Size N>
		Vec<T>& operator=(const C(&v)[ N ]);
		template<typename C>
		Vec<T>& operator=(const Table<C>& v);
		Vec<T>& operator=(const Vec<T>& v);
		//template<typename V>
		//Vec<T>& operator=(const V& v);
		Vec<T>& operator=(BasicVector<T>&& v);

		/************************************************************************/
		/* ================             ARITHMETIC             ================ */
		/************************************************************************/

		template<typename Functor, typename C>
		Vec<T>& apply(Functor & functor, const Table<C>& v);
		template<typename Functor>
		Vec<T>& apply(Functor& functor, const T& s);
		template<typename Functor>
		Vec<T>& apply(Functor& functor);

		template<typename Functor, typename C>
		Vec<T>& set(Functor& functor, const Table<C>& v);
		template<typename Functor>
		Vec<T>& set(Functor& functor, const T& s);
		template<typename Functor>
		Vec<T>& set(Functor& functor);

		template<typename C>
		Vec<T> & operator+=(const Table<C>& v);
		Vec<T>& operator+=(const T& s);

		template<typename C>
		Vec<T>& operator-=(const Table<C>& v);
		Vec<T>& operator-=(const T& s);

		template<typename C>
		Vec<T>& operator*=(const Table<C>& v);
		Vec<T>& operator*=(const T& s);

		template<typename C>
		Vec<T>& operator/=(const Table<C>& v);
		Vec<T>& operator/=(const T& s);

		template<typename C>
		Vec<T>& operator%=(const Table<C>& v);
		Vec<T>& operator%=(const T& s);

		Vec<T>& operator++();
		Vec<T>& operator--();
		Vec<T> operator-();

		/************************************************************************/
		/* ================              LOGICAL               ================ */
		/************************************************************************/

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		/**
		 * @brief 	Fill the complete vector with the specified data.
		 * @param 	data	data to be copied in the whole vector.
		 */
		Vec<T>& fill(const T& data);

		Vec<T>& zeros();
		Vec<T>& ones();
		Vec<T>& randomF();
		Vec<T>& random(const T & min, const T & max);

		///@brief Read a JSON object and set this to the read values.
		///@param nodeArray Pointer to the JSON object to be read.
		///@return true if success, false otherwise.
		template<typename C = UTF8String>
		bool fromJSON(const JSON::BasicNodeT<C> * node);

		///@brief Write this object to a Json object
		///@param o Json node to write to.
		template<typename C = UTF8String>
		JSON::NodeArrayT<C> * toJSON() const;

	protected:
	};

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

	template<typename T>
	Vec<T> operator+(const Vec<T>& v1, const Vec<T> & v2);
	template<typename T>
	Vec<T> operator+(const Vec<T>& v, const T& s);
	template<typename T>
	Vec<T> operator+(const T& s, const Vec<T>& v);
	/*template<typename T, typename V>
	Vec<T> operator+(const Vec<T>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T> operator+(const V& v1, const Vec<T>& v2);*/

	template<typename T>
	Vec<T> operator-(const Vec<T>& v1, const Vec<T>& v2);
	template<typename T>
	Vec<T> operator-(const Vec<T>& v, const T& s);
	template<typename T>
	Vec<T> operator-(const T& s, const Vec<T>& v);
	/*template<typename T, typename V>
	Vec<T> operator-(const Vec<T>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T> operator-(const V& v1, const Vec<T>& v2);*/

	template<typename T>
	Vec<T> operator*(const Vec<T>& v1, const Vec<T>& v2);
	template<typename T>
	Vec<T> operator*(const Vec<T>& v, const T& s);
	template<typename T>
	Vec<T> operator*(const T& s, const Vec<T>& v);
	/*template<typename T, typename V>
	Vec<T> operator*(const Vec<T>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T> operator*(const V& v1, const Vec<T>& v2);*/

	template<typename T>
	Vec<T> operator/(const Vec<T>& v1, const Vec<T>& v2);
	template<typename T>
	Vec<T> operator/(const Vec<T>& v, const T& s);
	template<typename T>
	Vec<T> operator/(const T& s, const Vec<T>& v);
	/*template<typename T, typename V>
	Vec<T> operator/(const Vec<T>& v1, const V& v2);
	template<typename T, typename V>
	Vec<T> operator/(const V& v1, const Vec<T>& v2);*/


















	template<typename T>
	inline Vec<T>::Vec() {}

	template<typename T>
	inline Vec<T>::Vec(const Size size) :
		BasicVector<T>(size)
	{}

	template<typename T>
	inline Vec<T>::Vec(BasicVector<T>&& v) :
		BasicVector<T>(Utility::toRValue(v))
	{
	}

	template<typename T>
	inline Vec<T>::~Vec() {

	}

	template<typename T>
	inline Vec<T>& Vec<T>::fill(const T& data) {
		BasicVector<T>::fill(data);
		return *this;
	}

	template<typename T>
	inline Vec<T>& Vec<T>::zeros() {
		return fill(T(0));
	}

	template<typename T>
	inline Vec<T>& Vec<T>::ones() {
		return fill(T(1));
	}

	template<typename T>
	inline Vec<T>& Vec<T>::randomF() {
		return set(Math::RandomF());
	}

	template<typename T>
	inline Vec<T>& Vec<T>::random(const T& min, const T& max) {
		return set(Math::Random<T>(min, max));
	}

	template<typename T>
	template<typename C>
	inline bool Vec<T>::fromJSON(const JSON::BasicNodeT<C>* node) {
		return JSON::fromJSON<C>(node, reinterpret_cast< BasicVector<T> * >( this ));
	}

	template<typename T>
	template<typename C>
	inline JSON::NodeArrayT<C>* Vec<T>::toJSON() const {
		return JSON::toJSON<C>(*reinterpret_cast< const Table<T> * >( this ));
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator=(BasicVector<T>&& v) {
		BasicVector<T>::operator=(Utility::toRValue(v));

		return *this;
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator+=(const T& s) {
		return apply(Math::Operations::AddEqual(), s);
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator-=(const T& s) {
		return apply(Math::Operations::SubEqual(), s);
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator*=(const T& s) {
		return apply(Math::Operations::MulEqual(), s);
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator/=(const T& s) {
		return apply(Math::Operations::DivEqual(), s);
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator%=(const T& s) {
		return apply(Math::Operations::ModulusEqual(), s);
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator++() {
		return apply(Math::Operations::Increment());
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator--() {
		return apply(Math::Operations::Decrement());
	}

	template<typename T>
	inline Vec<T> Vec<T>::operator-() {
		return ::Math::apply(Math::Operations::MinusUnary(), *this);
	}

	template<typename T>
	template<typename Functor, typename C>
	inline Vec<T>& Vec<T>::apply(Functor& functor, const Table<C>& v) {
		BasicVector<T>::apply(functor, v);

		return *this;
	}

	template<typename T>
	template<typename Functor>
	inline Vec<T>& Vec<T>::apply(Functor& functor, const T& s) {
		BasicVector<T>::apply(functor, s);

		return *this;
	}

	template<typename T>
	template<typename Functor>
	inline Vec<T>& Vec<T>::apply(Functor& functor) {
		BasicVector<T>::apply(functor);

		return *this;
	}

	template<typename T>
	template<typename Functor, typename C>
	inline Vec<T>& Vec<T>::set(Functor& functor, const Table<C>& v) {
		BasicVector<T>::set(functor, v);
		return *this;
	}

	template<typename T>
	template<typename Functor>
	inline Vec<T>& Vec<T>::set(Functor& functor, const T& s) {
		BasicVector<T>::set(functor, s);
		return *this;
	}

	template<typename T>
	template<typename Functor>
	inline Vec<T>& Vec<T>::set(Functor& functor) {
		BasicVector<T>::set(functor);
		return *this;
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator+=(const Table<C>& v) {
		return apply(Math::Operations::AddEqual(), v);
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator-=(const Table<C>& v) {
		return apply(Math::Operations::SubEqual(), v);
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator*=(const Table<C>& v) {
		return apply(Math::Operations::MulEqual(), v);
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator/=(const Table<C>& v) {
		return apply(Math::Operations::DivEqual(), v);
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator%=(const Table<C>& v) {
		return apply(Math::Operations::ModulusEqual(), v);
	}

	//template<typename T>
	//template<typename V>
	//inline Vec<T>::Vec(const V& v) :
	//	BasicVector<T>(v.getSize())
	//{
	//	for ( Size i(0); i < this->size; i++ ) {
	//		this->dataTable[ i ] = v[ i ];
	//	}
	//}

	template<typename T>
	template<typename C, Size N>
	inline Vec<T>::Vec(const C(&v)[ N ]) :
		BasicVector<T>(v)
	{
	}

	template<typename T>
	template<typename C>
	inline Vec<T>::Vec(const Table<C>& v) :
		BasicVector<T>(v)
	{
	}

	template<typename T>
	template<typename C>
	inline Vec<T>::Vec(const C* dataTable, const Size size) :
		BasicVector<T>(dataTable, size)
	{}

	template<typename T>
	inline Vec<T>::Vec(const Vec<T>& v) :
		BasicVector<T>(v)
	{}

	template<typename T>
	template<typename C, Size N>
	inline Vec<T>& Vec<T>::operator=(const C(&v)[ N ]) {
		BasicVector<T>::operator=(v);

		return *this;
	}

	template<typename T>
	template<typename C>
	inline Vec<T>& Vec<T>::operator=(const Table<C>& v) {
		BasicVector<T>::operator=(v);

		return *this;
	}

	template<typename T>
	inline Vec<T>& Vec<T>::operator=(const Vec<T>& v) {
		BasicVector<T>::operator=(v);

		return *this;
	}

	/*template<typename T>
	template<typename V>
	inline Vec<T>& Vec<T>::operator=(const V& v) {
		resizeNoCopy(v.getSize());
		Utility::copy(this->dataTable, v.getData(), this->size);

		return *this;
	}*/

	template<typename T, typename Functor>
	Vec<T> apply(Functor& functor, const Vec<T>& v1, const Vec<T>& v2) {
		_ASSERT(v1.getSize() == v2.getSize());
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
	Vec<T> apply(Functor& functor, const Vec<T>& v1, const Table<C>& v2) {
		_ASSERT(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
		for ( Size i(0); i < r.getSize(); i++ ) {
			r[ i ] = functor(v1[ i ], v2[ i ]);
		}
		return r;
	}

	template<typename T, typename Functor, typename C>
	Vec<T> apply(Functor& functor, const Table<C>& v1, const Vec<T>& v2) {
		_ASSERT(v1.getSize() == v2.getSize());
		Vec<T> r(Math::min(v1.getSize(), v2.getSize()));
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

	template<typename T>
	Vec<T> operator+(const Vec<T>& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Add(), v1, v2);
	}

	template<typename T>
	Vec<T> operator+(const Vec<T>& v, const T& s) {
		return apply(Math::Operations::Add(), v, s);
	}

	template<typename T>
	Vec<T> operator+(const T& s, const Vec<T>& v) {
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

	template<typename T>
	Vec<T> operator-(const Vec<T>& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Sub(), v1, v2);
	}

	template<typename T>
	Vec<T> operator-(const Vec<T>& v, const T& s) {
		return apply(Math::Operations::Sub(), v, s);
	}

	template<typename T>
	Vec<T> operator-(const T& s, const Vec<T>& v) {
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

	template<typename T>
	Vec<T> operator*(const Vec<T>& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Mul(), v1, v2);
	}

	template<typename T>
	Vec<T> operator*(const Vec<T>& v, const T& s) {
		return apply(Math::Operations::Mul(), v, s);
	}

	template<typename T>
	Vec<T> operator*(const T& s, const Vec<T>& v) {
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

	template<typename T>
	Vec<T> operator/(const Vec<T>& v1, const Vec<T>& v2) {
		return apply(Math::Operations::Div(), v1, v2);
	}

	template<typename T>
	Vec<T> operator/(const Vec<T>& v, const T& s) {
		return apply(Math::Operations::Div(), v, s);
	}

	template<typename T>
	Vec<T> operator/(const T& s, const Vec<T>& v) {
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