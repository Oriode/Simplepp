#pragma once


#include <utility>
#include <algorithm>
#include <ostream>



#include "Math/Logical.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "IO/BasicSimpleIO.h"
#include "IO/SimpleIO.h"


template<typename T>
using RandomAccessIterator = T *;



template<typename T = int>
class Vector : public BasicSimpleIO {
public:
	typedef RandomAccessIterator<T> Iterator;
	typedef T ElemType;
	typedef unsigned long long Size;


	Vector( void );
	Vector( typename Vector<T>::Size size, typename Vector<T>::Size maxSize );
	Vector( typename Vector<T>::Size maxSize );

	Vector( const Vector & vector );
	template<typename C>
	Vector( const Vector<C> & vector );

	///@brief Move Constructor
	///@param v Vector to be moved
	Vector( Vector && v );



	template<typename C, size_t N>
	Vector( const C( &data )[N] );

	template<typename C>
	Vector( const C * data, typename Vector<T>::Size maxSize );

	template<typename C>
	Vector( const C * data, typename Vector<T>::Size size, typename Vector<T>::Size maxSize );


	///@brief Constructor from two iterators, Begin and End
	///@param Pointer to the first element to copy in this vector
	///@param Pointer next to the last element to copy in this vector
	template<typename C>
	Vector( RandomAccessIterator<C> beginIt, typename RandomAccessIterator<C> endIt );

	~Vector( void );

	

	///@brief allocate the memory with the specified size and copy old datas (used method in push when the size isn't enough)
	///@param newMax New size of the inner buffer (the size won't be changed)
	void reserve( typename Vector<T>::Size newMax );

	///@brief allocate the new buffer size (without copying the olds datas and update the size)
	///@param newMax New size of the inner buffer (the size won't be changed and the data wont be copied)
	void allocate( typename Vector<T>::Size newMax );

	///@brief Set a new size, and reallocate and copy old datas if necessary.
	///@param newSize New size to be set for the vector
	void resize( typename Vector<T>::Size newSize );


	/************************************************************************/
	/* Iterations                                                           */
	/************************************************************************/
	///@brief Get the Begin Iterator
	///@return Begin Iterator
	typename Vector<T>::Iterator getBegin() const;

	///@brief Get the End Iterator
	///@return End Iterator
	typename Vector<T>::Iterator getEnd() const;

	///@brief alias of getBegin()
	typename Vector<T>::Iterator begin() const;

	///@brief alias of getEnd()
	typename Vector<T>::Iterator end() const;

	///@brief iterate ONE time the iterator and return if there is still data
	///@return it in out Iterator to iterate
	///@return If the iterator can return data
	bool iterate( typename Vector<T>::Iterator * it ) const;

	///@brief Iterate ONE time and set the pointer to the pointer of the data retrieved
	///@param it in out Iterator to iterate
	///@param v out Pointer to a pointer to the value retrieved
	///@return True if a data has been retrieved or False if the end has been reached
	bool iterate( typename Vector<T>::Iterator * it, ElemType ** v ) const;

	///@brief Iterate ONE time and set the pointer to the pointer of the data retrieved
	///@param it in out Iterator to iterate
	///@param v out Pointer to a pointer to the value retrieved
	///@param testFunctor Functor to check a condition before incrementing the iterator
	///								bool operator()( const ElemType & e );
	///@return True if a data has been retrieved or False if the end has been reached or false is the functor return false
	template<typename TestFunctor>
	bool iterate( typename Vector<T>::Iterator * it, ElemType ** v, TestFunctor & testFunctor ) const;

	/************************************************************************/
	/* Access                                                               */
	/************************************************************************/

	///@brief Get a value and can assign something else
	///@param index Index
	///@return Value founded
	const T & operator[]( typename Vector<T>::Size index ) const;
	T & operator[]( typename Vector<T>::Size index );

	///@brief Get the Value associated with an direct access index (of type typename Vector<T>::Size)
	///@param i Iterator used to retrieve the value (no bound check is done here)
	///@return Value founded
	const T & getValueI( typename Vector<T>::Size i ) const;
	T & getValueI( typename Vector<T>::Size i );

	///@brief Get the Value associated with an iterator
	///@param it Iterator used to retrieve the value (no bound check is done here)
	///@return Value founded
	const T & getValueIt( typename Vector<T>::Iterator i ) const;
	T & getValueIt( typename Vector<T>::Iterator i );

	///@brief Set the Value associated with an direct access index (of type Size)
	///@param i Iterator used to set the value (no bound check is done here)
	///@return Value to be set
	void setValueI( typename Vector<T>::Size i, const T & data );

