#pragma once


#include <ft2build.h>
#include FT_FREETYPE_H

#include "../String.h"
#include "../Map.h"
#include "../UTF8String.h"
#include "../Log.h"
#include "../IO/IO.h"


#include "FreeTypeChar.h"

namespace Graphic {

	template<typename T = unsigned char, typename LoadingFunc = FontLoadingFunc::Default>
	class FontT : public IO::BasicIO {
	public:

		class Template {
		public:
			static const UTF8String Ascii;
			static const UTF8String Latin1;
		};


		///@brief Empty constructor
		///@param createImageFunctor Functor to be used to load the glyphs
		///@see FontLoadingFunc
		FontT( const LoadingFunc & createImageFunctor = LoadingFunc() );

		///@brief Constructor from a stream
		///@param stream StreamT to read to create this object
		template<typename Stream>
		FontT( Stream * stream );

		///@brief constructor that take a filename of a font file (ttf, ttc, cff...)
		///@param fileName Path to the file to open
		///@param pixSize GSize of the loaded font.
		///@param loadingFunc Loading Functor (must inherite from FontLoadingFunc::Template)
		FontT( const WString & fileName, int pixSize, const LoadingFunc & loadingFunc = LoadingFunc() );

		///@brief Constructor using a font file dump and his size in bytes
		///@param fileDump memory copy of a font file.
		///@param fileSize size in bytes of the data buffer.
		///@param pixSize GSize in pixels of the font
		///@param loadingFunc Loading Functor (must inherite from FontLoadingFunc::Template)
		FontT( const char * fileDump, size_t fileSize, int pixSize, const LoadingFunc & loadingFunc = LoadingFunc() );

		///@brief Copy constructor
		///@param font Font to be copied
		FontT( const FontT<T, LoadingFunc> & font );

		///@brief move constructor
		///@param font Font to be moved
		FontT( FontT<T, LoadingFunc> && font );

		///@brief Destructor
		~FontT();


		///@brief Copy operator
		///@param font Font to be copied
		///@return reference to THIS
		FontT<T, LoadingFunc> & operator=( const FontT<T, LoadingFunc> & font );

		///@brief Move operator
		///@param font Font from were to move
		///@return reference to THIS
		FontT<T, LoadingFunc> & operator=( FontT<T, LoadingFunc> && font );



		///@brief Retrieve a POINTER to a char using its Unicode codePoint
		///@param codePoint Unicode codePoint
		///@return POINTER to a char (can be NULL if none has been founded)
		FreeTypeChar<T> * operator[]( UCodePoint codePoint );

		///@brief Retrieve a POINTER to a char using its Unicode codePoint
		///@param codePoint Unicode codePoint
		///@return POINTER to a char (can be NULL if none has been founded)
		const FreeTypeChar<T> * operator[]( UCodePoint codePoint ) const;

		///@brief Retrieve the complete map of (Unicode codePoint => POINTERS to char )
		///@return Map of (Unicode codePoint => POINTERS to char )
		const Map<UCodePoint, FreeTypeChar<T> *> & getCharMap() const;

		///@brief load a glyph on this 
		///@return const pointer of the character just created (NULL if nothing was loaded)
		const FreeTypeChar<T> * loadGlyph( UCodePoint codePoint );

		///@brief load all the glyph present inside the string
		void loadGlyph( const UTF8String & str );

		///@brief re load all the already loaded glyphs. Useful if you changed something with the loading functor
		void reloadGlyphs(  );

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;

		///@brief get the line height of this font.
		///@return line height
		float getLineHeight() const;

		///@brief Get the loading functor of this font
		///@return loading functor
		const LoadingFunc & getLoadingFunctor() const;

		///@brief set the loading functor of this image
		///@see reloadGlyphs()
		///@param loadingFunctor Loading Functor (must inherite from FontLoadingFunc::Template)
		void setLoadingFunctor( const LoadingFunc & loadingFunctor ) ;

		///@brief get the Bias using to draw this font (Bias retrieved by the loadingFunc)
		///@return Bias using to draw this font
		const Math::Vec2<float> & getDrawingBias() const;

		///@brief get the margins of the drawing
		///@return margins
		const Rectangle & getMargins() const;

		///@brief get the word space of this font
		///@return word space
		float getWordSpace() const;

		///@brief compute the rectangle of a text using this font.
		///@param 
		///@return the rectangle of this font.
		Math::Rectangle<int> computeRectangle( const UTF8String & text ) const;

		///@brief compute the size of each line of the text
		///@param in out vector Vector to be filled with the values (the vector wont be erased, the values will be pushed into)
		///@param text Text to be analyzed
		void computeLineWidth( Vector<float> * vector, const UTF8String & text ) const;

	protected:
		enum ctor { null };
		
		template<typename Stream>
		bool _read( Stream * stream );
		void _clear();
		void _nullify();
		bool _loadFreeType( const char * fileDump, size_t size, float pixSize );
		void _setPixSize( unsigned int size );
		void _unload();
		void _copy( const FontT<T, LoadingFunc> & font );
		void _move( FontT<T, LoadingFunc> && font );

		Map<UCodePoint, FreeTypeChar<T> *> charsMap;
		FreeTypeChar<T> * asciiMap[256];

		FT_Library ftLib;
		FT_Face ftFace;

		float pixSize;
		float lineHeight;
		float wordSpace;

		char * memoryFontObject;
		size_t memorySize;

		LoadingFunc loadingFunctor;
	};
	






	template<typename T>
	using Font = FontT<T>;

}

#include "Font.hpp"
