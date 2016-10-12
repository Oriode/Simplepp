///@file Graphic.h
///@brief Main file for graphics objects and methods
///@author Clément Gerber
///@date 19/04/2016 (DMY) 


#pragma once


#include "Graphic/TextureLoadable.h"
#include "Graphic/FontLoadable.h"
#include "Graphic/FreeImage.h"
#include "Graphic/GradientInterpolated.h"
#include "Graphic/Gradient.h"
#include "Graphic/FontEffect.h"









namespace Graphic {



	///@brief draw the text to the specified point using an horizontal gradient 
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Gradient::Horizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text inside the specified rectangle using an horizontal gradient 
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Gradient::Horizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text to the specified point using a vertical gradient
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Gradient::Vertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text into the specified rectangle using a vertical gradient
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param gradient to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Gradient::Vertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text to the specified point using a ColorR
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text into the specified rectangle using a ColorR
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );

	///@brief draw the text to the specified point using a ColorRGB
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text into the specified rectangle using a ColorRGB
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text to the specified point using a ColorRGBA
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text into the specified rectangle using a ColorRGBA
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param color to use to draw the text
	///@param centered If the text has to be centered vertically or horizontally.
	///@param blendFunc Functor with operator() overloaded with 
	///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text to the specified point without a blending, the character bitmap will directly be blended to the specified image
	///@param font Font object to use
	///@param point Position where to draw (left bottom anchor of the text)
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	///@brief draw the text into the specified rectangle without a blending, the character bitmap will directly be blended to the specified image
	///@param font Font object to use
	///@param rectangle Rectangle where the text will be.
	///@param text Text to draw
	///@param centered If the text has to be centered vertically or horizontally.
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );






	/************************************************************************/
	/* PRIVATE STUFF! DON'T TOUCH THIS!                                     */
	/************************************************************************/
	///@brief private function do not touch this.
	template<typename T, typename LoadingFunc, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc );

	///@brief private function do not touch this.
	template<typename T, typename LoadingFunc, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc );

	///@brief private function do not touch this.
	template<typename T, typename LoadingFunc, typename Func>
	void _drawText( const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );

	///@brief private function do not touch this.
	template<typename T, typename LoadingFunc, typename Func>
	void _drawTextWBB( const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );

	///@brief private function do not touch this.
	template<typename T, typename LoadingFunc, typename Func>
	void _drawText( const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );
}



#include "Graphic.hpp"


