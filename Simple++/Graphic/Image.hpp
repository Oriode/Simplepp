

namespace Graphic {

	template<typename T>
	ImageT<T>::ImageT( Format format ) :
		format( format ),
		buffer( NULL ),
		size( Math::Vec2<Size>::null ),
		nbPixels( 0 ) {
	}

	template<typename T>
	Graphic::ImageT<T>::ImageT( const Math::Vec2<Size> & size, Format format ) :
		format( format ),
		size( size ),
		nbPixels( size.x * size.y ),
		buffer( new T[this -> nbPixels * ( unsigned char ) format] ) {

	}

	template<typename T>
	ImageT<T>::ImageT( const ImageT<T> & image, bool normalize ) :
		format( image.format ),
		size( image.size ),
		nbPixels( image.nbPixels ) {
		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponents];
			Vector<T>::copy( this -> buffer, image.buffer, nbComponents );
		} else {
			this -> buffer = NULL;
		}
	}



	template<typename T>
	template<typename C>
	ImageT<T>::ImageT( const ImageT<C> & image, bool normalize ) :
		format( image.getFormat() ),
		size( image.getSize() ),
		nbPixels( image.getNbPixels() ) {
		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponents];
			_toType( this -> buffer, image.getDatas(), true );
		} else {
			this -> buffer = NULL;
		}
	}

	template<typename T>
	template<typename C>
	void ImageT<T>::_toType( T * bufferDest, const C * bufferSrc, bool normalize ) {
		size_t nbComponents( getNbComponents() * getNbPixels() );
		if ( normalize ) {
			for ( size_t i( 0 ); i < nbComponents; i++ ) {
				const C & colorSrc( bufferSrc[0] );
				T & colorDst( bufferDest[0] );

				Color<T>::castComponent( colorDst, colorSrc );

				bufferDest++;
				bufferSrc++;
			}
		} else {
			for ( size_t i( 0 ); i < nbComponents; i++ ) {
				const C & colorSrc( bufferSrc[0] );
				T & colorDst( bufferDest[0] );

				colorDst = T( colorSrc );

				bufferDest++;
				bufferSrc++;
			}
		}
	}

	template<typename T>
	ImageT<T>::ImageT( ImageT<T> && image ) :
		buffer( Utility::toRValue( image.buffer ) ),
		format( Utility::toRValue( image.format ) ),
		size( Utility::toRValue( image.size ) ),
		nbPixels( Utility::toRValue( image.nbPixels ) )

	{
		image.buffer = NULL;
	}



	template<typename T>
	ImageT<T>::ImageT( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat, bool invertY, size_t stride ) {
		_allocateAndCopy( data, size, loadingFormat, invertY, stride );
	}

	template<typename T>
	template<typename U>
	ImageT<T>::ImageT( const U * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat, bool invertY, size_t stride ) {
		_allocateAndCopy( data, size, loadingFormat, invertY, stride );
	}


	template<typename T>
	template<typename U>
	void ImageT<T>::_allocateAndCopy( const U * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat, bool invertY, size_t stride ) {
		this -> size = size;
		this -> nbPixels = size.x * size.y;

		if ( this -> nbPixels > 0 && data ) {
			this -> format = _loadingFormat2Format( loadingFormat );
			size_t nbComponentsPerRow = size.x * getNbComponents();
			size_t nbComponentsTotal = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponentsTotal];

			size_t strideBytes;

			if ( !stride )
				strideBytes = nbComponentsPerRow * sizeof( U );
			else
				strideBytes = stride;


			switch ( loadingFormat ) {
				case LoadingFormat::BGR:
					{
						if ( invertY ) {
							auto otherIt = ( const U * ) ( ( ( const unsigned char * ) data ) + strideBytes * ( size.y - 1 ) );
							T * thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									Color<T>::castComponent( thisIt2[0], otherIt2[2] );
									Color<T>::castComponent( thisIt2[1], otherIt2[1] );
									Color<T>::castComponent( thisIt2[2], otherIt2[0] );

									thisIt2 += 3;
									otherIt2 += 3;
								}
								thisIt += nbComponentsPerRow;
								otherIt = ( const U * ) ( ( ( const unsigned char* ) otherIt ) - strideBytes );
							}
						} else {
							auto otherIt = data;
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									Color<T>::castComponent( thisIt2[0], otherIt2[2] );
									Color<T>::castComponent( thisIt2[1], otherIt2[1] );
									Color<T>::castComponent( thisIt2[2], otherIt2[0] );

									thisIt2 += 3;
									otherIt2 += 3;
								}
								otherIt = ( const U* ) ( ( ( const unsigned char* ) otherIt ) + strideBytes );
								thisIt += nbComponentsPerRow;
							}
						}
						break;
					}
				case LoadingFormat::BGRA:
					{
						if ( invertY ) {
							auto otherIt = ( const U * ) ( ( ( const unsigned char * ) data ) + strideBytes * ( size.y - 1 ) );
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									Color<T>::castComponent( thisIt2[0], otherIt2[2] );
									Color<T>::castComponent( thisIt2[1], otherIt2[1] );
									Color<T>::castComponent( thisIt2[2], otherIt2[0] );
									Color<T>::castComponent( thisIt2[3], otherIt2[3] );

									thisIt2 += 4;
									otherIt2 += 4;
								}
								thisIt += nbComponentsPerRow;
								otherIt = ( const U* ) ( ( ( const unsigned char* ) otherIt ) - strideBytes );
							}
						} else {
							auto otherIt = data;
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									Color<T>::castComponent( thisIt2[0], otherIt2[2] );
									Color<T>::castComponent( thisIt2[1], otherIt2[1] );
									Color<T>::castComponent( thisIt2[2], otherIt2[0] );
									Color<T>::castComponent( thisIt2[3], otherIt2[3] );

									thisIt2 += 4;
									otherIt2 += 4;
								}
								otherIt = ( const U* ) ( ( ( const unsigned char* ) otherIt ) + strideBytes );
								thisIt += nbComponentsPerRow;
							}

						}
						break;
					}
				default:
					{
						if ( invertY ) {
							//Copy row per row.
							auto otherIt = ( const U * ) ( ( ( const unsigned char * ) data ) + strideBytes * ( size.y - 1 ) );
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < nbComponentsPerRow; x++ ) {
									Color<T>::castComponent( thisIt2[0], otherIt2[0] );
									thisIt2++;
									otherIt2++;
								}
								thisIt += nbComponentsPerRow;
								otherIt = ( const U* ) ( ( ( const unsigned char* ) otherIt ) - strideBytes );
							}
						} else {
							//Copy the whole data
							if ( stride ) {
								auto otherIt = data;
								auto thisIt = getDatas();
								for ( Size y = 0; y < size.y; y++ ) {
									auto thisIt2 = thisIt;
									auto otherIt2 = otherIt;
									for ( Size x = 0; x < nbComponentsPerRow; x++ ) {
										Color<T>::castComponent( thisIt2[0], otherIt2[0] );
										thisIt2++;
										otherIt2++;
									}
									thisIt += nbComponentsPerRow;
									otherIt = ( const U* ) ( ( ( const unsigned char* ) otherIt ) + strideBytes );
								}
							}
						}
					}
			}
		} else {
			this -> nbPixels = 0;
			this -> size.x = 0;
			this -> size.y = 0;
			this -> buffer = NULL;
		}
	}



	template<typename T>
	void ImageT<T>::_allocateAndCopy( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat, bool invertY, size_t stride ) {
		this -> size = size;
		this -> nbPixels = size.x * size.y;

		if ( this -> nbPixels > 0 && data ) {
			this -> format = _loadingFormat2Format( loadingFormat );
			size_t nbComponentsPerRow = size.x * getNbComponents();
			size_t nbComponentsTotal = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponentsTotal];

			size_t strideBytes;

			if ( !stride )
				strideBytes = nbComponentsPerRow * sizeof( T );
			else
				strideBytes = stride;


			switch ( loadingFormat ) {
				case LoadingFormat::BGR:
					{
						if ( invertY ) {

							auto otherIt = ( const T * ) ( ( ( const unsigned char * ) data ) + strideBytes * ( size.y - 1 ) );
							T * thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									thisIt2[0] = otherIt2[2];
									thisIt2[1] = otherIt2[1];
									thisIt2[2] = otherIt2[0];

									thisIt2 += 3;
									otherIt2 += 3;
								}
								thisIt += nbComponentsPerRow;
								otherIt = ( const T* ) ( ( ( const unsigned char* ) otherIt ) - strideBytes );
							}
						} else {
							auto otherIt = data;
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									thisIt2[0] = otherIt2[2];
									thisIt2[1] = otherIt2[1];
									thisIt2[2] = otherIt2[0];

									thisIt2 += 3;
									otherIt2 += 3;
								}
								otherIt = ( const T* ) ( ( ( const unsigned char* ) otherIt ) + strideBytes );
								thisIt += nbComponentsPerRow;
							}
						}
						break;
					}
				case LoadingFormat::BGRA:
					{
						if ( invertY ) {
							auto otherIt = ( const T * ) ( ( ( const unsigned char * ) data ) + strideBytes * ( size.y - 1 ) );
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									thisIt2[0] = otherIt2[2];
									thisIt2[1] = otherIt2[1];
									thisIt2[2] = otherIt2[0];
									thisIt2[3] = otherIt2[3];

									thisIt2 += 4;
									otherIt2 += 4;
								}
								thisIt += nbComponentsPerRow;
								otherIt = ( const T* ) ( ( ( const unsigned char* ) otherIt ) - strideBytes );
							}
						} else {
							auto otherIt = data;
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								auto thisIt2 = thisIt;
								auto otherIt2 = otherIt;
								for ( Size x = 0; x < size.x; x++ ) {
									thisIt2[0] = otherIt2[2];
									thisIt2[1] = otherIt2[1];
									thisIt2[2] = otherIt2[0];
									thisIt2[3] = otherIt2[3];

									thisIt2 += 4;
									otherIt2 += 4;
								}
								otherIt = ( const T* ) ( ( ( const unsigned char* ) otherIt ) + strideBytes );
								thisIt += nbComponentsPerRow;
							}

						}
						break;
					}
				default:
					{
						if ( invertY ) {
							//Copy row per row.
							auto otherIt = ( const T * ) ( ( ( const unsigned char * ) data ) + strideBytes * ( size.y - 1 ) );
							auto thisIt = getDatas();
							for ( Size y = 0; y < size.y; y++ ) {
								Vector<T>::copy( thisIt, otherIt, nbComponentsPerRow );
								thisIt += nbComponentsPerRow;
								otherIt = ( const T* ) ( ( ( const unsigned char* ) otherIt ) - strideBytes );
							}
						} else {
							//Copy the whole data
							if ( stride ) {
								auto otherIt = data;
								auto thisIt = getDatas();
								for ( Size y = 0; y < size.y; y++ ) {
									Vector<T>::copy( thisIt, otherIt, nbComponentsPerRow );
									thisIt += nbComponentsPerRow;
									otherIt = ( const T* ) ( ( ( const unsigned char* ) otherIt ) + strideBytes );
								}
							} else {
								Vector<T>::copy( this -> buffer, data, nbComponentsTotal );
							}
						}
					}
			}
		} else {
			this -> nbPixels = 0;
			this -> size.x = 0;
			this -> size.y = 0;
			this -> buffer = NULL;
		}
	}



	template<typename T>
	ImageT<T>::~ImageT() {
		delete[] this -> buffer;
	}


	template<typename T>
	void Graphic::ImageT<T>::setPixel( Size x, Size y, const T * p ) {
		switch ( this -> format ) {
			case Format::R:
				getDatas()[( this -> size.x * y + x )] = *p;
				break;
			case Format::RGB:
				size_t offset = ( this -> size.x * y + x ) * 3;
				getDatas()[offset + 0] = *( p + 0 );
				getDatas()[offset + 1] = *( p + 1 );
				getDatas()[offset + 2] = *( p + 2 );
				break;
			case Format::RGBA:
				size_t offset = ( this -> size.x * y + x ) * 4;
				getDatas()[offset + 0] = *( p + 0 );
				getDatas()[offset + 1] = *( p + 1 );
				getDatas()[offset + 2] = *( p + 2 );
				getDatas()[offset + 3] = *( p + 3 );
				break;
		}
	}

	template<typename T>
	const T * ImageT<T>::getPixel( Size x, Size y ) const {
		return getDatas( x, y );
	}




	template<typename T>
	T * Graphic::ImageT<T>::getPixel( Size x, Size y ) {
		return getDatas( x, y );
	}




	template<typename T>
	size_t ImageT<T>::getDataOffset( Size x, Size y ) const {
		return ( y * this -> size.x + x ) * getNbComponents();
	}


	template<typename T>
	bool ImageT<T>::write( IO::SimpleFileStream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> size ) )
			return false;
		if ( !IO::write( fileStream, &this -> format ) )
			return false;
		size_t nbComponents = this -> nbPixels * getNbComponents();
		if ( !IO::writeBuffer( fileStream, this -> buffer, nbComponents ) )
			return false;

		return true;
	}




	template<typename T>
	void ImageT<T>::setDatas( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat, bool invertY, size_t stride ) {
		delete[] this -> buffer;
		_allocateAndCopy( data, size, loadingFormat, invertY, stride );
	}

	template<typename T>
	template<typename U>
	void ImageT<T>::setDatas( const U * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat, bool invertY, size_t stride ) {
		delete[] this -> buffer;
		_allocateAndCopy( data, size, loadingFormat, invertY, stride );
	}



	template<typename T>
	bool ImageT<T>::_read( IO::SimpleFileStream * fileStream ) {
		if ( !IO::read( fileStream, &this -> size ) ) {
			this -> size.x = 0;
			this -> size.y = 0;
			this -> nbPixels = 0;
			this -> buffer = NULL;
			return false;
		}
		if ( !IO::read( fileStream, &this -> format ) ) {
			this -> size.x = 0;
			this -> size.y = 0;
			this -> nbPixels = 0;
			this -> buffer = NULL;
			return false;
		}
		this -> nbPixels = size.x * size.y;
		size_t nbComponents( this -> nbPixels * getNbComponents() );
		if ( this -> nbPixels ) this -> buffer = new T[nbComponents];
		else this -> buffer = NULL;

		if ( !IO::readBuffer( fileStream, this -> buffer, nbComponents ) ) {
			delete[] this -> buffer;
			this -> size.x = 0;
			this -> size.y = 0;
			this -> nbPixels = 0;
			this -> buffer = NULL;
			return false;
		}
		return true;
	}


	template<typename T>
	bool ImageT<T>::read( IO::SimpleFileStream * fileStream ) {
		delete[] this -> buffer;
		return _read( fileStream );
	}

	template<typename T>
	ImageT<T> & ImageT<T>::operator=( ImageT<T> && image ) {
		delete[] this -> buffer;
		this -> buffer = Utility::toRValue( image.buffer );
		this -> format = Utility::toRValue( image.format );
		this -> size = Utility::toRValue( image.size );
		this -> nbPixels = Utility::toRValue( image.nbPixels );

		image.buffer = NULL;

		return *this;
	}

	template<typename T>
	ImageT<T> & ImageT<T>::operator=( const ImageT<T> & image ) {
		delete[] this -> buffer;

		this -> size = image.size;
		this -> nbPixels = image.nbPixels;
		this -> format = image.format;

		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * this -> getNbComponents();
			this -> buffer = new T[nbComponents];
			Vector<T>::copy( this -> buffer, image.buffer, nbComponents );
		} else {
			this -> buffer = NULL;
		}

		return *this;
	}


	template<typename T>
	template<typename C>
	ImageT<T> & ImageT<T>::operator=( const ImageT<C> & image ) {
		delete[] this -> buffer;
		this -> size = image.getSize();
		this -> nbPixels = image.getNbPixels();
		this -> format = image.getFormat();

		//TODO copy constructor & operator= should copy format ! 


		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponents];

			_toType( this -> buffer, image.getDatas(), true );

		} else {
			this -> buffer = NULL;
		}

		return *this;
	}





	template<typename T>
	T * ImageT<T>::getDatas() {
		return this -> buffer;

	}
	template<typename T>
	const T * ImageT<T>::getDatas() const {
		return this -> buffer;
	}

	template<typename T>
	template<typename C>
	C * ImageT<T>::getDatas() {
		return ( ( C* )this -> buffer );
	}

	template<typename T>
	template<typename C>
	const C * ImageT<T>::getDatas() const {
		return ( ( const C* )this -> buffer );
	}

	template<typename T>
	T * ImageT<T>::getDatas( Size x, Size y ) {
		return this -> buffer + getDataOffset( x, y );
	}

	template<typename T>
	const T * ImageT<T>::getDatas( Size x, Size y ) const {
		return this -> buffer + getDataOffset( x, y );
	}

	template<typename T>
	template<typename C>
	C * ImageT<T>::getDatas( Size x, Size y ) {
		return ( ( C* )this -> buffer ) + this -> size.x * y + x;
	}

	template<typename T>
	template<typename C>
	const C * ImageT<T>::getDatas( Size x, Size y ) const {
		return ( ( const C* )this -> buffer ) + this -> size.x * y + x;
	}

	template<typename T>
	Size ImageT<T>::getHeight() const {
		return this -> size.y;
	}

	template<typename T>
	Size ImageT<T>::getWidth() const {
		return this -> size.x;
	}

	template<typename T>
	const Math::Vec2<Size> & ImageT<T>::getSize() const {
		return this -> size;
	}


	template<typename T>
	void ImageT<T>::clear() {
		delete[] this -> buffer;
		this -> buffer = NULL;
		this -> size.x = 0;
		this -> size.y = 0;
		this -> nbPixels = 0;
	}

	template<typename T>
	void ImageT<T>::clear( const Math::Vec2<Size> & size ) {
		delete[] this -> buffer;

		this -> size = size;
		this -> nbPixels = this -> size.x * this -> size.y;
		if ( this -> nbPixels ) {
			this -> buffer = new T[this -> nbPixels * size_t( this -> format )];
		} else {
			this -> buffer = NULL;
		}
	}


	template<typename T>
	void ImageT<T>::clear( const Math::Vec2<Size> & size, Format format ) {
		delete[] this -> buffer;

		this -> size = size;
		this -> format = format;
		this -> nbPixels = this -> size.x * this -> size.y;
		if ( this -> nbPixels ) {
			this -> buffer = new T[this -> nbPixels * size_t( this -> format )];
		} else {
			this -> buffer = NULL;
		}

	}



	template<typename T>
	ImageT<T> * ImageT<T>::createMipmap() {
		if ( getDatas() == NULL )
			return NULL;
		Math::Vec2<Size> newSize = getSize() / Math::Vec2<Size>( 2 );
		if ( newSize.x == 0 || newSize.y == 0 )
			return NULL;

		ImageT<T> * newImage = new ImageT<T>( newSize, this -> format );

		switch ( this -> format ) {
			case Format::R:
				return _createMipmap<ColorR<SumType>, ColorR<T>>( newImage, static_cast< T* >( NULL ) );
				break;
			case Format::RGB:
				return _createMipmap<ColorRGB<SumType>, ColorRGB<T>>( newImage, static_cast< T* >( NULL ) );
				break;
			case Format::RGBA:
				return _createMipmap<ColorRGBA<SumType>, ColorRGBA<T>>( newImage, static_cast< T* >( NULL ) );
				break;
		}
		return NULL;
	}

	template<typename T>
	template<typename SumType, typename C>
	ImageT<T> * ImageT<T>::_createMipmap( ImageT<T> * newImage, ... ) {
		Math::Vec2<Size> i( 0 );

		auto newSize = newImage -> getSize();
		auto newImageData = newImage -> getDatas<C>();
		C * p0_1 = ( C * ) this -> buffer;
		C * p0_2;

		for ( i.y = 0; i.y < newSize.y; i.y++ ) {
			p0_2 = p0_1;
			for ( i.x = 0; i.x < newSize.x; i.x++ ) {
				//P0	P1
				//P2	P3
				C * p2 = ( p0_2 + this -> size.x );

				SumType newP( *p0_2 );
				newP += SumType( *( p0_2 + 1 ) );
				newP += SumType( *p2 );
				newP += SumType( *( p2 + 1 ) );
				newP >>= 2;			//newP /= 4

				newImageData[0] = C( newP );
				newImageData++;

				p0_2 += 2;
			}
			p0_1 += this -> size.x * 2;
		}
		return newImage;
	}

	template<typename T>
	template<typename SumType, typename C>
	ImageT<T> * ImageT<T>::_createMipmap( ImageT<T> * newImage, typename Float * ) {
		Math::Vec2<Size> i( 0 );

		auto newSize = newImage -> getSize();
		auto newImageData = newImage -> getDatas<C>();
		C * p0_1 = ( C * ) this -> buffer;
		C * p0_2;

		for ( i.y = 0; i.y < newSize.y; i.y++ ) {
			p0_2 = p0_1;
			for ( i.x = 0; i.x < newSize.x; i.x++ ) {
				//P0	P1
				//P2	P3
				C * p2 = ( p0_2 + this -> size.x );

				SumType newP( *p0_2 );
				newP += SumType( *( p0_2 + 1 ) );
				newP += SumType( *p2 );
				newP += SumType( *( p2 + 1 ) );
				newP /= T( 4 );			//newP /= 4

				newImageData[0] = newP;
				newImageData++;

				p0_2 += 2;
			}
			p0_1 += this -> size.x * 2;
		}
		return newImage;
	}


	template<typename T>
	typename Format ImageT<T>::getFormat() const {
		return this -> format;
	}


	template<typename T>
	size_t ImageT<T>::getNbPixels() const {
		return this -> nbPixels;
	}





	template<typename T>
	void ImageT<T>::fillImage( const T * color ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _fillImage<ColorR<T>, ColorR<T>>( *( ( ColorR<T> * ) color ) );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, ColorRGB<T>>( *( ( ColorRGB<T> * ) color ) );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, ColorRGBA<T>>( *( ( ColorRGBA<T> * ) color ) );
		}
	}

	template<typename T>
	void ImageT<T>::fillImage( const T * color, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _fillImage<ColorR<T>, ColorRGBA<T>>( *( ( ColorR<T> * ) color ), rectangle );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, ColorRGBA<T>>( *( ( ColorRGB<T> * ) color ), rectangle );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, ColorRGBA<T>>( *( ( ColorRGBA<T> * ) color ), rectangle );
		}
	}


	template<typename T>
	void ImageT<T>::fillImage( const ColorR<T> & color ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _fillImage<ColorR<T>, ColorR<T>>( color );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, ColorR<T>>( color );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, ColorR<T>>( color );
		}
	}


	template<typename T>
	void ImageT<T>::fillImage( const ColorRGB<T> & color ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _fillImage<ColorR<T>, ColorRGB<T>>( color );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, ColorRGB<T>>( color );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, ColorRGB<T>>( color );
		}
	}


	template<typename T>
	void ImageT<T>::fillImage( const ColorRGBA<T> & color ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _fillImage<ColorR<T>, ColorRGBA<T>>( color );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, ColorRGBA<T>>( color );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, ColorRGBA<T>>( color );
		}
	}



	template<typename T>
	template<typename C1, typename C2>
	void ImageT<T>::_fillImage( const C2 & color ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );

		auto it = this -> buffer;
		auto end = it + getNbPixels() * N1;
		for ( ; it < end; it += N1 ) {
			BlendingFunc::None::blendColor( *( ( C1 * ) it ), color );
		}
	}


	////////////////////

	template<typename T>
	template<typename Functor>
	void ImageT<T>::setPixels( Functor & functor ) {
		return setPixels( functor, Rectangle( 0, getSize() ) );
	}


	template<typename T>
	template<typename Functor>
	void ImageT<T>::setPixels( Functor & functor, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend R -> R
				return _setPixels<Functor, ColorR<T>>( functor, rectangle );
			case Format::RGB: 	//Blend R -> RGB
				return _setPixels<Functor, ColorRGB<T>>( functor, rectangle );
			case Format::RGBA: 	//Blend R -> RGBA
				return _setPixels<Functor, ColorRGBA<T>>( functor, rectangle );
		}
	}

	template<typename T>
	template<typename Functor, typename C>
	void ImageT<T>::_setPixels( Functor & functor, const Rectangle & rectangle ) {

		Math::Rectangle<Size> rectangleUI = clampRectangle( rectangle );
		auto it = getDatas<C>( rectangleUI.getLeft(), rectangleUI.getBottom() );
		typename Math::Vec2<Size>::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLine = this -> size.x;

		Math::Vec2<typename Math::Vec2<Size>::Type> i;
		for ( i.y = rectangleUI.getBottom(); i.y < rectangleUI.getTop(); i.y++ ) {
			auto it2 = it;
			for ( i.x = rectangleUI.getLeft(); i.x < rectangleUI.getRight(); i.x++ ) {
				functor( i, *( it2 ) );
				it2++;
			}
			it += nbComponentsPerLine;
		}
	}

	template<typename T>
	Math::Rectangle<Size> ImageT<T>::clampRectangle( const Rectangle & rectangle ) const {
		Math::Rectangle<Size> rectangleUI;

		if ( rectangle.getBottom() < 0 ) 		rectangleUI.setBottom( 0 );
		else							rectangleUI.setBottom( rectangle.getBottom() );


		if ( rectangle.getLeft() < 0 )		rectangleUI.setLeft( 0 );
		else							rectangleUI.setLeft( rectangle.getLeft() );


		if ( rectangle.getTop() < 0 )				rectangleUI.setTop( 0 );
		else								rectangleUI.setTop( rectangle.getTop() );


		if ( rectangle.getRight() < 0 )			rectangleUI.setRight( 0 );
		else								rectangleUI.setRight( rectangle.getRight() );

		if ( rectangleUI.getTop() > getSize().y )		rectangleUI.setTop( getSize().y );
		if ( rectangleUI.getRight() > getSize().x )	rectangleUI.setRight( getSize().x );

		return rectangleUI;
	}


	////////////////////
	template<typename T>
	void ImageT<T>::fillImage( const ColorR<T> & color, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendingFunc::None, ColorR<T>, ColorR<T>>( rectangle, color, BlendingFunc::None() );
			case Format::RGB:
				return _drawRectangle<BlendingFunc::None, ColorRGB<T>, ColorR<T>>( rectangle, color, BlendingFunc::None() );
			case Format::RGBA:
				return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, ColorR<T>>( rectangle, color, BlendingFunc::None() );
		}
	}

	template<typename T>
	void Graphic::ImageT<T>::fillImage( const ColorRGB<T> & color, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendingFunc::None, ColorR<T>, ColorRGB<T>>( rectangle, color, BlendingFunc::None() );
			case Format::RGB:
				return _drawRectangle<BlendingFunc::None, ColorRGB<T>, ColorRGB<T>>( rectangle, color, BlendingFunc::None() );
			case Format::RGBA:
				return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, ColorRGB<T>>( rectangle, color, BlendingFunc::None() );
		}
	}

	template<typename T>
	void Graphic::ImageT<T>::fillImage( const ColorRGBA<T> & color, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendingFunc::None, ColorR<T>, ColorRGBA<T>>( rectangle, color, BlendingFunc::None() );
			case Format::RGB:
				return _drawRectangle<BlendingFunc::None, ColorRGB<T>, ColorRGBA<T>>( rectangle, color, BlendingFunc::None() );
			case Format::RGBA:
				return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, ColorRGBA<T>>( rectangle, color, BlendingFunc::None() );
		}
	}

	template<typename T>
	template<typename C, typename InterFunc>
	void Graphic::ImageT<T>::fillImage( const Gradient::Horizontal<C, InterFunc> & gradient, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 	//Blend RGBA -> R
				return _fillImage<ColorR<T>, C, InterFunc>( gradient, rectangle );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, C, InterFunc>( gradient, rectangle );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, C, InterFunc>( gradient, rectangle );
		}
	}

	template<typename T>
	template<typename C, typename InterFunc>
	void Graphic::ImageT<T>::fillImage( const Gradient::Vertical<C, InterFunc> & gradient, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 	//Blend RGBA -> R
				return _drawRectangle<BlendingFunc::None, ColorR<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _drawRectangle<BlendingFunc::None, ColorRGB<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
		}
	}


	template<typename T>
	template<typename C, typename InterFunc>
	void Graphic::ImageT<T>::fillImage( const Gradient::Linear<C, InterFunc> & gradient, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _drawRectangle<BlendingFunc::None, ColorR<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _drawRectangle<BlendingFunc::None, ColorRGB<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
		}
	}


	template<typename T>
	template<typename C, typename InterFunc>
	void Graphic::ImageT<T>::fillImage( const Gradient::Radial<C, InterFunc> & gradient, const Rectangle & rectangle ) {
		if ( getDatas() == NULL )
			return;
		switch ( this -> format ) {
			case Format::R: 		//Blend RGBA -> R
				return _drawRectangle<BlendingFunc::None, ColorR<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
			case Format::RGB: 	//Blend RGBA -> RGB
				return _drawRectangle<BlendingFunc::None, ColorRGB<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, BlendingFunc::None() );
		}
	}




	template<typename T>
	void ImageT<T>::fillImage( const Point & point, const ImageT<T> & image ) {
		fillImage( point, Rectangle( image.getSize() ), image );
	}

	template<typename T>
	void ImageT<T>::fillImage( const Point & point, const Rectangle & rectangle, const ImageT<T> & image ) {
		switch ( this -> format ) {
			case Format::R:
				{
					switch ( image.getFormat() ) {
						case Format::R: 		//Blend R -> R
							return _fillImage<ColorR<T>, ColorR<T>>( point, rectangle, image );
						case Format::RGB: 	//Blend RGB -> R
							return _fillImage<ColorR<T>, ColorRGB<T>>( point, rectangle, image );
						case Format::RGBA: 	//Blend RGBA -> R
							return _fillImage<ColorR<T>, ColorRGBA<T>>( point, rectangle, image );
					}
				}
			case Format::RGB:
				{
					switch ( image.getFormat() ) {
						case Format::R: 		//Blend R -> RGB
							return _fillImage<ColorRGB<T>, ColorR<T>>( point, rectangle, image );
						case Format::RGB: 	//Blend RGB -> RGB
							return _fillImage<ColorRGB<T>, ColorRGB<T>>( point, rectangle, image );
						case Format::RGBA: 	//Blend RGBA -> RGB
							return _fillImage<ColorRGB<T>, ColorRGBA<T>>( point, rectangle, image );
					}
				}
			case Format::RGBA:
				{
					switch ( image.getFormat() ) {
						case Format::R: 		//Blend R -> RGBA
							return _fillImage<ColorRGBA<T>, ColorR<T>>( point, rectangle, image );
						case Format::RGB: 	//Blend RGB -> RGBA
							return _fillImage<ColorRGBA<T>, ColorRGB<T>>( point, rectangle, image );
						case Format::RGBA: 	//Blend RGBA -> RGBA
							return _fillImage<ColorRGBA<T>, ColorRGBA<T>>( point, rectangle, image );
					}
				}
		}
	}



	template<typename T>
	template<typename C1, typename C2>
	void ImageT<T>::_fillImage( const Point & point, const Rectangle & rectangle, const ImageT<T> & image ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C2 ) / sizeof( T );

		Math::Vec2<Size> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<Size> otherImageBegin;
		Point size;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>( this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x );
		} else if ( point.x > ( typename Point::Type ) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
			size.x = Math::min<typename Point::Type>( this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft() );
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
			size.y = Math::min<typename Point::Type>( this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y );
		} else if ( point.y > ( typename Point::Type ) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>( this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom() );
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		auto thisIt = getDatas<C1>( begin.x, begin.y );
		auto thisImageOffset = this -> size.x;

		auto otherIt = image.getDatas<C2>( otherImageBegin.x, otherImageBegin.y );
		auto otherImageOffset = image.getSize().x;

		if ( N1 == N2 ) {
			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				Vector<T>::copy( thisIt, otherIt, size.x );
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		} else {
			Point i;
			size_t sizeOffset = size.x;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				auto maxit = thisIt + sizeOffset;
				for ( ; thisIt2 < maxit; ) {
					BlendingFunc::None::blendColor( *( thisIt2 ), *( otherIt2 ) );
					thisIt2++;
					otherIt2++;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		}
	}









	template<typename T>
	template<bool Fast>
	void ImageT<T>::drawImage( const Point & point, const ImageT<T> & image, const Point & maskPoint, const ImageT<T> & maskImage ) {
		drawImage<Fast>( point, image, Rectangle( image.getSize() ), maskPoint, maskImage );
	}

	template<typename T>
	template<bool Fast>
	void ImageT<T>::drawImage( const Point & point, const ImageT<T> & image, const ImageT<T> & maskImage ) {
		drawImage<Fast>( point, image, Rectangle( image.getSize() ), Point::null, maskImage );
	}

	template<typename T>
	template<bool Fast>
	void ImageT<T>::drawImage( const Point & point, const ImageT<T> & image ) {
		drawImage<Fast>( point, image, Rectangle( image.getSize() ) );
	}

	template<typename T>
	template<typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImage( const Point & point, const ColorR<T> & color, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		drawImage<BlendFunc, Fast>( point, color, Rectangle( maskImage.getSize() ), maskImage, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImage( const Point & point, const ColorRGB<T> & color, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		drawImage<BlendFunc, Fast>( point, color, Rectangle( maskImage.getSize() ), maskImage, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImage( const Point & point, const ColorRGBA<T> & color, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		drawImage<BlendFunc, Fast>( point, color, Rectangle( maskImage.getSize() ), maskImage, blendFunc );
	}



	template<typename T>
	template<bool Fast>
	void ImageT<T>::drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle ) {
		if ( getDatas() == NULL || image.getDatas() == NULL )
			return;
		switch ( getFormat() ) {
			case Format::R:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawImage<ColorR<T>, ColorR<T>, Fast>( point, image, rectangle );
						case Format::RGB:			//Blend RGB -> R
							return _drawImage<ColorR<T>, ColorRGB<T>, Fast>( point, image, rectangle );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawImage<ColorR<T>, ColorRGBA<T>, Fast>( point, image, rectangle );
					}
					break;
				}
			case Format::RGB:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawImage<ColorRGB<T>, ColorR<T>, Fast>( point, image, rectangle );
						case Format::RGB:			//Blend RGB -> R
							return _drawImage<ColorRGB<T>, ColorRGB<T>, Fast>( point, image, rectangle );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawImage<ColorRGB<T>, ColorRGBA<T>, Fast>( point, image, rectangle );
					}
					break;
				}
			case Format::RGBA:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawImage<ColorRGBA<T>, ColorR<T>, Fast>( point, image, rectangle );
						case Format::RGB:			//Blend RGB -> R
							return _drawImage<ColorRGBA<T>, ColorRGB<T>, Fast>( point, image, rectangle );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawImage<ColorRGBA<T>, ColorRGBA<T>, Fast>( point, image, rectangle );
					}
					break;
				}
		}
	}



	template<typename T>
	template<typename C1, typename C2, bool Fast>
	void ImageT<T>::_drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C2 ) / sizeof( T );

		if ( Fast ) {
			auto thisIt = getDatas<C1>( point.x, point.y );
			unsigned int thisImageOffset = this -> size.x;

			auto otherIt = image.getDatas<C2>( rectangle.getLeft(), rectangle.getBottom() );
			unsigned int otherImageOffset = image.getSize().x;

			Point size( rectangle.getRight() - rectangle.getLeft(), rectangle.getTop() - rectangle.getBottom() );

			if ( N1 != 4 && N1 == N2 ) {
				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					Vector<T>::copy( thisIt, ( C1 * ) otherIt, size.x );
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}
			} else {
				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						BlendingFunc::Normal::blendColor( *( thisIt2 ), *( otherIt2 ) );
						thisIt2++;
						otherIt2++;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}
			}

		} else {
			Math::Vec2<Size> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
			Math::Vec2<Size> otherImageBegin;
			Point size;
			if ( point.x < 0 ) {
				begin.x = 0;
				otherImageBegin.x = -point.x + rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x );
			} else if ( point.x > ( typename Point::Type ) this -> size.x ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.x = point.x;
				otherImageBegin.x = rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft() );
			}

			if ( point.y < 0 ) {
				begin.y = 0;
				otherImageBegin.y = -point.y + rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y );
			} else if ( point.y > ( typename Point::Type ) this -> size.y ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.y = point.y;
				otherImageBegin.y = rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom() );
			}

			if ( size.x <= 0 || size.y <= 0 ) return;

			auto thisIt = getDatas<C1>( begin.x, begin.y );
			unsigned int thisImageOffset = this -> size.x;

			auto otherIt = image.getDatas<C2>( otherImageBegin.x, otherImageBegin.y );
			unsigned int otherImageOffset = image.getSize().x;

			if ( N1 != 4 && N1 == N2 ) {
				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					Vector<T>::copy( thisIt, ( C1 * ) otherIt, size.x );
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}
			} else {
				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						BlendingFunc::Normal::blendColor( *( thisIt2 ), *( otherIt2 ) );
						thisIt2++;
						otherIt2++;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}
			}
		}
	}




	template<typename T>
	template<typename BlendFunc, bool Fast>
	void ImageT<T>::drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const BlendFunc & blendFunc ) {
		switch ( getFormat() ) {
			case Format::R:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawImage<BlendFunc, ColorR<T>, ColorR<T>, Fast>( point, image, rectangle, blendFunc );
						case Format::RGB:			//Blend RGB -> R
							return _drawImage<BlendFunc, ColorR<T>, ColorRGB<T>, Fast>( point, image, rectangle, blendFunc );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawImage<BlendFunc, ColorR<T>, ColorRGBA<T>, Fast>( point, image, rectangle, blendFunc );
					}
					break;
				}
			case Format::RGB:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawImage<BlendFunc, ColorRGB<T>, ColorR<T>, Fast>( point, image, rectangle, blendFunc );
						case Format::RGB:			//Blend RGB -> R
							return _drawImage<BlendFunc, ColorRGB<T>, ColorRGB<T>, Fast>( point, image, rectangle, blendFunc );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawImage<BlendFunc, ColorRGB<T>, ColorRGBA<T>, Fast>( point, image, rectangle, blendFunc );
					}
					break;
				}
			case Format::RGBA:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawImage<BlendFunc, ColorRGBA<T>, ColorR<T>, Fast>( point, image, rectangle, blendFunc );
						case Format::RGB:			//Blend RGB -> R
							return _drawImage<BlendFunc, ColorRGBA<T>, ColorRGB<T>, Fast>( point, image, rectangle, blendFunc );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawImage<BlendFunc, ColorRGBA<T>, ColorRGBA<T>, Fast>( point, image, rectangle, blendFunc );
					}
					break;
				}
		}
	}


	template<typename T>
	template<typename BlendFunc, typename C1, typename C2, bool Fast>
	void ImageT<T>::_drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const BlendFunc & blendFunc ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C2 ) / sizeof( T );

		if ( Fast ) {
			auto thisIt = getDatas<C1>( point.x, point.y );
			unsigned int thisImageOffset = this -> size.x;

			auto otherIt = image.getDatas<C2>( rectangle.getLeft(), rectangle.getBottom() );
			unsigned int otherImageOffset = image.getSize().x;

			Point size( rectangle.getRight() - rectangle.getLeft(), rectangle.getTop() - rectangle.getBottom() );


			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					blendFunc( *( thisIt2 ), *( otherIt2 ) );
					otherIt2++;
					thisIt2++;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		} else {

			Math::Vec2<Size> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
			Math::Vec2<Size> otherImageBegin;
			Point size;

			if ( point.x < 0 ) {
				begin.x = 0;
				otherImageBegin.x = -point.x + rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x );
			} else if ( point.x > ( typename Point::Type ) this -> size.x ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.x = point.x;
				otherImageBegin.x = rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft() );
			}

			if ( point.y < 0 ) {
				begin.y = 0;
				otherImageBegin.y = -point.y + rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y );
			} else if ( point.y > ( typename Point::Type ) this -> size.y ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.y = point.y;
				otherImageBegin.y = rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom() );
			}

			if ( size.x <= 0 || size.y <= 0 ) return;

			auto thisIt = getDatas<C1>( begin.x, begin.y );
			unsigned int thisImageOffset = this -> size.x;
			unsigned int sizeOffset = size.x;

			auto otherIt = image.getDatas<C2>( otherImageBegin.x, otherImageBegin.y );
			unsigned int otherImageOffset = image.getSize().x;

			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				auto maxIt = thisIt + sizeOffset;
				for ( ; thisIt2 < maxIt; thisIt2++ ) {
					blendFunc( *( thisIt2 ), *( otherIt2 ) );
					otherIt2++;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		}
	}




	template<typename T>
	template<typename BlendFunc, bool Fast>
	void ImageT<T>::drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const Point & maskPoint, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		switch ( getFormat() ) {
			case Format::R:
				{
					switch ( image.getFormat() ) {
						case Format::R:
							{			//Blend R -> R
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorR<T>, ColorR<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorR<T>, ColorR<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorR<T>, ColorR<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
						case Format::RGB:
							{			//Blend RGB -> R
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorR<T>, ColorRGB<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorR<T>, ColorRGB<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorR<T>, ColorRGB<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
						case Format::RGBA:
							{			//Blend RGBA -> R
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorR<T>, ColorRGBA<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorR<T>, ColorRGBA<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorR<T>, ColorRGBA<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
					}
				}
			case Format::RGB:
				{
					switch ( image.getFormat() ) {
						case Format::R:
							{			//Blend R -> RGB
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorRGB<T>, ColorR<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorRGB<T>, ColorR<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorRGB<T>, ColorR<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
						case Format::RGB:
							{			//Blend RGB -> RGB
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorRGB<T>, ColorRGB<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorRGB<T>, ColorRGB<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorRGB<T>, ColorRGB<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
						case Format::RGBA:
							{			//Blend RGBA -> RGB
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorRGB<T>, ColorRGBA<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorRGB<T>, ColorRGBA<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorRGB<T>, ColorRGBA<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
					}
				}
			case Format::RGBA:
				{
					switch ( image.getFormat() ) {
						case Format::R:
							{			//Blend R -> RGBA
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorRGBA<T>, ColorR<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorRGBA<T>, ColorR<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorRGBA<T>, ColorR<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
						case Format::RGB:
							{			//Blend RGB -> RGBA
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorRGBA<T>, ColorRGB<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorRGBA<T>, ColorRGB<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorRGBA<T>, ColorRGB<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
						case Format::RGBA:
							{			//Blend RGBA -> RGBA
								switch ( maskImage.getFormat() ) {
									case Format::R:
										return _drawImage<ColorRGBA<T>, ColorRGBA<T>, ColorR<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGB:
										return _drawImage<ColorRGBA<T>, ColorRGBA<T>, ColorRGB<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
									case Format::RGBA:
										return _drawImage<ColorRGBA<T>, ColorRGBA<T>, ColorRGBA<T>, Fast>( point, image, rectangle, maskPoint, maskImage, blendFunc );
								}
							}
					}
				}
		}

	}



	template<typename T>
	template<typename BlendFunc, typename C1, typename C2, typename C3, bool Fast>
	void ImageT<T>::_drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const Point & maskPoint, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {

		struct GetMaskComponentFunctor {
			inline const T & operator ()( const ColorR<T> & c ) const {
				return c.r;
			}
			inline const T & operator ()( const ColorRGB<T> & c ) const {
				return c.r;
			}
			inline const T & operator ()( const ColorRGBA<T> & c ) const {
				return c.a;
			}
		};

		static GetMaskComponentFunctor getMaskComponentFunctor;

		if ( Fast ) {
			auto maskIt = maskImage.getDatas<C3>( maskPoint.x, maskPoint.y );
			auto maskImageOffset = maskImage.getSize().x;

			auto thisIt = getDatas<C1>( point.x, point.y );
			unsigned int thisImageOffset = this -> size.x;

			auto otherIt = image.getDatas<C2>( rectangle.getLeft(), rectangle.getBottom() );
			unsigned int otherImageOffset = image.getSize().x;

			Point size( rectangle.getRight() - rectangle.getLeft(), rectangle.getTop() - rectangle.getBottom() );

			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				auto maskIt2 = maskIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					blendFunc( *( thisIt2 ), *( otherIt2 ), getMaskComponentFunctor( *( maskIt2 ) ) );
					thisIt2++;
					otherIt2++;
					maskIt2++;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
				maskIt += maskImageOffset;
			}


		} else {
			Math::Vec2<Size> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
			Math::Vec2<Size> otherImageBegin;
			Math::Vec2<Size> maskBegin;
			Point size;

			if ( maskPoint.x < 0 ) {
				begin.x = point.x - maskPoint.x;
				maskBegin.x = 0;
			} else {
				begin.x = point.x;
				maskBegin.x = maskPoint.x;
			}

			if ( maskPoint.y < 0 ) {
				begin.y = point.y - maskPoint.y;
				maskBegin.y = 0;
			} else {
				begin.y = point.y;
				maskBegin.y = maskPoint.y;
			}

			if ( begin.x < 0 ) {
				begin.x = 0;
				otherImageBegin.x = -point.x + rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x, maskImage.getSize().x - maskPoint.x + point.x );
			} else if ( point.x > ( typename Point::Type ) this -> size.x ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.x = point.x;
				otherImageBegin.x = rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x - point.x, maskImage.getSize().x - maskPoint.x );
			}

			if ( begin.y < 0 ) {
				begin.y = 0;
				otherImageBegin.y = -point.y + rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y, maskImage.getSize().y - maskPoint.y + point.y );
			} else if ( point.y > ( typename Point::Type ) this -> size.y ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.y = point.y;
				otherImageBegin.y = rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y - point.y, maskImage.getSize().y - maskPoint.y );
			}

			if ( size.x <= 0 || size.y <= 0 ) return;

			auto maskIt = maskImage.getDatas<C3>( maskBegin.x, maskBegin.y );
			unsigned int maskImageOffset = maskImage.getSize().x;
			unsigned int sizeOffset = size.x;

			auto thisIt = getDatas<C1>( begin.x, begin.y );
			unsigned int thisImageOffset = this -> size.x;

			auto otherIt = image.getDatas<C2>( otherImageBegin.x, otherImageBegin.y );
			unsigned int otherImageOffset = image.getSize().x;


			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				auto maskIt2 = maskIt;
				auto maxIt = thisIt + sizeOffset;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					blendFunc( *( thisIt2 ), *( otherIt2 ), getMaskComponentFunctor( *( maskIt2 ) ) );
					thisIt2++;
					otherIt2++;
					maskIt2++
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
				maskIt += maskImageOffset;
			}
		}
	}





	template<typename T>
	template<typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImage( const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		return drawImageFunctor<ColorFunc::SimpleColor<ColorR<T>>, BlendFunc, Fast>( point, ColorFunc::SimpleColor<ColorR<T>>( color ), rectangle, maskImage, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImage( const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		return drawImageFunctor<ColorFunc::SimpleColor<ColorRGB<T>>, BlendFunc, Fast>( point, ColorFunc::SimpleColor<ColorRGB<T>>( color ), rectangle, maskImage, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImage( const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		return drawImageFunctor<ColorFunc::SimpleColor<ColorRGBA<T>>, BlendFunc, Fast>( point, ColorFunc::SimpleColor<ColorRGBA<T>>( color ), rectangle, maskImage, blendFunc );
	}



	template<typename T>
	template<typename ColorFunc, typename BlendFunc, bool Fast>
	void Graphic::ImageT<T>::drawImageFunctor( const Point & point, ColorFunc & colorFunc, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {
		switch ( getFormat() ) {
			case Format::R:
				{			//Blend C -> R
					switch ( maskImage.getFormat() ) {
						case Format::R:
							return _drawImage<ColorFunc, BlendFunc, ColorR<T>, ColorR<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
						case Format::RGB:
							return _drawImage<ColorFunc, BlendFunc, ColorR<T>, ColorRGB<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
						case Format::RGBA:
							return _drawImage<ColorFunc, BlendFunc, ColorR<T>, ColorRGBA<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
					}
				}
			case Format::RGB:
				{			//Blend C -> RGB
					switch ( maskImage.getFormat() ) {
						case Format::R:
							return _drawImage<ColorFunc, BlendFunc, ColorRGB<T>, ColorR<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
						case Format::RGB:
							return _drawImage<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGB<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
						case Format::RGBA:
							return _drawImage<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGBA<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
					}
				}
			case Format::RGBA:
				{			//Blend C -> RGBA
					switch ( maskImage.getFormat() ) {
						case Format::R:
							return _drawImage<ColorFunc, BlendFunc, ColorRGBA<T>, ColorR<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
						case Format::RGB:
							return _drawImage<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGB<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
						case Format::RGBA:
							return _drawImage<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGBA<T>, Fast>( point, colorFunc, rectangle, maskImage, blendFunc );
					}
				}
		}
	}



	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1, typename C2, bool Fast>
	void Graphic::ImageT<T>::_drawImage( const Point & point, ColorFunc & colorFunc, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc ) {

		struct GetMaskComponentFunctor {
			inline const T & operator ()( const ColorR<T> & c ) const {
				return c.r;
			}
			inline const T & operator ()( const ColorRGB<T> & c ) const {
				return c.r;
			}
			inline const T & operator ()( const ColorRGBA<T> & c ) const {
				return c.a;
			}
		};

		static GetMaskComponentFunctor getMaskComponentFunctor;

		if ( Fast ) {
			colorFunc.init( rectangle );

			auto thisIt = getDatas<C1>( point.x, point.y );
			auto thisImageOffset = this -> size.x;

			auto maskIt = maskImage.getDatas<C2>( rectangle.getLeft(), rectangle.getBottom() );
			auto maskImageOffset = maskImage.getSize().x;

			Point size( rectangle.getRight() - rectangle.getLeft(), rectangle.getTop() - rectangle.getBottom() );

			Math::Vec2<Size> i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = maskIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					if ( getMaskComponentFunctor( *( otherIt2 ) ) != T( ColorR<T>::getMin() ) ) {
						blendFunc( *( thisIt2 ), colorFunc( i ), getMaskComponentFunctor( *( otherIt2 ) ) );
					}
					otherIt2++;
					thisIt2++;
				}
				thisIt += thisImageOffset;
				maskIt += maskImageOffset;
			}
		} else {
			Math::Vec2<Size> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
			Math::Vec2<Size> maskImageBegin;
			Point size;
			if ( point.x < 0 ) {
				begin.x = 0;
				maskImageBegin.x = -point.x + rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x );
			} else if ( point.x > ( typename Point::Type ) this -> size.x ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.x = point.x;
				maskImageBegin.x = rectangle.getLeft();
				size.x = Math::min<typename Point::Type>( this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft() );
			}

			if ( point.y < 0 ) {
				begin.y = 0;
				maskImageBegin.y = -point.y + rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y );
			} else if ( point.y > ( typename Point::Type ) this -> size.y ) {
				return;			//We are drawing outside, nothing will be changed.
			} else {
				begin.y = point.y;
				maskImageBegin.y = rectangle.getBottom();
				size.y = Math::min<typename Point::Type>( this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom() );
			}

			if ( size.x <= 0 || size.y <= 0 ) return;

			Math::Rectangle<Size> rectangleClamped( begin.x, begin.y, begin.x + size.x, begin.y + size.y );

			colorFunc.init( rectangleClamped );

			auto thisIt = getDatas<C1>( begin.x, begin.y );
			auto thisImageOffset = this -> size.x;

			auto maskIt = maskImage.getDatas<C2>( maskImageBegin.x, maskImageBegin.y );
			auto maskImageOffset = maskImage.getSize().x;


			Math::Vec2<Size> i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = maskIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					if ( getMaskComponentFunctor( *( otherIt2 ) ) != T( ColorR<T>::getMin() ) ) {
						blendFunc( *( thisIt2 ), colorFunc( i ), getMaskComponentFunctor( *( otherIt2 ) ) );
					}
					otherIt2++;
					thisIt2++;
				}
				thisIt += thisImageOffset;
				maskIt += maskImageOffset;
			}

		}


	}







	template<typename T>
	ImageT<T> ImageT<T>::applyGaussianBlur( Size radius, ConvolutionMode convolutionMode, const ColorRGBA<T> & color ) const {

		typedef KernelType F;
		struct ApplyGaussian {
			ApplyGaussian( const ImageT<T> & image ) : image( image ) {
				for ( Size i = 0; i < 10; i++ ) {
					Size diameter = i * 2 + 1;
					kernels[i] = new F[diameter];
					computeGaussianKernel( kernels[i], diameter );
				}
			}
			inline ImageT<T> operator()( Size radius, ConvolutionMode convolutionMode, const ColorRGBA<T> & color ) {
				Size diameter = radius * 2 + 1;
				if ( radius < 10 ) return this -> image.applyFilter<F>( this -> kernels[radius], this -> kernels[radius], diameter, ConvolutionOrder::HorizontalVertical, convolutionMode, color );
				else {
					Size diameter = radius * 2 + 1;
					F * kernelTmp = new F[diameter];
					computeGaussianKernel( kernelTmp, diameter );
					ImageT<T> image( this -> image.applyFilter<F>( kernelTmp, kernelTmp, diameter, ConvolutionOrder::HorizontalVertical, convolutionMode, color ) );
					delete[] kernelTmp;
					return image;
				}
			}

			~ApplyGaussian() {
				for ( Size i = 0; i < 10; i++ )
					delete[] this -> kernels[i];
			}

			F * kernels[10];
			const ImageT<T> & image;
		};
		static ApplyGaussian applyGaussian( *this );
		return applyGaussian( radius, convolutionMode, color );
	}


	template<typename T>
	ImageT<T> Graphic::ImageT<T>::applySobelFilter() {
		typedef KernelType F;

		static F sobelKernel1[3];
		static F sobelKernel2[3];

		computeSobel1Kernel( sobelKernel1 );
		computeSobel2Kernel( sobelKernel2 );

		ImageT<F> imageCasted( *this, false );

		ImageT<F> imageHori( imageCasted.applyFilter<F, KernelFunc::None, T>( sobelKernel1, sobelKernel2, 3, ImageT<F>::ConvolutionOrder::HorizontalVertical, ImageT<F>::ConvolutionMode::NormalSize, ColorRGBA<F>( 0 ), KernelFunc::None() ), false );
		ImageT<F> imageVert( imageCasted.applyFilter<F, KernelFunc::None, T>( sobelKernel1, sobelKernel2, 3, ImageT<F>::ConvolutionOrder::VerticalHorizontal, ImageT<F>::ConvolutionMode::NormalSize, ColorRGBA<F>( 0 ), KernelFunc::None() ), false );

		F * imageHoriIt( imageHori.getDatas() );
		F * imageVertIt( imageVert.getDatas() );

		unsigned int imageNbComponents( this -> size.x * this -> size.y * getNbComponents() );

		for ( unsigned int i( 0 ); i < imageNbComponents; i++ ) {
			F & imageHoriPix( imageHoriIt[0] );
			F & imageVertPix( imageVertIt[0] );

			F dist( Math::sqrt( imageHoriPix * imageHoriPix + imageVertPix * imageVertPix ) );
			imageVertIt[0] = T( Math::min<F>( dist / F( 2 ), F( Color<T>::getMax() ) ) );

			imageHoriIt++;
			imageVertIt++;
		}
		return ImageT<T>( imageVert, false );
	}





	template<typename T>
	template<typename F, typename KernelFunc, typename T1>
	ImageT<T> ImageT<T>::applyFilter( const F * filterX, const F * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & kernelFunc ) const {
		if ( getDatas() == NULL ) return *this;
		switch ( getFormat() ) {
			case Format::R: return _applyFilter<T1, ColorR<T>, T, ColorR<T>, ColorR<F>, KernelFunc>( filterX, filterY, size, convolutionOrder, convolutionMode, color, kernelFunc );
			case Format::RGB: return _applyFilter<T1, ColorRGB<T>, T, ColorRGB<T>, ColorRGB<F>, KernelFunc>( filterX, filterY, size, convolutionOrder, convolutionMode, color, kernelFunc );
			case Format::RGBA: return _applyFilter<T1, ColorRGBA<T>, T, ColorRGBA<T>, ColorRGBA<F>, KernelFunc>( filterX, filterY, size, convolutionOrder, convolutionMode, color, kernelFunc );
		}
	}

	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename SumType, typename KernelFunc>
	ImageT<T2> ImageT<T>::_applyFilter( const float * filterX, const float * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		return _applyFilterf<T1, C1, T2, C2, KernelFunc, float>( filterX, filterY, size, convolutionOrder, convolutionMode, color, kernelFunc );
	}
	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename SumType, typename KernelFunc>
	ImageT<T2> ImageT<T>::_applyFilter( const double * filterX, const double * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		return _applyFilterf<T1, C1, T2, C2, KernelFunc, double>( filterX, filterY, size, convolutionOrder, convolutionMode, color, kernelFunc );
	}

	template<typename T>
	template<typename F, typename KernelFunc, typename T1>
	ImageT<T> ImageT<T>::applyFilter( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & kernelFunc ) const {
		if ( getDatas() == NULL ) return *this;
		switch ( getFormat() ) {
			case Format::R: return _applyFilter<T1, ColorR<T>, T, ColorR<T>, ColorR<F>, KernelFunc>( filter, size, convolutionMode, color, kernelFunc );
			case Format::RGB: return _applyFilter<T1, ColorRGB<T>, T, ColorRGB<T>, ColorRGB<F>, KernelFunc>( filter, size, convolutionMode, color, kernelFunc );
			case Format::RGBA: return _applyFilter<T1, ColorRGBA<T>, T, ColorRGBA<T>, ColorRGBA<F>, KernelFunc>( filter, size, convolutionMode, color, kernelFunc );
		}
	}




	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename SumType, typename KernelFunc>
	ImageT<T2> ImageT<T>::_applyFilter( const float * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		return _applyFilterf<T1, C1, T2, C2, KernelFunc, float>( filter, size, convolutionMode, color, kernelFunc );
	}

	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename SumType, typename KernelFunc>
	ImageT<T2> ImageT<T>::_applyFilter( const double * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		return _applyFilterf<T1, C1, T2, C2, KernelFunc, double>( filter, size, convolutionMode, color, kernelFunc );
	}

	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc, typename F>
	ImageT<T2> ImageT<T>::_applyFilter( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		assert( size.x % 2 == 1 );
		assert( size.y % 2 == 1 );

		Math::Vec2<typename Size> NHalfed( size.x / 2, size.y / 2 );
		Math::Vec2<typename Size> NEven( NHalfed * 2 );

		Math::Vec2<typename Size> borderSize1;
		Math::Vec2<typename Size> borderSize2;

		switch ( convolutionMode ) {
			case ConvolutionMode::ExtendedSize:
				borderSize1 = NHalfed;
				borderSize2 = NHalfed - 1;
				break;
			case ConvolutionMode::NormalSize:
				borderSize1 = NHalfed;
				borderSize2 = 0;
		}

		Math::Vec2<typename Size> borderSize = borderSize1 + borderSize2;


		Math::Vec2<Size> sizeExtended( this -> size.x + borderSize2.x * 2, this -> size.y + borderSize2.y * 2 );
		Math::Vec2<Size> sizeBorder( this -> size.x + borderSize.x * 2, this -> size.y + borderSize.y * 2 );

		ImageT<T2> imageBorder( sizeBorder, this -> getFormat() );
		ImageT<T2> imageExtended( sizeExtended, this -> getFormat() );


		unsigned int nbComponentsPerRow = this -> getSize().x;
		unsigned int nbComponentsPerRowWithBorder = imageBorder.getSize().x;
		unsigned int nbComponentsPerRowExtended = sizeExtended.x;

		//drawing the background color 
		{
			auto imageBorderIt = imageBorder.getDatas<C2>();
			auto imageBorderEndIt = imageBorderIt + imageBorder.getSize().x * imageBorder.getSize().y;

			// Left
			for ( auto it = imageBorderIt; it < imageBorderEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize.x; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}
			//Right
			for ( auto it = imageBorderIt + imageBorder.getSize().x - borderSize.x; it < imageBorderEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize.x; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}

			//Top
			for ( auto it = imageBorderEndIt - borderSize.y * imageBorder.getSize().x; it < imageBorderEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );

			//Bottom
			imageBorderEndIt = imageBorderIt + imageBorder.getSize().x * borderSize.y;
			for ( auto it = imageBorderIt; it < imageBorderEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );
		}

		//copy the old image into a bigger one to handle border correctly without overflow
		{
			auto thisIt = this -> getDatas<C1>();
			auto imageBorderIt = imageBorder.getDatas<C2>( borderSize.x, borderSize.y );
			for ( typename Math::Vec2<Size>::Type y = 0; y < this -> size.y; y++ ) {
				Vector<T>::copy( imageBorderIt, thisIt, nbComponentsPerRow );

				thisIt += nbComponentsPerRow;
				imageBorderIt += nbComponentsPerRowWithBorder;
			}
		}

		{
			auto imageBorderIt = imageBorder.getDatas<C2>();
			auto imageExtendedIt = imageExtended.getDatas<C2>();

			constexpr F max( ( 1 << ImageT<T1>::getKernelSumNbBits<F>() ) * Color<T1>::getMax() );

			for ( typename Math::Vec2<Size>::Type y = 0; y < imageExtended.getSize().y; y++ ) {
				auto imageExtendedIt2 = imageBorderIt;
				auto imageHoriIt2 = imageExtendedIt;
				for ( typename Math::Vec2<Size>::Type x = 0; x < imageExtended.getSize().x; x++ ) {
					auto imageExtendedIt3 = imageExtendedIt2;
					auto filterIt2 = filter;

					Sum sum( 0 );
					for ( Size y = 0; y < size.y; y++ ) {
						auto imageExtendedIt4 = imageExtendedIt3;
						for ( Size x = 0; x < size.x; x++ ) {
							sum += Sum( imageExtendedIt4[0] ) * *( filterIt2 );

							imageExtendedIt4++;
							filterIt2++;
						}
						imageExtendedIt3 += nbComponentsPerRowWithBorder;
					}
					kernelFunc( sum, max );
					imageHoriIt2[0] = C2( sum >> ImageT<T1>::getKernelSumNbBits<F>() );

					imageExtendedIt2++;
					imageHoriIt2++;
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageExtendedIt += nbComponentsPerRowExtended;
			}
		}
		return imageExtended;
	}


	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename KernelFunc, typename F>
	ImageT<T2> ImageT<T>::_applyFilterf( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		assert( size.x % 2 == 1 );
		assert( size.y % 2 == 1 );

		Math::Vec2<typename Size> NHalfed( size.x / 2, size.y / 2 );
		Math::Vec2<typename Size> NEven( NHalfed * 2 );

		Math::Vec2<typename Size> borderSize1;
		Math::Vec2<typename Size> borderSize2;

		switch ( convolutionMode ) {
			case ConvolutionMode::ExtendedSize:
				borderSize1 = NHalfed;
				borderSize2 = NHalfed - 1;
				break;
			case ConvolutionMode::NormalSize:
				borderSize1 = NHalfed;
				borderSize2 = 0;
		}

		Math::Vec2<typename Size> borderSize = borderSize1 + borderSize2;


		Math::Vec2<Size> sizeExtended( this -> size.x + borderSize2.x * 2, this -> size.y + borderSize2.y * 2 );
		Math::Vec2<Size> sizeBorder( this -> size.x + borderSize.x * 2, this -> size.y + borderSize.y * 2 );

		ImageT<T2> imageBorder( sizeBorder, this -> getFormat() );
		ImageT<T2> imageExtended( sizeExtended, this -> getFormat() );


		unsigned int nbComponentsPerRow = this -> getSize().x;
		unsigned int nbComponentsPerRowWithBorder = imageBorder.getSize().x;
		unsigned int nbComponentsPerRowExtended = sizeExtended.x;

		//drawing the background color 
		{
			auto imageBorderIt = imageBorder.getDatas<C2>();
			auto imageBorderEndIt = imageBorderIt + imageBorder.getSize().x * imageBorder.getSize().y;

			// Left
			for ( auto it = imageBorderIt; it < imageBorderEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize.x; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}
			//Right
			for ( auto it = imageBorderIt + imageBorder.getSize().x - borderSize.x; it < imageBorderEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize.x; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}

			//Top
			for ( auto it = imageBorderEndIt - borderSize.y * imageBorder.getSize().x; it < imageBorderEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );

			//Bottom
			imageBorderEndIt = imageBorderIt + imageBorder.getSize().x * borderSize.y;
			for ( auto it = imageBorderIt; it < imageBorderEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );
		}

		//copy the old image into a bigger one to handle border correctly without overflow
		{
			auto thisIt = this -> getDatas<C1>();
			auto imageBorderIt = imageBorder.getDatas<C2>( borderSize.x, borderSize.y );
			for ( typename Math::Vec2<Size>::Type y = 0; y < this -> size.y; y++ ) {
				Vector<T>::copy( imageBorderIt, thisIt, nbComponentsPerRow );

				thisIt += nbComponentsPerRow;
				imageBorderIt += nbComponentsPerRowWithBorder;
			}
		}

		{
			auto imageBorderIt = imageBorder.getDatas<C2>();
			auto imageExtendedIt = imageExtended.getDatas<C2>();

			constexpr F max( 1.0f * Color<T1>::getMax() );

			for ( typename Math::Vec2<Size>::Type y = 0; y < imageExtended.getSize().y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageExtendedIt2 = imageExtendedIt;
				for ( typename Math::Vec2<Size>::Type x = 0; x < imageExtended.getSize().y; x++ ) {
					auto imageExtendedIt3 = imageBorderIt2;
					auto filterIt2 = filter;

					imageExtendedIt2[0] = C2( 0 );
					for ( Size y = 0; y < size.y; y++ ) {
						auto imageExtendedIt4 = imageExtendedIt3;
						for ( Size x = 0; x < size.x; x++ ) {
							imageExtendedIt2[0] += imageExtendedIt4[0] * *( filterIt2 );

							imageExtendedIt4++;
							filterIt2++;
						}
						imageExtendedIt3 += nbComponentsPerRowWithBorder;
					}
					kernelFunc( imageExtendedIt2[0], max );

					imageBorderIt2++;
					imageExtendedIt2++;
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageExtendedIt += nbComponentsPerRowExtended;
			}
		}
		return imageExtended;
	}



	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc, typename F>
	ImageT<T2> ImageT<T>::_applyFilter( const F * filterX, const F * filterY, Size kernelSize, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		assert( kernelSize % 2 == 1 );

		typename Size NHalfed( kernelSize / 2 );
		typename Size NEven( NHalfed * 2 );

		typename Size borderSize1;
		typename Size borderSize2;

		switch ( convolutionMode ) {
			case ConvolutionMode::ExtendedSize:
				borderSize1 = NHalfed;
				borderSize2 = NHalfed - 1;
				break;
			case ConvolutionMode::NormalSize:
				borderSize1 = NHalfed;
				borderSize2 = 0;
		}

		typename Math::Vec2<Size>::Type borderSize = borderSize1 + borderSize2;


		Math::Vec2<Size> sizeExtended( this -> size.x + borderSize2 * 2, this -> size.y + borderSize2 * 2 );
		Math::Vec2<Size> sizeBorder( this -> size.x + borderSize * 2, this -> size.y + borderSize * 2 );

		ImageT<T2> imageBorder( sizeBorder, this -> getFormat() );
		ImageT<T2> imageFilter1( imageBorder.getSize(), this -> getFormat() );
		ImageT<T2> imageFilter2( sizeExtended, this -> getFormat() );


		unsigned int nbComponentsPerRow = this -> getSize().x;
		unsigned int nbComponentsPerRowWithBorder = imageBorder.getSize().x;
		unsigned int nbComponentsPerRowExtended = imageFilter2.getSize().x;


		//drawing the background color 
		{
			C2 * imageHoriIt;
			C2 * imageHoriEndIt;
			C2 * imageVertIt;
			C2 * imageVertEndIt;

			if ( convolutionOrder == ConvolutionOrder::VerticalHorizontal ) {
				imageHoriIt = imageFilter1.getDatas<C2>();
				imageHoriEndIt = imageHoriIt + imageFilter1.getSize().x * imageFilter1.getSize().y;
				imageVertIt = imageBorder.getDatas<C2>();
				imageVertEndIt = imageVertIt + imageBorder.getSize().x * imageBorder.getSize().y;
			} else {
				imageHoriIt = imageBorder.getDatas<C2>();
				imageHoriEndIt = imageHoriIt + imageBorder.getSize().x * imageBorder.getSize().y;
				imageVertIt = imageFilter1.getDatas<C2>();
				imageVertEndIt = imageVertIt + imageFilter1.getSize().x * imageFilter1.getSize().y;
			}
			// Left
			for ( auto it = imageHoriIt; it < imageHoriEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}
			//Right
			for ( auto it = imageHoriIt + nbComponentsPerRowWithBorder - borderSize; it < imageHoriEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}

			//Top
			for ( auto it = imageVertEndIt - borderSize * nbComponentsPerRowWithBorder; it < imageVertEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );

			//Bottom
			imageVertEndIt = imageVertIt + nbComponentsPerRowWithBorder * borderSize;
			for ( auto it = imageVertIt; it < imageVertEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );
		}

		//copy the old image into a bigger one to handle border correctly without overflow
		{
			auto thisIt = this -> getDatas<C1>();
			C2 * imageBorderIt = imageBorder.getDatas<C2>( borderSize, borderSize );
			for ( typename Math::Vec2<Size>::Type y = 0; y < this -> size.y; y++ ) {
				Vector<T>::copy( imageBorderIt, thisIt, nbComponentsPerRow );

				thisIt += nbComponentsPerRow;
				imageBorderIt += nbComponentsPerRowWithBorder;
			}
		}

		constexpr F max( ( 1 << ImageT<T1>::getKernelSumNbBits<F>() ) * Color<T1>::getMax() );

		{
			C2 * imageFilter1It;
			C2 * imageBorderIt;
			unsigned int filterOffset;
			Math::Vec2<Size> size;

			if ( convolutionOrder == ConvolutionOrder::VerticalHorizontal ) {
				filterOffset = nbComponentsPerRowWithBorder;
				imageBorderIt = imageBorder.getDatas<C2>( borderSize, 0 );
				imageFilter1It = imageFilter1.getDatas<C2>( borderSize, borderSize1 );
				size.x = this -> size.x;
				size.y = sizeExtended.y;
			} else {
				filterOffset = 1;
				imageBorderIt = imageBorder.getDatas<C2>( 0, borderSize );
				imageFilter1It = imageFilter1.getDatas<C2>( borderSize1, borderSize );
				size.x = sizeExtended.x;
				size.y = this -> size.y;
			}


			for ( typename Math::Vec2<Size>::Type y = 0; y < size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageFilter1It2 = imageFilter1It;
				for ( typename Math::Vec2<Size>::Type x = 0; x < size.x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2;

					Sum sum( 0 );
					for ( Size i = 0; i < kernelSize; i++ ) {
						sum += Sum( imageBorderIt3[0] ) * filterX[i];
						//imageBorderIt3++;
						imageBorderIt3 += filterOffset;
					}
					kernelFunc( sum, max );
					imageFilter1It2[0] = C2( sum >> ImageT<T1>::getKernelSumNbBits<F>() );

					imageBorderIt2++;
					imageFilter1It2++;
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageFilter1It += nbComponentsPerRowWithBorder;
			}
		}

		{
			C2 * imageFilter2It;
			C2 * imageFilter1It;
			unsigned int filterOffset;
			Math::Vec2<Size> size;


			if ( convolutionOrder == ConvolutionOrder::VerticalHorizontal ) {
				filterOffset = 1;
				imageFilter2It = imageFilter2.getDatas<C2>();
				imageFilter1It = imageFilter1.getDatas<C2>( 0, borderSize1 );
				size.x = sizeExtended.x;
				size.y = sizeExtended.y;
			} else {
				filterOffset = nbComponentsPerRowWithBorder;
				imageFilter2It = imageFilter2.getDatas<C2>();
				imageFilter1It = imageFilter1.getDatas<C2>( borderSize1, 0 );
				size.x = sizeExtended.x;
				size.y = sizeExtended.y;
			}


			for ( typename Math::Vec2<Size>::Type y = 0; y < size.y; y++ ) {
				auto imageFilter2It2 = imageFilter2It;
				auto imageFilter1It2 = imageFilter1It;
				for ( typename Math::Vec2<Size>::Type x = 0; x < size.x; x++ ) {

					auto resultHoriIt3 = imageFilter1It2;

					Sum sum( 0 );
					for ( Size i = 0; i < kernelSize; i++ ) {
						sum += Sum( resultHoriIt3[0] ) * filterY[i];
						resultHoriIt3 += filterOffset;
					}
					kernelFunc( sum, max );
					imageFilter2It2[0] = C2( sum >> ImageT<T1>::getKernelSumNbBits<F>() );

					imageFilter2It2++;
					imageFilter1It2++;
				}


				imageFilter2It += nbComponentsPerRowExtended;
				imageFilter1It += nbComponentsPerRowWithBorder;
			}
		}
		return imageFilter2;
	}






	template<typename T>
	template<typename T1, typename C1, typename T2, typename C2, typename KernelFunc, typename F>
	ImageT<T2> ImageT<T>::_applyFilterf( const F * filterX, const F * filterY, Size kernelSize, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & kernelFunc ) const {
		assert( size % 2 == 1 );
		assert( ( Utility::isSame<T, F>::value ) );

		typename Size NHalfed( kernelSize / 2 );
		typename Size NEven( NHalfed * 2 );

		typename Size borderSize1;
		typename Size borderSize2;

		switch ( convolutionMode ) {
			case ConvolutionMode::ExtendedSize:
				borderSize1 = NHalfed;
				borderSize2 = NHalfed - 1;
				break;
			case ConvolutionMode::NormalSize:
				borderSize1 = NHalfed;
				borderSize2 = 0;
		}

		typename Math::Vec2<Size>::Type borderSize = borderSize1 + borderSize2;


		Math::Vec2<Size> sizeExtended( this -> size.x + borderSize2 * 2, this -> size.y + borderSize2 * 2 );
		Math::Vec2<Size> sizeBorder( this -> size.x + borderSize * 2, this -> size.y + borderSize * 2 );

		ImageT<T2> imageBorder( sizeBorder, this -> getFormat() );
		ImageT<T2> imageFilter1( imageBorder.getSize(), this -> getFormat() );
		ImageT<T2> imageFilter2( sizeExtended, this -> getFormat() );


		unsigned int nbComponentsPerRow = this -> getSize().x;
		unsigned int nbComponentsPerRowWithBorder = imageBorder.getSize().x;
		unsigned int nbComponentsPerRowExtended = imageFilter2.getSize().x;


		//drawing the background color 
		{
			C2 * imageHoriIt;
			C2 * imageHoriEndIt;
			C2 * imageVertIt;
			C2 * imageVertEndIt;

			if ( convolutionOrder == ConvolutionOrder::VerticalHorizontal ) {
				imageHoriIt = imageFilter1.getDatas<C2>();
				imageHoriEndIt = imageHoriIt + imageFilter1.getSize().x * imageFilter1.getSize().y;
				imageVertIt = imageBorder.getDatas<C2>();
				imageVertEndIt = imageVertIt + imageBorder.getSize().x * imageBorder.getSize().y;
			} else {
				imageHoriIt = imageBorder.getDatas<C2>();
				imageHoriEndIt = imageHoriIt + imageBorder.getSize().x * imageBorder.getSize().y;
				imageVertIt = imageFilter1.getDatas<C2>();
				imageVertEndIt = imageVertIt + imageFilter1.getSize().x * imageFilter1.getSize().y;
			}
			// Left
			for ( auto it = imageHoriIt; it < imageHoriEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}
			//Right
			for ( auto it = imageHoriIt + nbComponentsPerRowWithBorder - borderSize; it < imageHoriEndIt; it += nbComponentsPerRowWithBorder ) {
				auto it2 = it;
				for ( Size x = 0; x < borderSize; x++ ) {
					BlendingFunc::None::blendColor( *it2, color );
					it2++;
				}
			}

			//Top
			for ( auto it = imageVertEndIt - borderSize * nbComponentsPerRowWithBorder; it < imageVertEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );

			//Bottom
			imageVertEndIt = imageVertIt + nbComponentsPerRowWithBorder * borderSize;
			for ( auto it = imageVertIt; it < imageVertEndIt; it++ )
				BlendingFunc::None::blendColor( *it, color );
		}

		//copy the old image into a bigger one to handle border correctly without overflow
		{
			auto thisIt = this -> getDatas<C1>();
			auto imageBorderIt = imageBorder.getDatas<C2>( borderSize, borderSize );
			for ( typename Math::Vec2<Size>::Type y = 0; y < this -> size.y; y++ ) {
				Vector<T>::copy( imageBorderIt, thisIt, nbComponentsPerRow );

				thisIt += nbComponentsPerRow;
				imageBorderIt += nbComponentsPerRowWithBorder;
			}
		}

		constexpr F max( 1.0 * Color<T1>::getMax() );

		{
			C2 * imageFilter1It;
			C2 * imageBorderIt;
			unsigned int filterOffset;
			Math::Vec2<Size> size;

			if ( convolutionOrder == ConvolutionOrder::VerticalHorizontal ) {
				filterOffset = nbComponentsPerRowWithBorder;
				imageBorderIt = imageBorder.getDatas<C2>( borderSize, 0 );
				imageFilter1It = imageFilter1.getDatas<C2>( borderSize, borderSize1 );
				size.x = this -> size.x;
				size.y = sizeExtended.y;
			} else {
				filterOffset = 1;
				imageBorderIt = imageBorder.getDatas<C2>( 0, borderSize );
				imageFilter1It = imageFilter1.getDatas<C2>( borderSize1, borderSize );
				size.x = sizeExtended.x;
				size.y = this -> size.y;
			}


			for ( typename Math::Vec2<Size>::Type y = 0; y < size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageFilter1It2 = imageFilter1It;
				for ( typename Math::Vec2<Size>::Type x = 0; x < size.x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2;

					imageFilter1It2[0] = C2( 0.0 );
					for ( Size i = 0; i < kernelSize; i++ ) {
						imageFilter1It2[0] += imageBorderIt3[0] * filterX[i];
						imageBorderIt3 += filterOffset;
					}
					kernelFunc( imageFilter1It2[0], max );

					imageBorderIt2++;
					imageFilter1It2++;
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageFilter1It += nbComponentsPerRowWithBorder;
			}
		}

		{
			C2 * imageFilter2It;
			C2 * imageFilter1It;
			unsigned int filterOffset;
			Math::Vec2<Size> size;


			if ( convolutionOrder == ConvolutionOrder::VerticalHorizontal ) {
				filterOffset = 1;
				imageFilter2It = imageFilter2.getDatas<C2>();
				imageFilter1It = imageFilter1.getDatas<C2>( 0, borderSize1 );
				size.x = sizeExtended.x;
				size.y = sizeExtended.y;
			} else {
				filterOffset = nbComponentsPerRowWithBorder;
				imageFilter2It = imageFilter2.getDatas<C2>();
				imageFilter1It = imageFilter1.getDatas<C2>( borderSize1, 0 );
				size.x = sizeExtended.x;
				size.y = sizeExtended.y;
			}


			for ( typename Math::Vec2<Size>::Type y = 0; y < size.y; y++ ) {
				auto imageFilter2It2 = imageFilter2It;
				auto imageFilter1It2 = imageFilter1It;
				for ( typename Math::Vec2<Size>::Type x = 0; x < size.x; x++ ) {

					auto resultHoriIt3 = imageFilter1It2;

					imageFilter2It2[0] = C2( 0.0 );
					for ( Size i = 0; i < kernelSize; i++ ) {
						imageFilter2It2[0] += resultHoriIt3[0] * filterY[i];
						resultHoriIt3 += filterOffset;
					}
					kernelFunc( imageFilter2It2[0], max );

					imageFilter2It2++;
					imageFilter1It2++;
				}


				imageFilter2It += nbComponentsPerRowExtended;
				imageFilter1It += nbComponentsPerRowWithBorder;
			}
		}
		return imageFilter2;
	}



	template<typename T>
	template<typename K>
	constexpr K ImageT<T>::getKernelSumNbBits() {
		assert( Utility::TypesInfos<K>::getNbBits() - Utility::TypesInfos<T>::getNbBits() > 6 );
		return Utility::TypesInfos<K>::getNbBits() - Utility::TypesInfos<T>::getNbBits() - 6;
	}



	template<typename T>
	template<typename ConvertFunc>
	ImageT<T> ImageT<T>::toFormat( Format newFormat, ConvertFunc & convertFunc ) const {
		switch ( newFormat ) {
			case Format::R:
				{
					switch ( this -> format ) {
						case Format::R: 	//Convert R -> R
							return _toFormat<ColorR<T>, ColorR<T>, ConvertFunc>( newFormat, convertFunc );
						case Format::RGB: 	//Convert RGB -> R
							return _toFormat<ColorR<T>, ColorRGB<T>, ConvertFunc>( newFormat, convertFunc );
						case Format::RGBA: 	//Convert RGBA -> R
							return _toFormat<ColorR<T>, ColorRGBA<T>, ConvertFunc>( newFormat, convertFunc );
					}
				}
			case Format::RGB:
				{
					switch ( this -> format ) {
						case Format::R: 	//Convert R -> RGB
							return _toFormat<ColorRGB<T>, ColorR<T>, ConvertFunc>( newFormat, convertFunc );
						case Format::RGB: 	//Convert RGB -> RGB
							return _toFormat<ColorRGB<T>, ColorRGB<T>, ConvertFunc>( newFormat, convertFunc );
						case Format::RGBA: 	//Convert RGBA -> RGB
							return _toFormat<ColorRGB<T>, ColorRGBA<T>, ConvertFunc>( newFormat, convertFunc );
					}
				}
			case Format::RGBA:
				{
					switch ( this -> format ) {
						case Format::R: 	//Convert R -> RGBA
							return _toFormat<ColorRGBA<T>, ColorR<T>, ConvertFunc>( newFormat, convertFunc );
						case Format::RGB: 	//Convert RGB -> RGBA
							return _toFormat<ColorRGBA<T>, ColorRGB<T>, ConvertFunc>( newFormat, convertFunc );
						case Format::RGBA: 	//Convert RGBA -> RGBA
							return _toFormat<ColorRGBA<T>, ColorRGBA<T>, ConvertFunc>( newFormat, convertFunc );
					}
				}
		}
	}


	template<typename T>
	template<typename C1, typename C2, typename ConvertFunc>
	ImageT<T> ImageT<T>::_toFormat( Format newFormat, ConvertFunc & convertFunc ) const {
		ImageT<T> newImage( getSize(), newFormat );

		auto newImageIt0 = newImage.getDatas<C1>();
		auto thisImageIt0 = getDatas<C2>();

		_toFormat<C1, C2, ConvertFunc>( newImageIt0, thisImageIt0, convertFunc );

		return newImage;
	}

	template<typename T>
	template<typename C1, typename C2, typename ConvertFunc>
	void ImageT<T>::_toFormat( C1 * bufferDst, const C2 * bufferSrc, ConvertFunc & convertFunc ) const {
		size_t nbPixels( getNbPixels() );
		for ( size_t i( 0 ); i < nbPixels; i++ ) {

			C1 & colorDst( bufferDst[0] );
			const C2 & colorSrc( bufferSrc[0] );

			convertFunc( colorDst, colorSrc );
			//TODO memory leak near here
			bufferDst++;
			bufferSrc++;
		}
	}


	template<typename T>
	unsigned int Graphic::ImageT<T>::getNbComponents() const {
		return ( unsigned int ) this -> format;
	}


	template<typename T>
	Format ImageT<T>::_loadingFormat2Format( LoadingFormat loadingFormat ) {
		switch ( loadingFormat ) {
			case LoadingFormat::R:
				return Format::R;
			case LoadingFormat::RGB:
				return Format::RGB;
			case LoadingFormat::RGBA:
				return Format::RGBA;
			case LoadingFormat::BGR:
				return Format::RGB;
			case LoadingFormat::BGRA:
				return Format::RGBA;
			default:
				return Format::RGB;
		}
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const ColorR<T> & color, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, ColorR<T>>( rectangle, color, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, ColorR<T>>( rectangle, color, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, ColorR<T>>( rectangle, color, blendFunc );
		}
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const ColorRGB<T> & color, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, ColorRGB<T>>( rectangle, color, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, ColorRGB<T>>( rectangle, color, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, ColorRGB<T>>( rectangle, color, blendFunc );
		}
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const ColorRGBA<T> & color, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, ColorRGBA<T>>( rectangle, color, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, ColorRGBA<T>>( rectangle, color, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, ColorRGBA<T>>( rectangle, color, blendFunc );
		}
	}


	template<typename T>
	template<typename BlendFunc, typename C1, typename C2>
	void ImageT<T>::_drawRectangle( const Rectangle & rectangle, const C2 & color, const BlendFunc & functor ) {
		Math::Rectangle<Size> rectangleClamped = clampRectangle( rectangle );
		auto it = getDatas<C1>( rectangleClamped.getLeft(), rectangleClamped.getBottom() );
		typename Math::Vec2<Size>::Type width = rectangleClamped.getRight() - rectangleClamped.getLeft();
		Size nbComponentsPerLineRectangle = width;
		Size nbComponentsPerLine = this -> size.x;


		for ( typename Math::Vec2<Size>::Type y = rectangleClamped.getBottom(); y < rectangleClamped.getTop(); y++ ) {
			auto maxIt = it + nbComponentsPerLineRectangle;
			for ( auto it2 = it; it2 < maxIt; it2++ ) {
				functor( *( it2 ), color );
			}
			it += nbComponentsPerLine;
		}
	}



	template<typename T>
	template<typename C, typename InterFunc, typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const Gradient::Linear<C, InterFunc> & gradient, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, blendFunc );
		}
	}

	template<typename T>
	template<typename C, typename InterFunc, typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const Gradient::Radial<C, InterFunc> & gradient, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, blendFunc );
		}
	}

	template<typename T>
	template<typename C, typename InterFunc, typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, blendFunc );
		}
	}

	template<typename T>
	template<typename C, typename InterFunc, typename BlendFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const Gradient::Vertical<C, InterFunc> & gradient, const BlendFunc & blendFunc ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGB:
				return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>( rectangle, gradient, blendFunc );
			case Format::RGBA:
				return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>( rectangle, gradient, blendFunc );
		}
	}


	template<typename T>
	template<typename C, typename InterFunc>
	void ImageT<T>::drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C, InterFunc> & gradient ) {
		switch ( getFormat() ) {
			case Format::R:
				return _drawRectangle<ColorR<T>, C, InterFunc>( rectangle, gradient );
			case Format::RGB:
				return _drawRectangle<ColorRGB<T>, C, InterFunc>( rectangle, gradient );
			case Format::RGBA:
				return _drawRectangle<ColorRGBA<T>, C, InterFunc>( rectangle, gradient );
		}
	}




	template<typename T>
	template<typename C, typename InterFunc>
	size_t ImageT<T>::computeInterpolation( const Gradient::Horizontal<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle )  const {
		float size = rectangle.getRight() - rectangle.getLeft();
		*clampedRectangle = clampRectangle( rectangle );
		Size clampedSize = clampedRectangle -> getRight() - clampedRectangle -> getLeft();

		float begin = float( int( clampedRectangle -> getLeft() ) - rectangle.getLeft() ) / size;
		float end = 1.0f - float( rectangle.getRight() - int( clampedRectangle -> getRight() ) ) / size;

		//generate the gradient
		*buffer = new C[clampedSize];
		gradient.computeInterpolation( *buffer, clampedSize, begin, end );

		return clampedSize;
	}




	template<typename T>
	template<typename C1, typename C2, typename InterFunc>
	void ImageT<T>::_drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C2, InterFunc> & gradient ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C2 ) / sizeof( T );

		C2 * gradientArray;
		Math::Rectangle<Size> clampedRectangle;
		size_t size = computeInterpolation( gradient, &gradientArray, rectangle, &clampedRectangle );

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		if ( ( N1 != 4 ) && ( N1 == N2 ) ) {
			for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
				Vector<T>::copy( ( C2* ) thisIt, gradientArray, size );
				thisIt += thisImageOffset;
			}
		} else {
			for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
				auto maxIt = thisIt + size;
				auto gradientIt = gradientArray;
				for ( auto thisIt2 = thisIt; thisIt2 < maxIt; ) {
					BlendingFunc::Normal::blendColor( *( ( C1* ) thisIt2 ), *( ( C2* ) gradientIt ) );
					thisIt2++;
					gradientIt++;
				}
				thisIt += thisImageOffset;
			}
		}

		//free the buffer
		delete[] gradientArray;
	}


	template<typename T>
	template<typename C1, typename C2, typename InterFunc>
	void ImageT<T>::_fillImage( const Gradient::Horizontal<C2, InterFunc> & gradient, const Rectangle & rectangle ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C2 ) / sizeof( T );

		C2 * gradientArray;
		Math::Rectangle<Size> clampedRectangle;
		size_t size = computeInterpolation( gradient, &gradientArray, rectangle, &clampedRectangle );

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		if ( ( N1 == N2 ) ) {
			for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
				Vector<T>::copy( ( C2* ) thisIt, gradientArray, size );
				thisIt += thisImageOffset;
			}
		} else {
			for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
				auto maxIt = thisIt + size;
				auto gradientIt = gradientArray;
				for ( auto thisIt2 = thisIt; thisIt2 < maxIt; ) {
					BlendingFunc::None::blendColor( *( thisIt2 ), *( gradientIt ) );
					thisIt2++;
					gradientIt++;
				}
				thisIt += thisImageOffset;
			}
		}

		//free the buffer
		delete[] gradientArray;
	}




	template<typename T>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void ImageT<T>::_drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor ) {
		C2 * gradientArray;
		Math::Rectangle<Size> clampedRectangle;
		size_t size = computeInterpolation( gradient, &gradientArray, rectangle, &clampedRectangle );

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
			auto maxIt = thisIt + size;
			auto gradientIt = gradientArray;
			for ( auto thisIt2 = thisIt; thisIt2 < maxIt; thisIt2++ ) {
				blendingFunctor( *( thisIt2 ), *( gradientIt ) );
				gradientIt++;
			}
			thisIt += thisImageOffset;
		}

		//free the buffer
		delete[] gradientArray;
	}


	template<typename T>
	template<typename C, typename InterFunc>
	size_t ImageT<T>::computeInterpolation( const Gradient::Vertical<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const {
		float size = rectangle.getTop() - rectangle.getBottom();
		*clampedRectangle = clampRectangle( rectangle );
		Size clampedSize = clampedRectangle -> getTop() - clampedRectangle -> getBottom();

		float begin = float( int( clampedRectangle -> getBottom() ) - rectangle.getBottom() ) / size;
		float end = 1.0f - float( rectangle.getTop() - int( clampedRectangle -> getTop() ) ) / size;

		//generate the gradient
		*buffer = new C[clampedSize];
		gradient.computeInterpolation( *buffer, clampedSize, begin, end );

		return clampedSize;
	}

	template<typename T>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void ImageT<T>::_drawRectangle( const Rectangle & rectangle, const Gradient::Vertical<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor ) {

		C2 * gradientArray;
		Math::Rectangle<Size> clampedRectangle;
		size_t size = computeInterpolation( gradient, &gradientArray, rectangle, &clampedRectangle );

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		auto gradientIt = gradientArray;
		for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = clampedRectangle.getLeft(); i.x < clampedRectangle.getRight(); i.x++ ) {
				blendingFunctor( *( thisIt2 ), *( gradientIt ) );
				thisIt2++;
			}
			gradientIt++;
			thisIt += thisImageOffset;
		}
		//free the buffer
		delete[] gradientArray;
	}



	template<typename T>
	template<typename C, typename InterFunc>
	size_t ImageT<T>::computeInterpolation( const Gradient::Linear<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const {
		Math::Vec2<int> size = rectangle.getRightTop() - rectangle.getLeftBottom();
		*clampedRectangle = clampRectangle( rectangle );

		size_t gradientSize;
		if ( gradient.getLength() == 0 )
			gradientSize = size.x * Math::abs( gradient.getDirection().x ) + size.y * Math::abs( gradient.getDirection().y );
		else
			gradientSize = gradient.getLength();

		*buffer = new C[gradientSize];
		gradient.computeInterpolation( *buffer, gradientSize );

		return gradientSize;
	}


	template<typename T>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void ImageT<T>::_drawRectangle( const Rectangle & rectangle, const Gradient::Linear<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor ) {
		Math::Rectangle<Size> clampedRectangle;
		C2 * gradientArray;
		size_t size = computeInterpolation( gradient, &gradientArray, rectangle, &clampedRectangle );
		int gradientSizeMinusOne = int( size ) - 1;


		Point origin( rectangle.getLeft() + gradient.getPoint().x * float( rectangle.getRight() - rectangle.getLeft() ),
					  rectangle.getBottom() + gradient.getPoint().y * float( rectangle.getTop() - rectangle.getBottom() ) );

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = clampedRectangle.getLeft(); i.x < clampedRectangle.getRight(); i.x++ ) {
				auto index = gradient.computeIndex( Math::Vec2<float>( ( ( typename Point::Type ) i.x ) - origin.x, ( ( typename Point::Type ) i.y ) - origin.y ), gradientSizeMinusOne );
				blendingFunctor( *( thisIt2 ), gradientArray[index] );
				thisIt2++;
			}
			thisIt += thisImageOffset;
		}
		delete[] gradientArray;
	}


	template<typename T>
	template<typename C, typename InterFunc>
	size_t ImageT<T>::computeInterpolation( const Gradient::Radial<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const {
		*clampedRectangle = clampRectangle( rectangle );
		Math::Vec2<int> size = rectangle.getRightTop() - rectangle.getLeftBottom();
		Math::Vec2<Size> sizeClamped = clampedRectangle -> getRightTop() - clampedRectangle -> getLeftBottom();

		size_t gradientSize = int( Math::max<float>( gradient.getRadius().x * float( size.x ), gradient.getRadius().y * float( size.y ) ) * 2.0f );

		*buffer = new C[gradientSize];
		gradient.computeInterpolation( *buffer, gradientSize );

		return gradientSize;
	}



	template<typename T>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void ImageT<T>::_drawRectangle( const Rectangle & rectangle, const Gradient::Radial<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor ) {
		Math::Rectangle<Size> clampedRectangle;
		C2 * gradientArray;
		size_t size = computeInterpolation( gradient, &gradientArray, rectangle, &clampedRectangle );
		int gradientSizeMinusOne = int( size ) - 1;

		Point center( rectangle.getLeft() + gradient.getCenter().x * float( rectangle.getRight() - rectangle.getLeft() ),
					  rectangle.getBottom() + gradient.getCenter().y * float( rectangle.getTop() - rectangle.getBottom() ) );

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = clampedRectangle.getLeft(); i.x < clampedRectangle.getRight(); i.x++ ) {
				auto index = gradient.computeIndex( Math::Vec2<float>( ( ( typename Point::Type ) i.x ) - center.x, ( ( typename Point::Type ) i.y ) - center.y ), gradientSizeMinusOne );
				blendingFunctor( *( thisIt2 ), gradientArray[index] );
				thisIt2++;
			}
			thisIt += thisImageOffset;
		}
		delete[] gradientArray;
	}




	//////////////////////////////////////////////////////////////////////////


	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawRectangleFunctor( const Rectangle & rectangle, ColorFunc & colorFunctor, const BlendFunc & blendingFunctor ) {
		switch ( this -> format ) {
			case Format::R:
				return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorR<T>>( rectangle, colorFunctor, blendingFunctor );
			case Format::RGB:
				return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGB<T>>( rectangle, colorFunctor, blendingFunctor );
			case Format::RGBA:
				return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGBA<T>>( rectangle, colorFunctor, blendingFunctor );
		}
	}



	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawRectangleFunctor( const Rectangle & rectangle, ColorFunc & colorFunctor, const BlendFunc & blendingFunctor ) {
		Math::Rectangle<Size> clampedRectangle = clampRectangle( rectangle );
		colorFunctor.init( clampedRectangle );
		Math::Vec2<Size> size = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		auto thisIt = getDatas<C1>( clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y );
		auto thisImageOffset = this -> size.x;

		Math::Vec2<Size> i;
		for ( i.y = 0; i.y < size.y; i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = 0; i.x < size.x; i.x++ ) {
				blendingFunctor( *( thisIt2 ), colorFunctor( i ) );
				thisIt2++;
			}
			thisIt += thisImageOffset;
		}

	}







	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawLine( const LineF & l, const ColorR<T> & color, unsigned int thickness, const BlendFunc & blendFunc ) {
		return drawLineFunctor<ColorFunc::SimpleColor<ColorR<T>>, BlendFunc>( l, ColorFunc::SimpleColor<ColorR<T>>( color ), thickness, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawLine( const LineF & l, const ColorRGB<T> & color, unsigned int thickness, const BlendFunc & blendFunc ) {
		return drawLineFunctor<ColorFunc::SimpleColor<ColorRGB<T>>, BlendFunc>( l, ColorFunc::SimpleColor<ColorRGB<T>>( color ), thickness, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawLine( const LineF & l, const ColorRGBA<T> & color, unsigned int thickness, const BlendFunc & blendFunc ) {
		return drawLineFunctor<ColorFunc::SimpleColor<ColorRGBA<T>>, BlendFunc>( l, ColorFunc::SimpleColor<ColorRGBA<T>>( color ), thickness, blendFunc );
	}

	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;
		switch ( getFormat() ) {
			case Format::R: return _drawLineFunctor<ColorFunc, BlendFunc, ColorR<T>>( l, colorFunc, thickness, blendFunc, static_cast< T * >( NULL ) );
			case Format::RGB: return _drawLineFunctor<ColorFunc, BlendFunc, ColorRGB<T>>( l, colorFunc, thickness, blendFunc, static_cast< T * >( NULL ) );
			case Format::RGBA: return _drawLineFunctor<ColorFunc, BlendFunc, ColorRGBA<T>>( l, colorFunc, thickness, blendFunc, static_cast< T * >( NULL ) );
		}
	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, typename Float * t ) {
		return _drawLineFunctorf<ColorFunc, BlendFunc, C1>( l, colorFunc, thickness, blendFunc );
	}




	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, ... ) {
		//see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm

		assert( ( Utility::isBase<Graphic::BlendingFunc::Template, BlendFunc>::value ) );

		if ( thickness == 0 ) return;


		float steepY( Math::abs( l.getP1().y - l.getP0().y ) );
		float steepX( Math::abs( l.getP1().x - l.getP0().x ) );

		bool steep = steepY > steepX;

		float thicknessHalfed;
		Math::Vec2<float> p0;
		Math::Vec2<float> p1;


		if ( steep ) {
			thickness = float( thickness ) * ( 1.0f + steepX / steepY * 0.5f );
			thicknessHalfed = float( thickness / 2 );

			Math::Line<float> lineClamped( l );
			if ( !Math::clamp( &lineClamped, Math::Rectangle<float>( thicknessHalfed + 1.0f, 0.0f, getSize().x - thicknessHalfed - 2.0f, getSize().y ) ) )
				return;

			p0.y = lineClamped.getP0().x - thicknessHalfed;
			p0.x = lineClamped.getP0().y;

			p1.y = lineClamped.getP1().x - thicknessHalfed;
			p1.x = lineClamped.getP1().y;
		} else {
			thickness = float( thickness ) * ( 1.0f + steepY / steepX * 0.5f );
			thicknessHalfed = float( thickness / 2 );

			Math::Line<float> lineClamped( l );
			if ( !Math::clamp( &lineClamped, Math::Rectangle<float>( 0.0f, thicknessHalfed + 1.0f, getSize().x, getSize().y - thicknessHalfed - 2.0f ) ) )
				return;

			p0.y = lineClamped.getP0().y - thicknessHalfed;
			p0.x = lineClamped.getP0().x;

			p1.y = lineClamped.getP1().y - thicknessHalfed;
			p1.x = lineClamped.getP1().x;
		}
		if ( p0.x > p1.x ) {
			Utility::swap( p0.x, p1.x );
			Utility::swap( p0.y, p1.y );
		}

		typedef Utility::TypesInfos<SumType>::Signed Bigger;



		float dx = p1.x - p0.x;
		float dy = p1.y - p0.y;
		float gradientF = dy / dx;

		float tmp = float( int( p0.x ) );
		p0.y = p0.y - gradientF * ( p0.x - tmp );
		p0.x = tmp;

		tmp = float( int( p1.x ) );
		p1.y = p1.y + gradientF * ( p1.x - tmp );
		p1.x = tmp;


		Math::Vec2<int> p0i( int( p0.x ), int( p0.y ) );
		Math::Vec2<int> p1i( int( p1.x ), int( p1.y ) );

		Bigger gradientI = Bigger( gradientF * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );
		Bigger intery = Bigger( ( p0.y - float( p0i.y ) ) * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );


		int thisRow = getSize().x;
		int thicknessMinusOne = int( thickness ) - 1;
		Math::Vec2<int> i;

		// Main loop
		if ( steep ) {

			if ( dy < 0 ) {
				//////////////////////////////////////////////////////////////////////////
				///// STEEP & dy < 0								   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p1i.y, p0i.x );

				Math::Rectangle<Size> rectangle( p1i.y, p0i.x, p0i.y + Size( thickness ) + 1, p1i.x );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );

				Bigger intery = Bigger( ( ( p0.y - float( p0i.y ) ) + ( p0i.y - p1i.y ) ) * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );

				i.y = 0;
				i.x = intery >> Utility::TypesInfos<T>::getNbBits();
				T interyFPart = T( intery );

				auto it0 = p0It;
				it0 = p0It + i.x;

				if ( i.x >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
				}
				it0++;
				i.x++;
				auto max = i.x + thicknessMinusOne;
				while ( i.x < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0++;
					i.x++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );

				intery += gradientI;
				p0It += thisRow;
				i.y++;

				for ( ; i.y < size.y; i.y++ ) {
					i.x = intery >> Utility::TypesInfos<T>::getNbBits();
					interyFPart = T( intery );

					it0 = p0It + i.x;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
					it0++;
					i.x++;
					max = i.x + thicknessMinusOne;
					while ( i.x < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0++;
						i.x++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientI;
					p0It += thisRow;
				}
			} else {
				//////////////////////////////////////////////////////////////////////////
				///// STEEP & dy >= 0								   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p0i.y, p0i.x );

				Math::Rectangle<Size> rectangle( p0i.y, p0i.x, p1i.y + Size( thickness ) + 1, p1i.x );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );

				Bigger intery = Bigger( ( p0.y - float( p0i.y ) ) * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );

				i.y = 0;
				i.x = intery >> Utility::TypesInfos<T>::getNbBits();
				T interyFPart = T( intery );

				auto it0 = p0It;
				it0 = p0It + i.x;

				if ( i.x >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
				}
				it0++;
				i.x++;
				auto max = i.x + thicknessMinusOne;
				while ( i.x < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0++;
					i.x++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );

				intery += gradientI;
				p0It += thisRow;
				i.y++;

				for ( ; i.y < size.y; i.y++ ) {
					i.x = intery >> Utility::TypesInfos<T>::getNbBits();
					interyFPart = T( intery );

					it0 = p0It + i.x;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
					it0++;
					i.x++;
					max = i.x + thicknessMinusOne;
					while ( i.x < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0++;
						i.x++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientI;
					p0It += thisRow;
				}
			}
		} else {
			if ( dy < 0 ) {
				//////////////////////////////////////////////////////////////////////////
				///// NO STEEP & dy < 0								   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p0i.x, p1i.y );

				Math::Rectangle<Size> rectangle( p0i.x, p1i.y, p1i.x, p0i.y + Size( thickness ) + 1 );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );


				Bigger intery = Bigger( ( ( p0.y - float( p0i.y ) ) + ( p0i.y - p1i.y ) ) * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );

				i.x = 0;
				i.y = intery >> Utility::TypesInfos<T>::getNbBits();
				T interyFPart = T( intery );


				auto it0 = p0It + i.y * thisRow;
				if ( i.y >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
				}
				i.y++;
				it0 += thisRow;
				auto max = i.y + thicknessMinusOne;
				while ( i.y < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0 += thisRow;
					i.y++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );

				intery += gradientI;
				p0It++;
				i.x++;

				for ( ; i.x < size.x; i.x++ ) {
					i.y = intery >> Utility::TypesInfos<T>::getNbBits();
					interyFPart = T( intery );

					it0 = p0It + i.y * thisRow;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
					it0 += thisRow;
					i.y++;
					max = i.y + thicknessMinusOne;
					while ( i.y < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0 += thisRow;
						i.y++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientI;
					p0It++;
				}

			} else {
				//////////////////////////////////////////////////////////////////////////
				///// NO STEEP & dy >= 0							   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p0i.x, p0i.y );

				Math::Rectangle<Size> rectangle( p0i.x, p0i.y, p1i.x, p1i.y + Size( thickness ) + 1 );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );


				Bigger intery = Bigger( ( p0.y - float( p0i.y ) ) * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );

				i.x = 0;
				i.y = intery >> Utility::TypesInfos<T>::getNbBits();
				T interyFPart = T( intery );

				auto it0 = p0It + i.y * thisRow;
				if ( i.y >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
				}
				i.y++;
				it0 += thisRow;
				auto max = i.y + thicknessMinusOne;
				while ( i.y < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0 += thisRow;
					i.y++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );

				intery += gradientI;
				p0It++;
				i.x++;

				for ( ; i.x < size.x; i.x++ ) {
					i.y = intery >> Utility::TypesInfos<T>::getNbBits();
					interyFPart = T( intery );

					it0 = p0It + i.y * thisRow;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), Color<T>::getMax() - interyFPart );
					it0 += thisRow;
					i.y++;
					max = i.y + thicknessMinusOne;
					while ( i.y < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0 += thisRow;
						i.y++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientI;
					p0It++;
				}
			}
		}
	}
















	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawLineFunctorf( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc ) {
		//see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm

		assert( ( Utility::isBase<Graphic::BlendingFunc::Template, BlendFunc>::value ) );

		if ( thickness == 0 ) return;


		float steepY( Math::abs( l.getP1().y - l.getP0().y ) );
		float steepX( Math::abs( l.getP1().x - l.getP0().x ) );

		bool steep = steepY > steepX;

		float thicknessHalfed;

		Math::Vec2<float> p0;
		Math::Vec2<float> p1;


		if ( steep ) {
			thickness = float( thickness ) * ( 1.0f + steepX / steepY * 0.5f );
			thicknessHalfed = float( thickness / 2 );

			Math::Line<float> lineClamped( l );
			if ( !Math::clamp( &lineClamped, Math::Rectangle<float>( thicknessHalfed + 1.0f, 0.0f, getSize().x - thicknessHalfed - 2.0f, getSize().y ) ) )
				return;

			p0.y = lineClamped.getP0().x - thicknessHalfed;
			p0.x = lineClamped.getP0().y;

			p1.y = lineClamped.getP1().x - thicknessHalfed;
			p1.x = lineClamped.getP1().y;
		} else {
			thickness = float( thickness ) * ( 1.0f + steepY / steepX * 0.5f );
			thicknessHalfed = float( thickness / 2 );

			Math::Line<float> lineClamped( l );
			if ( !Math::clamp( &lineClamped, Math::Rectangle<float>( 0.0f, thicknessHalfed + 1.0f, getSize().x, getSize().y - thicknessHalfed - 2.0f ) ) )
				return;

			p0.y = lineClamped.getP0().y - thicknessHalfed;
			p0.x = lineClamped.getP0().x;

			p1.y = lineClamped.getP1().y - thicknessHalfed;
			p1.x = lineClamped.getP1().x;
		}
		if ( p0.x > p1.x ) {
			Utility::swap( p0.x, p1.x );
			Utility::swap( p0.y, p1.y );
		}


		//Math::Vec2<int> p0i(int(p0.x + 0.5f), int(p0.y + 0.5f));
		//Math::Vec2<int> p1i(int(p1.x + 0.5f), int(p1.y + 0.5f));

		float dx = p1.x - p0.x;
		float dy = p1.y - p0.y;
		float gradientF = dy / dx;

		float tmp = float( int( p0.x ) );
		p0.y = p0.y - gradientF * ( p0.x - tmp );
		p0.x = tmp;


		tmp = float( int( p1.x ) );
		p1.y = p1.y + gradientF * ( p1.x - tmp );
		p1.x = tmp;

		Math::Vec2<int> p0i( int( p0.x ), int( p0.y ) );
		Math::Vec2<int> p1i( int( p1.x ), int( p1.y ) );



		int thisRow = getSize().x;
		int thicknessMinusOne = int( thickness ) - 1;
		Math::Vec2<int> i;

		// Main loop
		if ( steep ) {
			if ( dy < 0 ) {
				//////////////////////////////////////////////////////////////////////////
				///// STEEP & dy < 0								   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p1i.y, p0i.x );


				Math::Rectangle<Size> rectangle( p1i.y, p0i.x, p0i.y + Size( thickness ) + 1, p1i.x );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );

				float intery = ( p0.y - float( p0i.y ) ) + ( p0i.y - p1i.y );


				i.y = 0;
				i.x = int( intery );
				T interyFPart = intery - float( i.x );
				assert( interyFPart >= 0.0f && interyFPart <= 1.0f );


				auto it0 = p0It;
				it0 = p0It + i.x;

				if ( i.x >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
				}
				it0++;
				i.x++;
				auto max = i.x + thicknessMinusOne;
				while ( i.x < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0++;
					i.x++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );

				intery += gradientF;
				p0It += thisRow;
				i.y++;

				for ( ; i.y < size.y; i.y++ ) {
					i.x = int( intery );
					T interyFPart = intery - float( i.x );
					assert( interyFPart >= 0.0f && interyFPart <= 1.0f );

					it0 = p0It + i.x;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
					it0++;
					i.x++;
					max = i.x + thicknessMinusOne;
					while ( i.x < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0++;
						i.x++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientF;
					p0It += thisRow;
				}
			} else {
				//////////////////////////////////////////////////////////////////////////
				///// STEEP & dy >= 0								   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p0i.y, p0i.x );


				Math::Rectangle<Size> rectangle( p0i.y, p0i.x, p1i.y + Size( thickness ) + 1, p1i.x );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );

				float intery = ( p0.y - float( p0i.y ) );


				i.y = 0;
				i.x = int( intery );
				T interyFPart = intery - float( i.x );
				assert( interyFPart >= 0.0f && interyFPart <= 1.0f );

				auto it0 = p0It;
				it0 = p0It + i.x;

				if ( i.x >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
				}
				it0++;
				i.x++;
				auto max = i.x + thicknessMinusOne;
				while ( i.x < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0++;
					i.x++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );

				intery += gradientF;
				p0It += thisRow;
				i.y++;

				for ( ; i.y < size.y; i.y++ ) {
					i.x = int( intery );
					T interyFPart = intery - float( i.x );
					assert( interyFPart >= 0.0f && interyFPart <= 1.0f );

					it0 = p0It + i.x;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
					it0++;
					i.x++;
					max = i.x + thicknessMinusOne;
					while ( i.x < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0++;
						i.x++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientF;
					p0It += thisRow;
				}
			}
		} else {
			if ( dy < 0 ) {
				//////////////////////////////////////////////////////////////////////////
				///// NO STEEP & dy < 0								   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p0i.x, p1i.y );


				Math::Rectangle<Size> rectangle( p0i.x, p1i.y, p1i.x, p0i.y + Size( thickness ) + 1 );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );


				float intery = ( p0.y - float( p0i.y ) ) + ( p0i.y - p1i.y );

				colorFunc.init( rectangle );

				i.x = 0;
				i.y = int( intery );
				T interyFPart = intery - float( i.y );
				assert( interyFPart >= 0.0f && interyFPart <= 1.0f );

				auto it0 = p0It + i.y * thisRow;
				if ( i.y >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
				}
				i.y++;
				it0 += thisRow;
				auto max = i.y + thicknessMinusOne;
				while ( i.y < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0 += thisRow;
					i.y++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );



				intery += gradientF;
				p0It++;
				i.x++;

				for ( ; i.x < size.x; i.x++ ) {
					i.y = int( intery );
					T interyFPart = intery - float( i.y );
					assert( interyFPart >= 0.0f && interyFPart <= 1.0f );

					auto it0 = p0It + i.y * thisRow;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
					it0 += thisRow;
					i.y++;
					auto max = i.y + thicknessMinusOne;
					while ( i.y < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0 += thisRow;
						i.y++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientF;
					p0It++;
				}

			} else {
				//////////////////////////////////////////////////////////////////////////
				///// NO STEEP & dy >= 0							   /////
				//////////////////////////////////////////////////////////////////////////

				auto p0It = getDatas<C1>( p0i.x, p0i.y );

				Math::Rectangle<Size> rectangle( p0i.x, p0i.y, p1i.x, p1i.y + Size( thickness ) + 1 );
				assert( rectangle.getLeft() >= 0 && rectangle.getBottom() >= 0 && rectangle.getRight() <= this -> size.x && rectangle.getTop() <= this -> size.y );
				Math::Vec2<Size> size( rectangle.getRightTop() - rectangle.getLeftBottom() );

				colorFunc.init( rectangle );

				float intery = ( p0.y - float( p0i.y ) );




				i.x = 0;
				i.y = int( intery );
				T interyFPart = intery - float( i.y );
				assert( interyFPart >= 0.0f && interyFPart <= 1.0f );


				auto it0 = p0It + i.y * thisRow;
				if ( i.y >= 0 ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
				}
				i.y++;
				it0 += thisRow;
				auto max = i.y + thicknessMinusOne;
				while ( i.y < max ) {
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ) );
					it0 += thisRow;
					i.y++;
				}
				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *it0, colorFunc( i ), interyFPart );


				intery += gradientF;
				p0It++;
				i.x++;

				for ( ; i.x < size.x; i.x++ ) {
					i.y = int( intery );
					T interyFPart = intery - float( i.y );
					assert( interyFPart >= 0.0f && interyFPart <= 1.0f );


					auto it0 = p0It + i.y * thisRow;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), 1.0f - interyFPart );
					it0 += thisRow;
					i.y++;
					auto max = i.y + thicknessMinusOne;
					while ( i.y < max ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it0, colorFunc( i ) );
						it0 += thisRow;
						i.y++;
					}
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it0, colorFunc( i ), interyFPart );

					intery += gradientF;
					p0It++;
				}
			}
		}
	}










	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawLineFunctorFilledBottom( const LineF & l, ColorFunc & colorFunc, const Rectangle & rectangle, const BlendFunc & blendFunc ) {
		typedef Utility::TypesInfos<SumType>::Signed Bigger;

		assert( ( Utility::isBase<Graphic::BlendingFunc::Template, BlendFunc>::value ) );
		debug( Math::Vec2<typename Rectangle::Type> size( rectangle.getRightTop() - rectangle.getLeftBottom() ););

		Math::Vec2<float> p0;
		Math::Vec2<float> p1;


		p0.y = l.getP0().y;
		p0.x = l.getP0().x;

		p1.y = l.getP1().y;
		p1.x = l.getP1().x;

		float dx = p1.x - p0.x;
		float dy = p1.y - p0.y;

		bool steep = Math::abs( dy ) > Math::abs( dx );

		Math::Vec2<int> p0i( int( p0.x ), int( p0.y ) );
		Math::Vec2<int> p1i( int( p1.x ), int( p1.y ) );

		int thisRow = getSize().x;
		Math::Vec2<int> i( p0i.x - rectangle.getLeft(), p0i.y - rectangle.getBottom() );
		int xMax = p1i.x - rectangle.getLeft();
		auto p0It = getDatas<C1>( rectangle.getLeft(), rectangle.getBottom() );

		if ( steep ) {
			float gradientF = dx / dy;
			Bigger gradientI = -Bigger( gradientF * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );

			if ( dy < 0.0f ) {
				auto it = p0It + thisRow * i.y + i.x;

				Bigger intery = Bigger( 0 );
				for ( ; i.x < xMax; ) {
					int lastX = ( intery >> 8 );
					int newX;
					do {
						unsigned char opacity = unsigned char( intery );
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it, colorFunc( i ), opacity );

						intery += gradientI;
						newX = ( intery >> 8 );

						it -= thisRow;
						i.y--;
					} while ( lastX == newX );

					auto it2 = it;
					auto tmp = i.y;
					while ( i.y >= 0 ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it2, colorFunc( i ) );

						it2 -= thisRow;
						i.y--;
					}
					i.y = tmp;

					i.x++;
					it++;
				}

			} else {
				auto it = p0It + thisRow * i.y + i.x;

				Bigger intery = Bigger( -1 );
				for ( ; i.x < xMax; ) {
					auto it2 = it;
					auto tmp = i.y;
					while ( i.y > 0 ) {
						it2 -= thisRow;
						i.y--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it2, colorFunc( i ) );
					}
					i.y = tmp;

					int lastX = ( intery >> 8 );
					int newX;
					do {
						unsigned char opacity = unsigned char( intery );
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it, colorFunc( i ), opacity );

						intery += gradientI;
						newX = ( intery >> 8 );

						it += thisRow;
						i.y++;
					} while ( lastX == newX );
					i.x++;
					it++;
				}
			}
		} else {
			float gradientF = dy / dx;
			Bigger gradientI = Bigger( gradientF * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );

			if ( dy < 0.0f ) {
				Bigger intery = Bigger( ( p0.y - float( rectangle.getBottom() ) ) * ( 1 << Utility::TypesInfos<T>::getNbBits() ) );
				for ( ; i.x < xMax; ) {
					i.y = ( intery >> 8 );
					auto it = p0It + thisRow * i.y + i.x;

					unsigned char opacity = unsigned char( intery );
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it, colorFunc( i ), opacity );

					while ( i.y > 0 ) {
						it -= thisRow;
						i.y--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it, colorFunc( i ) );
					}

					intery += gradientI;
					i.x++;
					it++;
				}
			} else {
				Bigger intery = Bigger( ( p0.y - float( rectangle.getBottom() ) ) * float( 1 << Utility::TypesInfos<T>::getNbBits() ) );
				for ( ; i.x < xMax; ) {
					i.y = ( intery >> 8 );
					auto it = p0It + thisRow * i.y + i.x;

					auto it2 = it;
					auto tmp = i.y;
					while ( i.y > 0 ) {
						it2 -= thisRow;
						i.y--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *it2, colorFunc( i ) );
					}
					i.y = tmp;

					unsigned char opacity = unsigned char( intery );
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *it, colorFunc( i ), opacity );

					intery += gradientI;
					i.x++;
					it++;
				}
			}
		}
	}




	template<typename T>
	void ImageT<T>::threshold( const ColorRGBA<T> & colorOver, const ColorRGBA<T> & colorUnder, const ColorRGBA<T> & limit ) {
		struct Functor {
			Functor( const ColorRGBA<T> & c ) : c( c ) {}
			inline bool operator()( Graphic::ColorR<T> & color )const { return ( color > c.r ); }
			inline bool operator()( Graphic::ColorRGB<T> & color )const { return ( color.r > c.r && color.g > c.g && color.b > c.b ); }
			inline bool operator()( Graphic::ColorRGBA<T> & color )const { return ( color.r > c.r && color.g > c.g && color.b > c.b && color.a > c.a ); }
			const ColorRGBA<T> & c;
		};

		return threshold( colorOver, colorUnder, Functor( limit ) );
	}



	template<typename T>
	template<typename ThreshFunc>
	void ImageT<T>::threshold( const ColorRGBA<T> & colorTrue, const ColorRGBA<T> & colorFalse, const ThreshFunc & threshFunc ) {
		switch ( getFormat() ) {
			case Format::R: return _threshold<ThreshFunc, ColorR<T>, ColorRGBA<T>>( colorTrue, colorFalse, threshFunc );
			case Format::RGB: return _threshold<ThreshFunc, ColorRGB<T>, ColorRGBA<T>>( colorTrue, colorFalse, threshFunc );
			case Format::RGBA: return _threshold<ThreshFunc, ColorRGBA<T>, ColorRGBA<T>>( colorTrue, colorFalse, threshFunc );
		}
	}



	template<typename T>
	template<typename ThreshFunc, typename C1, typename C2>
	void ImageT<T>::_threshold( const C2 & colorTrue, const C2 & colorFalse, const ThreshFunc & threshFunc ) {
		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C1 ) / sizeof( T );

		auto it = this -> buffer;
		auto end = it + getNbPixels() * N1;
		for ( ; it < end; it += N1 ) {
			if ( threshFunc( *( ( C1 * ) it ) ) )
				BlendingFunc::None::blendColor( *( ( C1 * ) it ), colorTrue );
			else
				BlendingFunc::None::blendColor( *( ( C1 * ) it ), colorFalse );
		}
	}



	template<typename T>
	template<typename BlendFunc >
	void ImageT<T>::drawStroke( const Point & point, const ImageT<T> & image, float thickness, const ColorR<T> & color, StrokeType strokeType, const BlendFunc & blendFunc ) {
		return drawStrokeFunctor<ColorFunc::SimpleColor<ColorR<T>>, BlendFunc>( point, image, thickness, ColorFunc::SimpleColor<ColorR<T>>( color ), strokeType, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc >
	void ImageT<T>::drawStroke( const Point & point, const ImageT<T> & image, float thickness, const ColorRGB<T> & color, StrokeType strokeType, const BlendFunc & blendFunc ) {
		return drawStrokeFunctor<ColorFunc::SimpleColor<ColorRGB<T>>, BlendFunc>( point, image, thickness, ColorFunc::SimpleColor<ColorRGB<T>>( color ), strokeType, blendFunc );
	}

	template<typename T>
	template<typename BlendFunc >
	void ImageT<T>::drawStroke( const Point & point, const ImageT<T> & image, float thickness, const ColorRGBA<T> & color, StrokeType strokeType, const BlendFunc & blendFunc ) {
		return drawStrokeFunctor<ColorFunc::SimpleColor<ColorRGBA<T>>, BlendFunc>( point, image, thickness, ColorFunc::SimpleColor<ColorRGBA<T>>( color ), strokeType, blendFunc );
	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawStrokeFunctor( const Point & point, const ImageT<T> & image, float width, ColorFunc & colorFunc, StrokeType strokeType, const BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;
		switch ( getFormat() ) {
			case Format::R:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorR<T>, ColorR<T>>( point, image, width, colorFunc, strokeType, blendFunc );
						case Format::RGB:			//Blend RGB -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorR<T>, ColorRGB<T>>( point, image, width, colorFunc, strokeType, blendFunc );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorR<T>, ColorRGBA<T>>( point, image, width, colorFunc, strokeType, blendFunc );
					}
					break;
				}
			case Format::RGB:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorRGB<T>, ColorR<T>>( point, image, width, colorFunc, strokeType, blendFunc );
						case Format::RGB:			//Blend RGB -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGB<T>>( point, image, width, colorFunc, strokeType, blendFunc );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGBA<T>>( point, image, width, colorFunc, strokeType, blendFunc );
					}
					break;
				}
			case Format::RGBA:
				{
					switch ( image.getFormat() ) {
						case Format::R: 			//Blend R -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorRGBA<T>, ColorR<T>>( point, image, width, colorFunc, strokeType, blendFunc );
						case Format::RGB:			//Blend RGB -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGB<T>>( point, image, width, colorFunc, strokeType, blendFunc );
						case Format::RGBA:		//Blend RGBA -> R
							return _drawStroke<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGBA<T>>( point, image, width, colorFunc, strokeType, blendFunc );
					}
					break;
				}
		}
	}



	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1, typename C2>
	void ImageT<T>::_drawStroke( const Point & point, const ImageT<T> & image, float thickness, ColorFunc & colorFunc, StrokeType strokeType, const BlendFunc & blendFunc ) {


		constexpr size_t N1 = sizeof( C1 ) / sizeof( T );
		constexpr size_t N2 = sizeof( C2 ) / sizeof( T );
		typedef int DistanceType;



		constexpr struct DistanceUtil {
			static constexpr DistanceType div( const T & x ) {
				return ( x >> ( Color<T>::getMaxNbBits() - 3 ) );
			}
			static constexpr DistanceType div( const Float & x ) {
				return x / ( Color<T>::getMax() / T( DistanceUtil::getMult() ) );
			}
			static constexpr float getMult() {
				return _getMult( static_cast< T * >( 0 ) );
			};
			static constexpr float _getMult( T * ) {
				return float( Color<T>::getMax() ) / float( 1 << ( Color<T>::getMaxNbBits() - 3 ) );
			}
			static constexpr float _getMult( Float * ) {
				return float( 5 );
			}
		};



		static const ColorR<DistanceType> maxValue( Utility::TypesInfos<DistanceType>::getMax() - ( 3 * DistanceType( DistanceUtil::getMult() * float( 3.0 ) ) ) );


		struct ThresholdingOutside {
			ThresholdingOutside( const T & threshold, const ColorR<DistanceType> & trueColor, const ColorR<DistanceType> & falseColor ) : trueColor( trueColor ), falseColor( falseColor ), threshold( threshold ) {}
			inline void operator()( ColorR<DistanceType> & out, const ColorR<T> & in ) {
				if ( in.r > threshold )		BlendingFunc::None::blendColor( out, this -> trueColor - DistanceUtil::div( in.r ) + DistanceType( DistanceUtil::getMult() ) );
				else					BlendingFunc::None::blendColor( out, this -> falseColor );
			};
			inline void operator()( ColorR<DistanceType> & out, const ColorRGB<T> & in ) {
				if ( in.r > threshold )		BlendingFunc::None::blendColor( out, this -> trueColor - DistanceUtil::div( in.r ) + DistanceType( DistanceUtil::getMult() ) );
				else					BlendingFunc::None::blendColor( out, this -> falseColor );
			}
			inline void operator()( ColorR<DistanceType> & out, const ColorRGBA<T> & in ) {
				if ( in.a > threshold )		BlendingFunc::None::blendColor( out, this -> trueColor - DistanceUtil::div( in.a ) + DistanceType( DistanceUtil::getMult() ) );
				else					BlendingFunc::None::blendColor( out, this -> falseColor );
			}
			T threshold;
			ColorR<DistanceType> trueColor;
			ColorR<DistanceType> falseColor;
		};

		struct ThresholdingInside {
			ThresholdingInside( const T & threshold, const ColorR<DistanceType> & trueColor, const ColorR<DistanceType> & falseColor ) : trueColor( trueColor ), falseColor( falseColor ), threshold( threshold ) {}
			inline void operator()( ColorR<DistanceType> & out, const ColorR<T> & in ) {
				if ( in.r < threshold )		BlendingFunc::None::blendColor( out, this -> trueColor - DistanceUtil::div( in.r ) );
				else					BlendingFunc::None::blendColor( out, this -> falseColor );
			};
			inline void operator()( ColorR<DistanceType> & out, const ColorRGB<T> & in ) {
				if ( in.r < threshold )		BlendingFunc::None::blendColor( out, this -> trueColor - DistanceUtil::div( in.r ) );
				else					BlendingFunc::None::blendColor( out, this -> falseColor );
			}
			inline void operator()( ColorR<DistanceType> & out, const ColorRGBA<T> & in ) {
				if ( in.a < threshold )		BlendingFunc::None::blendColor( out, this -> trueColor - DistanceUtil::div( in.a ) );
				else					BlendingFunc::None::blendColor( out, this -> falseColor );
			}
			T threshold;
			ColorR<DistanceType> trueColor;
			ColorR<DistanceType> falseColor;
		};

		struct Champfer {


			Champfer( unsigned int offset ) :
				offset( offset ) {
			}
			inline void operator()( ColorR<DistanceType> * it22 ) {
				static constexpr DistanceType d5( DistanceType( 1.0 * DistanceUtil::getMult() ) );
				static constexpr DistanceType d7( DistanceType( 1.41421356237 * DistanceUtil::getMult() ) );
				static constexpr DistanceType d10( DistanceType( 2.0 * DistanceUtil::getMult() ) );
				static constexpr DistanceType d11( DistanceType( 2.2360679775 * DistanceUtil::getMult() ) );
				static constexpr DistanceType d14( DistanceType( 2.82842712475 * DistanceUtil::getMult() ) );
				/*static DistanceType filter[5][5] = {
				{ d14, d11, d10, d11, d14 },
				{ d11, d7, d5, d7, d11 },
				{ d10, d5, 0, d5, d10 },
				{ d11, d7, d5, d7, d11 },
				{ d14, d11, d10, d11, d14 } };

				auto it00 = it22 - offset * 2 - 2;
				auto yMax = it22 + offset * 2;
				auto ity = it00;
				for ( unsigned int y(0) ; y < 5; y ++ ) {

					auto itx = ity;
					for ( unsigned int x(0); x < 5; x++ ) {
						DistanceType t( *itx + filter[x][y] );
						if ( *( it22 ) > t ) *( it22 ) = t;
						itx++;
					}

					ity += offset;
				}

				return;*/



				DistanceType & v( ( *it22 ).r );

				//if ( v < d5 ) return;

				DistanceType t;
				auto it12 = it22 - offset;
				auto it32 = it22 + offset;


				t = it12[0].r + d5;
				if ( v > t ) v = t;
				t = it22[-1].r + d5;
				if ( v > t ) v = t;
				t = it22[1].r + d5;
				if ( v > t ) v = t;
				t = it32[0].r + d5;
				if ( v > t ) v = t;

				//if ( v < d7 ) return;

				auto it11 = it12 - 1;
				auto it31 = it32 - 1;



				t = it11[0].r + d7;
				if ( v > t ) v = t;
				t = it12[1].r + d7;
				if ( v > t ) v = t;
				t = it31[0].r + d7;
				if ( v > t ) v = t;
				t = it32[1].r + d7;
				if ( v > t ) v = t;

				//if ( v < d10 ) return;

				auto it01 = it11 - offset;
				auto it41 = it31 + offset;

				t = it01[1].r + d10;
				if ( v > t ) v = t;
				t = it41[1].r + d10;
				if ( v > t ) v = t;
				t = it22[-2].r + d10;
				if ( v > t ) v = t;
				t = it22[2].r + d10;
				if ( v > t ) v = t;

				//if ( v < d11 ) return;

				t = it01[0].r + d11;
				if ( v > t ) v = t;
				t = it01[2].r + d11;
				if ( v > t ) v = t;
				t = it41[0].r + d11;
				if ( v > t ) v = t;
				t = it41[2].r + d11;
				if ( v > t ) v = t;

				t = it11[-1].r + d11;
				if ( v > t ) v = t;
				t = it31[-1].r + d11;
				if ( v > t ) v = t;
				t = it32[2].r + d11;
				if ( v > t ) v = t;
				t = it12[2].r + d11;
				if ( v > t ) v = t;

			}
			unsigned int offset;
		};

		ColorR<DistanceType> minValue( Color<T>::getMin() );

		ThresholdingOutside thresholdingOutside( T( 0 ), minValue, maxValue );
		ThresholdingInside thresholdingInside( Color<T>::getMax(), minValue, maxValue );



		constexpr size_t borderSize1 = 2;
		size_t borderSize2 = Math::max<size_t>( borderSize1, Math::ceil( thickness ) );
		size_t borderSize = borderSize1 + borderSize2;

		ImageT<DistanceType> imageOutside( Math::Vec2<Size>( image.getSize().x + borderSize * 2, image.getSize().y + borderSize * 2 ), Format::R );
		ImageT<DistanceType> imageInside( imageOutside.getSize(), Format::R );


		unsigned int imageOutInOffset = imageOutside.getSize().x;
		Champfer champfer( imageOutInOffset );

		//drawing the background color 
		imageOutside.fillImage( maxValue, Rectangle( 0, borderSize, borderSize, imageOutside.getSize().y - borderSize ) );
		imageOutside.fillImage( maxValue, Rectangle( imageOutside.getSize().x - borderSize, borderSize, imageOutside.getSize().x, imageOutside.getSize().y - borderSize ) );

		imageOutside.fillImage( maxValue, Rectangle( 0, 0, imageOutside.getSize().x, borderSize ) );
		imageOutside.fillImage( maxValue, Rectangle( 0, imageOutside.getSize().y - borderSize, imageOutside.getSize().x, imageOutside.getSize().y ) );

		if ( strokeType == StrokeType::Inside || strokeType == StrokeType::Middle ) {
			imageInside.fillImage( minValue, Rectangle( 0, borderSize, borderSize, imageInside.getSize().y - borderSize ) );
			imageInside.fillImage( minValue, Rectangle( imageInside.getSize().x - borderSize, borderSize, imageInside.getSize().x, imageInside.getSize().y - borderSize ) );

			imageInside.fillImage( minValue, Rectangle( 0, 0, imageInside.getSize().x, borderSize ) );
			imageInside.fillImage( minValue, Rectangle( 0, imageInside.getSize().y - borderSize, imageInside.getSize().x, imageInside.getSize().y ) );
		}




		unsigned int imageOffset = image.getSize().x;


		auto imageIt = image.getDatas<C2>();
		auto imageEndIt = imageIt + image.getNbPixels();

		auto imageOutsideIt = imageOutside.getDatas<ColorR<DistanceType>>( borderSize, borderSize );
		auto imageInsideIt = imageInside.getDatas<ColorR<DistanceType>>( borderSize, borderSize );

		while ( imageIt < imageEndIt ) {
			auto imageIt2 = imageIt;
			auto imageOutsideIt2 = imageOutsideIt;
			auto imageInsideIt2 = imageInsideIt;
			auto imageEndIt2 = imageIt + imageOffset;
			while ( imageIt2 < imageEndIt2 ) {

				thresholdingOutside( *imageOutsideIt2, *imageIt2 );
				thresholdingInside( *imageInsideIt2, *imageIt2 );

				imageOutsideIt2++;
				imageInsideIt2++;

				imageIt2++;
			}

			imageOutsideIt += imageOutInOffset;
			imageInsideIt += imageOutInOffset;

			imageIt += imageOffset;
		}


		//At this stage we have an unsigned char R image with 0 representing this object to stroke and 255 the other pixels. 
		//Now lets compute the distance with the Champfer 5-7-11 kernel
		//00[   ] 01[+11] 02[  ] 03[+11] 04[   ]			
		//10[+11] 11[ +7] 12[+5] 13[ +7] 14[+11]			
		//20[   ] 21[ +5] 22[+0] 23[ +5] 24[   ]			
		//30[+11] 31[ +7] 32[+5] 33[ +7] 34[+11]			
		//40[   ] 41[+11] 42[  ] 43[+11] 44[   ]			

		//Clamp the width with the maximum number of iterations we can handle
		thickness = Math::min<float>( thickness, 20.0f );


		auto imageOutInRow = ( image.getSize().x + borderSize2 * 2 );



		size_t numIterationsOutside;
		size_t numIterationsInside;

		switch ( strokeType ) {
			case StrokeType::Outside:
				numIterationsOutside = ( size_t( thickness ) + 2 ) / 2;
				numIterationsInside = 0;
				break;
			case StrokeType::Inside:
				numIterationsOutside = 0;
				numIterationsInside = ( size_t( thickness ) + 2 ) / 2;
				break;
			case StrokeType::Middle:
				numIterationsOutside = ( size_t( thickness ) + 4 ) / 4;
				numIterationsInside = numIterationsOutside;

				thickness *= float( 0.5 );

				break;
		}


		if ( numIterationsOutside ) {
			auto imageOutsideBeginIt = imageOutside.getDatas<ColorR<DistanceType>>( borderSize1, borderSize1 );
			auto imageOutsideEndIt = imageOutside.getDatas<ColorR<DistanceType>>( 0, imageOutside.getSize().y - borderSize1 );

			for ( size_t i = 0; i < numIterationsOutside; i++ ) {
				imageOutsideIt = imageOutsideBeginIt;
				while ( imageOutsideIt < imageOutsideEndIt ) {
					auto imageOutsideEndIt2 = imageOutsideIt + imageOutInRow;
					auto imageOutsideIt2 = imageOutsideIt;
					while ( imageOutsideIt2 < imageOutsideEndIt2 ) {
						champfer( imageOutsideIt2 );
						imageOutsideIt2++;
					}
					imageOutsideIt += imageOutInOffset;
				}
			}
		}
		if ( numIterationsInside ) {
			auto imageInsideBeginIt = imageInside.getDatas<ColorR<DistanceType>>( borderSize1, borderSize1 );
			auto imageInsideEndIt = imageInside.getDatas<ColorR<DistanceType>>( 0, imageInside.getSize().y - borderSize1 );

			for ( size_t i = 0; i < numIterationsInside; i++ ) {
				imageInsideIt = imageInsideBeginIt;
				while ( imageInsideIt < imageInsideEndIt ) {
					auto imageInsideEndIt2 = imageInsideIt + imageOutInRow;
					auto imageInsideIt2 = imageInsideIt;
					while ( imageInsideIt2 < imageInsideEndIt2 ) {
						champfer( imageInsideIt2 );
						imageInsideIt2++;
					}
					imageInsideIt += imageOutInOffset;
				}
			}
		}



		//distance is now computed, now draw the result

		Math::Vec2<Size> thisBegin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<Size> otherImageBegin;
		Point size;
		Rectangle rectangle( point.x - borderSize2, point.y - borderSize2, point.x + image.getSize().x + borderSize2, point.y + image.getSize().y + borderSize2 );


		if ( rectangle.getLeft() < 0 ) {
			thisBegin.x = 0;
			otherImageBegin.x = -rectangle.getLeft();
			size.x = Math::min<typename Point::Type>( getSize().x, rectangle.getRight() );
		} else {
			thisBegin.x = rectangle.getLeft();
			otherImageBegin.x = 0;
			size.x = Math::min<typename Point::Type>( getSize().x - rectangle.getLeft(), rectangle.getRight() - rectangle.getLeft() );
		}

		if ( rectangle.getBottom() < 0 ) {
			thisBegin.y = 0;
			otherImageBegin.y = -rectangle.getBottom();
			size.y = Math::min<typename Point::Type>( getSize().y, rectangle.getTop() );
		} else {
			thisBegin.y = rectangle.getBottom();
			otherImageBegin.y = 0;
			size.y = Math::min<typename Point::Type>( getSize().y - rectangle.getBottom(), rectangle.getTop() - rectangle.getBottom() );
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		Math::Rectangle<Size> rectangleClamped( thisBegin.x, thisBegin.y, thisBegin.x + size.x, thisBegin.y + size.y );
		colorFunc.init( rectangleClamped );

		Math::Vec2<Size> rectangleSize( rectangleClamped.getRight() - rectangleClamped.getLeft(), rectangleClamped.getTop() - rectangleClamped.getBottom() );

		auto thisIt = getDatas<C1>( thisBegin.x, thisBegin.y );
		unsigned int thisImageOffset = this -> size.x;

		imageOutsideIt = imageOutside.getDatas<ColorR<DistanceType>>( otherImageBegin.x + borderSize1, otherImageBegin.y + borderSize1 );
		imageInsideIt = imageInside.getDatas<ColorR<DistanceType>>( otherImageBegin.x + borderSize1, otherImageBegin.y + borderSize1 );

		Math::Vec2<Size> i;
		float thicknessPlus1( thickness + float( 1 ) );
		DistanceType thicknessScaled = DistanceType( thickness * DistanceUtil::getMult() );
		DistanceType thicknessScaledNext = DistanceType( ( thicknessPlus1 ) * DistanceUtil::getMult() );

		for ( i.y = 0; i.y < rectangleSize.y; i.y++ ) {
			auto thisIt2 = thisIt;
			auto imageOutsideIt2 = imageOutsideIt;
			auto imageInsideIt2 = imageInsideIt;

			for ( i.x = 0; i.x < rectangleSize.x; i.x++ ) {
				const ColorR<DistanceType> & r1 = *imageOutsideIt2;
				const ColorR<DistanceType> & r2 = *imageInsideIt2;
				DistanceType r = Math::max<DistanceType>( r1.r, r2.r );

				if ( r <= thicknessScaled ) {
					blendFunc( *( ( C1 * ) thisIt2 ), colorFunc( i ) );
				} else if ( r < thicknessScaledNext ) {			//anti aliasing here
					float alpha = ( thicknessPlus1 - ( float( r ) * float( 1.0f / DistanceUtil::getMult() ) ) );
					//T alpha = T( thicknessScaledNext - r );
					blendFunc( *( ( C1 * ) thisIt2 ), colorFunc( i ), alpha );
				}

				thisIt2++;
				imageOutsideIt2++;
				imageInsideIt2++;
			}
			thisIt += thisImageOffset;
			imageOutsideIt += imageOutInOffset;
			imageInsideIt += imageOutInOffset;

		}
	}


	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorR<T> & color, const BlendFunc & blendFunc ) {
		switch ( getFormat() ) {
			case Format::R:
				return _drawBezierCurve<BlendFunc, ColorR<T>, ColorR<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
			case Format::RGB:
				return _drawBezierCurve<BlendFunc, ColorRGB<T>, ColorR<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
			case Format::RGBA:
				return _drawBezierCurve<BlendFunc, ColorRGBA<T>, ColorR<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
		}
	}


	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorRGB<T> & color, const BlendFunc & blendFunc ) {
		switch ( getFormat() ) {
			case Format::R:
				return _drawBezierCurve<BlendFunc, ColorR<T>, ColorRGB<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
			case Format::RGB:
				return _drawBezierCurve<BlendFunc, ColorRGB<T>, ColorRGB<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
			case Format::RGBA:
				return _drawBezierCurve<BlendFunc, ColorRGBA<T>, ColorRGB<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
		}
	}


	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorRGBA<T> & color, const BlendFunc & blendFunc ) {
		switch ( getFormat() ) {
			case Format::R:
				return _drawBezierCurve<BlendFunc, ColorR<T>, ColorRGBA<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
			case Format::RGB:
				return _drawBezierCurve<BlendFunc, ColorRGB<T>, ColorRGBA<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
			case Format::RGBA:
				return _drawBezierCurve<BlendFunc, ColorRGBA<T>, ColorRGBA<T>>( p0, p1, p2, p3, thickness, color, blendFunc );
		}
	}


	template<typename T>
	template<typename BlendFunc, typename C1, typename C2>
	void ImageT<T>::_drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, const C2 & color, const BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;
		unsigned int numberPoints = 50;


		Math::Vec2<float> p( p0 );
		Math::Vec2<float> p_;
		float t = 0;
		float tIncr = 1.0f / float( numberPoints - 1 );
		for ( unsigned int i = 0; i < numberPoints; i++ ) {

			float oneMinusT = 1.0f - t;
			float oneMinusTSquare = oneMinusT * oneMinusT;
			float tSquare = t * t;

			float p0Factor = oneMinusTSquare * oneMinusT;
			float p1Factor = 3.0f * oneMinusTSquare * t;
			float p2Factor = 3.0f * oneMinusT * tSquare;
			float p3Factor = tSquare * t;

			p_.x = p0.x * p0Factor + p1.x * p1Factor + p2.x * p2Factor + p3.x * p3Factor;
			p_.y = p0.y * p0Factor + p1.y * p1Factor + p2.y * p2Factor + p3.y * p3Factor;

			drawLineFunctor( Math::Line<float>( p, p_ ), ColorFunc::SimpleColor<C2>( color ), thickness, blendFunc );
			p = p_;
			t += tIncr;
		}
	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawGraphValuesFunctor( const Vector<Math::Vec2<float>> & values, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;

		switch ( getFormat() ) {
			case Format::R:
				return _drawGraphValuesFunctor<ColorFunc, BlendFunc, ColorR<T>>( values, rectangle, colorFunc, blendFunc );
			case Format::RGB:
				return _drawGraphValuesFunctor<ColorFunc, BlendFunc, ColorRGB<T>>( values, rectangle, colorFunc, blendFunc );
			case Format::RGBA:
				return _drawGraphValuesFunctor<ColorFunc, BlendFunc, ColorRGBA<T>>( values, rectangle, colorFunc, blendFunc );
		}
	}

	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawGraphValuesFunctor( const Vector<Math::Vec2<float>> & values, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		warn( "Deprecated function" );
		return;
		if ( values.getSize() <= 2 ) {
			return;
		}


		Math::Rectangle<Size> clampedRectangle = clampRectangle( rectangle );
		Math::Vec2<Size> size = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();


		colorFunc.init( clampedRectangle );



		Vector<Math::Vec2<float>> tangents;
		tangents.reserve( values.getSize() );



		//Compute the first tangent
		tangents[0] = ( ( values[1] - values[0] ) ) * 0.3f;

		//Compute the last tangent
		auto lastIndex = values.getSize() - 1;
		tangents[lastIndex] = ( values[lastIndex - 1] - values[lastIndex] ) * 0.3f;

		//Compute the others tangents
		for ( size_t i = 1; i < lastIndex; i++ ) {
			const Math::Vec2<float> & p0 = values[i - 1];
			const Math::Vec2<float> & p1 = values[i];
			const Math::Vec2<float> & p2 = values[i + 1];

			tangents[i] = ( ( p2 - p0 ) ) * 0.3f;
		}


		Math::Vec2<float> & p0 = const_cast< Math::Vec2<float> & >( values[0] );
		Math::Vec2<float> & m0 = tangents[0];

		//lets draw this !
		for ( size_t i = 1; i < values.getSize(); i++ ) {
			Math::Vec2<float> & p1 = const_cast< Math::Vec2<float> & >( values[i] );
			Math::Vec2<float> & m1 = tangents[i];


			LineF lineClamped( p0, p1 );
			Math::clamp( &lineClamped, Math::Rectangle<float>( 0, 0, 1, 1 ) );
			p0 = lineClamped.getP0();
			p1 = lineClamped.getP1();


			//for each pixel
			Math::Vec2<Size> j;
			PointF p, p_;
			p_.x = float( int( p0.x * float( size.x ) + float( clampedRectangle.getLeft() ) ) );
			p_.y = p0.y * float( size.y ) + float( clampedRectangle.getBottom() );

			auto pixelBeginX = int( p_.x );
			auto pixelEndX = int( p1.x * float( size.x ) + float( clampedRectangle.getLeft() ) );
			auto numPixelstoDraw = pixelEndX - pixelBeginX;
			float tIncr = 1.0f / ( float( numPixelstoDraw ) );
			float t = tIncr;


			j.x = pixelBeginX;

			for ( size_t k = 0; k < numPixelstoDraw; k++ ) {
				j.x++;

				float t2 = t * t;
				float t3 = t2 * t;

				//Compute the Hermite factors 
				float p0Factor = 2.0f * t3 - 3.0f * t2 + 1.0f;
				float m0Factor = t3 - 2.0f * t2 + t;

				float p1Factor = -2.0f * t3 + 3.0f * t2;
				float m1Factor = t3 - t2;

				float y = p0.y * p0Factor + m0.y * m0Factor + p1.y * p1Factor + m1.y * m1Factor;


				p.x = j.x;
				p.y = y * float( size.y ) + float( clampedRectangle.getBottom() );


				LineF line( p_, p );

				//drawLine(line, ColorR<unsigned char>(0), 2);
				_drawLineFunctorFilledBottom<ColorFunc, BlendFunc, C1>( line, colorFunc, clampedRectangle, blendFunc );

				t += tIncr;
				p_ = p;
			}

			p0 = p1;
			m0 = m1;


		}

	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorR<T> & color, BlendFunc & blendFunc ) {
		return drawRectangleRoundedFunctor<ColorFunc::SimpleColor<Graphic::ColorR<T>>, BlendFunc>( rectangle, radius, ColorFunc::SimpleColor<Graphic::ColorR<T>>( color ), blendFunc );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorRGB<T> & color, BlendFunc & blendFunc ) {
		return drawRectangleRoundedFunctor<ColorFunc::SimpleColor<Graphic::ColorRGB<T>>, BlendFunc>( rectangle, radius, ColorFunc::SimpleColor<Graphic::ColorRGB<T>>( color ), blendFunc );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorRGBA<T> & color, BlendFunc & blendFunc ) {
		return drawRectangleRoundedFunctor<ColorFunc::SimpleColor<Graphic::ColorRGBA<T>>, BlendFunc>( rectangle, radius, ColorFunc::SimpleColor<Graphic::ColorRGBA<T>>( color ), blendFunc );
	}

	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawRectangleRoundedFunctor( const Rectangle & rectangle, unsigned int radius, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;
		switch ( getFormat() ) {
			case Format::R:
				return _drawRectangleRoundedFunctor<ColorFunc, BlendFunc, ColorR<T>>( rectangle, radius, colorFunc, blendFunc );
			case Format::RGB:
				return _drawRectangleRoundedFunctor<ColorFunc, BlendFunc, ColorRGB<T>>( rectangle, radius, colorFunc, blendFunc );
			case Format::RGBA:
				return _drawRectangleRoundedFunctor<ColorFunc, BlendFunc, ColorRGBA<T>>( rectangle, radius, colorFunc, blendFunc );
		}
	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawRectangleRoundedFunctor( const Rectangle & rectangle, unsigned int radiusi, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		auto clampedRectangle = clampRectangle( rectangle );
		Math::Vec2<Size> size = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();


		colorFunc.init( clampedRectangle );

		radiusi = Math::min<unsigned int>( radiusi, size.x / 2 );
		radiusi = Math::min<unsigned int>( radiusi, size.y / 2 );


		Math::Vec2<Size> i;
		Math::Vec2<Size> p( 0, radiusi );



		Float radius2 = Float( radiusi * radiusi ) - Float( 0.01 );


		Math::Vec2<Size> rightTopOffset( size.x - radiusi, size.y - radiusi );
		Math::Vec2<Size> leftTopOffset( radiusi - 1, size.y - radiusi );
		Math::Vec2<Size> leftBottomOffset( radiusi - 1, radiusi - 1 );
		Math::Vec2<Size> rightBottomOffset( size.x - radiusi, radiusi - 1 );

		auto p0it = ( ( C1* ) ( this -> buffer ) ) + clampedRectangle.getBottom() * this -> size.x + clampedRectangle.getLeft();









		auto xMid = ( size.x ) / 2;

		auto lastY = p.y;

		for ( ; p.x < p.y; p.x++ ) {
			Float x2( p.x * p.x );
			Float intery( Math::sqrt( radius2 - x2 ) );
			p.y = int( intery );
			Float interyFPart( intery - Float( p.y ) );



			{		//Octane 1
				Math::Vec2<Size> i( p + rightTopOffset );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );

				if ( p.y != lastY ) {
					while ( i.x > xMid ) {
						it--;
						i.x--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
					}
				}
			}
			{	//Octane 7
				Math::Vec2<Size> i( leftTopOffset.x - p.y, leftTopOffset.y + p.x );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );

				it++;
				i.x++;
				while ( i.x < xMid ) {


					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ) );
					it++;
					i.x++;
				}

			}
			{	//Octane 3
				Math::Vec2<Size> i( rightBottomOffset.x + p.y, rightBottomOffset.y - p.x );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );


				while ( i.x > xMid ) {
					it--;
					i.x--;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ) );
				}

			}
			{		//Octane 5
				Math::Vec2<Size> i( leftBottomOffset.x - p.x, leftBottomOffset.y - p.y );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );



				if ( p.y != lastY ) {
					it++;
					i.x++;
					while ( i.x < xMid ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
						it++;
						i.x++;
					}
				}
			}


			if ( p.y != p.x ) {
				{	//Octane 2
					Math::Vec2<Size> i( p.y + rightTopOffset.y, p.x + rightTopOffset.x );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );

					while ( i.x > xMid ) {

						it--;
						i.x--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
					}

				}
				{		//Octane 8
					Math::Vec2<Size> i( leftTopOffset.x - p.x, leftTopOffset.y + p.y );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );



					if ( p.y != lastY ) {
						it++;
						i.x++;
						while ( i.x < xMid ) {
							assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
							blendFunc( *( it ), colorFunc( i ) );
							it++;
							i.x++;
						}
					}
				}
				{	//Octane 4
					Math::Vec2<Size> i( rightBottomOffset.x + p.x, rightBottomOffset.y - p.y );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );



					if ( p.y != lastY ) {

						while ( i.x > xMid ) {
							it--;
							i.x--;
							assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
							blendFunc( *( it ), colorFunc( i ) );

						}
					}
				}
				{	//Octane 6
					Math::Vec2<Size> i( leftBottomOffset.x - p.y, leftBottomOffset.y - p.x );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );

					it++;
					i.x++;
					while ( i.x < xMid ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
						it++;
						i.x++;
					}

				}
			}




			lastY = p.y;
		}


		//draw the inside rectangle
		p0it += radiusi * this -> size.x;
		for ( i.y = radiusi; i.y < rightTopOffset.y; i.y++ ) {
			auto p1it = p0it;
			for ( i.x = 0; i.x < size.x; i.x++ ) {

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *p1it, colorFunc( i ) );

				p1it++;
			}

			p0it += this -> size.x;
		}


	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void Graphic::ImageT<T>::drawDisk( const Point & point, float radius, ColorR<T> & c, BlendFunc & blendFunc ) {
		return drawDiskFunctor<ColorFunc::SimpleColor<ColorR<T>>, BlendFunc>( point, radius, ColorFunc::SimpleColor<ColorR<T>>( c ), blendFunc );
	}

	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void Graphic::ImageT<T>::drawDisk( const Point & point, float radius, ColorRGB<T> & c, BlendFunc & blendFunc ) {
		return drawDiskFunctor<ColorFunc::SimpleColor<ColorRGB<T>>, BlendFunc>( point, radius, ColorFunc::SimpleColor<ColorRGB<T>>( c ), blendFunc );
	}

	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void Graphic::ImageT<T>::drawDisk( const Point & point, float radius, ColorRGBA<T> & c, BlendFunc & blendFunc ) {
		return drawDiskFunctor<ColorFunc::SimpleColor<ColorRGBAT>>, BlendFunc > ( point, radius, ColorFunc::SimpleColor<ColorRGBA<T>>( c ), blendFunc );
	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawDiskFunctor( const Point & point, float radius, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;
		switch ( getFormat() ) {
			case Format::R:
				return _drawDiskFunctor<ColorFunc, BlendFunc, ColorR<T>>( point, radius, colorFunc, blendFunc );
			case Format::RGB:
				return _drawDiskFunctor<ColorFunc, BlendFunc, ColorRGB<T>>( point, radius, colorFunc, blendFunc );
			case Format::RGBA:
				return _drawDiskFunctor<ColorFunc, BlendFunc, ColorRGBA<T>>( point, radius, colorFunc, blendFunc );
		}
	}




	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawDiskFunctor( const Point & point, float radius, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		radius = Math::min<float>( radius, this -> size.x / 2 );
		radius = Math::min<float>( radius, this -> size.y / 2 );

		int radiusi = int( radius + 0.5f );

		Point pointClamped( point );
		Math::clamp( &pointClamped, Math::Rectangle<typename Point::Type>( radiusi, radiusi, this -> size.x - radiusi, this -> size.y - radiusi ) );

		Math::Rectangle<Size> rectangleClamped( pointClamped.x - radiusi, pointClamped.y - radiusi, pointClamped.x + radiusi, pointClamped.y + radiusi );
		auto size = rectangleClamped.getRightTop() - rectangleClamped.getLeftBottom();


		Math::Vec2<Size> i;
		Math::Vec2<Size> p( 0, radiusi );


		float radius2 = float( radius * radius ) - 0.01f;
		auto p0it = ( ( C1* ) ( this -> buffer ) ) + rectangleClamped.getBottom() * this -> size.x + rectangleClamped.getLeft();


		Math::Vec2<Size> rightTopOffset( radiusi, radiusi );
		Math::Vec2<Size> leftTopOffset( radiusi - 1, radiusi );
		Math::Vec2<Size> leftBottomOffset( radiusi - 1, radiusi - 1 );
		Math::Vec2<Size> rightBottomOffset( radiusi, radiusi - 1 );

		auto lastY = p.y;
		auto xMid = ( size.x ) / 2;

		for ( ; p.x < p.y; p.x++ ) {
			Float x2( p.x * p.x );
			Float intery( Math::sqrt( radius2 - x2 ) );
			p.y = int( intery );
			Float interyFPart( intery - Float( p.y ) );



			{		//Octane 1
				Math::Vec2<Size> i( p + rightTopOffset );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );

				if ( p.y != lastY ) {
					while ( i.x > xMid ) {
						it--;
						i.x--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
					}
				}
			}
			{	//Octane 7
				Math::Vec2<Size> i( leftTopOffset.x - p.y, leftTopOffset.y + p.x );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );

				it++;
				i.x++;
				while ( i.x < xMid ) {


					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ) );
					it++;
					i.x++;
				}

			}
			{	//Octane 3
				Math::Vec2<Size> i( rightBottomOffset.x + p.y, rightBottomOffset.y - p.x );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );


				while ( i.x > xMid ) {
					it--;
					i.x--;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ) );
				}

			}
			{		//Octane 5
				Math::Vec2<Size> i( leftBottomOffset.x - p.x, leftBottomOffset.y - p.y );
				auto it = p0it + i.y * this -> size.x + i.x;

				assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
				blendFunc( *( it ), colorFunc( i ), interyFPart );



				if ( p.y != lastY ) {
					it++;
					i.x++;
					while ( i.x < xMid ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
						it++;
						i.x++;
					}
				}
			}


			if ( p.y != p.x ) {
				{	//Octane 2
					Math::Vec2<Size> i( p.y + rightTopOffset.y, p.x + rightTopOffset.x );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );

					while ( i.x > xMid ) {

						it--;
						i.x--;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
					}

				}
				{		//Octane 8
					Math::Vec2<Size> i( leftTopOffset.x - p.x, leftTopOffset.y + p.y );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );



					if ( p.y != lastY ) {
						it++;
						i.x++;
						while ( i.x < xMid ) {
							assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
							blendFunc( *( it ), colorFunc( i ) );
							it++;
							i.x++;
						}
					}
				}
				{	//Octane 4
					Math::Vec2<Size> i( rightBottomOffset.x + p.x, rightBottomOffset.y - p.y );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );



					if ( p.y != lastY ) {

						while ( i.x > xMid ) {
							it--;
							i.x--;
							assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
							blendFunc( *( it ), colorFunc( i ) );

						}
					}
				}
				{	//Octane 6
					Math::Vec2<Size> i( leftBottomOffset.x - p.y, leftBottomOffset.y - p.x );
					auto it = p0it + i.y * this -> size.x + i.x;

					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *( it ), colorFunc( i ), interyFPart );

					it++;
					i.x++;
					while ( i.x < xMid ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *( it ), colorFunc( i ) );
						it++;
						i.x++;
					}

				}
			}




			lastY = p.y;
		}



	}





	template<typename T>
	ImageT<T> ImageT<T>::resample( const Math::Vec2<Size> & newSize, ResamplingMode resamplingMode ) const {
		if ( getDatas() == NULL ) return *this;
		switch ( getFormat() ) {
			case Format::R:
				return _resample<ColorR<T>, ColorR<typename KernelType>, ColorR<typename Float>, KernelType>( newSize, resamplingMode );
			case Format::RGB:
				return _resample<ColorRGB<T>, ColorRGB<typename KernelType>, ColorRGB<typename Float>, KernelType>( newSize, resamplingMode );
			case Format::RGBA:
				return _resample<ColorRGBA<T>, ColorRGBA<typename KernelType>, ColorRGBA<typename Float>, KernelType>( newSize, resamplingMode );
		}
	}




	template<typename T>
	template<typename C, typename ColorSum, typename ColorFloat, typename SumType>
	ImageT<T> ImageT<T>::_resample( const Math::Vec2<Size> & newSize, ResamplingMode resamplingMode ) const {
		typedef typename Float Float;

		if ( newSize.x == this -> size.x && newSize.y == this -> size.y )
			return *this;


		ImageT<T> newImage( newSize, getFormat() );

		Math::Vec2<float> ratio( float( this -> size.x ) / float( newSize.x ), float( this -> size.y ) / float( newSize.y ) );


		Math::Vec2<bool> isUpscaling( newSize.x > this -> size.x, newSize.y > this -> size.y );


		auto thisImageIt0 = getDatas<C>();
		auto newImageIt0 = newImage.getDatas<C>();




		// Lanczos Upscaling is not supported, switched to linear instead
		if ( isUpscaling.x || isUpscaling.y )
			resamplingMode = ResamplingMode::Bilinear;



		switch ( resamplingMode ) {
			///////////////////////////////////////////
			//// NEAREST
			///////////////////////////////////////////
			case ResamplingMode::Nearest:
				{
					Math::Vec2<float> ratioInverse( float( newSize.x ) / float( this -> size.x ), float( newSize.y ) / float( this -> size.y ) );


					if ( !isUpscaling.x && !isUpscaling.y ) { // If downscaling
						Math::Vec2<Size> i, j;
						Math::Vec2<float> realPosition( 0 );

						for ( i.y = 0; i.y < newSize.y; i.y++ ) {
							auto newImageIt1 = newImageIt0;
							realPosition.x = 0.0f;
							j.y = Size( realPosition.y );
							realPosition.y += ratio.y;

							auto thisImageIt1 = thisImageIt0 + j.y * this -> size.y;

							for ( i.x = 0; i.x < newSize.x; i.x++ ) {
								C & newImagePixel = *newImageIt1;

								j.x = Size( realPosition.x );
								realPosition.x += ratio.x;

								auto thisImageIt2 = thisImageIt1 + j.x;
								const C & thisImagePixel = *thisImageIt2;
								newImagePixel = thisImagePixel;

								newImageIt1++;
							}

							newImageIt0 += newSize.x;
						}
					} else if ( isUpscaling.x && isUpscaling.y ) { // If upscaling

						Math::Vec2<Size> i, k, j0, j1;
						Math::Vec2<float> realPosition( 0 );

						j0.y = Size( 0 );
						for ( i.y = 0; i.y < this -> size.y; i.y++ ) {
							auto thisImageIt1 = thisImageIt0;
							auto newImageIt1 = newImageIt0 + j0.y * newSize.x;
							realPosition.x = 0.0f;
							realPosition.y += ratioInverse.y;
							j1.y = Size( realPosition.y );

							j0.x = Size( 0 );

							for ( i.x = 0; i.x < this -> size.x; i.x++ ) {
								const C & thisImagePixel = *thisImageIt1;

								auto newImageIt2 = newImageIt1 + j0.x;
								realPosition.x += ratioInverse.x;
								j1.x = Size( realPosition.x );

								for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
									auto newImageIt3 = newImageIt2;
									for ( k.x = j0.x; k.x < j1.x; k.x++ ) {

										assert( k.x >= 0 && k.y >= 0 && k.x < newSize.x && k.y < newSize.y );
										C & newImagePixel = *newImageIt3;
										newImagePixel = thisImagePixel;

										newImageIt3++;
									}
									newImageIt2 += newSize.x;
								}
								j0.x = j1.x;
								thisImageIt1++;
							}

							j0.y = j1.y;
							thisImageIt0 += this -> size.x;
						}
					} else if ( !isUpscaling.x && isUpscaling.y ) { //Upscaling Y, Downscaling X
						Math::Vec2<Size> i, k, j0, j1;
						Math::Vec2<float> realPosition( 0 );

						j0.y = Size( 0 );
						for ( i.y = 0; i.y < this -> size.y; i.y++ ) {
							auto thisImageIt1 = thisImageIt0;
							auto newImageIt1 = newImageIt0 + j0.y * newSize.x;
							realPosition.x = 0.0f;
							realPosition.y += ratioInverse.y;
							j1.y = Size( realPosition.y );

							for ( i.x = 0; i.x < newSize.x; i.x++ ) {
								k.x = Size( realPosition.x );
								realPosition.x += ratio.x;

								auto thisImageIt2 = thisImageIt1 + k.x;
								const C & thisImagePixel = *thisImageIt2;

								auto newImageIt2 = newImageIt1;
								for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
									assert( i.x >= 0 && k.y >= 0 && i.x < newSize.x && k.y < newSize.y );
									C & newImagePixel = *newImageIt2;
									newImagePixel = thisImagePixel;

									newImageIt2 += newSize.x;
								}
								newImageIt1++;
							}
							j0.y = j1.y;
							thisImageIt0 += this -> size.x;
						}
					} else if ( isUpscaling.x && !isUpscaling.y ) { //Upscaling X, Downscaling Y
						Math::Vec2<int> i, k, j0, j1;
						Math::Vec2<float> realPosition( 0 );

						for ( i.y = 0; i.y < newSize.y; i.y++ ) {
							j0.y = int( realPosition.y );

							auto thisImageIt1 = thisImageIt0 + j0.y * this -> size.x;
							auto newImageIt1 = newImageIt0 + i.y * newSize.x;

							realPosition.x = 0.0f;
							realPosition.y += ratio.y;

							for ( i.x = 0; i.x < this -> size.x; i.x++ ) {
								const C & thisImagePixel = *thisImageIt1;

								j0.x = int( realPosition.x );
								realPosition.x += ratioInverse.x;
								j1.x = int( realPosition.x );

								auto newImageIt2 = newImageIt1 + j0.x;
								for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
									assert( k.x >= 0 && i.y >= 0 && k.x < newSize.x && i.y < newSize.y );
									C & newImagePixel = *newImageIt2;
									newImagePixel = thisImagePixel;
									newImageIt2++;
								}

								j0.x = j1.x;
								thisImageIt1++;
							}
						}
					}
					break;
				}


				///////////////////////////////////////////
				//// LINEAR
				///////////////////////////////////////////
			case ResamplingMode::Bilinear:
				{
					Math::Vec2<float> ratioInverse( float( newSize.x ) / float( this -> size.x - 1 ), float( newSize.y ) / float( this -> size.y - 1 ) );


					if ( !isUpscaling.x && !isUpscaling.y ) { // If downscaling
						Math::Vec2<int> i, j0, j1, k;
						Math::Vec2<float> realPosition( 0 );

						for ( i.y = 0; i.y < newSize.y; i.y++ ) {
							auto newImageIt1 = newImageIt0;

							j0.y = int( realPosition.y );
							realPosition.y += ratio.y;
							j1.y = int( realPosition.y );

							C * thisImageIt1 = ( ( C * ) ( thisImageIt0 ) ) + j0.y * this -> size.x;

							realPosition.x = 0.0f;

							for ( i.x = 0; i.x < newSize.x; i.x++ ) {
								C & newImagePixel = *newImageIt1;

								j0.x = int( realPosition.x );
								realPosition.x += ratio.x;
								j1.x = int( realPosition.x );

								auto thisImageIt2 = thisImageIt1 + j0.x;

								ColorSum sum( 0 );
								SumType sumFactors = ( j1.x - j0.x ) * ( j1.y - j0.y );
								for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
									auto thisImageIt3 = thisImageIt2;
									for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
										const C & thisImagePixel = *thisImageIt3;
										sum += ColorSum( thisImagePixel );

										thisImageIt3++;
									}
									thisImageIt2 += this -> size.x;
								}

								newImagePixel = ( sum ) / sumFactors;
								newImageIt1++;
							}

							newImageIt0 += newSize.x;
						}
					} else if ( isUpscaling.x && isUpscaling.y ) {  // If Upscaling

						Math::Vec2<int> i, j0, j1, k;
						Math::Vec2<float> realPosition( 0 );
						Math::Vec2<int> kernelSize;


						auto maxX = this -> size.x - 1;
						auto maxY = this -> size.y - 1;

						for ( i.y = 0; i.y < maxY; i.y++ ) {
							auto thisImageIt1 = thisImageIt0;

							j0.y = int( realPosition.y );
							realPosition.y += ratioInverse.y;
							j1.y = int( realPosition.y );

							kernelSize.y = j1.y - j0.y;
							Float yRelativeIncr = Float( 1.0 ) / Float( kernelSize.y );

							auto newImageIt1 = ( ( C * ) ( newImageIt0 ) ) + ( j0.y ) * newSize.x;

							realPosition.x = 0.0f;
							for ( i.x = 0; i.x < maxX; i.x++ ) {
								ColorFloat thisImagePixel00( *( thisImageIt1 ) );

								j0.x = int( realPosition.x );
								realPosition.x += ratioInverse.x;
								j1.x = int( realPosition.x );

								kernelSize.x = j1.x - j0.x;

								auto newImageIt2 = newImageIt1 + ( j0.x );

								if ( kernelSize.x == 1 && kernelSize.y == 1 ) {
									C & newImagePixel = *newImageIt2;

									newImagePixel = C( thisImagePixel00 );
								} else {
									ColorFloat thisImagePixel10( *( thisImageIt1 + 1 ) );
									ColorFloat thisImagePixel01( *( thisImageIt1 + this -> size.x ) );
									ColorFloat thisImagePixel11( *( thisImageIt1 + this -> size.x + 1 ) );

									Float xRelativeIncr = Float( 1.0 ) / Float( kernelSize.x );

									Float yRelative( 0 );

									for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
										auto newImageIt3 = newImageIt2;
										Float yRelativeInverse = Float( 1.0 ) - yRelative;
										ColorFloat avg1( ( thisImagePixel00 ) * yRelativeInverse + ( thisImagePixel01 ) * yRelative );
										ColorFloat avg2( ( thisImagePixel10 ) * yRelativeInverse + ( thisImagePixel11 ) * yRelative );

										Float xRelative( 0 );
										for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
											Float xRelativeInverse = Float( 1.0 ) - xRelative;
											ColorSum avg3( avg1 * xRelativeInverse + avg2 * xRelative );

											C & newImagePixel = *( newImageIt3 );
											newImagePixel = avg3;

											xRelative += xRelativeIncr;
											newImageIt3++;
										}
										yRelative += yRelativeIncr;
										newImageIt2 += newSize.x;
									}
								}
								thisImageIt1++;
							}
							thisImageIt0 += this -> size.x;
						}

					} else if ( !isUpscaling.x && isUpscaling.y ) {  //Upscaling Y, Downscaling X
						Math::Vec2<int> i, j0, j1, k;
						Math::Vec2<float> realPosition( 0, 0 );
						Math::Vec2<int> kernelSize;
						ColorFloat avg;
						ColorFloat * lastAvg = new ColorFloat[newSize.x];

						// First we gonna initialize the lastAvgBuffer with the average on the first line.
						{
							auto lastAvgIt = lastAvg;
							for ( i.x = 0; i.x < newSize.x; i.x++ ) {
								j0.x = int( realPosition.x );
								realPosition.x += ratio.x;
								j1.x = int( realPosition.x );

								auto thisImageIt1 = thisImageIt0 + j0.x;
								ColorSum sum( 0 );
								SumType sumFactors = ( j1.x - j0.x );
								for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
									const C & thisImagePixel = *thisImageIt1;
									sum += ColorSum( thisImagePixel );
									thisImageIt1++;
								}
								*lastAvgIt = ColorFloat( sum / sumFactors );
								lastAvgIt++;
							}
						}

						auto maxY = this -> size.y - 1;
						for ( i.y = 0; i.y < maxY; i.y++ ) {
							thisImageIt0 += this -> size.x;

							auto thisImageIt1 = thisImageIt0;

							j0.y = int( realPosition.y );
							realPosition.x = 0.0f;
							realPosition.y += ratioInverse.y;
							j1.y = int( realPosition.y );

							kernelSize.y = j1.y - j0.y;
							float yRelativeIncr = 1.0f / float( kernelSize.y );

							auto newImageIt1 = ( ( C * ) ( newImageIt0 ) ) + ( j0.y ) * newSize.x;

							auto lastAvgIt = lastAvg;
							for ( i.x = 0; i.x < newSize.x; i.x++ ) {
								j0.x = int( realPosition.x );
								realPosition.x += ratio.x;
								j1.x = int( realPosition.x );

								auto thisImageIt2 = thisImageIt1 + j0.x;


								// Now compute the sum of the downscaling.
								ColorSum sum( 0 );
								SumType sumFactors = ( j1.x - j0.x );
								for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
									const C & thisImagePixel = *thisImageIt2;
									sum += ColorSum( thisImagePixel );
									thisImageIt2++;
								}
								avg = ColorFloat( sum / sumFactors );


								// Now create the gradient of the average we calculated.
								Float yRelative( 0 );
								auto newImageIt2 = newImageIt1;
								for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
									Float yRelativeInverse = Float( 1.0 ) - yRelative;
									C finalAvg( ( *lastAvgIt ) * yRelativeInverse + ( avg ) * yRelative );
									C & newImagePixel = *( newImageIt2 );
									newImagePixel = finalAvg;
									yRelative += yRelativeIncr;
									newImageIt2 += newSize.x;
								}

								*lastAvgIt = avg;
								newImageIt1++;
								lastAvgIt++;
							}
						}
						delete[] lastAvg;



					} else if ( isUpscaling.x && !isUpscaling.y ) {  //Upscaling X, Downscaling Y

						auto thisImageIt0 = getDatas<C>();
						auto newImageIt0 = newImage.getDatas<C>();
						Math::Vec2<int> i, j0, j1, k;
						Math::Vec2<float> realPosition( 0, 0 );
						Math::Vec2<int> kernelSize;
						ColorFloat avg;
						ColorFloat lastAvg;



						auto maxX = this -> size.x - 1;
						for ( i.y = 0; i.y < newSize.y; i.y++ ) {

							auto newImageIt1 = newImageIt0;

							j0.y = int( realPosition.y );
							realPosition.x = 0.0f;
							realPosition.y += ratio.y;
							j1.y = int( realPosition.y );

							auto thisImageIt1 = ( ( C * ) ( thisImageIt0 ) ) + ( j0.y ) * this -> size.x;


							// First we gonna initialize the lastAvgBuffer with the average on the first line.
							{
								auto thisImageIt2 = thisImageIt1;

								ColorSum sum( 0 );
								SumType sumFactors = ( j1.y - j0.y );
								for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
									const C & thisImagePixel = *thisImageIt2;
									sum += ColorSum( thisImagePixel );
									thisImageIt2 += this -> size.x;
								}
								lastAvg = ColorFloat( sum / sumFactors );

							}


							for ( i.x = 0; i.x < maxX; i.x++ ) {
								thisImageIt1++;

								j0.x = int( realPosition.x );
								realPosition.x += ratioInverse.x;
								j1.x = int( realPosition.x );

								auto thisImageIt2 = thisImageIt1;
								// Now compute the sum of the downscaling.
								ColorSum sum( 0 );
								SumType sumFactors = ( j1.y - j0.y );
								for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
									const C & thisImagePixel = *thisImageIt2;
									sum += ColorSum( thisImagePixel );
									thisImageIt2 += this -> size.x;
								}
								avg = ColorFloat( sum / sumFactors );


								// Now create the gradient of the average we calculated.
								kernelSize.x = j1.x - j0.x;
								Float xRelativeIncr = Float( 1.0 ) / Float( kernelSize.x );
								Float xRelative( 0 );
								auto newImageIt2 = newImageIt1 + j0.x;
								for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
									Float xRelativeInverse = 1.0f - xRelative;
									C finalAvg( ( lastAvg ) * xRelativeInverse + ( avg ) * xRelative );
									C & newImagePixel = *( newImageIt2 );
									newImagePixel = finalAvg;
									xRelative += xRelativeIncr;
									newImageIt2++;
								}

								lastAvg = avg;
							}
							newImageIt0 += newSize.x;
						}
					}

					break;
				}

				///////////////////////////////////////////
				//// LANCZOS
				///////////////////////////////////////////
			case ResamplingMode::Lanczos:
				{
					static constexpr Float MIN( Color<Float>::getMin() );
					struct Max {
						ColorR<Float> operator()( const ColorR<Float> & c ) {
							return ColorR<Float>( Math::max( c.r, MIN ) );
						}
						ColorRGB<Float> operator()( const ColorRGB<Float> & c ) {
							return ColorRGB<Float>( Math::max( c.r, MIN ), Math::max( c.g, MIN ), Math::max( c.b, MIN ) );
						}
						ColorRGBA<Float> operator()( const ColorRGBA<Float> & c ) {
							return ColorRGBA<Float>( Math::max( c.r, MIN ), Math::max( c.g, MIN ), Math::max( c.b, MIN ), Math::max( c.a, MIN ) );
						}
					};

					Max maxFunctor;

					Math::Vec2<float> ratioHalf( ratio.x * 0.7f, ratio.y * 0.7f );
					Math::Vec2<Float> distanceDivider( Float( 1.1 ) * Float( 50 ) );




					Math::Vec2<int> kernelSize( ratioHalf.x * 2.0f + 0.5f, ratioHalf.y * 2.0f + 0.5f );



					distanceDivider.x /= Float( ratio.x );
					distanceDivider.y /= Float( ratio.y );


					struct Lanczos {
						Lanczos() {
							constexpr Float A( 3.0f );
							lanczosValues[0] = Float( 1.0 );
							for ( int i = 1; i < 100; i++ ) {
								Float x = Float( i ) / Float( 50 );
								lanczosValues[i] = ( A * Math::sin( Math::pi() * x ) * Math::sin( ( Math::pi() * x ) / A ) ) / ( Math::pi() * Math::pi() * x * x );
							}
						}
						Float operator()( int i ) {
							assert( i >= 0 && i < 100 );
							return lanczosValues[i];
						}

						Float lanczosValues[100];
					};

					static Lanczos lanczosFunc;


					if ( !isUpscaling.x && !isUpscaling.y ) { // If downscaling
						Math::Vec2<int> i, j0, j1, k;
						Math::Vec2<Float> j, j0f;
						Math::Vec2<Float> realPositionInit( ( ratio.x ) / Float( 2.0 ), ( Float( ratio.y ) ) / Float( 2.0 ) );


						KernelFunc::Max kernelFunctor;

						j.y = realPositionInit.y;
						j0f.y = j.y - ratioHalf.y + 0.5f;
						for ( i.y = 0; i.y < newSize.y; i.y++ ) {
							auto newImageIt1 = newImageIt0;

							j0.y = Math::max<int>( int( j0f.y ), int( 0 ) );
							j1.y = Math::min<int>( int( j0.y ) + kernelSize.y, int( this -> size.y ) );

							assert( j1.y <= this -> size.y && j0.y >= 0 );
							if ( true ) {
								auto thisImageIt1 = ( ( C * ) ( thisImageIt0 ) ) + j0.y * this -> size.x;

								j.x = realPositionInit.x;
								j0f.x = j.x - ratioHalf.x + 0.5f;

								for ( i.x = 0; i.x < newSize.x; i.x++ ) {
									C & newImagePixel = *newImageIt1;

									j0.x = Math::max<int>( int( j0f.x ), int( 0 ) );
									j1.x = Math::min<int>( int( j0.x ) + kernelSize.x, int( this -> size.x ) );

									assert( j1.x <= this -> size.x && j1.x >= 0 );
									if ( true ) {
										auto thisImageIt2 = thisImageIt1 + j0.x;

										ColorFloat sum( 0 );
										Float sumFactors( 0 );

										for ( k.y = j0.y; k.y < j1.y; k.y++ ) {
											auto thisImageIt3 = thisImageIt2;

											Float disty = Float( Float( k.y ) - j.y ) * distanceDivider.y;
											Float factorY( lanczosFunc( Math::abs( int( disty ) ) ) );


											for ( k.x = j0.x; k.x < j1.x; k.x++ ) {
												const C & thisImagePixel = *thisImageIt3;

												Float distx = Float( Float( k.x ) - j.x ) * distanceDivider.x;
												Float factorX( lanczosFunc( Math::abs( int( distx ) ) ) );

												Float factor = factorY * factorX;

												sum += ColorFloat( thisImagePixel ) * factor;
												sumFactors += factor;
												thisImageIt3++;
											}
											thisImageIt2 += this -> size.x;
										}
										j.x += ratio.x;
										j0f.x += ratio.x;



										newImagePixel = C( maxFunctor( ColorFloat( sum / sumFactors ) ) );
									}
									newImageIt1++;
								}
							}
							j.y += ratio.y;
							j0f.y += ratio.y;

							newImageIt0 += newSize.x;
						}
					}
					break;
				}
		}
		return newImage;
	}






	template<typename T>
	template<typename ColorFunc, typename BlendFunc>
	void ImageT<T>::drawPolygonFunctor( const Math::Vec2<float> * vertices, typename Vector<Math::Vec2<float>>::Size nbVertices, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		if ( getDatas() == NULL ) return;
		switch ( getFormat() ) {
			case Format::R:
				return _drawPolygonFunctor<ColorFunc, BlendFunc, ColorR<T>>( vertices, nbVertices, rectangle, colorFunc, blendFunc );
			case Format::RGB:
				return _drawPolygonFunctor<ColorFunc, BlendFunc, ColorRGB<T>>( vertices, nbVertices, rectangle, colorFunc, blendFunc );
			case Format::RGBA:
				return _drawPolygonFunctor<ColorFunc, BlendFunc, ColorRGBA<T>>( vertices, nbVertices, rectangle, colorFunc, blendFunc );
		}
	}





	template<typename T>
	template<typename ColorFunc, typename BlendFunc, typename C1>
	void ImageT<T>::_drawPolygonFunctor( const Math::Vec2<float> * vertices, typename Vector<Math::Vec2<float>>::Size nbVertices, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc ) {
		auto clampedRectangle = clampRectangle( rectangle );
		auto size = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();


		struct Vertex {

			Float dx;
			Math::Vec2<Float> v;

		};

		Vertex * absoluteVertices = new Vertex[nbVertices];
		Float * intersectionsDx = new Float[nbVertices];
		Float * intersectionsX = new Float[nbVertices];


		Math::Vec2<Size> sizeMinusOne( size.x - 1, size.y - 1 );

		// Compute the absolute coordinate from the relatives [0;1] and the size of the rectangle.
		Math::Vec2<Float> v0Last = vertices[nbVertices - 1];
		for ( unsigned int i = 0; i < nbVertices; i++ ) {
			Vertex & v1 = absoluteVertices[i];
			const Math::Vec2<float> & v0( vertices[i] );

			v1.v.x = v0.x * size.x;
			v1.v.y = v0.y * size.y;

			Float dx = ( v0.x - v0Last.x );
			Float dy = ( v0.y - v0Last.y );

			v1.dx = dx / dy;

			v0Last = v0;
		}


		C1 * p0it = ( ( C1 * ) this -> buffer ) + clampedRectangle.getBottom() * this -> size.x + clampedRectangle.getLeft();



		// For each line, compute the intersections.
		Math::Vec2<Size> i;
		for ( i.y = 0; i.y < size.y; i.y++ ) {
			auto intersectionsDxIt = intersectionsDx;
			auto intersectionsXIt = intersectionsX;
			Float yf = Float( i.y );


			Math::Vec2<Float> vertexLast = absoluteVertices[nbVertices - 1].v;
			for ( typename Vector<Math::Vec2<Float>>::Size j = 0; j < nbVertices; j++ ) {
				Vertex & vertex = absoluteVertices[j];

				if ( ( yf < vertex.v.y && yf >= vertexLast.y ) || ( yf < vertexLast.y && yf >= vertex.v.y ) ) {
					intersectionsXIt[0] = ( vertexLast.x + ( yf - vertexLast.y ) * vertex.dx );
					intersectionsDxIt[0] = vertex.dx;
					intersectionsXIt++;
					intersectionsDxIt++;
				}
				vertexLast = vertex.v;
			}





			// Now we have all the intersections for a specified line. Let's order them with an insertion sort.
			auto nbIntersections = intersectionsXIt - intersectionsX;

			unsigned int j, k;
			for ( j = 1; j < nbIntersections; j++ ) {
				k = j;

				while ( k > 0 && intersectionsX[k - 1] > intersectionsX[k] ) {
					Utility::swap( intersectionsDx[k - 1], intersectionsDx[k] );
					Utility::swap( intersectionsX[k - 1], intersectionsX[k] );

					j--;
				}
			}


			for ( typename Vector<Math::Vec2<Float>>::Size j = 1; j < nbIntersections; j += 2 ) {

				Float & intersection0 = intersectionsX[j - 1];
				Float & intersection1 = intersectionsX[j];

				//If the zone to draw is less than one pixel
				if ( intersection1 - intersection0 < 1.0f ) {

					Float opacity = intersection1 - intersection0;
					if ( opacity == 0.0f ) continue;
					i.x = Size( ( intersection0 + intersection1 ) / 2 );

					C1 * p1it = p0it + i.x;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *p1it, colorFunc( i ), opacity );

				} else {
					Float & intersectionDx0 = intersectionsDx[j - 1];
					Float & intersectionDx1 = intersectionsDx[j];

					intersection0 += 0.5f;
					intersection1 += 0.5f;


					Float gradient1 = Math::abs( intersectionDx1 );
					Float gradient0 = Math::abs( intersectionDx0 );

					int xMin, xMax;

					// First Intersection !


					//If the gradient is bigger than One, anti aliasing is easy
					if ( gradient0 < 1.0f ) {
						int intersection0i = int( intersection0 );


						i.x = intersection0i;
						Float opacity = ( intersection0 ) -Float( intersection0i );

						C1 * p1it = p0it + i.x;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *p1it, colorFunc( i ), 1.0f - opacity );

						xMin = i.x + 1;
					} else {
						//the gradient is lower than 1.0, two possibilities here, Up or Down


						if ( intersectionDx0 > 0.0f ) {


							int intersection0i = int( intersection0 );
							int intersection0Beforei = Math::max<int>( int( intersection0 - intersectionDx0 ), 0 );

							Float incr = 1.0f / Float( intersection0i - intersection0Beforei );
							Float opacity = 0.0f;

							i.x = intersection0Beforei;

							xMax = i.x;

							C1 * p1it = p0it + i.x;
							for ( ; i.x < intersection0i; i.x++ ) {

								assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
								blendFunc( *p1it, colorFunc( i ), opacity );

								opacity += incr;
								p1it++;
							}
							xMin = i.x;
						} else {
							int intersection0i = int( intersection0 );
							int intersection0Afteri = Math::max<int>( int( intersection0 + intersectionDx0 ), 0 );


							Float incr = 1.0f / Float( intersection0i - intersection0Afteri );
							Float opacity = 0.0f;

							i.x = intersection0Afteri;

							C1 * p1it = p0it + i.x;
							for ( ; i.x < intersection0i; i.x++ ) {

								assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
								blendFunc( *p1it, colorFunc( i ), opacity );

								opacity += incr;
								p1it++;
							}
							xMin = i.x;

						}


					}




					// Second Intersection !

					//If the gradient is bigger than One, anti aliasing is easy

					if ( gradient1 < 1.0f ) {
						int intersection1i = int( intersection1 );

						i.x = Math::max<Size>( intersection1i, xMin );
						Float opacity = ( intersection1 ) -Float( intersection1i );

						C1 * p1it = p0it + i.x;
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *p1it, colorFunc( i ), opacity );

						xMax = i.x;
					} else {

						//the gradient is lower than 1.0, two possibilities here, Up or Down
						if ( intersectionDx1 > 0.0f ) {
							int intersection1i = int( intersection1 );
							int intersection1Afteri = Math::min<int>( int( intersection1 + intersectionDx1 ), size.x );

							Float incr = 1.0f / ( intersection1Afteri - intersection1i );
							Float opacity = 1.0f;

							i.x = Math::max<int>( intersection1i, xMin );
							xMax = i.x;

							C1 * p1it = p0it + i.x;
							for ( ; i.x < intersection1Afteri; i.x++ ) {

								assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
								blendFunc( *p1it, colorFunc( i ), opacity );

								opacity -= incr;
								p1it++;
							}
						} else {
							int intersection1i = int( intersection1 );
							int intersection1Beforei = Math::min<int>( int( intersection1 - intersectionDx1 ), size.x );



							Float incr = 1.0f / ( intersection1Beforei - intersection1i );
							Float opacity = 1.0f;

							i.x = Math::max<int>( intersection1i, xMin );
							xMax = i.x;

							C1 * p1it = p0it + i.x;
							for ( ; i.x < intersection1Beforei; i.x++ ) {

								assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
								blendFunc( *p1it, colorFunc( i ), opacity );

								opacity -= incr;
								p1it++;
							}

						}
					}

					// Fill the inside !
					i.x = xMin;
					C1 * p1it = p0it + i.x;

					for ( ; i.x < xMax; i.x++ ) {
						assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
						blendFunc( *p1it, colorFunc( i ) );
						p1it++;
					}
				}

				/*// Fill the inside !
				i.x = int(intersection0);

				for ( ; i.x < int( intersection1 ); i.x++ ) {
					C1 * p1it = p0it + i.y * this -> size.x + i.x;
					assert( i.x >= 0 && i.y >= 0 && i.x < size.x && i.y < size.y );
					blendFunc( *p1it, colorFunc( i ) );
				}*/
			}


			p0it += this -> size.x;
		}




		delete[] intersectionsDx;
		delete[] intersectionsX;
		delete[] absoluteVertices;
	}





	template<typename T>
	template<typename K, size_t N>
	K ImageT<T>::computeGaussianKernel( K( &kernel )[N] ) {
		return computeGaussianKernel( kernel, N );
	}

	template<typename T>
	template<typename K>
	K ImageT<T>::computeGaussianKernel( K * kernel, size_t size ) {
		struct KernelsComputed {
			KernelsComputed() {
				for ( size_t i = 0; i < 10; i++ ) {
					size_t diameter = i * 2 + 1;
					this -> kernels[i] = new K[diameter];
					this -> kernelsSum[i] = computeKernel( this -> kernels[i], diameter );
				}
			}

			K computeKernel( K * kernel, size_t size ) {
				return computeGaussianKernel( kernel, size, Float( size ) / Float( 4.0 ) );
			}

			K setKernel( K * kernel, size_t size ) {
				size_t radius = size / 2;
				if ( radius < 10 ) {
					for ( size_t i = 0; i < size; i++ )
						kernel[i] = this -> kernels[radius][i];
					return this -> kernelsSum[radius];
				} else {
					return computeKernel( kernel, size );
				}
			}
			~KernelsComputed() {
				for ( size_t i = 0; i < 10; i++ )
					delete[] this -> kernels[i];
			}
			K * kernels[10];
			K kernelsSum[10];
		};
		static KernelsComputed kernelComputed;


		return kernelComputed.setKernel( kernel, size );
	}




	template<typename T>
	template<typename K, size_t N>
	K ImageT<T>::computeGaussianKernel( K( &kernel )[N], const Float & sigma ) {
		return computeGaussianKernel<K>( ( K * ) kernel, N, sigma );
	}


	template<typename T>
	template<typename K, typename ComputeKernelFunc>
	static K ImageT<T>::_kernelFromFloat2Int( K * kernel, size_t size, ComputeKernelFunc & computeKernelFunc ) {
		constexpr K kernelWeight( 1 << ImageT<T>::getKernelSumNbBits<K>() );

		Float * kernelf = new Float[size];
		computeKernelFunc( kernelf, size );
		Float newWeight = Float( kernelWeight );

		for ( size_t i = 0; i < size; i++ )
			kernel[i] = K( kernelf[i] * newWeight );

		delete[] kernelf;
		return kernelWeight;
	}

	template<typename T>
	template<typename K>
	K ImageT<T>::computeGaussianKernel( K * kernel, size_t size, const Float & sigma ) {
		struct ComputeKernelFunc {
			ComputeKernelFunc( const Float & sigma ) : sigma( sigma ) {}
			void operator()( Float * kernel, size_t size ) const {
				_computeGaussianKernelf<Float>( kernel, size, sigma );
			}
			const Float & sigma;
		};
		ComputeKernelFunc computeKernelFunc( sigma );
		return _kernelFromFloat2Int( kernel, size, computeKernelFunc );
	}

	template<typename T>
	float ImageT<T>::computeGaussianKernel( float * kernel, size_t size, const float & sigma ) {
		return _computeGaussianKernelf<float>( kernel, size, sigma );
	}

	template<typename T>
	double ImageT<T>::computeGaussianKernel( double * kernel, size_t size, const double & sigma ) {
		return _computeGaussianKernelf<double>( kernel, size, sigma );
	}

	template<typename T>
	template<typename K>
	K ImageT<T>::_computeGaussianKernelf( K * kernel, size_t size, const K & sigma ) {
		assert( size % 2 == 1 );
		const size_t NHalfed = size / 2;

		K sigma2Square = K( 2 ) * ( sigma * sigma );
		K sum( 1 );
		kernel[NHalfed] = K( 1 );
		for ( size_t i = 0; i < NHalfed; i++ ) {
			size_t i2 = NHalfed - i;

			K v = Math::exp( -( ( K( i2 * i2 ) ) / sigma2Square ) );
			kernel[i] = v;
			kernel[size - i - 1] = v;

			sum += v * K( 2 );
		}

		//normalize datas
		K oneOnSum = K( 1 ) / sum;
		for ( size_t i = 0; i < size; i++ )
			kernel[i] *= oneOnSum;

		return K( 1.0 );

	}



	template<typename T>
	template<typename K>
	K ImageT<T>::computeSobel1Kernel( K * kernel ) {
		struct ComputeKernelFunc {
			void operator()( float * kernel, size_t size ) const {
				_computeSobel1Kernelf<float>( kernel );
			}
		};
		ComputeKernelFunc computeKernelFunc;
		return _kernelFromFloat2Int( kernel, 3, computeKernelFunc );
	}

	template<typename T>
	float ImageT<T>::computeSobel1Kernel( float * kernel ) {
		return _computeSobel1Kernelf( kernel );
	}

	template<typename T>
	double ImageT<T>::computeSobel1Kernel( double * kernel ) {
		return _computeSobel1Kernelf( kernel );
	}


	template<typename T>
	template<typename K>
	K ImageT<T>::computeSobel2Kernel( K * kernel ) {
		struct ComputeKernelFunc {
			void operator()( float * kernel, size_t size ) const {
				_computeSobel2Kernelf<float>( kernel );
			}
		};
		ComputeKernelFunc computeKernelFunc;
		return _kernelFromFloat2Int( kernel, 3, computeKernelFunc );
	}

	template<typename T>
	float ImageT<T>::computeSobel2Kernel( float * kernel ) {
		return _computeSobel2Kernelf( kernel );
	}

	template<typename T>
	double ImageT<T>::computeSobel2Kernel( double * kernel ) {
		return _computeSobel2Kernelf( kernel );
	}


	template<typename T>
	template<typename K>
	K ImageT<T>::_computeSobel1Kernelf( K * kernel ) {
		kernel[0] = K( -1 );
		kernel[1] = K( 0 );
		kernel[2] = K( 1 );

		return K( 1 );
	}

	template<typename T>
	template<typename K>
	K ImageT<T>::_computeSobel2Kernelf( K * kernel ) {
		kernel[0] = K( 1 );
		kernel[1] = K( 2 );
		kernel[2] = K( 1 );


		return K( 1 );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawImageShadow( const Point & point, unsigned int thickness, const ImageT<T> & image, const ColorR<T> & color, const BlendFunc & blendFunc ) {
		return drawImageShadowFunctor<ColorFunc::SimpleColor<ColorR<T>>>( point, thickness, image, ColorFunc::SimpleColor<ColorR<T>>( color ), blendFunc );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawImageShadow( const Point & point, unsigned int thickness, const ImageT<T> & image, const ColorRGB<T> & color, const BlendFunc & blendFunc ) {
		return drawImageShadowFunctor<ColorFunc::SimpleColor<ColorRGB<T>>>( point, thickness, image, ColorFunc::SimpleColor<ColorRGB<T>>( color ), blendFunc );
	}

	template<typename T>
	template<typename BlendFunc>
	void ImageT<T>::drawImageShadow( const Point & point, unsigned int thickness, const ImageT<T> & image, const ColorRGBA<T> & color, const BlendFunc & blendFunc ) {
		return drawImageShadowFunctor<ColorFunc::SimpleColor<ColorRGBA<T>>>( point, thickness, image, ColorFunc::SimpleColor<ColorRGBA<T>>( color ), blendFunc );
	}


	template<typename T>
	template<typename ColorFunc, typename BlendFunc >
	void ImageT<T>::drawImageShadowFunctor( const Point & point, unsigned int radius, const ImageT<T> & image, ColorFunc & colorFunc, const BlendFunc & blendFunc ) {
		if ( getDatas() == NULL || image.getDatas() == NULL ) return;

		if ( image.getFormat() == Format::R ) {
			Point finalPoint( point.x - radius, point.y - radius );
			if ( radius ) {
				ImageT<T> imageBlured( image.applyGaussianBlur( radius, ImageT<T>::ConvolutionMode::ExtendedSize ) );
				drawImageFunctor( finalPoint, colorFunc, Rectangle( imageBlured.getSize() ), imageBlured, blendFunc );
			} else {
				drawImageFunctor( finalPoint, colorFunc, Rectangle( image.getSize() ), image, blendFunc );
			}
		} else {
			ImageT<T> imageCopy( image.toFormat( Format::R, ColorConvertFunc::Alpha() ) );
			Point finalPoint( point.x - radius, point.y - radius );
			if ( radius ) {
				ImageT<T> imageBlured( imageCopy.applyGaussianBlur( radius, ImageT<T>::ConvolutionMode::ExtendedSize ) );
				drawImageFunctor( finalPoint, colorFunc, Rectangle( imageBlured.getSize() ), imageBlured, blendFunc );
			} else {
				drawImageFunctor( finalPoint, colorFunc, Rectangle( imageCopy.getSize() ), imageCopy, blendFunc );
			}

		}
	}

	template<typename T>
	void ImageT<T>::changeHueSaturationLightness( int hueBias, const Float & saturationFactor, const Float & lightnessFactor ) {
		struct Functor {
			Functor( int hueBias, const Float & saturationFactor, const Float & lightnessFactor ) : hueBias( Float( hueBias ) / Float( 360 ) ), saturationFactor( saturationFactor ), lightnessFactor( lightnessFactor ) {};

			void operator()( const Math::Vec2<Size> & p, ColorR<T> & c ) {
				c.r = Math::min<Float>( Float( c.r * lightnessFactor ), Float( Color<T>::getMax() ) );
			}
			void operator()( const Math::Vec2<Size> & p, ColorRGB<T> & c ) {
				ColorRGB<Float> colorHSL = c.toType<Float>().RGBtoHSL();
				colorHSL.h = Math::modulus( colorHSL.h + hueBias, ( Color<Float>::getMax() ) );
				colorHSL.s = Math::min<Float>( Float( colorHSL.s * saturationFactor ), Float( Color<Float>::getMax() ) );
				colorHSL.l = Math::min<Float>( Float( colorHSL.l * lightnessFactor ), Float( Color<Float>::getMax() ) );
				c = colorHSL.HSLtoRGB().toType<T>();
			}
			void operator()( const Math::Vec2<Size> & p, ColorRGBA<T> & c ) {
				ColorRGB<T> colorRGB( c );
				ColorRGB<Float> colorHSL = colorRGB.toType<Float>().RGBtoHSL();
				colorHSL.h = Math::modulus<SumType>( colorHSL.h + hueBias, Float( Color<Float>::getMax() ) );
				colorHSL.s = Math::min<Float>( Float( colorHSL.s * saturationFactor ), Float( Color<Float>::getMax() ) );
				colorHSL.l = Math::min<Float>( Float( colorHSL.l * lightnessFactor ), Float( Color<Float>::getMax() ) );
				colorRGB = colorHSL.HSLtoRGB().toType<T>();
				c.r = colorRGB.r;
				c.g = colorRGB.g;
				c.b = colorRGB.b;
			}

			Float hueBias;
			const Float & saturationFactor;
			const Float & lightnessFactor;
		};
		Functor functor( hueBias, saturationFactor, lightnessFactor );
		setPixels( functor );

	}



}
