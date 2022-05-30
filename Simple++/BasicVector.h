#pragma once

#include "Math/Logical.h"
#include "Math/BasicMath.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicIO.h"
#include "IO/SimpleIO.h"
#include "Table.h"

template<typename T, bool Static = false>
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

	template<typename C>
	friend class Table;

	template<typename C>
	friend class TensorView;

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
	BasicVector(const BasicVector<T, Static>& v);
	BasicVector(BasicVector<T, Static> && v);

	~BasicVector();

	/************************************************************************/
	/* ================            COPY OPERATOR           ================ */
	/************************************************************************/

	template<typename C, Size N>
	BasicVector<T, Static>& operator=(const C(&v)[ N ]);
	template<typename C>
	BasicVector<T, Static>& operator=(const Table<C>& v);
	BasicVector<T, Static>& operator=(const BasicVector<T, Static>& v);
	BasicVector<T, Static>& operator=(BasicVector<T, Static>&& v);

	/************************************************************************/
	/* ================                MISC                ================ */
	/************************************************************************/

	void resize(const Size newSize);
	void resizeNoCopy(const Size newSize);

	/**
	 * @brief 	read from a file stream
	 * @param [in,out]	stream	stream used to read load this object.
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool read(Stream* stream);

	BasicVector(const Size size, T* dataTable);

protected:
	BasicVector(BasicVector<T, Static>::protectedCtor);
};

template<typename T, bool Static>
inline BasicVector<T, Static>::BasicVector() :
	Table<T>(Size(0), NULL)
{}

template<typename T, bool Static>
inline BasicVector<T, Static>::BasicVector(const Size size) :
	Table<T>(size, ( size ) ? new T[ size ] : NULL)
{}

template<typename T, bool Static>
inline BasicVector<T, Static>::BasicVector(BasicVector<T, Static> && v) :
	Table<T>(Utility::toRValue(v))
{}

template<typename T, bool Static>
inline BasicVector<T, Static>::~BasicVector() {
	if ( Static == false && this->dataTable ) {
		delete[] this->dataTable;
	}
}

template<typename T, bool Static>
inline BasicVector<T, Static>& BasicVector<T, Static>::operator=(BasicVector<T, Static>&& v) {
	if ( this->dataTable ) {
		delete[] this->dataTable;
	}

	Table<T>::operator=(Utility::toRValue(v));

	return *this;
}

template<typename T, bool Static>
inline BasicVector<T, Static>::BasicVector(BasicVector<T, Static>::protectedCtor) :
	Table<T>(Table<T>::protectedCtor::null)
{}

template<typename T, bool Static>
inline BasicVector<T, Static>::BasicVector(const Size size, T * dataTable) :
	Table<T>(size, dataTable)
{}

template<typename T, bool Static>
template<typename C, Size N>
inline BasicVector<T, Static>::BasicVector(const C(&v)[ N ]) :
	Table<T>(N, new T[N])
{
	Utility::copy(this->dataTable, v, N);
}

template<typename T, bool Static>
template<typename C>
inline BasicVector<T, Static>::BasicVector(const C* v, const Size size) :
	Table<T>(size, new T[size])
{
	Utility::copy(this->dataTable, v, this->size);
}

template<typename T, bool Static>
template<typename C>
inline BasicVector<T, Static>::BasicVector(const Table<C>& v) :
	Table<T>(v.getSize(), new T[v.getSize()])
{
	Utility::copy(this->dataTable, v.getData(), this->size);
}

template<typename T, bool Static>
inline BasicVector<T, Static>::BasicVector(const BasicVector<T, Static>& v) :
	Table<T>(v.size, new T[v.size])
{
	Utility::copy(this->dataTable, v.dataTable, this->size);
}

template<typename T, bool Static>
template<typename C, Size N>
inline BasicVector<T, Static>& BasicVector<T, Static>::operator=(const C(&v)[ N ]) {
	resizeNoCopy(N);
	Utility::copy(this->dataTable, v, this->size);

	return *this;
}

template<typename T, bool Static>
template<typename C>
inline BasicVector<T, Static>& BasicVector<T, Static>::operator=(const Table<C>& v) {
	resizeNoCopy(v.getSize());
	Utility::copy(this->dataTable, v.getData(), this->size);

	return *this;
}

template<typename T, bool Static>
template<typename Stream>
inline bool BasicVector<T, Static>::read(Stream* stream) {
	Size readSize;
	if ( !IO::read(stream, &readSize) ) {
		return false;
	}

	resizeNoCopy(readSize);

	for ( Size i(0); i < this->size; i++ ) {
		if ( !IO::read(stream, &( this -> dataTable[ i ] )) ) {
			return false;
		}
	}

	return true;
}

template<typename T, bool Static>
inline BasicVector<T, Static>& BasicVector<T, Static>::operator=(const BasicVector<T, Static>& v) {
	resizeNoCopy(v.getSize());
	Utility::copy(this->dataTable, v.getData(), this->size);

	return *this;
}

template<typename T, bool Static>
inline void BasicVector<T, Static>::resize(const Size newSize) {
	if ( newSize == this->size ) {
		return;
	}

	static_assert( Static == false, "Unable to resize a static BasicVector." );

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

template<typename T, bool Static>
inline void BasicVector<T, Static>::resizeNoCopy(const Size newSize) {
	if ( newSize == this->size ) {
		return;
	}

	static_assert( Static == false, "Unable to resize a static BasicVector." );

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
