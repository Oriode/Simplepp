/**
 * @file	Map.h.
 *
 * @brief	Declares the map class
 * @author	Clément Gerber
 * @date	26/10/16 (D/M/Y)
 */
#pragma once

#include "Log.h"
#include "IO/IO.h"
#include "String.h"
#include "Utility.h"


 /**
  * @brief	A map object.
  *
  * @tparam	I	Generic type parameter.
  * @tparam	T	Generic type parameter.
  */
template<typename I, typename T>
class MapObject : public BasicSimpleIO {
public:
	/** @brief	Default constructor */
	MapObject();

	/**
	 * @brief	Constructor
	 *
	 * @param	index	Zero-based index of the.
	 * @param	value	The value.
	 */
	MapObject( const I & index, const T & value );

	/** @brief	Destructor */
	~MapObject();

	/**
	 * @brief	Cast that converts the given  to a BasicString
	 *
	 * @returns	The result of the operation.
	 */
	template<typename C = char>
	operator BasicString<C>() const;

	/**
	 * @brief	Get the Index of this Key
	 *
	 * @returns	Index.
	 */
	const I & getIndex() const;
	/**
	 * @brief	Gets the index
	 *
	 * @returns	The index.
	 */
	I & getIndex();

	/**
	 * @brief	Set the index of this key
	 *
	 * @param	index	Index to be set.
	 */
	void setIndex( const I & index );

	/**
	 * @brief	Get the value of this key
	 *
	 * @returns	Value.
	 */
	const T & getValue() const;
	/**
	 * @brief	Gets the value
	 *
	 * @returns	The value.
	 */
	T & getValue();

	/**
	 * @brief	Set the value of this key
	 *
	 * @param	value	Value to be set.
	 */
	void setValue( const T & value );

	/**
	 * @brief	Equality operator
	 *
	 * @param	o	A MapObject to process.
	 *
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==( const MapObject & o ) const;
	/**
	 * @brief	Greater-than comparison operator
	 *
	 * @param	o	A MapObject to process.
	 *
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>( const MapObject & o ) const;
	/**
	 * @brief	Less-than comparison operator
	 *
	 * @param	o	A MapObject to process.
	 *
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<( const MapObject & o ) const;
	/**
	 * @brief	Greater-than-or-equal comparison operator
	 *
	 * @param	o	A MapObject to process.
	 *
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=( const MapObject & o ) const;

	/**
	 * @brief	Less-than-or-equal comparison operator
	 *
	 * @param	o	A MapObject to process.
	 *
	 * @returns	True if the first parameter is less than or equal to the second.
	 */
	bool operator<=( const MapObject & o ) const;

	/** @brief	Index of the MapObject */
	I index;
	/** @brief	Value of the MapObject */
	T value;

	/**
	 * @brief	read from a file stream
	 *
	 * @param [in,out]	fileStream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( std::fstream * fileStream );

	/**
	 * @brief	write this object as binary into a file stream
	 *
	 * @param [in,out]	fileStream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool write( std::fstream * fileStream ) const;
};











/**
 * @brief	A rb node.
 *
 * @tparam	T	Generic type parameter.
 */
template<typename T>
class RBNode : public BasicIO {
public:
	/** @brief	Values that represent colors */
	enum class Color : bool {
		Red = true, Black = false
	};

	/** @brief	Empty constructor */
	RBNode();

	/**
	 * @brief	Constructor from parent
	 *
	 * @param [in,out]	parent	Pointer to the parent Node.
	 */
	RBNode( RBNode<T> * parent );

	/**
	 * @brief	Constructor from parent and a value
	 *
	 * @param [in,out]	parent	Pointer to the parent Node.
	 * @param 		  	value 	Value of this node.
	 */
	RBNode( RBNode<T> * parent, const T & value );

	/**
	 * @brief	Copy Constructor ( The node and all the sub tree is copied too, Parent is set to NULL )
	 *
	 * @param	node	Node to be copied.
	 */
	RBNode( const RBNode<T> & node );

