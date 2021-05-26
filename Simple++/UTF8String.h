#pragma once

#include "String.h"

template<typename T = char>
class UTF8StringT : public BasicString<T> {
public:
	typedef unsigned int CodePoint;

	UTF8StringT();

	template<typename C>
	UTF8StringT( const C * str );
	UTF8StringT( const char * str );

	///@brief Copy constructor from a NON-multibyte string
	///@param str String to be copied.
	///@param size buffer size (NOT the number of UTF8 characters).
	template<typename C>
	UTF8StringT( const C * str, typename UTF8StringT<T>::Size size );
	UTF8StringT( const char * str, typename UTF8StringT<T>::Size size );

	template<typename C>
	UTF8StringT( RandomAccessIterator<C> beginIt, RandomAccessIterator<C> endIt );

	template<typename C>
	UTF8StringT( const BasicString<C> & str );
	UTF8StringT( const BasicString<T> & str );
	UTF8StringT( const UTF8StringT<T> & str );
	UTF8StringT( UTF8StringT<T> && str );

	/**
	 * @brief		Constructor
	 * @tparam	C	String type.
	 * @param	str	Constant string.
	 */
	template<typename C, size_t N>
	UTF8StringT(const C(&str)[N]);


	// template<typename C>
	// UTF8StringT( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );
	// UTF8StringT( const std::string & str );

	//UTF8StringT( const typename UTF8StringT<T>::typename UTF8StringT<T>::CodePoint & codePoint );

	UTF8StringT( const int & i );
	UTF8StringT( const unsigned int & ui );
	UTF8StringT( const long & l );
	UTF8StringT( const unsigned long & ul );
	UTF8StringT( const long long & ll );
	UTF8StringT( const unsigned long long & ull );
	UTF8StringT( const double & d );
	UTF8StringT( const float & f );
	UTF8StringT( const bool & b );

	UTF8StringT( const char & c );

	///@brief Convert an UTF8 String into a standard String.
	///			Each Code point will be converted into the C type.
	///			No Error handling for code point overflowing the C type capability.
	template<typename C = char>
	operator BasicString<C>() const;



	~UTF8StringT();




	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/************************************************************************/
	template<typename C>
	UTF8StringT<T> & operator=( const BasicString<C> & str );
	UTF8StringT<T> & operator=( const BasicString<T> & str );
	UTF8StringT<T> & operator=( const UTF8StringT<T> & str );
	UTF8StringT<T> & operator=( UTF8StringT<T> && str );

	template<typename C>
	UTF8StringT<T> & operator=( const C * str );
	UTF8StringT<T> & operator=( const char * str );