	///@brief Set the Value associated with an iterator
	///@param it Iterator used to set the value
	///@return Value to be set
	void setValueIt( typename Vector<T>::Iterator i, const T & data );

	///@brief get the last element of this vector
	///@return Last element in the vector
	const T & getLast() const;
	T & getLast();

	///@brief get the first element of this vector
	///@return First element in the vector
	const T & getFirst() const;
	T & getFirst();


	/************************************************************************/
	/* LOGICAL                                                              */
	/************************************************************************/
	bool operator==( const Vector<T> & v ) const;
	bool operator!=( const Vector<T> & v ) const;
	bool operator<( const Vector<T> & v ) const;
	bool operator>( const Vector<T> & v ) const;
	bool operator<=( const Vector<T> & v ) const;
	bool operator>=( const Vector<T> & v ) const;

	bool operator==( const T & v ) const;
	bool operator!=( const T & v ) const;
	bool operator<( const T & v ) const;
	bool operator>( const T & v ) const;
	bool operator<=( const T & v ) const;
	bool operator>=( const T & v ) const;



	///@brief Copy Operator
	///@param vector Vector to be copied
	///@return reference to THIS
	template<typename C>
	Vector<T> & operator=( const Vector<C> & vector );
	Vector<T> & operator=( const Vector<T> & vector );

	///@brief Move operator
	///@param vector to be moved
	///@return reference to THIS
	Vector<T> & operator=( Vector && v );


	Vector<T> & operator+=( const Vector<T> & vector );


	///@brief insert a new data in the vector getSize() will be incremented and the memory auto managed.
	///@param data data to be inserted.
	///@return Pointer to the data just inserted
	T * push( const T & data );

	///@brief retrieve the last inserted object and decrement getSize() and decrement size
	///@return last inserted data
	T & pop();


	///@brief Insert a value a the specified index
	///@param i Index
	///@param v Value to insert
	void inserti( typename Vector<T>::Size i, const T & v );

	///@brief Fill the complete vector with the specified data.
	///@param data data to be copied in the whole vector.
	void fill( const T & data );

	///@brief Get the size of this vector
	///@return Number of datas of this vector
	typename Vector<T>::Size getSize() const;

	///@brief Get the size of this vector in bytes
	///@return typename Vector<T>::Size of this vector in bytes
	typename Vector<T>::Size getSizeBytes() const;

	///@brief Get the size of the inner buffer 
	///@return typename Vector<T>::Size of the inner buffer
	typename Vector<T>::Size getMaxSize() const;

	///@brief Set the size = 0
	void clear();

	///@brief Set the size = 0 and clear the memory
	void reset();

	///@brief Get if the Vector is empty of not
	///@return True if the Vector is empty, false otherwise.
	bool isEmpty() const;

	///@brief Get the datas of this vector
	///@return Data buffer of this vector
	const T * data() const;
	T * data();
	const T * getData() const;
	T * getData();

	///@brief Test if a value exists in this vector
	///@return True if the value has been founded and false instead
	bool exists( const T & value ) const;

	///@brief Clear and re create this vector from a data table
	///@param dataTable Table to be read
	///@param size Number of elements in the table to be read
	template<typename C>
	void createFromData( const C * dataTable, typename Vector<T>::Size size );

	///@brief Replace the first occurrence of the data
	///@param search Data to be searched
	///@param data Data to be set instead
	///@return True if something has been replaced, False otherwise
	bool replaceFirst( const T & search, const T & data );

	///@brief Replace ALL occurrences of the data searched
	///@param search Data to be searched
	///@param data Data to be set instead
	///@return True if something has been replaced, False otherwise
	bool replaceAll( const T & search, const T & data );

	///@brief Erase the first occurrence and rearrange the data
	///@param value Value to be searched and erased
	///@return True if something has been deleted, False otherwise
	bool eraseFirst( const T & value );

	///@brief Erase all the occurrences and rearrange the data
	///@param value Value to be searched and erased
	///@return True if something has been deleted, False otherwise
	bool eraseAll( const T & value );

	///@brief Erase the data at the specified index and rearrange the data
	///@param index Index to be erased
	void eraseIndex( typename Vector<T>::Size index );

	///@brief Quicksort the vector using the operator>()
	void sortDesc();

	///@brief Quicksort the vector using the operator<()
	void sortAsc();

	///@brief sort the elements of this vector using the quicksort algorithm
	///@param functor Functor with operator () overloaded with :
	///				bool operator()(const T &, const T &) const;
	template<typename Func = Math::Logical::Less>
	void sort( Func & functor = Func() );

