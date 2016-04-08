namespace Math {

	template <typename T>
	const Rectangle<T> Math::Rectangle<T>::null = Rectangle<T>(0, 0);

	template <typename T>
	Rectangle<T>::Rectangle(const T & left, const T & top, const T & right, const T & bottom){
		this->pointLeftBottom.x = left;
		this->pointLeftBottom.y = bottom;
		this->pointRightTop.x = right;
		this->pointRightTop.y = top;
	}

	template <typename T>
	Rectangle<T>::Rectangle(const Vec2<T> & leftBottom, const Vec2<T> & rightTop){
		this->pointLeftBottom = leftBottom;
		this->pointRightTop = rightTop;
	}

	template <typename T>
	Rectangle<T>::Rectangle(){

	}

	template <typename T>
	void Rectangle<T>::setRightTop(const Vec2<T> & rightTop){
		this->pointRightTop = rightTop;
	}

	template <typename T>
	void Rectangle<T>::setLeftBottom(const Vec2<T> & leftTop){
		this->pointLeftBottom = leftTop;
	}

	template <typename T>
	void Rectangle<T>::setBottom(const T & bottom){
		this->pointLeftBottom.y = bottom;
	}

	template <typename T>
	void Rectangle<T>::setRight(const T & right){
		this->pointRightTop.x = right;
	}

	template <typename T>
	void Rectangle<T>::setTop(const T & top){
		this->pointRightTop.y = top;
	}

	template <typename T>
	void Rectangle<T>::setLeft(const T & left){
		this->pointLeftBottom.x = left;
	}

	template <typename T>
	const Vec2<T> Rectangle<T>::getRightTop() const{
		return this->pointRightTop;
	}

	template <typename T>
	const Vec2<T> Rectangle<T>::getLeftBottom() const{
		return this->pointLeftBottom;
	}

	template <typename T>
	const T & Rectangle<T>::getBottom() const{
		return this->pointLeftBottom.y;
	}

	template <typename T>
	const T & Rectangle<T>::getRight() const{
		return this->pointRightTop.x;
	}

	template <typename T>
	const T & Rectangle<T>::getTop() const{
		return this->pointRightTop.y;
	}

	template <typename T>
	const T & Rectangle<T>::getLeft() const{
		return this->pointLeftBottom.x;
	}




	template <typename T>
	Rectangle<T> & Rectangle<T>::operator+=(const Vec2<T> & p){
		this->pointLeftBottom += p;
		this->pointRightTop += p;
		return *this;
	}



	template <typename T>
	Rectangle<T> & Rectangle<T>::operator-=(const Vec2<T> & p){
		this->pointLeftBottom -= p;
		this->pointRightTop -= p;
		return *this;
	}



	template <typename T>
	bool Rectangle<T>::isInside(const Vec2<T> & p) const{
		return (this->pointRightTop.x <= p.x && this->pointRightTop.y <= p.y &&
			this->pointLeftBottom.x >= p.x && this->pointLeftBottom.y >= p.y);


	}



	template<typename T>
	Rectangle<T> operator+(const Rectangle<T> & r, const Vec2<T> & p){
		return Rectangle<T>(r.getLeftBottom() + p, r.getRightTop() + p);
	}

	template<typename T>
	Rectangle<T> operator+(const Vec2<T> & p, const Rectangle<T> & r){
		return Rectangle<T>(r.getLeftBottom() + p, r.getRightTop() + p);
	}

	template<typename T>
	Rectangle<T> operator-(const Rectangle<T> & r, const Vec2<T> & p){
		return Rectangle<T>(r.getLeftBottom() - p, r.getRightTop() - p);
	}

	template<typename T>
	Rectangle<T> operator-(const Vec2<T> & p, const Rectangle<T> & r){
		return Rectangle<T>(p - r.getLeftBottom(), p - r.getRightTop());
	}


}