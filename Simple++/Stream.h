#pragma once


#include "Vector.h"


///@brief Representing a stream of T data (usefull for writing files or sending/receiving network data)
///@template T Type of data.
template<typename T>
class StreamT : public Vector<T> {
public:

	///@brief Empty constructor.
	StreamT();

	///@brief Constructor initializing a StreamT of a specific size and max size.
	///@param size Size of the stream.
	///@param maxSize Max size of the stream.
	StreamT( const typename Vector<T>::Size size, const typename Vector<T> maxSize );

	///@brief Constructor initializing a StreamT of a specific max size.
	///@param maxSize Max size of the stream.
	StreamT( const typename Vector<T>::Size maxSize );

	///@brief Copy constructor.
	///@param stream StreamT to be copied.
	StreamT( const StreamT & stream );

	///@brief Copy constructor.
	///@template C type of the StreamT to be copied.
	///@param stream StreamT to be copied.
	template<typename C>
	StreamT( const StreamT<C> & stream );

	///@brief Move constructor.
	///@param stream StreamT to be moved from.
	StreamT( StreamT && stream );

	///@brief Constructor using a static array.
	///@template C Array element type.
	///@template N Array size.
	///@param data Array to be copied.
	template<typename C, size_t N>
	StreamT( const C( &data )[ N ] );

	///@brief Constructor using an array and it's size.
	///@param data Array to be copied.
	///@param size Array size.
	StreamT( const T * data, const typename Vector<T>::Size size );

	///@brief Constructor using an array and it's size.
	///@template C Array element type.
	///@param data Array to be copied.
	///@param size Array size.
	template<typename C>
	StreamT( const C * data, const typename Vector<T>::Size size );

	///@brief Constructor using an array, it's size, and a maxSize for the StreamT to be allocated.
	///@param data Array to be copied.
	///@param size Array size.
	///@param maxSize StreamT max size.
	StreamT( const T * data, const typename Vector<T>::Size size, const typename Vector<T>::Size maxSize );

	///@brief Constructor for an Iterator Begin and an Iterator End. Will compute the size between the two iterators, allocate and copy the data into the StreamT.
	///@template C Element type to be copied.
	///@param beginIt Iterator begin.
	///@param endIt Iterator end.
	template<typename C>
	StreamT( RandomAccessIterator<C> beginIt, typename RandomAccessIterator<C> endIt );

	///@brief Add a new element to the stream ad the current position.
	///@param data New element to be added.
	///@return Reference to this.
	StreamT & operator<<( const T & data );

	///@brief Add an element of an another type to the StreamT at the current position. The element will be added in binary.
	///@template C Element type to be added.
	///@param data New element to be added.
	///@return Reference to this.
	template<typename C>
	StreamT & operator<<( const C & data );

	///@brief Append a new element to the stream.
	///@param data New element to be added.
	void push( const T & data );

	///@brief Append an element of an another type to the StreamT. The element will be added in binary.
	///@template C Element type to be added.
	///@param data New element to be added.
	template<typename C>
	void push( const C & data );

	///@brief Concat another StreamT into this one.
	///@param stream StreamT to be added.
	void concat( const StreamT<T> & stream );

	///@brief Concat another StreamT of another type to this one. (Multiple elements may be inserted if the element size is different.)
	///@template C Other StreamT type.
	///@param stream StreamT to be added.
	template<typename C>
	void concat( const StreamT<C> & stream );

	///@brief Get the current position as an Index.
	///@return Position index.
	typename Vector<T>::Size getPosition() const;

	///@brief Get the current position as an Iterator.
	///@return Position iterator.
	const typename Vector<T>::Iterator getPositionIt() const;
	typename Vector<T>::Iterator getPositionIt();

	///@brief Set the current position as an Index.
	///@param pos New position index.
	void setPosition( typename Vector<T>::Size pos );

	///@brief Set the current position as an Iterator.
	///@param pos New position iterator.
	void setPosition( typename Vector<T>::Iterator pos );


protected:
	/** Current position pointer. */
	typename Vector<T>::Size position;



};

using Stream = StreamT<unsigned char>;

#include "Stream.hpp"