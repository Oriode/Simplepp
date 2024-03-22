#include "Node.h"

namespace JSON {

	template<typename S>
	const Vector< NodeT<S>* > NodeT<S>::emptyVector = Vector< NodeT<S>* >();


	template<typename S>
	NodeT<S>::NodeT( typename NodeT<S>::Type type ) :
		type( type ),
		parent( NULL ) {

		// Ensure S is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<S::ElemType>, S>::value );
	}

	template<typename S>
	NodeT<S>::NodeT( const S& name, typename NodeT<S>::Type type ) :
		name( name ),
		type( type ) {

	}

	template<typename S>
	NodeT<S>::NodeT( const NodeT<S>& node ) :
		type( node.type ),
		name( node.name ),
		parent( NULL ) {

	}

	template<typename S>
	NodeT<S>::NodeT( NodeT<S>&& node ) :
		type( Utility::toRValue( node.type ) ),
		name( Utility::toRValue( node.name ) ),
		parent( Utility::toRValue( node.parent ) ) {}

	template<typename S>
	NodeT<S>::~NodeT() {

	}

	template<typename S>
	NodeT<S>& NodeT<S>::operator=( const NodeT<S>& node ) {
		this -> type = node.type;
		this -> name = name;
		this -> parent = NULL;

		return *this;
	}

	template<typename S>
	NodeT<S>& NodeT<S>::operator=( NodeT<S>&& node ) {
		this -> type = Utility::toRValue( node.type );
		this -> name = Utility::toRValue( node.name );
		this -> parent = Utility::toRValue( node.parent );

		return *this;
	}

	template<typename S>
	typename NodeT<S>::Type NodeT<S>::getType() const {
		return this -> type;
	}

	template<typename S>
	const NodeValueT<S>* NodeT<S>::toValue() const {
		ASSERT_SPP( this -> getType() == Type::Value );
		return reinterpret_cast< const NodeValueT<S> * >( this );
	}

	template<typename S>
	NodeValueT<S>* NodeT<S>::toValue() {
		ASSERT_SPP( this -> getType() == Type::Value );
		return reinterpret_cast< NodeValueT<S> * >( this );
	}

	template<typename S>
	const NodeArrayT<S>* NodeT<S>::toArray() const {
		ASSERT_SPP( this -> getType() == Type::Array );
		return reinterpret_cast< const NodeArrayT<S> * >( this );
	}

	template<typename S>
	NodeArrayT<S>* NodeT<S>::toArray() {
		ASSERT_SPP( this -> getType() == Type::Array );
		return reinterpret_cast< NodeArrayT<S> * >( this );
	}

	template<typename S>
	inline const NodeMapT<S>* NodeT<S>::toMap() const {
		ASSERT_SPP( this -> getType() == Type::Map );
		return reinterpret_cast< const NodeMapT<S> * >( this );
	}

	template<typename S>
	inline NodeMapT<S>* NodeT<S>::toMap() {
		ASSERT_SPP( this -> getType() == Type::Map );
		return reinterpret_cast< NodeMapT<S> * >( this );
	}

	template<typename S>
	const NodeMapT<S>* NodeT<S>::getParent() const {
		return this -> parent;
	}

	template<typename S>
	NodeMapT<S>* NodeT<S>::getParent() {
		return this -> parent;
	}

	template<typename S>
	const S& NodeT<S>::getValue() const {
		ERROR_SPP( TEXT( "Trying to retrieve a value on a non-value node." ) );
		return S::null;
	}

