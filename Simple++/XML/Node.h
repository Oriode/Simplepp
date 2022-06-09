///@file NodeT<T>.h
///@brief File containing the NodeT<T> Class, an XML NodeT<T>
///@author Clement Gerber
///@date 20/10/16
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../MultiMap.h"
#include "../Math/Math.h"
#include "Param.h"



namespace XML {

	template<typename T>
	class NodeTextT;

	///@brief Represent a node in the XML Tree, Only 3 Types available ( Element, Text and Document )
	template<typename T>
	class NodeT : public IO::BasicIO {
	public:
		enum class Type : unsigned int { 
			Element = 1,
			Text = 3,
			Document = 9
		};

		///@brief Empty constructor
		///@param type Type of this node
		NodeT( );

		///@brief create node
		///@param name Name of the node
		///@param type Type of this node
		NodeT( const T & name, Type type = Type::Element );

		///@brief Copy Constructor
		///@param node NodeT<T> to be copied
		NodeT( const NodeT<T> & node );

		///@brief Move Constructor
		///@param node NodeT<T> to be moved
		NodeT( NodeT<T> && node );

		///@brief Destructor.
		~NodeT();

		///@brief Copy operator
		///@param node NodeT<T> to be copied
		///@return reference to THIS
		NodeT<T> & operator=( const NodeT<T> & node );

		///@brief Move operator
		///@param node NodeT<T> to be moved
		///@return reference to THIS
		NodeT<T> & operator=( NodeT<T> && node );


		///@brief Get the type of this NodeT<T> (If the node is of type Text, it can be casted freely into NodeTextT, or the method toText can be used)
		///@return Type of this node
		NodeT<T>::Type getType() const;

		///@brief Cast this node into a text one, ONLY appliable if getType() return NodeT<T>::Type::Text
		///@return Pointer to a NodeTextT
		const NodeTextT<T> * toText() const;
		NodeTextT<T> * toText();

		///@brief Get the parent of this node
		///@return Pointer to the parent if there is one (NULL otherwise)
		const NodeT<T> * getParent() const;
		NodeT<T> * getParent();

		///@brief Get the Value of this node (Only appliable if getType() == Text) or of the child if a text child is present 
		///@return Value of this node
		const T & getValue() const;

		///@brief Set the value of this node (Will change this node value if getType() == Text, otherwise will try to change the first child value)
		///@param value Value to be set
		void setValue( const T & value );

		///@brief set the name of this node
		///@param name Name of this node
		void setName( const T & name );

		///@brief get the name of this node
		///@return name of this node
		const T & getName() const;

		///@brief Add a param to this node
		///@param param ParamT<T> to add to this node
		void addParam( const ParamT<T> & param );

		///@brief Add a param to this node
		///@param param Pointer to the ParamT<T> to add (Has to be allocated but NOT deallocated)
		void addParam( ParamT<T> * param );

		///brief Add a param to this node
		///@param name Name of the param to add
		///@param value Value of the param to add
		void addParam( const T & name, const T & value );

		///@brief get a param from his name
		///@param name Name of the param to retrieve
		///@return Pointer to the founded param or NULL of nothing has bee founded
		const ParamT<T> * getParam( const T & name ) const;
		ParamT<T> * getParam( const T & name );

		///@brief Get the number of params of this node
		///@return Number of params of this node
		Size getNbParams() const;
		
		///@brief Get a param from his index
		///@param i Index of the param to retrieve (between [0 ; getNbParams() - 1])
		///@return ParamT<T>
		const ParamT<T> & getParam( Size i ) const;
		ParamT<T> & getParam( Size i );

		///@brief Delete a param from this node
		///@param param ParamT<T> to be removed (The param itself is deleted during this operation, NEVER call delete directly from a param)
		///@return True if something has been removed, False otherwise
		bool deleteParam( ParamT<T> * param );

		///@brief Remove a child from this node
		///@param i Index of the param to be removed (The child itself is deleted during this operation, NEVER call delete directly from a param)
		///@return True if something has been removed, False otherwise
		bool deleteParam( Size i );

		///@brief Set the id of this node
		///@param id StringASCII representing the identifier if this node
		void setId( const T & id );

		///@brief Get the id of this node
		///@return Id of this node
		const T & getId() const;

