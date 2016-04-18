namespace Graphic {


	template<typename T>
	using ColorRGBA = Math::Vec4<T>;
	template<typename T>
	using ColorRGB = Math::Vec3<T>;
	template<typename T>
	using ColorR = T;

	typedef Math::Vec2<int> Point;
	typedef Math::Rectangle<int> Rectangle;

	enum class Format : unsigned int { R = 1, RGB = 3, RGBA = 4 };
	enum class LoadingFormat { R, RGB, BGR, RGBA, BGRA };

	namespace BlendingFunc {

		class Normal {
		public:
			//WITHOUT MASK
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc) const { blendColor(colorDest, colorSrc); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc) const { blendColor(colorDest, colorSrc); }

			//WITH MASK
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorR<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }
			template<typename T> void operator()(ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }

			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }
			template<typename T> void operator()(ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }

			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }
			template<typename T> void operator()(ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, const ColorR<T> & colorMask) const { blendColor(colorDest, colorSrc, colorMask); }


			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest = colorSrc;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest.r = colorSrc;
				colorDest.g = colorSrc;
				colorDest.b = colorSrc;
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc) {
				colorDest.r = colorSrc;
				colorDest.g = colorSrc;
				colorDest.b = colorSrc;
				colorDest.a = _Image<I>::getComponentMaxValue();
			}

			/************************************************************************/
			/* RGB -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGB<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				colorDest = I(( Bigger(colorSrc.r) + Bigger(colorSrc.g) + Bigger(colorSrc.b) ) / Bigger(3));
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorRGB<float> & colorSrc) {
				colorDest = ( colorSrc.r + colorSrc.g + colorSrc.b ) / float(3);
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGB<double> & colorSrc) {
				colorDest = ( colorSrc.r + colorSrc.g + colorSrc.b ) / double(3);
			}
			/************************************************************************/
			/* RGB -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			/************************************************************************/
			/* RGB -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = _Image<I>::getComponentMaxValue();
			}

			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorSrc.a);
				Bigger sum = Bigger(colorSrc.r) + Bigger(colorSrc.g) + Bigger(colorSrc.b);

				colorDest = ( colorDest * oneMinusAlpha + ( sum / Bigger(3) ) * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();
			}

			inline static void blendColor(ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest = colorDest * oneMinusAlpha + ( sum / F(3.0) ) * colorSrc.a;
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest = colorDest * oneMinusAlpha + ( sum / F(3.0) ) * colorSrc.a;
			}


			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorSrc.a);

				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();

			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorSrc.a);

				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.a = ( colorDest.a * oneMinusAlpha ) >> Utility::TypesInfos<I>::getNbBits() + colorSrc.a;


			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
				colorDest.a = colorDest.a * oneMinusAlpha + colorSrc.a;

			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorSrc.a;
				F sum = colorSrc.r + colorSrc.g + colorSrc.b;

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
				colorDest.a = colorDest.a * oneMinusAlpha + colorSrc.a;
			}


			/************************************************************************/
			/* WITH MASK                                                            */
			/************************************************************************/
			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorR<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorMask);
				colorDest = ( Bigger(colorDest) * oneMinusAlpha + Bigger(colorSrc) * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorR<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorMask;
				colorDest = colorDest * oneMinusAlpha + colorSrc * colorMask;
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorR<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorMask;
				colorDest = colorDest * oneMinusAlpha + colorSrc * colorMask;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorMask);

				Bigger tmp = Bigger(colorSrc) * Bigger(colorMask);

				colorDest.r = ( Bigger(colorDest.r) * oneMinusAlpha + tmp ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.g = ( Bigger(colorDest.g) * oneMinusAlpha + tmp ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.b = ( Bigger(colorDest.b) * oneMinusAlpha + tmp ) >> Utility::TypesInfos<I>::getNbBits();
			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorMask;
				F tmp = colorSrc * colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorMask;
				F tmp = colorSrc * colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorMask);

				Bigger tmp = Bigger(colorSrc) * Bigger(colorMask);

				colorDest.r = ( Bigger(colorDest.r) * oneMinusAlpha + tmp ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.g = ( Bigger(colorDest.g) * oneMinusAlpha + tmp ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.b = ( Bigger(colorDest.b) * oneMinusAlpha + tmp ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.a = ( Bigger(colorDest.a) * oneMinusAlpha ) >> Utility::TypesInfos<I>::getNbBits() + colorMask;

			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorMask;
				F tmp = colorSrc * colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
				colorDest.a = ( colorDest.a * oneMinusAlpha + colorMask );
			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorMask;
				F tmp = colorSrc * colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
				colorDest.a = ( colorDest.a * oneMinusAlpha + colorMask );
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorMask);
				Bigger sum = ( Bigger(colorSrc.r) + Bigger(colorSrc.g) + Bigger(colorSrc.b) ) / Bigger(3);
				colorDest = ( Bigger(colorDest) * oneMinusAlpha + sum * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorMask;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * colorMask );
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorMask;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * colorMask );
			}
			/************************************************************************/
			/* RGB -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorMask);
				colorDest.r = ( Bigger(colorDest.r) * oneMinusAlpha + colorSrc.r * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.g = ( Bigger(colorDest.g) * oneMinusAlpha + colorSrc.g * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.b = ( Bigger(colorDest.b) * oneMinusAlpha + colorSrc.b * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * colorMask );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * colorMask );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * colorMask );
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * colorMask );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * colorMask );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * colorMask );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = ( 1 << Utility::TypesInfos<I>::getNbBits() ) - Bigger(colorMask);
				colorDest.r = ( Bigger(colorDest.r) * oneMinusAlpha + colorSrc.r * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.g = ( Bigger(colorDest.g) * oneMinusAlpha + colorSrc.g * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.b = ( Bigger(colorDest.b) * oneMinusAlpha + colorSrc.b * Bigger(colorMask) ) >> Utility::TypesInfos<I>::getNbBits();
				colorDest.a = ( Bigger(colorDest.a) * oneMinusAlpha ) >> Utility::TypesInfos<I>::getNbBits() + colorMask;
			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F oneMinusAlpha = F(1.0) - colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * colorMask );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * colorMask );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * colorMask );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + colorMask;

			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F oneMinusAlpha = F(1.0) - colorMask;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * colorMask );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * colorMask );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * colorMask );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + colorMask;
			}

			/************************************************************************/
			/* RGBA -> R                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;

				SuperBigger alpha = SuperBigger(colorMask) * SuperBigger(colorSrc.a);
				SuperBigger oneMinusAlpha = ( 1 << Utility::TypesInfos<Bigger>::getNbBits() ) - alpha;
				SuperBigger sum = ( SuperBigger(colorSrc.r) + SuperBigger(colorSrc.g) + SuperBigger(colorSrc.b) ) / SuperBigger(3);
				colorDest = ( SuperBigger(colorDest) * oneMinusAlpha + sum * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
			}
			inline static void blendColor(ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F alpha = colorMask * colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor(ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F alpha = colorMask * colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				F sum = ( colorSrc.r + colorSrc.g + colorSrc.b ) / F(3);
				colorDest = ( colorDest * oneMinusAlpha + sum * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				SuperBigger alpha = SuperBigger(colorMask) * SuperBigger(colorSrc.a);
				SuperBigger oneMinusAlpha = ( 1 << Utility::TypesInfos<Bigger>::getNbBits() ) - alpha;
				colorDest.r = ( SuperBigger(colorDest.r) * oneMinusAlpha + colorSrc.r * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
				colorDest.g = ( SuperBigger(colorDest.g) * oneMinusAlpha + colorSrc.g * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
				colorDest.b = ( SuperBigger(colorDest.b) * oneMinusAlpha + colorSrc.b * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
			}
			inline static void blendColor(ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F alpha = colorMask * colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			inline static void blendColor(ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F alpha = colorMask * colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor(ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, const ColorR<I> & colorMask) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				SuperBigger alpha = SuperBigger(colorMask) * SuperBigger(colorSrc.a);
				SuperBigger oneMinusAlpha = ( 1 << Utility::TypesInfos<Bigger>::getNbBits() ) - alpha;
				colorDest.r = ( SuperBigger(colorDest.r) * oneMinusAlpha + colorSrc.r * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
				colorDest.g = ( SuperBigger(colorDest.g) * oneMinusAlpha + colorSrc.g * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
				colorDest.b = ( SuperBigger(colorDest.b) * oneMinusAlpha + colorSrc.b * alpha ) >> Utility::TypesInfos<Bigger>::getNbBits();
				colorDest.a = ( SuperBigger(colorDest.a) * oneMinusAlpha ) >> Utility::TypesInfos<Bigger>::getNbBits() + alpha;
			}
			inline static void blendColor(ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, const ColorR<float> & colorMask) {
				typedef float F;
				F alpha = colorMask * colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;

			}
			inline static void blendColor(ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, const ColorR<double> & colorMask) {
				typedef double F;
				F alpha = colorMask * colorSrc.a;
				F oneMinusAlpha = F(1.0) - alpha;
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}

		};
	}



}
