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
	_operatorCONCAT( str, str.getSize() );
}

template<typename C>
UTF8String & UTF8String::operator+=( const BasicString<C> & str ) {
	concat( str );
	return *this;
}


template<typename T>
void UTF8String::_operatorCONCAT( const T & str, const Size & bufferSize ) {
	typename UTF8String::Size oldSize = getSize();
	typename UTF8String::Size newSize = oldSize + bufferSize;
	auto newSizeSentinel = newSize + 1;

	if ( this -> maxSize < newSizeSentinel ) {
		this -> maxSize = newSizeSentinel * 2;

		char * newDatas = new char[this -> maxSize];
		Vector::copy( newDatas, this -> dataTable, oldSize );
		delete[] this -> dataTable;
		this -> dataTable = newDatas;
	}

	Size addedSize = bufferSize + 1;
	unsigned char size;
	auto bufferTmp = this -> dataTable + addedSize;
	for ( Size j = 0; j < addedSize; j++, bufferTmp += size )
		codePoint2Chars( str[j], bufferTmp, &size );

	*bufferTmp = '\0';
	this -> size = newSize;
	_updateIterators();
}

template<typename C>
UTF8String & UTF8String::operator=( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str ) {
	return _operatorEQUAL( str, str.size() );
}

template<typename C>
UTF8String & UTF8String::operator=( const C * str ) {
	return _operatorEQUAL( str, BasicString<C>::getSize( str ) );
}

template<typename T>
void UTF8String::_contructorEQUAL( const T & str, const Size & bufferSize ) {
	this -> maxSize = ( bufferSize + 1 ) * 4;
	this -> dataTable = new char[this -> maxSize];

	unsigned char size;
	auto bufferTmp = this -> dataTable;
	for ( Size j = 0; j < bufferSize; j++, bufferTmp += size )
		codePoint2Chars( str[j], bufferTmp, &size );

	*bufferTmp = '\0';
	this -> size = ( Size ) ( bufferTmp - this -> dataTable );
	_updateIterators();
}

template<typename T>
UTF8String & UTF8String::_operatorEQUAL( const T & str, const Size & bufferSize ) {
	if ( getMaxSize() < bufferSize + 1 )
		allocate( ( bufferSize + 1 ) * 4 );

	unsigned char size;
	auto bufferTmp = this -> dataTable;
	for ( Size j = 0; j < bufferSize; j++, bufferTmp += size )
		codePoint2Chars( str[j], bufferTmp, &size );

	*bufferTmp = '\0';
	this -> size = ( Size ) ( bufferTmp - this -> dataTable );
	_updateIterators();
	return *this;
}




template<typename C>
UTF8String & UTF8String::operator=( const BasicString<C> & str ) {
	return _operatorEQUAL( str, str.getSize() );
}

template<typename C>
UTF8String::UTF8String( const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str ) :
	String( ctor::null ) {
	_contructorEQUAL( str, str.size() );
}

template<typename C>
UTF8String::UTF8String( const BasicString<C> & str ) :
	String( ctor::null ) {
	_contructorEQUAL( str, str.getSize() );

}

template<typename C>
UTF8String::UTF8String( const C * str, Size size ) :
	String( ctor::null ) {
	_contructorEQUAL( str, size );
}

template<typename C>
UTF8String::UTF8String( const C * str ) :
	String( str ) {
	_contructorEQUAL( str, BasicString<C>::getSize( str ) );
}
