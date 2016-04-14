#pragma once


#include "Log.h"
#include "BasicLoadableIO.h"
#include "Math.h"
#include "Vector.h"
#include "String.h"
#include "Utility.h"
#include "BasicIO.h"






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
				colorDest = (colorSrc.r + colorSrc.g + colorSrc.b) / float(3);
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
				colorDest = (Bigger(colorDest) * oneMinusAlpha + Bigger(colorSrc) * Bigger(colorMask)) >> Utility::TypesInfos<I>::getNbBits();
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
				F sum = (colorSrc.r + colorSrc.g + colorSrc.b) / F(3);
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











	///@brief Image Class
	///@template T Type of one pixel
	///@template F Format of the image
	template<typename T = unsigned char>		
	class _Image : public BasicIO {
	public:

		enum class ConvolutionMode {NormalSize, ExtendedSize};
		enum class ConversionMode {Luminance, Trunquate, Alpha};


		
		///@brief copy constructor with an another storage type
		///@param image image to copy
		template<typename C>
		_Image(const _Image<C> & image);

		///@brief Empty constructor, create an image unallocated of size (0:0)
		///@param format of the image
		_Image(Format format = Format::RGB);

		///@brief Constructor to create an initialized image of specified size.
		///@param size size of the image to create.
		///@param format of the image
		_Image(const Math::vec2ui & size, Format format = Format::RGB);

		///@brief create a new image data from a file stream.
		///@param fileStream Stream to read
		///@param format of the image
		_Image(std::fstream * fileStream);


		///@brief Constructor to create an image from a data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param format of the image
		///@param invertY if the image has to be flipped vertically or not.
		_Image(const T * data, const Math::vec2ui & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);

		///@brief copy constructor
		_Image(const _Image<T> & image);

		///@brief move constructor
		_Image(_Image<T> && image);

		~_Image();

		///@brief get the actual size (width:height) of the image
		///@return the actual size of this image
		const Math::vec2ui & getSize() const;

		///@brief get the actual width of the image
		///@return actual width of this image
		unsigned int getWidth() const;

		///@brief get the actual height of the image
		///@return actual height of this image
		unsigned int getHeight() const;

		
		///@brief get the number of pixels of this image
		///@return number of pixels
		size_t getNbPixels() const;

		///@brief reset this image with a new size.
		///@param size new size
		void clear(const Math::vec2ui & size);


		///@brief reset this image with a new size and a new format
		///@param size new size
		///@param format new format of the image
		void clear(const Math::vec2ui & size, Format format);


		///@brief set the data from an another data buffer.
		///@param data Data buffer to copy
		///@param size size of the new image
		///@param invertY if the image has to be flipped vertically or not.
		void setDatas(const T * data, const Math::vec2ui & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);


		///@brief create a new image from this one with a size of width / 2 and height / 2
		///@return new image created from this one with an halved size.
		template<typename C = unsigned short>
		_Image<T> * createMipmap();					

		///@brief get the data buffer of this image 
		///@return data buffer
		const T * getDatas() const;


		///@brief get the data buffer of this image 
		///@return data buffer
		T * getDatas();



		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		const T * getDatas(unsigned int x, unsigned int y) const;

		///@brief get the data buffer of this image starting with the selected pixel
		///@return data buffer
		T * getDatas(unsigned int x, unsigned int y);


		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		const T * getPixel(unsigned int x, unsigned int y) const;

		///@brief get a pixel from this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@return the pixel from the picture at the specified 2D coordinate.
		T * getPixel(unsigned int x, unsigned int y);


		///@brief get the offset of pixel from the beginning of the data
		///@param x X coordinate
		///@param y Y coordinate
		///@return offset to be added to go from the begining of the data (getData()) and the selected pixel
		size_t getDataOffset(unsigned int x, unsigned int y) const;



		///@brief set a pixel inside this image
		///@param x x coordinate of the pixel
		///@param y y coordinate of the pixel
		///@param p The pixel to set.
		void setPixel(unsigned int x, unsigned int y, const T * p);



		///@brief copy operator with another type
		///@param image Image to copy
		template<typename C>
		_Image<T> & operator=(const _Image<C> & image);

		///@brief copy operator
		///@param image Image to copy
		_Image<T> & operator=(const _Image<T> & image);

		///@brief move operator
		///@param image Image to move from
		_Image<T> & operator=(_Image<T> && image);


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(std::fstream * fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(std::fstream * fileStream) const;

		///@brief get the format of this image
		///@return format of this image
		Format getFormat() const;


		///@brief  get the number of components per pixels of this image.
		///@return Number of components per pixels.
		inline unsigned int getNbComponents() const;


		///@brief Create a new Image from this one with a new format
		///@param newFormat Format of the new image
		///@param conversionMode Only used when converted to Format::R (Luminance : Use the average of the RGB channels, Trunquate : Use the R channel, Alpha : Use the Alpha Channel)
		///@return Image based of this one with a new format
		_Image<T> toFormat(Format newFormat, ConversionMode conversionMode = ConversionMode::Luminance) const;



		///@brief get the maximum value of a color component
		///@param maximum value of a component depending of the template type T
		inline static T getComponentMaxValue();



		/************************************************************************/
		/* Drawing methods                                                      */
		/************************************************************************/

		///@brief Set a functor to each pixels in the rectangle of this image
		///@param functor Functor with operator() overloaded with 
		///					"void operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorR<T> * c);"
		///					"void operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorRGB<T> * c);"
		///					"void operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorRGBA<T> * c);"
		///														
		///@param rectangle Rectangle where to apply the functor.
		template<typename Func>
		void setPixels(Func & functor, const Rectangle & rectangle);



		///@brief Set a functor to each pixels of this image
		///@param functor Functor with operator() overloaded with 
		///					"void operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorR<T> * c);"
		///					"void operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorRGB<T> * c);"
		///					"void operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorRGBA<T> * c);"
		template<typename Func>
		void setPixels(Func & functor);


		///@brief fill the complete image with a color.
		///param color pointer to a color with the same number of component of this image
		void fill(const T * color);

		///@brief fill the complete image with a color.
		///@param color pointer to a color with the same number of component of this image
		///@param rectangle Rectangle where to fill the color
		void fill(const T * color, const Rectangle & rectangle);



		///@brief fill the complete image with a color.
		///@param color R color
		void fill(const ColorR<T> & color);

		///@brief fill the complete image with a color.
		///@param color RGB color
		void fill(const ColorRGB<T> & color);

		///@brief fill the complete image with a color.
		///@param color RGBA color
		void fill(const ColorRGBA<T> & color);


		///@brief fill the complete image with a color.
		///@param color R color
		///@param rectangle Rectangle where to fill the color
		void fill(const ColorR<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color RGB color
		///@param rectangle Rectangle where to fill the color
		void fill(const ColorRGB<T> & color, const Rectangle & rectangle);

		///@brief fill the complete image with a color.
		///@param color RGBA color
		///@param rectangle Rectangle where to fill the color
		void fill(const ColorRGBA<T> & color, const Rectangle & rectangle);



		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param image Another image to draw
		void drawImage(const Point & point, const _Image<T> & image);


		///@brief draw an another image into this one
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image);


		///@brief draw an another image into this one with a custom blending function
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw
		///@param functor Functor with operator() overloaded with 
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorR<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGB<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"
		///
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorR<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGB<T> & colorSrc)const;"
		///					"void operator()(Graphic::ColorRGBA<T> & colorDest, const Graphic::ColorRGBA<T> & colorSrc)const;"

		template<typename Func>
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Func & functor);





		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorR<T> & color, const _Image<T> & maskImage);

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGB<T> & color, const _Image<T> & maskImage);

		///@brief draw a color to this image using a mask
		///@param point Position where to draw.
		///@param color Color to draw
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGBA<T> & color, const _Image<T> & maskImage);

		




		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorR<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage);


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGB<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage);


		///@brief draw a color to this image using a mask and a rectangle to know the part of the mask to use.
		///@param point Position where to draw.
		///@param color Color to draw
		///@param rectangle Rectangle of the maskImage to draw. (the rectangle has to be positive and smaller than the size of the maskImage)
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const ColorRGBA<T> & color, const Rectangle & rectangle, const _Image<T> & maskImage);


		


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const _Image<T> & image, const _Image<T> & maskImage);

		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage);


		///@brief draw an another image into this one with a mask image
		///@param point Position where to draw.
		///@param rectangle rectangle of the second image to draw. (The rectangle HAS TO BE smaller or equal of the given image)
		///@param image Another image to draw.
		///@param maskPoint Point inside the mask to use.
		///@param maskImage mask to use (only the first component will be used to determine the luminance)
		void drawImage(const Point & point, const Rectangle & rectangle, const _Image<T> & image, const Point & maskPoint, const _Image<T> & maskImage);





		///@brief apply a symmetrical convolution filter (Gaussian blur for example)
		///@param filter Filter table (the table has to have an odd size)
		///@param convolutionMode Mode of the convolution (if the convolution will create a bigger image or crop it to keep the original size.)
		///@param color Color of the background
		///@return Image with the filter applied
		template<typename C, int N>
		_Image<T> applyFilter(const C(&filter)[N],  ConvolutionMode convolutionMode = ConvolutionMode::ExtendedSize, const ColorRGBA<T> & color = ColorRGBA<T>::null) const;



		


		

	protected:


	private:
		void _allocateAndCopy(const T * data, const Math::vec2ui & size, LoadingFormat loadingFormat = LoadingFormat::RGB, bool invertY = false);

		static Format loadingFormat2Format(LoadingFormat loadingFormat);

		inline Math::Rectangle<unsigned int> _clampRectangle(const Rectangle & rectangle) const;

		template<typename C, int N>
		_Image<T> _applyFilter(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<typename C, int N>
		_Image<T> _applyFilterf(const C(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<int N>
		_Image<T> _applyFilter(const float(&filter)[N], ConvolutionMode convolutionMode , const ColorRGBA<T> & color) const;

		template<int N>
		_Image<T> _applyFilter(const double(&filter)[N], ConvolutionMode convolutionMode, const ColorRGBA<T> & color) const;

		template<typename C = Math::vec3ui, typename PIX>
		_Image<T> * _createMipmap(_Image<T> * destinationImage);

		bool _read(std::fstream * fileStream);


		template<typename C, typename D>
		inline static void _castComponment(D * dest, const C * source);
		inline static void _castComponment(unsigned char * dest, const float * source);
		inline static void _castComponment(unsigned char * dest, const double * source);
		inline static void _castComponment(float * dest, const unsigned char * source);
		inline static void _castComponment(double * dest, const unsigned char * source);


		Format format;
		Math::vec2ui size;
		size_t nbPixels;
		T * buffer;

	};






	typedef _Image<unsigned char> Image;
	typedef _Image<float> ImageF;



}


#include "Image.hpp"
