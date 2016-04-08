#pragma once

#include <fstream>
#include "SimpleLog.h"

class BasicSimpleIO {
public:
	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read(std::fstream * fileStream);

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write(std::fstream * fileStream) const;
};