	/**
	 * @brief	Move Constructor
	 *
	 * @param [in,out]	node	Node to be moved.
	 */
	RBNode( RBNode<T> && node );

	/** @brief	Destructor ( All the sub tree is deleted too ) */
	~RBNode();

	/**
	 * @brief	Copy operator (The node and all the sub tree is copied too, Parent is set to NULL)
	 *
	 * @param	node	Node to be copied.
	 *
	 * @returns	reference to THIS.
	 */
	RBNode<T> & operator=( const RBNode<T> & node );

	/**
	 * @brief	Move operator
	 *
	 * @param [in,out]	node	Node to be moved.
	 *
	 * @returns	reference to THIS.
	 */
	RBNode<T> & operator=( RBNode<T> && node );

	/**
	 * @brief	Get the parent of this node
	 *
	 * @returns	Pointer to the parent node of this one.
	 */
	const RBNode<T> * getParent() const;
	/**
	 * @brief	Gets the parent of this item
	 *
	 * @returns	Null if it fails, else the parent.
	 */
	RBNode<T> * getParent();

	/**
	 * @brief	Get the left child of this node
	 *
	 * @returns	Pointer to the left child node of this one.
	 */
	const RBNode<T> * getLeft() const;
	/**
	 * @brief	Gets the left
	 *
	 * @returns	Null if it fails, else the left.
	 */
	RBNode<T> * getLeft();

	/**
	 * @brief	Get the right child of this node
	 *
	 * @returns	Pointer to the right child node of this one.
	 */
	const RBNode<T> * getRight() const;
	/**
	 * @brief	Gets the right
	 *
	 * @returns	Null if it fails, else the right.
	 */
	RBNode<T> * getRight();

	/**
	 * @brief	Set the value of this node
	 *
	 * @param	value	Value of this node.
	 */
	void setValue( const T & value );

	/**
	 * @brief	Get the Value of this node
	 *
	 * @returns	Value of this node.
	 */
	const T & getValue() const;
	/**
	 * @brief	Gets the value
	 *
	 * @returns	The value.
	 */
	T & getValue();

	/**
	 * @brief	Get the color of this node
	 *
	 * @returns	Color of this node.
	 */
	typename RBNode<T>::Color getColor() const;

	/**
	 * @brief	Create a human readable string with this sub tree
	 *
	 * @tparam	C	Type of the c.
	 *
	 * @returns	StringASCII.
	 */
	template<typename C = char>
	BasicString<C> toString() const;

	/**
	 * @brief	read from a file stream (children will be read recursively)
	 *
	 * @param [in,out]	fileStream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( std::fstream * fileStream );

	/**
	 * @brief	write this object as binary into a file stream (children will be wrote recursively)
	 *
	 * @param [in,out]	fileStream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool write( std::fstream * fileStream ) const;

	/************************************************************************/
	/* STATIC                                                               */
	/************************************************************************/
	/**
	 * @brief	Get the Grand Parent of this node
	 *
	 * @param	n	Node from where to retrieve the uncle.
	 *
	 * @returns	Grand Parent of this node (Parent of the Parent)
	 */
	static RBNode<T> * getGrandParent( const RBNode<T> & n );

	/**
	 * @brief	Get the Uncle of this node
	 *
	 * @param	n	Node from where to retrieve the uncle.
	 *
	 * @returns	Uncle of this node.
	 */
	static RBNode<T> * getUncle( const RBNode<T> & n );

	/**
	 * @brief	Call this method when you have just inserted a new left in the tree to keep the tree balanced
	 *
	 * @param [in,out]	node	Pointer to the node just inserted (parent and child correctly set)
	 * @param [in,out]	root	out root Pointer to the Pointer of the root.
	 */
	static void insertNode( RBNode<T> * node, RBNode<T> ** root );

	/**
	 * @brief	Call this method when you want to insert a node at the left on one another and keep the tree balanced
	 *
	 * @param [in,out]	parentNode	Node where to place the new one.
	 * @param [in,out]	newNode   	Pointer to the node you want to insert.
	 * @param [in,out]	root	  	out root Pointer to the Pointer of the root.
	 */
	static void insertNodeLeft( RBNode<T> * parentNode, RBNode<T> * newNode, RBNode<T> ** root );

