


namespace Graphic {





	template<typename T, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		_drawText<T, ColorR<T>, BlendFunc>( image, font, point, text, color, centered, blendFunc );
	}

	template<typename T, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		_drawText<T, ColorR<T>, BlendFunc>( image, font, rectangle, text, color, centered, blendFunc );
	}

	template<typename T, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		_drawText<T, ColorRGB<T>, BlendFunc>( image, font, point, text, color, centered, blendFunc );
	}

	template<typename T, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		_drawText<T, ColorRGB<T>, BlendFunc>( image, font, rectangle, text, color, centered, blendFunc );
	}

	template<typename T, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		_drawText<T, ColorRGBA<T>, BlendFunc>( image, font, point, text, color, centered, blendFunc );
	}

	template<typename T, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		_drawText<T, ColorRGBA<T>, BlendFunc>( image, font, rectangle, text, color, centered, blendFunc );
	}


	/************************************************************************/
	/* Horizontal Gradient                                                  */
	/************************************************************************/

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const GradientHorizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
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
			Functor( _Image<T> * image, const GradientHorizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc ) : colorFunctor(), image( image ), gradient( gradient ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & rectangle ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}
			void operator()( float x, float y, const _Image<T> & c ) {
				this -> colorFunctor.offset = x - this -> clampedRectangle.getLeft();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );

			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			ColorFunctor colorFunctor;
			_Image<T> * image;
			const BlendFunc & blendFunc;
			const GradientHorizontal<C, InterFunc> & gradient;
			Math::Rectangle<Size> clampedRectangle;
		};
		Functor functor( image, gradient, blendFunc );
		_drawTextWBB( font, point, text, centered, functor );
	}

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const GradientHorizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
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
			Functor( _Image<T> * image, const GradientHorizontal<C, InterFunc> & gradient, const Rectangle & rectangle, const BlendFunc & blendFunc ) : colorFunctor(), image( image ), blendFunc( blendFunc ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}

			void operator()( float x, float y, const _Image<T> & c ) {
				this -> colorFunctor.offset = x - this -> clampedRectangle.getLeft();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc, true>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );
			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			_Image<T> * image;
			const BlendFunc & blendFunc;
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

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const GradientVertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
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
			Functor( _Image<T> * image, const GradientVertical<C, InterFunc> & gradient, const BlendFunc & blendFunc ) : colorFunctor(), image( image ), gradient( gradient ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & rectangle ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}
			void operator()( float x, float y, const _Image<T> & c ) {
				this -> colorFunctor.offset = y - this -> clampedRectangle.getBottom();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );
			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			ColorFunctor colorFunctor;
			_Image<T> * image;
			const BlendFunc & blendFunc;
			const GradientVertical<C, InterFunc> & gradient;
			Math::Rectangle<Size> clampedRectangle;
		};
		Functor functor( image, gradient, blendFunc );
		_drawTextWBB( font, point, text, centered, functor );
	}

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const GradientVertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
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
			Functor( _Image<T> * image, const GradientVertical<C, InterFunc> & gradient, const Rectangle & rectangle, const BlendFunc & blendFunc ) : colorFunctor(), image( image ), blendFunc( blendFunc ) {
				this -> image -> computeInterpolation( gradient, &this -> colorFunctor.interpolationDatas, rectangle, &this -> clampedRectangle );
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}

			void operator()( float x, float y, const _Image<T> & c ) {
				this -> colorFunctor.offset = y - this -> clampedRectangle.getBottom();
				return this -> image -> drawImageFunctor<ColorFunctor, BlendFunc, true>( Point( x, y ), this -> colorFunctor, Rectangle( c.getSize() ), c, this -> blendFunc );
			}

			~Functor() { delete[] this -> colorFunctor.interpolationDatas; }
		private:
			_Image<T> * image;
			const BlendFunc & blendFunc;
			ColorFunctor colorFunctor;
			Math::Rectangle<Size> clampedRectangle;
		};
		auto rectangleClamped( image -> clampRectangle( rectangle ) );
		Functor functor( image, gradient, rectangleClamped, blendFunc );
		_drawText( font, rectangleClamped, text, centered, functor );
	}



	template<typename T, typename C, typename BlendFunc>
	void _drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		struct Functor {
			Functor( _Image<T> * image, const C & color, const BlendFunc & blendFunc ) : image( image ), color( color ), blendFunc( blendFunc ) {}
			void onBegin( const Rectangle & size ) {}
			void operator()( float x, float y, const _Image<T> & c ) { this -> image -> drawImage<BlendFunc, true>( Point( x, y ), this -> color, c, this -> blendFunc ); }
		private:
			_Image<T> * image;
			const C & color;
			const BlendFunc & blendFunc;
		};
		auto rectangleClamped( image->clampRectangle( rectangle ) );
		Functor functor( image, color, blendFunc );
		_drawText( font, rectangleClamped, text, centered, functor );
	}


	template<typename T, typename C, typename BlendFunc>
	void _drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc ) {
		struct Functor {
			Functor( _Image<T> * image, const C & color, const BlendFunc & blendFunc ) : image( image ), color( color ), blendFunc( blendFunc ) {}
			void onBegin( const Math::Vec2<float> & size ) {}
			void operator()( float x, float y, const _Image<T> & c ) { this -> image -> drawImage( Point( x, y ), this -> color, c, this -> blendFunc ); }
		private:
			_Image<T> * image;
			const C & color;
			const BlendFunc & blendFunc;
		};
		Functor functor( image, color, blendFunc );
		_drawText( font, point, text, centered, functor );
	}



	template<typename T>
	void drawText( _Image<T> * image, const Font<T> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/ ) {
		struct Functor {
			Functor( _Image<T> * image ) : image( image ) {}
			void onBegin( const Rectangle & size ) {}
			void operator()( float x, float y, const _Image<T> & c ) { this -> image ->  drawImage( Point( x, y ), c ); }
		private:
			_Image<T> * image;
		};
		Functor functor( image );
		_drawText( font, point, text, centered, functor );
	}

	template<typename T>
	void drawText( _Image<T> * image, const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/ ) {
		struct Functor {
			Functor( _Image<T> * image ) : image( image ) {}
			void onBegin( const Rectangle & size ) {}
			void operator()( float x, float y, const _Image<T> & c ) { this -> image -> drawImage<true>( Point( x, y ), c ); }
		private:
			_Image<T> * image;
		};
		Functor functor( image );
		_drawText( font, image->clampRectangle( rectangle ), text, centered, functor );
	}





	template<typename T, typename Func>
	void _drawTextWBB( const Font<T> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func ) {
		Math::Vec2<float> initPoint( point );
		UCodePoint codePoint;

		Vector<float> lineWidth;
		lineWidth.reserve( 10 );
		float currentPosX = 0.0f;
		float rectangleHeight = font.getLineHeight();
		float maxLineWidth = 0.0f;
		Rectangle rectangle( 0, 0, 0, 0 );


		for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
			if ( codePoint == '\n' ) {
				rectangleHeight += font.getLineHeight();
				lineWidth.push( currentPosX / 2.0f );

				//
				maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );
				//

				currentPosX = 0;
			} else if ( codePoint == ' ' ) {
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



		float marginY = font.getLineHeight() * 0.7f;
		if ( centered.y ) {
			float rectangleHeightHalfed = rectangleHeight * 0.5f;
			rectangle.setTop( initPoint.y + rectangleHeightHalfed );				//update BB
			rectangle.setBottom( initPoint.y - rectangleHeightHalfed );				//update BB
			initPoint.y = initPoint.y - marginY + rectangleHeightHalfed;

		} else {
			rectangle.setTop( initPoint.y + marginY );										//update BB
			rectangle.setBottom( initPoint.y + marginY - rectangleHeight );						//update BB
		}



		if ( centered.x ) {
			rectangle.setLeft( initPoint.x - maxLineWidth * 0.5f );
			rectangle.setRight( initPoint.x + maxLineWidth * 0.5f );

			func.onBegin( rectangle );

			Math::Vec2<float> currentPos( initPoint.x - lineWidth[0], initPoint.y );
			unsigned int currentLine = 1;

			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;
				} else if ( codePoint == ' ' ) {
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

			Math::Vec2<float> currentPos( initPoint );
			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == ' ' ) {
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





	template<typename T, typename Func>
	void _drawText( const Font<T> & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func ) {
		Math::Vec2<float> initPoint( point );
		UCodePoint codePoint;

		if ( centered.x ) {
			Vector<float> lineWidth;
			lineWidth.reserve( 10 );
			float currentPosX = 0.0f;
			float rectangleTop = font.getLineHeight();
			float maxLineWidth = 0.0f;


			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					rectangleTop += font.getLineHeight();
					lineWidth.push( currentPosX / 2.0f );

					//
					maxLineWidth = Math::max<float>( maxLineWidth, currentPosX );
					//

					currentPosX = 0;
				} else if ( codePoint == ' ' ) {
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






			Math::Vec2<float> currentPos( initPoint.x - lineWidth[0], initPoint.y );
			unsigned int currentLine = 1;

			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;


				} else if ( codePoint == ' ' ) {
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
			if ( centered.y ) {
				float rectangleTop = font.getLineHeight();
				for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
					if ( codePoint == '\n' ) rectangleTop += font.getLineHeight();
				}

				initPoint.y = initPoint.y - font.getLineHeight() * 0.7f + rectangleTop * 0.5f;
			}

			Math::Vec2<float> currentPos( initPoint );
			for ( auto it = text.getBegin(); text.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == ' ' ) {
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
		}

	}




	template<typename T, typename Func>
	void _drawText( const Font<T> & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func ) {
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
					if ( codePoint == '\n' ) {
						goto drawText_afterIterate;	//if we reached the end of the word
					} else if ( codePoint == ' ' ) {
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
					*( lastIt ) = '\n';
					rectangleTop += font.getLineHeight();
					lastIt = it2 - 1;
				} else {
					currentPosX = tmpPosX;
					lastIt = it2 - 1;
					if ( *lastIt == '\n' ) {
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


			Math::Vec2<float> currentPos( initPoint.x - lineWidth[0], initPoint.y );
			unsigned int currentLine = 1;

			for ( auto it = textCopy.getBegin(); textCopy.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;
				} else if ( codePoint == ' ' ) {
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
					if ( codePoint == '\n' ) {
						goto drawText_afterIterate2;	//if we reached the end of the word
					} else if ( codePoint == ' ' ) {
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

					*( lastIt ) = '\n';
					rectangleTop += font.getLineHeight();
					lastIt = it2 - 1;

				} else {
					currentPosX = tmpPosX;
					lastIt = it2 - 1;
					if ( *lastIt == '\n' ) {
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


			Math::Vec2<float> currentPos( initPoint );

			for ( auto it = textCopy.getBegin(); textCopy.iterate( &it, &codePoint ); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar<T> * c = font[codePoint];
					if ( c ) {
						//image -> drawImage(Point(currentPos.x, currentPos.y + c -> getHoriOffsetY()), color, *c);
						func( currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c );
						currentPos.x += c -> getHoriAdvance();
					}
				}

			}
		}
	}


}
