///@file BlackRedTree.h
///@brief File containing the Map Object
///@author Clement Gerber
///@date 26/10/16 (D/M/Y)
#pragma once

#include "Log.h"
#include "IO/IO.h"
#include "String.h"
#include "Utility.h"







template<typename I, typename T>
class MapObject : public BasicSimpleIO {
public:
	MapObject();
	MapObject( const I & index, const T & value );
	~MapObject();

	template<typename C = char>
	operator BasicString<C>() const;

	///@brief Get the Index of this Key
	///@return Index
	const I & getIndex() const;
	I & getIndex();

	///@brief Set the index of this key
	///@param index Index to be set
	void setIndex( const I & index );

	///@brief Get the value of this key
	///@return Value
	const T & getValue() const;
	T & getValue();

	///@brief Set the value of this key
	///@param value Value to be set
	void setValue( const T & value );

	/************************************************************************/
	/* LOGICAL                                                              */
	/************************************************************************/
	bool operator==( const MapObject & o ) const;
	bool operator>( const MapObject & o ) const;
	bool operator<( const MapObject & o ) const;
	bool operator>=( const MapObject & o ) const;
	bool operator<=( const MapObject & o ) const;

	I index;
	T value;

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;
};











template<typename T>
class RBNode : public BasicIO {
public:
	enum class Color : bool { Red = true, Black = false };

	///@brief Empty constructor
	RBNode();

	///@brief Constructor from parent
	///@param parent Pointer to the parent Node
	RBNode( RBNode<T> * parent );

	///@brief Constructor from parent and a value
	///@param parent Pointer to the parent Node
	///@param value Value of this node
	RBNode( RBNode<T> * parent,  const T & value );

	///@brief Copy Constructor ( The node and all the sub tree is copied too, Parent is set to NULL )
	///@param node Node to be copied
	RBNode( const RBNode<T> & node );

	///@brief Move Constructor
	///@param node Node to be moved
	RBNode( RBNode<T> && node );

	///@brief Destructor ( All the sub tree is deleted too )
	~RBNode();

	///@brief Copy operator (The node and all the sub tree is copied too, Parent is set to NULL)
	///@param node Node to be copied
	///@return reference to THIS
	RBNode<T> & operator=( const RBNode<T> & node );

	///@brief Move operator
	///@param node Node to be moved
	///@return reference to THIS
	RBNode<T> & operator=( RBNode<T> && node );

	///@brief Set the parent of this node
	///@param parent Pointer to the parent node of this one
	void setParent( RBNode<T> * parent );

	///@brief Get the parent of this node
	///@return Pointer to the parent node of this one
	RBNode<T> * getParent() const;

	///@brief Set the left child of this node
	///@param left Pointer to the left child node of this one
	void setLeft( RBNode<T> * left );

	///@brief Get the left child of this node
	///@return Pointer to the left child node of this one
	RBNode<T> * getLeft() const;

	///@brief Set the right child of this node
	///@param left Pointer to the right child node of this one
	void setRight( RBNode<T> * right );

	///@brief Get the right child of this node
	///@return Pointer to the right child node of this one
	RBNode<T> * getRight() const;

	///@brief Set the value of this node
	///@param value Value of this node
	void setValue( const T & value );

	///@brief Get the Value of this node
	///@return Value of this node
	const T & getValue() const;
	T & getValue();

	///@brief Set the color of this node
	///@param color Color to set
	void setColor( typename RBNode<T>::Color color );

	///@brief Get the color of this node
	///@return Color of this node
	typename RBNode<T>::Color getColor() const;

	///@brief Swap the color of this node
	void swapColor();

	///@brief Create a human readable string with this sub tree
	///@return String
	template<typename C = char>
	BasicString<C> toString() const;

	///@brief read from a file stream (childs will be read recursively)
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief write this object as binary into a file stream (childs will be wrote recursively)
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;

	/************************************************************************/
	/* STATIC                                                               */
	/************************************************************************/

