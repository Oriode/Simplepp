#include "Node.h"
namespace JSON {

	template<typename S>
	const Vector< BasicNodeT<S>* > BasicNodeT<S>::emptyVector = Vector< BasicNodeT<S>* >();


	template<typename S>
	BasicNodeT<S>::BasicNodeT(typename BasicNodeT<S>::Type type) :
		type(type),
		parent(NULL) {

		// Ensure S is a derived of BasicString.
		static_assert( Utility::isBase<BasicString<S::ElemType>, S>::value );
	}

	template<typename S>
	BasicNodeT<S>::BasicNodeT(const S& name, typename BasicNodeT<S>::Type type) :
		name(name),
		type(type) {

	}

	template<typename S>
	BasicNodeT<S>::BasicNodeT(const BasicNodeT<S>& node) :
		type(node.type),
		name(node.name),
		parent(NULL) {

	}

	template<typename S>
	BasicNodeT<S>::BasicNodeT(BasicNodeT<S>&& node) :
		type(Utility::toRValue(node.type)),
		name(Utility::toRValue(node.name)),
		parent(Utility::toRValue(node.parent)) {}

	template<typename S>
	BasicNodeT<S>::~BasicNodeT() {

	}

	template<typename S>
	BasicNodeT<S>& BasicNodeT<S>::operator=(const BasicNodeT<S>& node) {
		this -> type = node.type;
		this -> name = name;
		this -> parent = NULL;

		return *this;
	}

	template<typename S>
	BasicNodeT<S>& BasicNodeT<S>::operator=(BasicNodeT<S>&& node) {
		this -> type = Utility::toRValue(node.type);
		this -> name = Utility::toRValue(node.name);
		this -> parent = Utility::toRValue(node.parent);

		return *this;
	}

	template<typename S>
	typename BasicNodeT<S>::Type BasicNodeT<S>::getType() const {
		return this -> type;
	}

	template<typename S>
	const NodeValueT<S>* BasicNodeT<S>::toValue() const {
		ASSERT(this -> getType() == Type::Value);
		return reinterpret_cast< const NodeValueT<S> * >( this );
	}

	template<typename S>
	NodeValueT<S>* BasicNodeT<S>::toValue() {
		ASSERT(this -> getType() == Type::Value);
		return reinterpret_cast< NodeValueT<S> * >( this );
	}

	template<typename S>
	const NodeArrayT<S>* BasicNodeT<S>::toArray() const {
		ASSERT(this -> getType() == Type::Array);
		return reinterpret_cast< const NodeArrayT<S> * >( this );
	}

	template<typename S>
	NodeArrayT<S>* BasicNodeT<S>::toArray() {
		ASSERT(this -> getType() == Type::Array);
		return reinterpret_cast< NodeArrayT<S> * >( this );
	}

	template<typename S>
	inline const NodeMapT<S>* BasicNodeT<S>::toMap() const {
		ASSERT(this -> getType() == Type::Map);
		return reinterpret_cast< const NodeMapT<S> * >( this );
	}

	template<typename S>
	inline NodeMapT<S>* BasicNodeT<S>::toMap() {
		ASSERT(this -> getType() == Type::Map);
		return reinterpret_cast< NodeMapT<S> * >( this );
	}

	template<typename S>
	const NodeMapT<S>* BasicNodeT<S>::getParent() const {
		return this -> parent;
	}

	template<typename S>
	NodeMapT<S>* BasicNodeT<S>::getParent() {
		return this -> parent;
	}

	template<typename S>
	const S& BasicNodeT<S>::getValue() const {
		ERROR(TEXT("Trying to retrieve a value on a non-value node."));
		return S::null;
	}