	/**
	 * @brief	Call this method when you want to insert a node at the right on one another and keep the tree balanced
	 *
	 * @param [in,out]	parentNode	Node where to place the new one.
	 * @param [in,out]	newNode   	Pointer to the node you want to insert.
	 * @param [in,out]	root	  	out root Pointer to the Pointer of the root.
	 */
	static void insertNodeRight( RBNode<T> * parentNode, RBNode<T> * newNode, RBNode<T> ** root );

	/**
	 * @brief	Delete a node from the tree
	 *
	 * @param [in,out]	node	Node to be deleted from the tree.
	 * @param [in,out]	root	out root Pointer to the Pointer of the root.
	 */
	static void deleteNode( RBNode<T> * node, RBNode<T> ** root );

	/**
	 * @brief	Create a human readable string with a sub tree (can be NULL)
	 *
	 * @tparam	C	Type of the c.
	 * @param [in,out]	root	Pointer to the root node of the tree.
	 *
	 * @returns	StringASCII.
	 */
	template<typename C = char>
	static BasicString<C> toString( RBNode<T> * root );


	/**
	 * @brief	DEBUG stuff, do not use it
	 *
	 * @param [in,out]	node			If non-null, the node.
	 * @param 		  	nbBlackNodes	The nb black nodes.
	 *
	 * @returns	An int.
	 */
	static unsigned int _checkNbBlackNode( RBNode<T> * node, unsigned int nbBlackNodes );
protected:
	/** @brief	Values that represent Constructors */
	enum ctor {
		null
	};
	/**
	 * @brief	Constructor
	 *
	 * @param	parameter1	The first parameter.
	 */
	RBNode( ctor );

private:
	/**
	 * @brief	Set the parent of this node
	 *
	 * @param [in,out]	parent Pointer to the parent node of this one
	 */
	void setParent( RBNode<T> * parent );

	/**
	 * @brief	Set the left child of this node
	 *
	 * @param [in,out]	left	Pointer to the left child node of this one.
	 */
	void setLeft( RBNode<T> * left );

	/**
	 * @brief	Set the right child of this node
	 *
	 * @param [in,out]	right	Pointer to the right child node of this one.
	 */
	void setRight( RBNode<T> * right );

	/**
	 * @brief	Set the color of this node
	 *
	 * @param	color	Color to set.
	 */
	void setColor( typename RBNode<T>::Color color );

	/** @brief	Swap the color of this node */
	void swapColor();

	/** @brief	Clears this object to its blank/initial state */
	void _clear();
	/** @brief	Unloads this object */
	void _unload();

	/**
	 * @brief	Deletes the fix up
	 *
	 * @param [in,out]	node   	If non-null, the node.
	 * @param [in,out]	root   	If non-null, the root.
	 * @param [in,out]	P	   	If non-null, a RBNode<T> to process.
	 * @param 		  	NisLeft	True to nis left.
	 */
	static void _deleteFixUp( RBNode<T> * node, RBNode<T> ** root, RBNode<T> * P, bool NisLeft );

	/** @brief	The value */
	T value;

	/** @brief	The parent */
	RBNode<T> * parent;
	/** @brief	The left */
	RBNode<T> * left;
	/** @brief	The right */
	RBNode<T> * right;

	/** @brief	The color */
	Color color;
};









/**
 * @brief	Data structure where datas of types T are ordered in a binary Red Black Tree
 *
 * @tparam	I	   	Generic type parameter.
 * @tparam	T	   	Generic type parameter.
 * @tparam	Compare	Type of the compare.
 *
 * @sa	https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 */
template<typename I, typename T, typename Compare = Math::Compare::Template>
class RBTree : public BasicIO {
public:
	/** @brief	Defines an alias representing the iterator */
	typedef RBNode< MapObject<I, T> > * Iterator;

	/**
	 * @brief	Empty Constructor
	 *
	 * @param	compareFunc	(Optional) Functor with operator() overloaded with : Math::Compare::Value operator()( const T & , const T & ) const;
	 * 						For security reasons, the functor should inherite from Math::Compare::Template.
	 */
	RBTree( const Compare & compareFunc = Compare() );

