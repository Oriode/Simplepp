#pragma once

#include "../Math.h"

namespace Graphic {

	template<typename T = unsigned char>
	using ColorRGBA = Math::Vec4<T>;
	template<typename T = unsigned char>
	using ColorRGB = Math::Vec3<T>;
	template<typename T = unsigned char>
	using ColorR = T;


	typedef ColorRGBA<float> ColorRGBAf;
	typedef ColorRGB<float> ColorRGBf;
	typedef ColorR<float> ColorRf;

	typedef int Size;

	typedef Math::Vec2<int> Point;
	typedef Math::Vec2<float> PointF;

	typedef Math::Rectangle<int> Rectangle;
	typedef Math::Line<int> Line;
	typedef Math::Line<float> LineF;

	enum class Format : unsigned int { R = 1, RGB = 3, RGBA = 4 };
	enum class LoadingFormat { R, RGB, BGR, RGBA, BGRA };



	/*ColorRGBA<unsigned char> colorWhiteR(255);
	ColorRGBA<unsigned char> colorWhiteRGB(255, 255, 255);
	ColorRGBA<unsigned char> colorWhiteRGBA(255, 255, 255, 255);


	ColorRGBA<unsigned char> colorBlackR(0);
	ColorRGBA<unsigned char> colorBlackRGB(0, 0, 0);
	ColorRGBA<unsigned char> colorBlackRGBA(0, 0, 0, 255);*/
}
