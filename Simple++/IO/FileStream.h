#pragma once

#include <fstream>

#include "../OS/Path.h"


namespace IO {

	///@brief Mode to open a FileStream.
	enum class OpenMode : unsigned char {
		Write = std::ios::out,
		Read = std::ios::in
	};

	///@brief Representing a File on the Operating System that can be read or write.
	///@template Should be a String Type (WString, UTF8String...)
	template<typename T>
	class FileStreamT {
	public:
		///@brief Constructor. Directly open the file. Can be checked afterward with isOpen().
		///			Position will be set to 0.
		///@param filePath Path to be opened.
		///@param openMode Mode to open the file. (Read or Write)
		FileStreamT(const OS::PathT<T> & filePath, OpenMode openMode);

		///@brief Get the associated path.
		///@return File Path.
		const OS::PathT<T>& getPath() const;

		///@brief Test if the file actually exists on the operating system. (Same as Path::exists()).
		bool exists() const;

		///@brief Close this object.
		void close();

		///@brief Read the whole file and convert it to a String Object.
		///@template C Should be a BasicStringT.
		///@param [out] stringP String to be modified.
		///@return number of char read (-1) if an error has occurred.
		template<typename C>
		Size readToString(BasicString<C>* stringP);

		///@brief Write data into this file at the current position.
		///@param data data to be wrtitten into the file.
		///@param size number of bytes to be written.
		///@return True if success, False otherwise.
		bool write(const char* data, Size size);

		///@brief read data from the file at the current position.
		///@param data Buffer to be filled with the read data.
		///@param size Number of bytes to be read.
		///@return True if success, False otherwise.
		bool read(char* data, Size size);

		///@brief get the current position.
		///@return Current position.
		Size getPosition();

		///@brief Set the current position from the beginning.
		///@param position New position to be set.
		void setPositionFromBegin(Size position);

		///@brief Set the current position from the end.
		///@param position New position to be set.
		void setPositionFromEnd(Size position);

		///@brief Check if the last operation has failed or not.
		///@return True if failed, False otherwise.
		bool hasFailed() const;

		///@brief Check if the File is currently open.
		///@return True if opened, False otherwise.
		bool isOpen() const;

		///@brief read the complete file stream (from begin to end) and allocate a new data and copy data inside.
		///@param data [out] data buffer to be allocated and filled with the content of the file stream.
		///@return number of char read if succeed, -1 otherwise. (Pointer will be set to NULL if failed, allocated otherwise.)
		Size readToBuffer(char** buffer);

		/************************************************************************/
		/* OPERATOR STREAM                                                      */
		/************************************************************************/

		///@brief Add a Character to the file.
		///@param c Byte to be added.
		///@return Reference to this.
		FileStreamT<T>& operator<<(char c);

		///@brief Add multiples characteres to file.
		FileStreamT<T>& operator<<(const char* buffer);

	private:
		OS::PathT<T> filePath;
		std::fstream stream;
	};

	using FileStream = FileStreamT<OS::Path::StringType>;

}

#include "FileStream.hpp"