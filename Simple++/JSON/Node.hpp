#include "Node.h"
namespace JSON {

	template<typename T>
	const Vector< BasicNodeT<T> * > BasicNodeT<T>::emptyVector = Vector< BasicNodeT<T> * >();


	template<typename T>
	BasicNodeT<T>::BasicNodeT( typename BasicNodeT<T>::Type type ) :
		type( type ),
		parent( NULL ) {

		// Ensure T is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<T::ElemType>, T>::value );
	}

	template<typename T>
	BasicNodeT<T>::BasicNodeT( const T & name, typename BasicNodeT<T>::Type type ) :
	name(name),
	type(type){

	}

	template<typename T>
	BasicNodeT<T>::BasicNodeT( const BasicNodeT<T> & node ) :
		type( node.type ),
		name(node.name),
		parent( NULL ) {
		
	}

	template<typename T>
	BasicNodeT<T>::BasicNodeT( BasicNodeT<T> && node ) :
		type( Utility::toRValue( node.type ) ),
		name( Utility::toRValue( node.name ) ),
		parent( Utility::toRValue( node.parent ) ) {
	}

	template<typename T>
	BasicNodeT<T>::~BasicNodeT() {

	}

	template<typename T>
	BasicNodeT<T> & BasicNodeT<T>::operator=( const BasicNodeT<T> & node ) {
		this -> type = node.type;
		this -> name = name;
		this -> parent = NULL;

		return *this;
	}

	template<typename T>
	BasicNodeT<T> & BasicNodeT<T>::operator=( BasicNodeT<T> && node ) {
		this -> type = Utility::toRValue( node.type );
		this -> name = Utility::toRValue( node.name );
		this -> parent = Utility::toRValue( node.parent );

		return *this;
	}

	template<typename T>
	typename BasicNodeT<T>::Type BasicNodeT<T>::getType() const {
		return this -> type;
	}

	template<typename T>
	const NodeValueT<T> * BasicNodeT<T>::toValue() const {
		assert( this -> getType() == Type::Value );
		return reinterpret_cast< const NodeValueT<T> * >( this );
	}

	template<typename T>
	NodeValueT<T> * BasicNodeT<T>::toValue() {
		assert( this -> getType() == Type::Value );
		return reinterpret_cast< NodeValueT<T> * >( this );
	}

	template<typename T>
	const NodeArrayT<T> * BasicNodeT<T>::toArray() const {
		assert( this -> getType() == Type::Array );
		return reinterpret_cast< const NodeArrayT<T> * >( this );
	}

	template<typename T>
	NodeArrayT<T> * BasicNodeT<T>::toArray() {
		assert( this -> getType() == Type::Array );
		return reinterpret_cast< NodeArrayT<T> * >( this );
	}

	template<typename T>
	inline const NodeMapT<T>* BasicNodeT<T>::toMap() const {
		assert(this -> getType() == Type::Map);
		return reinterpret_cast< const NodeMapT<T> * >( this );
	}

	template<typename T>
	inline NodeMapT<T>* BasicNodeT<T>::toMap() {
		assert(this -> getType() == Type::Map);
		return reinterpret_cast< NodeMapT<T> * >( this );
	}

	template<typename T>
	const NodeMapT<T> * BasicNodeT<T>::getParent() const {
		return this -> parent;
	}

	template<typename T>
	NodeMapT<T> * BasicNodeT<T>::getParent() {
		return this -> parent;
	}

	template<typename T>
	const T & BasicNodeT<T>::getValue() const {
		error( TEXT( "Trying to retrieve a value on a non-value node." ) );
		return T::null;
	}

