///@file FontEffect.hpp
///@brief File containing the FontEffect object
///@author Clement Gerber
///@date 06/10/2016 (DMY) 
#pragma once

#include "Font.h"


namespace Graphic {

	namespace FontLoadingFunc {

		template<typename OverlayColorFunc = ColorFunc::SimpleColor<ColorRGBA<unsigned char>>, typename StrokeColorFunc = ColorFunc::SimpleColor<ColorRGBA<unsigned char>>, typename ShadowColorFunc = ColorFunc::SimpleColor<ColorRGBA<unsigned char>>>
		class Effect : public Template, public IO::BasicIO {
		public:
			Effect();

			///@brief Activate or not the shadow effect
			///@param bActivated If the shadow effect is activated or not
			void setShadowActivated( bool bActivated );

			///@brief Get if the shadow effect is activated or not
			///@return Boolean
			bool isShadowActivated() const;

			///@brief Set the shadow effect blur radius
			///@param radius Radius of the shadows blurring
			///@see setShadowActivated
			void setShadowRadius( unsigned int radius );

			///@brief Get the shadow effect blur radius
			///@return Radius of the shadows blurring
			unsigned int getShadowRadius() const;

			///@brief Set the shadow bias 
			///@param Shadow bias
			void setShadowBias( const Math::Vec2<float> & bias );

			///@brief get the shadow bias
			///@return shadow bias
			const Math::Vec2<float> & getShadowBias() const;

			///@brief Set the shadow color functor
			///@param colorFunc Color functor of the shadow
			///@see setShadowActivated
			void setShadowColorFunc( const ShadowColorFunc & colorFunc );

			///@brief Get the shadow color functor
			///@return color functor of the shadow
			ShadowColorFunc & getShadowColorFunc();


			///@brief Activate or not the stroking effect
			///@param bActivated of the stroking effect is activated or not
			void setStrokeActivated( bool bActivated );

			///@brief Get if the stroke effect is activated or not
			///@return Boolean
			bool isStrokeActivated() const;

			///@brief Set the stroking color functor
			///@param colorFunc Color functor of the stroke effect
			void setStrokeColorFunc( const StrokeColorFunc & colorFunc );

			///@brief get the stroking color functor
			///@return Color functor of stroke effect
			StrokeColorFunc & getStrokeColorFunc();

			///@brief set the stroking size
			///@param size Size of the stroke
			void setStrokeSize( float size );

			///@brief get the stroking size
			///@return Size of the stroke
			float getStrokeSize() const;

			///@brief Set the color overlay functor
			///@param colorFunc Color overlay functor
			void setOverlayColorFunc( const OverlayColorFunc & overlayColorFunc );

			///@brief get the color overlay functor
			///@return get the color overlay functor
			OverlayColorFunc & getOverlayColorFunc();

			template<typename T>
			void operator()( ImageT<T> * image, const unsigned char * buffer, const Math::Vec2<float> & size );

			///@brief Reset with default parameters
			void clear();

			///@brief read from a file stream
			///@param fileStream stream used to read load this object
			///@return boolean to know if the operation is a success of not.
			bool read( IO::SimpleFileStream * fileStream );

			///@brief write this object as binary into a file stream
			///@param fileStream stream used to write this object
			///@return boolean to know if the operation is a success of not.
			bool write( IO::SimpleFileStream * fileStream ) const;
		private:
			void _updateBias();

			bool bShadowActivated;
			unsigned int shadowRadius;
			Math::Vec2<float> shadowBias;
			ShadowColorFunc shadowColorFunc;

			bool bStrokeActivated;
			StrokeColorFunc strokeColorFunc;
			float strokeSize;

			OverlayColorFunc overlayColorFunc;
		};

	
	}







	template<typename T = unsigned char, typename OverlayColorFunc = ColorFunc::SimpleColor<ColorRGBA<T>>, typename StrokeColorFunc = ColorFunc::SimpleColor<ColorRGBA<T>>, typename ShadowColorFunc = ColorFunc::SimpleColor<ColorRGBA<T>>>
	class FontEffect : public _Font<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>> {
	public:
		///@brief Empty Constructor
		FontEffect( );

		///@brief constructor that take a filename of a font file (ttf, ttc, cff...)
		///@param fileName Path to the file to open
		///@param pixSize Size of the loaded font.
		///@param loadingFunc Loading Functor (must inherite from FontLoadingFunc::Template)
		FontEffect( const WString & fileName, int pixSize );

		///@brief Constructor using a font file dump and his size in bytes
		///@param fileDump memory copy of a font file.
		///@param fileSize size in bytes of the data buffer.
		///@param pixSize Size in pixels of the font to be loaded
		FontEffect( const char * fileDump, size_t fileSize, int pixSize );

		///@brief Copy constructor
		///@param fontEffect Font to be copied
		FontEffect( const FontEffect & fontEffect );

		///@brief Move constructor
		///@param fontEffect Font to be moved
		FontEffect( FontEffect && fontEffect );

		///@brief Copy operator
		///@param fontEffect Font to be copied
		///@return reference to THIS
		FontEffect & operator=( const FontEffect & fontEffect );

		///@brief Move operator
		///@param fontEffect Font to be moved
		///@return reference to THIS
		FontEffect & operator=( FontEffect && fontEffect );

		///@brief Activate or not the shadow effect
		///@param bActivated If the shadow effect is activated or not
		void setShadowActivated( bool bActivated );

		///@brief Get if the shadow effect is activated or not
		///@return Boolean
		bool isShadowActivated() const;

		///@brief Set the shadow effect blur radius
		///@param radius Radius of the shadows blurring
		///@see setShadowActivated
		void setShadowRadius( unsigned int radius );

		///@brief Get the shadow effect blur radius
		///@return Radius of the shadows blurring
		unsigned int getShadowRadius() const;

		///@brief Set the shadow bias 
		///@param Shadow bias
		void setShadowBias( const Math::Vec2<float> & bias );

		///@brief get the shadow bias
		///@return shadow bias
		const Math::Vec2<float> & getShadowBias() const;

		///@brief Set the shadow color functor
		///@param colorFunc Color functor of the shadow
		///@see setShadowActivated
		void setShadowColorFunc( const ShadowColorFunc & colorFunc );

		///@brief Get the shadow color functor
		///@return color functor of the shadow
		ShadowColorFunc & getShadowColorFunc();


		///@brief Activate or not the stroking effect
		///@param bActivated of the stroking effect is activated or not
		void setStrokeActivated( bool bActivated );

		///@brief Get if the stroke effect is activated or not
		///@return Boolean
		bool isStrokeActivated() const;

		///@brief Set the stroking color functor
		///@param colorFunc Color functor of the stroke effect
		void setStrokeColorFunc( const StrokeColorFunc & colorFunc );

		///@brief get the stroking color functor
		///@return Color functor of stroke effect
		StrokeColorFunc & getStrokeColorFunc();

		///@brief set the stroking size
		///@param size Size of the stroke
		void setStrokeSize( float size );

		///@brief get the stroking size
		///@return Size of the stroke
		float getStrokeSize() const;


		///@brief Set the color overlay functor
		///@param colorFunc Color overlay functor
		void setOverlayColorFunc( const OverlayColorFunc & overlayColorFunc );

		///@brief get the color overlay functor
		///@return get the color overlay functor
		OverlayColorFunc & getOverlayColorFunc();


	};












}

#include "FontEffect.hpp"
