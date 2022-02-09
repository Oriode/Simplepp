///@file NodeMap.h
///@brief Representing an JSON NodeMap.
///@author Clément Gerber.
///@date (DMY) 23-05-2020
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../MultiMap.h"
#include "../Math/Math.h"
#include "../OS/Path.h"


namespace JSON {

	template<typename T>
	class NodeValueT;

	template<typename T>
	class NodeArrayT;

	template<typename T>
	class NodeMapT;

	///@brief Represent a node in the JSON Tree, Only 3 Types available ( Map, Array and Value )
	template<typename T>
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
		BasicNodeT( typename BasicNodeT<T>::Type type = BasicNodeT<T>::Type::Map );

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		///@param type NodeMap type.
		BasicNodeT( const T & name, typename BasicNodeT<T>::Type type = BasicNodeT<T>::Type::Map );

		///@brief Copy Constructor
		///@param node BasicNodeT<T> to be copied
		BasicNodeT( const BasicNodeT<T> & node );

		///@brief Move Constructor
		///@param node BasicNodeT<T> to be moved
		BasicNodeT( BasicNodeT<T> && node );

		///@brief Destructor
		virtual ~BasicNodeT();

		///@brief Copy operator
		///@param node BasicNodeT<T> to be copied
		///@return reference to THIS
		BasicNodeT<T> & operator=( const BasicNodeT<T> & node );

		///@brief Move operator
		///@param node BasicNodeT<T> to be moved
		///@return reference to THIS
		BasicNodeT<T> & operator=( BasicNodeT<T> && node );

		///@brief Get the type of this BasicNodeT<T>.
		///@return Type of this node
		BasicNodeT<T>::Type getType() const;

		///@brief Cast this node into an object one, ONLY appliable if getType() return BasicNodeT<T>::Type::Map
		///@return Pointer to a NodeValueT
		const NodeMapT<T> * toObject() const;
		NodeMapT<T> * toObject();

		///@brief Cast this node into a value one, ONLY appliable if getType() return BasicNodeT<T>::Type::Value
		///@return Pointer to a NodeValueT
		const NodeValueT<T> * toValue() const;
		NodeValueT<T> * toValue();

		///@brief Cast this node into an array one, ONLY appliable if getType() return BasicNodeT<T>::Type::Array
		///@return Pointer to a NodeArrayT
		const NodeArrayT<T> * toArray() const;
		NodeArrayT<T> * toArray();

		///@brief Get the parent of this node
		///@return Pointer to the parent if there is one (NULL otherwise)
		const NodeMapT<T> * getParent() const;
		NodeMapT<T> * getParent();

		///@brief Get the Value of this node (Only appliable if getType() == Value).
		///@return Value of this node
		virtual const T & getValue() const;

		///@brief Set the value of this node (Will change this node value if getType() == Value, otherwise will try to change this node type to be a value one.)
		///@param value Value to be set
		virtual void setValue( const T & value );

		///@brief set the name of this node
		///@param name Name of this node
		virtual void setName( const T & name );

