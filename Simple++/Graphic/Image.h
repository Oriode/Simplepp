///@file Image.h
///@brief Image Class with some drawing methods
///@author Clément Gerber
///@date 19/04/2016 (DMY) 



#pragma once


#include "../Log.h"
#include "../Math.h"
#include "../Vector.h"
#include "../String.h"
#include "../Utility.h"
#include "../BasicIO.h"
#include "Gradient.h"
#include "BlendingFunc.hpp"
#include "ColorFunc.h"
#include "KernelFunc.hpp"




namespace Graphic {

	///@brief Struct used to retrieve the type of a summation of multiple pixel components
	template<typename T>
	struct _ImageSumType {
		typedef typename Utility::TypesInfos<typename Utility::TypesInfos<T>::Bigger>::Bigger Type;
	};
	template<>
	struct _ImageSumType<float> {
		typedef float Type;
	};
	template<>
	struct _ImageSumType<double> {
		typedef double Type;
	};




	///@brief Image Class
	///@template T Type of one pixel
	///@template F Format of the image
	template<typename T = unsigned char>
	class _Image : public BasicIO {
	public:
		enum class ResamplingMode { Nearest, Linear, Lanczos };
		enum class ConvolutionMode { NormalSize, ExtendedSize };
		enum class ConversionMode { Luminance, Trunquate, Alpha };
		enum class StrokeType { Outside, Inside, Middle };

		///@brief Type used to sum multiple pixels components
		typedef typename _ImageSumType<T>::Type SumType;

		///@brief Type used to sum multiple pixels components multiplied with a negative value
		typedef typename Utility::TypesInfos<typename SumType>::Signed KernelType;


		///@brief copy constructor with an another storage type
		///@param image image to copy
		template<typename C>
		_Image( const _Image<C> & image );

		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		_Image( Format format = Format::RGB );

		///@brief Constructor to create an initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		_Image( const Math::Vec2<Size> & size, Format format = Format::RGB );

		///@brief create a new image data from a file stream.
		///@param fileStream Stream to read
		///@param format of the image
		_Image( std::fstream * fileStream );


		///@brief Constructor to create an image from a data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		///@param stride width of ONE line of the image data in bytes, if stride == 0, the lines are supposed to be contiguous without any padding
		_Image( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );

		///@brief copy constructor
		_Image( const _Image<T> & image );

		///@brief move constructor
		_Image( _Image<T> && image );

		~_Image( );

		///@brief get the actual size (width:height) of the image
		///@return the actual size of this image
		const Math::Vec2<Size> & getSize( ) const;

		///@brief get the actual width of the image
		///@return actual width of this image
		Size getWidth( ) const;

		///@brief get the actual height of the image
		///@return actual height of this image
		Size getHeight( ) const;


		///@brief get the number of pixels of this image
		///@return number of pixels
		size_t getNbPixels( ) const;

		///@brief reset this image with a new size.
		///@param size new size
		void clear( const Math::Vec2<Size> & size );


		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear( const Math::Vec2<Size> & size, Format format );


		///@brief set the data from an another data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param invertY if the image has to be flipped vertically or not.
		///@param stride width of ONE line of the image data in bytes, if stride == 0, the lines are supposed to be contiguous without any padding
		void setDatas( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );


		///@brief create a new image from this one with a size of width / 2 and height / 2
		///@return new image created from this one with an halved size.
		_Image<T> * createMipmap( );

		///@brief get the data buffer of this image 
		///@return data buffer
		const T * getDatas( ) const;


		///@brief get the data buffer of this image 
		///@return data buffer
		T * getDatas( );



		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		const T * getDatas( Size x, Size y ) const;

		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		T * getDatas( Size x, Size y );


		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel( Size x, Size y ) const;

		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		T * getPixel( Size x, Size y );


		///@brief get the offset of pixel from the beginning of the data
		///@param x X coordinate
		///@param y Y coordinate
		///@return offset to be added to go from the begining of the data (getData()) and the selected pixel
		size_t getDataOffset( Size x, Size y ) const;



		///@brief set a pixel inside this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel( Size x, Size y, const T * p );



		///@brief copy operator with another type
		///@param image Image to copy
		template<typename C>
		_Image<T> & operator=( const _Image<C> & image );

		///@brief copy operator
		///@param image Image to copy
		_Image<T> & operator=( const _Image<T> & image );

		///@brief move operator
		///@param image Image to move from
		_Image<T> & operator=( _Image<T> && image );


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

