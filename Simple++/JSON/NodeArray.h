///@file NodeArray.h
///@brief Representing an JSON NodeArray.
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

namespace JSON {


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
		NodeArrayT( const S& name, const Vector<NodeT<S>*>& v );

		///@brief Copy Constructor
		///@param node NodeT<S> to be copied
		NodeArrayT( const NodeArrayT<S>& node );

		///@brief Move Constructor
		///@param node NodeT<S> to be moved
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

	using NodeArray = NodeArrayT<UTF8String>;


}

#include "NodeArray.hpp"