	/**
	 * @brief	Copy Constructor
	 *
	 * @param	tree	Tree to copy.
	 */
	RBTree( const RBTree<I, T, Compare> & tree );

	/**
	 * @brief	Move Constructor
	 *
	 * @param [in,out]	tree	Tree to move from.
	 */
	RBTree( RBTree<I, T, Compare> && tree );

	/** @brief	destructor */
	~RBTree();

	/**
	 * @brief	Conversion to StringASCII operator
	 *
	 * @returns	The result of the operation.
	 */
	template<typename C = char>
	operator BasicString<C>() const;

	/**
	 * @brief	Copy operator
	 *
	 * @param	tree	Tree to copy.
	 *
	 * @returns	reference to THIS.
	 */
	RBTree<I, T, Compare> & operator=( const RBTree<I, T, Compare> & tree );

	/**
	 * @brief	Move operator
	 *
	 * @param [in,out]	tree	Tree to move from.
	 *
	 * @returns	reference to THIS.
	 */
	RBTree<I, T, Compare> & operator=( RBTree<I, T, Compare> && tree );

	/************************************************************************/
	/* Iterations                                                           */
	/************************************************************************/
	/**
	 * @brief	iterate ONE time the iterator and return if there is still data
	 *
	 * @param [in,out]	it	If non-null, the iterator.
	 *
	 * @returns	it in out Iterator to iterate.
	 * @returns	If the iterator can return data.
	 */
	bool iterate( typename RBTree<I, T, Compare>::Iterator * it ) const;

	/**
	 * @brief	Iterate ONE time and set the pointer to the pointer of the data retrieved
	 *
	 * @param [in,out]	it	in out Iterator to iterate.
	 * @param [in,out]	i 	out Pointer to a pointer to the index retrieved.
	 * @param [in,out]	v 	out Pointer to a pointer to the value retrieved.
	 *
	 * @returns	True if a data has been retrieved or False if the end has been reached.
	 */
	bool iterate( typename RBTree<I, T, Compare>::Iterator * it, I ** i, T ** v ) const;

	/**
	 * @brief	Iterate ONE time and set the pointer to the pointer of the data retrieved
	 *
	 * @tparam	TestFunctor	Type of the test functor.
	 * @param [in,out]	it		   	in out Iterator to iterate.
	 * @param [in,out]	i		   	out Pointer to a pointer to the index retrieved.
	 * @param [in,out]	v		   	out Pointer to a pointer to the value retrieved.
	 * @param [in,out]	testFunctor	Functor to check a condition before incrementing the iterator
	 * 								  		bool operator()( const T & e );
	 *
	 * @returns	True if a data has been retrieved or False if the end has been reached or false is the functor return false.
	 */
	template<typename TestFunctor>
	bool iterate( typename RBTree<I, T, Compare>::Iterator * it, I ** i, T ** v, TestFunctor & testFunctor ) const;

	/**
	 * @brief	get the Begin Iterator
	 *
	 * @returns	Begin Iterator.
	 */
	typename RBTree<I, T, Compare>::Iterator getBegin() const;
	/**
	 * @brief	Gets the begin
	 *
	 * @returns	A RBTree<I,T,Compare>::Iterator.
	 */
	typename RBTree<I, T, Compare>::Iterator begin() const;

	/**
	 * @brief	get the End Iterator
	 *
	 * @returns	End Iterator.
	 */
	typename RBTree<I, T, Compare>::Iterator getEnd() const;
	/**
	 * @brief	Gets the end
	 *
	 * @returns	A RBTree<I,T,Compare>::Iterator.
	 */
	typename RBTree<I, T, Compare>::Iterator end() const;

