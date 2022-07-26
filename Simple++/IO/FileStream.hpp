#include "FileStream.h"
namespace IO {

	template<typename T>
	FileStreamT<T>::FileStreamT(const OS::PathT<T> & filePath, OpenMode openMode) :
		filePath(filePath),
		stream(filePath.getData(), ( ( unsigned char ) openMode ) | std::ios::binary)
	{

	}

	template<typename T>
	const OS::PathT<T> & FileStreamT<T>::getPath() const {
		return this->filePath;
	}

	template<typename T>
	bool FileStreamT<T>::exists() const {
		return this->filePath.exists();
	}

	template<typename T>
	inline void FileStreamT<T>::close() {
		this->stream.close();
	}

	template<typename T>
	template<typename C>
	Size FileStreamT<T>::readToString(BasicString<C>* stringP) {
		setPositionFromEnd(0);
		Size length(getPosition());
		setPositionFromBegin(0);

		if ((*stringP).read(this, length)) {
			return stringP->getSize();
		}
		else {
			return Size(-1);
		}
	}

	template<typename T>
	bool FileStreamT<T>::write(char* data, Size size) {
		this->stream.write(data, size);
		return !hasFailed();
	}

	template<typename T>
	bool FileStreamT<T>::read(char* data, Size size) {
		this->stream.read(data, size);
		return !hasFailed();
	}

	template<typename T>
	Size FileStreamT<T>::getPosition() {
		return this->stream.tellp();
	}

	template<typename T>
	void FileStreamT<T>::setPositionFromBegin(Size position) {
		this->stream.seekg(position, this->stream.beg);
	}

	template<typename T>
	void FileStreamT<T>::setPositionFromEnd(Size position) {
		this->stream.seekg(position, this->stream.end);
	}

	template<typename T>
	bool FileStreamT<T>::hasFailed() const {
		return this->stream.fail();
	}

	template<typename T>
	bool FileStreamT<T>::isOpen() const {
		return this->stream.is_open();
	}

	template<typename T>
	Size FileStreamT<T>::readToBuffer(char** buffer) {
		setPositionFromEnd(0);
		Size length(getPosition());
		setPositionFromBegin(0);

		if ( length ) {
			*buffer = new char[ length ];
			if ( !read(*buffer, length) ) {
				*buffer = NULL;
				return Size(-1);
			}
		} else {
			*buffer = NULL;
			return Size(-1);
		}

		return length;
	}

	template<typename T>
	FileStreamT<T>& FileStreamT<T>::operator<<(char c) {
		this->stream << c;
		return *this;
	}

	template<typename T>
	FileStreamT<T>& FileStreamT<T>::operator<<(const char* buffer) {
		this->stream << buffer;
		return *this;
	}

}