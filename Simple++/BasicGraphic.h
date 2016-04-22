#pragma once


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

}
