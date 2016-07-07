#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H

#include "../UTF8String.h"


#include "Image.h"

namespace Graphic {

	class FreeTypeChar : public Image {
	public:
		///@brief Constructor
		///@param ftFace FreeType char object used to create this glyph.
		///@param Unicode codePoint representing this char.
		FreeTypeChar( FT_Face ftFace, UTF8String::CodePoint codePoint );

		///@brief Copy Constructor
		///@param c Char to be copied.
		FreeTypeChar( const FreeTypeChar & c );


		///@brief Constructor from a file Stream
		///@param fileStream file stream to read
		FreeTypeChar( std::fstream * fileStream );


		///@brief move Constructor
		///@param c Char to be moved.
		FreeTypeChar( FreeTypeChar && c );
		~FreeTypeChar();


		///@brief Copy operator
		///@param c Char to be copied.
		///@return reference to this
		FreeTypeChar & operator=( const FreeTypeChar & c );

		///@brief move operator
		///@param c Char to be copied.
		///@return reference to this
		FreeTypeChar & operator=( FreeTypeChar && c );


		/*	///@brief return the width of this glyph
			///@return width of this glyph in pixels
			float getWidth() const;


			///@brief return the height of this glyph
			///@return height of this glyph in pixels
			float getHeight() const;


			///@brief return the size of this glyph
			///@return size of this glyph
			const Math::vec2f & getSize() const;*/

			///@brief return the X coordinate of the horizontal bearing of this glyph
			///@return X bearing in pixels
		float getHoriBearingX() const;

		///@brief return the Y coordinate of the horizontal bearing of this glyph
		///@return Y bearing in pixels
		float getHoriBearingY() const;

		///@brief return the the horizontal bearing of this glyph
		///@return horizontal bearing in pixels
		const Math::vec2f & getHoriBearing() const;

		///@brief Get the Y coordinate of the Horizontal offset.
		///@return Y Offset when using this glyph horizontally
		float getHoriOffsetY() const;

		///@brief Get the advance of this glyph when used horizontally.
		///@return Advance of this glyph in pixels.
		float getHoriAdvance() const;


		///@brief get the code point of this character
		///@return code point in the Unicode table
		UTF8String::CodePoint getCodePoint() const;


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

	private:
		UCodePoint uCodePoint;

		Math::vec2f size;
		Math::vec2f horiBearing;

		float horiOffsetY;
		float horiAdvance;

		//Math::vec2f vertBearing;
		//float vertAdvance;

	};
}


