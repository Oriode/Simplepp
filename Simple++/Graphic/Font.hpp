
namespace Graphic {

	template<typename T, typename LoadingFunc>
	const UTF8String FontT<T, LoadingFunc>::Template::Ascii = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.+/_-*'\"()[]#^%!?";

	template<typename T, typename LoadingFunc>
	const UTF8String FontT<T, LoadingFunc>::Template::Latin1 = "\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf";


	template<typename T, typename LoadingFunc>
	template<typename Stream>
	FontT<T, LoadingFunc>::FontT( Stream * stream ) {
		_nullify();
		if ( !_read( stream ) )
			_clear();
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc>::FontT( const WString & fileName, int pixSize, const LoadingFunc & loadingFunctor ) :
		loadingFunctor( loadingFunctor )
	{
		static_assert( Utility::isBase<FontLoadingFunc::Template, LoadingFunc>::value, "The Loading Functor has to inherite from FontLoadingFunc::Template" );
		_setPixSize( pixSize );
		this -> memorySize = IO::readToBuffer( fileName, &this -> memoryFontObject );
		if ( this -> memorySize == -1 ) {
			Log::displayError( StringASCII( "Unable to open the font file : " ) << fileName );
			this -> memorySize = 0;
			this -> ftLib = NULL;
			this -> ftFace = NULL;
		} else {
			_loadFreeType( this -> memoryFontObject, this -> memorySize, this -> pixSize );
		}
		for ( size_t i = 0; i < 256; i++ )
			this -> asciiMap[i] = NULL;
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc>::FontT( const char * fileDump, size_t fileSize, int pixSize, const LoadingFunc & loadingFunctor ) :
		loadingFunctor( loadingFunctor ),
		memorySize( fileSize ) 
	{
		static_assert( Utility::isBase<FontLoadingFunc::Template<T>, LoadingFunc>::value, "The Loading Functor has to inherite from FontLoadingFunc::Template" );
		_setPixSize( pixSize );

		if ( this -> memorySize ) {
			this -> memoryFontObject = new char[this -> memorySize];
			Vector<char>::copy( this -> memoryFontObject, fileDump, this -> memorySize );
			if ( !_loadFreeType( this -> memoryFontObject, this -> memorySize, this -> pixSize ) ) {
				delete[] this -> memoryFontObject;
				this -> memoryFontObject = NULL;
				this -> memorySize = 0;
			}
		} else {
			this -> memoryFontObject = NULL;
			this -> ftLib = NULL;
			this -> ftFace = NULL;
		}

		for ( size_t i = 0; i < 256; i++ )
			this -> asciiMap[i] = NULL;
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc>::FontT( const LoadingFunc & loadingFunctor ) :
		loadingFunctor( loadingFunctor )
	{
		_nullify();
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc>::FontT( const FontT<T, LoadingFunc> & font ) {
		_copy( font );
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc>::FontT( FontT<T, LoadingFunc> && font ) {
		_move( Utility::toRValue(font) );
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::setLoadingFunctor( const LoadingFunc & loadingFunctor ) {
		this -> loadingFunctor = loadingFunctor;
	}

	template<typename T, typename LoadingFunc>
	const LoadingFunc & FontT<T, LoadingFunc>::getLoadingFunctor() const {
		return this -> loadingFunctor;
	}



	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc>::~FontT() {
		_unload();
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::_setPixSize( unsigned int size ) {
		this -> pixSize = float( size );
		this -> lineHeight = 1.0f * float( this -> pixSize );
		this -> wordSpace = 0.4f * float( this -> pixSize );
	}




	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::_unload() {
		if ( this -> memoryFontObject ) {
			if ( this -> ftFace ) FT_Done_Face( this -> ftFace );
			if ( this -> ftLib ) FT_Done_FreeType( this -> ftLib );
			delete[] this -> memoryFontObject;
		}
		for ( auto it = this -> charsMap.getBegin(); it != this -> charsMap.getEnd(); it++ ) 
			delete this -> charsMap.getValueIt(it);
		
		this -> charsMap.clear();
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::_nullify() {
		for ( size_t i = 0; i < 256; i++ )
			this -> asciiMap[i] = NULL;

		this -> memoryFontObject = NULL;
		this -> ftFace = NULL;
		this -> ftLib = NULL;
		this -> memorySize = 0;
	}

	template<typename T, typename LoadingFunc>
	FreeTypeChar<T> * FontT<T, LoadingFunc>::operator[]( UCodePoint codePoint ) {
		if ( codePoint < 256 ) {
			return this -> asciiMap[codePoint];
		} else {
			FreeTypeChar<T> ** c = this -> charsMap.getValueI( codePoint );
			if ( c ) {
				return *c;
			} else {
				return NULL;
			}
		}
	}

	template<typename T, typename LoadingFunc>
	const FreeTypeChar<T> * FontT<T, LoadingFunc>::operator[]( UCodePoint codePoint ) const {
		if ( codePoint < 256 ) {
			return this -> asciiMap[codePoint];
		} else {
			FreeTypeChar<T> * const * c = this -> charsMap.getValueI( codePoint );
			if ( c ) {
				return *c;
			} else {
				return NULL;
			}
		}
	}

	template<typename T, typename LoadingFunc>
	const Map<UCodePoint, FreeTypeChar<T> *> & FontT<T, LoadingFunc>::getCharMap() const {
		return this -> charsMap;
	}


	template<typename T, typename LoadingFunc>
	const FreeTypeChar<T> * FontT<T, LoadingFunc>::loadGlyph( UCodePoint codePoint ) {
		FreeTypeChar<T> ** c = this -> charsMap.getValueI( codePoint );

		if ( !c ) {
			if ( this -> ftFace ) {
				FreeTypeChar<T> * newChar = new FreeTypeChar<T>( this -> ftFace, codePoint, this -> loadingFunctor );
				if ( codePoint < 256 )
					this -> asciiMap[codePoint] = newChar;
				else
					this -> charsMap.insert( codePoint, newChar );
				return newChar;
			} else {
				return NULL;
			}
		} else {
			return *c;
		}
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::loadGlyph( const UTF8String & str ) {
		UCodePoint codePoint;
		for ( auto it = str.getBegin(); str.iterate( &it, &codePoint );) {
			loadGlyph( codePoint );
		}
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::reloadGlyphs(  ) {
		for ( size_t i( 0 ); i < 256; i++ ) {
			if ( this -> asciiMap[i] ) {
				delete this -> asciiMap[i];
				if ( this -> ftFace ) this -> asciiMap[i] = new FreeTypeChar<T>( this -> ftFace, UCodePoint(i), this -> loadingFunctor );
				else this -> asciiMap[i] = NULL;
			}
		}
		for ( auto it = this -> charsMap.getBegin(); it != this -> charsMap.getEnd(); it++ ) {
			delete this -> charsMap.getValueIt(it);
			if ( this -> ftFace ) this -> charsMap.setValueIt( it, new FreeTypeChar<T>( this -> ftFace, this -> charsMap.getIndexit(it), this -> loadingFunctor ) );
			else this -> charsMap.setValueIt( it, NULL );
		}
		this -> charsMap.eraseValueAll( NULL );
	}

	template<typename T, typename LoadingFunc>
	const Math::Vec2<float> & FontT<T, LoadingFunc>::getDrawingBias() const {
		return this -> loadingFunctor.getBias();
	}
	template<typename T, typename LoadingFunc>
	const Rectangle & FontT<T, LoadingFunc>::getMargins() const {
		return this -> loadingFunctor.getMargins();
	}


	template<typename T, typename LoadingFunc>
	template<typename Stream>
	bool FontT<T, LoadingFunc>::write(Stream* stream ) const {
		if ( !IO::write( stream, &this -> memorySize ) )
			return false;
		if ( !IO::write( stream, this -> memoryFontObject, this -> memorySize ) )
			return false;

		if ( !IO::write( stream, &this -> pixSize ) )
			return false;
		if ( !IO::write( stream, &this -> lineHeight ) )
			return false;
		if ( !IO::write( stream, &this -> wordSpace ) )
			return false;
		if ( !IO::write( stream, &this -> loadingFunctor ) )
			return false;

		size_t nbCharsLoaded( 0 );
		for ( auto it = this -> charsMap.getBegin(); it != this -> charsMap.getEnd(); this -> charsMap.iterate( &it ) ) {
			nbCharsLoaded++;
		}
		for ( size_t i( 0 ); i < 256; i++ ) {
			if ( this -> asciiMap[i] ) 
				nbCharsLoaded++;
		}
		

		if ( !IO::write( stream, &nbCharsLoaded ) )
			return false;

		for ( auto it = this -> charsMap.getBegin(); it != this -> charsMap.getEnd(); this -> charsMap.iterate( &it ) ) {
			if ( !IO::write( stream, this -> charsMap.getValueIt(it) ) )
				return false;
		}

		for ( size_t i( 0 ); i < 256; i++ ) {
			if ( this -> asciiMap[i] ) {
				if ( !IO::write( stream, this -> asciiMap[i] ) )
					return false;
			}
		}


		return true;
	}



	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::_clear( ) {
		_unload();
		_nullify();
		this -> pixSize = 0.0f;
		this -> lineHeight = 0.0f;
		this -> wordSpace = 0.0f;
	}

	template<typename T, typename LoadingFunc>
	template<typename Stream>
	bool FontT<T, LoadingFunc>::read( Stream * stream, int verbose ) {
		_unload();
		_nullify();
		if ( !_read( stream ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename T, typename LoadingFunc>
	template<typename Stream>
	bool FontT<T, LoadingFunc>::_read( Stream * stream ) {


		if ( !IO::read( stream, &this -> memorySize , verbose - 1 ) ) 
			return false;
		

		// Clamp the size with a big value in case of file corruption
		this -> memorySize = Math::min( this -> memorySize, size_t( 100000000 ) );

		if ( this -> memorySize ) this -> memoryFontObject = new char[this -> memorySize];
		else this -> memoryFontObject = NULL;

		if ( !IO::read( stream, this -> memoryFontObject, this -> memorySize ) )
			return false;
		
		if ( !IO::read( stream, &this -> pixSize , verbose - 1 ) ) 
			return false;
		if ( !IO::read( stream, &this -> lineHeight , verbose - 1 ) ) 
			return false;
		if ( !IO::read( stream, &this -> wordSpace , verbose - 1 ) ) 
			return false;
		if ( !IO::read( stream, &this -> loadingFunctor , verbose - 1 ) ) 
			return false;
		
		_loadFreeType( this -> memoryFontObject, this -> memorySize, this -> pixSize );

		size_t nbCharsLoaded;
		if ( !IO::read( stream, &nbCharsLoaded, verbose -1 ) )
			return false;

		nbCharsLoaded = Math::min( nbCharsLoaded, size_t( 100000 ) );

		for ( size_t i( 0 ); i < nbCharsLoaded; i++ ) {
			FreeTypeChar<T> * newChar = new FreeTypeChar<T>( );

			if ( newChar -> read( stream ) ) {
				if ( newChar -> getCodePoint() < 256 )
					this -> asciiMap[newChar -> getCodePoint()] = newChar;
				else
					this -> charsMap.insert( newChar -> getCodePoint(), newChar );
			} else {
				delete newChar;
				return false;
			}
			
		}

		return true;
	}

	template<typename T, typename LoadingFunc>
	float FontT<T, LoadingFunc>::getLineHeight() const {
		return this -> lineHeight;
	}

	template<typename T, typename LoadingFunc>
	float FontT<T, LoadingFunc>::getWordSpace() const {
		return this -> wordSpace;
	}

	template<typename T, typename LoadingFunc>
	Math::Rectangle<int> FontT<T, LoadingFunc>::computeRectangle( const UTF8String & text ) const {

		UCodePoint codePoint;
		Math::Rectangle<int> rectangle( 0, this -> getLineHeight(), 0, 0 );
		float currentPosX(0.0f);

		for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
			if ( codePoint == UCodePoint('\n') ) {
				rectangle.setTop( rectangle.getTop() + getLineHeight() );
				rectangle.setRight( Math::max<int>( rectangle.getRight(), currentPosX ) );
				currentPosX = 0;
			} else if ( codePoint == UCodePoint(' ') ) {
				currentPosX += getWordSpace();
			} else {
				const FreeTypeChar * c = this -> operator []( codePoint );
				if ( c ) {
					rectangle.setBottom( Math::min<int>( rectangle.getBottom(), -( c -> getHoriOffsetY() ) ) );
					currentPosX += c -> getHoriAdvance();
				}
			}
		}
		rectangle.setRight( Math::max<int>( rectangle.getRight(), currentPosX ) );


		return rectangle;
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::computeLineWidth( Vector<float> * vector, const UTF8String & text ) const {
		float currentPosX( 0 );
		UCodePoint codePoint;

		for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
			if ( codePoint < 33 ) {// If the code point is a special char
				if ( codePoint == UCodePoint('\n') ) {
					vector -> push( currentPosX * 0.5f );
					currentPosX = 0;
				} else if ( codePoint == UCodePoint(' ') )
					currentPosX += font.getWordSpace();
			} else {
				const FreeTypeChar<T> * c = (*this)[codePoint];
				if ( c ) currentPosX += c -> getHoriAdvance();	
			}
		}
		vector -> push( currentPosX * 0.5f );
	}


	

	template<typename T, typename LoadingFunc>
	bool FontT<T, LoadingFunc>::_loadFreeType( const char * fileDump, size_t size, float pixSize ) {
		if ( fileDump && size ) {
			//Load the FreeType library
			if ( FT_Init_FreeType( &this -> ftLib ) ) {
				Log::displayError( "Error when loading the FreeType library." );
				this -> ftFace = NULL;
				this -> ftLib = NULL;
				return false;
			}

			//Load the Font file in FreeType
			if ( FT_New_Memory_Face( this -> ftLib, ( FT_Byte * ) fileDump, size, 0, &this -> ftFace ) ) {
				Log::displayError( StringASCII( "Error while opening the font file " ) );
				FT_Done_FreeType( this -> ftLib );
				this -> ftLib = NULL;
				this -> ftFace = NULL;
				return false;
			}

			FT_Set_Pixel_Sizes( this -> ftFace, pixSize, pixSize );
			return true;
		} 
		this -> ftLib = NULL;
		this -> ftFace = NULL;
		return false;
	}


	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::_move( FontT<T, LoadingFunc> && font ) {
		this -> charsMap = Utility::toRValue( font.charsMap );
		for ( int i( 0 ); i < 256; i++ )
			this -> asciiMap[i] = Utility::toRValue( font.asciiMap[i] );

		this -> ftLib = Utility::toRValue( font.ftLib );
		this -> ftFace = Utility::toRValue( font.ftFace );
		this -> pixSize = Utility::toRValue( font.pixSize );
		this -> lineHeight = Utility::toRValue( font.lineHeight );
		this -> wordSpace = Utility::toRValue( font.wordSpace );
		this -> memoryFontObject = Utility::toRValue( font.memoryFontObject );
		this -> memorySize = Utility::toRValue( font.memorySize );
		this -> loadingFunctor = Utility::toRValue( font.loadingFunctor );
	}

	template<typename T, typename LoadingFunc>
	void FontT<T, LoadingFunc>::_copy( const FontT<T, LoadingFunc> & font ) {
		this -> pixSize = font.pixSize;
		this -> lineHeight = font.lineHeight;
		this -> wordSpace = font.wordSpace;
		this -> loadingFunctor = font.loadingFunctor;
		
		if ( font.memoryFontObject ) {
			this -> memoryFontObject = new char[font.memorySize];
			this -> memorySize = font.memorySize;
			Utility::copy( this -> memoryFontObject, font.memoryFontObject, font.memorySize );
			_loadFreeType( this -> memoryFontObject, this -> memorySize, this -> pixSize );
		} else {
			this -> memoryFontObject = NULL;
			this -> memorySize = 0;
			this -> ftLib = NULL;
			this -> ftFace = NULL;
		}

		for ( int i( 0 ); i < 256; i++ ) {
			if ( font.asciiMap[i] )
				this -> asciiMap[i] = new FreeTypeChar<T>( *( font.asciiMap[i] ) );
			else
				this -> asciiMap[i] = NULL;
		}

		for ( auto it( font.charsMap.getBegin() ); it != font.charsMap.getEnd(); font.charsMap.iterate( &it ) ) {
			this -> charsMap.insert( this -> charsMap.getIndexIt( it ), new FreeTypeChar<T>( *( this -> charsMap.getValueIt(it) ) ) );
		}

		
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc> & FontT<T, LoadingFunc>::operator=( FontT<T, LoadingFunc> && font ) {
		_unload();
		_move( Utility::toRValue( font ) );
		return *this;
	}

	template<typename T, typename LoadingFunc>
	FontT<T, LoadingFunc> & FontT<T, LoadingFunc>::operator=( const FontT<T, LoadingFunc> & font ) {
		_unload();
		_copy( font );
		return *this;
	}

}
