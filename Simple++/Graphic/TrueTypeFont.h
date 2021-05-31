#pragma once

#include "../BasicLoadable.h"

#include "Font.h"



namespace Graphic {

	template<typename T = unsigned char, typename LoadingFunc = FontLoadingFunc::Default>
	class TrueTypeFontT : public BasicLoadable, public FontT<T> {
	public:


		///@brief constructor that take a filename of a font file (ttf, ttc, cff...)
		///@param filePath Path to the file to open
		///@param pixSize Size of the loaded font.
		///@param loadingFunc Loading Functor (must inherite from FontLoadingFunc::Template)
		TrueTypeFontT( const OS::Path & filePath, int pixSize, const LoadingFunc & loadingFunc = LoadingFunc() );



		~TrueTypeFontT();

	protected:
		///@brief function to be overloaded to add action during the loading process.
		///@return True if loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if unloading has succeeded, False otherwise
		virtual bool onUnload() override;

	private:
		OS::Path filePath;

	};

	template<typename T>
	using TrueTypeFont = TrueTypeFontT<T>;

}

#include "TrueTypeFont.hpp"

