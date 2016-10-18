///@file Text.h
///@brief File containing the Text Object 
///@date 17/10/16 (DMY)
///@author Clement Gerber
#pragma once


#include "Image.h"
#include "Font.h"

namespace Graphic {




	template<typename T>
	class Text : public ImageT<T> {
	public:

		///@brief Empty constructor
		///@brief format Format to be used for the image render
		Text( Format format = Format::RGBA );


		///@brief Constructor which render directly
		///@param font Font file used to render
		///@param str String to be rendered
		///@param centering How the text has to be centered in the image
		///@param format Format of the resulting image
		template<typename LoadingFunc>
		Text( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering = Math::Vec2<bool>(false), Format format = Format::RGBA );

		//Text( const Text & text );

		//Text( Text && text );

		//Text & operator=( const Text & text );
		//Text & operator=( Text && text );


		///@brief set the text to be rendered
		///@param font Font file used to render
		///@param str String to be rendered
		///@param centering How the text has to be centered in the image
		template<typename LoadingFunc>
		void setText( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering = Math::Vec2<bool>( false ) );



		//const Math::Vec2<bool> & getCentering() const;
		//const Math::Rectangle<float> & getMargins() const;
		const Math::Vec2<float> & getBias() const;



		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		//bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		//bool write( std::fstream * fileStream ) const;
	private:
		template<typename LoadingFunc, typename Functor>
		void _setText( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering, Functor & func );
		void _clear();
		

		Math::Vec2<bool> centering;
		Math::Rectangle<float> margins;
		Math::Vec2<float> bias;
		Vector<float> linesWidth;
		UTF8String str;
	};

	template<typename T>
	const Math::Vec2<float> & Text<T>::getBias() const {
		return this -> bias;
	}

	template<typename T>
	void Text<T>::_clear() {
		ImageT<T>::clear();
		this -> centering.x = false;
		this -> centering.y = false;
		this -> margins.x = 0.0f;
		this -> margins.y = 0.0f;
		this -> bias.x = 0.0f;
		this -> bias.y = 0.0f;
		this -> linesWidth.clear();
		this -> str.clear();
	}

	template<typename T>
	template<typename LoadingFunc>
	Text<T>::Text( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering, Format format ) : ImageT<T>(format) {
		setText(font, str, centering);
	}

	template<typename T>
	Text<T>::Text( Format format ) : ImageT<T>( format ) ,
		centering( false ),
		margins( 0.0f ),
		bias( 0.0f )
	{

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

		Functor functor(this);
		_setText(font, str, centering, functor );
	}

	template<typename T>
	template<typename LoadingFunc, typename Functor>
	void Text<T>::_setText( const _Font<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering, Functor & func ) {

		Math::Vec2<float> initPoint;
		UCodePoint codePoint;

		float currentPosX( 0.0f );
		float rectangleHeight( font.getLineHeight() );
		float maxLineWidth( 0.0f );
		Rectangle rectangle(0, 0, 0, 0);
		this -> linesWidth.clear();

		for ( auto it = str.getBegin(); str.iterate( &it, &codePoint ); ) {
			if ( codePoint == UCodePoint( UCodePoint( '\n' ) ) ) {
				rectangleHeight += font.getLineHeight();
				this -> linesWidth.push( currentPosX * 0.5f );
				maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );
				currentPosX = 0;
			} else if ( codePoint == UCodePoint( ' ' ) ) {
				currentPosX += font.getWordSpace();
			} else {
				const FreeTypeChar<T> * c = font[codePoint];
				if ( c ) currentPosX += c -> getHoriAdvance();
			}
		}
		this -> linesWidth.push( currentPosX * 0.5f );
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

			Math::Vec2<float> currentPos( initPoint.x - this -> linesWidth[0] , initPoint.y  );
			unsigned int currentLine( 1 );
			for ( auto it = str.getBegin(); str.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint( '\n' ) ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - this -> linesWidth[currentLine];
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

			Math::Vec2<float> currentPos( initPoint  );
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



#include "Text.hpp"



