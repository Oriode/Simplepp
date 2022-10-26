#pragma once

#include "Math/Logical.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicIO.h"

template<typename T>
class Table : public IO::BasicIO {
public:
	template<typename C>
	friend class Vector;

	template<typename C>
	friend class Vec;

	template<typename C>
	friend class BasicString;

	template<typename C>
	friend class UTF8StringT;

	/** @brief	Defines an alias representing type of the element */
	typedef T ElemType;

	static constexpr Size elementSize = sizeof(T);

	/************************************************************************/
	/* ================             CONSTRUCTOR            ================ */
	/************************************************************************/

	Table();
	Table(const Size size, T* dataTable);
	template<typename C>
	Table(const Table<C>& v);
	Table(const Table<T>& v);
	Table(Table<T>&& v);

	/************************************************************************/
	/* ================            COPY OPERATOR           ================ */
	/************************************************************************/

	template<typename C>
	Table<T>& operator=(const Table<C>& v);
	Table<T>& operator=(const Table<T>& v);
	Table<T>& operator=(Table<T>&& v);

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

	const T& getValueF(float f) const;
	T& getValueF(float f);

	/**
	 * @brief 	Set the Value associated with an direct access index (of type Size)
	 * @param 	i   	Iterator used to set the value (no bound check is done here)
	 * @param 	data	The data.
	 */
	void setValueI(const Size i, const T& data);

	void setValueF(float f, const T& data);

	/**
	 * @brief 	get the last element of this vector
	 * @returns	Last element in the vector.
	 */
	const T& getLast() const;
	/**
	 * @brief 	Gets the last
	 * @returns	The last.
	 */
	T& getLast();

	/**
	 * @brief 	get the first element of this vector
	 * @returns	First element in the vector.
	 */
	const T& getFirst() const;
	/**
	 * @brief 	Gets the first
	 * @returns	The first.
	 */
	T& getFirst();

	Size getIndex(float f) const;

	/************************************************************************/
	/* ================              LOGICAL               ================ */
	/************************************************************************/

	template<typename Compare>
	MATH_FUNC_QUALIFIER bool AND(Compare& func, const Table<T>& v) const;
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool AND(Compare& func, const T& s) const;

	template<typename Compare>
	MATH_FUNC_QUALIFIER bool OR(Compare& func, const Table<T>& v) const;
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool OR(Compare& func, const T& s)const;

	/**
	 * @brief 	Equality operator
	 * @param 	v	A Vector<T> to process.
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==(const Table<T>& v) const;
	/**
	 * @brief 	Inequality operator
	 * @param 	v	A Vector<T> to process.
	 * @returns	True if the parameters are not considered equivalent.
	 */
	bool operator!=(const Table<T>& v) const;
	/**
	 * @brief 	Less-than comparison operator
	 * @param 	v	A Vector<T> to process.
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<(const Table<T>& v) const;
	/**
	 * @brief 	Greater-than comparison operator
	 * @param 	v	A Vector<T> to process.
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>(const Table<T>& v) const;
	/**
	 * @brief 	Less-than-or-equal comparison operator
	 * @param 	v	A Vector<T> to process.
	 * @returns	True if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const Table<T>& v) const;
	/**
	 * @brief 	Greater-than-or-equal comparison operator
	 * @param 	v	A Vector<T> to process.
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const Table<T>& v) const;

	/************************************************************************/
	/* ================                MISC                ================ */
	/************************************************************************/

	template<typename Functor, typename C>
	Table<T>& apply(Functor& functor, const Table<C>& v);
	template<typename Functor>
	Table<T>& apply(Functor& functor, const T& s);
	template<typename Functor>
	Table<T>& apply(Functor& functor);

	template<typename Functor, typename C>
	Table<T>& set(Functor& functor, const Table<C>& v);
	template<typename Functor>
	Table<T>& set(Functor& functor, const T& s);
	template<typename Functor>
	Table<T>& set(Functor& functor);

	/**
	 * @brief 	Fill the complete vector with the specified data.
	 * @param 	data	data to be copied in the whole vector.
	 */
	Table<T> & fill(const T& data);

	/**
	 * @brief 	Get the size of this vector
	 * @returns	Number of datas of this vector.
	 */
	const Size getSize() const;

