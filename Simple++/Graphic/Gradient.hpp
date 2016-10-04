
namespace Graphic {





	template<typename C>
	const C & GradientPoint<C>::getColor() const {
		return this -> color;
	}

	template<typename C>
	const typename C::FloatType & GradientPoint<C>::getColorFloat() const {
		return this -> colorFloat;
	}

	template<typename C>
	void GradientPoint<C>::setColor( const C & color ) {
		this -> color = color;
		this -> colorFloat = color;
	}

	template<typename C>
	float GradientPoint<C>::getPosition() const {
		return this -> position;
	}

	template<typename C>
	void GradientPoint<C>::setPosition( float position ) {
		this -> position = position;
	}

	template<typename C>
	GradientPoint<C>::GradientPoint( float position, const C & color ) :
		color( color ),
		colorFloat( color ),
		position( position ) {

	}




























	template<typename C, typename InterFunc>
	Gradient<C, InterFunc>::Gradient( const InterFunc & functor ) :
		functor( functor ),
		isOrdered( true ) {

	}



	template<typename C, typename InterFunc>
	Gradient<C, InterFunc>::~Gradient() {
		while ( this -> pointsVector.getSize() ) {
			delete this -> pointsVector.pop();
		}
	}

	template<typename C, typename InterFunc>
	void Gradient<C, InterFunc>::addPoint( float position, const C & color ) {
		this -> pointsVector.push( new GradientPoint<C>( position, color ) );
		this -> isOrdered = false;
	}

	template<typename C, typename InterFunc>
	typename Vector<GradientPoint<C> *>::Size Gradient<C, InterFunc>::getNumPoints() const {
		return this -> pointsVector.getSize();
	}

	template<typename C, typename InterFunc>
	GradientPoint<C> & Gradient<C, InterFunc>::operator[]( typename Vector<GradientPoint<C> *>::Size i ) {
		this -> isOrdered = false;
		return this -> pointsVector[i];
	}


	template<typename C, typename InterFunc>
	const GradientPoint<C> & Gradient<C, InterFunc>::operator[]( typename Vector<GradientPoint<C> *>::Size i ) const {
		return this -> pointsVector[i];
	}



	template<typename C, typename InterFunc>
	template<size_t N, typename InterFunc2>
	void Gradient<C, InterFunc>::computeInterpolation( C( &buffer )[N], const InterFunc2 & functor, float begin, float end ) const {
		return computeInterpolation( buffer, N, functor, begin, end );
	}

	template<typename C, typename InterFunc>
	void Gradient<C, InterFunc>::computeInterpolation( C * buffer, size_t size, float begin, float end ) const {
		return computeInterpolation( buffer, size, this -> functor, begin, end );
	}

	template<typename C, typename InterFunc>
	template<typename InterFunc2>
	void Gradient<C, InterFunc>::computeInterpolation( C * buffer, size_t size, const InterFunc2 & interFunctor, float begin, float end ) const {
		typedef typename C::FloatType::Type Float;

		if ( this -> pointsVector.getSize() == 1 ) {
			//fill the complete array with the same color
			for ( size_t i = 0; i < size; i++ ) {
				buffer[i] = this -> pointsVector[0] -> getColor();
			}

		} else if ( this -> pointsVector.getSize() > 1 ) {
			struct OrderFunctor {
				bool operator()( const GradientPoint<C> * p1, const GradientPoint<C> * p2 ) const {
					return ( p1 -> getPosition() < p2 -> getPosition() );
				}
			};


			if ( !this -> isOrdered ) {
				const_cast< Gradient<C, InterFunc> * >( this ) -> pointsVectorOrdered = const_cast< Gradient<C, InterFunc> * >( this ) -> pointsVector;
				const_cast< Gradient<C, InterFunc> * >( this ) -> pointsVectorOrdered.sort( OrderFunctor() );
				//Now we have the point correctly ordered.
				const_cast< Gradient<C, InterFunc> * >( this ) -> isOrdered = true;
			}
			Float multiplier = Float( size ) / ( end - begin );


			Float startClamped( 0 );
			int startIndex( 0 );
			Float endClamped( Math::min<Float>( end, this -> pointsVectorOrdered[0] -> getPosition() ) );
			int endIndex( Math::clamp<int>( int( ( endClamped - begin ) * multiplier ), 0, size ) );

			{
				auto color( this -> pointsVectorOrdered[0] -> getColor() );
				for ( int i = startIndex; i < endIndex; i++ )
					buffer[i] = color;
			}
			

			for ( typename Vector<GradientPoint<C> * >::Size i = 1; i < this -> pointsVectorOrdered.getSize(); i++ ) {
				const GradientPoint<C> & p1 = *this -> pointsVectorOrdered[i - 1];
				const GradientPoint<C> & p2 = *this -> pointsVectorOrdered[i];

				//Now we have to compute the beginning and ending index of the interpolations of the two colors.
				startIndex = endIndex;
				startClamped = Math::max(endClamped, begin);
				endClamped = Math::min<Float>( end, p2.getPosition() );
				endIndex =  Math::clamp<int>( int( ( endClamped - begin ) * multiplier ), 0, size ) ;
				

				Float increment = ( 1.0f - ( startClamped - p1.getPosition() + ( p2.getPosition() - endClamped ) ) ) / ( endIndex - startIndex );
				Float x = increment * 0.5f + ( startClamped - p1.getPosition() );
				for ( int i = startIndex; i < endIndex; i++ ) {
					auto xInterpolated = interFunctor( x );
					buffer[i] = p1.getColorFloat() * ( Float( 1.0 ) - xInterpolated ) + p2.getColorFloat() * xInterpolated;
					x += increment;
				}


				{
					auto color( this -> pointsVectorOrdered.getLast() -> getColor() );
					for ( int i = endIndex; i < size; i++ )
						buffer[i] = color;
				}


			}
		}
	}






