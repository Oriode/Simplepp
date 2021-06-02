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

#include "Math/Logical.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicSimpleIO.h"
#include "IO/SimpleIO.h"

 /** @brief	The Random Access Iterator */
template<typename T>
using RandomAccessIterator = T *;

/**
 * @brief		DataStructure used to store a "list" of elements represented by an index of type "Size" ( unsigned long long ) and a value of type T. The elements will be stored contiguously in memory.
 *			/!\ Elements can be accessed directly using Iterator ( A pointer of it ). But if the Vector is resized ( or the elements reorganized ), the Iterator will be deprecated and result in a segmentation fault.
 *
 * @tparam	T	Type of the Values to store.
 */
template<typename T = int>
class Vector : public IO::BasicSimpleIO {
public:

	/** @brief	Defines an alias representing the iterator */
	typedef RandomAccessIterator<T> Iterator;
	/** @brief	Defines an alias representing type of the element */
	typedef T ElemType;
	/** @brief	Defines an alias representing the size */
	typedef unsigned long long Size;

	static constexpr size_t elementSize = sizeof( T );

	/** @brief	Default constructor */
	Vector( void );

	///@brief Constructor initializing a Vector of a specific size and max size.
	///@param size Size of the vector.
	///@param maxSize Max size of the vector.
	Vector( const typename Vector<T>::Size size, const typename Vector<T>::Size maxSize );

	///@brief Constructor initializing a Vector of a specific max size.
	///@param maxSize Max size of the vector.
	Vector( const typename Vector<T>::Size maxSize );

	///@brief Copy constructor.
	///@param stream Vector to be copied.
	Vector( const Vector & vector );
	
	///@brief Copy constructor.
	///@template C type of the Vector to be copied.
	///@param stream Vector to be copied.
	template<typename C>
	Vector( const Vector<C> & vector );

	///@brief Move constructor.
	///@param stream Vector to be moved from.
	Vector( Vector && v );

	///@brief Constructor using a static array.
	///@template C Array element type.
	///@template N Array size.
	///@param data Array to be copied.
	template<typename C, size_t N>
	Vector( const C( &data )[ N ] );

	///@brief Constructor using an array and it's size.
	///@template C Array element type.
	///@param data Array to be copied.
	///@param size Array size.
	template<typename C>
	Vector( const C * data, const typename Vector<T>::Size size );

	///@brief Constructor using an array, it's size, and a maxSize for the Vector to be allocated.
	///@template C Array element type.
	///@param data Array to be copied.
	///@param size Array size.
	///@param maxSize Vector max size.
	template<typename C>
	Vector( const C * data, const typename Vector<T>::Size size, const typename Vector<T>::Size maxSize );

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
	void reserve( const typename Vector<T>::Size newMax );

	/**
	 * @brief 	allocate the new buffer size (without copying the olds datas and update the size)
	 *
	 * @param 	newMax	New size of the inner buffer (the size won't be changed and the data wont be copied)
	 */
	void allocate( const typename Vector<T>::Size newMax );

	/**
	 * @brief 	Set a new size, and reallocate and copy old datas if necessary.
	 *
	 * @param 	newSize	New size to be set for the vector.
	 */
	void resize( const typename Vector<T>::Size newSize );


	/************************************************************************/
	/* Iterations                                                           */
	/************************************************************************/
	/**
	 * @brief 	Get the Begin Iterator
	 *
	 * @returns	Begin Iterator.
	 */
	typename Vector<T>::Iterator getBegin() const;

	/**
	 * @brief 	Get the End Iterator
	 *
	 * @returns	End Iterator.
	 */
	typename Vector<T>::Iterator getEnd() const;

	/**
	 * @brief 	alias of getBegin()
	 *
	 * @returns	A Vector<T>::Iterator.
	 */
	typename Vector<T>::Iterator begin() const;

	/**
	 * @brief 	alias of getEnd()
	 *
	 * @returns	A Vector<T>::Iterator.
	 */
	typename Vector<T>::Iterator end() const;

	/**
	 * @brief 	iterate ONE time the iterator and return if there is still data
	 *
	 * @param [in,out]	it	If non-null, the iterator.
	 *
	 * @returns	it in out Iterator to iterate.
	 * @returns	If the iterator can return data.
	 */
	bool iterate( typename Vector<T>::Iterator * it ) const;

