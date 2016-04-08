#include "Font.h"

namespace Graphic {

	const UTF8String Font::Template::Ascii = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.+/_-*'\"()[]#^%!?";
	const UTF8String Font::Template::Latin1 = "\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf";

	Font::Font(const WString & fileName, int pixSize) 
	{
		_setPixSize(pixSize);
		this -> memorySize = IO::readToBuffer(fileName, &this -> memoryFontObject);
		if ( this -> memorySize == -1 ) {
			Log::displayError(String("Unable to open the font file : ") << fileName);
		}

		_loadFreeType(this -> memoryFontObject, this -> memorySize);
	}


	Font::Font(const char * fileDump, size_t fileSize) : 
	memorySize(fileSize)
	{
		Vector<char>::copy(this -> memoryFontObject, fileDump, fileSize);
	
		_loadFreeType(fileDump, fileSize);
	}

	Font::Font(ctor) : 
		memoryFontObject(NULL)
	{
		//NULL
	}




	Font::~Font() {
		_unload();
	}

	void Font::_setPixSize(unsigned int size) {
		this -> pixSize = float(size);
		this -> lineHeight = 1.0f * float(this -> pixSize);
		this -> wordSpace = 0.4f * float(this -> pixSize);
	}





	void Font::_unload() {
		if ( this -> memoryFontObject ) {
			FT_Done_Face(this -> ftFace);
			FT_Done_FreeType(this -> ftLib);
			delete[] this -> memoryFontObject;
			this -> memoryFontObject = NULL;
		}
	}

	FreeTypeChar * Font::operator[](UCodePoint codePoint) {
		FreeTypeChar ** c = this -> charsMap.getValue(codePoint);
		if ( c ) {
			return *c;
		} else {
			return NULL;
		}
	}


	const FreeTypeChar * Font::operator[](UCodePoint codePoint) const {
		FreeTypeChar * const * c = this -> charsMap.getValue(codePoint);
		if ( c ) {
			return *c;
		} else {
			return NULL;
		}
	}

	const OrderedMap<UCodePoint, FreeTypeChar *> & Font::getCharMap() const {
		return this -> charsMap;
	}


	
	const FreeTypeChar * Font::loadGlyph(UCodePoint codePoint) {
		if ( !this -> charsMap.existsIndex(codePoint) ) {
			FreeTypeChar * newChar = new FreeTypeChar(this -> ftFace, codePoint);
			this -> charsMap.insert(codePoint, newChar);
			return newChar;
		} else {
			return NULL;
		}
	}

	void Font::loadGlyph(const UTF8String & str) {
		UCodePoint codePoint;
		for ( auto it = str.getBegin(); str.iterate(&it, &codePoint);) {
			loadGlyph(codePoint);
		}
	}

	bool Font::read(std::fstream * fileStream) {
		_unload();
		return _read(fileStream);
	}

	bool Font::write(std::fstream * fileStream) const {
		if ( !IO::write(fileStream, &this -> memorySize) )
			return false;
		if ( !IO::writeBuffer(fileStream, this -> memoryFontObject, this -> memorySize) )
			return false;

		if ( !IO::write(fileStream, &this -> pixSize) )
			return false;
		if ( !IO::write(fileStream, &this -> lineHeight) )
			return false;
		if ( !IO::write(fileStream, &this -> wordSpace) )
			return false;

		OrderedMap<UCodePoint, FreeTypeChar *>::Size nbCharsLoaded = this -> charsMap.getSize();
		if ( !IO::write(fileStream, &nbCharsLoaded) )
			return false;
		for ( auto it = this -> charsMap.getBegin(); it != this -> charsMap.getEnd(); it++ ) {
			if ( !IO::write(fileStream, it ->getValue()) )
				return false;
		}

		return true;
	}



	float Font::getLineHeight() const {
		return this -> lineHeight;
	}

	float Font::getWordSpace() const {
		return this -> wordSpace;
	}

	Math::Rectangle<int> Font::computeRectangle(const UTF8String & text) const {

		UCodePoint codePoint;
		Math::Rectangle<int> rectangle(0, this -> getLineHeight(), 0, 0);
		float currentPosX = 0.0f;

		for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
			if ( codePoint == '\n' ) {
				rectangle.setTop(rectangle.getTop() + getLineHeight());
				rectangle.setRight(Math::max<int>(rectangle.getRight(), currentPosX));
				currentPosX = 0;
			} else if (codePoint == ' '){
				currentPosX += getWordSpace();
			} else {
				const FreeTypeChar * c = this -> operator [](codePoint);
				if ( c ) {
					rectangle.setBottom(Math::min<int>(rectangle.getBottom(), -c -> getHoriOffsetY()));
					currentPosX += c -> getHoriAdvance();
				}
			}
		}
		rectangle.setRight(Math::max<int>(rectangle.getRight(), currentPosX));


		return rectangle;
	}

	bool Font::_read(std::fstream * fileStream) {
		if ( !IO::read(fileStream, &this -> memorySize) )
			return false;
		this -> memoryFontObject = new char[this -> memorySize];
		if ( !IO::readBuffer(fileStream, this -> memoryFontObject, this -> memorySize) )
			return false;

		if ( !IO::read(fileStream, &this -> pixSize) )
			return false;
		if ( !IO::read(fileStream, &this -> lineHeight) )
			return false;
		if ( !IO::read(fileStream, &this -> wordSpace) )
			return false;

		_loadFreeType(this -> memoryFontObject, this -> memorySize);

		OrderedMap<UCodePoint, FreeTypeChar *>::Size nbCharsLoaded;
		if ( !IO::read(fileStream, &nbCharsLoaded) )
			return false;
		for ( OrderedMap<UCodePoint, FreeTypeChar *>::Size i = 0; i < nbCharsLoaded; i++ ) {
			FreeTypeChar * newChar = new FreeTypeChar(fileStream);
			this -> charsMap.insertFast(newChar -> getCodePoint(), newChar);
		}

		return true;
	}

	void Font::_loadFreeType(const char * fileDump, size_t size) {
		//Load the FreeType library
		if ( FT_Init_FreeType(&this -> ftLib) ) {
			Log::displayError("Error when loading the FreeType library.");
		}

		//Load the Font file in FreeType
		if ( FT_New_Memory_Face(this -> ftLib, ( FT_Byte * ) fileDump, size, 0, &this -> ftFace) ) {
			Log::displayError(String("Error while opening the font file "));
		}

		FT_Set_Pixel_Sizes(this -> ftFace, this -> pixSize, this -> pixSize);
	}


}