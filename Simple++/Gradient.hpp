
namespace Graphic {





	template<typename C /*= ColorRGBA<unsigned char>*/>
	const C & GradientPoint<C>::getColor() const {
		return this -> color;
	}

	template<typename C /*= ColorRGBA<unsigned char>*/>
	void GradientPoint<C>::setColor(const C & color) {
		this -> color = color;
	}

	template<typename C /*= ColorRGBA<unsigned char>*/>
	float GradientPoint<C>::getPosition() const {
		return this -> position;
	}

	template<typename C /*= ColorRGBA<unsigned char>*/>
	void GradientPoint<C>::setPosition(float position) {
		this -> position = position;
	}

	template<typename C /*= ColorRGBA<unsigned char>*/>
	GradientPoint<C>::GradientPoint(float position, const C & color) :
		color(color),
		position(position)
	{

	}




























	template<typename C>
	Gradient<C>::Gradient(Type type /*= Type::Vertical*/) :
		type(type) {

	}

	template<typename C>
	Gradient<C>::~Gradient() {
		while ( this -> pointsVector.getSize() ) {
			delete this -> pointsVector.pop();
		}
	}

	template<typename C>
	void Gradient<C>::addPoint(float position, const C & color) {
		this -> pointsVector.push(new GradientPoint<C>(position, color));
	}

	template<typename C>
	typename Vector<GradientPoint<C> *>::Size Gradient<C>::getNumPoints() const {
		return this -> pointsVector.getSize();
	}

	template<typename C>
	GradientPoint<C> & Gradient<C>::operator[](typename Vector<GradientPoint<C> *>::Size i) {
		return this -> pointsVector[i];
	}






	template<typename C>
	template<size_t N>
	void Gradient<C>::computeInterpolation(C(&buffer)[N]) const {
		return computeInterpolation(buffer, N);
	}




	template<typename C>
	void Gradient<C>::computeInterpolation(C * buffer, size_t size) const {
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


			for ( typename Vector<GradientPoint<C> * >::Size i = 1; i < orderedPointVector.getSize(); i++ ) {
				const GradientPoint<C> & p1 = *orderedPointVector[i - 1];
				const GradientPoint<C> & p2 = *orderedPointVector[i];

				//Now we have to compute the beginning and ending index of the interpolations of the two colors.
				float sizePart = p2.getPosition() - p1.getPosition();
				size_t startingIndex = Math::clamp<size_t>(size_t(p1.getPosition() * float(size)), 0, size);
				size_t endingIndex = Math::clamp<size_t>(startingIndex + size_t(sizePart * float(size)), 0, size);
				float increment = 1.0f / ( endingIndex - startingIndex );

				float factor = 0.0f;
				float oneMinusFactor = 1.0f;

				for ( size_t i = startingIndex; i < endingIndex; i++ ) {
					buffer[i] = p1.getColor() * oneMinusFactor + p2.getColor() * factor;
					factor += increment;
					oneMinusFactor = 1.0f - factor;
				}
			}
		}
	}



	template<typename C>
	typename Gradient<C>::Type Gradient<C>::getType() const {
		return this -> type;
	}
}

