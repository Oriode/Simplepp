#include "UTF8String.h"


UTF8String::UTF8String() {
}





UTF8String::UTF8String( const int & i ) :
	StringASCII( i ) {

}

UTF8String::UTF8String( const unsigned int & ui ) :
	StringASCII( ui ) {

}

UTF8String::UTF8String( const long & l ) :
	StringASCII( l ) {

}

UTF8String::UTF8String( const unsigned long & ul ) :
	StringASCII( ul ) {

}

UTF8String::UTF8String( const long long & ll ) :
	StringASCII( ll ) {

}

UTF8String::UTF8String( const unsigned long long & ull ) :
	StringASCII( ull ) {

}

UTF8String::UTF8String( const double & d ) :
	StringASCII( d ) {

}

UTF8String::UTF8String( const float & f ) :
	StringASCII( f ) {

}

UTF8String::UTF8String( const bool & b ) :
	StringASCII( b ) {

}

UTF8String::UTF8String( const char & c ) :
	StringASCII( c ) {

}

UTF8String::UTF8String( const StringASCII & str ) :
	StringASCII( str ) {
}

UTF8String::UTF8String( const std::string & str ) :
	StringASCII( str ) {
}

UTF8String::UTF8String( const UTF8String & str ) :
	StringASCII( str ) {
}

UTF8String::UTF8String( UTF8String && str ) :
	StringASCII( Utility::toRValue( str ) ) {
}

UTF8String::UTF8String( const char * str, Size size ) :
	StringASCII( str, size ) {
}

UTF8String::UTF8String( const char * str ) :
	StringASCII( str) {
}



/*
UTF8String::UTF8String( const CodePoint & codePoint ) : StringASCII( ctor::null ) {
	_allocateNoNullDelete(5);
	this -> size = codePoint2Chars( codePoint , this -> dataTable);
	this -> dataTable[this -> size] = char( '\0' );
	_updateIterators();
}
*/

UTF8String & UTF8String::operator=( const StringASCII & str ) {
	StringASCII::operator=( str );
	return *this;
}

UTF8String & UTF8String::operator=( const UTF8String & str ) {
	StringASCII::operator=( str );
	return *this;
}

UTF8String & UTF8String::operator=( UTF8String && str ) {
	StringASCII::operator=( Utility::toRValue( str ) );
	return *this;
}


UTF8String & UTF8String::operator=( const char * str ) {
	StringASCII::operator=( str );
	return *this;
}

UTF8String & UTF8String::operator=( const std::string & str ) {
	StringASCII::operator=( str );
	return *this;
}

UTF8String & UTF8String::operator+=( const UTF8String & str ) {
	StringASCII::operator+=( str );
	return *this;
}

UTF8String & UTF8String::operator+=( const StringASCII & str ) {
	concat( str );
	return *this;
}



UTF8String::~UTF8String() {
}



UTF8String UTF8String::getSubStr( Size index, Size size ) const  {
	auto beginIt( getBegin() );
	for ( ; index && this -> iterate( &beginIt ); index-- );

	auto endIt( beginIt );
	for ( ; size && this -> iterate( &endIt ); size-- );

	return UTF8String( beginIt, endIt );
}


UTF8String UTF8String::getSubStr( typename UTF8String::Iterator beginIt, Size size ) const {
	if ( beginIt >= getEnd() )
		return UTF8String();
	if ( beginIt < getBegin() )
		beginIt = getBegin();


	auto endIt( beginIt );
	for ( ; this -> iterate( &endIt ); );

	return UTF8String( beginIt, endIt );
}

UTF8String UTF8String::getSubStr( typename UTF8String::Iterator beginIt, typename UTF8String::Iterator endIt ) const {
	if ( beginIt >= getEnd() || endIt < getBegin() )
		return UTF8String();
	if ( beginIt < getBegin() )
		beginIt = getBegin();
	if ( endIt > getEnd() )
		endIt = getEnd();

	return UTF8String( beginIt, endIt );
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



bool UTF8String::iterate( typename UTF8String::Iterator * i ) const {
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
		if ( c != '\0' ) {
			*i += 1;
		} else {
			return false;
		}
	}
	return true;
}