	///@brief Copy a part of an another vector into this one
	///@param vector Vector to be copied
	///@param indexSrc Source index where to begin the copy
	///@param indexDst Destination index where to begin the copy
	///@param size Number of elements to copy
	template<typename C>
	void copy( Vector<C> vector, typename Vector<C>::Size indexSrc, typename Vector<T>::Size indexDest, typename Vector<C>::Size size );

	///@brief Copy datas from a buffer into this vector
	///@param indexDest Index where to copy the datas
	///@param size Number of elements to copy
	template<typename C>
	void copy( const C * datas, typename Vector<T>::Size indexDest, typename Vector<T>::Size size );

	///@brief Copy datas from a buffer into this vector
	///@param size Number of elements to copy
	template<typename C>
	void copy( const C * datas, typename Vector<T>::Size size );

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;

	///@brief Search a data and retrieve the index
	///@param data Data to be searched
	///@return Index where the data has bee founded if founded. return Vector<T>::overflow instead
	typename Vector<T>::Size search( const T & data ) const;

	/************************************************************************/
	/* Static                                                               */
	/************************************************************************/

	///@brief Copy datas from a buffer into an another one
	///@param destinationBuffer Where to copy the datas
	///@param sourceBuffer From where to copy
	///@param size Number of elements to copy
	template<typename C, typename D>
	static void copy( C * destinationBuffer, const D * sourceBuffer, typename Vector<T>::Size size );
	template<typename C, typename D>
	static void copy( C ** destinationBuffer, D * const * sourceBuffer, typename Vector<T>::Size size );
	static void copy( char * destinationBuffer, const char * sourceBuffer, typename Vector<T>::Size size );
	static void copy( unsigned char * destinationBuffer, const unsigned char * sourceBuffer, typename Vector<T>::Size size );
	static void copy( short * destinationBuffer, const short * sourceBuffer, typename Vector<T>::Size size );
	static void copy( unsigned short * destinationBuffer, const unsigned short * sourceBuffer, typename Vector<T>::Size size );
	static void copy( int * destinationBuffer, const int * sourceBuffer, typename Vector<T>::Size size );
	static void copy( unsigned int * destinationBuffer, const unsigned int * sourceBuffer, typename Vector<T>::Size size );
	static void copy( long * destinationBuffer, const long * sourceBuffer, typename Vector<T>::Size size );
	static void copy( unsigned long * destinationBuffer, const unsigned long * sourceBuffer, typename Vector<T>::Size size );
	static void copy( long long * destinationBuffer, const long long * sourceBuffer, typename Vector<T>::Size size );
	static void copy( unsigned long long * destinationBuffer, const unsigned long long * sourceBuffer, typename Vector<T>::Size size );
	static void copy( float * destinationBuffer, const float * sourceBuffer, typename Vector<T>::Size size );
	static void copy( double * destinationBuffer, const double * sourceBuffer, typename Vector<T>::Size size );
	static void copy( wchar_t * destinationBuffer, const wchar_t * sourceBuffer, typename Vector<T>::Size size );

	static typename Vector<T>::Size overflow;
protected:
	enum ctor { null };
	Vector( ctor );

	template<typename Compare>
	void quicksort( typename Vector<T>::Iterator start, typename Vector<T>::Iterator end, Compare func = Math::Logical::Less );

	void _clear();

	//Same as allocate(typename Vector<T>::Size) but without the test if the size = 0
	void _allocateNoNull( typename Vector<T>::Size newMax );

	//Same as allocate(typename Vector<T>::Size) but without the delete of the old buffer and without the test if the size = 0
	void _allocateNoNullDelete( typename Vector<T>::Size newMax );

	//Extend the actual buffer to be able to handle AT LEAST the newSizeNeeded (possible algo is *2), size has to be NOT null
	void _extendBuffer( typename Vector<T>::Size newSizeNeeded );

	void swap( typename Vector<T>::Size index1, typename Vector<T>::Size index2 );
	void swap( typename Vector<T>::Iterator index1, typename Vector<T>::Iterator index2 );

	void assign( typename Vector<T>::Size index1, typename Vector<T>::Size index2 ); // index1 = index2
	void _updateIterators();

	void _erasei( typename Vector<T>::Size index );
	void _eraseit( typename Vector<T>::Iterator it );


	typename Vector<T>::Size size;
	typename Vector<T>::Size maxSize;
	T * dataTable;
	typename Vector<T>::Iterator iteratorEnd;		//Pointer to the last value
};










template<typename T>
std::ostream & operator <<( std::ostream & stream, const Vector<T> & vector );



#include "Vector.hpp"




