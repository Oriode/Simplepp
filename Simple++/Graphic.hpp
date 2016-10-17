


namespace Graphic {





	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		_drawText<T, LoadingFunc, ColorR<T>, BlendFunc>( image, font, point, text, color, centered, blendFunc );
	}

	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		_drawText<T, LoadingFunc, ColorR<T>, BlendFunc>( image, font, rectangle, text, color, centered, blendFunc );
	}

	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		_drawText<T, LoadingFunc, ColorRGB<T>, BlendFunc>( image, font, point, text, color, centered, blendFunc );
	}

	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		_drawText<T, LoadingFunc, ColorRGB<T>, BlendFunc>( image, font, rectangle, text, color, centered, blendFunc );
	}

	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		_drawText<T, LoadingFunc, ColorRGBA<T>, BlendFunc>( image, font, point, text, color, centered, blendFunc );
	}

	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		_drawText<T, LoadingFunc, ColorRGBA<T>, BlendFunc>( image, font, rectangle, text, color, centered, blendFunc );
	}


	/************************************************************************/
	/* Horizontal Gradient                                                  */
	/************************************************************************/

	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Gradient::Horizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			struct ColorFunctor : public ColorFunc::Template<C> {
				ColorFunctor() {}
				inline C operator()( const Math::Vec2<Size> & p ) const {
					auto index = p.x + offset;
					return this -> interpolationDatas[index];
				}
				C * interpolationDatas;
				Size offset;
			};
			Functor( ImageT<T> * image, const Gradient::Horizontal<C, InterFunc> & gradient, BlendFunc & blendFunc ) : colorFunctor(), image( image ), gradient( gradient ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & rectangle ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}
			void operator()( float x, float y, const ImageT<T> & c ) {
				this -> colorFunctor.offset = x - this -> clampedRectangle.getLeft();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );

			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			ColorFunctor colorFunctor;
			ImageT<T> * image;
			BlendFunc & blendFunc;
			const Gradient::Horizontal<C, InterFunc> & gradient;
			Math::Rectangle<Size> clampedRectangle;
		};
		Functor functor( image, gradient, blendFunc );
		_drawTextWBB( font, point, text, centered, functor );
	}

	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Gradient::Horizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			struct ColorFunctor : public ColorFunc::Template<C> {
				ColorFunctor() {}
				inline C operator()( const Math::Vec2<Size> & p ) const {
					auto index = p.x + offset;
					return this -> interpolationDatas[index];
				}
				C * interpolationDatas;
				Size offset;
			};
			Functor( ImageT<T> * image, const Gradient::Horizontal<C, InterFunc> & gradient, const Rectangle & rectangle, BlendFunc & blendFunc ) : colorFunctor(), image( image ), blendFunc( blendFunc ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}

			void operator()( float x, float y, const ImageT<T> & c ) {
				this -> colorFunctor.offset = x - this -> clampedRectangle.getLeft();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc, false>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );
			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			ImageT<T> * image;
			BlendFunc & blendFunc;
			ColorFunctor colorFunctor;
			Math::Rectangle<Size> clampedRectangle;
		};
		auto rectangleClamped( image->clampRectangle( rectangle ) );

		Functor functor( image, gradient, rectangleClamped, blendFunc );
		_drawText( font, rectangleClamped, text, centered, functor );
	}

	/************************************************************************/
	/* Vertical Gradient	                                                */
	/************************************************************************/

	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Gradient::Vertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			struct ColorFunctor : public ColorFunc::Template<C> {
				ColorFunctor() {}
				inline C operator()( const Math::Vec2<Size> & p ) const {
					auto index = p.y + offset;
					return this -> interpolationDatas[index];
				}
				C * interpolationDatas;
				Size offset;
			};
			Functor( ImageT<T> * image, const Gradient::Vertical<C, InterFunc> & gradient, BlendFunc & blendFunc ) : colorFunctor(), image( image ), gradient( gradient ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & rectangle ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}
			void operator()( float x, float y, const ImageT<T> & c ) {
				this -> colorFunctor.offset = y - this -> clampedRectangle.getBottom();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );
			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			ColorFunctor colorFunctor;
			ImageT<T> * image;
			BlendFunc & blendFunc;
			const Gradient::Vertical<C, InterFunc> & gradient;
			Math::Rectangle<Size> clampedRectangle;
		};
		Functor functor( image, gradient, blendFunc );
		_drawTextWBB( font, point, text, centered, functor );
	}

	template<typename T, typename LoadingFunc, typename C, typename InterFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Gradient::Vertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			struct ColorFunctor : public ColorFunc::Template<C> {
				ColorFunctor() {}
				inline C operator()( const Math::Vec2<Size> & p ) const {
					auto index = p.y + offset;
					return this -> interpolationDatas[index];
				}
				C * interpolationDatas;
				Size offset;
			};
			Functor( ImageT<T> * image, const Gradient::Vertical<C, InterFunc> & gradient, const Rectangle & rectangle, BlendFunc & blendFunc ) : colorFunctor(), image( image ), blendFunc( blendFunc ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}

			void operator()( float x, float y, const ImageT<T> & c ) {
				this -> colorFunctor.offset = y - this -> clampedRectangle.getBottom();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc, false>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );
			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			ImageT<T> * image;
			BlendFunc & blendFunc;
			ColorFunctor colorFunctor;
			Math::Rectangle<Size> clampedRectangle;
		};
		auto rectangleClamped( image -> clampRectangle( rectangle ) );
		Functor functor( image, gradient, rectangleClamped, blendFunc );
		_drawText( font, rectangleClamped, text, centered, functor );
	}



	template<typename T, typename LoadingFunc, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			Functor( ImageT<T> * image, const C & color, BlendFunc & blendFunc ) : image( image ), color( color ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & size ) {}
			void operator()( float x, float y, const ImageT<T> & c ) { this -> image -> drawImage<BlendFunc, false>( Point( x, y ), this -> color, c, this -> blendFunc ); }
		private:
			ImageT<T> * image;
			const C & color;
			BlendFunc & blendFunc;
		};
		auto rectangleClamped( image -> clampRectangle( rectangle ) );
		Functor functor( image, color, blendFunc );
		_drawText( font, rectangleClamped, text, centered, functor );
	}


	template<typename T, typename LoadingFunc, typename C, typename BlendFunc>
	void _drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			Functor( ImageT<T> * image, const C & color, BlendFunc & blendFunc ) : image( image ), color( color ), blendFunc( blendFunc ) {}
			void onBegin( const Math::Vec2<float> & size ) {}
			void operator()( float x, float y, const ImageT<T> & c ) { this -> image -> drawImage( Point( x, y ), this -> color, c, this -> blendFunc ); }
		private:
			ImageT<T> * image;
			const C & color;
			BlendFunc & blendFunc;
		};
		Functor functor( image, color, blendFunc );
		_drawText( font, point, text, centered, functor );
	}



	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			Functor( ImageT<T> * image, BlendFunc & blendFunc ) : image( image ), blendFunc(blendFunc) {}
			void onBegin( const Rectangle & size ) {}
			void operator()( float x, float y, const ImageT<T> & c ) { this -> image ->  drawImage( Point( x, y ), c, Rectangle( c.getSize() ), this -> blendFunc ); }
		private:
			ImageT<T> * image;
			BlendFunc & blendFunc;
		};
		Functor functor( image, blendFunc );
		_drawText( font, point, text, centered, functor );
	}

	template<typename T, typename LoadingFunc, typename BlendFunc>
	void drawText( ImageT<T> * image, const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, BlendFunc & blendFunc ) {
		struct Functor {
			Functor( ImageT<T> * image, BlendFunc & blendFunc ) : image( image ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & size ) {}
			void operator()( float x, float y, const ImageT<T> & c ) { this -> image -> drawImage<false>( Point( x, y ), c, Rectangle( c.getSize() ), this -> blendFunc ); }
		private:
			ImageT<T> * image;
			BlendFunc & blendFunc;
		};
		Functor functor( image, blendFunc );
		_drawText( font, image->clampRectangle( rectangle ), text, centered, functor );
	}





	template<typename T, typename LoadingFunc, typename Func>
	void _drawTextWBB( const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func ) {
		Math::Vec2<float> initPoint( point );
		UCodePoint codePoint;

		Vector<float> lineWidth;
		lineWidth.reserve( 10 );
		float currentPosX = 0.0f;
		float rectangleHeight = font.getLineHeight();
		float maxLineWidth = 0.0f;
		Rectangle rectangle( 0, 0, 0, 0 );


		for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
			if ( codePoint == UCodePoint(UCodePoint('\n')) ) {
				rectangleHeight += font.getLineHeight();
				lineWidth.push( currentPosX * 0.5f );

				//
				maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );
				//

				currentPosX = 0;
			} else if ( codePoint == UCodePoint(' ') ) {
				currentPosX += font.getWordSpace();
			} else {
				const FreeTypeChar<T> * c = font[codePoint];
				if ( c ) currentPosX += c -> getHoriAdvance();
			}
		}
		lineWidth.push( currentPosX * 0.5f );
		maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );



		float marginY = font.getLineHeight() * 0.7f;
		if ( centered.y ) {
			float rectangleHeightHalfed = rectangleHeight * 0.5f;
			rectangle.setTop( initPoint.y + rectangleHeightHalfed );				//update BB
			rectangle.setBottom( initPoint.y - rectangleHeightHalfed );				//update BB
			initPoint.y = initPoint.y - marginY + rectangleHeightHalfed;

		} else {
			rectangle.setTop( initPoint.y + marginY );										//update BB
			rectangle.setBottom( initPoint.y + marginY - rectangleHeight );					//update BB
		}



		if ( centered.x ) {
			rectangle.setLeft( initPoint.x - maxLineWidth * 0.5f );
			rectangle.setRight( initPoint.x + maxLineWidth * 0.5f );

			func.onBegin( rectangle );

			Math::Vec2<float> currentPos( initPoint.x - lineWidth[0], initPoint.y );
			currentPos += font.getDrawingBias();
			unsigned int currentLine = 1;

			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;
				} else if ( codePoint == UCodePoint(' ') ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		} else {
			rectangle.setLeft( initPoint.x );
			rectangle.setRight( initPoint.x + maxLineWidth );

			func.onBegin( rectangle );

			Math::Vec2<float> currentPos( initPoint + font.getDrawingBias() );
			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == UCodePoint(' ') ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		}
	}





	template<typename T, typename LoadingFunc, typename Func>
	void _drawText( const _Font<T, LoadingFunc> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func ) {
		Math::Vec2<float> initPoint( point );
		UCodePoint codePoint;

		if ( centered.x ) {
			Vector<float> lineWidth;
			lineWidth.reserve( 10 );
			float currentPosX = 0.0f;
			float rectangleTop = font.getLineHeight();
			float maxLineWidth = 0.0f;


			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					rectangleTop += font.getLineHeight();
					lineWidth.push( currentPosX / 2.0f );

					//
					maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );
					//

					currentPosX = 0;
				} else if ( codePoint == UCodePoint(' ') ) {
					currentPosX += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						currentPosX += c -> getHoriAdvance();
					}
				}
			}
			lineWidth.push( currentPosX / 2.0f );
			maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );


			if ( centered.y ) {
				float rectangleTopHalfed = rectangleTop * 0.5f;
				initPoint.y = initPoint.y - font.getLineHeight() * 0.7f + rectangleTopHalfed;

			}






			Math::Vec2<float> currentPos( initPoint.x - lineWidth[0] + font.getDrawingBias().x, initPoint.y + font.getDrawingBias().y );
			unsigned int currentLine = 1;

			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;


				} else if ( codePoint == UCodePoint(' ') ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		} else {
			if ( centered.y ) {
				float rectangleTop = font.getLineHeight();
				for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
					if ( codePoint == UCodePoint('\n') ) rectangleTop += font.getLineHeight();
				}

				initPoint.y = initPoint.y - font.getLineHeight() * 0.7f + rectangleTop * 0.5f;
			}

			Math::Vec2<float> currentPos( initPoint + font.getDrawingBias() );
			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == UCodePoint(' ') ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}

			}
		}

	}




	template<typename T, typename LoadingFunc, typename Func>
	void _drawText( const _Font<T, LoadingFunc> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func ) {
		UCodePoint codePoint;
		Math::Vec2<int> rectangleSize( rectangle.getRight() - rectangle.getLeft(), rectangle.getTop() - rectangle.getBottom() );
		UTF8String textCopy( text );
		Math::Vec2<float> initPoint;



		if ( centered.x ) {
			Vector<float> lineWidth;
			lineWidth.reserve( 10 );
			float currentPosX = 0.0f;
			float rectangleTop = font.getLineHeight();


			auto it = textCopy.getBegin();
			auto lastIt = it;
			while ( true ) {

				//check if the next word will enter in the square.
				float tmpPosX = currentPosX;
				auto it2 = it;
				for ( ; textCopy.iterate( &it2, &codePoint ); ) {
					if ( codePoint == UCodePoint('\n') ) {
						goto drawText_afterIterate;	//if we reached the end of the word
					} else if ( codePoint == UCodePoint(' ') ) {
						tmpPosX += font.getWordSpace();
						goto drawText_afterIterate;	//if we reached the end of the word
					} else {
						const FreeTypeChar<T> * c = font[codePoint];
						if ( c ) tmpPosX += c -> getHoriAdvance();
					}
				}

				currentPosX = tmpPosX;


				break;
drawText_afterIterate:

				if ( tmpPosX > rectangleSize.x ) {
					//problem, the word is too big to enter in this line. replace the space with a new line.

					float newSize = tmpPosX - currentPosX - font.getWordSpace();
					lineWidth.push( currentPosX / 2.0f );
					if ( rectangleTop + font.getLineHeight() > rectangleSize.y ) {
						*( lastIt ) = '\0';
						//rectangle to small
						break;
					}
					currentPosX = newSize;
					*( lastIt ) = UCodePoint('\n');
					rectangleTop += font.getLineHeight();
					lastIt = it2 - 1;
				} else {
					currentPosX = tmpPosX;
					lastIt = it2 - 1;
					if ( *lastIt == UCodePoint('\n') ) {
						lineWidth.push( currentPosX / 2.0f );
						currentPosX = 0.0f;
						rectangleTop += font.getLineHeight();
					}
				}
				it = it2;
			}
			lineWidth.push( currentPosX / 2.0f );





			if ( centered.y ) {
				initPoint.y = rectangle.getTop() - font.getLineHeight() * 0.7f - ( rectangleSize.y - rectangleTop ) * 0.5f;
			} else {
				initPoint.y = rectangle.getTop() - font.getLineHeight();
			}
			initPoint.x = rectangle.getLeft() + rectangleSize.x / 2;


			Math::Vec2<float> currentPos( initPoint.x - lineWidth[0] + font.getDrawingBias().x, initPoint.y + font.getDrawingBias().y );
			unsigned int currentLine = 1;

			for ( auto it = textCopy.getBegin(); textCopy.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;
				} else if ( codePoint == UCodePoint(' ') ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						//image -> drawImage(Point(currentPos.x, currentPos.y + c -> getHoriOffsetY()), color, *c);
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		} else {


			float currentPosX = 0.0f;
			float rectangleTop = font.getLineHeight();

			auto it = textCopy.getBegin();
			auto lastIt = it;
			while ( true ) {

				//check if the next word will enter in the square.
				float tmpPosX = currentPosX;
				auto it2 = it;
				for ( ; textCopy.iterate( &it2, &codePoint ); ) {
					if ( codePoint == UCodePoint('\n') ) {
						goto drawText_afterIterate2;	//if we reached the end of the word
					} else if ( codePoint == UCodePoint(' ') ) {
						tmpPosX += font.getWordSpace();
						goto drawText_afterIterate2;	//if we reached the end of the word
					} else {
						const FreeTypeChar<T> * c = font[codePoint];
						if ( c ) tmpPosX += c -> getHoriAdvance();
					}
				}
				break;
drawText_afterIterate2:

				if ( tmpPosX > rectangleSize.x ) {
					//problem, the word is too big to enter in this line. replace the space with a new line.


					if ( rectangleTop + font.getLineHeight() > rectangleSize.y ) {
						*( lastIt ) = '\0';
						//rectangle to small
						break;
					}
					currentPosX = tmpPosX - currentPosX - font.getWordSpace();

					*( lastIt ) = UCodePoint('\n');
					rectangleTop += font.getLineHeight();
					lastIt = it2 - 1;

				} else {
					currentPosX = tmpPosX;
					lastIt = it2 - 1;
					if ( *lastIt == UCodePoint('\n') ) {
						currentPosX = 0.0f;
						rectangleTop += font.getLineHeight();
					}
				}
				it = it2;
			}



			if ( centered.y ) {
				initPoint.y = rectangle.getTop() - ( rectangleSize.y - rectangleTop ) * 0.5f - font.getLineHeight() * 0.7f;
			} else {
				initPoint.y = rectangle.getTop() - font.getLineHeight();
			}
			initPoint.x = rectangle.getLeft();


			Math::Vec2<float> currentPos( initPoint + font.getDrawingBias() );

			for ( auto it = textCopy.getBegin(); textCopy.iterate( &it, &codePoint ); ) {
				if ( codePoint == UCodePoint('\n') ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == UCodePoint(' ') ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}

			}
		}
	}


}