bool UTF8String::iterate( typename UTF8String::Iterator * i, CodePoint * codePoint ) const {
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
		if ( c != '\0' ) {
			*i += 1;
			return true;
		} else
			return false;
	}
}




bool UTF8String::cmp( typename UTF8String::Iterator it, const UTF8String & otherStr, typename UTF8String::Iterator anotherIt, Size size ) const {
	return cmp( &it, otherStr, &anotherIt, size );
}


bool UTF8String::cmp( typename UTF8String::Iterator * it, const UTF8String & otherStr, typename UTF8String::Iterator * anotherIt, Size size ) const {
	UCodePoint codePointThis;
	UCodePoint codePointOther;
	while ( size ) {
		if ( !this -> iterate( it, &codePointThis ) ) {
			if ( !otherStr.iterate( anotherIt, &codePointOther ) ) return true;
			else return false;
		}
		if ( !otherStr.iterate( anotherIt, &codePointOther ) ) return false;
		if ( codePointThis != codePointOther ) return false;
		size--;
	}
	return true;
}


bool UTF8String::cmp( typename UTF8String::Iterator it, const  BasicString<char> & otherStr, typename BasicString<char>::Iterator anotherIt, Size size ) const {
	return cmp( &it, otherStr, &anotherIt, size );
}


bool UTF8String::cmp( typename UTF8String::Iterator * it, const  BasicString<char> & otherStr, typename BasicString<char>::Iterator * anotherIt, Size size ) const {
	while ( size ) {
		if ( ( **it ) == ( **anotherIt ) ) {
			if ( ( **it ) == char( '\0' ) ) return true;
		} else {
			return false;
		}
		size--;
		( *it )++;
		( *anotherIt )++;
	}
	return true;
}

UTF8String::Size UTF8String::getSizeUTF8() const {
	Size numChar = 0;
	for ( auto it = getBegin(); iterate( &it );) numChar++;
	return numChar;
}

typename StringASCII::Size UTF8String::codePoint2Chars( const CodePoint & codePoint, char charBuffer[4] ) {
	if ( codePoint > 127 ) {
		if ( codePoint > 2047 ) {
			if ( codePoint > 65535 ) {
				charBuffer[0] = ( codePoint >> 18 ) | 0xF0;
				charBuffer[1] = ( ( codePoint >> 12 ) & 0x3F ) | 0xC0;
				charBuffer[2] = ( ( codePoint >> 6 ) & 0x3F ) | 0xC0;
				charBuffer[3] = ( codePoint & 0x3F ) | 0x80;
				return StringASCII::Size( 4 );
			} else {	//If the code point is on THREE Bytes ONLY !
				charBuffer[0] = ( codePoint >> 12 ) | 0xE0;
				charBuffer[1] = ( ( codePoint >> 6 ) & 0x3F ) | 0xC0;
				charBuffer[2] = ( codePoint & 0x3F ) | 0x80;
				return StringASCII::Size( 3 );
			}
		} else {	//If the code point is on TWO Bytes ONLY !
			charBuffer[0] = ( codePoint >> 6 ) | 0xC0;
			charBuffer[1] = ( codePoint & 0x3F ) | 0x80;
			return StringASCII::Size( 2 );
		}
	} else {		//If the code point is on ONE Byte ONLY !
		charBuffer[0] = codePoint;
		return StringASCII::Size( 1 );
	}
}


UTF8String UTF8String::codePoint2String( const CodePoint & codePoint ) {
	UTF8String result(ctor::null);
	result._allocateNoNullDelete( 5 );
	result.size = codePoint2Chars( codePoint, result.dataTable );
	result.dataTable[result.size] = char( '\0' );
	result._updateIterators();
	return result;
}


void UTF8String::concat( const UTF8String & str ) {
	StringASCII::concat( str );
}

void UTF8String::concat( const StringASCII & str ) {
	StringASCII::concat( str.data(), str.getSize() );
}

void UTF8String::concat( const char * buffer, const Size & bufferSize ) {
	StringASCII::concat( buffer, bufferSize );
}