		///@brief get the format of this image
		///@return format of this image
		Format getFormat( ) const;


		///@brief  get the number of components per pixels of this image.
		///@return Number of components per pixels.
		inline unsigned int getNbComponents( ) const;


		///@brief Create a new Image from this one with a new format
		///@param newFormat Format of the new image
		///@param conversionMode Only used when converted to Format::R (Luminance : Use the average of the RGB channels, Trunquate : Use the R channel, Alpha : Use the Alpha Channel)
		///@return Image based of this one with a new format
		_Image<T> toFormat( Format newFormat, ConversionMode conversionMode = ConversionMode::Luminance ) const;



		///@brief get the maximum value of a color component
		///@param maximum value of a component depending of the template type T
		constexpr static T getComponentMaxValue( );

		///@brief get the maximum value of a color component
		///@param maximum value of a component depending of the template type T
		constexpr static T getComponentMinValue( );


		/************************************************************************/
		/* Gradient                                                             */
		/************************************************************************/
		///@brief Compute the interpolation for horizontal gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const GradientHorizontal<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;


		///@brief Compute the interpolation for vertical gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const GradientVertical<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;


		///@brief Compute the interpolation for Linear gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const GradientLinear<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;

		///@brief Compute the interpolation for Radial gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const GradientRadial<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;

		/************************************************************************/
		/* Drawing methods                                                      */
		/************************************************************************/

		///@brief Threshold the image with a specified functor
		///@param colorTrue color applied in case of True (color is not blended, only copied)
		///@param colorFalse color applied in case of False (color is not blended, only copied)
		///@param functor Functor with operator() overloaded with 
		///					"template<typename T> inline bool operator()(Graphic::ColorR<T> & color)const;"
		///					"template<typename T> inline bool operator()(Graphic::ColorRGB<T> & color)const;"
		///					"template<typename T> inline bool operator()(Graphic::ColorRGBA<T> & color)const;"
		template<typename ThreshFunc>
		void threshold( const ColorRGBA<T> & colorTrue, const ColorRGBA<T> & colorFalse, const ThreshFunc & threshFunc );

