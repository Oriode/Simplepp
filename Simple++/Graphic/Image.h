///@file Image.h
///@brief Image Class with some drawing methods
///@author Clément Gerber
///@date 19/04/2016 (DMY) 



#pragma once


#include "../Log.h"
#include "../Math/Math.h"
#include "../Vector.h"
#include "../String.h"
#include "../Utility.h"
#include "../IO/BasicIO.h"
#include "Gradient.h"
#include "BlendingFunc.hpp"
#include "ColorFunc.h"
#include "KernelFunc.hpp"
#include "ColorConvertFunc.hpp"




namespace Graphic {





	///@brief Image Class
	///@template T Type of one pixel
	///@template F Format of the image
	template<typename T = unsigned char>
	class ImageT : public BasicIO {
	public:
		enum class ResamplingMode { Nearest, Bilinear, Lanczos };
		enum class ConvolutionMode { NormalSize, ExtendedSize };
		enum class ConvolutionOrder { HorizontalVertical, VerticalHorizontal };
		enum class StrokeType { Outside, Inside, Middle };

		///@brief Type used to sum multiple pixels components
		typedef typename Color<T>::SumType SumType;

		///@brief Type used to sum multiple pixels components multiplied with a negative value
		typedef typename Color<T>::KernelType KernelType;

		///@brief Floating type used for this type of image
		typedef typename Color<T>::Float Float;

		///@brief copy constructor
		///@param image Image to copy
		///@param normalize if the data has to be normalized to the new type
		///@param convertFunc Functor used to convert each pixels overloaded with :
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///@see Graphic::ColorConvertFunc
		ImageT( const ImageT<T> & image, bool normalize = true );

		///@brief copy constructor with an another storage type
		///@param image image to copy
		///@param normalize if the data has to be normalized to the new type
		///@param convertFunc Functor used to convert each pixels overloaded with :
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///@see Graphic::ColorConvertFunc
		template<typename C>
		ImageT( const ImageT<C> & image, bool normalize = true );

		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		ImageT( Format format = Format::RGB );

		///@brief Constructor to create an initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		ImageT( const Math::Vec2<Size> & size, Format format = Format::RGB );

		///@brief create a new image data from a file stream.
		///@param fileStream Stream to read
		///@param format of the image
		ImageT( std::fstream * fileStream );


		///@brief Constructor to create an image from a data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		///@param stride width of ONE line of the image data in bytes, if stride == 0, the lines are supposed to be contiguous without any padding
		ImageT( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );
		template<typename U>
		ImageT( const U * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );

		///@brief move constructor
		ImageT( ImageT<T> && image );

		~ImageT();

		///@brief get the actual size (width:height) of the image
		///@return the actual size of this image
		const Math::Vec2<Size> & getSize() const;

		///@brief get the actual width of the image
		///@return actual width of this image
		Size getWidth() const;

		///@brief get the actual height of the image
		///@return actual height of this image
		Size getHeight() const;


		///@brief get the number of pixels of this image
		///@return number of pixels
		size_t getNbPixels() const;


		///@brief reset this image as empty.
		void clear(  );

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
		template<typename U>
		void setDatas( const U * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );


		///@brief create a new image from this one with a size of width / 2 and height / 2
		///@return new image created from this one with an halved size.
		ImageT<T> * createMipmap();

		///@brief get the data buffer of this image 
		///@return data buffer
		const T * getDatas() const;
		template<typename C>
		const C * getDatas() const;

		///@brief get the data buffer of this image 
		///@return data buffer
		T * getDatas();
		template<typename C>
		C * getDatas();


		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		const T * getDatas( Size x, Size y ) const;
		template<typename C>
		const C * getDatas( Size x, Size y ) const;



		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		T * getDatas( Size x, Size y );
		template<typename C>
		C * getDatas( Size x, Size y );

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
		ImageT<T> & operator=( const ImageT<C> & image );

		///@brief copy operator
		///@param image Image to copy
		ImageT<T> & operator=( const ImageT<T> & image );

		///@brief move operator
		///@param image Image to move from
		ImageT<T> & operator=( ImageT<T> && image );


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
		Format getFormat() const;




		///@brief  get the number of components per pixels of this image.
		///@return Number of components per pixels.
		inline unsigned int getNbComponents() const;


