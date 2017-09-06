///@file Node.h
///@brief File containing the Node Class, an XML Node
///@author Clement Gerber
///@date 20/10/16
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../MultiMap.h"
#include "../Math/Math.h"




namespace XML {


	class Param : public BasicIO {
	public:
		///@brief Empty constructor
		Param();

		///brief Constructor from a name and a value
		///@param name Name of this param
		///@param value Value of this param
		Param( const UTF8String & name, const UTF8String & value );

		///@brief Copy Constructor
		///@param param Object to copy
		Param( const Param & param );

		///@brief Move Constructor
		///@param param Object to move
		Param( Param && param );

		///@brief Convert to StringASCII operator
		///@return StringASCII generated
		operator UTF8String() const;

		///@brief Move operator
		///@param param Object to be copied
		///@return reference to THIS
		Param & operator=( const Param & param );

		///@brief Move operator
		///@param param Object to be copied
		///@return reference to THIS
		Param & operator=( Param && param );

		///@brief get the name of this param
		///@return Name of the param
		const UTF8String & getName() const;

		///@brief Set the name of this param (Warning: Changing this param name to "id" will not change the id of the node associated, @see Node::setId())
		///@param name Name of this param
		void setName( const UTF8String & name );

		///@brief get the value of this param 
		///@return value of the param
		const UTF8String & getValue() const;

		///@brief Set the value of this param (Warning: Changing this param value if name is "id" will not change the id of the node associated, @see Node::setId())
		///@param value Value of this param
		void setValue( const UTF8String & value );

		///@brief Generate a StringASCII from this object
		///@return StringASCII
		UTF8String toString() const;

		///@brief Write this object in the XML syntax into the fileStream
		///@param fileStream stream used to write this object
		///@return True if success, False otherwise
		bool writeXML( std::fstream * fileStream ) const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream (@see writeXML for writing non binary)
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;
	private:
		void _clear();
		
		UTF8String name;
		UTF8String value;
	};




	class NodeText;


	///@brief Represent a node in the XML Tree, Only 3 Types available ( Element, Text and Document )
	/// 
	class Node : public BasicIO {
	public:
		enum class Type : unsigned int { 
			Element = 1,
			Text = 3,
			Document = 9
		};

		///@brief Empty constructor
		///@param type Type of this node
		Node( );

		///@brief create node
		///@param name Name of the node
		///@param type Type of this node
		Node( const UTF8String & name, Type type = Type::Element );

		///@brief Copy Constructor
		///@param node Node to be copied
		Node( const Node & node );

		///@brief Move Constructor
		///@param node Node to be moved
		Node( Node && node );

		///@brief Copy operator
		///@param node Node to be copied
		///@return reference to THIS
		Node & operator=( const Node & node );

		///@brief Move operator
		///@param node Node to be moved
		///@return reference to THIS
		Node & operator=( Node && node );


		///@brief Get the type of this Node (If the node is of type Text, it can be casted freely into NodeText, or the method toText can be used)
		///@return Type of this node
		Node::Type getType() const;

		///@brief Cast this node into a text one, ONLY appliable if getType() return Node::Type::Text
		///@return Pointer to a NodeText
		const NodeText * toText() const;
		NodeText * toText();

		///@brief Get the parent of this node
		///@return Pointer to the parent if there is one (NULL otherwise)
		const Node * getParent() const;
		Node * getParent();

		///@brief Get the Value of this node (Only appliable if getType() == Text) or of the child if a text child is present 
		///@return Value of this node
		const UTF8String & getValue() const;

		///@brief Set the value of this node (Will change this node value if getType() == Text, otherwise will try to change the first child value)
		///@param value Value to be set
		void setValue( const UTF8String & value );

		///@brief set the name of this node
		///@param name Name of this node
		void setName( const UTF8String & name );

		///@brief get the name of this node
		///@return name of this node
		const UTF8String & getName() const;

		///@brief Add a param to this node
		///@param param Param to add to this node
		void addParam( const Param & param );

		///@brief Add a param to this node
		///@param param Pointer to the Param to add (Has to be allocated but NOT deallocated)
		void addParam( Param * param );

