
namespace IO {

	template<typename C>
	bool write(const OS::Path& filePath, const C* object) {
		FileStream stream(filePath, IO::OpenMode::Write);
		if (stream.isOpen()) {
			bool result(IO::write(&stream, object));
			return result;
		}
		else
			return false;
	}


	template<typename C>
	bool read(const OS::Path & filePath, C* object, int verbose) {
		FileStream stream(filePath, IO::OpenMode::Read);
		if (stream.isOpen()) {
			bool result(IO::read(&stream, object, verbose));
			return result;
		}
		else
			return false;
	}

	template<typename T>
	size_t readToBuffer(const OS::Path & filePath, char** data, int verbose) {
		FileStream stream(filePath, IO::OpenMode::Read);
		if (stream.isOpen()) {
			return stream.readToBuffer(data, verbose);
		}
		else {
			*data = NULL;
			return size_t(-1);
		}
	}

	template<typename C>
	size_t readToString(const OS::Path& filePath, BasicString<C>* stringP, int verbose) {
		FileStream stream(filePath, IO::OpenMode::Read);
		if (stream.isOpen()) {
			return stream.readToString(stringP);
		}
		else {
			return size_t(-1);
		}
	}

}