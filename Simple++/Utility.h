#pragma once


#include <cfloat>
#include <limits>

namespace Utility {



	template<class T>
	struct removeReference {
		typedef T Type;
	};

	template<class T>
	struct removeReference<T &> {
		typedef T Type;
	};

	template<class T>
	struct removeReference<T &&> {
		typedef T Type;
	};

	template<typename T>
	void swap( T & v1, T & v2 );

	template<typename T>
	void swap( T * v1, T * v2 );

	template<typename T>
	constexpr typename removeReference<T>::Type && toRValue( T && t );


	template < typename Base, typename PotentialDerived >
	class isBase {
	public:

		typedef char( &no )[1];
		typedef char( &yes )[2];

		static yes check( Base * );
		static no  check( ... );
		enum : bool { value = sizeof( check( static_cast< PotentialDerived* >( 0 ) ) ) == sizeof( yes ) };
	};

	template < typename T1, typename T2 >
	class isSame {
	public:
		typedef char( &no )[1];
		typedef char( &yes )[2];

		static yes check( T1 * );
		static no  check( ... );
		enum : bool { value = sizeof( check( static_cast< T2* >( 0 ) ) ) == sizeof( yes ) };
	};

	

	template<typename T>
	class biggerType {
		typedef T Type;
	};

	template<>
	class biggerType<char> {
		typedef short Type;
	};

	template<>
	class biggerType<unsigned char> {
		typedef unsigned short Type;
	};





	//	template < typename Base, typename PotentialDerived >
	//	bool isBase<Base, PotentialDerived>::value = IsClassT<Base,PotentialDerived >::check(0);


		/*template<typename T>
		class isBase {
			typedef char yes[1];
			typedef char no[2];
			template<typename C> static yes& test(int C::*); // selected if C is a class type
			template<typename C> static no&  test(...);      // selected otherwise
		public:
			static bool const value = sizeof(test<T>(0)) == sizeof(yes);
		};*/



	template<typename T>
	struct TypesInfos {
		typedef T Bigger;
		typedef T Signed;
		typedef T Unsigned;

		constexpr static bool isInteger() { return false; }
		constexpr static T getMin() { return T(); }
		constexpr static T getMax() { return T(); }
		constexpr static bool isSigned() { return false; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }
	};


	template<>
	struct TypesInfos<char> {
		typedef char T;
		typedef short Bigger;
		typedef char Signed;
		typedef unsigned char Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( CHAR_MIN ); }
		constexpr static T getMax() { return T( CHAR_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }
	};

	template<>
	struct TypesInfos<unsigned char> {
		typedef unsigned char T;
		typedef unsigned short Bigger;
		typedef char Signed;
		typedef unsigned char Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( 0 ); }
		constexpr static T getMax() { return T( UCHAR_MAX ); }
		constexpr static bool isSigned() { return false; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};




	template<>
	struct TypesInfos<short> {
		typedef short T;
		typedef int Bigger;
		typedef short Signed;
		typedef unsigned short Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( SHRT_MIN ); }
		constexpr static T getMax() { return T( SHRT_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	struct TypesInfos<unsigned short> {
		typedef unsigned short T;
		typedef unsigned int Bigger;
		typedef short Signed;
		typedef unsigned short Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( 0 ); }
		constexpr static T getMax() { return T( USHRT_MAX ); }
		constexpr static bool isSigned() { return false; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	struct TypesInfos<int> {
		typedef int T;
		typedef long Bigger;
		typedef int Signed;
		typedef unsigned int Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( INT_MIN ); }
		constexpr static T getMax() { return T( INT_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	struct TypesInfos<unsigned int> {
		typedef unsigned int T;
		typedef unsigned long Bigger;
		typedef int Signed;
		typedef unsigned int Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( 0 ); }
		constexpr static T getMax() { return T( UINT_MAX ); }
		constexpr static bool isSigned() { return false; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	struct TypesInfos<long> {
		typedef long T;
		typedef long long Bigger;
		typedef long Signed;
		typedef unsigned long Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( LONG_MIN ); }
		constexpr static T getMax() { return T( LONG_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	struct TypesInfos<unsigned long> {
		typedef unsigned long T;
		typedef unsigned long long Bigger;
		typedef long Signed;
		typedef unsigned long Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( 0 ); }
		constexpr static T getMax() { return T( ULONG_MAX ); }
		constexpr static bool isSigned() { return false; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	struct TypesInfos<long long> {
		typedef long long T;
		typedef long long Bigger;
		typedef long long Signed;
		typedef unsigned long long Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( LLONG_MIN ); }
		constexpr static T getMax() { return T( LLONG_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	struct TypesInfos<unsigned long long> {
		typedef unsigned long long T;
		typedef unsigned long long Bigger;
		typedef long long Signed;
		typedef unsigned long long Unsigned;

		constexpr static bool isInteger() { return true; }
		constexpr static T getMin() { return T( 0 ); }
		constexpr static T getMax() { return T( ULLONG_MAX ); }
		constexpr static bool isSigned() { return false; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	struct TypesInfos<float> {
		typedef float T;
		typedef double Bigger;
		typedef float Signed;
		typedef float Unsigned;

		constexpr static bool isInteger() { return false; }
		constexpr static T getMin() { return T( FLT_MIN ); }
		constexpr static T getMax() { return T( FLT_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }


	};

	template<>
	struct TypesInfos<double> {
		typedef double T;
		typedef double Bigger;
		typedef double Signed;
		typedef double Unsigned;

		constexpr static bool isInteger() { return false; }
		constexpr static T getMin() { return T( DBL_MIN ); }
		constexpr static T getMax() { return T( DBL_MAX ); }
		constexpr static bool isSigned() { return true; }
		constexpr static size_t getNbBits() { return sizeof( T ) * 8; }




	};









}



#include "Utility.hpp"
