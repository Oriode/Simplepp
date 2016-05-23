namespace Graphic {


	template<typename T>
	TextureLoadable<T>::TextureLoadable(typename Format format) :
		Texture<T>(null),
		loadingType(LoadingType::EMPTY),
		size(Math::Vec2<Size>::null),
		format(format)
	{


	}



	template<typename T>
	TextureLoadable<T>::TextureLoadable(const Math::Vec2<Size> & size, typename Format format) :
		Texture<T>(null),
		loadingType(LoadingType::EMPTY),
		size(size),
		format(format)
	{



	}


	template<typename T>
	TextureLoadable<T>::TextureLoadable(const WString & filePath) : 
		Texture<T>(null),
		fileName(filePath),
		loadingType(LoadingType::FILE),
		size(Math::Vec2<Size>::null)
	{

	}


	template<typename T>
	TextureLoadable<T>::TextureLoadable(const TextureLoadable<T> & image) :
		Texture<T>(image),
		BasicLoadableIO(image),
		fileName(image.fileName),
		loadingType(image.loadingType),
		size(image.size),
		format(image.format)
	{
		

	}


	template<typename T>
	TextureLoadable<T>::TextureLoadable(TextureLoadable<T> && image) : 
		Texture<T>(Utility::toRValue(image)),
		BasicLoadableIO(Utility::toRValue(image)),
		fileName(Utility::toRValue(image.fileName)),
		loadingType(Utility::toRValue(image.loadingType)),
		size(Utility::toRValue(image.size)),
		format(Utility::toRValue(image.format))
	{

	}


	template<typename T>
	TextureLoadable<T>::~TextureLoadable() {

	}



	template<typename T>
	bool TextureLoadable<T>::onRead(std::fstream * fileStream) {
		if ( !Texture<T>::_read(fileStream) )
			return false;

		this -> fileName.clear();
		this -> size = this -> datas[0] -> getSize();
		this -> format = this -> datas[0] -> getFormat();

		return true;
	}

	template<typename T>
	bool TextureLoadable<T>::onWrite(std::fstream * fileStream) const {
		return Texture<T>::write(fileStream);
	}



	template<typename T>
	void TextureLoadable<T>::onUnload() {
		_unload();
	}


	template<typename T>
	void TextureLoadable<T>::onLoad() {
		switch ( this -> loadingType ) {
		case EMPTY: {
			this -> datas.push(new _Image<T>(this -> size, this -> format));
			break;
		}
		case FILE: {
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



	template<typename T>
	Texture<T> & TextureLoadable<T>::operator=(const Texture<T> & image) {
		unload();

		BasicLoadableIO::operator=(image);
		Texture<T>::operator=(image);

		this -> fileName = image.fileName;
		this -> loadingType = image.loadingType;
		this -> size = image.size;
		this -> format = image.format;

		
		return *this;
	}


	template<typename T>
	Texture<T> & Graphic::TextureLoadable<T>::operator=(Texture<T> && image) {
		unload();

		BasicLoadableIO::operator=(Utility::toRValue(image));
		Texture<T>::operator=(Utility::toRValue(image));

		this -> fileName = Utility::toRValue(image.fileName);
		this -> loadingType = Utility::toRValue(image.loadingType);
		this -> size = Utility::toRValue(image.size);
		this -> format = Utility::toRValue(image.format);

		return *this;
	}



	template<typename T>
	void TextureLoadable<T>::clear(const Math::Vec2<Size> & size) {
		this -> loadingType = LoadingType::EMPTY;
		this -> fileName.clear();
		this -> size = size;
		reload();
	}

	template<typename T>
	void TextureLoadable<T>::clear(const Math::Vec2<Size> & size, typename Format format) {
		this -> loadingType = LoadingType::EMPTY;
		this -> format = format;
		this -> fileName.clear();
		this -> size = size;
		reload();
	}


	template<typename T>
	void TextureLoadable<T>::setDatas(const T * dataBuffer, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat, bool invertY) {
		unload();
		lock();
		setLoading(true);

		this -> datas.push(new _Image<T>(dataBuffer, size, loadingFormat, invertY));

		setLoaded(true);
		setLoading(false);
		unlock();
	}

	template<typename T>
	template<typename C /*= unsigned short*/>
	void TextureLoadable<T>::generateMipmaps( ) {
		assert(isLoaded());
		Texture<T>::generateMipmaps<C>();
	}


	template<typename T>
	void TextureLoadable<T>::setPixel(typename Vector<_Image<T>>::Size i, unsigned int x, unsigned int y, const T * p) {
		assert(isLoaded());
		Texture<T>::setPixel(i, x, y, p);
	}

	template<typename T>
	const T * TextureLoadable<T>::getPixel(typename Vector<_Image<T>>::Size i, unsigned int x, unsigned int y) const {
		assert(isLoaded());
		return Texture<T>::getPixel(i, x, y);
	}

	template<typename T>
	T * TextureLoadable<T>::getDatas(typename Vector<_Image<T>>::Size i /*= 0*/) {
		assert(isLoaded());
		return Texture<T>::getDatas(i);
	}

	template<typename T>
	const T * TextureLoadable<T>::getDatas(typename Vector<_Image<T>>::Size i /*= 0*/) const {
		assert(isLoaded());
		return Texture<T>::getDatas(i);
	}

	template<typename T>
	typename Format TextureLoadable<T>::getFormat() const {
		return this -> format;
	}

}

