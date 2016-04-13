


namespace Graphic {


	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/) {

		struct Functor {
			Functor(_Image<T> * image, const ColorRGBA<T> & color) : image(image), color(color) {}

			void operator()(float x, float y, const _Image<T> & c) {
				this -> image ->  drawImage(Point(x, y), this -> color, c);
			}
		private:
			_Image<T> * image;
			const ColorRGBA<T> & color;
		};

		Functor functor(image, color);

		_drawText(font, point, text, centered, functor);

	}

	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Rectangle & rectangle, const UTF8String & text, const ColorRGBA<T> & color, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/) {

		struct Functor {
			Functor(_Image<T> * image, const ColorRGBA<T> & color) : image(image), color(color) {}

			void operator()(float x, float y, const _Image<T> & c) {
				this -> image -> drawImage(Point(x, y), this -> color, c);
			}
		private:
			_Image<T> * image;
			const ColorRGBA<T> & color;
		};

		Functor functor(image, color);

		_drawText(font, rectangle, text, centered, functor);
	}









	template<typename T>
	void drawText(_Image<T> * image, const Font & font, const Point & point, const UTF8String & text, const Math::Vec2<bool> & centered /*= Math::Vec2<bool>(false)*/) {

		struct Functor {
			Functor(_Image<T> * image) : image(image) {}

			void operator()(float x, float y, const _Image<T> & c) {
				this -> image ->  drawImage(Point(x, y), c);
			}
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

			void operator()(float x, float y, const _Image<T> & c) {
				this -> image -> drawImage(Point(x, y), c);
			}
		private:
			_Image<T> * image;
		};

		Functor functor(image);

		_drawText(font, rectangle, text, centered, functor);
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

					///
					maxLineWidth = Math::max<float>(maxLineWidth, currentPosX);
					///

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
					if ( codePoint == ' ' ) {
						tmpPosX += font.getWordSpace();
						goto drawText_afterIterate;	//if we reached the end of the word
					} else {
						const FreeTypeChar * c = font[codePoint];
						if ( c ) tmpPosX += c -> getHoriAdvance();
					}
				}
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

				} else {
					currentPosX = tmpPosX;
				}
				lastIt = it2 - 1;
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
					if ( codePoint == ' ' ) {
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

				} else {
					currentPosX = tmpPosX;
				}
				lastIt = it2 - 1;
				it = it2;
			}



			if ( centered.y ) {
				initPoint.y = rectangle.getTop() - font.getLineHeight() * 0.7f - ( rectangleSize.y - rectangleTop) * 0.5f;
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












	template<typename T, size_t N>
	T * computeGaussianKernel(T(&kernel)[N], const T & sigmaL) {
		assert(N % 2 == 1);
		const size_t NHalfed = N / 2;
		const T sigma = NHalfed / T(2);

		for ( size_t i = 0; i < NHalfed; i++ ) {
			size_t i2 = NHalfed - i;

			T sigma2Square = T(2) * ( sigma * sigma );
			kernel[i] = Math::exp(-( ( i2 * i2 ) / sigma2Square ));

			//apply symmetric
			kernel[N - i - 1] = kernel[i];
		}

		kernel[NHalfed] = T(1);


		T sum(0);
		for ( size_t i = 0; i < N; i++ ) {
			sum += kernel[i];
		}

		for ( size_t i = 0; i < N; i++ ) {
			kernel[i] *= T(1) / sum;
		}

		return kernel;
	}



}