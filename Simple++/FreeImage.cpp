#include "FreeImage.h"



FreeImage::FreeImage() :
	loadingType(LoadingType::EMPTY),
	freeImage(NULL),
	size(Math::vec2ui::null),
	loadingFormat(Format::R),
	BPP(getBitsFromFormat(this -> loadingFormat))
{


}

FreeImage::FreeImage(const WString & fileName, Format format, bool invertY, const Math::vec2ui & size)
{
	setFile(fileName, format, invertY, size);
}

FreeImage::FreeImage(const FreeImage & freeImage, const Math::vec2ui & newSize /*= vec2ui::null*/, Filter resampleFilter) :
	BasicLoadable(freeImage),
	fileName(freeImage.fileName),
	size(newSize),
	invertY(freeImage.invertY),
	loadingType(freeImage.loadingType),
	BPP(freeImage.BPP),
	loadingFormat(freeImage.loadingFormat),
	resampleFilter(resampleFilter)
{
	if ( freeImage.isLoaded() ) {
		Math::vec2ui toCopySize = freeImage.getSize();

		if ( this -> size != toCopySize )
			this -> freeImage = FreeImage_Rescale(freeImage.freeImage, this -> size.x, this -> size.y, ( FREE_IMAGE_FILTER ) this -> resampleFilter);
		else
			this -> freeImage = FreeImage_Clone(freeImage.freeImage);
	} else {
		this -> freeImage = freeImage.freeImage;	//Probably NULL
	}
}

FreeImage::FreeImage(const FreeImage & freeImage) :
	BasicLoadable(freeImage),
	fileName(freeImage.fileName),
	size(freeImage.size),
	invertY(invertY),
	loadingType(freeImage.loadingType),
	BPP(freeImage.BPP),
	loadingFormat(freeImage.loadingFormat),
	resampleFilter(freeImage.resampleFilter)
{
	if ( freeImage.isLoaded() ) {
		this -> freeImage = FreeImage_Clone(freeImage.freeImage);
	} else {
		this -> freeImage = freeImage.freeImage;	//Probably NULL
	}
}

FreeImage::FreeImage(FreeImage && freeImage) {
	memcpy(this, &freeImage, sizeof(freeImage));		//copy the whole object
	freeImage.freeImage = NULL;					//set the old buffer to NULL to ensure no other delete
}

FreeImage::~FreeImage(void) {
	unload();
}

void FreeImage::onLoad(){

	switch ( this -> loadingType ) {
	case LoadingType::EMPTY:
		this -> freeImage = FreeImage_Allocate(this -> size.x, this -> size.y, this -> BPP, 0, 0, 0);
		break;

	case LoadingType::FILE:
		// Check the file signature and deduce its format.  
		FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileTypeU(fileName.toCString(), 0);

		// If still unknown, try to guess the file format from the file extension.  
		if ( imageFormat == FIF_UNKNOWN ) {
			imageFormat = FreeImage_GetFIFFromFilenameU(fileName.toCString());
		}

		// If still unkown, return failure.  
		if ( imageFormat == FIF_UNKNOWN ) {
			error("Free Image was unable to detect the file format");
			return;
		}

		// Check that the plugin has reading capabilities and load the file.  
		if ( FreeImage_FIFSupportsReading(imageFormat) ) {
			this -> freeImage = FreeImage_LoadU(imageFormat, fileName.toCString());
		}

		if ( this -> freeImage == NULL ) {
			error("Free Image was unable to load the picture " + fileName);
			return;
		}
		if ( this -> size.x == 0 || this -> size.y == 0 ) {
			this -> size.x = FreeImage_GetWidth(this -> freeImage);
			this -> size.y = FreeImage_GetHeight(this -> freeImage);
		}


		if ( this -> loadingFormat == Format::UNDEFINED ) {
			switch ( FreeImage_GetColorType(this -> freeImage) ) {
			case FIC_PALETTE:
				_updateFormat(Format::R);
				break;
			case FIC_RGB:
				_updateFormat(Format::RGB);
				break;
			default:
				_updateFormat(Format::RGBA);
				break;
			}
		}

		log(this -> fileName << this -> size << " has been loaded successfully !");
		break;

	}

	//if we have to flip vertically.
	if (this -> invertY)
		FreeImage_FlipVertical(this -> freeImage);
	//Change BPP
	if (this -> BPP != FreeImage_GetBPP( this -> freeImage ))
		_updateBPP();
	//resize
	if (this -> size != Math::vec2ui(FreeImage_GetWidth( this -> freeImage ), FreeImage_GetHeight( this -> freeImage )))
		_updateSize();
	
}


void FreeImage::resize( const Math::vec2ui & newSize, Filter resampleFilter){
	this -> resampleFilter = resampleFilter;

	if (isLoaded() && this -> size != newSize ){
		this -> size = newSize;
		_updateSize();
	} else 
		this -> size = newSize;
}

