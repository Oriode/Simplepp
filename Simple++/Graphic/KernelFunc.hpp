///@file Image.h
///@brief Functions to be used in the applyFilter methods
///@author Clément Gerber
///@date 16/09/2016 (DMY) 

#pragma once

#include "../Math.h"
#include "BasicGraphic.h"



namespace Graphic {

	namespace KernelFunc {

		struct Template {

			///@brief Take the Color and modify it if necessary
			///@param color Color
			///@param max Maximum value allowed for each component of the color
			template<typename C, typename T> inline void operator()( C & color, const T & max ) {

			}

		};


		///@brief Do nothing
		///@see Graphic::KernelFunc::Template
		struct None : public Template {

		};

		///@brief Clamp the value between [-INF ; max ]
		///@see Graphic::KernelFunc::Template
		struct Min : public Template {
			template<typename T> inline void operator()( ColorR<T> & color, const T & max ) {
				color = Math::min( color, max );
			}

			template<typename T> inline void operator()( ColorRGB<T> & color, const T & max ) {
				color.r = Math::min( color.r, max );
				color.g = Math::min( color.g, max );
				color.b = Math::min( color.b, max );
			}

			template<typename T> inline void operator()( ColorRGBA<T> & color, const T & max ) {
				color.r = Math::min( color.r, max );
				color.g = Math::min( color.g, max );
				color.b = Math::min( color.b, max );
				color.a = Math::min( color.a, max );
			}
		};

		///@brief Clamp the value between [ 0 ; +INF ]
		///@see Graphic::KernelFunc::Template
		struct Max : public Template {
			template<typename T> inline void operator()( ColorR<T> & color, const T & max ) {
				color = Math::max( color, T( 0 ) );
			}

			template<typename T> inline void operator()( ColorRGB<T> & color, const T & max ) {
				color.r = Math::min( color.r, T( 0 ) );
				color.g = Math::min( color.g, T( 0 ) );
				color.b = Math::min( color.b, T( 0 ) );
			}

			template<typename T> inline void operator()( ColorRGBA<T> & color, const T & max ) {
				color.r = Math::min( color.r, T( 0 ) );
				color.g = Math::min( color.g, T( 0 ) );
				color.b = Math::min( color.b, T( 0 ) );
				color.a = Math::min( color.a, T( 0 ) );
			}
		};

		///@brief Clamp the value between [ 0 ; max ]
		///@see Graphic::KernelFunc::Template
		struct Clamp : public Template {
			template<typename T> inline void operator()( ColorR<T> & color, const T & max ) {
				color = Math::clamp( color, T( 0 ), max );
			}

			template<typename T> inline void operator()( ColorRGB<T> & color, const T & max ) {
				color.r = Math::clamp( color.r, T( 0 ), max );
				color.g = Math::clamp( color.g, T( 0 ), max );
				color.b = Math::clamp( color.b, T( 0 ), max );
			}

			template<typename T> inline void operator()( ColorRGBA<T> & color, const T & max ) {
				color.r = Math::clamp( color.r, T( 0 ), max );
				color.g = Math::clamp( color.g, T( 0 ), max );
				color.b = Math::clamp( color.b, T( 0 ), max );
				color.a = Math::clamp( color.a, T( 0 ), max );
			}
		};

		///@brief get the absolute value
		///@see Graphic::KernelFunc::Template
		struct Abs : public Template {
			template<typename T> inline void operator()( ColorR<T> & color, const T & max ) {
				color = Math::abs( color );
			}

			template<typename T> inline void operator()( ColorRGB<T> & color, const T & max ) {
				color.r = Math::min( color.r );
				color.g = Math::min( color.g );
				color.b = Math::min( color.b );
			}

			template<typename T> inline void operator()( ColorRGBA<T> & color, const T & max ) {
				color.r = Math::min( color.r );
				color.g = Math::min( color.g );
				color.b = Math::min( color.b );
				color.a = Math::min( color.a );
			}
		};

		///@brief get the absolute value and clamp it between [ 0 ; max ]
		///@see Graphic::KernelFunc::Template
		struct AbsClamp : public Template {
			template<typename T> inline void operator()( ColorR<T> & color, const T & max ) {
				color = Math::min( Math::abs( color ), max );
			}

			template<typename T> inline void operator()( ColorRGB<T> & color, const T & max ) {
				color.r = Math::min( Math::abs( color.r ), max );
				color.g = Math::min( Math::abs( color.g ), max );
				color.b = Math::min( Math::abs( color.b ), max );
			}

			template<typename T> inline void operator()( ColorRGBA<T> & color, const T & max ) {
				color.r = Math::min( Math::abs( color.r ), max );
				color.g = Math::min( Math::abs( color.g ), max );
				color.b = Math::min( Math::abs( color.b ), max );
				color.a = Math::min( Math::abs( color.a ), max );
			}
		};


	}



}