	template<typename T>
	void BasicNodeT<T>::setValue( const T & value ) {
		error( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename T>
	void BasicNodeT<T>::setName( const T & name ) {
		if ( this -> parent ) {
			getParent() -> _setChildName( this, this -> name, name );
		}
		this -> name = name;
	}

	template<typename T>
	const T & BasicNodeT<T>::getName() const {
		return this -> name;
	}

	template<typename T>
	inline BasicNodeT<T>* BasicNodeT<T>::getElementByName(const T& name) const {
		return NULL;
	}

	template<typename T>
	Vector< BasicNodeT<T> * > BasicNodeT<T>::getElementsByName( const T & name ) const {
		return Vector<BasicNodeT<T> *>();
	}

	template<typename T>
	Size BasicNodeT<T>::getNbChildren() const {
		return Size( 0 );
	}

	template<typename T>
	void BasicNodeT<T>::addChild( BasicNodeT<T> * child ) {
		error( TEXT( "Trying to add a child on a non Map/Array NodeMap." ) );
	}

	template<typename T>
	const Vector<BasicNodeT<T> *> & BasicNodeT<T>::getChildren() const {
		return BasicNodeT<T>::emptyVector;
	}

	template<typename T>
	const Vector< BasicNodeT<T> * > & BasicNodeT<T>::getChildren( const T & name ) const {
		return BasicNodeT<T>::emptyVector;
	}

	/*
	template<typename T>
	Vector< BasicNodeT<T> * > BasicNodeT<T>::getChildren( const T & name ) {
		return Vector<BasicNodeT<T> *>();
	}
	*/

	template<typename T>
	const BasicNodeT<T> * BasicNodeT<T>::getChild( const T & name ) const {
		return const_cast< BasicNodeT<T> * >( this ) ->getChild( name );
	}

	template<typename T>
	BasicNodeT<T> * BasicNodeT<T>::getChild( const T & name ) {
		return NULL;
	}

	template<typename T>
	const BasicNodeT<T> * BasicNodeT<T>::getChild( Size i ) const {
		return const_cast< BasicNodeT<T> * >( this ) -> getChild( i );
	}

	template<typename T>
	BasicNodeT<T> * BasicNodeT<T>::getChild( Size i ) {
		return NULL;
	}

	template<typename T>
	bool BasicNodeT<T>::deleteChild( BasicNodeT<T> * child ) {
		return false;
	}

	template<typename T>
	bool BasicNodeT<T>::deleteChild( Size i ) {
		return false;
	}

	template<typename T>
	BasicNodeT<T> * BasicNodeT<T>::removeChild( BasicNodeT<T> * child ) {
		return NULL;
	}

	template<typename T>
	BasicNodeT<T> * BasicNodeT<T>::removeChild( Size i ) {
		return NULL;
	}

	template<typename T>
	template<typename Stream>
	bool BasicNodeT<T>::writeJSON(Stream* fileStreamP, unsigned int indent ) const {
		Stream & stream( *fileStreamP );

		// Call the virtual protected method.
		_writeJSON<Stream, char>( stream, indent );

		return !( fileStreamP -> hasFailed() );
	}

	template<typename T>
	template<typename C>
	bool BasicNodeT<T>::writeJSON( C & str, unsigned int indent ) const {
		return _writeJSON<C, C::ElemType>( str, indent );
	}

	template<typename T>
	template<typename C>
	C BasicNodeT<T>::toString( unsigned int indent ) const {
		C newString;
		newString.reserve( 128 );

		_writeJSON<C, C::ElemType>( newString, indent );
		return newString;
	}

	template<typename T>
	template<typename C, typename Elem>
	void BasicNodeT<T>::_writeJSON( C & o, unsigned int indent ) const {
		if ( getType() == Type::Map ) {
			this -> toMap() -> _writeJSON<C, Elem>( o, indent );
		} else if ( getType() == Type::Array ) {
			this -> toArray() -> _writeJSON<C, Elem>( o, indent );
		} else if ( getType() == Type::Value ) {
			this -> toValue() -> _writeJSON<C, Elem>( o, indent );
		}
	}

	template<typename T>
	template<typename Stream>
	bool BasicNodeT<T>::read( Stream * stream ) {
		switch ( this->type ) {
			case Type::Array:
				return this->toArray()->read(stream);
			case Type::Map:
				return this->toMap()->read(stream);
			case Type::Value:
				return this->toValue()->read(stream);
			default:
				return false;
		}
	}

	template<typename T>
	template<typename Stream>
	bool BasicNodeT<T>::write( Stream * stream ) const {
		switch ( this->type ) {
			case Type::Array:
				return this->toArray()->write(stream);
			case Type::Map:
				return this->toMap()->write(stream);
			case Type::Value:
				return this->toValue()->write(stream);
			default:
				return false;
		}
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool BasicNodeT<T>::readJSON( const C ** buffer, const EndFunc & endFunc ) {
		switch ( this->type ) {
			case Type::Array:
				return this->toArray()->readJSON<C, EndFunc>(buffer, endFunc);
			case Type::Map:
				return this->toMap()->readJSON<C, EndFunc>(buffer, endFunc);
			case Type::Value:
				return this->toValue()->readJSON<C, EndFunc>(buffer, endFunc);
			default:
				return false;
		}
	}

	template<typename T>
	bool BasicNodeT<T>::writeFileJSON( const OS::Path & filePath ) const {
		IO::FileStream stream( filePath, IO::OpenMode::Write );
		if ( !stream.isOpen() ) {
			return false;
		}
		return writeJSON(&stream);
	}

	template<typename T>
	bool BasicNodeT<T>::readFileJSON( const OS::Path & filePath ) {
		_unload();

		T strOut;
		if (IO::readToString(filePath, &strOut) != size_t(-1)) {
			return readJSON(strOut);
		}
		else {
			_clear();
			return false;
		}
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool BasicNodeT<T>::readJSON( const C * buffer, const EndFunc & endFunc ) {
		return readJSON( &buffer, endFunc );
	}

	template<typename T>
	bool BasicNodeT<T>::readJSON( const T & str ) {
		const typename T::ElemType * buffer( str.toCString() );
		return readJSON<T::ElemType>( &buffer );
	}

	template<typename T>
	template<typename C>
	bool BasicNodeT<T>::_expectChar( const C ** buffer, const C & c ) {
		const C *& it( *buffer );

		if ( ( *it ) == c ) {
			it++;
			return true;
		} else {
			error( String::format( TEXT( "[JSON ERROR] : Expected '%'." ), c ) );
			return false;
		}
	}

	template<typename T>
	template<typename Stream>
	inline bool BasicNodeT<T>::_write(Stream* stream) const {
		if ( !IO::write(stream, &this -> name) )
			return false;
		return true;
	}

	template<typename T>
	template<typename Stream>
	inline bool BasicNodeT<T>::_read(Stream* stream) {
		if ( !IO::read(stream, &this -> name) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename T>
	void BasicNodeT<T>::_clear() {

	}

	template<typename T>
	void BasicNodeT<T>::_unload() {

	}




















































	template<typename T>
	NodeMapT<T>::NodeMapT( ) :
		BasicNodeT<T>( Type::Map ) {

	}

	template<typename T>
	NodeMapT<T>::NodeMapT( const T & name ) :
		BasicNodeT<T>( name, Type::Map ) {

	}

	template<typename T>
	NodeMapT<T>::NodeMapT( const T & name, const T & value ) :
		BasicNodeT<T>( name, Type::Map ) {

	}

	template<typename T>
	NodeMapT<T>::NodeMapT( const NodeMapT<T> & node ) :
		BasicNodeT<T>( node ) {
		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			BasicNodeT<T> * newNode( new BasicNodeT<T>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
	}

	template<typename T>
	NodeMapT<T>::NodeMapT( NodeMapT<T> && node ) :
		BasicNodeT<T>( Utility::toRValue( node ) ),
		childrenMap( Utility::toRValue( node.childrenMap ) ),
		childrenVector( Utility::toRValue( node.childrenVector ) ) {
		node.childrenVector.clear();
	}

	template<typename T>
	NodeMapT<T>::~NodeMapT() {
		_unload();
	}

	template<typename T>
	NodeMapT<T> & NodeMapT<T>::operator=( const NodeMapT<T> & node ) {
		BasicNodeT<T>::operator=( node );

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			BasicNodeT<T> * newNode( new BasicNodeT<T>( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		return *this;
	}

	template<typename T>
	NodeMapT<T> & NodeMapT<T>::operator=( NodeMapT<T> && node ) {
		BasicNodeT<T>::operator=( Utility::toRValue( node ) );

		this -> childrenVector = Utility::toRValue( node.childrenVector );
		this -> childrenMap = Utility::toRValue( node.childrenMap );

		node.childrenVector.clear();

		return *this;
	}

	template<typename T>
	inline BasicNodeT<T>* NodeMapT<T>::getElementByName(const T& name) const {
		if ( name == this -> name )
			return const_cast< NodeMapT<T> * >( this );
		else
			return _getElementByName(name);
	}

	template<typename T>
	Vector< BasicNodeT<T> * > NodeMapT<T>::getElementsByName( const T & name ) const {
		Vector< BasicNodeT<T> * > nodeVector;
		nodeVector.reserve( 20 );

		if ( name == this -> name )
			nodeVector.push( const_cast< NodeMapT<T> * >( this ) );

		_getElementsByName( &nodeVector, name );
		return nodeVector;
	}

	template<typename T>
	Size NodeMapT<T>::getNbChildren() const {
		return this -> childrenVector.getSize();
	}

	template<typename T>
	void NodeMapT<T>::addChild( BasicNodeT<T> * child ) {
		if ( child != NULL ) {
			if ( child -> getParent() )
				child -> getParent() -> removeChild( child );

			if ( child -> getName().getSize() ) {
				this -> childrenMap.insert( child -> getName(), child );
			}
		} else {
			child = new BasicNodeT<T>( Type::Null );
		}

		child -> parent = this;

		this -> childrenVector.push( child );
	}

	template<typename T>
	void NodeMapT<T>::_clear() {
		_unload();

		this -> name.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();
	}

	template<typename T>
	void NodeMapT<T>::_unload() {
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			BasicNodeT<T> * node( this -> childrenVector.getValueIt( it ) );

			delete node;
		}
	}

	template<typename T>
	const Vector<BasicNodeT<T> *> & NodeMapT<T>::getChildren() const {
		return this ->childrenVector;
	}

	template<typename T>
	const Vector< BasicNodeT<T> * > & NodeMapT<T>::getChildren( const T & name ) const {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return BasicNodeT<T>::emptyVector;
	}

	/*
	template<typename T>
	Vector< BasicNodeT<T> * > NodeMapT<T>::getChildren( const T & name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return Vector<BasicNodeT<T> *>();
	}
	*/

	template<typename T>
	const BasicNodeT<T> * NodeMapT<T>::getChild( const T & name ) const {
		return const_cast< NodeMapT<T> * >( this ) ->getChild( name );
	}

	template<typename T>
	BasicNodeT<T> * NodeMapT<T>::getChild( const T & name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) {
			Vector<BasicNodeT<T> * > childVector( *childP );
			if ( childVector.getSize() > 0 ) {
				return childVector[ 0 ];
			}
		}
		return NULL;
	}

	template<typename T>
	const BasicNodeT<T> * NodeMapT<T>::getChild( Size i ) const {
		return const_cast< NodeMapT<T> * >( this ) -> getChild( i );
	}

	template<typename T>
	BasicNodeT<T> * NodeMapT<T>::getChild( Size i ) {
		if ( i < this->childrenVector.getSize() ) {
			return this->childrenVector.getValueI( i );
		} else {
			return NULL;
		}
	}

	template<typename T>
	bool NodeMapT<T>::deleteChild( BasicNodeT<T> * child ) {
		BasicNodeT<T> * childRemoved( removeChild( child ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename T>
	bool NodeMapT<T>::deleteChild( Size i ) {
		BasicNodeT<T> * childRemoved( removeChild( i ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename T>
	BasicNodeT<T> * NodeMapT<T>::removeChild( BasicNodeT<T> * child ) {
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
	BasicNodeT<T> * NodeMapT<T>::removeChild( Size i ) {
		if ( i >= this -> childrenVector.getSize() ) {
			return NULL;
		} else {
			BasicNodeT<T> * child( this -> childrenVector[ i ] );
			this -> childrenVector.eraseI( i );
			if ( child ) {
				if ( child -> getName().getSize() )
					this -> childrenMap.eraseFirst( child -> getName(), child );
				child -> parent = NULL;
			}

			return child;
		}
	}

	template<typename T>
	template<typename Stream>
	bool NodeMapT<T>::read( Stream * stream ) {
		_unload();

		this -> childrenMap.clear();
		this -> childrenVector.clear();

		if ( !BasicNodeT<T>::_read( stream ) ) {
			_clear();
			return false;
		}
		

		// Read the children
		Size nbChilds;
		if ( !IO::read( stream, &nbChilds ) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min( nbChilds, Size( 1000 ) );
		for ( Size i( 0 ); i < nbChilds; i++ ) {
			bool isNull;
			if ( !IO::read( stream, &isNull ) ) {
				_clear();
				return false;
			}
			if ( isNull ) {
				this -> childrenVector.push( NULL );
			} else {
				Type newNodeType;
				if ( !IO::read( stream, &newNodeType ) ) {
					_clear();
					return false;
				}


				switch ( newNodeType ) {
					case Type::Map:
					{
						NodeMapT<T> * newNode( new NodeMapT<T>( ) );
						newNode -> parent = this;
						if ( !IO::read( stream, newNode ) ) {
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
						NodeValueT<T> * newNode( new NodeValueT<T>( ) );
						newNode -> parent = this;
						if ( !IO::read( stream, newNode ) ) {
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
						NodeArrayT<T> * newNode( new NodeArrayT<T>( ) );
						newNode -> parent = this;
						if ( !IO::read( stream, newNode ) ) {
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
						BasicNodeT<T> * newNode( new BasicNodeT<T>( newNodeType ) );
						newNode -> parent = this;
						if ( !IO::read( stream, newNode ) ) {
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


	template<typename T>
	bool NodeMapT<T>::_setChildName( BasicNodeT<T> * child, const T & oldName, const T & newName ) {
		if ( oldName.getSize() ) {
			if ( !this -> childrenMap.eraseFirst( oldName, child ) ) {
				return false;
			}
		}
		if ( child -> getName().getSize() )
			this -> childrenMap.insert( newName, child );
		return true;
	}

	template<typename T>
	void NodeMapT<T>::_getElementsByName( Vector < BasicNodeT<T> * > * nodeVector, const T & name ) const {
		const Vector < BasicNodeT<T> * > * vectorFounded( this -> childrenMap[ name ] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			BasicNodeT<T> * child( this -> childrenVector.getValueIt( it ) );
			if ( child -> getType() == Type::Map ) {
				child -> toMap() -> _getElementsByName( nodeVector, name );
			}
		}
	}

	template<typename T>
	inline BasicNodeT<T>* NodeMapT<T>::_getElementByName(const T& name) const {
		const Vector < BasicNodeT<T>* >* vectorFounded(this -> childrenMap[ name ]);
		if ( vectorFounded ) {
			return vectorFounded->getFirst();
		}

		// Recursively call every child too
		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			BasicNodeT<T>* child(this -> childrenVector.getValueIt(it));
			if ( child -> getType() == Type::Map ) {
				BasicNodeT<T>* foundedElement(child -> toMap() -> _getElementByName(name));
				if ( foundedElement ) {
					return foundedElement;
				}
			}
		}
		return NULL;
	}

	template<typename T>
	template<typename Stream>
bool NodeMapT<T>::write( Stream * stream ) const {
		if ( !BasicNodeT<T>::_write( stream ) ) {
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

	template<typename T>
	template<typename C, typename Elem>
	void NodeMapT<T>::_writeJSON( C & o, unsigned int indent ) const {

		if ( this -> getName().getSize() ) {
			o << Elem( '"' );
			o << this -> getName();
			o << Elem( '"' );
			o << Elem( ':' );
			o << Elem( ' ' );
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

				NodeMapT<T> * child( this -> childrenVector.getValueIt( it ) );
				child -> _writeJSON( o, indent );
			}
			o << Elem( ']' );

		} else {
		*/
		o << Elem( '{' );
		if ( this -> childrenVector.getSize() ) {
			o << Elem( '\n' );
			for ( unsigned int i( 0 ) ; i < indent + 1 ; i++ ) {
				o << Elem( '\t' );
			}
		}

		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			if ( it != this -> childrenVector.getBegin() ) {
				o << Elem( ',' );
				o << Elem( '\n' );

				for ( unsigned int i( 0 ) ; i < indent + 1 ; i++ ) {
					o << Elem( '\t' );
				}
			}

			BasicNodeT<T> * child( this -> childrenVector.getValueIt( it ) );
			child -> _writeJSON<C, Elem>( o, indent + 1 );
		}

		if ( this -> childrenVector.getSize() ) {
			o << Elem( '\n' );
			for ( unsigned int i( 0 ) ; i < indent ; i++ ) {
				o << Elem( '\t' );
			}
		}

		o << Elem( '}' );
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeMapT<T>::readJSON( const C ** buffer, const EndFunc & endFunc ) {
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

		if ( !_expectChar( &it, C( '{' ) ) ) return false;

		// if ( ( *it ) == C( '{' ) ) {
		// Map NodeMap.
		// it++;

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
					T nodeName( beginIt, Size( it - beginIt ) );


					if ( !_expectChar( &it, C( '"' ) ) ) return false;
					while ( functorSpace( *it ) ) it++;
					if ( !_expectChar( &it, C( ':' ) ) ) return false;
					
					BasicNodeT<T> * newNode( parseT<T, C, EndFunc>( &it, endFunc ) );
					if ( newNode ) {
						newNode -> setName( nodeName );
						this -> addChild( newNode );
					} else {
						error( String::format( TEXT( "[JSON Error] : Unable to parse the property \"%\"."), nodeName ) );
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

				NodeMapT<T> * newNode( new NodeMapT<T>() );
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
						error( TEXT( "[JSON Error] : Unexpected buffer end." ) );
						return false;
					}
					if ( !functorContentQuote( *it ) ) {
						if ( ( *( it - 1 ) ) != C( '\\' ) ) {
							break;
						}
					}
					it++;
				}

				T nodeValue( beginIt, Size( it - beginIt ) );
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

				T nodeValue( beginIt, Size( it - beginIt ) );

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

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeMapT<T>::readJSON( const C * buffer, const EndFunc & endFunc ) {
		return BasicNodeT<T>::readJSON<C, EndFunc>( buffer, endFunc );
	}

	template<typename T>
	bool NodeMapT<T>::readJSON( const T & str ) {
		return BasicNodeT<T>::readJSON( str );
	}




	/************************************************************************/
	/* NodeValueT<T>                                                         */
	/************************************************************************/

	template<typename T>
	NodeValueT<T>::NodeValueT() : BasicNodeT<T>( BasicNodeT<T>::Type::Value ) {

	}

	template<typename T>
	NodeValueT<T>::NodeValueT( const T & value ) : BasicNodeT<T>( BasicNodeT<T>::Type::Value ) {
		this -> value = value;
	}

	template<typename T>
	NodeValueT<T>::NodeValueT( const T & name, const T & value ) :
		BasicNodeT<T>( BasicNodeT<T>::Type::Value ) {
		this -> name = name;
		this -> value = value;
	}

	template<typename T>
	NodeValueT<T>::NodeValueT( const NodeValueT<T> & node ) : NodeT( node ), value(node.value), name( node.name ) {

	}

	template<typename T>
	NodeValueT<T>::NodeValueT( NodeValueT<T> && node ) : NodeT( Utility::toRValue( node ) ), value( Utility::toRValue( node.value )), name( Utility::toRValue( node.name ) ) {

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
	template<typename C, typename EndFunc>
	bool NodeValueT<T>::readJSON( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorContentQuote {
			bool operator()( const C & c ) { return c != C( '"' ); }
		};
		struct FunctorContent {
			bool operator()( const C & c ) { return c != C( ',' ) && c != C( '}' ) && c != C( ']' ) && c != C( ' ' ); }
		};
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};

		static FunctorContentQuote functorContentQuote;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		static const T nullString( "null" );

		const C *& it( *buffer );

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
				if ( !functorContentQuote( *it ) ) {
					if ( ( *( it - 1 ) ) != C( '\\' ) ) {
						break;
					}
				}
				it++;
			}

			T nodeValue( beginIt, Size( it - beginIt ) );
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

			T nodeValue( beginIt, Size( it - beginIt ) );

			if ( nodeValue == nullString ) {
				this -> type = Type::Null;
			} else {
				this -> value = nodeValue;
				this -> type = Type::Value;
			}
		}

		return true;
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeValueT<T>::readJSON( const C * buffer, const EndFunc & endFunc ) {
		return BasicNodeT<T>::readJSON<C, EndFunc>( buffer, endFunc );
	}

	template<typename T>
	bool NodeValueT<T>::readJSON( const T & str ) {
		return BasicNodeT<T>::readJSON( str );
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeValueT<T>::_writeJSON( C & o, unsigned int indent ) const {
		if ( this -> getName().getSize() ) {
			o << Elem( '"' );
			o << this -> getName();
			o << Elem( '"' );
			o << Elem( ':' );
			o << Elem( ' ' );
		}

		o << Elem( '"' );
		o << this -> getValue();
		o << Elem( '"' );
	}

	template<typename T>
	template<typename Stream>
	bool NodeValueT<T>::read( Stream * stream ) {
		if ( !BasicNodeT<T>::_read( stream ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool NodeValueT<T>::write( Stream * stream ) const {
		if ( !BasicNodeT<T>::_write( stream ) ) {
			return false;
		}
		if ( !IO::write( stream, &this -> value ) )
			return false;
		return true;
	}


	/************************************************************************/
	/* NodeArrayT<T>                                                         */
	/************************************************************************/

	template<typename T>
	NodeArrayT<T>::NodeArrayT() : NodeMapT<T>( ) {
		this -> type = Type::Array;
	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( const T & name ) : NodeMapT<T>( name ) {
		this -> type = Type::Array;
	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( const T & name, const Vector<BasicNodeT<T> *> & v ) :
		BasicNodeT<T>( name, BasicNodeT<T>::Type::Array ) {
		for ( auto it( v.getBegin() ); it != v.getEnd(); v.iterate( &it ) ) {
			BasicNodeT<T> * node( v.getValueIt( it ) );
			this -> addChild( node );
		}
	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( const NodeArrayT<T> & node ) : NodeT( node ) {

	}

	template<typename T>
	NodeArrayT<T>::NodeArrayT( NodeArrayT<T> && node ) : NodeT( Utility::toRValue( node ) ) {

	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeArrayT<T>::readJSON( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};

		static FunctorSpace functorSpace;

		const C *& it( *buffer );

		if ( !BasicNodeT<T>::_expectChar( &it, C( '[' ) ) ) return false;

		this -> type = Type::Array;
		while ( functorSpace( *it ) ) it++;

		while ( true ) {
			if ( ( *it ) == C( ']' ) ) {
				it++;
				break;
			}

			BasicNodeT<T> * newNode( parseT<T, C, EndFunc>( &it, endFunc ) );
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

	template<typename T>
	template<typename C, typename EndFunc>
	bool NodeArrayT<T>::readJSON( const C * buffer, const EndFunc & endFunc ) {
		return BasicNodeT<T>::readJSON<C, EndFunc>( buffer, endFunc );
	}

	template<typename T>
	bool NodeArrayT<T>::readJSON( const T & str ) {
		return BasicNodeT<T>::readJSON( str );
	}

	template<typename T>
	template<typename C, typename Elem>
	void NodeArrayT<T>::_writeJSON( C & o, unsigned int indent ) const {
		if ( this -> getName().getSize() ) {
			o << Elem( '"' );
			o << this -> getName();
			o << Elem( '"' );
			o << Elem( ':' );
			o << Elem( ' ' );
		}

		o << Elem( '[' );
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			if ( it != this -> childrenVector.getBegin() ) {
				o << Elem( ',' );
				o << Elem( ' ' );
			}

			BasicNodeT<T> * child( this -> childrenVector.getValueIt( it ) );
			child -> _writeJSON<C, Elem>( o, indent );
		}
		o << Elem( ']' );
	}















	template<typename T>
	inline DocumentT<T>::DocumentT() :
		rootNode(NULL) {}

	template<typename T>
	inline DocumentT<T>::DocumentT(const T& str) :
		rootNode(NULL) {
		readJSON(str);
	}

	template<typename T>
	inline DocumentT<T>::~DocumentT() {
		if ( this->rootNode ) {
			delete this->rootNode;
		}
	}

	template<typename T>
	inline const BasicNodeT<T>* DocumentT<T>::getRoot() const {
		return this->rootNode;
	}

	template<typename T>
	inline BasicNodeT<T>* DocumentT<T>::getRoot() {
		return this->rootNode;
	}

	template<typename T>
	inline BasicNodeT<T>* DocumentT<T>::getElementByName(const T& name) const {
		if ( this->rootNode ) {
			return this->rootNode->getElementByName(name);
		}
		return NULL;
	}

	template<typename T>
	inline Vector<BasicNodeT<T>*> DocumentT<T>::getElementsByName(const T& name) const {
		if ( this->rootNode ) {
			return this->rootNode->getElementsByName(name);
		}
		return Vector<BasicNodeT<T>*>();
	}

	template<typename T>
	inline bool DocumentT<T>::writeFileJSON(const OS::Path& filePath) const {
		IO::FileStream stream(filePath, IO::OpenMode::Write);
		if ( !stream.isOpen() ) {
			return false;
		}
		if ( this->rootNode ) {
			return this->rootNode->writeJSON(&stream);
		}
		return true;
	}

	template<typename T>
	inline bool DocumentT<T>::readFileJSON(const OS::Path& filePath) {
		_unload();

		T strOut;
		if ( IO::readToString(filePath, &strOut) != size_t(-1) ) {
			return readJSON(strOut);
		} else {
			_unload();
			return false;
		}
	}

	template<typename T>
	inline bool DocumentT<T>::readJSON(const T& str) {
		const typename T::ElemType* buffer(str.toCString());
		return readJSON<T::ElemType>(&buffer);
	}

	template<typename T>
	template<typename Stream>
	inline bool DocumentT<T>::writeJSON(Stream* stream, unsigned int indent) const {
		if ( this->rootNode ) {
			return this->rootNode->writeJSON(stream, indent);
		}
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool DocumentT<T>::read( Stream * stream ) {
		_unload();

		bool bIsRootNode;
		if ( !IO::read(stream, &bIsRootNode) ) {
			return false;
		}
		if ( bIsRootNode ) {
			unsigned char rootNodeTypeUC;
			if ( !IO::read(stream, &rootNodeTypeUC) ) {
				return false;
			}
			BasicNodeT<T>::Type rootNodeType(static_cast< BasicNodeT<T>::Type >( rootNodeTypeUC ));
			switch ( rootNodeType ) {
				case BasicNodeT<T>::Type::Map:
					{
						NodeMapT<T>* newRootNode(new NodeMapT<T>());
						if ( !IO::read(stream, newRootNode) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				case BasicNodeT<T>::Type::Value:
					{
						NodeValueT<T>* newRootNode(new NodeValueT<T>());
						if ( !IO::read(stream, newRootNode) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				case BasicNodeT<T>::Type::Array:
					{
						NodeArrayT<T>* newRootNode(new NodeArrayT<T>());
						if ( !IO::read(stream, newRootNode) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				default:
					{
						return false;
					}
			}
		}
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool DocumentT<T>::write( Stream * stream ) const {
		bool bIsRootNode(this->rootNode);
		if ( !IO::write(stream, &bIsRootNode) ) {
			return false;
		}
		if ( this->rootNode ) {
			BasicNodeT<T>::Type rootNodeType(this->rootNode->getType());
			unsigned char rootNodeTypeUC(static_cast< unsigned char >( rootNodeType ));
			if ( !IO::write(stream, &rootNodeTypeUC) ) {
				return false;
			}
			switch ( rootNodeType ) {
				case BasicNodeT<T>::Type::Map:
					{
						NodeMapT<T>* rootNode(this->rootNode->toMap());
						if ( !IO::write(stream, rootNode) ) {
							return false;
						}
						break;
					}
				case BasicNodeT<T>::Type::Value:
					{
						NodeValueT<T>* rootNode(this->rootNode->toValue());
						if ( !IO::write(stream, rootNode) ) {
							return false;
						}
						break;
					}
				case BasicNodeT<T>::Type::Array:
					{
						NodeArrayT<T>* rootNode(this->rootNode->toArray());
						if ( !IO::write(stream, rootNode) ) {
							return false;
						}
						break;
					}
				default:
					{
						return false;
					}
			}
		}

		return true;
	}

	template<typename T>
	inline void DocumentT<T>::_unload() {
		if ( this->rootNode ) {
			delete this->rootNode;
			this->rootNode = NULL;
		}
	}

	template<typename T>
	template<typename C, typename EndFunc>
	inline bool DocumentT<T>::readJSON(const C** buffer, const EndFunc& endFunc) {
		const C*& it(*buffer);

		// Can be empty.
		if ( endFunc(it) ) {
			return true;
		}

		BasicNodeT<T>* newNode(parseT<T, C, EndFunc>(&it, endFunc));

		if ( newNode ) {
			_unload();
			this->rootNode = newNode;
			return true;
		}

		return false;
	}

	template<typename T>
	template<typename C, typename EndFunc>
	inline bool DocumentT<T>::readJSON(const C* buffer, const EndFunc& endFunc) {
		return readJSON(&buffer, endFunc);
	}

	template<typename T>
	template<typename C>
	inline bool DocumentT<T>::writeJSON(C& str, unsigned int indent) const {
		if ( this->rootNode ) {
			return this->rootNode->writeJSON(str, indent);
		}
		return true;
	}

	template<typename T>
	template<typename C>
	inline C DocumentT<T>::toString(unsigned int indent) const {
		if ( this->rootNode ) {
			return this->rootNode->toString(indent);
		} else {
			return C::null;
		}
	}




















	template<typename T, typename C, typename EndFunc>
	BasicNodeT<T> * parseT( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		static FunctorSpace functorSpace;

		const C *& it( *buffer );

		while ( functorSpace( *it ) ) it++;

		if ( ( *it ) == C( '{' ) ) {
			NodeMapT<T> * newNode( new NodeMapT<T>( ) );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return NULL;
			} else {
				return newNode;
			}
		} else if ( ( *it ) == C( '[' ) ) {
			NodeArrayT<T> * newNode( new NodeArrayT<T>( ) );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return NULL;
			} else {
				return newNode;
			}
		} else {
			NodeValueT<T> * newNode( new NodeValueT<T>( ) );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return NULL;
			} else {
				return newNode;
			}
		}

		return NULL;
	}

	template<typename T, typename C, typename EndFunc>
	BasicNodeT<T> * parseT( const C * buffer, const EndFunc & endFunc ) {
		return parseT<T, C, EndFunc>( &buffer, endFunc );
	}

	template<typename T>
	BasicNodeT<T> * parseT( const T & str ) {
		const typename T::ElemType * buffer( str.toCString() );
		return parse<T, T::ElemType>( buffer );
	}

}