///@file ColorConvertFunc.hpp
///@brief File containing all the Color Conversions Functors
///@author Clement Gerber
///@date 30/09/2016 (DMY) 
#pragma once


#include "BasicGraphic.h"


namespace Graphic {

	namespace ColorConvertFunc {

		struct Template {
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const {};

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const {};

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const {};
		};


		struct Luminance {
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = colorSrc.getLightness();
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.getLightness();
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = colorSrc.a;
			}
		};


		struct Truncate {
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = Color<T>::getMax();
			}

			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = colorSrc.a;
			}
		};

		struct Alpha {
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { convertColor( colorDest, colorSrc ); };

			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = Color<T>::getMax();
				colorDest.g = Color<T>::getMax();
				colorDest.b = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) {
				colorDest.r = Color<T>::getMax();
				colorDest.g = Color<T>::getMax();
				colorDest.b = Color<T>::getMax();
				colorDest.a = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = Color<T>::getMax();
				colorDest.g = Color<T>::getMax();
				colorDest.b = Color<T>::getMax();
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) {
				colorDest.r = Color<T>::getMax();
				colorDest.g = Color<T>::getMax();
				colorDest.b = Color<T>::getMax();
				colorDest.a = Color<T>::getMax();
			}

			template<typename T>
			static void convertColor( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.a;
			}
			template<typename T>
			static void convertColor( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.a;
				colorDest.g = colorSrc.a;
				colorDest.b = colorSrc.a;
			}
			template<typename T>
			static void convertColor( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = colorSrc.a;
			}
		};



	}


}