	/************************************************************************/
	/* Access                                                               */
	/************************************************************************/
	/**
	 * @brief	Access from a value using and index
	 *
	 * @param	index	Index to be used.
	 *
	 * @returns	The indexed value.
	 *
	 * ### param	Pointer	to the value if founded, if not, return NULL.
	 */
	const T * operator[]( const I & index ) const;
	/**
	 * @brief	Array indexer operator
	 *
	 * @param	index	Zero-based index of the.
	 *
	 * @returns	The indexed value.
	 */
	T * operator[]( const I & index );

	/**
	 * @brief	Access from a value using and index
	 *
	 * @param	index	Index to be used.
	 *
	 * @returns	Null if it fails, else the value i.
	 *
	 * ### param	Pointer	to the value if founded, if not, return NULL.
	 */
	const T * getValueI( const I & index ) const;
	/**
	 * @brief	Gets value i
	 *
	 * @param	index	Zero-based index of the.
	 *
	 * @returns	Null if it fails, else the value i.
	 */
	T * getValueI( const I & index );

	/**
	 * @brief	Access from a value using and index
	 *
	 * @param	index	Index to be used.
	 *
	 * @returns	Null if it fails, else the node i.
	 *
	 * ### param	Pointer	to the node if founded, if not, return NULL.
	 */
	const RBNode< MapObject<I, T> > * getNodeI( const I & index ) const;
	/**
	 * @brief	Gets node i
	 *
	 * @param	index	Zero-based index of the.
	 *
	 * @returns	Null if it fails, else the node i.
	 */
	RBNode< MapObject<I, T> > * getNodeI( const I & index );

	/**
	 * @brief	Get the Value associated with an iterator
	 *
	 * @param	it	Iterator used to retrieve the value (no bound check is done here)
	 *
	 * @returns	Value founded.
	 */
	const T & getValueIt( typename RBTree<I, T, Compare>::Iterator it ) const;
	/**
	 * @brief	Gets value iterator
	 *
	 * @param	it	The iterator.
	 *
	 * @returns	The value iterator.
	 */
	T & getValueIt( typename RBTree<I, T, Compare>::Iterator it );

	/**
	 * @brief	Get the Index associated with an iterator
	 *
	 * @param	it	Iterator used to retrieve the index (no bound check is done here)
	 *
	 * @returns	Index founded.
	 */
	const I & getIndexIt( typename RBTree<I, T, Compare>::Iterator it ) const;
	/**
	 * @brief	Gets index iterator
	 *
	 * @param	it	The iterator.
	 *
	 * @returns	The index iterator.
	 */
	I & getIndexIt( typename RBTree<I, T, Compare>::Iterator it );

	/**
	 * @brief	Set the Value associated with an index ( The index has to already exists )
	 *
	 * @param	index	Index used to set the value.
	 * @param	v	 	A T to process.
	 */
	void setValueI( const I & index, const T & v );

	/**
	 * @brief	Set the Value associated with an iterator
	 *
	 * @param	it	Iterator used to set the value.
	 * @param	v 	A T to process.
	 */
	void setValueIt( typename RBTree<I, T, Compare>::Iterator it, const T & v );

	/**
	 * @brief	Set the Index associated with an iterator
	 *
	 * @param	it	Iterator used to set the index.
	 * @param	v 	An I to process.
	 */
	void setIndexIt( typename RBTree<I, T, Compare>::Iterator it, const I & v );



	/**
	 * @brief	Get if the Tree is empty of not
	 *
	 * @returns	True if the Tree is empty, false otherwise.
	 */
	bool isEmpty() const;

	/** @brief	clear the complete Tree */
	void clear();

	/**
	 * @brief	Insert a new [ Index => Value ] into the map
	 *
	 * @param	index	Index of the value to insert.
	 * @param	value	Value to be inserted.
	 *
	 * @returns	Pointer to the value just inserted, NULL if nothing has been inserted.
	 */
	T * insert( const I & index, const T & value );

	/**
	 * @brief	Insert a new [ Index => Value ] into the map and return the Node just insert (prefere using insert())
	 *
	 * @param	index	Index of the value to insert.
	 * @param	value	Value to be inserted.
	 *
	 * @returns	Pointer to the node just inserted, NULL if nothing has been inserted.
	 */
	RBNode< MapObject<I, T> > * insertNode( const I & index, const T & value );


