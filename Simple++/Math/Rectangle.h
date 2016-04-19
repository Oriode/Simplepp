#pragma once


#include "Log.h"
#include "Vec2.h"

namespace Math {


	template <typename T>
	class Rectangle {
	public:
		typedef T Type;

		Rectangle();
		Rectangle(const Vec2<T> & rightTop);
		Rectangle(const Vec2<T> & leftBottom,
				const Vec2<T> & rightTop);
		Rectangle(const T & left, const T & bottom, const T & right, const T & top);


		const T & getLeft() const;
		const T & getTop() const;

		const T & getRight() const;
		const T & getBottom() const;

		const Vec2<T> getLeftBottom() const;
		const Vec2<T> getRightTop() const;


		bool isInside(const Vec2<T> & p) const;


		void setLeft(const T & left);
		void setTop(const T & top);

		void setRight(const T & right);
		void setBottom(const T & bottom);

		void setLeftBottom(const Vec2<T> & leftTop);
		void setRightTop(const Vec2<T> & rightTop);

		Rectangle<T> & operator+=(const Vec2<T> & p);
		Rectangle<T> & operator-=(const Vec2<T> & p);



		static const Rectangle<T> null;
	private:
		Vec2<T> pointLeftBottom;
		Vec2<T> pointRightTop;
	};








	template<typename T>
	Rectangle<T> operator+(const Rectangle<T> & r, const Vec2<T> & p);

	template<typename T>
	Rectangle<T> operator+(const Vec2<T> & p, const Rectangle<T> & r);


	template<typename T>
	Rectangle<T> operator-(const Rectangle<T> & r, const Vec2<T> & p);

	template<typename T>
	Rectangle<T> operator-(const Vec2<T> & p, const Rectangle<T> & r);


	
	typedef Rectangle<float> RectF;
	typedef Rectangle<int> RectI;
	

}



#include "Rectangle.hpp"
