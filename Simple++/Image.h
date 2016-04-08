#pragma once


#include "Log.h"
#include "BasicLoadableIO.h"
#include "Math.h"
#include "Vector.h"
#include "String.h"
#include "Utility.h"
#include "BasicIO.h"






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


	///@brief Image Class
	///@template T Type of one pixel
	///@template F Format of the image
	template<typename T = unsigned char>		
	class _Image : public BasicIO {
	public:

		enum class LoadingFormat { R, RGB, BGR, RGBA, ABGR };
		enum class ConvolutionMode {NormalSize, ExtendedSize};


		
		///@brief copy constructor with an another storage type
		///@param image image to copy
		template<typename C>
		_Image(const _Image<C> & image);

		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		_Image(Format format = Format::RGB);

		///@brief Constructor to create an initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		_Image(const Math::vec2ui & size, Format format = Format::RGB);

		///@brief create a new image data from a file stream.
		///@param fileStream Stream to read
		///@param format of the image
		_Image(std::fstream * fileStream);


		///@brief Constructor to create an image from a data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		_Image(const T * data, const Math::vec2ui & size, Format format = Format::RGB, bool invertY = false);

		///@brief copy constructor
		_Image(const _Image<T> & image);

		///@brief move constructor
		_Image(_Image<T> && image);

		~_Image();

		///@brief get the actual size (width:height) of the image
		///@return the actual size of this image
		const Math::vec2ui & getSize() const;

		///@brief get the actual width of the image
		///@return actual width of this image
		unsigned int getWidth() const;

		///@brief get the actual height of the image
		///@return actual height of this image
		unsigned int getHeight() const;

		
		///@brief get the number of pixels of this image
		///@return number of pixels
		size_t getNbPixels() const;

		///@brief reset this image with a new size.
		///@param size new size
		void clear(const Math::vec2ui & size);


		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear(const Math::vec2ui & size, Format format);


		///@brief set the data from an another data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param invertY if the image has to be flipped vertically or not.
		void setDatas(const T * data, const Math::vec2ui & size, Format format = Format::RGB, bool invertY = false);


		///@brief create a new image from this one with a size of width / 2 and height / 2
		///@return new image created from this one with an halved size.
		template<typename C = unsigned short>
		_Image<T> * createMipmap();					

		///@brief get the data buffer of this image 
		///@return data buffer
		const T * getDatas() const;

		///@brief get the data buffer of this image 
		///@return data buffer
		T * getDatas();


		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel(unsigned int x, unsigned int y) const;

		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		T * getPixel(unsigned int x, unsigned int y);


		///@brief get the offset of pixel from the beginning of the data
		///@param x X coordinate
		///@param y Y coordinate
		///@return offset to be added to go from the begining of the data (getData()) and the selected pixel
		size_t getDataOffset(unsigned int x, unsigned int y) const;



		///@brief set a pixel inside this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel(unsigned int x, unsigned int y, const T * p);



		///@brief copy operator with another type
		///@param image Image to copy
		template<typename C>
		_Image<T> & operator=(const _Image<C> & image);

		///@brief copy operator
		///@param image Image to copy
		_Image<T> & operator=(const _Image<T> & image);

		///@brief move operator
		///@param image Image to move from
		_Image<T> & operator=(_Image<T> && image);


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(std::fstream * fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(std::fstream * fileStream) const;

		///@brief get the format of this image
		///@return format of this image
		Format getFormat() const;


		///@brief  get the number of components per pixels of this image.
		///@return Number of components per pixels.
		inline unsigned int getNbComponents() const;

		/************************************************************************/
		/* Drawing methods                                                      */
		/************************************************************************/


		///@brief fill the complete image with a color.
		///param color pointer to a color with the same number of component of this image
		void fill(const T * color);

		///@brief fill the complete image with a color.
		///@param color pointer to a color with the same number of component of this image
		///@param rectangle Rectangle where to fill the color
		void fill(const T * color, const Rectangle & rectangle);



		///@brief fill the complete image with a color.
		///@param color R color
		void fill(const ColorR<T> & color);

		///@brief fill the complete image with a color.
		///@param color RGB color
		void fill(const ColorRGB<T> & color);

		///@brief fill the complete image with a color.
		///@param color RGBA color
		void fill(const ColorRGBA<T> & color);


		///@brief fill the complete image with a color.
		///@param color R color
		///@param rectangle Rectangle where to fill the color
		void fill(const ColorR<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color RGB color
		///@param rectangle Rectangle where to fill the color
		void fill(const ColorRGB<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color RGBA color
		///@param rectangle Rectangle where to fill the color
		void fill(const ColorRGBA<T> & color, const Rectangle & rectangle);



		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param image Another image to draw
		void drawImage(const Point & point, const _Image<T> & image);


		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image);


		///@brief draw an another image into this one with a custom blending function
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		///@param blending function of type (template<typename C> void blendingFunc(Format destFormat, Format sourceFormat, C * destPixel, const C * sourcePixel) )
		template<typename Func>
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, Func blendingFunc);





		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorR<T> & color, const _Image<T> & maskImage);

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGB<T> & color, const _Image<T> & maskImage);

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGBA<T> & color, const _Image<T> & maskImage);

		




		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage);


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage);


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage);


		


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const _Image<T> & image, const _Image<T> & maskImage);

		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage);


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage);





		///@brief apply a symmetrical convolution filter (gaussian blur for exemple)
		///@param filter Filter table (the table has to have an odd size)
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@return Image with the filter applied
		template<typename C, int N>
		_Image<T> applyFilter(const C(&filter)[N],  ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null) const;


		

	protected:


	private:

		template<typename C, int N>
		_Image<T> _applyFilter(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<typename C, int N>
		_Image<T> _applyFilterf(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<int N>
		_Image<T> _applyFilter(const float(&filter)[N], ConvolutionMode convolutionMode , const ColorRGBA<T> & color) const;

		template<int N>
		_Image<T> _applyFilter(const double(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<typename C = Math::vec3ui, typename PIX>
		_Image<T> * _createMipmap(_Image<T> * destinationImage);

		bool _read(std::fstream * fileStream);


		template<typename C, typename D>
		inline static void _castComponment(D * dest, const C * source);
		inline static void _castComponment(unsigned char * dest, const float * source);
		inline static void _castComponment(unsigned char * dest, const double * source);
		inline static void _castComponment(float * dest, const unsigned char * source);
		inline static void _castComponment(double * dest, const unsigned char * source);


		template<typename C>
		inline static void _blendPixelRtoR(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRtoR(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRtoR(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRtoR(double * pixelDest, const double * pixelSource, const double * maskPixel);



		template<typename C>
		inline static void _blendPixelRtoRGB(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRtoRGB(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRtoRGB(double * pixelDest, const double * pixelSource, const double * maskPixel);


		template<typename C>
		inline static void _blendPixelRtoRGBA(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRtoRGBA(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRtoRGBA(double * pixelDest, const double * pixelSource, const double * maskPixel);


		template<typename C>
		inline static void _blendPixelRGBtoR(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRGBtoR(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRGBtoR(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRGBtoR(double * pixelDest, const double * pixelSource, const double * maskPixel);

		template<typename C>
		inline static void _blendPixelRGBtoRGB(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRGBtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRGBtoRGB(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRGBtoRGB(double * pixelDest, const double * pixelSource, const double * maskPixel);

		template<typename C>
		inline static void _blendPixelRGBtoRGBA(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRGBtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRGBtoRGBA(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRGBtoRGBA(double * pixelDest, const double * pixelSource, const double * maskPixel);



		template<typename C>
		inline static void _blendPixelRGBAtoR(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRGBAtoR(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRGBAtoR(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRGBAtoR(double * pixelDest, const double * pixelSource, const double * maskPixel);

		template<typename C>
		inline static void _blendPixelRGBAtoRGB(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRGBAtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRGBAtoRGB(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRGBAtoRGB(double * pixelDest, const double * pixelSource, const double * maskPixel);

		template<typename C>
		inline static void _blendPixelRGBAtoRGBA(C * pixelDest, const C * pixelSource, const C * maskPixel);
		inline static void _blendPixelRGBAtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource, const unsigned char * maskPixel);
		inline static void _blendPixelRGBAtoRGBA(float * pixelDest, const float * pixelSource, const float * maskPixel);
		inline static void _blendPixelRGBAtoRGBA(double * pixelDest, const double * pixelSource, const double * maskPixel);





		template<typename C>
		inline static void _blendPixelRtoRGBA(C * pixelDest, const C * pixelSource);
		inline static void _blendPixelRtoRGBA(float * pixelDest, const float * pixelSource);
		inline static void _blendPixelRtoRGBA(double * pixelDest, const double * pixelSource);

		template<typename C>
		inline static void _blendPixelRGBtoRGBA(C * pixelDest, const C * pixelSource);
		inline static void _blendPixelRGBtoRGBA(float * pixelDest, const float * pixelSource);
		inline static void _blendPixelRGBtoRGBA(double * pixelDest, const double * pixelSource);

		template<typename C>
		inline static void _blendPixelRGBAtoRGBA(C * pixelDest, const C * pixelSource);
		inline static void _blendPixelRGBAtoRGBA(unsigned char * pixelDest, const unsigned char * pixelSource);
		inline static void _blendPixelRGBAtoRGBA(float * pixelDest, const float * pixelSource);
		inline static void _blendPixelRGBAtoRGBA(double * pixelDest, const double * pixelSource);

		template<typename C>
		inline static void _blendPixelRtoRGB(C * pixelDest, const C * pixelSource);

		template<typename C>
		inline static void _blendPixelRGBtoR(C * pixelDest, const C * pixelSource);
		inline static void _blendPixelRGBtoR(float * pixelDest, const float * pixelSource);
		inline static void _blendPixelRGBtoR(double * pixelDest, const double * pixelSource);

		template<typename C>
		inline static void _blendPixelRGBAtoRGB(C * pixelDest, const C * pixelSource);
		inline static void _blendPixelRGBAtoRGB(unsigned char * pixelDest, const unsigned char * pixelSource);
		inline static void _blendPixelRGBAtoRGB(float * pixelDest, const float * pixelSource);
		inline static void _blendPixelRGBAtoRGB(double * pixelDest, const double * pixelSource);

		template<typename C>
		inline static void _blendPixelRGBAtoR(C * pixelDest, const C * pixelSource);
		inline static void _blendPixelRGBAtoR(unsigned char * pixelDest, const unsigned char * pixelSource);
		inline static void _blendPixelRGBAtoR(float * pixelDest, const float * pixelSource);
		inline static void _blendPixelRGBAtoR(double * pixelDest, const double * pixelSource);


		inline static T _getComponmentMaxValue();

		template<typename C>
		inline static void sumComponmentsRGB(const C * destBuffer, const T * inBuffer, size_t numPixels);

		Format format;
		Math::vec2ui size;
		size_t nbPixels;
		T * buffer;

	};

	template<typename T /*= unsigned char*/>
	unsigned int Graphic::_Image<T>::getNbComponents() const {
		return (unsigned int) this -> format;
	}


	template<typename T>
	template<typename C>
	void _Image<T>::sumComponmentsRGB(const C * destBuffer, const T * inBuffer, size_t numPixels) {

		destBuffer[0] = C(0);

		for ( size_t i = 0; i < numPixels; i++ ) {
			destBuffer[i] += inBuffer[i];
			buffer ++;
		}

	}



	typedef _Image<unsigned char> Image;
	typedef _Image<float> ImageF;



}


#include "Image.hpp"