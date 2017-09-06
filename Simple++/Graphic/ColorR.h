///@file Color.h
///@brief Colors objects to be used in all the graphic purpose
///@author Clément Gerber
///@date 21/09/2016 (DMY) 

#pragma once





#include "../Utility.h"
#include "../Math/Math.h"
#include "Color.h"

namespace Graphic {



	///@brief Class representing a color of 1 component of type T
	template<typename T>
	class ColorR : public Color<T> {
	public:
		typedef T Type;

		///@brief Type used to sum multiple pixels components
		typedef typename ColorR<typename Color<T>::SumType> ColorSum;

		///@brief Type used to sum multiple pixels components multiplied with a negative value
		typedef typename ColorR<typename Color<T>::KernelType> ColorKernel;

		///@brief Floating point type
		typedef typename ColorR<typename Color<T>::Float> ColorFloat;

		explicit ColorR();

		// Define every possible case because of automatic cast ambiguity
		explicit ColorR( const unsigned char & r );
		explicit ColorR( const unsigned short & r );
		explicit ColorR( const unsigned int & r );
		explicit ColorR( const unsigned long & r );
		explicit ColorR( const unsigned long long & r );

		explicit ColorR( const char & r );
		explicit ColorR( const short & r );
		explicit ColorR( const int & r );
		explicit ColorR( const long & r );
		explicit ColorR( const long long & r );

		explicit ColorR( const float & r );
		explicit ColorR( const double & r );


		template<typename U>
		explicit ColorR( const ColorR<U> & color );

		explicit operator T() const;
		template<typename C = char>
		operator BasicString<C>() const;

		template<typename U>
		ColorR<T> & operator=( const ColorR<U> & color );




		/************************************************************************/
		/* Arithmetic                                                           */
		/************************************************************************/

		ColorR<T> & operator+=( const ColorR<T> & color );
		ColorR<T> & operator*=( const ColorR<T> & color );
		ColorR<T> & operator-=( const ColorR<T> & color );
		ColorR<T> & operator/=( const ColorR<T> & color );
		ColorR<T> & operator%=( const ColorR<T> & color );
		ColorR<T> & operator>>=( const ColorR<T> & color );
		ColorR<T> & operator<<=( const ColorR<T> & color );

		ColorR<T> & operator+=( const T & color );
		ColorR<T> & operator*=( const T & color );
		ColorR<T> & operator-=( const T & color );
		ColorR<T> & operator/=( const T & color );
		ColorR<T> & operator%=( const T & color );
		ColorR<T> & operator>>=( const T & color );
		ColorR<T> & operator<<=( const T & color );

		ColorR<T> & operator++();
		ColorR<T> & operator--();
		ColorR<T> operator-() const;


		///@brief get the Lightness of this color (alias of getRed()) between [ getMin() ; getMax() ]
		///@return Lightness of this color
		const T & getLightness() const;


		///@brief get the Red component of this color (alias of getLightness()) between [ getMin() ; getMax() ]
		///@return Red component of this color
		const T & getRed() const;


		///@brief convert this color into an human readable string
		///@see toHex();
		///@return StringASCII of type C
		template<typename C = char>
		BasicString<C> toString() const;


		///@brief convert this color into Hexadecimal view
		///@return StringASCII of type C
		template<typename C = char>
		BasicString<C> toHex() const;





		template<typename U>
		ColorR<U> toType() const;




		T r;

		static constexpr Format getFormat() { return Format::R; }

		static const ColorR<T> black;
		static const ColorR<T> white;
		static const ColorR<T> red;
		static const ColorR<T> green;
		static const ColorR<T> blue;

		static const Format format;
	};

	
	




	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	bool operator==( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	bool operator==( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	bool operator==( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	bool operator!=( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	bool operator!=( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	bool operator!=( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	bool operator>=( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	bool operator>=( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	bool operator>=( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	bool operator<=( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	bool operator<=( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	bool operator<=( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	bool operator>( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	bool operator>( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	bool operator>( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	bool operator<( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	bool operator<( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	bool operator<( const T & c1, const ColorR<T> & c2 );


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	ColorR<T> operator+( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator+( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator+( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	ColorR<T> operator-( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator-( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator-( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	ColorR<T> operator/( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator/( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator/( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	ColorR<T> operator*( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator*( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator*( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	ColorR<T> operator%( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator%( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator%( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	ColorR<T> operator>>( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator>>( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator>>( const T & c1, const ColorR<T> & c2 );

	template<typename T>
	ColorR<T> operator<<( const ColorR<T> & c1, const ColorR<T> & c2 );
	template<typename T>
	ColorR<T> operator<<( const ColorR<T> & c1, const T & c2 );
	template<typename T>
	ColorR<T> operator<<( const T & c1, const ColorR<T> & c2 );



	

}

#include "ColorR.hpp"

