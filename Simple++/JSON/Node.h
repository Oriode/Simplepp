///@file Node.h
///@brief Representing an JSON Node.
///@author Clément Gerber.
///@date (DMY) 23-05-2020
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../MultiMap.h"
#include "../Math/Math.h"


namespace JSON {

	template<typename T>
	class NodeValueT;

	///@brief Represent a node in the JSON Tree, Only 3 Types available ( Object, Array and Value )
	template<typename T>
	class NodeT : public BasicIO {
	public:
		enum class Type : unsigned int {
			Object,
			Array,
			Value
		};

		///@brief Constructor with only the type
		///@param type Type of this node.
		NodeT( Type type = Type::Object );

		///@brief create node
		///@param name Name of the node
		///@param type Type of this node
		NodeT( const T & name, Type type = Type::Object );

		///@brief Copy Constructor
		///@param node NodeT<T> to be copied
		NodeT( const NodeT<T> & node );

		///@brief Move Constructor
		///@param node NodeT<T> to be moved
		NodeT( NodeT<T> && node );

		///@brief Destructor
		~NodeT();

		///@brief Copy operator
		///@param node NodeT<T> to be copied
		///@return reference to THIS
		NodeT<T> & operator=( const NodeT<T> & node );

		///@brief Move operator
		///@param node NodeT<T> to be moved
		///@return reference to THIS
		NodeT<T> & operator=( NodeT<T> && node );

		///@brief Get the type of this NodeT<T>.
		///@return Type of this node
		NodeT<T>::Type getType() const;

		///@brief Cast this node into a value one, ONLY appliable if getType() return NodeT<T>::Type::Value
		///@return Pointer to a NodeValueT
		const NodeValueT<T> * toValue() const;
		NodeValueT<T> * toValue();

		///@brief Get the parent of this node
		///@return Pointer to the parent if there is one (NULL otherwise)
		const NodeT<T> * getParent() const;
		NodeT<T> * getParent();

		///@brief Get the Value of this node (Only appliable if getType() == Value).
		///@return Value of this node
		const T & getValue() const;

		///@brief Set the value of this node (Will change this node value if getType() == Value, otherwise will try to change the first child value)
		///@param value Value to be set
		void setValue( const T & value );

		///@brief set the name of this node
		///@param name Name of this node
		void setName( const T & name );

		///@brief get the name of this node
		///@return name of this node
		const T & getName() const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<T>'s pointers with the searched name
		Vector< NodeT<T> * > getElementsByName( const T & name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		typename Vector< NodeT<T> * >::Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		const NodeT<T> * getChild( typename Vector< NodeT<T> * >::Size i ) const;
		NodeT<T> * getChild( typename Vector< NodeT<T> * >::Size i );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		void addChild( NodeT<T> * child );

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		const Vector<NodeT<T> *> getChild( const T & name ) const;
		Vector<NodeT<T> *> getChild( const T & name );

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		bool deleteChild( NodeT<T> * child );

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		bool deleteChild( typename Vector< NodeT<T> * >::Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		NodeT<T> * removeChild( NodeT<T> * child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		NodeT<T> * removeChild( typename Vector< NodeT<T> * >::Size i );

		///@brief Write this object in the JSON syntax into the fileStream
		///@param fileStream stream used to write this object
		///@param tabs Indentation.
		///@return True if success, False otherwise
		bool writeJSON( std::fstream * fileStream, unsigned int tabs = 0 ) const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

		///@brief Print an human-readable String of this NodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename C = T>
		C toString( unsigned int indent = 0 ) const;

		///@brief Print an human-readable String of this NodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		T toStringDebug( unsigned int indent = 0 ) const;

		template<typename C = T, typename Elem = C::ElemType>
		void _writeJSON( C & o, unsigned int tabs = 0 ) const;

	protected:
		void _clear();
		void _unload();
		bool _write( std::fstream * fileStream ) const;
		bool _read( std::fstream * fileStream );
		bool _setChildName( NodeT<T> * child, const T & name );
		bool _setChildId( NodeT<T> * child, const T & id );
		void _getElementsById( Vector < NodeT<T> * > * nodeVector, const T & id ) const;
		void _getElementsByName( Vector < NodeT<T> * > * nodeVector, const T & name ) const;


	private:
		Type type;
		T name;
		T value;

		NodeT<T> * parent;

		MultiMap< T, NodeT<T> * > childrenMap;
		Vector< NodeT<T> * > childrenVector;
	};

	using Node = NodeT<UTF8String>;


	template<typename T>
	class NodeValueT : public NodeT<T> {
	public:
		///@brief Empty constructor
		NodeValueT();

		///@brief create node
		///@param value value of the node
		NodeValueT( const T & value );

		///@brief Constructor using a name and a value.
		///@param name Node name.
		///@param value Node value.
		NodeValueT( const T & name, const T & value );

		///@brief Copy Constructor
		///@param node NodeT<T> to be copied
		NodeValueT( const NodeValueT<T> & node );

		///@brief Move Constructor
		///@param node NodeT<T> to be moved
		NodeValueT( NodeValueT<T> && node );

		///@brief Copy operator
		///@param node NodeT<T> to be copied
		///@return reference to THIS
		NodeValueT<T> & operator=( const NodeValueT<T> & node );

		///@brief Move operator
		///@param node NodeT<T> to be moved
		///@return reference to THIS
		NodeValueT<T> & operator=( NodeValueT<T> && node );

		///@brief Get the value of this node
		///@return Value
		const T & getValue() const;

		///@brief Set the value of this node
		///@param value Value to be set
		void setValue( const T & value );

		///@brief Write this object in the XML syntax into the fileStream
		///@param fileStream stream used to write this object
		///@return True if success, False otherwise
		bool writeXML( std::fstream * fileStream ) const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;

		///@brief Print an human-readable String of this NodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename C = T>
		C toString( unsigned int indent = 0 ) const;

		template<typename C = T, typename Elem = C::ElemType>
		void _writeXML( C & o, unsigned int tabs = 0 ) const;
	private:
		void _clear();



		T value;


	};

	using NodeValue = NodeValueT<UTF8String>;

}

#include "Node.hpp"