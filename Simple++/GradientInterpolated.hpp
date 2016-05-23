namespace Graphic {

	template<typename T, typename C, typename InterFunc>
	GradientInterpolation<T, C, InterFunc>::~GradientInterpolation() {
		delete[] this -> interpolatedArray;
	}

	template<typename T, typename C, typename InterFunc>
	const Math::Rectangle<Size> & GradientInterpolation<T, C, InterFunc>::getClampedRectangle() const {
		return this -> clampedRectangle;
	}

	template<typename T, typename C, typename InterFunc>
	GradientInterpolation<T, C, InterFunc>::GradientInterpolation()  {

	}

	template<typename T, typename C, typename InterFunc>
	const C * GradientInterpolation<T, C, InterFunc>::getInterpolatedDatas() const {
		return this -> interpolatedArray;
	}




	template<typename T, typename C, typename InterFunc>
	GradientHorizontalInterpolation<T, C, InterFunc>::GradientHorizontalInterpolation(const GradientHorizontal<C, InterFunc> & gradient, const _Image<T> & image, const Rectangle & rectangle) {
		this -> size = image.computeInterpolation(gradient, &this -> interpolatedArray, rectangle, &this -> clampedRectangle);
	}
	template<typename T, typename C, typename InterFunc>
	const C & GradientHorizontalInterpolation<T, C, InterFunc>::getColor(const Math::Vec2<Size> & p) const {
		return this -> interpolatedArray[GradientHorizontal<C, InterFunc>::computeIndex(p)];
	}




	template<typename T, typename C, typename InterFunc>
	const C & Graphic::GradientVerticalInterpolation<T, C, InterFunc>::getColor(const Math::Vec2<Size> & p) const {
		return this -> interpolatedArray[GradientVertical<C, InterFunc>::computeIndex(p)];
	}
	template<typename T, typename C, typename InterFunc>
	GradientVerticalInterpolation<T, C, InterFunc>::GradientVerticalInterpolation(const GradientVertical<C, InterFunc> & gradient, const _Image<T> & image, const Rectangle & rectangle) {
		this -> size = image.computeInterpolation(gradient, &this -> interpolatedArray, rectangle, &this -> clampedRectangle);
	}
}
