#pragma once

#include "Math/Logical.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicIO.h"
#include "IO/SimpleIO.h"

/** @brief	The Random Access Iterator */
template<typename T>
using RandomAccessIterator = T*;

template<typename T>
class BasicVector : public IO::BasicIO {
public:
	template<typename C>
	friend class Vector;

	template<typename C>
	friend class Vec;

	template<typename C>
	friend class BasicString;

	template<typename C>
	friend class UTF8StringT;

	/** @brief	Defines an alias representing the iterator */
	typedef RandomAccessIterator<T> Iterator;

	/** @brief	Defines an alias representing type of the element */
	typedef T ElemType;

	static constexpr Size elementSize = sizeof(T);

	BasicVector();
	BasicVector(const Size size);
	template<typename C, Size N>
	BasicVector(const C(&v)[ N ]);
	template<typename C>
	BasicVector(const C* v, const Size size);
	template<typename C>
	BasicVector(const BasicVector<C>& v);
	BasicVector(BasicVector<T> && v);

	~BasicVector();

	template<typename C, Size N>
	BasicVector<T>& operator=(const C(&v)[ N ]);
	template<typename C>
	BasicVector<T>& operator=(const BasicVector<C>& v);
	BasicVector<T>& operator=(BasicVector<T>&& v);

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

	/************************************************************************/
	/* Iterations                                                           */
	/************************************************************************/
	/**
	 * @brief 	Get the Begin Iterator
	 *
	 * @returns	Begin Iterator.
	 */
	typename BasicVector<T>::Iterator getBegin() const;

	/**
	 * @brief 	Get the End Iterator
	 *
	 * @returns	End Iterator.
	 */
	typename BasicVector<T>::Iterator getEnd() const;

	/**
	 * @brief 	iterate ONE time the iterator and return if there is still data
	 *
	 * @param [in,out]	it	If non-null, the iterator.
	 *
	 * @returns	it in out Iterator to iterate.
	 * @returns	If the iterator can return data.
	 */
	bool iterate(typename BasicVector<T>::Iterator* it) const;

	/**
	 * @brief 	Iterate ONE time and set the pointer to the pointer of the data retrieved
	 *
	 * @param [in,out]	it	in out Iterator to iterate.
	 * @param [in,out]	v 	out Pointer to a pointer to the value retrieved.
	 *
	 * @returns	True if a data has been retrieved or False if the end has been reached.
	 */
	bool iterate(typename BasicVector<T>::Iterator* it, ElemType** v) const;

	/**
	 * @brief 	Iterate ONE time and set the pointer to the pointer of the data retrieved
	 *
	 * @tparam	TestFunctor	Type of the test functor.
	 * @param [in,out]	it		   	in out Iterator to iterate.
	 * @param [in,out]	v		   	out Pointer to a pointer to the value retrieved.
	 * @param [in,out]	testFunctor	Functor to check a condition before incrementing the iterator
	 * 								  		bool operator()( const ElemType & e );
	 *
	 * @returns	True if a data has been retrieved or False if the end has been reached or false is the functor return false.
	 */
	template<typename TestFunctor>
	bool iterate(typename BasicVector<T>::Iterator* it, ElemType** v, TestFunctor& testFunctor) const;

	/************************************************************************/
	/* Access                                                               */
	/************************************************************************/

	/**
	 * @brief 	Get the Value associated with an direct access index (of type const Size)
	 *
	 * @param 	i	Iterator used to retrieve the value (no bound check is done here)
	 *
	 * @returns	Value founded.
	 */
	const T& getValueI(const Size i) const;
	T& getValueI(const Size i);

	/**
	 * @brief 	Get the Value associated with an iterator
	 *
	 * @param 	i	Iterator used to retrieve the value (no bound check is done here)
	 *
	 * @returns	Value founded.
	 */
	const T& getValueIt(typename BasicVector<T>::Iterator i) const;
	T& getValueIt(typename BasicVector<T>::Iterator i);

	const T& getValueF(float f) const;
	T& getValueF(float f);