	template<typename S>
	void BasicNodeT<S>::setValue(const S& value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	inline void BasicNodeT<S>::setValue(int value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	inline void BasicNodeT<S>::setValue(unsigned int value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	inline void BasicNodeT<S>::setValue(long long int value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	inline void BasicNodeT<S>::setValue(unsigned long long int value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	inline void BasicNodeT<S>::setValue(double value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	inline void BasicNodeT<S>::setValue(bool value) {
		ERROR(TEXT("Trying to set a value on a non-value node."));
	}

	template<typename S>
	void BasicNodeT<S>::setName(const S& name) {
		if ( this -> parent ) {
			getParent() -> _setChildName(this, this -> name, name);
		}
		this -> name = name;
	}

	template<typename S>
	const S& BasicNodeT<S>::getName() const {
		return this -> name;
	}

	template<typename S>
	inline BasicNodeT<S>* BasicNodeT<S>::getElementByName(const S& name) const {
		return NULL;
	}

	template<typename S>
	Vector< BasicNodeT<S>* > BasicNodeT<S>::getElementsByName(const S& name) const {
		return Vector<BasicNodeT<S>*>();
	}

	template<typename S>
	Size BasicNodeT<S>::getNbChildren() const {
		return Size(0);
	}

	template<typename S>
	void BasicNodeT<S>::addChild(BasicNodeT<S>* child) {
		ERROR(TEXT("Trying to add a child on a non Map/Array NodeMap."));
	}

	template<typename S>
	inline void BasicNodeT<S>::addChild(const S& name, BasicNodeT<S>* child) {
		ERROR(TEXT("Trying to add a child on a non Map/Array NodeMap."));
	}

	template<typename S>
	const Vector<BasicNodeT<S>*>& BasicNodeT<S>::getChildren() const {
		return BasicNodeT<S>::emptyVector;
	}

	template<typename S>
	const Vector< BasicNodeT<S>* >& BasicNodeT<S>::getChildren(const S& name) const {
		return BasicNodeT<S>::emptyVector;
	}

	/*
	template<typename S>
	Vector< BasicNodeT<S> * > BasicNodeT<S>::getChildren( const S & name ) {
		return Vector<BasicNodeT<S> *>();
	}
	*/

	template<typename S>
	const BasicNodeT<S>* BasicNodeT<S>::getChild(const S& name) const {
		return const_cast< BasicNodeT<S> * >( this ) ->getChild(name);
	}

	template<typename S>
	BasicNodeT<S>* BasicNodeT<S>::getChild(const S& name) {
		return NULL;
	}

	template<typename S>
	const BasicNodeT<S>* BasicNodeT<S>::getChild(Size i) const {
		return const_cast< BasicNodeT<S> * >( this ) -> getChild(i);
	}

	template<typename S>
	BasicNodeT<S>* BasicNodeT<S>::getChild(Size i) {
		return NULL;
	}

	template<typename S>
	bool BasicNodeT<S>::deleteChild(BasicNodeT<S>* child) {
		return false;
	}

	template<typename S>
	bool BasicNodeT<S>::deleteChild(Size i) {
		return false;
	}

	template<typename S>
	BasicNodeT<S>* BasicNodeT<S>::removeChild(BasicNodeT<S>* child) {
		return NULL;
	}

	template<typename S>
	BasicNodeT<S>* BasicNodeT<S>::removeChild(Size i) {
		return NULL;
	}

	template<typename S>
	template<typename Stream>
	bool BasicNodeT<S>::writeJSON(Stream* fileStreamP, unsigned int indent, bool beautyfy) const {
		Stream& stream(*fileStreamP);

		// Call the virtual protected method.
		_writeJSON<Stream, char>(stream, indent, beautyfy);

		return !( fileStreamP -> hasFailed() );
	}

	template<typename S>
	template<typename C>
	bool BasicNodeT<S>::writeJSON(C& str, unsigned int indent, bool beautyfy) const {
		return _writeJSON<C, C::ElemType>(str, indent, beautyfy);
	}

	template<typename S>
	template<typename S2>
	S2 BasicNodeT<S>::toString(unsigned int indent, bool beautyfy) const {
		S2 newString;
		newString.reserve(128);

		_writeJSON<S2, S2::ElemType>(newString, indent, beautyfy);
		return newString;
	}

	template<typename S>
	template<typename C, typename Elem>
	void BasicNodeT<S>::_writeJSON(C& o, unsigned int indent, bool beautyfy) const {
		if ( getType() == Type::Map ) {
			this -> toMap() -> _writeJSON<C, Elem>(o, indent, beautyfy);
		} else if ( getType() == Type::Array ) {
			this -> toArray() -> _writeJSON<C, Elem>(o, indent, beautyfy);
		} else if ( getType() == Type::Value ) {
			this -> toValue() -> _writeJSON<C, Elem>(o, indent, beautyfy);
		}
	}

	template<typename S>
	template<typename Stream>
	bool BasicNodeT<S>::read(Stream* stream) {
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

	template<typename S>
	template<typename Stream>
	bool BasicNodeT<S>::write(Stream* stream) const {
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

	template<typename S>
	template<typename C, typename EndFunc>
	bool BasicNodeT<S>::readJSON(const C** buffer, const EndFunc& endFunc) {
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

	template<typename S>
	bool BasicNodeT<S>::writeFileJSON(const OS::Path& filePath) const {
		IO::FileStream stream(filePath, IO::OpenMode::Write);
		if ( !stream.isOpen() ) {
			return false;
		}
		return writeJSON(&stream);
	}

	template<typename S>
	bool BasicNodeT<S>::readFileJSON(const OS::Path& filePath) {
		_unload();

		S strOut;
		if ( IO::readToString(filePath, &strOut) != size_t(-1) ) {
			return readJSON(strOut);
		} else {
			_clear();
			return false;
		}
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool BasicNodeT<S>::readJSON(const C* buffer, const EndFunc& endFunc) {
		return readJSON(&buffer, endFunc);
	}

	template<typename S>
	bool BasicNodeT<S>::readJSON(const S& str) {
		const typename S::ElemType* buffer(str.toCString());
		return readJSON<S::ElemType>(&buffer);
	}

	template<typename S>
	template<typename C>
	bool BasicNodeT<S>::_expectChar(const C** buffer, const C& c) {
		const C*& it(*buffer);

		if ( ( *it ) == c ) {
			it++;
			return true;
		} else {
			ERROR(String::format(TEXT("[JSON ERROR] : Expected '%'."), c));
			return false;
		}
	}

	template<typename S>
	template<typename Stream>
	inline bool BasicNodeT<S>::_write(Stream* stream) const {
		if ( !IO::write(stream, &this -> name) )
			return false;
		return true;
	}

	template<typename S>
	template<typename Stream>
	inline bool BasicNodeT<S>::_read(Stream* stream) {
		if ( !IO::read(stream, &this -> name) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename S>
	void BasicNodeT<S>::_clear() {

	}

	template<typename S>
	void BasicNodeT<S>::_unload() {

	}




















































	template<typename S>
	NodeMapT<S>::NodeMapT() :
		BasicNodeT<S>(Type::Map) {

	}

	template<typename S>
	NodeMapT<S>::NodeMapT(const S& name) :
		BasicNodeT<S>(name, Type::Map) {

	}

	template<typename S>
	NodeMapT<S>::NodeMapT(const S& name, const S& value) :
		BasicNodeT<S>(name, Type::Map) {

	}

	template<typename S>
	NodeMapT<S>::NodeMapT(const NodeMapT<S>& node) :
		BasicNodeT<S>(node) {
		for ( auto it(node.childrenVector.getBegin()); it != node.childrenVector.getEnd(); node.childrenVector.iterate(&it) ) {
			BasicNodeT<S>* newNode(new BasicNodeT<S>(*( node.childrenVector.getValueIt(it) )));
			addChild(newNode);
		}
	}

	template<typename S>
	NodeMapT<S>::NodeMapT(NodeMapT<S>&& node) :
		BasicNodeT<S>(Utility::toRValue(node)),
		childrenMap(Utility::toRValue(node.childrenMap)),
		childrenVector(Utility::toRValue(node.childrenVector)) {
		node.childrenVector.clear();
	}

	template<typename S>
	NodeMapT<S>::~NodeMapT() {
		_unload();
	}

	template<typename S>
	NodeMapT<S>& NodeMapT<S>::operator=(const NodeMapT<S>& node) {
		BasicNodeT<S>::operator=(node);

		for ( auto it(node.childrenVector.getBegin()); it != node.childrenVector.getEnd(); node.childrenVector.iterate(&it) ) {
			BasicNodeT<S>* newNode(new BasicNodeT<S>(*( node.childrenVector.getValueIt(it) )));
			addChild(newNode);
		}
		return *this;
	}

	template<typename S>
	NodeMapT<S>& NodeMapT<S>::operator=(NodeMapT<S>&& node) {
		BasicNodeT<S>::operator=(Utility::toRValue(node));

		this -> childrenVector = Utility::toRValue(node.childrenVector);
		this -> childrenMap = Utility::toRValue(node.childrenMap);

		node.childrenVector.clear();

		return *this;
	}

	template<typename S>
	inline BasicNodeT<S>* NodeMapT<S>::getElementByName(const S& name) const {
		if ( name == this -> name )
			return const_cast< NodeMapT<S> * >( this );
		else
			return _getElementByName(name);
	}

	template<typename S>
	Vector< BasicNodeT<S>* > NodeMapT<S>::getElementsByName(const S& name) const {
		Vector< BasicNodeT<S>* > nodeVector;
		nodeVector.reserve(20);

		if ( name == this -> name )
			nodeVector.push(const_cast< NodeMapT<S> * >( this ));

		_getElementsByName(&nodeVector, name);
		return nodeVector;
	}

	template<typename S>
	Size NodeMapT<S>::getNbChildren() const {
		return this -> childrenVector.getSize();
	}

	template<typename S>
	void NodeMapT<S>::addChild(BasicNodeT<S>* child) {
		if ( child != NULL ) {
			if ( child -> getParent() )
				child -> getParent() -> removeChild(child);

			if ( child -> getName().getSize() ) {
				this -> childrenMap.insert(child -> getName(), child);
			}
		} else {
			child = new BasicNodeT<S>(Type::Null);
		}

		child -> parent = this;

		this -> childrenVector.push(child);
	}

	template<typename S>
	inline void NodeMapT<S>::addChild(const S& name, BasicNodeT<S>* child) {
		child->setName(name);
		addChild(child);
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
		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			BasicNodeT<S>* node(this -> childrenVector.getValueIt(it));

			delete node;
		}
	}

	template<typename S>
	const Vector<BasicNodeT<S>*>& NodeMapT<S>::getChildren() const {
		return this ->childrenVector;
	}

	template<typename S>
	const Vector< BasicNodeT<S>* >& NodeMapT<S>::getChildren(const S& name) const {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return BasicNodeT<S>::emptyVector;
	}

	/*
	template<typename S>
	Vector< BasicNodeT<S> * > NodeMapT<S>::getChildren( const S & name ) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) return *childP;
		else return Vector<BasicNodeT<S> *>();
	}
	*/

	template<typename S>
	const BasicNodeT<S>* NodeMapT<S>::getChild(const S& name) const {
		return const_cast< NodeMapT<S> * >( this ) ->getChild(name);
	}

	template<typename S>
	BasicNodeT<S>* NodeMapT<S>::getChild(const S& name) {
		auto childP = this -> childrenMap[ name ];
		if ( childP ) {
			Vector<BasicNodeT<S>* > childVector(*childP);
			if ( childVector.getSize() > 0 ) {
				return childVector[ 0 ];
			}
		}
		return NULL;
	}

	template<typename S>
	const BasicNodeT<S>* NodeMapT<S>::getChild(Size i) const {
		return const_cast< NodeMapT<S> * >( this ) -> getChild(i);
	}

	template<typename S>
	BasicNodeT<S>* NodeMapT<S>::getChild(Size i) {
		if ( i < this->childrenVector.getSize() ) {
			return this->childrenVector.getValueI(i);
		} else {
			return NULL;
		}
	}

	template<typename S>
	bool NodeMapT<S>::deleteChild(BasicNodeT<S>* child) {
		BasicNodeT<S>* childRemoved(removeChild(child));
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	bool NodeMapT<S>::deleteChild(Size i) {
		BasicNodeT<S>* childRemoved(removeChild(i));
		if ( childRemoved ) {
			delete childRemoved;
			return true;
		} else {
			return false;
		}
	}

	template<typename S>
	BasicNodeT<S>* NodeMapT<S>::removeChild(BasicNodeT<S>* child) {
		if ( this -> childrenVector.eraseFirst(child) ) {
			if ( child -> getName().getSize() )
				this -> childrenMap.eraseFirst(child -> getName(), child);
			child -> parent = NULL;
			return child;
		} else {
			return NULL;
		}
	}

	template<typename S>
	BasicNodeT<S>* NodeMapT<S>::removeChild(Size i) {
		if ( i >= this -> childrenVector.getSize() ) {
			return NULL;
		} else {
			BasicNodeT<S>* child(this -> childrenVector[ i ]);
			this -> childrenVector.eraseI(i);
			if ( child ) {
				if ( child -> getName().getSize() )
					this -> childrenMap.eraseFirst(child -> getName(), child);
				child -> parent = NULL;
			}

			return child;
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeMapT<S>::read(Stream* stream) {
		_unload();

		this -> childrenMap.clear();
		this -> childrenVector.clear();

		if ( !BasicNodeT<S>::_read(stream) ) {
			_clear();
			return false;
		}


		// Read the children
		Size nbChilds;
		if ( !IO::read(stream, &nbChilds) ) {
			_clear();
			return false;
		}
		nbChilds = Math::min(nbChilds, Size(1000));
		for ( Size i(0); i < nbChilds; i++ ) {
			bool isNull;
			if ( !IO::read(stream, &isNull) ) {
				_clear();
				return false;
			}
			if ( isNull ) {
				this -> childrenVector.push(NULL);
			} else {
				Type newNodeType;
				if ( !IO::read(stream, &newNodeType) ) {
					_clear();
					return false;
				}


				switch ( newNodeType ) {
					case Type::Map:
						{
							NodeMapT<S>* newNode(new NodeMapT<S>());
							newNode -> parent = this;
							if ( !IO::read(stream, newNode) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push(newNode);
							if ( newNode -> getName().getSize() )
								this -> childrenMap.insert(newNode -> getName(), newNode);
							break;
						}
					case Type::Value:
						{
							NodeValueT<S>* newNode(new NodeValueT<S>());
							newNode -> parent = this;
							if ( !IO::read(stream, newNode) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push(newNode);
							if ( newNode -> getName().getSize() )
								this -> childrenMap.insert(newNode -> getName(), newNode);
							break;
						}
					case Type::Array:
						{
							NodeArrayT<S>* newNode(new NodeArrayT<S>());
							newNode -> parent = this;
							if ( !IO::read(stream, newNode) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push(newNode);
							if ( newNode -> getName().getSize() )
								this -> childrenMap.insert(newNode -> getName(), newNode);
							break;
						}
					default:
						{
							BasicNodeT<S>* newNode(new BasicNodeT<S>(newNodeType));
							newNode -> parent = this;
							if ( !IO::read(stream, newNode) ) {
								delete newNode;
								_clear();
								return false;
							}
							this -> childrenVector.push(newNode);
							break;
						}
				}
			}
		}

		return true;
	}


	template<typename S>
	bool NodeMapT<S>::_setChildName(BasicNodeT<S>* child, const S& oldName, const S& newName) {
		if ( oldName.getSize() ) {
			if ( !this -> childrenMap.eraseFirst(oldName, child) ) {
				return false;
			}
		}
		if ( child -> getName().getSize() )
			this -> childrenMap.insert(newName, child);
		return true;
	}

	template<typename S>
	void NodeMapT<S>::_getElementsByName(Vector < BasicNodeT<S>* >* nodeVector, const S& name) const {
		const Vector < BasicNodeT<S>* >* vectorFounded(this -> childrenMap[ name ]);
		if ( vectorFounded ) {
			// Concat the new one with what we already have
			nodeVector -> concat(*vectorFounded);
		}
		// Recursively call every child too
		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			BasicNodeT<S>* child(this -> childrenVector.getValueIt(it));
			if ( child -> getType() == Type::Map ) {
				child -> toMap() -> _getElementsByName(nodeVector, name);
			}
		}
	}

	template<typename S>
	inline BasicNodeT<S>* NodeMapT<S>::_getElementByName(const S& name) const {
		const Vector < BasicNodeT<S>* >* vectorFounded(this -> childrenMap[ name ]);
		if ( vectorFounded ) {
			return vectorFounded->getFirst();
		}

		// Recursively call every child too
		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			BasicNodeT<S>* child(this -> childrenVector.getValueIt(it));
			if ( child -> getType() == Type::Map ) {
				BasicNodeT<S>* foundedElement(child -> toMap() -> _getElementByName(name));
				if ( foundedElement ) {
					return foundedElement;
				}
			}
		}
		return NULL;
	}

	template<typename S>
	template<typename Stream>
	bool NodeMapT<S>::write(Stream* stream) const {
		if ( !BasicNodeT<S>::_write(stream) ) {
			return false;
		}


		Size nbChilds(this -> childrenVector.getSize());

		if ( !IO::write(stream, &nbChilds) )
			return false;
		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			bool isNull(*it == NULL);
			if ( !IO::write(stream, &isNull) )
				return false;
			if ( !isNull ) {
				Type type(this -> childrenVector.getValueIt(it) -> getType());
				if ( !IO::write(stream, &type) )
					return false;
				if ( !IO::write(stream, this -> childrenVector.getValueIt(it)) )
					return false;
			}
		}

		return true;
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeMapT<S>::_writeJSON(C& o, unsigned int indent, bool beautyfy) const {

		if ( this -> getName().getSize() ) {
			o << Elem('"');
			o << this -> getName();
			o << Elem('"');
			o << Elem(':');
			if ( beautyfy ) {
				o << Elem(' ');
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
		o << Elem('{');
		if ( beautyfy ) {
			if ( this -> childrenVector.getSize() ) {
				o << Elem('\n');
				for ( unsigned int i(0); i < indent + 1; i++ ) {
					o << Elem('\t');
				}
			}
		}

		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			if ( it != this -> childrenVector.getBegin() ) {
				o << Elem(',');

				if ( beautyfy ) {
					o << Elem('\n');

					for ( unsigned int i(0); i < indent + 1; i++ ) {
						o << Elem('\t');
					}
				}
			}

			BasicNodeT<S>* child(this -> childrenVector.getValueIt(it));
			child -> _writeJSON<C, Elem>(o, indent + 1, beautyfy);
		}

		if ( beautyfy ) {
			if ( this -> childrenVector.getSize() ) {
				o << Elem('\n');
				for ( unsigned int i(0); i < indent; i++ ) {
					o << Elem('\t');
				}
			}
		}

		o << Elem('}');
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeMapT<S>::readJSON(const C** buffer, const EndFunc& endFunc) {
		struct FunctorNodeName {
			bool operator()(const C& c) { return c != C('"') && c != C('\t') && c != C('\n'); }
		};
		struct FunctorContentQuote {
			bool operator()(const C& c) { return c != C('"'); }
		};
		struct FunctorContent {
			bool operator()(const C& c) { return c != C(',') && c != C('}') && c != C(']') && c != C(' '); }
		};
		struct FunctorSpace {
			bool operator()(const C& c) { return c == C('\n') || c == C('\t') || c == C(' '); }
		};
		struct FunctorNoSpace {
			bool operator()(const C& c) { return c != C('<') && c != C('\n') && c != C('\t') && c != C(' '); }
		};
		static FunctorNodeName functorNodeName;
		static FunctorContentQuote functorContentQuote;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		static const S nullString("null");

		const C*& it(*buffer);

		// Skip spaces.
		while ( functorSpace(*it) ) it++;

		if ( !_expectChar(&it, C('{')) ) return false;

		// if ( ( *it ) == C( '{' ) ) {
		// Map NodeMap.
		// it++;

		while ( true ) {
			// Skip spaces.
			while ( functorSpace(*it) ) it++;

			if ( ( *it ) == C('"') ) {
				it++;

				const C* beginIt(it);
				while ( true ) {
					if ( endFunc(it) ) {
						ERROR(TEXT("[JSON Error] : Unexpected buffer end."));
						return false;
					}
					if ( !functorNodeName(*it) )
						break;
					it++;
				}

				// If a name was founded.
				if ( beginIt != it ) {
					// We founded a name.
					S nodeName(beginIt, Size(it - beginIt));


					if ( !_expectChar(&it, C('"')) ) return false;
					while ( functorSpace(*it) ) it++;
					if ( !_expectChar(&it, C(':')) ) return false;

					BasicNodeT<S>* newNode(parseT<S, C, EndFunc>(&it, endFunc));
					if ( newNode ) {
						newNode -> setName(nodeName);
						this -> addChild(newNode);
					} else {
						ERROR(String::format(TEXT("[JSON Error] : Unable to parse the property \"%\"."), nodeName));
						return false;
					}

				} else {
					ERROR(TEXT("Expected property name."));
					return false;
				}

				while ( functorSpace(*it) ) it++;

				if ( ( *it ) == C(',') ) {
					it++;
					while ( functorSpace(*it) ) it++;
					continue;
				} else {
					if ( !_expectChar(&it, C('}')) ) return false;
					return true;
				}
			} else {
				if ( !_expectChar(&it, C('}')) ) return false;
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
					ERROR( TEXT( "[JSON Error] : Unexpected buffer end." ) );
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
					ERROR( TEXT( "[JSON Error] : Unexpected buffer end." ) );
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
	bool NodeMapT<S>::readJSON(const C* buffer, const EndFunc& endFunc) {
		return BasicNodeT<S>::readJSON<C, EndFunc>(buffer, endFunc);
	}

	template<typename S>
	bool NodeMapT<S>::readJSON(const S& str) {
		return BasicNodeT<S>::readJSON(str);
	}




	/************************************************************************/
	/* NodeValueT<S>                                                         */
	/************************************************************************/

	template<typename S>
	NodeValueT<S>::NodeValueT() :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		bAddQuotes(true) {

	}

	template<typename S>
	NodeValueT<S>::NodeValueT(const S& value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(value),
		bAddQuotes(true) {}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(value),
		bAddQuotes(false) {}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(unsigned int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(value),
		bAddQuotes(false) {}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(long long int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(unsigned long long int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(double value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(bool value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {}

	template<typename S>
	NodeValueT<S>::NodeValueT(const S& name, const S& value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(value),
		bAddQuotes(true) {
		this -> name = name;
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(const S& name, int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(value),
		bAddQuotes(false) {
		this -> name = name;
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(const S& name, unsigned int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(value),
		bAddQuotes(false) {
		this -> name = name;
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(const S& name, long long int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {
		this -> name = name;
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(const S& name, unsigned long long int value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {
		this -> name = name;
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(const S& name, double value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {
		this -> name = name;
	}

	template<typename S>
	inline NodeValueT<S>::NodeValueT(const S& name, bool value) :
		BasicNodeT<S>(BasicNodeT<S>::Type::Value),
		value(S::toString(value)),
		bAddQuotes(false) {
		this -> name = name;
	}

	template<typename S>
	NodeValueT<S>::NodeValueT(const NodeValueT<S>& node) :
		NodeT(node),
		value(node.value),
		bAddQuotes(node.bAddQuotes),
		name(node.name) {

	}

	template<typename S>
	NodeValueT<S>::NodeValueT(NodeValueT<S>&& node) :
		NodeT(Utility::toRValue(node)),
		value(Utility::toRValue(node.value)),
		bAddQuotes(Utility::toRValue(node.bAddQuotes)),
		name(Utility::toRValue(node.name)) {

	}

	template<typename S>
	const S& NodeValueT<S>::getValue() const {
		return this -> value;
	}

	template<typename S>
	void NodeValueT<S>::setValue(const S& value) {
		this -> value = value;
		this -> bAddQuotes = true;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue(int value) {
		this -> value = S::toString(value);
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue(unsigned int value) {
		this -> value = S::toString(value);
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue(long long int value) {
		this -> value = S::toString(value);
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue(unsigned long long int value) {
		this -> value = S::toString(value);
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue(double value) {
		this -> value = S::toString(value);
		this -> bAddQuotes = false;
	}

	template<typename S>
	inline void NodeValueT<S>::setValue(bool value) {
		this -> value = S::toString(value);
		this -> bAddQuotes = false;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeValueT<S>::readJSON(const C** buffer, const EndFunc& endFunc) {
		struct FunctorContentQuote {
			bool operator()(const C& c) { return c != C('"'); }
		};
		struct FunctorContent {
			bool operator()(const C& c) { return c != C(',') && c != C('}') && c != C(']') && c != C(' '); }
		};
		struct FunctorSpace {
			bool operator()(const C& c) { return c == C('\n') || c == C('\t') || c == C(' '); }
		};

		static FunctorContentQuote functorContentQuote;
		static FunctorContent functorContent;
		static FunctorSpace functorSpace;

		static const S nullString("null");

		const C*& it(*buffer);

		// Value node.
		if ( ( *it ) == C('"') ) {
			// Quote value.
			it++;
			const C* beginIt(it);
			while ( true ) {
				if ( endFunc(it) ) {
					ERROR(TEXT("[JSON Error] : Unexpected buffer end."));
					return false;
				}
				if ( !functorContentQuote(*it) ) {
					if ( ( *( it - 1 ) ) != C('\\') ) {
						break;
					}
				}
				it++;
			}

			S nodeValue(beginIt, Size(it - beginIt));

			if ( !_expectChar(&it, C('"')) ) return false;

			this -> value = nodeValue;
			this -> type = Type::Value;
			this -> bAddQuotes = true;
		} else {
			// Value without quote.

			const C* beginIt(it);
			while ( true ) {
				if ( endFunc(it) ) {
					ERROR(TEXT("[JSON Error] : Unexpected buffer end."));
					return false;
				}
				if ( !functorContent(*it) )
					break;
				it++;
			}

			S nodeValue(beginIt, Size(it - beginIt));

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
	bool NodeValueT<S>::readJSON(const C* buffer, const EndFunc& endFunc) {
		return BasicNodeT<S>::readJSON<C, EndFunc>(buffer, endFunc);
	}

	template<typename S>
	bool NodeValueT<S>::readJSON(const S& str) {
		return BasicNodeT<S>::readJSON(str);
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeValueT<S>::_writeJSON(C& o, unsigned int indent, bool beautyfy) const {
		if ( this -> getName().getSize() ) {
			o << Elem('"');
			o << this -> getName();
			o << Elem('"');
			o << Elem(':');
			if ( beautyfy ) {
				o << Elem(' ');
			}
		}

		if ( this -> bAddQuotes ) {
			o << Elem('"');
			o << this -> getValue();
			o << Elem('"');
		} else {
			o << this -> getValue();
		}
	}

	template<typename S>
	template<typename Stream>
	bool NodeValueT<S>::read(Stream* stream) {
		if ( !BasicNodeT<S>::_read(stream) ) {
			_clear();
			return false;
		}
		if ( !IO::read(stream, &this -> value) ) {
			_clear();
			return false;
		}
		if ( !IO::read(stream, &this -> bAddQuotes) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename S>
	template<typename Stream>
	bool NodeValueT<S>::write(Stream* stream) const {
		if ( !BasicNodeT<S>::_write(stream) ) {
			return false;
		}
		if ( !IO::write(stream, &this -> value) ) {
			return false;
		}
		if ( !IO::write(stream, &this -> bAddQuotes) ) {
			return false;
		}
		return true;
	}


	/************************************************************************/
	/* NodeArrayT<S>                                                         */
	/************************************************************************/

	template<typename S>
	NodeArrayT<S>::NodeArrayT() : NodeMapT<S>() {
		this -> type = Type::Array;
	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT(const S& name) : NodeMapT<S>(name) {
		this -> type = Type::Array;
	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT(const S& name, const Vector<BasicNodeT<S>*>& v) :
		BasicNodeT<S>(name, BasicNodeT<S>::Type::Array) {
		for ( auto it(v.getBegin()); it != v.getEnd(); v.iterate(&it) ) {
			BasicNodeT<S>* node(v.getValueIt(it));
			this -> addChild(node);
		}
	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT(const NodeArrayT<S>& node) : NodeT(node) {

	}

	template<typename S>
	NodeArrayT<S>::NodeArrayT(NodeArrayT<S>&& node) : NodeT(Utility::toRValue(node)) {

	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeArrayT<S>::readJSON(const C** buffer, const EndFunc& endFunc) {
		struct FunctorSpace {
			bool operator()(const C& c) { return c == C('\n') || c == C('\t') || c == C(' '); }
		};

		static FunctorSpace functorSpace;

		const C*& it(*buffer);

		if ( !BasicNodeT<S>::_expectChar(&it, C('[')) ) return false;

		this -> type = Type::Array;
		while ( functorSpace(*it) ) it++;

		while ( true ) {
			if ( ( *it ) == C(']') ) {
				it++;
				break;
			}

			BasicNodeT<S>* newNode(parseT<S, C, EndFunc>(&it, endFunc));
			if ( newNode ) {
				this -> addChild(newNode);
			}
			while ( functorSpace(*it) ) it++;

			if ( ( *it ) == C(',') ) {
				it++;
			}

		}

		while ( functorSpace(*it) ) it++;

		return true;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool NodeArrayT<S>::readJSON(const C* buffer, const EndFunc& endFunc) {
		return BasicNodeT<S>::readJSON<C, EndFunc>(buffer, endFunc);
	}

	template<typename S>
	bool NodeArrayT<S>::readJSON(const S& str) {
		return BasicNodeT<S>::readJSON(str);
	}

	template<typename S>
	template<typename C, typename Elem>
	void NodeArrayT<S>::_writeJSON(C& o, unsigned int indent, bool beautyfy) const {
		if ( this -> getName().getSize() ) {
			o << Elem('"');
			o << this -> getName();
			o << Elem('"');
			o << Elem(':');
			if ( beautyfy ) {
				o << Elem(' ');
			}
		}

		o << Elem('[');
		for ( auto it(this -> childrenVector.getBegin()); it != this -> childrenVector.getEnd(); this -> childrenVector.iterate(&it) ) {
			if ( it != this -> childrenVector.getBegin() ) {
				o << Elem(',');
				if ( beautyfy ) {
					o << Elem(' ');
				}
			}

			BasicNodeT<S>* child(this -> childrenVector.getValueIt(it));
			child -> _writeJSON<C, Elem>(o, indent, beautyfy);
		}
		o << Elem(']');
	}















	template<typename S>
	inline DocumentT<S>::DocumentT() :
		rootNode(NULL) {}

	template<typename S>
	inline DocumentT<S>::DocumentT(const S& str) :
		rootNode(NULL) {
		readJSON(str);
	}

	template<typename S>
	inline DocumentT<S>::DocumentT(BasicNodeT<S>* rootNode) :
		rootNode(rootNode) {}

	template<typename S>
	inline DocumentT<S>::~DocumentT() {
		if ( this->rootNode ) {
			delete this->rootNode;
		}
	}

	template<typename S>
	inline const BasicNodeT<S>* DocumentT<S>::getRoot() const {
		return this->rootNode;
	}

	template<typename S>
	inline BasicNodeT<S>* DocumentT<S>::getRoot() {
		return this->rootNode;
	}

	template<typename S>
	inline BasicNodeT<S>* DocumentT<S>::getElementByName(const S& name) const {
		if ( this->rootNode ) {
			return this->rootNode->getElementByName(name);
		}
		return NULL;
	}

	template<typename S>
	inline Vector<BasicNodeT<S>*> DocumentT<S>::getElementsByName(const S& name) const {
		if ( this->rootNode ) {
			return this->rootNode->getElementsByName(name);
		}
		return Vector<BasicNodeT<S>*>();
	}

	template<typename S>
	inline bool DocumentT<S>::writeFileJSON(const OS::Path& filePath) const {
		IO::FileStream stream(filePath, IO::OpenMode::Write);
		if ( !stream.isOpen() ) {
			return false;
		}
		if ( this->rootNode ) {
			return this->rootNode->writeJSON(&stream);
		}
		return true;
	}

	template<typename S>
	inline bool DocumentT<S>::readFileJSON(const OS::Path& filePath) {
		_unload();

		S strOut;
		if ( IO::readToString(filePath, &strOut) != size_t(-1) ) {
			return readJSON(strOut);
		} else {
			_unload();
			return false;
		}
	}

	template<typename S>
	inline bool DocumentT<S>::readJSON(const S& str) {
		const typename S::ElemType* buffer(str.toCString());
		return readJSON<S::ElemType>(&buffer);
	}

	template<typename S>
	template<typename Stream>
	inline bool DocumentT<S>::writeJSON(Stream* stream, unsigned int indent, bool beautyfy) const {
		if ( this->rootNode ) {
			return this->rootNode->writeJSON(stream, indent, beautyfy);
		}
		return true;
	}

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::read(Stream* stream) {
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
			BasicNodeT<S>::Type rootNodeType(static_cast< BasicNodeT<S>::Type >( rootNodeTypeUC ));
			switch ( rootNodeType ) {
				case BasicNodeT<S>::Type::Map:
					{
						NodeMapT<S>* newRootNode(new NodeMapT<S>());
						if ( !IO::read(stream, newRootNode) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				case BasicNodeT<S>::Type::Value:
					{
						NodeValueT<S>* newRootNode(new NodeValueT<S>());
						if ( !IO::read(stream, newRootNode) ) {
							delete newRootNode;
							return false;
						}
						this->rootNode = newRootNode;
						break;
					}
				case BasicNodeT<S>::Type::Array:
					{
						NodeArrayT<S>* newRootNode(new NodeArrayT<S>());
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

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::write(Stream* stream) const {
		bool bIsRootNode(this->rootNode);
		if ( !IO::write(stream, &bIsRootNode) ) {
			return false;
		}
		if ( this->rootNode ) {
			BasicNodeT<S>::Type rootNodeType(this->rootNode->getType());
			unsigned char rootNodeTypeUC(static_cast< unsigned char >( rootNodeType ));
			if ( !IO::write(stream, &rootNodeTypeUC) ) {
				return false;
			}
			switch ( rootNodeType ) {
				case BasicNodeT<S>::Type::Map:
					{
						NodeMapT<S>* rootNode(this->rootNode->toMap());
						if ( !IO::write(stream, rootNode) ) {
							return false;
						}
						break;
					}
				case BasicNodeT<S>::Type::Value:
					{
						NodeValueT<S>* rootNode(this->rootNode->toValue());
						if ( !IO::write(stream, rootNode) ) {
							return false;
						}
						break;
					}
				case BasicNodeT<S>::Type::Array:
					{
						NodeArrayT<S>* rootNode(this->rootNode->toArray());
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

	template<typename S>
	inline void DocumentT<S>::_unload() {
		if ( this->rootNode ) {
			delete this->rootNode;
			this->rootNode = NULL;
		}
	}

	template<typename S>
	template<typename C, typename EndFunc>
	inline bool DocumentT<S>::readJSON(const C** buffer, const EndFunc& endFunc) {
		const C*& it(*buffer);

		// Can be empty.
		if ( endFunc(it) ) {
			return true;
		}

		BasicNodeT<S>* newNode(parseT<S, C, EndFunc>(&it, endFunc));

		if ( newNode ) {
			_unload();
			this->rootNode = newNode;
			return true;
		}

		return false;
	}

	template<typename S>
	template<typename C, typename EndFunc>
	inline bool DocumentT<S>::readJSON(const C* buffer, const EndFunc& endFunc) {
		return readJSON(&buffer, endFunc);
	}

	template<typename S>
	template<typename C>
	inline bool DocumentT<S>::writeJSON(C& str, unsigned int indent, bool beautyfy) const {
		if ( this->rootNode ) {
			return this->rootNode->writeJSON(str, indent, beautyfy);
		}
		return true;
	}

	template<typename S>
	template<typename S2>
	inline S2 DocumentT<S>::toString(unsigned int indent, bool beautyfy) const {
		if ( this->rootNode ) {
			return this->rootNode->toString(indent, beautyfy);
		} else {
			return S2::null;
		}
	}




















	template<typename S, typename C, typename EndFunc>
	BasicNodeT<S>* parseT(const C** buffer, const EndFunc& endFunc) {
		struct FunctorSpace {
			bool operator()(const C& c) { return c == C('\n') || c == C('\t') || c == C(' '); }
		};
		static FunctorSpace functorSpace;

		const C*& it(*buffer);

		while ( functorSpace(*it) ) it++;

		if ( ( *it ) == C('{') ) {
			NodeMapT<S>* newNode(new NodeMapT<S>());

			if ( !newNode -> readJSON(&it, endFunc) ) {
				return NULL;
			} else {
				return newNode;
			}
		} else if ( ( *it ) == C('[') ) {
			NodeArrayT<S>* newNode(new NodeArrayT<S>());

			if ( !newNode -> readJSON(&it, endFunc) ) {
				return NULL;
			} else {
				return newNode;
			}
		} else {
			NodeValueT<S>* newNode(new NodeValueT<S>());

			if ( !newNode -> readJSON(&it, endFunc) ) {
				return NULL;
			} else {
				return newNode;
			}
		}

		return NULL;
	}

	template<typename S, typename C, typename EndFunc>
	BasicNodeT<S>* parseT(const C* buffer, const EndFunc& endFunc) {
		return parseT<S, C, EndFunc>(&buffer, endFunc);
	}

	template<typename S>
	BasicNodeT<S>* parseT(const S& str) {
		const typename S::ElemType* buffer(str.toCString());
		return parse<S, S::ElemType>(buffer);
	}

	template<typename S, typename C>
	bool fromJSON(const BasicNodeT<S>* node, C* v) {
		return _fromJSON<S>(node, v, reinterpret_cast< const C* >( NULL ));
	}

	template<typename S, typename C>
	bool fromJSON(const BasicNodeT<S>* node, Table<C>* t) {
		if ( node->getType() != JSON::BasicNodeT<S>::Type::Array ) {
			return false;
		}

		Size minSize(Math::min(node->getNbChildren(), t->getSize()));
		for ( Size i(0); i < minSize; i++ ) {
			const JSON::BasicNodeT<S>* nodeChild(node->getChild(i));
			if ( !JSON::fromJSON<S>(nodeChild, &t->getValueI(i)) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename C, Size N>
	bool fromJSON(const BasicNodeT<S>* node, StaticTable<C, N>* t) {
		if ( node->getType() != JSON::BasicNodeT<S>::Type::Array ) {
			return false;
		}

		Size minSize(Math::min(node->getNbChildren(), t->getSize()));
		for ( Size i(0); i < minSize; i++ ) {
			const JSON::BasicNodeT<S>* nodeChild(node->getChild(i));
			if ( !JSON::fromJSON<S>(nodeChild, &t->getValueI(i)) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON(const BasicNodeT<S>* node, BasicVector<C>* v) {
		if ( node->getType() != JSON::BasicNodeT<S>::Type::Array ) {
			return false;
		}

		v->resizeNoCopy(node->getNbChildren());

		for ( Size i(0); i < node->getNbChildren(); i++ ) {
			const JSON::BasicNodeT<S>* nodeChild(node->getChild(i));
			if ( !JSON::fromJSON(nodeChild, &v->getValueI(i)) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON(const BasicNodeT<S>* node, Vector<C>* v) {
		return _fromJSON<S>(node, v, reinterpret_cast< Table<C> * >( v ));
	}

	template<typename S, typename C>
	bool _fromJSON(const BasicNodeT<S>* node, C* v, const Jsonable*) {
		return v->fromJSON<S>(node);
	}

	template<typename S, typename C>
	bool _fromJSON(const BasicNodeT<S>* node, C* v, ...) {
		if ( node->getType() != BasicNodeT<S>::Type::Value ) {
			return false;
		}
		( *v ) = node->getValue().fromString<C>();
		return true;
	}

	template<typename S>
	BasicNodeT<S>* toJSON() {
		return new JSON::NodeValueT<S>();
	}

	template<typename S, typename C>
	BasicNodeT<S>* toJSON(const C& v) {
		return _toJSON<S>(v, reinterpret_cast< const C* >( NULL ));
	}

	template<typename S, typename C>
	NodeArrayT<S>* toJSON(const Table<C>& t) {
		JSON::NodeArrayT<S>* nodeArray(new JSON::NodeArrayT<S>());

		for ( Size i(0); i < t.getSize(); i++ ) {
			JSON::BasicNodeT<S>* nodeValue(toJSON<S>(t[ i ]));
			nodeArray->addChild(nodeValue);
		}

		return nodeArray;
	}

	template<typename S, typename C, Size N>
	NodeArrayT<S>* toJSON(const StaticTable<C, N>& t) {
		JSON::NodeArrayT<S>* nodeArray(new JSON::NodeArrayT<S>());

		for ( Size i(0); i < t.getSize(); i++ ) {
			JSON::BasicNodeT<S>* nodeValue(toJSON<S>(t[ i ]));
			nodeArray->addChild(nodeValue);
		}

		return nodeArray;
	}

	template<typename S, typename C>
	NodeArrayT<S>* toJSON(const BasicVector<C>& v) {
		return toJSON<S>(*reinterpret_cast< const Table<C> * >( &v ));
	}

	template<typename S, typename C>
	NodeArrayT<S>* toJSON(const Vector<C>& v) {
		return toJSON<S>(*reinterpret_cast< const Table<C> * >( &v ));
	}

	template<typename S, typename C>
	BasicNodeT<S>* _toJSON(const C& v, const Jsonable*) {
		return v.toJSON<S>();
	}

	template<typename S, typename C>
	BasicNodeT<S>* _toJSON(const C& v, ...) {
		return new NodeValueT<S>(S::toString(v));
	}

	template<typename S>
	inline bool Jsonable::fromJSON(const JSON::BasicNodeT<S>* node) {
		ERROR("Jsonable not overloaded the fromJSON method.");
		return false;
	}

	template<typename S>
	inline JSON::BasicNodeT<S>* Jsonable::toJSON() const {
		ERROR("Jsonable not overloaded the toJSON method.");
		return NULL;
	}

}