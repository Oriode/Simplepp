///@file Json.h
///@brief All the Json includes.
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
#include "../Time/TimePoint.h"

#include "Node.h"
#include "NodeValue.h"
#include "NodeArray.h"
#include "NodeMap.h"


namespace JSON {

	///@brief Read this object using a pointer to a String Iterator.
	///@param buffer Pointer to a String iterator
	///@param endFunc Functor to check the buffer end.
	///@return bool True if success, False otherwise.
	template<typename S = UTF8String, typename C = S::ElemType, typename EndFunc = BasicString<C>::IsEndSentinel>
	NodeT<S>* parseT( const C** buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );
	template<typename S = UTF8String, typename C = S::ElemType, typename EndFunc = BasicString<C>::IsEndSentinel>
	NodeT<S>* parseT( const C* buffer, const EndFunc& endFunc = BasicString<C>::IS_END_SENTINEL );

	///@brief read this object using a type S.
	///@param str String to read from.
	///@return bool True if success, False otherwise.
	template<typename S>
	NodeT<S>* parseT( const S& str );

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, const S& childName, C* outValue, int verbose = 0 );

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, C* v, int verbose = 0 );

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, Table<C>* t, int verbose = 0 );
	template<typename S, typename C, Size N>
	bool fromJSON( const NodeT<S>* node, StaticTable<C, N>* t, int verbose = 0 );
	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, BasicVector<C>* v, int verbose = 0 );
	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, Vector<C>* v, int verbose = 0 );
	template<typename S, typename Ratio>
	bool fromJSON( const NodeT<S>* node, Time::TimePoint<Ratio>* t, int verbose = 0 );

	template<typename S, typename C>
	bool _fromJSON( const NodeT<S>* node, C* v, const Jsonable* );
	template<typename S, typename C>
	bool _fromJSON( const NodeT<S>* node, C* v, ... );

	template<typename S>
	NodeT<S>* toJSON();
	template<typename S, typename C>
	NodeT<S>* toJSON( const C& v );
	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const Table<C>& t );
	template<typename S, typename C, Size N>
	NodeArrayT<S>* toJSON( const StaticTable<C, N>& t );
	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const BasicVector<C>& v );
	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const Vector<C>& v );

	template<typename S, typename C>
	NodeT<S>* _toJSON( const C& v, const Jsonable* );
	template<typename S, typename C>
	NodeT<S>* _toJSON( const C& v, ... );

	///@brief write an object to the file, this function will automatically test if the sent object (by pointer) inherit from BasicIO JSON::Jsonable and then call his own fromJSON method.
	///@param filePath file where to write.
	///@param object pointer to the object we wanna write.
	///@return Boolean if the result is a success or not.
	template<typename S = UTF8String, typename C>
	static bool write( const OS::Path& filePath, const C* object, int verbose = 0 );

	///@brief read from a file to an object, this function will automatically test if the sent object (by pointer) inherit from JSON::Jsonable himself and then call his own toJSON method.
	///@param filePath file where to read.
	///@param object pointer to the object we wanna read.
	///@return Boolean if the result is a success or not.
	template<typename S = UTF8String, typename C>
	bool read( const OS::Path& filePath, C* object, int verbose = 0 );

}


#include "Json.hpp"