	/**
	 * @brief 	Set the Value associated with an direct access index (of type Size)
	 *
	 * @param 	i   	Iterator used to set the value (no bound check is done here)
	 * @param 	data	The data.
	 */
	void setValueI(const Size i, const T& data);

	/**
	 * @brief 	Set the Value associated with an iterator
	 *
	 * @param 	i   	Iterator used to set the value.
	 * @param 	data	The data.
	 */
	void setValueIt(typename BasicVector<T>::Iterator i, const T& data);

	void setValueF(float f, const T& data);

	/**
	 * @brief 	get the last element of this vector
	 *
	 * @returns	Last element in the vector.
	 */
	const T& getLast() const;
	/**
	 * @brief 	Gets the last
	 *
	 * @returns	The last.
	 */
	T& getLast();

	/**
	 * @brief 	get the first element of this vector
	 *
	 * @returns	First element in the vector.
	 */
	const T& getFirst() const;
	/**
	 * @brief 	Gets the first
	 *
	 * @returns	The first.
	 */
	T& getFirst();

	/**
	 * @brief	Get the index from an Iterator.
	 *
	 * @param	it	Iterator to be used.
	 *
	 * @return	Index from the Iterator.
	 */
	Size getIndex(typename BasicVector<T>::Iterator it) const;
	Size getIndex(float f) const;

	typename BasicVector<T>::Iterator getIterator(const Size i) const;


	/**
	 * @brief 	Equality operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==(const BasicVector<T>& v) const;
	/**
	 * @brief 	Inequality operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the parameters are not considered equivalent.
	 */
	bool operator!=(const BasicVector<T>& v) const;
	/**
	 * @brief 	Less-than comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<(const BasicVector<T>& v) const;
	/**
	 * @brief 	Greater-than comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>(const BasicVector<T>& v) const;
	/**
	 * @brief 	Less-than-or-equal comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const BasicVector<T>& v) const;
	/**
	 * @brief 	Greater-than-or-equal comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const BasicVector<T>& v) const;

	/************************************************************************/
	/* ================                MISC                ================ */
	/************************************************************************/

	void resize(const Size newSize);
	void resizeNoCopy(const Size newSize);

	/**
	 * @brief 	Fill the complete vector with the specified data.
	 *
	 * @param 	data	data to be copied in the whole vector.
	 */
	void fill(const T& data);

	/**
	 * @brief 	Get the size of this vector
	 *
	 * @returns	Number of datas of this vector.
	 */
	const Size getSize() const;

	/**
	 * @brief 	Get the size of this vector in bytes
	 *
	 * @returns	const Size of this vector in bytes.
	 */
	const Size getSizeBytes() const;

	/**
	 * @brief 	Gets the data
	 *
	 * @returns	Null if it fails, else the data.
	 */
	const T* getData() const;
	/**
	 * @brief 	Gets the data
	 *
	 * @returns	Null if it fails, else the data.
	 */
	T* getData();

	/**
	 * @brief 	Test if a value exists in this vector
	 *
	 * @param 	value	The value.
	 *
	 * @returns	True if the value has been founded and false instead.
	 */
	bool exists(const T& value) const;

	/**
	 * @brief 	Replace the first occurrence of the data
	 *
	 * @param 	searchI	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 *
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceFirst(const T& search, const T& data);

	/**
	 * @brief 	Replace ALL occurrences of the data searched
	 *
	 * @param 	searchI	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 *
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceAll(const T& search, const T& data);

	/** @brief	Quicksort the vector using the operator>() */
	void sortDesc();

	/** @brief	Quicksort the vector using the operator<() */
	void sortAsc();

	/**
	 * @brief 	sort the elements of this vector using the quicksort algorithm
	 *
	 * @tparam	Func	Type of the function.
	 * @param [in,out]	functor	(Optional) Functor with operator () overloaded with : bool operator()(const T &, const T &) const;
	 */
	template<typename Func = Math::Logical::Less>
	void sort(Func& functor = Func());

