

namespace Graphic {

	template<typename T>
	_Image<T>::_Image(Format format) :
		format(format),
		buffer(NULL),
		size(Math::vec2ui::null),
		nbPixels(0) {
	}

	template<typename T>
	Graphic::_Image<T>::_Image(const Math::vec2ui & size, Format format) :
		format(format),
		size(size),
		nbPixels(size.x * size.y),
		buffer(new T[this -> nbPixels * (unsigned char) format]){

	}

	template<typename T>
	_Image<T>::_Image(const _Image<T> & image) :
		format(image.format),
		size(image.size),
		nbPixels(image.nbPixels){
		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponents];
			Vector<T>::copy(this -> buffer, image.buffer, nbComponents);
		} else {
			this -> buffer = NULL;
		}
	}



	template<typename T>
	template<typename C>
	_Image<T>::_Image(const _Image<C> & image) : 
		format(image.getFormat()),
		size(image.getSize()),
		nbPixels(image.getNbPixels()) {
		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponents];


			auto thisIt = this -> buffer;
			auto otherIt = image.getDatas();

			for ( size_t i = 0; i < nbComponents; i++ ) {
				_castComponment(thisIt, otherIt);
				thisIt++;
				otherIt++;
			}

		} else {
			this -> buffer = NULL;
		}
	}



	template<typename T>
	_Image<T>::_Image(_Image<T> && image) {
		*this = Utility::toRValue(image);
	}



	template<typename T>
	_Image<T>::_Image(const T * data, const Math::vec2ui & size, LoadingFormat loadingFormat, bool invertY) {
		_allocateAndCopy(data, size, loadingFormat, invertY);
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::_allocateAndCopy(const T * data, const Math::vec2ui & size, LoadingFormat loadingFormat /*= LoadingFormat::RGB*/, bool invertY /*= false*/) {
		this -> size = size;
		this -> nbPixels = size.x * size.y;

		if ( this -> nbPixels > 0 && data ) {
			this -> format = _loadingFormat2Format(loadingFormat);
			size_t nbComponentsTotal = this -> nbPixels * this -> getNbComponents();
			this -> buffer = new T[nbComponentsTotal];


			switch ( loadingFormat ) {
			case LoadingFormat::BGR: {
				if ( invertY ) {
					size_t nbComponentsPerRow = size.x * getNbComponents();
					auto otherIt = data + nbComponentsPerRow * ( size.y - 1 );
					auto thisIt = getDatas();
					for ( unsigned int y = 0; y < size.y; y++ ) {
						auto thisIt2 = thisIt;
						auto otherIt2 = otherIt;
						for ( unsigned int x = 0; x < size.x; x++ ) {
							thisIt2[0] = otherIt2[2];
							thisIt2[1] = otherIt2[1];
							thisIt2[2] = otherIt2[0];

							thisIt2 += getNbComponents();
							otherIt += getNbComponents();
						}
						thisIt += nbComponentsPerRow;
						otherIt -= nbComponentsPerRow;
					}
				} else {
					auto otherIt = data;
					auto thisIt = getDatas();
					for ( size_t i = 0; i < this -> nbPixels; i++ ) {
						thisIt[0] = otherIt[2];
						thisIt[1] = otherIt[1];
						thisIt[2] = otherIt[0];

						thisIt += getNbComponents();
						otherIt += getNbComponents();
					}
				}
				break;
			}
			case LoadingFormat::BGRA: {
				if ( invertY ) {
					size_t nbComponentsPerRow = size.x * getNbComponents();
					auto otherIt = data + nbComponentsPerRow * ( size.y - 1 );
					auto thisIt = getDatas();
					for ( unsigned int y = 0; y < size.y; y++ ) {
						auto thisIt2 = thisIt;
						auto otherIt2 = otherIt;
						for ( unsigned int x = 0; x < size.x; x++ ) {
							thisIt2[0] = otherIt2[2];
							thisIt2[1] = otherIt2[1];
							thisIt2[2] = otherIt2[0];
							thisIt2[3] = otherIt2[3];

							thisIt2 += getNbComponents();
							otherIt += getNbComponents();
						}
						thisIt += nbComponentsPerRow;
						otherIt -= nbComponentsPerRow;
					}
				} else {
					auto otherIt = data;
					auto thisIt = getDatas();
					for ( size_t i = 0; i < this -> nbPixels; i++ ) {
						thisIt[0] = otherIt[2];
						thisIt[1] = otherIt[1];
						thisIt[2] = otherIt[0];
						thisIt[3] = otherIt[3];

						thisIt += getNbComponents();
						otherIt += getNbComponents();
					}
				}
				break;
			}
			default: {
				if ( invertY ) {
					//Copy row per row.
					size_t nbComponentsPerRow = size.x * getNbComponents();
					auto otherIt = data + nbComponentsPerRow * ( size.y - 1 );
					auto thisIt = getDatas();
					for ( unsigned int y = 0; y < size.y; y++ ) {
						Vector<T>::copy(thisIt, otherIt, nbComponentsPerRow);
						thisIt += nbComponentsPerRow;
						otherIt -= nbComponentsPerRow;
					}
				} else {
					//Copy the whole data
					Vector<T>::copy(this -> buffer, data, nbComponentsTotal);
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
	_Image<T>::~_Image() {
		delete[] this -> buffer;
	}


	template<typename T>
	void Graphic::_Image<T>::setPixel(unsigned int x, unsigned int y, const T * p) {
		switch ( this -> format ) {
		case Format::R:
			getDatas()[(this -> size.x * y + x) * this -> format] = *p;
			break;
		case Format::RGB:
			size_t offset = (this -> size.x * y + x) * this -> format;
			getDatas()[offset + 0] = *(p + 0);
			getDatas()[offset + 1] = *(p + 1);
			getDatas()[offset + 2] = *(p + 2);
			break;
		case Format::RGBA:
			size_t offset = ( this -> size.x * y + x ) * this -> format;
			getDatas()[offset + 0] = *( p + 0 );
			getDatas()[offset + 1] = *( p + 1 );
			getDatas()[offset + 2] = *( p + 2 );
			getDatas()[offset + 3] = *( p + 3 );
			break;
		}
	}

	template<typename T>
	const T * _Image<T>::getPixel(unsigned int x, unsigned int y) const {
		return getDatas(x, y);
	}




	template<typename T /*= unsigned char*/>
	T * Graphic::_Image<T>::getPixel(unsigned int x, unsigned int y) {
		return getDatas(x, y);
	}




	template<typename T /*= unsigned char*/>
	size_t _Image<T>::getDataOffset(unsigned int x, unsigned int y) const {
		return ( y * this -> size.x + x ) * getNbComponents();
	}


	template<typename T>
	bool _Image<T>::write(std::fstream * fileStream) const {
		if ( !IO::write(fileStream, &this -> size) )
			return false;
		if ( !IO::write(fileStream, &this -> format) )
			return false;
		size_t nbComponents = this -> nbPixels * getNbComponents();
		if ( !IO::writeBuffer(fileStream, this -> buffer, nbComponents) )
			return false;

		return true;
	}


	template<typename T>
	_Image<T>::_Image(std::fstream * fileStream) {
		_read(fileStream);
	}


	template<typename T>
	void _Image<T>::setDatas(const T * data, const Math::vec2ui & size, LoadingFormat loadingFormat, bool invertY) {
		delete[] this -> buffer;
		_allocateAndCopy(data, size, loadingFormat, invertY);
	}



	template<typename T>
	bool _Image<T>::_read(std::fstream * fileStream) {
		if ( !IO::read(fileStream, &this -> size) )
			return false;
		if ( !IO::read(fileStream, &this -> format) )
			return false;
		this -> nbPixels = size.x * size.y;
		size_t nbComponents = this -> nbPixels * getNbComponents();
		this -> buffer = new T[nbComponents];

		if ( !IO::readBuffer(fileStream, this -> buffer, nbComponents) )
			return false;
		return true;
	}


	template<typename T>
	bool _Image<T>::read(std::fstream * fileStream) {
		delete[] this -> buffer;
		return _read(fileStream);
	}

	template<typename T>
	_Image<T> & _Image<T>::operator=(_Image<T> && image) {
		this -> buffer = Utility::toRValue(image.buffer);
		this -> format = Utility::toRValue(image.format);
		this -> size = Utility::toRValue(image.size);
		this -> nbPixels = Utility::toRValue(image.nbPixels);

		image.buffer = NULL;

		return *this;
	}

	template<typename T>
	_Image<T> & _Image<T>::operator=(const _Image<T> & image) {
			this -> size = image.size;
			this -> nbPixels = image.nbPixels;
			this -> format = image.format;

			if ( this -> nbPixels ) {
				size_t nbComponents = this -> nbPixels * this -> getNbComponents();
				this -> buffer = new T[nbComponents];
				Vector<T>::copy(this -> buffer, image.buffer, nbComponents);
			} else {
				this -> buffer = NULL;
			}

		return *this;
	}


	template<typename T>
	template<typename C>
	_Image<T> & _Image<T>::operator=(const _Image<C> & image) {
		this -> size = image.getSize();
		this -> nbPixels = image.getNbPixels();
		this -> format = image.getFormat();


		if ( this -> nbPixels ) {
			size_t nbComponents = this -> nbPixels * getNbComponents();
			this -> buffer = new T[nbComponents];


			auto thisIt = this -> buffer;
			auto otherIt = image.getDatas();

			for ( size_t i = 0; i < nbComponents; i++ ) {
				_castComponment(thisIt, otherIt);
				thisIt++;
				otherIt++;
			}

		} else {
			this -> buffer = NULL;
		}

		return *this;
	}





	template<typename T>
	T * _Image<T>::getDatas() {
		return this -> buffer;

	}

	template<typename T>
	const T * _Image<T>::getDatas() const {
		return this -> buffer;
	}

	template<typename T>
	T * _Image<T>::getDatas(unsigned int x, unsigned int y) {
		return this -> buffer + getDataOffset(x, y);

	}

	template<typename T>
	const T * _Image<T>::getDatas(unsigned int x, unsigned int y) const {
		return this -> buffer + getDataOffset(x, y);
	}


	template<typename T>
	unsigned int _Image<T>::getHeight() const {
		return this -> size.y;
	}

	template<typename T>
	unsigned int _Image<T>::getWidth() const {
		return this -> size.x;
	}

	template<typename T>
	const Math::vec2ui & _Image<T>::getSize() const {
		return this -> size;
	}


	template<typename T>
	void _Image<T>::clear(const Math::vec2ui & size) {
		this -> size = size;
		this -> nbPixels = this -> size.x * this -> size.y;
		delete[] this -> buffer;
		size_t nbComponents = this -> nbPixels * this -> format;
		this -> buffer = new T[nbComponents];
	}


	template<typename T>
	void _Image<T>::clear(const Math::vec2ui & size, Format format) {
		this -> size = size;
		this -> format = format;
		this -> nbPixels = this -> size.x * this -> size.y;
		delete[] this -> buffer;
		size_t nbComponents = this -> nbPixels * this -> format;
		this -> buffer = new T[nbComponents];
	}



	template<typename T>
	template<typename C /* = unsigned short */>
	_Image<T> * _Image<T>::createMipmap() {
		Math::vec2ui newSize = getSize() / Math::vec2ui(2);
		if ( newSize.x == 0 || newSize.y == 0 )
			return NULL;

		_Image<T> * newImage = new _Image<T>(newSize, this -> format);

		switch ( this -> format ) {
		case Format::R:
			return _createMipmap<C, T>(newImage);
			break;
		case Format::RGB:
			return _createMipmap<Math::Vec3<C>, Math::Vec3<T>>(newImage);
			break;
		case Format::RGBA:
			return _createMipmap<Math::Vec4<C>, Math::Vec4<T>>(newImage);
			break;
		}
		return NULL;
	}

	template<typename T>
	template<typename C /*= unsigned short */, typename PIX>
	_Image<T> * _Image<T>::_createMipmap(_Image<T> * newImage) {
		Math::vec2ui i(0);

		auto newSize = newImage -> getSize();
		PIX * newImageData = (PIX *) newImage -> getDatas();
		PIX * p0_1 = ( PIX * ) this -> buffer;
		PIX * p0_2;

		for ( i.y = 0; i.y < newSize.y; i.y++ ) {
			p0_2 = p0_1;
			for ( i.x = 0; i.x < newSize.x; i.x++ ) {
				//P0	P1
				//P2	P3
				PIX * p2 = ( p0_2 + this -> size.x );

				C newP(*p0_2);
				newP += *( p0_2 + 1 );
				newP += *p2;
				newP += *( p2 + 1 );
				newP >>= 2;			//newP /= 4

				newImageData[0] = PIX(newP);
				newImageData++;

				p0_2 += 2;
			}
			p0_1 += this -> size.x * 2;
		}
		return newImage;
	}


	template<typename T>
	typename Format _Image<T>::getFormat() const {
		return this -> format;
	}


	template<typename T /*= unsigned char*/>
	size_t _Image<T>::getNbPixels() const {
		return this -> nbPixels;
	}





	template<typename T>
	void _Image<T>::fillImage(const T * color) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _fillImage<ColorR<T>, ColorR<T>>(*((ColorR<T> *) color));
		case Format::RGB: 	//Blend RGBA -> RGB
			return _fillImage<ColorRGB<T>, ColorRGB<T>>(*( (ColorRGB<T> *) color ));
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _fillImage<ColorRGBA<T>, ColorRGBA<T>>(*( (ColorRGBA<T> *) color ));
		}
	}

	template<typename T>
	void _Image<T>::fillImage(const T * color, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _fillImage<ColorR<T>, ColorRGBA<T>>(*( (ColorR<T> *) color ), rectangle);
		case Format::RGB: 	//Blend RGBA -> RGB
			return _fillImage<ColorRGB<T>, ColorRGBA<T>>(*( (ColorRGB<T> *) color ), rectangle);
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _fillImage<ColorRGBA<T>, ColorRGBA<T>>(*( (ColorRGBA<T> *) color ), rectangle);
		}
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::fillImage(const ColorR<T> & color) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _fillImage<ColorR<T>, ColorR<T>>(color);
		case Format::RGB: 	//Blend RGBA -> RGB
			return _fillImage<ColorRGB<T>, ColorR<T>>(color);
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _fillImage<ColorRGBA<T>, ColorR<T>>(color);
		}
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::fillImage(const ColorRGB<T> & color) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _fillImage<ColorR<T>, ColorRGB<T>>(color);
		case Format::RGB: 	//Blend RGBA -> RGB
			return _fillImage<ColorRGB<T>, ColorRGB<T>>(color);
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _fillImage<ColorRGBA<T>, ColorRGB<T>>(color);
		}
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::fillImage(const ColorRGBA<T> & color) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _fillImage<ColorR<T>, ColorRGBA<T>>(color);
		case Format::RGB: 	//Blend RGBA -> RGB
			return _fillImage<ColorRGB<T>, ColorRGBA<T>>(color);
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _fillImage<ColorRGBA<T>, ColorRGBA<T>>(color);
		}
	}



	template<typename T /*= unsigned char*/>
	template<typename C1, typename C2>
	void _Image<T>::_fillImage(const C2 & color) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);

		auto it = this -> buffer;
		for ( size_t i = 0; i < this -> nbPixels; i++ ) {
			BlendingFunc::None::blendColor(*( ( C1 * ) it ), color);
			it += N1;
		}
	}


	////////////////////

	template<typename T /*= unsigned char*/>
	template<typename ColorFunc>
	void _Image<T>::setPixels(ColorFunc & colorFunc) {
		return setPixels(colorFunc, Rectangle(0, getSize()));
	}


	template<typename T /*= unsigned char*/>
	template<typename ColorFunc>
	void _Image<T>::setPixels(ColorFunc & colorFunc, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: 		//Blend R -> R
			return _setPixels<ColorFunc, ColorR<T>>(colorFunc, rectangle);
		case Format::RGB: 	//Blend R -> RGB
			return _setPixels<ColorFunc, ColorRGB<T>>(colorFunc, rectangle);
		case Format::RGBA: 	//Blend R -> RGBA
			return _setPixels<ColorFunc, ColorRGBA<T>>(colorFunc, rectangle);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename C>
	void _Image<T>::_setPixels(ColorFunc & colorFunc, const Rectangle & rectangle) {
		constexpr size_t N = sizeof(C) / sizeof(T);

		Math::Rectangle<unsigned int> rectangleUI = clampRectangle(rectangle);
		auto it = getDatas(rectangleUI.getLeft(), rectangleUI.getBottom());
		typename Math::vec2ui::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLine = N * this -> size.x;

		Math::Vec2<typename Math::vec2ui::Type> i;
		for ( i.y = rectangleUI.getBottom(); i.y < rectangleUI.getTop(); i.y++ ) {
			auto it2 = it;
			for ( i.x = rectangleUI.getLeft(); i.x < rectangleUI.getRight(); i.x++ ) {
				colorFunc(i, *( (C *) it2 ));
				it2 += N;
			}
			it += nbComponentsPerLine;
		}
	}

	template<typename T /*= unsigned char*/>
	Math::Rectangle<unsigned int> _Image<T>::clampRectangle(const Rectangle & rectangle) const {
		Math::Rectangle<unsigned int> rectangleUI;

		if ( rectangle.getBottom() < 0 ) 		rectangleUI.setBottom(0);
		else							rectangleUI.setBottom(rectangle.getBottom());


		if ( rectangle.getLeft() < 0 )		rectangleUI.setLeft(0);
		else							rectangleUI.setLeft(rectangle.getLeft());


		if ( rectangle.getTop() < 0 )				rectangleUI.setTop(0);
		else								rectangleUI.setTop(rectangle.getTop());


		if ( rectangle.getRight() < 0 )			rectangleUI.setRight(0);
		else								rectangleUI.setRight(rectangle.getRight());

		if ( rectangleUI.getTop() > getSize().y )		rectangleUI.setTop(getSize().y);
		if ( rectangleUI.getRight() > getSize().x )	rectangleUI.setRight(getSize().x);

		return rectangleUI;
	}


	////////////////////
	template<typename T /*= unsigned char*/>
	void _Image<T>::fillImage(const ColorR<T> & color, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendingFunc::None, ColorR<T>, ColorR<T>>(rectangle, color, BlendingFunc::None());
		case Format::RGB:
			return _drawRectangle<BlendingFunc::None, ColorRGB<T>, ColorR<T>>(rectangle, color, BlendingFunc::None());
		case Format::RGBA:
			return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, ColorR<T>>(rectangle, color, BlendingFunc::None());
		}
	}

	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fillImage(const ColorRGB<T> & color, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendingFunc::None, ColorR<T>, ColorRGB<T>>(rectangle, color, BlendingFunc::None());
		case Format::RGB:
			return _drawRectangle<BlendingFunc::None, ColorRGB<T>, ColorRGB<T>>(rectangle, color, BlendingFunc::None());
		case Format::RGBA:
			return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, ColorRGB<T>>(rectangle, color, BlendingFunc::None());
		}
	}

	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fillImage(const ColorRGBA<T> & color, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendingFunc::None, ColorR<T>, ColorRGBA<T>>(rectangle, color, BlendingFunc::None());
		case Format::RGB:
			return _drawRectangle<BlendingFunc::None, ColorRGB<T>, ColorRGBA<T>>(rectangle, color, BlendingFunc::None());
		case Format::RGBA:
			return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, ColorRGBA<T>>(rectangle, color, BlendingFunc::None());
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc>
	void Graphic::_Image<T>::fillImage(const GradientHorizontal<C, InterFunc> & gradient, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _fillImage<ColorR<T>, C, InterFunc>(gradient, rectangle);
		case Format::RGB: 	//Blend RGBA -> RGB
			return _fillImage<ColorRGB<T>, C, InterFunc>(gradient, rectangle);
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _fillImage<ColorRGBA<T>, C, InterFunc>(gradient, rectangle);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc>
	void Graphic::_Image<T>::fillImage(const GradientVertical<C, InterFunc> & gradient, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _drawRectangle<BlendingFunc::None, ColorR<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		case Format::RGB: 	//Blend RGBA -> RGB
			return _drawRectangle<BlendingFunc::None, ColorRGB<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		}
	}


	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc>
	void Graphic::_Image<T>::fillImage(const GradientLinear<C, InterFunc> & gradient, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _drawRectangle<BlendingFunc::None, ColorR<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		case Format::RGB: 	//Blend RGBA -> RGB
			return _drawRectangle<BlendingFunc::None, ColorRGB<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		}
	}


	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc>
	void Graphic::_Image<T>::fillImage(const GradientRadial<C, InterFunc> & gradient, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: 		//Blend RGBA -> R
			return _drawRectangle<BlendingFunc::None, ColorR<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		case Format::RGB: 	//Blend RGBA -> RGB
			return _drawRectangle<BlendingFunc::None, ColorRGB<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		case Format::RGBA: 	//Blend RGBA -> RGBA
			return _drawRectangle<BlendingFunc::None, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, BlendingFunc::None());
		}
	}


	

	template<typename T /*= unsigned char*/>
	void _Image<T>::fillImage(const Point & point, const _Image<T> & image) {
		fillImage(point, Rectangle(image.getSize()), image);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::fillImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image) {
		switch ( this -> format ) {
		case Format::R: {
			switch ( image.getFormat() ) {
			case Format::R: 		//Blend R -> R
				return _fillImage<ColorR<T>, ColorR<T>>(point, rectangle, image);
			case Format::RGB: 	//Blend RGB -> R
				return _fillImage<ColorR<T>, ColorRGB<T>>(point, rectangle, image);
			case Format::RGBA: 	//Blend RGBA -> R
				return _fillImage<ColorR<T>, ColorRGBA<T>>(point, rectangle, image);
			}
		}
		case Format::RGB: {
			switch ( image.getFormat() ) {
			case Format::R: 		//Blend R -> RGB
				return _fillImage<ColorRGB<T>, ColorR<T>>(point, rectangle, image);
			case Format::RGB: 	//Blend RGB -> RGB
				return _fillImage<ColorRGB<T>, ColorRGB<T>>(point, rectangle, image);
			case Format::RGBA: 	//Blend RGBA -> RGB
				return _fillImage<ColorRGB<T>, ColorRGBA<T>>(point, rectangle, image);
			}
		}
		case Format::RGBA: {
			switch ( image.getFormat() ) {
			case Format::R: 		//Blend R -> RGBA
				return _fillImage<ColorRGBA<T>, ColorR<T>>(point, rectangle, image);
			case Format::RGB: 	//Blend RGB -> RGBA
				return _fillImage<ColorRGBA<T>, ColorRGB<T>>(point, rectangle, image);
			case Format::RGBA: 	//Blend RGBA -> RGBA
				return _fillImage<ColorRGBA<T>, ColorRGBA<T>>(point, rectangle, image);
			}
		}
		}
	}

	

	template<typename T /*= unsigned char*/>
	template<typename C1, typename C2>
	void _Image<T>::_fillImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Vec2<unsigned int> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<unsigned int> otherImageBegin;
		Point size;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x);
		} else if ( point.x > (typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft());
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y);
		} else if ( point.y > (typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		auto thisIt = getDatas(begin.x, begin.y);
		auto thisImageOffset = this -> size.x * N1;

		auto otherIt = image.getDatas(otherImageBegin.x, otherImageBegin.y);
		auto otherImageOffset = image.getSize().x * N2;

		if ( N1 == N2 ) {
			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				Vector<T>::copy(thisIt, otherIt, size.x * N1);
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		} else {
			Point i;
			size_t sizeOffset = size.x * N1;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				auto maxit = thisIt + sizeOffset;
				for ( ; thisIt2 < maxit; ) {
					BlendingFunc::None::blendColor(*( ( C1 * )thisIt2 ), *( ( C2 * ) otherIt2 ));
					thisIt2 += N1;
					otherIt2 += N2;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		}
	}









	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage) {
		drawImage(point, Rectangle(image.getSize()), image, maskPoint, maskImage);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const _Image<T> & image, const _Image<T> & maskImage) {
		drawImage(point, Rectangle(image.getSize()), image, Point::null, maskImage);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const _Image<T> & image) {
		drawImage(point, Rectangle(image.getSize()), image);
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorR<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		drawImage(point, color, Rectangle(maskImage.getSize()), maskImage, blendFunc);
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGB<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		drawImage(point, color, Rectangle(maskImage.getSize()), maskImage, blendFunc);
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGBA<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		drawImage(point, color, Rectangle(maskImage.getSize()), maskImage, blendFunc);
	}



	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image) {
		switch ( getFormat() ) {
		case Format::R: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<ColorR<T>, ColorR<T>>(point, rectangle, image);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<ColorR<T>, ColorRGB<T>>(point, rectangle, image);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<ColorR<T>, ColorRGBA<T>>(point, rectangle, image);
			}
			break;
		}
		case Format::RGB: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<ColorRGB<T>, ColorR<T>>(point, rectangle, image);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<ColorRGB<T>, ColorRGB<T>>(point, rectangle, image);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<ColorRGB<T>, ColorRGBA<T>>(point, rectangle, image);
			}
			break;
		}
		case Format::RGBA: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<ColorRGBA<T>, ColorR<T>>(point, rectangle, image);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<ColorRGBA<T>, ColorRGB<T>>(point, rectangle, image);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<ColorRGBA<T>, ColorRGBA<T>>(point, rectangle, image);
			}
			break;
		}
		}
	}



	template<typename T /*= unsigned char*/>
	template<typename C1, typename C2>
	void _Image<T>::_drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);


		Math::Vec2<unsigned int> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<unsigned int> otherImageBegin;
		Point size;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x);
		} else if ( point.x > (typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft());
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y);
		} else if ( point.y > (typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		auto thisIt = getDatas(begin.x, begin.y);
		auto thisImageOffset = this -> size.x * N1;

		auto otherIt = image.getDatas(otherImageBegin.x, otherImageBegin.y);
		auto otherImageOffset = image.getSize().x * N2;

		if ( N1 != 4 && N1 == N2 ) {
			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				Vector<T>::copy(thisIt, otherIt, size.x * N1);
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		} else {
			Point i;
			size_t sizeOffset = size.x * N1;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				auto maxit = thisIt + sizeOffset;
				for ( ; thisIt2 < maxit; ) {
					BlendingFunc::Normal::blendColor(*( ( C1* )thisIt2 ), *( ( C2* ) otherIt2 ));
					thisIt2 += N1;
					otherIt2 += N2;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}
		}
	}




	template<typename T>
	template<typename BlendFunc>
	void _Image<T>::drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const BlendFunc & blendFunc) {
		switch ( getFormat() ) {
		case Format::R: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<BlendFunc, ColorR<T>, ColorR<T>>(point, rectangle, image,  blendFunc);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<BlendFunc, ColorR<T>, ColorRGB<T>>(point, rectangle, image, blendFunc);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<BlendFunc, ColorR<T>, ColorRGBA<T>>(point, rectangle, image, blendFunc);
			}
			break;
		}
		case Format::RGB: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<BlendFunc, ColorRGB<T>, ColorR<T>>(point, rectangle, image, blendFunc);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<BlendFunc, ColorRGB<T>, ColorRGB<T>>(point, rectangle, image, blendFunc);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<BlendFunc, ColorRGB<T>, ColorRGBA<T>>(point, rectangle, image, blendFunc);
			}
			break;
		}
		case Format::RGBA: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<BlendFunc, ColorRGBA<T>, ColorR<T>>(point, rectangle, image, blendFunc);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<BlendFunc, ColorRGBA<T>, ColorRGB<T>>(point, rectangle, image, blendFunc);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<BlendFunc, ColorRGBA<T>, ColorRGBA<T>>(point, rectangle, image, blendFunc);
			}
			break;
		}
		}
	}


	template<typename T>
	template<typename BlendFunc, typename C1, typename C2>
	void _Image<T>::_drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const BlendFunc & blendFunc) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Vec2<unsigned int> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<unsigned int> otherImageBegin;
		Point size;

		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x);
		} else if ( point.x > (typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft());
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y);
		} else if ( point.y > (typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		auto thisIt = getDatas(begin.x, begin.y);
		auto thisImageOffset = this -> size.x * N1;
		size_t sizeOffset = size.x * N1;

		auto otherIt = image.getDatas(otherImageBegin.x, otherImageBegin.y);
		auto otherImageOffset = image.getSize().x * N2;

		Point i;
		for ( i.y = 0; i.y < size.y; i.y++ ) {
			auto thisIt2 = thisIt;
			auto otherIt2 = otherIt;
			auto maxIt = thisIt + sizeOffset;
			for ( ; thisIt2 < maxIt; thisIt2 += N1 ) {
				blendFunc(*( ( C1* )thisIt2 ), *( ( C2* )otherIt2 ));
				otherIt2 += N2;
			}
			thisIt += thisImageOffset;
			otherIt += otherImageOffset;
		}
	}




	template<typename T /*= unsigned char */>
	template<typename BlendFunc>
	void _Image<T>::drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		switch ( getFormat() ) {
		case Format::R: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<ColorR<T>, ColorR<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<ColorR<T>, ColorRGB<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<ColorR<T>, ColorRGBA<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			}
			break;
		}
		case Format::RGB: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<ColorRGB<T>, ColorR<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<ColorRGB<T>, ColorRGB<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<ColorRGB<T>, ColorRGBA<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			}
			break;
		}
		case Format::RGBA: {
			switch ( image.getFormat() ) {
			case Format::R: 			//Blend R -> R
				return _drawImage<ColorRGBA<T>, ColorR<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			case Format::RGB:			//Blend RGB -> R
				return _drawImage<ColorRGBA<T>, ColorRGB<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			case Format::RGBA:		//Blend RGBA -> R
				return _drawImage<ColorRGBA<T>, ColorRGBA<T>>(point, rectangle, image, maskPoint, maskImage, blendFunc);
			}
			break;
		}
		}

	}



	template<typename T /*= unsigned char */>
	template<typename BlendFunc, typename C1, typename C2>
	void _Image<T>::_drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Vec2<unsigned int> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<unsigned int> otherImageBegin;
		Math::Vec2<unsigned int> maskBegin;
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
			size.x = Math::min<typename Point::Type>(this -> size.x, maskImage.getSize().x - maskPoint.x + point.x);
		} else if ( point.x > (typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x - point.x, maskImage.getSize().x - maskPoint.x);
		}

		if ( begin.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y, maskImage.getSize().y - maskPoint.y + point.y);
		} else if ( point.y > (typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, maskImage.getSize().y - maskPoint.y);
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		auto maskIt = maskImage.getDatas(maskBegin.x, maskBegin.y);
		auto maskImageOffset = maskImage.getSize().x * maskImage.getNbComponents();
		size_t sizeOffset = size.x * N1;

		auto thisIt = getDatas(begin.x, begin.y);
		auto thisImageOffset = this -> size.x * N1;

		auto otherIt = image.getDatas(otherImageBegin.x, otherImageBegin.y);
		auto otherImageOffset = image.getSize().x * N2;


		Point i;
		for ( i.y = 0; i.y < size.y; i.y++ ) {
			auto thisIt2 = thisIt;
			auto otherIt2 = otherIt;
			auto maskIt2 = maskIt;
			auto maxIt = thisIt + sizeOffset;
			for ( i.x = 0; i.x < size.x; i.x++ ) {
				blendFunc(*( (C1*) thisIt2 ), *( (C2*) otherIt2 ), *( ( ColorR<T>* ) maskIt2 ));
				thisIt2 += N1;
				otherIt2 += N2;
				maskIt2 += maskImage.getNbComponents();
			}
			thisIt += thisImageOffset;
			otherIt += otherImageOffset;
			maskIt += maskImageOffset;
		}
	}





	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		class MyColorFunc {
		public:
			MyColorFunc(const ColorR<T> & color) : color(color) {}
			inline ColorR<T> operator()(const Math::Vec2<unsigned int> & p) const { return this -> color; }
			const ColorR<T> & color;
		};

		switch ( getFormat() ) {
		case Format::R: 			//Blend R -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorR<T>, ColorR<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		case Format::RGB:			//Blend RGB -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorRGB<T>, ColorR<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		case Format::RGBA:		//Blend RGBA -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorRGBA<T>, ColorR<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		class MyColorFunc {
		public:
			MyColorFunc(const ColorRGB<T> & color) : color(color) {}
			inline ColorRGB<T> operator()(const Math::Vec2<unsigned int> & p) const { return this -> color; }
			const ColorRGB<T> & color;
		};

		switch ( getFormat() ) {
		case Format::R: 			//Blend R -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorR<T>, ColorRGB<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		case Format::RGB:			//Blend RGB -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorRGB<T>, ColorRGB<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		case Format::RGBA:		//Blend RGBA -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorRGBA<T>, ColorRGB<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		class MyColorFunc {
		public:
			MyColorFunc(const ColorRGBA<T> & color) : color(color) {}
			inline ColorRGBA<T> operator()(const Math::Vec2<unsigned int> & p) const { return this -> color; }
			const ColorRGBA<T> & color;
		};

		switch ( getFormat() ) {
		case Format::R: 			//Blend R -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorR<T>, ColorRGBA<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		case Format::RGB:			//Blend RGB -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorRGB<T>, ColorRGBA<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		case Format::RGBA:		//Blend RGBA -> R
			return _drawImage<MyColorFunc, BlendFunc, ColorRGBA<T>, ColorRGBA<T>>(point, MyColorFunc(color), rectangle, maskImage, blendFunc);
		}
	}



	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc>
	void Graphic::_Image<T>::drawImageR(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		switch ( getFormat() ) {
		case Format::R: 			//Blend R -> R
			return _drawImage<ColorFunc, BlendFunc, ColorR<T>, ColorR<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		case Format::RGB:			//Blend RGB -> R
			return _drawImage<ColorFunc, BlendFunc, ColorRGB<T>, ColorR<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		case Format::RGBA:		//Blend RGBA -> R
			return _drawImage<ColorFunc, BlendFunc, ColorRGBA<T>, ColorR<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc>
	void Graphic::_Image<T>::drawImageRGB(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		switch ( getFormat() ) {
		case Format::R: 			//Blend R -> R
			return _drawImage<ColorFunc, BlendFunc, ColorR<T>, ColorRGB<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		case Format::RGB:			//Blend RGB -> R
			return _drawImage<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGB<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		case Format::RGBA:		//Blend RGBA -> R
			return _drawImage<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGB<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc>
	void Graphic::_Image<T>::drawImageRGBA(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		switch ( getFormat() ) {
		case Format::R: 			//Blend R -> R
			return _drawImage<ColorFunc, BlendFunc, ColorR<T>, ColorRGBA<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		case Format::RGB:			//Blend RGB -> R
			return _drawImage<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGBA<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		case Format::RGBA:		//Blend RGBA -> R
			return _drawImage<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGBA<T>>(point, colorFunc, rectangle, maskImage, blendFunc);
		}
	}



	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc, typename C1, typename C2>
	void Graphic::_Image<T>::_drawImage(const Point & point, const ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Vec2<unsigned int> begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Math::Vec2<unsigned int> maskImageBegin;
		Point size;
		if ( point.x < 0 ) {
			begin.x = 0;
			maskImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x);
		} else if ( point.x > (typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			maskImageBegin.x = rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft());
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			maskImageBegin.y = -point.y + rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y, rectangle.getTop() - rectangle.getBottom() + point.y);
		} else if ( point.y > (typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			maskImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}

		if ( size.x <= 0 || size.y <= 0 ) return;

		auto thisIt = getDatas(begin.x, begin.y);
		auto thisImageOffset = this -> size.x * N1;

		auto maskIt = maskImage.getDatas(maskImageBegin.x, maskImageBegin.y);
		auto maskImageOffset = maskImage.getSize().x * maskImage.getNbComponents();


		Math::Vec2<unsigned int> end(begin.x + size.x, begin.y + size.y);
		Math::Vec2<unsigned int> i;
		for ( i.y = begin.y; i.y < end.y; i.y++ ) {
			auto thisIt2 = thisIt;
			auto otherIt2 = maskIt;
			for ( i.x = begin.x; i.x < end.x; i.x++ ) {
				if ( *( ( ColorR<T>* ) otherIt2 ) != T(0) ) {
					blendFunc(*( (C1*) thisIt2 ), colorFunc(i), *( ( ColorR<T>* ) otherIt2 ));
				}
				otherIt2 += maskImage.getNbComponents();
				thisIt2 += N1;
			}
			thisIt += thisImageOffset;
			maskIt += maskImageOffset;
		}
	}



	template<typename T /*= unsigned char*/>
	T _Image<T>::getComponentMaxValue() {
		return Utility::TypesInfos<T>::getMax();
	}

	template<>
	float _Image<float>::getComponentMaxValue() {
		return 1.0f;
	}

	template<>
	double _Image<double>::getComponentMaxValue() {
		return 1.0;
	}




	template<typename T /*= unsigned char*/>
	void _Image<T>::_castComponment(unsigned char * dest, const float * source) {
		( *dest ) = (unsigned char) ( *(source) * 255.0f );
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_castComponment(unsigned char * dest, const double * source) {
		( *dest ) = (unsigned char) ( *(source) * 255.0 );
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_castComponment(float * dest, const unsigned char * source) {
		( *dest ) = ( (float) *( source ) ) / 255.0f;
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_castComponment(double * dest, const unsigned char * source) {
		( *dest ) = ( (double) *( source ) ) / 255.0;
	}

	template<typename T>
	template<typename C, typename D>
	void _Image<T>::_castComponment(D * dest, const C * source) {
		*( dest ) = D(*( source ));
	}




	template<typename T>
	template<typename C, int N>
	_Image<T> _Image<T>::applyFilter(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		return applyFilter(filter, N, convolutionMode, color);
	}



	template<typename T>
	template<typename C>
	_Image<T> _Image<T>::applyFilter(const C * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		return _applyFilter(filter, size, convolutionMode, color);
	}



	template<typename T>
	template<int N>
	_Image<T> _Image<T>::_applyFilter(const float * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		return _applyFilterf<float>(filter, size, convolutionMode, color);
	}

	template<typename T>
	template< int N>
	_Image<T> _Image<T>::_applyFilter(const double * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		return _applyFilterf<double>(filter, size, convolutionMode, color);
	}


	template<typename T>
	template<typename C>
	_Image<T> _Image<T>::_applyFilter(const C * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		assert(size % 2 == 1);

		typename Math::vec2ui::Type NHalfed = ( size / 2 );
		typename Math::vec2ui::Type NEven = NHalfed * 2;

		typename Math::vec2ui::Type borderSize1;
		typename Math::vec2ui::Type borderSize2;

		switch ( convolutionMode ) {
		case ConvolutionMode::ExtendedSize:
			borderSize1 = NHalfed;
			borderSize2 = NHalfed - 1;
			break;
		case ConvolutionMode::NormalSize:
			borderSize1 = NHalfed;
			borderSize2 = 0;
		}
		
		typename Math::vec2ui::Type borderSize = borderSize1 + borderSize2;


		Math::vec2ui sizeExtended(this -> size.x + borderSize2 * 2, this -> size.y + borderSize2 * 2);
		Math::vec2ui sizeBorder(this -> size.x + borderSize * 2, this -> size.y + borderSize * 2);

		_Image<T> imageBorder(sizeBorder, this -> getFormat());
		_Image<T> imageHori(imageBorder.getSize(), this -> getFormat());
		_Image<T> imageVert(sizeExtended, this -> getFormat());


		size_t nbComponentsPerRow = this -> getNbComponents() * this -> getSize().x;
		size_t nbComponentsPerRowWithBorder = this -> getNbComponents() * imageBorder.getSize().x;
		size_t nbComponentsPerRowExtended = this -> getNbComponents() * imageVert.getSize().x;


		//drawing the background color 
		imageBorder.fillImage(color, Rectangle(0, borderSize, borderSize, imageBorder.getSize().y - borderSize ));
		imageBorder.fillImage(color, Rectangle(imageBorder.getSize().x - borderSize, borderSize, imageBorder.getSize().x, imageBorder.getSize().y - borderSize ));

		imageHori.fillImage(color, Rectangle(0, 0, imageHori.getSize().x, borderSize));
		imageHori.fillImage(color, Rectangle(0, imageHori.getSize().y - borderSize, imageHori.getSize().x, imageHori.getSize().y));


		//copy the old image into a bigger one to handle border correctly without overflow
		auto thisIt = this -> getDatas();
		auto imageBorderIt = imageBorder.getDatas() + imageBorder.getDataOffset(borderSize, borderSize);
		for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
			Vector<T>::copy(imageBorderIt, thisIt, nbComponentsPerRow);

			thisIt += nbComponentsPerRow;
			imageBorderIt += nbComponentsPerRowWithBorder;
		}
		C divide = 0;
		for ( size_t i = 0; i < size; i++ )
			divide += filter[i];

		auto NOffset = imageBorder.getDataOffset(borderSize1, borderSize1 + borderSize2);
		imageBorderIt = imageBorder.getDatas() + NOffset;
		auto imageHoriIt = imageHori.getDatas() + NOffset;
		NOffset = borderSize1 * this -> getNbComponents();
		auto imageVertIt = imageVert.getDatas();


		switch ( this -> format ) {
		case Format::R: {
			C sum;
			for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2 - NOffset;

					sum = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						sum += C(imageBorderIt3[0]) * filter[i];
						imageBorderIt3 += imageBorder.getNbComponents();
					}
					imageHoriIt2[0] = T(sum / divide);

					imageBorderIt2 += imageBorder.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}

			imageHoriIt = imageHori.getDatas() + imageHori.getDataOffset(borderSize1, borderSize1);
			NOffset = NHalfed * nbComponentsPerRowWithBorder;
			for ( typename Math::vec2ui::Type y = 0; y < imageVert.getSize().y; y++ ) {
				auto imageVertIt2 = imageVertIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {

					auto resultHoriIt3 = imageHoriIt2 - NOffset;

					sum = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						sum += C(resultHoriIt3[0]) * filter[i];
						resultHoriIt3 += nbComponentsPerRowWithBorder;
					}
					imageVertIt2[0] = T(sum / divide);

					imageVertIt2 += imageVert.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageVertIt += nbComponentsPerRowExtended;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}
			break;
		}
		case Format::RGB: {
			C sum[3];
			for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2 - NOffset;

					sum[0] = C(0);
					sum[1] = C(0);
					sum[2] = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						sum[0] += C(imageBorderIt3[0]) * filter[i];
						sum[1] += C(imageBorderIt3[1]) * filter[i];
						sum[2] += C(imageBorderIt3[2]) * filter[i];

						imageBorderIt3 += imageBorder.getNbComponents();
					}

					imageHoriIt2[0] = T(sum[0] / divide);
					imageHoriIt2[1] = T(sum[1] / divide);
					imageHoriIt2[2] = T(sum[2] / divide);

					imageBorderIt2 += imageBorder.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}

			imageHoriIt = imageHori.getDatas() + imageHori.getDataOffset(borderSize1, borderSize1);
			NOffset = NHalfed * nbComponentsPerRowWithBorder;
			for ( typename Math::vec2ui::Type y = 0; y < imageVert.getSize().y; y++ ) {
				auto imageVertIt2 = imageVertIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {

					auto resultHoriIt3 = imageHoriIt2 - NOffset;

					sum[0] = C(0);
					sum[1] = C(0);
					sum[2] = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						sum[0] += C(resultHoriIt3[0]) * filter[i];
						sum[1] += C(resultHoriIt3[1]) * filter[i];
						sum[2] += C(resultHoriIt3[2]) * filter[i];
						resultHoriIt3 += nbComponentsPerRowWithBorder;
					}

					imageVertIt2[0] = T(sum[0] / divide);
					imageVertIt2[1] = T(sum[1] / divide);
					imageVertIt2[2] = T(sum[2] / divide);

					imageVertIt2 += imageVert.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageVertIt += nbComponentsPerRowExtended;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}
			break;
		}
		case Format::RGBA: {
			C sum[4];
			for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2 - NOffset;

					sum[0] = C(0);
					sum[1] = C(0);
					sum[2] = C(0);
					sum[3] = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						sum[0] += C(imageBorderIt3[0]) * filter[i];
						sum[1] += C(imageBorderIt3[1]) * filter[i];
						sum[2] += C(imageBorderIt3[2]) * filter[i];
						sum[3] += C(imageBorderIt3[3]) * filter[i];

						imageBorderIt3 += imageBorder.getNbComponents();
					}

					imageHoriIt2[0] = T(sum[0] / divide);
					imageHoriIt2[1] = T(sum[1] / divide);
					imageHoriIt2[2] = T(sum[2] / divide);
					imageHoriIt2[3] = T(sum[3] / divide);

					imageBorderIt2 += imageBorder.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}

			imageHoriIt = imageHori.getDatas() + imageHori.getDataOffset(borderSize1, borderSize1);
			NOffset = NHalfed * nbComponentsPerRowWithBorder;
			for ( typename Math::vec2ui::Type y = 0; y < imageVert.getSize().y; y++ ) {
				auto imageVertIt2 = imageVertIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {

					auto resultHoriIt3 = imageHoriIt2 - NOffset;

					sum[0] = C(0);
					sum[1] = C(0);
					sum[2] = C(0);
					sum[3] = C(0);

					for ( size_t i = 0; i < size; i++ ) {
						sum[0] += C(resultHoriIt3[0]) * filter[i];
						sum[1] += C(resultHoriIt3[1]) * filter[i];
						sum[2] += C(resultHoriIt3[2]) * filter[i];
						sum[3] += C(resultHoriIt3[3]) * filter[i];

						resultHoriIt3 += nbComponentsPerRowWithBorder;
					}

					imageVertIt2[0] = T(sum[0] / divide);
					imageVertIt2[1] = T(sum[1] / divide);
					imageVertIt2[2] = T(sum[2] / divide);
					imageVertIt2[3] = T(sum[3] / divide);

					imageVertIt2 += imageVert.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageVertIt += nbComponentsPerRowExtended;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}
			break;
		}
		}


		return imageVert;
	}



	


	template<typename T>
	template<typename C>
	_Image<T> _Image<T>::_applyFilterf(const C * filter, size_t size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		assert(size % 2 == 1);
		assert((Utility::isSame<T, C>::value));

		typename Math::vec2ui::Type NHalfed = ( size / 2 );
		typename Math::vec2ui::Type NEven = NHalfed * 2;

		typename Math::vec2ui::Type borderSize1;
		typename Math::vec2ui::Type borderSize2;

		switch ( convolutionMode ) {
		case ConvolutionMode::ExtendedSize:
			borderSize1 = NHalfed;
			borderSize2 = NHalfed - 1;
			break;
		case ConvolutionMode::NormalSize:
			borderSize1 = NHalfed;
			borderSize2 = 0;
		}
		typename Math::vec2ui::Type borderSize = borderSize1 + borderSize2;


		Math::vec2ui sizeExtended(this -> size.x + borderSize2 * 2, this -> size.y + borderSize2 * 2);
		Math::vec2ui sizeBorder(this -> size.x + borderSize * 2, this -> size.y + borderSize * 2);

		_Image<T> imageBorder(sizeBorder, this -> getFormat());
		_Image<T> imageHori(imageBorder.getSize(), this -> getFormat());
		_Image<T> imageVert(sizeExtended, this -> getFormat());


		size_t nbComponentsPerRow = this -> getNbComponents() * this -> getSize().x;
		size_t nbComponentsPerRowWithBorder = this -> getNbComponents() * imageBorder.getSize().x;
		size_t nbComponentsPerRowExtended = this -> getNbComponents() * imageVert.getSize().x;


		//drawing the background color 
		imageBorder.fill(color, Rectangle(0, borderSize, borderSize, imageBorder.getSize().y - borderSize));
		imageBorder.fill(color, Rectangle(imageBorder.getSize().x - borderSize, borderSize, imageBorder.getSize().x, imageBorder.getSize().y - borderSize));

		imageHori.fill(color, Rectangle(0, 0, imageHori.getSize().x, borderSize));
		imageHori.fill(color, Rectangle(0, imageHori.getSize().y - borderSize, imageHori.getSize().x, imageHori.getSize().y));


		//copy the old image into a bigger one to handle border correctly without overflow
		auto thisIt = this -> getDatas();
		auto imageBorderIt = imageBorder.getDatas() + imageBorder.getDataOffset(borderSize, borderSize);
		for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
			Vector<T>::copy(imageBorderIt, thisIt, nbComponentsPerRow);

			thisIt += nbComponentsPerRow;
			imageBorderIt += nbComponentsPerRowWithBorder;
		}

		auto NOffset = imageBorder.getDataOffset(borderSize1, borderSize1 + borderSize2);
		imageBorderIt = imageBorder.getDatas() + NOffset;
		auto imageHoriIt = imageHori.getDatas() + NOffset;
		NOffset = borderSize1 * this -> getNbComponents();
		auto imageVertIt = imageVert.getDatas();


		switch ( this -> format ) {
		case Format::R: {
			for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2 - NOffset;

					imageHoriIt2[0] = C(0);
					for ( int i = 0; i < N; i++ ) {
						imageHoriIt2[0] += C(imageBorderIt3[0]) * filter[i];
						imageBorderIt3 += imageBorder.getNbComponents();
					}
					imageBorderIt2 += imageBorder.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}

			imageHoriIt = imageHori.getDatas() + imageHori.getDataOffset(borderSize1, borderSize1);
			NOffset = NHalfed * nbComponentsPerRowWithBorder;
			for ( typename Math::vec2ui::Type y = 0; y < imageVert.getSize().y; y++ ) {
				auto imageVertIt2 = imageVertIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {

					auto resultHoriIt3 = imageHoriIt2 - NOffset;

					imageVertIt2[0] = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						imageVertIt2[0] += C(resultHoriIt3[0]) * filter[i];
						resultHoriIt3 += nbComponentsPerRowWithBorder;
					}
					imageVertIt2 += imageVert.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageVertIt += nbComponentsPerRowExtended;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}
			break;
		}
		case Format::RGB: {
			for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2 - NOffset;

					imageHoriIt2[0] = C(0);
					imageHoriIt2[1] = C(0);
					imageHoriIt2[2] = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						imageHoriIt2[0] += C(imageBorderIt3[0]) * filter[i];
						imageHoriIt2[1] += C(imageBorderIt3[1]) * filter[i];
						imageHoriIt2[2] += C(imageBorderIt3[2]) * filter[i];

						imageBorderIt3 += imageBorder.getNbComponents();
					}

					imageBorderIt2 += imageBorder.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}

			imageHoriIt = imageHori.getDatas() + imageHori.getDataOffset(borderSize1, borderSize1);
			NOffset = NHalfed * nbComponentsPerRowWithBorder;
			for ( typename Math::vec2ui::Type y = 0; y < imageVert.getSize().y; y++ ) {
				auto imageVertIt2 = imageVertIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {

					auto resultHoriIt3 = imageHoriIt2 - NOffset;

					imageVertIt2[0] = C(0);
					imageVertIt2[1] = C(0);
					imageVertIt2[2] = C(0);
					for ( size_t i = 0; i < size; i++ ) {
						imageVertIt2[0] += C(resultHoriIt3[0]) * filter[i];
						imageVertIt2[1] += C(resultHoriIt3[1]) * filter[i];
						imageVertIt2[2] += C(resultHoriIt3[2]) * filter[i];
						resultHoriIt3 += nbComponentsPerRowWithBorder;
					}



					imageVertIt2 += imageVert.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageVertIt += nbComponentsPerRowExtended;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}
			break;
		}
		case Format::RGBA: {
			for ( typename Math::vec2ui::Type y = 0; y < this -> size.y; y++ ) {
				auto imageBorderIt2 = imageBorderIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto imageBorderIt3 = imageBorderIt2 - NOffset;
					imageHoriIt2[0] = C(0);
					imageHoriIt2[1] = C(1);
					imageHoriIt2[2] = C(2);
					imageHoriIt2[3] = C(3);

					for ( size_t i = 0; i < size; i++ ) {
						imageHoriIt2[0] += C(imageBorderIt3[0]) * filter[i];
						imageHoriIt2[1] += C(imageBorderIt3[1]) * filter[i];
						imageHoriIt2[2] += C(imageBorderIt3[2]) * filter[i];
						imageHoriIt2[3] += C(imageBorderIt3[3]) * filter[i];

						imageBorderIt3 += imageBorder.getNbComponents();
					}

					imageBorderIt2 += imageBorder.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageBorderIt += nbComponentsPerRowWithBorder;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}

			imageHoriIt = imageHori.getDatas() + imageHori.getDataOffset(borderSize1, borderSize1);
			NOffset = NHalfed * nbComponentsPerRowWithBorder;
			for ( typename Math::vec2ui::Type y = 0; y < imageVert.getSize().y; y++ ) {
				auto imageVertIt2 = imageVertIt;
				auto imageHoriIt2 = imageHoriIt;
				for ( typename Math::vec2ui::Type x = 0; x < imageVert.getSize().x; x++ ) {
					auto resultHoriIt3 = imageHoriIt2 - NOffset;
					imageVertIt2[0] = C(0);
					imageVertIt2[1] = C(1);
					imageVertIt2[2] = C(2);
					imageVertIt2[3] = C(3);
					for ( size_t i = 0; i < size; i++ ) {
						imageVertIt2[0] += C(resultHoriIt3[0]) * filter[i];
						imageVertIt2[1] += C(resultHoriIt3[1]) * filter[i];
						imageVertIt2[2] += C(resultHoriIt3[2]) * filter[i];
						imageVertIt2[3] += C(resultHoriIt3[3]) * filter[i];

						resultHoriIt3 += nbComponentsPerRowWithBorder;
					}

					imageVertIt2 += imageVert.getNbComponents();
					imageHoriIt2 += imageHori.getNbComponents();
				}


				imageVertIt += nbComponentsPerRowExtended;
				imageHoriIt += nbComponentsPerRowWithBorder;
			}
			break;
		}
		}


		return imageVert;
	}







	template<typename T /*= unsigned char*/>
	_Image<T> _Image<T>::toFormat(Format newFormat, ConversionMode conversionMode) const {
		_Image<T> newImage(getSize(), newFormat);

		switch ( getFormat() ) {
		case Format::R: {

			switch ( newFormat ) {
			case Format::R: {		// R -> R
				Vector<T>::copy(newImage.buffer, this -> buffer, getNbPixels() * getNbComponents());
				break;
			}
			case Format::RGB: {	// R -> RGB
				auto thisIt = this -> buffer;
				auto otherIt = newImage.getDatas();
				auto maxIt = thisIt + getNbPixels() * getNbComponents();

				for ( ; thisIt < maxIt; ) {
					otherIt[0] = thisIt[0];
					otherIt[1] = thisIt[0];
					otherIt[2] = thisIt[0];

					thisIt += getNbComponents();
					otherIt += newImage.getNbComponents();
				}
				break;
			}
			case Format::RGBA: {	//R -> RGBA
				auto thisIt = this -> buffer;
				auto otherIt = newImage.getDatas();
				auto maxIt = thisIt + getNbPixels() * getNbComponents();

				for ( ; thisIt < maxIt; ) {
					otherIt[0] = thisIt[0];
					otherIt[1] = thisIt[0];
					otherIt[2] = thisIt[0];
					otherIt[3] = getComponentMaxValue();

					thisIt += getNbComponents();
					otherIt += newImage.getNbComponents();
				}
				break;
			}
			}


			break;
		}
		case Format::RGB: {

			switch ( newFormat ) {
			case Format::R: {		// RGB -> R
				auto thisIt = this -> buffer;
				auto otherIt = newImage.getDatas();
				auto maxIt = thisIt + getNbPixels() * getNbComponents();

				switch ( conversionMode ) {
				case ConversionMode::Alpha:
					for ( ; thisIt < maxIt; ) {
						otherIt[0] = getComponentMaxValue();
						thisIt += getNbComponents();
						otherIt += newImage.getNbComponents();
					}

					break;
				case ConversionMode::Luminance: {
					for ( ; thisIt < maxIt; ) {
						BlendingFunc::Normal::blendColor(*( ( ColorR<T>* )otherIt ), *( ( ColorRGB<T>* )thisIt ));
						thisIt += getNbComponents();
						otherIt += newImage.getNbComponents();
					}
				}
				case ConversionMode::Trunquate: {
					for ( ; thisIt < maxIt; ) {
						otherIt[0] = thisIt[0];
						thisIt += getNbComponents();
						otherIt += newImage.getNbComponents();
					}
				}
				default:
					break;
				}


				break;
			}
			case Format::RGB: {	// RGB -> RGB
				Vector<T>::copy(newImage.buffer, this -> buffer, getNbPixels() * getNbComponents());
				break;
			}
			case Format::RGBA: {	//RGB -> RGBA
				auto thisIt = this -> buffer;
				auto otherIt = newImage.getDatas();
				auto maxIt = thisIt + getNbPixels() * getNbComponents();

				for ( ; thisIt < maxIt; ) {
					BlendingFunc::Normal::blendColor(*( ( ColorRGBA<T>* )otherIt ), *( ( ColorRGB<T>* )thisIt ));
					thisIt += getNbComponents();
					otherIt += newImage.getNbComponents();
				}
				break;
			}
			}

			break;
		}
		case Format::RGBA: {

			switch ( newFormat ) {
			case Format::R: {		// RGBA -> R
				auto thisIt = this -> buffer;
				auto otherIt = newImage.getDatas();
				auto maxIt = thisIt + getNbPixels() * getNbComponents();

				switch ( conversionMode ) {
				case ConversionMode::Alpha:
					for ( ; thisIt < maxIt; ) {
						otherIt[0] = thisIt[3];
						otherIt += newImage.getNbComponents();
					}

					break;
				case ConversionMode::Luminance: {
					for ( ; thisIt < maxIt; ) {
						BlendingFunc::Normal::blendColor(*( ( ColorR<T>* )otherIt ), *( ( ColorRGB<T>* )thisIt ));
						thisIt += getNbComponents();
						otherIt += newImage.getNbComponents();
					}
				}
				case ConversionMode::Trunquate: {
					for ( ; thisIt < maxIt; ) {
						otherIt[0] = thisIt[0];
						thisIt += getNbComponents();
						otherIt += newImage.getNbComponents();
					}
				}
				default:
					break;
				}


				break;
			}
			case Format::RGB: {	// RGBA -> RGB
				auto thisIt = this -> buffer;
				auto otherIt = newImage.getDatas();
				auto maxIt = thisIt + getNbPixels() * getNbComponents();

				for ( ; thisIt < maxIt; ) {
					otherIt[0] = thisIt[0];
					otherIt[1] = thisIt[1];
					otherIt[2] = thisIt[2];

					thisIt += getNbComponents();
					otherIt += newImage.getNbComponents();
				}
				break;
			}
			case Format::RGBA: {	//RGBA -> RGBA
				Vector<T>::copy(newImage.buffer, this -> buffer, getNbPixels() * getNbComponents());
				break;
			}
			}
			break;
		}
		}



		return newImage;


	}

	template<typename T /*= unsigned char*/>
	unsigned int Graphic::_Image<T>::getNbComponents() const {
		return ( unsigned int ) this -> format;
	}


	template<typename T /*= unsigned char*/>
	Format _Image<T>::_loadingFormat2Format(LoadingFormat loadingFormat) {
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

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const ColorR<T> & color, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R: 
			return _drawRectangle<BlendFunc, ColorR<T>, ColorR<T>>(rectangle, color, blendFunc);
		case Format::RGB: 
			return _drawRectangle<BlendFunc, ColorRGB<T>, ColorR<T>>(rectangle, color, blendFunc);
		case Format::RGBA: 
			return _drawRectangle<BlendFunc, ColorRGBA<T>, ColorR<T>>(rectangle, color, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const ColorRGB<T> & color, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendFunc, ColorR<T>, ColorRGB<T>>(rectangle, color, blendFunc);
		case Format::RGB:
			return _drawRectangle<BlendFunc, ColorRGB<T>, ColorRGB<T>>(rectangle, color, blendFunc);
		case Format::RGBA:
			return _drawRectangle<BlendFunc, ColorRGBA<T>, ColorRGB<T>>(rectangle, color, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const ColorRGBA<T> & color, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendFunc, ColorR<T>, ColorRGBA<T>>(rectangle, color, blendFunc);
		case Format::RGB:
			return _drawRectangle<BlendFunc, ColorRGB<T>, ColorRGBA<T>>(rectangle, color, blendFunc);
		case Format::RGBA:
			return _drawRectangle<BlendFunc, ColorRGBA<T>, ColorRGBA<T>>(rectangle, color, blendFunc);
		}
	}


	template<typename T /*= unsigned char*/>
	template<typename BlendFunc, typename C1, typename C2>
	void _Image<T>::_drawRectangle(const Rectangle & rectangle, const C2 & color, const BlendFunc & functor) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Rectangle<unsigned int> rectangleUI = clampRectangle(rectangle);
		auto it = getDatas(rectangleUI.getLeft(), rectangleUI.getBottom());
		typename Math::vec2ui::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLineRectangle = N1 * width;
		size_t nbComponentsPerLine = N1 * this -> size.x;


		for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
			auto maxIt = it + nbComponentsPerLineRectangle;
			for ( auto it2 = it; it2 < maxIt; it2 += N1 ) {
				functor(*( (C1 *) it2 ), color);
			}
			it += nbComponentsPerLine;
		}
	}



	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc, typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const GradientLinear<C, InterFunc> & gradient, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGB:
			return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGBA:
			return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc, typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const GradientRadial<C, InterFunc> & gradient, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGB:
			return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGBA:
			return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc, typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGB:
			return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGBA:
			return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc, typename BlendFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const GradientVertical<C, InterFunc> & gradient, const BlendFunc & blendFunc) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangle<BlendFunc, ColorR<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGB:
			return _drawRectangle<BlendFunc, ColorRGB<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		case Format::RGBA:
			return _drawRectangle<BlendFunc, ColorRGBA<T>, C, InterFunc>(rectangle, gradient, blendFunc);
		}
	}


	template<typename T /*= unsigned char*/>
	template<typename C, typename InterFunc>
	void _Image<T>::drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C, InterFunc> & gradient) {
		switch ( getFormat() ) {
			case Format::R:
				return _drawRectangle<ColorR<T>, C, InterFunc>(rectangle, gradient);
			case Format::RGB:
				return _drawRectangle<ColorRGB<T>, C, InterFunc>(rectangle, gradient);
			case Format::RGBA:
				return _drawRectangle<ColorRGBA<T>, C, InterFunc>(rectangle, gradient);
		}
	}




	template<typename T /*= unsigned char*/>
	template<typename C1, typename C2, typename InterFunc>
	void _Image<T>::_drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C2, InterFunc> & gradient) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);


		float size = rectangle.getRight() - rectangle.getLeft();
		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<unsigned int> clampedSize = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		float begin = float(int(clampedRectangle.getLeft()) - rectangle.getLeft()) / size;
		float end = 1.0f - float(rectangle.getRight() - int(clampedRectangle.getRight())) / size;

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * N1;

		//generate the gradient
		C2 * gradientArray = new C2[clampedSize.x];
		gradient.computeInterpolation(gradientArray, clampedSize.x, begin, end);

		Math::Vec2<unsigned int> i;
		if ((N1 != 4) && (N1 == N2)) {
			for ( i.y = 0; i.y < clampedSize.y; i.y++ ) {
				Vector<T>::copy((C2*)thisIt, gradientArray, clampedSize.x);
				thisIt += thisImageOffset;
			}
		} else {
			for ( i.y = 0; i.y < clampedSize.y; i.y++ ) {
				auto maxIt = thisIt + clampedSize.x * N1;
				auto gradientIt = gradientArray;
				for ( auto thisIt2 = thisIt; thisIt2 < maxIt; ) {
					BlendingFunc::Normal::blendColor(*( ( C1* )thisIt2 ), *( (C2*) gradientIt ));
					thisIt2 += N1;
					gradientIt ++;
				}
				thisIt += thisImageOffset;
			}
		}

		//free the buffer
		delete[] gradientArray;
	}


	template<typename T /*= unsigned char*/>
	template<typename C1, typename C2, typename InterFunc>
	void _Image<T>::_fillImage(const GradientHorizontal<C2, InterFunc> & gradient, const Rectangle & rectangle){
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		float size = rectangle.getRight() - rectangle.getLeft();
		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<unsigned int> clampedSize = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		float begin = float(int(clampedRectangle.getLeft()) - rectangle.getLeft()) / size;
		float end = 1.0f - float(rectangle.getRight() - int(clampedRectangle.getRight())) / size;

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * N1;

		//generate the gradient
		C2 * gradientArray = new C2[clampedSize.x];
		gradient.computeInterpolation(gradientArray, clampedSize.x, end, begin);

		Math::Vec2<unsigned int> i;
		if ( ( N1 == N2 ) ) {
			for ( i.y = 0; i.y < clampedSize.y; i.y++ ) {
				Vector<T>::copy((C2*)thisIt, gradientArray, clampedSize.x);
				thisIt += thisImageOffset;
			}
		} else {
			for ( i.y = 0; i.y < clampedSize.y; i.y++ ) {
				auto maxIt = thisIt + clampedSize.x * N1;
				auto gradientIt = gradientArray;
				for ( auto thisIt2 = thisIt; thisIt2 < maxIt; ) {
					BlendingFunc::None::blendColor(*( (C1*) thisIt2 ), *( (C2*) gradientIt ));
					thisIt2 += N1;
					gradientIt ++;
				}
				thisIt += thisImageOffset;
			}
		}

		//free the buffer
		delete[] gradientArray;
	}




	template<typename T /*= unsigned char*/>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void _Image<T>::_drawRectangle(const Rectangle & rectangle, const GradientHorizontal<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		float size = rectangle.getRight() - rectangle.getLeft();
		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<unsigned int> clampedSize = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		float begin = float(int(clampedRectangle.getLeft()) - rectangle.getLeft()) / size;
		float end = 1.0f - float(rectangle.getRight() - int(clampedRectangle.getRight())) / size;

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * N1;

		//generate the gradient
		C2 * gradientArray = new T[clampedSize.x];
		gradient.computeInterpolation(gradientArray, clampedSize.x, begin, end);

		Point i;
		for ( i.y = 0; i.y < clampedSize.y; i.y++ ) {
			auto maxIt = thisIt + clampedSize.x * N1;
			auto gradientIt = gradientArray;
			for ( auto thisIt2 = thisIt; thisIt2 < maxIt; thisIt2 += N1 ) {
				blendingFunctor(*( ( C1* )thisIt2 ), *( gradientIt ));
				gradientIt++;
			}
			thisIt += thisImageOffset;
		}
		
		//free the buffer
		delete[] gradientArray;
	}

	template<typename T /*= unsigned char*/>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void _Image<T>::_drawRectangle(const Rectangle & rectangle, const GradientVertical<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		float size = rectangle.getTop() - rectangle.getBottom();
		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<unsigned int> clampedSize = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		float begin = float(int(clampedRectangle.getBottom()) - rectangle.getBottom()) / size;
		float end = 1.0f - float(rectangle.getTop() - int(clampedRectangle.getTop())) / size;

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * N1;

		//generate the gradient
		C2 * gradientArray = new C2[clampedSize.y];
		gradient.computeInterpolation(gradientArray, clampedSize.y, begin, end);

		Point i;
		auto gradientIt = gradientArray;
		for ( i.y = 0; i.y < clampedSize.y; i.y++ ) {
			auto maxIt = thisIt + clampedSize.x * getNbComponents();
			for ( auto thisIt2 = thisIt; thisIt2 < maxIt; thisIt2 += N1 ) {
				blendingFunctor(*( ( C1* )thisIt2 ), *( gradientIt ));
			}
			gradientIt++;
			thisIt += thisImageOffset;
		}
		//free the buffer
		delete[] gradientArray;
	}



	template<typename T /*= unsigned char*/>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void _Image<T>::_drawRectangle(const Rectangle & rectangle, const GradientLinear<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Vec2<int> size = rectangle.getRightTop() - rectangle.getLeftBottom();
		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<unsigned int> sizeClamped = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * N1;

		Point origin(gradient.getPoint().x * float(size.x), gradient.getPoint().y * float(size.y));
		Math::Vec2<float> v(Math::cos(gradient.getAngleRad()), Math::sin(gradient.getAngleRad()));

		int gradientSize;
		if ( gradient.getLength() == 0 ) 
			gradientSize = size.x * Math::abs(v.x) + size.y * Math::abs(v.y);
		else 
			gradientSize = gradient.getLength();
		
		int gradientSizeMinusOne = gradientSize - 1;

		C2 * gradientArray = new C2[gradientSize];
		gradient.computeInterpolation(gradientArray, gradientSize);

		Point i;
		for ( i.y = 0; i.y < sizeClamped.y; i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = 0; i.x < sizeClamped.x; i.x++ ) {
				auto index = GradientLinear<C2, InterFunc>::computeIndex(i - origin, gradientSizeMinusOne, gradient.getDirection());
				blendingFunctor(*( (C1*) thisIt2 ), gradientArray[index]);
				thisIt2 += N1;
			}
			thisIt += thisImageOffset;
		}
		delete[] gradientArray;
	}






	template<typename T /*= unsigned char*/>
	template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
	void _Image<T>::_drawRectangle(const Rectangle & rectangle, const GradientRadial<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<int> size = rectangle.getRightTop() - rectangle.getLeftBottom();
		Math::Vec2<unsigned int> sizeClamped = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * getNbComponents();


		Point center(gradient.getCenter().x * float(size.x), gradient.getCenter().y * float(size.y));

		int gradientSize = int(Math::max<float>(gradient.getRadius().x * float(size.x), gradient.getRadius().y * float(size.y)));
		int gradientSizeMinusOne = gradientSize - 1;

		C2 * gradientArray = new C2[gradientSize];
		gradient.computeInterpolation(gradientArray, gradientSize);

		Point i;
		for ( i.y = 0; i.y < sizeClamped.y; i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = 0; i.x < sizeClamped.x; i.x++ ) {
				auto index = GradientRadial<C2, InterFunc>::computeIndex(i - center, gradientSizeMinusOne, gradient.getRadius());
				blendingFunctor(*( (C1*) thisIt2 ), gradientArray[index]);
				thisIt2 += N1;
			}
			thisIt += thisImageOffset;
		}
		delete[] gradientArray;
	}




	//////////////////////////////////////////////////////////////////////////


	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc>
	void _Image<T>::drawRectangleR(const Rectangle & rectangle, const ColorFunc & colorFunctorR, const BlendFunc & blendingFunctor) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorR<T>, ColorR<T>>(rectangle, colorFunctorR, blendingFunctor);
		case Format::RGB:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGB<T>, ColorR<T>>(rectangle, colorFunctorR, blendingFunctor);
		case Format::RGBA:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGBA<T>, ColorR<T>>(rectangle, colorFunctorR, blendingFunctor);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc>
	void _Image<T>::drawRectangleRGB(const Rectangle & rectangle, const ColorFunc & colorFunctorRGB, const BlendFunc & blendingFunctor) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorR<T>, ColorRGB<T>>(rectangle, colorFunctorRGB, blendingFunctor);
		case Format::RGB:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGB<T>>(rectangle, colorFunctorRGB, blendingFunctor);
		case Format::RGBA:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGB<T>>(rectangle, colorFunctorRGB, blendingFunctor);
		}
	}

	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc>
	void _Image<T>::drawRectangleRGBA(const Rectangle & rectangle, const ColorFunc & colorFunctorRGBA, const BlendFunc & blendingFunctor) {
		switch ( this -> format ) {
		case Format::R:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorR<T>, ColorRGBA<T>>(rectangle, colorFunctorRGBA, blendingFunctor);
		case Format::RGB:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGB<T>, ColorRGBA<T>>(rectangle, colorFunctorRGBA, blendingFunctor);
		case Format::RGBA:
			return _drawRectangleFunctor<ColorFunc, BlendFunc, ColorRGBA<T>, ColorRGBA<T>>(rectangle, colorFunctorRGBA, blendingFunctor);
		}
	}


	template<typename T /*= unsigned char*/>
	template<typename ColorFunc, typename BlendFunc, typename C1, typename C2>
	void _Image<T>::_drawRectangleFunctor(const Rectangle & rectangle, const ColorFunc & colorFunctor, const BlendFunc & blendingFunctor) {
		constexpr size_t N1 = sizeof(C1) / sizeof(T);
		constexpr size_t N2 = sizeof(C2) / sizeof(T);

		Math::Rectangle<unsigned int> clampedRectangle = clampRectangle(rectangle);
		Math::Vec2<unsigned int> size = clampedRectangle.getRightTop() - clampedRectangle.getLeftBottom();

		auto thisIt = getDatas(clampedRectangle.getLeftBottom().x, clampedRectangle.getLeftBottom().y);
		auto thisImageOffset = this -> size.x * getNbComponents();

		C2 color;
		Math::Vec2<unsigned int> i;
		for ( i.y = clampedRectangle.getBottom(); i.y < clampedRectangle.getTop(); i.y++ ) {
			auto thisIt2 = thisIt;
			for ( i.x = clampedRectangle.getLeft(); i.x < clampedRectangle.getRight(); i.x++ ) {
				blendingFunctor(*( ( C1* )thisIt2 ), colorFunctor(i));
				thisIt2 += N1;
			}
			thisIt += thisImageOffset;
		}
			
	}
}