		///brief Add a param to this node
		///@param name Name of the param to add
		///@param value Value of the param to add
		void addParam( const UTF8String & name, const UTF8String & value );

		///@brief get a param from his name
		///@param name Name of the param to retrieve
		///@return Pointer to the founded param or NULL of nothing has bee founded
		const Param * getParam( const UTF8String & name ) const;
		Param * getParam( const UTF8String & name );

		///@brief Get the number of params of this node
		///@return Number of params of this node
		typename Vector< Param * >::Size getNbParams() const;
		
		///@brief Get a param from his index
		///@param i Index of the param to retrieve (between [0 ; getNbParams() - 1])
		///@return Param
		const Param & getParam( typename Vector< Param * >::Size i ) const;
		Param & getParam( typename Vector< Param * >::Size i );

		///@brief Delete a param from this node
		///@param param Param to be removed (The param itself is deleted during this operation, NEVER call delete directly from a param)
		///@return True if something has been removed, False otherwise
		bool deleteParam( Param * param );

		///@brief Remove a child from this node
		///@param i Index of the param to be removed (The child itself is deleted during this operation, NEVER call delete directly from a param)
		///@return True if something has been removed, False otherwise
		bool deleteParam( typename Vector< Param * >::Size i );

		///@brief Set the id of this node
		///@param id StringASCII representing the identifier if this node
		void setId( const UTF8String & id );

		///@brief Get the id of this node
		///@return Id of this node
		const UTF8String & getId() const;

		///@brief Get a vector filled by pointer to all the node corresponding to the id searched in this sub tree.
		///@param id Id to look for
		///@return Vector of Node's pointers with the searched id
		Vector< Node * > getElementsById( const UTF8String & id ) const;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of Node's pointers with the searched name
		Vector< Node * > getElementsByName( const UTF8String & name ) const;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		typename Vector< Node * >::Size getNbChildren() const;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		const Node & getChild( typename Vector< Node * >::Size i ) const;
		Node & getChild( typename Vector< Node * >::Size i );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		void addChild( Node * child );

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		const Vector<Node *> getChild( const UTF8String & name ) const;
		Vector<Node *> getChild( const UTF8String & name );

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		bool deleteChild( Node * child );

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		bool deleteChild( typename Vector< Node * >::Size i );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		Node * removeChild( Node * child );

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		Node * removeChild( typename Vector< Node * >::Size i );

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
	protected:
		void _clear();
		void _unload();
		bool _writeXML( std::fstream * fileStream, unsigned int tabs ) const;
		bool _write( std::fstream * fileStream ) const;
		bool _read( std::fstream * fileStream );
		bool _setChildName( Node * child, const UTF8String & name );
		bool _setChildId( Node * child, const UTF8String & id );
		void _getElementsById( Vector < Node * > * nodeVector, const UTF8String & id ) const;
		void _getElementsByName( Vector < Node * > * nodeVector, const UTF8String & name ) const;

	private:
		Type type;
		UTF8String name;
		UTF8String id;

		Node * parent;

		Map< UTF8String, Param * > paramsMap;
		MultiMap< UTF8String, Node * > childrenMap;
		Vector< Param * > paramsVector;
		Vector< Node * > childrenVector;

		MultiMap< UTF8String, Node * > childrenByIdMap;
	};


	class NodeText : public Node {
	public:
		///@brief Empty constructor
		NodeText();

		///@brief create node
		///@param value value of the node
		NodeText( const UTF8String & value );

		///@brief Copy Constructor
		///@param node Node to be copied
		NodeText( const NodeText & node );

		///@brief Move Constructor
		///@param node Node to be moved
		NodeText( NodeText && node );

		///@brief Copy operator
		///@param node Node to be copied
		///@return reference to THIS
		NodeText & operator=( const NodeText & node );

		///@brief Move operator
		///@param node Node to be moved
		///@return reference to THIS
		NodeText & operator=( NodeText && node );

		///@brief Get the value of this node
		///@return Value
		const UTF8String & getValue() const;

		///@brief Set the value of this node
		///@param value Value to be set
		void setValue( const UTF8String & value );

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
	private:
		void _clear();

		
		UTF8String value;


	};



}
