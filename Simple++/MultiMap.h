#pragma once


#include "Vector.h"
#include "Map.h"


///@brief Same as Map but can store multiple items with the same index
template<typename I, typename T, typename Compare = Math::Compare::Template>
class MultiMap : public Map< I, Vector <T>, Compare> {
public:
	using Map< I, Vector <T>, Compare>::Iterator;

	///@brief Empty Constructor
	///@param compareFunc Functor with operator() overloaded with :
	///            Math::Compare::Value operator()( const T & , const T & ) const;
	///            For security reasons, the functor should inherite from Math::Compare::Template
	MultiMap( const Compare & compareFunc = Compare() );

	///@brief Copy Constructor
	///@param map Map to copy
	MultiMap( const MultiMap<I, T, Compare> & map );

	///@brief Move Constructor
	///@param map Map to move from
	MultiMap( MultiMap<I, T, Compare> && map );

	///@brief Conversion to StringASCII operator
	template<typename C = char>
	operator BasicString<C>() const;

	///@brief Copy operator
	///@param map Map to copy
	///@return reference to THIS
	MultiMap<I, T, Compare> & operator=( const MultiMap<I, T, Compare> & map );

	///@brief Move operator
	///@param map Map to move from
	///@return reference to THIS
	MultiMap<I, T, Compare> & operator=( MultiMap<I, T, Compare> && map );



	///@brief Insert a new [ Index => Value ] into the map, The Map can handle multiple value on the same index
	///@param index Index of the value to insert
	///@param value Value to be inserted
	///@return Pointer to the value just inserted, NULL if nothing has been inserted
	T * insert( const I & index, const T & value );

	///@brief Delete the first value founded from the map
	///@param index Index to search and to be deleted
	///@param value Value to search and to be deleted
	///@return Boolean if a key has been deleted
	bool eraseFirst( const I & index, const T & value );

	///@brief Delete all the values founded from the map
	///@param index Index to search and to be deleted
	///@param value Value to search and to be deleted
	///@return Boolean if a key has been deleted
	bool eraseAll( const I & index, const T & value );

private:
	///@brief Create a new node [Index => Value] and insert it into the tree
	///@return Node freshly created (NULL if nothing has been inserted)
	T * _insert( const I & index, const T & value );
	
};

#include "MultiMap.hpp"


