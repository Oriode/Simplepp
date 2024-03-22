///@file NodeValue.h
///@brief Representing an JSON NodeValue.
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


	template<typename S>
	class NodeValueT : public NodeT<S> {
	public:

		enum class ValueType {
			String,
			Int,
			Float,
			Null
		};

		///@brief Empty constructor
		NodeValueT();

		///@brief create node
		///@param value value of the node
		NodeValueT( const S& value );
		NodeValueT( int value );
		NodeValueT( unsigned int value );
		NodeValueT( long long int value );
		NodeValueT( unsigned long long int value );
		NodeValueT( double value );
		NodeValueT( bool value );
		template<typename P>
		NodeValueT( const P* nullPtr );						// nullptr only.

		///@brief Constructor using a name and a value.
		///@param name NodeMap name.
		///@param value NodeMap value.
		NodeValueT( const S& name, const S& value );
		NodeValueT( const S& name, int value );
		NodeValueT( const S& name, unsigned int value );
		NodeValueT( const S& name, long long int value );
		NodeValueT( const S& name, unsigned long long int value );
		NodeValueT( const S& name, double value );
		NodeValueT( const S& name, bool value );
		template<typename P>
		NodeValueT( const S& name, const P* nullPtr );						// nullptr only.

		///@brief Copy Constructor
		///@param node NodeT<S> to be copied
		NodeValueT( const NodeValueT<S>& node );

		///@brief Move Constructor
		///@param node NodeT<S> to be moved
		NodeValueT( NodeValueT<S>&& node );

		///@brief Get the Value of this node (Only appliable if getType() == Value).
		///@return Value of this node
		const S& getValue() const override;

		///@brief Set the value of this node (Will change this node value if getType() == Value, otherwise will try to change this node type to be a value one.)
		///@param value Value to be set
		virtual void setValue( const S& value ) override;
		virtual void setValue( int value ) override;
		virtual void setValue( unsigned int value ) override;
		virtual void setValue( long long int value ) override;
		virtual void setValue( unsigned long long int value ) override;
		virtual void setValue( double value ) override;
		virtual void setValue( bool value ) override;

		template<typename P>
		void setValue( const P* nullPtr );						// nullptr only.

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
	protected:
		S value;
		bool bAddQuotes;
	};

	using NodeValue = NodeValueT<UTF8String>;


}


#include "NodeValue.hpp"