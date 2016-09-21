#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H

#include "../String.h"
#include "../OrderedMap.h"
#include "../UTF8String.h"
#include "../Log.h"
#include "../IO.h"


#include "FreeTypeChar.h"

namespace Graphic {

	template<typename T = unsigned char>
	class Font : public BasicIO {
	public:

		class Template {
		public:
			static const UTF8String Ascii;
			static const UTF8String Latin1;
		};



		///@brief constructor that take a filename of a font file (ttf, ttc, cff...)
		///@param fileName Path to the file to open
		///@param pixSize Size of the loaded font.
		Font( const WString & fileName, int pixSize );


		///@brief Constructor using a font file dump and his size in bytes
		///@param fileDump memory copy of a font file.
		///@param fileSize size in bytes of the data buffer.
		Font( const char * fileDump, size_t fileSize );



		~Font();



		FreeTypeChar<T> * operator[]( UCodePoint codePoint );

		const FreeTypeChar<T> * operator[]( UCodePoint codePoint ) const;


		const OrderedMap<UCodePoint, FreeTypeChar<T> *> & getCharMap() const;


		///@brief load a glyph on this 
		///@return const pointer of the character just created (NULL if nothing was loaded)
		const FreeTypeChar<T> * loadGlyph( UCodePoint codePoint );

		///@brief load all the glyph present inside the string
		void loadGlyph( const UTF8String & str );

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;


		///@brief get the line height of this font.
		///@return line height
		float getLineHeight() const;



		///@brief get the word space of this font
		///@return word space
		float getWordSpace() const;

		///@brief compute the rectangle of a text using this font.
		///@param 
		///@return the rectangle of this font.
		Math::Rectangle<int> computeRectangle( const UTF8String & text ) const;

	protected:
		enum ctor { null };
		Font( ctor );

		bool _read( std::fstream * fileStream );
		void _loadFreeType( const char * fileDump, size_t size );
		void _setPixSize( unsigned int size );
		void _unload();

		OrderedMap<UCodePoint, FreeTypeChar<T> *> charsMap;
		FreeTypeChar<T> * asciiMap[256];

		FT_Library ftLib;
		FT_Face ftFace;

		float pixSize;
		float lineHeight;
		float wordSpace;

		char * memoryFontObject;
		size_t memorySize;
	};

}

#include "Font.hpp"
