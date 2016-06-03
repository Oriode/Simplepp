namespace Graphic {

	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc>::GradientInterpolation() : interpolatedArray(NULL) {

	}

	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc>::~GradientInterpolation() {
		delete[] this -> interpolatedArray;
	}

	template<typename C, typename InterFunc>
	const Math::Rectangle<Size> & GradientInterpolation<C, InterFunc>::getClampedRectangle() const {
		return this -> clampedRectangle;
	}

	template<typename C, typename InterFunc>
	const C * GradientInterpolation<C, InterFunc>::getInterpolatedDatas() const {
		return this -> interpolatedArray;
	}

	template<typename C, typename InterFunc>
	size_t Graphic::GradientInterpolation<C, InterFunc>::getSize() const {
		return this -> size;
	}


	namespace ColorFunc {
		template<typename C, typename InterFunc>
		GradientHorizontal<C, InterFunc>::GradientHorizontal(const Graphic::GradientHorizontal<C, InterFunc> & gradient) : 
		gradient(gradient)
		{
		}
		template<typename C, typename InterFunc>
		C GradientHorizontal<C, InterFunc>::operator()(const Math::Vec2<Size> & p) const {
			return this -> interpolatedArray[p.x];

		}
		template<typename C, typename InterFunc>
		void GradientHorizontal<C, InterFunc>::init(const Math::Rectangle<Size> & rectangle) {
			this -> size = rectangle.getRight() - rectangle.getLeft();
			this -> interpolatedArray = new C[size];
			this -> gradient.computeInterpolation(this -> interpolatedArray, this -> size);
		}




		template<typename C, typename InterFunc>
		GradientVertical<C, InterFunc>::GradientVertical(const Graphic::GradientVertical<C, InterFunc> & gradient) : 
		gradient(gradient)
		{
		}
		template<typename C, typename InterFunc>
		C GradientVertical<C, InterFunc>::operator()(const Math::Vec2<Size> & p) const {
			return this -> interpolatedArray[p.y];
		}
		template<typename C, typename InterFunc>
		void GradientVertical<C, InterFunc>::init(const Math::Rectangle<Size> & rectangle) {
			this -> size = rectangle.getTop() - rectangle.getBottom();
			this -> interpolatedArray = new C[size];
			this -> gradient.computeInterpolation(this -> interpolatedArray, this -> size);
		}

	}

	

}
