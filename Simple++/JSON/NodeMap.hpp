namespace JSON {

	template<typename S>
	NodeMapT<S>::NodeMapT() :
		NodeT<S>( Type::Map ) {

	}

	template<typename S>
	NodeMapT<S>::NodeMapT( const S& name ) :
		NodeT<S>( name, Type::Map ) {

	}

	template<typename S>
	NodeMapT<S>::NodeMapT( const S& name, const S& value ) :
		NodeT<S>( name, Type::Map ) {

	}

	template<typename S>
	NodeMapT<S>::NodeMapT( const NodeMapT<S>& node ) :
		NodeT<S>( node ) {
		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<S>* newNode( new NodeT<S>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
	}

	template<typename S>
	NodeMapT<S>::NodeMapT( NodeMapT<S>&& node ) :
		NodeT<S>( Utility::toRValue( node ) ),
		childrenMap( Utility::toRValue( node.childrenMap ) ),
		childrenVector( Utility::toRValue( node.childrenVector ) ) {
		node.childrenVector.clear();
	}

	template<typename S>
	NodeMapT<S>::~NodeMapT() {
		_unload();
	}

	template<typename S>
	NodeMapT<S>& NodeMapT<S>::operator=( const NodeMapT<S>& node ) {
		NodeT<S>::operator=( node );

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			NodeT<S>* newNode( new NodeT<S>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		return *this;
	}

	template<typename S>
	NodeMapT<S>& NodeMapT<S>::operator=( NodeMapT<S>&& node ) {
		NodeT<S>::operator=( Utility::toRValue( node ) );

		this -> childrenVector = Utility::toRValue( node.childrenVector );
		this -> childrenMap = Utility::toRValue( node.childrenMap );

		node.childrenVector.clear();

		return *this;
	}

	template<typename S>
	inline NodeT<S>* NodeMapT<S>::getElementByName( const S& name ) const {
		if ( name == this -> name )
			return const_cast< NodeMapT<S> * >( this );
		else
			return _getElementByName( name );
	}

	template<typename S>
	Vector< NodeT<S>* > NodeMapT<S>::getElementsByName( const S& name ) const {
		Vector< NodeT<S>* > nodeVector;
		nodeVector.reserve( 20 );

		if ( name == this -> name )
			nodeVector.push( const_cast< NodeMapT<S> * >( this ) );

		_getElementsByName( &nodeVector, name );
		return nodeVector;
	}

	template<typename S>
	Size NodeMapT<S>::getNbChildren() const {
		return this -> childrenVector.getSize();
	}

	template<typename S>
	void NodeMapT<S>::addChild( NodeT<S>* child ) {
		if ( child != NULL ) {
			if ( child -> getParent() )
				child -> getParent() -> removeChild( child );

			if ( child -> getName().getSize() ) {
				this -> childrenMap.insert( child -> getName(), child );
			}
		} else {
			child = new NodeT<S>( Type::Null );
		}

		child -> parent = this;

		this -> childrenVector.push( child );
	}

	template<typename S>
	inline void NodeMapT<S>::addChild( const S& name, NodeT<S>* child ) {
		child->setName( name );
		addChild( child );
	}

	template<typename S>
	void NodeMapT<S>::_clear() {
		_unload();

		this -> name.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();
	}

	template<typename S>
	void NodeMapT<S>::_unload() {
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			NodeT<S>* node( this -> childrenVector.getValueIt( it ) );

			delete node;
		}
	}

	template<typename S>
	const Vector<NodeT<S>*>& NodeMapT<S>::getChildren() const {
		return this ->childrenVector;
	}

	template<typename S>
	const Vector< NodeT<S>* >& NodeMapT<S>::getChildren( const S& name ) const {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return NodeT<S>::emptyVector;
	}

	/*
	template<typename S>
	Vector< NodeT<S> * > NodeMapT<S>::getChildren( const S & name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return Vector<NodeT<S> *>();
	}
	*/

	template<typename S>
	const NodeT<S>* NodeMapT<S>::getChild( const S& name ) const {
		return const_cast< NodeMapT<S> * >( this ) ->getChild( name );
	}

	template<typename S>
	NodeT<S>* NodeMapT<S>::getChild( const S& name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) {
			Vector<NodeT<S>* > childVector( *childP );
			if ( childVector.getSize() > 0 ) {
				return childVector[ 0 ];
			}
		}
		return NULL;
	}

	template<typename S>
	const NodeT<S>* NodeMapT<S>::getChild( Size i ) const {
		return const_cast< NodeMapT<S> * >( this ) -> getChild( i );
	}

	template<typename S>
	NodeT<S>* NodeMapT<S>::getChild( Size i ) {
		if ( i < this->childrenVector.getSize() ) {
			return this->childrenVector.getValueI( i );
		} else {
			return NULL;
		}
	}

	template<typename S>
	bool NodeMapT<S>::deleteChild( NodeT<S>* child ) {
		NodeT<S>* childRemoved( removeChild( child ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	bool NodeMapT<S>::deleteChild( Size i ) {
		NodeT<S>* childRemoved( removeChild( i ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	NodeT<S>* NodeMapT<S>::removeChild( NodeT<S>* child ) {
		if ( this -> childrenVector.eraseFirst( child ) ) {
			if ( child -> getName().getSize() )
				this -> childrenMap.eraseFirst( child -> getName(), child );
			child -> parent = NULL;
			return child;
		} else {
			return NULL;
		}
	}

	template<typename S>
	NodeT<S>* NodeMapT<S>::removeChild( Size i ) {
		if ( i >= this -> childrenVector.getSize() ) {
			return NULL;
		} else {
			NodeT<S>* child( this -> childrenVector[ i ] );
			this -> childrenVector.eraseI( i );
			if ( child ) {
				if ( child -> getName().getSize() )
					this -> childrenMap.eraseFirst( child -> getName(), child );
				child -> parent = NULL;
			}

			return child;
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeMapT<S>::read( Stream* stream, int verbose ) {
		_unload();

		this -> childrenMap.clear();
		this -> childrenVector.clear();

		if ( !NodeT<S>::_read( stream, verbose ) ) {
			_clear();
			return false;
		}


		// Read the children
		Size nbChilds;
		if ( !IO::read( stream, &nbChilds, verbose - 1 ) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min( nbChilds, Size( 1000 ) );
		for ( Size i( 0 ); i < nbChilds; i++ ) {
			bool isNull;
			if ( !IO::read( stream, &isNull, verbose - 1 ) ) {
				_clear();
				return false;
			}
			if ( isNull ) {
				this -> childrenVector.push( NULL );
			} else {
				Type newNodeType;
				if ( !IO::read( stream, &newNodeType, verbose - 1 ) ) {
					_clear();
					return false;
				}


				switch ( newNodeType ) {
					case Type::Map:
						{
							NodeMapT<S>* newNode( new NodeMapT<S>() );
							newNode -> parent = this;
							if ( !IO::read( stream, newNode, verbose - 1 ) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push( newNode );
							if ( newNode -> getName().getSize() )
								this -> childrenMap.insert( newNode -> getName(), newNode );
							break;
						}
					case Type::Value:
						{
							NodeValueT<S>* newNode( new NodeValueT<S>() );
							newNode -> parent = this;
							if ( !IO::read( stream, newNode, verbose - 1 ) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push( newNode );
							if ( newNode -> getName().getSize() )
								this -> childrenMap.insert( newNode -> getName(), newNode );
							break;
						}
					case Type::Array:
						{
							NodeArrayT<S>* newNode( new NodeArrayT<S>() );
							newNode -> parent = this;
							if ( !IO::read( stream, newNode, verbose - 1 ) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push( newNode );
							if ( newNode -> getName().getSize() )
								this -> childrenMap.insert( newNode -> getName(), newNode );
							break;
						}
					default:
						{
							NodeT<S>* newNode( new NodeT<S>( newNodeType ) );
							newNode -> parent = this;
							if ( !IO::read( stream, newNode, verbose - 1 ) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push( newNode );
							break;
						}
				}
			}
		}

		return true;
	}


	template<typename S>
	bool NodeMapT<S>::_setChildName( NodeT<S>* child, const S& oldName, const S& newName ) {
		if ( oldName.getSize() ) {
			if ( !this -> childrenMap.eraseFirst( oldName, child ) ) {
				return false;
			}
		}
		if ( child -> getName().getSize() )
			this -> childrenMap.insert( newName, child );
		return true;
	}

	template<typename S>
	void NodeMapT<S>::_getElementsByName( Vector < NodeT<S>* >* nodeVector, const S& name ) const {
		const Vector < NodeT<S>* >* vectorFounded( this -> childrenMap[ name ] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			NodeT<S>* child( this -> childrenVector.getValueIt( it ) );
			if ( child -> getType() == Type::Map ) {
				child -> toMap() -> _getElementsByName( nodeVector, name );
			}
		}
	}

	template<typename S>
	inline NodeT<S>* NodeMapT<S>::_getElementByName( const S& name ) const {
		const Vector < NodeT<S>* >* vectorFounded( this -> childrenMap[ name ] );
		if ( vectorFounded ) {
			return vectorFounded->getFirst();
		}

		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			NodeT<S>* child( this -> childrenVector.getValueIt( it ) );
			if ( child -> getType() == Type::Map ) {
				NodeT<S>* foundedElement( child -> toMap() -> _getElementByName( name ) );
				if ( foundedElement ) {
					return foundedElement;
				}
			}
		}
		return NULL;
	}

	template<typename S>
	template<typename Stream>
	bool NodeMapT<S>::write( Stream* stream ) const {
		if ( !NodeT<S>::_write( stream ) ) {
			return false;
		}


		Size nbChilds( this -> childrenVector.getSize() );

		if ( !IO::write( stream, &nbChilds ) )
			return false;
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			bool isNull( *it == NULL );
			if ( !IO::write( stream, &isNull ) )
				return false;
			if ( !isNull ) {
				Type type( this -> childrenVector.getValueIt( it ) -> getType() );
				if ( !IO::write( stream, &type ) )
					return false;
				if ( !IO::write( stream, this -> childrenVector.getValueIt( it ) ) )
					return false;
			}
		}

		return true;
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeMapT<S>::_writeJSON( C& o, unsigned int indent, bool beautyfy ) const {

		if ( this -> getName().getSize() ) {
			o << Elem( '"' );
			o << this -> getName();
			o << Elem( '"' );
			o << Elem( ':' );
			if ( beautyfy ) {
				o << Elem( ' ' );
			}
		}

		/*
		if ( getType() == Type::Value ) {
			o << Elem( '"' );
			o << this -> getValue();
			o << Elem( '"' );
		} else if ( getType() == Type::Null ) {
			o << Elem( 'n' );
			o << Elem( 'u' );
			o << Elem( 'l' );
			o << Elem( 'l' );
		} else if ( getType() == Type::Array ) {
			o << Elem( '[' );
			for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
				if ( it != this -> childrenVector.getBegin() ) {
					o << Elem( ',' );
					o << Elem( ' ' );
				}

				NodeMapT<S> * child( this -> childrenVector.getValueIt( it ) );
				child -> _writeJSON( o, indent );
			}
			o << Elem( ']' );

		} else {
		*/
		o << Elem( '{' );
		if ( beautyfy ) {
			if ( this -> childrenVector.getSize() ) {
				o << Elem( '\n' );
				for ( unsigned int i( 0 ); i < indent + 1; i++ ) {
					o << Elem( '\t' );
				}
			}
		}

		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			if ( it != this -> childrenVector.getBegin() ) {
				o << Elem( ',' );

				if ( beautyfy ) {
					o << Elem( '\n' );

					for ( unsigned int i( 0 ); i < indent + 1; i++ ) {
						o << Elem( '\t' );
					}
				}
			}

			NodeT<S>* child( this -> childrenVector.getValueIt( it ) );
			child -> _writeJSON<C, Elem>( o, indent + 1, beautyfy );
		}

		if ( beautyfy ) {
			if ( this -> childrenVector.getSize() ) {
				o << Elem( '\n' );
				for ( unsigned int i( 0 ); i < indent; i++ ) {
					o << Elem( '\t' );
				}
			}
		}

		o << Elem( '}' );
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeMapT<S>::readJSON( const C** buffer, const EndFunc& endFunc ) {
		struct FunctorNodeName {
			bool operator()( const C& c ) { return c != C( '"' ) && c != C( '\t' ) && c != C( '\n' ); }
		};
		struct FunctorContentQuote {
			bool operator()( const C& c ) { return c != C( '"' ); }
		};
		struct FunctorContent {
			bool operator()( const C& c ) { return c != C( ',' ) && c != C( '}' ) && c != C( ']' ) && c != C( ' ' ); }
		};
		struct FunctorSpace {
			bool operator()( const C& c ) { return c == C( '\n' ) || c == C( '\r' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		struct FunctorNoSpace {
			bool operator()( const C& c ) { return c != C( '<' ) && c != C( '\n' ) && c != C( '\t' ) && c != C( ' ' ); }
		};
		static FunctorNodeName functorNodeName;
		static FunctorContentQuote functorContentQuote;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		static const S nullString( "null" );

		const C*& it( *buffer );

		// Skip spaces.
		while ( functorSpace( *it ) ) it++;

		if ( !_expectChar( &it, C( '{' ) ) ) return false;

		// if ( ( *it ) == C( '{' ) ) {
		// Map NodeMap.
		// it++;

		while ( true ) {
			// Skip spaces.
			while ( functorSpace( *it ) ) it++;

			if ( ( *it ) == C( '"' ) ) {
				it++;

				const C* beginIt( it );
				while ( true ) {
					if ( endFunc( it ) ) {
						ERROR_SPP( TEXT( "[JSON Error] : Unexpected buffer end." ) );
						return false;
					}
					if ( !functorNodeName( *it ) )
						break;
					it++;
				}

				// If a name was founded.
				if ( beginIt != it ) {
					// We founded a name.
					S nodeName( beginIt, Size( it - beginIt ) );


					if ( !_expectChar( &it, C( '"' ) ) ) return false;
					while ( functorSpace( *it ) ) it++;
					if ( !_expectChar( &it, C( ':' ) ) ) return false;

					NodeT<S>* newNode( parseT<S, C, EndFunc>( &it, endFunc ) );
					if ( newNode ) {
						newNode -> setName( nodeName );
						this -> addChild( newNode );
					} else {
						ERROR_SPP( String::format( TEXT( "[JSON Error] : Unable to parse the property \"%\"." ), nodeName ) );
						return false;
					}

				} else {
					ERROR_SPP( TEXT( "Expected property name." ) );
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
		/*
	} else if ( ( *it ) == C( '[' ) ) {
		this -> type = Type::Array;
		it++;
		while ( functorSpace( *it ) ) it++;

		while ( true ) {
			if ( ( *it ) == C( ']' ) ) {
				it++;
				break;
			}

			NodeMapT<S> * newNode( new NodeMapT<S>() );
			this -> addChild( newNode );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return false;
			}
			while ( functorSpace( *it ) ) it++;

			if ( ( *it ) == C( ',' ) ) {
				it++;
			}

		}

		while ( functorSpace( *it ) ) it++;
	} else {
		// Value node.
		if ( ( *it ) == C( '"' ) ) {
			// Quote value.
			it++;
			const C * beginIt( it );
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
			this -> value = nodeValue;
			this -> type = Type::Value;

			if ( !_expectChar( &it, C( '"' ) ) ) return false;
		} else {
			// Value without quote.

			const C * beginIt( it );
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
		}
	}
	*/
		return true;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeMapT<S>::readJSON( const C* buffer, const EndFunc& endFunc ) {
		return NodeT<S>::readJSON<C, EndFunc>( buffer, endFunc );
	}

	template<typename S>
	bool NodeMapT<S>::readJSON( const S& str ) {
		return NodeT<S>::readJSON( str );
	}

}