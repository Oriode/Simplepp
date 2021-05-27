#pragma once

#include <sys/stat.h>
#include <filesystem>

#include "../UTF8String.h"

namespace OS {

	///@brief Represent a Path in the current OS.
	///@template T String Type.
	template<typename T>
	class PathT : public T {
	public:

		typedef T StringType;

		PathT();
		PathT( const T & str );

		/**
		 * @brief		Constructor
		 * @tparam	C	String type.
		 * @param	str	Constant string.
		 */
		template<typename C, size_t N>
		PathT(const C(&str)[N]);

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
		PathT<T> & _join( const BasicString<T> & str );
	};


///@brief Simple overloads for Windows & other systems not handling file names the same way.
#if defined WIN32
	using Path = PathT<WString>;
#else
	using Path = PathT<UTF8String>;
#endif
}




#include "Path.hpp"