		///@brief Threshold the image with a specified threshold
		///@param colorOver color applied in case if every component is OVER the limit (color is not blended, only copied)
		///@param colorFalse color applied in case if at least one component is UNDER the limit (color is not blended, only copied)
		///@param limit color used to be the threshold, component to component will be compared.
		void threshold( const ColorRGBA<T> & colorOver, const ColorRGBA<T> & colorUnder, const ColorRGBA<T> & limit );


		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param color Color to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawLine( const LineF & l, const ColorR<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param color Color to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawLine( const LineF & l, const ColorRGB<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param color Color to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawLine( const LineF & l, const ColorRGBA<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw an anti aliased line from point p1 to point p2
		///@see https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm
		///@param l Line
		///@param colorFunc functor that will generate the color for each pixels (see Graphic::ColorFunc::Template), width the methods :
		///					"inline void init(const Rectangle & rectangle);"
		///					"inline const C & operator()(const Math::Vec2<Size> & p) const;"
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief Set a functor to each pixels in the rectangle of this image
		///@param functor Functor with the methods :
		///					"inline void operator()(const Math::Vec2<Size> & p, Graphic::ColorR<T> & c);"
		///					"inline void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGB<T> & c);"
		///					"inline void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGBA<T> & c);"
		///														
		///@param rectangle Rectangle where to apply the functor.
		template<typename Functor>
		void setPixels( Functor & functor, const Rectangle & rectangle );

		///@brief Set a functor to each pixels of this image
		///@param functor Functor with operator() overloaded with 
		///					"template<typename T> void operator()(const Math::Vec2<Size> & p, Graphic::ColorR<T> & c);"
		///					"template<typename T> void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGB<T> & c);"
		///					"template<typename T> void operator()(const Math::Vec2<Size> & p, Graphic::ColorRGBA<T> & c);"
		template<typename Functor>
		void setPixels( Functor & functor );


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const ColorR<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const ColorRGB<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const ColorRGBA<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		template<typename C, typename InterFunc>
		void drawRectangle( const Rectangle & rectangle, const GradientHorizontal<C, InterFunc> & gradient );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const GradientLinear<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const GradientRadial<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrcc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc>
		void drawRectangle( const Rectangle & rectangle, const GradientHorizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const GradientVertical<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param colorFunc functor that will generate the color for each pixels (see Graphic::ColorFunc::Template), width the methods :
		///					"inline void init(const Rectangle & rectangle);"
		///					"inline const C & operator()(const Math::Vec2<Size> & p) const;"
		///@param blendFunc Functor with the methods :
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleFunctor( const Rectangle & rectangle, ColorFunc & colorFunc, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief fill the complete image with a color.
		///param color pointer to a color with the same number of component of this image
		void fillImage( const T * color );

		///@brief fill the complete image with a color.
		///@param color pointer to a color with the same number of component of this image
		///@param rectangle Rectangle where to fill the color
		void fillImage( const T * color, const Rectangle & rectangle );

		///@brief fill the complete image with a color.
		///@param color R color
		void fillImage( const ColorR<T> & color );

		///@brief fill the complete image with a color.
		///@param color RGB color
		void fillImage( const ColorRGB<T> & color );

		///@brief fill the complete image with a color.
		///@param color RGBA color
		void fillImage( const ColorRGBA<T> & color );


		///@brief fill the complete image with a color.
		///@param color R color
		///@param rectangle Rectangle where to fill the color
		void fillImage( const ColorR<T> & color, const Rectangle & rectangle );

		///@brief fill the complete image with a color.
		///@param color RGB color
		///@param rectangle Rectangle where to fill the color
		void fillImage( const ColorRGB<T> & color, const Rectangle & rectangle );

		///@brief fill the complete image with a color.
		///@param color RGBA color
		///@param rectangle Rectangle where to fill the color
		void fillImage( const ColorRGBA<T> & color, const Rectangle & rectangle );

		///@brief fill the complete image with a horizontal gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const GradientHorizontal<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill the complete image with a vertical gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const GradientVertical<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill the complete image with a Linear gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const GradientLinear<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill the complete image with a Radial gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const GradientRadial<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill an another image into this one (no blending will be applied)
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void fillImage( const Point & point, const _Image<T> & image );

		///@brief fill an another image into this one (no blending will be applied)
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void fillImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image );


		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param image Another image to draw
		void drawImage( const Point & point, const _Image<T> & image );


		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void drawImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image );


		///@brief draw an another image into this one with a custom blending function
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );



		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const ColorR<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const ColorRGB<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const ColorRGBA<T> & color, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param colorFunc functor that will generate the color for each pixels (see Graphic::ColorFunc::Template), width the methods :
		///					"inline void init(const Rectangle & rectangle);"
		///					"inline const C & operator()(const Math::Vec2<Size> & p) const;"
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawImageFunctor( const Point & point, ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage( const Point & point, const _Image<T> & image, const _Image<T> & maskImage );

		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage( const Point & point, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage );


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const Graphic::ColorR<T> & colorMask)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief Stroke the image with a specified color functor
		///@param point Point where to draw the stroking
		///@param image Image used to compute the stroking (R & RGB will use the r channel and RGBA the a channel)
		///@param thickness Thickness of the stroking
		///@param colorFunc functor that will generate the color for each pixels, width the methods :
		///					"inline void init(const Rectangle & rectangle);"
		///					"inline const C & operator()(const Math::Vec2<Size> & p) const;"
		///@param strokeType Type of the stroking (Outside, Inside or Middle)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawStrokeFunctor( const Point & point, const _Image<T> & image, unsigned int thickness, ColorFunc & colorFunc, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief Stroke the image with a specified color
		///@param point Point where to draw the stroking
		///@param image Image used to compute the stroking (R & RGB will use the r channel and RGBA the a channel)
		///@param thickness Thickness of the stroking
		///@param color color to be used
		///@param strokeType Type of the stroking (Outside, Inside or Middle)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawStroke( const Point & point, const _Image<T> & image, unsigned int thickness, const ColorR<T> & color, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief Stroke the image with a specified color
		///@param point Point where to draw the stroking
		///@param image Image used to compute the stroking (R & RGB will use the r channel and RGBA the a channel)
		///@param thickness Thickness of the stroking
		///@param color color to be used
		///@param strokeType Type of the stroking (Outside, Inside or Middle)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawStroke( const Point & point, const _Image<T> & image, unsigned int thickness, const ColorRGB<T> & color, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief Stroke the image with a specified color
		///@param point Point where to draw the stroking
		///@param image Image used to compute the stroking (R & RGB will use the r channel and RGBA the a channel)
		///@param thickness Thickness of the stroking
		///@param color color to be used
		///@param strokeType Type of the stroking (Outside, Inside or Middle)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawStroke( const Point & point, const _Image<T> & image, unsigned int thickness, const ColorRGBA<T> & color, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@method drawBezierCurve
		///@brief Draw a Cubic Bezier curve
		///@param p0 Point 0
		///@param p1 Point 1
		///@param p2 Point 2
		///@param p3 Point 3
		///@param thickness Thickness of the curve
		///@param color Color to be used
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, T alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, T alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, T alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;" 
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorR<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename BlendFunc = BlendingFunc::Normal>
		void drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorRGB<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename BlendFunc = BlendingFunc::Normal>
		void drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorRGBA<T> & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief draw points (x,y) as a graph inside a rectangle
		///@param values Vector of floating points (points has to be between 0.0 and 1.0) (the points has to be ascending ordered using their x coordinate)
		///@param rectangle Rectangle where to draw the graph
		///@param colorFunc Color Functor used to draw
		///@param blendFunc Blending Functor used to draw
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawGraphValuesFunctor( const Vector<Math::Vec2<float>> & values, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief Get the number of bits of the sum of a kernel depending of the types used
		///@return number of bits of the sum of a integer kernel (floating kernel will every time has a sum of 1.0)
		template<typename K = typename KernelType>
		constexpr static K getKernelSumNbBits();

		///@brief apply a symmetrical convolution filter (Gaussian blur for example)
		///@param filter Filter table (the table has to have an odd size)
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@param kernelFunc Function to be used to treat the summation before dividing it (Handle overflow, negatives values etc...)
		///@see _Image<T>::SumType for an automatically generated Filter Type
		///@see Graphic::KernelFunc for many preconfigured functors
		///@return Image with the filter applied
		template<typename F, typename KernelFunc = KernelFunc::None>
		_Image<T> applyFilter( const F * filter, Size size, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null, KernelFunc & kernelFunc = KernelFunc::None() ) const;


		///@brief Apply a convolution filter
		///@param filter Filter Matrix of size (size.x * size.y) stored row per row from bottom to top from left to right
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@param kernelFunc Function to be used to treat the summation before dividing it (Handle overflow, negatives values etc...)
		///@see _Image<T>::SumType for an automatically generated Filter Type
		///@see Graphic::KernelFunc for many preconfigured functors
		///@return Image with the filter applied
		template<typename F, typename KernelFunc = KernelFunc::None>
		_Image<T> applyFilter( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null, KernelFunc & kernelFunc = KernelFunc::None() ) const;


		///@brief apply a Gaussian Blur Filter
		///@param radius Radius of the blur
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@return Image with the filter applied
		_Image<T> applyGaussianBlur( Size radius, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null ) const;


		///@brief Clamp a rectangle inside the image
		///@param rectangle rectangle to be clamped
		///@return A Rectangle clamped inside the image
		inline Math::Rectangle<Size> clampRectangle( const Rectangle & rectangle ) const;


		///@brief Draw a rounded rectangle with a color
		///@param rectangle Rectangle to be drawn
		///@param radius Radius of the rounded angles
		///@param color Color
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorR<T> & color, BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief Draw a rounded rectangle with a color
		///@param rectangle Rectangle to be drawn
		///@param radius Radius of the rounded angles
		///@param color Color
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorRGB<T> & color, BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		///@brief Draw a rounded rectangle with a color
		///@param rectangle Rectangle to be drawn
		///@param radius Radius of the rounded angles
		///@param color Color
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorRGBA<T> & color, BlendFunc & blendFunc = BlendingFunc::Normal( ) );


		///@brief Draw a rounded rectangle with a color Functor
		///@param rectangle Rectangle to be drawn
		///@param radius Radius of the rounded angles
		///@param colorFunc Color Functor
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		///@see Graphic::ColorFunc::SimpleColor for a solid color functor
		///@see Graphic::ColorFunc::Template for making your own color functor
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangleRoundedFunctor( const Rectangle & rectangle, unsigned int radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal( ) );



		///@brief Resize the image with re sampling and return the new one
		///@param newSize size of the resulting image
		///@param resamplingMode Mode used to compute the resulting pixels 
		///						Nearest : Faster algorithm available, use the nearest pixel without any transformation.
		///						Linear : Do a linear interpolation to compute the resulting pixels.
		///						Lanczos : Use the Lanczos algorithm with a constant of 3 (Note : only available for strict reduction, linear will be used instead)
		///@see https://en.wikipedia.org/wiki/Lanczos_resampling
		_Image<T> resample( const Math::Vec2<Size> & newSize, ResamplingMode resamplingMode = ResamplingMode::Nearest ) const;


		///@brief Draw a filed Polygon
		///@param vertices table of vertices to be drawn (vertices have to be between 0.0 and 1.0)
		///@param nbVertices Number of vertices to draw
		///@param rectangle Rectangle of the image where to draw the polygon
		///@param colorFunc Color Functor to be used (@see Graphic::ColorFunc::Template for making your own)
		///@param blendFunc Blending Functor to be used with operator() overloaded with : 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		///@see Graphic::ColorFunc::SimpleColor for a solid color functor
		///@see Graphic::ColorFunc::Template for making your own color functor
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawPolygonFunctor( const Math::Vec2<float> * vertices, typename Vector<Math::Vec2<float>>::Size nbVertices, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal() );



		///@brief Draw a filed Disk
		///@param p Center point of the disk
		///@param radius Radius of the circle in pixels
		///@param c Color used to fill the disk
		///@param blendFunc Blending Functor to be used with operator() overloaded with : 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc>
		void drawDisk( const Point & p, float radius, ColorR<T> & c, BlendFunc & blendFunc = BlendingFunc::Normal() );

		///@brief Draw a filed Disk
		///@param p Center point of the disk
		///@param radius Radius of the circle in pixels
		///@param c Color used to fill the disk
		///@param blendFunc Blending Functor to be used with operator() overloaded with : 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc>
		void drawDisk( const Point & p, float radius, ColorRGB<T> & c, BlendFunc & blendFunc = BlendingFunc::Normal() );

		///@brief Draw a filed Disk
		///@param p Center point of the disk
		///@param radius Radius of the circle in pixels
		///@param c Color used to fill the disk
		///@param blendFunc Blending Functor to be used with operator() overloaded with : 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc)const;"
		template<typename ColorFunc, typename BlendFunc>
		void drawDisk( const Point & p, float radius, ColorRGBA<T> & c, BlendFunc & blendFunc = BlendingFunc::Normal() );


		///@brief Draw a filed Disk
		///@param p Center point of the disk
		///@param radius Radius of the circle in pixels
		///@param colorFunc Color Functor to be used
		///@param blendFunc Blending Functor to be used with operator() overloaded with : 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc, float alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		///@see Graphic::ColorFunc::SimpleColor for a solid color functor
		///@see Graphic::ColorFunc::Template for making your own color functor
		template<typename ColorFunc, typename BlendFunc>
		void drawDiskFunctor( const Point & p, float radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal() );





		
		/************************************************************************/
		/* Kernels                                                              */
		/************************************************************************/
		///@brief compute the Vertical/Horizontal Gaussian Kernel (K : Type of Values in your Kernel, N : Size of your kernel (has to be odd))
		///@param kernel table to be filled (has to be already allocated)
		///@param sigma Sigma used during the computation
		///@return The weight computed
		template<typename K, size_t N>
		static K computeGaussianKernel( K( &kernel )[N], const float & sigma );

		///@brief compute the Vertical/Horizontal Gaussian Kernel (K : Type of Values in your Kernel, N : Size of your kernel (has to be odd))
		///@param kernel table to be filled (has to be already allocated)
		///@return The weight computed
		template<typename K, size_t N>
		static K computeGaussianKernel( K( &kernel )[N] );

		///@brief compute the Vertical/Horizontal Gaussian Kernel (K : Type of Values in your Kernel )
		///@param kernel table to be filled (has to be already allocated)
		///@param size (Radius * 2 + 1) of the kernel (must be odd)
		///@param sigma Sigma used during the computation
		///@return The weight computed
		template<typename K>
		K computeGaussianKernel( K * kernel, size_t size, const float & sigma );
		static float computeGaussianKernel( float * kernel, size_t size, const float & sigma );
		static double computeGaussianKernel( double * kernel, size_t size, const double & sigma );

		///@brief compute the Vertical/Horizontal Gaussian Kernel (K : Type of Values in your Kernel )
		///@param kernel table to be filled (has to be already allocated)
		///@param size (Radius * 2 + 1) of the kernel (must be odd)
		///@return The weight computed
		template<typename K>
		static K computeGaussianKernel( K * kernel, size_t size );
		static float computeGaussianKernel( float * kernel, size_t size );
		static double computeGaussianKernel( double * kernel, size_t size );




		


		
	protected:


	private:
		template<typename K>
		static K _computeGaussianKernelf( K * kernel, size_t size, const K & sigma );
		template<typename K>
		static K _computeGaussianKernelf( K * kernel, size_t size );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawDiskFunctor( const Point & p, float radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal() );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawPolygonFunctor( const Math::Vec2<float> * vertices, typename Vector<Math::Vec2<float>>::Size nbVertices, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal() );

		template<typename C1, typename Sum>
		_Image<T> _resample( const Math::Vec2<Size> & newSize, ResamplingMode resamplingMode = ResamplingMode::Nearest ) const;

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawRectangleRoundedFunctor( const Rectangle & rectangle, unsigned int radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctorFilledBottom( const LineF & l, ColorFunc & colorFunc, const Rectangle & rectangle, const BlendFunc & blendFunc );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawGraphValuesFunctor( const Vector<Math::Vec2<float>> & values, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, const C2 & color, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename ColorFunc, typename BlendFunc, typename C1, typename C2>
		void _drawStroke( const Point & point, const _Image<T> & image, unsigned int width, ColorFunc & colorFunc, StrokeType strokeType, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename ThreshFunc, typename C1, typename C2>
		void _threshold( const C2 & colorTrue, const C2 & colorFalse, const ThreshFunc & threshFunc );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawLine( const LineF & l, const C2 & color, unsigned int thickness, const BlendFunc & blendFunc );

		template<typename ColorFunc, typename BlendFunc, typename C1, typename I>
		void _drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, const I * t );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, const float * t );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, const double * t );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctorf( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc );

		template<typename C1, typename C2>
		void _fillImage( const C2 & color );

		template<typename C1, typename C2>
		void _fillImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image );

		template<typename C1, typename C2, typename InterFunc>
		void _fillImage( const GradientHorizontal<C2, InterFunc> & color, const Rectangle & rectangle );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage, const BlendFunc & functor = BlendingFunc::Normal( ) );

