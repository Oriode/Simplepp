///@file BlendingFunc.hpp
///@brief File containing all the Color Blending Functors
///@author Clement Gerber
///@date 30/09/2016 (DMY) 
#pragma once

#include "../BuildConfig.h"
#include "BasicGraphic.h"

namespace Graphic {




	namespace BlendingFunc {

		class Template {
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const {};

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const {};

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const {};
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const {};

			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const {};
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const {};
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const {};

			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const {};
			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const {};
			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const {};

			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const {};
			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const {};
			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const {};
		};



		///@brief Standard Blending Functor
		/// Some Examples of Blending : 
		///			[ colorDst ]	[ colorSrc ]	[ alpha ]	-> [ colorDst ] 
		///			[ 0 ]			[ 1 1 1 ]					-> [ 0.5 ]
		///			[ 0 0 0 ]		[ 0 1 0 0.5]				-> [ 0 0.5 0 ]
		///			[ 0 0 0 1 ]		[ 1 0 0 1 ]					-> [ 1 0 0 1 ]
		///			[ 0 0 0 1 ]		[ 1 0 0 1 ]	[ 0.5 ]			-> [ 0.5 0 0 1 ]
		class Normal : public Template {
		public:
			//WITHOUT MASK
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }

			//WITH MASK
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }

			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }

			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }


			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = Color<I>::getMax();
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				colorDest.r = colorSrc.getLightness();
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			/************************************************************************/
			/* RGB -> RGBA                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = Color<I>::getMax();
			}

			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == I( Color<I>::getMin() ) ) {
					return;
				} else if ( colorSrc.a == I( Color<I>::getMax() ) ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha = Color<I>::getMax() - Bigger( colorSrc.a );
				colorDest.r = I( ( colorDest.r * oneMinusAlpha + Bigger( colorSrc.getLightness() ) * colorSrc.a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F alpha( F( colorSrc.a ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( ( colorDest.r * oneMinusAlpha + F( colorSrc.getLightness() ) * alpha ) );
				#endif
			}

			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<F>::getMin() ) {
					return;
				} else if ( colorSrc.a == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a );
				colorDest.r = colorDest.r * oneMinusAlpha + F( colorSrc.getLightness() ) * colorSrc.a;
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<F>::getMin() ) {
					return;
				} else if ( colorSrc.a == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a );
				colorDest.r = colorDest.r * oneMinusAlpha + F( colorSrc.getLightness() ) * colorSrc.a;
			}


			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == I( Color<I>::getMin() ) ) {
					return;
				} else if ( colorSrc.a == I( Color<I>::getMax() ) ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger alpha = Bigger( colorSrc.a );
				Bigger oneMinusAlpha = Color<I>::getMax() - alpha;

				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * alpha ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + Bigger( colorSrc.g ) * alpha ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + Bigger( colorSrc.b ) * alpha ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F alpha( F( colorSrc.a ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha ) );
				colorDest.g = I( ( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha ) );
				colorDest.b = I( ( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha ) );
				#endif
			}

			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<F>::getMin()  ) {
					return;
				} else if ( colorSrc.a == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a);
				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<F>::getMin() ) {
					return;
				} else if ( colorSrc.a == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a );
				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<I>::getMin() ) {
					return;
				} else if ( colorSrc.a == Color<I>::getMax() || colorDest.a == Color<I>::getMin() ) {
					colorDest = colorSrc;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( colorSrc.a );
				Biggest oneMinusAlpha( Biggest(Color<I>::getMax()) - alphaSrc );

				if ( colorDest.a == Color<I>::getMax() ) {
					colorDest.r = I( ( Biggest( colorDest.r ) * oneMinusAlpha + Biggest( colorSrc.r ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
					colorDest.g = I( ( Biggest( colorDest.g ) * oneMinusAlpha + Biggest( colorSrc.g ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
					colorDest.b = I( ( Biggest( colorDest.b ) * oneMinusAlpha + Biggest( colorSrc.b ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
			   } else {
					Biggest alphaDst( colorDest.a );
					Biggest alphaOut( alphaSrc + ( ( alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) );
					Biggest divider( alphaOut );

					colorDest.a = I( alphaOut );
					colorDest.r = I( ( ( ( ( Biggest( colorDest.r ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + ( Biggest( colorSrc.r ) * alphaSrc ) ) ) / divider );
					colorDest.g = I( ( ( ( ( Biggest( colorDest.g ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + ( Biggest( colorSrc.g ) * alphaSrc ) ) ) / divider );
					colorDest.b = I( ( ( ( ( Biggest( colorDest.b ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + ( Biggest( colorSrc.b ) * alphaSrc ) ) ) / divider );
				}
				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( colorSrc.a ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<I>::getMax() ) {
					colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) );
					colorDest.g = I( ( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alphaSrc ) );
					colorDest.b = I( ( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alphaSrc ) );
				} else {
					F alphaDst( F( colorDest.a ) / F( Color<I>::getMax() ) );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = I( alphaOut * F( Color<I>::getMax() ) );
					colorDest.r = I( ( F( colorDest.r ) * alphaDst * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = I( ( F( colorDest.g ) * alphaDst * oneMinusAlpha + F( colorSrc.g ) * alphaSrc ) / alphaOut );
					colorDest.b = I( ( F( colorDest.b ) * alphaDst * oneMinusAlpha + F( colorSrc.b ) * alphaSrc ) / alphaOut );
				}
				#endif
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<F>::getMin() ) {
					return;
				} else if ( colorSrc.a == Color<F>::getMax() || colorDest.a == Color<F>::getMin() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( colorSrc.a );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
					colorDest.g = ( ( colorDest.g ) * oneMinusAlpha + ( colorSrc.g ) * alphaSrc );
					colorDest.b = ( ( colorDest.b ) * oneMinusAlpha + ( colorSrc.b ) * alphaSrc );
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = ( ( colorDest.r ) * alphaDst * oneMinusAlpha + ( colorSrc.r ) * alphaSrc ) / alphaOut ;
					colorDest.g = ( ( colorDest.g ) * alphaDst * oneMinusAlpha + ( colorSrc.g ) * alphaSrc ) / alphaOut ;
					colorDest.b = ( ( colorDest.b ) * alphaDst * oneMinusAlpha + ( colorSrc.b ) * alphaSrc ) / alphaOut ;
				}
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == Color<F>::getMin() ) {
					return;
				} else if ( colorSrc.a == Color<F>::getMax() || colorDest.a == Color<F>::getMin() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( colorSrc.a );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
					colorDest.g = ( ( colorDest.g ) * oneMinusAlpha + ( colorSrc.g ) * alphaSrc );
					colorDest.b = ( ( colorDest.b ) * oneMinusAlpha + ( colorSrc.b ) * alphaSrc );
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = ( ( colorDest.r ) * alphaDst * oneMinusAlpha + ( colorSrc.r ) * alphaSrc ) / alphaOut;
					colorDest.g = ( ( colorDest.g ) * alphaDst * oneMinusAlpha + ( colorSrc.g ) * alphaSrc ) / alphaOut;
					colorDest.b = ( ( colorDest.b ) * alphaDst * oneMinusAlpha + ( colorSrc.b ) * alphaSrc ) / alphaOut;
				}
			}


			/************************************************************************/
			/* WITH MASK                                                            */
			/************************************************************************/
			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( alpha );
				Biggest oneMinusAlpha( Biggest( Color<I>::getMax() ) - alphaSrc );

				colorDest.r = I( ( Biggest( colorDest.r ) * oneMinusAlpha + Biggest( colorSrc.r ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
				
				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) );
				
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc );				
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( alpha );
				Biggest oneMinusAlpha( Biggest( Color<I>::getMax() ) - alphaSrc );

				colorDest.r = I( ( Biggest( colorDest.r ) * oneMinusAlpha + Biggest( colorSrc.getLightness() ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;

				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.getLightness() ) * alphaSrc ) );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;

				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.getLightness() ) * alphaSrc );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.getLightness() ) * alphaSrc );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() || colorDest.a == Color<I>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
					colorDest.a = alpha;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( alpha );
				Biggest oneMinusAlpha( Biggest( Color<I>::getMax() ) - alphaSrc );

				if ( colorDest.a == Color<I>::getMax() ) {
					colorDest.r = I( ( Biggest( colorDest.r ) * oneMinusAlpha + Biggest( colorSrc.r ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
					colorDest.g = colorDest.r;
					colorDest.b = colorDest.r;
				} else {
					Biggest alphaDst( colorDest.a );
					Biggest alphaOut( alphaSrc + ( ( alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) );
					Biggest divider( alphaOut );

					colorDest.a = I( alphaOut );
					colorDest.r = I( ( ( ( ( Biggest( colorDest.r ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + Biggest( colorSrc.r ) * alphaSrc ) ) / divider );
					colorDest.g = colorDest.r;
					colorDest.b = colorDest.r;
				}
				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<I>::getMax() ) {
					colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) );
					colorDest.g = colorDest.r;
					colorDest.b = colorDest.r;
				} else {
					F alphaDst( F( colorDest.a ) / F( Color<I>::getMax() ) );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = I( alphaOut * F( Color<I>::getMax() ) );
					colorDest.r = I( ( F( colorDest.r ) * alphaDst * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = colorDest.r;
					colorDest.b = colorDest.r;
				}
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() || colorDest.a == Color<I>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
					colorDest.a = I( alpha * F( Color<I>::getMax() ) );
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc );
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = I( ( F( colorDest.r ) * alphaDst * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
				}
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() || colorDest.a == Color<F>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
					colorDest.a = alpha;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = ( ( colorDest.r ) * alphaDst * oneMinusAlpha + ( colorSrc.r ) * alphaSrc ) / alphaOut;
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
				}
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() || colorDest.a == Color<F>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
					colorDest.a = alpha;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = ( ( colorDest.r ) * alphaDst * oneMinusAlpha + ( colorSrc.r ) * alphaSrc ) / alphaOut;
					colorDest.g = colorSrc.r;
					colorDest.b = colorSrc.r;
				}
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger oneMinusAlpha( Color<I>::getMax() - Bigger( alpha ) );
				colorDest.r = I( ( colorDest.r * oneMinusAlpha + Bigger( colorSrc.getLightness() ) * alpha ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( ( colorDest.r * oneMinusAlpha + F( colorSrc.getLightness() ) * a ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.getLightness() ) * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.getLightness() ) * alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.getLightness() ) * alpha );
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger( alpha );
				Bigger oneMinusAlpha = Color<I>::getMax() - a;

				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + Bigger( colorSrc.g ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + Bigger( colorSrc.b ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * a ) );
				colorDest.g = I( ( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * a ) );
				colorDest.b = I( ( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * a ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alpha );
				colorDest.g = ( ( colorDest.g ) * oneMinusAlpha + ( colorSrc.g ) * alpha );
				colorDest.b = ( ( colorDest.b ) * oneMinusAlpha + ( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alpha );
				colorDest.g = ( ( colorDest.g ) * oneMinusAlpha + ( colorSrc.g ) * alpha );
				colorDest.b = ( ( colorDest.b ) * oneMinusAlpha + ( colorSrc.b ) * alpha );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                          */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() || colorDest.a == Color<I>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					colorDest.a = alpha;

					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( alpha );
				Biggest oneMinusAlpha( Biggest( Color<I>::getMax() ) - alphaSrc );

				if ( colorDest.a == Color<I>::getMax() ) {
					colorDest.r = I( ( Biggest( colorDest.r ) * oneMinusAlpha + Biggest( colorSrc.r ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
					colorDest.g = I( ( Biggest( colorDest.g ) * oneMinusAlpha + Biggest( colorSrc.g ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
					colorDest.b = I( ( Biggest( colorDest.b ) * oneMinusAlpha + Biggest( colorSrc.b ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
			} else {
					Biggest alphaDst( colorDest.a );
					Biggest alphaOut( alphaSrc + ( ( alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) );
					Biggest divider( alphaOut );

					colorDest.a = I( alphaOut );
					colorDest.r = I( ( ( ( ( Biggest( colorDest.r ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + Biggest( colorSrc.r ) * alphaSrc ) ) / divider );
					colorDest.g = I( ( ( ( ( Biggest( colorDest.g ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + Biggest( colorSrc.g ) * alphaSrc ) ) / divider );
					colorDest.b = I( ( ( ( ( Biggest( colorDest.b ) * alphaDst * oneMinusAlpha ) >> Color<I>::getMaxNbBits() ) + Biggest( colorSrc.b ) * alphaSrc ) ) / divider );
				}
				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<I>::getMax() ) {
					colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) );
					colorDest.g = I( ( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alphaSrc ) );
					colorDest.b = I( ( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alphaSrc ) );
				} else {
					F alphaDst( F( colorDest.a ) / F( Color<I>::getMax() ) );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = I( alphaOut * F( Color<I>::getMax() ) );
					colorDest.r = I( ( F( colorDest.r ) * alphaDst * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = I( ( F( colorDest.g ) * alphaDst * oneMinusAlpha + F( colorSrc.g ) * alphaSrc ) / alphaOut );
					colorDest.b = I( ( F( colorDest.b ) * alphaDst * oneMinusAlpha + F( colorSrc.b ) * alphaSrc ) / alphaOut );
				}
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() || colorDest.a == Color<I>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					colorDest.a = alpha * F( Color<I>::getMax() );
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alphaSrc );
					colorDest.g = ( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alphaSrc );
					colorDest.b = ( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alphaSrc );
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = I( ( F( colorDest.r ) * alphaDst * oneMinusAlpha + F( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = I( ( F( colorDest.g ) * alphaDst * oneMinusAlpha + F( colorSrc.g ) * alphaSrc ) / alphaOut );
					colorDest.b = I( ( F( colorDest.b ) * alphaDst * oneMinusAlpha + F( colorSrc.b ) * alphaSrc ) / alphaOut );
				}
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() || colorDest.a == Color<F>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					colorDest.a = alpha;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
					colorDest.g = ( ( colorDest.g ) * oneMinusAlpha + ( colorSrc.g ) * alphaSrc );
					colorDest.b = ( ( colorDest.b ) * oneMinusAlpha + ( colorSrc.b ) * alphaSrc );
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = ( ( ( colorDest.r ) * alphaDst * oneMinusAlpha + ( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = ( ( ( colorDest.g ) * alphaDst * oneMinusAlpha + ( colorSrc.g ) * alphaSrc ) / alphaOut );
					colorDest.b = ( ( ( colorDest.b ) * alphaDst * oneMinusAlpha + ( colorSrc.b ) * alphaSrc ) / alphaOut );
				}
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() || colorDest.a == Color<F>::getMin() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					colorDest.a = alpha;
					return;
				}
				#endif

				F alphaSrc( alpha );
				F oneMinusAlpha( F( 1.0 ) - alphaSrc );

				if ( colorDest.a == Color<F>::getMax() ) {
					colorDest.r = ( ( colorDest.r ) * oneMinusAlpha + ( colorSrc.r ) * alphaSrc );
					colorDest.g = ( ( colorDest.g ) * oneMinusAlpha + ( colorSrc.g ) * alphaSrc );
					colorDest.b = ( ( colorDest.b ) * oneMinusAlpha + ( colorSrc.b ) * alphaSrc );
				} else {
					F alphaDst( colorDest.a );
					F alphaOut( alphaSrc + alphaDst * oneMinusAlpha );

					colorDest.a = alphaOut;
					colorDest.r = ( ( ( colorDest.r ) * alphaDst * oneMinusAlpha + ( colorSrc.r ) * alphaSrc ) / alphaOut );
					colorDest.g = ( ( ( colorDest.g ) * alphaDst * oneMinusAlpha + ( colorSrc.g ) * alphaSrc ) / alphaOut );
					colorDest.b = ( ( ( colorDest.b ) * alphaDst * oneMinusAlpha + ( colorSrc.b ) * alphaSrc ) / alphaOut );
				}
			}

			/************************************************************************/
			/* RGBA -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				ColorRGBA<I> c( colorSrc.r, colorSrc.g, colorSrc.b, I( Bigger( colorSrc.a ) * Bigger( alpha ) / Bigger( Color<I>::getMax() ) ) );
				blendColor( colorDest, c );
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				ColorRGBA<I> c( colorSrc.r, colorSrc.g, colorSrc.b, I( F( colorSrc.a ) * alpha ) );
				blendColor( colorDest, c );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				ColorRGBA<F> c( colorSrc.r, colorSrc.g, colorSrc.b, colorSrc.a * alpha );
				blendColor( colorDest, c );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				ColorRGBA<F> c( colorSrc.r, colorSrc.g, colorSrc.b, colorSrc.a * alpha );
				blendColor( colorDest, c );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				ColorRGBA<I> c( colorSrc.r, colorSrc.g, colorSrc.b, I( Bigger( colorSrc.a ) * Bigger( alpha ) / Bigger( Color<I>::getMax() ) ) );
				blendColor( colorDest, c );
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				ColorRGBA<I> c( colorSrc.r, colorSrc.g, colorSrc.b, I( F( colorSrc.a ) * alpha ) );
				blendColor( colorDest, c );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				ColorRGBA<F> c( colorSrc.r, colorSrc.g, colorSrc.b, colorSrc.a * alpha );
				blendColor( colorDest, c );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				ColorRGBA<F> c( colorSrc.r, colorSrc.g, colorSrc.b, colorSrc.a * alpha );
				blendColor( colorDest, c );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				ColorRGBA<I> c( colorSrc.r, colorSrc.g, colorSrc.b, I( Bigger( colorSrc.a ) * Bigger( alpha ) / Bigger( Color<I>::getMax() ) ) );
				blendColor( colorDest, c );
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				ColorRGBA<I> c( colorSrc.r, colorSrc.g, colorSrc.b, I( F( colorSrc.a ) * alpha ) );
				blendColor( colorDest, c );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				ColorRGBA<F> c( colorSrc.r, colorSrc.g, colorSrc.b, colorSrc.a * alpha );
				blendColor( colorDest, c );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				ColorRGBA<F> c( colorSrc.r, colorSrc.g, colorSrc.b, colorSrc.a * alpha );
				blendColor( colorDest, c );
			}

		};













		///@brief Same as the Normal Blending but without taking care of the colorDst, the colorSrc is applied without blending
		/// Some Examples of Blending : 
		///			[ colorDst ]	[ colorSrc ]	[ alpha ]	-> [ colorDst ] 
		///			[ 0 ]			[ 1 1 1 ]					-> [ 0.5 ]
		///			[ 0 0 0 ]		[ 0 1 0 0.5	]				-> [ 0 0.5 0 ]
		///			[ 0 0 0 1 ]		[ 1 0 0 1 ]					-> [ 1 0 0 1 ]
		///			[ 0 0 0 1 ]		[ 1 0 0 1 ]	[ 0.5 ]			-> [ 0.5 0 0 1 ]
		class None : public Template {
		public:
			//WITHOUT MASK
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }

			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }

			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }
			template<typename T> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc ) const { blendColor( colorDest, colorSrc ); }

			//WITH MASK
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorR<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }

			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGB<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }

			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorR<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorRGB<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }
			template<typename T, typename A> void operator()( ColorRGBA<T> & colorDest, const ColorRGBA<T> & colorSrc, A alpha ) const { blendColor( colorDest, colorSrc, alpha ); }

			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc ) {
				Normal::blendColor( colorDest, colorSrc );
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc ) {
				Normal::blendColor( colorDest, colorSrc );
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc ) {
				Normal::blendColor( colorDest, colorSrc );
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				Normal::blendColor( colorDest, colorSrc );
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				Normal::blendColor( colorDest, colorSrc );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				Normal::blendColor( colorDest, colorSrc );
			}
			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				colorDest.r = colorSrc.getLightness();
			}
			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = colorSrc.a;
			}

			/************************************************************************/
			/* WITH MASK                                                            */
			/************************************************************************/
			/************************************************************************/
			/* R -> R                                                               */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( alpha );
				colorDest.r = I( ( Biggest( colorSrc.r ) * alphaSrc ) >> Color<I>::getMaxNbBits() );

				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( alpha ) / F( Color<I>::getMax() ) );

				colorDest.r = I( F( colorSrc.r ) * alphaSrc );

				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha / F( Color<I>::getMax() ) );
				colorDest.r = ( F( colorSrc.r ) * alphaSrc );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				colorDest.r = ( F( colorSrc.r ) * alphaSrc );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				colorDest.r = ( F( colorSrc.r ) * alphaSrc );
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;

				Biggest alphaSrc( alpha );

				colorDest.r = I( ( Biggest( colorSrc.getLightness() ) * alphaSrc ) >> Color<I>::getMaxNbBits() );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;

				#else
				typedef typename Color<I>::Float F;
				F alphaSrc( F( alpha ) / F( Color<I>::getMax() ) );

				colorDest.r = I( F( colorSrc.r ) * alphaSrc );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;

				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );

				colorDest.r = I( F( colorSrc.r ) * alphaSrc );
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				colorDest.r = F( colorSrc.r ) * alphaSrc;
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest = colorSrc;
					return;
				}
				#endif

				F alphaSrc( alpha );
				colorDest.r = F( colorSrc.r ) * alphaSrc;
				colorDest.g = colorDest.r;
				colorDest.b = colorDest.r;
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = alpha;
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = I( alpha * F( Color<I>::getMax() ) );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = alpha;
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {	
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.r;
				colorDest.b = colorSrc.r;
				colorDest.a = alpha;
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				colorDest.r = I( ( Bigger( colorSrc.getLightness() ) * alpha ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Color<I>::getMax() ) );
				colorDest.r = I( F( colorSrc.getLightness() ) * a );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				colorDest.r = I( F( colorSrc.getLightness() ) * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				colorDest.r = ( colorSrc.getLightness() ) * alpha;
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.getLightness();
					return;
				}
				#endif
				colorDest.r = ( colorSrc.getLightness() ) * alpha;
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<I>::getMin() ) {
					return;
				} else if ( alpha == Color<I>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger( alpha );

				colorDest.r = I( ( Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorSrc.g ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorSrc.b ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( F( colorSrc.r ) * a );
				colorDest.g = I( F( colorSrc.g ) * a );
				colorDest.b = I( F( colorSrc.b ) * a );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				colorDest.r = I( F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				colorDest.r = ( ( colorSrc.r ) * alpha );
				colorDest.g = ( ( colorSrc.g ) * alpha );
				colorDest.b = ( ( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == Color<F>::getMin() ) {
					return;
				} else if ( alpha == Color<F>::getMax() ) {
					colorDest.r = colorSrc.r;
					colorDest.g = colorSrc.g;
					colorDest.b = colorSrc.b;
					return;
				}
				#endif
				colorDest.r = ( ( colorSrc.r ) * alpha );
				colorDest.g = ( ( colorSrc.g ) * alpha );
				colorDest.b = ( ( colorSrc.b ) * alpha );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                          */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = alpha;
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = alpha * F( Color<I>::getMax() );	
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = alpha;	
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = alpha;
			}

			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;
				colorDest.r = I( ( Biggest( alpha ) * Biggest( colorSrc.a ) * Biggest( colorSrc.getLightness() ) ) >> ( Color<I>::getMaxNbBits() * 2 ) );
				#else
				typedef typename Color<I>::Float F;
				colorDest.r = I( ( F( alpha ) * F( colorSrc.a ) * F( colorSrc.getLightness() ) ) / F( ColorR<T>::getMax() * ColorR<I>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				colorDest.r = I( ( F( alpha ) * F( colorSrc.a ) * F( colorSrc.getLightness() ) ) / F( ColorR<I>::getMax() ) );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				colorDest.r = F( alpha ) * F( colorSrc.a ) * F( colorSrc.getLightness() );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				colorDest.r = F( alpha ) * F( colorSrc.a ) * F( colorSrc.getLightness() );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger Biggest;
				Biggest a( Biggest( alpha ) * Biggest( colorSrc.a ) );
				colorDest.r = I( ( a * Biggest( colorSrc.r ) ) >> ( Color<I>::getMaxNbBits() * 2 ) );
				colorDest.g = I( ( a * Biggest( colorSrc.g ) ) >> ( Color<I>::getMaxNbBits() * 2 ) );
				colorDest.b = I( ( a * Biggest( colorSrc.b ) ) >> ( Color<I>::getMaxNbBits() * 2 ) );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) * F( colorSrc.a ) / F( ColorR<I>::getMax() * ColorR<I>::getMax() ) );
				colorDest.r = I( a * F( colorSrc.r ) );
				colorDest.g = I( a * F( colorSrc.g ) );
				colorDest.b = I( a * F( colorSrc.b ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F a( F( alpha ) * F( colorSrc.a ) / F( ColorR<I>::getMax() ) );
				colorDest.r = I( a * F( colorSrc.r ) );
				colorDest.g = I( a * F( colorSrc.g ) );
				colorDest.b = I( a * F( colorSrc.b ) );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				F a( F( alpha ) * F( colorSrc.a ) );
				colorDest.r = a * F( colorSrc.r );
				colorDest.g = a * F( colorSrc.g );
				colorDest.b = a * F( colorSrc.b );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				F a( F( alpha ) * F( colorSrc.a ) );
				colorDest.r = a * F( colorSrc.r );
				colorDest.g = a * F( colorSrc.g );
				colorDest.b = a * F( colorSrc.b );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = I( ( Bigger( alpha ) * Bigger( colorSrc.a ) ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = F( ( F( alpha ) * F( colorSrc.a ) ) / F( ColorR<T>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = I( F( alpha ) * F( colorSrc.a ) );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = F( alpha ) * F( colorSrc.a );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				colorDest.r = colorSrc.r;
				colorDest.g = colorSrc.g;
				colorDest.b = colorSrc.b;
				colorDest.a = F( alpha ) * F( colorSrc.a );
			}

		};



	

	}
}
