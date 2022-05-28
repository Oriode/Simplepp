/**
 * @file	MultiMap.h.
 *
 * @brief	Declares the multi map class
 */

#pragma once


#include "Vector.h"
#include "Map.h"


 /**
  * @class	MultiMap
  *
  * @brief	Same as Map but can store multiple items with the same index
  *
  * @tparam	I	   	Generic type parameter.
  * @tparam	T	   	Generic type parameter.
  * @tparam	Compare	Type of the compare.
  */
template<typename I, typename T, typename Compare = Math::Compare::Template>
class MultiMap : public Map< I, Vector <T>, Compare> {
public:
	/** @brief	. */
	using Map< I, Vector <T>, Compare>::Iterator;

	/**
	 * @fn	MultiMap::MultiMap( const Compare & compareFunc = Compare() );
	 *
	 * @brief	Empty Constructor
	 *
	 * @param	compareFunc	(Optional) Functor with operator() overloaded with : Math::Compare::Value operator()( const T & , const T & ) const;
	 * 						For security reasons, the functor should inherite from Math::Compare::Template.
	 */
	MultiMap( const Compare & compareFunc = Compare() );

	/**
	 * @fn	MultiMap::MultiMap( const MultiMap<I, T, Compare> & map );
	 *
	 * @brief	Copy Constructor
	 *
	 * @param	map	Map to copy.
	 */
	MultiMap( const MultiMap<I, T, Compare> & map );

	/**
	 * @fn	MultiMap::MultiMap( MultiMap<I, T, Compare> && map );
	 *
	 * @brief	Move Constructor
	 *
	 * @param [in,out]	map	Map to move from.
	 */
	MultiMap( MultiMap<I, T, Compare> && map );

	/**
	 * @fn	template<typename C = char> operator MultiMap::BasicString<C>() const;
	 *
	 * @brief	Conversion to StringASCII operator
	 *
	 * @returns	The result of the operation.
	 */
	template<typename C = char>
	operator BasicString<C>() const;

	/**
	 * @fn	MultiMap<I, T, Compare> & MultiMap::operator=( const MultiMap<I, T, Compare> & map );
	 *
	 * @brief	Copy operator
	 *
	 * @param	map	Map to copy.
	 *
	 * @returns	reference to THIS.
	 */
	MultiMap<I, T, Compare> & operator=( const MultiMap<I, T, Compare> & map );

	/**
	 * @fn	MultiMap<I, T, Compare> & MultiMap::operator=( MultiMap<I, T, Compare> && map );
	 *
	 * @brief	Move operator
	 *
	 * @param [in,out]	map	Map to move from.
	 *
	 * @returns	reference to THIS.
	 */
	MultiMap<I, T, Compare> & operator=( MultiMap<I, T, Compare> && map );



	/**
	 * @fn	T * MultiMap::insert( const I & index, const T & value );
	 *
	 * @brief	Insert a new [ Index => Value ] into the map, The Map can handle multiple value on the same index
	 *
	 * @param	index	Index of the value to insert.
	 * @param	value	Value to be inserted.
	 *
	 * @returns	Pointer to the value just inserted, NULL if nothing has been inserted.
	 */
	T * insert( const I & index, const T & value );

	/**
	 * @fn	bool MultiMap::eraseFirst( const I & index, const T & value );
	 *
	 * @brief	Delete the first value founded from the map
	 *
	 * @param	index	Index to searchI and to be deleted.
	 * @param	value	Value to searchI and to be deleted.
	 *
	 * @returns	Boolean if a key has been deleted.
	 */
	bool eraseFirst( const I & index, const T & value );

	/**
	 * @fn	bool MultiMap::eraseAll( const I & index, const T & value );
	 *
	 * @brief	Delete all the values founded from the map
	 *
	 * @param	index	Index to searchI and to be deleted.
	 * @param	value	Value to searchI and to be deleted.
	 *
	 * @returns	Boolean if a key has been deleted.
	 */
	bool eraseAll( const I & index, const T & value );

private:
	/**
	 * @fn	T * MultiMap::_insert( const I & index, const T & value );
	 *
	 * @brief	Create a new node [Index => Value] and insert it into the tree
	 *
	 * @param	index	Zero-based index of the.
	 * @param	value	The value.
	 *
	 * @returns	Node freshly created (NULL if nothing has been inserted)
	 */
	T * _insert( const I & index, const T & value );

};

#include "MultiMap.hpp"


