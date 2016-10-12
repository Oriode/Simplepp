#include "UTF8String.h"


UTF8String::UTF8String() {
}





UTF8String::UTF8String( const int & i ) :
	String( i ) {

}

UTF8String::UTF8String( const unsigned int & ui ) :
	String( ui ) {

}

UTF8String::UTF8String( const long & l ) :
	String( l ) {

}

UTF8String::UTF8String( const unsigned long & ul ) :
	String( ul ) {

}

UTF8String::UTF8String( const long long & ll ) :
	String( ll ) {

}

UTF8String::UTF8String( const unsigned long long & ull ) :
	String( ull ) {

}

UTF8String::UTF8String( const double & d ) :
	String( d ) {

}

UTF8String::UTF8String( const float & f ) :
	String( f ) {

}

UTF8String::UTF8String( const bool & b ) :
	String( b ) {

}

UTF8String::UTF8String( const char & c ) :
	String( c ) {

}

UTF8String::UTF8String( const String & str ) :
	String( ctor::null ) {
	_contructorEQUAL( str, str.getSize() );
}

UTF8String::UTF8String( const std::string & str ) :
	String( ctor::null ) {
	_contructorEQUAL( str, str.size() );
}

UTF8String::UTF8String( const UTF8String & str ) :
	String( str ) {
}

UTF8String::UTF8String( UTF8String && str ) :
	String( Utility::toRValue( str ) ) {
}

UTF8String::UTF8String( const char * str, Size size ) :
	String( ctor::null ) {
	_contructorEQUAL( str, size );
}


UTF8String::UTF8String( const char * str ) :
	String( ctor::null ) {
	_contructorEQUAL( str, String::getSize( str ) );
}


UTF8String & UTF8String::operator=( const String & str ) {
	return _operatorEQUAL( str, str.getSize() );
}

UTF8String & UTF8String::operator=( const UTF8String & str ) {
	String::operator=( str );
	return *this;
}

UTF8String & UTF8String::operator=( UTF8String && str ) {
	String::operator=( Utility::toRValue( str ) );
	return *this;
}


UTF8String & UTF8String::operator=( const char * str ) {
	return _operatorEQUAL( str, String::getSize( str ) );
}

UTF8String & UTF8String::operator=( const std::string & str ) {
	return _operatorEQUAL( str, str.size() );
}



UTF8String & UTF8String::operator+=( const UTF8String & str ) {
	String::operator+=( str );
	return *this;
}

UTF8String & UTF8String::operator+=( const String & str ) {
	concat( str );
	return *this;
}



UTF8String::~UTF8String() {
}



UTF8String::CodePoint UTF8String::getCodePoint( char charTmp[4] ) {
	if ( charTmp[0] & 0x80 ) {				//1100 0000
		if ( charTmp[1] & 0x20 ) {			//1110 0000
			if ( charTmp[2] & 0x10 )		//1111 0000
				return ( ( charTmp[0] & 0x7 ) << 18 ) | ( ( charTmp[1] & 0x3F ) << 12 ) | ( ( charTmp[2] & 0x3F ) << 6 ) | ( charTmp[3] & 0x3F );

			else  //If the code point is on THREE Bytes ONLY !
				return ( ( charTmp[0] & 0xF ) << 12 ) | ( ( charTmp[1] & 0x3F ) << 6 ) | ( charTmp[2] & 0x3F );

		} else  //If the code point is on TWO Bytes ONLY !
			return ( ( charTmp[0] & 0x1F ) << 6 ) | ( charTmp[1] & 0x3F );
	} else   //If the code point is on ONE Byte ONLY !
		return ( CodePoint ) charTmp[0];
}



bool UTF8String::iterate( RandomAccessIterator * i ) const {
	char & c = **i;
	if ( c & 0x80 ) {				//1000 0000
		if ( c & 0x20 ) {			//1110 0000
			if ( c & 0x10 ) {		//1111 0000
				*i += 4;
			} else { //If the code point is on THREE Bytes ONLY 
				*i += 3;
			}
		} else { //If the code point is on TWO Bytes ONLY !
			*i += 2;
		}
	} else {  //If the code point is on ONE Byte ONLY !
		*i += 1;
	}
	return *i < getEnd();
}




bool UTF8String::iterate( RandomAccessIterator * i, CodePoint * codePoint ) const {
	char & c = **i;
	if ( c & 0x80 ) {				//1100 0000
		char & c1 = *( *i + 1 );
		if ( c & 0x20 ) {			//1110 0000
			char & c2 = *( *i + 2 );
			if ( c & 0x10 ) {		//1111 0000
				char & c3 = *( *i + 3 );
				*codePoint = ( ( c & 0x7 ) << 18 ) | ( ( c1 & 0x3F ) << 12 ) | ( ( c2 & 0x3F ) << 6 ) | ( c3 & 0x3F );
				*i += 4;
				return true;
			} else {  //If the code point is on THREE Bytes ONLY !
				*codePoint = ( ( c & 0xF ) << 12 ) | ( ( c1 & 0x3F ) << 6 ) | ( c2 & 0x3F );
				*i += 3;
				return true;
			}
		} else {  //If the code point is on TWO Bytes ONLY !
			*codePoint = ( ( c & 0x1F ) << 6 ) | ( c1 & 0x3F );
			*i += 2;
			return true;
		}
	} else {  //If the code point is on ONE Byte ONLY !
		*codePoint = ( CodePoint ) c;
		*i += 1;
		return c != '\0';
	}
}




UTF8String::Size UTF8String::getSizeUTF8() const {
	Size numChar = 0;
	for ( auto it = getBegin(); iterate( &it );) numChar++;
	return numChar;
}

void UTF8String::CodePoint2Chars( const CodePoint & codePoint, char charBuffer[4], unsigned char * size ) {
	if ( codePoint > 127 ) {
		if ( codePoint > 2047 ) {
			if ( codePoint > 65535 ) {
				charBuffer[0] = ( codePoint >> 18 ) | 0xF0;
				charBuffer[1] = ( ( codePoint >> 12 ) & 0x3F ) | 0xC0;
				charBuffer[2] = ( ( codePoint >> 6 ) & 0x3F ) | 0xC0;
				charBuffer[3] = ( codePoint & 0x3F ) | 0x80;
				*size = 4;
			} else {	//If the code point is on THREE Bytes ONLY !
				charBuffer[0] = ( codePoint >> 12 ) | 0xE0;
				charBuffer[1] = ( ( codePoint >> 6 ) & 0x3F ) | 0xC0;
				charBuffer[2] = ( codePoint & 0x3F ) | 0x80;
				*size = 3;
			}
		} else {	//If the code point is on TWO Bytes ONLY !
			charBuffer[0] = ( codePoint >> 6 ) | 0xC0;
			charBuffer[1] = ( codePoint & 0x3F ) | 0x80;
			*size = 2;
		}
	} else {		//If the code point is on ONE Byte ONLY !
		charBuffer[0] = codePoint;
		*size = 1;
	}
}

void UTF8String::concat( const UTF8String & str ) {
	String::concat( str );
}

void UTF8String::concat( const String & str ) {
	_operatorCONCAT( str, str.getSize() );
}

void UTF8String::concat( const char * buffer, const Size & bufferSize ) {
	_operatorCONCAT( buffer, bufferSize );
}