void FreeImage::setFormat( Format format ){
	if (format == Format::UNDEFINED)
		return;
	
	_updateFormat(format);

	if (isLoaded() && this -> BPP != FreeImage_GetBPP( this -> freeImage ))
		_updateBPP();
}

FreeImage::Format FreeImage::getFormat() const{
	return this -> loadingFormat;
}

FIBITMAP * FreeImage::getFreeImage(){
	return this -> freeImage;
}

unsigned int FreeImage::getBPP() const{
	return this ->  BPP;
}

unsigned char * FreeImage::getDatas() const{
	return FreeImage_GetBits(this -> freeImage);
}

void FreeImage::onUnload(){
	if ( this -> freeImage )
		FreeImage_Unload( this -> freeImage ); 
	this -> freeImage = NULL;
}


unsigned int FreeImage::getBitsFromFormat( Format format ){
	switch (format){
	case Format::R:
		return 8;
	case Format::RGB:
		return 24;
	case Format::RGBA:
		return 32;
	default:
		return 24;
	}
}

bool FreeImage::saveToFile( const WString & fileName, SavingFormat savingFormat, unsigned int quality /*= 100*/ ){
	load();

	if ( savingFormat == SavingFormat::JPG ) {
		if ( FreeImage_SaveU((FREE_IMAGE_FORMAT) savingFormat, this -> freeImage, fileName.toCString(), quality) ) {
			log(String("Success writing file : ") << fileName);
			return true;
		} else {
			error(String("error writing file : ") << fileName);
			return false;
		}


	} else {
		if ( FreeImage_SaveU((FREE_IMAGE_FORMAT) savingFormat, this -> freeImage, fileName.toCString()) ){
			log(String("Success writing file : ") << fileName);
			return true;
		} else {
			error(String("error writing file : ") << fileName);
			return false;
		}
	}
	
}


const Math::vec2ui & FreeImage::getSize() const{
	return this -> size;
}



FreeImage & FreeImage::operator=(FreeImage && image) {
	memcpy(this, &freeImage, sizeof(freeImage));		//copy the whole object
	image.freeImage = NULL;						//set the old buffer to NULL to ensure no other delete
	return *this;
}

void FreeImage::setFile(const WString & fileName, Format format /*= UNDEFINED*/, bool invertY, const Math::vec2ui & size) {
	unload();

	this -> invertY = invertY;
	this -> fileName = fileName;
	this -> loadingType = LoadingType::FILE;
	_updateFormat(format);
	this -> resampleFilter = Filter::Bilinear;
	this -> BPP = getBitsFromFormat(format);
	this -> size = size;

	reload();
}

void FreeImage::loadFromDatas( unsigned char * datas, const Math::vec2ui & size, Format format, bool datasInvertY ){
	unload();

	lock();
	setLoading(true);
	_updateFormat(format);
	this -> size = size;
	this -> invertY = datasInvertY;
	this -> loadingType = LoadingType::EMPTY;
	this -> fileName.clear();			//we have no reason to keep a filepath now.


#ifdef WIN32 
	if ( format == Format::RGB || format == Format::RGBA ) {
		//because FreeImage do not care of MASK and use BGR on Windows
		size_t numPixels = this -> size.x * this -> size.y;
		size_t offsetPerPixel = ( this -> BPP / 8 );
		unsigned char * newDatas = new unsigned char[offsetPerPixel * numPixels];

		auto otherIt = datas;
		auto thisIt = newDatas;
		for ( size_t i = 0; i < numPixels; i++ ) {
			thisIt[0] = otherIt[2];
			thisIt[1] = otherIt[1];
			thisIt[2] = otherIt[0];

			otherIt += offsetPerPixel;
			thisIt += offsetPerPixel;
		}
		this -> freeImage = FreeImage_ConvertFromRawBits(newDatas, this -> size.x, this -> size.y, this -> size.x * ( this -> BPP / 8 ), this -> BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, this -> invertY);
		delete[] newDatas;
	} else {
		this -> freeImage = FreeImage_ConvertFromRawBits(datas, this -> size.x, this -> size.y, this -> size.x * ( this -> BPP / 8 ), this -> BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, this -> invertY);
	}
#else
	this -> freeImage = FreeImage_ConvertFromRawBits(datas, this -> size.x, this -> size.y, this -> size.x * ( this -> BPP / 8 ), this -> BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, this -> invertY);
#endif

	setLoading(false);
	setLoaded(true);
	unlock();
}

FreeImage & FreeImage::operator=( const FreeImage & image ){
		this -> fileName = image.fileName;
		this -> size = size;
		this -> invertY = image.invertY;
		this -> loadingType = image.loadingType;
		this -> BPP = image.BPP;
		this -> loadingFormat = image.loadingFormat;
		this -> resampleFilter = image.resampleFilter;

		if ( image.isLoaded() ) {
			lock();
			this -> freeImage = FreeImage_Clone(image.freeImage);
			setLoaded(true);
			unlock();
		} else {
			this -> freeImage = image.freeImage;	//Probably NULL
			setLoaded(false);
		}
	return *this;
}



