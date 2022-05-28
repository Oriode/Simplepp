/**
 * @file	Vector.h.
 *
 * @brief 	Declares the vector class
 * @author	Clément Gerber
 * @date		???
 */
#pragma once

#include <utility>
#include <algorithm>
#include <ostream>

#include "BasicVector.h"
#include "Math/Logical.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicIO.h"
#include "IO/SimpleIO.h"

/**
 * @brief		DataStructure used to store a "list" of elements represented by an index of type "Size" ( unsigned long long int ) and a value of type T. The elements will be stored contiguously in memory.
 *			/!\ Elements can be accessed directly using Iterator ( A pointer of it ). But if the Vector is resized ( or the elements reorganized ), the Iterator will be deprecated and result in a segmentation fault.
 *
 * @tparam	T	Type of the Values to store.
 */
template<typename T = int>
class Vector : public BasicVector<T> {
public:
	template<typename C>
	friend class BasicString;

	template<typename C>
	friend class UTF8StringT;
	
	/** @brief	Default constructor */
	Vector( void );

	///@brief Constructor initializing a Vector of a specific size and max size.
	///@param size Size of the vector.
	///@param maxSize Max size of the vector.
	Vector( const Size size, const Size maxSize );

	///@brief Constructor initializing a Vector of a specific max size.
	///@param maxSize Max size of the vector.
	Vector( const Size maxSize );

	///@brief Copy constructor.
	///@template C type of the Vector to be copied.
	///@param stream Vector to be copied.
	template<typename C>
	Vector( const Vector<C> & vector );

	///@brief Copy constructor.
	///@template C type of the Vector to be copied.
	///@param stream Vector to be copied.
	template<typename C>
	Vector(const BasicVector<C>& vector);

	///@brief Move constructor.
	///@param stream Vector to be moved from.
	Vector( Vector<T> && v );

	///@brief Constructor using a static array.
	///@template C Array element type.
	///@template N Array size.
	///@param data Array to be copied.
	template<typename C, Size N>
	Vector( const C( &data )[ N ] );

	///@brief Constructor using an array and it's size.
	///@template C Array element type.
	///@param data Array to be copied.
	///@param size Array size.
	template<typename C>
	Vector( const C * data, const Size size );

	///@brief Constructor using an array, it's size, and a maxSize for the Vector to be allocated.
	///@template C Array element type.
	///@param data Array to be copied.
	///@param size Array size.
	///@param maxSize Vector max size.
	template<typename C>
	Vector( const C * data, const Size size, const Size maxSize );

	///@brief Constructor for an Iterator Begin and an Iterator End. Will compute the size between the two iterators, allocate and copy the data into the Vector.
	///@template C Element type to be copied.
	///@param beginIt Iterator begin.
	///@param endIt Iterator end.
	template<typename C>
	Vector( const typename RandomAccessIterator<C> beginIt, const typename RandomAccessIterator<C> endIt );

	/** @brief	Destructor */
	~Vector( void );



	/**
	 * @brief 	allocate the memory with the specified size and copy old datas (used method in push when the size isn't enough)
	 *
	 * @param 	newMax	New size of the inner buffer (the size won't be changed)
	 */
	void reserve( const Size newMax );

	/**
	 * @brief 	allocate the new buffer size (without copying the olds datas and update the size)
	 *
	 * @param 	newMax	New size of the inner buffer (the size won't be changed and the data wont be copied)
	 */
	void allocate( const Size newMax );

	/**
	 * @brief 	Set a new size, and reallocate and copy old datas if necessary.
	 *
	 * @param 	newSize	New size to be set for the vector.
	 */
	void resize( const Size newSize );
	void resizeNoCopy(const Size newSize);

	/**
	 * @brief	Extend the size to the left by shifting the values.
	 *
	 * @param	increasedSize Size to be added to the left.
	 */
	void extendLeft( const Size increasedSize );

	/**
	 * @brief	Extend the size to the right. resize(this -> size + increasedSize)
	 *
	 * @param	increasedSize Size to be added to the right.
	 */
	void extendRight( const Size increasedSize );

