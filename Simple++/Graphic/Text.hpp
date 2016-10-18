
namespace Graphic {

	template<typename T>
	const Math::Rectangle<float> & Text<T>::getMargins() const {
		return this -> margins;
	}

	template<typename T>
	const Math::Vec2<bool> & Text<T>::getCentering() const {
		return this -> centering;
	}

	template<typename T>
	bool Text<T>::write( std::fstream * fileStream ) const {
		if ( !IO::write( fileStream, (ImageT<T> *) this ) )
			return false;
		if ( !IO::write( fileStream, &this -> centering ) )
			return false;
		if ( !IO::write( fileStream, &this -> margins ) )
			return false;
		if ( !IO::write( fileStream, &this -> bias ) )
			return false;
		if ( !IO::write( fileStream, &this -> str ) )
			return false;

		return true;
	}

	template<typename T>
	bool Text<T>::read( std::fstream * fileStream ) {
		if ( !IO::read( fileStream, ( ImageT<T> * ) this ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> centering ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> margins ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> bias ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> str ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename T>
	Text<T>::Text( const Text & text ) : ImageT<T>( text ),
		centering( text.centering ),
		margins( text.margins ),
		bias( text.bias ),
		str( text.str ) {

	}


	template<typename T>
	Text<T>::Text( Text && text ) : ImageT<T>( Utility::toRValue( text ) ),
		centering( Utility::toRValue( text.centering ) ),
		margins( Utility::toRValue( text.margins ) ),
		bias( Utility::toRValue( text.bias ) ),
		str( Utility::toRValue( text.str ) ) {

	}

	template<typename T>
	Text<T> & Text<T>::operator=( const Text & text ) {
		ImageT<T>::operator=( text );

		this -> centering = text.centering;
		this -> margins = text.margins;
		this -> bias = text.bias;
		this -> str = text.str;

		return *this;
	}

	template<typename T>
	Text<T> & Text<T>::operator=( Text && text ) {
		ImageT<T>::operator=( Utility::toRValue( text ) );

		this -> centering = Utility::toRValue( text.centering );
		this -> margins = Utility::toRValue( text.margins );
		this -> bias = Utility::toRValue( text.bias );
		this -> str = Utility::toRValue( text.str );

		return *this;
	}

	template<typename T>
	const Math::Vec2<float> & Text<T>::getBias() const {
		return this -> bias;
	}

	template<typename T>
	void Text<T>::_clear() {
		ImageT<T>::clear();
		this -> centering.x = false;
		this -> centering.y = false;
		this -> margins.setLeft( 0.0f );
		this -> margins.setBottom( 0.0f );
		this -> margins.setRight( 0.0f );
		this -> margins.setTop( 0.0f );
		this -> bias.x = 0.0f;
		this -> bias.y = 0.0f;
		this -> str.clear();
	}

	template<typename T>
	template<typename LoadingFunc>
	Text<T>::Text( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering, Format format ) : ImageT<T>( format ) {
		setText( font, str, centering );
	}

	template<typename T>
	Text<T>::Text( Format format ) : ImageT<T>( format ),
		centering( false ),
		margins( 0.0f ),
		bias( 0.0f ) {

	}


	template<typename T>
	template<typename LoadingFunc>
	void Text<T>::setText( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering ) {
		this -> str = str;
		this -> centering = centering;

		struct Functor {
			Functor( ImageT<T> * image ) : image( image ) {}
			void operator()( float x, float y, const ImageT<T> & c ) {
				this -> image -> drawImage<BlendingFunc::Normal, false>( Point( x, y ), c, Rectangle( c.getSize() ), BlendingFunc::Normal() );
			}
			void onBegin( const Rectangle & rect ) {}
			ImageT<T> * image;
		};

		Functor functor( this );
		_setText( font, str, centering, functor );
	}

	template<typename T>
	template<typename LoadingFunc, typename Functor>
	void Text<T>::_setText( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering, Functor & func ) {

		Math::Vec2<float> initPoint;
		UCodePoint codePoint;

		float currentPosX( 0.0f );
		float rectangleHeight( font.getLineHeight() );
		float maxLineWidth( 0.0f );
		Rectangle rectangle( 0, 0, 0, 0 );
		Vector<float> linesWidth;
		linesWidth.reserve( 10 );

		for ( auto it = str.getBegin(); str.iterate( &it, &codePoint ); ) {
			if ( codePoint == UCodePoint( UCodePoint( '\n' ) ) ) {
				rectangleHeight += font.getLineHeight();
				linesWidth.push( currentPosX * 0.5f );
				maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );
				currentPosX = 0;
			} else if ( codePoint == UCodePoint( ' ' ) ) {
				currentPosX += font.getWordSpace();
			} else {
				const FreeTypeChar<T> * c = font[codePoint];
				if ( c ) currentPosX += c -> getHoriAdvance();
			}
		}
		linesWidth.push( currentPosX * 0.5f );
		maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );

		// Add Margins
		rectangle.setTop( Math::ceil( rectangleHeight + font.getMargins().getTop() + font.getMargins().getBottom() ) );
		rectangle.setRight( Math::ceil( maxLineWidth + font.getMargins().getLeft() + font.getMargins().getRight() ) );

		// Clear the image with a new size
		clear( Math::Vec2<Size>( rectangle.getRight(), rectangle.getTop() ) );

		// Use of memset for optimizations (because 0 of float/int/double/char is a representation of 0x00)
		memset( getDatas(), 0, getNbPixels() * getNbComponents() );

		float marginY( font.getLineHeight() * 0.7f );

		initPoint.y = rectangleHeight - marginY;
		if ( centering.y ) {
			this -> bias.y = -( rectangleHeight * 0.5f ) + font.getDrawingBias().y;
		} else {
			this -> bias.y = font.getDrawingBias().y - font.getLineHeight() * 0.3f;
		}

		if ( centering.x ) {
			initPoint.x = ( maxLineWidth * 0.5f );
			this -> bias.x = -( maxLineWidth * 0.5f ) + font.getDrawingBias().x;
		} else {
			initPoint.x = 0.0f;
			this -> bias.x = font.getDrawingBias().x;
		}

		// DRAW !!!


		if ( centering.x ) {
			func.onBegin( rectangle );

			Math::Vec2<float> currentPos( initPoint.x - linesWidth[0], initPoint.y );
			unsigned int currentLine( 1 );
			for ( auto it = str.getBegin(); str.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint( '\n' ) ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - linesWidth[currentLine];
					currentLine++;
				} else if ( codePoint == UCodePoint( ' ' ) ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		} else {
			func.onBegin( rectangle );

			Math::Vec2<float> currentPos( initPoint );
			for ( auto it = str.getBegin(); str.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint( '\n' ) ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == UCodePoint( ' ' ) ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		}




	}

}
