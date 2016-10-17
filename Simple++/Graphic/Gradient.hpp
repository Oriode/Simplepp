
namespace Graphic {


	namespace Gradient {

		template<typename C>
		const C & Point<C>::getColor() const {
			return this -> color;
		}

		template<typename C>
		const typename C::ColorFloat & Point<C>::getColorFloat() const {
			return this -> colorFloat;
		}

		template<typename C>
		void Point<C>::setColor( const C & color ) {
			this -> color = color;
			this -> colorFloat = color;
		}

		template<typename C>
		float Point<C>::getPosition() const {
			return this -> position;
		}

		template<typename C>
		void Point<C>::setPosition( float position ) {
			this -> position = position;
		}

		template<typename C>
		Point<C>::Point( float position, const C & color ) :
			color( color ),
			colorFloat( color ),
			position( position ) {

		}

		template<typename C >
		Point<C>::Point() {

		}



























		template<typename C, typename InterFunc>
		Template<C, InterFunc>::Template( const InterFunc & functor ) :
			functor( functor ),
			isOrdered( true ) {

		}



		template<typename C, typename InterFunc>
		Template<C, InterFunc>::~Template() {
			_unload();
		}

		template<typename C, typename InterFunc>
		void Template<C, InterFunc>::addPoint( float position, const C & color ) {
			this -> pointsVector.push( new Point<C>( position, color ) );
			this -> isOrdered = false;
		}

		template<typename C, typename InterFunc>
		typename Vector<Point<C> *>::Size Template<C, InterFunc>::getNumPoints() const {
			return this -> pointsVector.getSize();
		}

		template<typename C, typename InterFunc>
		Point<C> & Template<C, InterFunc>::operator[]( typename Vector<Point<C> *>::Size i ) {
			this -> isOrdered = false;
			return this -> pointsVector[i];
		}


		template<typename C, typename InterFunc>
		const Point<C> & Template<C, InterFunc>::operator[]( typename Vector<Point<C> *>::Size i ) const {
			return this -> pointsVector[i];
		}



		template<typename C, typename InterFunc>
		template<size_t N, typename InterFunc2>
		void Template<C, InterFunc>::computeInterpolation( C( &buffer )[N], const InterFunc2 & functor, float begin, float end ) const {
			return computeInterpolation( buffer, N, functor, begin, end );
		}

		template<typename C, typename InterFunc>
		void Template<C, InterFunc>::computeInterpolation( C * buffer, size_t size, float begin, float end ) const {
			return computeInterpolation( buffer, size, this -> functor, begin, end );
		}

