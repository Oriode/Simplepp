///@file Gradient.h
///@brief Gradient Class
///@author Cl�ment Gerber
///@date 19/04/16 (DMY)


#pragma once
#include "Math.h"

namespace Graphic {


	template<typename T>
	using ColorRGBA = Math::Vec4<T>;
	template<typename T>
	using ColorRGB = Math::Vec3<T>;
	template<typename T>
	using ColorR = T;

	typedef Math::Vec2<int> Point;
	typedef Math::Rectangle<int> Rectangle;

	enum class Format : unsigned int { R = 1, RGB = 3, RGBA = 4 };
	enum class LoadingFormat { R, RGB, BGR, RGBA, BGRA };


	///@brief A point in a gradient
	template<typename C = ColorRGBA<unsigned char>>
	class GradientPoint {


		///@brief Create a Point for a Gradient initialized with a position and a color
		///@param position Floating number between 0 and 1 representing the position on the gradient.
		///@param color Color of this point.
		GradientPoint(float position, const C & color);
		

	private:
		ColorRGBA<T> color;
		float position;			//between 0 and 1
	};



	///@brief Represent a 2D Gradient for 2D image processing.
	template<typename C>
	class Gradient {
	public:
		enum class Type { Vertical, Horizontal };








	private:
		Vector<GradientPoint<C>>
	};
}



