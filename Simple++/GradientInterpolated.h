///@file GradientInterpolated.h
///@brief All the Interpolated Gradient Classes
///@author Clément Gerber
///@date 23/05/16 (DMY)


#pragma once
#include "Math.h"
#include "BasicGraphic.h"
#include "InterpolationFunc.hpp"
#include "Gradient.h"
#include "Image.h"


namespace Graphic {

	///@brief base class of an interpolated gradient
	template<typename T, typename C, typename InterFunc>
	class GradientInterpolation {
	public:
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
		GradientInterpolation();

		C * interpolatedArray;
		Math::Rectangle<Size> clampedRectangle;
		size_t size;
	};

	template<typename T, typename C, typename InterFunc>
	size_t Graphic::GradientInterpolation<T, C, InterFunc>::getSize() const {
		return this -> size;
	}
	
	


	///@brief An Horizontal gradient already interpolated for a specified image
	template<typename T, typename C, typename InterFunc>
	class GradientHorizontalInterpolation : public GradientInterpolation<T, C, InterFunc> {
	public:
		///@brief Create a new Horizontal gradient.
		GradientHorizontalInterpolation(const GradientHorizontal<C, InterFunc> & gradient, const _Image<T> & image, const Rectangle & rectangle);

		///@brief Get a color for this gradient
		///@param p Point relative to the clamped rectangle (see getClampedRectangle())
		///@return Color
		const C & getColor(const Math::Vec2<Size> & p) const;


		///@brief operator() to be able to use this object as a color functor
		///@param p Point relative to the image rectangle
		///@return Color
		inline C operator()(const Math::Vec2<Size> & p) const;
	};




	///@brief A Vertical gradient already interpolated for a specified image
	template<typename T, typename C, typename InterFunc>
	class GradientVerticalInterpolation : public GradientInterpolation<T, C, InterFunc> {
	public:
		///@brief Create a new Horizontal gradient.
		GradientVerticalInterpolation(const GradientVertical<C, InterFunc> & gradient, const _Image<T> & image, const Rectangle & rectangle);

		///@brief Get a color for this gradient
		///@param p Point relative to the clamped rectangle (see getClampedRectangle())
		///@return Color
		const C & getColor(const Math::Vec2<Size> & p) const;


		///@brief operator() to be able to use this object as a color functor
		///@param p Point relative to the image rectangle
		///@return Color
		inline C operator()(const Math::Vec2<Size> & p) const;
	};

	

}

#include "GradientInterpolated.hpp"