const WString & FreeImage::getFileName() const{
	return this -> fileName;
}



FreeImage::LoadingType FreeImage::getLoadingType() const{
	return this -> loadingType;
}

void FreeImage::clear(){
	this -> loadingType = LoadingType::EMPTY;
	this -> fileName.clear();
	reload();
}



FreeImage * FreeImage::copy(){
	return new FreeImage(*this);
}



void FreeImage::_updateBPP(){
	FIBITMAP * newBPPImage = NULL;
	if (this -> BPP == 8){
		newBPPImage = FreeImage_ConvertTo8Bits(this -> freeImage);
	} else if (this -> BPP == 24){
		newBPPImage = FreeImage_ConvertTo24Bits(this -> freeImage);
	} else if (this -> BPP == 32){
		newBPPImage = FreeImage_ConvertTo32Bits(this -> freeImage);
	} else {
		error("Wrong format for an image loading");
		return;
	}
	//free this image, not needed now
	FreeImage_Unload( this -> freeImage );
	this -> freeImage = newBPPImage;
	
}

void FreeImage::_updateSize(){
	FIBITMAP * resizedImage = FreeImage_Rescale(this -> freeImage, this -> size.x, this -> size.y , (FREE_IMAGE_FILTER) this -> resampleFilter);
	FreeImage_Unload( freeImage ); 
	freeImage = resizedImage;
}

void FreeImage::_updateFormat(Format format){
	if (this -> loadingFormat == format)
		return;

	this -> loadingFormat = format;

	this -> BPP = getBitsFromFormat(this -> loadingFormat);
	//this -> pixelFormat = getPixelFormat(this -> loadingFormat);
	//this -> sizedInternalFormat = getSizedInternalFormat(this -> loadingFormat);
}

Math::vec4 FreeImage::getPixelf(unsigned int x, unsigned int y) const{
	unsigned int iIndex = (y * this -> size.x + x) * (this -> BPP / 8);


	unsigned char b = 0;
	unsigned char g = 0;
	unsigned char r = 0;
	unsigned char a = 0;

	switch (this -> loadingFormat){
	case Format::R:
		r = getDatas()[iIndex];
		break;
	case Format::RGB:
		b = getDatas()[iIndex];
		g = getDatas()[iIndex + 1];
		r = getDatas()[iIndex + 2];
		break;
	case Format::RGBA:
		b = getDatas()[iIndex];
		g = getDatas()[iIndex + 1];
		r = getDatas()[iIndex + 2];
		a = getDatas()[iIndex + 3];
		break;
	}


	return Math::vec4(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, float(a) / 255.0f);
}

void FreeImage::setFlipY( bool value ){
	if ( isLoaded() && value != this -> invertY) {
		FreeImage_FlipVertical(this -> freeImage);
	}
	this -> invertY = value;
}

bool FreeImage::isYFlipped() const{
	return this -> invertY;
}

BITMAPINFO * FreeImage::getInfos(){
	if (isLoaded()){
		return FreeImage_GetInfo(this -> freeImage);
	} else {
		return NULL;
	}
}

/*
Texture::PixelFormat FreeImage::getPixelFormat() const{
	return this -> pixelFormat;
}

Texture::PixelFormat FreeImage::getPixelFormat( Format freeImageFormat ){
	switch(freeImageFormat){
	case FreeImage::Format::R:
		return Texture::PixelFormat::R;
	case FreeImage::Format::RGB:
		return Texture::PixelFormat::BGR;
	case FreeImage::Format::RGBA:
		return Texture::PixelFormat::BGRA;
	default:
		return Texture::PixelFormat::BGR;
	}
}


Texture::SizedInternalFormat FreeImage::getSizedInternalFormat( FreeImage::Format freeImageFormat ){
	switch(freeImageFormat){
	case FreeImage::Format::R:
		return Texture::SizedInternalFormat::R8;
	case FreeImage::Format::RGB:
		return Texture::SizedInternalFormat::RGB8;
	case FreeImage::Format::RGBA:
		return Texture::SizedInternalFormat::RGBA8;
	default:
		return Texture::SizedInternalFormat::RGB8;
	}
}

Texture::SizedInternalFormat FreeImage::getSizedInternalFormat() const{
	return this -> sizedInternalFormat;
}

FreeImage::Format FreeImage::getFreeImageFormat( Texture::PixelFormat pixelFormat ){
	switch (pixelFormat){
	case Texture::PixelFormat::R:
		return Format::R;
	case Texture::PixelFormat::RGB:
		return Format::RGB;
	case Texture::PixelFormat::BGR:
		return Format::RGB;
	case Texture::PixelFormat::RGBA:
		return Format::RGBA;
	case Texture::PixelFormat::BGRA:
		return Format::RGBA;
	default:
		return Format::RGB;
	}
}
*/

