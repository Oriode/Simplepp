/**
 * @file	OrderedVector.h.
 *
 * @brief	Declares the ordered vector class
 */

#pragma once

#include "Vector.h"


 /**
  * @brief	An ordered vector.
  *
  * @tparam	T	   	Generic type parameter.
  * @tparam	Compare	Type of the compare.
  */
template<typename T, typename Compare = Math::Logical::Less>
class OrderedVector : private Vector<T> {
public:
	/**
	 * @brief	Constructor
	 *
	 * @param	compareFunc	(Optional) Functor with operator() overloaded with : bool operator()( const T & , const T & ) const;
	 */
	OrderedVector( const Compare & compareFunc = Compare() );
	/**
	 * @brief	Copy constructor
	 *
	 * @param	vector	The vector.
	 */
	OrderedVector( const OrderedVector & vector );
	/**
	 * @brief	Move constructor
	 *
	 * @param [in,out]	v	an OrderedVector to process.
	 */
	OrderedVector( OrderedVector && v );

	/** @brief	Destructor */
	~OrderedVector( void );

	/**
	 * @brief	Gets the []
	 *
	 * @returns	The [].
	 */
	using Vector<T>::operator[];

	/**
	 * @brief	Assignment operator
	 *
	 * @param	vector	The vector.
	 *
	 * @returns	A shallow copy of this object.
	 */
	OrderedVector<T, Compare> & operator=( const OrderedVector<T, Compare> & vector );
	/**
	 * @brief	Move assignment operator
	 *
	 * @param [in,out]	vector	The vector.
	 *
	 * @returns	A shallow copy of this object.
	 */
	OrderedVector<T, Compare> && operator=( OrderedVector<T, Compare> && vector );

	/** @brief	. */
	using Vector<T>::reserve;
	/** @brief	. */
	using Vector<T>::resize;
	/** @brief	. */
	using Vector<T>::getSize;
	/** @brief	. */
	using Vector<T>::size;
	/** @brief	. */
	using Vector<T>::swap;
	/** @brief	. */
	using Vector<T>::iterate;
	/** @brief	. */
	using Vector<T>::begin;
	/** @brief	. */
	using Vector<T>::end;
	/** @brief	. */
	using Vector<T>::getBegin;
	/** @brief	. */
	using Vector<T>::getEnd;
	/** @brief	. */
	using Vector<T>::isEmpty;

	/**
	 * @brief	Insert a new value and keep the buffer ordered
	 *
	 * @param	data	Data to be inserted.
	 *
	 * @sa	insertFast For multiple insert without access
	 */
	void insert( const T & data );

	/**
	 * @brief	Insert a new value and do not keep the buffer ordered (it will be ordered at the next access)
	 *
	 * @param	data	Data to be inserted.
	 */
	void insertFast( const T & data );

	/** @brief	. */
	using Vector<T>::fill;
	/** @brief	. */
	using Vector<T>::eraseFirst;
	/** @brief	. */
	using Vector<T>::clear;
	/** @brief	. */
	using Vector<T>::reset;

	/**
	 * @brief	Search the index of a data using dichotomic search
	 *
	 * @param	data	Data to searched.
	 *
	 * @returns	Index of the founded data or Vector<T>::overflow if nothing founded.
	 */
	Size search( const T & data );

	/**
	 * @brief	search if a data exists using dichotomic search
	 *
	 * @param	data	Data to be searched.
	 *
	 * @returns	True if something has been found or false instead.
	 */
	bool exists( const T & data );

	/**
	 * @brief	Gets number entries
	 *
	 * @param	value	The value.
	 *
	 * @returns	The number entries.
	 */
	Size getNumEntries( const T & value );

	/**
	 * @brief	read from a file stream
	 *
	 * @param [in,out]	fileStream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( IO::SimpleFileStream * fileStream );

	/**
	 * @brief	write this object as binary into a file stream
	 *
	 * @param [in,out]	fileStream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool write( IO::SimpleFileStream * fileStream ) const;


private:
	/** @brief	The sort function */
	Compare sortFunction;
	/** @brief	True if is ordered, false if not */
	bool isOrdered;

	/**
	 * @brief	Inserts
	 *
	 * @param	index	Zero-based index of the.
	 * @param	data 	The data.
	 */
	void insert( Size index, const T & data );
	void _sort();

};





#include "OrderedVector.hpp"




