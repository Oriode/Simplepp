#include "Path.h"
namespace OS {



	template<typename T>
	PathT<T>::PathT() {
		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );
	}

	template<typename T>
	PathT<T>::PathT( const T & str ) : path(str) {

	}

	template<typename T>
	inline bool PathT<T>::exists() const {
		return PathT<T>::exists( this -> path );
	}

	template<typename T>
	PathT<T> & PathT<T>::join( const T & str ) {
		return _join( str );
	}

	template<typename T>
	PathT<T> & PathT<T>::join( const PathT<T> & path ) {
		return _join( path );
	}

	template<typename T>
	template<typename C, typename ...Args>
	PathT<T> & PathT<T>::join( const C & c, Args ... args ) {
		return this -> _join( c ).join( args... );
	}

	template<typename T>
	PathT<T> & PathT<T>::join() {
		return *this;
	}

	template<typename T>
	T PathT<T>::basename() const {
		T result;

		const typename T::Iterator separetorIt( this -> path.getLastIt( PathT<T>::separatorChar ) );
		if ( separetorIt == this -> path.getEnd() ) {
			return this -> path;
		} else {
			return this -> path.getSubStr( separetorIt + 1, this -> path.getEnd() );
		}
	}

	template<typename T>
	const T & PathT<T>::toString() const {
		return this -> path;
	}

	template<typename T>
	inline bool PathT<T>::exists( const T & str ) {
		return std::filesystem::exists( str.toCString() );
	}

	template<typename T>
	inline PathT<T> & PathT<T>::_join( const T & str ) {
		this -> path.concat( PathT<T>::separatorChar );
		this -> path.concat( str );
		return *this;
	}

	template<typename T>
	inline PathT<T> & PathT<T>::_join( const PathT<T> & path ) {
		return _join( path.toString() );
	}

}