	/**
	 * @brief	Get the min value of this Vector using the specified functor to compare the items.
	 *
	 * @tparam	Func	Type of the Functor used to compare items.
	 * @param [in,out]	functor Functor used to compare items.
	 *
	 * @return	Iterator to the founded item, NULL if none.
	 */
	template<typename Func = Math::Logical::Less>
	const Size getMinI(Func& functor = Func()) const;

	/**
	 * @brief	Get the max value of this Vector using the specified functor to compare the items.
	 *
	 * @tparam	Func	Type of the Functor used to compare items.
	 * @param [in,out]	functor Functor used to compare items.
	 *
	 * @return	Iterator to the founded item, NULL if none.
	 */
	template<typename Func = Math::Logical::Less>
	const Size getMaxI(Func& functor = Func()) const;

	/**
	 * @brief	Get the min value of this Vector using the specified functor to compare the items.
	 *
	 * @tparam	Func	Type of the Functor used to compare items.
	 * @param [in,out]	functor Functor used to compare items.
	 *
	 * @return	Iterator to the founded item, NULL if none.
	 */
	template<typename Func = Math::Logical::Less>
	typename BasicVector<T>::Iterator getMinIt(Func& functor = Func()) const;

	/**
	 * @brief	Get the max value of this Vector using the specified functor to compare the items.
	 *
	 * @tparam	Func	Type of the Functor used to compare items.
	 * @param [in,out]	functor Functor used to compare items.
	 *
	 * @return	Iterator to the founded item, NULL if none.
	 */
	template<typename Func = Math::Logical::Less>
	typename BasicVector<T>::Iterator getMaxIt(Func& functor = Func()) const;

	/**
	 * @brief 	read from a file stream
	 *
	 * @param [in,out]	stream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool read(Stream* stream);

	/**
	 * @brief 	write this object as binary into a file stream
	 *
	 * @param [in,out]	stream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool write(Stream* stream) const;

	/**
	 * @brief 	Search a data and retrieve the index
	 *
	 * @param 	data	Data to be searched.
	 *
	 * @returns	Index where the data has bee founded if founded. return Vector<T>::overflow instead.
	 */
	const Size searchI(const T& data) const;

	/************************************************************************/
	/* Static                                                               */
	/************************************************************************/



	/**
	 * @brief 	Gets the overflow
	 *
	 * @returns	The overflow.
	 */
	static const Size overflow;


protected:
	/** @brief	Values that represent Constructors */
	enum class ctor {
		null
	};

	BasicVector(BasicVector<T>::ctor);

	/**
	 * @brief 	Quicksorts
	 *
	 * @tparam	Compare	Type of the compare.
	 * @param 	start	The start.
	 * @param 	end  	The end.
	 * @param 	func 	(Optional) The function.
	 */
	template<typename Compare>
	void quicksort(typename BasicVector<T>::Iterator start, typename BasicVector<T>::Iterator end, Compare func = Math::Logical::Less);

	/**
	 * @brief 	Swaps
	 *
	 * @param 	index1	The first index.
	 * @param 	index2	The second index.
	 */
	void swap(const Size index1, const Size index2);
	/**
	 * @brief 	Swaps
	 *
	 * @param 	index1	The first index.
	 * @param 	index2	The second index.
	 */
	void swap(typename BasicVector<T>::Iterator index1, typename BasicVector<T>::Iterator index2);

	/** Size of the Vector */
	Size size;

	/** @brief	The data table */
	T* dataTable;
};

template<typename T>
const Size BasicVector<T>::overflow = Size(-1);

template<typename T>
inline BasicVector<T>::BasicVector() :
	size(Size(0)),
	dataTable(NULL)
{}

template<typename T>
inline BasicVector<T>::BasicVector(const Size size) :
	size(size),
	dataTable((size) ? new T[size] : NULL)
{}

template<typename T>
inline BasicVector<T>::BasicVector(BasicVector && v) :
	size(Utility::toRValue(v.size)),
	dataTable(Utility::toRValue(v.dataTable))
{
	v.dataTable = NULL;
}

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

	this->size = Utility::toRValue(v.size);
	this->dataTable = Utility::toRValue(v.dataTable);

	v.dataTable = NULL;
}

