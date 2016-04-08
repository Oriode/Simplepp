#pragma once



#include "Image.h"
#include "Font.h"
#include "FreeImage.h"

namespace Graphic {




	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));




	///@brief draw the text to the specified position without a blending, the character bitmap will directly by copied to the specified image
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));


	///@brief draw the text to the specified position without a blending, the character bitmap will directly by copied to the specified image
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>(false));



	template<typename Func>
	void _drawText(const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func);

	template<typename Func>
	void _drawText(const Font & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );
}



#include "Graphic.hpp"