		///@brief Get a vector filled by pointer to all the node corresponding to the id searched in this sub tree.
		///@param id Id to look for
		///@return Vector of NodeT<T>'s pointers with the searched id
		Vector< NodeT<T> * > getElementsById( const T & id ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<T>'s pointers with the searched name
		Vector< NodeT<T> * > getElementsByName( const T & name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		const NodeT<T> * getChild( Size i ) const;
		NodeT<T> * getChild( Size i );

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
		bool deleteChild( Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		NodeT<T> * removeChild( NodeT<T> * child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		NodeT<T> * removeChild( Size i );

		///@brief Write this object in the XML syntax into the stream
		///@param stream stream used to write this object
		///@param tabs Indentation.
		///@return True if success, False otherwise
		template<typename Stream>
		bool writeXML( Stream * stream, unsigned int tabs = 0 ) const;

		///@brief Write this Node to an Object that support operator '<<'.
		///@param str Object to write to.
		///@param tabs Number of tabulation to be added.
		///@return bool True if success, False otherwise.
		template<typename C = T>
		bool writeXML( C & str, unsigned int tabs = 0 ) const;

		///@brief Parse some XML as text and append it to this object.
		///@param buffer Buffer to be read.
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool appendXML( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool appendXML( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief Parse some XML as text and append it to this object.
		///@param str String to be read.
		///@return bool True if success, False otherwise.
		bool appendXML( const T & str );

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;

		///@brief Print an human-readable String of this NodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S = T>
		S toString( unsigned int indent = 0 ) const;

		///@brief Print an human-readable String of this NodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		T toStringDebug( unsigned int indent = 0 ) const;

		///@brief Read this node using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool _readXML( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief Write this node to an Object that support opperator '<<'.
		///@param o Object to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = T, typename Elem = C::ElemType>
		void _writeXML( C & o, unsigned int tabs = 0 ) const;

		///@brief Check if the buffer at the current position is the expected character. Increment the buffer it True.
		///@param buffer Buffer to check.
		///@param c Character to be compared.
		///@return bool True if the buffer is the expected character at the current position.
		template<typename C>
		static bool _expectChar( const C ** buffer, const C & c );

	protected:
		void _clear();
		void _unload();
		template<typename Stream>
		bool _write( Stream * stream ) const;
		template<typename Stream>
		bool _read( Stream * stream );
		bool _setChildName( NodeT<T> * child, const T & name );
		bool _setChildId( NodeT<T> * child, const T & id );
		void _getElementsById( Vector < NodeT<T> * > * nodeVector, const T & id ) const;
		void _getElementsByName( Vector < NodeT<T> * > * nodeVector, const T & name ) const;
		
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool _parseParameter( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		

	private:
		Type type;
		T name;
		T id;

		NodeT<T> * parent;

		Map< T, ParamT<T> * > paramsMap;
		MultiMap< T, NodeT<T> * > childrenMap;
		Vector< ParamT<T> * > paramsVector;
		Vector< NodeT<T> * > childrenVector;

		MultiMap< T, NodeT<T> * > childrenByIdMap;
	};

	using Node = NodeT<UTF8String>;

	template<typename T>
	class NodeTextT : public NodeT<T> {
	public:
		///@brief Empty constructor
		NodeTextT();

		///@brief create node
		///@param value value of the node
		NodeTextT( const T & value );

		///@brief Copy Constructor
		///@param node NodeT<T> to be copied
		NodeTextT( const NodeTextT<T> & node );

		///@brief Move Constructor
		///@param node NodeT<T> to be moved
		NodeTextT( NodeTextT<T> && node );

		///@brief Copy operator
		///@param node NodeT<T> to be copied
		///@return reference to THIS
		NodeTextT<T> & operator=( const NodeTextT<T> & node );

		///@brief Move operator
		///@param node NodeT<T> to be moved
		///@return reference to THIS
		NodeTextT<T> & operator=( NodeTextT<T> && node );

		///@brief Get the value of this node
		///@return Value
		const T & getValue() const;
		T & getValue();


		///@brief Set the value of this node
		///@param value Value to be set
		void setValue( const T & value );

		///@brief Write this object in the XML syntax into the stream
		///@param stream stream used to write this object
		///@return True if success, False otherwise
		template<typename Stream>
		bool writeXML( Stream * stream ) const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;

		///@brief Print an human-readable String of this NodeT<T> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S = T>
		S toString( unsigned int indent = 0 ) const;

		template<typename C = T, typename Elem = C::ElemType>
		void _writeXML( C & o, unsigned int tabs = 0 ) const;
	private:
		void _clear();
		

		
		T value;


	};

	using NodeText = NodeTextT<UTF8String>;



}

#include "Node.hpp"
