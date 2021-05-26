#include "Path.h"
namespace OS {



	template<typename T>
	PathT<T>::PathT() {
		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );
	}

	template<typename T>
	PathT<T>::PathT( const T & str ) : T(str) {

	}

	template<typename T>
	template<typename C, size_t N>
	PathT<T>::PathT(const C(&str)[N]) :
		T(str)
	{

	}








	template<typename T>
	inline bool PathT<T>::exists() const {
		return PathT<T>::exists( *this );
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

		const typename T::Iterator separetorIt( this -> getLastIt( PathT<T>::separatorChar ) );
		if ( separetorIt == this -> getEnd() ) {
			return *this;
		} else {
			return this -> getSubStr( separetorIt + 1, this -> getEnd() );
		}
	}

	template<typename T>
	const T & PathT<T>::toString() const {
		return *this;
	}

	template<typename T>
	inline bool PathT<T>::exists( const T & str ) {
		return std::filesystem::exists( str.toCString() );
	}

	template<typename T>
	inline PathT<T> & PathT<T>::_join( const T & str ) {
		this -> concat( PathT<T>::separatorChar );
		this -> concat( str );
		return *this;
	}

	template<typename T>
	inline PathT<T> & PathT<T>::_join( const PathT<T> & path ) {
		return _join( path.toString() );
	}

}