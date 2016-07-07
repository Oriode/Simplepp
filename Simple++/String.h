#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include "SimpleLog.h"
#include "Vector.h"





//T = buffer type
template<typename T>
class BasicString : public Vector<T> {
public:
	BasicString();




	template<typename C>
	BasicString( const C * str );

	/*template<typename C, size_t N = 0>
	BasicString(const C(&s)[N]);*/

	template<typename C>
	BasicString( const C * str, Size size );


	template<typename C>
	BasicString( const BasicString<C> & str );

	BasicString( const BasicString & str );

	BasicString( BasicString<T> && str );


	template<typename C>
	BasicString( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );

	BasicString( const unsigned char & ui );
	BasicString( const unsigned short & ui );
	BasicString( const int & i );
	BasicString( const unsigned int & ui );
	BasicString( const long & l );
	BasicString( const unsigned long & ul );
	BasicString( const long long & ll );
	BasicString( const unsigned long long & ull );
	BasicString( const double & d );
	BasicString( const float & f );
	BasicString( const bool & b );

	BasicString( const T & c );



	~BasicString();

	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/************************************************************************/
	template<typename C>
	BasicString & operator=( const C * str );

	template<typename C>
	BasicString & operator=( const BasicString<C> & str );
	BasicString & operator=( BasicString<T> && str );
	BasicString & operator=( const BasicString<T> & str );


