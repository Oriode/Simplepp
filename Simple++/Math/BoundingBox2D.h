#pragma once


#include "Vec2.h"
#include "Rectangle.h"


namespace Math {

	template <typename T>
	class BoundingBox2D {
	public:
		BoundingBox2D();
		BoundingBox2D(const Vec2<T> & center, const Vec2<T> & size);
		BoundingBox2D(const Rectangle<T> & r);
		~BoundingBox2D();


		Rectangle<T> toRectangle() const;

		BoundingBox2D<T> & operator=(const Rectangle<T> & r);

		BoundingBox2D<T> & operator-=(const Vec2<T> & p);
		BoundingBox2D<T> & operator+=(const Vec2<T> & p);


		const Vec2<T> & getCenter() const;
		const Vec2<T> & getSize() const;

		void setCenter(const Vec2<T> & center);
		void setSize(const Vec2<T> & size);


		bool isColiding(const BoundingBox2D<T> & r) const;


	private:
		Vec2<T> center;
		Vec2<T> size;
	};



	template <typename T>
	BoundingBox2D<T>::BoundingBox2D(const Rectangle<T> & r){
		*this = r;
	}

	template <typename T>
	BoundingBox2D<T> & BoundingBox2D<T>::operator=(const Rectangle<T> & r){
		this -> size = r.getRightTop() - r.getLeftBottom();
		this -> center = (r.getLeftBottom() + r.getRightTop()) / T(2);
		return *this;
	}

	template <typename T>
	Rectangle<T> BoundingBox2D<T>::toRectangle() const{
		Vec2<T> size2(this -> size / T(2));
		return Rectangle<T>(this -> center - size2, this -> center + size2);
	}


	template<typename T>
	BoundingBox2D<T> operator+(const BoundingBox2D<T> & r, const Vec2<T> & p);

	template<typename T>
	BoundingBox2D<T> operator+(const Vec2<T> & p, const BoundingBox2D<T> & r);


	template<typename T>
	BoundingBox2D<T> operator-(const BoundingBox2D<T> & r, const Vec2<T> & p);

	template<typename T>
	BoundingBox2D<T> operator-(const Vec2<T> & p, const BoundingBox2D<T> & r);


	typedef BoundingBox2D<float> BoundingBox2Df;
	typedef BoundingBox2D<int> BoundingBox2Di;

}







#include "BoundingBox2D.hpp"