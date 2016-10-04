///@file Color.h
///@brief Colors objects to be used in all the graphic purpose
///@author Cl�ment Gerber
///@date 21/09/2016 (DMY) 
#pragma once


#include "../Utility.h"
#include "../Math.h"
#include "ColorR.h"
#include "ColorRGB.h"


namespace Graphic {


	///@brief Class representing a color of 4 components of type T
	template<typename T>
	class ColorRGBA : public Math::Vec4<T>, public Color<T> {
	public:
		explicit ColorRGBA( void );

		explicit ColorRGBA( const unsigned char & l );
		explicit ColorRGBA( const unsigned short & l );
		explicit ColorRGBA( const unsigned int & l );
		explicit ColorRGBA( const unsigned long & l );
		explicit ColorRGBA( const unsigned long long & l );

		explicit ColorRGBA( const char & l );
		explicit ColorRGBA( const short & l );
		explicit ColorRGBA( const int & l );
		explicit ColorRGBA( const long & l );
		explicit ColorRGBA( const long long & l );

		explicit ColorRGBA( const float & l );
		explicit ColorRGBA( const double & l );

		template<typename U>
		explicit ColorRGBA( const U & r, const U & g, const U & b );
		template<typename U>
		explicit ColorRGBA( const U & r, const U & g, const U & b, const U & a );
		template<typename U>
		explicit ColorRGBA( const ColorR<U> & v );
		template<typename U>
		explicit ColorRGBA( const Math::Vec3<U> & v );
		template<typename U>
		explicit ColorRGBA( const ColorRGB<U> & v );
		template<typename U>
		explicit ColorRGBA( const Math::Vec4<U> & v );
		template<typename U>
		explicit ColorRGBA( const ColorRGBA<U> & v );

		template<typename U>
		explicit operator ColorR<U>() const;

		template<typename U>
		explicit operator ColorRGB<U>() const;

		template<typename C = char>
		operator BasicString<C>() const;

		template<typename U>
		ColorRGBA<T> & operator=( const ColorR<U> & );

		template<typename U>
		ColorRGBA<T> & operator=( const ColorRGB<U> & );

		template<typename U>
		ColorRGBA<T> & operator=( const Math::Vec3<U> & );

		template<typename U>
		ColorRGBA<T> & operator=( const ColorRGBA<U> & );

		template<typename U>
		ColorRGBA<T> & operator=( const Math::Vec4<U> & );


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

		///@brief get the Alpha component of this color 
		///@return Blue component between [getMin() ; getMax()]
		const T & getAlpha() const;


		///@brief Convert this RGB (Red Green Blue) Color into a HSL (Hue Saturation Lightness) one
		///		H : Hue (Value between [ getMin() ; getMax() ] )
		///		S : Saturation (Value between [ getMin() ; getMax() ] )
		///		L : Lightness (Value between [ getMin() ; getMax() ] )
		///		A : Alpha (Value between [ getMin() ; getMax() ] )
		///@return HSL color
		ColorRGBA<T> RGBAtoHSLA() const;

		
		///@brief Convert this HSL (Hue Saturation Lightness) Color into a RGB (Red Green Blue) one
		///		R : Red (Value between [ getMin() ; getMax() ] )
		///		G : Green (Value between [ getMin() ; getMax() ] )
		///		B : Blue (Value between [ getMin() ; getMax() ] )
		///		A : Alpha (Value between [ getMin() ; getMax() ] )
		///@return RGB color
		ColorRGBA<T> HSLAtoRGBA() const;


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
		///@return ColorRGBA<U> Color of a new type
		template<typename U>
		ColorRGBA<U> toType() const;


		static const ColorRGBA<T> black;
		static const ColorRGBA<T> white;
		static const ColorRGBA<T> red;
		static const ColorRGBA<T> green;
		static const ColorRGBA<T> blue;

	private:
		template<typename U>
		void _castFromR( const U & l );

		template<typename U>
		void _castFromRGB( const U & r, const U & g, const U & b );

	};



}


#include "ColorRGBA.hpp"
