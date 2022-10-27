


namespace Graphic {

	template<typename T>
	FreeTypeChar<T>::FreeTypeChar() : ImageT<T>() {

	}

	template<typename T>
	template<typename LoadingFunc>
	FreeTypeChar<T>::FreeTypeChar( FT_Face ftFace, UTF8String::CodePoint codePoint, LoadingFunc & createImageFunctor ) :
		ImageT<T>( Format::R ),
		uCodePoint( codePoint ) {

		unsigned int glyphindex = FT_Get_Char_Index( ftFace, this -> uCodePoint );

		if ( glyphindex == 0 ) {
			ERROR_SPP( StringASCII( "No glyph founded for character " ) << this -> uCodePoint );
			return;
		}
		FT_Load_Glyph( ftFace, glyphindex, FT_LOAD_DEFAULT );
		FT_GlyphSlot ftGlyph = ftFace -> glyph;

		if ( ftGlyph -> format != FT_GLYPH_FORMAT_BITMAP ) {
			if ( FT_Render_Glyph( ftFace -> glyph, FT_RENDER_MODE_NORMAL ) ) {
				ERROR_SPP( StringASCII( "Error while rendering the Unicode character " ) << codePoint );
			}
		}



		this -> size.x = float( ftGlyph -> metrics.width ) / 64.0f;
		this -> size.y = float( ftGlyph -> metrics.height ) / 64.0f;
		this -> horiBearing.x = float( ftGlyph -> metrics.horiBearingX ) / 64.0f;
		this -> horiBearing.y = float( ftGlyph -> metrics.horiBearingY ) / 64.0f;
		this -> horiAdvance = float( ftGlyph -> metrics.horiAdvance ) / 64.0f;

		//this -> vertBearing.x = float(ftGlyph -> metrics.vertBearingX) / 64.0f;
		//this -> vertBearing.y = float(ftGlyph -> metrics.vertBearingY) / 64.0f;
		//this -> vertAdvance = float(ftGlyph -> metrics.vertAdvance) / 64.0f;

		this -> horiOffsetY = this -> horiBearing.y - this -> size.y;

		FT_Bitmap * ftBitmap = &ftGlyph -> bitmap;

		createImageFunctor( this, ( unsigned char * ) ( ftBitmap -> buffer ), Math::Vec2<Size>( ftBitmap -> width, ftBitmap -> rows ) );
	}

	template<typename T>
	FreeTypeChar<T>::FreeTypeChar( const FreeTypeChar<T> & c ) :
		Image( c ),
		uCodePoint( c.uCodePoint ),
		size( c.size ),
		horiOffsetY( c.horiOffsetY ),
		horiBearing( c.horiBearing ),
		horiAdvance( c.horiAdvance ) {

	}

	template<typename T>
	FreeTypeChar<T>::FreeTypeChar( FreeTypeChar<T> && c ) :
		ImageT<T>( Utility::toRValue( c ) ),
		uCodePoint( Utility::toRValue( c.uCodePoint ) ),
		size( Utility::toRValue( c.size ) ),
		horiOffsetY( Utility::toRValue( c.horiOffsetY ) ),
		horiBearing( Utility::toRValue( c.horiBearing ) ),
		horiAdvance( Utility::toRValue( c.horiAdvance ) ) {

	}

	template<typename T>
	template<typename Stream>
	FreeTypeChar<T>::FreeTypeChar( Stream * stream ) :
		ImageT<T>( stream ) {
		IO::read( stream, &this -> uCodePoint );
		IO::read( stream, &this -> size );
		IO::read( stream, &this -> horiBearing );
		IO::read( stream, &this -> horiOffsetY );
		IO::read( stream, &this -> horiAdvance );
	}


	template<typename T>
	FreeTypeChar<T>::~FreeTypeChar() {
	}

	template<typename T>
	FreeTypeChar<T> & FreeTypeChar<T>::operator=( const FreeTypeChar<T> & c ) {
		Image::operator=( c );
		this -> uCodePoint = c.uCodePoint;
		this -> size = c.size;
		this -> horiOffsetY = c.horiOffsetY;
		this -> horiBearing = c.horiBearing;
		this -> horiAdvance = c.horiAdvance;

		return *this;
	}

	template<typename T>
	FreeTypeChar<T> & FreeTypeChar<T>::operator=( FreeTypeChar<T> && c ) {
		Image::operator=( Utility::toRValue( c ) );
		this -> uCodePoint = Utility::toRValue( c.uCodePoint );
		this -> size = Utility::toRValue( c.size );
		this -> horiOffsetY = Utility::toRValue( c.horiOffsetY );
		this -> horiBearing = Utility::toRValue( c.horiBearing );
		this -> horiAdvance = Utility::toRValue( c.horiAdvance );

		return *this;
	}

	template<typename T>
	float FreeTypeChar<T>::getHoriBearingX() const {
		return this -> horiBearing.x;
	}

	template<typename T>
	float FreeTypeChar<T>::getHoriBearingY() const {
		return this -> horiBearing.y;
	}

	template<typename T>
	const Math::vec2f & FreeTypeChar<T>::getHoriBearing() const {
		return this -> horiBearing;
	}

	template<typename T>
	float FreeTypeChar<T>::getHoriOffsetY() const {
		return this -> horiOffsetY;
	}

	template<typename T>
	float FreeTypeChar<T>::getHoriAdvance() const {
		return this -> horiAdvance;
	}

	template<typename T>
	UTF8String::CodePoint FreeTypeChar<T>::getCodePoint() const {
		return this -> uCodePoint;
	}

	template<typename T>
	void FreeTypeChar<T>::_clear() {
		ImageT<T>::clear();

		this -> uCodePoint = 0;

		this -> size.x = 0.0f;
		this -> size.y = 0.0f;

		this -> horiBearing.x = 0.0f;
		this -> horiBearing.y = 0.0f;

		this -> horiOffsetY = 0.0f;
		this -> horiAdvance = 0.0f;
	}

	template<typename T>
	template<typename Stream>
	bool FreeTypeChar<T>::read( Stream * stream ) {
		if ( !Image::read( stream ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> uCodePoint ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> size ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> horiBearing ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> horiOffsetY ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> horiAdvance ) ) {
			_clear();
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename Stream>
	bool FreeTypeChar<T>::write( Stream * stream ) const {
		if ( !Image::write( stream ) )
			return false;

		if ( !IO::write( stream, &this -> uCodePoint ) )
			return false;
		if ( !IO::write( stream, &this -> size ) )
			return false;
		if ( !IO::write( stream, &this -> horiBearing ) )
			return false;
		if ( !IO::write( stream, &this -> horiOffsetY ) )
			return false;
		if ( !IO::write( stream, &this -> horiAdvance ) )
			return false;

		return true;
	}

}

