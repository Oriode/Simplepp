#pragma once

#include "../SimpleLog.h"

namespace IO {

	///@brief This class is not intended to be used, @see BasicIO
	template<typename T = int>
	class BasicSimpleIOT {
	public:
		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write(Stream* stream) const;
	};

	using BasicSimpleIO = BasicSimpleIOT<int>;

}

#include "BasicSimpleIO.hpp"