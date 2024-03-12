#pragma once

#include <sys/stat.h>
#include <filesystem>

#include "../UTF8String.h"

namespace OS {

	///@brief Represent a Path in the current OS.
	///@template S String Type.
	template<typename S>
	class PathT : public S {
	public:

		typedef S StringType;

		PathT();
		PathT( const S & str );

		/**
		 * @brief		Constructor
		 * @tparam	C	String type.
		 * @param	str	Constant string.
		 */
		template<typename C, size_t N>
		PathT(const C(&str)[N]);

		bool exists() const;
		PathT<S> & join( const S & str );
		PathT<S> & join( const PathT<S> & path );
		template<typename C, typename ...Args>
		PathT<S> & join( const C & c, Args ... args );
		PathT<S> & join();

		bool remove() const;

		S basename() const;

		const S & toString() const;

		static bool exists( const S & str );
		static bool remove(const S& str);

	#if defined WIN32
		static constexpr typename S::ElemType separatorChar = S::ElemType( '\\' );
	#else
		static constexpr typename S::ElemType separatorChar = S::ElemType( '/' );
	#endif

		// static constexpr typename S::ElemType separatorChar;
	private:
		PathT<S> & _join( const S & str );
	};


///@brief Simple overloads for Windows & other systems not handling file names the same way.
#if defined WIN32
#ifndef PATH
#define __PATH(str) L##str
#define PATH(str) __PATH(str)
#endif
	using Path = PathT<WString>;
#else
#ifndef PATH
#define __PATH(str) #str
#define PATH(str) __PATH(str)
#endif
	using Path = PathT<UTF8String>;
#endif
}




#include "Path.hpp"