		template<typename C, typename InterFunc>
		template<typename InterFunc2>
		void Template<C, InterFunc>::computeInterpolation( C * buffer, size_t size, const InterFunc2 & interFunctor, float begin, float end ) const {
			typedef typename C::ColorFloat::Type Float;

			if ( this -> pointsVector.getSize() == 1 ) {
				//fill the complete array with the same color
				for ( size_t i = 0; i < size; i++ ) {
					buffer[i] = this -> pointsVector[0] -> getColor();
				}

			} else if ( this -> pointsVector.getSize() > 1 ) {
				if ( !this -> isOrdered ) const_cast< Template<C, InterFunc> * >( this ) -> _updateOrdered();

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


				for ( typename Vector<Point<C> * >::Size i = 1; i < this -> pointsVectorOrdered.getSize(); i++ ) {
					const Point<C> & p1 = *this -> pointsVectorOrdered[i - 1];
					const Point<C> & p2 = *this -> pointsVectorOrdered[i];

					//Now we have to compute the beginning and ending index of the interpolations of the two colors.
					startIndex = endIndex;
					startClamped = Math::max( endClamped, begin );
					endClamped = Math::min<Float>( end, p2.getPosition() );
					endIndex = Math::clamp<int>( int( ( endClamped - begin ) * multiplier ), 0, size );


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

		template<typename C, typename InterFunc >
		void Template<C, InterFunc>::_updateOrdered() {
			struct OrderFunctor {
				bool operator()( const Point<C> * p1, const Point<C> * p2 ) const {
					return ( p1 -> getPosition() < p2 -> getPosition() );
				}
			};
			static OrderFunctor orderFunctor;
			this -> pointsVectorOrdered = this -> pointsVector;
			this -> pointsVectorOrdered.sort( orderFunctor );
			//Now we have the point correctly ordered.
			this -> isOrdered = true;

		}

		template<typename C, typename InterFunc>
		void Template<C, InterFunc>::_clear() {
			_unload();
			this -> pointsVectorOrdered.clear();
			this -> isOrdered = true;
		}


		template<typename C, typename InterFunc>
		bool Template<C, InterFunc>::read( std::fstream * fileStream ) {
			_unload();

			Vector<Point<C> * >::Size nbPoints;
			if ( !IO::read( fileStream, &nbPoints ) ) {
				_clear();
				return false;
			}

			//	Clamp in case of file corruption	
			nbPoints = Math::min( nbPoints, Vector<Point<C> * >::Size(1000) );

			for ( Vector<Point<C> * >::Size i( 0 ); i < nbPoints; i++ ) {
				Point<C> * gradientPoint = new Point<C>();
				if ( !IO::read( fileStream, gradientPoint ) ) {
					delete gradientPoint;
					_clear();
					return false;
				} else
					this -> pointsVector.push( gradientPoint );
			}

			if ( !IO::read( fileStream, &this -> functor ) ) {
				_clear();
				return false;
			}

			_updateOrdered();

			return true;
		}

		template<typename C, typename InterFunc>
		bool Template<C, InterFunc>::write( std::fstream * fileStream ) const {

			Vector<Point<C> * >::Size nbPoints( this -> pointsVector.getSize() );
			if ( !IO::write( fileStream, &nbPoints ) )
				return false;

			for ( auto it( this -> pointsVector.getBegin() ); it != this -> pointsVector.getEnd(); this->pointsVector.iterate( &it ) ) {
				if ( !IO::write( fileStream, *it ) )
					return false;
			}

			if ( !IO::write( fileStream, &this -> functor ) )
				return false;

			return true;
		}

		template<typename C, typename InterFunc >
		void Template<C, InterFunc>::_unload() {
			while ( this -> pointsVector.getSize() ) {
				delete this -> pointsVector.pop();
			}
		}

		template<typename C, typename InterFunc >
		void Template<C, InterFunc>::_copy( const Template & fontEffect ) {
			_unload();
			this -> isOrdered = false;

			for ( auto it( fontEffect.pointsVector.getBegin() ); it != fontEffect.pointsVector.getEnd(); fontEffect.pointsVector.iterate( &it ) ) {
				this -> pointsVector.push( new Point<C>( **it ) );
			}

			this -> functor = fontEffect.functor;
		}

		template<typename C, typename InterFunc >
		void Template<C, InterFunc>::_move( Template && fontEffect ) {
			this -> isOrdered = Utility::toRValue( fontEffect.isOrdered );
			this -> pointsVector = Utility::toRValue( ntEffect.pointsVector );
			this -> pointsVectorOrdered = Utility::toRValue( fontEffect.pointsVectorOrdered );
			this -> functor = Utility::toRValue( fontEffect.functor );

			fontEffect.pointsVector.clear();
		}

		template<typename C, typename InterFunc >
		Template<C, InterFunc>::Template( const Template & fontEffect ) {
			_copy( fontEffect );
		}

		template<typename C, typename InterFunc >
		Template<C, InterFunc>::Template( Template && fontEffect ) {
			_move( fontEffect );
		}

		template<typename C, typename InterFunc >
		Template<C, InterFunc> & Template<C, InterFunc>::operator =( const Template & fontEffect ) {
			_copy( fontEffect );
			return *this;
		}

		template<typename C, typename InterFunc >
		Template<C, InterFunc> & Template<C, InterFunc>::operator =( Template && fontEffect ) {
			_move( fontEffect );
			return *this;
		}












		template<typename C, typename InterFunc>
		Horizontal<C, InterFunc>::Horizontal( const InterFunc & functor ) :
			Template<C, InterFunc>( functor ) {

		}

		template<typename C, typename InterFunc>
		Horizontal<C, InterFunc>::Horizontal( const Horizontal & gradientHorizontal ) :
			Template<C, InterFunc>( gradientHorizontal ) {
		}

		template<typename C, typename InterFunc>
		Horizontal<C, InterFunc>::Horizontal( Horizontal && gradientHorizontal ) :
			Template<C, InterFunc>( Utility::toRValue( gradientHorizontal ) ) {
		}

		template<typename C, typename InterFunc>
		Horizontal<C, InterFunc> & Horizontal<C, InterFunc>::operator=( const Horizontal<C, InterFunc> & gradientHorizontal ) {
			Template<C, InterFunc>::operator =( gradientHorizontal );
			return *this;
		}

		template<typename C, typename InterFunc>
		Horizontal<C, InterFunc> & Horizontal<C, InterFunc>::operator=( Horizontal<C, InterFunc> && gradientHorizontal ) {
			Template<C, InterFunc>::operator =( Utility::toRValue( gradientHorizontal ) );
			return *this;
		}

		template<typename C, typename InterFunc >
		int Horizontal<C, InterFunc>::computeIndex( const Math::Vec2<Size> & p ) {
			return p.x;
		}


		template<typename C, typename InterFunc >
		int Horizontal<C, InterFunc>::computeIndex( const Graphic::Point & p, int maxIndex ) {
			return Math::clamp( p.x, 0, maxIndex );
		}



		template<typename C, typename InterFunc>
		Vertical<C, InterFunc>::Vertical( const InterFunc & functor ) :
			Template<C, InterFunc>( functor ) {

		}

		template<typename C, typename InterFunc>
		Vertical<C, InterFunc>::Vertical( const Vertical & gradientHorizontal ) :
			Template<C, InterFunc>( gradientHorizontal ) {
		}

		template<typename C, typename InterFunc>
		Vertical<C, InterFunc>::Vertical( Vertical && gradientHorizontal ) :
			Template<C, InterFunc>( Utility::toRValue( gradientHorizontal ) ) {
		}

		template<typename C, typename InterFunc>
		Vertical<C, InterFunc> & Vertical<C, InterFunc>::operator=( const Vertical<C, InterFunc> & gradientHorizontal ) {
			Template<C, InterFunc>::operator =( gradientHorizontal );
			return *this;
		}

		template<typename C, typename InterFunc>
		Vertical<C, InterFunc> & Vertical<C, InterFunc>::operator=( Vertical<C, InterFunc> && gradientHorizontal ) {
			Template<C, InterFunc>::operator =( Utility::toRValue( gradientHorizontal ) );
			return *this;
		}

		template<typename C, typename InterFunc >
		int Vertical<C, InterFunc>::computeIndex( const Math::Vec2<Size> & p ) {
			return p.y;
		}


		template<typename C, typename InterFunc >
		int Vertical<C, InterFunc>::computeIndex( const Graphic::Point & p, int maxIndex ) {
			return Math::clamp( p.y, 0, maxIndex );
		}


		template<typename C, typename InterFunc>
		void Linear<C, InterFunc>::setAngle( float angle ) {
			this -> angle = angle;
			this -> angleRad = angle * 0.0174533f;
			this -> v.x = Math::cos( gradient.getAngleRad() );
			this -> v.y = Math::sin( gradient.getAngleRad() );
		}

		template<typename C, typename InterFunc>
		unsigned int Linear<C, InterFunc>::getLength() const {
			return this -> length;
		}

		template<typename C, typename InterFunc>
		const Math::Vec2<float> & Linear<C, InterFunc>::getPoint() const {
			return this -> p;
		}

		template<typename C, typename InterFunc>
		float Linear<C, InterFunc>::getAngle() const {
			return this -> angle;
		}

		template<typename C, typename InterFunc>
		void Linear<C, InterFunc>::setLength( unsigned int length ) {
			this -> length = length;
		}

		template<typename C, typename InterFunc>
		void Linear<C, InterFunc>::setPoint( const Math::Vec2<float> & p ) {
			this -> p = p;
		}

		template<typename C, typename InterFunc>
		Linear<C, InterFunc>::Linear( float angle, const Math::Vec2<float> & p, unsigned int length, const InterFunc & functor ) :
			Template<C, InterFunc>( functor ),
			angle( angle ),
			angleRad( Math::radians( angle ) ),
			p( p ),
			length( length ),
			v( Math::cos( angleRad ), Math::sin( angleRad ) )

		{

		}

		template<typename C, typename InterFunc>
		Linear<C, InterFunc>::Linear( const Linear & gradientLinear ) :
			Template<C, InterFunc>( gradientLinear ),
			angle( gradientLinear.angle ),
			angleRad( gradientLinear.angleRad ),
			p( gradientLinear.p ),
			length( gradientLinear.length ),
			v( gradientLinear.v ) {
		}

		template<typename C, typename InterFunc>
		Linear<C, InterFunc>::Linear( Linear && gradientLinear ) :
			Template<C, InterFunc>( Utility::toRValue( gradientLinear ) ),
			angle( Utility::toRValue( gradientLinear.angle ) ),
			angleRad( Utility::toRValue( gradientLinear.angleRad ) ),
			p( Utility::toRValue( gradientLinear.p ) ),
			length( Utility::toRValue( gradientLinear.length ) ),
			v( Utility::toRValue( gradientLinear.v ) ) {
		}

		template<typename C, typename InterFunc>
		Linear<C, InterFunc> & Linear<C, InterFunc>::operator=( const Linear<C, InterFunc> & gradientLinear ) {
			Template<C, InterFunc>::operator =( gradientLinear );
			this -> angle = gradientLinear.angle;
			this -> angleRad = gradientLinear.angleRad;
			this -> p = gradientLinear.p;
			this -> length = gradientLinear.length;
			this -> v = gradientLinear.v;
			return *this;
		}

		template<typename C, typename InterFunc>
		Linear<C, InterFunc> & Linear<C, InterFunc>::operator=( Linear<C, InterFunc> && gradientLinear ) {
			Template<C, InterFunc>::operator =( Utility::toRValue( gradientLinear ) );
			this -> angle = Utility::toRValue( gradientLinear.angle );
			this -> angleRad = Utility::toRValue( gradientLinear.angleRad );
			this -> p = Utility::toRValue( gradientLinear.p );
			this -> length = Utility::toRValue( gradientLinear.length );
			this -> v = Utility::toRValue( gradientLinear.v );
			return *this;
		}



		template<typename C, typename InterFunc >
		int Linear<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex, const Math::Vec2<float> & direction ) {
			return Math::clamp<int>( ( int ) Math::dot( p, direction ), 0, maxIndex );
		}

		template<typename C, typename InterFunc >
		int Linear<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex ) const {
			return Linear<C, InterFunc>::computeIndex( p, maxIndex, getDirection() );
		}

		template<typename C, typename InterFunc >
		const Math::Vec2<float> & Linear<C, InterFunc>::getDirection() const {
			return this -> v;
		}


		template<typename C, typename InterFunc>
		float Linear<C, InterFunc>::getAngleRad() const {
			return this -> angleRad;
		}

		template<typename C, typename InterFunc>
		bool Linear<C, InterFunc>::read( std::fstream * fileStream ) {
			if ( !Template<C, InterFunc>::read( fileStream ) )
				return false;
			if ( !IO::read( fileStream, &this -> length ) )
				return false;
			if ( !IO::read( fileStream, &this -> p ) )
				return false;
			if ( !IO::read( fileStream, &this -> angle ) )
				return false;
			this -> angleRad = Math::radians( this -> angle );
			this -> v.x = Math::cos( this -> angleRad );
			this -> v.y = Math::sin( this -> angleRad );

			return true;
		}

		template<typename C, typename InterFunc>
		bool Linear<C, InterFunc>::write( std::fstream * fileStream ) const {
			if ( !Template<C, InterFunc>::write( fileStream ) )
				return false;
			if ( !IO::write( fileStream, &this -> length ) )
				return false;
			if ( !IO::write( fileStream, &this -> p ) )
				return false;
			if ( !IO::write( fileStream, &this -> angle ) )
				return false;


			return true;
		}



		template<typename C, typename InterFunc>
		const Math::Vec2<float> & Radial<C, InterFunc>::getRadius() const {
			return this -> radius;
		}

		template<typename C, typename InterFunc>
		void Radial<C, InterFunc>::setRadius( const Math::Vec2<float> & radius ) {
			this -> radius = radius;
		}

		template<typename C, typename InterFunc>
		const Math::Vec2<float> & Radial<C, InterFunc>::getCenter() const {
			return this -> center;
		}

		template<typename C, typename InterFunc>
		void Radial<C, InterFunc>::setCenter( const Math::Vec2<float> & center ) {
			this -> center = center;
		}

		template<typename C, typename InterFunc>
		Radial<C, InterFunc>::Radial( const Math::Vec2<float> & center, const Math::Vec2<float> & radius, const InterFunc & functor ) :
			Template<C, InterFunc>( functor ),
			radius( radius ),
			center( center ) {

		}

		template<typename C, typename InterFunc>
		Radial<C, InterFunc>::Radial( const Radial & gradientRadial ) :
			Template<C, InterFunc>( gradientRadial ),
			radius( gradientRadial.radius ),
			center( gradientRadial.center ) {
		}

		template<typename C, typename InterFunc>
		Radial<C, InterFunc>::Radial( Radial && gradientRadial ) :
			Template<C, InterFunc>( Utility::toRValue( gradientRadial ) ),
			radius( Utility::toRValue( gradientRadial.radius ) ),
			center( Utility::toRValue( gradientRadial.center ) ) {
		}

		template<typename C, typename InterFunc>
		Radial<C, InterFunc> & Radial<C, InterFunc>::operator=( const Radial<C, InterFunc> & gradientRadial ) {
			Template<C, InterFunc>::operator =( gradientRadial );
			this -> radius = gradientRadial.radius;
			this -> center = gradientRadial.center;
			return *this;
		}

		template<typename C, typename InterFunc>
		Radial<C, InterFunc> & Radial<C, InterFunc>::operator=( Radial<C, InterFunc> && gradientRadial ) {
			Template<C, InterFunc>::operator =( Utility::toRValue( gradientRadial ) );
			this -> radius = Utility::toRValue( gradientRadial.radius );
			this -> center = Utility::toRValue( gradientRadial.center );
			return *this;
		}


		template<typename C, typename InterFunc >
		int Radial<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex, const Math::Vec2<float> & radius ) {
			return Math::min<int>( int( Math::length( p ) * 2.0f ), maxIndex );
		}


		template<typename C, typename InterFunc >
		int Radial<C, InterFunc>::computeIndex( const Math::Vec2<float> & p, int maxIndex ) const {
			return Radial<C, InterFunc>::computeIndex( p, maxIndex, getRadius() );
		}


		template<typename C, typename InterFunc>
		bool Radial<C, InterFunc>::read( std::fstream * fileStream ) {
			if ( !Template<C, InterFunc>::read( fileStream ) )
				return false;
			if ( !IO::read( fileStream, &this -> center ) )
				return false;
			if ( !IO::read( fileStream, &this -> radius ) )
				return false;

			return true;
		}

		template<typename C, typename InterFunc>
		bool Radial<C, InterFunc>::write( std::fstream * fileStream ) const {
			if ( !Template<C, InterFunc>::write( fileStream ) )
				return false;
			if ( !IO::write( fileStream, &this -> center ) )
				return false;
			if ( !IO::write( fileStream, &this -> radius ) )
				return false;

			return true;
		}

	}


	


}

