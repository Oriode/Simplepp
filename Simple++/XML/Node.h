///@file NodeT<S>.h
///@brief File containing the NodeT<S> Class, an XML NodeT<S>
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

	template<typename S>
	class NodeTextT;

	///@brief Represent a node in the XML Tree, Only 3 Types available ( Element, Text and Document )
	template<typename S>
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
		NodeT( const S & name, Type type = Type::Element );

		///@brief Copy Constructor
		///@param node NodeT<S> to be copied
		NodeT( const NodeT<S> & node );

		///@brief Move Constructor
		///@param node NodeT<S> to be moved
		NodeT( NodeT<S> && node );

		///@brief Destructor.
		~NodeT();

		///@brief Copy operator
		///@param node NodeT<S> to be copied
		///@return reference to THIS
		NodeT<S> & operator=( const NodeT<S> & node );

		///@brief Move operator
		///@param node NodeT<S> to be moved
		///@return reference to THIS
		NodeT<S> & operator=( NodeT<S> && node );


		///@brief Get the type of this NodeT<S> (If the node is of type Text, it can be casted freely into NodeTextT, or the method toText can be used)
		///@return Type of this node
		NodeT<S>::Type getType() const;

		///@brief Cast this node into a text one, ONLY appliable if getType() return NodeT<S>::Type::Text
		///@return Pointer to a NodeTextT
		const NodeTextT<S> * toText() const;
		NodeTextT<S> * toText();

		///@brief Get the parent of this node
		///@return Pointer to the parent if there is one (NULL otherwise)
		const NodeT<S> * getParent() const;
		NodeT<S> * getParent();

		///@brief Get the Value of this node (Only appliable if getType() == Text) or of the child if a text child is present 
		///@return Value of this node
		const S & getValue() const;

		///@brief Set the value of this node (Will change this node value if getType() == Text, otherwise will try to change the first child value)
		///@param value Value to be set
		void setValue( const S & value );

		///@brief set the name of this node
		///@param name Name of this node
		void setName( const S & name );

		///@brief get the name of this node
		///@return name of this node
		const S & getName() const;

		///@brief Add a param to this node
		///@param param ParamT<S> to add to this node
		void addParam( const ParamT<S> & param );

		///@brief Add a param to this node
		///@param param Pointer to the ParamT<S> to add (Has to be allocated but NOT deallocated)
		void addParam( ParamT<S> * param );

		///brief Add a param to this node
		///@param name Name of the param to add
		///@param value Value of the param to add
		void addParam( const S & name, const S & value );

		///@brief get a param from his name
		///@param name Name of the param to retrieve
		///@return Pointer to the founded param or NULL of nothing has bee founded
		const ParamT<S> * getParam( const S & name ) const;
		ParamT<S> * getParam( const S & name );

		///@brief Get the number of params of this node
		///@return Number of params of this node
		Size getNbParams() const;
		
		///@brief Get a param from his index
		///@param i Index of the param to retrieve (between [0 ; getNbParams() - 1])
		///@return ParamT<S>
		const ParamT<S> & getParam( Size i ) const;
		ParamT<S> & getParam( Size i );

		///@brief Delete a param from this node
		///@param param ParamT<S> to be removed (The param itself is deleted during this operation, NEVER call delete directly from a param)
		///@return True if something has been removed, False otherwise
		bool deleteParam( ParamT<S> * param );

		///@brief Remove a child from this node
		///@param i Index of the param to be removed (The child itself is deleted during this operation, NEVER call delete directly from a param)
		///@return True if something has been removed, False otherwise
		bool deleteParam( Size i );

		///@brief Set the id of this node
		///@param id StringASCII representing the identifier if this node
		void setId( const S & id );

		///@brief Get the id of this node
		///@return Id of this node
		const S & getId() const;

		///@brief Get a vector filled by pointer to all the node corresponding to the id searched in this sub tree.
		///@param id Id to look for
		///@return Vector of NodeT<S>'s pointers with the searched id
		Vector< NodeT<S> * > getElementsById( const S & id ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeT<S>'s pointers with the searched name
		Vector< NodeT<S> * > getElementsByName( const S & name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		const NodeT<S> * getChild( Size i ) const;
		NodeT<S> * getChild( Size i );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		void addChild( NodeT<S> * child );

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		const Vector<NodeT<S> *> getChild( const S & name ) const;
		Vector<NodeT<S> *> getChild( const S & name );

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		bool deleteChild( NodeT<S> * child );

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		bool deleteChild( Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		NodeT<S> * removeChild( NodeT<S> * child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		NodeT<S> * removeChild( Size i );

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
		template<typename C = S>
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
		bool appendXML( const S & str );

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

		///@brief Print an human-readable String of this NodeT<S> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S2 = S>
		S2 toString( unsigned int indent = 0 ) const;

		///@brief Print an human-readable String of this NodeT<S> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		S toStringDebug( unsigned int indent = 0 ) const;

		///@brief Read this node using a pointer to a String Iterator.
		///@param buffer Pointer to a String iterator
		///@param endFunc Functor to check the buffer end.
		///@return bool True if success, False otherwise.
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool _readXML( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		///@brief Write this node to an Object that support opperator '<<'.
		///@param o Object to write to.
		///@param tabs Number of tabulations to be added.
		template<typename C = S, typename Elem = C::ElemType>
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
		bool _setChildName( NodeT<S> * child, const S & name );
		bool _setChildId( NodeT<S> * child, const S & id );
		void _getElementsById( Vector < NodeT<S> * > * nodeVector, const S & id ) const;
		void _getElementsByName( Vector < NodeT<S> * > * nodeVector, const S & name ) const;
		
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		bool _parseParameter( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		

	private:
		Type type;
		S name;
		S id;

		NodeT<S> * parent;

		Map< S, ParamT<S> * > paramsMap;
		MultiMap< S, NodeT<S> * > childrenMap;
		Vector< ParamT<S> * > paramsVector;
		Vector< NodeT<S> * > childrenVector;

		MultiMap< S, NodeT<S> * > childrenByIdMap;
	};

	using Node = NodeT<UTF8String>;

	template<typename S>
	class NodeTextT : public NodeT<S> {
	public:
		///@brief Empty constructor
		NodeTextT();

		///@brief create node
		///@param value value of the node
		NodeTextT( const S & value );

		///@brief Copy Constructor
		///@param node NodeT<S> to be copied
		NodeTextT( const NodeTextT<S> & node );

		///@brief Move Constructor
		///@param node NodeT<S> to be moved
		NodeTextT( NodeTextT<S> && node );

		///@brief Copy operator
		///@param node NodeT<S> to be copied
		///@return reference to THIS
		NodeTextT<S> & operator=( const NodeTextT<S> & node );

		///@brief Move operator
		///@param node NodeT<S> to be moved
		///@return reference to THIS
		NodeTextT<S> & operator=( NodeTextT<S> && node );

		///@brief Get the value of this node
		///@return Value
		const S & getValue() const;
		S & getValue();


		///@brief Set the value of this node
		///@param value Value to be set
		void setValue( const S & value );

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

		///@brief Print an human-readable String of this NodeT<S> and it's children.
		///@param indent Identation.
		///@return Human-redable String.
		template<typename S2 = S>
		S2 toString( unsigned int indent = 0 ) const;

		template<typename C = S, typename Elem = C::ElemType>
		void _writeXML( C & o, unsigned int tabs = 0 ) const;
	private:
		void _clear();
		

		
		S value;


	};

	using NodeText = NodeTextT<UTF8String>;



}

#include "Node.hpp"
