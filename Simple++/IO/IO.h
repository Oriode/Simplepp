#pragma once

#include "../Log.h"
#include "../UTF8String.h"
#include "BasicIO.h"
#include "../OS/Path.h"
#include "FileStream.h"

namespace IO {

	///@brief write an object to the file, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own write method.
	///@param filePath file where to write.
	///@param object pointer to the object we wanna write.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool write( const OS::Path& filePath, const C* object, int verbose = 0 );

	///@brief read from a file to an object, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own read method.
	///@param filePath file where to read.
	///@param object pointer to the object we wanna read.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool read( const OS::Path& filePath, C* object, int verbose = 0 );

	///@brief open the file and read the complete file (from begin to end) and allocate a new data and copy data inside.
	///@param filePath file to read.
	///@param data [out] data buffer to be allocated and filled with the content of the file.
	///@return number of char read (-1) if an error has occurred. (Pointer will be set to NULL if failed, allocated otherwise.)
	template<typename T = int>
	static Size readToBuffer( const OS::Path& filePath, char** data, int verbose = 0 );

	///@brief Read the whole file and convert it to a String Object.
	///@template C Should be a BasicStringT.
	///@param filePath Path to be opened.
	///@param [out] stringP String to be modified.
	///@return number of char read (-1) if an error has occurred.
	template<typename C>
	Size readToString( const OS::Path& filePath, BasicString<C>* stringP, int verbose = 0 );
}


#include "IO.hpp"
