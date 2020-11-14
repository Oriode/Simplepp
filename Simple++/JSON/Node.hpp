namespace JSON {

	template<typename T>
	NodeT<T>::NodeT( Type type ) :
		type( type ),
		parent( NULL ) {

	}

	template<typename T>
	NodeT<T>::NodeT( const T & name, Type type ) :
		name( name ),
		type( type ),
		parent( NULL ) {

	}

	template<typename T>
	NodeT<T>::NodeT( const NodeT<T> & node ) :
		name( node.name ),
		type( node.type ),
		parent( NULL ) {
		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<T> * newNode( new NodeT<T>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
	}

	template<typename T>
	NodeT<T>::NodeT( NodeT<T> && node ) :
		name( Utility::toRValue( node.name ) ),
		type( Utility::toRValue( node.type ) ),
		childrenMap( Utility::toRValue( node.childrenMap ) ),
		childrenVector( Utility::toRValue( node.childrenVector ) ),
		parent( Utility::toRValue( node.parent ) ) {
		node.childrenVector.clear();
	}

	template<typename T>
	NodeT<T>::~NodeT() {
		_unload();
	}

	template<typename T>
	NodeT<T> & NodeT<T>::operator=( const NodeT<T> & node ) {
		this -> name = node.name;
		this -> type = node.type;
		this -> parent = NULL;

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<T> * newNode( new NodeT<T>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		return *this;
	}

	template<typename T>
	NodeT<T> & NodeT<T>::operator=( NodeT<T> && node ) {
		this -> name = Utility::toRValue( node.name );
		this -> type = Utility::toRValue( node.type );
		this -> childrenVector = Utility::toRValue( node.childrenVector );
		this -> childrenMap = Utility::toRValue( node.childrenMap );
		this -> parent = Utility::toRValue( node.parent );

		node.childrenVector.clear();

		return *this;
	}

	template<typename T>
	typename NodeT<T>::Type NodeT<T>::getType() const {
		return this -> type;
	}

	template<typename T>
	const NodeValueT<T> * NodeT<T>::toValue() const {
		return ( static_cast< const NodeValueT<T> * >( this ) );
	}

	template<typename T>
	NodeValueT<T> * NodeT<T>::toValue() {
		return ( static_cast< NodeValueT<T> * >( this ) );
	}

	template<typename T>
	const NodeArrayT<T> * NodeT<T>::toArray() const {
		return ( static_cast< const NodeArrayT<T> * >( this ) );
	}

	template<typename T>
	NodeArrayT<T> * NodeT<T>::toArray() {
		return ( static_cast< NodeArrayT<T> * >( this ) );
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
		return this -> value;
	}

	template<typename T>
	void NodeT<T>::setValue( const T & value ) {
		if ( getType() != Type::Value ) {
			if ( this -> childrenVector.getSize() == 0 ) {
				this -> type = Type::Value;
			} else {
				error( TEXT( "Trying to set a value to a JSON node having at least one child." ) );
				return;
			}
		}
		this -> value = value;
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
	void NodeT<T>::addChild( NodeT<T> * child ) {
		if ( this -> type == Type::Value ) {
			if ( this -> parent ) {
				this -> parent -> addChild( child );
			} else {
				error( TEXT( "Trying to add a child on a root Value Node." ) );
			}
		} else {
			if ( child != NULL ) {
				if ( child -> parent )
					child -> parent -> removeChild( child );

				if ( child -> getName().getSize() ) {
					this -> childrenMap.insert( child -> getName(), child );
				}
			} else {
				child = new NodeT<T>( Type::Null );
			}

			child -> parent = this;
			
			this -> childrenVector.push( child );
		}
	}

	template<typename T>
	void NodeT<T>::_clear() {
		_unload();

		this -> name.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();
	}

	template<typename T>
	void NodeT<T>::_unload() {
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			NodeT<T> * node( this -> childrenVector.getValueIt( it ) );

			if ( node ) {
				delete node;
				continue;
				switch ( node->getType() ) {
					case NodeT<T>::Type::Value:
					{
						NodeValueT<T> * nodeValue( (NodeValueT<T> *) node );
						delete nodeValue;
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
			if ( child -> getName().getSize() )
				this -> childrenMap.eraseFirst( child -> getName(), child );
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
			if ( child ) {
				if ( child -> getName().getSize() )
					this -> childrenMap.eraseFirst( child -> getName(), child );
				child -> parent = NULL;
			}
			
			return child;
		}
	}

	template<typename T>
	bool NodeT<T>::writeJSON( std::fstream * fileStreamP, unsigned int indent ) const {
		std::fstream & fileStream( *fileStreamP );

		_writeJSON<std::fstream, char>( fileStream, indent );

		return !( fileStreamP -> bad() );
	}

	template<typename T>
	template<typename C>
	bool NodeT<T>::writeJSON( C & str, unsigned int indent ) const {
		return _writeJSON<C, C::ElemType>( str, indent );
	}

	template<typename T>
	template<typename C>
	C NodeT<T>::toString( unsigned int indent ) const {
		C newString;
		newString.reserve( 128 );

		_writeJSON<C, C::ElemType>( newString, indent );
		return newString;
	}

	template<typename T>
	bool NodeT<T>::read( std::fstream * fileStream ) {
		if ( getType() == Type::Value )
			return this -> toValue() -> read( fileStream );
		else
			return _read( fileStream );
	}

	template<typename T>
	bool NodeT<T>::_read( std::fstream * fileStream ) {
		_unload();

		this -> childrenMap.clear();
		this -> childrenVector.clear();

		if ( !IO::read( fileStream, &this -> name ) ) {
			_clear();
			return false;
		}

		// Read the children
		Vector< NodeT<T> * >::Size nbChilds;
		if ( !IO::read( fileStream, &nbChilds ) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min( nbChilds, Vector< NodeT<T> * >::Size( 1000 ) );
		for ( Vector< NodeT<T> * >::Size i( 0 ); i < nbChilds; i++ ) {
			bool isNull;
			if ( !IO::read( fileStream, &isNull ) ) {
				_clear();
				return false;
			}
			if ( isNull ) {
				this -> childrenVector.push( NULL );
			} else {
				Type newNodeType;
				if ( !IO::read( fileStream, &newNodeType ) ) {
					_clear();
					return false;
				}
				
				NodeT<T> * newNode( new NodeT<T>() );
				newNode -> parent = this;
				if ( !IO::read( fileStream, newNode ) ) {
					delete newNode;
					_clear();
					return false;
				}
				this -> childrenVector.push( newNode );
				if ( newNode -> getName().getSize() )
					this -> childrenMap.insert( newNode -> getName(), newNode );
			}
		}

		return true;
	}

	template<typename T>
	bool NodeT<T>::_setChildName( NodeT<T> * child, const T & name ) {
		if ( child -> getName().getSize() ) {
			if ( !this -> childrenMap.eraseFirst( child -> getName(), child ) ) {
				return false;
			}
		}
		child -> name = name;
		if ( child -> getName().getSize() )
			this -> childrenMap.insert( child -> getName(), child );
		return true;
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
			NodeT<T> * child( this -> childrenVector.getValueIt( it ) );
			this -> childrenVector.getValueIt( it ) -> _getElementsByName( nodeVector, name );
		}
	}

	template<typename T>
	bool NodeT<T>::write( std::fstream * fileStream ) const {
		if ( getType() == Type::Value )
			return this -> toValue() -> write( fileStream );
		else
			return _write( fileStream );
	}

	template<typename T>
	bool NodeT<T>::_write( std::fstream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> name ) )
			return false;

		Vector< NodeT<T> * >::Size nbChilds( this -> childrenVector.getSize() );

		if ( !IO::write( fileStream, &nbChilds ) )
			return false;
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			bool isNull( *it == NULL );
			if ( !IO::write( fileStream, &isNull ) )
				return false;
			if ( !isNull ) {
				Type type( this -> childrenVector.getValueIt( it ) -> getType() );
				if ( !IO::write( fileStream, &type ) )
					return false;
				if ( !IO::write( fileStream, this -> childrenVector.getValueIt( it ) ) )
					return false;
			}
		}

		return true;
	}

	template<typename T>
	T NodeT<T>::toStringDebug( unsigned int indent ) const {
		T newString;
		newString.reserve( 128 );

		for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
			newString << T::ElemType( '\t' );
		}

		if ( this -> name.getSize() ) {
			newString << T::ElemType( '"' );
			newString << this -> name;
			newString << T::ElemType( '"' );
			newString << T::ElemType( ':' );
			newString << T::ElemType( ' ' );
		}

		if ( this -> type == Type::Value ) {
			// this -> toValue() -> _writeJSON<T, T::ElemType>( newString, 0 );
			newString << T::ElemType( '"' );
			newString << this -> getValue();
			newString << T::ElemType( '"' );
		} else {
			if ( this -> type == Type::Array ) {
				newString << T::ElemType( '[' );
			} else {
				newString << T::ElemType( '{' );
			}

			newString << T::ElemType( '\n' );

			for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
				if ( it != this -> childrenVector.getBegin() ) {
					newString << T::ElemType( ',' );
					newString << T::ElemType( '\n' );
				}

				NodeT<T> * child( this -> childrenVector.getValueIt( it ) );
				if ( child -> getType() == Type::Null ) {

					for ( unsigned int i( 0 ) ; i < indent + 1 ; i++ ) {
						newString << T::ElemType( '\t' );
					}

					newString << T::ElemType( 'n' );
					newString << T::ElemType( 'u' );
					newString << T::ElemType( 'l' );
					newString << T::ElemType( 'l' );
				} else {
					newString << child -> toStringDebug( indent + 1 );
				}
			}

			newString << T::ElemType( '\n' );

			for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
				newString << T::ElemType( '\t' );
			}

			if ( this -> type == Type::Array ) {
				newString << T::ElemType( ']' );
			} else {
				newString << T::ElemType( '}' );
			}
		}

		return newString;
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeT<T>::_writeJSON( C & o, unsigned int indent ) const {

		for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
			o << Elem( '\t' );
		}

		if ( this -> name.getSize() ) {
			o << Elem( '"' );
			o << this -> name;
			o << Elem( '"' );
			o << Elem( ':' );
			o << Elem( ' ' );
		}

		if ( getType() == Type::Value ) {
			o << Elem( '"' );
			o << this -> getValue();
			o << Elem( '"' );
		} else if (getType() == Type::Null ){
			o << Elem( 'n' );
			o << Elem( 'u' );
			o << Elem( 'l' );
			o << Elem( 'l' );
		} else {
			if ( getType() == Type::Array ) {
				o << Elem( '[' );
			} else {
				o << Elem( '{' );
			}

			if (this -> childrenVector.getSize() )
				o << Elem( '\n' );

			for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
				if ( it != this -> childrenVector.getBegin() ) {
					o << Elem( ',' );
					o << Elem( '\n' );
				}

				NodeT<T> * child( this -> childrenVector.getValueIt( it ) );
				child -> _writeJSON( o, indent + 1 );
			}

			if ( this -> childrenVector.getSize() ) {
				o << Elem( '\n' );
				o << Elem( '\t' );
			}

			if ( getType() == Type::Array ) {
				o << Elem( ']' );
			} else {
				o << Elem( '}' );
			}
		}

		

	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeT<T>::readJSON( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorNodeName {
			bool operator()( const C & c ) { return c != C( '"' ) && c != C( '\t' ) && c != C( '\n' ); }
		};
		struct FunctorContentQuote {
			bool operator()( const C & c ) { return c != C( '"' ); }
		};
		struct FunctorContent {
			bool operator()( const C & c ) { return c != C( ',' ) && c != C( '}' ) && c != C( ']' ) && c != C( ' ' ); }
		};
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		struct FunctorNoSpace {
			bool operator()( const C & c ) { return c != C( '<' ) && c != C( '\n' ) && c != C( '\t' ) && c != C( ' ' ); }
		};
		static FunctorNodeName functorNodeName;
		static FunctorContentQuote functorContentQuote;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		static const T nullString( "null" );

		const C *& it( *buffer );

		// Skip spaces.
		while ( functorSpace( *it ) ) it++;

		if ( (*it ) == C('{') ) {
			// Object Node.
			it++;

			while ( true ) {
				// Skip spaces.
				while ( functorSpace( *it ) ) it++;

				if ( ( *it ) == C( '"' ) ) {
					it++;

					const C * beginIt( it );
					while ( true ) {
						if ( endFunc( it ) ) {
							error( TEXT( "[JSON Error] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorNodeName( *it ) )
							break;
						it++;
					}

					// If a name was founded.
					if ( beginIt != it ) {
						// We founded a name.
						T nodeName( beginIt, T::Size( it - beginIt ) );


						if ( !_expectChar( &it, C( '"' ) ) ) return false;
						while ( functorSpace( *it ) ) it++;
						if ( !_expectChar( &it, C( ':' ) ) ) return false;
						while ( functorSpace( *it ) ) it++;

						NodeT<T> * newNode( new NodeT<T>( nodeName, Type::Object ) );
						this -> addChild( newNode );

						if ( !newNode -> readJSON( &it, endFunc ) ) {
							return false;
						}
					} else {
						error( TEXT( "Expected property name." ) );
						return false;
					}

					while ( functorSpace( *it ) ) it++;

					if ( ( *it ) == C( ',' ) ) {
						it++;
						while ( functorSpace( *it ) ) it++;
						continue;
					} else {
						if ( !_expectChar( &it, C( '}' ) ) ) return false;
						return true;
					}
				} else {
					if ( !_expectChar( &it, C( '}' ) ) ) return false;
					return true;
				}
			}
		} else if ( ( *it ) == C( '[' ) ) {
			this -> type = Type::Array;
			it++;
			while ( functorSpace( *it ) ) it++;
			// TODO : parse array.
		} else {
			// Value node.
			if ( ( *it ) == C( '"' ) ) {
				// Quote value.
				it++;
				const C * beginIt( it );
				while ( true ) {
					if ( endFunc( it ) ) {
						error( TEXT( "[JSON Error] : Unexpected buffer end." ) );
						return false;
					}
					if ( !functorContentQuote(*it) ) {
						if ( ( *( it - 1 ) ) != C( '\\' ) ) {
							break;
						}
					}
					it++;
				}

				T nodeValue( beginIt, T::Size( it - beginIt ) );
				this -> value = nodeValue;
				this -> type = Type::Value;

				if ( !_expectChar( &it, C( '"' ) ) ) return false;
			} else {
				// Value without quote.
				
				const C * beginIt( it );
				while ( true ) {
					if ( endFunc( it ) ) {
						error( TEXT( "[JSON Error] : Unexpected buffer end." ) );
						return false;
					}
					if ( !functorContent( *it ) )
						break;
					it++;
				}

				T nodeValue( beginIt, T::Size( it - beginIt ) );

				if ( nodeValue == nullString ) {
					this -> type = Type::Null;
				} else {
					this -> value = nodeValue;
					this -> type = Type::Value;
				}
			}
		}

		return true;


		if ( ( *it ) == C( '[' ) ) {
			this -> type = Type::Array;
			it++;
			while ( functorSpace( *it ) ) it++;
		} else if ( ( *it ) == C( '{' ) ) {
			// Append new Object Node !
			NodeT<T> * newNode( new NodeT<T>( Type::Object ) );
			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return false;
			}
		}

		
		if ( ( *it ) == C( '}' ) ) {
			if ( getType() != Type::Object ) {
				error( TEXT( "[JSON Error] : Trying to close an object in a non-object node." ) );
				return false;
			} else {
				// Closing Object Node.
				it++;
				return true;
			}
		} else if ( ( *it ) == C( ']' ) ) {
			if ( getType() != Type::Array ) {
				error( TEXT( "[JSON Error] : Trying to close an array in a non-array node." ) );
				return false;
			} else {
				// Closing Object Node.
				it++;
				return true;
			}
		} else if ( ( *it ) == C( '{' ) ) {
			// Append new Object Node !
			NodeT<T> * newNode( new NodeT<T>( Type::Object ) );
			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return false;
			}
		} else if ( ( *it ) == C( '[' ) ) {
			// Append a new Array Node !
			NodeT<T> * newNode( new NodeT<T>( Type::Array ) );
			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return false;
			}
		} else {
			// Value.
			
			if ( ( *it ) == C( '"' ) ) {
				// Quote value.
				it++;
				const C * beginIt( it );
				while ( true ) {
					if ( endFunc( it ) ) {
						error( TEXT( "[JSON Error] : Unexpected buffer end." ) );
						return false;
					}
					if ( ( *it ) == C( '"' ) ) {
						if ( ( *( it - 1 ) ) != C( '\\' ) ) {
							break;
						}
					}
					it++;
				}

				T nodeValue( beginIt, T::Size( it - beginIt ) );
				this -> setValue( value );
				it++;
			}

		}

		
		

		


		return true;
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeT<T>::readJSON( const C * buffer, const EndFunc & endFunc ) {
		return readJSON( &buffer, endFunc );
	}

	template<typename T>
	template<typename C>
	bool NodeT<T>::_expectChar( const C ** buffer, const C & c ) {
		const C *& it( *buffer );

		if ( ( *it ) == c ) {
			it++;
			return true;
		} else {
			error( String::format( TEXT( "[XML ERROR] : Expected '%'." ), c ) );
			return false;
		}

	}




	/************************************************************************/
	/* NodeValueT<T>                                                         */
	/************************************************************************/

	template<typename T>
	bool NodeValueT<T>::writeJSON( std::fstream * fileStreamP ) const {
		std::fstream & fileStream( *fileStreamP );

		_writeJSON<std::fstream, char>( fileStream, 0 );

		return !( fileStreamP -> bad() );
	}

	template<typename T>
	bool NodeValueT<T>::read( std::fstream * fileStream ) {
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
	bool NodeValueT<T>::write( std::fstream * fileStream ) const {
		/*
		if ( !NodeT<T>::_write( fileStream ) )
			return false;
		*/
		if ( !IO::write( fileStream, &this -> value ) )
			return false;
		return true;
	}

	template<typename T>
	void NodeValueT<T>::_clear() {
		NodeT<T>::_clear();
		this -> value.clear();
	}

	template<typename T>
	NodeValueT<T>::NodeValueT() : NodeT<T>( NodeT<T>::Type::Value ) {

	}

	template<typename T>
	NodeValueT<T>::NodeValueT( const T & value ) : NodeT<T>( NodeT<T>::Type::Value ),
		value( value ) {

	}

	template<typename T>
	NodeValueT<T>::NodeValueT( const T & name, const T & value ) :
		NodeT<T>( name, NodeT<T>::Type::Value ),
		value( value ) {

	}

	template<typename T>
	NodeValueT<T>::NodeValueT( const NodeValueT<T> & node ) : NodeT( node ),
		value( node.value ) {

	}

	template<typename T>
	NodeValueT<T>::NodeValueT( NodeValueT<T> && node ) : NodeT( Utility::toRValue( node ) ),
		value( Utility::toRValue( node.value ) ) {

	}

	template<typename T>
	NodeValueT<T> & NodeValueT<T>::operator=( const NodeValueT<T> & node ) {
		NodeT<T>::operator=( node );
		this -> value = node.value;
		return *this;
	}

	template<typename T>
	NodeValueT<T> & NodeValueT<T>::operator=( NodeValueT<T> && node ) {
		NodeT<T>::operator=( Utility::toRValue( node ) );
		this -> value = Utility::toRValue( node.value );
		return *this;
	}

	template<typename T>
	const T & NodeValueT<T>::getValue() const {
		return this -> value;
	}

	template<typename T>
	void NodeValueT<T>::setValue( const T & value ) {
		this -> value = value;
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeValueT<T>::_writeJSON( C & o, unsigned int indent ) const {
		o << this -> value;
	}

	template<typename T>
	template<typename C>
	C NodeValueT<T>::toString( unsigned int indent ) const {
		C newString;
		newString.reserve( 128 );

		_writeJSON<C, C::ElemType>( newString, indent );
		return newString;
	}





	/************************************************************************/
	/* NodeArrayT<T>                                                         */
	/************************************************************************/

	template<typename T>
	bool NodeArrayT<T>::writeJSON( std::fstream * fileStreamP ) const {
		std::fstream & fileStream( *fileStreamP );

		_writeJSON<std::fstream, char>( fileStream, 0 );

		return !( fileStreamP -> bad() );
	}

	template<typename T>
	void NodeArrayT<T>::_clear() {
		NodeT<T>::_clear();
		Vector<NodeT<T>>::clear();
	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT() : NodeT<T>( NodeT<T>::Type::Array ) {

	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( const Vector<NodeT<T>> & v ) : NodeT<T>( NodeT<T>::Type::Array ), Vector<NodeT<T>>( v ) {

	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( const T & name, const Vector<NodeT<T>> & v ) :
		NodeT<T>( name, NodeT<T>::Type::Value ),
		Vector<NodeT<T>>( v ) {

	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( const NodeArrayT<T> & node ) : NodeT( node ), Vector<NodeT<T>>( node ) {

	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( NodeArrayT<T> && node ) : NodeT( Utility::toRValue( node ) ), Vector<NodeT<T>>( Utility::toRValue( node.value ) ) {

	}

	template<typename T>
	NodeArrayT<T> & NodeArrayT<T>::operator=( const NodeArrayT<T> & node ) {
		NodeT<T>::operator=( node );
		Vector<NodeT<T>>::operator=( node );
		return *this;
	}

	template<typename T>
	NodeArrayT<T> & NodeArrayT<T>::operator=( NodeArrayT<T> && node ) {
		NodeT<T>::operator=( Utility::toRValue( node ) );
		Vector<NodeT<T>>::operator=( Utility::toRValue( node ) );
		return *this;
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeArrayT<T>::_writeJSON( C & o, unsigned int indent ) const {

		/*
		o << Elem( '[' );
		o << Elem( ' ' );

		for ( typename Vector<NodeT<T>>::Iterator & it( this->getBegin() ) ; it != this->getEnd(); this->iterate( &it ) ) {
			const T & v( this ->getValueIt( it ) );

			if ( it != this -> getBegin() ) {
				o << Elem( ',' );
				o << Elem( ' ' );
			}

			o << v;
		}

		o << Elem( ' ' );
		o << Elem( ']' );

		return true;
		*/
	}

}