	///@brief Get the Grand Parent of this node
	///@param n Node from where to retrieve the uncle
	///@return Grand Parent of this node (Parent of the Parent)
	static RBNode<T> * getGrandParent( const RBNode<T> & n );

	///@brief Get the Uncle of this node
	///@param n Node from where to retrieve the uncle
	///@return Uncle of this node
	static RBNode<T> * getUncle( const RBNode<T> & n );


	///@brief Call this method when you have just inserted a new left in the tree to keep the tree balanced
	///@param node Pointer to the node just inserted (parent and child correctly set)
	///@param in out root Pointer to the Pointer of the root
	static void insertNode( RBNode<T> * node, RBNode<T> ** root );

	///@brief Delete a node from the tree
	///@param node Node to be deleted from the tree
	///@param in out root Pointer to the Pointer of the root
	static void deleteNode( RBNode<T> * node, RBNode<T> ** root );

	///@brief Create a human readable string with a sub tree (can be NULL)
	///@param root Pointer to the root node of the tree
	///@return String
	template<typename C = char>
	static BasicString<C> toString( RBNode<T> * root );


	///@brief DEBUG stuff, do not use it
	static unsigned int _checkNbBlackNode( RBNode<T> * node, unsigned int nbBlackNodes );
protected:
	enum ctor { null };
	RBNode( ctor );

private:
	void _clear();
	void _unload();

	static void _deleteFixUp( RBNode<T> * node, RBNode<T> ** root, RBNode<T> * P, bool NisLeft );

	T value;

	RBNode<T> * parent;
	RBNode<T> * left;
	RBNode<T> * right;

	Color color;
};



	




///@brief Data structure where datas of types T are ordered in a binary Red Black Tree
///@see https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
template<typename I, typename T, typename Compare = Math::Logical::Less>
class RBTree : public BasicIO {
public:
	typedef RBNode< MapObject<I, T> > * Iterator;

	///@brief Empty Constructor
	///@param compareFunc Functor used to order the Tree
	RBTree( const Compare & compareFunc = Compare() );

	///@brief Copy Constructor
	///@param tree Tree to copy
	RBTree( const RBTree<I, T, Compare> & tree );

	///@brief Move Constructor
	///@param tree Tree to move from
	RBTree( RBTree<I, T, Compare> && tree );

	///@brief destructor
	~RBTree();

	///@brief Conversion to String operator
	template<typename C = char>
	operator BasicString<C>() const;

	///@brief Copy operator
	///@param tree Tree to copy
	///@return reference to THIS
	RBTree<I, T, Compare> & operator=( const RBTree<I, T, Compare> & tree );

	///@brief Move operator
	///@param tree Tree to move from
	///@return reference to THIS
	RBTree<I, T, Compare> & operator=( RBTree<I, T, Compare> && tree );

	/************************************************************************/
	/* Iterations                                                           */
	/************************************************************************/
	///@brief iterate ONE time the iterator and return if there is still data
	///@return it in out Iterator to iterate
	///@return If the iterator can return data
	bool iterate( typename RBTree<I, T, Compare>::Iterator * it ) const;

	///@brief Iterate ONE time and set the pointer to the pointer of the data retrieved
	///@param it in out Iterator to iterate
	///@param i out Pointer to a pointer to the index retrieved
	///@param v out Pointer to a pointer to the value retrieved
	///@return True if a data has been retrieved or False if the end has been reached
	bool iterate( typename RBTree<I, T, Compare>::Iterator * it, I ** i, T ** v ) const;

	///@brief Iterate ONE time and set the pointer to the pointer of the data retrieved
	///@param it in out Iterator to iterate
	///@param i out Pointer to a pointer to the index retrieved
	///@param v out Pointer to a pointer to the value retrieved
	///@param testFunctor Functor to check a condition before incrementing the iterator
	///								bool operator()( const T & e );
	///@return True if a data has been retrieved or False if the end has been reached or false is the functor return false
	template<typename TestFunctor>
	bool iterate( typename RBTree<I, T, Compare>::Iterator * it, I ** i, T ** v, TestFunctor & testFunctor ) const;

