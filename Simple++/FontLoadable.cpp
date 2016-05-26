#include "FontLoadable.h"



namespace Graphic {





	FontLoadable::FontLoadable(const WString & fileName) : 
		Font(ctor::null),
		loadingType(LoadingType::FILE),
		fileName(fileName)
	{

	}

	FontLoadable::FontLoadable(const WString & fileName, int pixSize) :
		Font(ctor::null),
		loadingType(LoadingType::FTFILE),
		fileName(fileName)
	{
		_setPixSize(pixSize);
	}



	FontLoadable::~FontLoadable() {
		unload();
	}


	void FontLoadable::onLoad() {
		switch ( this -> loadingType ) {
		case LoadingType::FTFILE: {
			this -> memorySize = IO::readToBuffer(this -> fileName, &this -> memoryFontObject);
			if ( this -> memorySize == -1 ) {
				Log::displayError(String("Unable to open the font file : ") << this -> fileName);
				return;
			}

			_loadFreeType(this -> memoryFontObject, this -> memorySize);


			break;
		} case LoadingType::FILE: {
			std::fstream file(this -> fileName.getData(), std::ios::in | std::ios::binary);
			if ( file.is_open() ) {
				if ( !onRead(&file) ) {
					error(String("Error while reading the file : ") << this -> fileName);
				}
				file.close();
			} else {
				error(String("Error while opening the file : ") << this -> fileName);
			}

			break;
		}
		}
	}

	void FontLoadable::onUnload() {
		_unload();
	}

	bool FontLoadable::onRead(std::fstream * fileStream) {
		return Font::_read(fileStream);
	}

	bool FontLoadable::onWrite(std::fstream * fileStream) const {
		return Font::write(fileStream);
	}

}