		///@brief get the name of this node
		///@return name of this node
		virtual const T & getName() const;

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return BasicNodeT<T> pointer with the searched name or NULL if none.
		virtual BasicNodeT<T>* getElementByName(const T& name) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of BasicNodeT<T>'s pointers with the searched name
		virtual Vector< BasicNodeT<T> * > getElementsByName( const T & name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		virtual Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		virtual const BasicNodeT<T> * getChild( Size i ) const;
		virtual BasicNodeT<T> * getChild( Size i );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		virtual void addChild( BasicNodeT<T> * child );

		///@brief Get the complete children vector of this node.
		///@return Children Vector.
		virtual const Vector<BasicNodeT<T> *> & getChildren() const;

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		virtual const Vector<BasicNodeT<T> *> & getChildren( const T & name ) const;
		// virtual Vector<BasicNodeT<T> *> getChildren( const T & name );

		///@brief Get the first child founded from a name
		///@param name Name to look for
		///@return pointer to the child if one has been founded, NULL instead
		virtual const BasicNodeT<T> * getChild( const T & name ) const;
		virtual BasicNodeT<T> * getChild( const T & name );

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( BasicNodeT<T> * child );

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<T> * removeChild( BasicNodeT<T> * child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<T> * removeChild( Size i );

		///@brief Write this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		virtual bool writeFileJSON( const OS::Path & filePath ) const;

		///@brief Read this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		bool readFileJSON( const OS::Path & filePath );

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type T.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const T & str );

		///@brief Write this object in the JSON syntax into the fileStream
		///@param fileStream stream used to write this object
		///@param indent Indentation.
		///@return True if success, False otherwise
		bool writeJSON( IO::SimpleFileStream * fileStream, unsigned int indent = 0 ) const;

		template<typename C = T>
		bool writeJSON( C & str, unsigned int indent = 0 ) const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool read( IO::SimpleFileStream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool write( IO::SimpleFileStream * fileStream ) const;

		///@brief Print an human-readable String of this BasicNodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename C = T>
		C toString( unsigned int indent = 0 ) const;

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = T, typename Elem = C::ElemType>
		void _writeJSON( C & o, unsigned int indent = 0 ) const;

		NodeMapT<T> * parent;
	protected:
		///@brief Check if the buffer at the current position is the expected character. Increment the buffer it True.
		///@param buffer Buffer to check.
		///@param c Character to be compared.
		///@return bool True if the buffer is the expected character at the current position.
		template<typename C>
		static bool _expectChar( const C ** buffer, const C & c );

		virtual void _clear();
		virtual void _unload();

		Type type;
		T name;

		static const Vector< BasicNodeT<T> * > emptyVector;
	};






	///@brief Represent a node in the JSON Tree, Only 3 Types available ( Map, Array and Value )
	template<typename T>
	class NodeMapT : public BasicNodeT<T> {
	public:
		using BasicNodeT<T>::Type;

		///@brief Anonymous Map NodeMap Constructor.
		///@param type NodeMap type.
		NodeMapT( );

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		///@param type NodeMap type.
		NodeMapT( const T & name );

		///@brief Value NodeMap Constructor.
		///@param name Name.
		///@param value Value.
		NodeMapT( const T & name, const T & value );

		///@brief Copy Constructor
		///@param node NodeMapT<T> to be copied
		NodeMapT( const NodeMapT<T> & node );

		///@brief Move Constructor
		///@param node NodeMapT<T> to be moved
		NodeMapT( NodeMapT<T> && node );

		///@brief Destructor
		~NodeMapT();

		///@brief Copy operator
		///@param node NodeMapT<T> to be copied
		///@return reference to THIS
		NodeMapT<T> & operator=( const NodeMapT<T> & node );

		///@brief Move operator
		///@param node NodeMapT<T> to be moved
		///@return reference to THIS
		NodeMapT<T> & operator=( NodeMapT<T> && node );

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return BasicNodeT<T> pointer with the searched name or NULL if none.
		virtual BasicNodeT<T>* getElementByName(const T& name) const override;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeMapT<T>'s pointers with the searched name
		virtual Vector< BasicNodeT<T> * > getElementsByName( const T & name ) const override;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		virtual Size getNbChildren() const override;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		virtual const BasicNodeT<T> * getChild( Size i ) const override;
		virtual BasicNodeT<T> * getChild( Size i ) override;

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		virtual void addChild( BasicNodeT<T> * child ) override;

		///@brief Get the complete children vector of this node.
		///@return Children Vector.
		virtual const Vector<BasicNodeT<T> *> & getChildren() const override;

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		virtual const Vector<BasicNodeT<T> *> & getChildren( const T & name ) const override;
		// Vector<BasicNodeT<T> *> getChildren( const T & name ) override;

		///@brief Get the first child founded from a name
		///@param name Name to look for
		///@return pointer to the child if one has been founded, NULL instead
		virtual const BasicNodeT<T> * getChild( const T & name ) const override;
		virtual BasicNodeT<T> * getChild( const T & name ) override;

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( BasicNodeT<T> * child ) override;

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( Size i ) override;

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<T> * removeChild( BasicNodeT<T> * child ) override;

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual BasicNodeT<T> * removeChild( Size i ) override;

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type T.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const T & str );

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool read( IO::SimpleFileStream * fileStream ) override;

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool write( IO::SimpleFileStream * fileStream ) const override;

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = T, typename Elem = C::ElemType>
		void _writeJSON( C & o, unsigned int indent = 0 ) const;

		bool _setChildName( BasicNodeT<T> * child, const T & oldName, const T & newName );
	protected:
		void _clear();
		void _unload();
		void _getElementsByName( Vector < BasicNodeT<T> * > * nodeVector, const T & name ) const;
		BasicNodeT<T>* _getElementByName(const T& name) const;

		
	protected:
		MultiMap< T, BasicNodeT<T> * > childrenMap;
		Vector< BasicNodeT<T> * > childrenVector;
	};



	template<typename T>
	class NodeValueT : public BasicNodeT<T> {
	public:
		///@brief Empty constructor
		NodeValueT();

