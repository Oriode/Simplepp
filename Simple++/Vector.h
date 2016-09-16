#pragma once


#include <utility>
#include <algorithm>
#include <ostream>



#include "Logical.h"
#include "Utility.h"
#include "SimpleLog.h"
#include "BasicSimpleIO.h"
#include "SimpleIO.h"

template<typename T = int>
class Vector : public BasicSimpleIO { 
public:
	typedef T * RandomAccessIterator;
	typedef T ElemType;
	typedef unsigned long long Size;


	Vector(void);
	Vector(Size size, Size maxSize);
	Vector(Size maxSize);

	Vector(const Vector & vector);
	template<typename C>
	Vector(const Vector<C> & vector);

	Vector(Vector && v);



	template<typename C, size_t N>
	Vector(const C (&data)[N]);

	template<typename C>
	Vector(const C * data, Size maxSize);

	template<typename C>
	Vector(const C * data, Size size, Size maxSize);


	~Vector(void);


	bool iterate(RandomAccessIterator * it, ElemType ** e);

	//allocate the memory with the specified size and copy old datas (used method in push when the size isn't enough)
	void reserve(Size newMax);

	//allocate the new buffer size (without copying the olds datas and update the size)
	void allocate(Size newMax);

	//Set a new size, and reallocate and copy old datas if necessary.
	void resize(Size newSize);

	//get a value and can assign something else
	const T & operator[](Size index) const;
	T & operator[](Size index);




	/*	DISABLED FOR AMBIGOUS 
	const T & operator[]( RandomAccessIterator i) const;
	T & operator[]( RandomAccessIterator i);
	*/

	T & getValuei(Size i);
	const T & getValuei(Size i) const;
	T & getValueit(RandomAccessIterator i);
	const T & getValueit(RandomAccessIterator i) const;


	void setValuei(Size i, const T & data);
	void setValueit(RandomAccessIterator i, const T & data);

	RandomAccessIterator getBegin() const;
	RandomAccessIterator getEnd() const;


	RandomAccessIterator begin() const;
	RandomAccessIterator end() const;



	/************************************************************************/
	/* LOGICAL                                                                     */
	/************************************************************************/
	bool operator==(const Vector<T> & v) const;
	bool operator!=(const Vector<T> & v) const;
	bool operator<(const Vector<T> & v) const;
	bool operator>(const Vector<T> & v) const;
	bool operator<=(const Vector<T> & v) const;
	bool operator>=(const Vector<T> & v) const;

	bool operator==(const T & v) const;
	bool operator!=(const T & v) const;
	bool operator<(const T & v) const;
	bool operator>(const T & v) const;
	bool operator<=(const T & v) const;
	bool operator>=(const T & v) const;


	//used to copy data
	Vector<T> & operator=(const Vector<T> & vector);

	Vector<T> & operator=(Vector && v);


	template<typename C>
	Vector<T> & operator=(const Vector<C> & vector);


	Vector<T> & operator+=(const Vector<T> & vector);


	///@brief insert a new data in the vector getSize() will be incremented and the memory auto managed.
	///@param data data to be inserted.
	void push(const T & data);

	///@brief retrieve the last inserted object and decrement getSize();
	///@return last inserted data
	T & pop();

	///@brief Fill the complete vector with the specified data.
	///@param data data to be copied in the whole vector.
	void fill(const T & data);

	//return the size of this vector (push will increment it)
	Size getSize() const;

	//get the size of the datas in bytes
	Size getSizeBytes() const;

	//return the total allocated size
	Size getMaxSize() const;

	//set size = 0
	void clear();

	//Set size = 0 AND free memory
	void reset();

	const T & getLast() const;

	T & getLast();


	const T & getFirst() const;

	T & getFirst();


	//get the data table
	const T * data() const;
	T * data();

	const T * getData() const;
	T * getData();

	

	//test if a specified value exists in the table
	bool exists(const T & value) const;


	
	void createFromData(const T * dataTable, Size size);

	template<typename C>
	void createFromData(const C * dataTable, Size size);


	//replace first identical data by parameter
	void replaceFirst(const T & search, const T & data);
	void replaceAll(const T & search, const T & data);

	//delete a value and rearrange others data
	void eraseFirst(const T & value);
	void eraseAll(const T & value);

	void eraseIndex(Size index);

	//ordering methods
	void sortDesc();
	void sortAsc();

	///@brief sort the elements of this vector using the quicksort algorithm
	///@param functor Functor with operator () overloaded with :
	///				bool operator()(const T & v1, const T & v2) const;
	template<typename Func>
	void sort( Func functor );

	//Copy from the input vector to this one
	void copy(Vector vector, Size indexSrc, Size indexDest, Size size);

	template<typename C>
	void copy(Vector<C> vector, typename Vector<C>::Size indexSrc, Size indexDest, typename Vector<C>::Size size);

	template<typename C>
	void copy(const C * datas, Size index, Size size);

	template<typename C>
	void copy(const C * datas, Size size);

	//Static copy
	template<typename C, typename D>
	static void copy(C * destinationBuffer, const D * sourceBuffer, const Size & size);
	static void copy(char * destinationBuffer, const char * sourceBuffer, const Size & size);
	static void copy(unsigned char * destinationBuffer, const unsigned char * sourceBuffer, const Size & size);
	static void copy(short * destinationBuffer, const short * sourceBuffer, const Size & size);
	static void copy(unsigned short * destinationBuffer, const unsigned short * sourceBuffer, const Size & size);
	static void copy(int * destinationBuffer, const int * sourceBuffer, const Size & size);
	static void copy(unsigned int * destinationBuffer, const unsigned int * sourceBuffer, const Size & size);
	static void copy(long * destinationBuffer, const long * sourceBuffer, const Size & size);
	static void copy(unsigned long * destinationBuffer, const unsigned long * sourceBuffer, const Size & size);
	static void copy(long long * destinationBuffer, const long long * sourceBuffer, const Size & size);
	static void copy(unsigned long long * destinationBuffer, const unsigned long long * sourceBuffer, const Size & size);
	static void copy(float * destinationBuffer, const float * sourceBuffer, const Size & size);
	static void copy(double * destinationBuffer, const double * sourceBuffer, const Size & size);
	static void copy(wchar_t * destinationBuffer, const wchar_t * sourceBuffer, const Size & size);



	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read(std::fstream * fileStream);

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write(std::fstream * fileStream) const;


	Size search(const T & data) const;

	template<typename Compare>
	void quicksort(RandomAccessIterator start, RandomAccessIterator end, Compare func = Math::Logical::Less);

	static Size overflow;
protected:
	enum ctor { null };
	Vector(ctor);





	//Same as allocate(Size) but without the test if the size = 0
	void _allocateNoNull(const Size & newMax);

	//Same as allocate(Size) but without the delete of the old buffer and without the test if the size = 0
	void _allocateNoNullDelete(const Size & newMax);

	//Extend the actual buffer to be able to handle AT LEAST the newSizeNeeded (possible algo is *2), size has to be NOT null
	void _extendBuffer(const Size & newSizeNeeded);

	void swap(Size index1, Size index2);
	void swap(RandomAccessIterator index1, RandomAccessIterator index2);

	void assign(Size index1, Size index2); // index1 = index2
	void _updateIterators();

	void _erasei(Size index);
	void _eraseit(RandomAccessIterator it);


	Size size;
	Size maxSize;
	T * dataTable;
	RandomAccessIterator iteratorEnd;		//Pointer to the last value
};




template<typename T>
std::ostream & operator <<(std::ostream & stream, const Vector<T> & vector);



#include "Vector.hpp"