	/**
	 * @brief 	Iterate ONE time and set the pointer to the pointer of the data retrieved
	 *
	 * @param [in,out]	it	in out Iterator to iterate.
	 * @param [in,out]	v 	out Pointer to a pointer to the value retrieved.
	 *
	 * @returns	True if a data has been retrieved or False if the end has been reached.
	 */
	bool iterate( typename Vector<T>::Iterator * it, ElemType ** v ) const;

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
	bool iterate( typename Vector<T>::Iterator * it, ElemType ** v, TestFunctor & testFunctor ) const;

	/************************************************************************/
	/* Access                                                               */
	/************************************************************************/

	/**
	 * @brief 	Get a value and can assign something else
	 *
	 * @param 	index	Index.
	 *
	 * @returns	Value founded.
	 */
	const T & operator[]( const typename Vector<T>::Size index ) const;
	/**
	 * @brief 	Array indexer operator
	 *
	 * @param 	index	Zero-based index of the.
	 *
	 * @returns	The indexed value.
	 */
	T & operator[]( const typename Vector<T>::Size index );

	/**
	 * @brief 	Get the Value associated with an direct access index (of type const typename Vector<T>::Size)
	 *
	 * @param 	i	Iterator used to retrieve the value (no bound check is done here)
	 *
	 * @returns	Value founded.
	 */
	const T & getValueI( const typename Vector<T>::Size i ) const;
	/**
	 * @brief 	Gets value i
	 *
	 * @param 	i	Zero-based index of the.
	 *
	 * @returns	The value i.
	 */
	T & getValueI( const typename Vector<T>::Size i );

	/**
	 * @brief 	Get the Value associated with an iterator
	 *
	 * @param 	i	Iterator used to retrieve the value (no bound check is done here)
	 *
	 * @returns	Value founded.
	 */
	const T & getValueIt( typename Vector<T>::Iterator i ) const;
	/**
	 * @brief 	Gets value iterator
	 *
	 * @param 	i	Zero-based index of the.
	 *
	 * @returns	The value iterator.
	 */
	T & getValueIt( typename Vector<T>::Iterator i );

	/**
	 * @brief 	Set the Value associated with an direct access index (of type Size)
	 *
	 * @param 	i   	Iterator used to set the value (no bound check is done here)
	 * @param 	data	The data.
	 */
	void setValueI( const typename Vector<T>::Size i, const T & data );

	/**
	 * @brief 	Set the Value associated with an iterator
	 *
	 * @param 	i   	Iterator used to set the value.
	 * @param 	data	The data.
	 */
	void setValueIt( typename Vector<T>::Iterator i, const T & data );

	/**
	 * @brief 	get the last element of this vector
	 *
	 * @returns	Last element in the vector.
	 */
	const T & getLast() const;
	/**
	 * @brief 	Gets the last
	 *
	 * @returns	The last.
	 */
	T & getLast();

	/**
	 * @brief 	get the first element of this vector
	 *
	 * @returns	First element in the vector.
	 */
	const T & getFirst() const;
	/**
	 * @brief 	Gets the first
	 *
	 * @returns	The first.
	 */
	T & getFirst();


	/************************************************************************/
	/* LOGICAL                                                              */
	/**
	 * @brief 	Equality operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==( const Vector<T> & v ) const;
	/**
	 * @brief 	Inequality operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the parameters are not considered equivalent.
	 */
	bool operator!=( const Vector<T> & v ) const;
	/**
	 * @brief 	Less-than comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<( const Vector<T> & v ) const;
	/**
	 * @brief 	Greater-than comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>( const Vector<T> & v ) const;
	/**
	 * @brief 	Less-than-or-equal comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is less than or equal to the second.
	 */
	bool operator<=( const Vector<T> & v ) const;
	/**
	 * @brief 	Greater-than-or-equal comparison operator
	 *
	 * @param 	v	A Vector<T> to process.
	 *
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=( const Vector<T> & v ) const;

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
	/**
	 * @brief 	Assignment operator
	 *
	 * @param 	vector	The vector.
	 *
	 * @returns	A shallow copy of this object.
	 */
	Vector<T> & operator=( const Vector<T> & vector );

	/**
	 * @brief 	Move operator
	 *
	 * @param [in,out]	v	to be moved.
	 *
	 * @returns	reference to THIS.
	 */
	Vector<T> & operator=( Vector && v );

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
	void inserti( const typename Vector<T>::Size i, const T & v );

