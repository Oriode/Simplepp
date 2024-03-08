#pragma once

#include <algorithm>
#include "Vector.h"
#include "String.h"

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
	template<typename Stream>__NL__bool read( Stream * stream, int verbose = 0 );

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( IO::SimpleFileStream * fileStream ) const;
};




template<typename I, typename T>
class Map : protected Vector<MapObject<I, T> *> {
public:

	Map( void );
	Map( const Map & m );

	template<typename I2, typename T2>
	Map( const Map<I2, T2> & m );

	Map( Map && m );
	~Map( void );

	template<typename C = char>
	operator BasicString<C>() const;

	using Vector<MapObject<I, T> *>::reserve;
	using Vector<MapObject<I, T> *>::allocate;
	using Vector<MapObject<I, T> *>::resize;

	template<typename I2, typename T2>
	Map<I, T> & operator=( const Map<I2, T2> & map );
	Map<I, T> & operator=( Map && m );

	///@brief Operator [] return the value for a specified index (can be NULL if the value is not found)
	///@param index Index
	///@return pointer to the value we are looking for (NULL if not found)
	T * operator[]( const I & index );


	///@brief Operator [] return the value for a specified index (can be NULL if the value is not found)
	///@param index Index
	///@return pointer to the value we are looking for (NULL if not found)
	const T * operator[]( const I & index ) const;


	//T & operator[](typename Map<I,T>::Iterator i);				//DISABLE FOR AMBIGOUS
	MapObject<I, T> & operator()( typename Size i );
	const MapObject<I, T> & operator()( typename Size i ) const;


	/************************************************************************/
	/* GET INDEX                                                            */
	/************************************************************************/
	I & getIndexi( Size i );
	const I & getIndexi( Size i ) const;
	I & getIndexit( typename Map<I,T>::Iterator i );
	const I & getIndexit( typename Map<I,T>::Iterator i ) const;

	/************************************************************************/
	/* SET INDEX                                                            */
	/************************************************************************/
	void setIndexi( Size i, const I & index );
	void setIndexit( typename Map<I,T>::Iterator i, const T & index );

	/************************************************************************/
	/* SET VALUE                                                            */
	/************************************************************************/
	void setValueI( Size i, const T & value );
	void setValueIt( typename Map<I,T>::Iterator i, const T & value );


	/************************************************************************/
	/* GET VALUE                                                            */
	/************************************************************************/
	T & getValueIt( typename Map<I,T>::Iterator i );
	const T & getValueIt( typename Map<I,T>::Iterator i ) const;

	T & getValueI( Size i );
	const T & getValueI( Size i ) const;
	T * getValue( const I & index );


	//retrieve the last data in the map
	using Vector<MapObject<I, T> *>::getLast;

	const T & getLastValue() const;
	T & getLastValue();

	const T & getLastIndex() const;
	T & getLastIndex();

	void set( Size i, const I & index, const T & data );
	void insert( const I & index, const T & data );

	///@brief Insert a value at the specified i
	///@param i index where to insert the [Index => Value]
	///@param index Index of the key to insert
	///@param data Data of the key to insert
	void inserti( Size i, const I & index, const T & data );

	///@brief Sort the map with the specified functor
	///@param func Functor overloaded with
	///					template<typename I> bool operator()( const I & i1, const I & i2 );
	template<typename Compare = Math::Logical::Less>
	void sort( Compare & func = Compare() );

	//return the size of this vector (push will increment it)
	using Vector<MapObject<I, T> *>::getSize;
	using Vector<MapObject<I, T> *>::size;

	///@brief Set size = 0
	void clear();

	///@brief Set size = 0 AND free memory
	void reset();

	//test if a specified value exists in the table
	using Vector<MapObject<I, T> *>::exists;

	bool existsIndex( const I & index ) const;

	using Vector<MapObject<I, T> *>::begin;
	using Vector<MapObject<I, T> *>::end;
	using Vector<MapObject<I, T> *>::getBegin;
	using Vector<MapObject<I, T> *>::getEnd;
	using Vector<MapObject<I, T> *>::iterate;


	void eraseValueFirst( const T & data );
	void eraseValueAll( const T & data );

	void eraseIndexFirst( const I & index );
	void eraseIndexAll( const I & index );

	Size searchIndex( const I & index ) const;

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>__NL__bool read( Stream * stream, int verbose = 0 );

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write( IO::SimpleFileStream * fileStream ) const;

protected:
	enum ctor { null };
	Map( ctor );

	void _clear();
	void _unload();
	void _erasei( Size index );
	void _eraseit( typename Vector<T>::Iterator it );
};




template<typename I, typename T>
std::ostream & operator <<( std::ostream & stream, const Map<I, T> & map );


#include "Map.hpp"

