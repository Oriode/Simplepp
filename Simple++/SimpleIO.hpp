


template<typename C>
bool SimpleIO::_writeObject(std::fstream * fileStream, C * buffer, BasicSimpleLoadableIO * b) {
	return buffer -> write(fileStream);
}

template<typename C>
bool SimpleIO::_writeObject(std::fstream * fileStream, C * buffer, BasicSimpleIO * b) {
	return buffer -> write(fileStream);
}


template<typename C>
bool SimpleIO::_writeObject(std::fstream * fileStream, C * buffer, ...) {
	debug(size_t tmp = sizeof(C); size_t beginPos = fileStream -> tellp(););
	fileStream -> write((char *) buffer, sizeof(C));
	debug(size_t charWrote = (size_t) ( fileStream -> tellp() ) - beginPos;);
	return !fileStream->fail();
}


template<typename C>
bool SimpleIO::write(std::fstream * fileStream, C * buffer) {
	return IO::_writeObject(fileStream, buffer, buffer);
}


template<typename C>
bool SimpleIO::_readObject(std::fstream * fileStream, C * buffer, BasicSimpleLoadableIO * b) {
	return buffer -> read(fileStream);
}

template<typename C>
bool SimpleIO::_readObject(std::fstream * fileStream, C * buffer, BasicSimpleIO * b) {
	return buffer -> read(fileStream);
}

template<typename C>
bool SimpleIO::_readObject(std::fstream * fileStream, C * buffer, ...) {
	debug(size_t tmp = sizeof(C); size_t beginPos = fileStream -> tellp(););
	fileStream -> read((char *) buffer, sizeof(C));
	debug(size_t charWrote = (size_t) ( fileStream -> tellp() ) - beginPos;);
	return !fileStream->fail();
}

template<typename C>
bool SimpleIO::read(std::fstream * fileStream, C * buffer) {
	return IO::_readObject(fileStream, buffer, buffer);
}


template<typename C>
bool SimpleIO::writeBuffer(std::fstream * fileStream, C * buffer, size_t size) {
	return _writeBuffer(fileStream, buffer, size, buffer);
}


template<typename C>
bool SimpleIO::readBuffer(std::fstream * fileStream, C * buffer, size_t size) {
	return _readBuffer(fileStream, buffer, size, buffer);
}



template<typename C>
bool SimpleIO::_writeBuffer(std::fstream * fileStream, C * buffer, size_t size, BasicSimpleLoadableIO * b) {
	for ( size_t i = 0; i < size; i++ ) {
		if ( !buffer[i].write(fileStream) )
			return false;
	}
	return true;
}



template<typename C>
bool SimpleIO::_writeBuffer(std::fstream * fileStream, C * buffer, size_t size, BasicSimpleIO * b) {
	for ( size_t i = 0; i < size; i++ ) {
		if ( !buffer[i].write(fileStream) )
			return false;
	}
	return true;
}

template<typename C>
bool SimpleIO::_writeBuffer(std::fstream * fileStream, C * buffer, size_t size, ...) {
	debug(size_t tmp = sizeof(C) * size; size_t beginPos = fileStream -> tellp(););
	fileStream -> write((char *) buffer, sizeof(C) * size);
	debug(size_t charWrote = (size_t) ( fileStream -> tellp() ) - beginPos;);
	return !fileStream->fail();
}



template<typename C>
bool SimpleIO::_readBuffer(std::fstream * fileStream, C * buffer, size_t size, BasicSimpleLoadableIO * b) {
	for ( size_t i = 0; i < size; i++ ) {
		if ( !buffer[i].read(fileStream) )
			return false;
	}
	return true;
}

template<typename C>
bool SimpleIO::_readBuffer(std::fstream * fileStream, C * buffer, size_t size, BasicSimpleIO * b) {
	for ( size_t i = 0; i < size; i++ ) {
		if ( !buffer[i].read(fileStream) )
			return false;
	}
	return true;
}

template<typename C>
bool SimpleIO::_readBuffer(std::fstream * fileStream, C * buffer, size_t size, ...) {
	debug(size_t tmp = sizeof(C) * size; size_t beginPos = fileStream -> tellp(););
	fileStream -> read((char *) buffer, sizeof(C) * size);
	debug(size_t charWrote = (size_t) fileStream -> tellp() - beginPos;);
	return !fileStream->fail();
}