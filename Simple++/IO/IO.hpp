
namespace IO {

	template<typename C>
	bool write( const OS::Path& filePath, const C* object, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Writting to file \"%\"...", filePath ) ); }

		FileStream stream( filePath, IO::OpenMode::Write );
		if ( !stream.isOpen() ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Unable to open the file." ) ); }
			return false;
		}

		if ( !IO::write( &stream, object ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to write." ) ); }
			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success." ) ); }

		return true;
	}


	template<typename C>
	bool read( const OS::Path& filePath, C* object, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Reading a new file \"%\"...", filePath ) ); }

		FileStream stream( filePath, IO::OpenMode::Read );
		if ( !stream.isOpen() ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Unable to open the file." ) ); }
			return false;
		}

		if ( !IO::read( &stream, object, verbose ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to read." ) ); }
			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success." ) ); }

		return true;
	}

	template<typename T>
	Size readToBuffer( const OS::Path& filePath, char** data, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Reading a new file \"%\"...", filePath ) ); }

		FileStream stream( filePath, IO::OpenMode::Read );
		if ( !stream.isOpen() ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Unable to open the file." ) ); }

			*data = NULL;
			return Size( -1 );
		}

		if ( !stream.readToBuffer( data, verbose ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to read." ) ); }
			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success." ) ); }

		return true;
	}

	template<typename C>
	Size readToString( const OS::Path& filePath, BasicString<C>* stringP, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Reading a new file \"%\"...", filePath ) ); }

		FileStream stream( filePath, IO::OpenMode::Read );
		if ( stream.isOpen() ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Unable to open the file." ) ); }

			return Size( -1 );
		}

		if ( !stream.readToString( stringP ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to read." ) ); }

			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success." ) ); }

		return true;
	}

}