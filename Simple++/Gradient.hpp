
namespace Graphic {





	template<typename C>
	const C & GradientPoint<C>::getColor() const {
		return this -> color;
	}

	template<typename C>
	void GradientPoint<C>::setColor(const C & color) {
		this -> color = color;
	}

	template<typename C>
	float GradientPoint<C>::getPosition() const {
		return this -> position;
	}

	template<typename C>
	void GradientPoint<C>::setPosition(float position) {
		this -> position = position;
	}

	template<typename C>
	GradientPoint<C>::GradientPoint(float position, const C & color) :
		color(color),
		position(position)
	{

	}




























	template<typename C, typename Func>
	Gradient<C, Func>::Gradient(const Func & functor) :
	functor(functor)
	{

	}



	template<typename C, typename Func>
	Gradient<C, Func>::~Gradient() {
		while ( this -> pointsVector.getSize() ) {
			delete this -> pointsVector.pop();
		}
	}

	template<typename C, typename Func>
	void Gradient<C, Func>::addPoint(float position, const C & color) {
		this -> pointsVector.push(new GradientPoint<C>(position, color));
	}

	template<typename C, typename Func>
	typename Vector<GradientPoint<C> *>::Size Gradient<C, Func>::getNumPoints() const {
		return this -> pointsVector.getSize();
	}

	template<typename C, typename Func>
	GradientPoint<C> & Gradient<C, Func>::operator[](typename Vector<GradientPoint<C> *>::Size i) {
		return this -> pointsVector[i];
	}






	template<typename C, typename Func>
	template<size_t N, typename Func2>
	void Gradient<C, Func>::computeInterpolation(C(&buffer)[N], const Func2 & functor) const {
		return computeInterpolation(buffer, N, functor);
	}

	template<typename C, typename Func>
	void Gradient<C, Func>::computeInterpolation(C * buffer, size_t size) const {
		return computeInterpolation(buffer, size, this -> functor);
	}

	template<typename C, typename Func>
	template<typename Func2>
	void Gradient<C, Func>::computeInterpolation(C * buffer, size_t size, const Func2 & functor) const {
		if ( this -> pointsVector.getSize() == 1 ) {
			//fill the complete array with the same color
			for ( size_t i = 0; i < size; i++ ) {
				buffer[i] = this -> pointsVector[0]->getColor();
			}

		} else if ( this -> pointsVector.getSize() > 1 ) {
			Vector<GradientPoint<C> * > orderedPointVector(this -> pointsVector);

			struct orderFunctor {
				bool operator()(const GradientPoint<C> * p1, const GradientPoint<C> * p2) const {
					return ( p1 -> getPosition() < p2 -> getPosition() );
				}
			};

			orderedPointVector.sort(orderFunctor());
			//Now we have the point correctly ordered.

			size_t startingIndex = 0;
			for ( typename Vector<GradientPoint<C> * >::Size i = 1; i < orderedPointVector.getSize(); i++ ) {
				const GradientPoint<C> & p1 = *orderedPointVector[i - 1];
				const GradientPoint<C> & p2 = *orderedPointVector[i];

				//Now we have to compute the beginning and ending index of the interpolations of the two colors.
				size_t endingIndex = Math::clamp<size_t>(size_t(p2.getPosition() * float(size)), 0, size);
				float increment = 1.0f / ( endingIndex - startingIndex );
				float x = increment / 2.0f;
				for ( size_t i = startingIndex; i < endingIndex; i++ ) {
					buffer[i] = functor(p1.getColor(), p2.getColor(), x);
					x += increment;
				}
				startingIndex = endingIndex;
			}
		}
	}






	template<typename C, typename Func>
	GradientHorizontal<C, Func>::GradientHorizontal(const Func & functor) :
		Gradient(functor) {

	}

	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	int GradientHorizontal<C, Func>::computeIndex(const Point & p) {
		return p.x;
	}


	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	int GradientHorizontal<C, Func>::computeIndex(const Point & p, int maxIndex) {
		return Math::clamp(p.x, 0, maxIndex);
	}



	template<typename C, typename Func>
	GradientVertical<C, Func>::GradientVertical(const Func & functor) :
		Gradient(functor) {

	}

	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	int GradientVertical<C, Func>::computeIndex(const Point & p) {
		return p.y;
	}


	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	int GradientVertical<C, Func>::computeIndex(const Point & p, int maxIndex) {
		return Math::clamp(p.y, 0, maxIndex);
	}


	template<typename C, typename Func>
	void GradientLinear<C, Func>::setAngle(float angle) {
		this -> angle = angle;
		this -> angleRad = angle * 0.0174533f;
		this -> v.x = Math::cos(gradient.getAngleRad());
		this -> v.y = Math::sin(gradient.getAngleRad());
	}

	template<typename C, typename Func>
	unsigned int GradientLinear<C, Func>::getLength() const {
		return this -> length;
	}

	template<typename C, typename Func>
	const Math::Vec2<float> & GradientLinear<C, Func>::getPoint() const {
		return this -> p;
	}

	template<typename C, typename Func>
	float GradientLinear<C, Func>::getAngle() const {
		return this -> angle;
	}

	template<typename C, typename Func>
	void GradientLinear<C, Func>::setLength(unsigned int length) {
		this -> length = length;
	}

	template<typename C, typename Func>
	void GradientLinear<C, Func>::setPoint(const Math::Vec2<float> & p) {
		this -> p = p;
	}

	template<typename C, typename Func>
	GradientLinear<C, Func>::GradientLinear(float angle, const Math::Vec2<float> & p /*= Math::Vec2<float>::null*/, unsigned int length /*= 0*/, const Func & functor /*= Func()*/) :
		Gradient(functor),
		angle(angle),
		angleRad( angle * 0.0174533 ),
		p(p),
		length(length),
		v(Math::cos(angleRad), Math::sin(angleRad))
	
	{

	}


	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	int GradientLinear<C, Func>::computeIndex(const Point & p, int maxIndex, const Math::Vec2<float> & direction) {
		return Math::clamp<int>((int) Math::dot(Math::Vec2<float>(p), direction), 0, maxIndex);
	}

	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	const Math::Vec2<float> & GradientLinear<C, Func>::getDirection() const {
		return this -> v;
	}


	template<typename C, typename Func>
	float GradientLinear<C, Func>::getAngleRad() const {
		return this -> angleRad;
	}

	template<typename C, typename Func>
	const Math::Vec2<float> & GradientRadial<C, Func>::getRadius() const {
		return this -> radius;
	}

	template<typename C, typename Func>
	void GradientRadial<C, Func>::setRadius(const Math::Vec2<float> & radius) {
		this -> radius = radius;
	}

	template<typename C, typename Func>
	const Math::Vec2<float> & GradientRadial<C, Func>::getCenter() const {
		return this -> center;
	}

	template<typename C, typename Func>
	void GradientRadial<C, Func>::setCenter(const Math::Vec2<float> & center) {
		this -> center = center;
	}

	template<typename C, typename Func>
	GradientRadial<C, Func>::GradientRadial(const Math::Vec2<float> & center /*= Math::Vec2<float>(0.5f)*/, const Math::Vec2<float> & radius /*= Math::Vec2<float>(1.0f)*/, const Func & functor) :
		Gradient(functor),
		radius(radius),
		center(center) {

	}


	template<typename C, typename Func /*= InterpolationFunc::Linear*/>
	int GradientRadial<C, Func>::computeIndex(const Point & p, int maxIndex, const Math::Vec2<float> & radius) {
		return int(Math::length(Math::Vec2<float>(p) * radius));
	}

}