	/**
	 * @brief	Delete a node from the map
	 *
	 * @param	index	Index to search and to be deleted.
	 *
	 * @returns	Boolean if a key has been deleted.
	 */
	bool eraseIndex( const I & index );

	/**
	 * @brief	Delete a node from the map
	 *
	 * @param [in,out]	node	Node to be deleted from the map.
	 *
	 * @returns	Boolean if the node has been deleted.
	 */
	bool eraseNode( RBNode< MapObject<I, T> > * node );


	/**
	 * @brief	Create an human readable string from this tree
	 *
	 * @tparam	C	Type of the c.
	 *
	 * @returns	StringASCII.
	 */
	template<typename C = char>
	BasicString<C> toString() const;

	/**
	 * @brief	Read from a file stream (children will be read recursively)
	 *
	 * @param [in,out]	fileStream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( std::fstream * fileStream );

	/**
	 * @brief	Write this object as binary into a file stream (children will be wrote recursively)
	 *
	 * @param [in,out]	fileStream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool write( std::fstream * fileStream ) const;
protected:
	/** @brief	Clears this object to its blank/initial state */
	void _clear();
	/** @brief	Unloads this object */
	void _unload();

	/**
	 * @brief	Create a new node [Index => Value] and insert it into the tree
	 *
	 * @param	index	Zero-based index of the.
	 * @param	value	The value.
	 *
	 * @returns	Node freshly created (NULL if nothing has been inserted)
	 */
	RBNode< MapObject< I, T > > * _insert( const I & index, const T & value );

	/**
	 * @brief	Check the integrity of the tree
	 *
	 * @param [in,out]	root   	Pointer of the root.
	 * @param [in,out]	functor	Comparison functor.
	 */
	static void _checkTree( RBNode< MapObject<I, T> > * root, Compare & functor );
	/**
	 * @brief	Check tree sorted
	 *
	 * @param [in,out]	root   	If non-null, the root.
	 * @param [in,out]	functor	The functor.
	 */
	static void _checkTreeSorted( RBNode< MapObject<I, T> > * root, Compare & functor );

