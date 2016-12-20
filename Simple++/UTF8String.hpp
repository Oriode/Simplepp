template<typename C>
UTF8String & UTF8String::operator+=( const C & c ) {
	BasicString<char>::operator+=( c );
	return *this;
}

template<typename C>
UTF8String & UTF8String::operator=( const C & c ) {
	BasicString<char>::operator=( c );
	return *this;
}

template<typename C>
void UTF8String::concat( const C * buffer, typename const BasicString<C>::Size & bufferSize ) {
	_operatorCONCAT( buffer, bufferSize );
}



template<typename C>
void UTF8String::concat( const BasicString<C> & str ) {
	_operatorCONCAT( str.getData(), str.getSize() );
}

template<typename C>
UTF8String & UTF8String::operator+=( const BasicString<C> & str ) {
	concat( str );
	return *this;
}




template<typename C>
UTF8String & UTF8String::operator=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str ) {
	return _operatorEQUAL( str.data(), str.size() );
}

template<typename C>
UTF8String & UTF8String::operator=( const C * str ) {
	return _operatorEQUAL( str, BasicString<C>::getSize( str ) );
}

template<typename T>
void UTF8String::_contructorEQUAL( const T * str, const Size & bufferSize ) {
	this -> maxSize = ( bufferSize + 1 ) * 4;
	this -> dataTable = new char[this -> maxSize];

	auto bufferTmp = this -> dataTable;
	for ( Size j = 0; j < bufferSize; j++ )
		bufferTmp += codePoint2Chars( str[j], bufferTmp );

	*bufferTmp = '\0';
	this -> size = ( Size ) ( bufferTmp - this -> dataTable );
	_updateIterators();
}

template<typename T>
UTF8String & UTF8String::_operatorEQUAL( const T * str, const Size & bufferSize ) {
	if ( getMaxSize() < bufferSize + 1 )
		allocate( ( bufferSize + 1 ) * 4 );

	auto bufferTmp = this -> dataTable;
	for ( Size j = 0; j < bufferSize; j++ )
		bufferTmp += codePoint2Chars( str[j], bufferTmp );

	*bufferTmp = '\0';
	this -> size = ( Size ) ( bufferTmp - this -> dataTable );
	_updateIterators();
	return *this;
}

template<typename T>
void UTF8String::_operatorCONCAT( const T * str, const Size & bufferSize ) {
	typename UTF8String::Size oldSize = getSize();
	typename UTF8String::Size newSize = oldSize + bufferSize;
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
	for ( Size j = 0; j < addedSize; j++ )
		bufferTmp += codePoint2Chars( str[j], bufferTmp );

	*bufferTmp = '\0';
	this -> size = newSize;
	_updateIterators();
}



template<typename TestFunctor>
bool UTF8String::iterate( typename Iterator * it, CodePoint * codePoint, TestFunctor & testFunctor ) const {
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
		*codePoint = ( CodePoint ) c;
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




template<typename C>
UTF8String & UTF8String::operator=( const BasicString<C> & str ) {
	return _operatorEQUAL( str.getData(), str.getSize() );
}

template<typename C>
UTF8String::UTF8String( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str ) :
	String( ctor::null ) {
	_contructorEQUAL( str.data(), str.size() );
}

template<typename C>
UTF8String::UTF8String( const BasicString<C> & str ) :
	String( ctor::null ) {
	_contructorEQUAL( str.getData(), str.getSize() );
}

template<typename C>
UTF8String::UTF8String( const C * str, Size size ) :
	String( ctor::null ) {
	_contructorEQUAL( str, size );
}

template<typename C>
UTF8String::UTF8String( RandomAccessIterator<C> beginIt, RandomAccessIterator<C> endIt ) : BasicString<char>(beginIt, endIt) {

}

template<typename C>
UTF8String::UTF8String( const C * str ) :
	String( str ) {
	_contructorEQUAL( str, BasicString<C>::getSize( str ) );
}

template<typename T>
UTF8String::operator BasicString<T>() const {
	if ( Utility::isSame<T, char>::value ) {
		return BasicString<T>( getData(), getSize() );
	} else {
		BasicString<T> r(ctor::null);
		r._allocateNoNullDelete( getSize() );
		CodePoint codePoint;
		auto newDatas( r.getData() );
		BasicString<T>::Size i( 0 );
		for ( auto it( getBegin() ); iterate( &it, &codePoint ); i++ ) {
			newDatas[i] = codePoint;
		}
		newDatas[i] = T( '\0' );
		r.size = i;
		r._updateIterators();
		return r;
	}


}