	template<typename S>
	void NodeT<S>::setValue( const S& value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	inline void NodeT<S>::setValue( int value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	inline void NodeT<S>::setValue( unsigned int value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	inline void NodeT<S>::setValue( long long int value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	inline void NodeT<S>::setValue( unsigned long long int value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	inline void NodeT<S>::setValue( double value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	inline void NodeT<S>::setValue( bool value ) {
		ERROR_SPP( TEXT( "Trying to set a value on a non-value node." ) );
	}

	template<typename S>
	void NodeT<S>::setName( const S& name ) {
		if ( this -> parent ) {
			getParent() -> _setChildName( this, this -> name, name );
		}
		this -> name = name;
	}

	template<typename S>
	const S& NodeT<S>::getName() const {
		return this -> name;
	}

	template<typename S>
	inline NodeT<S>* NodeT<S>::getElementByName( const S& name ) const {
		return NULL;
	}

	template<typename S>
	Vector< NodeT<S>* > NodeT<S>::getElementsByName( const S& name ) const {
		return Vector<NodeT<S>*>();
	}

	template<typename S>
	Size NodeT<S>::getNbChildren() const {
		return Size( 0 );
	}

	template<typename S>
	void NodeT<S>::addChild( NodeT<S>* child ) {
		ERROR_SPP( TEXT( "Trying to add a child on a non Map/Array NodeMap." ) );
	}

	template<typename S>
	inline void NodeT<S>::addChild( const S& name, NodeT<S>* child ) {
		ERROR_SPP( TEXT( "Trying to add a child on a non Map/Array NodeMap." ) );
	}

	template<typename S>
	const Vector<NodeT<S>*>& NodeT<S>::getChildren() const {
		return NodeT<S>::emptyVector;
	}

	template<typename S>
	const Vector< NodeT<S>* >& NodeT<S>::getChildren( const S& name ) const {
		return NodeT<S>::emptyVector;
	}

	/*
	template<typename S>
	Vector< NodeT<S> * > NodeT<S>::getChildren( const S & name ) {
		return Vector<NodeT<S> *>();
	}
	*/

	template<typename S>
	const NodeT<S>* NodeT<S>::getChild( const S& name ) const {
		return const_cast< NodeT<S> * >( this ) ->getChild( name );
	}

	template<typename S>
	NodeT<S>* NodeT<S>::getChild( const S& name ) {
		return NULL;
	}

	template<typename S>
	const NodeT<S>* NodeT<S>::getChild( Size i ) const {
		return const_cast< NodeT<S> * >( this ) -> getChild( i );
	}

	template<typename S>
	NodeT<S>* NodeT<S>::getChild( Size i ) {
		return NULL;
	}

	template<typename S>
	bool NodeT<S>::deleteChild( NodeT<S>* child ) {
		return false;
	}

	template<typename S>
	bool NodeT<S>::deleteChild( Size i ) {
		return false;
	}

	template<typename S>
	NodeT<S>* NodeT<S>::removeChild( NodeT<S>* child ) {
		return NULL;
	}

	template<typename S>
	NodeT<S>* NodeT<S>::removeChild( Size i ) {
		return NULL;
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::writeJSON( Stream* fileStreamP, unsigned int indent, bool beautyfy ) const {
		Stream& stream( *fileStreamP );

		// Call the virtual protected method.
		_writeJSON<Stream, char>( stream, indent, beautyfy );

		return !( fileStreamP -> hasFailed() );
	}

	template<typename S>
	template<typename C>
	bool NodeT<S>::writeJSON( C& str, unsigned int indent, bool beautyfy ) const {
		return _writeJSON<C, C::ElemType>( str, indent, beautyfy );
	}

	template<typename S>
	template<typename S2>
	S2 NodeT<S>::toString( unsigned int indent, bool beautyfy ) const {
		S2 newString;
		newString.reserve( 128 );

		_writeJSON<S2, S2::ElemType>( newString, indent, beautyfy );
		return newString;
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeT<S>::_writeJSON( C& o, unsigned int indent, bool beautyfy ) const {
		if ( getType() == Type::Map ) {
			this -> toMap() -> _writeJSON<C, Elem>( o, indent, beautyfy );
		} else if ( getType() == Type::Array ) {
			this -> toArray() -> _writeJSON<C, Elem>( o, indent, beautyfy );
		} else if ( getType() == Type::Value ) {
			this -> toValue() -> _writeJSON<C, Elem>( o, indent, beautyfy );
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::read( Stream* stream, int verbose ) {
		switch ( this->type ) {
			case Type::Array:
				return this->toArray()->read( stream );
			case Type::Map:
				return this->toMap()->read( stream );
			case Type::Value:
				return this->toValue()->read( stream );
			default:
				return false;
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeT<S>::write( Stream* stream ) const {
		switch ( this->type ) {
			case Type::Array:
				return this->toArray()->write( stream );
			case Type::Map:
				return this->toMap()->write( stream );
			case Type::Value:
				return this->toValue()->write( stream );
			default:
				return false;
		}
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeT<S>::readJSON( const C** buffer, const EndFunc& endFunc ) {
		switch ( this->type ) {
			case Type::Array:
				return this->toArray()->readJSON<C, EndFunc>( buffer, endFunc );
			case Type::Map:
				return this->toMap()->readJSON<C, EndFunc>( buffer, endFunc );
			case Type::Value:
				return this->toValue()->readJSON<C, EndFunc>( buffer, endFunc );
			default:
				return false;
		}
	}

	template<typename S>
	bool NodeT<S>::writeFileJSON( const OS::Path& filePath ) const {
		IO::FileStream stream( filePath, IO::OpenMode::Write );
		if ( !stream.isOpen() ) {
			return false;
		}
		return writeJSON( &stream );
	}

	template<typename S>
	bool NodeT<S>::readFileJSON( const OS::Path& filePath, int verbose ) {
		_unload();

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Reading new JSON file \"%\"...", filePath ) ); }

		S strOut;
		if ( IO::readToString( filePath, &strOut, verbose ) == Size( -1 ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed.", filePath ) ); }

			_clear();
			return false;
		}

		if ( !readJSON( strOut ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed.", filePath ) ); }

			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success.", filePath ) ); }

		return true;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeT<S>::readJSON( const C* buffer, const EndFunc& endFunc ) {
		return readJSON( &buffer, endFunc );
	}

	template<typename S>
	bool NodeT<S>::readJSON( const S& str ) {
		const typename S::ElemType* buffer( str.toCString() );
		return readJSON<S::ElemType>( &buffer );
	}

	template<typename S>
	template<typename C>
	bool NodeT<S>::_expectChar( const C** buffer, const C& c ) {
		const C*& it( *buffer );

		if ( ( *it ) == c ) {
			it++;
			return true;
		} else {
			ERROR_SPP( String::format( TEXT( "[JSON ERROR] : Expected '%'." ), c ) );
			return false;
		}
	}

	template<typename S>
	template<typename Stream>
	inline bool NodeT<S>::_write( Stream* stream ) const {
		if ( !IO::write( stream, &this -> name ) )
			return false;
		return true;
	}

	template<typename S>
	template<typename Stream>
	inline bool NodeT<S>::_read( Stream* stream, int verbose ) {
		if ( !IO::read( stream, &this -> name, verbose - 1 ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename S>
	void NodeT<S>::_clear() {

	}

	template<typename S>
	void NodeT<S>::_unload() {

	}




















































	




	













	

	template<typename S>
	inline DocumentT<S>::DocumentT() :
		rootNode( NULL ) {}

	template<typename S>
	inline DocumentT<S>::DocumentT( const S& str ) :
		rootNode( NULL ) {
		readJSON( str );
	}

	template<typename S>
	inline DocumentT<S>::DocumentT( NodeT<S>* rootNode ) :
		rootNode( rootNode ) {}

	template<typename S>
	inline DocumentT<S>::~DocumentT() {
		if ( this->rootNode ) {
			delete this->rootNode;
		}
	}

	template<typename S>
	inline const NodeT<S>* DocumentT<S>::getRoot() const {
		return this->rootNode;
	}

	template<typename S>
	inline NodeT<S>* DocumentT<S>::getRoot() {
		return this->rootNode;
	}

	template<typename S>
	inline NodeT<S>* DocumentT<S>::getElementByName( const S& name ) const {
		if ( this->rootNode ) {
			return this->rootNode->getElementByName( name );
		}
		return NULL;
	}

	template<typename S>
	inline Vector<NodeT<S>*> DocumentT<S>::getElementsByName( const S& name ) const {
		if ( this->rootNode ) {
			return this->rootNode->getElementsByName( name );
		}
		return Vector<NodeT<S>*>();
	}

	template<typename S>
	inline bool DocumentT<S>::writeFileJSON( const OS::Path& filePath ) const {
		IO::FileStream stream( filePath, IO::OpenMode::Write );
		if ( !stream.isOpen() ) {
			return false;
		}
		if ( this->rootNode ) {
			return this->rootNode->writeJSON( &stream );
		}
		return true;
	}

	template<typename S>
	inline bool DocumentT<S>::readFileJSON( const OS::Path& filePath, int verbose ) {
		_unload();

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Reading new JSON file \"%\"...", filePath ) ); }

		S strOut;
		if ( !IO::readToString( filePath, &strOut ) != size_t( -1 ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed.", filePath ) ); }

			_unload();
			return false;
		}

		if ( !readJSON( strOut ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed.", filePath ) ); }

			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success.", filePath ) ); }

		return true;
	}

	template<typename S>
	inline bool DocumentT<S>::readJSON( const S& str ) {
		const typename S::ElemType* buffer( str.toCString() );
		return readJSON<S::ElemType>( &buffer );
	}

	template<typename S>
	template<typename Stream>
	inline bool DocumentT<S>::writeJSON( Stream* stream, unsigned int indent, bool beautyfy ) const {
		if ( this->rootNode ) {
			return this->rootNode->writeJSON( stream, indent, beautyfy );
		}
		return true;
	}

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::read( Stream* stream, int verbose ) {
		_unload();

		bool bIsRootNode;
		if ( !IO::read( stream, &bIsRootNode, verbose - 1 ) ) {
			return false;
		}
		if ( bIsRootNode ) {
			unsigned char rootNodeTypeUC;
			if ( !IO::read( stream, &rootNodeTypeUC, verbose - 1 ) ) {
				return false;
			}
			NodeT<S>::Type rootNodeType( static_cast< NodeT<S>::Type >( rootNodeTypeUC ) );
			switch ( rootNodeType ) {
				case NodeT<S>::Type::Map:
					{
						NodeMapT<S>* newRootNode( new NodeMapT<S>() );
						if ( !IO::read( stream, newRootNode, verbose - 1 ) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				case NodeT<S>::Type::Value:
					{
						NodeValueT<S>* newRootNode( new NodeValueT<S>() );
						if ( !IO::read( stream, newRootNode, verbose - 1 ) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				case NodeT<S>::Type::Array:
					{
						NodeArrayT<S>* newRootNode( new NodeArrayT<S>() );
						if ( !IO::read( stream, newRootNode, verbose - 1 ) ) {
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

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::write( Stream* stream ) const {
		bool bIsRootNode( this->rootNode );
		if ( !IO::write( stream, &bIsRootNode ) ) {
			return false;
		}
		if ( this->rootNode ) {
			NodeT<S>::Type rootNodeType( this->rootNode->getType() );
			unsigned char rootNodeTypeUC( static_cast< unsigned char >( rootNodeType ) );
			if ( !IO::write( stream, &rootNodeTypeUC ) ) {
				return false;
			}
			switch ( rootNodeType ) {
				case NodeT<S>::Type::Map:
					{
						NodeMapT<S>* rootNode( this->rootNode->toMap() );
						if ( !IO::write( stream, rootNode ) ) {
							return false;
						}
						break;
					}
				case NodeT<S>::Type::Value:
					{
						NodeValueT<S>* rootNode( this->rootNode->toValue() );
						if ( !IO::write( stream, rootNode ) ) {
							return false;
						}
						break;
					}
				case NodeT<S>::Type::Array:
					{
						NodeArrayT<S>* rootNode( this->rootNode->toArray() );
						if ( !IO::write( stream, rootNode ) ) {
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

	template<typename S>
	inline void DocumentT<S>::_unload() {
		if ( this->rootNode ) {
			delete this->rootNode;
			this->rootNode = NULL;
		}
	}

	template<typename S>
	template<typename C, typename EndFunc>
	inline bool DocumentT<S>::readJSON( const C** buffer, const EndFunc& endFunc ) {
		const C*& it( *buffer );

		// Can be empty.
		if ( endFunc( it ) ) {
			return true;
		}

		NodeT<S>* newNode( parseT<S, C, EndFunc>( &it, endFunc ) );

		if ( newNode ) {
			_unload();
			this->rootNode = newNode;
			return true;
		}

		return false;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	inline bool DocumentT<S>::readJSON( const C* buffer, const EndFunc& endFunc ) {
		return readJSON( &buffer, endFunc );
	}

	template<typename S>
	template<typename C>
	inline bool DocumentT<S>::writeJSON( C& str, unsigned int indent, bool beautyfy ) const {
		if ( this->rootNode ) {
			return this->rootNode->writeJSON( str, indent, beautyfy );
		}
		return true;
	}

	template<typename S>
	template<typename S2>
	inline S2 DocumentT<S>::toString( unsigned int indent, bool beautyfy ) const {
		if ( this->rootNode ) {
			return this->rootNode->toString( indent, beautyfy );
		} else {
			return S2::null;
		}
	}



}