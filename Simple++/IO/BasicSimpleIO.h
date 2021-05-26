#pragma once

#include "../SimpleLog.h"
#include "SimpleFileStream.h"

namespace IO {

	///@brief This class is not intended to be used, @see BasicIO
	template<typename T = int>
	class BasicSimpleIOT {
	public:
		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(SimpleFileStream* fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(SimpleFileStream* fileStream) const;
	};

	using BasicSimpleIO = BasicSimpleIOT<int>;

}

#include "BasicSimpleIO.hpp"