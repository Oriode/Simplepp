///@file NodeMap.h
///@brief Representing an JSON NodeMap.
///@author Cl�ment Gerber.
///@date (DMY) 23-05-2020
#pragma once

#include "../Log.h"
#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../MultiMap.h"
#include "../Math/BasicMath.h"
#include "../OS/Path.h"
#include "../StaticTable.h"


namespace JSON {

	template<typename S>
	class NodeValueT;

	template<typename S>
	class NodeArrayT;

	template<typename S>
	class NodeMapT;

	///@brief Represent a node in the JSON Tree, Only 3 Types available ( Map, Array and Value )
	template<typename S>
	class BasicNodeT : public IO::BasicIO {
	public:
		enum class Type : unsigned int {
			Map,
			Array,
			Value,
			Null
		};

		///@brief Anonymous Map NodeMap Constructor.
		///@param type NodeMap type.
		BasicNodeT( typename BasicNodeT<S>::Type type = BasicNodeT<S>::Type::Map );

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		///@param type NodeMap type.
		BasicNodeT( const S& name, typename BasicNodeT<S>::Type type = BasicNodeT<S>::Type::Map );

		///@brief Copy Constructor
		///@param node BasicNodeT<S> to be copied
		BasicNodeT( const BasicNodeT<S>& node );

		///@brief Move Constructor
		///@param node BasicNodeT<S> to be moved
		BasicNodeT( BasicNodeT<S>&& node );

		///@brief Destructor
		virtual ~BasicNodeT();

		///@brief Copy operator
		///@param node BasicNodeT<S> to be copied
		///@return reference to THIS
		BasicNodeT<S>& operator=( const BasicNodeT<S>& node );

		///@brief Move operator
		///@param node BasicNodeT<S> to be moved
		///@return reference to THIS
		BasicNodeT<S>& operator=( BasicNodeT<S>&& node );

		///@brief Get the type of this BasicNodeT<S>.
		///@return Type of this node
		BasicNodeT<S>::Type getType() const;

		///@brief Cast this node into a value one, ONLY appliable if getType() return BasicNodeT<S>::Type::Value
		///@return Pointer to a NodeValueT
		const NodeValueT<S>* toValue() const;
		NodeValueT<S>* toValue();

		///@brief Cast this node into an array one, ONLY appliable if getType() return BasicNodeT<S>::Type::Array
		///@return Pointer to a NodeArrayT
		const NodeArrayT<S>* toArray() const;
		NodeArrayT<S>* toArray();

		///@brief Cast this node into an Map one, ONLY appliable if getType() return BasicNodeT<S>::Type::Map
		///@return Pointer to a NodeMapT
		const NodeMapT<S>* toMap() const;
		NodeMapT<S>* toMap();

		///@brief Get the parent of this node
		///@return Pointer to the parent if there is one (NULL otherwise)
		const NodeMapT<S>* getParent() const;
		NodeMapT<S>* getParent();

		///@brief Get the Value of this node (Only appliable if getType() == Value).
		///@return Value of this node
		virtual const S& getValue() const;

		///@brief Set the value of this node (Will change this node value if getType() == Value, otherwise will try to change this node type to be a value one.)
		///@param value Value to be set
		virtual void setValue( const S& value );
		virtual void setValue( int value );
		virtual void setValue( unsigned int value );
		virtual void setValue( long long int value );
		virtual void setValue( unsigned long long int value );
		virtual void setValue( double value );
		virtual void setValue( bool value );

		///@brief set the name of this node
		///@param name Name of this node
		virtual void setName( const S& name );

