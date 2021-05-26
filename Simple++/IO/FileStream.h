#pragma once

#include "SimpleFileStream.h"
#include "../OS/Path.h"


namespace IO {

	///@brief Representing a File on the Operating System that can be read or write.
	///@template Should be a String Type (WString, UTF8String...)
	template<typename T>
	class FileStreamT : public SimpleFileStreamT<typename T::ElemType> {
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

		///@brief Read the whole file and convert it to a String Object.
		///@template C Should be a BasicStringT.
		///@param [out] stringP String to be modified.
		///@return number of char read (-1) if an error has occurred.
		template<typename C>
		size_t readToString(BasicString<C>* stringP);

	private:
		OS::PathT<T> filePath;
		std::fstream stream;
	};

	using FileStream = FileStreamT<OS::Path::StringType>;

}

#include "FileStream.hpp"