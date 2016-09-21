


namespace Graphic {




	template<typename T>
	FontLoadable<T>::FontLoadable( const WString & fileName ) :
		Font<T>( ctor::null ),
		loadingType( LoadingType::FILE ),
		fileName( fileName ) {

	}

	template<typename T>
	FontLoadable<T>::FontLoadable( const WString & fileName, int pixSize ) :
		Font<T>( ctor::null ),
		loadingType( LoadingType::FTFILE ),
		fileName( fileName ) {
		_setPixSize( pixSize );
	}


	template<typename T>
	FontLoadable<T>::~FontLoadable() {
		unload();
	}

	template<typename T>
	void FontLoadable<T>::onLoad() {
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

	template<typename T>
	void FontLoadable<T>::onUnload() {
		_unload();
	}

	template<typename T>
	bool FontLoadable<T>::onRead( std::fstream * fileStream ) {
		return Font::_read( fileStream );
	}

	template<typename T>
	bool FontLoadable<T>::onWrite( std::fstream * fileStream ) const {
		return Font::write( fileStream );
	}

}