	/**
	 * @brief 	Get the size of this vector in bytes
	 * @returns	const Size of this vector in bytes.
	 */
	const Size getSizeBytes() const;

	/**
	 * @brief 	Gets the data
	 * @returns	Null if it fails, else the data.
	 */
	const T* getData() const;
	/**
	 * @brief 	Gets the data
	 * @returns	Null if it fails, else the data.
	 */
	T* getData();

	/**
	 * @brief 	Test if a value exists in this vector
	 * @param 	value	The value.
	 * @returns	True if the value has been founded and false instead.
	 */
	bool exists(const T& value) const;

	/**
	 * @brief 	Replace the first occurrence of the data
	 * @param 	searchI	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceFirst(const T& search, const T& data);

	/**
	 * @brief 	Replace ALL occurrences of the data searched
	 * @param 	searchI	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceAll(const T& search, const T& data);

	/** @brief	Quicksort the vector using the operator>() */
	void sortDesc();

	/** @brief	Quicksort the vector using the operator<() */
	void sortAsc();

	/**
	 * @brief 	sort the elements of this vector using the quicksort algorithm
	 * @tparam	Func	Type of the function.
	 * @param [in,out]	functor	(Optional) Functor with operator () overloaded with : bool operator()(const T &, const T &) const;
	 */
	template<typename Func = Math::Logical::Less>
	void sort(Func& functor = Func());

	/**
	 * @brief	Get the min value of this Vector using the specified functor to compare the items.
	 * @tparam	Func	Type of the Functor used to compare items.
	 * @param [in,out]	functor Functor used to compare items.
	 * @return	Iterator to the founded item, NULL if none.
	 */
	template<typename Func = Math::Logical::Less>
	const Size getMinI(Func& functor = Func()) const;

	/**
	 * @brief	Get the max value of this Vector using the specified functor to compare the items.
	 * @tparam	Func	Type of the Functor used to compare items.
	 * @param [in,out]	functor Functor used to compare items.
	 * @return	Iterator to the founded item, NULL if none.
	 */
	template<typename Func = Math::Logical::Less>
	const Size getMaxI(Func& functor = Func()) const;

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

	/**
	 * @brief 	Search a data and retrieve the index
	 * @param 	data	Data to be searched.
	 * @returns	Index where the data has bee founded if founded. return Vector<T>::overflow instead.
	 */
	const Size searchI(const T& data) const;

	template<typename S = String>
	S toString() const;

	/************************************************************************/
	/* Static                                                               */
	/************************************************************************/

	/**
	 * @brief 	Gets the overflow
	 * @returns	The overflow.
	 */
	static const Size overflow;

protected:
	/** @brief	Values that represent Constructors */
	enum class protectedCtor {
		null
	};

	Table(typename Table<T>::protectedCtor);

	/**
	 * @brief 	Quicksorts
	 * @tparam	Compare	Type of the compare.
	 * @param 	start	The start.
	 * @param 	end  	The end.
	 * @param 	func 	(Optional) The function.
	 */
	template<typename Compare>
	void quicksort(T* startIt, T* endIt, Compare func = Math::Logical::Less);

	/**
	 * @brief 	Swaps
	 * @param 	i1	The first index.
	 * @param 	i2	The second index.
	 */
	void swap(const Size i1, const Size i2);

	/** Size of the Vector */
	Size size;

	/** @brief	The data table */
	T* dataTable;
};

template<typename T>
const Size Table<T>::overflow = Size(-1);

template<typename T>
Table<T>::Table() :
	size(Size(0)),
	dataTable(NULL)
{}

template<typename T>
Table<T>::Table(const Size size, T * dataTable) :
	size(size),
	dataTable(dataTable)
{}

template<typename T>
Table<T>::Table(Table<T> && v) :
	size(Utility::toRValue(v.size)),
	dataTable(Utility::toRValue(v.dataTable))
{
	v.dataTable = NULL;
}

template<typename T>
Table<T>& Table<T>::operator=(Table<T>&& v) {
	this->size = Utility::toRValue(v.size);
	this->dataTable = Utility::toRValue(v.dataTable);

	v.dataTable = NULL;

	return *this;
}

template<typename T>
Table<T>::Table(typename Table<T>::protectedCtor) {}

