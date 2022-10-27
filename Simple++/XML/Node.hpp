namespace XML {

	template<typename S>
	NodeT<S>::NodeT() :
		type( Type::Element ),
		parent( NULL ) {

		// Ensure S is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<S::ElemType>, S>::value );
	}

	template<typename S>
	NodeT<S>::NodeT( const S & name, Type type ) :
		name( name ),
		type( type ),
		parent( NULL ) {

		// Ensure S is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<S::ElemType>, S>::value );
	}

	template<typename S>
	NodeT<S>::NodeT( const NodeT<S> & node ) :
		name( node.name ),
		id( node.id ),
		type( node.type ),
		parent( NULL ) {

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<S> * newNode( new NodeT<S>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		for ( auto it( node.paramsVector.getBegin() ); it != node.paramsVector.getEnd(); node.paramsVector.iterate( &it ) ) {
			ParamT<S> * newParam( new ParamT<S>( *( node.paramsVector.getValueIt( it ) ) ) );
			addParam( newParam );
		}
	}

	template<typename S>
	NodeT<S>::NodeT( NodeT<S> && node ) :
		name( Utility::toRValue( node.name ) ),
		id( Utility::toRValue( node.id ) ),
		type( Utility::toRValue( node.type ) ),
		paramsMap( Utility::toRValue( node.paramsMap ) ),
		paramsVector( Utility::toRValue( node.paramsVector ) ),
		childrenMap( Utility::toRValue( node.childrenMap ) ),
		childrenVector( Utility::toRValue( node.childrenVector ) ),
		parent( Utility::toRValue( node.parent ) ) {

		node.childrenVector.clear();
		node.paramsVector.clear();
	}

	template<typename S>
	NodeT<S>::~NodeT() {
		_unload();
	}

	template<typename S>
	NodeT<S> & NodeT<S>::operator=( const NodeT<S> & node ) {
		this -> name = node.name;
		this -> id = node.id;
		this -> type = node.type;
		this -> parent = NULL;

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<S> * newNode( new NodeT<S>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		for ( auto it( node.paramsVector.getBegin() ); it != node.paramsVector.getEnd(); node.paramsVector.iterate( &it ) ) {
			ParamT<S> * newParam( new ParamT<S>( *( node.paramsVector.getValueIt( it ) ) ) );
			addParam( newParam );
		}
		return *this;
	}

	template<typename S>
	NodeT<S> & NodeT<S>::operator=( NodeT<S> && node ) {
		this -> name = Utility::toRValue( node.name );
		this -> id = Utility::toRValue( node.id );
		this -> type = Utility::toRValue( node.type );
		this -> paramsVector = Utility::toRValue( node.paramsVector );
		this -> paramsMap = Utility::toRValue( node.paramsMap );
		this -> childrenVector = Utility::toRValue( node.childrenVector );
		this -> childrenMap = Utility::toRValue( node.childrenMap );
		this -> parent = Utility::toRValue( node.parent );

		node.childrenVector.clear();
		node.paramsVector.clear();

		return *this;
	}

	template<typename S>
	typename NodeT<S>::Type NodeT<S>::getType() const {
		return this -> type;
	}

	template<typename S>
	const NodeTextT<S> * NodeT<S>::toText() const {
		return ( static_cast< const NodeTextT<S> * >( this ) );
	}

	template<typename S>
	NodeTextT<S> * NodeT<S>::toText() {
		return ( static_cast< NodeTextT<S> * >( this ) );
	}

	template<typename S>
	const NodeT<S> * NodeT<S>::getParent() const {
		return this -> parent;
	}

	template<typename S>
	NodeT<S> * NodeT<S>::getParent() {
		return this -> parent;
	}

	template<typename S>
	const S & NodeT<S>::getValue() const {
		if ( getType() == Type::Text ) {
			return toText() -> getValue();
		} else if ( this -> childrenVector.getSize() == 1 ) {
			return this -> childrenVector[ 0 ] -> getValue();
		} else {
			//Error, you shouldn't call this method, return an empty string
			return S::null;
		}
	}

	template<typename S>
	void NodeT<S>::setValue( const S & value ) {
		if ( getType() == Type::Text ) {
			this -> toText() -> setValue( value );
		} else {
			if ( this -> childrenVector.getSize() > 0 ) {
				// We are not a Text node, and we have at least one child, if the first one is a Text one, set it's value.
				if ( this -> childrenVector[ 0 ] -> getType() == Type::Text )
					this -> childrenVector[ 0 ] -> toText() -> setValue( value );
			} else {
				// We are not a Text node, and do not have any child, add one
				NodeTextT<S> * newNode( new NodeTextT<S>( value ) );
				addChild( newNode );
			}
		}
	}

	template<typename S>
	void NodeT<S>::setName( const S & name ) {
		if ( this -> parent ) {
			this -> parent -> _setChildName( this, name );
		} else {
			this -> name = name;
		}
	}

	template<typename S>
	const S & NodeT<S>::getName() const {
		return this -> name;
	}

	template<typename S>
	void NodeT<S>::addParam( const ParamT<S> & param ) {
		ParamT<S> * newParam( new ParamT<S>( param ) );

		this -> paramsMap.insert( newParam -> getName(), newParam );
		this -> paramsVector.push( newParam );
	}

	template<typename S>
	void NodeT<S>::addParam( const S & name, const S & value ) {
		ParamT<S> * newParam( new ParamT<S>( name, value ) );

		this -> paramsMap.insert( newParam -> getName(), newParam );
		this -> paramsVector.push( newParam );
	}

	template<typename S>
	void NodeT<S>::addParam( ParamT<S> * param ) {
		static S idStr( "id" );
		if ( param -> getName() == idStr )
			setId( param -> getValue() );

		this -> paramsMap.insert( param -> getName(), param );
		this -> paramsVector.push( param );
	}

	template<typename S>
	ParamT<S> * NodeT<S>::getParam( const S & name ) {
		auto paramP = this -> paramsMap[ name ];
		if ( paramP ) return *paramP;
		else return NULL;
	}

	template<typename S>
	const ParamT<S> * NodeT<S>::getParam( const S & name ) const {
		auto paramP = this -> paramsMap[ name ];
		if ( paramP ) return *paramP;
		else return NULL;
	}

	template<typename S>
	ParamT<S> & NodeT<S>::getParam( Size i ) {
		return *( this -> paramsVector.getValueI( i ) );
	}

	template<typename S>
	const ParamT<S> & NodeT<S>::getParam( Size i ) const {
		return *( this -> paramsVector.getValueI( i ) );
	}

	template<typename S>
	bool NodeT<S>::deleteParam( ParamT<S> * param ) {
		if ( this -> paramsVector.eraseFirst( param ) ) {
			this -> paramsMap.eraseI( param -> getName() );
			delete param;
			return true;
		}
		return false;
	}

	template<typename S>
	bool NodeT<S>::deleteParam( Size i ) {
		if ( i >= this -> paramsVector.getSize() ) {
			return false;
		} else {
			ParamT<S> * param( this -> paramsVector[ i ] );
			this -> paramsVector.eraseI( i );
			this -> paramsMap.eraseI( param -> getName() );
			delete param;
			return true;
		}
	}

	template<typename S>
	void NodeT<S>::setId( const S & id ) {
		if ( this -> parent ) {
			this -> parent -> _setChildId( this, id );
		} else {
			this -> id = id;
		}
	}

	template<typename S>
	const S & NodeT<S>::getId() const {
		return this -> id;
	}

	template<typename S>
	Vector< NodeT<S> * > NodeT<S>::getElementsById( const S & id ) const {
		Vector< NodeT<S> * > nodeVector;
		nodeVector.reserve( 20 );

		if ( id == this -> id )
			nodeVector.push( const_cast< NodeT<S> * >( this ) );

		_getElementsById( &nodeVector, id );
		return nodeVector;
	}

	template<typename S>
	Vector< NodeT<S> * > NodeT<S>::getElementsByName( const S & name ) const {
		Vector< NodeT<S> * > nodeVector;
		nodeVector.reserve( 20 );

		if ( name == this -> name )
			nodeVector.push( const_cast< NodeT<S> * >( this ) );

		_getElementsByName( &nodeVector, name );
		return nodeVector;
	}

	template<typename S>
	Size NodeT<S>::getNbChildren() const {
		return this -> childrenVector.getSize();
	}

	template<typename S>
	Size NodeT<S>::getNbParams() const {
		return this -> paramsVector.getSize();
	}

	template<typename S>
	void NodeT<S>::addChild( NodeT<S> * child ) {
		if ( this -> type == Type::Text ) {
			if ( child -> getType() == Type::Text ) {
				NodeTextT<S> * nodeTextThis( this -> toText() );
				NodeTextT<S> * nodeTextChild( child -> toText() );

				nodeTextThis -> getValue().concat( nodeTextChild -> getValue() );
				delete nodeTextChild;
			} else {
				if ( this -> parent ) {
					this -> parent -> addChild( child );
				}
			}
		} else {
			if ( child -> parent )
				child -> parent -> removeChild( child );
			if ( child -> getId().getSize() )
				this -> childrenByIdMap.insert( child -> getId(), child );

			child -> parent = this;
			this -> childrenMap.insert( child -> getName(), child );
			this -> childrenVector.push( child );
		}
	}

	template<typename S>
	void NodeT<S>::_clear() {
		_unload();

		this -> name.clear();
		this -> id.clear();

		this -> paramsMap.clear();
		this -> paramsVector.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();
	}

	template<typename S>
	void NodeT<S>::_unload() {
		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			delete this -> paramsVector.getValueIt( it );
		}
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			NodeT<S> * node( this -> childrenVector.getValueIt( it ) );
			switch ( node->getType() ) {
				case NodeT<S>::Type::Text:
				{
					NodeTextT<S> * nodeText( ( NodeTextT<S> * ) node );
					delete nodeText;
					break;
				}
				default:
				{
					delete node;
					break;
				}
			}
		}
	}

	template<typename S>
	const Vector< NodeT<S> * > NodeT<S>::getChild( const S & name ) const {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return NULL;
	}

	template<typename S>
	Vector< NodeT<S> * > NodeT<S>::getChild( const S & name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return NULL;
	}

	template<typename S>
	const NodeT<S> * NodeT<S>::getChild( Size i ) const {
		return const_cast< NodeT<S> * >( this ) -> getChild( i );
	}

	template<typename S>
	NodeT<S> * NodeT<S>::getChild( Size i ) {
		if ( i < this->childrenVector.getSize() ) {
			return this->childrenVector.getValueI( i );
		} else {
			return NULL;
		}
	}

	template<typename S>
	bool NodeT<S>::deleteChild( NodeT<S> * child ) {
		NodeT<S> * childRemoved( removeChild( child ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	bool NodeT<S>::deleteChild( Size i ) {
		NodeT<S> * childRemoved( removeChild( i ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	NodeT<S> * NodeT<S>::removeChild( NodeT<S> * child ) {
		if ( this -> childrenVector.eraseFirst( child ) ) {
			this -> childrenMap.eraseFirst( child -> getName(), child );
			if ( child -> getId().getSize() )
				this -> childrenByIdMap.eraseFirst( child -> getId(), child );
			child -> parent = NULL;
			return child;
		} else {
			return NULL;
		}
	}

	template<typename S>
	NodeT<S> * NodeT<S>::removeChild( Size i ) {
		if ( i >= this -> childrenVector.getSize() ) {
			return NULL;
		} else {
			NodeT<S> * child( this -> childrenVector[ i ] );
			this -> childrenVector.eraseI( i );
			this -> childrenMap.eraseFirst( child -> getName(), child );
			if ( child -> getId().getSize() )
				this -> childrenByIdMap.eraseFirst( child -> getId(), child );
			child -> parent = NULL;
			return child;
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::writeXML( Stream * fileStreamP, unsigned int tabs ) const {
		Stream & stream( *fileStreamP );
		
		_writeXML<Stream, char>( stream, tabs );

		return !( fileStreamP -> bad() );
	}

	template<typename S>
	template<typename C>
	bool NodeT<S>::writeXML( C & str, unsigned int tabs ) const {
		_writeXML<C, C::ElemType>( str, tabs );
		return true;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeT<S>::_readXML( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorNodeName {
			bool operator()( const C & c ) { return c != C( ' ' ) && c != C( '\t' ) && c != C( '>' ) && c != C( '/' ); }
		};
		struct FunctorContent {
			bool operator()( const C & c ) { return c != C( '<' ); }
		};
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		struct FunctorNoSpace {
			bool operator()( const C & c ) { return c != C( '<' ) && c != C( '\n' ) && c != C( '\t' ) && c != C( ' ' ); }
		};
		static FunctorNodeName functorNodeName;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		const C *& it( *buffer );

		{
			while ( functorSpace( *it ) ) it++;

			if ( !NodeT<S>::_expectChar( &it, C( '<' ) ) ) return false;

			// We have an opening node or self closing
			auto beginIt( it );
			while ( true ) {
				if ( endFunc( it ) ) {
					ERROR_SPP( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
					return false;
				}
				if ( !functorNodeName( *it ) ) break;
				it++;
			}
			// Call the constructor (pointer, size).
			S nodeName( beginIt, Size( it - beginIt ) );

			this -> setName( nodeName );

			while ( _parseParameter( &it, endFunc ) );

			if ( ( *it ) == C( '/' ) ) {
				// Self closing node
				it++;
				while ( functorSpace( *it ) ) it++;

				return NodeT<S>::_expectChar( &it, C( '>' ) );
			} else {
				while ( functorSpace( *it ) ) it++;
				if ( ( *it ) != C( '>' ) ) {
					ERROR_SPP( TEXT( "[XML ERROR] : Expecting '>'." ) );
					return false;
				}
				it++;
				// End of opening node.
			}
		}

		// Start of node content.

		appendXML( &it, endFunc );

		{
			it++; // Skip the '/'
			auto beginIt( it );
			while ( true ) {
				if ( endFunc( it ) ) {
					ERROR_SPP( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
					return false;
				}
				if ( !functorNodeName( *it ) ) break;
				it++;
			}

			// Call the constructor (pointer, size).
			S nodeName( beginIt, Size( it - beginIt ) );

			while ( functorSpace( *it ) ) it++;

			if ( nodeName != this -> getName() ) {
				ERROR_SPP( String::format( TEXT( "[XML ERROR] : Closing node do not match. \"%\" != \"%\"." ), this -> getName(), nodeName ) );
				// SYNTAX ERROR
				return false;
			} else {
				return NodeT<S>::_expectChar( &it, C( '>' ) );
			}
		}
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeT<S>::appendXML( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorContent {
			bool operator()( const C & c ) { return c != C( '<' ); }
		};
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		const C *& it( *buffer );

		while ( true ) {
			while ( functorSpace( *it ) ) it++;
			const C * beginIt( it );
			const C * endIt;
			while ( functorContent( *it ) && !endFunc( it ) ) it++;

			if ( it > beginIt ) {
				// We probably found something.
				endIt = it;
				while ( functorSpace( *( endIt -1) ) ) endIt--;

				if ( endIt != beginIt ) {
					// We have content, so we gonna create a text node and add the content
					// Call the constructor (pointer, size).
					S textContent( beginIt, Size( endIt - beginIt ) );
					NodeTextT<S> * nodeText( new NodeTextT<S>( textContent ) );

					this -> addChild( nodeText );
				}
			}

			if ( endFunc( it ) ) {
				return true;
			}

			if ( ( *it ) == C( '<' ) ) {
				const C * tmpIt( it );
				tmpIt++;
				while ( functorSpace( *tmpIt ) ) tmpIt++;
				if ( ( *tmpIt ) == C( '/' ) ) {
					it = tmpIt;
					break;
				} else {
					NodeT<S> * newNode( new NodeT<S>() );
					this -> addChild( newNode );

					if ( !newNode -> _readXML( &it, endFunc ) )
						return false;
				}
			} else {
				ERROR_SPP( TEXT( "[XML ERROR] : Expected '<'." ) );
				return false;
			}
		}
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeT<S>::appendXML( const C * buffer, const EndFunc & endFunc ) {
		return appendXML( &buffer, endFunc );
	}

	template<typename S>
	bool NodeT<S>::appendXML( const S & str ) {
		const S::ElemType * buffer( str.toCString() );
		return appendXML<S::ElemType>( &buffer );
	}


	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeT<S>::_parseParameter( const C ** buffer, const EndFunc & endFunc ) {
		const C *& it( *buffer );

		struct FunctorValue {
			bool operator()( const C & c ) { return c != C( '"' ); }
		};
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		struct FunctorName {
			bool operator()( const C & c ) { return c != C( '=' ) && c != C( '\t' ) && c != C( ' ' ) && c != C( '>' ) && c != C( '/' ); }
		};
		static FunctorName functorName;
		static FunctorSpace functorSpace;
		static FunctorValue functorValue;

		// Now lets skip all the blanks
		while ( functorSpace( *it ) ) it++;

		// ? is a special char
		if ( ( *it ) == C( '?' ) || ( *it ) == C( '/' ) || endFunc( it ) ) return false;
		auto iteratorBegin( it );
		while ( true ) {
			if ( endFunc( it ) ) {
				ERROR_SPP( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
				return false;
			}
			if ( !functorName( *it ) )
				break;
			it++;
		}

		if ( iteratorBegin != it ) {
			ParamT<S> * newParam( new ParamT<S>() );

			newParam -> setName( S( iteratorBegin, Size( it - iteratorBegin ) ) );

			if ( ( *it ) == C( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == C( '"' ) ) {
					( it )++; // Skip the quotes too

					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							ERROR_SPP( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorValue( *it ) )
							break;
						it++;
					}
					newParam -> setValue( S( iteratorBegin, Size( it - iteratorBegin ) ) );

					if ( ( *it ) == C( '"' ) ) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							ERROR_SPP( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorName( *it ) )
							break;
						it++;
					}
					newParam -> setValue( S( iteratorBegin, Size( it - iteratorBegin ) ) );
				}

			}
			this -> addParam( newParam );
			return true;
		}
		return false;
	}

	template<typename S>
	template<typename S2>
	S2 NodeT<S>::toString( unsigned int indent ) const {
		S2 newString;
		newString.reserve( 128 );

		_writeXML<S2, S2::ElemType>( newString, indent );
		return newString;
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::read( Stream * stream ) {
		if ( getType() == Type::Text )
			return this -> toText() -> read( stream );
		else
			return _read( stream );
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::_read( Stream * stream ) {
		_unload();
		this -> paramsMap.clear();
		this -> paramsVector.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();

		if ( !IO::read( stream, &this -> name ) ) {
			_clear();
			return false;
		}

		if ( !IO::read( stream, &this -> id ) ) {
			_clear();
			return false;
		}

		// Read the Params
		Size nbParams;
		if ( !IO::read( stream, &nbParams ) ) {
			_clear();
			return false;
		}
		nbParams = Math::min( nbParams, Size( 1000 ) );
		for ( Size i( 0 ); i < nbParams; i++ ) {
			ParamT<S> * newParam( new ParamT<S>() );
			if ( !IO::read( stream, newParam ) ) {
				delete newParam;
				_clear();
				return false;
			}
			addParam( newParam );
		}

		// Read the children
		Size nbChilds;
		if ( !IO::read( stream, &nbChilds ) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min( nbChilds, Size( 1000 ) );
		for ( Size i( 0 ); i < nbChilds; i++ ) {
			Type newNodeType;
			if ( !IO::read( stream, &newNodeType ) ) {
				_clear();
				return false;
			}
			if ( newNodeType == Type::Text ) {
				NodeTextT<S> * newNode( new NodeTextT<S>() );
				newNode -> parent = this;
				if ( !IO::read( stream, newNode ) ) {
					delete newNode;
					_clear();
					return false;
				}
				this -> childrenVector.push( newNode );
				this -> childrenMap.insert( newNode -> getName(), newNode );
			} else {
				NodeT<S> * newNode( new NodeT() );
				newNode -> parent = this;
				if ( !IO::read( stream, newNode ) ) {
					delete newNode;
					_clear();
					return false;
				}
				this -> childrenVector.push( newNode );
				this -> childrenMap.insert( newNode -> getName(), newNode );
			}


		}


		return true;
	}

	template<typename S>
	bool NodeT<S>::_setChildName( NodeT<S> * child, const S & name ) {
		if ( this -> childrenMap.eraseFirst( child -> getName(), child ) ) {
			child -> name = name;
			this -> childrenMap.insert( child -> getName(), child );
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	bool NodeT<S>::_setChildId( NodeT<S> * child, const S & id ) {
		this -> childrenByIdMap.eraseFirst( child -> getId(), child );
		child -> id = id;
		if ( id.getSize() )
			this -> childrenByIdMap.insert( child -> getId(), child );
		return true;
	}

	template<typename S>
	void NodeT<S>::_getElementsById( Vector < NodeT<S> * > * nodeVector, const S & id ) const {
		const Vector < NodeT<S> * > * vectorFounded( this -> childrenByIdMap[ id ] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			this -> childrenVector.getValueIt( it ) -> _getElementsById( nodeVector, id );
		}
	}

	template<typename S>
	void NodeT<S>::_getElementsByName( Vector < NodeT<S> * > * nodeVector, const S & name ) const {
		const Vector < NodeT<S> * > * vectorFounded( this -> childrenMap[ name ] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			this -> childrenVector.getValueIt( it ) -> _getElementsByName( nodeVector, name );
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::write( Stream * stream ) const {
		if ( getType() == Type::Text )
			return this -> toText() -> write( stream );
		else
			return _write( stream );
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::_write( Stream * stream ) const {


		if ( !IO::write( stream, &this -> name ) )
			return false;
		if ( !IO::write( stream, &this -> id ) )
			return false;

		Size nbParams( this -> paramsVector.getSize() );
		Size nbChilds( this -> childrenVector.getSize() );

		if ( !IO::write( stream, &nbParams ) )
			return false;
		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			if ( !IO::write( stream, this -> paramsVector.getValueIt( it ) ) )
				return false;
		}

		if ( !IO::write( stream, &nbChilds ) )
			return false;
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			Type type( this -> childrenVector.getValueIt( it ) -> getType() );
			if ( !IO::write( stream, &type ) )
				return false;
			if ( !IO::write( stream, this -> childrenVector.getValueIt( it ) ) )
				return false;
		}

		return true;
	}

	template<typename S>
	S NodeT<S>::toStringDebug( unsigned int indent ) const {
		S newString;
		newString.reserve( 100 );

		for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
			newString << S::ElemType( '\t' );
		}

		newString << S::ElemType( '<' );
		newString << this -> name;

		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			newString << S::ElemType( ' ' );
			newString << this -> paramsVector.getValueIt( it ) -> toString();
		}

		newString << S::ElemType( '>' );
		newString << S::ElemType( '\n' );

		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			newString << this -> childrenVector.getValueIt( it ) -> toStringDebug( indent + 1 );
			newString << S::ElemType( '\n' );
		}

		if ( this -> type == Type::Text ) {
			for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
				newString << S::ElemType( '\t' );
			}

			newString << this -> toText() -> getValue();
			newString << S::ElemType( '\n' );
		}

		for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
			newString << S::ElemType( '\t' );
		}

		newString << S::ElemType( '<' );
		newString << S::ElemType( '/' );
		newString << this -> name;
		newString << S::ElemType( '>' );

		return newString;
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeT<S>::_writeXML( C & o, unsigned int tabs ) const {
		if ( getType() == Type::Text )
			return this -> toText() -> _writeXML<C, Elem>( o, tabs );

		for ( unsigned int i( 0 ); i < tabs; i++ )
			o << Elem( '\t' );

		o << Elem( '<' );
		o << this -> name;

		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			o << Elem( ' ' );
			this -> paramsVector.getValueIt( it ) -> _writeXML<C, Elem>( o );
		}

		// If we have children, it's not an self closing one
		if ( this -> childrenVector.getSize() ) {
			o << Elem( '>' );

			for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
				if ( getNbChildren() > 1 )
					o << Elem( '\n' );
				NodeT<S> * child( this -> childrenVector.getValueIt( it ) );
				if ( child -> getType() == NodeT<S>::Type::Text && getNbChildren() == 1 ) {
					this -> childrenVector.getValueIt( it ) -> _writeXML<C, Elem>( o, 0 );
				} else {
					this -> childrenVector.getValueIt( it ) -> _writeXML<C, Elem>( o, tabs + 1 );
				}
			}

			// Now Close
			if ( getNbChildren() > 1 ) {
				o << Elem( '\n' );
				for ( unsigned int i( 0 ); i < tabs; i++ )
					o << Elem( '\t' );
			}

			o << Elem( '<' );
			o << Elem( '/' );
			o << this -> name;
			o << Elem( '>' );
		} else {
			o << Elem( '/' );
			o << Elem( '>' );
		}
	}

	template<typename S>
	template<typename C>
	bool NodeT<S>::_expectChar( const C ** buffer, const C & c ) {
		const C *& it( *buffer );

		if ( ( *it ) == c ) {
			it++;
			return true;
		} else {
			ERROR_SPP( String::format(TEXT( "[XML ERROR] : Expected '%'." ), c) );
			return false;
		}

	}






	/************************************************************************/
	/* NodeTextT<S>                                                         */
	/************************************************************************/

	template<typename S>
	template<typename Stream>
	bool NodeTextT<S>::writeXML( Stream * fileStreamP ) const {
		Stream & stream( *fileStreamP );

		_writeXML<Stream, char>( stream, 0 );

		return !( fileStreamP -> bad() );
	}

	template<typename S>
	template<typename Stream>
	bool NodeTextT<S>::read( Stream * stream ) {
		this -> value.clear();

		/*
		if ( !NodeT<S>::_read( stream ) ) {
			return false;
		}
		*/
		if ( !IO::read( stream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename S>
	template<typename Stream>
bool NodeTextT<S>::write( Stream * stream ) const {
		/*
		if ( !NodeT<S>::_write( stream ) )
			return false;
		*/
		if ( !IO::write( stream, &this -> value ) )
			return false;
		return true;
	}

	template<typename S>
	void NodeTextT<S>::_clear() {
		NodeT<S>::_clear();
		this -> value.clear();
	}

	template<typename S>
	NodeTextT<S>::NodeTextT() : NodeT<S>( S( "#text" ), NodeT<S>::Type::Text ) {

	}

	template<typename S>
	NodeTextT<S>::NodeTextT( const S & value ) : NodeT<S>( S( "#text" ), NodeT<S>::Type::Text ),
		value( value ) {

	}

	template<typename S>
	NodeTextT<S>::NodeTextT( const NodeTextT<S> & node ) : NodeT( node ),
		value( node.value ) {

	}

	template<typename S>
	NodeTextT<S>::NodeTextT( NodeTextT<S> && node ) : NodeT( Utility::toRValue( node ) ),
		value( Utility::toRValue( node.value ) ) {

	}

	template<typename S>
	NodeTextT<S> & NodeTextT<S>::operator=( const NodeTextT<S> & node ) {
		NodeT<S>::operator=( node );
		this -> value = node.value;
		return *this;
	}

	template<typename S>
	NodeTextT<S> & NodeTextT<S>::operator=( NodeTextT<S> && node ) {
		NodeT<S>::operator=( Utility::toRValue( node ) );
		this -> value = Utility::toRValue( node.value );
		return *this;
	}

	template<typename S>
	const S & NodeTextT<S>::getValue() const {
		return this -> value;
	}

	template<typename S>
	S & NodeTextT<S>::getValue() {
		return this -> value;
	}

	template<typename S>
	void NodeTextT<S>::setValue( const S & value ) {
		this -> value = value;
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeTextT<S>::_writeXML( C & o, unsigned int tabs ) const {
		for ( unsigned int i( 0 ); i < tabs; i++ )
			o << Elem( '\t' );
		o << this -> value;
	}

	template<typename S>
	template<typename S2>
	S2 NodeTextT<S>::toString( unsigned int indent ) const {
		S2 newString;
		newString.reserve( 128 );

		_writeXML<S2, S2::ElemType>( newString, indent );
		return newString;
	}

}
