#pragma once


#include "Graphic/TextureLoadable.h"
#include "Graphic/FontLoadable.h"
#include "Graphic/FreeImage.h"
#include "Graphic/GradientInterpolated.h"
#include "Graphic/Gradient.h"










namespace Graphic {



	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const GradientHorizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const GradientHorizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const GradientVertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );

	
	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const GradientVertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );

	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), const BlendFunc & blendFunc = BlendingFunc::Normal() );


	///@brief draw the text to the specified position without a blending, the character bitmap will directly by copied to the specified image
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ) );


	///@brief draw the text to the specified position without a blending, the character bitmap will directly by copied to the specified image
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T>
	void drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ) );

	///@brief private function do not touch this.
	template<typename T, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc );

	///@brief private function do not touch this.
	template<typename T, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc );

	///@brief private function do not touch this.
	template<typename T, typename Func>
	void _drawText( const Font<T> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );

	///@brief private function do not touch this.
	template<typename T, typename Func>
	void _drawTextWBB( const Font<T> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );

	///@brief private function do not touch this.
	template<typename T, typename Func>
	void _drawText( const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );
}



#include "Graphic.hpp"


