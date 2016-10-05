///@file Color.h
///@brief Basic for every type of color
///@author Cl�ment Gerber
///@date 22/09/2016 (DMY) 
#pragma once

#include "../Utility.h"
#include "../String.h"

namespace Graphic {

	///@brief Struct used to retrieve the type compilation times informations 
	template<typename T>
	struct _ColorHelper {
		typedef typename Utility::TypesInfos<typename Utility::TypesInfos<T>::Bigger>::Bigger Type;
		typedef float Float;
		constexpr static T getMax() {
			return Utility::TypesInfos<T>::getMax();
		}
	};
	template<>
	struct _ColorHelper<float> {
		typedef float Type;
		typedef float Float;
		constexpr static float getMax() {
			return 1.0f;
		}
	};
	template<>
	struct _ColorHelper<double> {
		typedef double Type;
		typedef double Float;
		constexpr static double getMax() {
			return 1.0;
		}
	};





	///@brief Class representing a color of 1 component of type T
	template<typename T>
	class Color {
	public:

		///@brief Type used to sum multiple pixels components
		typedef typename _ColorHelper<T>::Type SumType;

		///@brief Type used to sum multiple pixels components multiplied with a negative value
		typedef typename Utility::TypesInfos<typename SumType>::Signed KernelType;

		///@brief Floating point type
		typedef typename _ColorHelper<T>::Float Float;


		inline static void castComponent( float & comDest, const float & compSrc );

		template<typename T1>
		inline static void castComponent( T1 & comDest, const T1 & compSrc );
		template<typename T1, typename T2>
		inline static void castComponent( T1 & comDest, const T2 & compSrc );
		template<typename U>
		inline static void castComponent( float & comDest, const U & compSrc );
		template<typename U>
		inline static void castComponent( double & comDest, const U & compSrc );
		template<typename U>
		inline static void castComponent( U & comDest, const float & compSrc );
		template<typename U>
		inline static void castComponent( U & comDest, const double & compSrc );




		constexpr static T getMin() {
			return T( 0 );
		}
		static constexpr T getMax() {
			return _ColorHelper<T>::getMax();
		}
		constexpr static T getMaxNbBits() {
			return Utility::TypesInfos<T>::getNbBits();
		}
	};


	

	

	template<typename T>
	void Color<T>::castComponent( float & comDest, const float & compSrc ) {
		comDest = ( compSrc );
	}

	template<typename T>
	template<typename T1>
	void Color<T>::castComponent( T1 & comDest, const T1 & compSrc ) {
		comDest = ( compSrc );
	}

	template<typename T>
	template<typename T1, typename T2>
	void Color<T>::castComponent( T1 & comDest, const T2 & compSrc ) {
		comDest = T1( compSrc );
	}

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( float & comDest, const U & compSrc ) {
		comDest = float( compSrc ) / float( ColorR<U>::getMax() );
	}

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( U & comDest, const float & compSrc ) {
		comDest = unsigned char( compSrc * float( ColorR<U>::getMax() ) );
	}

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( double & comDest, const U & compSrc ) {
		comDest = double( compSrc ) / double( ColorR<U>::getMax() );
	}

	template<typename T>
	template<typename U>
	void Color<T>::castComponent( U & comDest, const double & compSrc ) {
		comDest = unsigned char( compSrc * double( ColorR<U>::getMax() ) );
	}


}
