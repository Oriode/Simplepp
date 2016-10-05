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
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				colorDest.r = I( ( Bigger( colorSrc.r ) + Bigger( colorSrc.g ) + Bigger( colorSrc.b ) ) / Bigger( 3 ) );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc ) {
				colorDest.r = ( colorSrc.r + colorSrc.g + colorSrc.b ) / float( 3 );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc ) {
				colorDest.r = ( colorSrc.r + colorSrc.g + colorSrc.b ) / double( 3 );
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
				if ( colorSrc.a == I( 0 ) ) {
					return;
				} else if ( colorSrc.a == I( Color<I>::getMax() ) ) {
					typedef Utility::TypesInfos<I>::Bigger Bigger;
					Bigger sum = Bigger( colorSrc.r ) + Bigger( colorSrc.g ) + Bigger( colorSrc.b );
					colorDest.r = I( sum / Bigger( 3 ) );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = Color<I>::getMax() - Bigger( colorSrc.a );
				Bigger sum = Bigger( colorSrc.r ) + Bigger( colorSrc.g ) + Bigger( colorSrc.b );

				colorDest.r = I( ( colorDest.r * oneMinusAlpha + ( sum / Bigger( 3 ) ) * colorSrc.a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;

				F alpha( F( colorSrc.a ) / F(Color<I>::getMax()) );
				F oneMinusAlpha( F( 1.0 ) - alpha );

				F sum( F( colorSrc.r ) + F( colorSrc.g ) + F( colorSrc.b ) );
				colorDest.r = I( ( colorDest.r * oneMinusAlpha + ( sum / F( 3.0 ) ) * alpha ) );
				#endif
			}

			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				F oneMinusAlpha(F( 1.0 ) - colorSrc.a);
				F sum( colorSrc.r + colorSrc.g + colorSrc.b );

				colorDest.r = colorDest.r * oneMinusAlpha + ( sum / F( 3.0 ) ) * colorSrc.a;
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a );
				F sum( colorSrc.r + colorSrc.g + colorSrc.b );

				colorDest.r = colorDest.r * oneMinusAlpha + ( sum / F( 3.0 ) ) * colorSrc.a;
			}


			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == I( 0 ) ) {
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
				F oneMinusAlpha( F( 1.0f ) - alpha );
				colorDest.r = I( ( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha ) );
				colorDest.g = I( ( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha ) );
				colorDest.b = I( ( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha ) );
				#endif
			}

			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a);
				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
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
				if ( colorSrc.a == I( 0 ) ) {
					return;
				} else if ( colorSrc.a == I( Color<I>::getMax() ) ) {
					colorDest = colorSrc;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha( Color<I>::getMax() - Bigger( colorSrc.a ) );

				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * Bigger( colorSrc.a ) ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + Bigger( colorSrc.g ) * Bigger( colorSrc.a ) ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + Bigger( colorSrc.b ) * Bigger( colorSrc.a ) ) >> Color<I>::getMaxNbBits() );
				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha ) >> Color<I>::getMaxNbBits() + Bigger( colorSrc.a ) );
				#else
				typedef typename Color<I>::Float F;
				F alpha( F( colorSrc.a ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( ( float( colorDest.r ) * oneMinusAlpha + float( colorSrc.r ) * alpha ) );
				colorDest.g = I( ( float( colorDest.g ) * oneMinusAlpha + float( colorSrc.g ) * alpha ) );
				colorDest.b = I( ( float( colorDest.b ) * oneMinusAlpha + float( colorSrc.b ) * alpha ) );
				colorDest.a = I( ( float( colorDest.a ) * oneMinusAlpha + colorSrc.a ) );
				#endif
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				F oneMinusAlpha = F( 1.0 ) - colorSrc.a;
				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * colorSrc.a;
				colorDest.g = colorDest.g * oneMinusAlpha + colorSrc.g * colorSrc.a;
				colorDest.b = colorDest.b * oneMinusAlpha + colorSrc.b * colorSrc.a;
				colorDest.a = colorDest.a * oneMinusAlpha + colorSrc.a;

			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
				F oneMinusAlpha = F( 1.0 ) - colorSrc.a;
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
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Utility::TypesInfos<A>::getMax() ) );
				#endif	
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * alpha;
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r * alpha;
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );
				Bigger tmp( Bigger( colorSrc.r ) * a );

				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + tmp ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + tmp ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + tmp ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Utility::TypesInfos<A>::getMax() ) );
				#endif		
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F tmp( ( colorSrc.r ) * alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + tmp );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + tmp );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + tmp );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F tmp( ( colorSrc.r ) * alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F tmp( ( colorSrc.r ) * alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif 
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a = Bigger( alpha );
				Bigger oneMinusAlpha = Color<I>::getMax() - a;
				Bigger tmp = Bigger( colorSrc.r ) * a;

				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + tmp ) << Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + tmp ) << Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + tmp ) << Color<I>::getMaxNbBits() );
				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha ) << Color<I>::getMaxNbBits() + alpha );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Utility::TypesInfos<A>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				F tmp( F( colorSrc ) * a );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + tmp );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + tmp );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + tmp );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha + alpha );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F tmp( F( colorSrc.r ) * alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + tmp );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + tmp );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + tmp );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha + alpha * Color<I>::getMax() );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F tmp( ( colorSrc.r ) * alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
				colorDest.a = ( colorDest.a * oneMinusAlpha + alpha );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F tmp( ( colorSrc.r ) * alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + tmp );
				colorDest.g = ( colorDest.g * oneMinusAlpha + tmp );
				colorDest.b = ( colorDest.b * oneMinusAlpha + tmp );
				colorDest.a = ( colorDest.a * oneMinusAlpha + alpha );
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a( alpha );
				Bigger oneMinusAlpha (Color<I>::getMax() - a);
				Bigger sum( ( Bigger( colorSrc.r ) + Bigger( colorSrc.g ) + Bigger( colorSrc.b ) ) / Bigger( 3 ) );
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + sum * a ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Utility::TypesInfos<A>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( F( colorSrc.r ) + F( colorSrc.g ) + F( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( ( colorSrc.r ) + ( colorSrc.g ) + ( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = ( colorDest.r * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( ( colorSrc.r ) + ( colorSrc.g ) + ( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = ( colorDest.r * oneMinusAlpha + sum * alpha );
			}
			/************************************************************************/
			/* RGB -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + Bigger( colorSrc.g ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + Bigger( colorSrc.b ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Utility::TypesInfos<A>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
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
				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha ) >> Color<I>::getMaxNbBits() + alpha );
				#else
				typedef float F;
				F a( F( alpha ) / F( Utility::TypesInfos<A>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * a );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * a );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * a );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha ) + alpha;
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha ) + alpha * Color<I>::getMax();
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}

			/************************************************************************/
			/* RGBA -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;

				SuperBigger a( SuperBigger( alpha ) * SuperBigger( colorSrc.a ) );
				SuperBigger oneMinusAlpha( Utility::TypesInfos<Bigger>::getMax() - a );
				SuperBigger sum( ( SuperBigger( colorSrc.r ) + SuperBigger( colorSrc.g ) + SuperBigger( colorSrc.b ) ) / SuperBigger( 3 ) );
				colorDest.r = I( ( SuperBigger( colorDest.r ) * oneMinusAlpha + sum * a ) >> Utility::TypesInfos<Bigger>::getNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) * F( colorSrc.a ) / F( Color<I>::getMax() ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				F sum( ( F( colorSrc.r ) + F( colorSrc.g ) + F( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + sum * a );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				alpha *= F( colorSrc.a ) / F( Color<I>::getMax() );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( F( colorSrc.r ) + F( colorSrc.g ) + F( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( ( colorSrc.r ) + ( colorSrc.g ) + ( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = ( colorDest.r * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( ( colorSrc.r ) + ( colorSrc.g ) + ( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = ( colorDest.r * oneMinusAlpha + sum * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				SuperBigger a = SuperBigger( alpha ) * SuperBigger( colorSrc.a );
				SuperBigger oneMinusAlpha = Utility::TypesInfos<Bigger>::getMax() - a;
				colorDest.r = I( ( SuperBigger( colorDest.r ) * oneMinusAlpha + SuperBigger( colorSrc.r ) * a ) >> Utility::TypesInfos<Bigger>::getNbBits() );
				colorDest.g = I( ( SuperBigger( colorDest.g ) * oneMinusAlpha + SuperBigger( colorSrc.g ) * a ) >> Utility::TypesInfos<Bigger>::getNbBits() );
				colorDest.b = I( ( SuperBigger( colorDest.b ) * oneMinusAlpha + SuperBigger( colorSrc.b ) * a ) >> Utility::TypesInfos<Bigger>::getNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) * F( colorSrc.a ) / F( Color<I>::getMax() ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * a );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * a );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * a );
				#endif		
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				alpha *= F( colorSrc.a ) / F( Color<I>::getMax() );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				Bigger a1( alpha );
				Bigger a2( colorSrc.a );

				Bigger oneMinusAlpha1( Color<I>::getMax() - a1 );
				Bigger oneMinusAlpha2( Color<I>::getMax() - a2 );

				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha2 + Bigger( colorSrc.r ) * a2 ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha2 + Bigger( colorSrc.g ) * a2 ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha2 + Bigger( colorSrc.b ) * a2 ) >> Color<I>::getMaxNbBits() );
				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha1 + Bigger( colorSrc.a ) * a1 ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Color<I>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F a( F( colorSrc.a ) / F(Color<I>::getMax()) );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F oneMinusA( F( 1.0 ) - a );

				colorDest.r = I( F( colorDest.r ) * oneMinusA + F( colorSrc.r ) * a );
				colorDest.g = I( F( colorDest.g ) * oneMinusA + F( colorSrc.g ) * a );
				colorDest.b = I( F( colorDest.b ) * oneMinusA + F( colorSrc.b ) * a );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha + F( colorSrc.a ) * alpha );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				F a( colorSrc.a );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F oneMinusA( F( 1.0 ) - a );

				colorDest.r = ( colorDest.r * oneMinusA + colorSrc.r * a );
				colorDest.g = ( colorDest.g * oneMinusA + colorSrc.g * a );
				colorDest.b = ( colorDest.b * oneMinusA + colorSrc.b * a );
				colorDest.a = ( colorDest.a * oneMinusAlpha + colorSrc.a * alpha );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				F a( colorSrc.a );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F oneMinusA( F( 1.0 ) - a );

				colorDest.r = ( colorDest.r * oneMinusA + colorSrc.r * a );
				colorDest.g = ( colorDest.g * oneMinusA + colorSrc.g * a );
				colorDest.b = ( colorDest.b * oneMinusA + colorSrc.b * a );
				colorDest.a = ( colorDest.a * oneMinusAlpha + colorSrc.a * alpha );
			}

		};











		class Erase : public Template {
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
				colorDest.a = colorSrc.r;
			}

			/************************************************************************/
			/* RGB -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc ) {
				colorDest.r = colorSrc.r;
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc ) {
				colorDest.r = colorSrc.r;
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
				colorDest.a = ImageT<I>::getComponentMinValue();
			}

			/************************************************************************/
			/* RGBA -> R                                                            */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( colorSrc.a == I( 0 ) ) {
					return;
				} else if ( colorSrc.a == I( Color<I>::getMax() ) ) {
					colorDest.r = colorSrc.r;
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger oneMinusAlpha = Color<I>::getMax() - Bigger( colorSrc.a );

				colorDest = I( ( colorDest * oneMinusAlpha + colorSrc.r * colorSrc.a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<T>::Float F;
				F alpha( F( colorSrc.a ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - alpha );

				colorDest.r = I( ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha ) );
				#endif
			}

			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a );

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r  * colorSrc.a;
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - colorSrc.a );
				F sum( colorSrc.r + colorSrc.g + colorSrc.b );

				colorDest.r = colorDest.r * oneMinusAlpha + colorSrc.r  * colorSrc.a;
			}


			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				return Normal::blendColor( colorDest, colorSrc );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				return Normal::blendColor( colorDest, colorSrc );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
				return Normal::blendColor( colorDest, colorSrc );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc ) {
				colorDest.a = colorSrc.a;
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc ) {
				colorDest.a = colorSrc.a;
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc ) {
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
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					colorDest.a = colorSrc.r;
					return;
				}
				#endif 
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );

				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) << Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Utility::TypesInfos<A>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha + a * F( colorSrc ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha + alpha * F( colorSrc.r ) );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = F( colorDest.a ) * oneMinusAlpha + alpha * F( colorSrc.r );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = F( colorDest.a ) * oneMinusAlpha + alpha * F( colorSrc.r );
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Utility::TypesInfos<A>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			/************************************************************************/
			/* RGB -> RGB                                                           */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_BRANCHING_BLENDING
				if ( alpha == A( 0 ) ) {
					return;
				} else if ( alpha == A( Utility::TypesInfos<A>::getMax() ) ) {
					blendColor( colorDest, colorSrc );
					return;
				}
				#endif
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;

				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );

				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha ) >> Color<I>::getMaxNbBits() );
				#else
				typedef typename Color<I>::Float F;
				F a( F( alpha ) / F( Utility::TypesInfos<A>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha );
			}

			/************************************************************************/
			/* RGBA -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;

				SuperBigger a( SuperBigger( alpha ) * SuperBigger( colorSrc.a ) );
				SuperBigger oneMinusAlpha( Utility::TypesInfos<Bigger>::getMax() - a );
				colorDest.r = I( ( SuperBigger( colorDest.r ) * oneMinusAlpha + SuperBigger( colorSrc.r ) * a ) >> Utility::TypesInfos<Bigger>::getNbBits() );
				#else
				typedef float F;
				F a( F( alpha ) * F( colorSrc.a ) / F( Color<I>::getMax() ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * a );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				alpha *= F( colorSrc.a ) / F( Color<I>::getMax() );
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + F( colorSrc.r ) * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                          */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				typedef Utility::TypesInfos<Bigger>::Bigger SuperBigger;
				SuperBigger a( SuperBigger( alpha ) * SuperBigger( colorSrc.a ) );
				SuperBigger oneMinusAlpha( Utility::TypesInfos<Bigger>::getMax() - a );
				colorDest.a = I( ( SuperBigger( colorDest.a ) * oneMinusAlpha ) >> Utility::TypesInfos<Bigger>::getNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Color<I>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				alpha *= F( colorSrc.a ) / Color<I>::getMax();
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				alpha *= colorSrc.a;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha ) + alpha;
			}

		};









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
			/* RGB -> R                                                               */
			/************************************************************************/
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc ) {
				colorDest.r = colorSrc.r;
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
				colorDest.r = colorSrc.r;
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
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* R -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* R -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorR<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorR<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorR<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}

			/************************************************************************/
			/* RGB -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* RGB -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			/************************************************************************/
			/* RGB -> RGBA                                                            */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, A alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGB<I> & colorSrc, typename Color<I>::Float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGB<float> & colorSrc, float alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGB<double> & colorSrc, double alpha ) {
				Normal::blendColor( colorDest, colorSrc, alpha );
			}

			/************************************************************************/
			/* RGBA -> R                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger a ( alpha );
				Bigger oneMinusAlpha (Color<I>::getMax() - a);
				Bigger sum(( Bigger( colorSrc.r ) + Bigger( colorSrc.g ) + Bigger( colorSrc.b ) ) / Bigger( 3 ));
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + sum * a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef float F;
				F a( F( alpha ) / F( Color<I>::getMax() ) );
				F oneMinusAlpha( F( 1.0 ) - a );
				F sum( ( F( colorSrc.r ) + F( colorSrc.g ) + F( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + sum * a );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorR<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( F( colorSrc.r ) + F( colorSrc.g ) + F( colorSrc.b ) ) / F( 3 ) );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor( ColorR<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( colorSrc.r + colorSrc.g + colorSrc.b ) / F( 3 ) );
				colorDest.r = ( colorDest.r * oneMinusAlpha + sum * alpha );
			}
			inline static void blendColor( ColorR<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				F sum( ( colorSrc.r + colorSrc.g + colorSrc.b ) / F( 3 ) );
				colorDest.r = ( colorDest.r * oneMinusAlpha + sum * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGB                                                             */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + Bigger( colorSrc.g ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + Bigger( colorSrc.b ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				typedef float F;
				F a( F( alpha ) / Color<I>::getMax() );
				F oneMinusAlpha( F( 1.0 ) - a );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * a );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * a );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * a );
				#endif		
			}
			template<typename I>
			inline static void blendColor( ColorRGB<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha );
			}
			inline static void blendColor( ColorRGB<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			inline static void blendColor( ColorRGB<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
			}
			/************************************************************************/
			/* RGBA -> RGBA                                                         */
			/************************************************************************/
			template<typename I, typename A>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, A alpha ) {
				#ifdef GRAPHIC_FAST_BLENDING
				typedef Utility::TypesInfos<I>::Bigger Bigger;
				Bigger a( alpha );
				Bigger oneMinusAlpha( Color<I>::getMax() - a );
				colorDest.r = I( ( Bigger( colorDest.r ) * oneMinusAlpha + Bigger( colorSrc.r ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.g = I( ( Bigger( colorDest.g ) * oneMinusAlpha + Bigger( colorSrc.g ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.b = I( ( Bigger( colorDest.b ) * oneMinusAlpha + Bigger( colorSrc.b ) * a ) >> Color<I>::getMaxNbBits() );
				colorDest.a = I( ( Bigger( colorDest.a ) * oneMinusAlpha + Bigger( colorSrc.a ) * a ) >> Color<I>::getMaxNbBits() );
				#else
				blendColor( colorDest, colorSrc, typename Color<I>::Float( alpha ) / typename Color<I>::Float( Color<I>::getMax() ) );
				#endif
			}
			template<typename I>
			inline static void blendColor( ColorRGBA<I> & colorDest, const ColorRGBA<I> & colorSrc, typename Color<I>::Float alpha ) {
				typedef typename Color<I>::Float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = I( F( colorDest.r ) * oneMinusAlpha + F( colorSrc.r ) * alpha );
				colorDest.g = I( F( colorDest.g ) * oneMinusAlpha + F( colorSrc.g ) * alpha );
				colorDest.b = I( F( colorDest.b ) * oneMinusAlpha + F( colorSrc.b ) * alpha );
				colorDest.a = I( F( colorDest.a ) * oneMinusAlpha + F( colorSrc.a ) * alpha );
			}
			inline static void blendColor( ColorRGBA<float> & colorDest, const ColorRGBA<float> & colorSrc, float alpha ) {
				typedef float F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha + colorSrc.a * alpha );
			}
			inline static void blendColor( ColorRGBA<double> & colorDest, const ColorRGBA<double> & colorSrc, double alpha ) {
				typedef double F;
				F oneMinusAlpha( F( 1.0 ) - alpha );
				colorDest.r = ( colorDest.r * oneMinusAlpha + colorSrc.r * alpha );
				colorDest.g = ( colorDest.g * oneMinusAlpha + colorSrc.g * alpha );
				colorDest.b = ( colorDest.b * oneMinusAlpha + colorSrc.b * alpha );
				colorDest.a = ( colorDest.a * oneMinusAlpha + colorSrc.a * alpha );
			}

		};







	}



}
