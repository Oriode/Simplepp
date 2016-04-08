#pragma once

#include "Font.h"
#include "BasicLoadableIO.h"



namespace Graphic {

	class FontLoadable : public BasicLoadableIO, public Font {
	public:

		enum LoadingType {
			FTFILE,	///Loading using a standard font file
			FILE		///Loading using a special format only used by this code.
		};


		///@brief constructor that take a filename of a special font file (file created by saveToFile())
		///@param fileName Path to the file to open
		///@param pixSize Size of the loaded font.
		FontLoadable(const WString & fileName);


		///@brief constructor that take a filename of a font file (ttf, ttc, cff...)
		///@param fileName Path to the file to open
		///@param pixSize Size of the loaded font.
		FontLoadable(const WString & fileName, int pixSize);



		~FontLoadable();

	protected:
		///@brief function to be overloaded to add action during the loading process.
		virtual void onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		virtual void onUnload() override;

		///@brief function to be overloaded to set the action when reading from a stream.
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onRead(std::fstream * fileStream) override;

		///@brief function to be overloaded to set the action when writing from a stream.
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onWrite(std::fstream * fileStream) const override;

	private:
		WString fileName;
		LoadingType loadingType;


	};


}


