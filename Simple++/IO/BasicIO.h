#pragma once



#include "BasicSimpleIO.h"

namespace IO {

	///@brief BasicIO is the base Class for every Class that can be read/write from a file.
	template<typename T = int>
	class BasicIOT {
	public:

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read(Stream* stream);

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write(Stream* stream) const;


	};

	using BasicIO = BasicIOT<int>;

}





#include "BasicIO.hpp"
