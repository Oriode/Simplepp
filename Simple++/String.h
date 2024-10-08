///@file	String.h.
///@brief		Declares the string class

#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include "SimpleLog.h"
#include "Math/BasicComparable.h"
#include "Vector.h"
#include "Optional.h"

#if defined WIN32 && defined ENABLE_WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif

 ///@brief		.
 ///@tparam	T	buffer type
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

	static constexpr Size DefaultPrecisionDouble = 5;
	static constexpr Size DefaultPrecisionFloat = 3;


	using Vector<T>::ElemType;

	template<typename C>
	friend class BasicString;

	template<typename C>
	friend class UTF8StringT;

	/** @brief	Default constructor */
	BasicString();




	///@brief		Constructor
	///@tparam	C	Type of the c.
	///@param	str	The string.
	template<typename C>
	BasicString( C * const & str );

	///@brief		Constructor
	///@tparam	C	Type of the c.
	///@param	str 	The string.
	///@param	size	The size.
	template<typename C>
	BasicString( const C * str, Size size );
	///@brief		Constructor
	///@tparam	C	Type of the c.
	///@param	beginIt	The begin iterator.
	///@param	endIt  	The end iterator.
	template<typename C>
	BasicString( const typename RandomAccessIterator<C> beginIt, const typename RandomAccessIterator<C> endIt );


	///@brief		Constructor
	///@tparam	C	Type of the c.
	///@param	str	The string.
	template<typename C>
	BasicString( const BasicString<C> & str );
	///@brief		Constructor
	///@param	str	The string.
	BasicString( const BasicString<T> & str );
	///@brief		Constructor
	///@param [in,out]	str	The string.
	BasicString( BasicString<T> && str );


	///@brief		Constructor
	///@tparam	C	String type.
	///@param	str	Constant string.
	template<typename C, size_t N>
	BasicString( const C (& str)[N] );

	///@brief			Constructor using an Interger.
	///@param	u/ui	Unsigned int.
	///@param base		Base used for the conversion.
	BasicString( const unsigned char & ui, unsigned int base = 10 );
	BasicString( const unsigned short & ui, unsigned int base = 10 );
	BasicString( const int & i, unsigned int base = 10 );
	BasicString( const unsigned int & ui, unsigned int base = 10 );
	BasicString( const long int & l, unsigned int base = 10 );
	BasicString( const unsigned long int & ul, unsigned int base = 10 );
	BasicString( const long long int & ll, unsigned int base = 10 );
	BasicString( const unsigned long long int & ull, unsigned int base = 10 );

	///@brief		Constructor using a Float.
	///@param	f/d	A Float to process.
	///@param		precision Precision to be used.
	///@param base	Base used for the conversion.
	BasicString( const double & d, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	BasicString( const float & f, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );

	///@brief		Constructor using a Boolean.
	///@param		b	Boolean.
	BasicString( const bool & b );

	///@brief		Constructor using a single char.
	///@param		c	Char.
	BasicString( const T & c );

	///@brief		Constructor from a comparable value.
	///@param		compareValue	Value of a compare.
	BasicString(const typename Math::Compare::Value & compareValue);



	/** @brief	Destructor */
	~BasicString();

	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	///@brief		Assignment operator
	///@param	str	The string.
	///@returns	A shallow copy of this object.
	template<typename C>
	BasicString & operator=( C * const & str );

	///@brief		Assignment operator
	///@param	str	The string.
	///@returns	A shallow copy of this object.
	template<typename C>
	BasicString & operator=( const BasicString<C> & str );
	///@brief		Assignment operator
	///@param	str	The string.
	///@returns	A shallow copy of this object.
	BasicString & operator=( const BasicString<T> & str );
	///@brief		Move assignment operator
	///@param [in,out]	str	The string.
	///@returns	A shallow copy of this object.
	BasicString & operator=( BasicString<T> && str );


	///@brief		Assignment operator
	///@param	str	The string.
	///@returns	A shallow copy of this object.
	template<typename C, size_t N>
	BasicString & operator=( const C (& str)[N] );

	///@brief		Assignment operator using an Integer.
	///@param	i	Integer to be assigned.
	///@returns		Reference to this.
	BasicString & operator=( const unsigned char & i );
	BasicString & operator=( const unsigned short & i );
	BasicString & operator=( const int & i );
	BasicString & operator=( const unsigned int & i );
	BasicString & operator=( const long int & i );
	BasicString & operator=( const unsigned long int & i );
	BasicString & operator=( const long long int & i );
	BasicString & operator=( const unsigned long long int & i );

	///@brief		Assignment operator using a Float.
	///@param	i	Float to be assigned.
	///@returns	A	Reference to this.
	BasicString & operator=( const double & i );
	BasicString & operator=( const float & i );

	///@brief		Assignment operator
	///@param	b	True to b.
	///@returns	A shallow copy of this object.
	BasicString & operator=( const bool & b );

	///@brief		Assignment operator
	///@param	c	A T to process.
	///@returns	A shallow copy of this object.
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

	template<typename C>
	BasicString& operator<<( const Optional<C> & o );

	BasicString & operator<<( const unsigned char & uc );
	BasicString & operator<<( const unsigned short & us );
	BasicString & operator<<( const int & i );
	BasicString & operator<<( const unsigned int & ui );
	BasicString & operator<<( const long int & l );
	BasicString & operator<<( const unsigned long int & ul );
	BasicString & operator<<( const long long int & ll );
	BasicString & operator<<( const unsigned long long int & ull );
	BasicString & operator<<( const double & d );
	BasicString & operator<<( const float & f );
	BasicString & operator<<( const bool & b );
	BasicString & operator<<( const wchar_t & c );
	BasicString & operator<<( const char & c );

	template<typename C>
	BasicString<T> & operator<<( const Vector<C> & v );

	/************************************************************************/
	/* OPERATOR +=	                                                      */
	///@brief		Addition assignment operator
	///@param	str	The string.
	///@returns	The result of the operation.
	template<typename C>
	BasicString & operator+=( C * const & str );

	///@brief		Addition assignment operator
	///@param	str	The string.
	///@returns	The result of the operation.
	template<typename C>
	BasicString & operator+=( const BasicString<C> & str );

	///@brief		Addition assignment operator
	///@param	str	The string.
	///@returns	The result of the operation.
	template<typename C, size_t N>
	BasicString & operator+=( const C (& str)[N] );

	template<typename C>
	BasicString& operator+=( const Optional<C>& o );

	///@brief		Concat operator with an Integer.
	///@param	uc	Integer to be concatenated.
	///@returns		Reference to this.
	BasicString & operator+=( const unsigned char & uc );
	BasicString & operator+=( const unsigned short & us );
	BasicString & operator+=( const int & i );
	BasicString & operator+=( const unsigned int & ui );
	BasicString & operator+=( const long int & l );
	BasicString & operator+=( const unsigned long int & ul );
	BasicString & operator+=( const long long int & ll );
	BasicString & operator+=( const unsigned long long int & ull );
	BasicString & operator+=( const double & d );

	///@brief		Concat operator with a Float.
	///@param	f	A float to be concatenated.
	///@returns		Reference to this.
	BasicString & operator+=( const float & f );
	BasicString & operator+=( const bool & b );

	///@brief		Addition assignment operator
	///@param	c	A C to process.
	///@returns	The result of the operation.
	template<typename C>
	BasicString & operator+=( const C & c );
	///@brief		Addition assignment operator
	///@param	c	A char to process.
	///@returns	The result of the operation.
	BasicString & operator+=( const char & c );
	///@brief		Addition assignment operator
	///@param	c	A wchar_t to process.
	///@returns	The result of the operation.
	BasicString & operator+=( const wchar_t & c );




	/************************************************************************/
	/* OPERATOR CONCAT                                                      */
	///@brief		Concatenates the given string
	///@param	str	The string.
	///@returns	A reference to a BasicString.

	BasicString & concat( const BasicString<T> & str );

	template<typename C>
	BasicString & concat( const BasicString<C> & str );

	template<typename C>
	BasicString & concat( const C * buffer, const Size & bufferSize );

	template<typename C>
	BasicString & concat( C * const & buffer );

	template<typename C, size_t N>
	BasicString & concat( const C (& str)[N] );

	template<typename C>
	BasicString& concat( const Optional<C>& o );

	BasicString & concat( const bool & b );
	BasicString & concat( const char & c );
	BasicString & concat( const wchar_t & c );


	///@brief			Concat an Integer to this String.
	///@param	uc  	The Integer.
	///@param	base	The base.
	///@returns			Reference to this.
	BasicString & concat( const unsigned char & uc, unsigned int base = 10 );
	BasicString & concat( const unsigned short & us, unsigned int base = 10 );
	BasicString & concat( const int & i, unsigned int base = 10 );
	BasicString & concat( const unsigned int & ui, unsigned int base = 10 );
	BasicString & concat( const long int & l, unsigned int base = 10 );
	BasicString & concat( const unsigned long int & ul, unsigned int base = 10 );
	BasicString & concat( const long long int & ll, unsigned int base = 10 );
	BasicString & concat( const unsigned long long int & ull, unsigned int base = 10 );

	///@brief				Concat a Float to this String.
	///@param	d		 	The Float.
	///@param	precision	The number of decimals to be displayed.
	///@param	base	 	The base.
	///@returns				Reference to this.
	BasicString & concat( const double & d, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	BasicString & concat( const float & f, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );



	BasicString& concatFill( const BasicString<T>& str, const Size& fillNb, const T& fillChar = T( ' ' ) );

	template<typename C>
	BasicString& concatFill( const BasicString<C>& str, const Size& fillNb, const T& fillChar = T( ' ' ) );

	template<typename C>
	BasicString& concatFill( const C* buffer, const Size& bufferSize, const Size& fillNb, const T& fillChar = T( ' ' ) );

	template<typename C>
	BasicString& concatFill( C* const& buffer, const Size& fillNb, const T& fillChar = T( ' ' ) );

	template<typename C, size_t N>
	BasicString& concatFill( const C( &str )[ N ], const Size& fillNb, const T& fillChar = T( ' ' ) );

	///@brief	Concatenate the number and fill the first characters to have at least the specified number.
	///@param 	uc			Number.
	///@param 	fillNb  	Characters number to be concatenated.
	///@param 	fillChar	(Optional) The fill character.
	///@param 	base		(Optional) The base.
	///@returns	A reference to this.
	BasicString & concatFill( const unsigned char & uc, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const unsigned short & us, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const int & i, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const unsigned int & ui, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const long int & l, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const unsigned long int & ul, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const long long int & ll, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString & concatFill( const unsigned long long int & ull, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );

	///@brief	Concatenate the number and fill the first characters to have at least the specified number.
	///@param 	d			Number.
	///@param 	fillNb  	Characters number to be concatenated.
	///@param 	fillChar	(Optional) The fill character.
	///@param	precision	(Optional) The precision.
	///@param 	base		(Optional) The base.
	///@returns	A reference to this.
	// BasicString & concatFill( const double & d, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	///@brief	Concatenate the number and fill the first characters to have at least the specified number.
	///@param 	f			Number.
	///@param 	fillNb  	Characters number to be concatenated.
	///@param 	fillChar	(Optional) The fill character.
	///@param	precision	(Optional) The precision.
	///@param 	base		(Optional) The base.
	///@returns	A reference to this.
	// BasicString & concatFill( const float & f, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );

	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	void copy(const BasicString<T>::Iterator* itP, const EndFunc& endFunc = BasicString<T>::IS_END_SENTINEL);

	/************************************************************************/
	/* toCString()                                                          */
	///@brief			Convert a character into a String.
	///@tparam	C		Character Type.
	///@param 		  	c	  	Character.
	///@param [in,out]	The buffer to fill with the conversion.
	///@returns			Number of characters written.
	template<typename C>
	static Size toCString( const C & c, T * buffer );
	///@brief			Convert a character into a String.
	///@param 		  	c	  	Character.
	///@param [in,out]	The buffer to fill with the conversion.
	///@returns			Number of characters written.
	static Size toCString( const char & c, T * buffer );
	///@brief			Convert a character into a String.
	///@param 		  	c	  	Character.
	///@param [in,out]	The buffer to fill with the conversion.
	///@returns			Number of characters written.
	static Size toCString( const wchar_t & c, T * buffer );


	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( unsigned char number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( unsigned short number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( unsigned int  number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( int number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( unsigned long int number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Value to converted to a String.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( long long int number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Value to converted to a String.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( unsigned long long int number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Base	Type of the base.
	///@param 		  	number	Value to converted to a String.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCString( long int number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param 		  	number	Value to converted to a String.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// static Size toCString( double number, T * buffer );

	///@brief		Converts this object to a c string
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param 		  	number	Value to converted to a String.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Precision = DefaultPrecisionFloat, unsigned int Base = 10>
	// static Size toCString( float number, T * buffer );


	///@brief			Converts a Number to a String.
	///@param 		  	number	Number to be converted.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@param 		  	base  	The base.
	///@returns			Number of characters written.
	static Size toCString( unsigned char number, T * buffer, unsigned int base = 10 );
	static Size toCString( unsigned char number, T ** buffer, unsigned int base = 10 );
	static Size toCString( unsigned short number, T * buffer, unsigned int base = 10 );
	static Size toCString( unsigned short number, T ** buffer, unsigned int base = 10 );
	static Size toCString( unsigned int  number, T * buffer, unsigned int base = 10 );
	static Size toCString( unsigned int  number, T ** buffer, unsigned int base = 10 );
	static Size toCString( int number, T * buffer, unsigned int base = 10 );
	static Size toCString( int number, T ** buffer, unsigned int base = 10 );
	static Size toCString( unsigned long int number, T * buffer, unsigned int base = 10 );
	static Size toCString( unsigned long int number, T ** buffer, unsigned int base = 10 );
	static Size toCString( long long int number, T * buffer, unsigned int base = 10 );
	static Size toCString( long long int number, T ** buffer, unsigned int base = 10 );
	static Size toCString( unsigned long long int number, T * buffer, unsigned int base = 10 );
	static Size toCString( unsigned long long int number, T ** buffer, unsigned int base = 10 );
	static Size toCString( long int number, T * buffer, unsigned int base = 10 );
	static Size toCString( long int number, T ** buffer, unsigned int base = 10 );

	///@brief			Converts a Number to a String.
	///@param 		  	number	Number to be converted.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@param			precision	The number of decimals.
	///@param 		  	base  	The base.
	///@returns			Number of characters written.
	static Size toCString( double number, T * buffer, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	static Size toCString( double number, T ** buffer, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	static Size toCString( float number, T * buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );
	static Size toCString( float number, T ** buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );

	///@brief				Write in the buffer a value representing a bool
	///@param 		  	b	  	Value to converted to a String.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	static Size toCString( bool b, T * buffer );
	static Size toCString( bool b, T ** buffer );

	///@brief			Write in the buffer a value representing a Math::Compare::Value
	///@param 		  	compareValue	  	Value to converted to a String.
	///@param [in,out]	buffer				Buffer where to write
	///@returns			Number of characters written.
	static Size toCString(const typename Math::Compare::Value& compareValue, T* buffer);
	static Size toCString( const typename Math::Compare::Value & compareValue, T ** buffer );


	/************************************************************************/
	/* ToCString() without adding sentinel                                  */
	///@brief		Convert a character to a String without adding the sentinel.
	///@tparam	C	Character Type.
	///@param 		  	c	  	Character.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@returns			Number of characters written.
	template<typename C>
	static Size toCStringWOS( const C & c, T * buffer );
	static Size toCStringWOS( const char & c, T * buffer );
	static Size toCStringWOS( const wchar_t & c, T * buffer );


	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( unsigned char number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( unsigned short number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( unsigned int  number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( int number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( unsigned long int number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( long long int number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( unsigned long long int number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Base = 10>
	// static Size toCStringWOS( long int number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// static Size toCStringWOS( double number, T * buffer );

	///@brief		Converts this object to a c string whithout \0
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	// template<unsigned int Precision = DefaultPrecisionFloat, unsigned int Base = 10>
	// static Size toCStringWOS( float number, T * buffer );


	///@brief			Converts a Number to a String without adding the sentinel.
	///@param 		  	number	Number to be converted.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@param 		  	base  	The base.
	///@returns			Number of characters written.
	static Size toCStringWOS( unsigned char number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned char number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned short number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned short number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned int  number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned int  number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( int number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( int number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned long int number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned long int number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( long long int number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( long long int number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned long long int number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( unsigned long long int number, T ** buffer, unsigned int base = 10 );
	static Size toCStringWOS( long int number, T * buffer, unsigned int base = 10 );
	static Size toCStringWOS( long int number, T ** buffer, unsigned int base = 10 );

	///@brief			Converts a Number to a String without adding the sentinel.
	///@param 		  	number	Number to be converted.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@param			precision	The number of decimals.
	///@param 		  	base  	The base.
	///@returns			Number of characters written.
	static Size toCStringWOS( double number, T * buffer, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	static Size toCStringWOS( double number, T ** buffer, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	static Size toCStringWOS( float number, T * buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );
	static Size toCStringWOS( float number, T ** buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );

	///@brief		Converts this object to a c string whithout \0
	///@param 		  	b	  	True to b.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns			Number of characters written.
	static Size toCStringWOS( bool b, T * buffer );
	static Size toCStringWOS( bool b, T ** buffer );


	///@brief			Write in the buffer a value representing a Math::Compare::Value without \0
	///@param 		  	compareValue	  	Value to converted to a String.
	///@param [in,out]	buffer				Buffer where to write
	///@returns			Number of characters written.
	static Size toCStringWOS(const typename Math::Compare::Value& compareValue, T* buffer);
	static Size toCStringWOS( const typename Math::Compare::Value & compareValue, T ** buffer );



	///@brief			Converts a Number to a String without adding the sentinel and filling for AT LEAST the fillNb number of characters.
	///@param 		  	number	Number to be converted.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@param 	fillNb  	Characters number to be concatenated.
	///@param 	fillChar	(Optional) The fill character.
	///@param 		  	base  	The base.
	///@returns			Number of characters written.
	static Size toCStringWOSFill( unsigned char number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned char number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned short number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned short number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned int  number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned int  number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( int number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( int number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned long int number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned long int number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( long long int number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( long long int number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned long long int number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( unsigned long long int number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( long int number, T * buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	static Size toCStringWOSFill( long int number, T ** buffer, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );

	///@brief Write the hexadecimal 0 filled representation of a number into the buffer.
	static void toCStringHexadecimal(unsigned char uc, T ** itP);

	/************************************************************************/
	/* From StringASCII to number                                                */
	///@brief		Converts this object to a character
	///@tparam	Base	Type of the base.
	///@returns	This object as a char.
	// template<unsigned int Base = 10>
	// char toChar() const;

	///@brief		Converts this object to an int
	///@tparam	Base	Type of the base.
	///@returns	This object as an int.
	// template<unsigned int Base = 10>
	// int toInt() const;

	///@brief		Converts this object to a short
	///@tparam	Base	Type of the base.
	///@returns	This object as a short.
	// template<unsigned int Base = 10>
	// short toShort() const;

	///@brief		Converts this object to a long int
	///@tparam	Base	Type of the base.
	///@returns	This object as a long int.
	// template<unsigned int Base = 10>
	// long int toLong() const;

	///@brief		Converts this object to a long int
	///@tparam	Base	Type of the base.
	///@returns	This object as a long int.
	// template<unsigned int Base = 10>
	// long long int toLongLong() const;

	///@brief		Converts this object to an u character
	///@tparam	Base	Type of the base.
	///@returns	This object as a char.
	// template<unsigned int Base = 10>
	// unsigned char toUChar() const;

	///@brief		Converts this object to an u int
	///@tparam	Base	Type of the base.
	///@returns	This object as an int.
	// template<unsigned int Base = 10>
	// unsigned int toUInt() const;

	///@brief		Converts this object to an u short
	///@tparam	Base	Type of the base.
	///@returns	This object as a short.
	// template<unsigned int Base = 10>
	// unsigned short toUShort() const;

	///@brief		Converts this object to an u long int
	///@tparam	Base	Type of the base.
	///@returns	This object as a long int.
	// template<unsigned int Base = 10>
	// unsigned long int toULong() const;

	///@brief		Converts this object to an u long int
	///@tparam	Base	Type of the base.
	///@returns	This object as a long int.
	// template<unsigned int Base = 10>
	// unsigned long long int toULongLong() const;

	///@brief		Converts this object to a float
	///@tparam	Base	Type of the base.
	///@returns	This object as a float.
	// template<unsigned int Base = 10>
	// float toFloat() const;

	///@brief		Converts this object to a double
	///@tparam	Base	Type of the base.
	///@returns	This object as a double.
	// template<unsigned int Base = 10>
	// double toDouble() const;


	///@brief		Converts this String into a Number.
	///@param	base	The base.
	///@returns	Number.
	char toChar( unsigned int base = 10 ) const;
	int toInt( unsigned int base = 10 ) const;
	short toShort( unsigned int base = 10 ) const;
	long int toLong( unsigned int base = 10 ) const;
	long long int toLongLong( unsigned int base = 10 ) const;
	unsigned char toUChar( unsigned int base = 10 ) const;
	unsigned int toUInt( unsigned int base = 10 ) const;
	unsigned short toUShort( unsigned int base = 10 ) const;
	unsigned long int toULong( unsigned int base = 10 ) const;
	unsigned long long int toULongLong( unsigned int base = 10 ) const;

	///@brief		Converts this String into a Number.
	///@param	base	The base.
	///@returns	Number.
	float toFloat( unsigned int base = 10 ) const;
	double toDouble( unsigned int base = 10 ) const;

	bool toBool() const;

	///@brief	Try to convert the String into the type C. Works only with native types.
	///			Null strings will return 0 for Numbers and false for bool.
	template<typename C>
	C fromString() const;


	/************************************************************************/
	/* FromCString()                                                        */
	///@brief		Converts a buffer to a character
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a char.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static char toChar( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static char toChar( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an int
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as an int.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static int toInt( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static int toInt( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to a short
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a short.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static short toShort( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static short toShort( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to a long int
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a long int.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long int toLong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long int toLong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to a long int
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a long int.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long long int toLongLong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static long long int toLongLong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an u character
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a char.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned char toUChar( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned char toUChar( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an u int
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as an int.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned int toUInt( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned int toUInt( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an u short
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a short.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned short toUShort( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned short toUShort( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an u long int
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a long int.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long int toULong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long int toULong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an u long int
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a long int.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long long int toULongLong( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static unsigned long long int toULongLong( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to a float
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a float.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static float toFloat( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static float toFloat( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to a double
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a double.
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static double toDouble( const T * buffer, const EndFunc & endFunc = IS_END_SENTINEL );
	// template<unsigned int Base = 10, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static double toDouble( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );


	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static BasicString<T> toString(const T* it, const EndFunc& endFunc = IS_END_SENTINEL);
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static BasicString<T> toString(const T** it, const EndFunc& endFunc = IS_END_SENTINEL);

	///@brief		Converts a String from a buffer into a Number.
	///@tparam	EndFunc	Functor type to detect end.
	///@param [in,out]	buffer	Buffer to be read.
	///@param 		  	base  	The base.
	///@param	endFunc	Functor to detect end.
	///@returns	Number.
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static char toChar( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static char toChar( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static int toInt( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static int toInt( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static short toShort( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static short toShort( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long int toLong( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long int toLong( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long long int toLongLong( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static long long int toLongLong( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned char toUChar( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned char toUChar( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned int toUInt( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned int toUInt( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned short toUShort( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned short toUShort( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long int toULong( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long int toULong( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long long int toULongLong( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long long int toULongLong( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a String from a buffer into a Number.
	///@tparam	EndFunc	Functor type to detect end.
	///@param [in,out]	buffer	Buffer to be read.
	///@param 		  	base  	The base.
	///@param	endFunc	Functor to detect end.
	///@returns	Number.
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static float toFloat( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static float toFloat( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static double toDouble( const T * it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static double toDouble( const T ** it, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static double toBool(const T* it, const EndFunc& endFunc = IS_END_SENTINEL);
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static double toBool(const T** it, const EndFunc& endFunc = IS_END_SENTINEL);

	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static C fromString(const T* it, const EndFunc& endFunc = IS_END_SENTINEL);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static C fromString(const T** it, const EndFunc& endFunc = IS_END_SENTINEL);


	/************************************************************************/
	/* Logical                                                              */
	///@brief		Inequality operator
	///@param	text	The text.
	///@returns	True if the parameters are not considered equivalent.
	bool operator!=( const BasicString<T> & text ) const;
	///@brief		Equality operator
	///@param	text	The text.
	///@returns	True if the parameters are considered equivalent.
	bool operator==( const BasicString<T> & text ) const;
	///@brief		Greater-than comparison operator
	///@param	text	The text.
	///@returns	True if the first parameter is greater than to the second.
	bool operator>( const BasicString<T> & text ) const;
	///@brief		Less-than comparison operator
	///@param	text	The text.
	///@returns	True if the first parameter is less than the second.
	bool operator<( const BasicString<T> & text ) const;
	///@brief		Greater-than-or-equal comparison operator
	///@param	text	The text.
	///@returns	True if the first parameter is greater than or equal to the second.
	bool operator>=( const BasicString<T> & text ) const;

	bool operator<=( const BasicString<T> & text ) const;

	///@brief		Inequality operator
	///@param	text	The text.
	///@returns	True if the parameters are not considered equivalent.
	bool operator!=( const T & text ) const;
	///@brief		Equality operator
	///@param	text	The text.
	///@returns	True if the parameters are considered equivalent.
	bool operator==( const T & text ) const;
	///@brief		Greater-than comparison operator
	///@param	text	The text.
	///@returns	True if the first parameter is greater than to the second.
	bool operator>( const T & text ) const;
	///@brief		Less-than comparison operator
	///@param	text	The text.
	///@returns	True if the first parameter is less than the second.
	bool operator<( const T & text ) const;
	///@brief		Greater-than-or-equal comparison operator
	///@param	text	The text.
	///@returns	True if the first parameter is greater than or equal to the second.
	bool operator>=( const T & text ) const;

	bool operator<=( const T & text ) const;


	/************************************************************************/
	/* To StringASCII                                                            */
	///@brief	Simple redirection for overload purposes.
	///@param	str	BasicString<T> to be returned.
	///@return	str
	static const BasicString<T>& toString(const BasicString<T>& str);

	///@brief		Convert this object into a string representation
	///@param	c	A T to process.
	///@returns	A BasicString<T> that represents this object.
	static BasicString<T> toString( const T & c );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned char number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned short number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned int number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( int number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned long int number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( long long int number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( unsigned long long int number );

	///@brief		Convert this object into a string representation
	///@tparam	Base	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Base = 10>
	// static BasicString<T> toString( long int number );

	///@brief		Convert this object into a string representation
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Precision = 10, unsigned int Base = 10>
	// static BasicString<T> toString( double number );

	///@brief		Convert this object into a string representation
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param	number	Number of.
	///@returns	Number as a BasicString<T>
	// template<unsigned int Precision = DefaultPrecisionFloat, unsigned int Base = 10>
	// static BasicString<T> toString( float number );



	///@brief		Convert a Number into a String.
	///@param	number	Number to be converted.
	///@param	base  	The base.
	///@returns	A BasicString<T> that represents the Number.
	static BasicString<T> toString( unsigned char number, unsigned int base = 10 );
	static BasicString<T> toString( unsigned short number, unsigned int base = 10 );
	static BasicString<T> toString( unsigned int number, unsigned int base = 10 );
	static BasicString<T> toString( int number, unsigned int base = 10 );
	static BasicString<T> toString( unsigned long int number, unsigned int base = 10 );
	static BasicString<T> toString( long long int number, unsigned int base = 10 );
	static BasicString<T> toString( unsigned long long int number, unsigned int base = 10 );
	static BasicString<T> toString( long int number, unsigned int base = 10 );
	///@brief		Convert a Number into a String.
	///@param	number	Number to be converted.
	///@param	precision	Number of decimals.
	///@param	base  	The base.
	///@returns	A BasicString<T> that represents the Number.
	static BasicString<T> toString( double number, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	static BasicString<T> toString( float number, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );

	///@brief		Convert this object into a string representation
	///@param	b	True to b.
	///@returns	A BasicString<T> that represents this object.
	static BasicString<T> toString( bool b );



	static BasicString<T> toStringFill( unsigned char number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( unsigned short number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( unsigned int number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( int number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( unsigned long int number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( long long int number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( unsigned long long int number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	static BasicString<T> toStringFill( long int number, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );

	/************************************************************************/
	/* Others                                                               */
	///@brief		Splits the given delimiter
	///@param	delimiter	The delimiter.
	///@returns	A Vector<BasicString<T>>
	Vector<BasicString<T>> split( const T & delimiter ) const;
	///@brief		Query if this object is numeric
	///@returns	True if numeric, false if not.
	bool isNumeric() const;

	///@brief		Resize the string
	///@param	newSize	New size of this string.
	void resize( Size newSize );

	/** @brief	. */
	using Vector<T>::getSize;

	///@brief		Gets a size
	///@param	str	The string.
	///@returns	The size.
	template<typename C>
	static Size getSize( C * const & str );

	///@brief		Gets a size
	///@param	str	The string.
	///@returns	The size.
	template<typename C, size_t N>
	static Size getSize( const C (&str)[N] );

	///@brief		Converts this object to a c string
	///@returns	This object as a const T*.
	const T * toCString() const;

	/** @brief	set the size to 0 */
	void clear();

	///@brief		Get the iterator of the first occurence of a character. May return getEnd() if nothing founded.
	///@param	c	The character to look for.
	///@returns	Iterator of the first occurence or getEnd() if nothing founded.
	typename BasicString<T>::Iterator getFirstIt( const T & c ) const;
	///@brief		Get the iterator of the last occurence of a character. May return getEnd() if nothing founded.
	///@param	c	The character to look for.
	///@returns	Iterator of the last occurence or getEnd() if nothing founded.
	typename BasicString<T>::Iterator getLastIt( const T & c ) const;

	///@brief		Get the iterator of the first occurence of a string. May return getEnd() if nothing founded.
	///@param	c	The string to look for.
	///@returns	Iterator of the first occurence or getEnd() if nothing founded.
	typename BasicString<T>::Iterator getFirstIt( const BasicString<T> & str ) const;
	///@brief		Get the iterator of the last occurence of a string. May return getEnd() if nothing founded.
	///@param	c	The string to look for.
	///@returns	Iterator of the last occurence or getEnd() if nothing founded.
	typename BasicString<T>::Iterator getLastIt( const BasicString<T> & str ) const;

	///@brief		Get the index of the first occurence of a character. May return BasicString<T>::overflow if nothing founded.
	///@param	c	The character to look for.
	///@returns	Index of the first occurence or BasicString<T>::overflow if nothing founded.
	Size getFirst( const T & c ) const;
	///@brief		Get the index of the last occurence of a character. May return BasicString<T>::overflow if nothing founded.
	///@param	c	The character to look for.
	///@returns	Index of the last occurence or BasicString<T>::overflow if nothing founded.
	Size getLast( const T & c ) const;

	///@brief		Get the index of the first occurence of a string. May return BasicString<T>::overflow if nothing founded.
	///@param	c	The string to look for.
	///@returns	Index of the first occurence or BasicString<T>::overflow if nothing founded.
	Size getFirst( const BasicString<T> & str ) const;
	///@brief		Get the index of the last occurence of a string. May return BasicString<T>::overflow if nothing founded.
	///@param	c	The string to look for.
	///@returns	Index of the last occurence or BasicString<T>::overflow if nothing founded.
	Size getLast( const BasicString<T> & str ) const;

	///@brief		Replaces
	///@param	toReplace	to replace.
	///@param	byThis   	The by this.
	void replace( const T & toReplace, const T & byThis );
	///@brief		Replaces
	///@param	toReplace	to replace.
	///@param	byThis   	The by this.
	void replace( const T & toReplace, const BasicString<T> & byThis );
	///@brief		Replaces
	///@param	toReplace	to replace.
	///@param	byThis   	The by this.
	void replace( const BasicString<T> & toReplace, const BasicString<T> & byThis );

	///@brief		Gets the directory
	///@returns	The directory.
	BasicString<T> getDirectory() const;
	///@brief		Gets file name
	///@returns	The file name.
	BasicString<T> getFileName() const;
	///@brief		Gets sub string
	///@param	index	Zero-based index of the.
	///@param	size 	The size.
	///@returns	The sub string.
	BasicString<T> getSubStr( Size index, Size size ) const;
	///@brief		Gets sub string
	///@param	beginIt	The begin iterator.
	///@param	size   	The size.
	///@returns	The sub string.
	BasicString<T> getSubStr( typename BasicString<T>::Iterator beginIt, Size size ) const;
	///@brief		Gets sub string
	///@param	beginIt	The begin iterator.
	///@param	endIt  	The end iterator.
	///@returns	The sub string.
	BasicString<T> getSubStr( typename BasicString<T>::Iterator beginIt, typename BasicString<T>::Iterator endIt ) const;

	BasicString<T> toLower() const;
	BasicString<T> toUpper() const;


	///@brief		Function to compare two elements
	///@param	x	First Element.
	///@param	y	Second Element.
	///@returns	Equal (x == y), Less (x < y) or Greater (x > y)
	static Math::Compare::Value compare( const BasicString<T> & x, const BasicString<T> & y );


	///@brief		Write this string into a file as readable (non binary)
	///@param [in,out]	stream	StreamT used to write this string.
	///@returns	boolean to know if the operation is a success of not.
	template<typename Stream>
	bool writeReadable(Stream* stream ) const;

	///@brief		read from a file stream
	///@param [in,out]	stream	stream used to read load this object.
	///@returns	boolean to know if the operation is a success of not.
	template<typename Stream>
	bool read( Stream * stream, int verbose = 0 );

	///@brief		read from a file stream
	///@param [in,out]	stream	stream used to read load this object.
	///@param 		  	size	  	Number of characters to read.
	///@returns	boolean to know if the operation is a success of not.
	template<typename Stream>
	bool read(Stream* stream, Size size );

	/************************************************************************/
	/* Some static methods                                                  */
	///@brief		Query if 'v' is numeric
	///@param	v	A BasicString<T> to process.
	///@returns	True if numeric, false if not.
	static bool isNumeric( const BasicString<T> & v );
	///@brief		Splits
	///@param	s		 	A BasicString<T> to process.
	///@param	delimiter	The delimiter.
	///@returns	A Vector<BasicString<T>>
	static Vector<BasicString<T>> split( const BasicString<T> & s, const T & delimiter );

	///@brief		Format a reference String with values. To place a variable use the character '%'. To place a '%' use the '/''%' characters.
	///@tparam	T1   	First element type.
	///@tparam	Types	Others elements.
	///@param	referenceString	The reference string.
	///@param	arg1		   	The first argument.
	///@param	args		   	Variable arguments providing the variables.
	///@returns	The formatted String.
	template<typename T1, typename... Types>
	static BasicString<T> format( const BasicString<T> & referenceString, const T1 & arg1, Types ... args );
	static BasicString<T> format( const BasicString<T> & referenceString );

	///@brief		Format a reference String with values. To place a variable use the character '%'. To place a '%' use the '/''%' characters.
	///@tparam	C		Reference string type.
	///@tparam	T1   	First element type.
	///@tparam	Types	Others elements.
	///@param	str		The reference string.
	///@param	arg1		   	The first argument.
	///@param	args		   	Variable arguments providing the variables.
	///@returns	The formatted String.
	template<typename C, typename T1, typename... Types>
	static BasicString<T> format( C * const & str, const T1 & arg1, Types ... args );
	template<typename C>
	static BasicString<T> format( C* const& str);

	///@brief		Format a reference String with values. To place a variable use the character '%'. To place a '%' use the '/''%' characters.
	///@tparam	C		Reference string type.
	///@tparam	N		Refernce string size.
	///@tparam	T1   	First element type.
	///@tparam	Types	Others elements.
	///@param	str		The reference string.
	///@param	arg1		   	The first argument.
	///@param	args		   	Variable arguments providing the variables.
	///@returns	The formatted String.
	template<typename C, size_t N, typename T1, typename... Types>
	static BasicString<T> format( const C( &str )[ N ], const T1 & arg1, Types ... args );
	template<typename C, size_t N>
	static BasicString<T> format( const C( &str )[ N ] );


	///@brief		Gets a first
	///@param	buffer	  	The buffer.
	///@param	bufferSize	Size of the buffer.
	///@param	c		  	A T to process.
	///@returns	The first.
	static Size getFirst( const T * buffer, Size bufferSize, const T & c );
	///@brief		Gets a last
	///@param	buffer	  	The buffer.
	///@param	bufferSize	Size of the buffer.
	///@param	c		  	A T to process.
	///@returns	The last.
	static Size getLast( const T * buffer, Size bufferSize, const T & c );

	///@brief		Gets a first
	///@param	buffer			The buffer.
	///@param	bufferSize  	Size of the buffer.
	///@param	toSearch		to searchI.
	///@param	toSearchSize	Size of to searchI.
	///@returns	The first.
	static Size getFirst( const T * buffer, Size bufferSize, const T * toSearch, Size toSearchSize );
	///@brief		Gets a last
	///@param	buffer			The buffer.
	///@param	bufferSize  	Size of the buffer.
	///@param	toSearch		to searchI.
	///@param	toSearchSize	Size of to searchI.
	///@returns	The last.
	static Size getLast( const T * buffer, Size bufferSize, const T * toSearch, Size toSearchSize );

	///@brief		Gets a first
	///@param	buffer	The buffer.
	///@param	c	  	A T to process.
	///@returns	The first.
	static Size getFirst( const T * buffer, const T & c );
	///@brief		Gets a last
	///@param	buffer	The buffer.
	///@param	c	  	A T to process.
	///@returns	The last.
	static Size getLast( const T * buffer, const T & c );

	///@brief		Gets a first
	///@param	buffer  	The buffer.
	///@param	toSearch	to searchI.
	///@returns	The first.
	static Size getFirst( const T * buffer, const T * toSearch );
	///@brief		Gets a last
	///@param	buffer  	The buffer.
	///@param	toSearch	to searchI.
	///@returns	The last.
	static Size getLast( const T * buffer, const T * toSearch );

	///@brief	Convert a character to a number.
	///@param 	c	The character to be converted.
	///@returns	The number.
	template<typename N = char, int nbChars = 1, int base = 10>
	static N parseNumber( const T ** c );

	using Vector<T>::copy;
	/************************************************************************/
	/* CONVERSION                                                           */
	/************************************************************************/

	///@brief Base 64 encode a binary data Vector to a BasicString<T>
	///@param dataVector Binary data Vector to be encoded.
	///@param itP Pointer to a BasicString<T> Iterator to be filled.
	///@return True if success, False otherwise.
	static bool encodeBase64(const Vector<char>& dataVector, T** itP);

	///@brief Base 64 encode a binary data Vector to a BasicString<T>
	///@param dataVector Binary data Vector to be encoded.
	///@return BasicString<T> generated.
	static BasicString<T> encodeBase64(const Vector<char>& dataVector);

	///@brief Base 64 decode a BasicString<T> to a binary data Vector.
	///@param inputStr BasicString<T> to be decoded.
	///@param itP Pointer to a binary data Vector Iterator.
	///@return True if success, False otherwise.
	static bool decodeBase64(const BasicString<T>& inputStr, char** itP);

	///@brief Base 64 decode a BasicString<T> to a binary data Vector.
	///@param inputStr BasicString<T> to be decoded.
	///@return Binary data Vector generated. 0 sized if error.
	static Vector<char> decodeBase64(const BasicString<T>& inputStr);

	///@brief Get the BasicString<T> Size of the base 64 encoding of the data Vector.
	///@param dataVector Binary data Vector to be used to compute the Size.
	///@return BasicString<T> Size.
	static Size getBase64EncodeSize(const Vector<char>& dataVector);

	///@brief Get the binary data Vector reserve Size of the base 64 decoding of the BasicString<T>. Final Size may be lower.
	///@param inputStr BasicString<T> to be used to compute the reserve Size.
	///@return Binary data Vector reserve Size.
	static Size getBase64DecodeReserveSize(const BasicString<T>& inputStr);

	///@brief	Encode a String into a HTTP URL encoded one.
	///@param	inputStr Input string to be converted.
	///@param	out outStr Pointer to the string iterator to be generated, will point to the end character.
	///@return	size of the generated string, will be at max size(inputStr) * 3. 
	static Size encodeUrl( const T * inputStr, T ** outStr );

	///@brief	Encode a String into a HTTP URL encoded one.
	///@param	inputStr Input string to be converted.
	///@return	Converted string.
	static BasicString<T> encodeUrl( const BasicString<T> & inputStr );

	///@brief	Create a new String with specials chars escaped, usefull to be formated in a quotted string in json/html/javascript...
	///@param	inputStr Input string to be converted.
	///@param	out outStr Pointer to the string iterator to be generated, will point to the end character.
	///@return	size of the generated string, will be at max size(inputStr) * 3. 
	static Size escapeSpecials( const T* inputStr, T** outStr );

	///@brief	Create a new String with specials chars escaped, usefull to be formated in a quotted string in json/html/javascript...
	///@param	inputStr Input string to be converted.
	///@return	Converted string.
	static BasicString<T> escapeSpecials( const BasicString<T>& inputStr );


	///@brief Hexadecimal encode a binary data Vector to a BasicString<T>
	///@param dataVector Binary data Vector to be encoded.
	///@param itP Pointer to a BasicString<T> Iterator to be filled.
	///@return True if success, False otherwise.
	static bool encodeHexadecimal(const Vector<char>& dataVector, T** itP);

	///@brief Hexadecimal encode a binary data Vector to a BasicString<T>
	///@param dataVector Binary data Vector to be encoded.
	///@return BasicString<T> generated.
	static BasicString<T> encodeHexadecimal(const Vector<char>& dataVector);

	///@brief Hexadecimal decode a BasicString<T> to a binary data Vector.
	///@param inputStr BasicString<T> to be decoded.
	///@param itP Pointer to a binary data Vector Iterator.
	///@return True if success, False otherwise.
	static bool decodeHexadecimal(const BasicString<T>& inputStr, char** itP);

	///@brief Hexadecimal decode a BasicString<T> to a binary data Vector.
	///@param inputStr BasicString<T> to be decoded.
	///@return Binary data Vector generated. 0 sized if error.
	static Vector<char> decodeHexadecimal(const BasicString<T>& inputStr);




	///@brief Table of characters used in base 64 encoding.
	static const T base64CharTable[ 64 ];

	/** @brief	The numbers[ 16] */
	static const T numbers[ 16 ];
	/** @brief	The null */
	static const BasicString<T> null;

	/** Default EndFunc */
	static const IsEndSentinel IS_END_SENTINEL;

protected:
	///@brief		Constructor
	///@param	parameter1	The first parameter.
	BasicString( typename BasicString<T>::protectedCtor);

	/************************************************************************/
	/* concat() without adding sentinel                                     */
	BasicString & _concatWOS( const BasicString<T> & str );

	template<typename C>
	BasicString & _concatWOS( const BasicString<C> & str );

	template<typename C>
	BasicString & _concatWOS( C * const & buffer, const Size & bufferSize );

	template<typename C>
	BasicString & _concatWOS( C * const & buffer);

	template<typename C, size_t N>
	BasicString & _concatWOS( const C (& str)[N] );

	template<typename C>
	BasicString& _concatWOS( const Optional<C> & o );

	BasicString & _concatWOS( const bool & b );
	BasicString & _concatWOS( const char & c );
	BasicString & _concatWOS( const wchar_t & c );
	BasicString & _concatWOS( const unsigned char & uc, unsigned int base = 10 );
	BasicString & _concatWOS( const unsigned short & us, unsigned int base = 10 );
	BasicString & _concatWOS( const int & i, unsigned int base = 10 );
	BasicString & _concatWOS( const unsigned int & ui, unsigned int base = 10 );
	BasicString & _concatWOS( const long int & l, unsigned int base = 10 );
	BasicString & _concatWOS( const unsigned long int & ul, unsigned int base = 10 );
	BasicString & _concatWOS( const long long int & ll, unsigned int base = 10 );
	BasicString & _concatWOS( const unsigned long long int & ull, unsigned int base = 10 );
	BasicString & _concatWOS( const double & d, unsigned int precision = DefaultPrecisionDouble, unsigned int base = 10 );
	BasicString & _concatWOS( const float & f, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );


	template<typename C>
	BasicString& _concatFillWOS( const BasicString<C> & str, const Size& fillNb, const T& fillChar = T( ' ' ) );
	template<typename C>
	BasicString& _concatFillWOS( C* const& buffer, const Size& bufferSize, const Size& fillNb, const T& fillChar = T( ' ' ) );
	template<typename C>
	BasicString& _concatFillWOS( C* const& buffer, const Size& fillNb, const T& fillChar = T( ' ' ) );
	template<typename C, size_t N>
	BasicString& _concatFillWOS( const C( &str )[ N ], const Size& fillNb, const T& fillChar = T( ' ' ) );

	BasicString& _concatFillWOS( const unsigned char& uc, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const unsigned short& us, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const int& i, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const unsigned int& ui, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const long int& l, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const unsigned long int& ul, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const long long int& ll, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );
	BasicString& _concatFillWOS( const unsigned long long int& ull, const Size& fillNb, const T& fillChar = T( ' ' ), unsigned int base = 10 );


private:

	char _fromString(const char*) const;
	int _fromString(const int*) const;
	short _fromString(const short*) const;
	long int _fromString(const long int*) const;
	long long int _fromString(const long long int*) const;
	unsigned char _fromString(const unsigned char*) const;
	unsigned int _fromString(const unsigned int*) const;
	unsigned short _fromString(const unsigned short*) const;
	unsigned long int _fromString(const unsigned long int*) const;
	unsigned long long int _fromString(const unsigned long long int*) const;
	float _fromString(const float*) const;
	double _fromString(const double*) const;
	bool _fromString(const bool*) const;
	const BasicString<T>& _fromString(...) const;

	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static char _fromString(const T** it, const EndFunc& endFunc, const char*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static int _fromString(const T** it, const EndFunc& endFunc, const int*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static short _fromString(const T** it, const EndFunc& endFunc, const short*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static long int _fromString(const T** it, const EndFunc& endFunc, const long int*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static long long int _fromString(const T** it, const EndFunc& endFunc, const long long int*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned char _fromString(const T** it, const EndFunc& endFunc, const unsigned char*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned int _fromString(const T** it, const EndFunc& endFunc, const unsigned int*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned short _fromString(const T** it, const EndFunc& endFunc, const unsigned short*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long int _fromString(const T** it, const EndFunc& endFunc, const unsigned long int*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static unsigned long long int _fromString(const T** it, const EndFunc& endFunc, const unsigned long long int*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static float _fromString(const T** it, const EndFunc& endFunc, const float*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static double _fromString(const T** it, const EndFunc& endFunc, const double*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static bool _fromString(const T** it, const EndFunc& endFunc, const bool*);
	template<typename C, typename EndFunc = BasicString<T>::IsEndSentinel>
	static T* _fromString(const T** it, const EndFunc& endFunc, ...);

	///@brief		Formats
	///@tparam	C		Reference string type.
	///@tparam	T1   	First element type.
	///@tparam	Types	Others elements.
	///@param	referenceStringBegin	Pointer to the reference string begin.
	///@param	referenceStringEnd		Pointer to the reference string end.
	///@param	arg1		   	The first argument.
	///@param	args		   	Variable arguments providing the variables.
	///@returns	The formatted value.
	template<typename C, typename T1, typename... Types>
	static BasicString<T> _format( const C * referenceStringBegin, const C * referenceStringEnd, const T1 & arg1, Types ... args );

	///@brief		Formats
	///@tparam	T1   	Generic type parameter.
	///@tparam	Types	Type of the types.
	///@param 		  	referenceStringBegin	The reference string begin.
	///@param 		  	referenceStringEnd  	The reference string end.
	///@param [in,out]	newString				If non-null, the new string.
	///@param 		  	arg1					The first argument.
	///@param 		  	vars					Variable arguments providing the variables.
	template<typename C, typename T1, typename... Types>
	static void __format( const C * referenceStringBegin, const C * referenceStringEnd, BasicString<T> * newString, const T1 & arg1, Types ... args );

	///@brief		Formats
	///@param 		  	referenceStringBegin	The reference string begin.
	///@param 		  	referenceStringEnd  	The reference string end.
	///@param [in,out]	newString				If non-null, the new string.
	template<typename C>
	static void __format( const C * referenceStringBegin, const C * referenceStringEnd, BasicString<T> * newString );

	///@brief		Concatenate integer
	///@tparam	Type	Type of the type.
	///@tparam	Base	Type of the base.
	///@param	i	Integer to be concatenated.
	///@returns	A reference to a BasicString.
	// template<typename Type, unsigned int Base = 10>
	// BasicString & _concatInteger( const Type & i );

	///@brief		Concatenate integer
	///@tparam	Type	Type of the type.
	///@param	i	Integer to be concatenated.
	///@param	base	The base.
	///@returns	A reference to a BasicString.
	template<typename Type>
	BasicString & _concatInteger( const Type & i, unsigned int base = 10 );

	///@brief		Concatenate integer and fill for adding at least "FillNb" number of chars.
	///@tparam	Type	Type.
	///@param	i	Integer to be concatenated.
	///@tparam	fillNb	Minimal number of chars to be added.
	///@param	fillChar	Chars to be added as a filler.
	///@param	base	The base.
	///@returns	A reference to a BasicString.
	template<typename Type>
	BasicString & _concatFillIntegerWOS( const Type & i, const Size & fillNb, const T & fillChar, unsigned int base = 10 );

	template<typename C>
	BasicString& _concatFillStringWOS( const C* buffer, const Size bufferSize, const Size& fillNb, const T& fillChar );


	///@brief		Concatenate float
	///@tparam	Type	 	Type of the type.
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param	f	Float to be concatenated.
	///@returns	A reference to a BasicString.
	// template<typename Type, unsigned int Precision = DefaultPrecisionFloat, unsigned int Base = 10>
	// BasicString & _concatFloat( const Type & f );

	///@brief		Concatenate float
	///@tparam	Type	Type of the type.
	///@param	f	Float to be concatenated.
	///@param	precision	The precision.
	///@param	base	 	The base.
	///@returns	A reference to a BasicString.
	template<typename Type>
	BasicString & _concatFloat( const Type & f, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );



	///@brief		Concatenate integer whithout \0
	///@tparam	Type	Type of the type.
	///@tparam	Base	Type of the base.
	///@param	i	Zero-based index of the.
	///@returns	A reference to a BasicString.
	// template<typename Type, unsigned int Base = 10>
	// BasicString & _concatIntegerWOS( const Type & i );

	///@brief		Concatenate integer whithout \0
	///@tparam	Type	Type of the type.
	///@param	i   	Zero-based index of the.
	///@param	base	The base.
	///@returns	A reference to a BasicString.
	template<typename Type>
	BasicString & _concatIntegerWOS( const Type & i, unsigned int base = 10 );

	///@brief		Concatenate float whithout \0
	///@tparam	Type	 	Type of the type.
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param	f	A Type to process.
	///@returns	A reference to a BasicString.
	// template<typename Type, unsigned int Precision = DefaultPrecisionFloat, unsigned int Base = 10>
	// BasicString & _concatFloatWOS( const Type & f );

	///@brief		Concatenate float whithout \0
	///@tparam	Type	Type of the type.
	///@param	f		 	A Type to process.
	///@param	precision	The precision.
	///@param	base	 	The base.
	///@returns	A reference to a BasicString.
	template<typename Type>
	BasicString & _concatFloatWOS( const Type & f, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );




	///@brief		Converts a buffer to a float
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Type	Return type.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a Type.
	// template<typename Type, unsigned int Base, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static Type _toFloat( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to a signed integer
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Type	Return type.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a Type.
	// template<typename Type, unsigned int Base, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static Type _toSignedInteger( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts a buffer to an unsigned integer
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Type	Return type.
	///@tparam	Base	Type of the base.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param	endFunc	Functor to detect end.
	///@returns	Buffer as a Type.
	// template<typename Type, unsigned int Base, typename EndFunc = BasicString<T>::IsEndSentinel>
	// static Type _toUnsignedInteger( const T ** buffer, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts this object to a String
	///@tparam	EndFunc	Functor type to detect end.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@param	endFunc	Functor to detect end.
	///@returns	The given data converted to a Type.
	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static BasicString<T> _toString(const T** itP, const EndFunc& endFunc = IS_END_SENTINEL);

	///@brief		Converts this object to a float
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Type	Return type.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@param	endFunc	Functor to detect end.
	///@returns	The given data converted to a Type.
	template<typename Type, typename EndFunc = BasicString<T>::IsEndSentinel>
	static Type _toFloat( const T ** itP, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts this object to a signed integer
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Type	Return type.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@param	endFunc	Functor to detect end.
	///@returns	The given data converted to a Type.
	template<typename Type, typename EndFunc = BasicString<T>::IsEndSentinel>
	static Type _toSignedInteger( const T ** itP, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	///@brief		Converts this object to an unsigned integer
	///@tparam	EndFunc	Functor type to detect end.
	///@tparam	Type	Return type.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@param	endFunc	Functor to detect end.
	///@returns	The given data converted to a Type.
	template<typename Type, typename EndFunc = BasicString<T>::IsEndSentinel>
	static Type _toUnsignedInteger( const T ** itP, unsigned int base = 10, const EndFunc & endFunc = IS_END_SENTINEL );

	template<typename EndFunc = BasicString<T>::IsEndSentinel>
	static bool _toBool(const T** itP, const EndFunc& endFunc = IS_END_SENTINEL);



	///@brief		Convert i 2 string
	///@tparam	Type	Type of the type.
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns	The i converted 2 string.
	// template<typename Type, unsigned int Base>
	// static Size _convertI2String( Type number, T * buffer );

	///@brief		Convert i 2 string
	///@tparam	Type	Type of the type.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@returns	The i converted 2 string.
	template< typename Type>
	static Size _convertI2String( Type number, T ** buffer, unsigned int base = 10 );

	///@brief		Convert user interface 2 string
	///@tparam	Type	Type of the type.
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns	The user converted interface 2 string.
	// template<typename Type, unsigned int Base>
	// static Size _convertUI2String( Type number, T * buffer );

	///@brief		Convert user interface 2 string
	///@tparam	Type	Type of the type.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@returns	The user converted interface 2 string.
	template<typename Type>
	static Size _convertUI2String( Type number, T ** buffer, unsigned int base = 10 );

	///@brief		Convert float 2 string
	///@tparam	Type	 	Type of the type.
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns	The float converted 2 string.
	// template<typename Type, unsigned int Precision = 10, unsigned int Base>
	// static Size _convertFloat2String( Type number, T * buffer );

	///@brief		Convert float 2 string
	///@tparam	Type	Type of the type.
	///@param 		  	number   	Number of.
	///@param [in,out]	buffer   	If non-null, the buffer.
	///@param 		  	precision	The precision.
	///@param 		  	base	 	The base.
	///@returns	The float converted 2 string.
	template<typename Type>
	static Size _convertFloat2String( Type number, T ** buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );




	///@brief		Convert i 2 string whithout \0
	///@tparam	Type	Type of the type.
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns	The i converted 2 string whithout \0.
	// template<typename Type, unsigned int Base>
	// static Size _convertI2StringWOS( Type number, T * buffer );

	///@brief		Convert i 2 string whithout \0
	///@tparam	Type	Type of the type.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@returns	The i converted 2 string whithout \0.
	template< typename Type>
	static Size _convertI2StringWOS( Type number, T ** buffer, unsigned int base = 10 );
	template< typename Type>
	static void __convertI2StringWOS( Type number, T ** buffer, unsigned int base = 10 );

	///@brief		Convert user interface 2 string whithout \0
	///@tparam	Type	Type of the type.
	///@tparam	Base	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns	The user converted interface 2 string whithout \0.
	// template<typename Type, unsigned int Base>
	// static Size _convertUI2StringWOS( Type number, T * buffer );

	///@brief		Convert user interface 2 string whithout \0
	///@tparam	Type	Type of the type.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@param 		  	base  	The base.
	///@returns	The user converted interface 2 string whithout \0.
	template<typename Type>
	static Size _convertUI2StringWOS( Type number, T ** buffer, unsigned int base = 10 );
	template<typename Type>
	static void __convertUI2StringWOS( Type number, T ** buffer, unsigned int base = 10 );

	///@brief		Convert float 2 string whithout \0
	///@tparam	Type	 	Type of the type.
	///@tparam	Precision	Type of the precision.
	///@tparam	Base	 	Type of the base.
	///@param 		  	number	Number of.
	///@param [in,out]	buffer	If non-null, the buffer.
	///@returns	The float converted 2 string whithout \0.
	// template<typename Type, unsigned int Precision = 10, unsigned int Base>
	// static Size _convertFloat2StringWOS( Type number, T * buffer );

	///@brief		Convert float 2 string whithout \0
	///@tparam	Type	Type of the type.
	///@param 		  	number   	Number of.
	///@param [in,out]	buffer   	If non-null, the buffer.
	///@param 		  	precision	The precision.
	///@param 		  	base	 	The base.
	///@returns	The float converted 2 string whithout \0.
	template<typename Type>
	static Size _convertFloat2StringWOS( Type number, T ** buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );
	template<typename Type>
	static void __convertFloat2StringWOS( Type number, T ** buffer, unsigned int precision = DefaultPrecisionFloat, unsigned int base = 10 );


	///@brief			Converts a Number to a String without adding the sentinel and filling for AT LEAST the fillNb number of characters.
	///@template		Number Type.
	///@param 		  	number	Number to be converted.
	///@param [in,out]	buffer	Buffer to be filled with the converted value.
	///@param 	fillNb  	Characters number to be concatenated.
	///@param 	fillChar	(Optional) The fill character.
	///@param 		  	base  	The base.
	///@returns			Number of characters written.
	template<typename Type>
	static Size _convertI2StringWOSFill( Type number, T ** bufferP, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	template<typename Type>
	static Size _convertUI2StringWOSFill( Type number, T ** bufferP, const Size & fillNb, const T & fillChar = T( ' ' ), unsigned int base = 10 );
	


	///@brief Copy a static array.
	///@template N sourceBuffer size.
	///@param destinationBuffer Buffer Pointer to the buffer where to copy the data.
	///@param sourceBuffer Buffer from where to copy.
	///@return Number of elements copied
	template<size_t N>
	static Size copy( T ** destinationBuffer, const T( &sourceBuffer )[ N ] );


	///@brief Get the size of an integer as a number of characters
	///@template Type Integer type.
	///@param i Integer to be counted.
	///@param base The base used for the conversion to String.
	///@return Number of characters.
	template<typename Type>
	static Size _getILength(Type i, unsigned int base);

	///@brief Get the size of an positive integer as a number of characters
	///@template Type Integer type.
	///@param i Integer to be counted.
	///@param base The base used for the conversion to String.
	///@return Number of characters.
	template<typename Type>
	static Size _getUILength( Type i, unsigned int base );

	
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
BasicString<T> & operator<<(BasicString<T> basicString, const long int & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned long int & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const long long int & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const unsigned long long int & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const double & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const float & i);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const bool & b);

template<typename T>
BasicString<T> & operator<<(BasicString<T> basicString, const T & c);





/************************************************************************/
/* OPERATOR +                                                           */
///@brief		*********************************************************************
///@param	str1	The first value.
///@param	str2	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<T> & str2 );

///@brief		Addition operator
///@param	str1	The first value.
///@param	str2	A value to add to it.
///@returns	The result of the operation.
template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<C> & str2 );

///@brief		Addition operator
///@param	str	The first value.
///@param	i  	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const int & i );

///@brief		Addition operator
///@param	i  	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const int & i, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	ui 	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned char & ui );

///@brief		Addition operator
///@param	ui 	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const unsigned char & ui, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	ui 	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned short & ui );

///@brief		Addition operator
///@param	ui 	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const unsigned short & ui, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	ui 	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned int & ui );

///@brief		Addition operator
///@param	ui 	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const unsigned int & ui, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	l  	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long int & l );

///@brief		Addition operator
///@param	l  	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const long int & l, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	ul 	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long int & ul );

///@brief		Addition operator
///@param	ul 	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const unsigned long int & ul, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	ll 	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long long int & ll );

///@brief		Addition operator
///@param	ll 	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const long long int & ll, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	ull	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long long int & ull );

///@brief		Addition operator
///@param	ull	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const unsigned long long int & ull, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	f  	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const float & f );

///@brief		Addition operator
///@param	f  	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const float & f, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	b  	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const bool & b );

///@brief		Addition operator
///@param	b  	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const bool & b, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	d  	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const double & d );

///@brief		Addition operator
///@param	d  	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const double & d, const BasicString<T> & str );

///@brief		Addition operator
///@param	str	The first value.
///@param	c  	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const T & c );

///@brief		Addition operator
///@param	c  	The first value.
///@param	str	A value to add to it.
///@returns	The result of the operation.
template<typename T>
BasicString<T> operator+( const T & c, const BasicString<T> & str );

///@brief		Addition operator
///@param	str1	The first value.
///@param	str2	A value to add to it.
///@returns	The result of the operation.
template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, C * const & str2);

///@brief		Addition operator
///@param	str1	The first value.
///@param	str2	A value to add to it.
///@returns	The result of the operation.
template<typename T, typename C>
BasicString<T> operator+( C * const & str1, const BasicString<T> & str2 );


///@brief		Addition operator
///@param	str1	The first value.
///@param	str2	A value to add to it.
///@returns	The result of the operation.
template<typename T, typename C, size_t N>
BasicString<T> operator+( const C (&str1)[N], const BasicString<T> & str2 );

///@brief		Addition operator
///@param	str1	The first value.
///@param	str2	A value to add to it.
///@returns	The result of the operation.
template<typename T, typename C, size_t N>
BasicString<T> operator+( const BasicString<T> & str1, const C (&str2)[N] );


template<typename T>
std::ostream & operator<<( std::ostream & stream, const BasicString<T> & str );

template<typename Stream, typename T>
Stream& operator<<(Stream& stream, const BasicString<T>& str);

/** @brief	Defines an alias representing an ASCII String */
typedef BasicString<char> StringASCII;
/** @brief	Defines an alias representing an UTF16 String */
typedef BasicString<wchar_t> WString;
/** @brief	Defines an alias representing an UTF32 String */
typedef BasicString<unsigned int> UTF32String;

#if defined WIN32 && defined WIN32_WSTRING
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

