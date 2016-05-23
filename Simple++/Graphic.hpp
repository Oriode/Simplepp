


namespace Graphic {





	template<typename T, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		_drawText<T, ColorR<T>, BlendFunc>(image, font, point, text, color, centered, blendFunc);
	}

	template<typename T, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const ColorR<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		_drawText<T, ColorR<T>, BlendFunc>(image, font, rectangle, text, color, centered, blendFunc);
	}

	template<typename T, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		_drawText<T, ColorRGB<T>, BlendFunc>(image, font, point, text, color, centered, blendFunc);
	}

	template<typename T, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGB<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		_drawText<T, ColorRGB<T>, BlendFunc>(image, font, rectangle, text, color, centered, blendFunc);
	}

	template<typename T, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		_drawText<T, ColorRGBA<T>, BlendFunc>(image, font, point, text, color, centered, blendFunc);
	}

	template<typename T, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		_drawText<T, ColorRGBA<T>, BlendFunc>(image, font, rectangle, text, color, centered, blendFunc);
	}


	/************************************************************************/
	/* Horizontal Gradient                                                  */
	/************************************************************************/

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const GradientHorizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		struct Functor {
			struct ColorFunctor {
				ColorFunctor() {}
				inline C operator()(const Math::Vec2<Size> & p) const {
					auto index = p.x - this -> gradientInterpolation -> getClampedRectangle().getLeft();
					return this -> gradientInterpolation -> getInterpolatedDatas()[index];
				}
				GradientHorizontalInterpolation<T, C, InterFunc> * gradientInterpolation;
			};
			Functor(_Image<T> * image, const GradientHorizontal<C, InterFunc> & gradient, const BlendFunc & blendFunc) : colorFunctor(), image(image), gradient(gradient), blendFunc(blendFunc) {}
			void onBegin(const Rectangle & rectangle) {
				this -> colorFunctor.gradientInterpolation = new GradientHorizontalInterpolation<T, C, InterFunc>(this -> gradient, *this -> image, rectangle);
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}
			void operator()(float x, float y, const _Image<T> & c) { 
				constexpr size_t N = sizeof(C) / sizeof(T);
				switch ( N ) {		//switch on a constexpr, will be interpreted during compilation
				case 1:			//R -> ?
					return this -> image -> drawImageR<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 3:			//R -> ?
					return this -> image -> drawImageRGB<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 4:			//R -> ?
					return this -> image -> drawImageRGBA<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				}
			}

			~Functor() { delete this -> colorFunctor.gradientInterpolation; }
		private:
			ColorFunctor colorFunctor;
			_Image<T> * image;
			const BlendFunc & blendFunc;
			const GradientHorizontal<C, InterFunc> & gradient;
		};
		Functor functor(image, gradient, blendFunc);
		_drawTextWBB(font, point, text, centered, functor);
	}

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const GradientHorizontal<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		struct Functor {
			struct ColorFunctor {
				ColorFunctor() {}
				inline C operator()(const Math::Vec2<Size> & p) const {
					auto index = p.x - this -> gradientInterpolation -> getClampedRectangle().getLeft();
					return this -> gradientInterpolation -> getInterpolatedDatas()[index];
				}
				GradientHorizontalInterpolation<T, C, InterFunc> * gradientInterpolation;
			};
			Functor(_Image<T> * image, const GradientHorizontal<C, InterFunc> & gradient, const Rectangle & rectangle, const BlendFunc & blendFunc) : colorFunctor(), image(image), blendFunc(blendFunc) {
				this -> colorFunctor.gradientInterpolation = new GradientHorizontalInterpolation<T, C, InterFunc>(gradient, *image, rectangle);
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}

			void operator()(float x, float y, const _Image<T> & c) {
				constexpr size_t N = sizeof(C) / sizeof(T);
				switch ( N ) {		//switch on a constexpr, will be interpreted during compilation
				case 1:			//R -> ?
					return this -> image -> drawImageR<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 3:			//R -> ?
					return this -> image -> drawImageRGB<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 4:			//R -> ?
					return this -> image -> drawImageRGBA<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				}
			}

			~Functor() { delete this -> colorFunctor.gradientInterpolation; }
		private:
			_Image<T> * image;
			const BlendFunc & blendFunc;
			ColorFunctor colorFunctor;
		};
		Functor functor(image, gradient, rectangle, blendFunc);
		_drawText(font, rectangle, text, centered, functor);
	}

	/************************************************************************/
	/* Vertical Gradient	                                                */
	/************************************************************************/

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const GradientVertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		struct Functor {
			struct ColorFunctor {
				ColorFunctor() {}
				inline C operator()(const Math::Vec2<Size> & p) const {
					auto index = p.y - this -> gradientInterpolation -> getClampedRectangle().getBottom();
					return this -> gradientInterpolation -> getInterpolatedDatas()[index];
				}
				GradientVerticalInterpolation<T, C, InterFunc> * gradientInterpolation;
			};
			Functor(_Image<T> * image, const GradientVertical<C, InterFunc> & gradient, const BlendFunc & blendFunc) : colorFunctor(), image(image), gradient(gradient), blendFunc(blendFunc) {}
			void onBegin(const Rectangle & rectangle) {
				this -> colorFunctor.gradientInterpolation = new GradientVerticalInterpolation<T, C, InterFunc>(this -> gradient, *this -> image, rectangle);
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}
			void operator()(float x, float y, const _Image<T> & c) {
				constexpr size_t N = sizeof(C) / sizeof(T);
				switch ( N ) {		//switch on a constexpr, will be interpreted during compilation
				case 1:			//R -> ?
					return this -> image -> drawImageR<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 3:			//R -> ?
					return this -> image -> drawImageRGB<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 4:			//R -> ?
					return this -> image -> drawImageRGBA<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				}
			}

			~Functor() { delete this -> colorFunctor.gradientInterpolation; }
		private:
			ColorFunctor colorFunctor;
			_Image<T> * image;
			const BlendFunc & blendFunc;
			const GradientVertical<C, InterFunc> & gradient;
		};
		Functor functor(image, gradient, blendFunc);
		_drawTextWBB(font, point, text, centered, functor);
	}

	template<typename T, typename C, typename InterFunc, typename BlendFunc>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const GradientVertical<C, InterFunc> & gradient, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		struct Functor {
			struct ColorFunctor {
				ColorFunctor() {}
				inline C operator()(const Math::Vec2<Size> & p) const {
					auto index = p.y - this -> gradientInterpolation -> getClampedRectangle().getBottom();
					return this -> gradientInterpolation -> getInterpolatedDatas()[index];
				}
				GradientVerticalInterpolation<T, C, InterFunc> * gradientInterpolation;
			};
			Functor(_Image<T> * image, const GradientVertical<C, InterFunc> & gradient, const Rectangle & rectangle, const BlendFunc & blendFunc) : colorFunctor(), image(image), blendFunc(blendFunc) {
				this -> colorFunctor.gradientInterpolation = new GradientVerticalInterpolation<T, C, InterFunc>(gradient, *image, rectangle);
				//this -> image -> drawRectangle(rectangle, ColorR<T>(42));						//DEBUG
			}

			void operator()(float x, float y, const _Image<T> & c) {
				constexpr size_t N = sizeof(C) / sizeof(T);
				switch ( N ) {		//switch on a constexpr, will be interpreted during compilation
				case 1:			//R -> ?
					return this -> image -> drawImageR<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 3:			//R -> ?
					return this -> image -> drawImageRGB<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				case 4:			//R -> ?
					return this -> image -> drawImageRGBA<ColorFunctor, BlendFunc>(Point(x, y), this -> colorFunctor, Rectangle(c.getSize()), c, this -> blendFunc);
				}
			}

			~Functor() { delete this -> colorFunctor.gradientInterpolation; }
		private:
			_Image<T> * image;
			const BlendFunc & blendFunc;
			ColorFunctor colorFunctor;
		};
		Functor functor(image, gradient, rectangle, blendFunc);
		_drawText(font, rectangle, text, centered, functor);
	}



	template<typename T, typename C, typename BlendFunc>
	void _drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		struct Functor {
			Functor(_Image<T> * image, const C & color, const BlendFunc & blendFunc) : image(image), color(color), blendFunc(blendFunc) {}
			void onBegin(const Rectangle & size) {}
			void operator()(float x, float y, const _Image<T> & c) { this -> image -> drawImage(Point(x, y), this -> color, c, this -> blendFunc); }
		private:
			_Image<T> * image;
			const C & color;
			const BlendFunc & blendFunc;
		};
		Functor functor(image, color, blendFunc);
		_drawText(font, rectangle, text, centered, functor);
	}


	template<typename T, typename C, typename BlendFunc>
	void _drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const C & color, const Math::Vec2<bool> & centered, const BlendFunc & blendFunc) {
		struct Functor {
			Functor(_Image<T> * image, const C & color, const BlendFunc & blendFunc) : image(image), color(color), blendFunc(blendFunc) {}
			void onBegin(const Math::Vec2<float> & size) {}
			void operator()(float x, float y, const _Image<T> & c) { this -> image -> drawImage(Point(x, y), this -> color, c, this -> blendFunc); }
		private:
			_Image<T> * image;
			const C & color;
			const BlendFunc & blendFunc;
		};
		Functor functor(image, color, blendFunc);
		_drawText(font, point, text, centered, functor);
	}



	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/) {
		struct Functor {
			Functor(_Image<T> * image) : image(image) {}
			void onBegin(const Rectangle & size) {}
			void operator()(float x, float y, const _Image<T> & c) { this -> image ->  drawImage(Point(x, y), c); }
		private:
			_Image<T> * image;
		};
		Functor functor(image);
		_drawText(font, point, text, centered, functor);
	}

	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/) {
		struct Functor {
			Functor(_Image<T> * image) : image(image) {}
			void onBegin(const Rectangle & size) {}
			void operator()(float x, float y, const _Image<T> & c) { this -> image -> drawImage(Point(x, y), c); }
		private:
			_Image<T> * image;
		};
		Functor functor(image);
		_drawText(font, rectangle, text, centered, functor);
	}





	template<typename Func>
	void _drawTextWBB(const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func) {
		Math::Vec2<float> initPoint(point);
		UCodePoint codePoint;

		Vector<float> lineWidth;
		lineWidth.reserve(10);
		float currentPosX = 0.0f;
		float rectangleHeight = font.getLineHeight();
		float maxLineWidth = 0.0f;
		Rectangle rectangle(0,0,0,0);


		for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
			if ( codePoint == '\n' ) {
				rectangleHeight += font.getLineHeight();
				lineWidth.push(currentPosX / 2.0f);

				//
				maxLineWidth = Math::max<float>(maxLineWidth, currentPosX);
				//

				currentPosX = 0;
			} else if ( codePoint == ' ' ) {
				currentPosX += font.getWordSpace();
			} else {
				const FreeTypeChar * c = font[codePoint];
				if ( c ) {
					currentPosX += c -> getHoriAdvance();
				}
			}
		}
		lineWidth.push(currentPosX / 2.0f);
		maxLineWidth = Math::max<float>(maxLineWidth, currentPosX);



		float marginY = font.getLineHeight() * 0.7f;
		if ( centered.y ) {
			float rectangleHeightHalfed = rectangleHeight * 0.5f;
			rectangle.setTop(initPoint.y + rectangleHeightHalfed);				//update BB
			rectangle.setBottom(initPoint.y - rectangleHeightHalfed);				//update BB
			initPoint.y = initPoint.y - marginY + rectangleHeightHalfed;

		} else {
			rectangle.setTop(initPoint.y + marginY);										//update BB
			rectangle.setBottom(initPoint.y + marginY - rectangleHeight);						//update BB
		}



		if ( centered.x ) {
			rectangle.setLeft(initPoint.x - maxLineWidth * 0.5f);
			rectangle.setRight(initPoint.x + maxLineWidth * 0.5f);

			func.onBegin(rectangle);

			Math::Vec2<float> currentPos(initPoint.x - lineWidth[0], initPoint.y);
			unsigned int currentLine = 1;

			for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;
				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						func(currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c);
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		} else {
			rectangle.setLeft(initPoint.x);
			rectangle.setRight(initPoint.x + maxLineWidth);

			func.onBegin(rectangle);

			Math::Vec2<float> currentPos(initPoint);
			for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						func(currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c);
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}
		}
	}





	template<typename Func>
	void _drawText(const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func) {
		Math::Vec2<float> initPoint(point);
		UCodePoint codePoint;

		if ( centered.x ) {
			Vector<float> lineWidth;
			lineWidth.reserve(10);
			float currentPosX = 0.0f;
			float rectangleTop = font.getLineHeight();
			float maxLineWidth = 0.0f;


			for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					rectangleTop += font.getLineHeight();
					lineWidth.push(currentPosX / 2.0f);

					//
					maxLineWidth = Math::max<float>(maxLineWidth, currentPosX);
					//

					currentPosX = 0;
				} else if ( codePoint == ' ' ) {
					currentPosX += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						currentPosX += c -> getHoriAdvance();
					}
				}
			}
			lineWidth.push(currentPosX / 2.0f);
			maxLineWidth = Math::max<float>(maxLineWidth, currentPosX);


			if ( centered.y ) {
				float rectangleTopHalfed = rectangleTop * 0.5f;
				initPoint.y = initPoint.y - font.getLineHeight() * 0.7f + rectangleTopHalfed;

			} 
			

		



			Math::Vec2<float> currentPos(initPoint.x - lineWidth[0], initPoint.y);
			unsigned int currentLine = 1;

			for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;


				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						func(currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c);
						//image -> drawImage(Point(currentPos.x, currentPos.y + c -> getHoriOffsetY()), color, *c);
						currentPos.x += c -> getHoriAdvance();
					}
				}
			}



		} else {
			if ( centered.y ) {
				float rectangleTop = font.getLineHeight();
				for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
					if ( codePoint == '\n' ) rectangleTop += font.getLineHeight();
				}

				initPoint.y = initPoint.y - font.getLineHeight() * 0.7f + rectangleTop * 0.5f;
			}

			Math::Vec2<float> currentPos(initPoint);
			for ( auto it = text.getBegin(); text.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						func(currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c);
						//image -> drawImage(Point(currentPos.x, currentPos.y + c -> getHoriOffsetY()), color, *c);
						currentPos.x += c -> getHoriAdvance();
					}
				}

			}
		}

	}




	template<typename Func>
	void _drawText(const Font & font, const Rectangle & rectangle, const UTF8String & text, const Math::Vec2<bool> & centered, Func & func) {
		UCodePoint codePoint;
		Math::Vec2<int> rectangleSize(rectangle.getRight() - rectangle.getLeft(), rectangle.getTop() - rectangle.getBottom());
		UTF8String textCopy(text);
		Math::Vec2<float> initPoint;



		if ( centered.x ) {
			Vector<float> lineWidth;
			lineWidth.reserve(10);
			float currentPosX = 0.0f;
			float rectangleTop = font.getLineHeight();


			auto it = textCopy.getBegin();
			auto lastIt = it;
			while (true) {
				
				//check if the next word will enter in the square.
				float tmpPosX = currentPosX;
				auto it2 = it;
				for ( ; textCopy.iterate(&it2, &codePoint); ) {
					if ( codePoint == '\n' ) {
						goto drawText_afterIterate;	//if we reached the end of the word
					} else if ( codePoint == ' ' ) {
						tmpPosX += font.getWordSpace();
						goto drawText_afterIterate;	//if we reached the end of the word
					} else {
						const FreeTypeChar * c = font[codePoint];
						if ( c ) tmpPosX += c -> getHoriAdvance();
					}
				}

				currentPosX = tmpPosX;


				break;
				drawText_afterIterate:

				if ( tmpPosX > rectangleSize.x ) {
					//problem, the word is too big to enter in this line. replace the space with a new line.

					float newSize = tmpPosX - currentPosX - font.getWordSpace();
					lineWidth.push(currentPosX / 2.0f);
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
						lineWidth.push(currentPosX / 2.0f);
						currentPosX = 0.0f;
						rectangleTop += font.getLineHeight();
					}
				}
				it = it2;
			}
			lineWidth.push(currentPosX / 2.0f);





			if ( centered.y ) {
				initPoint.y = rectangle.getTop() - font.getLineHeight() * 0.7f - ( rectangleSize.y - rectangleTop ) * 0.5f;
			} else {
				initPoint.y = rectangle.getTop() - font.getLineHeight();
			}
			initPoint.x = rectangle.getLeft() + rectangleSize.x / 2;


			Math::Vec2<float> currentPos(initPoint.x - lineWidth[0], initPoint.y);
			unsigned int currentLine = 1;

			for ( auto it = textCopy.getBegin(); textCopy.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x - lineWidth[currentLine];
					currentLine++;
				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						func(currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c);
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
				for ( ; textCopy.iterate(&it2, &codePoint); ) {
					if ( codePoint == '\n' ) {
						goto drawText_afterIterate2;	//if we reached the end of the word
					} else if ( codePoint == ' ' ) {
						tmpPosX += font.getWordSpace();
						goto drawText_afterIterate2;	//if we reached the end of the word
					} else {
						const FreeTypeChar * c = font[codePoint];
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
				initPoint.y = rectangle.getTop() - (rectangleSize.y - rectangleTop) * 0.5f - font.getLineHeight() * 0.7f;
			} else {
				initPoint.y = rectangle.getTop() - font.getLineHeight();
			}
			initPoint.x = rectangle.getLeft();


			Math::Vec2<float> currentPos(initPoint);

			for ( auto it = textCopy.getBegin(); textCopy.iterate(&it, &codePoint); ) {
				if ( codePoint == '\n' ) {
					currentPos.y -= font.getLineHeight();
					currentPos.x = initPoint.x;
				} else if ( codePoint == ' ' ) {
					currentPos.x += font.getWordSpace();
				} else {
					const FreeTypeChar * c = font[codePoint];
					if ( c ) {
						//image -> drawImage(Point(currentPos.x, currentPos.y + c -> getHoriOffsetY()), color, *c);
						func(currentPos.x, currentPos.y + c -> getHoriOffsetY(), *c);
						currentPos.x += c -> getHoriAdvance();
					}
				}

			}
		}
	}



	template<typename I, size_t N, typename C>
	I computeGaussianKernel(I(&kernel)[N], const float & sigma) {
		float kernelf[N];
		_computeGaussianKernelf<float, N>(kernelf, sigma);
		float newWeight = float(std::numeric_limits<I>::max() / Utility::TypesInfos<C>::getMax());

		for ( size_t i = 0; i < N; i++ ) {
			kernel[i] = I(kernelf[i] * newWeight);
		}
		return newWeight;
	}


	template<typename I, typename C>
	I computeGaussianKernel(I * kernel, size_t size, const float & sigma) {
		float * kernelf = new float[size];
		_computeGaussianKernelf<float>(kernelf, size, sigma);
		float newWeight = float(std::numeric_limits<I>::max() / Utility::TypesInfos<C>::getMax());

		for ( size_t i = 0; i < size; i++ ) {
			kernel[i] = I(kernelf[i] * newWeight);
		}
		delete[] kernelf;
		return I(newWeight);
	}



	template<size_t N>
	float computeGaussianKernel(float(&kernel)[N], const float & sigma) {
		return _computeGaussianKernelf<float, N>(kernel, sigma);
	}

	template<size_t N>
	double computeGaussianKernel(double(&kernel)[N], const double & sigma) {
		return _computeGaussianKernelf<double, N>(kernel, sigma);
	}

	float computeGaussianKernel(float * kernel, size_t size, const float & sigma) {
		return _computeGaussianKernelf<float>(kernel, size, sigma);
	}

	double computeGaussianKernel(double * kernel, size_t size, const double & sigma) {
		return _computeGaussianKernelf<double>(kernel, size, sigma);
	}



	template<typename T, size_t N>
	T _computeGaussianKernelf(T(&kernel)[N], const T & sigma) {
		assert(N % 2 == 1);
		const size_t NHalfed = N / 2;

		T sigma2Square = T(2) * ( sigma * sigma );
		T sum(1);
		kernel[NHalfed] = T(1);
		for ( size_t i = 0; i < NHalfed; i++ ) {
			size_t i2 = NHalfed - i;

			T v = Math::exp(-( ( T(i2 * i2) ) / sigma2Square ));
			kernel[i] = v;
			kernel[N - i - 1] = v;

			sum += v * T(2);
		}

		//normalize datas
		T oneOnSum = T(1) / sum;
		for ( size_t i = 0; i < N; i++ )
			kernel[i] *= oneOnSum;

		return sum;
		
	}

	template<typename T>
	T _computeGaussianKernelf(T * kernel, size_t size, const T & sigma) {
		assert(size % 2 == 1);
		const size_t NHalfed = size / 2;

		T sigma2Square = T(2) * ( sigma * sigma );
		T sum(1);
		kernel[NHalfed] = T(1);
		for ( size_t i = 0; i < NHalfed; i++ ) {
			size_t i2 = NHalfed - i;

			T v = Math::exp(-( ( T(i2 * i2) ) / sigma2Square ));
			kernel[i] = v;
			kernel[size - i - 1] = v;

			sum += v * T(2);
		}

		//normalize datas
		T oneOnSum = T(1) / sum;
		for ( size_t i = 0; i < size; i++ )
			kernel[i] *= oneOnSum;

		return sum;

	}



	template<size_t N>
	unsigned int computeGaussianKernel(unsigned int(&kernel)[N]) {
		return computeGaussianKernel(kernel, N);
	}

	unsigned int computeGaussianKernel(unsigned int * kernel, size_t size) {
		assert(size % 2 == 1);

		size_t NHalfed = size / 2;

		static const size_t kernelOffsets[] = { 0,1,4,9,16,25,36,49,64,81,100 };
		static const unsigned int kernels[] = {
			16843008 ,
			3799952, 9243102, 3799952 ,
			1556650, 4065498, 5598710, 4065498, 1556650 ,
			922672, 2087247, 3406352, 4010465, 3406352, 2087247, 922672 ,
			643095, 1283892, 2103754, 2829273, 3122973, 2829273, 2103754, 1283892, 643095 ,
			489598, 887694, 1410129, 1962580, 2393142, 2556714, 2393142, 1962580, 1410129, 887694, 489598 ,
			393717, 662714, 1014731, 1413381, 1790815, 2064076, 2164134, 2064076, 1790815, 1413381, 1014731, 662714, 393717 ,
			328544, 521597, 771245, 1062103, 1362253, 1627293, 1810466, 1875997, 1810466, 1627293, 1362253, 1062103, 771245, 521597, 328544 ,
			281534, 426443, 611148, 828683, 1063131, 1290449, 1482008, 1610336, 1655536, 1610336, 1482008, 1290449, 1063131, 828683, 611148, 426443, 281534 ,
			246101, 358696, 500138, 667123, 851280, 1039180, 1213558, 1355757, 1448954, 1481423, 1448954, 1355757, 1213558, 1039180, 851280, 667123, 500138, 358696, 246101 ,
			218479, 308389, 419789, 551069, 697630, 851701, 1002749, 1138520, 1246616, 1316339, 1340436, 1316339, 1246616, 1138520, 1002749, 851701, 697630, 551069, 419789, 308389, 218479
		};

		if ( NHalfed <= 10 ) {
			memcpy(kernel, kernels + kernelOffsets[NHalfed], sizeof(unsigned int) * size);
			return 16843008;
		} else {
			return computeGaussianKernel<unsigned int>(kernel, size, float(size) / 4.0f);

		}
	}

}
