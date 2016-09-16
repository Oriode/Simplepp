#pragma once


#include "Map.h"


template<typename I, typename T, typename Compare = Math::Logical::Less>
class OrderedMap : protected Map<I, T> {
public:
	OrderedMap( Compare & compareFunc = Compare() );
	OrderedMap( const OrderedMap & map );
	OrderedMap( OrderedMap && map );


	~OrderedMap( void );


	///@brief Operator [] return the value for a specified index (can be NULL if the value is not found)
	///@param index Index
	///@return pointer to the value we are looking for (NULL if not found)
	T * operator[]( const I & index );


	///@brief Operator [] return the value for a specified index (can be NULL if the value is not found)
	///@param index Index
	///@return pointer to the value we are looking for (NULL if not found)
	const T * operator[]( const I & index ) const;


	using Map<I, T>::Size;
	using Map<I, T>::operator();
	using Map<I, T>::getValuei;
	using Map<I, T>::getValueit;
	using Map<I, T>::getIndexi;
	using Map<I, T>::getIndexit;

	using Map<I, T>::exists;
	using Map<I, T>::getBegin;
	using Map<I, T>::getEnd;
	using Map<I, T>::end;
	using Map<I, T>::begin;

	using Map<I, T>::clear;
	using Map<I, T>::reset;
	using Map<I, T>::reserve;
	using Map<I, T>::getSize;
	using Map<I, T>::size;
	using Map<I, T>::pop;
	using Map<I, T>::fill;
	using Map<I, T>::eraseFirst;
	using Map<I, T>::eraseAll;

	T * getValue( const I & index );
	const T * getValue( const I & index ) const;


	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/************************************************************************/
	OrderedMap & operator=( const OrderedMap & map );
	OrderedMap & operator=( OrderedMap && map );

	void eraseIndex( const I & index );

	//Add a value and order the table
	void insert( const I & index, const T & data );
	void insertFast( const I & index, const T & data );


	bool existsIndex( const I & index );
	Size searchIndex( const I & index );
	Size getNumEntriesIndex( const I & index );


	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;

private:
	Compare & sortFunction;
	bool isOrdered;

	void inserti( Size i, const I & index, const T & data );
	void _sort();
};
template<typename I, typename T, typename Compare>
std::ostream & operator <<( std::ostream & stream, const OrderedMap<I, T, Compare> & map );


#include "OrderedMap.hpp"



