
namespace IO {

	template<typename T>
	BasicLoadableIOT<T>::BasicLoadableIOT() {
	}

	template<typename T>
	BasicLoadableIOT<T>::~BasicLoadableIOT() {
	}

	template<typename T>
	bool BasicLoadableIOT<T>::writeToFile( const OS::Path & path ) {
		FileStream fileStream(path, OpenMode::Write);
		if (fileStream.isOpen()) {
			load();
			if (!write(&fileStream)) {
				error(StringASCII("Unable to write the fileStream : ") << path);
				return false;
			}
			log(StringASCII("Success writting the fileStream  : ") << path);
			return true;
		}
		else {
			error(StringASCII("Unable to open the fileStream : ") << path);
			return false;
		}
	}

	template<typename T>
	bool BasicLoadableIOT<T>::readFromFile( const OS::Path & path ) {
		FileStream fileStream(path, OpenMode::Read);
		if (fileStream.isOpen()) {
			if (!read(&fileStream)) {
				error(StringASCII("Unable to read the fileStream : ") << path);
				return false;
			}
			log(StringASCII("Success writting the fileStream  : ") << path);
			return true;
		}
		else {
			error(StringASCII("Unable to open the fileStream : ") << path);
			return false;
		}
	}

}

