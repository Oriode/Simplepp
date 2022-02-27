
namespace Graphic {

	namespace FontLoadingFunc {

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::Effect() :
			bShadowActivated( false ),
			bStrokeActivated( false ),
			shadowBias( 0.0f ),
			strokeSize( 0.0f ),
			shadowRadius( 0.0f ) {

		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::_updateBias() {
			this -> bias.x = Math::min<float>( this -> shadowBias.x - this -> shadowRadius, 0 );
			this -> bias.x = Math::min<float>( -float( this -> strokeSize ), this -> bias.x );

			this -> bias.y = Math::min<float>( this -> shadowBias.y - this -> shadowRadius, 0 );
			this -> bias.y = Math::min<float>( -float( this -> strokeSize ), this -> bias.y );

			this -> margins.setLeft( Math::ceil( -this -> bias.x ) );
			this -> margins.setBottom( Math::ceil( -this -> bias.y ) );

			this -> margins.setRight( Math::ceil( Math::max<float>( Math::max<float>( this -> shadowBias.x + this -> shadowRadius, 0.0f ), this -> strokeSize ) ) );
			this -> margins.setTop( Math::ceil( Math::max<float>( Math::max<float>( this -> shadowBias.y + this -> shadowRadius, 0.0f ), this -> strokeSize ) ) );
		}


		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		template<typename T>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::operator()( ImageT<T> * image, const unsigned char * buffer, const Math::Vec2<float> & size ) {
			// Lets create a new image that will be the mask image
			ImageT<T> imageMask( buffer, size, LoadingFormat::R, true );

			// Now Clear the final image
			image -> clear( Math::Vec2<Size>( Size( -this -> bias.x + size.x ) + this -> margins.getRight(), Size( -this -> bias.y + size.y ) + this -> margins.getTop() ), Format::RGBA );

			image -> fillImage( ColorRGBA<T>( Color<T>::getMin(), Color<T>::getMin(), Color<T>::getMin(), Color<T>::getMin() ) );

			// Draw the shadow
			if ( this -> bShadowActivated ) image -> drawImageShadowFunctor<ShadowColorFunc, BlendingFunc::None>( Point( float( this -> margins.getLeft() + this -> shadowBias.x ), float(this -> margins.getBottom() + this -> shadowBias.y ) ), this -> shadowRadius, imageMask, this -> shadowColorFunc, BlendingFunc::None() );

			// Draw the stroke effect
			if ( this -> bStrokeActivated && this -> bShadowActivated ) image -> drawStrokeFunctor<StrokeColorFunc>( this -> margins.getLeftBottom(), imageMask, this -> strokeSize, this -> strokeColorFunc, ImageT<T>::StrokeType::Outside );
			else if ( this -> bStrokeActivated && !this -> bShadowActivated )image -> drawStrokeFunctor<StrokeColorFunc, BlendingFunc::None>( this -> margins.getLeftBottom(), imageMask, this -> strokeSize, this -> strokeColorFunc, ImageT<T>::StrokeType::Outside, BlendingFunc::None() );

			// Draw the mask with the color functor to the final image
			if ( !this -> bStrokeActivated && !this -> bShadowActivated) image -> drawImageFunctor<OverlayColorFunc, BlendingFunc::None>( this -> margins.getLeftBottom(), this -> overlayColorFunc, Rectangle( imageMask.getSize() ), imageMask, BlendingFunc::None() );
			else image -> drawImageFunctor<OverlayColorFunc>( this -> margins.getLeftBottom(), this -> overlayColorFunc, Rectangle( imageMask.getSize() ), imageMask );

			// Finish !
		}


		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowActivated( bool bActivated ) {
			this -> bShadowActivated = bActivated;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		bool Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::isShadowActivated() const {
			return this -> bShadowActivated;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowRadius( unsigned int radius ) {
			this -> shadowRadius = radius;
			_updateBias();
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		unsigned int Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getShadowRadius() const {
			return this -> shadowRadius;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowBias( const Math::Vec2<float> & bias ) {
			this -> shadowBias = bias;
			_updateBias();
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		const Math::Vec2<float> & Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getShadowBias() const {
			return this -> shadowBias;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowColorFunc( const ShadowColorFunc & colorFunc ) {
			this -> shadowColorFunc = colorFunc;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		ShadowColorFunc & Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getShadowColorFunc() {
			return this -> shadowColorFunc;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setStrokeActivated( bool bActivated ) {
			this -> bStrokeActivated = bActivated;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		bool Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::isStrokeActivated() const {
			return this -> bStrokeActivated;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setStrokeColorFunc( const StrokeColorFunc & colorFunc ) {
			this -> strokeColorFunc = colorFunc;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		StrokeColorFunc & Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getStrokeColorFunc() {
			return this -> strokeColorFunc;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setStrokeSize( float size ) {
			this -> strokeSize = size;
			_updateBias();
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		float Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getStrokeSize() const {
			return this -> strokeSize;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setOverlayColorFunc( const OverlayColorFunc & colorFunc ) {
			this -> overlayColorFunc = colorFunc;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		OverlayColorFunc & Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getOverlayColorFunc() {
			return this -> overlayColorFunc;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		void Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::clear() {
			this -> bShadowActivated = false;
			this -> shadowRadius = 0;
			this -> shadowBias = Math::Vec2<float>::null;
			this -> bStrokeActivated = false;
			this -> strokeSize = 0;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		template<typename Stream>
		bool Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::read(Stream* stream ) {
			if ( !IO::read( stream, (Template *) this ) ) {
				clear();
				return false;
			}

			if ( !IO::read( stream, &this -> bShadowActivated ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> shadowRadius ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> shadowBias ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> bStrokeActivated ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> strokeSize ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> shadowColorFunc ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> strokeColorFunc ) ) {
				clear();
				return false;
			}
			if ( !IO::read( stream, &this -> overlayColorFunc ) ) {
				clear();
				return false;
			}

			// Clamping the data in case of file corruption
			this -> shadowRadius = Math::min( this -> shadowRadius, unsigned int( 100 ) );
			this -> shadowBias.x = Math::clamp( this -> shadowBias.x, -100.0f, 100.0f );
			this -> shadowBias.y = Math::clamp( this -> shadowBias.y, -100.0f, 100.0f );
			this -> strokeSize = Math::min( this -> strokeSize, 50.0f );

			return true;
		}

		template<typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
		template<typename Stream>
		bool Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::write(Stream* stream ) const {
			if ( !IO::write( stream, ( Template * ) this ) )
				return false;

			if ( !IO::write( stream, &this -> bShadowActivated ) )
				return false;

			if ( !IO::write( stream, &this -> shadowRadius ) )
				return false;

			if ( !IO::write( stream, &this -> shadowBias ) )
				return false;

			if ( !IO::write( stream, &this -> bStrokeActivated ) )
				return false;

			if ( !IO::write( stream, &this -> strokeSize ) )
				return false;

			if ( !IO::write( stream, &this -> shadowColorFunc ) )
				return false;

			if ( !IO::write( stream, &this -> strokeColorFunc ) )
				return false;

			if ( !IO::write( stream, &this -> overlayColorFunc ) )
				return false;



			return true;
		}
	}




	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::FontEffect() : FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>() {

	}



	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::FontEffect( const char * fileDump, size_t fileSize, int pixSize ) : FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>( fileDump, fileSize, pixSize ) {

	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::FontEffect( const WString & fileName, int pixSize ) : FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>( fileName, pixSize ) {

	}


	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	OverlayColorFunc & FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getOverlayColorFunc() {
		return this -> loadingFunctor.getOverlayColorFunc();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setOverlayColorFunc( const OverlayColorFunc & overlayColorFunc ) {
		this -> loadingFunctor.setOverlayColorFunc( overlayColorFunc );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	float FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getStrokeSize() const {
		return this -> loadingFunctor.getStrokeSize();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setStrokeSize( float size ) {
		this -> loadingFunctor.setStrokeSize( size );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	StrokeColorFunc & FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getStrokeColorFunc() {
		return this -> loadingFunctor.getStrokeColorFunc();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setStrokeColorFunc( const StrokeColorFunc & colorFunc ) {
		this -> loadingFunctor.setStrokeColorFunc( colorFunc );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	bool FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::isStrokeActivated() const {
		return this -> loadingFunctor.isStrokeActivated();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setStrokeActivated( bool bActivated ) {
		this -> loadingFunctor.setStrokeActivated( bActivated );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	ShadowColorFunc & FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getShadowColorFunc() {
		return this -> loadingFunctor.getShadowColorFunc();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowColorFunc( const ShadowColorFunc & colorFunc ) {
		this -> loadingFunctor.setShadowColorFunc( colorFunc );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	const Math::Vec2<float> & FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getShadowBias() const {
		return this -> loadingFunctor.getShadowBias();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowBias( const Math::Vec2<float> & bias ) {
		this -> loadingFunctor.setShadowBias( bias );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	unsigned int FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::getShadowRadius() const {
		return this -> loadingFunctor.getShadowRadius();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowRadius( unsigned int radius ) {
		this -> loadingFunctor.setShadowRadius( radius );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	bool FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::isShadowActivated() const {
		return this -> loadingFunctor.isShadowActivated();
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc>
	void FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::setShadowActivated( bool bActivated ) {
		this -> loadingFunctor.setShadowActivated( bActivated );
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc >
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc> & FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::operator=( FontEffect && fontEffect ) {
		FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>::operator =( Utility::toRValue( fontEffect ) );
		return *this;
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc >
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc> & FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::operator=( const FontEffect & fontEffect ) {
		FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>::operator =( fontEffect );
		return *this;
	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc >
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::FontEffect( const FontEffect & fontEffect ) : FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>( fontEffect ) {

	}

	template<typename T, typename OverlayColorFunc, typename StrokeColorFunc, typename ShadowColorFunc >
	FontEffect<T, OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>::FontEffect( FontEffect && fontEffect ) : FontT<T, FontLoadingFunc::Effect<OverlayColorFunc, StrokeColorFunc, ShadowColorFunc>>( Utility::toRValue( fontEffect ) ) {

	}

}