template<typename T>
const T& Table<T>::operator[](const Size i) const {
	return getValueI(i);
}

template<typename T>
T& Table<T>::operator[](const Size i) {
	return getValueI(i);
}

template<typename T>
const T& Table<T>::getLast() const {
	return this->dataTable[ this->size - Size(1) ];
}

template<typename T>
T& Table<T>::getLast() {
	return this->dataTable[ this->size - Size(1) ];
}

template<typename T>
const T& Table<T>::getFirst() const {
	return *this->dataTable;
}

template<typename T>
T& Table<T>::getFirst() {
	return *this->dataTable;
}

template<typename T>
Size Table<T>::getIndex(float f) const {
	float rounding(0.5f / float(this->size));
	f = f + rounding;
	if ( f < 0.0f ) {
		return Size(0);
	} else if ( f > 1.0f ) {
		return this->size - Size(1);
	} else {
		Size i(static_cast< Size >( f * float(this->size - Size(1)) ));
		return i;
	}
}

template<typename T>
void Table<T>::setValueI(const Size i, const T& data) {
#ifdef DEBUG
	if ( i >= this->size ) {
		_ERROR("Table::setValueI Out of bounds.");
	}
#endif
	this -> dataTable[ i ] = data;
}

template<typename T>
void Table<T>::setValueF(float f, const T& data) {
	this->dataTable[ getIndex(f) ] = data;
}

template<typename T>
const T& Table<T>::getValueF(float f) const {
	return const_cast< Table<T> * >( this )->getValueF(f);
}

template<typename T>
T& Table<T>::getValueF(float f) {
	return this->dataTable[ getIndex(f) ];
}

template<typename T>
const T& Table<T>::getValueI(const Size i) const {
	return const_cast< Table<T> * >( this )->getValueI(i);
}

template<typename T>
T& Table<T>::getValueI(const Size i) {
#ifdef DEBUG
	if ( i >= this->size ) {
		_ERROR("Table::getValueI Out of bounds.");
	}
#endif
	return this -> dataTable[ i ];
}

template<typename T>
bool Table<T>::operator<(const Table<T>& v) const {
	if ( this -> size < v.size )
		return true;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] < v[ i ] )
			return true;
		else if ( this -> dataTable[ i ] > v[ i ] )
			return false;
	}

	return false;
}

template<typename T>
bool Table<T>::operator>(const Table<T>& v) const {
	if ( this -> size > v.size )
		return true;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] > v[ i ] )
			return true;
		else if ( this -> dataTable[ i ] < v[ i ] )
			return false;
	}

	return false;
}

template<typename T>
bool Table<T>::operator<=(const Table<T>& v) const {
	if ( this -> size < v.size )
		return true;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] < v[ i ] )
			return true;
		else if ( this -> dataTable[ i ] > v[ i ] )
			return false;
	}

	return true;
}

template<typename T>
bool Table<T>::operator>=(const Table<T>& v) const {
	if ( this -> size > v.size )
		return true;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] > v[ i ] )
			return true;
		else if ( this -> dataTable[ i ] < v[ i ] )
			return false;
	}

	return true;
}

template<typename T>
template<typename Compare>
MATH_FUNC_QUALIFIER bool Table<T>::AND(Compare& func, const Table<T>& v) const {
	if ( this -> size != v.size )
		return false;

	for ( Size i(0); i < this->size; i++ ) {
		if ( !( func(this->dataTable[ i ], v[ i ]) ) ) {
			return false;
		}
	}
	return true;
}

template<typename T>
template<typename Compare>
MATH_FUNC_QUALIFIER bool Table<T>::AND(Compare& func, const T& s) const {
	for ( Size i(0); i < this->size; i++ ) {
		if ( !( func(this->dataTable[ i ], s) ) ) {
			return false;
		}
	}
	return true;
}

template<typename T>
template<typename Compare>
MATH_FUNC_QUALIFIER bool Table<T>::OR(Compare& func, const Table<T>& v) const {
	Size minSize(Math::min(getSize(), v.getSize()));

	for ( Size i(0); i < minSize; i++ ) {
		if ( func(this->dataTable[ i ], v[ i ]) ) {
			return true;
		}
	}
	return false;
}

