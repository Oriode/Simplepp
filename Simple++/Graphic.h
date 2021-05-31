/**
 * @file	Graphic.h.
 *
 * @brief	Main file for graphics objects and methods
 * @author	Clément Gerber
 * @date	19/04/2016 (DMY)
 */
#pragma once

#include "Graphic/Texture.h"
#include "Graphic/TrueTypeFont.h"
#include "Graphic/FreeImage.h"
#include "Graphic/GradientInterpolated.h"
#include "Graphic/Gradient.h"
#include "Graphic/FontEffect.h"
#include "Graphic/Text.h"


namespace Graphic {
	/**
	 * @brief	draw the text to the specified point using an horizontal gradient
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	C		   	Type of the c.
	 * @tparam	terFunc	   	Type of the ter function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	point	 	Position where to draw (left bottom anchor of the text)
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	gradient 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Gradient::Horizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text inside the specified rectangle using an horizontal gradient
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	C		   	Type of the c.
	 * @tparam	terFunc	   	Type of the ter function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	gradient 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Gradient::Horizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text to the specified point using a vertical gradient
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	C		   	Type of the c.
	 * @tparam	terFunc	   	Type of the ter function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	point	 	Position where to draw (left bottom anchor of the text)
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	gradient 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Gradient::Vertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text into the specified rectangle using a vertical gradient
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	C		   	Type of the c.
	 * @tparam	terFunc	   	Type of the ter function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	gradient 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Gradient::Vertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text to the specified point using a ColorR
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	point	 	Position where to draw (left bottom anchor of the text)
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	color	 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text into the specified rectangle using a ColorR
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	color	 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );

	/**
	 * @brief	draw the text to the specified point using a ColorRGB
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	point	 	Position where to draw (left bottom anchor of the text)
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	color	 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text into the specified rectangle using a ColorRGB
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	color	 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc,
	 * 								const Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const
	 * 								Graphic::ColorR<T> & colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text to the specified point using a ColorRGBA
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	point	 	Position where to draw (left bottom anchor of the text)
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	color	 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc,
	 * 								const Graphic::ColorR<T>
	 * 								& colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> &
	 * 								colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> &
	 * 								colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text into the specified rectangle using a ColorRGBA
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	color	 	to use to draw the text.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc,
	 * 								const Graphic::ColorR<T>
	 * 								& colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> &
	 * 								colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> &
	 * 								colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text into the specified rectangle using a Color Functor
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	ColorFunc  	Type of the color function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param [in,out]	colorFunc	Color Functor to be used to draw (@see Graphic::ColorFunc)
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) Functor with operator() overloaded with "void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc,
	 * 								const Graphic::ColorR<T>
	 * 								& colorMask)const;" "void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> &
	 * 								colorMask)const;" "void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> &
	 * 								colorMask)const;".
	 */
	template<typename T, typename LoadingFunc, typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawTextFunctor( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, ColorFunc & colorFunc, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	Normal>s
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	ColorFunc  	Type of the color function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	The font.
	 * @param 		  	point	 	The point.
	 * @param 		  	text	 	The text.
	 * @param [in,out]	colorFunc	The color function.
	 * @param 		  	centered 	(Optional) The centered.
	 * @param [in,out]	blendFunc	(Optional) The blend function.
	 */
	template<typename T, typename LoadingFunc, typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawTextFunctor( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, ColorFunc & colorFunc, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );

	/**
	 * @brief	draw the text to the specified point without a blending, the character bitmap will directly be blended to the specified image
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	point	 	Position where to draw (left bottom anchor of the text)
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) The blend function.
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );


	/**
	 * @brief	draw the text into the specified rectangle without a blending, the character bitmap will directly be blended to the specified image
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	Font object to use.
	 * @param 		  	rectangle	Rectangle where the text will be.
	 * @param 		  	text	 	Text to draw.
	 * @param 		  	centered 	(Optional) If the text has to be centered vertically or horizontally.
	 * @param [in,out]	blendFunc	(Optional) The blend function.
	 */
	template<typename T, typename LoadingFunc, typename BlendFunc = BlendingFunc::Normal>
	void drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered = Math::Vec2<bool>( false ), BlendFunc & blendFunc = BlendFunc() );






	/************************************************************************/
	/* PRIVATE STUFF! DON'T TOUCH THIS!                                     */
	/************************************************************************/
	/**
	 * @brief	private function do not touch this.
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	C		   	Type of the c.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	The font.
	 * @param 		  	point	 	The point.
	 * @param 		  	text	 	The text.
	 * @param 		  	color	 	The color.
	 * @param 		  	centered 	The centered.
	 * @param [in,out]	blendFunc	The blend function.
	 */
	template<typename T, typename LoadingFunc, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc );

	/**
	 * @brief	private function do not touch this.
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	C		   	Type of the c.
	 * @tparam	BlendFunc  	Type of the blend function.
	 * @param [in,out]	image	 	If non-null, the image.
	 * @param 		  	font	 	The font.
	 * @param 		  	rectangle	The rectangle.
	 * @param 		  	text	 	The text.
	 * @param 		  	color	 	The color.
	 * @param 		  	centered 	The centered.
	 * @param [in,out]	blendFunc	The blend function.
	 */
	template<typename T, typename LoadingFunc, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc );

	/**
	 * @brief	private function do not touch this.
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	Func	   	Type of the function.
	 * @param 		  	font		The font.
	 * @param 		  	point   	The point.
	 * @param 		  	text		The text.
	 * @param 		  	centered	The centered.
	 * @param [in,out]	func		The function.
	 */
	template<typename T, typename LoadingFunc, typename Func>
	void _drawText( const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );

	/**
	 * @brief	private function do not touch this.
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	Func	   	Type of the function.
	 * @param 		  	font		The font.
	 * @param 		  	point   	The point.
	 * @param 		  	text		The text.
	 * @param 		  	centered	The centered.
	 * @param [in,out]	func		The function.
	 */
	template<typename T, typename LoadingFunc, typename Func>
	void _drawTextWBB( const FontT<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );

	/**
	 * @brief	private function do not touch this.
	 *
	 * @tparam	T		   	Generic type parameter.
	 * @tparam	LoadingFunc	Type of the loading function.
	 * @tparam	Func	   	Type of the function.
	 * @param 		  	font	 	The font.
	 * @param 		  	rectangle	The rectangle.
	 * @param 		  	text	 	The text.
	 * @param 		  	centered 	The centered.
	 * @param [in,out]	func	 	The function.
	 */
	template<typename T, typename LoadingFunc, typename Func>
	void _drawText( const FontT<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func );
}



#include "Graphic.hpp"


