

namespace Math {



	template <typename T>
	Math::BoundingBox2D<T>::BoundingBox2D(){

	}


	template <typename T>
	Math::BoundingBox2D<T>::BoundingBox2D(const Vec2<T> & center, const Vec2<T> & size) :
		center(center),
		size(size)
	{

	}



	template <typename T>
	Math::BoundingBox2D<T>::~BoundingBox2D(){

	}


	template <typename T>
	const Vec2<T> & BoundingBox2D<T>::getCenter() const{
		return this -> center;
	}

	template <typename T>
	const Vec2<T> & BoundingBox2D<T>::getSize() const{
		return this -> size;
	}


	template <typename T>
	void BoundingBox2D<T>::setSize(const Vec2<T> & size){
		this -> size = size;
	}

	template <typename T>
	void BoundingBox2D<T>::setCenter(const Vec2<T> & center){
		this -> center = center;
	}

	template <typename T>
	bool BoundingBox2D<T>::isColiding(const BoundingBox2D<T> & r) const{
		return (std::abs(this -> center.x - r.getCenter().x) * 2 < (this -> size.x + r.getSize().x)) &&
			(std::abs(this -> center.y - r.getCenter().y) * 2 < (this -> size.y + r.getSize().y));

	}

	template <typename T>
	BoundingBox2D<T> & BoundingBox2D<T>::operator+=(const Vec2<T> & p){
		this -> center += p;
		return *this;
	}

	template <typename T>
	BoundingBox2D<T> & BoundingBox2D<T>::operator-=(const Vec2<T> & p){
		this -> center -= p;
		return *this;
	}




	template<typename T>
	BoundingBox2D<T> operator+(const BoundingBox2D<T> & r, const Vec2<T> & p){
		return BoundingBox2D<T>(r.getCenter() + p, r.getSize());
	}

	template<typename T>
	BoundingBox2D<T> operator+(const Vec2<T> & p, const BoundingBox2D<T> & r){
		return BoundingBox2D<T>(r.getCenter() + p, r.getSize());
	}

	template<typename T>
	BoundingBox2D<T> operator-(const BoundingBox2D<T> & r, const Vec2<T> & p){
		return BoundingBox2D<T>(r.getCenter() - p, r.getSize());
	}

	template<typename T>
	BoundingBox2D<T> operator-(const Vec2<T> & p, const BoundingBox2D<T> & r){
		return BoundingBox2D<T>(p - r.getCenter(), r.getSize());
	}





}