template<typename T>
template<typename Compare>
MATH_FUNC_QUALIFIER bool Table<T>::OR(Compare& func, const T& s) const {
	for ( Size i(0); i < this->size; i++ ) {
		if ( func(this->dataTable[ i ], s) ) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Table<T>::operator!=(const Table<T>& v) const {
	return !AND(Math::Logical::Equal(), v);
}

template<typename T>
bool Table<T>::operator==(const Table<T>& v) const {
	return AND(Math::Logical::Equal(), v);
}

template<typename T>
template<typename C>
Table<T>::Table(const Table<C>& v) :
	size(v.size),
	dataTable(v.dataTable)
{}

template<typename T>
template<typename C>
Table<T>& Table<T>::operator=(const Table<C>&v) {
	this->size = v.size;
	this->dataTable = v.dataTable;
}

template<typename T>
Table<T>& Table<T>::operator=(const Table<T>& v) {
	this->size = v.size;
	this->dataTable = v.dataTable;
}

template<typename T>
Table<T>::Table(const Table<T>& v) :
	size(v.size),
	dataTable(v.dataTable) {}

template<typename T>
template<typename Functor, typename C>
Table<T>& Table<T>::apply(Functor& functor, const Table<C>& v) {
	ASSERT(getSize() == v.getSize());
	for ( Size i(0); i < getSize(); i++ ) {
		functor(this->dataTable[ i ], v[ i ]);
	}

	return *this;
}

template<typename T>
template<typename Functor>
Table<T>& Table<T>::apply(Functor& functor, const T& s) {
	for ( Size i(0); i < getSize(); i++ ) {
		functor(this->dataTable[ i ], s);
	}

	return *this;
}

template<typename T>
template<typename Functor>
Table<T>& Table<T>::apply(Functor& functor) {
	for ( Size i(0); i < getSize(); i++ ) {
		functor(this->dataTable[ i ]);
	}

	return *this;
}

template<typename T>
template<typename Functor, typename C>
Table<T>& Table<T>::set(Functor& functor, const Table<C>& v) {
	ASSERT(getSize() == v.getSize());
	for ( Size i(0); i < getSize(); i++ ) {
		T& value(this->dataTable[ i ]);
		value = functor(v[ i ]);
	}

	return *this;
}

template<typename T>
template<typename Functor>
Table<T>& Table<T>::set(Functor& functor, const T& s) {
	for ( Size i(0); i < getSize(); i++ ) {
		T& value(this->dataTable[ i ]);
		value = functor(s);
	}

	return *this;
}

template<typename T>
template<typename Functor>
Table<T>& Table<T>::set(Functor& functor) {
	for ( Size i(0); i < getSize(); i++ ) {
		T& value(this->dataTable[ i ]);
		value = functor.operator()<T>( );
	}

	return *this;
}

template<typename T>
Table<T>& Table<T>::fill(const T& data) {
	return apply(Math::Operations::Assign(), data);
}

template<typename T>
const Size Table<T>::getSize() const {
	return this -> size;
}

template<typename T>
const Size Table<T>::getSizeBytes() const {
	return this -> size * sizeof(T);
}

template<typename T>
T* Table<T>::getData() {
	return this -> dataTable;
}

template<typename T>
const T* Table<T>::getData() const {
	return this -> dataTable;
}

template<typename T>
bool Table<T>::exists(const T& value) const {
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == value )
			return true;
	}
	return false;
}

template<typename T>
bool Table<T>::replaceAll(const T& search, const T& data) {
	bool r(false);
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == search ) {
			this -> dataTable[ i ] = data;
			r = true;
		}
	}
	return r;
}

template<typename T>
bool Table<T>::replaceFirst(const T& search, const T& data) {
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == search ) {
			this -> dataTable[ i ] = data;
			return true;
		}
	}
	return false;
}

template<typename T>
void Table<T>::sortAsc() {
	sort(Math::Logical::Less());
}

template<typename T>
void Table<T>::sortDesc() {
	sort(Math::Logical::Greater());
}

template<typename T>
template<typename Func>
void Table<T>::sort(Func& functor) {
	if ( this -> size ) quicksort(this->dataTable, this->dataTable + this->size - Size(1), functor);
}

