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
	class TypesInfos {
	public:
		typedef T Bigger;
		typedef T Signed;
		typedef T Unsigned;

		static bool isInteger() { return false; }
		static T getMin() { return T(); }
		static T getMax() { return T(); }
		static bool isSigned() { return false; }
		static size_t getNbBits() { return sizeof( T ) * 8; }
	};


	template<>
	class TypesInfos<char> {
	public:
		typedef char T;
		typedef short Bigger;
		typedef char Signed;
		typedef unsigned char Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( CHAR_MIN ); }
		static T getMax() { return T( CHAR_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }
	};

	template<>
	class TypesInfos<unsigned char> {
	public:
		typedef unsigned char T;
		typedef unsigned short Bigger;
		typedef char Signed;
		typedef unsigned char Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( 0 ); }
		static T getMax() { return T( UCHAR_MAX ); }
		static bool isSigned() { return false; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};




	template<>
	class TypesInfos<short> {
	public:
		typedef short T;
		typedef int Bigger;
		typedef short Signed;
		typedef unsigned short Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( SHRT_MIN ); }
		static T getMax() { return T( SHRT_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	class TypesInfos<unsigned short> {
	public:
		typedef unsigned short T;
		typedef unsigned int Bigger;
		typedef short Signed;
		typedef unsigned short Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( 0 ); }
		static T getMax() { return T( USHRT_MAX ); }
		static bool isSigned() { return false; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	class TypesInfos<int> {
	public:
		typedef int T;
		typedef long Bigger;
		typedef int Signed;
		typedef unsigned int Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( INT_MIN ); }
		static T getMax() { return T( INT_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	class TypesInfos<unsigned int> {
	public:
		typedef unsigned int T;
		typedef unsigned long Bigger;
		typedef int Signed;
		typedef unsigned int Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( 0 ); }
		static T getMax() { return T( UINT_MAX ); }
		static bool isSigned() { return false; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	class TypesInfos<long> {
	public:
		typedef long T;
		typedef long long Bigger;
		typedef long Signed;
		typedef unsigned long Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( LONG_MIN ); }
		static T getMax() { return T( LONG_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	class TypesInfos<unsigned long> {
	public:
		typedef unsigned long T;
		typedef unsigned long long Bigger;
		typedef long Signed;
		typedef unsigned long Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( 0 ); }
		static T getMax() { return T( ULONG_MAX ); }
		static bool isSigned() { return false; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	class TypesInfos<long long> {
	public:
		typedef long long T;
		typedef long long Bigger;
		typedef long long Signed;
		typedef unsigned long long Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( LLONG_MIN ); }
		static T getMax() { return T( LLONG_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};

	template<>
	class TypesInfos<unsigned long long> {
	public:
		typedef unsigned long long T;
		typedef unsigned long long Bigger;
		typedef long long Signed;
		typedef unsigned long long Unsigned;

		static bool isInteger() { return true; }
		static T getMin() { return T( 0 ); }
		static T getMax() { return T( ULLONG_MAX ); }
		static bool isSigned() { return false; }
		static size_t getNbBits() { return sizeof( T ) * 8; }

	};


	template<>
	class TypesInfos<float> {
	public:
		typedef float T;
		typedef double Bigger;
		typedef float Signed;
		typedef float Unsigned;

		static bool isInteger() { return false; }
		static T getMin() { return T( FLT_MIN ); }
		static T getMax() { return T( FLT_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }


	};

	template<>
	class TypesInfos<double> {
	public:
		typedef double T;
		typedef double Bigger;
		typedef double Signed;
		typedef double Unsigned;

		static bool isInteger() { return false; }
		static T getMin() { return T( DBL_MIN ); }
		static T getMax() { return T( DBL_MAX ); }
		static bool isSigned() { return true; }
		static size_t getNbBits() { return sizeof( T ) * 8; }




	};









}



#include "Utility.hpp"
