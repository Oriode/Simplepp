#pragma once
///@class FreeImage
///@brief load, resize et save almost every types of image file.






#include <FreeImage.h>


#include "../BasicLoadable.h"
#include "../Math/Math.h"
#include "../Log.h"
#include "../UTF8String.h"

#include "BasicGraphic.h"



namespace Graphic {


	class FreeImage : public BasicLoadable {
	public:
		enum class Format {
			UNDEFINED,
			R,
			RGB,
			RGBA
		};

		enum class LoadingType { EMPTY, FILE };

		enum class SavingFormat {
			PNG = FIF_PNG,
			JPG = FIF_JPEG,
			BMP = FIF_BMP,
			TGA = FIF_TARGA
		};


		enum class Filter {
			Box = FILTER_BOX,
			Bilinear = FILTER_BILINEAR,
			Bspline = FILTER_BSPLINE,
			Bicubic = FILTER_BICUBIC,
			Catmullrom = FILTER_CATMULLROM,
			Lanczos3 = FILTER_LANCZOS3
		};


		///@brief Empty constructor, it will generate an NULL image.
		FreeImage();

		///@brief Create a new Image using a file stored on the HD, the format can be specified if all the colors aren't usefully 
		///@param fileName Path to the image to be opened.
		///@param format Format of the image (Format::UNDEFINED meens automatic detection. The file will be converted instead.)
		///@param invertY Specify if the image has to be flipped vertically when loaded.
		///@param size the size the image will have. (Math::Vec2<Size>::null meens the original one).
		FreeImage( const String & fileName, Format format = Format::UNDEFINED, bool invertY = false, const Math::Vec2<Size> & size = Math::Vec2<Size>::null );

		///@brief Create a new Image, a copy from an another one existing but resize it directly.
		///@param freeImage the image to be copied.
		///@param newSize the new size to be applied to the copied version
		///@param resampleFilter the re sample filter to be used during the resizing.
		FreeImage( const FreeImage & freeImage, const Math::Vec2<Size> & newSize, Filter resampleFilter = Filter::Bilinear );

		///@brief Create a new Image, a copy from an another one existing.
		///@param freeImage the image to be copied.
		FreeImage( const FreeImage & freeImage );

		///@brief Move constructor
		FreeImage( FreeImage && freeImage );


		///@brief destructor
		~FreeImage( void );


		///@brief Copy operator
		FreeImage & operator=( const FreeImage & image );

		///@brief Move operator
		FreeImage & operator=( FreeImage && image );




		///@brief define a new file to be this image. This object will be automatically reloaded if already loaded.
		///@param fileName new file Path to be opened
		///@param format loading format to be used if every components are not useful. (Format::UNDEFINED will use the file's one.)
		///@param invertY if we have to flip the image vertically.
		///@param size the new size of the loaded image (Math::Vec2<Size>::null mean full image resolution).
		void setFile( const String & fileName, Format format = Format::UNDEFINED, bool invertY = false, const Math::Vec2<Size> & size = Math::Vec2<Size>::null );


		///@brief load this object using raw datas
		///@param datas The datas buffer to be used during the loading.
		///@param size the size of the image.
		///@param format the loading format of this image.
		///@param datasInvertY if we have to flip the image vertically or not.
		void loadFromDatas( unsigned char * datas, const Math::Vec2<Size> & size, Format format, bool datasInvertY = false );




		///@brief return a pixel as a Math::vec4 object. Value will be between 0.0f and 0.1f.
		Math::vec4 getPixelf( Size x, Size y ) const;


		///@brief Set the actual format of each pixel stored, it will change the BPP
		void setFormat( Format format );



		///@brief Retrieve the actual image format                                    
		Format getFormat() const;

		///@brief Retrieve the inside FreeImage format object (not advised)
		FIBITMAP * getFreeImage();

		///@brief Retrieve the actual BPP of this image
		unsigned int getBPP() const;

		///@brief Retrieve datas has BGRA format
		unsigned char * getDatas() const;

		///@brief Retrieve the stride (width of one line in bytes)
		///@return stride
		size_t getStride() const;


		///@brief Save the image to a file, the quality is only for JPG from 0 to 100
		bool saveToFile( const String & fileName, SavingFormat savingFormat, unsigned int quality = 100 );

		///@brief Resize the image to the specified size using the specified Filter
		void resize( const Math::Vec2<Size> & newSize, Filter resampleFilter = Filter::Bilinear );



		///@brief Retrieve this image size
		const Math::Vec2<Size> & getSize() const;



		///@brief Get if the Y is flipped or not
		bool isYFlipped() const;

		///@brief Set if the image should be Y flipped
		void setFlipY( bool value );

		///@brief Retrieve the fileName
		const String & getFileName() const;


		///@brief Create a new image full black
		void clear();



		///@brief Create a copy of this image
		FreeImage * copy();



		BITMAPINFO * getInfos();

		///@brief Get the loading type
		LoadingType getLoadingType() const;

		///@brief Retrieve the number of bits from a specified format
		static unsigned int getBitsFromFormat( Format format );


	protected:
		///@brief function to be overloaded to add action during the loading process.
		///@return True if loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if unloading has succeeded, False otherwise
		virtual bool onUnload() override;

	private:
		void _updateBPP();
		void _updateSize();
		void _updateFormat( Format format );

		LoadingType loadingType;
		FIBITMAP * freeImage;

		String fileName;

		Math::Vec2<Size> size;
		Filter resampleFilter;
		size_t stride;

		Format loadingFormat;
		bool invertY;
		unsigned int BPP;
	};

}