	/************************************************************************/
	/* LOGICAL                                                              */

	/**
	 * @brief 	Equality operator
	 *
	 * @param 	v	A T to process.
	 *
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==( const T & v ) const;
	/**
	 * @brief 	Inequality operator
	 *
	 * @param 	v	A T to process.
	 *
	 * @returns	True if the parameters are not considered equivalent.
	 */
	bool operator!=( const T & v ) const;
	/**
	 * @brief 	Less-than comparison operator
	 *
	 * @param 	v	A T to process.
	 *
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<( const T & v ) const;
	/**
	 * @brief 	Greater-than comparison operator
	 *
	 * @param 	v	A T to process.
	 *
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>( const T & v ) const;
	/**
	 * @brief 	Less-than-or-equal comparison operator
	 *
	 * @param 	v	A T to process.
	 *
	 * @returns	True if the first parameter is less than or equal to the second.
	 */
	bool operator<=( const T & v ) const;
	/**
	 * @brief 	Greater-than-or-equal comparison operator
	 *
	 * @param 	v	A T to process.
	 *
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=( const T & v ) const;



	/**
	 * @brief 	Copy Operator
	 *
	 * @param 	vector	Vector to be copied.
	 *
	 * @returns	reference to THIS.
	 */
	template<typename C>
	Vector<T> & operator=( const Vector<C> & vector );
	template<typename C>
	Vector<T>& operator=(const BasicVector<C>& vector);

	/**
	 * @brief 	Move operator
	 *
	 * @param [in,out]	v	to be moved.
	 *
	 * @returns	reference to THIS.
	 */
	Vector<T> & operator=( Vector<T> && v );

	/**
	 * @brief 	Concat another vector to this one
	 *
	 * @param 	vector	Vector to be concatenated.
	 *
	 * @returns	reference to THIS.
	 */
	template<typename C>
	Vector<T> & operator+=( const Vector<C> & vector );

	/**
	 * @brief 	Concat another vector to this one
	 *
	 * @param 	vector	Vector to be concatenated.
	 */
	template<typename C>
	void concat( const Vector<C> & vector );

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
	/**
	 * @brief 	Gets value i
	 *
	 * @param 	i	Zero-based index of the.
	 *
	 * @returns	The value i.
	 */
	T& getValueI(const Size i);

	/**
	 * @brief 	Get the Value associated with an iterator
	 *
	 * @param 	i	Iterator used to retrieve the value (no bound check is done here)
	 *
	 * @returns	Value founded.
	 */
	const T& getValueIt(typename Vector<T>::Iterator i) const;
	/**
	 * @brief 	Gets value iterator
	 *
	 * @param 	i	Zero-based index of the.
	 *
	 * @returns	The value iterator.
	 */
	T& getValueIt(typename Vector<T>::Iterator i);

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
	void setValueIt(typename Vector<T>::Iterator i, const T& data);

	/**
	 * @brief 	insert a new data in the vector getSize() will be incremented and the memory auto managed.
	 *
	 * @param 	data	data to be inserted.
	 *
	 * @returns	Pointer to the data just inserted.
	 */
	T * push( const T & data );

	/**
	 * @brief 	retrieve the last inserted object and decrement getSize() and decrement size
	 *
	 * @returns	last inserted data.
	 */
	T & pop();


	/**
	 * @brief 	Insert a value a the specified index
	 *
	 * @param 	i	Index.
	 * @param 	v	Value to insert.
	 */
	void inserti( const Size i, const T & v );

	/**
	 * @brief 	Get the size of the inner buffer
	 *
	 * @returns	const Size of the inner buffer.
	 */
	const Size getMaxSize() const;

	/** @brief	Set the size = 0 */
	void clear();

	/** @brief	Set the size = 0 and clear the memory */
	void reset();

	/**
	 * @brief 	Get if the Vector is empty of not
	 *
	 * @returns	True if the Vector is empty, false otherwise.
	 */
	bool isEmpty() const;

