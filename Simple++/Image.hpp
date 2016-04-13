

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
	_Image<T>::_Image(const T * data, const Math::vec2ui & size, Format format, bool invertY) :
		format(format),
		size(size),
		nbPixels(size.x * size.y)
	{
		assert(this -> nbPixels);			//just in case we putted an empty size
		size_t nbComponents = this -> nbPixels * this -> getNbComponents();
		this -> buffer = new T[nbComponents];

		if ( invertY ) {
			//Copy row per row.
			size_t nbComponentsPerRow = size.x * getNbComponents();
			size_t offset = nbComponentsPerRow * sizeof(T);
			const T * pDescend = data + offset * ( size.y - 1 );
			T * pAscend = this -> buffer;
			for ( unsigned int y = 0; y < size.y; y++ ) {
				Vector<T>::copy(pAscend, pDescend, nbComponentsPerRow);
				pAscend += nbComponentsPerRow;
				pDescend -= nbComponentsPerRow;
			}
		} else {
			//Copy the whole data
			Vector<T>::copy(this -> buffer, data, nbComponents);
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
	void _Image<T>::setDatas(const T * data, const Math::vec2ui & size, Format format, bool invertY) {
		this -> size = size;
		this -> nbPixels = size.x * size.y;
		this -> format = format;
		size_t nbComponents = this -> nbPixels * this -> getNbComponents();

		assert(this -> nbPixels);			//just in case we putted an empty size
		delete [] this -> buffer;
		this -> buffer = new T[nbComponents];


		if ( invertY ) {
			//Copy row per row.
			size_t nbComponentsPerLine = size.x * getNbComponents();
			size_t offset = nbComponentsPerLine * sizeof(T);
			const T * pDescend = data + offset * ( size.y - 1 );
			T * pAscend = this -> buffer;
			for ( unsigned int y = 0; y < size.y; y++ ) {
				Vector<T>::copy(pAscend, pDescend, nbComponentsPerLine);
				pAscend += nbComponentsPerLine;
				pDescend -= nbComponentsPerLine;
			}
		} else {
			//Copy the whole data
			Vector<T>::copy(this -> buffer, data, nbComponents);
		}
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
	void _Image<T>::fill(const T * color) {
		switch ( this -> format ) {
		case Format::R: {			//Blend R -> R
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = *( color + 0 );
				it += getNbComponents();
			}
			break;
		}
		case Format::RGB: {		//Blend RGB -> RGB
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = *( color + 0 );
				*( it + 1 ) = *( color + 1 );
				*( it + 2 ) = *( color + 2 );
				it += getNbComponents();
			}
			break;
		}
		case Format::RGBA: {		//Blend RGB -> RGB
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = *( color + 0 );
				*( it + 1 ) = *( color + 1 );
				*( it + 2 ) = *( color + 2 );
				*( it + 3 ) = *( color + 3 );
				it += getNbComponents();
			}
			break;
		}
		}
	}

	template<typename T>
	void _Image<T>::fill(const T * color, const Rectangle & rectangle) {
		switch ( this -> format ) {
		case Format::R: {			//Blend R -> R
			auto it = this -> buffer + (rectangle.getBottom() * this -> size.x + rectangle.getLeft()) * this -> getNbComponents();
			typename Math::vec2ui::Type width = rectangle.getRight() - rectangle.getLeft();
			size_t nbComponentsPerLineRectangle = getNbComponents() * width;
			size_t nbComponentsPerLine = getNbComponents() * this -> size.x;
			for ( typename Math::vec2ui::Type y = rectangle.getBottom(); y < rectangle.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2+= 1) {
					it2[0] = color[0];
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGB: {		//Blend RGB -> RGB
			auto it = this -> buffer + ( rectangle.getBottom() * this -> size.x + rectangle.getLeft() ) * getNbComponents();
			typename Math::vec2ui::Type width = rectangle.getRight() - rectangle.getLeft();
			size_t nbComponentsPerLineRectangle = getNbComponents() * width;
			size_t nbComponentsPerLine = getNbComponents() * this -> size.x;
			for ( typename Math::vec2ui::Type y = rectangle.getBottom(); y < rectangle.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 3 ) {
					it2[0] = color[0];
					it2[1] = color[1];
					it2[2] = color[2];
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGBA: {		//Blend RGB -> RGB
			auto it = this -> buffer;
			typename Math::vec2ui::Type width = rectangle.getRight() - rectangle.getLeft();
			size_t nbComponentsPerLineRectangle = getNbComponents() * width;
			size_t nbComponentsPerLine = getNbComponents() * this -> size.x;
			for ( typename Math::vec2ui::Type y = rectangle.getBottom(); y < rectangle.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 4 ) {
					it2[0] = color[0];
					it2[1] = color[1];
					it2[2] = color[2];
					it2[3] = color[3];
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		}
	}




	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fill(const ColorR<T> & color) {
		switch ( this -> format ) {
		case Format::R: {		//Blend R -> R
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color;
				it += getNbComponents();
			}
			break;
		}
		case Format::RGB: {	//Blend R -> RGB
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color;
				*( it + 1 ) = color;
				*( it + 2 ) = color;
				it += getNbComponents();
			}
			break;
		}
		case Format::RGBA: {	//Blend R -> RGBA
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color;
				*( it + 1 ) = color;
				*( it + 2 ) = color;
				*( it + 3 ) = _getComponmentMaxValue();
				it += getNbComponents();
			}
			break;
		}
		}
	}


	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fill(const ColorRGB<T> & color) {
		switch ( this -> format ) {
		case Format::R: {		//Blend RGB -> R
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color.r;
				it += getNbComponents();
			}
			break;
		}
		case Format::RGB: {	//Blend RGB -> RGB
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color.r;
				*( it + 1 ) = color.g;
				*( it + 2 ) = color.b;
				it += getNbComponents();
			}
			break;
		}
		case Format::RGBA: {	//Blend RGB -> RGBA
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color.r;
				*( it + 1 ) = color.g;
				*( it + 2 ) = color.b;
				*( it + 3 ) = _getComponmentMaxValue();
				it += getNbComponents();
			}
			break;
		}
		}
	}


	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fill(const ColorRGBA<T> & color) {
		switch ( this -> format ) {
		case Format::R: {		//Blend RGBA -> R
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color.r;
				it += getNbComponents();
			}
			break;
		}
		case Format::RGB: {	//Blend RGBA -> RGB
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color.r;
				*( it + 1 ) = color.g;
				*( it + 2 ) = color.b;
				it += getNbComponents();
			}
			break;
		}
		case Format::RGBA: {	//Blend RGBA -> RGBA
			auto it = this -> buffer;
			for ( size_t i = 0; i < this -> nbPixels; i++ ) {
				*( it + 0 ) = color.r;
				*( it + 1 ) = color.g;
				*( it + 2 ) = color.b;
				*( it + 3 ) = color.a;
				it += getNbComponents();
			}
			break;
		}
		}
	}


	////////////////////

	template<typename T /*= unsigned char*/>
	template<typename Func>
	void _Image<T>::setPixels(Func & functor) {
		return setPixels(functor, Rectangle(0, getSize()));
	}


	template<typename T /*= unsigned char*/>
	template<typename Func>
	void _Image<T>::setPixels(Func & functor, const Rectangle & rectangle) {

		Math::Rectangle<unsigned int> rectangleUI = _clampRectangle(rectangle);
		auto it = getDatas(rectangleUI.getLeft(), rectangleUI.getBottom());
		typename Math::vec2ui::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLine = getNbComponents() * this -> size.x;


		Math::Vec2<typename Math::vec2ui::Type> i;

		switch ( this -> format ) {
		case Format::R: {		//Blend R -> R
			for ( i.y = rectangleUI.getBottom(); i.y < rectangleUI.getTop(); i.y++ ) {
				auto it2 = it;
				for ( i.x = rectangleUI.getLeft(); i.x < rectangleUI.getRight(); i.x++ ) {
					functor(i, ( ColorR<T> * ) it2);
					it2 += 1;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGB: {	//Blend R -> RGB
			for ( i.y = rectangleUI.getBottom(); i.y < rectangleUI.getTop(); i.y++ ) {
				auto it2 = it;
				for ( i.x = rectangleUI.getLeft(); i.x < rectangleUI.getRight(); i.x++ ) {
					functor(i, ( ColorRGB<T> * ) it2);
					it2 += 3;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGBA: {	//Blend R -> RGBA
			for ( i.y = rectangleUI.getBottom(); i.y < rectangleUI.getTop(); i.y++ ) {
				auto it2 = it;
				for ( i.x = rectangleUI.getLeft(); i.x < rectangleUI.getRight(); i.x++ ) {
					functor(i, ( ColorRGBA<T> * ) it2);
					it2 += 4;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		}
	}

	template<typename T /*= unsigned char*/>
	Math::Rectangle<unsigned int> _Image<T>::_clampRectangle(const Rectangle & rectangle) const {
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
	void Graphic::_Image<T>::fill(const ColorR<T> & color, const Rectangle & rectangle) {
		Math::Rectangle<unsigned int> rectangleUI = _clampRectangle(rectangle);
		auto it = getDatas(rectangleUI.getLeft(), rectangleUI.getBottom());
		typename Math::vec2ui::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLineRectangle = getNbComponents() * width;
		size_t nbComponentsPerLine = getNbComponents() * this -> size.x;

		switch ( this -> format ) {
		case Format::R: {		//Blend R -> R
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 1 ) {
					it2[0] = color;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGB: {	//Blend R -> RGB
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 3 ) {
					it2[0] = color;
					it2[1] = color;
					it2[2] = color;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGBA: {	//Blend R -> RGBA
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 4 ) {
					it2[0] = color;
					it2[1] = color;
					it2[2] = color;
					it2[4] = _getComponmentMaxValue();
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		}
	}


	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fill(const ColorRGB<T> & color, const Rectangle & rectangle) {
		Math::Rectangle<unsigned int> rectangleUI = _clampRectangle(rectangle);
		auto it = getDatas(rectangleUI.getLeft(), rectangleUI.getBottom());
		typename Math::vec2ui::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLineRectangle = getNbComponents() * width;
		size_t nbComponentsPerLine = getNbComponents() * this -> size.x;

		switch ( this -> format ) {
		case Format::R: {		//Blend RGB -> R
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 1 ) {
					it2[0] = color.r;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGB: {	//Blend RGB -> RGB
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 3 ) {
					it2[0] = color.r;
					it2[1] = color.g;
					it2[2] = color.b;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGBA: {	//Blend RGB -> RGBA
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 4 ) {
					it2[0] = color.r;
					it2[1] = color.g;
					it2[2] = color.b;
					it2[3] = _getComponmentMaxValue();
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		}
	}


	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::fill(const ColorRGBA<T> & color, const Rectangle & rectangle) {
		Math::Rectangle<unsigned int> rectangleUI = _clampRectangle(rectangle);
		auto it = getDatas(rectangleUI.getLeft(), rectangleUI.getBottom());
		typename Math::vec2ui::Type width = rectangleUI.getRight() - rectangleUI.getLeft();
		size_t nbComponentsPerLineRectangle = getNbComponents() * width;
		size_t nbComponentsPerLine = getNbComponents() * this -> size.x;
		switch ( this -> format ) {
		case Format::R: {		//Blend RGBA -> R
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 1 ) {
					it2[0] = color.r;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGB: {	//Blend RGBA -> RGB
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 3 ) {
					it2[0] = color.r;
					it2[1] = color.g;
					it2[2] = color.b;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		case Format::RGBA: {	//Blend RGBA -> RGBA
			for ( typename Math::vec2ui::Type y = rectangleUI.getBottom(); y < rectangleUI.getTop(); y++ ) {
				auto maxIt = it + nbComponentsPerLineRectangle;
				for ( auto it2 = it; it2 < maxIt; it2 += 4 ) {
					it2[0] = color.r;
					it2[1] = color.g;
					it2[2] = color.b;
					it2[3] = color.a;
				}
				it += nbComponentsPerLine;
			}
			break;
		}
		}
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage) {
		drawImage(point, Rectangle(Math::Vec2<typename Point::Type>::null, image.getSize()), image, maskPoint, maskImage);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const _Image<T> & image, const _Image<T> & maskImage) {
		drawImage(point, Rectangle(Math::Vec2<typename Point::Type>::null, image.getSize()), image, Point::null, maskImage);
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const _Image<T> & image) {
		drawImage(point, Rectangle(Math::Vec2<typename Point::Type>::null, image.getSize()), image);
	}


	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorR<T> & color, const _Image<T> & maskImage) {
		drawImage(point, color, Rectangle(Math::Vec2<typename Point::Type>::null, maskImage.getSize()), maskImage);
	}

	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGB<T> & color, const _Image<T> & maskImage) {
		drawImage(point, color, Rectangle(Math::Vec2<typename Point::Type>::null, maskImage.getSize()), maskImage);
	}

	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGBA<T> & color, const _Image<T> & maskImage) {
		drawImage(point, color, Rectangle(Math::Vec2<typename Point::Type>::null, maskImage.getSize()), maskImage);
	}



	template<typename T /*= unsigned char*/>
	void _Image<T>::drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image) {
		
		//Rectangle is signed, check if the bottom left is positive.
		//rectangle.setLeft(Math::max(rectangle.getLeft(), 0));
		//rectangle.setBottom(Math::max(rectangle.getBottom(), 0));


		Point begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Point otherImageBegin;
		Point size;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x , rectangle.getRight() - rectangle.getLeft() + point.x);
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
		} else if ( point.y >(typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}

	

		//verification if the given rectangle is correctly inside the given image
		//size.x = Math::min<typename Point::Type>(size.x, image.getSize().x - rectangle.getLeft());
		//size.y = Math::min<typename Point::Type>(size.y, image.getSize().y - rectangle.getTop());

		//end.x = Math::clamp<typename Point::Type>(point.x + image.size.x, 0, this -> size.x);	//0 <= endX <= size.x
		//end.y = Math::clamp<typename Point::Type>(point.y + image.size.y, 0, this -> size.y);	//0 <= endY <= size.y

		//Point size(end.x - begin.x, end.y - begin.y);
		//Point end(begin + size);
		//Point otherImageEnd(otherImageBegin + size);


		switch ( this -> format ) {
		case Format::R: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 1;
			auto thisImageOffset = this -> size.x * 1;


			switch ( image.getFormat() ) {
			case Format::R: {			//Blend R -> R
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 1;
				auto otherImageOffset = image.size.x * 1;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					Vector<T>::copy(thisIt, otherIt, size.x * 1);
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			case Format::RGB: {		//Blend RGB -> R
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 3;
				auto otherImageOffset = image.size.x * 3;


				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBtoR(thisIt2, otherIt2);

						thisIt2 += 1;
						otherIt2 += 3;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			case Format::RGBA: {		//Blend RGBA -> R
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 4;
				auto otherImageOffset = image.size.x * 4;


				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBAtoR(thisIt2, otherIt2);

						thisIt2 += 1;
						otherIt2 += 4;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			}

			break;
		}
		case Format::RGB: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 3;
			auto thisImageOffset = this -> size.x * 3;



			switch ( image.getFormat() ) {
			case Format::R: {			//Blend R -> RGB
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 1;
				auto otherImageOffset = image.size.x * 1;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRtoRGB(thisIt2, otherIt2);

						thisIt2 += 3;
						otherIt2 += 1;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			case Format::RGB: {		//Blend RGB -> RGB
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 3;
				auto otherImageOffset = image.size.x * 3;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					Vector<T>::copy(thisIt, otherIt, size.x * 3);
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}


				break;
			}
			case Format::RGBA: {		//Blend RGBA -> RGB
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 4;
				auto otherImageOffset = image.size.x * 4;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBAtoRGB(thisIt2, otherIt2);
						thisIt2 += 3;
						otherIt2 += 4;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			}


			break;
		}
		case Format::RGBA: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 4;
			auto thisImageOffset = this -> size.x * 4;

			switch ( image.getFormat() ) {
			case Format::R: {			//Blend R -> RGBA
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 1;
				auto otherImageOffset = image.size.x * 1;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRtoRGBA(thisIt2, otherIt2);

						thisIt2 += 4;
						otherIt2 += 1;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			case Format::RGB: {		//Blend RGB -> RGBA
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 3;
				auto otherImageOffset = image.size.x * 3;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBtoRGBA(thisIt2, otherIt2);

						thisIt2 += 4;
						otherIt2 += 3;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}


				break;
			}
			case Format::RGBA: {		//Blend RGBA -> RGBA
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 4;
				auto otherImageOffset = image.size.x * 4;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBAtoRGBA(thisIt2, otherIt2);
						thisIt2 += 4;
						otherIt2 += 4;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
				}

				break;
			}
			}


			break;
		}
		}


	}


















	template<typename T>
	template<typename Func>
	void _Image<T>::drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, Func blendingFunc) {
		Point begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Point otherImageBegin;
		Point size;

		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x);
		} else if ( point.x >(typename Point::Type) this -> size.x ) {
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
		} else if ( point.y >(typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}

		//Point end(begin + size);
		//Point otherImageEnd(otherImageBegin + size);


		auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * this -> getNbComponents();
		auto thisImageOffset = this -> size.x * getNbComponents();



		auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * (unsigned char) image.getFormat();
		auto otherImageOffset = image.size.x * (unsigned char) image.getFormat();

		Point i;
		for ( i.y = 0; i.y < size.y; i.y++ ) {
			auto thisIt2 = thisIt;
			auto otherIt2 = otherIt;
			for ( i.x = 0; i.x < size.x; i.x++ ) {
				blendingFunc(this -> format, image.getFormat(), thisIt2, otherIt2);

				thisIt2 += this -> getNbComponents();
				otherIt2 += (unsigned char) image.getFormat();
			}
			thisIt += thisImageOffset;
			otherIt += otherImageOffset;
		}

	}














	template<typename T /*= unsigned char */>
	void _Image<T>::drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage) {
		Point begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Point otherImageBegin;
		Point maskBegin;
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
		} else if ( point.x >(typename Point::Type) this -> size.x ) {
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
		} else if ( point.y >(typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, maskImage.getSize().y - maskPoint.y);
		}

		


		auto maskIt = maskImage.buffer + ( maskImage.size.x * maskBegin.y + maskBegin.x ) * (unsigned char) maskImage.format;
		auto maskImageOffset = maskImage.size.x * (unsigned char) maskImage.format;







		switch ( this -> format ) {
		case Format::R: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 1;
			auto thisImageOffset = this -> size.x * 1;


			switch ( image.getFormat() ) {
			case Format::R: {			//Blend R -> R
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x) * 1;
				auto otherImageOffset = image.size.x * 1;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRtoR(thisIt2, otherIt2, maskIt2);

						thisIt2 += 1;
						otherIt2 += 1;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			case Format::RGB: {		//Blend RGB -> R
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 3;
				auto otherImageOffset = image.size.x * 3;


				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBtoR(thisIt2, otherIt2, maskIt2);

						thisIt2 += 1;
						otherIt2 += 3;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			case Format::RGBA: {		//Blend RGBA -> R
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 4;
				auto otherImageOffset = image.size.x * 4;


				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBAtoR(thisIt2, otherIt2, maskIt2);

						thisIt2 += 1;
						otherIt2 += 4;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			}

			break;
		}
		case Format::RGB: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 3;
			auto thisImageOffset = this -> size.x * 3;



			switch ( image.getFormat() ) {
			case Format::R: {			//Blend R -> RGB
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 1;
				auto otherImageOffset = image.size.x * 1;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRtoRGB(thisIt2, otherIt2, maskIt2);

						thisIt2 += 3;
						otherIt2 += 1;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			case Format::RGB: {		//Blend RGB -> RGB
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 3;
				auto otherImageOffset = image.size.x * 3;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBtoRGB(thisIt2, otherIt2, maskIt2);

						thisIt2 += 3;
						otherIt2 += 3;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}


				break;
			}
			case Format::RGBA: {		//Blend RGBA -> RGB
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 4;
				auto otherImageOffset = image.size.x * 4;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBAtoRGB(thisIt2, otherIt2, maskIt2);

						thisIt2 += 3;
						otherIt2 += 4;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			}


			break;
		}
		case Format::RGBA: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 4;
			auto thisImageOffset = this -> size.x * 4;

			switch ( image.getFormat() ) {
			case Format::R: {			//Blend R -> RGBA
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 1;
				auto otherImageOffset = image.size.x * 1;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRtoRGBA(thisIt2, otherIt2, maskIt2);

						thisIt2 += 4;
						otherIt2 += 1;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			case Format::RGB: {		//Blend RGB -> RGBA
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 3;
				auto otherImageOffset = image.size.x * 3;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBtoRGBA(thisIt2, otherIt2, maskIt2);

						thisIt2 += 4;
						otherIt2 += 3;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}


				break;
			}
			case Format::RGBA: {		//Blend RGBA -> RGBA
				auto otherIt = image.buffer + ( image.size.x * otherImageBegin.y + otherImageBegin.x ) * 4;
				auto otherImageOffset = image.size.x * 4;

				Point i;
				for ( i.y = 0; i.y < size.y; i.y++ ) {
					auto thisIt2 = thisIt;
					auto otherIt2 = otherIt;
					auto maskIt2 = maskIt;
					for ( i.x = 0; i.x < size.x; i.x++ ) {
						_blendPixelRGBAtoRGBA(thisIt2, otherIt2, maskIt2);

						thisIt2 += 4;
						otherIt2 += 4;
						maskIt2 += (unsigned char) maskImage.format;
					}
					thisIt += thisImageOffset;
					otherIt += otherImageOffset;
					maskIt += maskImageOffset;
				}

				break;
			}
			}


			break;
		}
		}

	}





	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage) {

		//Rectangle is signed, check if the bottom left is positive.
		//rectangle.setLeft(Math::max(rectangle.getLeft(), 0));
		//rectangle.setBottom(Math::max(rectangle.getBottom(), 0));


		Point begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Point otherImageBegin;
		Point size;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
			size.x = Math::min<typename Point::Type>(this -> size.x, rectangle.getRight() - rectangle.getLeft() + point.x);
		} else if ( point.x >(typename Point::Type) this -> size.x ) {
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
		} else if ( point.y >(typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
			size.y = Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom());
		}





		auto otherIt = maskImage.buffer + ( maskImage.size.x * otherImageBegin.y + otherImageBegin.y ) * (unsigned char) maskImage.format;
		auto otherImageOffset = maskImage.size.x * (unsigned char) maskImage.format;

		switch ( this -> format ) {
		case Format::R: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 1;
			auto thisImageOffset = this -> size.x * 1;



			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRGBAtoR(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 1;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		case Format::RGB: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 3;
			auto thisImageOffset = this -> size.x * 3;



			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRGBAtoRGB(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 3;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		case Format::RGBA: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 4;
			auto thisImageOffset = this -> size.x * 4;

			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRGBAtoRGBA(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 4;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		}
	}















	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage) {

		//Rectangle is signed, check if the bottom left is positive.
		//rectangle.setLeft(Math::max(rectangle.getLeft(), 0));
		//rectangle.setBottom(Math::max(rectangle.getBottom(), 0));


		Point begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Point otherImageBegin;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
		} else if ( point.x >(typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
		} else if ( point.y >(typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
		}

		Point size(
			Math::min<typename Point::Type>(this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft()),
			Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom()));


		auto otherIt = maskImage.buffer + ( maskImage.size.x * otherImageBegin.y + otherImageBegin.y ) * (unsigned char) maskImage.format;
		auto otherImageOffset = maskImage.size.x * (unsigned char) maskImage.format;

		switch ( this -> format ) {
		case Format::R: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 1;
			auto thisImageOffset = this -> size.x * 1;



			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRtoR(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 1;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		case Format::RGB: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 3;
			auto thisImageOffset = this -> size.x * 3;



			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRtoRGB(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 3;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		case Format::RGBA: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 4;
			auto thisImageOffset = this -> size.x * 4;

			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRtoRGBA(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 4;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		}
	}













	template<typename T /*= unsigned char*/>
	void Graphic::_Image<T>::drawImage(const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage) {

		//Rectangle is signed, check if the bottom left is positive.
		//rectangle.setLeft(Math::max(rectangle.getLeft(), 0));
		//rectangle.setBottom(Math::max(rectangle.getBottom(), 0));


		Point begin;			//0 <= beginX <= size.x && 0 <= beginY <= size.y
		Point otherImageBegin;
		if ( point.x < 0 ) {
			begin.x = 0;
			otherImageBegin.x = -point.x + rectangle.getLeft();
		} else if ( point.x >(typename Point::Type) this -> size.x ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.x = point.x;
			otherImageBegin.x = rectangle.getLeft();
		}

		if ( point.y < 0 ) {
			begin.y = 0;
			otherImageBegin.y = -point.y + rectangle.getBottom();
		} else if ( point.y >(typename Point::Type) this -> size.y ) {
			return;			//We are drawing outside, nothing will be changed.
		} else {
			begin.y = point.y;
			otherImageBegin.y = rectangle.getBottom();
		}

		Point size(
			Math::min<typename Point::Type>(this -> size.x - point.x, rectangle.getRight() - rectangle.getLeft()),
			Math::min<typename Point::Type>(this -> size.y - point.y, rectangle.getTop() - rectangle.getBottom()));


		auto otherIt = maskImage.buffer + ( maskImage.size.x * otherImageBegin.y + otherImageBegin.y ) * (unsigned char) maskImage.format;
		auto otherImageOffset = maskImage.size.x * (unsigned char) maskImage.format;

		switch ( this -> format ) {
		case Format::R: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 1;
			auto thisImageOffset = this -> size.x * 1;



			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRGBtoR(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 1;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		case Format::RGB: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 3;
			auto thisImageOffset = this -> size.x * 3;



			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRGBtoRGB(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 3;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		case Format::RGBA: {
			auto thisIt = this -> buffer + ( this -> size.x * begin.y + begin.x ) * 4;
			auto thisImageOffset = this -> size.x * 4;

			Point i;
			for ( i.y = 0; i.y < size.y; i.y++ ) {
				auto thisIt2 = thisIt;
				auto otherIt2 = otherIt;
				for ( i.x = 0; i.x < size.x; i.x++ ) {
					_blendPixelRGBtoRGBA(thisIt2, (const T*) &color, otherIt2);

					thisIt2 += 4;
					otherIt2 += (unsigned char) maskImage.format;
				}
				thisIt += thisImageOffset;
				otherIt += otherImageOffset;
			}


			break;
		}
		}
	}











	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRGBAtoRGBA(C * pixelDest, const C * pixelSource) {
		float alpha = float(*( pixelSource + 3 )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;


		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + *( pixelSource + 0 ) * alpha;
		*( pixelDest + 1 ) = *( pixelDest + 1 ) * oneMinusAlpha + *( pixelSource + 1 ) * alpha;
		*( pixelDest + 2 ) = *( pixelDest + 2 ) * oneMinusAlpha + *( pixelSource + 2 ) * alpha;
		*( pixelDest + 3 ) = *( pixelDest + 3 ) * oneMinusAlpha + *( pixelSource + 3 );
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource) {
		unsigned short alpha = pixelSource[3];
		unsigned short oneMinusAlpha = 256 - alpha;


		pixelDest[0] = ( ( (unsigned short) pixelDest[0] ) * oneMinusAlpha + ( (unsigned short) pixelSource[0] ) * alpha ) >> 8;
		pixelDest[1] = ( ( (unsigned short) pixelDest[1] ) * oneMinusAlpha + ( (unsigned short) pixelSource[1] ) * alpha ) >> 8;
		pixelDest[2] = ( ( (unsigned short) pixelDest[2] ) * oneMinusAlpha + ( (unsigned short) pixelSource[2] ) * alpha ) >> 8;
		pixelDest[3] = (( ( (unsigned short) pixelDest[3] ) * oneMinusAlpha ) >> 8 )+ ( (unsigned short) pixelSource[3] );
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoRGBA(float * pixelDest, const float * pixelSource) {
		float alpha = *( pixelSource + 3 );
		float oneMinusAlpha = 1.0f - alpha;


		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + *( pixelSource + 0 ) * alpha;
		*( pixelDest + 1 ) = *( pixelDest + 1 ) * oneMinusAlpha + *( pixelSource + 1 ) * alpha;
		*( pixelDest + 2 ) = *( pixelDest + 2 ) * oneMinusAlpha + *( pixelSource + 2 ) * alpha;
		*( pixelDest + 3 ) = *( pixelDest + 3 ) * oneMinusAlpha + *( pixelSource + 3 );
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoRGBA(double * pixelDest, const double * pixelSource) {
		double alpha = *( pixelSource + 3 );
		double oneMinusAlpha = 1.0 - alpha;


		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + *( pixelSource + 0 ) * alpha;
		*( pixelDest + 1 ) = *( pixelDest + 1 ) * oneMinusAlpha + *( pixelSource + 1 ) * alpha;
		*( pixelDest + 2 ) = *( pixelDest + 2 ) * oneMinusAlpha + *( pixelSource + 2 ) * alpha;
		*( pixelDest + 3 ) = *( pixelDest + 3 ) * oneMinusAlpha + *( pixelSource + 3 );
	}



	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRGBtoRGBA(C * pixelDest, const C * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 1 );
		*( pixelDest + 2 ) = *( pixelSource + 2 );
		*( pixelDest + 3 ) = C(-1);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBtoRGBA(float * pixelDest, const float * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 1 );
		*( pixelDest + 2 ) = *( pixelSource + 2 );
		*( pixelDest + 3 ) = 1.0f;
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBtoRGBA(double * pixelDest, const double * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 1 );
		*( pixelDest + 2 ) = *( pixelSource + 2 );
		*( pixelDest + 3 ) = 1.0;
	}


	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRtoRGBA(C * pixelDest, const C * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 0 );
		*( pixelDest + 2 ) = *( pixelSource + 0 );
		*( pixelDest + 3 ) = C(-1);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRtoRGBA(float * pixelDest, const float * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 0 );
		*( pixelDest + 2 ) = *( pixelSource + 0 );
		*( pixelDest + 3 ) = 1.0f;
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRtoRGBA(double * pixelDest, const double * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 0 );
		*( pixelDest + 2 ) = *( pixelSource + 0 );
		*( pixelDest + 3 ) = 1.0;
	}


	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRtoRGB(C * pixelDest, const C * pixelSource) {

		*( pixelDest + 0 ) = *( pixelSource + 0 );
		*( pixelDest + 1 ) = *( pixelSource + 0 );
		*( pixelDest + 2 ) = *( pixelSource + 0 );
	}

	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRGBAtoRGB(C * pixelDest, const C * pixelSource) {
		float alpha = float(*( pixelSource + 3 )) / float(T(-1));
		float oneMinusAlpha = 1.0f - alpha;

		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + *( pixelSource + 0 ) * alpha;
		*( pixelDest + 1 ) = *( pixelDest + 1 ) * oneMinusAlpha + *( pixelSource + 1 ) * alpha;
		*( pixelDest + 2 ) = *( pixelDest + 2 ) * oneMinusAlpha + *( pixelSource + 2 ) * alpha;
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource) {
		unsigned short alpha = pixelSource[3];
		unsigned short oneMinusAlpha = 256 - alpha;


		pixelDest[0] = ( ( (unsigned short) pixelDest[0] ) * oneMinusAlpha + ( (unsigned short) pixelSource[0] ) * alpha ) >> 8;
		pixelDest[1] = ( ( (unsigned short) pixelDest[1] ) * oneMinusAlpha + ( (unsigned short) pixelSource[1] ) * alpha ) >> 8;
		pixelDest[2] = ( ( (unsigned short) pixelDest[2] ) * oneMinusAlpha + ( (unsigned short) pixelSource[2] ) * alpha ) >> 8;
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoRGB(float * pixelDest, const float * pixelSource) {
		float alpha = *( pixelSource + 3 );
		float oneMinusAlpha = 1.0f - alpha;

		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + *( pixelSource + 0 ) * alpha;
		*( pixelDest + 1 ) = *( pixelDest + 1 ) * oneMinusAlpha + *( pixelSource + 1 ) * alpha;
		*( pixelDest + 2 ) = *( pixelDest + 2 ) * oneMinusAlpha + *( pixelSource + 2 ) * alpha;
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoRGB(double * pixelDest, const double * pixelSource) {
		double alpha = *( pixelSource + 3 );
		double oneMinusAlpha = 1.0 - alpha;

		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + *( pixelSource + 0 ) * alpha;
		*( pixelDest + 1 ) = *( pixelDest + 1 ) * oneMinusAlpha + *( pixelSource + 1 ) * alpha;
		*( pixelDest + 2 ) = *( pixelDest + 2 ) * oneMinusAlpha + *( pixelSource + 2 ) * alpha;
	}




	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRGBAtoR(C * pixelDest, const C * pixelSource) {
		float alpha = float(*( pixelSource + 3 )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		unsigned int sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );

		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + (sum / 3) * alpha;
	}



	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoR(unsigned char * pixelDest, const unsigned char * pixelSource) {
		unsigned short alpha = *( pixelSource + 3 );
		unsigned short oneMinusAlpha = 256 - alpha;
		unsigned short sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );

		*( pixelDest + 0 ) = (*( pixelDest + 0 ) * oneMinusAlpha + ( sum / 3 ) * alpha) >> 8;
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoR(float * pixelDest, const float * pixelSource) {
		auto alpha = *( pixelSource + 3 );
		auto oneMinusAlpha = 1.0f - alpha;
		auto sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );

		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + (sum / 3.0f) * alpha;
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBAtoR(double * pixelDest, const double * pixelSource) {
		auto alpha = *( pixelSource + 3 );
		auto oneMinusAlpha = 1.0 - alpha;
		auto sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );

		*( pixelDest + 0 ) = *( pixelDest + 0 ) * oneMinusAlpha + ( sum / 3.0 ) * alpha;

	}


	template<typename T /*= unsigned char*/>
	template<typename C>
	void _Image<T>::_blendPixelRGBtoR(C * pixelDest, const C * pixelSource) {
		unsigned int sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );
		*( pixelDest ) = C(sum / 3);
	}

	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBtoR(unsigned char * pixelDest, const unsigned char * pixelSource) {
		unsigned short sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );
		*( pixelDest ) = unsigned char(sum / 3);
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBtoR(float * pixelDest, const float * pixelSource) {
		auto sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );
		*( pixelDest ) = float(sum / 3.0f);
	}


	template<typename T /*= unsigned char*/>
	void _Image<T>::_blendPixelRGBtoR(double * pixelDest, const double * pixelSource) {
		auto sum = *( pixelSource + 0 ) + *( pixelSource + 1 ) + *( pixelSource + 2 );
		*( pixelDest ) = double(sum / 3.0);
	}

	/*
	template<typename T / *= unsigned char* />
	void _Image<T>::drawText(const Font & font, const Point & point, const UTF8String & text) {
		



	}
	*/





	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRtoR(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = float(*( maskPixel )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		*( pixelDest ) = float(*( pixelDest )) * oneMinusAlpha + float(*( pixelSource )) * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoR(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned short alpha = *( maskPixel );
		unsigned short oneMinusAlpha = 256 - alpha;

		*( pixelDest ) = ( *(pixelDest) * oneMinusAlpha + *(pixelSource) * alpha ) >> 8;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoR(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel );
		float oneMinusAlpha = float(1.0) - alpha;

		*( pixelDest ) = *(pixelDest) * oneMinusAlpha + *(pixelSource) * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoR(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel );
		double oneMinusAlpha = double(1.0) - alpha;

		*( pixelDest ) = *(pixelDest) * oneMinusAlpha + *(pixelSource) * alpha;
	}






	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRtoRGB(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = float(*( maskPixel )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		float tmp = float(pixelSource[0]) * alpha;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + tmp;
		pixelDest[1] = float(pixelDest[1]) * oneMinusAlpha + tmp;
		pixelDest[2] = float(pixelDest[2]) * oneMinusAlpha + tmp;

	}

	template<typename T>
	void _Image<T>::_blendPixelRtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned short alpha = *( maskPixel );
		unsigned short oneMinusAlpha = 256 - alpha;

		pixelDest[0] = ( ( pixelDest[0] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
		pixelDest[1] = ( ( pixelDest[1] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
		pixelDest[2] = ( ( pixelDest[2] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoRGB(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel );
		float oneMinusAlpha = 1.0f - alpha;

		float tmp = pixelSource[0] * alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + tmp;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + tmp;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + tmp;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoRGB(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel );
		double oneMinusAlpha = 1.0 - alpha;

		double tmp = pixelSource[0] * alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + tmp;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + tmp;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + tmp;
	}




	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRtoRGBA(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = float(*( maskPixel )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		float tmp = float(pixelSource[0]) * alpha;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + tmp;
		pixelDest[1] = float(pixelDest[1]) * oneMinusAlpha + tmp;
		pixelDest[2] = float(pixelDest[2]) * oneMinusAlpha + tmp;
		pixelDest[3] = float(pixelDest[3]) * oneMinusAlpha + *( maskPixel );
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned short alpha = *( maskPixel );
		unsigned short oneMinusAlpha = 256 - alpha;

		pixelDest[0] = ( ( pixelDest[0] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
		pixelDest[1] = ( ( pixelDest[1] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
		pixelDest[2] = ( ( pixelDest[2] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
		pixelDest[3] = ( ( pixelDest[3] ) * oneMinusAlpha ) >> 8 + alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoRGBA(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel );
		float oneMinusAlpha = 1.0f - alpha;

		float tmp = pixelSource[0] * alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + tmp;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + tmp;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + tmp;
		pixelDest[3] = pixelDest[3] * oneMinusAlpha + alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRtoRGBA(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel );
		double oneMinusAlpha = 1.0 - alpha;

		double tmp = pixelSource[0] * alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + tmp;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + tmp;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + tmp;
		pixelDest[3] = pixelDest[3] * oneMinusAlpha + alpha;
	}











	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRGBtoR(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = float(*( maskPixel )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		float sum = ( float(pixelSource[0]) + float(pixelSource[1]) + float(pixelSource[2]) ) / 3.0f;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + sum * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoR(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned short alpha = *( maskPixel );
		unsigned short oneMinusAlpha = 256 - alpha;
		unsigned short sum = pixelSource[0] + pixelSource[1] + pixelSource[2];

		pixelDest[0] = ( ( pixelDest[0] ) * oneMinusAlpha + (sum / 3) * alpha ) >> 8;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoR(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel );
		float oneMinusAlpha = 1.0f - alpha;

		float sum = ( pixelSource[0] + pixelSource[1] + pixelSource[2] ) / 3.0f;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + sum * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoR(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel );
		double oneMinusAlpha = 1.0 - alpha;
		double sum = ( pixelSource[0] + pixelSource[1] + pixelSource[2] ) / 3.0;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + tmp * alpha;
	}










	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRGBtoRGB(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = float(*( maskPixel )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + float(pixelSource[0]) * alpha;
		pixelDest[1] = float(pixelDest[1]) * oneMinusAlpha + float(pixelSource[1]) * alpha;
		pixelDest[2] = float(pixelDest[2]) * oneMinusAlpha + float(pixelSource[2]) * alpha;

	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned short alpha = *( maskPixel );
		unsigned short oneMinusAlpha = 256 - alpha;

		pixelDest[0] = ( pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha ) >> 8;
		pixelDest[1] = ( pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha ) >> 8;
		pixelDest[2] = ( pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha ) >> 8;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoRGB(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel );
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoRGB(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel );
		double oneMinusAlpha = 1.0 - alpha;
		
		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
	}









	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRGBtoRGBA(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = float(*( maskPixel )) / float(C(-1));
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + float(pixelSource[0]) * alpha;
		pixelDest[1] = float(pixelDest[1]) * oneMinusAlpha + float(pixelSource[1]) * alpha;
		pixelDest[2] = float(pixelDest[2]) * oneMinusAlpha + float(pixelSource[2]) * alpha;
		pixelDest[3] = float(pixelDest[3]) * oneMinusAlpha + *( maskPixel );
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned short alpha = *( maskPixel );
		unsigned short oneMinusAlpha = 256 - alpha;

		pixelDest[0] = ( ( pixelDest[0] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 8;
		pixelDest[1] = ( ( pixelDest[1] ) * oneMinusAlpha + ( pixelSource[1] ) * alpha ) >> 8;
		pixelDest[2] = ( ( pixelDest[2] ) * oneMinusAlpha + ( pixelSource[2] ) * alpha ) >> 8;
		pixelDest[3] = ( ( pixelDest[3] ) * oneMinusAlpha ) >> 8 + alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoRGBA(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel );
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
		pixelDest[3] = pixelDest[3] * oneMinusAlpha + alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBtoRGBA(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel );
		double oneMinusAlpha = 1.0 - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
		pixelDest[3] = pixelDest[3] * oneMinusAlpha + alpha;
	}











	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRGBAtoR(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = (float(*( maskPixel )) / float(C(-1))) * ( float(pixelSource[3]) / float(C(-1)) );
		float oneMinusAlpha = 1.0f - alpha;

		float sum = ( float(pixelSource[0]) + float(pixelSource[1]) + float(pixelSource[2]) ) / 3.0f;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + sum * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoR(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned int alpha = (*( maskPixel ) * pixelSource[3]);
		unsigned int oneMinusAlpha = 65536 - alpha;
		unsigned int sum = pixelSource[0] + pixelSource[1] + pixelSource[2];

		pixelDest[0] = ( ( pixelDest[0] ) * oneMinusAlpha + ( sum / 3 ) * alpha ) >> 16;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoR(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel ) * pixelSource[3];
		float oneMinusAlpha = 1.0f - alpha;
		float sum = ( pixelSource[0] + pixelSource[1] + pixelSource[2] ) / 3.0f;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + sum * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoR(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel ) * pixelSource[3];
		double oneMinusAlpha = 1.0 - alpha;
		double sum = ( pixelSource[0] + pixelSource[1] + pixelSource[2] ) / 3.0;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + tmp * alpha;
	}














	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRGBAtoRGB(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = (float(*( maskPixel )) / float(C(-1))) * ( float(pixelSource[3]) / float(C(-1)) );
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + float(pixelSource[0]) * alpha;
		pixelDest[1] = float(pixelDest[1]) * oneMinusAlpha + float(pixelSource[1]) * alpha;
		pixelDest[2] = float(pixelDest[2]) * oneMinusAlpha + float(pixelSource[2]) * alpha;

	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned int alpha = *( maskPixel ) * pixelSource[3];
		unsigned int oneMinusAlpha = 65536 - alpha;

		pixelDest[0] = ( pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha ) >> 16;
		pixelDest[1] = ( pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha ) >> 16;
		pixelDest[2] = ( pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha ) >> 16;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoRGB(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel ) * pixelSource[3];
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoRGB(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel ) * pixelSource[3];
		double oneMinusAlpha = 1.0 - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
	}










	template<typename T>
	template<typename C>
	void _Image<T>::_blendPixelRGBAtoRGBA(C * pixelDest, const C * pixelSource, const C * maskPixel) {
		float alpha = (float(*( maskPixel )) / float(C(-1))) * ( float(pixelSource[3]) / float(C(-1)) );
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = float(pixelDest[0]) * oneMinusAlpha + float(pixelSource[0]) * alpha;
		pixelDest[1] = float(pixelDest[1]) * oneMinusAlpha + float(pixelSource[1]) * alpha;
		pixelDest[2] = float(pixelDest[2]) * oneMinusAlpha + float(pixelSource[2]) * alpha;
		pixelDest[3] = float(pixelDest[3]) * oneMinusAlpha + alpha * float(C(-1));
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel) {
		unsigned int alpha = *( maskPixel ) * pixelSource[3];
		unsigned int oneMinusAlpha = 65536 - alpha;

		pixelDest[0] = ( ( pixelDest[0] ) * oneMinusAlpha + ( pixelSource[0] ) * alpha ) >> 16;
		pixelDest[1] = ( ( pixelDest[1] ) * oneMinusAlpha + ( pixelSource[1] ) * alpha ) >> 16;
		pixelDest[2] = ( ( pixelDest[2] ) * oneMinusAlpha + ( pixelSource[2] ) * alpha ) >> 16;
		pixelDest[3] = ( ( pixelDest[3] ) * oneMinusAlpha ) >> 16 + alpha >> 8;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoRGBA(float * pixelDest, const float * pixelSource, const float * maskPixel) {
		float alpha = *( maskPixel ) * pixelSource[3];
		float oneMinusAlpha = 1.0f - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
		pixelDest[3] = pixelDest[3] * oneMinusAlpha + alpha;
	}

	template<typename T>
	void _Image<T>::_blendPixelRGBAtoRGBA(double * pixelDest, const double * pixelSource, const double * maskPixel) {
		double alpha = *( maskPixel ) * pixelSource[3];
		double oneMinusAlpha = 1.0 - alpha;

		pixelDest[0] = pixelDest[0] * oneMinusAlpha + pixelSource[0] * alpha;
		pixelDest[1] = pixelDest[1] * oneMinusAlpha + pixelSource[1] * alpha;
		pixelDest[2] = pixelDest[2] * oneMinusAlpha + pixelSource[2] * alpha;
		pixelDest[3] = pixelDest[3] * oneMinusAlpha + alpha;
	}












	template<typename T>
	T _Image<T>::_getComponmentMaxValue() {
		return T(-1);
	}


	template<>
	float _Image<float>::_getComponmentMaxValue() {
		return 1.0f;
	}

	template<>
	double _Image<double>::_getComponmentMaxValue() {
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
		return _applyFilter(filter, convolutionMode, color);
	}



	template<typename T>
	template<int N>
	_Image<T> _Image<T>::_applyFilter(const float(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		return _applyFilterf<float, N>(filter, convolutionMode, color);
	}

	template<typename T>
	template< int N>
	_Image<T> _Image<T>::_applyFilter(const double(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		return _applyFilterf<double, N>(filter, convolutionMode, color);
	}


	template<typename T>
	template<typename C, int N>
	_Image<T> _Image<T>::_applyFilter(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		assert(N % 2 == 1);

		typename Math::vec2ui::Type NHalfed = ( N / 2 );
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
		imageBorder.fill(color, Rectangle(0, borderSize, borderSize, imageBorder.getSize().y - borderSize ));
		imageBorder.fill(color, Rectangle(imageBorder.getSize().x - borderSize, borderSize, imageBorder.getSize().x, imageBorder.getSize().y - borderSize ));

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
		C divide = 0;
		for ( size_t i = 0; i < N; i++ )
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
					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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

					for ( int i = 0; i < N; i++ ) {
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
	template<typename C, int N>
	_Image<T> _Image<T>::_applyFilterf(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const {
		assert(N % 2 == 1);
		assert((Utility::isSame<T, C>::value));

		typename Math::vec2ui::Type NHalfed = ( N / 2 );
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
					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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

					for ( int i = 0; i < N; i++ ) {
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
					for ( int i = 0; i < N; i++ ) {
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
					otherIt[3] = _getComponmentMaxValue();

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
						otherIt[0] = _getComponmentMaxValue();
						thisIt += getNbComponents();
						otherIt += newImage.getNbComponents();
					}

					break;
				case ConversionMode::Luminance: {
					for ( ; thisIt < maxIt; ) {
						_blendPixelRGBtoR(otherIt, thisIt);
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
					_blendPixelRGBtoRGBA(otherIt, thisIt);
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
						_blendPixelRGBtoR(otherIt, thisIt);
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


	template<typename T>
	template<typename C>
	void _Image<T>::sumComponmentsRGB(const C * destBuffer, const T * inBuffer, size_t numPixels) {

		destBuffer[0] = C(0);

		for ( size_t i = 0; i < numPixels; i++ ) {
			destBuffer[i] += inBuffer[i];
			buffer++;
		}

	}




}