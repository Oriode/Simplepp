///@file GradientInterpolated.h
///@brief All the Interpolated Gradient Classes
///			A Gradient is abstract without precomputed datas, this objects take abstract gradient and transform them into color functors
///@author Clément Gerber
///@date 23/05/16 (DMY)


#pragma once
#include "Math.h"
#include "BasicGraphic.h"
#include "InterpolationFunc.hpp"
#include "ColorFunc.h"
#include "Gradient.h"
#include "Vector.h"


namespace Graphic {

	///@brief base class of an interpolated gradient
	template<typename C, typename InterFunc>
	class GradientInterpolation {
	public:
		GradientInterpolation();

		///@brief destructor
		~GradientInterpolation();

		///@brief copy constructor
		GradientInterpolation( const GradientInterpolation<C, InterFunc> & gradient );

		///@brief move constructor
		GradientInterpolation( GradientInterpolation<C, InterFunc> && gradient );

		///@brief get the effective rectangle of this gradient (intersection between the specified rectangle and the specified image)
		///@return rectangle
		const Math::Rectangle<Size> & getClampedRectangle() const;

		///@brief get the size of the interpolations datas
		///@return size of the interpolation array
		size_t getSize() const;

		///@brief direct access to the interpolated array
		///@param array of data interpolated
		const C * getInterpolatedDatas() const;

		///@brief copy operator
		GradientInterpolation<C, InterFunc> & operator=( const GradientInterpolation<C, InterFunc> & gradient );

		///@brief move operator
		GradientInterpolation<C, InterFunc> & operator=( GradientInterpolation<C, InterFunc> && gradient );

	protected:

		C * interpolatedArray;
		Math::Rectangle<Size> clampedRectangle;
		int size;
	};





	namespace ColorFunc {

		///@brief An Horizontal gradient color Functor
		template<typename C, typename InterFunc>
		class GradientHorizontal : public GradientInterpolation<C, InterFunc>, protected Template<C> {
		public:
			///@brief Create a new Horizontal gradient.
			GradientHorizontal( const Graphic::GradientHorizontal<C, InterFunc> & gradient );

			///@brief Copy Constructor
			GradientHorizontal( const GradientHorizontal<C, InterFunc> & gradient );

			///@brief Move Constructor
			GradientHorizontal( GradientHorizontal<C, InterFunc> && gradient );

			///@brief Initialize the gradient with the rectangle where to draw
			///@param rectangle Rectangle where to draw
			inline void init( const Math::Rectangle<Size> & rectangle );

			///@brief operator() to be able to use this object as a color functor
			///@param p Point relative to the image rectangle (see init())
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const;

			///@brief Copy operator
			GradientHorizontal<C, InterFunc> & operator=( const GradientHorizontal<C, InterFunc> & gradient );

			///@brief Move operator
			GradientHorizontal<C, InterFunc> & operator=( GradientHorizontal<C, InterFunc> && gradient );

		private:
			const Graphic::GradientHorizontal<C, InterFunc> & gradient;
		};




		///@brief A Vertical gradient color Functor
		template<typename C, typename InterFunc>
		class GradientVertical : public GradientInterpolation<C, InterFunc>, protected Template<C> {
		public:
			///@brief Create a new Horizontal gradient.
			GradientVertical( const Graphic::GradientVertical<C, InterFunc> & gradient );

			///@brief Copy Constructor
			GradientVertical( const GradientVertical<C, InterFunc> & gradient );

			///@brief Move Constructor
			GradientVertical( GradientVertical<C, InterFunc> && gradient );

			///@brief Initialize the gradient with the rectangle where to draw
			///@param rectangle Rectangle where to draw
			inline void init( const Math::Rectangle<Size> & rectangle );


			///@brief operator() to be able to use this object as a color functor
			///@param p Point relative to the image rectangle (see init())
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const;

			///@brief Copy operator
			GradientVertical<C, InterFunc> & operator=( const GradientVertical<C, InterFunc> & gradient );

			///@brief Move operator
			GradientVertical<C, InterFunc> & operator=( GradientVertical<C, InterFunc> && gradient );

		private:
			const Graphic::GradientVertical<C, InterFunc> & gradient;
		};


		///@brief Linear Gradient Color Functor
		template<typename C, typename InterFunc>
		class GradientLinear : public GradientInterpolation<C, InterFunc>, protected Template<C> {
		public:
			///@brief Create a new Horizontal gradient.
			GradientLinear( const Graphic::GradientLinear<C, InterFunc> & gradient );

			///@brief Copy Constructor
			GradientLinear( const GradientLinear<C, InterFunc> & gradient );

			///@brief Move Constructor
			GradientLinear( GradientLinear<C, InterFunc> && gradient );

			///@brief Initialize the gradient with the rectangle where to draw
			///@param rectangle Rectangle where to draw
			inline void init( const Math::Rectangle<Size> & rectangle );

			///@brief operator() to be able to use this object as a color functor
			///@param p Point relative to the image rectangle (see init())
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const;

			///@brief Copy operator
			GradientLinear<C, InterFunc> & operator=( const GradientLinear<C, InterFunc> & gradient );

			///@brief Move operator
			GradientLinear<C, InterFunc> & operator=( GradientLinear<C, InterFunc> && gradient );

		private:
			const Graphic::GradientLinear<C, InterFunc> & gradient;
			int sizeMinusOne;
			Point origin;
		};

		///@brief Linear Gradient Color Functor
		template<typename C, typename InterFunc>
		class GradientRadial : public GradientInterpolation<C, InterFunc>, protected Template<C> {
		public:
			///@brief Create a new Horizontal gradient.
			GradientRadial( const Graphic::GradientRadial<C, InterFunc> & gradient );

			///@brief Copy Constructor
			GradientRadial( const GradientRadial<C, InterFunc> & gradient );

			///@brief Move Constructor
			GradientRadial( GradientRadial<C, InterFunc> && gradient );

			///@brief Initialize the gradient with the rectangle where to draw
			///@param rectangle Rectangle where to draw
			inline void init( const Math::Rectangle<Size> & rectangle );

			///@brief operator() to be able to use this object as a color functor
			///@param p Point relative to the image rectangle (see init())
			///@return Color
			inline C operator()( const Math::Vec2<Size> & p ) const;

			///@brief Copy operator
			GradientRadial<C, InterFunc> & operator=( const GradientRadial<C, InterFunc> & gradient );

			///@brief Move operator
			GradientRadial<C, InterFunc> & operator=( GradientRadial<C, InterFunc> && gradient );

		private:
			const Graphic::GradientRadial<C, InterFunc> & gradient;
			int sizeMinusOne;
			Point center;
		};




	}







}

#include "GradientInterpolated.hpp"