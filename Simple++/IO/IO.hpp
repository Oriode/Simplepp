
namespace IO {

	template<typename C>
	bool write(const OS::Path& filePath, const C* object) {
		FileStream fileStream(filePath, IO::OpenMode::Write);
		if (fileStream.isOpen()) {
			bool result(IO::write(&fileStream, object));
			return result;
		}
		else
			return false;
	}


	template<typename C>
	bool read(const OS::Path & filePath, C* object) {
		FileStream fileStream(filePath, IO::OpenMode::Read);
		if (fileStream.isOpen()) {
			bool result(IO::read(&fileStream, object));
			return result;
		}
		else
			return false;
	}

	template<typename T>
	size_t readToBuffer(const OS::Path & filePath, char** data) {
		FileStream fileStream(filePath, IO::OpenMode::Read);
		if (fileStream.isOpen()) {
			return fileStream.readToBuffer(data);
		}
		else {
			*data = NULL;
			return size_t(-1);
		}
	}

	template<typename C>
	size_t readToString(const OS::Path& filePath, BasicString<C>* stringP) {
		FileStream fileStream(filePath, IO::OpenMode::Read);
		if (fileStream.isOpen()) {
			return fileStream.readToString(stringP);
		}
		else {
			return size_t(-1);
		}
	}

}