		///@brief get the name of this node
		///@return name of this node
		virtual const S& getName() const;

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return BasicNodeT<S> pointer with the searched name or NULL if none.
		virtual BasicNodeT<S>* getElementByName( const S& name ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of BasicNodeT<S>'s pointers with the searched name
		virtual Vector< BasicNodeT<S>* > getElementsByName( const S& name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		virtual Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		virtual const BasicNodeT<S>* getChild( Size i ) const;
		virtual BasicNodeT<S>* getChild( Size i );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		virtual void addChild( BasicNodeT<S>* child );
		virtual void addChild( const S& name, BasicNodeT<S>* child );

		///@brief Get the complete children vector of this node.
		///@return Children Vector.
		virtual const Vector<BasicNodeT<S>*>& getChildren() const;

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		virtual const Vector<BasicNodeT<S>*>& getChildren( const S& name ) const;
		// virtual Vector<BasicNodeT<S> *> getChildren( const S & name );

		///@brief Get the first child founded from a name
		///@param name Name to look for
		///@return pointer to the child if one has been founded, NULL instead
		virtual const BasicNodeT<S>* getChild( const S& name ) const;
		virtual BasicNodeT<S>* getChild( const S& name );

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( BasicNodeT<S>* child );

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<S>* removeChild( BasicNodeT<S>* child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<S>* removeChild( Size i );

		///@brief Write this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		virtual bool writeFileJSON( const OS::Path& filePath ) const;

		///@brief Read this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		bool readFileJSON( const OS::Path& filePath, int verbose = 0 );

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type S.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const S& str );

		///@brief Write this object in the JSON syntax into the stream
		///@param stream stream used to write this object
		///@param indent Indentation.
		///@return True if success, False otherwise
		template<typename Stream>
		bool writeJSON( Stream* stream, unsigned int indent = 0, bool beautyfy = true ) const;

		template<typename C = S>
		bool writeJSON( C& str, unsigned int indent = 0, bool beautyfy = true ) const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream* stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream* stream ) const;

		///@brief Print an human-readable String of this BasicNodeT<S> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S2 = S>
		S2 toString( unsigned int indent = 0, bool beautyfy = true ) const;

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = S, typename Elem = C::ElemType>
		void _writeJSON( C& o, unsigned int indent = 0, bool beautyfy = true ) const;

		NodeMapT<S>* parent;
	protected:
		///@brief Check if the buffer at the current position is the expected character. Increment the buffer it True.
		///@param buffer Buffer to check.
		///@param c Character to be compared.
		///@return bool True if the buffer is the expected character at the current position.
		template<typename C>
		static bool _expectChar( const C** buffer, const C& c );

		virtual void _clear();
		virtual void _unload();

		template<typename Stream>
		bool _write( Stream* stream ) const;
		template<typename Stream>
		bool _read( Stream* stream );

		Type type;
		S name;

		static const Vector< BasicNodeT<S>* > emptyVector;
	};






	///@brief Represent a node in the JSON Tree, Only 3 Types available ( Map, Array and Value )
	template<typename S>
	class NodeMapT : public BasicNodeT<S> {
	public:
		using BasicNodeT<S>::Type;

		///@brief Anonymous Map NodeMap Constructor.
		///@param type NodeMap type.
		NodeMapT();

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		///@param type NodeMap type.
		NodeMapT( const S& name );

		///@brief Value NodeMap Constructor.
		///@param name Name.
		///@param value Value.
		NodeMapT( const S& name, const S& value );

		///@brief Copy Constructor
		///@param node NodeMapT<S> to be copied
		NodeMapT( const NodeMapT<S>& node );

		///@brief Move Constructor
		///@param node NodeMapT<S> to be moved
		NodeMapT( NodeMapT<S>&& node );

		///@brief Destructor
		~NodeMapT();

		///@brief Copy operator
		///@param node NodeMapT<S> to be copied
		///@return reference to THIS
		NodeMapT<S>& operator=( const NodeMapT<S>& node );

		///@brief Move operator
		///@param node NodeMapT<S> to be moved
		///@return reference to THIS
		NodeMapT<S>& operator=( NodeMapT<S>&& node );

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return BasicNodeT<S> pointer with the searched name or NULL if none.
		virtual BasicNodeT<S>* getElementByName( const S& name ) const override;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeMapT<S>'s pointers with the searched name
		virtual Vector< BasicNodeT<S>* > getElementsByName( const S& name ) const override;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		virtual Size getNbChildren() const override;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		virtual const BasicNodeT<S>* getChild( Size i ) const override;
		virtual BasicNodeT<S>* getChild( Size i ) override;

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		virtual void addChild( BasicNodeT<S>* child ) override;
		virtual void addChild( const S& name, BasicNodeT<S>* child );

		///@brief Get the complete children vector of this node.
		///@return Children Vector.
		virtual const Vector<BasicNodeT<S>*>& getChildren() const override;

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		virtual const Vector<BasicNodeT<S>*>& getChildren( const S& name ) const override;
		// Vector<BasicNodeT<S> *> getChildren( const S & name ) override;

		///@brief Get the first child founded from a name
		///@param name Name to look for
		///@return pointer to the child if one has been founded, NULL instead
		virtual const BasicNodeT<S>* getChild( const S& name ) const override;
		virtual BasicNodeT<S>* getChild( const S& name ) override;

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( BasicNodeT<S>* child ) override;

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( Size i ) override;

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<S>* removeChild( BasicNodeT<S>* child ) override;

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<S>* removeChild( Size i ) override;

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type S.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const S& str );

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream* stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream* stream ) const;

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = S, typename Elem = C::ElemType>
		void _writeJSON( C& o, unsigned int indent = 0, bool beautyfy = true ) const;

