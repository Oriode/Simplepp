#pragma once



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
	void swap(T & v1, T & v2);

	template<typename T>
	void swap(T * v1, T * v2);

	template<typename T>
	constexpr typename removeReference<T>::Type && toRValue(T && t);


	template < typename Base, typename PotentialDerived >
	class isBase {
	public:

		typedef char(&no)	[1];
		typedef char(&yes)[2];

		static yes check(Base * );
		static no  check(...);
		enum : bool { value = sizeof(check(static_cast<PotentialDerived*>( 0 ))) == sizeof(yes) };
	};

	template < typename T1, typename T2 >
	class isSame {
	public:
		typedef char(&no)[1];
		typedef char(&yes)[2];

		static yes check(T1 *);
		static no  check(...);
		enum : bool { value = sizeof(check(static_cast<T2*>( 0 ))) == sizeof(yes) };
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




}



#include "Utility.hpp"