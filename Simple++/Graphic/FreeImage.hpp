#include "FreeImage.h"
namespace Graphic {

	template<typename T>
	FreeImageT<T>::FreeImageT() :
		loadingType( LoadingType::EMPTY ),
		freeImage( NULL ),
		size( Math::Vec2<GSize>::null ),
		loadingFormat( Format::R ),
		stride( 0 ),
		BPP( getBitsFromFormat( this -> loadingFormat ) ) {


	}

	template <typename T>
	FreeImageT<T>::FreeImageT( const OS::Path& filePath, Format format, bool invertY, const Math::Vec2<GSize>& size ) {
		setFile( filePath, format, invertY, size );
	}

	template <typename T>
	FreeImageT<T>::FreeImageT( const FreeImageT& freeImage, const Math::Vec2<GSize>& newSize, Filter resampleFilter ) :
		BasicLoadable( freeImage ),
		filePath( freeImage.filePath ),
		size( newSize ),
		invertY( freeImage.invertY ),
		loadingType( freeImage.loadingType ),
		BPP( freeImage.BPP ),
		loadingFormat( freeImage.loadingFormat ),
		resampleFilter( resampleFilter ) {
		if ( freeImage.isLoaded() ) {
			Math::Vec2<GSize> toCopySize = freeImage.getSize();

			if ( this -> size != toCopySize )
				this -> freeImage = FreeImage_Rescale( freeImage.freeImage, this -> size.x, this -> size.y, ( FREE_IMAGE_FILTER ) this -> resampleFilter );
			else
				this -> freeImage = FreeImage_Clone( freeImage.freeImage );
		} else {
			this -> freeImage = freeImage.freeImage;	//Probably NULL
		}
		if ( this -> freeImage )
			this -> stride = FreeImage_GetPitch( this -> freeImage );
		else
			this -> stride = 0;
	}

	template <typename T>
	FreeImageT<T>::FreeImageT( const FreeImageT& freeImage ) :
		BasicLoadable( freeImage ),
		filePath( freeImage.filePath ),
		size( freeImage.size ),
		invertY( invertY ),
		loadingType( freeImage.loadingType ),
		BPP( freeImage.BPP ),
		loadingFormat( freeImage.loadingFormat ),
		resampleFilter( freeImage.resampleFilter ) {
		if ( freeImage.isLoaded() ) {
			this -> freeImage = FreeImage_Clone( freeImage.freeImage );
		} else {
			this -> freeImage = freeImage.freeImage;	//Probably NULL
		}
		if ( this -> freeImage )
			this -> stride = FreeImage_GetPitch( this -> freeImage );
		else
			this -> stride = 0;
	}

	template <typename T>
	FreeImageT<T>::FreeImageT( FreeImageT&& freeImage ) :
		BasicLoadable( Utility::toRValue( freeImage ) ),
		freeImage( Utility::toRValue( freeImage.freeImage ) ),
		filePath( Utility::toRValue( freeImage.filePath ) ),
		size( Utility::toRValue( freeImage.size ) ),
		invertY( invertY ),
		loadingType( Utility::toRValue( freeImage.loadingType ) ),
		BPP( Utility::toRValue( freeImage.BPP ) ),
		loadingFormat( Utility::toRValue( freeImage.loadingFormat ) ),
		resampleFilter( Utility::toRValue( freeImage.resampleFilter ) ),
		stride( Utility::toRValue( freeImage.stride ) ) {
		freeImage.freeImage = NULL;					//set the old buffer to NULL to ensure no other delete
	}

	template <typename T>
	FreeImageT<T>::~FreeImageT( void ) {
		unload();
	}

