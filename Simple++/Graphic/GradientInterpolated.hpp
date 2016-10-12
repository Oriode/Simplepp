namespace Graphic {

	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc>::GradientInterpolation() : interpolatedArray( NULL ) {

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

	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc>::GradientInterpolation( const GradientInterpolation<C, InterFunc> & gradient ) :
		size( gradient.size ),
		clampedRectangle( gradient.clampedRectangle )
	{
		if ( gradient.interpolatedArray ) {
			this -> interpolatedArray = new C[this -> size];
			Vector<C>::copy( this -> interpolatedArray, gradient.interpolatedArray, this -> size );
		} else {
			this -> interpolatedArray = NULL;
		}	
	}

	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc>::GradientInterpolation( GradientInterpolation<C, InterFunc> && gradient ) :
		size( Utility::toRValue( gradient.size ) ),
		clampedRectangle( Utility::toRValue( gradient.clampedRectangle ) ),
		interpolatedArray( Utility::toRValue( gradient.interpolatedArray ) )
	{
		gradient.interpolatedArray = NULL;
	}


	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc> & GradientInterpolation<C, InterFunc>::operator=( const GradientInterpolation<C, InterFunc> & gradient ) {
		this -> size = gradient.size;
		this -> clampedRectangle = gradient.clampedRectangle;
		delete[] this -> interpolatedArray;
		if ( gradient.interpolatedArray ) {
			this -> interpolatedArray = new C[this -> size];
			Vector<C>::copy( this -> interpolatedArray, gradient.interpolatedArray, this -> size );
		} else {
			this -> interpolatedArray = NULL;
		}
		
		return *this;
	}


	template<typename C, typename InterFunc>
	GradientInterpolation<C, InterFunc> & GradientInterpolation<C, InterFunc>::operator=( GradientInterpolation<C, InterFunc> && gradient ) {
		this -> size = Utility::toRValue( gradient.size );
		this -> clampedRectangle = Utility::toRValue( gradient.clampedRectangle );
		this -> interpolatedArray = Utility::toRValue( gradient.interpolatedArray );
		gradient.interpolatedArray = NULL;
		return *this;
	}

	template<typename C, typename InterFunc>
	bool GradientInterpolation<C, InterFunc>::read( std::fstream * fileStream ) {
		delete[] this -> interpolatedArray;
		this -> interpolatedArray = NULL;
		return true;
	}

	template<typename C, typename InterFunc>
	bool GradientInterpolation<C, InterFunc>::write( std::fstream * fileStream ) const {
		return true;
	}



	namespace ColorFunc {
		//////////////////////////////////////////////////////////////////////////
        //// HORIZONTAL
		template<typename C, typename InterFunc>
		GradientHorizontal<C, InterFunc>::GradientHorizontal( const Graphic::Gradient::Horizontal<C, InterFunc> & gradient ) :
			gradient( gradient ) {
		}
		template<typename C, typename InterFunc>
		GradientHorizontal<C, InterFunc>::GradientHorizontal( const GradientHorizontal<C, InterFunc> & gradient ) :
			GradientInterpolation<C, InterFunc>(gradient),
			gradient ( gradient.gradient ){
		}

		template<typename C, typename InterFunc>
		GradientHorizontal<C, InterFunc>::GradientHorizontal( GradientHorizontal<C, InterFunc> && gradient ) :
			GradientInterpolation<C, InterFunc>( Utility::toRValue(gradient) ),
			gradient(  Utility::toRValue(gradient.gradient) ) {
		}

		template<typename C, typename InterFunc>
		C GradientHorizontal<C, InterFunc>::operator()( const Math::Vec2<Size> & p ) const {
			return this -> interpolatedArray[p.x];

		}
		template<typename C, typename InterFunc>
		void GradientHorizontal<C, InterFunc>::init( const Math::Rectangle<Size> & rectangle ) {
			this -> size = rectangle.getRight() - rectangle.getLeft();
			delete[] this -> interpolatedArray;
			this -> interpolatedArray = new C[size];
			this -> gradient.computeInterpolation( this -> interpolatedArray, this -> size );
		}

		template<typename C, typename InterFunc>
		GradientHorizontal<C, InterFunc> & ColorFunc::GradientHorizontal<C, InterFunc>::operator=( const GradientHorizontal<C, InterFunc> & gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( gradient );
			this -> gradient = gradient.gradient;
			return *this;
		}

		template<typename C, typename InterFunc>
		GradientHorizontal<C, InterFunc> & ColorFunc::GradientHorizontal<C, InterFunc>::operator=( GradientHorizontal<C, InterFunc> && gradient ) {
			GradientInterpolation<C, InterFunc>::operator=(  Utility::toRValue(gradient) );
			this -> gradient = Utility::toRValue(gradient.gradient);
			return *this;
		}

		template<typename C, typename InterFunc>
		bool GradientHorizontal<C, InterFunc>::read( std::fstream * fileStream ) {
			if ( !GradientInterpolation<C, InterFunc>::read( fileStream ) )
				return false;
			if ( !IO::read( fileStream, &this -> gradient ) )
				return false;

			return true;
		}

		template<typename C, typename InterFunc>
		bool GradientHorizontal<C, InterFunc>::write( std::fstream * fileStream ) const {
			if ( !GradientInterpolation<C, InterFunc>::write( fileStream ) )
				return false;
			if ( !IO::write( fileStream, &this -> gradient ) )
				return false;

			return true;
		}


		//////////////////////////////////////////////////////////////////////////
        //// VERTICAL
		template<typename C, typename InterFunc>
		GradientVertical<C, InterFunc>::GradientVertical( const Graphic::Gradient::Vertical<C, InterFunc> & gradient ) :
			gradient( gradient ) {
		}

		template<typename C, typename InterFunc>
		GradientVertical<C, InterFunc>::GradientVertical( const GradientVertical<C, InterFunc> & gradient ) :
			GradientInterpolation<C, InterFunc>( gradient ),
			gradient( gradient.gradient ) {
		}

		template<typename C, typename InterFunc>
		GradientVertical<C, InterFunc>::GradientVertical( GradientVertical<C, InterFunc> && gradient ) :
			GradientInterpolation<C, InterFunc>( Utility::toRValue( gradient ) ),
			gradient( Utility::toRValue( gradient.gradient ) ) {
		}

		template<typename C, typename InterFunc>
		C GradientVertical<C, InterFunc>::operator()( const Math::Vec2<Size> & p ) const {
			return this -> interpolatedArray[p.y];
		}
		template<typename C, typename InterFunc>
		void GradientVertical<C, InterFunc>::init( const Math::Rectangle<Size> & rectangle ) {
			this -> size = rectangle.getTop() - rectangle.getBottom();
			delete[] this -> interpolatedArray;
			this -> interpolatedArray = new C[this -> size];
			this -> gradient.computeInterpolation( this -> interpolatedArray, this -> size );
		}

		template<typename C, typename InterFunc>
		GradientVertical<C, InterFunc> & ColorFunc::GradientVertical<C, InterFunc>::operator=( const GradientVertical<C, InterFunc> & gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( gradient );
			this -> gradient = gradient.gradient;
			return *this;
		}

		template<typename C, typename InterFunc>
		GradientVertical<C, InterFunc> & ColorFunc::GradientVertical<C, InterFunc>::operator=( GradientVertical<C, InterFunc> && gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( Utility::toRValue( gradient ) );
			this -> gradient = Utility::toRValue( gradient.gradient );
			return *this;
		}

		template<typename C, typename InterFunc>
		bool GradientVertical<C, InterFunc>::read( std::fstream * fileStream ) {
			if ( !GradientInterpolation<C, InterFunc>::read( fileStream ) )
				return false;
			if ( !IO::read( fileStream, &this -> gradient ) )
				return false;

			return true;
		}

		template<typename C, typename InterFunc>
		bool GradientVertical<C, InterFunc>::write( std::fstream * fileStream ) const {
			if ( !GradientInterpolation<C, InterFunc>::write( fileStream ) )
				return false;
			if ( !IO::write( fileStream, &this -> gradient ) )
				return false;

			return true;
		}

		//////////////////////////////////////////////////////////////////////////
        //// LINEAR
		template<typename C, typename InterFunc>
		GradientLinear<C, InterFunc>::GradientLinear( const Graphic::Gradient::Linear<C, InterFunc> & gradient ) : 
			gradient( gradient ) {

		}

		template<typename C, typename InterFunc>
		GradientLinear<C, InterFunc>::GradientLinear( const GradientLinear<C, InterFunc> & gradient ) :
			GradientInterpolation<C, InterFunc>( gradient ),
			gradient( gradient.gradient ),
			origin(gradient.origin),
			sizeMinusOne(gradient.sizeMinusOne){
		}

		template<typename C, typename InterFunc>
		GradientLinear<C, InterFunc>::GradientLinear( GradientLinear<C, InterFunc> && gradient ) :
			GradientInterpolation<C, InterFunc>( Utility::toRValue( gradient ) ),
			gradient( Utility::toRValue( gradient.gradient ) ),
			origin( Utility::toRValue(gradient.origin )),
			sizeMinusOne( Utility::toRValue(gradient.sizeMinusOne )) {
		}

		template<typename C, typename InterFunc>
		void GradientLinear<C, InterFunc>::init( const Math::Rectangle<Size> & rectangle ) {
			Math::Vec2<int> size = rectangle.getRightTop() - rectangle.getLeftBottom();

			if ( gradient.getLength() == 0 )
				this -> size = size.x * Math::abs( gradient.getDirection().x ) + size.y * Math::abs( gradient.getDirection().y );
			else
				this -> size = gradient.getLength();

			this -> sizeMinusOne = this -> size - 1;

			delete[] this -> interpolatedArray;
			this -> interpolatedArray = new C[this -> size];
			this -> gradient.computeInterpolation( this -> interpolatedArray, this -> size );

			this -> origin.x = gradient.getPoint().x * float( rectangle.getRight() - rectangle.getLeft() );
			this -> origin.y = gradient.getPoint().y * float( rectangle.getTop() - rectangle.getBottom() );
		}

		template<typename C, typename InterFunc>
		C GradientLinear<C, InterFunc>::operator()( const Math::Vec2<Size> & p ) const {
			auto index = gradient.computeIndex( Math::Vec2<float>( p.x - this -> origin.x, p.y - this -> origin.y ), this -> sizeMinusOne );
			return this -> interpolatedArray[index];
		}

		template<typename C, typename InterFunc>
		GradientLinear<C, InterFunc> & ColorFunc::GradientLinear<C, InterFunc>::operator=( const GradientLinear<C, InterFunc> & gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( gradient );
			this -> gradient = gradient.gradient;
			this -> origin = gradient.origin;
			this -> sizeMinusOne = gradient.sizeMinusOne;
			return *this;
		}

		template<typename C, typename InterFunc>
		GradientLinear<C, InterFunc> & ColorFunc::GradientLinear<C, InterFunc>::operator=( GradientLinear<C, InterFunc> && gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( Utility::toRValue( gradient ) );
			this -> gradient = Utility::toRValue( gradient.gradient );
			this -> origin = Utility::toRValue(gradient.origin);
			this -> sizeMinusOne = Utility::toRValue(gradient.sizeMinusOne);
			return *this;
		}

		template<typename C, typename InterFunc>
		bool GradientLinear<C, InterFunc>::read( std::fstream * fileStream ) {
			if ( !GradientInterpolation<C, InterFunc>::read( fileStream ) )
				return false;
			if ( !IO::read( fileStream, &this -> gradient ) )
				return false;

			return true;
		}

		template<typename C, typename InterFunc>
		bool GradientLinear<C, InterFunc>::write( std::fstream * fileStream ) const {
			if ( !GradientInterpolation<C, InterFunc>::write( fileStream ) )
				return false;
			if ( !IO::write( fileStream, &this -> gradient ) )
				return false;

			return true;
		}

		//////////////////////////////////////////////////////////////////////////
		//// RADIAL
		template<typename C, typename InterFunc>
		ColorFunc::GradientRadial<C, InterFunc>::GradientRadial( const Graphic::Gradient::Radial<C, InterFunc> & gradient ) :
			gradient( gradient ) {

		}

		template<typename C, typename InterFunc>
		GradientRadial<C, InterFunc>::GradientRadial( const GradientRadial<C, InterFunc> & gradient ) :
			GradientInterpolation<C, InterFunc>( gradient ),
			gradient( gradient.gradient ),
			center( gradient.center ),
			sizeMinusOne( gradient.sizeMinusOne ) {
		}

		template<typename C, typename InterFunc>
		GradientRadial<C, InterFunc>::GradientRadial( GradientRadial<C, InterFunc> && gradient ) :
			GradientInterpolation<C, InterFunc>( Utility::toRValue( gradient ) ),
			gradient( Utility::toRValue( gradient.gradient ) ),
			center( Utility::toRValue( gradient.center ) ),
			sizeMinusOne( Utility::toRValue( gradient.sizeMinusOne ) ) {
		}

		template<typename C, typename InterFunc>
		void GradientRadial<C, InterFunc>::init( const Math::Rectangle<Size> & rectangle ) {
			Math::Vec2<int> size = rectangle.getRightTop() - rectangle.getLeftBottom();

			this -> size = Math::max<float>( gradient.getRadius().x * float( size.x ), gradient.getRadius().y * float( size.y ) ) * 2.0f;
			this -> sizeMinusOne = this -> size - 1;

			delete[] this -> interpolatedArray;
			this -> interpolatedArray = new C[this -> size];
			this -> gradient.computeInterpolation( this -> interpolatedArray, this -> size );

			this -> center.x = gradient.getCenter().x * float( rectangle.getRight() - rectangle.getLeft() );
			this -> center.y = gradient.getCenter().y * float( rectangle.getTop() - rectangle.getBottom() );
		}

		template<typename C, typename InterFunc>
		C GradientRadial<C, InterFunc>::operator()( const Math::Vec2<Size> & p ) const {
			auto index = gradient.computeIndex( Math::Vec2<float>( p.x - this -> center.x, p.y - this -> center.y ), this -> sizeMinusOne );
			return this -> interpolatedArray[index];
		}

		template<typename C, typename InterFunc>
		GradientRadial<C, InterFunc> & ColorFunc::GradientRadial<C, InterFunc>::operator=( const GradientRadial<C, InterFunc> & gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( gradient );
			this -> gradient = gradient.gradient;
			this -> center = gradient.center;
			this -> sizeMinusOne = gradient.sizeMinusOne;
			return *this;
		}

		template<typename C, typename InterFunc>
		GradientRadial<C, InterFunc> & ColorFunc::GradientRadial<C, InterFunc>::operator=( GradientRadial<C, InterFunc> && gradient ) {
			GradientInterpolation<C, InterFunc>::operator=( Utility::toRValue( gradient ) );
			this -> gradient = Utility::toRValue( gradient.gradient );
			this -> center = Utility::toRValue( gradient.center );
			this -> sizeMinusOne = Utility::toRValue( gradient.sizeMinusOne );
			return *this;
		}

		template<typename C, typename InterFunc>
		bool GradientRadial<C, InterFunc>::read( std::fstream * fileStream ) {
			if ( !GradientInterpolation<C, InterFunc>::read( fileStream ) )
				return false;
			if ( !IO::read( fileStream, &this -> gradient ) )
				return false;

			return true;
		}

		template<typename C, typename InterFunc>
		bool GradientRadial<C, InterFunc>::write( std::fstream * fileStream ) const {
			if ( !GradientInterpolation<C, InterFunc>::write( fileStream ) )
				return false;
			if ( !IO::write( fileStream, &this -> gradient ) )
				return false;

			return true;
		}
	}







}
