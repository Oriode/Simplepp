/**
 * @file	String.h.
 * @brief		Declares the string class
 */

#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include "SimpleLog.h"
#include "Stream.h"
#include "Math/BasicComparable.h"

#if defined WIN32 && defined ENABLE_WIN32
#include <Windows.h>
#endif

 /**
  * @brief		.
  * @tparam	T	buffer type
  */
template<typename T>
class BasicString : public Vector<T>, public Math::Compare::BasicComparable {
public:

	///@brief Functor to test if the pointer is at the end.
	class IsEndSentinel {
	public:
		bool operator()( const T * it ) const;
	};

	///@brief Functor to test if the pointer is at the end.
	class IsEndIterator {
	public:
		IsEndIterator( const T * endIt );
		bool operator()( const T * it ) const;
	private:
		const T * endIt;
	};


	using Vector<T>::Size;
	using Vector<T>::ElemType;

	/** @brief	Default constructor */
	BasicString();




	/**
	 * @brief		Constructor
	 * @tparam	C	Type of the c.
	 * @param	str	The string.
	 */
	template<typename C>
	BasicString( C * const & str );

	/**
	 * @brief		Constructor
	 * @tparam	C	Type of the c.
	 * @param	str 	The string.
	 * @param	size	The size.
	 */
	template<typename C>
	BasicString( const C * str, typename BasicString<T>::Size size );
	/**
	 * @brief		Constructor
	 * @tparam	C	Type of the c.
	 * @param	beginIt	The begin iterator.
	 * @param	endIt  	The end iterator.
	 */
	template<typename C>
	BasicString( RandomAccessIterator<C> beginIt, RandomAccessIterator<C> endIt );


	/**
	 * @brief		Constructor
	 * @tparam	C	Type of the c.
	 * @param	str	The string.
	 */
	template<typename C>
	BasicString( const BasicString<C> & str );
	/**
	 * @brief		Constructor
	 * @param	str	The string.
	 */
	BasicString( const BasicString<T> & str );
	/**
	 * @brief		Constructor
	 * @param [in,out]	str	The string.
	 */
	BasicString( BasicString<T> && str );

	///@brief Constructor using a Stream.
	///@template C Stream element type.
	///@param stream Stream to be copied.
	template<typename C>
	BasicString( const StreamT<C> & stream );


	/**
	 * @brief		Constructor
	 * @tparam	C	String type.
	 * @param	str	Constant string.
	 */
	template<typename C, size_t N>
	BasicString( const C (& str)[N] );