	template<typename C>
	BasicString & operator=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );

	BasicString & operator=( const unsigned char & i );
	BasicString & operator=( const unsigned short & i );

	BasicString & operator=( const int & i );
	BasicString & operator=( const unsigned int & i );

	BasicString & operator=( const long & i );
	BasicString & operator=( const unsigned long & i );

	BasicString & operator=( const long long & i );
	BasicString & operator=( const unsigned long long & i );

	BasicString & operator=( const double & i );
	BasicString & operator=( const float & i );

	BasicString & operator=( const bool & b );

	BasicString & operator=( const T & c );



	/************************************************************************/
	/* OPERATOR STREAM                                                      */
	/************************************************************************/

	template<typename C>
	BasicString & operator<<( const C * str );

	template<typename C>
	BasicString & operator<<( const BasicString<C> & str );

	template<typename C>
	BasicString & operator<<( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );

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
	/************************************************************************/
	template<typename C>
	BasicString & operator+=( const C * str );

	template<typename C>
	BasicString & operator+=( const BasicString<C> & str );

	template<typename C>
	BasicString & operator+=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );

	BasicString & operator+=( const unsigned char & uc );
	BasicString & operator+=( const unsigned short & us );

	BasicString & operator+=( const int & i );
	BasicString & operator+=( const unsigned int & ui );

	BasicString & operator+=( const long & l );
	BasicString & operator+=( const unsigned long & ul );

	BasicString & operator+=( const long long & ll );
	BasicString & operator+=( const unsigned long long & ull );

	BasicString & operator+=( const double & d );
	BasicString & operator+=( const float & f );

	BasicString & operator+=( const bool & b );

	template<typename C>
	BasicString & operator+=( const C & c );
	BasicString & operator+=( const char & c );
	BasicString & operator+=( const wchar_t & c );




	/************************************************************************/
	/* OPERATOR CONCAT                                                      */
	/************************************************************************/

	BasicString & concat( const BasicString<T> & str );
	template<typename C>
	BasicString & concat( const BasicString<C> & str );

	template<typename C>
	BasicString & concat( const C * buffer, typename const BasicString<C>::Size & bufferSize );

	template<typename C>
	BasicString & concat( const C * buffer );

	template<typename C>
	BasicString & concat( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );

	BasicString & concat( const bool & b );


	BasicString & concat( const char & c );
	BasicString & concat( const wchar_t & c );

	template<unsigned int Base = 10>
	BasicString & concat( const unsigned char & uc );

	template<unsigned int Base = 10>
	BasicString & concat( const unsigned short & us );

	template<unsigned int Base = 10>
	BasicString & concat( const int & i );

	template<unsigned int Base = 10>
	BasicString & concat( const unsigned int & ui );

	template<unsigned int Base = 10>
	BasicString & concat( const long & l );

	template<unsigned int Base = 10>
	BasicString & concat( const unsigned long & ul );

	template<unsigned int Base = 10>
	BasicString & concat( const long long & ll );

	template<unsigned int Base = 10>
	BasicString & concat( const unsigned long long & ull );

	template<unsigned int Precision = 10, unsigned int Base = 10>
	BasicString & concat( const double & d );

	template<unsigned int Precision = 5, unsigned int Base = 10>
	BasicString & concat( const float & f );


	BasicString & concat( const unsigned char & uc, unsigned int base );
	BasicString & concat( const unsigned short & us, unsigned int base );
	BasicString & concat( const int & i, unsigned int base );
	BasicString & concat( const unsigned int & ui, unsigned int base );
	BasicString & concat( const long & l, unsigned int base );
	BasicString & concat( const unsigned long & ul, unsigned int base );
	BasicString & concat( const long long & ll, unsigned int base );
	BasicString & concat( const unsigned long long & ull, unsigned int base );
	BasicString & concat( const double & d, unsigned int precision, unsigned int base );
	BasicString & concat( const float & f, unsigned int precision, unsigned int base );



	/************************************************************************/
	/* toCString()                                                          */
	/************************************************************************/
	template<typename C>
	static typename BasicString<T>::Size toCString( const C & c, T * buffer );
	static typename BasicString<T>::Size toCString( const char & c, T * buffer );
	static typename BasicString<T>::Size toCString( const wchar_t & c, T * buffer );


	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( unsigned char number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( unsigned short number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( unsigned int  number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( int number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( unsigned long number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( long long number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( unsigned long long number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( long number, T * buffer );

	template<unsigned int Precision = 10, unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( double number, T * buffer );

	template<unsigned int Precision = 5, unsigned int Base = 10>
	static typename BasicString<T>::Size toCString( float number, T * buffer );


	static typename BasicString<T>::Size toCString( unsigned char number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( unsigned short number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( unsigned int  number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( int number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( unsigned long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( long long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( unsigned long long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCString( double number, T * buffer, unsigned int precision, unsigned int base );
	static typename BasicString<T>::Size toCString( float number, T * buffer, unsigned int precision, unsigned int base );
	static typename BasicString<T>::Size toCString( bool b, T * buffer );


	/************************************************************************/
	/* ToCString() without adding sentinel                                  */
	/************************************************************************/

	template<typename C>
	static typename BasicString<T>::Size toCStringWOS( const C & c, T * buffer );
	static typename BasicString<T>::Size toCStringWOS( const char & c, T * buffer );
	static typename BasicString<T>::Size toCStringWOS( const wchar_t & c, T * buffer );


	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( unsigned char number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( unsigned short number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( unsigned int  number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( int number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( unsigned long number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( long long number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( unsigned long long number, T * buffer );

	template<unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( long number, T * buffer );

	template<unsigned int Precision = 10, unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( double number, T * buffer );

	template<unsigned int Precision = 5, unsigned int Base = 10>
	static typename BasicString<T>::Size toCStringWOS( float number, T * buffer );


	static typename BasicString<T>::Size toCStringWOS( unsigned char number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( unsigned short number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( unsigned int  number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( int number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( unsigned long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( long long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( unsigned long long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( long number, T * buffer, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( double number, T * buffer, unsigned int precision, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( float number, T * buffer, unsigned int precision, unsigned int base );
	static typename BasicString<T>::Size toCStringWOS( bool b, T * buffer );


	/************************************************************************/
	/* From String to number                                                */
	/************************************************************************/
	template<unsigned int Base = 10>
	char toChar();

	template<unsigned int Base = 10>
	int toInt();

	template<unsigned int Base = 10>
	short toShort();

	template<unsigned int Base = 10>
	long toLong();

	template<unsigned int Base = 10>
	long long toLongLong();

	template<unsigned int Base = 10>
	unsigned char toUChar();

	template<unsigned int Base = 10>
	unsigned int toUInt();

	template<unsigned int Base = 10>
	unsigned short toUShort();

	template<unsigned int Base = 10>
	unsigned long toULong();

	template<unsigned int Base = 10>
	unsigned long long toULongLong();

	template<unsigned int Base = 10>
	float toFloat();

	template<unsigned int Base = 10>
	double toDouble();


	char toChar( unsigned int base );
	int toInt( unsigned int base );
	short toShort( unsigned int base );
	long toLong( unsigned int base );
	long long toLongLong( unsigned int base );
	unsigned char toUChar( unsigned int base );
	unsigned int toUInt( unsigned int base );
	unsigned short toUShort( unsigned int base );
	unsigned long toULong( unsigned int base );
	unsigned long long toULongLong( unsigned int base );
	float toFloat( unsigned int base );
	double toDouble( unsigned int base );



	/************************************************************************/
	/* FromCString()                                                        */
	/************************************************************************/
	template<unsigned int Base = 10>
	static char toChar( T * buffer );

	template<unsigned int Base = 10>
	static int toInt( T * buffer );

	template<unsigned int Base = 10>
	static short toShort( T * buffer );

	template<unsigned int Base = 10>
	static long toLong( T * buffer );

	template<unsigned int Base = 10>
	static long long toLongLong( T * buffer );

	template<unsigned int Base = 10>
	static unsigned char toUChar( T * buffer );

	template<unsigned int Base = 10>
	static unsigned int toUInt( T * buffer );

	template<unsigned int Base = 10>
	static unsigned short toUShort( T * buffer );

	template<unsigned int Base = 10>
	static unsigned long toULong( T * buffer );

	template<unsigned int Base = 10>
	static unsigned long long toULongLong( T * buffer );

	template<unsigned int Base = 10>
	static float toFloat( T * buffer );

	template<unsigned int Base = 10>
	static double toDouble( T * buffer );


	static char toChar( T * buffer, unsigned int base );
	static int toInt( T * buffer, unsigned int base );
	static short toShort( T * buffer, unsigned int base );
	static long toLong( T * buffer, unsigned int base );
	static long long toLongLong( T * buffer, unsigned int base );
	static unsigned char toUChar( T * buffer, unsigned int base );
	static unsigned int toUInt( T * buffer, unsigned int base );
	static unsigned short toUShort( T * buffer, unsigned int base );
	static unsigned long toULong( T * buffer, unsigned int base );
	static unsigned long long toULongLong( T * buffer, unsigned int base );
	static float toFloat( T * buffer, unsigned int base );
	static double toDouble( T * buffer, unsigned int base );


	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	bool operator!=( const BasicString<T> & text ) const;
	bool operator==( const BasicString<T> & text ) const;
	bool operator>( const BasicString<T> & text ) const;
	bool operator<( const BasicString<T> & text ) const;
	bool operator>=( const BasicString<T> & text ) const;
	bool operator<=( const BasicString<T> & text ) const;

	bool operator!=( const T & text ) const;
	bool operator==( const T & text ) const;
	bool operator>( const T & text ) const;
	bool operator<( const T & text ) const;
	bool operator>=( const T & text ) const;
	bool operator<=( const T & text ) const;


	/************************************************************************/
	/* To String                                                            */
	/************************************************************************/
	static BasicString<T> toString( const T & c );

	template<unsigned int Base = 10>
	static BasicString<T> toString( unsigned char number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( unsigned short number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( unsigned int number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( int number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( unsigned long number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( long long number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( unsigned long long number );

	template<unsigned int Base = 10>
	static BasicString<T> toString( long number );

	template<unsigned int Precision = 10, unsigned int Base = 10>
	static BasicString<T> toString( double number );

	template<unsigned int Precision = 5, unsigned int Base = 10>
	static BasicString<T> toString( float number );



	static BasicString<T> toString( unsigned char number, unsigned int base );
	static BasicString<T> toString( unsigned short number, unsigned int base );
	static BasicString<T> toString( unsigned int number, unsigned int base );
	static BasicString<T> toString( int number, unsigned int base );
	static BasicString<T> toString( unsigned long number, unsigned int base );
	static BasicString<T> toString( long long number, unsigned int base );
	static BasicString<T> toString( unsigned long long number, unsigned int base );
	static BasicString<T> toString( long number, unsigned int base );
	static BasicString<T> toString( double number, unsigned int precision, unsigned int base );
	static BasicString<T> toString( float number, unsigned int precision, unsigned int base );
	static BasicString<T> toString( bool b );

	/************************************************************************/
	/* Others                                                               */
	/************************************************************************/
	Vector<BasicString<T>> split( const T & delimiter ) const;
	bool isNumeric() const;

	//resize the string and reallocate if necessary.
	void resize( typename Vector<T>::Size newSize );

	using Vector<T>::getSize;
	static typename Vector<T>::Size getSize( const T * str );

	const T * toCString() const;

	///@brief set the size to 0
	void clear();

	typename BasicString<T>::RandomAccessIterator getFirstIt( const T & c ) const;
	typename BasicString<T>::RandomAccessIterator getLastIt( const T & c ) const;

	typename BasicString<T>::RandomAccessIterator getFirstIt( const BasicString<T> & str ) const;
	typename BasicString<T>::RandomAccessIterator getLastIt( const BasicString<T> & str ) const;

	typename BasicString<T>::Size getFirst( const T & c ) const;
	typename BasicString<T>::Size getLast( const T & c ) const;

	typename BasicString<T>::Size getFirst( const BasicString<T> & str ) const;
	typename BasicString<T>::Size getLast( const BasicString<T> & str ) const;

	void replace( const T & toReplace, const T & byThis );
	void replace( const T & toReplace, const BasicString<T> & byThis );
	void replace( const BasicString<T> & toReplace, const BasicString<T> & byThis );

	BasicString<T> getDirectory();
	BasicString<T> getFileName();
	BasicString<T> getSubStr( const Size & index, const Size & size );

	///@brief read from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read( std::fstream * fileStream );


	/************************************************************************/
	/* Some static methods                                                  */
	/************************************************************************/
	static bool isNumeric( const BasicString<T> & v );
	static Vector<BasicString<T>> split( const BasicString<T> & s, const T & delimiter );

	template<typename T1, typename... Types>
	static BasicString<T> format( const BasicString<T> referenceString, const T1 & arg1, Types ... vars );


	static typename BasicString<T>::Size getFirst( const T * buffer, const Size & bufferSize, const T & c );
	static typename BasicString<T>::Size getLast( const T * buffer, const Size & bufferSize, const T & c );

	static typename BasicString<T>::Size getFirst( const T * buffer, const Size & bufferSize, const T * toSearch, const Size & toSearchSize );
	static typename BasicString<T>::Size getLast( const T * buffer, const Size & bufferSize, const T * toSearch, const Size & toSearchSize );

	static typename BasicString<T>::Size getFirst( const T * buffer, const T & c );
	static typename BasicString<T>::Size getLast( const T * buffer, const T & c );

	static typename BasicString<T>::Size getFirst( const T * buffer, const T * toSearch );
	static typename BasicString<T>::Size getLast( const T * buffer, const T * toSearch );

	static const T numbers[16];
	static const BasicString<T> null;

protected:
	BasicString( ctor );

	/************************************************************************/
	/* concat() without adding sentinel                                     */
	/************************************************************************/
	BasicString & _concatWOS( const BasicString<T> & str );
	template<typename C>
	BasicString & _concatWOS( const BasicString<C> & str );

	template<typename C>
	BasicString & _concatWOS( const C * buffer, typename const BasicString<C>::Size & bufferSize );

	template<typename C>
	BasicString & _concatWOS( const C * buffer );

	template<typename C>
	BasicString & _concatWOS( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );

	BasicString & _concatWOS( const bool & b );


	BasicString & _concatWOS( const char & c );
	BasicString & _concatWOS( const wchar_t & c );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const unsigned char & uc );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const unsigned short & us );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const int & i );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const unsigned int & ui );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const long & l );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const unsigned long & ul );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const long long & ll );

	template<unsigned int Base = 10>
	BasicString & _concatWOS( const unsigned long long & ull );

	template<unsigned int Precision = 10, unsigned int Base = 10>
	BasicString & _concatWOS( const double & d );

	template<unsigned int Precision = 5, unsigned int Base = 10>
	BasicString & _concatWOS( const float & f );


	BasicString & _concatWOS( const unsigned char & uc, unsigned int base );
	BasicString & _concatWOS( const unsigned short & us, unsigned int base );
	BasicString & _concatWOS( const int & i, unsigned int base );
	BasicString & _concatWOS( const unsigned int & ui, unsigned int base );
	BasicString & _concatWOS( const long & l, unsigned int base );
	BasicString & _concatWOS( const unsigned long & ul, unsigned int base );
	BasicString & _concatWOS( const long long & ll, unsigned int base );
	BasicString & _concatWOS( const unsigned long long & ull, unsigned int base );
	BasicString & _concatWOS( const double & d, unsigned int precision, unsigned int base );
	BasicString & _concatWOS( const float & f, unsigned int precision, unsigned int base );



private:

	template<typename T1, typename... Types>
	static void _format( const typename BasicString<T>::RandomAccessIterator &  referenceStringBegin, const typename BasicString<T>::RandomAccessIterator &  referenceStringEnd, BasicString<T> * newString, const T1 & arg1, Types ... vars );
	static void _format( const typename BasicString<T>::RandomAccessIterator &  referenceStringBegin, const typename BasicString<T>::RandomAccessIterator &  referenceStringEnd, BasicString<T> * newString );

	template<typename Type, unsigned int Base = 10>
	BasicString & _concatInteger( const Type & i );

	template<typename Type>
	BasicString & _concatInteger( const Type & i, unsigned int base );

	template<typename Type, unsigned int Precision = 5, unsigned int Base = 10>
	BasicString & _concatFloat( const Type & f );

	template<typename Type>
	BasicString & _concatFloat( const Type & f, unsigned int precision, unsigned int base );



	template<typename Type, unsigned int Base = 10>
	BasicString & _concatIntegerWOS( const Type & i );

	template<typename Type>
	BasicString & _concatIntegerWOS( const Type & i, unsigned int base );

	template<typename Type, unsigned int Precision = 5, unsigned int Base = 10>
	BasicString & _concatFloatWOS( const Type & f );

	template<typename Type>
	BasicString & _concatFloatWOS( const Type & f, unsigned int precision, unsigned int base );



	template<typename Type, unsigned int Base>
	static Type _toFloat( T * buffer );

	template<typename Type, unsigned int Base>
	static Type _toSignedInteger( T * buffer );

	template<typename Type, unsigned int Base>
	static Type _toUnsignedInteger( T * buffer );


	template<typename Type>
	static Type _toFloat( T * buffer, unsigned int base );

	template<typename Type>
	static Type _toSignedInteger( T * buffer, unsigned int base );

	template<typename Type>
	static Type _toUnsignedInteger( T * buffer, unsigned int base );



	template<typename Type, unsigned int Base>
	static typename BasicString<T>::Size _convertI2String( Type number, T * buffer );

	template< typename Type>
	static typename BasicString<T>::Size _convertI2String( Type number, T * buffer, unsigned int base );

	template<typename Type, unsigned int Base>
	static typename BasicString<T>::Size _convertUI2String( Type number, T * buffer );

	template<typename Type>
	static typename BasicString<T>::Size _convertUI2String( Type number, T * buffer, unsigned int base );

	template<typename Type, unsigned int Precision = 10, unsigned int Base>
	static typename BasicString<T>::Size _convertFloat2String( Type number, T * buffer );

	template<typename Type>
	static typename BasicString<T>::Size _convertFloat2String( Type number, T * buffer, unsigned int precision, unsigned int base );




	template<typename Type, unsigned int Base>
	static typename BasicString<T>::Size _convertI2StringWOS( Type number, T * buffer );

	template< typename Type>
	static typename BasicString<T>::Size _convertI2StringWOS( Type number, T * buffer, unsigned int base );

	template<typename Type, unsigned int Base>
	static typename BasicString<T>::Size _convertUI2StringWOS( Type number, T * buffer );

	template<typename Type>
	static typename BasicString<T>::Size _convertUI2StringWOS( Type number, T * buffer, unsigned int base );

	template<typename Type, unsigned int Precision = 10, unsigned int Base>
	static typename BasicString<T>::Size _convertFloat2StringWOS( Type number, T * buffer );

	template<typename Type>
	static typename BasicString<T>::Size _convertFloat2StringWOS( Type number, T * buffer, unsigned int precision, unsigned int base );
};










/************************************************************************/
/* OPERATOR STREAM                                                      */
/************************************************************************/
/*
template<typename T>
template<typename C>
BasicString<T> & operator<<(BasicString<T> basicString, const C * str);

template<typename T>
template<typename C>
BasicString<T> & operator<<(BasicString<T> basicString, const BasicString<C> & str);

template<typename T>
template<typename C>
BasicString<T> & operator<<(BasicString<T> basicString, const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str);

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
/************************************************************************/
template<typename T>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<T> & str2 );

template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<C> & str2 );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const int & i );

template<typename T>
BasicString<T> operator+( const int & i, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned char & ui );

template<typename T>
BasicString<T> operator+( const unsigned char & ui, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned short & ui );

template<typename T>
BasicString<T> operator+( const unsigned short & ui, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned int & ui );

template<typename T>
BasicString<T> operator+( const unsigned int & ui, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long & l );

template<typename T>
BasicString<T> operator+( const long & l, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long & ul );

template<typename T>
BasicString<T> operator+( const unsigned long & ul, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long long & ll );

template<typename T>
BasicString<T> operator+( const long long & ll, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long long & ull );

template<typename T>
BasicString<T> operator+( const unsigned long long & ull, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const float & f );

template<typename T>
BasicString<T> operator+( const float & f, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const bool & b );

template<typename T>
BasicString<T> operator+( const bool & b, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const double & d );

template<typename T>
BasicString<T> operator+( const double & d, const BasicString<T> & str );

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const T & c );

template<typename T>
BasicString<T> operator+( const T & c, const BasicString<T> & str );

template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, const C * str2 );

template<typename T, typename C>
BasicString<T> operator+( const C * str1, const BasicString<T> & str2 );


template<typename T, typename C>
BasicString<T> operator+( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str1, const BasicString<T> & str2 );

template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str2 );





template<typename T>
std::ostream & operator <<( std::ostream & stream, const BasicString<T> & str );










typedef BasicString<char> String;
typedef BasicString<wchar_t> WString;
typedef BasicString<unsigned int> UTF32String;



#include "String.hpp"




