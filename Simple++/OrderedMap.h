#pragma once


#include "Map.h"


template<typename I, typename T, typename Compare = Logical::less<I>>
class OrderedMap : protected Map<I,T>{
public:
	OrderedMap(void);
	OrderedMap(const OrderedMap & map);
	OrderedMap(OrderedMap && map);
	template<typename I2, typename T2, typename Compare2>
	OrderedMap(const OrderedMap<I2, T2, Compare2> & map);

	~OrderedMap(void);

	T & operator[](const I & index);
	const T & operator[](const I & index) const;


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

	//set size = 0
	using Map<I, T>::clear;
	//Set size = 0 AND free memory
	using Map<I, T>::reset;

	//allocate the memory with the specified size (used method in push when the size isn't enough)
	using Map<I, T>::reserve;
	//return the size of this vector (push will increment it)
	using Map<I, T>::getSize;
	using Map<I, T>::size;
	using Map<I, T>::pop;
	//it will totally fill all the buffer with the specified value 
	using Map<I, T>::fill;
	//delete a value and rearrange others data
	using Map<I, T>::eraseFirst;
	using Map<I, T>::eraseAll;

	T * getValue( const I & index );
	const T * getValue(const I & index) const;


	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/************************************************************************/
	OrderedMap & operator=(const OrderedMap & map);
	template<typename I2, typename T2, typename Compare2>
	OrderedMap & operator=(const OrderedMap<I2, T2, Compare2> & map);
	OrderedMap & operator=(OrderedMap && map);

	void eraseIndex(const I & index);

	//Add a value and order the table
	void insert(const I & index, const T & data);
	void insertFast( const I & index, const T & data);


	bool existsIndex(const I & index);
	Size searchIndex(const I & index);
	Size getNumEntriesIndex(const I & index);


	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read(std::fstream * fileStream);

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write(std::fstream * fileStream) const;

private:
	Compare sortFunction;
	bool isOrdered;

	void inserti(Size i, const I & index, const T & data);
	void _sort();
};
template<typename I, typename T, typename Compare>
std::ostream & operator <<(std::ostream & stream, const OrderedMap<I, T, Compare> & map);


#include "OrderedMap.hpp"



