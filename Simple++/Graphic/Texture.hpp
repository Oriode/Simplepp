

namespace Graphic {

	template<typename T>
	Texture<T>::Texture( typename Format format ) 
	{
		this -> datas.push( new ImageT<T>( format ) );
	}

	template<typename T>
	Graphic::Texture<T>::Texture( const Math::Vec2<Size> & size, typename Format format ) {
		this -> datas.push( new ImageT<T>( size, format ) );
	}

	template<typename T>
	Texture<T>::Texture( std::fstream * fileStream ) {
		if ( !read( fileStream ) ) {

		}
	}

	template<typename T>
	Texture<T>::Texture( const Texture<T> & image ) {
		for ( auto it = image.datas.getBegin(); it != image.datas.getEnd(); it++ )
			this -> datas.push( new ImageT<T>( **it ) );
	}

	template<typename T>
	Texture<T>::Texture( const WString & filePath ) 
	{

	}

	template<typename T>
	Texture<T>::Texture( const T * dataBuffer, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat, bool invertY ) {
		this -> datas.push( new ImageT<T>( dataBuffer, size, loadingFormat, invertY ) );
	}

	template<typename T>
	Texture<T>::Texture( ctor ) {

	}


	template<typename T>
	Texture<T>::Texture( Texture<T> && image ) :
		datas( Utility::toRValue( image.datas ) ) {
		image.datas.clear();	//clear the others datas to ensure no double delete
	}


	template<typename T>
	Texture<T>::~Texture() {
		_unload();
	}


	template<typename T>
	void Graphic::Texture<T>::setPixel( typename Vector<ImageT<T>>::Size i, unsigned int x, unsigned int y, const T * p ) {
		this -> datas[i] ->  getDatas()[this -> size.x * y + x] = p;
	}

	template<typename T>
	const T * Texture<T>::getPixel( typename Vector<ImageT<T>>::Size i, unsigned int x, unsigned int y ) const {
		return this -> datas[i] ->  getDatas()[this -> size.x * y + x];
	}




	template<typename T>
	void Texture<T>::generateMipmaps() {
		if ( this -> datas.getSize() > 1 ) {
			for ( auto it = this -> datas.getBegin() + 1; it != this -> datas.getEnd(); it++ ) {
				delete * it;
			}
			this -> datas.resize( 1 );
		}

		Vector<ImageT<T>>::Size i = 0;
		auto newMipmap = this -> datas[i] -> createMipmap();
		while ( newMipmap ) {
			this -> datas.push( newMipmap );
			i++;
			newMipmap = this -> datas[i] -> createMipmap();
		}
	}


	template<typename T>
	bool Texture<T>::write( std::fstream * fileStream ) const {
		Vector<ImageT<T> *>::Size nbMipmaps = this -> datas.getSize();
		if ( !IO::write( fileStream, &nbMipmaps ) )
			return false;

		for ( auto it = this -> datas.getBegin(); it != this -> datas.getEnd(); it++ ) {
			if ( !IO::write( fileStream, *it ) )
				return false;
		}

		return true;
	}

	template<typename T>
	bool Texture<T>::read( std::fstream * fileStream ) {
		_unload();
		return _read( fileStream );
	}


	template<typename T>
	void Texture<T>::_unload() {
		while ( this -> datas.getSize() )
			delete this -> datas.pop();
	}


	template<typename T>
	bool Texture<T>::_read( std::fstream * fileStream ) {
		Vector<ImageT<T> *>::Size nbDatas;
		if ( !IO::read( fileStream, &nbDatas ) )
			return false;

		// Clamp the number of datas with a big number just in case of file corruption.
		nbDatas = Math::min<Vector<ImageT<T> *>::Size>( nbDatas, 100 );

		for ( Vector<ImageT<T> * >::Size i = 0; i < nbDatas; i++ ) {
			ImageT<T> * newImage = new ImageT<T>();
			if ( newImage -> read( fileStream ) ) {
				this -> datas.push( newImage );
			} else {
				delete newImage;
				_unload();
				return false;
			}
		}
		return true;
	}

	template<typename T>
	void Texture<T>::setDatas( const T * data, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat /*= LoadingFormat::RGB*/, bool invertY /*= false*/ ) {
		_unload();
		this -> datas.push( new ImageT<T>( data, size, loadingFormat, invertY ) );
	}


	template<typename T>
	Texture<T> & Texture<T>::operator=( Texture<T> && image ) {
		for ( auto it = this -> datas.getBegin(); it != this -> datas.getEnd(); it++ )
			delete ( *it );

		this -> datas = Utility::toRValue( image.datas );
		image.datas.clear();	//clear the others datas to ensure no double delete
		return *this;
	}

	template<typename T>
	Texture<T> & Texture<T>::operator=( const Texture<T> & image ) {
		for ( auto it = this -> datas.getBegin(); it != this -> datas.getEnd(); it++ )
			delete ( *it );

		this -> datas.clear();

		for ( auto it = image.datas.getBegin(); it != image.datas.getEnd(); it++ )
			this -> datas.push( new Image( **it ) );

		return *this;
	}



	template<typename T>
	T * Texture<T>::getDatas( typename Vector<ImageT<T>>::Size i ) {
		return this -> datas[i] -> getDatas();
	}

	template<typename T>
	const T * Texture<T>::getDatas( typename Vector<ImageT<T>>::Size i ) const {
		return this -> datas[i] -> getDatas();
	}






	template<typename T>
	unsigned int Texture<T>::getHeight( typename Vector<ImageT<T>>::Size i ) const {
		return this -> datas[i] -> getSize().y;
	}

	template<typename T>
	unsigned int Texture<T>::getWidth( typename Vector<ImageT<T>>::Size i ) const {
		return this -> datas[i] -> getSize().x;
	}

	template<typename T>
	const Math::Vec2<Size> & Texture<T>::getSize( typename Vector<ImageT<T>>::Size i ) const {
		return this -> datas[i] -> getSize();
	}


	template<typename T>
	void Texture<T>::clear( const Math::Vec2<Size> & size ) {
		Format format = getFormat();
		_unload();
		this -> datas.push( new Image( size, format ) );
	}


	template<typename T>
	void Texture<T>::clear( const Math::Vec2<Size> & size, typename Format format ) {
		_unload();
		this -> datas.push( new Image( size, format ) );
	}


	template<typename T>
	typename Format Texture<T>::getFormat() const {
		return this -> datas[0] -> getFormat();
	}

	template<typename T>
	ImageT<T> *Texture<T>::getMipmap( typename Vector<ImageT<T>>::Size i /*= 0*/ ) {
		return this -> datas[i];
	}


	template<typename T /*= unsigned char*/>
	ImageT<T> * Graphic::Texture<T>::operator[]( typename Vector<ImageT<T>>::Size i /*= 0*/ ) {
		return this -> datas[i];
	}

	template<typename T /*= unsigned char*/>
	typename Vector<ImageT<T> * >::Size Texture<T>::getNumMipmaps() const {
		return this -> datas.getSize();
	}
}
