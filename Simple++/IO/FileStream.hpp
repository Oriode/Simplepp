namespace IO { 

	template<typename T>
	FileStreamT<T>::FileStreamT(const OS::PathT<T> & filePath, OpenMode openMode) :
		SimpleFileStreamT<T::ElemType>(filePath.toString().getData(), openMode),
		filePath(filePath)
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
	template<typename C>
	size_t FileStreamT<T>::readToString(BasicString<C>* stringP) {
		setPositionFromEnd(0);
		size_t length(getPosition());
		setPositionFromBegin(0);

		if ((*stringP).read(this, length)) {
			return stringP->getSize();
		}
		else {
			return size_t(-1);
		}
	}

}