	template<typename C>
	UTF8StringT<T> & operator=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str );
	UTF8StringT<T> & operator=( const std::string & str );

	template<typename C>
	UTF8StringT<T> & operator=( const C & c );


	/************************************************************************/
	/* OPERATOR CONCAT                                                      */
	/************************************************************************/
	using BasicString<T>::operator+=;

	template<typename C>
	UTF8StringT<T> & operator+=( const BasicString<C> & str );
	UTF8StringT<T> & operator+=( const BasicString<T> & str );
	UTF8StringT<T> & operator+=( const UTF8StringT<T> & str );


	template<typename C>
	UTF8StringT<T> & operator+=( const C & c );


	template<typename C>
	void concat( const BasicString<C> & str );
	void concat( const BasicString<T> & str );
	void concat( const UTF8StringT<T> & str );

	template<typename C>
	void concat( const C * buffer, typename const BasicString<C>::Size & bufferSize );
	void concat( const char * buffer, const typename UTF8StringT<T>::Size & bufferSize );


	///\brief iterate the buffer by passing a pointer to a buffer. The index has to be initialized to the first value you wanna iterate to.
	bool iterate( typename UTF8StringT<T>::Iterator * it ) const;

	///\brief iterate the buffer by passing a pointer to a buffer AND a pointer to a code point. The index has to be initialized to the first value you wanna iterate to.
	bool iterate( typename UTF8StringT<T>::Iterator * it, typename UTF8StringT<T>::CodePoint * codePoint ) const;

	///@brief Iterate ONE time and set the pointer to codePoint with the new one just retrieved
	///@param it Iterator to iterate
	///@param codePoint out Will be set to point to the data retrieved
	///@param testFunctor Functor to check a condition before incrementing the iterator
	///								bool operator()( const typename UTF8StringT<T>::CodePoint & c );
	///@return True if a data has been retrieved or False if the end has been reached or false is the functor return false
	template<typename TestFunctor>
	bool iterate( typename UTF8StringT<T>::Iterator * it, typename UTF8StringT<T>::CodePoint * codePoint, TestFunctor & testFunctor ) const;

	///@brief Compare a sub string of this UTF8 BasicString<T> with an another one
	///@param it Iterator of this string where you want to begin the comparison
	///@param otherStr Other BasicString<T>
	///@param anotherIt It of the other UTF8 BasicString<T> to be compared
	///@param size Number of chars to be compared
	///@return True if the two substring are equals, false instead
	bool cmp( typename UTF8StringT<T>::Iterator it, const UTF8StringT<T> & otherStr, typename UTF8StringT<T>::Iterator anotherIt, typename UTF8StringT<T>::Size size ) const;

	///brief Same as cmp without using pointer but the iterator will be modified instead of being copied
	bool cmp( typename UTF8StringT<T>::Iterator * it, const UTF8StringT<T> & otherStr, typename UTF8StringT<T>::Iterator * anotherIt, typename UTF8StringT<T>::Size size ) const;

	///@brief same as the one with UTF8StringT<T> but a bit faster for using ASCII strings
	bool cmp( typename UTF8StringT<T>::Iterator it, const BasicString<T> & otherStr, typename BasicString<T>::Iterator anotherIt, typename UTF8StringT<T>::Size size ) const;

	///brief Same as cmp without using pointer but the iterator will be modified instead of being copied
	bool cmp( typename UTF8StringT<T>::Iterator * it, const BasicString<T> & otherStr, typename BasicString<T>::Iterator * anotherIt, typename UTF8StringT<T>::Size size ) const;
	

	///@brief Create a sub BasicString<T> of this one
	///@param beginIt Iterator of the beginning
	UTF8StringT<T> getSubStr( typename UTF8StringT<T>::Size index, typename UTF8StringT<T>::Size size ) const;
	UTF8StringT<T> getSubStr( typename UTF8StringT<T>::Iterator beginIt, typename UTF8StringT<T>::Size size ) const;
	UTF8StringT<T> getSubStr( typename UTF8StringT<T>::Iterator beginIt, typename UTF8StringT<T>::Iterator endIt ) const;


	///@brief get the codePoint associated with an iterator
	///@param it Iterator
	///@return codePoint computed
	static typename UTF8StringT<T>::CodePoint getCodePoint( char charTmp[4] );


	//\brief this is the special version for UTF8 of the getSize() method /!\ WARNING /!\ This method iterate the whole string to retrieve the length.
	Size getSizeUTF8() const;

	///@brief Convert an Unicode Code Point into an char * (Without any '\0')
	///@param codePoint Code Point to be converted
	///@param in out buffer where to write
	///@return Number of character wrote
	static typename BasicString<T>::Size codePoint2Chars( const typename UTF8StringT<T>::CodePoint & codePoint, char charBuffer[4] );

	///@brief Convert an Unicode Code Point into an UTF8 BasicString<T>
	///@param codePoint Code Point to be converted
	///@param in out buffer where to write
	///@return BasicString<T> result
	static UTF8StringT<T> codePoint2String( const typename UTF8StringT<T>::CodePoint & codePoint );

	/** @brief	The null */
	static const UTF8StringT<T> null;
private:
	template<typename C>
	UTF8StringT<T> & _operatorEQUAL( const C * str, const typename UTF8StringT<T>::Size & bufferSize );

	template<typename C>
	void _contructorEQUAL( const C * str, const typename UTF8StringT<T>::Size & bufferSize );

	template<typename C>
	void _operatorCONCAT( const C * str, const typename UTF8StringT<T>::Size & bufferSize );

};

using UTF8String = UTF8StringT<char>;

typedef UTF8String::CodePoint UCodePoint;

#include "UTF8String.hpp"
