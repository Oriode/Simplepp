#pragma once

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

	///@brief write an object inside the file stream, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own write method.
	///@param stream file stream where to write.
	///@param object pointer to the object we wanna write.
	///@return Boolean if the result is a success or not.
	template<typename Stream, typename C>
	static bool write(Stream* stream, const C* object);

	///@brief read from a file stream to an object, this function will automatically test if the sent object (by pointer) inherit from BasicIO himself and then call his own read method.
	///@param stream file stream where to read.
	///@param object pointer to the object we wanna read.
	///@return Boolean if the result is a success or not.
	template<typename Stream, typename C>
	static bool read(Stream* stream, C* object);


	///@brief write a table of objects inside the file stream, this function will automatically test for each object inherit from BasicIO themselves and then call there own write method.
	///@param stream file stream where to write.
	///@param buffer pointer to the table of objects we wanna write.
	///@param size number of elements in the table.
	///@return Boolean if the result is a success or not.
	template<typename Stream, typename C>
	static bool write(Stream* stream, const C* buffer, Size size);

	///@brief read from a file stream to a table of objects, this function will automatically test for each object inherit from BasicIO themselves and then call there own write method.
	///@param stream file stream where to read.
	///@param buffer pointer to the table of objects we wanna read.
	///@param size number of elements in the table.
	///@return Boolean if the result is a success or not.
	template<typename Stream, typename C>
	static bool read(Stream* stream, C* buffer, Size size);











	template<typename Stream, typename C>
	static bool _writeObject(Stream* stream, const C* buffer, const BasicIO* b);

	template<typename Stream, typename C>
	static bool _writeObject(Stream* stream, const C* buffer, ...);


	template<typename Stream, typename C>
	static bool _writeBuffer(Stream* stream, const C* buffer, Size size, const BasicIO* b);

	template<typename Stream, typename C>
	static bool _writeBuffer(Stream* stream, const C* buffer, Size size, ...);





	template<typename Stream, typename C>
	static bool _readObject(Stream* stream, C* buffer, BasicIO* b);

	template<typename Stream, typename C>
	static bool _readObject(Stream* stream, C* buffer, ...);

	template<typename Stream, typename C>
	static bool _readBuffer(Stream* stream, C* buffer, Size size, BasicIO* b);

	template<typename Stream, typename C>
	static bool _readBuffer(Stream* stream, C* buffer, Size size, ...);

}





#include "BasicIO.hpp"