		bool _setChildName( BasicNodeT<S>* child, const S& oldName, const S& newName );
	protected:
		void _clear();
		void _unload();
		void _getElementsByName( Vector < BasicNodeT<S>* >* nodeVector, const S& name ) const;
		BasicNodeT<S>* _getElementByName( const S& name ) const;

		MultiMap< S, BasicNodeT<S>* > childrenMap;
		Vector< BasicNodeT<S>* > childrenVector;
	};



	template<typename S>
	class NodeValueT : public BasicNodeT<S> {
	public:
		///@brief Empty constructor
		NodeValueT();

		///@brief create node
		///@param value value of the node
		NodeValueT( const S& value );
		NodeValueT( int value );
		NodeValueT( unsigned int value );
		NodeValueT( long long int value );
		NodeValueT( unsigned long long int value );
		NodeValueT( double value );
		NodeValueT( bool value );

		///@brief Constructor using a name and a value.
		///@param name NodeMap name.
		///@param value NodeMap value.
		NodeValueT( const S& name, const S& value );
		NodeValueT( const S& name, int value );
		NodeValueT( const S& name, unsigned int value );
		NodeValueT( const S& name, long long int value );
		NodeValueT( const S& name, unsigned long long int value );
		NodeValueT( const S& name, double value );
		NodeValueT( const S& name, bool value );

		///@brief Copy Constructor
		///@param node BasicNodeT<S> to be copied
		NodeValueT( const NodeValueT<S>& node );

		///@brief Move Constructor
		///@param node BasicNodeT<S> to be moved
		NodeValueT( NodeValueT<S>&& node );

		///@brief Get the Value of this node (Only appliable if getType() == Value).
		///@return Value of this node
		const S& getValue() const override;

		///@brief Set the value of this node (Will change this node value if getType() == Value, otherwise will try to change this node type to be a value one.)
		///@param value Value to be set
		virtual void setValue( const S& value ) override;
		virtual void setValue( int value ) override;
		virtual void setValue( unsigned int value ) override;
		virtual void setValue( long long int value ) override;
		virtual void setValue( unsigned long long int value ) override;
		virtual void setValue( double value ) override;
		virtual void setValue( bool value ) override;

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type S.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const S& str );

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream* stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream* stream ) const;

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = S, typename Elem = C::ElemType>
		void _writeJSON( C& o, unsigned int indent = 0, bool beautyfy = true ) const;
	protected:
		S value;
		bool bAddQuotes;
	};

	template<typename S>
	class NodeArrayT : public NodeMapT<S> {
	public:
		///@brief Empty constructor
		NodeArrayT();

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		NodeArrayT( const S& name );

		///@brief Constructor using a name and a value.
		///@param name NodeMap name.
		///@param value NodeMap value.
		NodeArrayT( const S& name, const Vector<BasicNodeT<S>*>& v );

		///@brief Copy Constructor
		///@param node BasicNodeT<S> to be copied
		NodeArrayT( const NodeArrayT<S>& node );

		///@brief Move Constructor
		///@param node BasicNodeT<S> to be moved
		NodeArrayT( NodeArrayT<S>&& node );


		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type S.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const S& str );

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = S, typename Elem = C::ElemType>
		void _writeJSON( C& o, unsigned int indent = 0, bool beautyfy = true ) const;

	private:
	};

	template<typename S>
	class DocumentT : public IO::BasicIO {
	public:
		///@brief Create a new empty JSON DocumentT.
		DocumentT();

		///@brief Create a new JSON document using a string to be parsed.
		///@param str String to be parsed.
		DocumentT( const S& str );

		///@brief Create a new JSON document using a pointer to a node. The node will be memory managed.
		///@param rootNode JSON node.
		DocumentT( BasicNodeT<S>* rootNode );

		///@brief Destructor.
		~DocumentT();

		///@brief Get the root Node of this DocumentT. Can be NULL.
		///@return Pointer to the root Node of this DocumentT. Can be NULL;
		const BasicNodeT<S>* getRoot() const;
		BasicNodeT<S>* getRoot();

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return BasicNodeT<S> pointer with the searched name or NULL if none.
		virtual BasicNodeT<S>* getElementByName( const S& name ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of BasicNodeT<S>'s pointers with the searched name
		virtual Vector< BasicNodeT<S>* > getElementsByName( const S& name ) const;

		///@brief Write this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		virtual bool writeFileJSON( const OS::Path& filePath ) const;

		///@brief Read this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		bool readFileJSON( const OS::Path& filePath, int verbose = 0 );

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type S.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const S& str );

		///@brief Write this object in the JSON syntax into the stream
		///@param stream stream used to write this object
		///@param indent Indentation.
		///@return True if success, False otherwise
		template<typename Stream>
		bool writeJSON( Stream* stream, unsigned int indent = 0, bool beautyfy = true ) const;

		template<typename C = S>
		bool writeJSON( C& str, unsigned int indent = 0, bool beautyfy = true ) const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream* stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream* stream ) const;

		///@brief Print an human-readable String of this BasicNodeT<S> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S2 = S>
		S2 toString( unsigned int indent = 0, bool beautyfy = true ) const;

	private:
		void _unload();

		BasicNodeT<S>* rootNode;
	};

	class Jsonable {
	public:
		///@brief Read a JSON object and set this to the read values.
		///@param nodeArray Pointer to the JSON object to be read.
		///@return true if success, false otherwise.
		template<typename S = UTF8String>
		bool fromJSON( const JSON::BasicNodeT<S>* node, int verbose = 0 );

		///@brief Write this object to a Json object
		///@param o Json node to write to.
		template<typename S = UTF8String>
		JSON::BasicNodeT<S>* toJSON() const;
	};

	using Node = BasicNodeT<UTF8String>;
	using NodeMap = NodeMapT<UTF8String>;
	using NodeValue = NodeValueT<UTF8String>;
	using NodeArray = NodeArrayT<UTF8String>;
	using Document = DocumentT<UTF8String>;


	///@brief Read this object using a pointer to a String Iterator.
	///@param buffer Pointer to a String iterator
	///@param endFunc Functor to check the buffer end.
	///@return bool True if success, False otherwise.
	template<typename S = UTF8String, typename C = S::ElemType, typename EndFunc = BasicString<C>::IsEndSentinel>
	BasicNodeT<S>* parseT( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
	template<typename S = UTF8String, typename C = S::ElemType, typename EndFunc = BasicString<C>::IsEndSentinel>
	BasicNodeT<S>* parseT( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

	///@brief read this object using a type S.
	///@param str String to read from.
	///@return bool True if success, False otherwise.
	template<typename S>
	BasicNodeT<S>* parseT( const S& str );

	template<typename S, typename C>
	bool fromJSON( const BasicNodeT<S>* node, C* v, int verbose = 0 );

	template<typename S, typename C>
	bool fromJSON( const BasicNodeT<S>* node, Table<C>* t, int verbose = 0 );
	template<typename S, typename C, Size N>
	bool fromJSON( const BasicNodeT<S>* node, StaticTable<C, N>* t, int verbose = 0 );
	template<typename S, typename C>
	bool fromJSON( const BasicNodeT<S>* node, BasicVector<C>* v, int verbose = 0 );
	template<typename S, typename C>
	bool fromJSON( const BasicNodeT<S>* node, Vector<C>* v, int verbose = 0 );

	template<typename S, typename C>
	bool _fromJSON( const BasicNodeT<S>* node, C* v, const Jsonable* );
	template<typename S, typename C>
	bool _fromJSON( const BasicNodeT<S>* node, C* v, ... );

	template<typename S>
	BasicNodeT<S>* toJSON();
	template<typename S, typename C>
	BasicNodeT<S>* toJSON( const C& v );
	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const Table<C>& t );
	template<typename S, typename C, Size N>
	NodeArrayT<S>* toJSON( const StaticTable<C, N>& t );
	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const BasicVector<C>& v );
	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const Vector<C>& v );

	template<typename S, typename C>
	BasicNodeT<S>* _toJSON( const C& v, const Jsonable* );
	template<typename S, typename C>
	BasicNodeT<S>* _toJSON( const C& v, ... );

	///@brief write an object to the file, this function will automatically test if the sent object (by pointer) inherit from BasicIO JSON::Jsonable and then call his own fromJSON method.
	///@param filePath file where to write.
	///@param object pointer to the object we wanna write.
	///@return Boolean if the result is a success or not.
	template<typename S = UTF8String, typename C>
	static bool write( const OS::Path& filePath, const C* object, int verbose = 0 );

	///@brief read from a file to an object, this function will automatically test if the sent object (by pointer) inherit from JSON::Jsonable himself and then call his own toJSON method.
	///@param filePath file where to read.
	///@param object pointer to the object we wanna read.
	///@return Boolean if the result is a success or not.
	template<typename S = UTF8String, typename C>
	bool read( const OS::Path& filePath, C* object, int verbose = 0 );

}

#include "Node.hpp"