#pragma once

#include "Log.h"
#include "String.h"
#include "SimpleIO.h"

class IO : public SimpleIO {
public:

	///@brief read the complete file stream (from begin to end) and allocate a new data and copy data inside.
	///@param fileStream file stream to read.
	///@param data [out] data buffer to be allocated and filled with the content of the file stream.
	///@return number of char read.
	static size_t readToBuffer( std::fstream * fileStream, char ** data );

	///@brief open the file and read the complete file (from begin to end) and allocate a new data and copy data inside.
	///@param fileName file to read.
	///@param data [out] data buffer to be allocated and filled with the content of the file.
	///@return number of char read (-1) if an error has occurred.
	static size_t readToBuffer( const WString & fileName, char ** data );
};


#include "IO.hpp"