template<typename T>
inline const T& BasicVector<T>::operator[](const Size i) const {
	return this->dataTable[ i ];
}

template<typename T>
inline T& BasicVector<T>::operator[](const Size i) {
	return this->dataTable[ i ];
}

template<typename T>
inline BasicVector<T>::BasicVector(BasicVector<T>::ctor) {}

template<typename T>
template<typename C, Size N>
inline BasicVector<T>::BasicVector(const C(&v)[ N ]) :
	size(N),
	dataTable(new T[N])
{
	Utility::copy(this->dataTable, v, N);
}

template<typename T>
template<typename C>
inline BasicVector<T>::BasicVector(const C* v, const Size size) :
	size(size),
	dataTable(new T[size])
{
	Utility::copy(this->dataTable, v, this->size);
}

template<typename T>
template<typename C>
inline BasicVector<T>::BasicVector(const BasicVector<C>& v) :
	size(v.size),
	dataTable(new T[v.size])
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
inline BasicVector<T>& BasicVector<T>::operator=(const BasicVector<C>& v) {
	resizeNoCopy(v.getSize());
	Utility::copy(this->dataTable, v, this->size);

	return *this;
}

template<typename T>
bool BasicVector<T>::operator<(const BasicVector<T>& v) const {
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
bool BasicVector<T>::operator>(const BasicVector<T>& v) const {
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
bool BasicVector<T>::operator<=(const BasicVector<T>& v) const {
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
bool BasicVector<T>::operator>=(const BasicVector<T>& v) const {
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

template<typename T>
bool BasicVector<T>::operator!=(const BasicVector<T>& v) const {
	if ( this -> size != v.size )
		return true;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] != v.dataTable[ i ] )
			return true;
	}
	return false;
}

template<typename T>
bool BasicVector<T>::operator==(const BasicVector<T>& v) const {
	if ( this -> size != v.size )
		return false;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] != v.dataTable[ i ] )
			return false;
	}
	return true;
}

template<typename T>
void BasicVector<T>::fill(const T& data) {
	for ( Size i(0); i < this -> size; i++ ) {
		this -> dataTable[ i ] = data;
	}
}

template<typename T>
const Size BasicVector<T>::getSize() const {
	return this -> size;
}

template<typename T>
const Size BasicVector<T>::getSizeBytes() const {
	return this -> size * sizeof(T);
}

template<typename T>
T* BasicVector<T>::getData() {
	return this -> dataTable;
}

template<typename T>
const T* BasicVector<T>::getData() const {
	return this -> dataTable;
}

template<typename T>
bool BasicVector<T>::exists(const T& value) const {
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == value )
			return true;
	}
	return false;
}

template<typename T>
bool BasicVector<T>::replaceAll(const T& search, const T& data) {
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
bool BasicVector<T>::replaceFirst(const T& search, const T& data) {
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == search ) {
			this -> dataTable[ i ] = data;
			return true;
		}
	}
	return false;
}

template<typename T>
void BasicVector<T>::sortAsc() {
	sort(Math::Logical::Less());
}

template<typename T>
void BasicVector<T>::sortDesc() {
	sort(Math::Logical::Greater());
}

template<typename T>
template<typename Func>
void BasicVector<T>::sort(Func& functor) {
	if ( this -> size ) quicksort(this -> dataTable, this -> dataTable + this->size - Size(1), functor);
}

