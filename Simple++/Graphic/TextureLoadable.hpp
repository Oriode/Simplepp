namespace Graphic {


	template<typename T>
	TextureLoadable<T>::TextureLoadable( typename Format format ) :
		Texture<T>( ctor::null ),
		loadingType( LoadingType::EMPTY ),
		size( Math::Vec2<Size>::null ),
		format( format ) {


	}



	template<typename T>
	TextureLoadable<T>::TextureLoadable( const Math::Vec2<Size> & size, typename Format format ) :
		Texture<T>( ctor::null ),
		loadingType( LoadingType::EMPTY ),
		size( size ),
		format( format ) {



	}


	template<typename T>
	TextureLoadable<T>::TextureLoadable( const OS::Path & filePath ) :
		Texture<T>( ctor::null ),
		fileName( filePath ),
		loadingType( LoadingType::FILE ),
		size( Math::Vec2<Size>::null ) {

	}


	template<typename T>
	TextureLoadable<T>::TextureLoadable( const TextureLoadable<T> & image ) :
		Texture<T>( image ),
		BasicLoadableIO( image ),
		fileName( image.fileName ),
		loadingType( image.loadingType ),
		size( image.size ),
		format( image.format ) {


	}


	template<typename T>
	TextureLoadable<T>::TextureLoadable( TextureLoadable<T> && image ) :
		Texture<T>( Utility::toRValue( image ) ),
		BasicLoadableIO( Utility::toRValue( image ) ),
		fileName( Utility::toRValue( image.fileName ) ),
		loadingType( Utility::toRValue( image.loadingType ) ),
		size( Utility::toRValue( image.size ) ),
		format( Utility::toRValue( image.format ) ) {

	}


	template<typename T>
	TextureLoadable<T>::~TextureLoadable() {

	}



	template<typename T>
	bool TextureLoadable<T>::onRead( IO::SimpleFileStream * fileStream ) {
		if ( !Texture<T>::_read( fileStream ) )
			return false;

		this -> fileName.clear();
		this -> size = this -> datas[0] -> getSize();
		this -> format = this -> datas[0] -> getFormat();

		return true;
	}

	template<typename T>
	bool TextureLoadable<T>::onWrite( IO::SimpleFileStream * fileStream ) const {
		return Texture<T>::write( fileStream );
	}



	template<typename T>
	bool TextureLoadable<T>::onUnload() {
		_unload();
		return true;
	}


	template<typename T>
	bool TextureLoadable<T>::onLoad() {
		switch ( this -> loadingType ) {
			case EMPTY:
				{
					this -> datas.push( new ImageT<T>( this -> size, this -> format ) );
					break;
				}
			case FILE:
				{
					IO::FileStream fileStream( this -> fileName, IO::OpenMode::Read );
					if ( fileStream.isOpen() ) {
						if ( !onRead( &fileStream ) ) {
							error( StringASCII( "[IO] Error while reading the file : " ) << this -> fileName );
							return false;
						}
					} else {
						error( StringASCII( "[IO] Error while opening the file : " ) << this -> fileName );
						return false;
					}
					break;
				}
		}
		return true;
	}



	template<typename T>
	Texture<T> & TextureLoadable<T>::operator=( const Texture<T> & image ) {
		unload();

		BasicLoadableIO::operator=( image );
		Texture<T>::operator=( image );

		this -> fileName = image.fileName;
		this -> loadingType = image.loadingType;
		this -> size = image.size;
		this -> format = image.format;


		return *this;
	}


	template<typename T>
	Texture<T> & Graphic::TextureLoadable<T>::operator=( Texture<T> && image ) {
		unload();

		BasicLoadableIO::operator=( Utility::toRValue( image ) );
		Texture<T>::operator=( Utility::toRValue( image ) );

		this -> fileName = Utility::toRValue( image.fileName );
		this -> loadingType = Utility::toRValue( image.loadingType );
		this -> size = Utility::toRValue( image.size );
		this -> format = Utility::toRValue( image.format );

		return *this;
	}



	template<typename T>
	void TextureLoadable<T>::clear( const Math::Vec2<Size> & size ) {
		this -> loadingType = LoadingType::EMPTY;
		this -> fileName.clear();
		this -> size = size;
		reload();
	}

	template<typename T>
	void TextureLoadable<T>::clear( const Math::Vec2<Size> & size, typename Format format ) {
		this -> loadingType = LoadingType::EMPTY;
		this -> format = format;
		this -> fileName.clear();
		this -> size = size;
		reload();
	}


	template<typename T>
	void TextureLoadable<T>::setDatas( const T * dataBuffer, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat, bool invertY ) {
		unload();
		lock();
		setLoading( true );
		this -> loadingType = LoadingType::EMPTY;
		this -> fileName.clear();
		this -> datas.push( new ImageT<T>( dataBuffer, size, loadingFormat, invertY ) );
		this -> format = this -> datas[0] -> getFormat();
		setLoaded( true );
		setLoading( false );
		unlock();
	}


	template<typename T>
	void Graphic::TextureLoadable<T>::setDatas( const ImageT<T> & image ) {
		unload();
		lock();
		setLoading( true );
		this -> loadingType = LoadingType::EMPTY;
		this -> fileName.clear();
		this -> datas.push( new ImageT<T>( image ) );
		this -> format = this -> datas[0] -> getFormat();
		setLoaded( true );
		setLoading( false );
		unlock();
	}



	template<typename T>
	void TextureLoadable<T>::generateMipmaps() {
		assert( isLoaded() );
		Texture<T>::generateMipmaps();
	}


	template<typename T>
	void TextureLoadable<T>::setPixel( typename Vector<ImageT<T>>::Size i, unsigned int x, unsigned int y, const T * p ) {
		assert( isLoaded() );
		Texture<T>::setPixel( i, x, y, p );
	}

	template<typename T>
	const T * TextureLoadable<T>::getPixel( typename Vector<ImageT<T>>::Size i, unsigned int x, unsigned int y ) const {
		assert( isLoaded() );
		return Texture<T>::getPixel( i, x, y );
	}

	template<typename T>
	T * TextureLoadable<T>::getDatas( typename Vector<ImageT<T>>::Size i ) {
		assert( isLoaded() );
		return Texture<T>::getDatas( i );
	}

	template<typename T>
	const T * TextureLoadable<T>::getDatas( typename Vector<ImageT<T>>::Size i ) const {
		assert( isLoaded() );
		return Texture<T>::getDatas( i );
	}

	template<typename T>
	typename Format TextureLoadable<T>::getFormat() const {
		return this -> format;
	}

	template<typename T>
	TextureLoadable<T>::operator Texture<T>() const {
		//return Texture<T>( *( ( Texture<T> * ) this ) );
		if ( isLoaded() ) {
			Texture<T> newTexture( ctor::null );
			for ( auto it( this -> datas.getBegin() ); it != this -> datas.getEnd(); this -> datas.iterate( &it ) ) {
				newTexture.datas.push( new Image<T>( *( this -> datas.getValueIt( it ) ) ) );
			}
		} else {
			return Texture<T>( this -> format );
		}
	}

}

