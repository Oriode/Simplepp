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
	class NodeT : public IO::BasicIO {
	public:
		enum class Type : unsigned int {
			Map,
			Array,
			Value,
			Null
		};

		///@brief Anonymous Map NodeMap Constructor.
		///@param type NodeMap type.
		NodeT( typename NodeT<S>::Type type = NodeT<S>::Type::Map );

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		///@param type NodeMap type.
		NodeT( const S& name, typename NodeT<S>::Type type = NodeT<S>::Type::Map );

		///@brief Copy Constructor
		///@param node NodeT<S> to be copied
		NodeT( const NodeT<S>& node );

		///@brief Move Constructor
		///@param node NodeT<S> to be moved
		NodeT( NodeT<S>&& node );

		///@brief Destructor
		virtual ~NodeT();

		///@brief Copy operator
		///@param node NodeT<S> to be copied
		///@return reference to THIS
		NodeT<S>& operator=( const NodeT<S>& node );

		///@brief Move operator
		///@param node NodeT<S> to be moved
		///@return reference to THIS
		NodeT<S>& operator=( NodeT<S>&& node );

		///@brief Get the type of this NodeT<S>.
		///@return Type of this node
		NodeT<S>::Type getType() const;

		///@brief Cast this node into a value one, ONLY appliable if getType() return NodeT<S>::Type::Value
		///@return Pointer to a NodeValueT
		const NodeValueT<S>* toValue() const;
		NodeValueT<S>* toValue();

		///@brief Cast this node into an array one, ONLY appliable if getType() return NodeT<S>::Type::Array
		///@return Pointer to a NodeArrayT
		const NodeArrayT<S>* toArray() const;
		NodeArrayT<S>* toArray();

		///@brief Cast this node into an Map one, ONLY appliable if getType() return NodeT<S>::Type::Map
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
		///@return NodeT<S> pointer with the searched name or NULL if none.
		virtual NodeT<S>* getElementByName( const S& name ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<S>'s pointers with the searched name
		virtual Vector< NodeT<S>* > getElementsByName( const S& name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		virtual Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (between [0 ; getNbChildren() - 1])
		///@return Child
		virtual const NodeT<S>* getChild( Size i ) const;
		virtual NodeT<S>* getChild( Size i );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		virtual void addChild( NodeT<S>* child );
		virtual void addChild( const S& name, NodeT<S>* child );

		///@brief Get the complete children vector of this node.
		///@return Children Vector.
		virtual const Vector<NodeT<S>*>& getChildren() const;

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		virtual const Vector<NodeT<S>*>& getChildren( const S& name ) const;
		// virtual Vector<NodeT<S> *> getChildren( const S & name );

		///@brief Get the first child founded from a name
		///@param name Name to look for
		///@return pointer to the child if one has been founded, NULL instead
		virtual const NodeT<S>* getChild( const S& name ) const;
		virtual NodeT<S>* getChild( const S& name );

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( NodeT<S>* child );

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual NodeT<S>* removeChild( NodeT<S>* child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual NodeT<S>* removeChild( Size i );

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

		///@brief Print an human-readable String of this NodeT<S> and it's children.
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
		bool _read( Stream* stream, int verbose = 0 );

		Type type;
		S name;

		static const Vector< NodeT<S>* > emptyVector;
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
		DocumentT( NodeT<S>* rootNode );

		///@brief Destructor.
		~DocumentT();

		///@brief Get the root Node of this DocumentT. Can be NULL.
		///@return Pointer to the root Node of this DocumentT. Can be NULL;
		const NodeT<S>* getRoot() const;
		NodeT<S>* getRoot();

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return NodeT<S> pointer with the searched name or NULL if none.
		virtual NodeT<S>* getElementByName( const S& name ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<S>'s pointers with the searched name
		virtual Vector< NodeT<S>* > getElementsByName( const S& name ) const;

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

		///@brief Print an human-readable String of this NodeT<S> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S2 = S>
		S2 toString( unsigned int indent = 0, bool beautyfy = true ) const;

	private:
		void _unload();

		NodeT<S>* rootNode;
	};

	class Jsonable {
	public:
		///@brief Read a JSON object and set this to the read values.
		///@param nodeArray Pointer to the JSON object to be read.
		///@return true if success, false otherwise.
		template<typename S = UTF8String>
		bool fromJSON( const JSON::NodeT<S>* node, int verbose = 0 );

		///@brief Write this object to a Json object
		///@param o Json node to write to.
		template<typename S = UTF8String>
		JSON::NodeT<S>* toJSON() const;
	};

	using Node = NodeT<UTF8String>;
	using Document = DocumentT<UTF8String>;


	

}

#include "Node.hpp"