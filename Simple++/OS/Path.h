#pragma once




#include <sys/stat.h>
#include <filesystem>

#include "../String.h"

namespace OS {

	template<typename T>
	class PathT {
	public:

		PathT();
		PathT( const T & str );

		bool exists() const;
		PathT<T> & join( const T & str );
		PathT<T> & join( const PathT<T> & path );
		template<typename C, typename ...Args>
		PathT<T> & join( const C & c, Args ... args );
		PathT<T> & join();

		T basename() const;

		const T & toString() const;

		static bool exists( const T & str );



	#if defined WIN32
		static constexpr typename T::ElemType separatorChar = T::ElemType( '\\' );
	#else
		static constexpr typename T::ElemType separatorChar = T::ElemType( '/' );
	#endif

		// static constexpr typename T::ElemType separatorChar;
	private:
		PathT<T> & _join( const T & str );
		PathT<T> & _join( const PathT<T> & path );


		T path;
	};


#if defined WIN32
	using Path = PathT<WString>;
#else
	using Path = PathT<UTF8String>;
#endif
}




#include "Path.hpp"

