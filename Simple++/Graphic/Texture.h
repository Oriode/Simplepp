#pragma once


#include "../Log.h"
#include "../IO/IO.h"
#include "../Math/Math.h"
#include "../Vector.h"
#include "../String.h"
#include "../Utility.h"
#include "Image.h"

namespace Graphic {

	template<typename T = unsigned char>		//this is the type of ONE pixel
	class Texture : public IO::BasicIO {
	public:
		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		Texture( typename Format format = Format::RGB );

		///@brief Constructor to create an not initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		Texture( const Math::Vec2<Size> & size, typename Format format = Format::RGB );

		///@brief copy constructor
		Texture( const Texture<T> & image );

		///@brief create a Texture from a image data
		///@param dataBuffer buffer of the image to copy.
		///@param size size of the image to copy.
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		Texture( const T * dataBuffer, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false );

		///@brief Create a texture from an ImageT
		///@param image Image to use to create the mipmap 0
		Texture( const ImageT<T> & image );

		///@brief move constructor
		Texture( Texture<T> && image );

		~Texture();

		///@brief get the actual size (width:height) of the image
		///@param i num of the mipmap
		///@return the actual size of this image
		const Math::Vec2<Size> & getSize( ::Size i = 0 ) const;

		///@brief get the actual width of the image
		///@param i num of the mipmap
		///@return actual width of this image
		unsigned int getWidth( ::Size i = 0 ) const;

		///@brief get the actual height of the image
		///@param i num of the mipmap
		///@return actual height of this image
		unsigned int getHeight( ::Size i = 0 ) const;

		///@brief set the data from an another data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param invertY if the image has to be flipped vertically or not.
		void setDatas( const T * data, const Math::Vec2<Size> & size, typename LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false );

		///@brief Set the data of this texture from an ImageT
		///@param image Image to be used
		void setDatas( const ImageT<T> & image );

		///@brief reset this image with a new size.
		///@param size new size
		void clear( const Math::Vec2<Size> & size );


		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear( const Math::Vec2<Size> & size, typename Format format );


		///@brief get a mipmap from this texture
		///@param i mipmap number (0 mean original size)
		///@return pointer to the mipmap wanted.
		const ImageT<T> & getMipmap( ::Size i = 0 ) const;
		ImageT<T> & getMipmap( ::Size i = 0 );


		///@brief get a mipmap from this texture
		///@param i mipmap number (0 mean the original size)
		///@return pointer to the mipmap
		const ImageT<T> & operator[]( ::Size i ) const;
		ImageT<T> & operator[]( ::Size i );

		///@brief get the mipmaps vector
		///@return Vector of mipmaps
		const typename Vector<ImageT<T> * > & getMipmapVector() const;
		typename Vector<ImageT<T> * > & getMipmapVector();


		///@brief generate the mipmap from the actual lod 0
		void generateMipmaps();


		///@brief get the data buffer of this image
		///@param i number of mipmap (0 = original image)
		///@return data buffer
		const T * getDatas( ::Size i = 0 ) const;

		///@brief get the data buffer of this image
		///@param i number of mipmap (0 = original image)
		///@return data buffer
		T * getDatas( ::Size i = 0 );


		///@brief get a pixel from this texture
		///@param i mipmap level
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel( ::Size i, unsigned int x, unsigned int y ) const;


		///@brief set a pixel inside this image
		///@param i mipmap level
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel( ::Size i, unsigned int x, unsigned int y, const T * p );


		///@brief copy operator
		///@param image Image to copy
		Texture<T> & operator=( const Texture<T> & image );

		///@brief move operator
		///@param image Image to move from
		Texture<T> & operator=( Texture<T> && image );


		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;

		///@brief get the format of this image
		///@return format of this image (its castable in unsigned char to retrieve the number of components)
		typename Format getFormat() const;



		///@brief get the number of mipmap of this texture
		///@return number of mipmaps
		::Size getNbMipmaps() const;
	protected:
		enum ctor { null };
		Texture( ctor );

		template<typename Stream>
		bool _read( Stream * stream );
		void _unload();

		Vector<ImageT<T> * > datas;
	};

}


#include "Texture.hpp"
