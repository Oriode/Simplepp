namespace JSON {

	template<typename T>
	NodeT<T>::NodeT( Type type = Type::Object ) :
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
	const NodeT<T> * NodeT<T>::getParent() const {
		return this -> parent;
	}

	template<typename T>
	NodeT<T> * NodeT<T>::getParent() {
		return this -> parent;
	}

	template<typename T>
	const T & NodeT<T>::getValue() const {
		if ( getType() == Type::Value ) {
			return toValue() -> getValue();
		} else if ( this -> childrenVector.getSize() == 1 && this -> childrenVector[ 0 ] != NULL ) {
			return this -> childrenVector[ 0 ] -> getValue();
		} else {
			//Error, you shouldn't call this method, return an empty string
			return T::null;
		}
	}

	template<typename T>
	void NodeT<T>::setValue( const T & value ) {
		if ( getType() == Type::Value ) {
			this -> toValue() -> setValue( value );
		} else {
			if ( this -> childrenVector.getSize() > 0 && this -> childrenVector[ 0 ] != NULL ) {
				// We are not a Text node, and we have at least one child, if the first one is a Text one, set it's value.
				if ( this -> childrenVector[ 0 ] -> getType() == Type::Value )
					this -> childrenVector[ 0 ] -> toValue() -> setValue( value );
			} else {
				// We are not a Text node, and do not have any child, add one
				NodeValueT<T> * newNode( new NodeValueT<T>( value ) );
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
			}
		} else {
			if ( child != NULL ) {
				if ( child -> parent )
					child -> parent -> removeChild( child );

				child -> parent = this;

				if ( child -> getName().getSize() ) {
					this -> childrenMap.insert( child -> getName(), child );
				}
			}
			
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
			if (*it )
				delete this -> childrenVector.getValueIt( it );
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
	bool NodeT<T>::writeJSON( std::fstream * fileStreamP, unsigned int tabs ) const {
		std::fstream & fileStream( *fileStreamP );

		_writeJSON<std::fstream, char>( fileStream, tabs );

		return !( fileStreamP -> bad() );
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
			boolean isNull;
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
				if ( newNodeType == Type::Value ) {
					NodeValueT<T> * newNode( new NodeValueT<T>() );
					newNode -> parent = this;
					if ( !IO::read( fileStream, newNode ) ) {
						delete newNode;
						_clear();
						return false;
					}
					this -> childrenVector.push( newNode );
					if ( newNode -> getName().getSize() )
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
					if ( newNode -> getName().getSize() )
						this -> childrenMap.insert( newNode -> getName(), newNode );
				}
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
			boolean isNull( *it == NULL );
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
			newString << this -> toValue() -> getValue();
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

				if ( *it == NULL ) {

					for ( unsigned int i( 0 ) ; i < indent + 1 ; i++ ) {
						newString << T::ElemType( '\t' );
					}

					newString << T::ElemType( 'n' );
					newString << T::ElemType( 'u' );
					newString << T::ElemType( 'l' );
					newString << T::ElemType( 'l' );
				} else {
					newString << this -> childrenVector.getValueIt( it ) -> toStringDebug( indent + 1 );
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
	void NodeT<T>::_writeJSON( C & o, unsigned int tabs ) const {
		if ( getType() == Type::Value )
			return this -> toValue() -> _writeJSON<C, Elem>( o, tabs );

		for ( unsigned int i( 0 ); i < tabs; i++ )
			o << Elem( '\t' );

		o << Elem( '<' );
		o << this -> name;

		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			o << Elem( ' ' );
			this -> paramsVector.getValueIt( it ) -> _writeJSON<C, Elem>( o );
		}

		// If we have children, it's not an self closing one
		if ( this -> childrenVector.getSize() ) {
			o << Elem( '>' );

			for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
				if ( getNbChildren() > 1 )
					o << Elem( '\n' );
				this -> childrenVector.getValueIt( it ) -> _writeJSON<C, Elem>( o, tabs + 1 );
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




	/************************************************************************/
	/* NodeValueT<T>                                                         */
	/************************************************************************/

	template<typename T>
	bool NodeValueT<T>::writeXML( std::fstream * fileStreamP ) const {
		std::fstream & fileStream( *fileStreamP );

		_writeXML<std::fstream, char>( fileStream, 0 );

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
	void NodeValueT<T>::_writeXML( C & o, unsigned int tabs ) const {
		o << this -> value;
	}

	template<typename T>
	template<typename C>
	C NodeValueT<T>::toString( unsigned int indent ) const {
		C newString;
		newString.reserve( 128 );

		_writeXML<C, C::ElemType>( newString, indent );
		return newString;
	}

}