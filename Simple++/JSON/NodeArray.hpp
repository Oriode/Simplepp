namespace JSON {

	/************************************************************************/
		/* NodeArrayT<S>                                                         */
		/************************************************************************/

	template<typename S>
	NodeArrayT<S>::NodeArrayT() : NodeMapT<S>() {
		this -> type = Type::Array;
	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT( const S& name ) : NodeMapT<S>( name ) {
		this -> type = Type::Array;
	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT( const S& name, const Vector<NodeT<S>*>& v ) :
		NodeT<S>( name, NodeT<S>::Type::Array ) {
		for ( auto it( v.getBegin() ); it != v.getEnd(); v.iterate( &it ) ) {
			NodeT<S>* node( v.getValueIt( it ) );
			this -> addChild( node );
		}
	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT( const NodeArrayT<S>& node ) : NodeT( node ) {

	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT( NodeArrayT<S>&& node ) : NodeT( Utility::toRValue( node ) ) {

	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeArrayT<S>::readJSON( const C** buffer, const EndFunc& endFunc ) {
		struct FunctorSpace {
			bool operator()( const C& c ) { return c == C( '\n' ) || c == C( '\r' ) || c == C( '\t' ) || c == C( ' ' ); }
		};

		static FunctorSpace functorSpace;

		const C*& it( *buffer );

		if ( !NodeT<S>::_expectChar( &it, C( '[' ) ) ) return false;

		this -> type = Type::Array;
		while ( functorSpace( *it ) ) it++;

		while ( true ) {
			if ( ( *it ) == C( ']' ) ) {
				it++;
				break;
			}

			NodeT<S>* newNode( parseT<S, C, EndFunc>( &it, endFunc ) );
			if ( newNode ) {
				this -> addChild( newNode );
			}
			while ( functorSpace( *it ) ) it++;

			if ( ( *it ) == C( ',' ) ) {
				it++;
			}

		}

		while ( functorSpace( *it ) ) it++;

		return true;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeArrayT<S>::readJSON( const C* buffer, const EndFunc& endFunc ) {
		return NodeT<S>::readJSON<C, EndFunc>( buffer, endFunc );
	}

	template<typename S>
	bool NodeArrayT<S>::readJSON( const S& str ) {
		return NodeT<S>::readJSON( str );
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeArrayT<S>::_writeJSON( C& o, unsigned int indent, bool beautyfy ) const {
		if ( this -> getName().getSize() ) {
			o << Elem( '"' );
			o << this -> getName();
			o << Elem( '"' );
			o << Elem( ':' );
			if ( beautyfy ) {
				o << Elem( ' ' );
			}
		}

		o << Elem( '[' );
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			if ( it != this -> childrenVector.getBegin() ) {
				o << Elem( ',' );
				if ( beautyfy ) {
					o << Elem( ' ' );
				}
			}

			NodeT<S>* child( this -> childrenVector.getValueIt( it ) );
			child -> _writeJSON<C, Elem>( o, indent, beautyfy );
		}
		o << Elem( ']' );
	}

}