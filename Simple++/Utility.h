/**
 * @file	Utility.h.
 *
 * @brief		Some Static/Compile-Time utilities methods.
 * @author	Clément Gerber
 */

#pragma once

#include <cfloat>
#include <limits>

 /** @brief	Defines an alias representing the size */
typedef unsigned long long int Size;

namespace Utility {

	/**
	 * @brief		Simple compile-time method for removing a reference.
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template<class T>
	struct removeReference {
		typedef T Type;
	};

	/**
	 * @brief		Simple compile-time method for removing a reference.
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template<class T>
	struct removeReference<T&> {
		typedef T Type;
	};

	/**
	 * @brief		Simple compile-time method for removing a reference.
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template<class T>
	struct removeReference<T&&> {
		typedef T Type;
	};

	/**
	 * @brief		Simple method for swapping two elements.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	v1	The first value.
	 * @param [in,out]	v2	The second value.
	 */
	template<typename T>
	void swap( T& v1, T& v2 );

	/**
	 * @brief		Simple method for swapping two elements.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	v1	The first value.
	 * @param [in,out]	v2	The second value.
	 */
	template<typename T>
	void swap( T* v1, T* v2 );

	/**
	 * @brief		Convert a reference to a R-Value.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	t	A T to process.
	 *
	 * @returns	An R-Value.
	 * @sa		https://en.cppreference.com/w/cpp/language/value_category
	 */
	template<typename T>
	constexpr typename removeReference<T>::Type&& toRValue( T&& t );

	/**
	 * @brief		Template Struct used to get compile-time informations if a template type is derived from one another.
	 *
	 * @tparam	T1	Generic type parameter.
	 * @tparam	T2	Generic type parameter.
	 */
	template < typename Base, typename PotentialDerived >
	class isBase {
	public:

		typedef char( &no )[ 1 ];
		typedef char( &yes )[ 2 ];

		static yes checkType( Base* );
		static no  checkType( ... );
		enum : bool {
			value = sizeof( checkType( static_cast< PotentialDerived* >( 0 ) ) ) == sizeof( yes )
		};
	};

	/**
	 * @brief		Get if a type is a pointer or not.
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template < typename T >
	class isPointer {
	public:

		typedef char( &no )[ 1 ];
		typedef char( &yes )[ 2 ];

		template<typename C>
		static yes checkType( C** );
		static no  checkType( ... );
		enum : bool {
			value = sizeof( checkType( static_cast< T* >( 0 ) ) ) == sizeof( yes )
		};
	};

	template<typename T>
	T& removePointer( T* v ) {
		return *v;
	}
	template<typename T>
	T& removePointer( T & v ) {
		return v;
	}
	template<typename T>
	const T& removePointer( const T* v ) {
		return *v;
	}
	template<typename T>
	const T& removePointer( const T& v ) {
		return v;
	}

	/**
	 * @brief		Template Struct used to get compile-time informations if two template types are the same.
	 *
	 * @tparam	T1	Generic type parameter.
	 * @tparam	T2	Generic type parameter.
	 */
	template < typename T1, typename T2 >
	class isSame {
	public:
		enum : bool {
			value = false
		};
	};
	template < typename T1 >
	class isSame<T1, T1> {
	public:
		enum : bool {
			value = true
		};
	};

	template<typename T>
	bool isInf( const T& x );

	template<typename T>
	bool isNan( const T& x );

