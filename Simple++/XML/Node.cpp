#include "Node.h"

namespace XML {

	Param::Param( const UTF8String & name, const UTF8String & value ) : name(name), value(value) {

	}

	Param::Param() {

	}


	Param::Param( const Param & param ) : 
		name( param.name ),
		value( param.value )
	{

	}

	Param::Param( Param && param ) :
		name( Utility::toRValue( param.name ) ),
		value( Utility::toRValue( param.value ) ) {

	}

	Param::operator UTF8String() const {
		return toString();
	}

	Param & Param::operator=( const Param & param ) {
		this -> name = param.name;
		this -> value = param.value;
		return *this;
	}

	Param & Param::operator=( Param && param ) {
		this -> name = Utility::toRValue( param.name );
		this -> value = Utility::toRValue( param.value );
		return *this;
	}

	const UTF8String & Param::getName() const {
		return this -> name;
	}

	void Param::setName( const UTF8String & name ) {
		this -> name = name;
	}

	const UTF8String & Param::getValue() const {
		return this -> value;
	}

	void Param::setValue( const UTF8String & value ) {
		this -> value = value;
	}


	UTF8String Param::toString() const {
		if ( this -> value.getSize() ) {
			UTF8String newString;
			newString.reserve( this -> name.getSize() + this -> value.getSize() + 4 );
			newString << this -> name << char( '=' ) << char( '"' ) << this -> value << char( '"' );
			return newString;
		} else {
			return this -> name;
		}
	}


	bool Param::writeXML( std::fstream * fileStream ) const {
		this -> name.writeReadable( fileStream );
		if ( this -> value.getSize() ) {
			fileStream -> put( char( '=' ) );
			fileStream -> put( char( '"' ) );
			this -> value.writeReadable( fileStream );
			fileStream -> put( char( '"' ) );
		}
		return !( fileStream -> bad() );
	}

	bool Param::read( std::fstream * fileStream ) {
		if ( !IO::read( fileStream, &this -> name ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}


	bool Param::write( std::fstream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> name ) )
			return false;
		if ( !IO::write( fileStream, &this -> value ) )
			return false;
		return true;
	}

	void Param::_clear() {
		this -> name.clear();
		this -> value.clear();
	}















	Node::Node( ) : 
		type( Type::Element ),
		parent(NULL)
	{

	}

	Node::Node( const UTF8String & name, Type type ) :
		name( name ),
		type( type ),
		parent( NULL )
	{

	}

