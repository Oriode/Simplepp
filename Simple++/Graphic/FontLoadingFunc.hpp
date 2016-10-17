///@file FontLoadingFunc.hpp
///@brief File containing all Char Loading Functors
///@author Clement Gerber
///@date 06/10/2016 (DMY) 
#pragma once

#include "../Math/Vec2.h"
#include "Image.h"

namespace Graphic {
	namespace FontLoadingFunc {

		class Template {
		public:
			Template( const Math::Vec2<float> & bias = Math::Vec2<float>( 0 ), Rectangle & rectangle = Rectangle( 0 ) ) : bias( bias ), margins(rectangle) {}

			///@brief Retrieve the actual bias of the char images
			///@return Bias of the font/chars when drawing them (simply add this bias to the initial position when drawing)
			const Math::Vec2<float> & getBias() const { return this -> bias; }

			///@brief Retrieve the actual margins of the images
			///@return Margins of the font/chars images 
			const Rectangle & getMargins() const { return this -> margins; }

			///@brief Operator to be overloaded, this function will set the image from the given buffer of the given size.
			///@param image in out image to be set
			///@param buffer bitmap buffer read from the font file
			///@param size size of the given bitmap
			template<typename T>
			void operator()( ImageT<T> * image, const unsigned char * buffer, const Math::Vec2<float> & size ) const {}

		protected:
			///@brief Set the bias of this loading functor
			///@see getBias()
			///@return Bias	
			void setBias( const Math::Vec2<float> & bias ) { this -> bias = bias; }

			///@brief Set the margins of this loading functor
			///@see getMargins()
			///@return Margins
			void setBias( const Rectangle & margins ) { this -> margins = margins; }

			Math::Vec2<float> bias;
			Rectangle margins;
		};

		class Default : public Template {
		public:
			template<typename T>
			void operator()( ImageT<T> * image, const unsigned char * buffer, const Math::Vec2<float> & size ) const {
				image -> setDatas( buffer, size, LoadingFormat::R, true );
			}
		};
	}
}