	/**
	 * @brief		Template Struct used to get compile-time informations of a number type.
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template<typename T>
	struct TypesInfos {
		typedef T Smaller;
		typedef T Bigger;
		typedef T Signed;
		typedef T Unsigned;

		constexpr static bool isInteger() {
			return false;
		}
		constexpr static T getMin() {
			return T();
		}
		constexpr static T getMax() {
			return T();
		}
		constexpr static bool isSigned() {
			return false;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}
	};


	template<>
	struct TypesInfos<char> {
		typedef char T;
		typedef char Smaller;
		typedef short Bigger;
		typedef char Signed;
		typedef unsigned char Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( CHAR_MIN );
		}
		constexpr static T getMax() {
			return T( CHAR_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}
	};

	template<>
	struct TypesInfos<unsigned char> {
		typedef unsigned char T;
		typedef unsigned char Smaller;
		typedef unsigned short Bigger;
		typedef char Signed;
		typedef unsigned char Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( 0 );
		}
		constexpr static T getMax() {
			return T( UCHAR_MAX );
		}
		constexpr static bool isSigned() {
			return false;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};




	template<>
	struct TypesInfos<short> {
		typedef short T;
		typedef char Smaller;
		typedef int Bigger;
		typedef short Signed;
		typedef unsigned short Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( SHRT_MIN );
		}
		constexpr static T getMax() {
			return T( SHRT_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};

	template<>
	struct TypesInfos<unsigned short> {
		typedef unsigned short T;
		typedef unsigned char Smaller;
		typedef unsigned int Bigger;
		typedef short Signed;
		typedef unsigned short Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( 0 );
		}
		constexpr static T getMax() {
			return T( USHRT_MAX );
		}
		constexpr static bool isSigned() {
			return false;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};


	template<>
	struct TypesInfos<int> {
		typedef int T;
		typedef short Smaller;
		typedef long int Bigger;
		typedef int Signed;
		typedef unsigned int Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( INT_MIN );
		}
		constexpr static T getMax() {
			return T( INT_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};

	template<>
	struct TypesInfos<unsigned int> {
		typedef unsigned int T;
		typedef unsigned short Smaller;
		typedef unsigned long int Bigger;
		typedef int Signed;
		typedef unsigned int Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( 0 );
		}
		constexpr static T getMax() {
			return T( UINT_MAX );
		}
		constexpr static bool isSigned() {
			return false;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};


	template<>
	struct TypesInfos<long int> {
		typedef long int T;
		typedef int Smaller;
		typedef long long int Bigger;
		typedef long int Signed;
		typedef unsigned long int Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( LONG_MIN );
		}
		constexpr static T getMax() {
			return T( LONG_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};

	template<>
	struct TypesInfos<unsigned long int> {
		typedef unsigned long int T;
		typedef unsigned int Smaller;
		typedef unsigned long long int Bigger;
		typedef long int Signed;
		typedef unsigned long int Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( 0 );
		}
		constexpr static T getMax() {
			return T( ULONG_MAX );
		}
		constexpr static bool isSigned() {
			return false;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};


	template<>
	struct TypesInfos<long long int> {
		typedef long long int T;
		typedef long int Smaller;
		typedef long long int Bigger;
		typedef long long int Signed;
		typedef unsigned long long int Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( LLONG_MIN );
		}
		constexpr static T getMax() {
			return T( LLONG_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};

	template<>
	struct TypesInfos<unsigned long long int> {
		typedef unsigned long long int T;
		typedef unsigned long int Smaller;
		typedef unsigned long long int Bigger;
		typedef long long int Signed;
		typedef unsigned long long int Unsigned;

		constexpr static bool isInteger() {
			return true;
		}
		constexpr static T getMin() {
			return T( 0 );
		}
		constexpr static T getMax() {
			return T( ULLONG_MAX );
		}
		constexpr static bool isSigned() {
			return false;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}

	};


	template<>
	struct TypesInfos<float> {
		typedef float T;
		typedef float Smaller;
		typedef double Bigger;
		typedef float Signed;
		typedef float Unsigned;

		constexpr static bool isInteger() {
			return false;
		}
		constexpr static T getMin() {
			return T( FLT_MIN );
		}
		constexpr static T getMax() {
			return T( FLT_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}


	};

	template<>
	struct TypesInfos<double> {
		typedef double T;
		typedef float Smaller;
		typedef double Bigger;
		typedef double Signed;
		typedef double Unsigned;

		constexpr static bool isInteger() {
			return false;
		}
		constexpr static T getMin() {
			return T( DBL_MIN );
		}
		constexpr static T getMax() {
			return T( DBL_MAX );
		}
		constexpr static bool isSigned() {
			return true;
		}
		constexpr static size_t getNbBits() {
			return sizeof( T ) * 8;
		}
	};

	template<typename T>
	class UtilityT {
	public:
		/**
		 * @brief 	Copy datas from a buffer into an another one
		 *
		 * @tparam	C	Type of the c.
		 * @tparam	D	Type of the d.
		 * @param [in,out]	destinationBuffer	Where to copy the datas.
		 * @param 		  	sourceBuffer	 	From where to copy.
		 * @param 		  	size			 	Number of elements to copy.
		 */
		template<typename C, typename D>
		static void copy( C* destinationBuffer, const D* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @tparam	C	Type of the c.
		 * @tparam	D	Type of the d.
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		template<typename C, typename D>
		static void copy( C** destinationBuffer, D* const* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( char* destinationBuffer, const char* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( unsigned char* destinationBuffer, const unsigned char* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( short* destinationBuffer, const short* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( unsigned short* destinationBuffer, const unsigned short* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( int* destinationBuffer, const int* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( unsigned int* destinationBuffer, const unsigned int* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( long int* destinationBuffer, const long int* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( unsigned long int* destinationBuffer, const unsigned long int* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( long long int* destinationBuffer, const long long int* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( unsigned long long int* destinationBuffer, const unsigned long long int* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( float* destinationBuffer, const float* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( double* destinationBuffer, const double* sourceBuffer, const Size size );
		/**
		 * @brief 	Copies this object
		 *
		 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
		 * @param 		  	sourceBuffer	 	Buffer for source data.
		 * @param 		  	size			 	The size.
		 */
		static void copy( wchar_t* destinationBuffer, const wchar_t* sourceBuffer, const Size size );
	};

	using Utility = UtilityT<int>;

	/**
	* @brief 	Copy datas from a buffer into an another one
	*
	* @tparam	C	Type of the c.
	* @tparam	D	Type of the d.
	* @param [in,out]	destinationBuffer	Where to copy the datas.
	* @param 		  	sourceBuffer	 	From where to copy.
	* @param 		  	size			 	Number of elements to copy.
	*/
	template<typename C, typename D>
	static void copy( C* destinationBuffer, const D* sourceBuffer, const Size size ) {
		return Utility::copy( destinationBuffer, sourceBuffer, size );
	}
	/**
	 * @brief 	Copies this object
	 *
	 * @tparam	C	Type of the c.
	 * @tparam	D	Type of the d.
	 * @param [in,out]	destinationBuffer	If non-null, buffer for destination data.
	 * @param 		  	sourceBuffer	 	Buffer for source data.
	 * @param 		  	size			 	The size.
	 */
	template<typename C, typename D>
	static void copy( C** destinationBuffer, D* const* sourceBuffer, const Size size ) {
		return Utility::copy( destinationBuffer, sourceBuffer, size );
	}
}



#include "Utility.hpp"
