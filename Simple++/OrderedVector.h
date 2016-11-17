#pragma once

#include "Vector.h"


template<typename T, typename Compare = Math::Logical::Less>
class OrderedVector : private Vector<T> {
public:
	///@brief Constructor
	///@param compareFunc Functor with operator() overloaded with :
	///        bool operator()( const T & , const T & ) const;
	OrderedVector( const Compare & compareFunc = Compare() );
	OrderedVector( const OrderedVector & vector );
	OrderedVector( OrderedVector && v );

	~OrderedVector( void );

	using Vector<T>::operator[];

	OrderedVector<T, Compare> & operator=( const OrderedVector<T, Compare> & vector );
	OrderedVector<T, Compare> && operator=( OrderedVector<T, Compare> && vector );

	using Vector<T>::reserve;
	using Vector<T>::resize;
	using Vector<T>::getSize;
	using Vector<T>::size;
	using Vector<T>::swap;
	using Vector<T>::iterate;
	using Vector<T>::begin;
	using Vector<T>::end;
	using Vector<T>::getBegin;
	using Vector<T>::getEnd;
	using Vector<T>::isEmpty;

	///@brief Insert a new value and keep the buffer ordered
	///@see insertFast For multiple insert without access
	///@param data Data to be inserted
	void insert( const T & data );

	///@brief Insert a new value and do not keep the buffer ordered (it will be ordered at the next access)
	///@param data Data to be inserted
	void insertFast( const T & data );

	using Vector<T>::fill;
	using Vector<T>::eraseFirst;
	using Vector<T>::clear;
	using Vector<T>::reset;

	///@brief Search the index of a data using dichotomic search
	///@param data Data to searched
	///@return Index of the founded data or Vector<T>::overflow if nothing founded
	Size search( const T & data );

	///@brief search if a data exists using dichotomic search
	///@param data Data to be searched
	///@return True if something has been found or false instead.
	bool exists( const T & data );

	Size getNumEntries( const T & value );

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;


private:
	Compare sortFunction;
	bool isOrdered;

	void insert( Size index, const T & data );
	void _sort();

};





#include "OrderedVector.hpp"




