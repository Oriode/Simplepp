#pragma once




#include "Math.h"
#include "Vector.h"
#include "OrderedMap.hpp"



template<typename F, typename I, unsigned int size = 1000>
class CoordinateSystem {
public:
	CoordinateSystem();
	~CoordinateSystem();



	CoordinateChunk<F, I, size> * insertChunk(const Vec3<I> & position) {








	}







private:
	CoordinateChunk<F,I,size> * zeroChunk;


};


#include "CoordinateSystem.hpp"
