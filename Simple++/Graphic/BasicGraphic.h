#pragma once

#include "../Math/Math.h"
#include "ColorR.h"
#include "ColorRGB.h"
#include "ColorRGBA.h"


namespace Graphic {


	typedef ColorRGBA<float> ColorRGBAf;
	typedef ColorRGB<float> ColorRGBf;
	typedef ColorR<float> ColorRf;

	typedef int Size;

	typedef Math::Vec2<int> Point;
	typedef Math::Vec2<float> PointF;

	typedef Math::Rectangle<int> Rectangle;
	typedef Math::Line<int> Line;
	typedef Math::Line<float> LineF;

	enum class LoadingFormat { R, RGB, BGR, RGBA, BGRA };



	/*ColorRGBA<unsigned char> colorWhiteR(255);
	ColorRGBA<unsigned char> colorWhiteRGB(255, 255, 255);
	ColorRGBA<unsigned char> colorWhiteRGBA(255, 255, 255, 255);


	ColorRGBA<unsigned char> colorBlackR(0);
	ColorRGBA<unsigned char> colorBlackRGB(0, 0, 0);
	ColorRGBA<unsigned char> colorBlackRGBA(0, 0, 0, 255);*/
}
