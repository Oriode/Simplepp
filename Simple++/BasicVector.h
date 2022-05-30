#pragma once

#include "Math/Logical.h"
#include "Math/BasicMath.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicIO.h"
#include "IO/SimpleIO.h"
#include "Table.h"

template<typename T>
class BasicVector : public Table<T> {
public:
	template<typename C>
	friend class Vector;

	template<typename C>
	friend class Vec;

	template<typename C>
	friend class BasicString;

	template<typename C>
	friend class UTF8StringT;

	/************************************************************************/
	/* ================             CONSTRUCTOR            ================ */
	/************************************************************************/

	BasicVector();
	BasicVector(const Size size);
	template<typename C, Size N>
	BasicVector(const C(&v)[ N ]);
	template<typename C>
	BasicVector(const C* v, const Size size);
	template<typename C>
	BasicVector(const Table<C>& v);
	BasicVector(const BasicVector<T>& v);
	BasicVector(BasicVector<T> && v);

	~BasicVector();

	/************************************************************************/
	/* ================            COPY OPERATOR           ================ */
	/************************************************************************/

	template<typename C, Size N>
	BasicVector<T>& operator=(const C(&v)[ N ]);
	template<typename C>
	BasicVector<T>& operator=(const Table<C>& v);
	BasicVector<T>& operator=(const BasicVector<T>& v);
	BasicVector<T>& operator=(BasicVector<T>&& v);

	/************************************************************************/
	/* ================                MISC                ================ */
	/************************************************************************/

	void resize(const Size newSize);
	void resizeNoCopy(const Size newSize);

protected:
	BasicVector(BasicVector<T>::ctor);
};

template<typename T>
inline BasicVector<T>::BasicVector() :
	Table<T>(Size(0), NULL)
{}

template<typename T>
inline BasicVector<T>::BasicVector(const Size size) :
	Table<T>(size, ( size ) ? new T[ size ] : NULL)
{}

template<typename T>
inline BasicVector<T>::BasicVector(BasicVector && v) :
	Table<T>(Utility::toRValue(v))
{}

template<typename T>
inline BasicVector<T>::~BasicVector() {
	if ( this->dataTable ) {
		delete[] this->dataTable;
	}
}

template<typename T>
inline BasicVector<T>& BasicVector<T>::operator=(BasicVector<T>&& v) {
	if ( this->dataTable ) {
		delete[] this->dataTable;
	}

	Table<T>::operator=(Utility::toRValue(v));

	return *this;
}

template<typename T>
inline BasicVector<T>::BasicVector(BasicVector<T>::ctor) :
	Table<T>(Table<T>::ctor::null)
{}

template<typename T>
template<typename C, Size N>
inline BasicVector<T>::BasicVector(const C(&v)[ N ]) :
	Table<T>(N, new T[N])
{
	Utility::copy(this->dataTable, v, N);
}

template<typename T>
template<typename C>
inline BasicVector<T>::BasicVector(const C* v, const Size size) :
	Table<T>(size, new T[size])
{
	Utility::copy(this->dataTable, v, this->size);
}

template<typename T>
template<typename C>
inline BasicVector<T>::BasicVector(const Table<C>& v) :
	Table<T>(v.size, new T[v.size])
{
	Utility::copy(this->dataTable, v.dataTable, this->size);
}

template<typename T>
inline BasicVector<T>::BasicVector(const BasicVector<T>& v) :
	Table<T>(v.size, new T[v.size])
{
	Utility::copy(this->dataTable, v.dataTable, this->size);
}

template<typename T>
template<typename C, Size N>
inline BasicVector<T>& BasicVector<T>::operator=(const C(&v)[ N ]) {
	resizeNoCopy(N);
	Utility::copy(this->dataTable, v, this->size);

	return *this;
}

template<typename T>
template<typename C>
inline BasicVector<T>& BasicVector<T>::operator=(const Table<C>& v) {
	resizeNoCopy(v.getSize());
	Utility::copy(this->dataTable, v.getData(), this->size);

	return *this;
}

template<typename T>
inline BasicVector<T>& BasicVector<T>::operator=(const BasicVector<T>& v) {
	resizeNoCopy(v.getSize());
	Utility::copy(this->dataTable, v.getData(), this->size);

	return *this;
}

template<typename T>
inline void BasicVector<T>::resize(const Size newSize) {
	if ( newSize == this->size ) {
		return;
	}
	if ( newSize == Size(0) ) {
		delete[] this->dataTable;
		this->dataTable = NULL;
	} else {
		T* newDataTable(new T[ newSize ]);

		if ( this->size > Size(0) ) {
			Utility::copy(newDataTable, this->dataTable, Math::min(this->size, newSize));

			delete[] this->dataTable;
		}

		this->dataTable = newDataTable;
	}

	this->size = newSize;
}

template<typename T>
inline void BasicVector<T>::resizeNoCopy(const Size newSize) {
	if ( newSize == this->size ) {
		return;
	}
	if ( newSize == Size(0) ) {
		delete[] this->dataTable;
		this->dataTable = NULL;
	} else {
		T* newDataTable(new T[ newSize ]);

		if ( this->size > Size(0) ) {
			delete[] this->dataTable;
		}

		this->dataTable = newDataTable;
	}

	this->size = newSize;
}
