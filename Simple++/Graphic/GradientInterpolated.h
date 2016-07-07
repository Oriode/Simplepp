///@file GradientInterpolated.h
///@brief All the Interpolated Gradient Classes
///@author Clément Gerber
///@date 23/05/16 (DMY)


#pragma once
#include "Math.h"
#include "BasicGraphic.h"
#include "InterpolationFunc.hpp"
#include "ColorFunc.h"
#include "Gradient.h"


namespace Graphic {

	///@brief base class of an interpolated gradient
	template<typename C, typename InterFunc>
	class GradientInterpolation {
	public:
		GradientInterpolation();

		///@brief destructor
		~GradientInterpolation();

		///@brief get the effective rectangle of this gradient (intersection between the specified rectangle and the specified image)
		///@return rectangle
		const Math::Rectangle<Size> & getClampedRectangle() const;

		///@brief get the size of the interpolations datas
		///@return size of the interpolation array
		size_t getSize() const;


		///@brief direct access to the interpolated array
		///@param array of data interpolated
		const C * getInterpolatedDatas() const;

	protected:

		C * interpolatedArray;
		Math::Rectangle<Size> clampedRectangle;
		size_t size;
	};



	namespace ColorFunc {

		///@brief An Horizontal gradient color Functor
		template<typename C, typename InterFunc>
		class GradientHorizontal : public GradientInterpolation<C, InterFunc>, protected Template<C> {
		public:
			///@brief Create a new Horizontal gradient.
			GradientHorizontal( const Graphic::GradientHorizontal<C, InterFunc> & gradient );

			///@brief Initialize the gradient with the rectangle where to draw
			///@param rectangle Rectangle where to draw
			inline void init( const Math::Rectangle<Size> & rectangle );


			///@brief operator() to be able to use this object as a color functor
			///@param p Point relative to the image rectangle (see init())
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const;

		private:
			const Graphic::GradientHorizontal<C, InterFunc> & gradient;
		};


		///@brief A Vertical gradient color Functor
		template<typename C, typename InterFunc>
		class GradientVertical : public GradientInterpolation<C, InterFunc>, protected Template<C> {
		public:
			///@brief Create a new Horizontal gradient.
			GradientVertical( const Graphic::GradientVertical<C, InterFunc> & gradient );


			///@brief Initialize the gradient with the rectangle where to draw
			///@param rectangle Rectangle where to draw
			inline void init( const Math::Rectangle<Size> & rectangle );


			///@brief operator() to be able to use this object as a color functor
			///@param p Point relative to the image rectangle (see init())
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const;

		private:
			const Graphic::GradientVertical<C, InterFunc> & gradient;
		};


	}







}

#include "GradientInterpolated.hpp"
