namespace XML {

	template<typename T>
	NodeT<T>::NodeT() :
		type( Type::Element ),
		parent( NULL ) {

		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );

	}

	template<typename T>
	NodeT<T>::NodeT( const T & name, Type type ) :
		name( name ),
		type( type ),
		parent( NULL ) {

		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );

	}

	template<typename T>
	NodeT<T>::NodeT( const NodeT<T> & node ) :
		name( node.name ),
		id( node.id ),
		type( node.type ),
		parent( NULL ) {

		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<T> * newNode( new NodeT<T>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		for ( auto it( node.paramsVector.getBegin() ); it != node.paramsVector.getEnd(); node.paramsVector.iterate( &it ) ) {
			ParamT<T> * newParam( new ParamT<T>( *( node.paramsVector.getValueIt( it ) ) ) );
			addParam( newParam );
		}
	}

	template<typename T>
	NodeT<T>::NodeT( NodeT<T> && node ) :
		name( Utility::toRValue( node.name ) ),
		id( Utility::toRValue( node.id ) ),
		type( Utility::toRValue( node.type ) ),
		paramsMap( Utility::toRValue( node.paramsMap ) ),
		paramsVector( Utility::toRValue( node.paramsVector ) ),
		childrenMap( Utility::toRValue( node.childrenMap ) ),
		childrenVector( Utility::toRValue( node.childrenVector ) ),
		parent( Utility::toRValue( node.parent ) ) {

		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );

		node.childrenVector.clear();
		node.paramsVector.clear();
	}

	template<typename T>
	NodeT<T>::~NodeT() {
		_unload();
	}

	template<typename T>
	NodeT<T> & NodeT<T>::operator=( const NodeT<T> & node ) {
		this -> name = node.name;
		this -> id = node.id;
		this -> type = node.type;
		this -> parent = NULL;

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<T> * newNode( new NodeT<T>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		for ( auto it( node.paramsVector.getBegin() ); it != node.paramsVector.getEnd(); node.paramsVector.iterate( &it ) ) {
			ParamT<T> * newParam( new ParamT<T>( *( node.paramsVector.getValueIt( it ) ) ) );
			addParam( newParam );
		}
		return *this;
	}

	template<typename T>
	NodeT<T> & NodeT<T>::operator=( NodeT<T> && node ) {
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

	template<typename T>
	typename NodeT<T>::Type NodeT<T>::getType() const {
		return this -> type;
	}

	template<typename T>
	const NodeTextT<T> * NodeT<T>::toText() const {
		return ( static_cast< const NodeTextT<T> * >( this ) );
	}

	template<typename T>
	NodeTextT<T> * NodeT<T>::toText() {
		return ( static_cast< NodeTextT<T> * >( this ) );
	}

	template<typename T>
	const NodeT<T> * NodeT<T>::getParent() const {
		return this -> parent;
	}

	template<typename T>
	NodeT<T> * NodeT<T>::getParent() {
		return this -> parent;
	}

	template<typename T>
	const T & NodeT<T>::getValue() const {
		if ( getType() == Type::Text ) {
			return toText() -> getValue();
		} else if ( this -> childrenVector.getSize() == 1 ) {
			return this -> childrenVector[ 0 ] -> getValue();
		} else {
			//Error, you shouldn't call this method, return an empty string
			return T::null;
		}
	}

	template<typename T>
	void NodeT<T>::setValue( const T & value ) {
		if ( getType() == Type::Text ) {
			this -> toText() -> setValue( value );
		} else {
			if ( this -> childrenVector.getSize() > 0 ) {
				// We are not a Text node, and we have at least one child, if the first one is a Text one, set it's value.
				if ( this -> childrenVector[ 0 ] -> getType() == Type::Text )
					this -> childrenVector[ 0 ] -> toText() -> setValue( value );
			} else {
				// We are not a Text node, and do not have any child, add one
				NodeTextT<T> * newNode( new NodeTextT<T>( value ) );
				addChild( newNode );
			}
		}
	}

	template<typename T>
	void NodeT<T>::setName( const T & name ) {
		if ( this -> parent ) {
			this -> parent -> _setChildName( this, name );
		} else {
			this -> name = name;
		}
	}

	template<typename T>
	const T & NodeT<T>::getName() const {
		return this -> name;
	}

	template<typename T>
	void NodeT<T>::addParam( const ParamT<T> & param ) {
		ParamT<T> * newParam( new ParamT<T>( param ) );

		this -> paramsMap.insert( newParam -> getName(), newParam );
		this -> paramsVector.push( newParam );
	}

	template<typename T>
	void NodeT<T>::addParam( const T & name, const T & value ) {
		ParamT<T> * newParam( new ParamT<T>( name, value ) );

		this -> paramsMap.insert( newParam -> getName(), newParam );
		this -> paramsVector.push( newParam );
	}

	template<typename T>
	void NodeT<T>::addParam( ParamT<T> * param ) {
		static T idStr( "id" );
		if ( param -> getName() == idStr )
			setId( param -> getValue() );

		this -> paramsMap.insert( param -> getName(), param );
		this -> paramsVector.push( param );
	}

	template<typename T>
	ParamT<T> * NodeT<T>::getParam( const T & name ) {
		auto paramP = this -> paramsMap[ name ];
		if ( paramP ) return *paramP;
		else return NULL;
	}

	template<typename T>
	const ParamT<T> * NodeT<T>::getParam( const T & name ) const {
		auto paramP = this -> paramsMap[ name ];
		if ( paramP ) return *paramP;
		else return NULL;
	}

	template<typename T>
	ParamT<T> & NodeT<T>::getParam( typename Vector< ParamT<T> * >::Size i ) {
		return *( this -> paramsVector.getValueI( i ) );
	}

	template<typename T>
	const ParamT<T> & NodeT<T>::getParam( typename Vector< ParamT<T> * >::Size i ) const {
		return *( this -> paramsVector.getValueI( i ) );
	}

	template<typename T>
	bool NodeT<T>::deleteParam( ParamT<T> * param ) {
		if ( this -> paramsVector.eraseFirst( param ) ) {
			this -> paramsMap.eraseIndex( param -> getName() );
			delete param;
			return true;
		}
		return false;
	}

	template<typename T>
	bool NodeT<T>::deleteParam( typename Vector< ParamT<T> * >::Size i ) {
		if ( i >= this -> paramsVector.getSize() ) {
			return false;
		} else {
			ParamT<T> * param( this -> paramsVector[ i ] );
			this -> paramsVector.eraseIndex( i );
			this -> paramsMap.eraseIndex( param -> getName() );
			delete param;
			return true;
		}
	}

	template<typename T>
	void NodeT<T>::setId( const T & id ) {
		if ( this -> parent ) {
			this -> parent -> _setChildId( this, id );
		} else {
			this -> id = id;
		}
	}

	template<typename T>
	const T & NodeT<T>::getId() const {
		return this -> id;
	}

	template<typename T>
	Vector< NodeT<T> * > NodeT<T>::getElementsById( const T & id ) const {
		Vector< NodeT<T> * > nodeVector;
		nodeVector.reserve( 20 );

		if ( id == this -> id )
			nodeVector.push( const_cast< NodeT<T> * >( this ) );

		_getElementsById( &nodeVector, id );
		return nodeVector;
	}

	template<typename T>
	Vector< NodeT<T> * > NodeT<T>::getElementsByName( const T & name ) const {
		Vector< NodeT<T> * > nodeVector;
		nodeVector.reserve( 20 );

		if ( name == this -> name )
			nodeVector.push( const_cast< NodeT<T> * >( this ) );

		_getElementsByName( &nodeVector, name );
		return nodeVector;
	}

	template<typename T>
	typename Vector< NodeT<T> * >::Size NodeT<T>::getNbChildren() const {
		return this -> childrenVector.getSize();
	}

	template<typename T>
	typename Vector< ParamT<T> * >::Size NodeT<T>::getNbParams() const {
		return this -> paramsVector.getSize();
	}

	template<typename T>
	void NodeT<T>::addChild( NodeT<T> * child ) {
		if ( this -> type == Type::Text ) {
			if ( child -> getType() == Type::Text ) {
				NodeTextT<T> * nodeTextThis( this -> toText() );
				NodeTextT<T> * nodeTextChild( child -> toText() );

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

	template<typename T>
	void NodeT<T>::_clear() {
		_unload();

		this -> name.clear();
		this -> id.clear();

		this -> paramsMap.clear();
		this -> paramsVector.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();
	}

	template<typename T>
	void NodeT<T>::_unload() {
		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			delete this -> paramsVector.getValueIt( it );
		}
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			NodeT<T> * node( this -> childrenVector.getValueIt( it ) );
			switch ( node->getType() ) {
				case NodeT<T>::Type::Text:
				{
					NodeTextT<T> * nodeText( ( NodeTextT<T> * ) node );
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

	template<typename T>
	const Vector< NodeT<T> * > NodeT<T>::getChild( const T & name ) const {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return NULL;
	}

	template<typename T>
	Vector< NodeT<T> * > NodeT<T>::getChild( const T & name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return NULL;
	}

	template<typename T>
	const NodeT<T> * NodeT<T>::getChild( typename Vector< NodeT<T> * >::Size i ) const {
		return const_cast< NodeT<T> * >( this ) -> getChild( i );
	}

	template<typename T>
	NodeT<T> * NodeT<T>::getChild( typename Vector< NodeT<T> * >::Size i ) {
		if ( i < this->childrenVector.getSize() ) {
			return this->childrenVector.getValueI( i );
		} else {
			return NULL;
		}
	}

	template<typename T>
	bool NodeT<T>::deleteChild( NodeT<T> * child ) {
		NodeT<T> * childRemoved( removeChild( child ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename T>
	bool NodeT<T>::deleteChild( typename Vector< NodeT<T> * >::Size i ) {
		NodeT<T> * childRemoved( removeChild( i ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename T>
	NodeT<T> * NodeT<T>::removeChild( NodeT<T> * child ) {
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

	template<typename T>
	NodeT<T> * NodeT<T>::removeChild( typename Vector< NodeT<T> * >::Size i ) {
		if ( i >= this -> childrenVector.getSize() ) {
			return NULL;
		} else {
			NodeT<T> * child( this -> childrenVector[ i ] );
			this -> childrenVector.eraseIndex( i );
			this -> childrenMap.eraseFirst( child -> getName(), child );
			if ( child -> getId().getSize() )
				this -> childrenByIdMap.eraseFirst( child -> getId(), child );
			child -> parent = NULL;
			return child;
		}
	}

	template<typename T>
	bool NodeT<T>::writeXML( std::fstream * fileStreamP, unsigned int tabs ) const {
		std::fstream & fileStream( *fileStreamP );
		
		_writeXML<std::fstream, char>( fileStream, tabs );

		return !( fileStreamP -> bad() );
	}

	template<typename T>
	template<typename C>
	bool NodeT<T>::writeXML( C & str, unsigned int tabs ) const {
		_writeXML<C, C::ElemType>( str, tabs );
		return true;
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeT<T>::_readXML( const C ** buffer, const EndFunc & endFunc ) {
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

			if ( !NodeT<T>::_expectChar( &it, C( '<' ) ) ) return false;

			// We have an opening node or self closing
			auto beginIt( it );
			while ( true ) {
				if ( endFunc( it ) ) {
					error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
					return false;
				}
				if ( !functorNodeName( *it ) ) break;
				it++;
			}
			// Call the constructor (pointer, size).
			T nodeName( beginIt, T::Size( it - beginIt ) );

			this -> setName( nodeName );

			while ( _parseParameter( &it, endFunc ) );

			if ( ( *it ) == C( '/' ) ) {
				// Self closing node
				it++;
				while ( functorSpace( *it ) ) it++;

				return NodeT<T>::_expectChar( &it, C( '>' ) );
			} else {
				while ( functorSpace( *it ) ) it++;
				if ( ( *it ) != C( '>' ) ) {
					error( TEXT( "[XML ERROR] : Expecting '>'." ) );
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
					error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
					return false;
				}
				if ( !functorNodeName( *it ) ) break;
				it++;
			}

			// Call the constructor (pointer, size).
			T nodeName( beginIt, T::Size( it - beginIt ) );

			while ( functorSpace( *it ) ) it++;

			if ( nodeName != this -> getName() ) {
				error( String::format( TEXT( "[XML ERROR] : Closing node do not match. \"%\" != \"%\"." ), this -> getName(), nodeName ) );
				// SYNTAX ERROR
				return false;
			} else {
				return NodeT<T>::_expectChar( &it, C( '>' ) );
			}
		}
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeT<T>::appendXML( const C ** buffer, const EndFunc & endFunc ) {
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
					T textContent( beginIt, T::Size( endIt - beginIt ) );
					NodeTextT<T> * nodeText( new NodeTextT<T>( textContent ) );

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
					NodeT<T> * newNode( new NodeT<T>() );
					this -> addChild( newNode );

					if ( !newNode -> _readXML( &it, endFunc ) )
						return false;
				}
			} else {
				error( TEXT( "[XML ERROR] : Expected '<'." ) );
				return false;
			}
		}
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeT<T>::appendXML( const C * buffer, const EndFunc & endFunc ) {
		return appendXML( &buffer, endFunc );
	}

	template<typename T>
	bool NodeT<T>::appendXML( const T & str ) {
		const T::ElemType * buffer( str.toCString() );
		return appendXML<T::ElemType>( &buffer );
	}


	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeT<T>::_parseParameter( const C ** buffer, const EndFunc & endFunc ) {
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
				error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
				return false;
			}
			if ( !functorName( *it ) )
				break;
			it++;
		}

		if ( iteratorBegin != it ) {
			ParamT<T> * newParam( new ParamT<T>() );

			newParam -> setName( T( iteratorBegin, T::Size( it - iteratorBegin ) ) );

			if ( ( *it ) == C( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == C( '"' ) ) {
					( it )++; // Skip the quotes too

					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorValue( *it ) )
							break;
						it++;
					}
					newParam -> setValue( T( iteratorBegin, T::Size( it - iteratorBegin ) ) );

					if ( ( *it ) == C( '"' ) ) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorName( *it ) )
							break;
						it++;
					}
					newParam -> setValue( T( iteratorBegin, T::Size( it - iteratorBegin ) ) );
				}

			}
			this -> addParam( newParam );
			return true;
		}
		return false;
	}

	template<typename T>
	template<typename C>
	C NodeT<T>::toString( unsigned int indent ) const {
		C newString;
		newString.reserve( 128 );

		_writeXML<C, C::ElemType>( newString, indent );
		return newString;
	}

	template<typename T>
	bool NodeT<T>::read( std::fstream * fileStream ) {
		if ( getType() == Type::Text )
			return this -> toText() -> read( fileStream );
		else
			return _read( fileStream );
	}

	template<typename T>
	bool NodeT<T>::_read( std::fstream * fileStream ) {
		_unload();
		this -> paramsMap.clear();
		this -> paramsVector.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();

		if ( !IO::read( fileStream, &this -> name ) ) {
			_clear();
			return false;
		}

		if ( !IO::read( fileStream, &this -> id ) ) {
			_clear();
			return false;
		}

		// Read the Params
		Vector< ParamT<T> * >::Size nbParams;
		if ( !IO::read( fileStream, &nbParams ) ) {
			_clear();
			return false;
		}
		nbParams = Math::min( nbParams, Vector< ParamT<T> * >::Size( 1000 ) );
		for ( Vector< ParamT<T> * >::Size i( 0 ); i < nbParams; i++ ) {
			ParamT<T> * newParam( new ParamT<T>() );
			if ( !IO::read( fileStream, newParam ) ) {
				delete newParam;
				_clear();
				return false;
			}
			addParam( newParam );
		}

		// Read the children
		Vector< NodeT<T> * >::Size nbChilds;
		if ( !IO::read( fileStream, &nbChilds ) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min( nbChilds, Vector< NodeT<T> * >::Size( 1000 ) );
		for ( Vector< NodeT<T> * >::Size i( 0 ); i < nbChilds; i++ ) {
			Type newNodeType;
			if ( !IO::read( fileStream, &newNodeType ) ) {
				_clear();
				return false;
			}
			if ( newNodeType == Type::Text ) {
				NodeTextT<T> * newNode( new NodeTextT<T>() );
				newNode -> parent = this;
				if ( !IO::read( fileStream, newNode ) ) {
					delete newNode;
					_clear();
					return false;
				}
				this -> childrenVector.push( newNode );
				this -> childrenMap.insert( newNode -> getName(), newNode );
			} else {
				NodeT<T> * newNode( new NodeT() );
				newNode -> parent = this;
				if ( !IO::read( fileStream, newNode ) ) {
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

	template<typename T>
	bool NodeT<T>::_setChildName( NodeT<T> * child, const T & name ) {
		if ( this -> childrenMap.eraseFirst( child -> getName(), child ) ) {
			child -> name = name;
			this -> childrenMap.insert( child -> getName(), child );
			return true;
		} else {
			return false;
		}
	}

	template<typename T>
	bool NodeT<T>::_setChildId( NodeT<T> * child, const T & id ) {
		this -> childrenByIdMap.eraseFirst( child -> getId(), child );
		child -> id = id;
		if ( id.getSize() )
			this -> childrenByIdMap.insert( child -> getId(), child );
		return true;
	}

	template<typename T>
	void NodeT<T>::_getElementsById( Vector < NodeT<T> * > * nodeVector, const T & id ) const {
		const Vector < NodeT<T> * > * vectorFounded( this -> childrenByIdMap[ id ] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			this -> childrenVector.getValueIt( it ) -> _getElementsById( nodeVector, id );
		}
	}

	template<typename T>
	void NodeT<T>::_getElementsByName( Vector < NodeT<T> * > * nodeVector, const T & name ) const {
		const Vector < NodeT<T> * > * vectorFounded( this -> childrenMap[ name ] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			this -> childrenVector.getValueIt( it ) -> _getElementsByName( nodeVector, name );
		}
	}

	template<typename T>
	bool NodeT<T>::write( std::fstream * fileStream ) const {
		if ( getType() == Type::Text )
			return this -> toText() -> write( fileStream );
		else
			return _write( fileStream );
	}

	template<typename T>
	bool NodeT<T>::_write( std::fstream * fileStream ) const {


		if ( !IO::write( fileStream, &this -> name ) )
			return false;
		if ( !IO::write( fileStream, &this -> id ) )
			return false;

		Vector< ParamT<T> * >::Size nbParams( this -> paramsVector.getSize() );
		Vector< NodeT<T> * >::Size nbChilds( this -> childrenVector.getSize() );

		if ( !IO::write( fileStream, &nbParams ) )
			return false;
		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			if ( !IO::write( fileStream, this -> paramsVector.getValueIt( it ) ) )
				return false;
		}

		if ( !IO::write( fileStream, &nbChilds ) )
			return false;
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			Type type( this -> childrenVector.getValueIt( it ) -> getType() );
			if ( !IO::write( fileStream, &type ) )
				return false;
			if ( !IO::write( fileStream, this -> childrenVector.getValueIt( it ) ) )
				return false;
		}

		return true;
	}

	template<typename T>
	T NodeT<T>::toStringDebug( unsigned int indent ) const {
		T newString;
		newString.reserve( 100 );

		for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
			newString << T::ElemType( '\t' );
		}

		newString << T::ElemType( '<' );
		newString << this -> name;

		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			newString << T::ElemType( ' ' );
			newString << this -> paramsVector.getValueIt( it ) -> toString();
		}

		newString << T::ElemType( '>' );
		newString << T::ElemType( '\n' );

		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			newString << this -> childrenVector.getValueIt( it ) -> toStringDebug( indent + 1 );
			newString << T::ElemType( '\n' );
		}

		if ( this -> type == Type::Text ) {
			for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
				newString << T::ElemType( '\t' );
			}

			newString << this -> toText() -> getValue();
			newString << T::ElemType( '\n' );
		}

		for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
			newString << T::ElemType( '\t' );
		}

		newString << T::ElemType( '<' );
		newString << T::ElemType( '/' );
		newString << this -> name;
		newString << T::ElemType( '>' );

		return newString;
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeT<T>::_writeXML( C & o, unsigned int tabs ) const {
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
				NodeT<T> * child( this -> childrenVector.getValueIt( it ) );
				if ( child -> getType() == NodeT<T>::Type::Text && getNbChildren() == 1 ) {
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

	template<typename T>
	template<typename C>
	bool NodeT<T>::_expectChar( const C ** buffer, const C & c ) {
		const C *& it( *buffer );

		if ( ( *it ) == c ) {
			it++;
			return true;
		} else {
			error( String::format(TEXT( "[XML ERROR] : Expected '%'." ), c) );
			return false;
		}

	}






	/************************************************************************/
	/* NodeTextT<T>                                                         */
	/************************************************************************/

	template<typename T>
	bool NodeTextT<T>::writeXML( std::fstream * fileStreamP ) const {
		std::fstream & fileStream( *fileStreamP );

		_writeXML<std::fstream, char>( fileStream, 0 );

		return !( fileStreamP -> bad() );
	}

	template<typename T>
	bool NodeTextT<T>::read( std::fstream * fileStream ) {
		this -> value.clear();

		/*
		if ( !NodeT<T>::_read( fileStream ) ) {
			return false;
		}
		*/
		if ( !IO::read( fileStream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename T>
	bool NodeTextT<T>::write( std::fstream * fileStream ) const {
		/*
		if ( !NodeT<T>::_write( fileStream ) )
			return false;
		*/
		if ( !IO::write( fileStream, &this -> value ) )
			return false;
		return true;
	}

	template<typename T>
	void NodeTextT<T>::_clear() {
		NodeT<T>::_clear();
		this -> value.clear();
	}

	template<typename T>
	NodeTextT<T>::NodeTextT() : NodeT<T>( T( "#text" ), NodeT<T>::Type::Text ) {

	}

	template<typename T>
	NodeTextT<T>::NodeTextT( const T & value ) : NodeT<T>( T( "#text" ), NodeT<T>::Type::Text ),
		value( value ) {

	}

	template<typename T>
	NodeTextT<T>::NodeTextT( const NodeTextT<T> & node ) : NodeT( node ),
		value( node.value ) {

	}

	template<typename T>
	NodeTextT<T>::NodeTextT( NodeTextT<T> && node ) : NodeT( Utility::toRValue( node ) ),
		value( Utility::toRValue( node.value ) ) {

	}

	template<typename T>
	NodeTextT<T> & NodeTextT<T>::operator=( const NodeTextT<T> & node ) {
		NodeT<T>::operator=( node );
		this -> value = node.value;
		return *this;
	}

	template<typename T>
	NodeTextT<T> & NodeTextT<T>::operator=( NodeTextT<T> && node ) {
		NodeT<T>::operator=( Utility::toRValue( node ) );
		this -> value = Utility::toRValue( node.value );
		return *this;
	}

	template<typename T>
	const T & NodeTextT<T>::getValue() const {
		return this -> value;
	}

	template<typename T>
	T & NodeTextT<T>::getValue() {
		return this -> value;
	}

	template<typename T>
	void NodeTextT<T>::setValue( const T & value ) {
		this -> value = value;
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeTextT<T>::_writeXML( C & o, unsigned int tabs ) const {
		for ( unsigned int i( 0 ); i < tabs; i++ )
			o << Elem( '\t' );
		o << this -> value;
	}

	template<typename T>
	template<typename C>
	C NodeTextT<T>::toString( unsigned int indent ) const {
		C newString;
		newString.reserve( 128 );

		_writeXML<C, C::ElemType>( newString, indent );
		return newString;
	}

}