	template <typename T>
	bool FreeImageT<T>::onLoad() {

		switch ( this -> loadingType ) {
			case LoadingType::EMPTY:
				{
					this -> freeImage = FreeImage_Allocate( this -> size.x, this -> size.y, this -> BPP, 0, 0, 0 );
					break;
				}
			case LoadingType::FILE:
				{
					// Check the file signature and deduce its format.
				#if defined WIN32
					FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileTypeU( filePath.toCString(), 0 );
				#else
					FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType( filePath.toCString(), 0 );
				#endif

					// If still unknown, try to guess the file format from the file extension.  
					if ( imageFormat == FIF_UNKNOWN ) {
					#if defined WIN32
						imageFormat = FreeImage_GetFIFFromFilenameU( filePath.toCString() );
					#else
						imageFormat = FreeImage_GetFIFFromFilename( filePath.toCString() );
					#endif
					}

					// If still unknown, return failure.  
					if ( imageFormat == FIF_UNKNOWN ) {
						ERROR_SPP( String( TEXT( "Free Image was unable to detect the file format : " ) ) << filePath );
						return false;
					}

					// Check that the plugin has reading capabilities and load the file.  
					if ( FreeImage_FIFSupportsReading( imageFormat ) ) {
					#if defined WIN32
						this -> freeImage = FreeImage_LoadU( imageFormat, filePath.toCString() );
					#else
						this -> freeImage = FreeImage_Load( imageFormat, filePath.toCString() );
					#endif
					}

					if ( this -> freeImage == NULL ) {
						ERROR_SPP( String( TEXT( "Free Image was unable to load the picture : " ) ) << filePath );
						return false;
					}
					if ( this -> size.x == 0 || this -> size.y == 0 ) {
						this -> size.x = FreeImage_GetWidth( this -> freeImage );
						this -> size.y = FreeImage_GetHeight( this -> freeImage );
					}


					if ( this -> loadingFormat == Format::UNDEFINED ) {
						switch ( FreeImage_GetColorType( this -> freeImage ) ) {
							case FIC_PALETTE:
								_updateFormat( Format::R );
								break;
							case FIC_RGB:
								_updateFormat( Format::RGB );
								break;
							default:
								_updateFormat( Format::RGBA );
								break;
						}
					}

					// INFO_SPP( this -> filePath << this -> size << " has been loaded successfully !" );
					break;
				}

		}


		//if we have to flip vertically.
		if ( this -> invertY )
			FreeImage_FlipVertical( this -> freeImage );
		//Change BPP
		if ( this -> BPP != FreeImage_GetBPP( this -> freeImage ) )
			_updateBPP();
		//resize
		if ( this -> size != Math::Vec2<GSize>( FreeImage_GetWidth( this -> freeImage ), FreeImage_GetHeight( this -> freeImage ) ) )
			_updateSize();

		this -> stride = FreeImage_GetPitch( this -> freeImage );
		return true;
	}

	template <typename T>
	void FreeImageT<T>::resize( const Math::Vec2<GSize>& newSize, Filter resampleFilter ) {
		this -> resampleFilter = resampleFilter;

		if ( isLoaded() && this -> size != newSize ) {
			this -> size = newSize;
			_updateSize();
		} else
			this -> size = newSize;
	}

	template <typename T>
	void FreeImageT<T>::setFormat( Format format ) {
		if ( format == Format::UNDEFINED )
			return;

		_updateFormat( format );

		if ( isLoaded() && this -> BPP != FreeImage_GetBPP( this -> freeImage ) )
			_updateBPP();
	}

	template <typename T>
	typename FreeImageT<T>::Format FreeImageT<T>::getFormat() const {
		return this -> loadingFormat;
	}

	template <typename T>
	FIBITMAP* FreeImageT<T>::getFreeImage() {
		return this -> freeImage;
	}

	template <typename T>
	unsigned int FreeImageT<T>::getBPP() const {
		return this ->  BPP;
	}

	template <typename T>
	unsigned char* FreeImageT<T>::getDatas() const {
		return FreeImage_GetBits( this -> freeImage );
	}

	template <typename T>
	bool FreeImageT<T>::onUnload() {
		if ( this -> freeImage )
			FreeImage_Unload( this -> freeImage );
		this -> freeImage = NULL;

		return true;
	}

