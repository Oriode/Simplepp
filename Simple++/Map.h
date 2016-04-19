#pragma once

#include <algorithm>
#include "Vector.h"

template<typename I, typename T>
class MapObject : public BasicSimpleIO {
public:
	MapObject();
	MapObject(const I & index, const T & value);
	~MapObject();

	const I & getIndex() const;
	void setIndex(const I & index);

	const T & getValue() const;
	void setValue(const T & value);

	/************************************************************************/
	/* LOGICAL                                                              */
	/************************************************************************/
	bool operator==(const MapObject & o) const;
	bool operator>(const MapObject & o) const;
	bool operator<(const MapObject & o) const;
	bool operator>=(const MapObject & o) const;
	bool operator<=(const MapObject & o) const;


	I index;
	T value;

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read(std::fstream * fileStream);

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write(std::fstream * fileStream) const;
};




template<typename I, typename T>
class Map : protected Vector<MapObject<I, T>> {
public:
	Map(void);
	Map(const Map & m);

	template<typename I2, typename T2>
	Map(const Map<I2, T2> & m);

	Map(Map && m);
	~Map(void);

	using Vector<MapObject<I, T>>::Size;

	using Vector<MapObject<I, T>>::reserve;
	using Vector<MapObject<I, T>>::allocate;
	using Vector<MapObject<I, T>>::resize;
	
	Map<I, T> & operator=(const Map<I, T> & map);
	template<typename I2, typename T2>
	Map<I, T> & operator=(const Map<I2, T2> & map);
	Map<I, T> & operator=(Map && m);

	///@brief Operator [] return the value for a specified index (can be NULL if the value is not found)
	///@param index Index
	///@return pointer to the value we are looking for (NULL if not found)
	T * operator[](const I & index);


	///@brief Operator [] return the value for a specified index (can be NULL if the value is not found)
	///@param index Index
	///@return pointer to the value we are looking for (NULL if not found)
	const T * operator[](const I & index) const;

	
	//T & operator[](RandomAccessIterator i);				//DISABLE FOR AMBIGOUS
	MapObject<I, T> & operator()(Size i);
	const MapObject<I, T> & operator()(Size i) const;


	/************************************************************************/
	/* GET INDEX                                                            */
	/************************************************************************/
	I & getIndexi( Size i );
	const I & getIndexi( Size i ) const;
	I & getIndexit(RandomAccessIterator i);
	const I & getIndexit(RandomAccessIterator i) const;

	/************************************************************************/
	/* SET INDEX                                                            */
	/************************************************************************/
	void setIndexi(Size i, const I & index);
	void setIndexit(RandomAccessIterator i, const T & index);

	/************************************************************************/
	/* SET VALUE                                                            */
	/************************************************************************/
	void setValuei(Size i, const T & value);
	void setValueit(RandomAccessIterator i, const T & value);


	/************************************************************************/
	/* GET VALUE                                                            */
	/************************************************************************/
	T & getValueit(RandomAccessIterator i);
	const T & getValueit(RandomAccessIterator i) const;

	T & getValuei(Size i);
	const T & getValuei(Size i) const;
	T * getValue(const I & index);


	//retrieve the last data in the map
	using Vector<MapObject<I, T>>::getLast;

	const T & getLastValue() const;
	T & getLastValue();

	const T & getLastIndex() const;
	T & getLastIndex();

	

	void set( Size i, const I & index, const T & data);
	void insert(const I & index, const T & data);

	using Vector<MapObject<I, T>>::pop;

	//return the size of this vector (push will increment it)
	using Vector<MapObject<I, T>>::getSize;
	using Vector<MapObject<I, T>>::size;

	//it will totally fill all the buffer with the specified value 
	using Vector<MapObject<I, T>>::fill;
	using Vector<MapObject<I, T>>::reset;
	using Vector<MapObject<I, T>>::clear;



	//test if a specified value exists in the table
	using Vector<MapObject<I, T>>::exists;

	bool existsIndex(const I & index) const;

	using Vector<MapObject<I, T>>::begin;
	using Vector<MapObject<I, T>>::end;
	using Vector<MapObject<I, T>>::getBegin;
	using Vector<MapObject<I, T>>::getEnd;

	void eraseFirst(const T & data);
	void eraseAll(const T & data);

	void eraseIndexFirst(const I & index);
	void eraseIndexAll(const I & index);

	Size searchIndex(const I & index) const;
protected:
	enum ctor { null };
	Map(ctor);


	template<typename Compare>
	void _sort(Compare func);

	template<typename Compare>
	void _quicksort(RandomAccessIterator start, RandomAccessIterator end, Compare func = Logical::less<I>);
};


template<typename I, typename T>
std::ostream & operator <<(std::ostream & stream, const Map<I, T> & map);


#include "Map.hpp"

