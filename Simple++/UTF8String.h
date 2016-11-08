#pragma once

#include "String.h"


class UTF8String : public BasicString<char> {
public:
	typedef unsigned int CodePoint;

	UTF8String();

	template<typename C>
	UTF8String( const C * str );
	UTF8String( const char * str );

	///@brief Copy constructor from a NON-multibyte string
	template<typename C>
	UTF8String( const C * str, Size size );
	UTF8String( const char * str, Size size );

	template<typename C>
	UTF8String( RandomAccessIterator<C> beginIt, RandomAccessIterator<C> endIt );

	template<typename C>
	UTF8String( const BasicString<C> & str );
	UTF8String( const String & str );
	UTF8String( const UTF8String & str );
	UTF8String( UTF8String && str );


	template<typename C>
	UTF8String( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );
	UTF8String( const std::string & str );


	UTF8String( const int & i );
	UTF8String( const unsigned int & ui );
	UTF8String( const long & l );
	UTF8String( const unsigned long & ul );
	UTF8String( const long long & ll );
	UTF8String( const unsigned long long & ull );
	UTF8String( const double & d );
	UTF8String( const float & f );
	UTF8String( const bool & b );

	UTF8String( const char & c );



	~UTF8String();




	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/************************************************************************/
	template<typename C>
	UTF8String & operator=( const BasicString<C> & str );
	UTF8String & operator=( const String & str );
	UTF8String & operator=( const UTF8String & str );
	UTF8String & operator=( UTF8String && str );

	template<typename C>
	UTF8String & operator=( const C * str );
	UTF8String & operator=( const char * str );

	template<typename C>
	UTF8String & operator=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );
	UTF8String & operator=( const std::string & str );

	template<typename C>
	UTF8String & operator=( const C & c );


	/************************************************************************/
	/* OPERATOR CONCAT                                                      */
	/************************************************************************/
	using String::operator+=;

	template<typename C>
	UTF8String & operator+=( const BasicString<C> & str );
	UTF8String & operator+=( const String & str );
	UTF8String & operator+=( const UTF8String & str );


	template<typename C>
	UTF8String & operator+=( const C & c );


	template<typename C>
	void concat( const BasicString<C> & str );
	void concat( const String & str );
	void concat( const UTF8String & str );

	template<typename C>
	void concat( const C * buffer, typename const BasicString<C>::Size & bufferSize );
	void concat( const char * buffer, const Size & bufferSize );


	///\brief iterate the buffer by passing a pointer to a buffer. The index has to be initialized to the first value you wanna iterate to.
	bool iterate( typename UTF8String::Iterator * it ) const;

	///\brief iterate the buffer by passing a pointer to a buffer AND a pointer to a code point. The index has to be initialized to the first value you wanna iterate to.
	bool iterate( typename UTF8String::Iterator * it, CodePoint * codePoint ) const;

	///@brief Iterate ONE time and set the pointer to codePoint with the new one just retrieved
	///@param it Iterator to iterate
	///@param codePoint out Will be set to point to the data retrieved
	///@param testFunctor Functor to check a condition before incrementing the iterator
	///								bool operator()( const CodePoint & c );
	///@return True if a data has been retrieved or False if the end has been reached or false is the functor return false
	template<typename TestFunctor>
	bool iterate( typename UTF8String::Iterator * it, CodePoint * codePoint, TestFunctor & testFunctor ) const;

	///@brief Compare a sub string of this UTF8 String with an another one
	///@param it Iterator of this string where you want to begin the comparison
	///@param otherStr Other String
	///@param anotherIt It of the other UTF8 String to be compared
	///@param size Number of chars to be compared
	///@return True if the two substring are equals, false instead
	bool cmp( typename UTF8String::Iterator it, const UTF8String & otherStr, typename UTF8String::Iterator anotherIt, Size size ) const;

	///brief Same as cmp without using pointer but the iterator will be modified instead of being copied
	bool cmp( typename UTF8String::Iterator * it, const UTF8String & otherStr, typename UTF8String::Iterator * anotherIt, Size size ) const;

	///@brief same as the one with UTF8String but a bit faster for using ASCII strings
	bool cmp( typename UTF8String::Iterator it, const BasicString<char> & otherStr, typename BasicString<char>::Iterator anotherIt, Size size ) const;

	///brief Same as cmp without using pointer but the iterator will be modified instead of being copied
	bool cmp( typename UTF8String::Iterator * it, const BasicString<char> & otherStr, typename BasicString<char>::Iterator * anotherIt, Size size ) const;
	

	///@brief Create a sub String of this one
	///@param beginIt Iterator of the beginning
	UTF8String getSubStr( Size index, Size size ) const;
	UTF8String getSubStr( typename UTF8String::Iterator beginIt, Size size ) const;
	UTF8String getSubStr( typename UTF8String::Iterator beginIt, typename UTF8String::Iterator endIt ) const;


	///@brief get the codePoint associated with an iterator
	///@param it Iterator
	///@return codePoint computed
	static CodePoint getCodePoint( char charTmp[4] );


	//\brief this is the special version for UTF8 of the getSize() method /!\ WARNING /!\ This method iterate the whole string to retrieve the length.
	Size getSizeUTF8() const;

	static void codePoint2Chars( const CodePoint & codePoint, char charBuffer[4], unsigned char * size );
private:
	template<typename T>
	UTF8String & _operatorEQUAL( const T & str, const Size & bufferSize );

	template<typename T>
	void _contructorEQUAL( const T & str, const Size & bufferSize );

	template<typename T>
	void _operatorCONCAT( const T & str, const Size & bufferSize );

};


typedef  UTF8String::CodePoint UCodePoint;

#include "UTF8String.hpp"
