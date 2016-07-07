#pragma once

#include <string>
#include "BuildConfig.h"
#include "Math.h"
#include "Vector.h"
#include "String.h"



typedef unsigned int UCodePoint;


class UTF8StringOLD {
public:
	UTF8StringOLD(bool bufferize = false);
	UTF8StringOLD(const std::string & text,  bool bufferize = false);
	UTF8StringOLD(const char * text, bool bufferize = false);
	UTF8StringOLD(const char * text, unsigned int size, bool bufferize = false);

	~UTF8StringOLD(void);


	UTF8StringOLD & operator=( const std::string & text );
	UTF8StringOLD & operator=( const char * text );
	UTF8StringOLD & operator=( const UTF8StringOLD & text );
	UTF8StringOLD & operator+=( const UTF8StringOLD & text );
	UTF8StringOLD & operator+=( char c );


	bool operator!=( const UTF8StringOLD & text ) const;
	bool operator==( const UTF8StringOLD & text ) const;
	bool operator>( const UTF8StringOLD & text ) const;
	bool operator<( const UTF8StringOLD & text ) const;
	bool operator>=( const UTF8StringOLD & text ) const;
	bool operator<=( const UTF8StringOLD & text ) const;



	char operator[](unsigned int i) const;

	/************************************************************************/
	/* WARNING, if  setUseCodePointBuffer isn't used, the method will loop
	 * FOR EVERY call until found the char wanted, instead a buffer will be
	 * created.														 */
	/************************************************************************/
	UCodePoint getCodePoint( unsigned int index );

	std::string toStdString();

	void reserve( unsigned int size );

	void copy( const UTF8StringOLD & text, unsigned int index, unsigned int size );

	void clear();

	void reset();

	unsigned int getSize();
	unsigned int getDataSize() const;
	unsigned int size();


	void push( char c );
	void push( const UTF8StringOLD & text );


	UTF8StringOLD substr( unsigned int index, unsigned int length ) const;



	char * getData();
	const char * getData() const;

	bool iterate( unsigned int * i ) const;
	bool iterate( unsigned int * i , UCodePoint * codePoint) const;


	unsigned int getDataSize(unsigned int index, unsigned int size);


	/************************************************************************/
	/* highly recommended for ultra fast direct code point access           */
	/************************************************************************/
	void setUseCodePointBuffer( bool useCodePointBuffer );

	/************************************************************************/
	/* Specials Methods                                                     */
	/************************************************************************/
	bool isNumeric() const;
	Vector<UTF8StringOLD> split( char delimiter ) const;
	UTF8StringOLD getDirectory( ) const;
	UTF8StringOLD getFileName( ) const;
	UTF8StringOLD getFirstWord( ) const;
	void replace( char toReplace, char change );

	/************************************************************************/
	/* Some static methods                                                  */
	/************************************************************************/
	static bool isNumeric(const UTF8StringOLD & v);

	static Vector<UTF8StringOLD> split( const UTF8StringOLD & s, char delimiter );

	static UTF8StringOLD getDirectory( const UTF8StringOLD & filePath );

	static UTF8StringOLD getFileName( const UTF8StringOLD & filePath );

	static UTF8StringOLD getFirstWord( const UTF8StringOLD & text );

	static UTF8StringOLD replace( const UTF8StringOLD & text, char toReplace, const UTF8StringOLD & change );
private:
	void updateCodePoints();
	void updateSize();

	bool useCodePointBuffer;
	bool needUpdateSize;


	Vector<char> charData;
	Vector<UCodePoint> codePoints;			//For each char, his code points, used for UTF8 only
	unsigned int numChars;
};


UTF8StringOLD operator+(const UTF8StringOLD & text1, const UTF8StringOLD & text2);
std::ostream& operator<< (std::ostream & out, UTF8StringOLD & text);