	/**
	 * @brief		Constructor
	 * @param	ui	Unsigned int.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const unsigned char & ui, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param	ui	Unsigned short
	 * @param base	Base used for the conversion.
	 */
	BasicString( const unsigned short & ui, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param	i	Zero-based index of the.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const int & i, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param	ui	Unsigned int
	 * @param base	Base used for the conversion.
	 */
	BasicString( const unsigned int & ui, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param	l	A long to process.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const long & l, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param	ul	The ul.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const unsigned long & ul, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param	ll	The ll.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const long long & ll, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param		ull	The ull.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const unsigned long long & ull, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param		d	A double to process.
	 * @param		precision Precision to be used.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const double & d, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param		f	A float to process.
	 * @param		precision Precision to be used.
	 * @param base	Base used for the conversion.
	 */
	BasicString( const float & f, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Constructor
	 * @param		b	True to b.
	 */
	BasicString( const bool & b );

	/**
	 * @brief		Constructor
	 * @param		c	A T to process.
	 */
	BasicString( const T & c );

	/**
	 * @brief		Constructor from a comparable value.
	 * @param		compareValue	Value of a compare.
	 */
	BasicString(const typename Math::Compare::Value & compareValue);



	/** @brief	Destructor */
	~BasicString();

	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/**
	 * @brief		Assignment operator
	 * @param	str	The string.
	 * @returns	A shallow copy of this object.
	 */
	template<typename C>
	BasicString & operator=( C * const & str );

	/**
	 * @brief		Assignment operator
	 * @param	str	The string.
	 * @returns	A shallow copy of this object.
	 */
	template<typename C>
	BasicString & operator=( const BasicString<C> & str );
	/**
	 * @brief		Assignment operator
	 * @param	str	The string.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const BasicString<T> & str );
	/**
	 * @brief		Move assignment operator
	 * @param [in,out]	str	The string.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( BasicString<T> && str );


	/**
	 * @brief		Assignment operator
	 * @param	str	The string.
	 * @returns	A shallow copy of this object.
	 */
	template<typename C, size_t N>
	BasicString & operator=( const C (& str)[N] );

	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const unsigned char & i );
	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const unsigned short & i );

	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const int & i );
	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const unsigned int & i );

	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const long & i );
	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const unsigned long & i );

	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const long long & i );
	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const unsigned long long & i );

	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const double & i );
	/**
	 * @brief		Assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const float & i );

	/**
	 * @brief		Assignment operator
	 * @param	b	True to b.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const bool & b );

	/**
	 * @brief		Assignment operator
	 * @param	c	A T to process.
	 * @returns	A shallow copy of this object.
	 */
	BasicString & operator=( const T & c );



	/************************************************************************/
	/* OPERATOR STREAM                                                      */
	/************************************************************************/

	template<typename C>
	BasicString & operator<<( C * const & str );


	template<typename C>
	BasicString & operator<<( const BasicString<C> & str );


	template<typename C, size_t N>
	BasicString & operator<<( const C (& str)[N] );


	BasicString & operator<<( const unsigned char & uc );
	BasicString & operator<<( const unsigned short & us );
	BasicString & operator<<( const int & i );
	BasicString & operator<<( const unsigned int & ui );
	BasicString & operator<<( const long & l );
	BasicString & operator<<( const unsigned long & ul );
	BasicString & operator<<( const long long & ll );
	BasicString & operator<<( const unsigned long long & ull );
	BasicString & operator<<( const double & d );
	BasicString & operator<<( const float & f );
	BasicString & operator<<( const bool & b );
	BasicString & operator<<( const wchar_t & c );
	BasicString & operator<<( const char & c );

	template<typename C>
	BasicString<T> & operator<<( const Vector<C> & v );

	/************************************************************************/
	/* OPERATOR +=	                                                      */
	/**
	 * @brief		Addition assignment operator
	 * @param	str	The string.
	 * @returns	The result of the operation.
	 */
	template<typename C>
	BasicString & operator+=( C * const & str );

	/**
	 * @brief		Addition assignment operator
	 * @param	str	The string.
	 * @returns	The result of the operation.
	 */
	template<typename C>
	BasicString & operator+=( const BasicString<C> & str );

	/**
	 * @brief		Addition assignment operator
	 * @param	str	The string.
	 * @returns	The result of the operation.
	 */
	template<typename C, size_t N>
	BasicString & operator+=( const C (& str)[N] );

	/**
	 * @brief		Addition assignment operator
	 * @param	uc	The uc.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const unsigned char & uc );
	/**
	 * @brief		Addition assignment operator
	 * @param	us	The us.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const unsigned short & us );

	/**
	 * @brief		Addition assignment operator
	 * @param	i	Zero-based index of the.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const int & i );
	/**
	 * @brief		Addition assignment operator
	 * @param	ui	The user interface.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const unsigned int & ui );

	/**
	 * @brief		Addition assignment operator
	 * @param	l	A long to process.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const long & l );
	/**
	 * @brief		Addition assignment operator
	 * @param	ul	The ul.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const unsigned long & ul );

	/**
	 * @brief		Addition assignment operator
	 * @param	ll	The ll.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const long long & ll );
	/**
	 * @brief		Addition assignment operator
	 * @param	ull	The ull.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const unsigned long long & ull );

	/**
	 * @brief		Addition assignment operator
	 * @param	d	A double to process.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const double & d );
	/**
	 * @brief		Addition assignment operator
	 * @param	f	A float to process.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const float & f );

	/**
	 * @brief		Addition assignment operator
	 * @param	b	True to b.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const bool & b );

	/**
	 * @brief		Addition assignment operator
	 * @param	c	A C to process.
	 * @returns	The result of the operation.
	 */
	template<typename C>
	BasicString & operator+=( const C & c );
	/**
	 * @brief		Addition assignment operator
	 * @param	c	A char to process.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const char & c );
	/**
	 * @brief		Addition assignment operator
	 * @param	c	A wchar_t to process.
	 * @returns	The result of the operation.
	 */
	BasicString & operator+=( const wchar_t & c );




	/************************************************************************/
	/* OPERATOR CONCAT                                                      */
	/**
	 * @brief		Concatenates the given string
	 * @param	str	The string.
	 * @returns	A reference to a BasicString.
	 */

	BasicString & concat( const BasicString<T> & str );
	/**
	 * @brief		Concatenates the given string
	 * @tparam	C	Type of the c.
	 * @param	str	The string.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C>
	BasicString & concat( const BasicString<C> & str );

	/**
	 * @brief		Concats
	 * @tparam	C	Type of the c.
	 * @param	buffer	  	The buffer.
	 * @param	bufferSize	Size of the buffer.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C>
	BasicString & concat( const C * buffer, const typename BasicString<C>::Size & bufferSize );

	/**
	 * @brief		Concatenates the given buffer
	 * @tparam	C	Type of the c.
	 * @param	buffer	The buffer.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C>
	BasicString & concat( C * const & buffer );

	/**
	 * @brief		Concatenates the given string
	 * @tparam	C	Type of the c.
	 * @param	str	The string.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C, size_t N>
	BasicString & concat( const C (& str)[N] );

	/**
	 * @brief		Concatenates the given b
	 * @param	b	True to b.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const bool & b );


	/**
	 * @brief		Concatenates the given c
	 * @param	c	A char to process.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const char & c );
	/**
	 * @brief		Concatenates the given c
	 * @param	c	A wchar_t to process.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const wchar_t & c );

	/**
	 * @brief		Concatenates the given uc
	 * @tparam	Base	Type of the base.
	 * @param	uc	The uc.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const unsigned char & uc );

	/**
	 * @brief		Concatenates the given us
	 * @tparam	Base	Type of the base.
	 * @param	us	The us.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const unsigned short & us );

	/**
	 * @brief		Concatenates the given i
	 * @tparam	Base	Type of the base.
	 * @param	i	Zero-based index of the.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const int & i );

	/**
	 * @brief		Concatenates the given user interface
	 * @tparam	Base	Type of the base.
	 * @param	ui	The user interface.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const unsigned int & ui );

	/**
	 * @brief		Concatenates the given l
	 * @tparam	Base	Type of the base.
	 * @param	l	A long to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const long & l );

	/**
	 * @brief		Concatenates the given ul
	 * @tparam	Base	Type of the base.
	 * @param	ul	The ul.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const unsigned long & ul );

	/**
	 * @brief		Concatenates the given ll
	 * @tparam	Base	Type of the base.
	 * @param	ll	The ll.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const long long & ll );

	/**
	 * @brief		Concatenates the given ull
	 * @tparam	Base	Type of the base.
	 * @param	ull	The ull.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & concat( const unsigned long long & ull );

	/**
	 * @brief		Concatenates the given d
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	d	A double to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// BasicString & concat( const double & d );

	/**
	 * @brief		Concatenates the given f
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	f	A float to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Precision = 5, unsigned int Base = 10>
	// BasicString & concat( const float & f );


	/**
	 * @brief		Concats
	 * @param	uc  	The uc.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const unsigned char & uc, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	us  	The us.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const unsigned short & us, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	i   	Zero-based index of the.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const int & i, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	ui  	The user interface.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const unsigned int & ui, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	l   	A long to process.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const long & l, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	ul  	The ul.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const unsigned long & ul, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	ll  	The ll.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const long long & ll, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	ull 	The ull.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const unsigned long long & ull, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	d		 	A double to process.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const double & d, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Concats
	 * @param	f		 	A float to process.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & concat( const float & f, unsigned int precision = 5, unsigned int base = 10 );


	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	uc			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const unsigned char & uc, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	us			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const unsigned short & us, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	i			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const int & i, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	ui			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const unsigned int & ui, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	l			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const long & l, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	ul			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const unsigned long & ul, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	ll			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const long long & ll, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	ull			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	BasicString & concatFill( const unsigned long long & ull, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	d			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param	precision	(Optional) The precision.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	// BasicString & concatFill( const double & d, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief	Concatenate the number and fill the first characters to have at least the specified number.
	 * @param 	f			Number.
	 * @param 	fillNb  	Characters number to be concatenated.
	 * @param 	fillChar	(Optional) The fill character.
	 * @param	precision	(Optional) The precision.
	 * @param 	base		(Optional) The base.
	 * @returns	A reference to this.
	 */
	// BasicString & concatFill( const float & f, const typename BasicString<T>::Size & fillNb, const T & fillChar = T( ' ' ), unsigned int precision = 5, unsigned int base = 10 );



	/************************************************************************/
	/* toCString()                                                          */
	/**
	 * @brief		Converts this object to a c string
	 * @tparam	C	Type of the c.
	 * @param 		  	c	  	A C to process.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	template<typename C>
	static typename BasicString<T>::Size toCString( const C & c, T * buffer );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	c	  	A char to process.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( const char & c, T * buffer );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	c	  	A wchar_t to process.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( const wchar_t & c, T * buffer );


	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( unsigned char number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( unsigned short number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( unsigned int  number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( int number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( unsigned long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( long long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( unsigned long long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( double number, T * buffer );

	/**
	 * @brief		Converts this object to a c string
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Precision = 5, unsigned int Base = 10>
	// static typename BasicString<T>::Size toCString( float number, T * buffer );


	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.s
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( unsigned char number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( unsigned short number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( unsigned int  number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( int number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( unsigned long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( long long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( unsigned long long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( long number, T * buffer, unsigned int base = 10 );

	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number   	Value to converted to a String.
	 * @param [in,out]	buffer   	If non-null, the buffer.
	 * @param 		  	precision	The precision.
	 * @param 		  	base	 	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( double number, T * buffer, unsigned int precision = 5, unsigned int base = 10 );

	/**
	 * @brief		Converts this object to a c string
	 * @param 		  	number   	Value to converted to a String.
	 * @param [in,out]	buffer   	If non-null, the buffer.
	 * @param 		  	precision	The precision.
	 * @param 		  	base	 	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( float number, T * buffer, unsigned int precision = 5, unsigned int base = 10 );

	/**
	 * @brief				Write in the buffer a value representing a bool
	 * @param 		  	b	  	Value to converted to a String.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString( bool b, T * buffer );

	/**
	 * @brief			Write in the buffer a value representing a Math::Compare::Value
	 * @param 		  	compareValue	  	Value to converted to a String.
	 * @param [in,out]	buffer				Buffer where to write
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCString(const typename Math::Compare::Value& compareValue, T* buffer);


	/************************************************************************/
	/* ToCString() without adding sentinel                                  */
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	C	Type of the c.
	 * @param 		  	c	  	A C to process.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */

	template<typename C>
	static typename BasicString<T>::Size toCStringWOS( const C & c, T * buffer );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	c	  	A char to process.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( const char & c, T * buffer );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	c	  	A wchar_t to process.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( const wchar_t & c, T * buffer );


	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( unsigned char number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( unsigned short number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( unsigned int  number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( int number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( unsigned long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( long long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( unsigned long long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( long number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( double number, T * buffer );

	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	// template<unsigned int Precision = 5, unsigned int Base = 10>
	// static typename BasicString<T>::Size toCStringWOS( float number, T * buffer );


	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( unsigned char number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( unsigned short number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( unsigned int  number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( int number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( unsigned long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( long long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( unsigned long long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( long number, T * buffer, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number   	Number of.
	 * @param [in,out]	buffer   	If non-null, the buffer.
	 * @param 		  	precision	The precision.
	 * @param 		  	base	 	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( double number, T * buffer, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	number   	Number of.
	 * @param [in,out]	buffer   	If non-null, the buffer.
	 * @param 		  	precision	The precision.
	 * @param 		  	base	 	The base.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( float number, T * buffer, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Converts this object to a c string whithout \0
	 * @param 		  	b	  	True to b.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS( bool b, T * buffer );

	/**
	 * @brief			Write in the buffer a value representing a Math::Compare::Value without \0
	 * @param 		  	compareValue	  	Value to converted to a String.
	 * @param [in,out]	buffer				Buffer where to write
	 * @returns			Number of characters written.
	 */
	static typename BasicString<T>::Size toCStringWOS(const typename Math::Compare::Value& compareValue, T* buffer);

	/************************************************************************/
	/* From StringASCII to number                                                */
	/**
	 * @brief		Converts this object to a character
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a char.
	 */
	// template<unsigned int Base = 10>
	// char toChar() const;

	/**
	 * @brief		Converts this object to an int
	 * @tparam	Base	Type of the base.
	 * @returns	This object as an int.
	 */
	// template<unsigned int Base = 10>
	// int toInt() const;

	/**
	 * @brief		Converts this object to a short
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a short.
	 */
	// template<unsigned int Base = 10>
	// short toShort() const;

	/**
	 * @brief		Converts this object to a long
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a long.
	 */
	// template<unsigned int Base = 10>
	// long toLong() const;

	/**
	 * @brief		Converts this object to a long
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a long.
	 */
	// template<unsigned int Base = 10>
	// long long toLongLong() const;

	/**
	 * @brief		Converts this object to an u character
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a char.
	 */
	// template<unsigned int Base = 10>
	// unsigned char toUChar() const;

	/**
	 * @brief		Converts this object to an u int
	 * @tparam	Base	Type of the base.
	 * @returns	This object as an int.
	 */
	// template<unsigned int Base = 10>
	// unsigned int toUInt() const;

	/**
	 * @brief		Converts this object to an u short
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a short.
	 */
	// template<unsigned int Base = 10>
	// unsigned short toUShort() const;

	/**
	 * @brief		Converts this object to an u long
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a long.
	 */
	// template<unsigned int Base = 10>
	// unsigned long toULong() const;

	/**
	 * @brief		Converts this object to an u long
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a long.
	 */
	// template<unsigned int Base = 10>
	// unsigned long long toULongLong() const;

	/**
	 * @brief		Converts this object to a float
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a float.
	 */
	// template<unsigned int Base = 10>
	// float toFloat() const;

	/**
	 * @brief		Converts this object to a double
	 * @tparam	Base	Type of the base.
	 * @returns	This object as a double.
	 */
	// template<unsigned int Base = 10>
	// double toDouble() const;


	/**
	 * @brief		Converts a base to a character
	 * @param	base	The base.
	 * @returns	Base as a char.
	 */
	char toChar( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to an int
	 * @param	base	The base.
	 * @returns	Base as an int.
	 */
	int toInt( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to a short
	 * @param	base	The base.
	 * @returns	Base as a short.
	 */
	short toShort( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to a long
	 * @param	base	The base.
	 * @returns	Base as a long.
	 */
	long toLong( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to a long
	 * @param	base	The base.
	 * @returns	Base as a long.
	 */
	long long toLongLong( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to an u character
	 * @param	base	The base.
	 * @returns	Base as a char.
	 */
	unsigned char toUChar( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to an u int
	 * @param	base	The base.
	 * @returns	Base as an int.
	 */
	unsigned int toUInt( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to an u short
	 * @param	base	The base.
	 * @returns	Base as a short.
	 */
	unsigned short toUShort( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to an u long
	 * @param	base	The base.
	 * @returns	Base as a long.
	 */
	unsigned long toULong( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to an u long
	 * @param	base	The base.
	 * @returns	Base as a long.
	 */
	unsigned long long toULongLong( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to a float
	 * @param	base	The base.
	 * @returns	Base as a float.
	 */
	float toFloat( unsigned int base = 10 ) const;
	/**
	 * @brief		Converts a base to a double
	 * @param	base	The base.
	 * @returns	Base as a double.
	 */
	double toDouble( unsigned int base = 10 ) const;


	/************************************************************************/
	/* FromCString()                                                        */
	/**
	 * @brief		Converts a buffer to a character
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a char.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static char toChar( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static char toChar( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an int
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as an int.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static int toInt( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static int toInt( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to a short
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a short.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static short toShort( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static short toShort( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to a long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a long.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long toLong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long toLong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to a long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a long.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long long toLongLong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long long toLongLong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an u character
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a char.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned char toUChar( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned char toUChar( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an u int
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as an int.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned int toUInt( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned int toUInt( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an u short
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a short.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned short toUShort( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned short toUShort( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an u long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a long.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long toULong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long toULong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an u long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a long.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long long toULongLong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long long toULongLong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to a float
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a float.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static float toFloat( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static float toFloat( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to a double
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a double.
	 */
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static double toDouble( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static double toDouble( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );


	/**
	 * @brief		Converts this object to a character
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a char.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static char toChar( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static char toChar( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to an int
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to an int.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static int toInt( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static int toInt( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to a short
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a short.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static short toShort( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static short toShort( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to a long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a long.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long toLong( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long toLong( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to a long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a long.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long long toLongLong( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long long toLongLong( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to an u character
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a char.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned char toUChar( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned char toUChar( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to an u int
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to an int.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned int toUInt( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned int toUInt( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to an u short
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a short.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned short toUShort( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned short toUShort( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to an u long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a long.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long toULong( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long toULong( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to an u long
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a long.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long long toULongLong( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long long toULongLong( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to a float
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a float.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static float toFloat( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static float toFloat( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	/**
	 * @brief		Converts this object to a double
	 * @tparam	EndFunc	Functor type to detect end.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a double.
	 */
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static double toDouble( const T * buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static double toDouble( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );


	/************************************************************************/
	/* Logical                                                              */
	/**
	 * @brief		Inequality operator
	 * @param	text	The text.
	 * @returns	True if the parameters are not considered equivalent.
	 */
	bool operator!=( const BasicString<T> & text ) const;
	/**
	 * @brief		Equality operator
	 * @param	text	The text.
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==( const BasicString<T> & text ) const;
	/**
	 * @brief		Greater-than comparison operator
	 * @param	text	The text.
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>( const BasicString<T> & text ) const;
	/**
	 * @brief		Less-than comparison operator
	 * @param	text	The text.
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<( const BasicString<T> & text ) const;
	/**
	 * @brief		Greater-than-or-equal comparison operator
	 * @param	text	The text.
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=( const BasicString<T> & text ) const;

	bool operator<=( const BasicString<T> & text ) const;

	/**
	 * @brief		Inequality operator
	 * @param	text	The text.
	 * @returns	True if the parameters are not considered equivalent.
	 */
	bool operator!=( const T & text ) const;
	/**
	 * @brief		Equality operator
	 * @param	text	The text.
	 * @returns	True if the parameters are considered equivalent.
	 */
	bool operator==( const T & text ) const;
	/**
	 * @brief		Greater-than comparison operator
	 * @param	text	The text.
	 * @returns	True if the first parameter is greater than to the second.
	 */
	bool operator>( const T & text ) const;
	/**
	 * @brief		Less-than comparison operator
	 * @param	text	The text.
	 * @returns	True if the first parameter is less than the second.
	 */
	bool operator<( const T & text ) const;
	/**
	 * @brief		Greater-than-or-equal comparison operator
	 * @param	text	The text.
	 * @returns	True if the first parameter is greater than or equal to the second.
	 */
	bool operator>=( const T & text ) const;

	bool operator<=( const T & text ) const;


	/************************************************************************/
	/* To StringASCII                                                            */
	/**
	 * @brief		Convert this object into a string representation
	 * @param	c	A T to process.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( const T & c );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned char number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned short number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned int number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( int number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned long number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( long long number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned long long number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Base	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( long number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// static BasicString<T> toString( double number );

	/**
	 * @brief		Convert this object into a string representation
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	number	Number of.
	 * @returns	Number as a BasicString<T>
	 */
	// template<unsigned int Precision = 5, unsigned int Base = 10>
	// static BasicString<T> toString( float number );



	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( unsigned char number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( unsigned short number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( unsigned int number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( int number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( unsigned long number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( long long number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( unsigned long long number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number	Number of.
	 * @param	base  	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( long number, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number   	Number of.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( double number, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	number   	Number of.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( float number, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Convert this object into a string representation
	 * @param	b	True to b.
	 * @returns	A BasicString<T> that represents this object.
	 */
	static BasicString<T> toString( bool b );

	/************************************************************************/
	/* Others                                                               */
	/**
	 * @brief		Splits the given delimiter
	 * @param	delimiter	The delimiter.
	 * @returns	A Vector<BasicString<T>>
	 */
	Vector<BasicString<T>> split( const T & delimiter ) const;
	/**
	 * @brief		Query if this object is numeric
	 * @returns	True if numeric, false if not.
	 */
	bool isNumeric() const;

	/**
	 * @brief		Resize the string
	 * @param	newSize	New size of this string.
	 */
	void resize( typename BasicString<T>::Size newSize );

	/** @brief	. */
	using Vector<T>::getSize;

	/**
	 * @brief		Gets a size
	 * @param	str	The string.
	 * @returns	The size.
	 */
	template<typename C>
	static typename BasicString<T>::Size getSize( C * const & str );

	/**
	 * @brief		Gets a size
	 * @param	str	The string.
	 * @returns	The size.
	 */
	template<typename C, size_t N>
	static typename BasicString<T>::Size getSize( const C (&str)[N] );

	/**
	 * @brief		Converts this object to a c string
	 * @returns	This object as a const T*.
	 */
	const T * toCString() const;

	/** @brief	set the size to 0 */
	void clear();

	/**
	 * @brief		Get the iterator of the first occurence of a character. May return getEnd() if nothing founded.
	 * @param	c	The character to look for.
	 * @returns	Iterator of the first occurence or getEnd() if nothing founded.
	 */
	typename BasicString<T>::Iterator getFirstIt( const T & c ) const;
	/**
	 * @brief		Get the iterator of the last occurence of a character. May return getEnd() if nothing founded.
	 * @param	c	The character to look for.
	 * @returns	Iterator of the last occurence or getEnd() if nothing founded.
	 */
	typename BasicString<T>::Iterator getLastIt( const T & c ) const;

	/**
	 * @brief		Get the iterator of the first occurence of a string. May return getEnd() if nothing founded.
	 * @param	c	The string to look for.
	 * @returns	Iterator of the first occurence or getEnd() if nothing founded.
	 */
	typename BasicString<T>::Iterator getFirstIt( const BasicString<T> & str ) const;
	/**
	 * @brief		Get the iterator of the last occurence of a string. May return getEnd() if nothing founded.
	 * @param	c	The string to look for.
	 * @returns	Iterator of the last occurence or getEnd() if nothing founded.
	 */
	typename BasicString<T>::Iterator getLastIt( const BasicString<T> & str ) const;

	/**
	 * @brief		Get the index of the first occurence of a character. May return BasicString<T>::overflow if nothing founded.
	 * @param	c	The character to look for.
	 * @returns	Index of the first occurence or BasicString<T>::overflow if nothing founded.
	 */
	typename BasicString<T>::Size getFirst( const T & c ) const;
	/**
	 * @brief		Get the index of the last occurence of a character. May return BasicString<T>::overflow if nothing founded.
	 * @param	c	The character to look for.
	 * @returns	Index of the last occurence or BasicString<T>::overflow if nothing founded.
	 */
	typename BasicString<T>::Size getLast( const T & c ) const;

	/**
	 * @brief		Get the index of the first occurence of a string. May return BasicString<T>::overflow if nothing founded.
	 * @param	c	The string to look for.
	 * @returns	Index of the first occurence or BasicString<T>::overflow if nothing founded.
	 */
	typename BasicString<T>::Size getFirst( const BasicString<T> & str ) const;
	/**
	 * @brief		Get the index of the last occurence of a string. May return BasicString<T>::overflow if nothing founded.
	 * @param	c	The string to look for.
	 * @returns	Index of the last occurence or BasicString<T>::overflow if nothing founded.
	 */
	typename BasicString<T>::Size getLast( const BasicString<T> & str ) const;

	/**
	 * @brief		Replaces
	 * @param	toReplace	to replace.
	 * @param	byThis   	The by this.
	 */
	void replace( const T & toReplace, const T & byThis );
	/**
	 * @brief		Replaces
	 * @param	toReplace	to replace.
	 * @param	byThis   	The by this.
	 */
	void replace( const T & toReplace, const BasicString<T> & byThis );
	/**
	 * @brief		Replaces
	 * @param	toReplace	to replace.
	 * @param	byThis   	The by this.
	 */
	void replace( const BasicString<T> & toReplace, const BasicString<T> & byThis );

	/**
	 * @brief		Gets the directory
	 * @returns	The directory.
	 */
	BasicString<T> getDirectory() const;
	/**
	 * @brief		Gets file name
	 * @returns	The file name.
	 */
	BasicString<T> getFileName() const;
	/**
	 * @brief		Gets sub string
	 * @param	index	Zero-based index of the.
	 * @param	size 	The size.
	 * @returns	The sub string.
	 */
	BasicString<T> getSubStr( typename BasicString<T>::Size index, typename BasicString<T>::Size size ) const;
	/**
	 * @brief		Gets sub string
	 * @param	beginIt	The begin iterator.
	 * @param	size   	The size.
	 * @returns	The sub string.
	 */
	BasicString<T> getSubStr( typename BasicString<T>::Iterator beginIt, typename BasicString<T>::Size size ) const;
	/**
	 * @brief		Gets sub string
	 * @param	beginIt	The begin iterator.
	 * @param	endIt  	The end iterator.
	 * @returns	The sub string.
	 */
	BasicString<T> getSubStr( typename BasicString<T>::Iterator beginIt, typename BasicString<T>::Iterator endIt ) const;

	BasicString<T> toLower() const;
	BasicString<T> toUpper() const;


	/**
	 * @brief		Function to compare two elements
	 * @param	x	First Element.
	 * @param	y	Second Element.
	 * @returns	Equal (x == y), Less (x < y) or Greater (x > y)
	 */
	static Math::Compare::Value compare( const BasicString<T> & x, const BasicString<T> & y );


	/**
	 * @brief		Write this string into a file as readable (non binary)
	 * @param [in,out]	fileStream	StreamT used to write this string.
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool writeReadable( IO::SimpleFileStream * fileStream ) const;

	/**
	 * @brief		read from a file stream
	 * @param [in,out]	fileStream	stream used to read load this object.
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( IO::SimpleFileStream * fileStream );

	/**
	 * @brief		read from a file stream
	 * @param [in,out]	fileStream	stream used to read load this object.
	 * @param 		  	size	  	Number of characters to read.
	 * @returns	boolean to know if the operation is a success of not.
	 */
	bool read( IO::SimpleFileStream * fileStream, typename BasicString<T>::Size size );

	/************************************************************************/
	/* Some static methods                                                  */
	/**
	 * @brief		Query if 'v' is numeric
	 * @param	v	A BasicString<T> to process.
	 * @returns	True if numeric, false if not.
	 */
	static bool isNumeric( const BasicString<T> & v );
	/**
	 * @brief		Splits
	 * @param	s		 	A BasicString<T> to process.
	 * @param	delimiter	The delimiter.
	 * @returns	A Vector<BasicString<T>>
	 */
	static Vector<BasicString<T>> split( const BasicString<T> & s, const T & delimiter );

	/**
	 * @brief		Formats
	 * @tparam	T1   	First element type.
	 * @tparam	Types	Others elements.
	 * @param	referenceString	The reference string.
	 * @param	arg1		   	The first argument.
	 * @param	args		   	Variable arguments providing the variables.
	 * @returns	The formatted value.
	 */
	template<typename T1, typename... Types>
	static BasicString<T> format( const BasicString<T> referenceString, const T1 & arg1, Types ... args );

	/**
	 * @brief		Formats
	 * @tparam	C		Reference string type.
	 * @tparam	T1   	First element type.
	 * @tparam	Types	Others elements.
	 * @param	str		The reference string.
	 * @param	arg1		   	The first argument.
	 * @param	args		   	Variable arguments providing the variables.
	 * @returns	The formatted value.
	 */
	template<typename C, typename T1, typename... Types>
	static BasicString<T> format( C * const & str, const T1 & arg1, Types ... args );

	/**
	 * @brief		Formats
	 * @tparam	C		Reference string type.
	 * @tparam	N		Refernce string size.
	 * @tparam	T1   	First element type.
	 * @tparam	Types	Others elements.
	 * @param	str		The reference string.
	 * @param	arg1		   	The first argument.
	 * @param	args		   	Variable arguments providing the variables.
	 * @returns	The formatted value.
	 */
	template<typename C, size_t N, typename T1, typename... Types>
	static BasicString<T> format( const C( &str )[ N ], const T1 & arg1, Types ... args );


	/**
	 * @brief		Gets a first
	 * @param	buffer	  	The buffer.
	 * @param	bufferSize	Size of the buffer.
	 * @param	c		  	A T to process.
	 * @returns	The first.
	 */
	static typename BasicString<T>::Size getFirst( const T * buffer, typename BasicString<T>::Size bufferSize, const T & c );
	/**
	 * @brief		Gets a last
	 * @param	buffer	  	The buffer.
	 * @param	bufferSize	Size of the buffer.
	 * @param	c		  	A T to process.
	 * @returns	The last.
	 */
	static typename BasicString<T>::Size getLast( const T * buffer, typename BasicString<T>::Size bufferSize, const T & c );

	/**
	 * @brief		Gets a first
	 * @param	buffer			The buffer.
	 * @param	bufferSize  	Size of the buffer.
	 * @param	toSearch		to search.
	 * @param	toSearchSize	Size of to search.
	 * @returns	The first.
	 */
	static typename BasicString<T>::Size getFirst( const T * buffer, typename BasicString<T>::Size bufferSize, const T * toSearch, typename BasicString<T>::Size toSearchSize );
	/**
	 * @brief		Gets a last
	 * @param	buffer			The buffer.
	 * @param	bufferSize  	Size of the buffer.
	 * @param	toSearch		to search.
	 * @param	toSearchSize	Size of to search.
	 * @returns	The last.
	 */
	static typename BasicString<T>::Size getLast( const T * buffer, typename BasicString<T>::Size bufferSize, const T * toSearch, typename BasicString<T>::Size toSearchSize );

	/**
	 * @brief		Gets a first
	 * @param	buffer	The buffer.
	 * @param	c	  	A T to process.
	 * @returns	The first.
	 */
	static typename BasicString<T>::Size getFirst( const T * buffer, const T & c );
	/**
	 * @brief		Gets a last
	 * @param	buffer	The buffer.
	 * @param	c	  	A T to process.
	 * @returns	The last.
	 */
	static typename BasicString<T>::Size getLast( const T * buffer, const T & c );

	/**
	 * @brief		Gets a first
	 * @param	buffer  	The buffer.
	 * @param	toSearch	to search.
	 * @returns	The first.
	 */
	static typename BasicString<T>::Size getFirst( const T * buffer, const T * toSearch );
	/**
	 * @brief		Gets a last
	 * @param	buffer  	The buffer.
	 * @param	toSearch	to search.
	 * @returns	The last.
	 */
	static typename BasicString<T>::Size getLast( const T * buffer, const T * toSearch );

	/**
	 * @brief	Convert a character to a number.
	 * @param 	c	The character to be converted.
	 * @returns	The number.
	 */
	template<typename N = char, int nbChars = 1, int base = 10>
	static N parseNumber( const T ** c );



	/************************************************************************/
	/* CONVERSION                                                           */
	/************************************************************************/
	template<typename C>
	operator StreamT<C>();




	/** @brief	The numbers[ 16] */
	static const T numbers[ 16 ];
	/** @brief	The null */
	static const BasicString<T> null;

	/** Default EndFunc */
	static const IsEndSentinel IS_END_SENTINEL;

protected:
	/**
	 * @brief		Constructor
	 * @param	parameter1	The first parameter.
	 */
	BasicString( typename Vector<T>::ctor );

	/************************************************************************/
	/* concat() without adding sentinel                                     */
	/**
	 * @brief		Concatenate whithout \0
	 * @param	str	The string.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const BasicString<T> & str );
	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	C	Type of the c.
	 * @param	str	The string.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C>
	BasicString & _concatWOS( const BasicString<C> & str );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	C	Type of the c.
	 * @param	buffer	  	The buffer.
	 * @param	bufferSize	Size of the buffer.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C>
	BasicString & _concatWOS( C * const & buffer, const typename BasicString<C>::Size & bufferSize );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	C	Type of the c.
	 * @param	buffer	The buffer.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C>
	BasicString & _concatWOS( C * const & buffer);

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	C	Type of the c.
	 * @param	str	The string.
	 * @returns	A reference to a BasicString.
	 */
	template<typename C, size_t N>
	BasicString & _concatWOS( const C (& str)[N] );

	/**
	 * @brief		Concatenate whithout \0
	 * @param	b	True to b.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const bool & b );


	/**
	 * @brief		Concatenate whithout \0
	 * @param	c	A char to process.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const char & c );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	c	A wchar_t to process.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const wchar_t & c );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	uc	The uc.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const unsigned char & uc );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	us	The us.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const unsigned short & us );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	i	Zero-based index of the.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const int & i );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	ui	The user interface.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const unsigned int & ui );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	l	A long to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const long & l );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	ul	The ul.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const unsigned long & ul );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	ll	The ll.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const long long & ll );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Base	Type of the base.
	 * @param	ull	The ull.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Base = 10>
	// BasicString & _concatWOS( const unsigned long long & ull );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	d	A double to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// BasicString & _concatWOS( const double & d );

	/**
	 * @brief		Concatenate whithout \0
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	f	A float to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<unsigned int Precision = 5, unsigned int Base = 10>
	// BasicString & _concatWOS( const float & f );


	/**
	 * @brief		Concatenate whithout \0
	 * @param	uc  	The uc.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const unsigned char & uc, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	us  	The us.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const unsigned short & us, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	i   	Zero-based index of the.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const int & i, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	ui  	The user interface.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const unsigned int & ui, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	l   	A long to process.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const long & l, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	ul  	The ul.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const unsigned long & ul, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	ll  	The ll.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const long long & ll, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	ull 	The ull.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const unsigned long long & ull, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	d		 	A double to process.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const double & d, unsigned int precision = 5, unsigned int base = 10 );
	/**
	 * @brief		Concatenate whithout \0
	 * @param	f		 	A float to process.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A reference to a BasicString.
	 */
	BasicString & _concatWOS( const float & f, unsigned int precision = 5, unsigned int base = 10 );






private:

	/**
	 * @brief		Formats
	 * @tparam	C		Reference string type.
	 * @tparam	T1   	First element type.
	 * @tparam	Types	Others elements.
	 * @param	referenceStringBegin	Pointer to the reference string begin.
	 * @param	referenceStringEnd		Pointer to the reference string end.
	 * @param	arg1		   	The first argument.
	 * @param	args		   	Variable arguments providing the variables.
	 * @returns	The formatted value.
	 */
	template<typename C, typename T1, typename... Types>
	static BasicString<T> _format( const C * referenceStringBegin, const C * referenceStringEnd, const T1 & arg1, Types ... args );

	/**
	 * @brief		Formats
	 * @tparam	T1   	Generic type parameter.
	 * @tparam	Types	Type of the types.
	 * @param 		  	referenceStringBegin	The reference string begin.
	 * @param 		  	referenceStringEnd  	The reference string end.
	 * @param [in,out]	newString				If non-null, the new string.
	 * @param 		  	arg1					The first argument.
	 * @param 		  	vars					Variable arguments providing the variables.
	 */
	template<typename C, typename T1, typename... Types>
	static void __format( const C * referenceStringBegin, const C * referenceStringEnd, BasicString<T> * newString, const T1 & arg1, Types ... args );

	/**
	 * @brief		Formats
	 * @param 		  	referenceStringBegin	The reference string begin.
	 * @param 		  	referenceStringEnd  	The reference string end.
	 * @param [in,out]	newString				If non-null, the new string.
	 */
	template<typename C>
	static void __format( const C * referenceStringBegin, const C * referenceStringEnd, BasicString<T> * newString );

	/**
	 * @brief		Concatenate integer
	 * @tparam	Type	Type of the type.
	 * @tparam	Base	Type of the base.
	 * @param	i	Integer to be concatenated.
	 * @returns	A reference to a BasicString.
	 */
	// template<typename Type, unsigned int Base = 10>
	// BasicString & _concatInteger( const Type & i );

	/**
	 * @brief		Concatenate integer
	 * @tparam	Type	Type of the type.
	 * @param	i	Integer to be concatenated.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	template<typename Type>
	BasicString & _concatInteger( const Type & i, unsigned int base = 10 );

	/**
	 * @brief		Concatenate integer and fill for adding at least "FillNb" number of chars.
	 * @tparam	Type	Type.
	 * @param	i	Integer to be concatenated.
	 * @tparam	fillNb	Minimal number of chars to be added.
	 * @param	fillChar	Chars to be added as a filler.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	template<typename Type>
	BasicString & _concatFillInteger( const Type & i, const typename BasicString<T>::Size & fillNb, const T & fillChar, unsigned int base = 10 );

	/**
	 * @brief		Concatenate float
	 * @tparam	Type	 	Type of the type.
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	f	Float to be concatenated.
	 * @returns	A reference to a BasicString.
	 */
	// template<typename Type, unsigned int Precision = 5, unsigned int Base = 10>
	// BasicString & _concatFloat( const Type & f );

	/**
	 * @brief		Concatenate float
	 * @tparam	Type	Type of the type.
	 * @param	f	Float to be concatenated.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A reference to a BasicString.
	 */
	template<typename Type>
	BasicString & _concatFloat( const Type & f, unsigned int precision = 5, unsigned int base = 10 );



	/**
	 * @brief		Concatenate integer whithout \0
	 * @tparam	Type	Type of the type.
	 * @tparam	Base	Type of the base.
	 * @param	i	Zero-based index of the.
	 * @returns	A reference to a BasicString.
	 */
	// template<typename Type, unsigned int Base = 10>
	// BasicString & _concatIntegerWOS( const Type & i );

	/**
	 * @brief		Concatenate integer whithout \0
	 * @tparam	Type	Type of the type.
	 * @param	i   	Zero-based index of the.
	 * @param	base	The base.
	 * @returns	A reference to a BasicString.
	 */
	template<typename Type>
	BasicString & _concatIntegerWOS( const Type & i, unsigned int base = 10 );

	/**
	 * @brief		Concatenate float whithout \0
	 * @tparam	Type	 	Type of the type.
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param	f	A Type to process.
	 * @returns	A reference to a BasicString.
	 */
	// template<typename Type, unsigned int Precision = 5, unsigned int Base = 10>
	// BasicString & _concatFloatWOS( const Type & f );

	/**
	 * @brief		Concatenate float whithout \0
	 * @tparam	Type	Type of the type.
	 * @param	f		 	A Type to process.
	 * @param	precision	The precision.
	 * @param	base	 	The base.
	 * @returns	A reference to a BasicString.
	 */
	template<typename Type>
	BasicString & _concatFloatWOS( const Type & f, unsigned int precision = 5, unsigned int base = 10 );



	/**
	 * @brief		Converts a buffer to a float
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Type	Return type.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a Type.
	 */
	// template<typename Type, unsigned int Base, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static Type _toFloat( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to a signed integer
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Type	Return type.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a Type.
	 */
	// template<typename Type, unsigned int Base, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static Type _toSignedInteger( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts a buffer to an unsigned integer
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Type	Return type.
	 * @tparam	Base	Type of the base.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param	endFunc	Functor to detect end.
	 * @returns	Buffer as a Type.
	 */
	// template<typename Type, unsigned int Base, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static Type _toUnsignedInteger( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );


	/**
	 * @brief		Converts this object to a float
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Type	Return type.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a Type.
	 */
	template<typename Type, typename EndFunc = BasicString<T>::IsEndSentinel>
	static Type _toFloat( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts this object to a signed integer
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Type	Return type.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a Type.
	 */
	template<typename Type, typename EndFunc = BasicString<T>::IsEndSentinel>
	static Type _toSignedInteger( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	/**
	 * @brief		Converts this object to an unsigned integer
	 * @tparam	EndFunc	Functor type to detect end.
	 * @tparam	Type	Return type.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @param	endFunc	Functor to detect end.
	 * @returns	The given data converted to a Type.
	 */
	template<typename Type, typename EndFunc = BasicString<T>::IsEndSentinel>
	static Type _toUnsignedInteger( const T ** buffer, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );



	/**
	 * @brief		Convert i 2 string
	 * @tparam	Type	Type of the type.
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns	The i converted 2 string.
	 */
	// template<typename Type, unsigned int Base>
	// static typename BasicString<T>::Size _convertI2String( Type number, T * buffer );

	/**
	 * @brief		Convert i 2 string
	 * @tparam	Type	Type of the type.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns	The i converted 2 string.
	 */
	template< typename Type>
	static typename BasicString<T>::Size _convertI2String( Type number, T * buffer, unsigned int base = 10 );

	/**
	 * @brief		Convert user interface 2 string
	 * @tparam	Type	Type of the type.
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns	The user converted interface 2 string.
	 */
	// template<typename Type, unsigned int Base>
	// static typename BasicString<T>::Size _convertUI2String( Type number, T * buffer );

	/**
	 * @brief		Convert user interface 2 string
	 * @tparam	Type	Type of the type.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns	The user converted interface 2 string.
	 */
	template<typename Type>
	static typename BasicString<T>::Size _convertUI2String( Type number, T * buffer, unsigned int base = 10 );

	/**
	 * @brief		Convert float 2 string
	 * @tparam	Type	 	Type of the type.
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns	The float converted 2 string.
	 */
	// template<typename Type, unsigned int Precision = 10, unsigned int Base>
	// static typename BasicString<T>::Size _convertFloat2String( Type number, T * buffer );

	/**
	 * @brief		Convert float 2 string
	 * @tparam	Type	Type of the type.
	 * @param 		  	number   	Number of.
	 * @param [in,out]	buffer   	If non-null, the buffer.
	 * @param 		  	precision	The precision.
	 * @param 		  	base	 	The base.
	 * @returns	The float converted 2 string.
	 */
	template<typename Type>
	static typename BasicString<T>::Size _convertFloat2String( Type number, T * buffer, unsigned int precision = 5, unsigned int base = 10 );




	/**
	 * @brief		Convert i 2 string whithout \0
	 * @tparam	Type	Type of the type.
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns	The i converted 2 string whithout \0.
	 */
	// template<typename Type, unsigned int Base>
	// static typename BasicString<T>::Size _convertI2StringWOS( Type number, T * buffer );

	/**
	 * @brief		Convert i 2 string whithout \0
	 * @tparam	Type	Type of the type.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns	The i converted 2 string whithout \0.
	 */
	template< typename Type>
	static typename BasicString<T>::Size _convertI2StringWOS( Type number, T * buffer, unsigned int base = 10 );

	/**
	 * @brief		Convert user interface 2 string whithout \0
	 * @tparam	Type	Type of the type.
	 * @tparam	Base	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns	The user converted interface 2 string whithout \0.
	 */
	// template<typename Type, unsigned int Base>
	// static typename BasicString<T>::Size _convertUI2StringWOS( Type number, T * buffer );

	/**
	 * @brief		Convert user interface 2 string whithout \0
	 * @tparam	Type	Type of the type.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @param 		  	base  	The base.
	 * @returns	The user converted interface 2 string whithout \0.
	 */
	template<typename Type>
	static typename BasicString<T>::Size _convertUI2StringWOS( Type number, T * buffer, unsigned int base = 10 );

	/**
	 * @brief		Convert float 2 string whithout \0
	 * @tparam	Type	 	Type of the type.
	 * @tparam	Precision	Type of the precision.
	 * @tparam	Base	 	Type of the base.
	 * @param 		  	number	Number of.
	 * @param [in,out]	buffer	If non-null, the buffer.
	 * @returns	The float converted 2 string whithout \0.
	 */
	// template<typename Type, unsigned int Precision = 10, unsigned int Base>
	// static typename BasicString<T>::Size _convertFloat2StringWOS( Type number, T * buffer );

	/**
	 * @brief		Convert float 2 string whithout \0
	 * @tparam	Type	Type of the type.
	 * @param 		  	number   	Number of.
	 * @param [in,out]	buffer   	If non-null, the buffer.
	 * @param 		  	precision	The precision.
	 * @param 		  	base	 	The base.
	 * @returns	The float converted 2 string whithout \0.
	 */
	template<typename Type>
	static typename BasicString<T>::Size _convertFloat2StringWOS( Type number, T * buffer, unsigned int precision = 5, unsigned int base = 10 );


	

	

	
};











/************************************************************************/
/* OPERATOR STREAM                                                      */
/************************************************************************/
/*
template<typename T>
template<typename C>
BasicString<T> & operator<<(BasicString<T> basicString, C * const & str);

template<typename T>
template<typename C>
BasicString<T> & operator<<(BasicString<T> basicString, const BasicString<C> & str);

template<typename T>
template<typename C, size_t N>
BasicString<T> & operator<<(BasicString<T> basicString, const C (& str)[N]);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned char & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned short & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const int & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned int & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const long & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned long & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const long long & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned long long & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const double & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const float & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const bool & b);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const T & c);

*/




/************************************************************************/
/* OPERATOR +                                                           */
/**
 * @brief		*********************************************************************
 * @param	str1	The first value.
 * @param	str2	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<T> & str2 );

/**
 * @brief		Addition operator
 * @param	str1	The first value.
 * @param	str2	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<C> & str2 );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	i  	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const int & i );

/**
 * @brief		Addition operator
 * @param	i  	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const int & i, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	ui 	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned char & ui );

/**
 * @brief		Addition operator
 * @param	ui 	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const unsigned char & ui, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	ui 	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned short & ui );

/**
 * @brief		Addition operator
 * @param	ui 	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const unsigned short & ui, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	ui 	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned int & ui );

/**
 * @brief		Addition operator
 * @param	ui 	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const unsigned int & ui, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	l  	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long & l );

/**
 * @brief		Addition operator
 * @param	l  	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const long & l, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	ul 	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long & ul );

/**
 * @brief		Addition operator
 * @param	ul 	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const unsigned long & ul, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	ll 	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long long & ll );

/**
 * @brief		Addition operator
 * @param	ll 	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const long long & ll, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	ull	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long long & ull );

/**
 * @brief		Addition operator
 * @param	ull	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const unsigned long long & ull, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	f  	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const float & f );

/**
 * @brief		Addition operator
 * @param	f  	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const float & f, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	b  	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const bool & b );

/**
 * @brief		Addition operator
 * @param	b  	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const bool & b, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	d  	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const double & d );

/**
 * @brief		Addition operator
 * @param	d  	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const double & d, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str	The first value.
 * @param	c  	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const T & c );

/**
 * @brief		Addition operator
 * @param	c  	The first value.
 * @param	str	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T>
BasicString<T> operator+( const T & c, const BasicString<T> & str );

/**
 * @brief		Addition operator
 * @param	str1	The first value.
 * @param	str2	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, C * const & str2);

/**
 * @brief		Addition operator
 * @param	str1	The first value.
 * @param	str2	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T, typename C>
BasicString<T> operator+( C * const & str1, const BasicString<T> & str2 );


/**
 * @brief		Addition operator
 * @param	str1	The first value.
 * @param	str2	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T, typename C, size_t N>
BasicString<T> operator+( const C (&str1)[N], const BasicString<T> & str2 );

/**
 * @brief		Addition operator
 * @param	str1	The first value.
 * @param	str2	A value to add to it.
 * @returns	The result of the operation.
 */
template<typename T, typename C, size_t N>
BasicString<T> operator+( const BasicString<T> & str1, const C (&str2)[N] );


template<typename T>
std::ostream & operator<<( std::ostream & stream, const BasicString<T> & str );

template<typename T>
IO::SimpleFileStream& operator<<(IO::SimpleFileStream& stream, const BasicString<T>& str);

/** @brief	Defines an alias representing an ASCII String */
typedef BasicString<char> StringASCII;
/** @brief	Defines an alias representing an UTF16 String */
typedef BasicString<wchar_t> WString;
/** @brief	Defines an alias representing an UTF32 String */
typedef BasicString<unsigned int> UTF32String;

#ifdef WIN32
/** @brief	If in Win32, Standard String will be UTF16 */
typedef WString String;
#else
/** @brief	If not in Win32, Standard String will be ASCII */
typedef StringASCII String;
#endif


template<typename N, int nbChars, int base = 10>
class __ParseNumber {
public:

	template<typename T>
	static N compute(const T ** c ) {

		T cVal( **c );
		( *c )++;

		return N( cVal - T( '0' ) ) * pow( N(base), N(nbChars - 1) ) + __ParseNumber<N, nbChars - 1, base>::compute( c );
	}

private:
	static constexpr N pow( const N & v, const N & e ) {
		return ( e == N( 0 ) ) ? N( 1 ) : v * pow( v, e - N( 1 ) );
	}

};

template<typename N, int base>
class __ParseNumber< N, 0, base > {
public:

	template<typename T>
	static N compute( const T ** c ) {
		return N( 0 );
	}

};


#include "String.hpp"