	/**
	 * @brief 	Clear and re create this vector from a data table
	 *
	 * @tparam	C	Type of the c.
	 * @param 	dataTable	Table to be read.
	 * @param 	size	 	Number of elements in the table to be read.
	 */
	template<typename C>
	void createFromData( const C * dataTable, const Size size );

	/**
	 * @brief 	Erase the first occurrence and rearrange the data
	 *
	 * @param 	value	Value to be searched and erased.
	 *
	 * @returns	True if something has been deleted, False otherwise.
	 */
	bool eraseFirst( const T & value );

	/**
	 * @brief 	Erase all the occurrences and rearrange the data
	 *
	 * @param 	value	Value to be searched and erased.
	 *
	 * @returns	True if something has been deleted, False otherwise.
	 */
	bool eraseAll( const T & value );

	/**
	 * @brief 	Erase the data at the specified index and rearrange the data
	 *
	 * @param 	index	Index to be erased.
	 */
	void eraseI( const Size i );

	/**
	 * @brief 	Erase the data at the specified iterator and rearrange the data
	 *
	 * @param 	index	Iterator to be erased.
	 */
	void eraseIt( const typename Vector<T>::Iterator it );

	/**
	 * @brief 	Copy a part of an another vector into this one
	 *
	 * @tparam	C	Type of the c.
	 * @param 	vector   	Vector to be copied.
	 * @param 	indexSrc 	Source index where to begin the copy.
	 * @param 	indexDest	Destination index where to begin the copy.
	 * @param 	size	 	Number of elements to copy.
	 */
	template<typename C>
	void copy( Vector<C> vector, Size indexSrc, const Size indexDest, Size size );

	/**
	 * @brief 	Copy datas from a buffer into this vector
	 *
	 * @tparam	C	Type of the c.
	 * @param 	datas	 	The datas.
	 * @param 	indexDest	Index where to copy the datas.
	 * @param 	size	 	Number of elements to copy.
	 */
	template<typename C>
	void copy( const C * datas, const Size indexDest, const Size size );

	/**
	 * @brief 	Copy datas from a buffer into this vector
	 *
	 * @tparam	C	Type of the c.
	 * @param 	datas	The datas.
	 * @param 	size 	Number of elements to copy.
	 */
	template<typename C>
	void copy( const C * datas, const Size size );

	/**
	 * @brief 	read from a file stream
	 *
	 * @param [in,out]	stream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool read( Stream * stream );


protected:
	/**
	 * @brief 	Constructor
	 *
	 * @param 	parameter1	The first parameter.
	 */
	Vector( Vector<T>::ctor );

	/** @brief	Clears this object to its blank/initial state */
	void _clear();

	/**
	 * @brief 	Delete the old buffer; allocate a new one; Set the new maxSize;
	 *
	 * @param 	newMax	The new maximum.
	 */
	void _allocateNoNull( const Size newMax );

	/**
	 * @brief 	allocate a new buffer; Set the new maxSize;
	 *
	 * @param 	newMax	The new maximum.
	 */
	void _allocateNoNullDelete( const Size newMax );

	/**
	 * @brief 	Extend the actual buffer to be able to handle AT LEAST the newSizeNeeded (possible algo is *2), size has to be NOT null
	 *
	 * @param 	newSizeNeeded	The new size needed.
	 */
	void _extendBuffer( const Size newSizeNeeded );

	/** @brief	Updates the iterators */
	void _updateIterators();

	/**
	 * @brief 	Erase a value at a specified index.
	 *
	 * @param 	index	Zero-based index.
	 */
	void _erasei( const Size index );
	/**
	 * @brief 	Erase a value at a specified iterator.
	 *
	 * @param 	it	The iterator.
	 */
	void _eraseit( typename Vector<T>::Iterator it );

	/** Size of the buffer */
	Size maxSize;

	/** Pointer to the last value */
	typename Vector<T>::Iterator iteratorEnd;
};


template<typename T>
std::ostream & operator <<( std::ostream & stream, const Vector<T> & vector );



#include "Vector.hpp"




