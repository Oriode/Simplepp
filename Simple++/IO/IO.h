#pragma once

#include "../Log.h"
#include "../UTF8String.h"
#include "SimpleIO.h"
#include "BasicIO.h"

class IO : public SimpleIO {
public:
	using SimpleIO::write;
	using SimpleIO::read;

	///@brief write an object to the file, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own write method.
	///@param fileName file where to write.
	///@param object pointer to the object we wanna write.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool write( const String & fileName, const C * object );

	///@brief read from a file to an object, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own read method.
	///@param fileName file where to read.
	///@param object pointer to the object we wanna read.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool read( const String & fileName, C * object );


	///@brief read the complete file stream (from begin to end) and allocate a new data and copy data inside.
	///@param fileStream file stream to read.
	///@param data [out] data buffer to be allocated and filled with the content of the file stream.
	///@return number of char read.
	static size_t readToBuffer( std::fstream * fileStream, char ** data );

	///@brief open the file and read the complete file (from begin to end) and allocate a new data and copy data inside.
	///@param fileName file to read.
	///@param data [out] data buffer to be allocated and filled with the content of the file.
	///@return number of char read (-1) if an error has occurred.
	static size_t readToBuffer( const String & fileName, char ** data );
};


#include "IO.hpp"
