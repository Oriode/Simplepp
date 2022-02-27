
namespace IO {

	template<typename Stream, typename C>
	bool _writeObject( Stream * stream, const C * buffer, const BasicSimpleIO * b ) {
		return buffer->write( stream );
	}

	template<typename Stream, typename C>
	bool _writeObject( Stream * stream, const C * buffer, ... ) {
		debug( Size tmp = sizeof( C ); Size beginPos = stream->getPosition(););
		bool r( stream->write( ( char * ) buffer, sizeof( C ) ) );
		debug( Size charWrote = ( Size ) ( stream->getPosition() )-beginPos;);
		return r;
	}

	template<typename Stream, typename C>
	bool write( Stream * stream, const C * buffer ) {
		if ( !buffer ) return true;
		return _writeObject( stream, buffer, buffer );
	}


	template<typename Stream, typename C>
	bool _readObject( Stream * stream, C * buffer, BasicSimpleIO * b ) {
		return buffer->read( stream );
	}

	template<typename Stream, typename C>
	bool _readObject( Stream * stream, C * buffer, ... ) {
		debug( Size tmp = sizeof( C ); Size beginPos = stream->getPosition(););
		bool r( stream->read( ( char * ) buffer, sizeof( C ) ) );
		debug( Size charWrote = ( Size ) ( stream->getPosition() )-beginPos;);
		return r;
	}

	template<typename Stream, typename C>
	bool read( Stream * stream, C * buffer ) {
		if ( !buffer ) return true;
		return _readObject( stream, buffer, buffer );
	}


	template<typename Stream, typename C>
	bool writeBuffer( Stream * stream, const C * buffer, Size size ) {
		if ( !buffer ) return true;
		return _writeBuffer( stream, buffer, size, buffer );
	}


	template<typename Stream, typename C>
	bool readBuffer( Stream * stream, C * buffer, Size size ) {
		if ( !buffer ) return true;
		return _readBuffer( stream, buffer, size, buffer );
	}





	template<typename Stream, typename C>
	bool _writeBuffer( Stream * stream, const C * buffer, Size size, const BasicSimpleIO * b ) {
		for ( Size i = 0; i<size; i++ ) {
			if ( !buffer[ i ].write( stream ) )
				return false;
		}
		return true;
	}

	template<typename Stream, typename C>
	bool _writeBuffer( Stream * stream, const C * buffer, Size size, ... ) {
		debug( Size tmp = sizeof( C )*size; Size beginPos = stream->getPosition(););
		bool r( stream->write( ( char * ) buffer, sizeof( C )*size ) );
		debug( Size charWrote = ( Size ) ( stream->getPosition() )-beginPos;);
		return r;
	}



	template<typename Stream, typename C>
	bool _readBuffer( Stream * stream, C * buffer, Size size, BasicSimpleIO * b ) {
		for ( Size i = 0; i<size; i++ ) {
			if ( !buffer[ i ].read( stream ) )
				return false;
		}
		return true;
	}

	template<typename Stream, typename C>
	bool _readBuffer( Stream * stream, C * buffer, Size size, ... ) {
		debug( Size tmp = sizeof( C )*size; Size beginPos = stream->getPosition(););
		bool r( stream->read( ( char * ) buffer, sizeof( C )*size ) );
		debug( Size charWrote = ( Size ) stream->getPosition()-beginPos;);
		return r;
	}

}
