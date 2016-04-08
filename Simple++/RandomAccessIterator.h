#pragma once


#include <stdlib.h>


/*
template<typename T>
class RandomAccessIterator {
public:
	RandomAccessIterator(void);
	RandomAccessIterator(T * iterator);
	~RandomAccessIterator(void);

	std::size_t getElementSize() const;
	void next();
	void previous();

	RandomAccessIterator & operator++();
	RandomAccessIterator & operator+=(std::size_t size);

	RandomAccessIterator & operator--();
	RandomAccessIterator & operator-=(std::size_t size);

	T & getValue() const;
	T * getPointer() const;
private:
	T * iterator;
};

*/

#include "RandomAccessIterator.hpp"
