#include "NodeValue.h"
namespace JSON {

	/************************************************************************/
	/* NodeValueT<S>                                                         */
	/************************************************************************/

	template<typename S>
	NodeValueT<S>::NodeValueT() :
		NodeT<S>( NodeT<S>::Type::Value ),
		bAddQuotes( true ) {

	}

	template<typename S>
	NodeValueT<S>::NodeValueT( const S& value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( unsigned int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( long long int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( unsigned long long int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( double value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( bool value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( value );
	}

	template<typename S>
	template<typename P>
	inline NodeValueT<S>::NodeValueT( const P* nullPtr ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( nullPtr );
	}

	template<typename S>
	NodeValueT<S>::NodeValueT( const S& name, const S& value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		this -> name = name;
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( const S& name, int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		this -> name = name;
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( const S& name, unsigned int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		this -> name = name;
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( const S& name, long long int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		this -> name = name;
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( const S& name, unsigned long long int value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		this -> name = name;
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( const S& name, double value ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		this -> name = name;
		setValue( value );
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT( const S& name, bool value ) :
		NodeT<S>( NodeT<S>::Type::Value ),
	{
		this -> name = name;
		setValue( value );
	}

		template<typename S>
	template<typename P>
	inline NodeValueT<S>::NodeValueT( const S& name, const P* nullPtr ) :
		NodeT<S>( NodeT<S>::Type::Value ) {
		setValue( nullPtr );
	}

	template<typename S>
	NodeValueT<S>::NodeValueT( const NodeValueT<S>& node ) :
		NodeT( node ),
		value( node.value ),
		bAddQuotes( node.bAddQuotes ),
		name( node.name ) {

	}

	template<typename S>
	NodeValueT<S>::NodeValueT( NodeValueT<S>&& node ) :
		NodeT( Utility::toRValue( node ) ),
		value( Utility::toRValue( node.value ) ),
		bAddQuotes( Utility::toRValue( node.bAddQuotes ) ),
		name( Utility::toRValue( node.name ) ) {

	}

	template<typename S>
	const S& NodeValueT<S>::getValue() const {
		return this -> value;
	}

	template<typename S>
	void NodeValueT<S>::setValue( const S& value ) {
		this -> value = value;
		this -> bAddQuotes = true;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue( int value ) {
		this -> value = S::toString( value );
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue( unsigned int value ) {
		this -> value = S::toString( value );
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue( long long int value ) {
		this -> value = S::toString( value );
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue( unsigned long long int value ) {
		this -> value = S::toString( value );
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue( double value ) {
		this -> value = S::toString( value );
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue( bool value ) {
		this -> value = S::toString( value );
		this -> bAddQuotes = false;
	}

	template<typename S>
	template<typename P>
	inline void NodeValueT<S>::setValue( const P* nullPtr ) {
		const S nullString( "null" );
		this -> value = nullString;
		this -> bAddQuotes = false;
	}



	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeValueT<S>::readJSON( const C** buffer, const EndFunc& endFunc ) {
		struct FunctorContentQuote {
			bool operator()( const C& c ) { return c != C( '"' ); }
		};
		struct FunctorContent {
			bool operator()( const C& c ) { return c != C( ',' ) && c != C( '}' ) && c != C( ']' ) && c != C( ' ' ); }
		};
		struct FunctorSpace {
			bool operator()( const C& c ) { return c == C( '\n' ) || c == C( '\r' ) || c == C( '\t' ) || c == C( ' ' ); }
		};

		static FunctorContentQuote functorContentQuote;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		static const S nullString( "null" );

		const C*& it( *buffer );

		// Value node.
		if ( ( *it ) == C( '"' ) ) {
			// Quote value.
			it++;
			const C* beginIt( it );
			while ( true ) {
				if ( endFunc( it ) ) {
					ERROR_SPP( TEXT( "[JSON Error] : Unexpected buffer end." ) );
					return false;
				}
				if ( !functorContentQuote( *it ) ) {
					if ( ( *( it - 1 ) ) != C( '\\' ) ) {
						break;
					}
				}
				it++;
			}

			S nodeValue( beginIt, Size( it - beginIt ) );

			if ( !_expectChar( &it, C( '"' ) ) ) return false;

			this -> value = nodeValue;
			this -> type = Type::Value;
			this -> bAddQuotes = true;
		} else {
			// Value without quote.

			const C* beginIt( it );
			while ( true ) {
				if ( endFunc( it ) ) {
					ERROR_SPP( TEXT( "[JSON Error] : Unexpected buffer end." ) );
					return false;
				}
				if ( !functorContent( *it ) )
					break;
				it++;
			}

			S nodeValue( beginIt, Size( it - beginIt ) );

			if ( nodeValue == nullString ) {
				this -> type = Type::Null;
			} else {
				this -> value = nodeValue;
				this -> type = Type::Value;
			}

			this -> bAddQuotes = false;
		}

		return true;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeValueT<S>::readJSON( const C* buffer, const EndFunc& endFunc ) {
		return NodeT<S>::readJSON<C, EndFunc>( buffer, endFunc );
	}

	template<typename S>
	bool NodeValueT<S>::readJSON( const S& str ) {
		return NodeT<S>::readJSON( str );
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeValueT<S>::_writeJSON( C& o, unsigned int indent, bool beautyfy ) const {
		if ( this -> getName().getSize() ) {
			o << Elem( '"' );
			o << this -> getName();
			o << Elem( '"' );
			o << Elem( ':' );
			if ( beautyfy ) {
				o << Elem( ' ' );
			}
		}

		if ( this -> bAddQuotes ) {
			o << Elem( '"' );
			o << this -> getValue();
			o << Elem( '"' );
		} else {
			o << this -> getValue();
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeValueT<S>::read( Stream* stream, int verbose ) {
		if ( !NodeT<S>::_read( stream ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> value, verbose - 1 ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> bAddQuotes, verbose - 1 ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename S>
	template<typename Stream>
	bool NodeValueT<S>::write( Stream* stream ) const {
		if ( !NodeT<S>::_write( stream ) ) {
			return false;
		}
		if ( !IO::write( stream, &this -> value ) ) {
			return false;
		}
		if ( !IO::write( stream, &this -> bAddQuotes ) ) {
			return false;
		}
		return true;
	}




}