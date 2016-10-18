#pragma once


#include "BasicGraphic.h"


namespace Graphic {

	namespace ColorFunc {


		///@brief Virtual function to be overloaded for doing Color Functors
		template<typename C>
		class Template {
		public:
			typedef C Color;

			Template() {}


			///@brief function called before any drawing to specify the rectangle where the drawing will be.
			///@param rectangle Rectangle of the image where the functor is gonna call the operator()()
			inline void init( const Math::Rectangle<Size> & rectangle ) {}


			///@brief operator() to be used as a functor, retrieve a color for a specified coordinate
			///@param p Point representing the coordinate where to retrieve the color relatively of the rectangle given in the init()
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const { return C( 0 ); }
		};



		///@brief Color functor with a simple color
		template<typename C>
		class SimpleColor : public Template<C> {
		public:
			///@brief empty constructor (will not init anything)
			SimpleColor() {};

			///@brief construct a Simple Color functor with a color
			SimpleColor( const C & color ) : color( color ) {}


			///@brief function called before any drawing to specify the rectangle where the drawing will be.
			///@param rectangle Rectangle of the image where the functor is gonna call the operator()()
			inline void init( const Math::Rectangle<Size> & rectangle ) {}


			///@brief operator() to be used as a functor, retrieve a color for a specified coordinate
			///@param p Point representing the coordinate where to retrieve the color relatively of the rectangle given in the init()
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) { return this -> color; }

			///@brief Retrieve the color of this functor
			///@return Color
			const C & getColor() const { return this -> color; }


			///@brief Set the color of this functor
			///@param color Color
			void setColor( const C & color ) { this -> color = color; }
		private:
			C color;

		};

	}







}
