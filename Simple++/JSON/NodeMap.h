///@file NodeMap.h
///@brief Representing an JSON NodeMap.
///@author Clément Gerber.
///@date (DMY) 22-03-2024


#pragma once

#include "../Log.h"
#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../MultiMap.h"
#include "../Math/BasicMath.h"
#include "../OS/Path.h"
#include "../StaticTable.h"

#include "Node.h"

namespace JSON {

	///@brief Represent a node in the JSON Tree, Only 3 Types available ( Map, Array and Value )
	template<typename S>
	class NodeMapT : public NodeT<S> {
	public:
		using NodeT<S>::Type;

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
		///@return NodeT<S> pointer with the searched name or NULL if none.
		virtual NodeT<S>* getElementByName( const S& name ) const override;

		///@brief Get a vector filled by pointer to all the node corresponding to the name searched in this sub tree.
		///@param name Name to look for
		///@return Vector of NodeMapT<S>'s pointers with the searched name
		virtual Vector< NodeT<S>* > getElementsByName( const S& name ) const override;

		///@brief Get the number of children of this node
		///@return Number of children of this node
		virtual Size getNbChildren() const override;

		///@brief Get a child from his index
		///@param i Index of the child to retrieve (betwwen [0 ; getNbChildren() - 1])
		///@return Child
		virtual const NodeT<S>* getChild( Size i ) const override;
		virtual NodeT<S>* getChild( Size i ) override;

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		virtual void addChild( NodeT<S>* child ) override;
		virtual void addChild( const S& name, NodeT<S>* child );

		///@brief Get the complete children vector of this node.
		///@return Children Vector.
		virtual const Vector<NodeT<S>*>& getChildren() const override;

		///@brief Get Vector of children from a name
		///@param name Name to look for
		///@return pointer to the Vector of children if one has been founded, NULL instead
		virtual const Vector<NodeT<S>*>& getChildren( const S& name ) const override;
		// Vector<NodeT<S> *> getChildren( const S & name ) override;

		///@brief Get the first child founded from a name
		///@param name Name to look for
		///@return pointer to the child if one has been founded, NULL instead
		virtual const NodeT<S>* getChild( const S& name ) const override;
		virtual NodeT<S>* getChild( const S& name ) override;

		///@brief Delete a child from this node (And delete it)
		///@param child Child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( NodeT<S>* child ) override;

		///@brief Delete a child from this node (And delete it)
		///@param i Index of the child to be deleted (The child itself is deleted during this operation, NEVER call delete directly from a node)
		///@return True if something has been deleted, False otherwise
		virtual bool deleteChild( Size i ) override;

		///@brief Remove a child from this node (And do NOT delete it)
		///@param child Child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual NodeT<S>* removeChild( NodeT<S>* child ) override;

		///@brief Remove a child from this node (And do NOT delete it)
		///@param i Index of the child to be removed (The child itself is not deleted and can be set as a child to another node)
		///@return Pointer to the child removed from his parent (or NULL if nothing has been founded)
		virtual NodeT<S>* removeChild( Size i ) override;

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

		bool _setChildName( NodeT<S>* child, const S& oldName, const S& newName );
	protected:
		void _clear();
		void _unload();
		void _getElementsByName( Vector < NodeT<S>* >* nodeVector, const S& name ) const;
		NodeT<S>* _getElementByName( const S& name ) const;

		MultiMap< S, NodeT<S>* > childrenMap;
		Vector< NodeT<S>* > childrenVector;
	};

	using NodeMap = NodeMapT<UTF8String>;

}

#include "NodeMap.hpp"