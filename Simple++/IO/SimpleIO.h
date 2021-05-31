#pragma once

#include "../SimpleLog.h"
#include "BasicSimpleIO.h"
#include "SimpleFileStream.h"

namespace IO {

	///@brief write an object inside the file stream, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own write method.
	///@param fileStream file stream where to write.
	///@param object pointer to the object we wanna write.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool write(SimpleFileStream * fileStream, const C * object);

	///@brief read from a file stream to an object, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own read method.
	///@param fileStream file stream where to read.
	///@param object pointer to the object we wanna read.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool read(SimpleFileStream * fileStream, C * object);


	///@brief write a table of objects inside the file stream, this function will automatically test for each object inherit from BasicIO themselves and then call there own write method.
	///@param fileStream file stream where to write.
	///@param buffer pointer to the table of objects we wanna write.
	///@param size number of elements in the table.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool writeBuffer(SimpleFileStream * fileStream, const C * buffer, size_t size);

	///@brief read from a file stream to a table of objects, this function will automatically test for each object inherit from BasicIO themselves and then call there own write method.
	///@param fileStream file stream where to read.
	///@param buffer pointer to the table of objects we wanna read.
	///@param size number of elements in the table.
	///@return Boolean if the result is a success or not.
	template<typename C>
	static bool readBuffer(SimpleFileStream * fileStream, C * buffer, size_t size);

	template<typename C>
	static bool _writeObject(SimpleFileStream * fileStream, const C * buffer, const BasicSimpleIO * b);

	template<typename C>
	static bool _writeObject(SimpleFileStream * fileStream, const C * buffer, ...);


	template<typename C>
	static bool _writeBuffer(SimpleFileStream * fileStream, const C * buffer, size_t size, const BasicSimpleIO * b);

	template<typename C>
	static bool _writeBuffer(SimpleFileStream * fileStream, const C * buffer, size_t size, ...);





	template<typename C>
	static bool _readObject(SimpleFileStream * fileStream, C * buffer, BasicSimpleIO * b);

	template<typename C>
	static bool _readObject(SimpleFileStream * fileStream, C * buffer, ...);

	template<typename C>
	static bool _readBuffer(SimpleFileStream * fileStream, C * buffer, size_t size, BasicSimpleIO * b);

	template<typename C>
	static bool _readBuffer(SimpleFileStream * fileStream, C * buffer, size_t size, ...);

}


#include "SimpleIO.hpp"

