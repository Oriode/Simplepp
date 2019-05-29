/**
 * @file	Graphic\Color.h.
 *
 * @brief	Declares the color class
 */

#pragma once

#include "../Utility.h"
#include "../String.h"

 /**
  * @namespace	Graphic
  *
  * @brief	.
  */

namespace Graphic {

	/**
	 * @enum	Format
	 *
	 * @brief	Values that represent formats
	 */

	enum class Format : unsigned int {
		R = 1, RGB = 3, RGBA = 4
	};

	/**

	/**
	 * @struct	_ColorHelper
	 *
	 * @brief	A color helper.
	 * @brief	Struct used to retrieve the type compilation times informations
	 *
	 * @author	Clement
	 * @author	Clement
	 * @date	29-May-19 /
	 * @date	29-May-19
	 *
	 * @tparam	T	Generic type parameter.
	 */

	template<typename T>
	struct _ColorHelper {
		typedef typename Utility::TypesInfos<typename Utility::TypesInfos<T>::Bigger>::Bigger Type;

		/**
		 * @typedef	float Float
		 *
		 * @brief	Defines an alias representing the float
		 */

		typedef float Float;

		/**
		 * @fn	constexpr static T getMax()
		 *
		 * @brief	Get the maximum
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @returns	The calculated maximum.
		 */

		constexpr static T getMax() {
			return Utility::TypesInfos<T>::getMax();
		}
	};

	/**
	 * @struct	_ColorHelper<float>
	 *
	 * @brief	A color helper.
	 *
	 * @author	Clement
	 * @date	29-May-19
	 */

	template<>
	struct _ColorHelper<float> {
		typedef float Type;

		/**
		 * @typedef	float Float
		 *
		 * @brief	Defines an alias representing the float
		 */

		typedef float Float;

		/**
		 * @fn	constexpr static float getMax()
		 *
		 * @brief	Get the maximum
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @returns	The calculated maximum.
		 */

		constexpr static float getMax() {
			return 1.0f;
		}
	};

	/**
	 * @struct	_ColorHelper<double>
	 *
	 * @brief	A color helper.
	 *
	 * @author	Clement
	 * @date	29-May-19
	 */

	template<>
	struct _ColorHelper<double> {
		typedef double Type;

		/**
		 * @typedef	double Float
		 *
		 * @brief	Defines an alias representing the float
		 */

		typedef double Float;

		/**
		 * @fn	constexpr static double getMax()
		 *
		 * @brief	Gets the maximum
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @returns	The calculated maximum.
		 */

		constexpr static double getMax() {
			return 1.0;
		}
	};

	/**
	 * @class	Color
	 *
	 * @brief	Class representing a color of 1 component of type T
	 *
	 * @author	Clement
	 * @date	29-May-19
	 *
	 * @tparam	T	Generic type parameter.
	 */

	template<typename T>
	class Color {
	public:

		/**
		 * @typedef	typename _ColorHelper<T>::Type SumType
		 *
		 * @brief	Type used to sum multiple pixels components
		 */

		typedef typename _ColorHelper<T>::Type SumType;

		/**
		 * @typedef	typename Utility::TypesInfos<typename SumType>::Signed KernelType
		 *
		 * @brief	Type used to sum multiple pixels components multiplied with a negative value
		 */

		typedef typename Utility::TypesInfos<typename SumType>::Signed KernelType;

		/**
		 * @typedef	typename _ColorHelper<T>::Float Float
		 *
		 * @brief	Floating point type
		 */

		typedef typename _ColorHelper<T>::Float Float;

