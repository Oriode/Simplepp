///@file Color.h
///@brief Colors objects to be used in all the graphic purpose
///@author Cl�ment Gerber
///@date 21/09/2016 (DMY) 
#pragma once


#include "../Utility.h"
#include "../Math.h"
#include "ColorR.h"


namespace Graphic {


	///@brief Class representing a color of 3 component of type T
	template<typename T>
	class ColorRGB : public Math::Vec3<T>, public Color<T> {
	public:
		///@brief Type used to sum multiple pixels components
		typedef typename ColorRGB<typename Color<T>::SumType> ColorSum;

		///@brief Type used to sum multiple pixels components multiplied with a negative value
		typedef typename ColorRGB<typename Color<T>::KernelType> ColorKernel;

		///@brief Floating point type
		typedef typename ColorRGB<typename Color<T>::Float> ColorFloat;


		explicit ColorRGB( void );

		explicit ColorRGB( const unsigned char & l );
		explicit ColorRGB( const unsigned short & l );
		explicit ColorRGB( const unsigned int & l );
		explicit ColorRGB( const unsigned long & l );
		explicit ColorRGB( const unsigned long long & l );

		explicit ColorRGB( const char & l );
		explicit ColorRGB( const short & l );
		explicit ColorRGB( const int & l );
		explicit ColorRGB( const long & l );
		explicit ColorRGB( const long long & l );

		explicit ColorRGB( const float & l );
		explicit ColorRGB( const double & l );


		template<typename U>
		explicit ColorRGB( const U & r, const U & g, const U & b );
		template<typename U>
		explicit ColorRGB( const ColorR<U> & v );
		template<typename U>
		explicit ColorRGB( const Math::Vec3<U> & v );
		template<typename U>
		explicit ColorRGB( const ColorRGB<U> & v );

		template<typename U>
		explicit operator ColorR<U>() const;

		template<typename C = char>
		operator BasicString<C>() const;

		template<typename U>
		ColorRGB<T> & operator=( const ColorR<U> & );

		template<typename U>
		ColorRGB<T> & operator=( const ColorRGB<U> & );

		template<typename U>
		ColorRGB<T> & operator=( const Math::Vec3<U> & );


		///@brief get the lightness of this color (this function is not a direct access, it will compute the lightness from the 3 color)
		///@return Lightness between [getMin() ; getMax()]
		T getLightness() const;

		///@brief get the Red component of this color 
		///@return Red component between [getMin() ; getMax()]
		const T & getRed() const;

		///@brief get the Green component of this color 
		///@return Green component between [getMin() ; getMax()]
		const T & getGreen() const;

		///@brief get the Blue component of this color 
		///@return Blue component between [getMin() ; getMax()]
		const T & getBlue() const;


		///@brief Convert this RGB (Red Green Blue) Color into a HSL (Hue Saturation Lightness) one
		///		H : Hue (Value between [ getMin() ; getMax() ] )
		///		S : Saturation (Value between [ getMin() ; getMax() ] )
		///		L : Lightness (Value between [ getMin() ; getMax() ] )
		///@return HSL color
		ColorRGB<T> RGBtoHSL() const;

		
		///@brief Convert this HSL (Hue Saturation Lightness) Color into a RGB (Red Green Blue) one
		///		R : Red (Value between [ getMin() ; getMax() ] )
		///		G : Green (Value between [ getMin() ; getMax() ] )
		///		B : Blue (Value between [ getMin() ; getMax() ] )
		///@return RGB color
		ColorRGB<T> HSLtoRGB() const;


		///@brief convert this color into an human readable string
		///@see toHex();
		///@return String of type C
		template<typename C = char>
		BasicString<C> toString() const;


		///@brief convert this color into Hexadecimal view
		///@return String of type C
		template<typename C = char>
		BasicString<C> toHex() const;


		///@brief Convert this color into an another type (values are normalized to the new type)
		///@template U Type to convert to
		///@return ColorRGB<U> Color of a new type
		template<typename U>
		ColorRGB<U> toType() const;


		static const ColorRGB<T> black;
		static const ColorRGB<T> white;
		static const ColorRGB<T> red;
		static const ColorRGB<T> green;
		static const ColorRGB<T> blue;

	private:
		template<typename U>
		void _castFromR( const U & l );

	};



}


#include "ColorRGB.hpp"
