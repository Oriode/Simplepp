#pragma once


#include "Vector.h"
#include "String.h"


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
	StreamT( const typename RandomAccessIterator<C> beginIt, const typename RandomAccessIterator<C> endIt );

	///@brief Consructor using a String.
	///@template C Type of a String element.
	///@param str String to be converted.
	template<typename C>
	StreamT( const BasicString<C> & str );



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

	/************************************************************************/
	/* POSITIONING                                                          */
	/************************************************************************/

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

	/************************************************************************/
	/* READ / WRITE                                                         */
	/************************************************************************/

	///@brief Add a new element to the stream ad the current position.
	///@param data New element to be added.
	///@return Reference to this.
	bool write( const T & data );

	///@brief Add an element of an another type to the StreamT at the current position. The element will be added in binary.
	///@template C Element type to be added.
	///@param data New element to be added.
	///@return Reference to this.
	template<typename C>
	bool write( const C & data );

	///@brief Add multiple new elements to the stream ad the current position.
	///@template N Number of data to be written.
	///@param data New elements to be added.
	///@return Reference to this.
	template<size_t N>
	bool write( const T( &data )[ N ] );

	///@brief Add multiple elements of an another type to the StreamT at the current position. The element will be added in binary.
	///@template C Element type to be added.
	///@template N Number of data to be written.
	///@param data New elements to be added.
	///@return Reference to this.
	template<typename C, size_t N>
	bool write( const C( &data )[ N ] );

	///@brief Write data into this Stream at the current position.
	///@param data data to be wrtitten into the Stream.
	///@param size number of data to be written.
	///@return True if success, False otherwise.
	bool write( const T * data, typename Vector<T>::Size size );

	///@brief Write data of an another type into this Stream at the current position.
	///@template C Element type to be added.
	///@param data data to be wrtitten into the Stream.
	///@param size number of data to be written.
	///@return True if success, False otherwise.
	template<typename C>
	bool write( const C * data, typename Vector<T>::Size size );

	///@brief read data from the Stream at the current position.
	///@param data Buffer to be filled with the read data.
	///@param size Number of data to be read.
	///@return True if success, False otherwise.
	bool read( T * data, typename Vector<T>::Size size );

	/************************************************************************/
	/* OPERATOR STREAM                                                      */
	/************************************************************************/

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

	///@brief Add multiple new elements to the stream ad the current position.
	///@template N Number of data to be written.
	///@param data New elements to be added.
	///@return Reference to this.
	template<size_t N>
	StreamT & operator<<( const T( &data )[ N ] );

	///@brief Add multiple elements of an another type to the StreamT at the current position. The element will be added in binary.
	///@template C Element type to be added.
	///@template N Number of data to be written.
	///@param data New elements to be added.
	///@return Reference to this.
	template<typename C, size_t N>
	StreamT & operator<<( const C( &data )[ N ] );

	/************************************************************************/
	/* CONVERSION                                                           */
	/************************************************************************/

	///@brief Convert this Stream into a String without any conversion.
	///@template Output String element type.
	///@return String.
	template<typename C = char>
	BasicString<C> toStringRaw() const;

	///@brief Convert an element to a String using it's hexadecimal representation.
	///@template Output String element type.
	///@return String.
	template<typename C = char>
	BasicString<C> toStringHexa() const;



protected:
	/** Current position. */
	typename Vector<T>::Size position;



};

using Stream = StreamT<unsigned char>;

#include "Stream.hpp"