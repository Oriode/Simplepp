#include "FreeTypeChar.h"




namespace Graphic {


	FreeTypeChar::FreeTypeChar(FT_Face ftFace, UTF8String::CodePoint codePoint) : 
		Image(Format::R),
		uCodePoint(codePoint)
	{

		unsigned int glyphindex = FT_Get_Char_Index(ftFace, this -> uCodePoint);

		if ( glyphindex == 0 ) {
			error(String("No glyph founded for character ") << this -> uCodePoint);
			return;
		}
		FT_Load_Glyph(ftFace, glyphindex, FT_LOAD_DEFAULT);
		FT_GlyphSlot ftGlyph = ftFace -> glyph;

		if ( ftGlyph -> format != FT_GLYPH_FORMAT_BITMAP ) {
			if ( FT_Render_Glyph(ftFace -> glyph, FT_RENDER_MODE_NORMAL) ) {
				error(String("Error while rendering the Unicode character ") << codePoint);
			}
		}



		this -> size.x = float(ftGlyph -> metrics.width) / 64.0f;
		this -> size.y = float(ftGlyph -> metrics.height) / 64.0f;
		this -> horiBearing.x = float(ftGlyph -> metrics.horiBearingX) / 64.0f;
		this -> horiBearing.y = float(ftGlyph -> metrics.horiBearingY) / 64.0f;
		this -> horiAdvance = float(ftGlyph -> metrics.horiAdvance) / 64.0f;

		//this -> vertBearing.x = float(ftGlyph -> metrics.vertBearingX) / 64.0f;
		//this -> vertBearing.y = float(ftGlyph -> metrics.vertBearingY) / 64.0f;
		//this -> vertAdvance = float(ftGlyph -> metrics.vertAdvance) / 64.0f;

		this -> horiOffsetY = this -> horiBearing.y - this -> size.y;

		FT_Bitmap * ftBitmap = &ftGlyph -> bitmap;

		this -> setDatas(ftBitmap -> buffer, Math::vec2ui(ftBitmap -> width, ftBitmap -> rows), LoadingFormat::R, true);
	}


	FreeTypeChar::FreeTypeChar(const FreeTypeChar & c) : 
		Image(c),
		uCodePoint(c.uCodePoint),
		size(c.size),
		horiOffsetY(c.horiOffsetY),
		horiBearing(c.horiBearing),
		horiAdvance(c.horiAdvance)
	{

	}

	FreeTypeChar::FreeTypeChar(FreeTypeChar && c) : 
		Image(Utility::toRValue(c)),
		uCodePoint(Utility::toRValue(c.uCodePoint)),
		size(Utility::toRValue(c.size)),
		horiOffsetY(Utility::toRValue(c.horiOffsetY)),
		horiBearing(Utility::toRValue(c.horiBearing)),
		horiAdvance(Utility::toRValue(c.horiAdvance))
	{

	}

	FreeTypeChar::FreeTypeChar(std::fstream * fileStream) :
		Image(fileStream)
	{
		IO::read(fileStream, &this -> uCodePoint);
		IO::read(fileStream, &this -> size);
		IO::read(fileStream, &this -> horiBearing);
		IO::read(fileStream, &this -> horiOffsetY);
		IO::read(fileStream, &this -> horiAdvance);
	}

	FreeTypeChar::~FreeTypeChar() {
	}


	FreeTypeChar & FreeTypeChar::operator=(const FreeTypeChar & c) {
		Image::operator=(c);
		this -> uCodePoint = c.uCodePoint;
		this -> size = c.size;
		this -> horiOffsetY = c.horiOffsetY;
		this -> horiBearing = c.horiBearing;
		this -> horiAdvance = c.horiAdvance;

		return *this;
	}

	FreeTypeChar & FreeTypeChar::operator=(FreeTypeChar && c) {
		Image::operator=(Utility::toRValue(c));
		this -> uCodePoint = Utility::toRValue(c.uCodePoint);
		this -> size = Utility::toRValue(c.size);
		this -> horiOffsetY = Utility::toRValue(c.horiOffsetY);
		this -> horiBearing = Utility::toRValue(c.horiBearing);
		this -> horiAdvance = Utility::toRValue(c.horiAdvance);

		return *this;
	}

	float FreeTypeChar::getHoriBearingX() const {
		return this -> horiBearing.x;
	}

	float FreeTypeChar::getHoriBearingY() const {
		return this -> horiBearing.y;
	}

	const Math::vec2f & FreeTypeChar::getHoriBearing() const {
		return this -> horiBearing;
	}

	float FreeTypeChar::getHoriOffsetY() const {
		return this -> horiOffsetY;
	}

	float FreeTypeChar::getHoriAdvance() const {
		return this -> horiAdvance;
	}

	UTF8String::CodePoint FreeTypeChar::getCodePoint() const {
		return this -> uCodePoint;
	}

	bool FreeTypeChar::read(std::fstream * fileStream) {
		if ( !Image::read(fileStream) )
			return false;

		if ( !IO::read(fileStream, &this -> uCodePoint) )
			return false;
		if ( !IO::read(fileStream, &this -> size) )
			return false;
		if ( !IO::read(fileStream, &this -> horiBearing) )
			return false;
		if ( !IO::read(fileStream, &this -> horiOffsetY) )
			return false;
		if ( !IO::read(fileStream, &this -> horiAdvance) )
			return false;
		
		return true;
	}

	bool FreeTypeChar::write(std::fstream * fileStream) const {
		if ( !Image::write(fileStream) )
			return false;

		if ( !IO::write(fileStream, &this -> uCodePoint) )
			return false;
		if ( !IO::write(fileStream, &this -> size) )
			return false;
		if ( !IO::write(fileStream, &this -> horiBearing) )
			return false;
		if ( !IO::write(fileStream, &this -> horiOffsetY) )
			return false;
		if ( !IO::write(fileStream, &this -> horiAdvance) )
			return false;

		return true;
	}

}

