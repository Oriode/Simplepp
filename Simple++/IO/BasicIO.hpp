
namespace IO {

	template<typename T>
	template<typename Stream>
	bool BasicIOT<T>::read(Stream* stream) {
		_ASSERT(stream->isOpen());
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool BasicIOT<T>::write(Stream* stream) const {
		_ASSERT(stream->isOpen());
		return true;
	}

	template<typename Stream, typename C>
	bool _writeObject(Stream* stream, const C* buffer, const BasicIO* b) {
		return buffer->write(stream);
	}

	template<typename Stream, typename C>
	bool _writeObject(Stream* stream, const C* buffer, ...) {
		DEBUG_SPP(Size expectedSize(sizeof(C)); Size beginPos(stream->getPosition()););
		bool r(stream->write(( char* ) buffer, sizeof(C)));
		DEBUG_SPP(Size charWrote(stream->getPosition() - beginPos););
		ASSERT_SPP(charWrote == expectedSize);
		return r;
	}

	template<typename Stream, typename C>
	bool write(Stream* stream, const C* buffer) {
		if ( !buffer ) return true;
		return _writeObject(stream, buffer, buffer);
	}


	template<typename Stream, typename C>
	bool _readObject(Stream* stream, C* buffer, BasicIO* b) {
		return buffer->read(stream);
	}

	template<typename Stream, typename C>
	bool _readObject(Stream* stream, C* buffer, ...) {
		DEBUG_SPP(Size expectedSize(sizeof(C)); Size beginPos(stream->getPosition()););
		bool r(stream->read(( char* ) buffer, sizeof(C)));
		DEBUG_SPP(Size charRead(stream->getPosition() - beginPos););
		ASSERT_SPP(charRead == expectedSize);
		return r;
	}

	template<typename Stream, typename C>
	bool read(Stream* stream, C* buffer) {
		if ( !buffer ) return true;
		return _readObject(stream, buffer, buffer);
	}


	template<typename Stream, typename C>
	bool write(Stream* stream, const C* buffer, Size size) {
		if ( !buffer ) return true;
		return _writeBuffer(stream, buffer, size, buffer);
	}


	template<typename Stream, typename C>
	bool read(Stream* stream, C* buffer, Size size) {
		if ( !buffer ) return true;
		return _readBuffer(stream, buffer, size, buffer);
	}





	template<typename Stream, typename C>
	bool _writeBuffer(Stream* stream, const C* buffer, Size size, const BasicIO* b) {
		for ( Size i = 0; i < size; i++ ) {
			if ( !buffer[ i ].write(stream) )
				return false;
		}
		return true;
	}

	template<typename Stream, typename C>
	bool _writeBuffer(Stream* stream, const C* buffer, Size size, ...) {
		DEBUG_SPP(Size expectedSize(sizeof(C) * size); Size beginPos(stream->getPosition()););
		bool r(stream->write(( char* ) buffer, sizeof(C) * size));
		DEBUG_SPP(Size charWrote(stream->getPosition() - beginPos););
		ASSERT_SPP(charWrote == expectedSize);
		return r;
	}



	template<typename Stream, typename C>
	bool _readBuffer(Stream* stream, C* buffer, Size size, BasicIO* b) {
		for ( Size i = 0; i < size; i++ ) {
			if ( !buffer[ i ].read(stream) )
				return false;
		}
		return true;
	}

	template<typename Stream, typename C>
	bool _readBuffer(Stream* stream, C* buffer, Size size, ...) {
		DEBUG_SPP(Size expectedSize(sizeof(C) * size); Size beginPos(stream->getPosition()););
		bool r(stream->read(( char* ) buffer, sizeof(C) * size));
		DEBUG_SPP(Size charRead(stream->getPosition() - beginPos););
		ASSERT_SPP(charRead == expectedSize);
		return r;
	}

}