template<typename T>
template<typename Func>
const Size BasicVector<T>::getMinI(Func& functor) const {
	if ( this->size == Size(0) ) {
		return BasicVector<T>::overflow;
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
const Size BasicVector<T>::getMaxI(Func& functor) const {
	if ( this->size == Size(0) ) {
		return BasicVector<T>::overflow;
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
template<typename Func>
typename BasicVector<T>::Iterator BasicVector<T>::getMinIt(Func& functor) const {
	if ( this->size == Size(0) ) {
		return typename BasicVector<T>::Iterator(NULL);
	} else {
		typename BasicVector<T>::Iterator foundedMinIt(this->dataTable);
		for ( typename BasicVector<T>::Iterator it(getBegin() + 1); it < getEnd(); iterate(&it) ) {
			const T& v(getValueIt(it));

			if ( functor(v, getValueIt(foundedMinIt)) ) {
				foundedMinIt = it;
			}
		}
		return foundedMinIt;
	}
}

template<typename T>
template<typename Func>
typename BasicVector<T>::Iterator BasicVector<T>::getMaxIt(Func& functor) const {
	if ( this->size == Size(0) ) {
		return typename BasicVector<T>::Iterator(NULL);
	} else {
		typename BasicVector<T>::Iterator foundedMaxIt(this->dataTable);
		for ( typename BasicVector<T>::Iterator it(getBegin() + 1); it < getEnd(); iterate(&it) ) {
			const T& v(getValueIt(it));

			if ( functor(getValueIt(foundedMaxIt), v) ) {
				foundedMaxIt = it;
			}
		}
		return foundedMaxIt;
	}
}

template<typename T>
const Size BasicVector<T>::searchI(const T& data) const {
	for ( Size i(0); i < this -> size; i++ ) {
		if ( this -> dataTable[ i ] == data )
			return i;
	}
	return BasicVector<T>::overflow;
}

template<typename T>
template<typename Stream>
bool BasicVector<T>::write(Stream* stream) const {
	if ( !IO::write(stream, &this -> size) )
		return false;

	for ( Size i(0); i < this -> size; i++ ) {
		if ( !IO::write(stream, &( this -> dataTable[ i ] )) )
			return false;
	}

	return true;
}

template<typename T>
template<typename Stream>
bool BasicVector<T>::read(Stream* stream) {
	Size readSize;
	if ( !IO::read(stream, &readSize) ) {
		return false;
	}

	Size minSize(Math::min(readSize, this->size));
	for ( Size i(0); i < minSize; i++ ) {
		if ( !IO::read(stream, &( this -> dataTable[ i ] )) ) {
			return false;
		}
	}

	return true;
}

template<typename T>
template<typename Compare>
void BasicVector<T>::quicksort(typename BasicVector<T>::Iterator start, typename BasicVector<T>::Iterator end, Compare func) {
	// Create an auxiliary stack
	typedef struct {
		typename BasicVector<T>::Iterator start;
		typename BasicVector<T>::Iterator end;
	} quicksortStackItem;

	quicksortStackItem* stack = new quicksortStackItem[ ( end - start ) / 2 + 1 ];


	// push initial values of l and h to stack
	stack[ 0 ].start = start;
	stack[ 0 ].end = end;

	//initialize stack iterator
	quicksortStackItem* top = &( stack[ 0 ] );

	// Keep popping from stack while is not empty
	while ( top >= stack ) {
		end = top -> end;
		start = top -> start;
		top--;

		typename BasicVector<T>::Iterator storeIndex = start;

		for ( auto i = start; i < end; i++ ) {
			if ( func(*i, *end) ) {
				BasicVector::swap(i, storeIndex);
				storeIndex++;
			}
		}
		BasicVector::swap(end, storeIndex);

		// If there are elements on left side of pivot, then push 
		if ( storeIndex - 1 > start ) {
			top++;
			top -> start = start;
			top -> end = storeIndex - 1;
		}

		// If there are elements on right side of pivot, then push 
		if ( storeIndex + 1 < end ) {
			top++;
			top -> start = storeIndex + 1;
			top -> end = end;
		}
	}

	delete[] stack;
}

template<typename T>
const T& BasicVector<T>::getLast() const {
	return *( this -> iteratorEnd - 1 );
}


template<typename T>
T& BasicVector<T>::getLast() {
	return *( this -> iteratorEnd - 1 );
}


template<typename T>
const T& BasicVector<T>::getFirst() const {
	return *dataTable;
}


template<typename T>
T& BasicVector<T>::getFirst() {
	return *dataTable;
}

template<typename T>
Size BasicVector<T>::getIndex(typename BasicVector<T>::Iterator it) const {
	return Size(it - this->dataTable);
}

template<typename T>
inline Size BasicVector<T>::getIndex(float f) const {
	float rounding(0.5f / float(this->size));
	f = f + rounding;
	if ( f < 0.0f ) {
		return Size(0);
	} else if ( f > 1.0f ) {
		return this->size - Size(1);
	} else {
		Size i(f * float(this->size - Size(1)));
		return i;
	}
}

template<typename T>
inline typename BasicVector<T>::Iterator BasicVector<T>::getIterator(const Size i) const {
	return this->dataTable + i;
}

/************************************************************************/
/* ITERATIONS                                                           */
/************************************************************************/

template<typename T>
bool BasicVector<T>::iterate(typename BasicVector<T>::Iterator* it) const {
	( *it )++;
	return !( *it == getEnd() );
}

template<typename T>
bool BasicVector<T>::iterate(typename BasicVector<T>::Iterator* it, ElemType** e) const {
	if ( *it == getEnd() )
		return false;
	*e = *it;
	( *it )++;
	return true;
}

template<typename T>
template<typename TestFunctor>
bool BasicVector<T>::iterate(typename BasicVector<T>::Iterator* it, ElemType** e, TestFunctor& testFunctor) const {
	if ( *it == getEnd() )
		return false;
	*e = *it;
	if ( testFunctor(*e) ) {
		( *it )++;
		return true;
	}
	return false;
}

template<typename T>
typename BasicVector<T>::Iterator BasicVector<T>::getBegin() const {
	return this -> dataTable;
}

template<typename T>
typename BasicVector<T>::Iterator BasicVector<T>::getEnd() const {
	return this -> iteratorEnd;
}

template<typename T>
void BasicVector<T>::setValueI(const Size i, const T& data) {
#ifdef DEBUG
	if ( i >= this->size ) {
		_error("BasicVector::setValueI Out of bounds.");
	}
#endif
	this -> dataTable[ i ] = data;
}

template<typename T>
void BasicVector<T>::setValueIt(typename BasicVector<T>::Iterator i, const T& data) {
#ifdef DEBUG
	if ( i < this->dataTable || i >= this->dataTable + this->size ) {
		_error("BasicVector::setValueIt Out of bounds.");
	}
#endif
	* i = data;
}

template<typename T>
inline void BasicVector<T>::setValueF(float f, const T& data) {
	this->dataTable[ getIndex(f) ] = data;
}

template<typename T>
inline const T& BasicVector<T>::getValueF(float f) const {
	return const_cast< BasicVector<T> * >( this )->getValueF(f);
}

template<typename T>
inline T& BasicVector<T>::getValueF(float f) {
	return this->dataTable[ getIndex(f) ];
}

template<typename T>
const T& BasicVector<T>::getValueI(const Size i) const {
	return const_cast<BasicVector<T> *>(this)->getValueI(i);
}

template<typename T>
T& BasicVector<T>::getValueI(const Size i) {
#ifdef DEBUG
	if ( i >= this->size ) {
		_error("BasicVector::getValueI Out of bounds.");
	}
#endif
	return this -> dataTable[ i ];
}

template<typename T>
const T& BasicVector<T>::getValueIt(typename BasicVector<T>::Iterator it) const {
	return const_cast< BasicVector<T> * >( this )->getValueIt(it);
}

template<typename T>
T& BasicVector<T>::getValueIt(typename BasicVector<T>::Iterator it) {
#ifdef DEBUG
	if ( it < this->dataTable || it >= this->dataTable + this->size ) {
		_error("BasicVector::getValueIt Out of bounds.");
	}
#endif
	return *it;
}

template<typename T>
void BasicVector<T>::swap(const Size index1, const Size index2) {
	Utility::swap<T>(this -> dataTable[ index1 ], this -> dataTable[ index2 ]);
}

template<typename T>
void BasicVector<T>::swap(typename BasicVector<T>::Iterator index1, typename BasicVector<T>::Iterator index2) {
	Utility::swap<T>(*index1, *index2);
}
