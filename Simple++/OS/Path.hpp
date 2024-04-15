#include "Path.h"
namespace OS {



	template<typename S>
	PathT<S>::PathT() {
		// Ensure S is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<S::ElemType>, S>::value );
	}

	template<typename S>
	PathT<S>::PathT( const S& str ) : S( str ) {

	}

	template<typename S>
	template<typename C, size_t N>
	PathT<S>::PathT( const C( &str )[ N ] ) :
		S( str ) {

	}








	template<typename S>
	inline PathT<S>::PathT( const UTF8String& str ) :
		S( str ) { }

	template<typename S>
	inline bool PathT<S>::exists() const {
		return PathT<S>::exists( *this );
	}

	template<typename S>
	PathT<S>& PathT<S>::join( const S& str ) {
		return _join( str );
	}

	template<typename S>
	PathT<S>& PathT<S>::join( const PathT<S>& path ) {
		return _join( path );
	}

	template<typename S>
	template<typename C, typename ...Args>
	PathT<S>& PathT<S>::join( const C& c, Args ... args ) {
		return this -> _join( c ).join( args... );
	}

	template<typename S>
	PathT<S>& PathT<S>::join() {
		return *this;
	}

	template<typename S>
	inline bool PathT<S>::remove() const {
		return PathT<S>::remove( *this );
	}

	template<typename S>
	S PathT<S>::basename() const {
		S result;

		const typename S::Iterator separetorIt( this -> getLastIt( PathT<S>::separatorChar ) );
		if ( separetorIt == this -> getEnd() ) {
			return *this;
		} else {
			return this -> getSubStr( separetorIt + 1, this -> getEnd() );
		}
	}

	template<typename S>
	const S& PathT<S>::toString() const {
		return *this;
	}

	template<typename S>
	inline bool PathT<S>::exists( const S& str ) {
		return std::filesystem::exists( str.toCString() );
	}

	template<typename S>
	inline bool PathT<S>::remove( const S& str ) {
		return std::filesystem::remove( str.toCString() );
	}

	template<typename S>
	inline PathT<S>& PathT<S>::_join( const S& str ) {
		this -> concat( PathT<S>::separatorChar );
		this -> concat( str );
		return *this;
	}

}