		/**
		 * @fn	inline static void Color::castComponent( float & comDest, const float & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		inline static void castComponent( float & comDest, const float & compSrc );

		/**
		 * @fn	template<typename T1> inline static void Color::castComponent( T1 & comDest, const T1 & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @tparam	T1	Generic type parameter.
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		template<typename T1>
		inline static void castComponent( T1 & comDest, const T1 & compSrc );

		/**
		 * @fn	template<typename T1, typename T2> inline static void Color::castComponent( T1 & comDest, const T2 & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @tparam	T1	Generic type parameter.
		 * @tparam	T2	Generic type parameter.
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		template<typename T1, typename T2>
		inline static void castComponent( T1 & comDest, const T2 & compSrc );

		/**
		 * @fn	template<typename U> inline static void Color::castComponent( float & comDest, const U & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @tparam	U	Generic type parameter.
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		template<typename U>
		inline static void castComponent( float & comDest, const U & compSrc );

		/**
		 * @fn	template<typename U> inline static void Color::castComponent( double & comDest, const U & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @tparam	U	Generic type parameter.
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		template<typename U>
		inline static void castComponent( double & comDest, const U & compSrc );

		/**
		 * @fn	template<typename U> inline static void Color::castComponent( U & comDest, const float & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @tparam	U	Generic type parameter.
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		template<typename U>
		inline static void castComponent( U & comDest, const float & compSrc );

		/**
		 * @fn	template<typename U> inline static void Color::castComponent( U & comDest, const double & compSrc );
		 *
		 * @brief	Cast component
		 *
		 * @tparam	U	Generic type parameter.
		 * @param [in,out]	comDest	The com destination.
		 * @param 		  	compSrc	The component source.
		 */

		template<typename U>
		inline static void castComponent( U & comDest, const double & compSrc );

		/**
		 * @fn	constexpr static T Color::getMin()
		 *
		 * @brief	Gets the minimum
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @returns	The calculated minimum.
		 */

		constexpr static T getMin() {
			return T( 0 );
		}

		/**
		 * @fn	static constexpr T Color::getMax()
		 *
		 * @brief	Gets the maximum
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @returns	The calculated maximum.
		 */

		static constexpr T getMax() {
			return _ColorHelper<T>::getMax();
		}

		/**
		 * @fn	constexpr static T Color::getMaxNbBits()
		 *
		 * @brief	Gets maximum nb bits
		 *
		 * @author	Clement
		 * @date	29-May-19
		 *
		 * @returns	The maximum nb bits.
		 */

		constexpr static T getMaxNbBits() {
			return Utility::TypesInfos<T>::getNbBits();
		}
	};

	/**
	 * @fn	template<typename T> void Color<T>::castComponent( float & comDest, const float & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	void Color<T>::castComponent( float & comDest, const float & compSrc ) {
		comDest = ( compSrc );
	}

	/**
	 * @fn	template<typename T> template<typename T1> void Color<T>::castComponent( T1 & comDest, const T1 & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	template<typename T1>
	void Color<T>::castComponent( T1 & comDest, const T1 & compSrc ) {
		comDest = ( compSrc );
	}

	/**
	 * @fn	template<typename T> template<typename T1, typename T2> void Color<T>::castComponent( T1 & comDest, const T2 & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	template<typename T1, typename T2>
	void Color<T>::castComponent( T1 & comDest, const T2 & compSrc ) {
		comDest = T1( compSrc );
	}

	/**
	 * @fn	template<typename T> template<typename U> void Color<T>::castComponent( float & comDest, const U & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( float & comDest, const U & compSrc ) {
		comDest = float( compSrc ) / float( ColorR<U>::getMax() );
	}

	/**
	 * @fn	template<typename T> template<typename U> void Color<T>::castComponent( U & comDest, const float & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( U & comDest, const float & compSrc ) {
		comDest = unsigned char( compSrc * float( ColorR<U>::getMax() ) );
	}

	/**
	 * @fn	template<typename T> template<typename U> void Color<T>::castComponent( double & comDest, const U & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( double & comDest, const U & compSrc ) {
		comDest = double( compSrc ) / double( ColorR<U>::getMax() );
	}

	/**
	 * @fn	template<typename T> template<typename U> void Color<T>::castComponent( U & comDest, const double & compSrc )
	 *
	 * @brief	Cast component
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	comDest	The com destination.
	 * @param 		  	compSrc	The component source.
	 */

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( U & comDest, const double & compSrc ) {
		comDest = unsigned char( compSrc * double( ColorR<U>::getMax() ) );
	}


}
