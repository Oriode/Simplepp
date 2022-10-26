#pragma once

#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicIO.h"

template<typename T, Size N>
class StaticTable : public IO::BasicIO {
public:

	/** @brief	Defines an alias representing type of the element */
	typedef T ElemType;

	static constexpr Size elementSize = sizeof(T);
	static constexpr Size size = N;

	/************************************************************************/
	/* ================             CONSTRUCTOR            ================ */
	/************************************************************************/

	StaticTable();
	template<typename C>
	StaticTable(const StaticTable<C, N>& t);
	StaticTable(const StaticTable<T, N>& t);
	template<typename C>
	StaticTable(const C(&t)[ N ]);

	/************************************************************************/
	/* ================            COPY OPERATOR           ================ */
	/************************************************************************/

	template<typename C>
	StaticTable<T, N>& operator=(const StaticTable<C, N>& t);
	StaticTable<T, N>& operator=(const StaticTable<T, N>& t);
	template<typename C>
	StaticTable<T, N>& operator=(const C(&t)[ N ]);

	/************************************************************************/
	/* ================               ACCESS               ================ */
	/************************************************************************/

	/**
	 * @brief 	Get a value and can assign something else
	 * @param 	index	Index.
	 * @returns	Value founded.
	 */
	const T& operator[](const Size i) const;
	/**
	 * @brief 	Array indexer operator
	 * @param 	index	Zero-based index of the.
	 * @returns	The indexed value.
	 */
	T& operator[](const Size i);

	/**
	 * @brief 	Get the Value associated with an direct access index (of type const Size)
	 * @param 	i	Iterator used to retrieve the value (no bound check is done here)
	 * @returns	Value founded.
	 */
	const T& getValueI(const Size i) const;
	T& getValueI(const Size i);

	/**
	 * @brief 	Set the Value associated with an direct access index (of type Size)
	 * @param 	i   	Iterator used to set the value (no bound check is done here)
	 * @param 	data	The data.
	 */
	void setValueI(const Size i, const T& data);

	constexpr Size getSize() const;

	const T* getData() const;
	T* getData();

	/************************************************************************/
	/* ================                MISC                ================ */
	/************************************************************************/

	/**
	 * @brief 	read from a file stream
	 * @param [in,out]	stream	stream used to read load this object.
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool read(Stream* stream);

	/**
	 * @brief 	write this object as binary into a file stream
	 * @param [in,out]	stream	stream used to write this object.
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool write(Stream* stream) const;

	template<typename S = String>
	S toString() const;

	/************************************************************************/
	/* Static                                                               */
	/************************************************************************/

	static const StaticTable<T, N>* reinterpret(const T* data);
	static StaticTable<T, N>* reinterpret(T* data);

private:
	T dataTable[ N ];
};

template<typename T, Size N>
inline StaticTable<T, N>::StaticTable() {}

template<typename T, Size N>
inline void StaticTable<T, N>::setValueI(const Size i, const T& data) {
#ifdef DEBUG
	if ( i >= getSize() ) {
		_ERROR("StaticTable::setValueI Out of bounds.");
	}
#endif
	this -> dataTable[ i ] = data;
}

template<typename T, Size N>
inline constexpr Size StaticTable<T, N>::getSize() const {
	return N;
}

template<typename T, Size N>
inline const T* StaticTable<T, N>::getData() const {
	return this->dataTable;
}

template<typename T, Size N>
inline T* StaticTable<T, N>::getData() {
	return this->dataTable;
}

template<typename T, Size N>
inline const StaticTable<T, N>* StaticTable<T, N>::reinterpret(const T* data) {
	return reinterpret_cast< const StaticTable<T, N> * >( data );
}

template<typename T, Size N>
inline StaticTable<T, N> * StaticTable<T, N>::reinterpret(T* data) {
	return reinterpret_cast< StaticTable<T, N> * >( data );
}

template<typename T, Size N>
template<typename C>
inline StaticTable<T, N>::StaticTable(const StaticTable<C, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);
}

template<typename T, Size N>
template<typename C>
inline StaticTable<T, N>::StaticTable(const C(&t)[ N ]) {
	Utility::copy(this->dataTable, t, N);
}

template<typename T, Size N>
template<typename C>
inline StaticTable<T, N>& StaticTable<T, N>::operator=(const StaticTable<C, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);

	return *this;
}

template<typename T, Size N>
template<typename C>
inline StaticTable<T, N>& StaticTable<T, N>::operator=(const C(&t)[ N ]) {
	Utility::copy(this->dataTable, t, N);

	return *this;
}

template<typename T, Size N>
template<typename Stream>
inline bool StaticTable<T, N>::read(Stream* stream) {
	Size readSize;
	if ( !IO::read(stream, &readSize) ) {
		return false;
	}

	if ( readSize != this->size ) {
		SimpleLog::callErrorHandler(TEXT("Trying to load a StaticTable of the wrong size."), SimpleLog::MessageSeverity::Warning, SimpleLog::MessageColor::Red);
	}

	Size minSize(Math::min(readSize, getSize()));
	if ( !IO::read(stream, getData(), getSize()) ) {
		return false;
	}

	return true;
}

template<typename T, Size N>
template<typename Stream>
inline bool StaticTable<T, N>::write(Stream* stream) const {
	const Size size(N);
	if ( !IO::write(stream, &size) ) {
		return false;
	}

	if ( !IO::write(stream, getData(), getSize()) ) {
		return false;
	}

	return true;
}

template<typename T, Size N>
template<typename S>
inline S StaticTable<T, N>::toString() const {
	S outputStr;

	outputStr << S::ElemType('[');
	outputStr << S::ElemType(' ');

	for ( Size i(0); i < getSize(); i++ ) {
		if ( i > Size(0) ) {
			outputStr << S::ElemType(',');
			outputStr << S::ElemType(' ');
		}
		outputStr << getValueI(i);
	}

	outputStr << S::ElemType(' ');
	outputStr << S::ElemType(']');

	return outputStr;
}

template<typename T, Size N>
inline StaticTable<T, N>& StaticTable<T, N>::operator=(const StaticTable<T, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);

	return *this;
}

template<typename T, Size N>
inline const T& StaticTable<T, N>::operator[](const Size i) const {
	return getValueI(i);
}

template<typename T, Size N>
inline T& StaticTable<T, N>::operator[](const Size i) {
	return getValueI(i);
}

template<typename T, Size N>
inline const T& StaticTable<T, N>::getValueI(const Size i) const {
	return const_cast< StaticTable<T, N> * >( this )->getValueI(i);
}

template<typename T, Size N>
inline T& StaticTable<T, N>::getValueI(const Size i) {
#ifdef DEBUG
	if ( i >= getSize() ) {
		_ERROR("StaticTable::getValueI Out of bounds.");
	}
#endif
	return this -> dataTable[ i ];
}

template<typename T, Size N>
inline StaticTable<T, N>::StaticTable(const StaticTable<T, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);
}
