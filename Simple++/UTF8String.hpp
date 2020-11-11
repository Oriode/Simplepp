template<typename T>
const UTF8StringT<T> UTF8StringT<T>::null = UTF8StringT<T>( "" );


template<typename T>
UTF8StringT<T>::UTF8StringT() {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const int & i ) :
	BasicString<T>( i ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const unsigned int & ui ) :
	BasicString<T>( ui ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const long & l ) :
	BasicString<T>( l ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const unsigned long & ul ) :
	BasicString<T>( ul ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const long long & ll ) :
	BasicString<T>( ll ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const unsigned long long & ull ) :
	BasicString<T>( ull ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const double & d ) :
	BasicString<T>( d ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const float & f ) :
	BasicString<T>( f ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const bool & b ) :
	BasicString<T>( b ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const char & c ) :
	BasicString<T>( c ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const BasicString<T> & str ) :
	BasicString<T>( str ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const std::string & str ) :
	BasicString<T>( str ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const UTF8StringT<T> & str ) :
	BasicString<T>( str ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( UTF8StringT<T> && str ) :
	BasicString<T>( Utility::toRValue( str ) ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const char * str, typename UTF8StringT<T>::Size size ) :
	BasicString<T>( str, size ) {}

template<typename T>
UTF8StringT<T>::UTF8StringT( const char * str ) :
	BasicString<T>( str ) {}

/*
template<typename T>
UTF8StringT<T>::UTF8StringT( const typename UTF8StringT<T>::CodePoint & codePoint ) : BasicString<T>( ctor::null ) {
	_allocateNoNullDelete(5);
	this -> size = codePoint2Chars( codePoint , this -> dataTable);
	this -> dataTable[this -> size] = char( '\0' );
	_updateIterators();
}
*/

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator=( const BasicString<T> & str ) {
	BasicString<T>::operator=( str );
	return *this;
}

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator=( const UTF8StringT<T> & str ) {
	BasicString<T>::operator=( str );
	return *this;
}

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator=( UTF8StringT<T> && str ) {
	BasicString<T>::operator=( Utility::toRValue( str ) );
	return *this;
}

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator=( const char * str ) {
	BasicString<T>::operator=( str );
	return *this;
}

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator=( const std::string & str ) {
	BasicString<T>::operator=( str );
	return *this;
}

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator+=( const UTF8StringT<T> & str ) {
	BasicString<T>::operator+=( str );
	return *this;
}

template<typename T>
UTF8StringT<T> & UTF8StringT<T>::operator+=( const BasicString<T> & str ) {
	concat( str );
	return *this;
}

template<typename T>
UTF8StringT<T>::~UTF8StringT() {}

template<typename T>
UTF8StringT<T> UTF8StringT<T>::getSubStr( typename UTF8StringT<T>::Size index, typename UTF8StringT<T>::Size size ) const {
	auto beginIt( getBegin() );
	for ( ; index && this -> iterate( &beginIt ); index-- );

	auto endIt( beginIt );
	for ( ; size && this -> iterate( &endIt ); size-- );

	return UTF8StringT( beginIt, endIt );
}

template<typename T>
UTF8StringT<T> UTF8StringT<T>::getSubStr( typename UTF8StringT<T>::Iterator beginIt, typename UTF8StringT<T>::Size size ) const {
	if ( beginIt >= getEnd() )
		return UTF8StringT();
	if ( beginIt < getBegin() )
		beginIt = getBegin();


	auto endIt( beginIt );
	for ( ; this -> iterate( &endIt ); );

	return UTF8StringT( beginIt, endIt );
}

template<typename T>
UTF8StringT<T> UTF8StringT<T>::getSubStr( typename UTF8StringT<T>::Iterator beginIt, typename UTF8StringT<T>::Iterator endIt ) const {
	if ( beginIt >= getEnd() || endIt < getBegin() )
		return UTF8StringT();
	if ( beginIt < getBegin() )
		beginIt = getBegin();
	if ( endIt > getEnd() )
		endIt = getEnd();

	return UTF8StringT( beginIt, endIt );
}

template<typename T>
typename UTF8StringT<T>::CodePoint UTF8StringT<T>::getCodePoint( char charTmp[ 4 ] ) {
	if ( charTmp[ 0 ] & 0x80 ) {				//1100 0000
		if ( charTmp[ 1 ] & 0x20 ) {			//1110 0000
			if ( charTmp[ 2 ] & 0x10 )		//1111 0000
				return ( ( charTmp[ 0 ] & 0x7 ) << 18 ) | ( ( charTmp[ 1 ] & 0x3F ) << 12 ) | ( ( charTmp[ 2 ] & 0x3F ) << 6 ) | ( charTmp[ 3 ] & 0x3F );

			else  //If the code point is on THREE Bytes ONLY !
				return ( ( charTmp[ 0 ] & 0xF ) << 12 ) | ( ( charTmp[ 1 ] & 0x3F ) << 6 ) | ( charTmp[ 2 ] & 0x3F );

		} else  //If the code point is on TWO Bytes ONLY !
			return ( ( charTmp[ 0 ] & 0x1F ) << 6 ) | ( charTmp[ 1 ] & 0x3F );
	} else   //If the code point is on ONE Byte ONLY !
		return ( typename UTF8StringT<T>::CodePoint ) charTmp[ 0 ];
}

template<typename T>
bool UTF8StringT<T>::iterate( typename UTF8StringT<T>::Iterator * i ) const {
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

template<typename T>
bool UTF8StringT<T>::iterate( typename UTF8StringT<T>::Iterator * i, typename UTF8StringT<T>::CodePoint * codePoint ) const {
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
		*codePoint = ( typename UTF8StringT<T>::CodePoint ) c;
		if ( c != '\0' ) {
			*i += 1;
			return true;
		} else
			return false;
	}
}

template<typename T>
bool UTF8StringT<T>::cmp( typename UTF8StringT<T>::Iterator it, const UTF8StringT<T> & otherStr, typename UTF8StringT<T>::Iterator anotherIt, typename UTF8StringT<T>::Size size ) const {
	return cmp( &it, otherStr, &anotherIt, size );
}

template<typename T>
bool UTF8StringT<T>::cmp( typename UTF8StringT<T>::Iterator * it, const UTF8StringT<T> & otherStr, typename UTF8StringT<T>::Iterator * anotherIt, typename UTF8StringT<T>::Size size ) const {
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

template<typename T>
bool UTF8StringT<T>::cmp( typename UTF8StringT<T>::Iterator it, const BasicString<T> & otherStr, typename BasicString<T>::Iterator anotherIt, typename UTF8StringT<T>::Size size ) const {
	return cmp( &it, otherStr, &anotherIt, size );
}

template<typename T>
bool UTF8StringT<T>::cmp( typename UTF8StringT<T>::Iterator * it, const BasicString<T> & otherStr, typename BasicString<T>::Iterator * anotherIt, typename UTF8StringT<T>::Size size ) const {
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

template<typename T>
typename UTF8StringT<T>::Size UTF8StringT<T>::getSizeUTF8() const {
	Size numChar = 0;
	for ( auto it = getBegin(); iterate( &it );) numChar++;
	return numChar;
}

template<typename T>
typename BasicString<T>::Size UTF8StringT<T>::codePoint2Chars( const typename UTF8StringT<T>::CodePoint & codePoint, char charBuffer[ 4 ] ) {
	if ( codePoint > 127 ) {
		if ( codePoint > 2047 ) {
			if ( codePoint > 65535 ) {
				charBuffer[ 0 ] = ( codePoint >> 18 ) | 0xF0;
				charBuffer[ 1 ] = ( ( codePoint >> 12 ) & 0x3F ) | 0xC0;
				charBuffer[ 2 ] = ( ( codePoint >> 6 ) & 0x3F ) | 0xC0;
				charBuffer[ 3 ] = ( codePoint & 0x3F ) | 0x80;
				return BasicString<T>::Size( 4 );
			} else {	//If the code point is on THREE Bytes ONLY !
				charBuffer[ 0 ] = ( codePoint >> 12 ) | 0xE0;
				charBuffer[ 1 ] = ( ( codePoint >> 6 ) & 0x3F ) | 0xC0;
				charBuffer[ 2 ] = ( codePoint & 0x3F ) | 0x80;
				return BasicString<T>::Size( 3 );
			}
		} else {	//If the code point is on TWO Bytes ONLY !
			charBuffer[ 0 ] = ( codePoint >> 6 ) | 0xC0;
			charBuffer[ 1 ] = ( codePoint & 0x3F ) | 0x80;
			return BasicString<T>::Size( 2 );
		}
	} else {		//If the code point is on ONE Byte ONLY !
		charBuffer[ 0 ] = codePoint;
		return BasicString<T>::Size( 1 );
	}
}

template<typename T>
UTF8StringT<T> UTF8StringT<T>::codePoint2String( const typename UTF8StringT<T>::CodePoint & codePoint ) {
	UTF8StringT<T> result( ctor::null );
	result._allocateNoNullDelete( 5 );
	result.size = codePoint2Chars( codePoint, result.dataTable );
	result.dataTable[ result.size ] = char( '\0' );
	result._updateIterators();
	return result;
}

template<typename T>
void UTF8StringT<T>::concat( const UTF8StringT<T> & str ) {
	BasicString<T>::concat( str );
}

template<typename T>
void UTF8StringT<T>::concat( const BasicString<T> & str ) {
	BasicString<T>::concat( str.data(), str.getSize() );
}

template<typename T>
void UTF8StringT<T>::concat( const char * buffer, const typename UTF8StringT<T>::Size & bufferSize ) {
	BasicString<T>::concat( buffer, bufferSize );
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::operator+=( const C & c ) {
	BasicString<T>::operator+=( c );
	return *this;
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::operator=( const C & c ) {
	BasicString<T>::operator=( c );
	return *this;
}

template<typename T>
template<typename C>
void UTF8StringT<T>::concat( const C * buffer, typename const BasicString<C>::Size & bufferSize ) {
	_operatorCONCAT( buffer, bufferSize );
}

template<typename T>
template<typename C>
void UTF8StringT<T>::concat( const BasicString<C> & str ) {
	_operatorCONCAT( str.getData(), str.getSize() );
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::operator+=( const BasicString<C> & str ) {
	concat( str );
	return *this;
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::operator=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str ) {
	return _operatorEQUAL( str.data(), str.size() );
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::operator=( const C * str ) {
	return _operatorEQUAL( str, BasicString<C>::getSize( str ) );
}

template<typename T>
template<typename C>
void UTF8StringT<T>::_contructorEQUAL( const C * str, const typename UTF8StringT<T>::Size & bufferSize ) {
	this -> maxSize = ( bufferSize + 1 ) * 4;
	this -> dataTable = new char[this -> maxSize];

	auto bufferTmp = this -> dataTable;
	for ( typename UTF8StringT<T>::Size j = 0; j < bufferSize; j++ )
		bufferTmp += codePoint2Chars( str[j], bufferTmp );

	*bufferTmp = '\0';
	this -> size = ( typename UTF8StringT<T>::Size ) ( bufferTmp - this -> dataTable );
	_updateIterators();
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::_operatorEQUAL( const C * str, const typename UTF8StringT<T>::Size & bufferSize ) {
	if ( getMaxSize() < bufferSize + 1 )
		allocate( ( bufferSize + 1 ) * 4 );

	auto bufferTmp = this -> dataTable;
	for ( typename UTF8StringT<T>::Size j = 0; j < bufferSize; j++ )
		bufferTmp += codePoint2Chars( str[j], bufferTmp );

	*bufferTmp = '\0';
	this -> size = ( typename UTF8StringT<T>::Size ) ( bufferTmp - this -> dataTable );
	_updateIterators();
	return *this;
}

template<typename T>
template<typename C>
void UTF8StringT<T>::_operatorCONCAT( const C * str, const typename UTF8StringT<T>::Size & bufferSize ) {
	typename UTF8StringT<T>::Size oldSize = getSize();
	typename UTF8StringT<T>::Size newSize = oldSize + bufferSize;
	auto newSizeSentinel( newSize + 1 );

	if ( this -> maxSize < newSizeSentinel ) {
		this -> maxSize = newSizeSentinel * 2;

		char * newDatas = new char[this -> maxSize];
		Vector::copy( newDatas, this -> dataTable, oldSize );
		delete[] this -> dataTable;
		this -> dataTable = newDatas;
	}

	Size addedSize = bufferSize + 1;
	auto bufferTmp = this -> dataTable + addedSize;
	for ( typename UTF8StringT<T>::Size j = 0; j < addedSize; j++ )
		bufferTmp += codePoint2Chars( str[j], bufferTmp );

	*bufferTmp = '\0';
	this -> size = newSize;
	_updateIterators();
}

template<typename T>
template<typename TestFunctor>
bool UTF8StringT<T>::iterate( typename UTF8StringT<T>::Iterator * it, typename UTF8StringT<T>::CodePoint * codePoint, TestFunctor & testFunctor ) const {
	char & c = **it;
	if ( c & 0x80 ) {				//1100 0000
		char & c1 = *( *it + 1 );
		if ( c & 0x20 ) {			//1110 0000
			char & c2 = *( *it + 2 );
			if ( c & 0x10 ) {		//1111 0000
				char & c3 = *( *it + 3 );
				*codePoint = ( ( c & 0x7 ) << 18 ) | ( ( c1 & 0x3F ) << 12 ) | ( ( c2 & 0x3F ) << 6 ) | ( c3 & 0x3F );
				if ( testFunctor( *codePoint ) ) {
					*it += 4;
					return true;
				}
			} else {  //If the code point is on THREE Bytes ONLY !
				*codePoint = ( ( c & 0xF ) << 12 ) | ( ( c1 & 0x3F ) << 6 ) | ( c2 & 0x3F );
				if ( testFunctor( *codePoint ) ) {
					*it += 3;
					return true;
				}
			}
		} else {  //If the code point is on TWO Bytes ONLY !
			*codePoint = ( ( c & 0x1F ) << 6 ) | ( c1 & 0x3F );
			if ( testFunctor( *codePoint ) ) {
				*it += 2;
				return true;
			}
		}
	} else {  //If the code point is on ONE Byte ONLY !
		*codePoint = ( typename UTF8StringT<T>::CodePoint ) c;
		if ( c != '\0' ) {
			if ( testFunctor( *codePoint ) ) {
				*it += 1;
				return true;
			}
		} else {
			return false;
		}
		
	}
	return false;
}

template<typename T>
template<typename C>
UTF8StringT<T> & UTF8StringT<T>::operator=( const BasicString<C> & str ) {
	return _operatorEQUAL( str.getData(), str.getSize() );
}

template<typename T>
template<typename C>
UTF8StringT<T>::UTF8StringT( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str ) :
	BasicString<T>( ctor::null ) {
	_contructorEQUAL( str.data(), str.size() );
}

template<typename T>
template<typename C>
UTF8StringT<T>::UTF8StringT( const BasicString<C> & str ) :
	BasicString<T>( ctor::null ) {
	_contructorEQUAL( str.getData(), str.getSize() );
}

template<typename T>
template<typename C>
UTF8StringT<T>::UTF8StringT( const C * str, typename UTF8StringT<T>::Size size ) :
	BasicString<T>( ctor::null ) {
	_contructorEQUAL( str, size );
}

template<typename T>
template<typename C>
UTF8StringT<T>::UTF8StringT( RandomAccessIterator<C> beginIt, RandomAccessIterator<C> endIt ) : BasicString<T>(beginIt, endIt) {

}

template<typename T>
template<typename C>
UTF8StringT<T>::UTF8StringT( const C * str ) :
	BasicString<T>( str ) {
	_contructorEQUAL( str, BasicString<C>::getSize( str ) );
}

template<typename T>
template<typename C>
UTF8StringT<T>::operator BasicString<C>() const {
	if ( Utility::isSame<C, char>::value ) {
		return BasicString<C>( getData(), getSize() );
	} else {
		BasicString<C> r(ctor::null);
		r._allocateNoNullDelete( getSize() );
		CodePoint codePoint;
		auto newDatas( r.getData() );
		BasicString<C>::Size i( 0 );
		for ( auto it( getBegin() ); iterate( &it, &codePoint ); i++ ) {
			newDatas[i] = codePoint;
		}
		newDatas[i] = T( '\0' );
		r.size = i;
		r._updateIterators();
		return r;
	}


}
