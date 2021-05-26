namespace IO {

	template<typename T>
	SimpleFileStreamT<T>::SimpleFileStreamT(const T * filePath, OpenMode openMode) :
		stream(filePath, ((unsigned char)openMode) | std::ios::binary)
	{

	}

	template<typename T>
	bool SimpleFileStreamT<T>::write(char* data, size_t size) {
		this->stream.write(data, size);
		return !hasFailed();
	}

	template<typename T>
	bool SimpleFileStreamT<T>::read(char* data, size_t size) {
		this->stream.read(data, size);
		return !hasFailed();
	}

	template<typename T>
	size_t SimpleFileStreamT<T>::getPosition() {
		return this->stream.tellp();
	}

	template<typename T>
	void SimpleFileStreamT<T>::setPositionFromBegin(size_t position) {
		this->stream.seekg(position, this->stream.beg);
	}

	template<typename T>
	void SimpleFileStreamT<T>::setPositionFromEnd(size_t position) {
		this->stream.seekg(position, this->stream.end);
	}

	template<typename T>
	bool SimpleFileStreamT<T>::hasFailed() const {
		return this->stream.fail();
	}

	template<typename T>
	bool SimpleFileStreamT<T>::isOpen() const {
		return this->stream.is_open();
	}

	template<typename T>
	size_t SimpleFileStreamT<T>::readToBuffer(char** buffer) {
		setPositionFromEnd(0);
		size_t length(getPosition());
		setPositionFromBegin(0);

		if (length) {
			*buffer = new char[length];
			if (!read(*buffer, length)) {
				*buffer = NULL;
				return size_t(-1);
			}
		}
		else {
			*buffer = NULL;
			return size_t(-1);
		}

		return length;
	}

	template<typename T>
	SimpleFileStreamT<T>& SimpleFileStreamT<T>::operator<<(char c) {
		this->stream << c;
		return *this;
	}

	template<typename T>
	SimpleFileStreamT<T>& SimpleFileStreamT<T>::operator<<(const char* buffer) {
		this->stream << buffer;
		return *this;
	}

}