
namespace IO {

	template<typename C>
	bool _writeObject( SimpleFileStream * fileStream, const C * buffer, const BasicSimpleLoadableIO * b ) {
		return buffer->write( fileStream );
	}

	template<typename C>
	bool _writeObject( SimpleFileStream * fileStream, const C * buffer, const BasicSimpleIO * b ) {
		return buffer->write( fileStream );
	}

	template<typename C>
	bool _writeObject( SimpleFileStream * fileStream, const C * buffer, ... ) {
		debug( size_t tmp = sizeof( C ); size_t beginPos = fileStream->getPosition(););
		bool r( fileStream->write( ( char * ) buffer, sizeof( C ) ) );
		debug( size_t charWrote = ( size_t ) ( fileStream->getPosition() )-beginPos;);
		return r;
	}

	template<typename C>
	bool write( SimpleFileStream * fileStream, const C * buffer ) {
		if ( !buffer ) return true;
		return _writeObject( fileStream, buffer, buffer );
	}


	template<typename C>
	bool _readObject( SimpleFileStream * fileStream, C * buffer, BasicSimpleLoadableIO * b ) {
		return buffer->read( fileStream );
	}

	template<typename C>
	bool _readObject( SimpleFileStream * fileStream, C * buffer, BasicSimpleIO * b ) {
		return buffer->read( fileStream );
	}

	template<typename C>
	bool _readObject( SimpleFileStream * fileStream, C * buffer, ... ) {
		debug( size_t tmp = sizeof( C ); size_t beginPos = fileStream->getPosition(););
		bool r( fileStream->read( ( char * ) buffer, sizeof( C ) ) );
		debug( size_t charWrote = ( size_t ) ( fileStream->getPosition() )-beginPos;);
		return r;
	}

	template<typename C>
	bool read( SimpleFileStream * fileStream, C * buffer ) {
		if ( !buffer ) return true;
		return _readObject( fileStream, buffer, buffer );
	}


	template<typename C>
	bool writeBuffer( SimpleFileStream * fileStream, const C * buffer, size_t size ) {
		if ( !buffer ) return true;
		return _writeBuffer( fileStream, buffer, size, buffer );
	}


	template<typename C>
	bool readBuffer( SimpleFileStream * fileStream, C * buffer, size_t size ) {
		if ( !buffer ) return true;
		return _readBuffer( fileStream, buffer, size, buffer );
	}



	template<typename C>
	bool _writeBuffer( SimpleFileStream * fileStream, const C * buffer, size_t size, const BasicSimpleLoadableIO * b ) {
		for ( size_t i = 0; i<size; i++ ) {
			if ( !buffer[ i ].write( fileStream ) )
				return false;
		}
		return true;
	}



	template<typename C>
	bool _writeBuffer( SimpleFileStream * fileStream, const C * buffer, size_t size, const BasicSimpleIO * b ) {
		for ( size_t i = 0; i<size; i++ ) {
			if ( !buffer[ i ].write( fileStream ) )
				return false;
		}
		return true;
	}

	template<typename C>
	bool _writeBuffer( SimpleFileStream * fileStream, const C * buffer, size_t size, ... ) {
		debug( size_t tmp = sizeof( C )*size; size_t beginPos = fileStream->getPosition(););
		bool r( fileStream->write( ( char * ) buffer, sizeof( C )*size ) );
		debug( size_t charWrote = ( size_t ) ( fileStream->getPosition() )-beginPos;);
		return r;
	}



	template<typename C>
	bool _readBuffer( SimpleFileStream * fileStream, C * buffer, size_t size, BasicSimpleLoadableIO * b ) {
		for ( size_t i = 0; i<size; i++ ) {
			if ( !buffer[ i ].read( fileStream ) )
				return false;
		}
		return true;
	}

	template<typename C>
	bool _readBuffer( SimpleFileStream * fileStream, C * buffer, size_t size, BasicSimpleIO * b ) {
		for ( size_t i = 0; i<size; i++ ) {
			if ( !buffer[ i ].read( fileStream ) )
				return false;
		}
		return true;
	}

	template<typename C>
	bool _readBuffer( SimpleFileStream * fileStream, C * buffer, size_t size, ... ) {
		debug( size_t tmp = sizeof( C )*size; size_t beginPos = fileStream->getPosition(););
		bool r( fileStream->read( ( char * ) buffer, sizeof( C )*size ) );
		debug( size_t charWrote = ( size_t ) fileStream->getPosition()-beginPos;);
		return r;
	}

}