	/** @brief	The root node */
	RBNode< MapObject<I, T> > * rootNode;
	/** @brief	The compare function */
	Compare compareFunc;
};






/** @brief	The map */
template<typename I, typename T, typename Compare = Math::Compare::Template>
using Map = RBTree<I, T, Compare>;










/*
///@brief Data structure where datas of types T are ordered in a binary Red Black Tree
///@see https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
template<typename I, typename T, typename Compare = Math::Logical::Less>
class Map : protected Vector< MapObject<I, T> * >, public RBTree<I, T, Compare>, public virtual BasicSimpleIO {
public:
	using Vector< MapObject<I, T> * >::Iterator;
	using Vector< MapObject<I, T> * >::Size;

	///@brief Empty Constructor
	///@param compareFunc Functor used to order the Tree
	Map( const Compare & compareFunc = Compare() );

	///@brief Copy Constructor
	///@param tree Tree to copy
	Map( const Map<I, T, Compare> & tree );

	///@brief Move Constructor
	///@param tree Tree to move from
	Map( Map<I, T, Compare> && tree );

	///@brief Conversion to StringASCII operator
	///@return StringASCII
	template<typename C = char>
	operator BasicString<C>() const;

	///@brief Copy operator
	///@param tree Tree to copy
	///@return reference to THIS
	Map<I, T, Compare> & operator=( const Map<I, T, Compare> & tree );

	///@brief Move operator
	///@param tree Tree to move from
	///@return reference to THIS
	Map<I, T, Compare> & operator=( Map<I, T, Compare> && tree );

	///@see RBTree::operator[]
	using RBTree<I, T, Compare>::operator[];


	/ ************************************************************************ /
	/ * Iterations                                                           * /
	/ ************************************************************************ /

	///@brief iterate ONE time the iterator and return if there is still data
	///@return it in out Iterator to iterate
	///@return If the iterator can return data
	bool iterate( typename Map<I, T, Compare>::Iterator * it ) const;

	///@brief Iterate ONE time and set the pointer to the pointer of the data retrieved
	///@param it in out Iterator to iterate
	///@param i out Pointer to a pointer to the index retrieved
	///@param v out Pointer to a pointer to the value retrieved
	///@return True if a data has been retrieved or False if the end has been reached
	bool iterate( typename Map<I, T, Compare>::Iterator * it, I ** i, T ** v ) const;

	///@brief Iterate ONE time and set the pointer to the pointer of the data retrieved
	///@param it in out Iterator to iterate
	///@param i out Pointer to a pointer to the index retrieved
	///@param v out Pointer to a pointer to the value retrieved
	///@param testFunctor Functor to check a condition before incrementing the iterator
	///								bool operator()( const ElemType & e );
	///@return True if a data has been retrieved or False if the end has been reached or false is the functor return false
	template<typename TestFunctor>
	bool iterate( typename Map<I, T, Compare>::Iterator * it, I ** i, T ** v, TestFunctor & testFunctor ) const;

	///@see Vector::getBegin()
	using Vector< MapObject<I, T> * >::getBegin;
	using Vector< MapObject<I, T> * >::begin;

	///@see Vector::getEnd()
	using Vector< MapObject<I, T> * >::getEnd;
	using Vector< MapObject<I, T> * >::end;


	/ ************************************************************************ /
	/ * Access                                                               * /
	/ ************************************************************************ /

	///@brief Get the Value associated with an iterator
	///@param it Iterator used to retrieve the value (no bound check is done here)
	///@return Value founded
	const T & getValueIt( typename Map<I, T, Compare>::Iterator it ) const;
	T & getValueIt( typename Map<I, T, Compare>::Iterator it );

	///@brief Get the Index associated with an iterator
	///@param it Iterator used to retrieve the index (no bound check is done here)
	///@return Index founded
	const I & getIndexIt( typename Map<I, T, Compare>::Iterator it ) const;
	I & getIndexIt( typename Map<I, T, Compare>::Iterator it );

	///@brief Get the Value associated with an direct access index (of type Size)
	///@param i Iterator used to retrieve the value (no bound check is done here)
	///@return Value founded
	const T & getValueI( typename Map<I, T, Compare>::Size i ) const;
	T & getValueI( typename Map<I, T, Compare>::Size i );

	///@brief Get the Index associated with an iterator
	///@param i Iterator used to retrieve the index (no bound check is done here)
	///@return Index founded
	const I & getIndexI( typename Map<I, T, Compare>::Size i ) const;
	I & getIndexI( typename Map<I, T, Compare>::Size i );

	///@brief Set the Value associated with an iterator
	///@param it Iterator used to set the value
	void setValueIt( typename Map<I, T, Compare>::Iterator it, const T & v );

	///@brief Set the Index associated with an iterator
	///@param it Iterator used to set the index
	void setIndexIt( typename Map<I, T, Compare>::Iterator it, const I & v );

	///@brief Set the Value associated with an direct access index (of type Size)
	///@param i Iterator used to set the value (no bound check is done here)
	void setValueI( typename Map<I, T, Compare>::Size i, const T & v );

	///@brief Set the Index associated with an iterator
	///@param i Iterator used to set the index (no bound check is done here)
	void setIndexI( typename Map<I, T, Compare>::Size i, const I & v );



	///@brief Get if the Map is empty of not
	///@return True if the Map is empty, false otherwise.
	bool isEmpty() const;

	///@brief Clear the complete map
	void clear();

	///@brief Insert a new [ Index => Value ] into the map
	///@param index Index of the value to insert
	///@param value Value to be inserted
	///@return Pointer to the value just inserted, NULL if nothing has been inserted
	T * insert( const I & index, const T & value );

	///@brief Create an human readable string from this map
	///@return StringASCII
	template<typename C = char>
	BasicString<C> toString() const;

	///@brief Read from a file stream (children will be read recursively)
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief Write this object as binary into a file stream (children will be wrote recursively)
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;

protected:
	void _clear();

};*/





#include "MapObject.hpp"
#include "Map.hpp"
