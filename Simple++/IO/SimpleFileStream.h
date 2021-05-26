#pragma once

#include <fstream>

namespace IO {

	///@brief Mode to open a FileStream.
	enum class OpenMode : unsigned char {
		Write = std::ios::out,
		Read = std::ios::in
	};

	template<typename T>
	class SimpleFileStreamT {
	public:
		///@brief Constructor. Directly open the file. Can be checked afterward with isOpen().
		///			Position will be set to 0.
		///@param filePath Path to be opened.
		///@param openMode Mode to open the file. (Read or Write)
		SimpleFileStreamT(const T * filePath, OpenMode openMode);

		///@brief Write data into this file at the current position.
		///@param data data to be wrtitten into the file.
		///@param size number of bytes to be written.
		///@return True if success, False otherwise.
		bool write(char* data, size_t size);

		///@brief read data from the file at the current position.
		///@param data Buffer to be filled with the read data.
		///@param size Number of bytes to be read.
		///@return True if success, False otherwise.
		bool read(char* data, size_t size);

		///@brief get the current position.
		///@return Current position.
		size_t getPosition();

		///@brief Set the current position from the beginning.
		///@param position New position to be set.
		void setPositionFromBegin(size_t position);

		///@brief Set the current position from the end.
		///@param position New position to be set.
		void setPositionFromEnd(size_t position);

		///@brief Check if the last operation has failed or not.
		///@return True if failed, False otherwise.
		bool hasFailed() const;

		///@brief Check if the File is currently open.
		///@return True if opened, False otherwise.
		bool isOpen() const;

		///@brief read the complete file stream (from begin to end) and allocate a new data and copy data inside.
		///@param data [out] data buffer to be allocated and filled with the content of the file stream.
		///@return number of char read. (Pointer will be set to NULL if failed, allocated otherwise.)
		size_t readToBuffer(char** buffer);

		///@brief Add a Character to the file.
		SimpleFileStreamT<T> & operator<<(char c);

		///@brief Add multiples characteres to file.
		SimpleFileStreamT<T>& operator<<(const char* buffer);

	private:
		std::fstream stream;
	};


#ifdef WIN32
	using SimpleFileStream = SimpleFileStreamT<wchar_t>;
#else
	using SimpleFileStream = SimpleFileStreamT<char>;
#endif

}

#include "SimpleFileStream.hpp"