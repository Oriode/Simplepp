#pragma once



#include "BasicSimpleIO.h"
#include "../Log.h"
#include "../String.h"

namespace IO {

	///@brief BasicIO is the base Class for every Class that can be read/write from a file.
	template<typename T = int>
	class BasicIOT : public virtual BasicSimpleIO {
	public:




	};

	using BasicIO = BasicIOT<int>;

}





#include "BasicIO.hpp"