	/**
	 * @brief 	Fill the complete vector with the specified data.
	 *
	 * @param 	data	data to be copied in the whole vector.
	 */
	void fill( const T & data );

	/**
	 * @brief 	Get the size of this vector
	 *
	 * @returns	Number of datas of this vector.
	 */
	const typename Vector<T>::Size getSize() const;

	/**
	 * @brief 	Get the size of this vector in bytes
	 *
	 * @returns	const typename Vector<T>::Size of this vector in bytes.
	 */
	const typename Vector<T>::Size getSizeBytes() const;

	/**
	 * @brief 	Get the size of the inner buffer
	 *
	 * @returns	const typename Vector<T>::Size of the inner buffer.
	 */
	const typename Vector<T>::Size getMaxSize() const;

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
	 * @brief 	Get the datas of this vector
	 *
	 * @returns	Data buffer of this vector.
	 */
	const T * data() const;
	/**
	 * @brief 	Gets the data
	 *
	 * @returns	Null if it fails, else a pointer to a T.
	 */
	T * data();
	/**
	 * @brief 	Gets the data
	 *
	 * @returns	Null if it fails, else the data.
	 */
	const T * getData() const;
	/**
	 * @brief 	Gets the data
	 *
	 * @returns	Null if it fails, else the data.
	 */
	T * getData();

	/**
	 * @brief 	Test if a value exists in this vector
	 *
	 * @param 	value	The value.
	 *
	 * @returns	True if the value has been founded and false instead.
	 */
	bool exists( const T & value ) const;

	/**
	 * @brief 	Clear and re create this vector from a data table
	 *
	 * @tparam	C	Type of the c.
	 * @param 	dataTable	Table to be read.
	 * @param 	size	 	Number of elements in the table to be read.
	 */
	template<typename C>
	void createFromData( const C * dataTable, const typename Vector<T>::Size size );

	/**
	 * @brief 	Replace the first occurrence of the data
	 *
	 * @param 	search	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 *
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceFirst( const T & search, const T & data );

	/**
	 * @brief 	Replace ALL occurrences of the data searched
	 *
	 * @param 	search	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 *
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceAll( const T & search, const T & data );

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
	void eraseIndex( const typename Vector<T>::Size index );

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
	template<typename Func = Math::Logical::Less()>
	void sort( Func & functor = Func() );

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
	void copy( Vector<C> vector, typename Vector<C>::Size indexSrc, const typename Vector<T>::Size indexDest, typename Vector<C>::Size size );

	/**
	 * @brief 	Copy datas from a buffer into this vector
	 *
	 * @tparam	C	Type of the c.
	 * @param 	datas	 	The datas.
	 * @param 	indexDest	Index where to copy the datas.
	 * @param 	size	 	Number of elements to copy.
	 */
	template<typename C>
	void copy( const C * datas, const typename Vector<T>::Size indexDest, const typename Vector<T>::Size size );

	/**
	 * @brief 	Copy datas from a buffer into this vector
	 *
	 * @tparam	C	Type of the c.
	 * @param 	datas	The datas.
	 * @param 	size 	Number of elements to copy.
	 */
	template<typename C>
	void copy( const C * datas, const typename Vector<T>::Size size );

	/**
	 * @brief 	read from a file stream
	 *
	 * @param [in,out]	fileStream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( IO::SimpleFileStream * fileStream );

	/**
	 * @brief 	write this object as binary into a file stream
	 *
	 * @param [in,out]	fileStream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool write( IO::SimpleFileStream * fileStream ) const;

	/**
	 * @brief 	Search a data and retrieve the index
	 *
	 * @param 	data	Data to be searched.
	 *
	 * @returns	Index where the data has bee founded if founded. return Vector<T>::overflow instead.
	 */
	const typename Vector<T>::Size search( const T & data ) const;

	/************************************************************************/
	/* Static                                                               */
	/************************************************************************/

