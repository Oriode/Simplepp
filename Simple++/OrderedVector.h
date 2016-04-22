#pragma once

#include "Vector.h"


template<typename T, typename Compare = Logical::less<T>>
class OrderedVector : private Vector<T> {
public:
	OrderedVector(const Compare & compareFunc = Compare());
	OrderedVector(const OrderedVector & vector);
	OrderedVector(OrderedVector && v);

	~OrderedVector(void);

	//get a value and can assign something else
	using Vector<T>::operator[];

	//used to copy datas
	OrderedVector<T, Compare> & operator=(const OrderedVector<T, Compare> & vector);
	OrderedVector<T, Compare> && operator=(OrderedVector<T, Compare> && vector);


	//allocate the memory with the specified size (used method in push when the size isn't enough)
	using Vector<T>::reserve;
	using Vector<T>::resize;

	//return the size of this vector (push will increment it)
	using Vector<T>::getSize;
	using Vector<T>::size;

	using Vector<T>::swap;

	//Add a value and order the table
	void insert(const T & data);
	void insertFast(const T & data);

	//it will totally fill all the buffer with the specified value 
	using Vector<T>::fill;

	//delete a value and rearrange others data
	using Vector<T>::eraseFirst;


	//set size = 0
	using Vector<T>::clear;

	//Set size = 0 AND free memory
	using Vector<T>::reset;

	Size search(const T & data);
	bool exists(const T & data);

	Size getNumEntries(const T & value);

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read(std::fstream * fileStream);

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write(std::fstream * fileStream) const;


private:
	const Compare & sortFunction;
	bool isOrdered;

	void insert(Size index, const T & data);
	void _sort();

};






#include "OrderedVector.h"