	template <typename T>
	unsigned int FreeImageT<T>::getBitsFromFormat( Format format ) {
		switch ( format ) {
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

	template <typename T>
	bool FreeImageT<T>::saveToFile( const OS::Path& filePath, CompressedFormat savingFormat, unsigned int quality ) const {

	#if defined WIN32
		bool r( FreeImage_SaveU( ( FREE_IMAGE_FORMAT ) savingFormat, const_cast< FIBITMAP* >( this -> freeImage ), filePath.toCString(), quality ) );
	#else
		bool r( FreeImage_Save( ( FREE_IMAGE_FORMAT ) savingFormat, const_cast< FIBITMAP* >( this -> freeImage ), filePath.toCString(), quality ) );
	#endif

		if ( r ) {
			INFO_SPP( String( TEXT( "Success writing file : " ) ) << filePath );
			return true;
		} else {
			ERROR_SPP( String( TEXT( "Error writing file : " ) ) << filePath );
			return false;
		}
	}

	template <typename T>
	const Math::Vec2<GSize>& FreeImageT<T>::getSize() const {
		return this -> size;
	}

	template <typename T>
	size_t FreeImageT<T>::getStride() const {
		return this -> stride;
	}

	template <typename T>
	void FreeImageT<T>::setFile( const OS::Path& filePath, Format format /*= UNDEFINED*/, bool invertY, const Math::Vec2<GSize>& size ) {
		unload();

		this -> invertY = invertY;
		this -> filePath = filePath;

		this -> loadingType = LoadingType::FILE;
		_updateFormat( format );
		this -> resampleFilter = Filter::Bilinear;
		this -> BPP = getBitsFromFormat( format );
		this -> size = size;

		reload();
	}

	template <typename T>
	bool FreeImageT<T>::loadFromDatas( unsigned char* datas, const Math::Vec2<GSize>& size, Format format, bool datasInvertY ) {
		unload();

		lock();
		setLoading( true );
		_updateFormat( format );
		this -> size = size;
		this -> invertY = datasInvertY;
		this -> loadingType = LoadingType::EMPTY;
		this -> filePath.clear();			//we have no reason to keep a filepath now.

	#if defined WIN32
		if ( format == Format::RGB || format == Format::RGBA ) {
			//because FreeImageT do not care of MASK and use BGR on Windows
			size_t numPixels = this -> size.x * this -> size.y;
			size_t offsetPerPixel = ( this -> BPP / 8 );
			unsigned char* newDatas = new unsigned char[ offsetPerPixel * numPixels ];

			auto otherIt = datas;
			auto thisIt = newDatas;

			if ( format == Format::RGB ) {
				for ( size_t i = 0; i < numPixels; i++ ) {
					thisIt[ 0 ] = otherIt[ 2 ];
					thisIt[ 1 ] = otherIt[ 1 ];
					thisIt[ 2 ] = otherIt[ 0 ];

					otherIt += offsetPerPixel;
					thisIt += offsetPerPixel;
				}
			} else if ( format == Format::RGBA ) {
				for ( size_t i = 0; i < numPixels; i++ ) {
					thisIt[ 0 ] = otherIt[ 2 ];
					thisIt[ 1 ] = otherIt[ 1 ];
					thisIt[ 2 ] = otherIt[ 0 ];
					thisIt[ 3 ] = otherIt[ 3 ];

					otherIt += offsetPerPixel;
					thisIt += offsetPerPixel;
				}
			}

			this -> freeImage = FreeImage_ConvertFromRawBits( newDatas, this -> size.x, this -> size.y, this -> size.x * ( this -> BPP / 8 ), this -> BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, this -> invertY );
			delete[] newDatas;
		} else {
			this -> freeImage = FreeImage_ConvertFromRawBits( datas, this -> size.x, this -> size.y, this -> size.x * ( this -> BPP / 8 ), this -> BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, this -> invertY );
		}
	#else
		this -> freeImage = FreeImage_ConvertFromRawBits( datas, this -> size.x, this -> size.y, this -> size.x * ( this -> BPP / 8 ), this -> BPP, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, this -> invertY );
	#endif

		if ( !this->freeImage ) {
			setLoading( false );
			unlock();
			return false;
		}

		this -> stride = FreeImage_GetPitch( this -> freeImage );

		setLoading( false );
		setLoaded( true );
		unlock();
		return true;
	}

	template <typename T>
	FreeImageT<T>& FreeImageT<T>::operator=( const FreeImageT<T>& image ) {
		this -> filePath = image.filePath;
		this -> size = size;
		this -> invertY = image.invertY;
		this -> loadingType = image.loadingType;
		this -> BPP = image.BPP;
		this -> loadingFormat = image.loadingFormat;
		this -> resampleFilter = image.resampleFilter;

		if ( image.isLoaded() ) {
			lock();
			this -> freeImage = FreeImage_Clone( image.freeImage );
			setLoaded( true );
			unlock();
		} else {
			this -> freeImage = image.freeImage;	//Probably NULL
			setLoaded( false );
		}
		if ( this -> freeImage )
			this -> stride = FreeImage_GetPitch( this -> freeImage );
		else
			this -> stride = 0;

		return *this;
	}

	template <typename T>
	FreeImageT<T>& FreeImageT<T>::operator=( FreeImageT<T>&& image ) {
		BasicLoadable::operator=( Utility::toRValue( image ) );
		this -> freeImage = Utility::toRValue( image.freeImage );
		this -> filePath = Utility::toRValue( image.filePath );
		this -> size = Utility::toRValue( size );
		this -> invertY = Utility::toRValue( image.invertY );
		this -> loadingType = Utility::toRValue( image.loadingType );
		this -> BPP = Utility::toRValue( image.BPP );
		this -> loadingFormat = Utility::toRValue( image.loadingFormat );
		this -> resampleFilter = Utility::toRValue( image.resampleFilter );
		this -> stride = Utility::toRValue( image.stride );

		image.freeImage = NULL;						//set the old buffer to NULL to ensure no other delete
		return *this;
	}

	template <typename T>
	const OS::Path& FreeImageT<T>::getFileName() const {
		return this -> filePath;
	}

	template <typename T>
	typename FreeImageT<T>::LoadingType FreeImageT<T>::getLoadingType() const {
		return this -> loadingType;
	}

	template <typename T>
	void FreeImageT<T>::clear() {
		this -> loadingType = LoadingType::EMPTY;
		this -> filePath.clear();
		reload();
	}

	template <typename T>
	FreeImageT<T>* FreeImageT<T>::copy() {
		return new FreeImageT( *this );
	}

	template <typename T>
	void FreeImageT<T>::_updateBPP() {
		FIBITMAP* newBPPImage = NULL;
		if ( this -> BPP == 8 ) {
			newBPPImage = FreeImage_ConvertTo8Bits( this -> freeImage );
		} else if ( this -> BPP == 24 ) {
			newBPPImage = FreeImage_ConvertTo24Bits( this -> freeImage );
		} else if ( this -> BPP == 32 ) {
			newBPPImage = FreeImage_ConvertTo32Bits( this -> freeImage );
		} else {
			ERROR_SPP( TEXT( "Wrong format for an image loading" ) );
			return;
		}
		//free this image, not needed now
		FreeImage_Unload( this -> freeImage );
		this -> freeImage = newBPPImage;
		this -> stride = FreeImage_GetPitch( this -> freeImage );
	}

	template <typename T>
	void FreeImageT<T>::_updateSize() {
		FIBITMAP* resizedImage = FreeImage_Rescale( this -> freeImage, this -> size.x, this -> size.y, ( FREE_IMAGE_FILTER ) this -> resampleFilter );
		FreeImage_Unload( freeImage );
		freeImage = resizedImage;
		this -> stride = FreeImage_GetPitch( this -> freeImage );
	}

	template <typename T>
	void FreeImageT<T>::_updateFormat( Format format ) {
		if ( this -> loadingFormat == format )
			return;

		this -> loadingFormat = format;

		this -> BPP = getBitsFromFormat( this -> loadingFormat );
		//this -> pixelFormat = getPixelFormat(this -> loadingFormat);
		//this -> sizedInternalFormat = getSizedInternalFormat(this -> loadingFormat);
	}

	template<typename T>
	inline bool FreeImageT<T>::loadFromCompressed( const void* data, Size size, bool invertY ) {

		unload();
		lock();
		setLoading( true );

		// Create the memory stream.
		FIMEMORY* fiMemory( FreeImage_OpenMemory( const_cast< BYTE* >( reinterpret_cast< const BYTE* >( data ) ), static_cast< DWORD >( size ) ) );

		// Get the file type from the binary.
		FREE_IMAGE_FORMAT freeImageFormat( FreeImage_GetFileTypeFromMemory( fiMemory, 0 ) );

		// Try to load the image.
		this -> freeImage = FreeImage_LoadFromMemory( freeImageFormat, fiMemory, 0 );

		// Close the memory stream.
		FreeImage_CloseMemory( fiMemory );

		if ( !this->freeImage ) {
			setLoading( false );
			unlock();
			return false;
		}

		if ( this -> size.x == 0 || this -> size.y == 0 ) {
			this -> size.x = FreeImage_GetWidth( this -> freeImage );
			this -> size.y = FreeImage_GetHeight( this -> freeImage );
		}

		switch ( FreeImage_GetColorType( this -> freeImage ) ) {
			case FIC_PALETTE:
				_updateFormat( Format::R );
				break;
			case FIC_RGB:
				_updateFormat( Format::RGB );
				break;
			default:
				_updateFormat( Format::RGBA );
				break;
		}

		this -> stride = FreeImage_GetPitch( this -> freeImage );

		//if we have to flip vertically.
		if ( this -> invertY )
			FreeImage_FlipVertical( this -> freeImage );

		setLoading( false );
		setLoaded( true );
		unlock();

		return true;
	}

	template <typename T>
	Math::vec4 FreeImageT<T>::getPixelf( GSize x, GSize y ) const {
		unsigned int iIndex = ( y * this -> size.x + x ) * ( this -> BPP / 8 );


		unsigned char b = 0;
		unsigned char g = 0;
		unsigned char r = 0;
		unsigned char a = 0;

		switch ( this -> loadingFormat ) {
			case Format::R:
				r = getDatas()[ iIndex ];
				break;
			case Format::RGB:
				b = getDatas()[ iIndex ];
				g = getDatas()[ iIndex + 1 ];
				r = getDatas()[ iIndex + 2 ];
				break;
			case Format::RGBA:
				b = getDatas()[ iIndex ];
				g = getDatas()[ iIndex + 1 ];
				r = getDatas()[ iIndex + 2 ];
				a = getDatas()[ iIndex + 3 ];
				break;
		}


		return Math::vec4( float( r ) / 255.0f, float( g ) / 255.0f, float( b ) / 255.0f, float( a ) / 255.0f );
	}

	template <typename T>
	void FreeImageT<T>::setFlipY( bool value ) {
		if ( isLoaded() && value != this -> invertY ) {
			FreeImage_FlipVertical( this -> freeImage );
		}
		this -> invertY = value;
	}

	template <typename T>
	bool FreeImageT<T>::isYFlipped() const {
		return this -> invertY;
	}

	template <typename T>
	BITMAPINFO* FreeImageT<T>::getInfos() {
		if ( isLoaded() ) {
			return FreeImage_GetInfo( this -> freeImage );
		} else {
			return NULL;
		}
	}

	/*
	Texture::PixelFormat FreeImageT<T>::getPixelFormat() const{
	return this -> pixelFormat;
	}

	Texture::PixelFormat FreeImageT<T>::getPixelFormat( Format freeImageFormat ){
	switch(freeImageFormat){
	case FreeImageT<T>::Format::R:
	return Texture::PixelFormat::R;
	case FreeImageT<T>::Format::RGB:
	return Texture::PixelFormat::BGR;
	case FreeImageT<T>::Format::RGBA:
	return Texture::PixelFormat::BGRA;
	default:
	return Texture::PixelFormat::BGR;
	}
	}


	Texture::SizedInternalFormat FreeImageT<T>::getSizedInternalFormat( FreeImageT<T>::Format freeImageFormat ){
	switch(freeImageFormat){
	case FreeImageT<T>::Format::R:
	return Texture::SizedInternalFormat::R8;
	case FreeImageT<T>::Format::RGB:
	return Texture::SizedInternalFormat::RGB8;
	case FreeImageT<T>::Format::RGBA:
	return Texture::SizedInternalFormat::RGBA8;
	default:
	return Texture::SizedInternalFormat::RGB8;
	}
	}

	Texture::SizedInternalFormat FreeImageT<T>::getSizedInternalFormat() const{
	return this -> sizedInternalFormat;
	}

	FreeImageT<T>::Format FreeImageT<T>::getFreeImageFormat( Texture::PixelFormat pixelFormat ){
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


}