		template< typename ColorFunc, typename BlendFunc, typename C1>
		void _drawImage( const Point & point, ColorFunc & colorFunc, const Rectangle & rectangle, const _Image<T> & maskImage, const BlendFunc & blendFunc = BlendingFunc::Normal( ) );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image, const BlendFunc & blendFunc );

		template<typename C1, typename C2>
		void _drawImage( const Point & point, const Rectangle & rectangle, const _Image<T> & image );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawRectangleFunctor( const Rectangle & rectangle, ColorFunc & colorFunctor, const BlendFunc & blendingFunctor = BlendingFunc::Normal( ) );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawRectangle( const Rectangle & rectangle, const C2 & color, const BlendFunc & functor = BlendingFunc::Normal( ) );

		template<typename Functor, typename C>
		void _setPixels( Functor & functor, const Rectangle & rectangle );

		template<typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const GradientHorizontal<C2, InterFunc> & gradient );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const GradientLinear<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const GradientRadial<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const GradientHorizontal<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const GradientVertical<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		void _allocateAndCopy( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );

		static Format _loadingFormat2Format( LoadingFormat loadingFormat );


		template<typename C1, typename Sum, typename KernelFunc, typename F>
		_Image<T> _applyFilter( const F * filter, Size size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename C1, typename KernelFunc, typename F>
		_Image<T> _applyFilterf( const F * filter, Size size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename C1, typename Sum, typename KernelFunc >
		_Image<T> _applyFilter( const float * filter, Size size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename C1, typename Sum, typename KernelFunc >
		_Image<T> _applyFilter( const double * filter, Size size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;


		template<typename C1, typename Sum, typename KernelFunc, typename F>
		_Image<T> _applyFilter( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename C1, typename Sum, typename KernelFunc>
		_Image<T> _applyFilter( const float * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename C1, typename Sum, typename KernelFunc>
		_Image<T> _applyFilter( const double * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename C1, typename KernelFunc, typename F>
		_Image<T> _applyFilterf( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T> & color, KernelFunc & func ) const;

		template<typename SumType, typename C>
		_Image<T> * _createMipmap( _Image<T> * destinationImage );

		bool _read( std::fstream * fileStream );


		template<typename C, typename D>
		inline static void _castComponment( D * dest, const C * source );
		inline static void _castComponment( unsigned char * dest, const float * source );
		inline static void _castComponment( unsigned char * dest, const double * source );
		inline static void _castComponment( float * dest, const unsigned char * source );
		inline static void _castComponment( double * dest, const unsigned char * source );


		Format format;
		Math::Vec2<Size> size;
		size_t nbPixels;
		T * buffer;

	};


	typedef _Image<unsigned char> Image;
	typedef _Image<float> ImageF;



}


#include "Image.hpp"