		///@brief create node
		///@param value value of the node
		NodeValueT( const T & value );

		///@brief Constructor using a name and a value.
		///@param name NodeMap name.
		///@param value NodeMap value.
		NodeValueT( const T & name, const T & value );

		///@brief Copy Constructor
		///@param node BasicNodeT<T> to be copied
		NodeValueT( const NodeValueT<T> & node );

		///@brief Move Constructor
		///@param node BasicNodeT<T> to be moved
		NodeValueT( NodeValueT<T> && node );

		///@brief Get the Value of this node (Only appliable if getType() == Value).
		///@return Value of this node
		const T & getValue() const override;

		///@brief Set the value of this node (Will change this node value if getType() == Value, otherwise will try to change this node type to be a value one.)
		///@param value Value to be set
		void setValue( const T & value ) override;

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type T.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const T & str );

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( IO::SimpleFileStream * fileStream ) override;

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( IO::SimpleFileStream * fileStream ) const override;

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = T, typename Elem = C::ElemType>
		void _writeJSON( C & o, unsigned int indent = 0 ) const;
	protected:
		T value;
	};

	template<typename T>
	class NodeArrayT : public NodeMapT<T> {
	public:
		///@brief Empty constructor
		NodeArrayT();

		///@brief Named Map NodeMap Constructor.
		///@param name Name of the node
		NodeArrayT( const T & name );

		///@brief Constructor using a name and a value.
		///@param name NodeMap name.
		///@param value NodeMap value.
		NodeArrayT( const T & name, const Vector<BasicNodeT<T> *> & v );

		///@brief Copy Constructor
		///@param node BasicNodeT<T> to be copied
		NodeArrayT( const NodeArrayT<T> & node );

		///@brief Move Constructor
		///@param node BasicNodeT<T> to be moved
		NodeArrayT( NodeArrayT<T> && node );


		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief read this object using a type T.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON( const T & str );

		///@brief Write this node to an Map that support opperator '<<'.
		///@param o Map to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = T, typename Elem = C::ElemType>
		void _writeJSON( C & o, unsigned int indent = 0 ) const;

	private:
	};

	template<typename T>
	class DocumentT : public IO::BasicIO {
	public:
		///@brief Create a new empty JSON DocumentT.
		DocumentT();

		///@brief Create a new JSON document using a string to be parsed.
		///@param str String to be parsed.
		DocumentT(const T& str);

		///@brief Destructor.
		~DocumentT();

		///@brief Get the root Node of this DocumentT. Can be NULL.
		///@return Pointer to the root Node of this DocumentT. Can be NULL;
		const BasicNodeT<T>* getRoot() const;
		BasicNodeT<T>* getRoot();

		///@brief Get the first pointer to the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return BasicNodeT<T> pointer with the searched name or NULL if none.
		virtual BasicNodeT<T>* getElementByName(const T& name) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of BasicNodeT<T>'s pointers with the searched name
		virtual Vector< BasicNodeT<T>* > getElementsByName(const T& name) const;

		///@brief Write this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		virtual bool writeFileJSON(const OS::Path& filePath) const;

		///@brief Read this object as an JSON file
		///@param filePath Where to write
		///@return True if success, False otherwise
		bool readFileJSON(const OS::Path& filePath);

		///@brief Read this object using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON(const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL);
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool readJSON(const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL);

		///@brief read this object using a type T.
		///@param str String to read from.
		///@return bool True if success, False otherwise.
		bool readJSON(const T& str);

		///@brief Write this object in the JSON syntax into the fileStream
		///@param fileStream stream used to write this object
		///@param indent Indentation.
		///@return True if success, False otherwise
		bool writeJSON(IO::SimpleFileStream* fileStream, unsigned int indent = 0) const;

		template<typename C = T>
		bool writeJSON(C& str, unsigned int indent = 0) const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool read(IO::SimpleFileStream* fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool write(IO::SimpleFileStream* fileStream) const;

		///@brief Print an human-readable String of this BasicNodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename C = T>
		C toString(unsigned int indent = 0) const;

	private:
		void _unload();

		BasicNodeT<T>* rootNode;
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
	template<typename T, typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
	BasicNodeT<T> * parseT( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
	template<typename T, typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
	BasicNodeT<T> * parseT( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

	///@brief read this object using a type T.
	///@param str String to read from.
	///@return bool True if success, False otherwise.
	template<typename T>
	BasicNodeT<T> * parseT( const T & str );

}

#include "Node.hpp"