		///@brief Create a new Image from this one with a new format
		///@param newFormat Format of the new image
		///@param convertFunc Functor used to convert each pixels overloaded with :
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///@see Graphic::ColorConvertFunc
		///@return Image based of this one with a new format
		template<typename ConvertFunc = ColorConvertFunc::Luminance>
		ImageT<T> toFormat( Format newFormat, ConvertFunc & convertFunc = ColorConvertFunc::Luminance() ) const;





		/************************************************************************/
		/* Gradient                                                             */
		/************************************************************************/
		///@brief Compute the interpolation for horizontal gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const Gradient::Horizontal<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;


		///@brief Compute the interpolation for vertical gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const Gradient::Vertical<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;


		///@brief Compute the interpolation for Linear gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const Gradient::Linear<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;

		///@brief Compute the interpolation for Radial gradient
		///@param out buffer Pointer to a buffer that will be allocated (will be deletable with delete [])
		///@param in rectangle used to specify the size of the gradient
		///@param out clampedRectangle Rectangle clamped inside this image
		///return size of the freshly allocated buffer
		template<typename C, typename InterFunc>
		size_t computeInterpolation( const Gradient::Radial<C, InterFunc> & gradient, C ** buffer, const Rectangle & rectangle, Math::Rectangle<Size> * clampedRectangle ) const;

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
		void drawLine( const LineF & l, const ColorR<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendFunc() );

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
		void drawLine( const LineF & l, const ColorRGB<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendFunc() );

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
		void drawLine( const LineF & l, const ColorRGBA<T> & color, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendFunc() );


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
		void drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness = 1, const BlendFunc & blendFunc = BlendFunc() );

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
		void drawRectangle( const Rectangle & rectangle, const ColorR<T> & color, const BlendFunc & blendFunc = BlendFunc() );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const ColorRGB<T> & color, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param color Color to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const ColorRGBA<T> & color, const BlendFunc & blendFunc = BlendFunc() );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		template<typename C, typename InterFunc>
		void drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C, InterFunc> & gradient );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const Gradient::Linear<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendFunc() );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Blending functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const Gradient::Radial<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendFunc() );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrcc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc>
		void drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc );

		///@brief draw a rectangle inside this image.
		///@param rectangle Rectangle representing the pixels to draw. (the rectangle is clamped inside the image)
		///@param gradient Gradient to draw.
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc)const;"
		template<typename C, typename InterFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawRectangle( const Rectangle & rectangle, const Gradient::Vertical<C, InterFunc> & gradient, const BlendFunc & blendFunc = BlendFunc() );


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
		void drawRectangleFunctor( const Rectangle & rectangle, ColorFunc & colorFunc, const BlendFunc & blendFunc = BlendFunc() );


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
		void fillImage( const Gradient::Horizontal<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill the complete image with a vertical gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const Gradient::Vertical<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill the complete image with a Linear gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const Gradient::Linear<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill the complete image with a Radial gradient.
		///@param gradient Gradient
		///@param rectangle Rectangle where to fill the gradient
		template<typename C, typename InterFunc>
		void fillImage( const Gradient::Radial<C, InterFunc> & gradient, const Rectangle & rectangle );

		///@brief fill an another image into this one (no blending will be applied)
		///@param point Position where to draw.
		///@param rectangle rectangle of the image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void fillImage( const Point & point, const ImageT<T> & image );

		///@brief fill an another image into this one (no blending will be applied)
		///@param point Position where to draw.
		///@param rectangle rectangle of the image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void fillImage( const Point & point, const Rectangle & rectangle, const ImageT<T> & image );


		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param image Another image to draw
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<bool Fast = false>
		void drawImage( const Point & point, const ImageT<T> & image );


		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<bool Fast = false>
		void drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle );


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
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const BlendFunc & blendFunc = BlendFunc() );



		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ColorR<T> & color, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ColorRGB<T> & color, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ColorRGBA<T> & color, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param colorFunc functor that will generate the color for each pixels (see Graphic::ColorFunc::Template), width the methods :
		///					"inline void init(const Rectangle & rectangle);"
		///					"inline const C & operator()(const Math::Vec2<Size> & p) const;"
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImageFunctor( const Point & point, ColorFunc & colorFunc, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<bool Fast = false>
		void drawImage( const Point & point, const ImageT<T> & image, const ImageT<T> & maskImage );

		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<bool Fast = false>
		void drawImage( const Point & point, const ImageT<T> & image, const Point & maskPoint, const ImageT<T> & maskImage );


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc, T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc, const T & colorMask)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc, const T & colorMask)const;"
		///@template Fast if the methods will check for overflow (set this to true only if you know exactly what you are doing)
		template<typename BlendFunc = BlendingFunc::Normal, bool Fast = false>
		void drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const Point & maskPoint, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );


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
		void drawStrokeFunctor( const Point & point, const ImageT<T> & image, float thickness, ColorFunc & colorFunc, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendFunc() );


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
		void drawStroke( const Point & point, const ImageT<T> & image, float thickness, const ColorR<T> & color, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendFunc() );

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
		void drawStroke( const Point & point, const ImageT<T> & image, float thickness, const ColorRGB<T> & color, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendFunc() );

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
		void drawStroke( const Point & point, const ImageT<T> & image, float thickness, const ColorRGBA<T> & color, StrokeType strokeType = StrokeType::Middle, const BlendFunc & blendFunc = BlendFunc() );



		///@brief Draw the shadow of an image into this one
		///@param point where to draw the shadow
		///@param thickness size of the blurring of the shadow
		///@param image image from where to create a shadow
		///@param color Color to be used to draw the shadow
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorR<T> & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, const T & alpha)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImageShadow( const Point & point, unsigned int thickness, const ImageT<T> & image, const ColorR<T> & color, const BlendFunc & blendFunc = BlendFunc() );

		///@brief Draw the shadow of an image into this one
		///@param point where to draw the shadow
		///@param thickness size of the blurring of the shadow
		///@param image image from where to create a shadow
		///@param color Color to be used to draw the shadow
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, const T & alpha)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImageShadow( const Point & point, unsigned int thickness, const ImageT<T> & image, const ColorRGB<T> & color, const BlendFunc & blendFunc = BlendFunc() );

		///@brief Draw the shadow of an image into this one
		///@param point where to draw the shadow
		///@param thickness size of the blurring of the shadow
		///@param image image from where to create a shadow
		///@param color Color to be used to draw the shadow
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, const T & alpha)const;"
		template<typename BlendFunc = BlendingFunc::Normal>
		void drawImageShadow( const Point & point, unsigned int thickness, const ImageT<T> & image, const ColorRGBA<T> & color, const BlendFunc & blendFunc = BlendFunc() );


		///@brief Draw the shadow of an image into this one
		///@param point where to draw the shadow
		///@param thickness size of the blurring of the shadow
		///@param image image from where to create a shadow
		///@param colorFunc functor that will generate the color for each pixels, width the methods :
		///					"inline void init(const Rectangle & rectangle);"
		///					"inline const C & operator()(const Math::Vec2<Size> & p) const;"
		///@param blendFunc Functor with operator() overloaded with 
		///					"template<typename T> void operator()(Graphic::ColorR<T> & colorDest, const C & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGB<T> & colorDest, const C & colorSrc, const T & alpha)const;"
		///					"template<typename T> void operator()(Graphic::ColorRGBA<T> & colorDest, const C & colorSrc, const T & alpha)const;"
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawImageShadowFunctor( const Point & point, unsigned int thickness, const ImageT<T> & image, ColorFunc & colorFunc, const BlendFunc & blendFunc = BlendFunc() );


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
		void drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorR<T> & color, const BlendFunc & blendFunc = BlendFunc() );

		template<typename BlendFunc = BlendingFunc::Normal>
		void drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorRGB<T> & color, const BlendFunc & blendFunc = BlendFunc() );

		template<typename BlendFunc = BlendingFunc::Normal>
		void drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, ColorRGBA<T> & color, const BlendFunc & blendFunc = BlendFunc() );


		///@brief draw points (x,y) as a graph inside a rectangle
		///@param values Vector of floating points (points has to be between 0.0 and 1.0) (the points has to be ascending ordered using their x coordinate)
		///@param rectangle Rectangle where to draw the graph
		///@param colorFunc Color Functor used to draw
		///@param blendFunc Blending Functor used to draw
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawGraphValuesFunctor( const Vector<Math::Vec2<float>> & values, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );


		///@brief Change the Hue Saturation Lightness of this image
		///@param hueBias Value added to the Hue value of each pixel [ -359 ; 359 ]
		///@param saturationFactor Factor multiplied to the saturation of each pixel (must be positive)
		///@param lightnessFactor Factor multiplied to the lightness of each pixel (must be positive)
		void changeHueSaturationLightness( int hueBias, const Float & saturationFactor, const Float & lightnessFactor );

		///@brief Get the number of bits of the sum of a kernel depending of the types used
		///@return number of bits of the sum of a integer kernel (floating kernel will every Time/Time.has a sum of 1.0)
		template<typename K>
		constexpr static K getKernelSumNbBits();

		///@brief apply a symmetrical convolution filter (Gaussian blur for example)
		///@template T1 Type of the value of this image (most of the time T)
		///@param filter Filter table (the table has to have an odd size)
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@param kernelFunc Function to be used to treat the summation before dividing it (Handle overflow, negatives values etc...)
		///@see _Image<T>::SumType for an automatically generated Filter Type
		///@see Graphic::KernelFunc for many preconfigured functors
		///@return Image with the filter applied
		template<typename F, typename KernelFunc = KernelFunc::None, typename T1 = T>
		ImageT<T> applyFilter( const F * filterX, const F * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null, KernelFunc & kernelFunc = KernelFunc::None() ) const;


		///@brief Apply a convolution filter
		///@template T1 Type of the value of this image (most of the time T)
		///@param filter Filter Matrix of size (size.x * size.y) stored row per row from bottom to top from left to right
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@param kernelFunc Function to be used to treat the summation before dividing it (Handle overflow, negatives values etc...)
		///@see _Image<T>::SumType for an automatically generated Filter Type
		///@see Graphic::KernelFunc for many preconfigured functors
		///@return Image with the filter applied
		template<typename F, typename KernelFunc = KernelFunc::None, typename T1 = T>
		ImageT<T> applyFilter( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null, KernelFunc & kernelFunc = KernelFunc::None() ) const;


		///@brief apply a Gaussian Blur Filter
		///@param radius Radius of the blur
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@return Image with the filter applied
		ImageT<T> applyGaussianBlur( Size radius, ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::black ) const;

		///@brief apply a Sobel filter and return the resulting image (note the final pixels components will be "min(sqrt(x*x + y*y) / 2, MAX)" where x is the sobel filter horizontal and y vertical)
		///@return Image with the Sobel filter applied
		///@see https://en.wikipedia.org/wiki/Sobel_operator
		ImageT<T> applySobelFilter();


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
		void drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorR<T> & color, BlendFunc & blendFunc = BlendFunc() );

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
		void drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorRGB<T> & color, BlendFunc & blendFunc = BlendFunc() );

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
		void drawRectangleRounded( const Rectangle & rectangle, unsigned int radius, const ColorRGBA<T> & color, BlendFunc & blendFunc = BlendFunc() );


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
		void drawRectangleRoundedFunctor( const Rectangle & rectangle, unsigned int radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );



		///@brief Resize the image with re sampling and return the new one
		///@param newSize size of the resulting image
		///@param resamplingMode Mode used to compute the resulting pixels 
		///						Nearest : Faster algorithm available, use the nearest pixel without any transformation.
		///						Linear : Do a linear interpolation to compute the resulting pixels.
		///						Lanczos : Use the Lanczos algorithm with a constant of 3 (Note : only available for strict reduction, linear will be used instead)
		///@see https://en.wikipedia.org/wiki/Lanczos_resampling
		ImageT<T> resample( const Math::Vec2<Size> & newSize, ResamplingMode resamplingMode = ResamplingMode::Nearest ) const;


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
		void drawPolygonFunctor( const Math::Vec2<float> * vertices, typename Vector<Math::Vec2<float>>::Size nbVertices, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );



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
		void drawDisk( const Point & p, float radius, ColorR<T> & c, BlendFunc & blendFunc = BlendFunc() );

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
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawDisk( const Point & p, float radius, ColorRGB<T> & c, BlendFunc & blendFunc = BlendFunc() );

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
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawDisk( const Point & p, float radius, ColorRGBA<T> & c, BlendFunc & blendFunc = BlendFunc() );


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
		template<typename ColorFunc, typename BlendFunc = BlendingFunc::Normal>
		void drawDiskFunctor( const Point & p, float radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );






		/************************************************************************/
		/* Kernels                                                              */
		/************************************************************************/
		///@brief compute the Vertical/Horizontal Gaussian Kernel (K : Type of Values in your Kernel, N : Size of your kernel (has to be odd))
		///@param kernel table to be filled (has to be already allocated)
		///@param sigma Sigma used during the computation
		///@return The weight computed
		template<typename K, size_t N>
		static K computeGaussianKernel( K( &kernel )[N], const Float & sigma );

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
		static K computeGaussianKernel( K * kernel, size_t size, const Float & sigma );
		static float computeGaussianKernel( float * kernel, size_t size, const float & sigma );
		static double computeGaussianKernel( double * kernel, size_t size, const double & sigma );

		///@brief compute the Vertical/Horizontal Gaussian Kernel (K : Type of Values in your Kernel )
		///@param kernel table to be filled (has to be already allocated)
		///@param size (Radius * 2 + 1) of the kernel (must be odd)
		///@return The weight computed
		template<typename K>
		static K computeGaussianKernel( K * kernel, size_t size );





		///@brief compute the the Sobel kernel [-1 0 1] for this image and put it into a buffer
		///@param kernel buffer to fill with the kernel (already allocated of size 3)
		///@return pound of this kernel
		template<typename K>
		static K computeSobel1Kernel( K * kernel );
		static float computeSobel1Kernel( float * kernel );
		static double computeSobel1Kernel( double * kernel );


		///@brief compute the the Sobel kernel [1 2 1] for this image and put it into a buffer
		///@param kernel buffer to fill with the kernel (already allocated of size 3)
		///@return pound of this kernel
		template<typename K>
		static K computeSobel2Kernel( K * kernel );
		static float computeSobel2Kernel( float * kernel );
		static double computeSobel2Kernel( double * kernel );







	protected:


	private:
		template<typename K, typename ComputeKernelFunc>
		static K _kernelFromFloat2Int( K * kernel, size_t size, ComputeKernelFunc & computeKernelFunc );
		template<typename K>
		static K _computeGaussianKernelf( K * kernel, size_t size, const K & sigma );

		template<typename K>
		static K _computeSobel1Kernelf( K * kernel );
		template<typename K>
		static K _computeSobel2Kernelf( K * kernel );


		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawDiskFunctor( const Point & p, float radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawPolygonFunctor( const Math::Vec2<float> * vertices, typename Vector<Math::Vec2<float>>::Size nbVertices, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );

		template<typename C1, typename Sum, typename SumF, typename K >
		ImageT<T> _resample( const Math::Vec2<Size> & newSize, ResamplingMode resamplingMode = ResamplingMode::Nearest ) const;

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawRectangleRoundedFunctor( const Rectangle & rectangle, unsigned int radius, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctorFilledBottom( const LineF & l, ColorFunc & colorFunc, const Rectangle & rectangle, const BlendFunc & blendFunc );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawGraphValuesFunctor( const Vector<Math::Vec2<float>> & values, const Rectangle & rectangle, ColorFunc & colorFunc, BlendFunc & blendFunc = BlendFunc() );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawBezierCurve( const PointF & p0, const PointF & p1, const PointF p2, const PointF & p3, unsigned int thickness, const C2 & color, const BlendFunc & blendFunc = BlendFunc() );

		template<typename ColorFunc, typename BlendFunc, typename C1, typename C2>
		void _drawStroke( const Point & point, const ImageT<T> & image, float width, ColorFunc & colorFunc, StrokeType strokeType, const BlendFunc & blendFunc = BlendFunc() );

		template<typename ThreshFunc, typename C1, typename C2>
		void _threshold( const C2 & colorTrue, const C2 & colorFalse, const ThreshFunc & threshFunc );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, ... );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctor( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc, typename Float * );


		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawLineFunctorf( const LineF & l, ColorFunc & colorFunc, unsigned int thickness, const BlendFunc & blendFunc );

		template<typename C1, typename C2>
		void _fillImage( const C2 & color );

		template<typename C1, typename C2>
		void _fillImage( const Point & point, const Rectangle & rectangle, const ImageT<T> & image );

		template<typename C1, typename C2, typename InterFunc>
		void _fillImage( const Gradient::Horizontal<C2, InterFunc> & color, const Rectangle & rectangle );

		template<typename BlendFunc, typename C1, typename C2, typename C3, bool Fast>
		void _drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle, const Point & maskPoint, const ImageT<T> & maskImage, const BlendFunc & functor = BlendFunc() );

		template<typename ColorFunc, typename BlendFunc, typename C1, typename C2, bool Fast>
		void _drawImage( const Point & point, ColorFunc & colorFunc, const Rectangle & rectangle, const ImageT<T> & maskImage, const BlendFunc & blendFunc = BlendFunc() );

		template<typename BlendFunc, typename C1, typename C2, bool Fast>
		void _drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle,  const BlendFunc & blendFunc );

		template <typename C1, typename C2, bool Fast>
		void _drawImage( const Point & point, const ImageT<T> & image, const Rectangle & rectangle );

		template<typename ColorFunc, typename BlendFunc, typename C1>
		void _drawRectangleFunctor( const Rectangle & rectangle, ColorFunc & colorFunctor, const BlendFunc & blendingFunctor = BlendFunc() );

		template<typename BlendFunc, typename C1, typename C2>
		void _drawRectangle( const Rectangle & rectangle, const C2 & color, const BlendFunc & functor = BlendFunc() );

		template<typename Functor, typename C>
		void _setPixels( Functor & functor, const Rectangle & rectangle );

		template<typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C2, InterFunc> & gradient );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const Gradient::Linear<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const Gradient::Radial<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const Gradient::Horizontal<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		template<typename BlendFunc, typename C1, typename C2, typename InterFunc>
		void _drawRectangle( const Rectangle & rectangle, const Gradient::Vertical<C2, InterFunc> & gradient, const BlendFunc & blendingFunctor );

		void _allocateAndCopy( const T * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );

		template<typename U>
		void _allocateAndCopy( const U * data, const Math::Vec2<Size> & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false, size_t stride = 0 );

		static Format _loadingFormat2Format( LoadingFormat loadingFormat );


		template<typename C1, typename C2, typename ConvertFunc>
		ImageT<T> _toFormat( Format newFormat, ConvertFunc & convertFunc ) const;

		template<typename C1, typename C2, typename ConvertFunc>
		void _toFormat( C1 * bufferDst, const C2 * bufferSrc, ConvertFunc & convertFunctor ) const;


		template<typename C>
		void _toType( T * bufferDest, const C * bufferSrc, bool normalize );


		template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc, typename F>
		ImageT<T2> _applyFilter( const F * filterX, const F * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename KernelFunc, typename F>
		ImageT<T2> _applyFilterf( const F * filterX, const F * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc >
		ImageT<T2> _applyFilter( const float * filterX, const float * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc >
		ImageT<T2> _applyFilter( const double * filterX, const double * filterY, Size size, ConvolutionOrder convolutionOrder, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc, typename F>
		ImageT<T2> _applyFilter( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc>
		ImageT<T2> _applyFilter( const float * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename Sum, typename KernelFunc>
		ImageT<T2> _applyFilter( const double * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename T1, typename C1, typename T2, typename C2, typename KernelFunc, typename F>
		ImageT<T2> _applyFilterf( const F * filter, const Math::Vec2<Size> & size, ConvolutionMode convolutionMode, const ColorRGBA<T2> & color, KernelFunc & func ) const;

		template<typename SumType, typename C>
		ImageT<T> * _createMipmap( ImageT<T> * destinationImage, ... );


		template<typename SumType, typename C>
		ImageT<T> * _createMipmap( ImageT<T> * destinationImage, typename Float * );

		bool _read( std::fstream * fileStream );



		Format format;
		Math::Vec2<Size> size;
		size_t nbPixels;
		T * buffer;

	};




	typedef ImageT<unsigned char> Image;
	typedef ImageT<float> ImageF;



}


#include "Image.hpp"
