namespace Graphic {

	template<typename T, typename LoadingFunc>
	TrueTypeFontT<T, LoadingFunc>::TrueTypeFontT( const OS::Path & filePath, int pixSize, const LoadingFunc & loadingFunc ) :
		FontT<T, LoadingFunc>( loadingFunc ),
		filePath( filePath ) {
		_setPixSize( pixSize );
	}


	template<typename T, typename LoadingFunc>
	TrueTypeFontT<T, LoadingFunc>::~TrueTypeFontT() {
		unload();
	}

	template<typename T, typename LoadingFunc>
	bool TrueTypeFontT<T, LoadingFunc>::onLoad() {

		this -> memorySize = IO::readToBuffer( this -> filePath, &this -> memoryFontObject );
		if ( this -> memorySize == -1 ) {
			Log::displayError( StringASCII( "Unable to open the font file : " ) << this -> filePath );
			this -> memorySize = 0;
			this -> ftLib = NULL;
			this -> ftFace = NULL;
			return false;
		} else {
			return _loadFreeType( this -> memoryFontObject, this -> memorySize, this -> pixSize );
		}

		return true;
	}

	template<typename T, typename LoadingFunc>
	bool TrueTypeFontT<T, LoadingFunc>::onUnload() {
		_clear();
		return true;
	}

}