	Node::Node( const Node & node ) : 
		name( node.name ),
		id( node.id ),
		type( node.type ),
		parent(NULL)
	{
		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			Node * newNode( new Node( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		for ( auto it( node.paramsVector.getBegin() ); it != node.paramsVector.getEnd(); node.paramsVector.iterate( &it ) ) {
			Param * newParam( new Param( *( node.paramsVector.getValueIt( it ) ) ) );
			addParam( newParam );
		}
	}


	Node::Node( Node && node ) :
		name( Utility::toRValue( node.name ) ),
		id( Utility::toRValue( node.id ) ),
		type( Utility::toRValue( node.type ) ),
		paramsMap( Utility::toRValue( node.paramsMap ) ),
		paramsVector( Utility::toRValue( node.paramsVector ) ),
		childrenMap( Utility::toRValue( node.childrenMap ) ),
		childrenVector( Utility::toRValue( node.childrenVector ) ),
		parent( Utility::toRValue( node.parent ) )
	{
		node.childrenVector.clear();
		node.paramsVector.clear();
	}


	Node & Node::operator=( const Node & node ) {
		this -> name = node.name;
		this -> id = node.id;
		this -> type = node.type;
		this -> parent = NULL;

		for ( auto it( node.childrenVector.getBegin() ); it != node.childrenVector.getEnd(); node.childrenVector.iterate( &it ) ) {
			Node * newNode( new Node( *( node.childrenVector.getValueIt( it ) ) ) );
			addChild( newNode );
		}
		for ( auto it( node.paramsVector.getBegin() ); it != node.paramsVector.getEnd(); node.paramsVector.iterate( &it ) ) {
			Param * newParam( new Param( *( node.paramsVector.getValueIt( it ) ) ) );
			addParam( newParam );
		}
		return *this;
	}

	Node & Node::operator=( Node && node ) {
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


	Node::Type Node::getType() const {
		return this -> type;
	}


	const NodeText * Node::toText() const {
		return ( static_cast< const NodeText * >( this ) );
	}

	NodeText * Node::toText() {
		return ( static_cast< NodeText * >( this ) );
	}


	const Node * Node::getParent() const {
		return this -> parent;
	}


	Node * Node::getParent() {
		return this -> parent;
	}

	const UTF8String & Node::getValue() const {
		if ( getType() == Type::Text ) {
			return toText() -> getValue();
		} else if (this -> childrenVector.getSize() == 1 && this -> childrenVector[0] -> getType() == Type::Text)  {
			return this -> childrenVector[0] -> toText() -> getValue();
		} else {
			//Error, you shouldn't call this method, return an empty string
			static const UTF8String emptyString;
			return emptyString;
		}
	}


	void Node::setValue( const UTF8String & value ) {
		if ( getType() == Type::Text ) {
			this -> toText() -> setValue( value );
		} else {
			if ( this -> childrenVector.getSize() > 0 ) {
				// We are not a Text node, and we have at least one child, if the first one is a Text one, set it's value.
				if ( this -> childrenVector[0] -> getType() == Type::Text )
					this -> childrenVector[0] -> toText() -> setValue( value );
			} else {
				// We are not a Text node, and do not have any child, add one
				NodeText * newNode( new NodeText( value ) );
				addChild( newNode );
			}
		}
	}

	void Node::setName( const UTF8String & name ) {
		if ( this -> parent ) {
			this -> parent -> _setChildName( this, name );
		} else {
			this -> name = name;
		}
	}

	const UTF8String & Node::getName() const {
		return this -> name;
	}


	void Node::addParam( const Param & param ) {
		Param * newParam( new Param( param ) );

		this -> paramsMap.insert( newParam -> getName(), newParam );
		this -> paramsVector.push( newParam );
	}


	void Node::addParam( const UTF8String & name, const UTF8String & value ) {
		Param * newParam( new Param( name, value ) );

		this -> paramsMap.insert( newParam -> getName(), newParam );
		this -> paramsVector.push( newParam );
	}

	void Node::addParam( Param * param ) {
		static UTF8String idStr( "id" );
		if ( param -> getName() == idStr ) 
			setId( param -> getValue() );
		
		this -> paramsMap.insert( param -> getName(), param );
		this -> paramsVector.push( param );
	}

	Param * Node::getParam( const UTF8String & name ) {
		auto paramP = this -> paramsMap[name];
		if ( paramP ) return *paramP;
		else return NULL;
	}

	const Param * Node::getParam( const UTF8String & name ) const {
		auto paramP = this -> paramsMap[name];
		if ( paramP ) return *paramP;
		else return NULL;
	}


	Param & Node::getParam( typename Vector< Param * >::Size i ) {
		return *( this -> paramsVector.getValueI( i ) );
	}

	const Param & Node::getParam( typename Vector< Param * >::Size i ) const {
		return *( this -> paramsVector.getValueI( i ) );
	}


	bool Node::deleteParam( Param * param ) {
		if ( this -> paramsVector.eraseFirst( param ) ) {
			this -> paramsMap.eraseIndex( param -> getName() );
			delete param;
			return true;
		}
		return false;
	}


	bool Node::deleteParam( typename Vector< Param * >::Size i ) {
		if ( i >= this -> paramsVector.getSize() ) {
			return false;
		} else {
			Param * param( this -> paramsVector[i] );
			this -> paramsVector.eraseIndex( i );
			this -> paramsMap.eraseIndex( param -> getName() );
			delete param;
			return true;
		}
	}


	void Node::setId( const UTF8String & id ) {
		if ( this -> parent ) {
			this -> parent -> _setChildId( this, id );
		} else {
			this -> id = id;
		}
	}


	const UTF8String & Node::getId() const {
		return this -> id;
	}


	Vector< Node * > Node::getElementsById( const UTF8String & id ) const {
		Vector< Node * > nodeVector;
		nodeVector.reserve( 20 );

		if ( id == this -> id )
			nodeVector.push( const_cast< Node * >( this ) );

		_getElementsById( &nodeVector, id );
		return nodeVector;
	}


	Vector< Node * > Node::getElementsByName( const UTF8String & name ) const {
		Vector< Node * > nodeVector;
		nodeVector.reserve( 20 );

		if ( name == this -> name )
			nodeVector.push( const_cast< Node * >( this ) );

		_getElementsByName( &nodeVector, name );
		return nodeVector;
	}

	typename Vector< Param * >::Size Node::getNbChildren() const {
		return this -> childrenVector.getSize();
	}

	typename Vector< Node * >::Size Node::getNbParams() const {
		return this -> paramsVector.getSize();
	}

	void Node::addChild( Node * child ) {
		if ( child -> parent ) 
			child -> parent -> removeChild( child );
		if ( child -> getId().getSize() )
			this -> childrenByIdMap.insert( child -> getId(), child );
		
		child -> parent = this;
		this -> childrenMap.insert( child -> getName(), child );
		this -> childrenVector.push( child );
	}

	void Node::_clear() {
		_unload();

		this -> name.clear();
		this -> id.clear();

		this -> paramsMap.clear();
		this -> paramsVector.clear();

		this -> childrenMap.clear();
		this -> childrenVector.clear();
	}


	void Node::_unload() {
		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			delete this -> paramsVector.getValueIt( it );
		}
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			delete this -> childrenVector.getValueIt( it );
		}
	}

	const Vector< Node * > Node::getChild( const UTF8String & name ) const {
		auto childP = this -> childrenMap[name];
		if ( childP ) return *childP;
		else return NULL;
	}

	Vector< Node * > Node::getChild( const UTF8String & name ) {
		auto childP = this -> childrenMap[name];
		if ( childP ) return *childP;
		else return NULL;
	}


	const Node & Node::getChild( typename Vector< Node * >::Size i ) const {
		return *(this -> childrenVector.getValueI( i ));
	}


	Node & Node::getChild( typename Vector< Node * >::Size i ) {
		return *( this -> childrenVector.getValueI( i ) );
	}

	bool Node::deleteChild( Node * child ) {
		Node * childRemoved( removeChild( child ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}


	bool Node::deleteChild( typename Vector< Node * >::Size i ) {
		Node * childRemoved( removeChild( i ) );
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}


	Node * Node::removeChild( Node * child ) {
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


	Node * Node::removeChild( typename Vector< Node * >::Size i ) {
		if ( i >= this -> childrenVector.getSize() ) {
			return NULL;
		} else {
			Node * child( this -> childrenVector[i] );
			this -> childrenVector.eraseIndex( i );
			this -> childrenMap.eraseFirst( child -> getName(), child );
			if ( child -> getId().getSize() )
				this -> childrenByIdMap.eraseFirst( child -> getId(), child );
			child -> parent = NULL;
			return child;
		}
	}

	bool Node::writeXML( std::fstream * fileStream ) const {
		return _writeXML( fileStream, 0 );
	}

	bool Node::_writeXML( std::fstream * fileStream, unsigned int tabs ) const {
		if ( getType() == Type::Text )
			return this -> toText() -> writeXML( fileStream );

		/*if ( tabs > 0 )
			fileStream -> put( char( '\n' ) );*/


		for ( unsigned int i( 0 ); i < tabs; i++ )
			fileStream -> put( char( '\t' ) );

		fileStream -> put( char( '<' ) );
		this -> name.writeReadable( fileStream );

		for ( auto it( this -> paramsVector.getBegin() ); it != this -> paramsVector.getEnd(); this -> paramsVector.iterate( &it ) ) {
			fileStream -> put( char( ' ' ) );
			this -> paramsVector.getValueIt( it ) -> writeXML( fileStream );
		}

		// If we have children, it's not an self closing one
		if ( this -> childrenVector.getSize() ) {
			fileStream -> put( char( '>' ) );
			/*if ( getNbChildren() > 1 )
				fileStream -> put( char( '\n' ) );*/


			for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
				if (  getNbChildren() > 1 )
					fileStream -> put( char( '\n' ) );
				this -> childrenVector.getValueIt( it ) -> _writeXML( fileStream, tabs + 1 );
			}


			// Now Close
			if ( getNbChildren() > 1 ) {
				fileStream -> put( char( '\n' ) );
				for ( unsigned int i( 0 ); i < tabs; i++ )
					fileStream -> put( char( '\t' ) );
			}

			
			fileStream -> put( char( '<' ) );
			fileStream -> put( char( '/' ) );
			this -> name.writeReadable( fileStream );
			fileStream -> put( char( '>' ) );
		} else {
			fileStream -> put( char( '/' ) );
			fileStream -> put( char( '>' ) );
		}


		return !( fileStream -> bad() );

	}


	

	bool Node::read( std::fstream * fileStream ) {
		if ( getType() == Type::Text )
			return this -> toText() -> read( fileStream );
		else
			return _read( fileStream );
	}

	bool Node::_read( std::fstream * fileStream ) {
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
		Vector< Param * >::Size nbParams;
		if ( !IO::read( fileStream, &nbParams ) ) {
			_clear();
			return false;
		}
		nbParams = Math::min( nbParams, Vector< Param * >::Size( 1000 ) );
		for ( Vector< Param * >::Size i( 0 ); i < nbParams; i++ ) {
			Param * newParam( new Param() );
			if ( !IO::read( fileStream, newParam ) ) {
				delete newParam;
				_clear();
				return false;
			}
			addParam( newParam );
		}

		// Read the children
		Vector< Node * >::Size nbChilds;
		if ( !IO::read( fileStream, &nbChilds ) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min( nbChilds, Vector< Node * >::Size( 1000 ) );
		for ( Vector< Node * >::Size i( 0 ); i < nbChilds; i++ ) {
			Type newNodeType;
			if ( !IO::read( fileStream, &newNodeType ) ) {
				_clear();
				return false;
			}
			if ( newNodeType == Type::Text ) {
				NodeText * newNode( new NodeText() );
				newNode -> parent = this;
				if ( !IO::read( fileStream, newNode ) ) {
					delete newNode;
					_clear();
					return false;
				}
				this -> childrenVector.push( newNode );
				this -> childrenMap.insert( newNode -> getName(), newNode );
			} else {
				Node * newNode( new Node() );
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


	bool Node::_setChildName( Node * child, const UTF8String & name ) {
		if ( this -> childrenMap.eraseFirst( child -> getName(), child ) ) {
			child -> name = name;
			this -> childrenMap.insert( child -> getName(), child );
			return true;
		} else {
			return false;
		}
	}


	bool Node::_setChildId( Node * child, const UTF8String & id ) {
		this -> childrenByIdMap.eraseFirst( child -> getId(), child );
		child -> id = id;
		if ( id.getSize() ) 
			this -> childrenByIdMap.insert( child -> getId(), child );
		return true;
	}


	void Node::_getElementsById( Vector < Node * > * nodeVector, const UTF8String & id ) const {
		const Vector < Node * > * vectorFounded( this -> childrenByIdMap[id] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			this -> childrenVector.getValueIt( it ) -> _getElementsById( nodeVector, id );
		}
	}


	void Node::_getElementsByName( Vector < Node * > * nodeVector, const UTF8String & name ) const {
		const Vector < Node * > * vectorFounded( this -> childrenMap[name] );
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat( *vectorFounded );
		}
		// Recursively call every child too
		for ( auto it( this -> childrenVector.getBegin() ); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate( &it ) ) {
			this -> childrenVector.getValueIt( it ) -> _getElementsByName( nodeVector, name );
		}
	}

	bool Node::write( std::fstream * fileStream ) const {
		if ( getType() == Type::Text )
			return this -> toText() -> write( fileStream );
		else
			return _write( fileStream );
	}

	bool Node::_write( std::fstream * fileStream ) const {
		

		if ( !IO::write( fileStream, &this -> name ) )
			return false;
		if ( !IO::write( fileStream, &this -> id ) )
			return false;

		Vector< Param * >::Size nbParams( this -> paramsVector.getSize() );
		Vector< Node * >::Size nbChilds( this -> childrenVector.getSize() );

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








	/************************************************************************/
	/* NodeText                                                             */
	/************************************************************************/

	bool NodeText::writeXML( std::fstream * fileStream ) const {
		return this -> value.writeReadable( fileStream );
	}


	bool NodeText::read( std::fstream * fileStream ) {
		this -> value.clear();

		if ( !Node::_read( fileStream ) ) {
			return false;
		}
		if ( !IO::read( fileStream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}


	bool NodeText::write( std::fstream * fileStream ) const {
		if ( !Node::_write( fileStream ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> value ) ) 
			return false;
		return true;
	}

	void NodeText::_clear() {
		Node::_clear();
		this -> value.clear();
	}

	NodeText::NodeText() : Node( UTF8String( "#text" ), Node::Type::Text ) {

	}


	NodeText::NodeText( const UTF8String & value ) : Node( UTF8String( "#text" ), Node::Type::Text ),
		value( value )
	{

	}


	NodeText::NodeText( const NodeText & node ) : Node(node),
		value( node.value )
	{

	}


	NodeText::NodeText( NodeText && node ) : Node(Utility::toRValue(node)),
		value( Utility::toRValue( node.value ) )
	{

	}


	NodeText & NodeText::operator=( const NodeText & node ) {
		Node::operator=( node );
		this -> value = node.value;
		return *this;
	}


	NodeText & NodeText::operator=( NodeText && node ) {
		Node::operator=( Utility::toRValue( node ) );
		this -> value = Utility::toRValue( node.value );
		return *this;
	}

	const UTF8String & NodeText::getValue() const {
		return this -> value;
	}


	void NodeText::setValue( const UTF8String & value ) {
		this -> value = value;
	}

}
