
namespace Graphic {

	namespace FontLoadingFunc {

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::Effect() :
		bShadowActivated(false),
		bStrokeActivated(false),
			shadowBias(0.0f),
			strokeSize(0.0f),
			shadowRadius(0.0f)
		{
			
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::_updateBias() {
			this -> bias.x = Math::min<float>( this -> shadowBias.x - this -> shadowRadius, 0 );
			this -> bias.x = Math::min<float>( -float(this -> strokeSize), this -> bias.x );

			this -> bias.y = Math::min<float>( this -> shadowBias.y - this -> shadowRadius, 0 );
			this -> bias.y = Math::min<float>( -float(this -> strokeSize), this -> bias.y );
		}


		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::operator()( ImageT<T> * image, const unsigned char * buffer, const Math::Vec2<float> & size ) {
			Math::Vec2<float> bottomLeftExtend( -this -> bias.x, -this -> bias.y );
			Math::Vec2<float> topRightExtend( Math::max<float>( Math::max<float>( this -> shadowBias.x + this -> shadowRadius, 0.0f ), this -> strokeSize ),
											  Math::max<float>( Math::max<float>( this -> shadowBias.y + this -> shadowRadius, 0.0f ), this -> strokeSize ) );

			// Lets create a new image that will be the mask image
			ImageT<T> imageMask( buffer, size, LoadingFormat::R, true );

			// Now Clear the final image
			image -> clear( Math::Vec2<Size>( Size( -this -> bias.x + topRightExtend.x + size.x ), Size( -this -> bias.y + topRightExtend.y + size.y ) ), Format::RGBA );
			image -> fillImage( ColorRGBA<T>( Color<T>::getMin(), Color<T>::getMin(), Color<T>::getMin(), Color<T>::getMin() ) );

			// Draw the shadow
			if (this -> bShadowActivated) image -> drawImageShadowFunctor<ShadowColorFunc>( Point( bottomLeftExtend.x + this -> shadowBias.x, bottomLeftExtend.y + this -> shadowBias.y ), this -> shadowRadius, imageMask, this -> shadowColorFunc );
			
			

			// Draw the stroke effect
			if ( this -> bStrokeActivated ) image -> drawStrokeFunctor<StrokeColorFunc>( Point( bottomLeftExtend.x, bottomLeftExtend.y ), imageMask, this -> strokeSize, this -> strokeColorFunc, ImageT<T>::StrokeType::Outside );

			// Draw the mask with the color functor to the final image
			image -> drawImageFunctor<OverlayColorFunc>( Math::Vec2<Size>( bottomLeftExtend.x, bottomLeftExtend.y ), this -> overlayColorFunc, Rectangle( imageMask.getSize() ), imageMask );

			// Finish !
		}


		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setShadowActivated( bool bActivated ) {
			this -> bShadowActivated = bActivated;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		bool Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::isShadowActivated( ) const {
			return this -> bShadowActivated;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setShadowRadius( unsigned int radius ) {
			this -> shadowRadius = radius;
			_updateBias();
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		unsigned int Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::getShadowRadius() const {
			return this -> shadowRadius;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setShadowBias( const Math::Vec2<float> & bias ) {
			this -> shadowBias = bias;
			_updateBias();
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		const Math::Vec2<float> & Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::getShadowBias() const {
			return this -> shadowBias;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setShadowColorFunc( const ShadowColorFunc & colorFunc ) {
			this -> shadowColorFunc = colorFunc;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		ShadowColorFunc & Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::getShadowColorFunc( ) {
			return this -> shadowColorFunc;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setStrokeActivated( bool bActivated ) {
			this -> bStrokeActivated = bActivated;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		bool Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::isStrokeActivated() const {
			return this -> bStrokeActivated;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setStrokeColorFunc( const StrokeColorFunc & colorFunc ) {
			this -> strokeColorFunc = colorFunc;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		StrokeColorFunc & Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::getStrokeColorFunc() {
			return this -> strokeColorFunc;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setStrokeSize( float size ) {
			this -> strokeSize = size;
			_updateBias();
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		float Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::getStrokeSize() const {
			return this -> strokeSize;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		void Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::setOverlayColorFunc( const OverlayColorFunc & colorFunc ) {
			this -> overlayColorFunc = colorFunc;
		}

		template<typename T, typename StrokeColorFunc, typename ShadowColorFunc, typename OverlayColorFunc>
		OverlayColorFunc & Effect<T, StrokeColorFunc, ShadowColorFunc, OverlayColorFunc>::getOverlayColorFunc() {
			return this -> overlayColorFunc;
		}
	}

}