	template<typename C, typename InterFunc>
	GradientHorizontal<C, InterFunc>::GradientHorizontal( const InterFunc & functor ) :
		Gradient( functor ) {

	}

	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientHorizontal<C, InterFunc>::computeIndex( const Math::Vec2<Size> & p ) {
		return p.x;
	}


	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientHorizontal<C, InterFunc>::computeIndex( const Point & p, int maxIndex ) {
		return Math::clamp( p.x, 0, maxIndex );
	}



	template<typename C, typename InterFunc>
	GradientVertical<C, InterFunc>::GradientVertical( const InterFunc & functor ) :
		Gradient( functor ) {

	}

	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientVertical<C, InterFunc>::computeIndex( const Math::Vec2<Size> & p ) {
		return p.y;
	}


	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientVertical<C, InterFunc>::computeIndex( const Point & p, int maxIndex ) {
		return Math::clamp( p.y, 0, maxIndex );
	}


	template<typename C, typename InterFunc>
	void GradientLinear<C, InterFunc>::setAngle( float angle ) {
		this -> angle = angle;
		this -> angleRad = angle * 0.0174533f;
		this -> v.x = Math::cos( gradient.getAngleRad() );
		this -> v.y = Math::sin( gradient.getAngleRad() );
	}

	template<typename C, typename InterFunc>
	unsigned int GradientLinear<C, InterFunc>::getLength() const {
		return this -> length;
	}

	template<typename C, typename InterFunc>
	const Math::Vec2<float> & GradientLinear<C, InterFunc>::getPoint() const {
		return this -> p;
	}

	template<typename C, typename InterFunc>
	float GradientLinear<C, InterFunc>::getAngle() const {
		return this -> angle;
	}

	template<typename C, typename InterFunc>
	void GradientLinear<C, InterFunc>::setLength( unsigned int length ) {
		this -> length = length;
	}

	template<typename C, typename InterFunc>
	void GradientLinear<C, InterFunc>::setPoint( const Math::Vec2<float> & p ) {
		this -> p = p;
	}

	template<typename C, typename InterFunc>
	GradientLinear<C, InterFunc>::GradientLinear( float angle, const Math::Vec2<float> & p /*= Math::Vec2<float>::null*/, unsigned int length /*= 0*/, const InterFunc & functor /*= Func()*/ ) :
		Gradient( functor ),
		angle( angle ),
		angleRad( angle * 0.0174533 ),
		p( p ),
		length( length ),
		v( Math::cos( angleRad ), Math::sin( angleRad ) )

	{

	}


	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientLinear<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex, const Math::Vec2<float> & direction ) {
		return Math::clamp<int>( ( int ) Math::dot( p, direction ), 0, maxIndex );
	}

	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientLinear<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex ) const {
		return GradientLinear<C, InterFunc>::computeIndex( p, maxIndex, getDirection() );
	}

	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	const Math::Vec2<float> & GradientLinear<C, InterFunc>::getDirection() const {
		return this -> v;
	}


	template<typename C, typename InterFunc>
	float GradientLinear<C, InterFunc>::getAngleRad() const {
		return this -> angleRad;
	}

	template<typename C, typename InterFunc>
	const Math::Vec2<float> & GradientRadial<C, InterFunc>::getRadius() const {
		return this -> radius;
	}

	template<typename C, typename InterFunc>
	void GradientRadial<C, InterFunc>::setRadius( const Math::Vec2<float> & radius ) {
		this -> radius = radius;
	}

	template<typename C, typename InterFunc>
	const Math::Vec2<float> & GradientRadial<C, InterFunc>::getCenter() const {
		return this -> center;
	}

	template<typename C, typename InterFunc>
	void GradientRadial<C, InterFunc>::setCenter( const Math::Vec2<float> & center ) {
		this -> center = center;
	}

	template<typename C, typename InterFunc>
	GradientRadial<C, InterFunc>::GradientRadial( const Math::Vec2<float> & center /*= Math::Vec2<float>(0.5f)*/, const Math::Vec2<float> & radius /*= Math::Vec2<float>(1.0f)*/, const InterFunc & functor ) :
		Gradient( functor ),
		radius( radius ),
		center( center ) {

	}


	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientRadial<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex, const Math::Vec2<float> & radius ) {
		return Math::min<int>( int( Math::length( p ) * 2.0f ), maxIndex );
	}


	template<typename C, typename InterFunc /*= InterpolationFunc::Linear*/>
	int GradientRadial<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex ) const {
		return GradientRadial<C, InterFunc>::computeIndex( p, maxIndex, getRadius() );
	}

}

