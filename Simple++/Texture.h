#pragma once


#include "Log.h"
#include "BasicLoadableIO.h"
#include "Math.h"
#include "Vector.h"
#include "String.h"
#include "Utility.h"
#include "Image.h"

namespace Graphic {

	template<typename T = unsigned char>		//this is the type of ONE pixel
	class Texture : public BasicIO {
	public:
		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		Texture(typename Format format = Format::RGB);

		///@brief Constructor to create an not initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		Texture(const Math::Vec2<Size> & size, typename Format format = Format::RGB);

		///@brief create a new image using a path to a file (only support official file format)
		Texture(const WString & filePath);

		///@brief create a new Texture using a file stream to read.
		///@param fileStream file stream to read.
		Texture(std::fstream * fileStream);

		///@brief copy constructor
		Texture(const Texture<T> & image);

		///@brief create a Texture from a image data
		///@param dataBuffer buffer of the image to copy.
		///@param size size of the image to copy.
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		Texture(const T * dataBuffer, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);


		///@brief move constructor
		Texture(Texture<T> && image);

		~Texture();

		///@brief get the actual size (width:height) of the image
		///@param i num of the mipmap
		///@return the actual size of this image
		const Math::Vec2<Size> & getSize(typename Vector<_Image<T>>::Size i = 0) const;

		///@brief get the actual width of the image
		///@param i num of the mipmap
		///@return actual width of this image
		unsigned int getWidth(typename Vector<_Image<T>>::Size i = 0) const;

		///@brief get the actual height of the image
		///@param i num of the mipmap
		///@return actual height of this image
		unsigned int getHeight(typename Vector<_Image<T>>::Size i = 0) const;

		///@brief set the data from an another data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param invertY if the image has to be flipped vertically or not.
		void setDatas(const T * data, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);


		///@brief reset this image with a new size.
		///@param size new size
		void clear(const Math::Vec2<Size> & size);
		

		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear(const Math::Vec2<Size> & size, typename Format format);


		///@brief get a mipmap from this texture
		///@param i mipmap number (0 mean original size)
		///@return pointer to the mipmap wanted.
		_Image<T> * getMipmap(typename Vector<_Image<T>>::Size i = 0);


		///@brief get a mipmap from this texture
		///@param i mipmap number (0 mean the original size)
		///@return pointer to the mipmap
		_Image<T> * operator[](typename Vector<_Image<T>>::Size i);



		///@brief generate the mipmap from the actual lod 0
		///@template C type able to handle the sum of 4 type T
		template<typename C = unsigned short>
		void generateMipmaps();


		///@brief get the data buffer of this image
		///@param i number of mipmap (0 = original image)
		///@return data buffer
		const T * getDatas(typename Vector<_Image<T>>::Size i = 0) const;

		///@brief get the data buffer of this image
		///@param i number of mipmap (0 = original image)
		///@return data buffer
		T * getDatas(typename Vector<_Image<T>>::Size i = 0);


		///@brief get a pixel from this texture
		///@param i mipmap level
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel(typename Vector<_Image<T>>::Size i, unsigned int x, unsigned int y) const;


		///@brief set a pixel inside this image
		///@param i mipmap level
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel(typename Vector<_Image<T>>::Size i, unsigned int x, unsigned int y, const T * p);


		///@brief copy operator
		///@param image Image to copy
		Texture<T> & operator=(const Texture<T> & image);

		///@brief move operator
		///@param image Image to move from
		Texture<T> & operator=(Texture<T> && image);


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(std::fstream * fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(std::fstream * fileStream) const;

		///@brief get the format of this image
		///@return format of this image (its castable in unsigned char to retrieve the number of components)
		typename Format getFormat() const;



		///@brief get the number of mipmap of this texture
		///@return number of mipmaps
		typename Vector<_Image<T> * >::Size getNumMipmaps() const;
	protected:
		enum ctor { null };
		Texture(ctor);

		bool _read(std::fstream * fileStream);
		void _unload();

		Vector<_Image<T> * > datas;
	};




}


#include "Texture.hpp"
