#pragma once

#include "String.h"


class UTF8String : public BasicString<char> {
public:
	typedef unsigned int CodePoint;

	UTF8String();


	template<typename C>
	UTF8String(const C * str);
	UTF8String(const char * str);



	template<typename C>
	UTF8String(const C * str, Size size);
	UTF8String(const char * str, Size size);


	template<typename C>
	UTF8String(const BasicString<C> & str);
	UTF8String(const String & str);
	UTF8String(const UTF8String & str);


	template<typename C>
	UTF8String(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str);
	UTF8String(const std::string & str);


	UTF8String(const int & i);
	UTF8String(const unsigned int & ui);
	UTF8String(const long & l);
	UTF8String(const unsigned long & ul);
	UTF8String(const long long & ll);
	UTF8String(const unsigned long long & ull);
	UTF8String(const double & d);
	UTF8String(const float & f);
	UTF8String(const bool & b);

	UTF8String(const char & c);



	~UTF8String();


	/************************************************************************/
	/* OPERATOR EQUAL                                                       */
	/************************************************************************/
	template<typename C>
	UTF8String & operator=(const BasicString<C> & str);
	UTF8String & operator=(const String & str);
	UTF8String & operator=(const UTF8String & str);

	template<typename C>
	UTF8String & operator=(const C * str);
	UTF8String & operator=(const char * str);

	template<typename C>
	UTF8String & operator=(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str);
	UTF8String & operator=(const std::string & str);

	template<typename C>
	UTF8String & operator=(const C & c);


	/************************************************************************/
	/* OPERATOR CONCAT                                                      */
	/************************************************************************/
	using String::operator+=;

	template<typename C>
	UTF8String & operator+=(const BasicString<C> & str);
	UTF8String & operator+=(const String & str);
	UTF8String & operator+=(const UTF8String & str);
	

	template<typename C>
	UTF8String & operator+=(const C & c);


	template<typename C>
	void concat(const BasicString<C> & str);
	void concat(const String & str);
	void concat(const UTF8String & str);

	template<typename C>
	void concat(const C * buffer, typename const BasicString<C>::Size & bufferSize);
	void concat(const char * buffer, const Size & bufferSize);


	///\brief iterate the buffer by passing a pointer to a buffer. The index has to be initialized to the first value you wanna iterate to.
	bool iterate(RandomAccessIterator * i) const;

	///\brief iterate the buffer by passing a pointer to a buffer AND a pointer to a code point. The index has to be initialized to the first value you wanna iterate to.
	bool iterate(RandomAccessIterator * i, CodePoint * codePoint) const;



	///\brief compute the code point associated with the char buffer
	static CodePoint getCodePoint(char charTmp[4]);


	//\brief this is the special version for UTF8 of the getSize() method /!\ WARNING /!\ This method iterate the whole string to retrieve the length.
	Size getSizeUTF8() const;

	static void CodePoint2Chars(const CodePoint & codePoint, char charBuffer[4], unsigned char * size);
private:
	template<typename T>
	UTF8String & _operatorEQUAL(const T & str, const Size & bufferSize);

	template<typename T>
	void _contructorEQUAL(const T & str, const Size & bufferSize);

	template<typename T>
	void _operatorCONCAT(const T & str, const Size & bufferSize);

};



typedef  UTF8String::CodePoint UCodePoint;

#include "UTF8String.hpp"