	///@brief get the Begin Iterator
	///@return Begin Iterator
	typename RBTree<I, T, Compare>::Iterator getBegin() const;
	typename RBTree<I, T, Compare>::Iterator begin() const;

	///@brief get the End Iterator
	///@return End Iterator
	typename RBTree<I, T, Compare>::Iterator getEnd() const;
	typename RBTree<I, T, Compare>::Iterator end() const;

	/************************************************************************/
	/* Access                                                               */
	/************************************************************************/
	///@brief Access from a value using and index
	///@param index Index to be used
	///@param Pointer to the value if founded, if not, return NULL
	const T * operator[]( const I & index ) const;
	T * operator[]( const I & index );

	///@brief Get the Value associated with an iterator
	///@param it Iterator used to retrieve the value (no bound check is done here)
	///@return Value founded
	const T & getValueIt( typename RBTree<I, T, Compare>::Iterator it ) const;
	T & getValueIt( typename RBTree<I, T, Compare>::Iterator it );

	///@brief Get the Index associated with an iterator 
	///@param it Iterator used to retrieve the index (no bound check is done here)
	///@return Index founded
	const I & getIndexIt( typename RBTree<I, T, Compare>::Iterator it ) const;
	I & getIndexIt( typename RBTree<I, T, Compare>::Iterator it );

	///@brief Set the Value associated with an iterator
	///@param it Iterator used to set the value
	void setValueIt( typename RBTree<I, T, Compare>::Iterator it, const T & v );

	///@brief Set the Index associated with an iterator
	///@param it Iterator used to set the index
	void setIndexIt( typename RBTree<I, T, Compare>::Iterator it, const I & v );




	///@brief clear the complete Tree
	void clear();

	///@brief Insert a new [ Index => Value ] into the map
	///@param index Index of the value to insert
	///@param value Value to be inserted
	///@return True of the index didn't exist and has been added. false instead.
	bool insert( const I & index, const T & value );


	///@brief Delete a node from the map
	///@param index Index to search and to be deleted
	///@return Boolean if a key has been deleted
	bool eraseIndex( const I & index );

	///@brief Create an human readable string from this tree
	///@return String
	template<typename C = char>
	BasicString<C> toString() const;

	///@brief Read from a file stream (childs will be read recursively)
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief Write this object as binary into a file stream (childs will be wrote recursively)
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;


protected:
	void _clear();
	void _unload();

	///@brief Create a new node [Index => Value] and insert it into the tree
	///@return Node freshly created (NULL if nothing has been inserted)
	RBNode< MapObject< I, T > > * _insert( const I & index, const T & value );

	///@brief Check the integrity of the tree
	///@param root Pointer of the root
	///@param functor Comparison functor
	static void _checkTree( RBNode< MapObject<I, T> > * root, Compare & functor );
	static void _checkTreeSorted( RBNode< MapObject<I, T> > * root, Compare & functor );

	RBNode< MapObject<I, T> > * rootNode;
	Compare compareFunc;
};



template<typename I, typename T, typename Compare = Math::Logical::Less>
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

	///@brief Conversion to String operator
	///@return String
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





	///@brief Clear the complete map
	void clear();

	///@brief Insert a new [ Index => Value ] into the map
	///@param index Index of the value to insert
	///@param value Value to be inserted
	///@return True of the index didn't exist and has been added. false instead.
	bool insert( const I & index, const T & value );

	///@brief Create an human readable string from this map
	///@return String
	template<typename C = char>
	BasicString<C> toString() const;

	///@brief Read from a file stream (childs will be read recursively)
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );

	///@brief Write this object as binary into a file stream (childs will be wrote recursively)
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( std::fstream * fileStream ) const;

protected:
	void _clear();

};*/





#include "MapObject.hpp"
#include "Map.hpp"
