


namespace Graphic {




	template<typename T, typename LoadingFunc>
	_FontLoadable<T, LoadingFunc>::_FontLoadable( const WString & fileName ) :
		_Font<T, LoadingFunc>(  ),
		loadingType( LoadingType::FILE ),
		fileName( fileName ) {

	}

	template<typename T, typename LoadingFunc>
	_FontLoadable<T, LoadingFunc>::_FontLoadable( const WString & fileName, int pixSize, const LoadingFunc & loadingFunc ) :
		_Font<T, LoadingFunc>( loadingFunc ),
		loadingType( LoadingType::FTFILE ),
		fileName( fileName ) {
		_setPixSize( pixSize );
	}


	template<typename T, typename LoadingFunc>
	_FontLoadable<T, LoadingFunc>::~_FontLoadable() {
		unload();
	}

	template<typename T, typename LoadingFunc>
	bool _FontLoadable<T, LoadingFunc>::onLoad() {
		switch ( this -> loadingType ) {
		case LoadingType::FTFILE:
		{
			this -> memorySize = IO::readToBuffer( this -> fileName, &this -> memoryFontObject );
			if ( this -> memorySize == -1 ) {
				Log::displayError( StringASCII( "Unable to open the font file : " ) << this -> fileName );
				this -> memorySize = 0;
				this -> ftLib = NULL;
				this -> ftFace = NULL;
				return false;
			} else {
				return _loadFreeType( this -> memoryFontObject, this -> memorySize );
			}


			break;
		} case LoadingType::FILE:
		{
			IO::SimpleFileStream file( this -> fileName.getData(), std::ios::in | std::ios::binary );
			if ( file.is_open() ) {
				if ( !onRead( &file ) ) {
					error( String( TEXT( "Error while reading the file : " ) ) << this -> fileName );
					return false;
				}
				file.close();
				return true;
			} else {
				error( StringASCII( TEXT( "Error while opening the file : " ) ) << this -> fileName );
				return false;
			}

			break;
		}
		}
		return true;
	}

	template<typename T, typename LoadingFunc>
	bool _FontLoadable<T, LoadingFunc>::onUnload() {
		_clear();
	}

	template<typename T, typename LoadingFunc>
	bool _FontLoadable<T, LoadingFunc>::onRead( IO::SimpleFileStream * fileStream ) {
		return _Font::_read( fileStream );
	}

	template<typename T, typename LoadingFunc>
	bool _FontLoadable<T, LoadingFunc>::onWrite( IO::SimpleFileStream * fileStream ) const {
		return _Font::write( fileStream );
	}

}

