///@file FontEffect.hpp
///@brief File containing the FontEffect object
///@author Clement Gerber
///@date 06/10/2016 (DMY) 
#pragma once

#include "Font.h"


namespace Graphic {

	namespace FontLoadingFunc {

		template<typename T, typename StrokeColorFunc = ColorFunc::SimpleColor<ColorRGBA<T>>, typename ShadowColorFunc = ColorFunc::SimpleColor<ColorRGBA<T>>, typename OverlayColorFunc = ColorFunc::SimpleColor<ColorRGBA<T>>>
		class Effect : public Template {
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


			void operator()( ImageT<T> * image, const unsigned char * buffer, const Math::Vec2<float> & size );

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



}

#include "FontEffect.hpp"
