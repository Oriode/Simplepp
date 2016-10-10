


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
	void _FontLoadable<T, LoadingFunc>::onLoad() {
		switch ( this -> loadingType ) {
		case LoadingType::FTFILE:
		{
			this -> memorySize = IO::readToBuffer( this -> fileName, &this -> memoryFontObject );
			if ( this -> memorySize == -1 ) {
				Log::displayError( String( "Unable to open the font file : " ) << this -> fileName );
				return;
			}

			_loadFreeType( this -> memoryFontObject, this -> memorySize );


			break;
		} case LoadingType::FILE:
		{
			std::fstream file( this -> fileName.getData(), std::ios::in | std::ios::binary );
			if ( file.is_open() ) {
				if ( !onRead( &file ) ) {
					error( String( "Error while reading the file : " ) << this -> fileName );
				}
				file.close();
			} else {
				error( String( "Error while opening the file : " ) << this -> fileName );
			}

			break;
		}
		}
	}

	template<typename T, typename LoadingFunc>
	void _FontLoadable<T, LoadingFunc>::onUnload() {
		_unload();
	}

	template<typename T, typename LoadingFunc>
	bool _FontLoadable<T, LoadingFunc>::onRead( std::fstream * fileStream ) {
		return _Font::_read( fileStream );
	}

	template<typename T, typename LoadingFunc>
	bool _FontLoadable<T, LoadingFunc>::onWrite( std::fstream * fileStream ) const {
		return _Font::write( fileStream );
	}

}