	/**
	 * @brief 	Copy datas from a buffer into an another one
	 *
	 * @tparam	C	Type of the c.
	 * @tparam	D	Type of the d.
	 * @param [in,out]	destinationBuffer	Where to copy the datas.
	 * @param 		  	sourceBuffer	 	From where to copy.
	 * @param 		  	size			 	Number of elements to copy.
	 */
	template<typename C, typename D>
	static void copy( C * destinationBuffer, const D * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @tparam	C	Type of the c.
	 * @tparam	D	Type of the d.
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	template<typename C, typename D>
	static void copy( C ** destinationBuffer, D * const * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( char * destinationBuffer, const char * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( unsigned char * destinationBuffer, const unsigned char * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( short * destinationBuffer, const short * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( unsigned short * destinationBuffer, const unsigned short * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( int * destinationBuffer, const int * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( unsigned int * destinationBuffer, const unsigned int * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( long * destinationBuffer, const long * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( unsigned long * destinationBuffer, const unsigned long * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( long long * destinationBuffer, const long long * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( unsigned long long * destinationBuffer, const unsigned long long * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( float * destinationBuffer, const float * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( double * destinationBuffer, const double * sourceBuffer, const typename Vector<T>::Size size );
	/**
	 * @brief 	Copies this object
	 *
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	static void copy( wchar_t * destinationBuffer, const wchar_t * sourceBuffer, const typename Vector<T>::Size size );

	/**
	 * @brief 	Gets the overflow
	 *
	 * @returns	The overflow.
	 */
	static const typename Vector<T>::Size overflow;
protected:
	/** @brief	Values that represent Constructors */
	enum class ctor {
		null
	};
	/**
	 * @brief 	Constructor
	 *
	 * @param 	parameter1	The first parameter.
	 */
	Vector( Vector<T>::ctor );

	/**
	 * @brief 	Quicksorts
	 *
	 * @tparam	Compare	Type of the compare.
	 * @param 	start	The start.
	 * @param 	end  	The end.
	 * @param 	func 	(Optional) The function.
	 */
	template<typename Compare>
	void quicksort( typename Vector<T>::Iterator start, typename Vector<T>::Iterator end, Compare func = Math::Logical::Less );

	/** @brief	Clears this object to its blank/initial state */
	void _clear();

	/**
	 * @brief 	Delete the old buffer; allocate a new one; Set the new maxSize;
	 *
	 * @param 	newMax	The new maximum.
	 */
	void _allocateNoNull( const typename Vector<T>::Size newMax );

	/**
	 * @brief 	allocate a new buffer; Set the new maxSize;
	 *
	 * @param 	newMax	The new maximum.
	 */
	void _allocateNoNullDelete( const typename Vector<T>::Size newMax );

	/**
	 * @brief 	Extend the actual buffer to be able to handle AT LEAST the newSizeNeeded (possible algo is *2), size has to be NOT null
	 *
	 * @param 	newSizeNeeded	The new size needed.
	 */
	void _extendBuffer( const typename Vector<T>::Size newSizeNeeded );

	/**
	 * @brief 	Swaps
	 *
	 * @param 	index1	The first index.
	 * @param 	index2	The second index.
	 */
	void swap( const typename Vector<T>::Size index1, const typename Vector<T>::Size index2 );
	/**
	 * @brief 	Swaps
	 *
	 * @param 	index1	The first index.
	 * @param 	index2	The second index.
	 */
	void swap( typename Vector<T>::Iterator index1, typename Vector<T>::Iterator index2 );

	/**
	 * @brief 	Assigns
	 *
	 * @param 	index1	The first index.
	 * @param 	index2	The second index.
	 */
	void assign( const typename Vector<T>::Size index1, const typename Vector<T>::Size index2 ); // index1 = index2
	/** @brief	Updates the iterators */
	void _updateIterators();

	/**
	 * @brief 	Erase a value at a specified index.
	 *
	 * @param 	index	Zero-based index.
	 */
	void _erasei( const typename Vector<T>::Size index );
	/**
	 * @brief 	Erase a value at a specified iterator.
	 *
	 * @param 	it	The iterator.
	 */
	void _eraseit( typename Vector<T>::Iterator it );

	/** Size of the Vector */
	typename Vector<T>::Size size;
	/** Size of the buffer */
	typename Vector<T>::Size maxSize;

	/** @brief	The data table */
	T * dataTable;

	/** Pointer to the last value */
	typename Vector<T>::Iterator iteratorEnd;
};


template<typename T>
std::ostream & operator <<( std::ostream & stream, const Vector<T> & vector );



#include "Vector.hpp"