template<typename T>
template<typename Func>
const Size Table<T>::getMinI(Func& functor) const {
	if ( this->size == Size(0) ) {
		return Table<T>::overflow;
	} else {
		Size foundedMinI(0);
		for ( Size i(0); i < this->size; i++ ) {
			const T& v(getValueI(i));

			if ( functor(v, getValueI(foundedMinI)) ) {
				foundedMinI = i;
			}
		}
		return foundedMinI;
	}
}

template<typename T>
template<typename Func>
const Size Table<T>::getMaxI(Func& functor) const {
	if ( this->size == Size(0) ) {
		return Table<T>::overflow;
	} else {
		Size foundedMaxI(0);
		for ( Size i(0); i < this->size; i++ ) {
			const T& v(getValueI(i));

			if ( functor(getValueI(foundedMaxI), v) ) {
				foundedMaxI = i;
			}
		}
		return foundedMaxI;
	}
}

template<typename T>
const Size Table<T>::searchI(const T& data) const {
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == data )
			return i;
	}
	return Table<T>::overflow;
}

template<typename T>
template<typename S>
S Table<T>::toString() const {
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

template<typename T>
template<typename Stream>
bool Table<T>::write(Stream* stream) const {
	if ( !IO::write(stream, &this -> size) )
		return false;

	if ( !IO::write(stream, getData(), getSize()) ) {
		return false;
	}

	return true;
}

template<typename T>
template<typename Stream>
bool Table<T>::read(Stream* stream) {
	Size readSize;
	if ( !IO::read(stream, &readSize) ) {
		return false;
	}

	if ( readSize != this->size ) {
		SimpleLog::callErrorHandler(TEXT("Trying to load a Table of the wrong size."), SimpleLog::MessageSeverity::Warning, SimpleLog::MessageColor::Red);
	}

	Size minSize(Math::min(readSize, this->size));
	if ( !IO::read(stream, getData(), minSize) ) {
		return false;
	}

	return true;
}

template<typename T>
template<typename Compare>
void Table<T>::quicksort(T* startIt, T* endIt, Compare func) {
	// Create an auxiliary stack
	typedef struct {
		T* startIt;
		T* endIt;
	} quicksortStackItem;

	const Size stackSize(((endIt - startIt) >> Size(1)) + Size(1));
	quicksortStackItem* stack = new quicksortStackItem[ stackSize ];

	// push initial values of l and h to stack
	stack[ 0 ].startIt = startIt;
	stack[ 0 ].endIt = endIt;

	//initialize stack iterator
	quicksortStackItem* top = &( stack[ 0 ] );

	// Keep popping from stack while is not empty
	while ( top >= stack ) {
#ifdef DEBUG
		if ( !( top >= stack && top < stack + stackSize ) ) {
			SimpleLog::callErrorHandler("quicksort overflow", SimpleLog::MessageSeverity::Error, SimpleLog::MessageColor::Red);
		}
#endif
		endIt = top -> endIt;
		startIt = top -> startIt;
		top--;

		T* storeIt(startIt);

		for ( T* it(startIt); it < endIt; it++ ) {
			if ( func(*it, *endIt) ) {
				Utility::swap(it, storeIt);
				storeIt++;
			}
		}
		Utility::swap(endIt, storeIt);

		// If there are elements on left side of pivot, then push 
		if ( storeIt - Size(1) > startIt ) {
			top++;
#ifdef DEBUG
			if ( !( top >= stack && top < stack + stackSize ) ) {
				SimpleLog::callErrorHandler("quicksort overflow", SimpleLog::MessageSeverity::Error, SimpleLog::MessageColor::Red);
			}
#endif
			top -> startIt = startIt;
			top -> endIt = storeIt - Size(1);
		}

		// If there are elements on right side of pivot, then push 
		if ( storeIt + Size(1) < endIt ) {
			top++;
#ifdef DEBUG
			if ( !( top >= stack && top < stack + stackSize ) ) {
				SimpleLog::callErrorHandler("quicksort overflow", SimpleLog::MessageSeverity::Error, SimpleLog::MessageColor::Red);
			}
#endif
			top -> startIt = storeIt + Size(1);
			top -> endIt = endIt;
		}
	}

	delete[] stack;
}

template<typename T>
void Table<T>::swap(const Size i1, const Size i2) {
	Utility::swap<T>(this -> dataTable[ i1 ], this -> dataTable[ i2 ]);
}
