#include "String.h"











template<typename T>
const T BasicString<T>::base64CharTable[ 64 ] = { T('A'), T('B'), T('C'), T('D'), T('E'), T('F'), T('G'), T('H'), T('I'), T('J'), T('K'), T('L'), T('M'), T('N'), T('O'), T('P'), T('Q'), T('R'), T('S'), T('T'), T('U'), T('V'), T('W'), T('X'), T('Y'), T('Z'), T('a'), T('b'), T('c'), T('d'), T('e'), T('f'), T('g'), T('h'), T('i'), T('j'), T('k'), T('l'), T('m'), T('n'), T('o'), T('p'), T('q'), T('r'), T('s'), T('t'), T('u'), T('v'), T('w'), T('x'), T('y'), T('z'), T('0'), T('1'), T('2'), T('3'), T('4'), T('5'), T('6'), T('7'), T('8'), T('9'), T('+'), T('/') };

template<typename T>
const T BasicString<T>::numbers[ 16 ] = { T( '0' ), T( '1' ), T( '2' ), T( '3' ), T( '4' ), T( '5' ), T( '6' ), T( '7' ), T( '8' ), T( '9' ), T( 'a' ), T( 'b' ), T( 'c' ), T( 'd' ), T( 'e' ), T( 'f' ) };

template<typename T>
const BasicString<T> BasicString<T>::null = BasicString<T>( "" );

template<typename T>
const typename BasicString<T>::IsEndSentinel BasicString<T>::IS_END_SENTINEL;














/************************************************************************/
/* Constructors                                                         */
/************************************************************************/





template<typename T>
template<typename C>
BasicString<T>::BasicString( C * const & str ) :
	Vector( Vector<T>::protectedCtor::null ) {
	this -> size = BasicString<C>::getSize( str );
	this -> maxSize = this -> size + 1;
	this -> dataTable = new T[ this -> maxSize ];
	Vector<T>::_updateIterators();
	copy( str, Vector<T>::getMaxSize() );
}


/*
template<typename T>
template<typename C, size_t N>
BasicString<T>::BasicString(const C(&s)[N]) :
Vector<T>(ctor::null)
{
	this -> size = N - 1;
	this -> maxSize = N;
	this -> dataTable = new T[N];
	Utility::copy(this -> dataTable, s, N);
	_updateIterators();
}*/


template<typename T>
template<typename C>
BasicString<T>::BasicString( const C * str, Size size ) :
	Vector( str, size, size + 1 ) {
	this -> dataTable[ this -> size ] = T( '\0' );
}

template<typename T>
template<typename C>
BasicString<T>::BasicString( const typename RandomAccessIterator<C> beginIt, const typename RandomAccessIterator<C> endIt ) :
	Vector<T>( beginIt, Size( endIt - beginIt ), Size( endIt - beginIt + 1 ) ) {
	this -> dataTable[ this -> size ] = T( '\0' );
}



template<typename T>
BasicString<T>::BasicString() :
	Vector<T>( Size( 0 ), Size( 1 ) ) {
	this -> dataTable[ 0 ] = T( '\0' );
}


template<typename T>
BasicString<T>::BasicString( const unsigned char & ui, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 5;
	this -> dataTable = new T[ 5 ];
	this -> size = toCString( ui, this -> dataTable, base );
	Vector<T>::_updateIterators();
}


template<typename T>
BasicString<T>::BasicString( const unsigned short & ui, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 7;
	this -> dataTable = new T[ 7 ];
	this -> size = toCString( ui, this -> dataTable, base );
	Vector<T>::_updateIterators();
}


template<typename T>
BasicString<T>::BasicString( const int & i, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 12;
	this -> dataTable = new T[ 12 ];
	this -> size = toCString( i, this -> dataTable, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const unsigned int & ui, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 11;
	this -> dataTable = new T[ 11 ];
	this -> size = toCString( ui, this -> dataTable, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const long int & l, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 21;
	this -> dataTable = new T[ 21 ];
	this -> size = toCString( l, this -> dataTable, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const unsigned long int & ul, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 21;
	this -> dataTable = new T[ 21 ];
	this -> size = toCString( ul, this -> dataTable, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const long long int & ll, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 21;
	this -> dataTable = new T[ 21 ];
	this -> size = toCString( ll, this -> dataTable, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const unsigned long long int & ull, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 21;
	this -> dataTable = new T[ 21 ];
	this -> size = toCString( ull, this -> dataTable, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const double & d, unsigned int precision, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 50;
	this -> dataTable = new T[ 50 ];
	this -> size = toCString( d, this -> dataTable, precision, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const float & f, unsigned int precision, unsigned int base ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 30;
	this -> dataTable = new T[ 30 ];
	this -> size = toCString( f, this -> dataTable, precision, base );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const bool & b ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this -> maxSize = 6;
	this -> dataTable = new T[ 6 ];
	this -> size = toCString( b, this -> dataTable );
	Vector<T>::_updateIterators();
}

template<typename T>
BasicString<T>::BasicString( const T & c ) :
	Vector<T>( 1, 2 ) {
	this -> dataTable[ 0 ] = T( c );
	this -> dataTable[ 1 ] = T( '\0' );
}



template<typename T>
template<typename C, size_t N>
BasicString<T>::BasicString( const C( &str )[ N ] ) :
	Vector<T>( N - 1, N ) {
	Utility::copy( this -> dataTable, str, N );
}

template<typename T>
template<typename C>
BasicString<T>::BasicString( const BasicString<C> & str ) :
	Vector<T>( str.getSize(), str.getSize() + 1 ) {
	Utility::copy( this -> dataTable, str.getData(), Vector<T>::getMaxSize() );
}

template<typename T>
BasicString<T>::BasicString( const BasicString<T> & str ) :
	Vector<T>(Vector<T>::protectedCtor::null) {
	if ( str.getSize() > Size(0) ) {
		this->size = str.getSize();
		this->maxSize = str.getMaxSize();
		this->dataTable = new T[ this->maxSize ];
		Utility::copy(this -> dataTable, str.dataTable, Vector<T>::getMaxSize());
	} else {
		this->size = Size(0);
		this->maxSize = Size(1);
		this->dataTable = new T[ this->maxSize ];
		this->dataTable[ 0 ] = T('\0');
	}
}

template<typename T>
BasicString<T>::BasicString( BasicString<T> && str ) :
	Vector<T>( Utility::toRValue( str ) ) {}

template<typename T>
BasicString<T>::BasicString(typename BasicString<T>::protectedCtor) : Vector<T>( Vector<T>::protectedCtor::null ) {

}

template<typename T>
inline BasicString<T>::BasicString( const typename Math::Compare::Value & compareValue ) :
	Vector<T>( Vector<T>::protectedCtor::null ) {
	this->maxSize = 8;
	this->dataTable = new T[ 8 ];
	this->size = toCString( compareValue, this->dataTable );
	_updateIterators();




}

template<typename T>
BasicString<T>::~BasicString() {}








/************************************************************************/
/* OPERATOR +                                                           */
/************************************************************************/

template<typename T>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<T> & str2 ) {
	BasicString<T> newStr( str1 );
	newStr += str2;
	return newStr;
}


template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, const BasicString<C> & str2 ) {
	BasicString<T> newStr( str1 );
	newStr += str2;
	return newStr;
}



template<typename T, typename C>
BasicString<T> operator+( const BasicString<T> & str1, C * const & str2 ) {
	BasicString<T> newStr( str1 );
	newStr += str2;
	return newStr;
}

template<typename T, typename C>
BasicString<T> operator+( C * const & str1, const BasicString<T> & str2 ) {
	BasicString<T> newStr( str1 );
	newStr += str2;
	return newStr;
}


template<typename T>
BasicString<T> operator+( const BasicString<T> & str1, const int & i ) {
	BasicString<T> newStr( str1 );
	newStr += i;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const int & i, const BasicString<T> & str ) {
	BasicString<T> newStr( i );
	newStr += str;
	return newStr;
}


template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned char & ui ) {
	BasicString<T> newStr( str );
	newStr += ui;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const unsigned char & ui, const BasicString<T> & str ) {
	BasicString<T> newStr( ui );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned short & ui ) {
	BasicString<T> newStr( str );
	newStr += ui;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const unsigned short & ui, const BasicString<T> & str ) {
	BasicString<T> newStr( ui );
	newStr += str;
	return newStr;
}


template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned int & ui ) {
	BasicString<T> newStr( str );
	newStr += ui;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const unsigned int & ui, const BasicString<T> & str ) {
	BasicString<T> newStr( ui );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long int & l ) {
	BasicString<T> newStr( str );
	newStr += l;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const long int & l, const BasicString<T> & str ) {
	BasicString<T> newStr( l );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long int & ul ) {
	BasicString<T> newStr( str );
	newStr += ul;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const unsigned long int & ul, const BasicString<T> & str ) {
	BasicString<T> newStr( ul );
	newStr += str;
	return newStr;
}


template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const long long int & ll ) {
	BasicString<T> newStr( str );
	newStr += ll;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const long long int & ll, const BasicString<T> & str ) {
	BasicString<T> newStr( ll );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const unsigned long long int & ull ) {
	BasicString<T> newStr( str );
	newStr += ull;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const unsigned long long int & ull, const BasicString<T> & str ) {
	BasicString<T> newStr( ull );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const float & f ) {
	BasicString<T> newStr( str );
	newStr += f;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const float & f, const BasicString<T> & str ) {
	BasicString<T> newStr( f );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const bool & b ) {
	BasicString<T> newStr( str );
	newStr += b;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const bool & b, const BasicString<T> & str ) {
	BasicString<T> newStr( b );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const double & d ) {
	BasicString<T> newStr( str );
	newStr += d;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const double & d, const BasicString<T> & str ) {
	BasicString<T> newStr( d );
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const BasicString<T> & str, const T & c ) {
	BasicString<T> newStr( str );
	newStr += c;
	return newStr;
}

template<typename T>
BasicString<T> operator+( const T & c, const BasicString<T> & str ) {
	BasicString<T> newStr( c );
	newStr += str;
	return newStr;
}

template<typename T, typename C, size_t N>
BasicString<T> operator+( const C( &str1 )[ N ], const BasicString<T> & str2 ) {
	BasicString<T> newStr( str1 );
	newStr += str2;
	return newStr;
}


template<typename T, typename C, size_t N>
BasicString<T> operator+( const BasicString<T> & str1, const C( &str2 )[ N ] ) {
	BasicString<T> newStr( str1 );
	newStr += str2;
	return newStr;
}







/************************************************************************/
/* Operator +=                                                          */
/************************************************************************/


template<typename T>
template<typename C, size_t N>
BasicString<T> & BasicString<T>::concat( const C( &str )[ N ] ) {
	this -> concat( str, N - 1 );
	return *this;
}



template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat( C * const & str ) {
	_concatWOS( str );

	*this -> iteratorEnd = T( '\0' );
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::concat( const bool & b ) {
	auto newMaxSize = this -> size + 6;
	if ( newMaxSize > this -> maxSize ) {
		_extendBuffer( newMaxSize );
		_updateIterators();
	}

	this -> size += toCString( b, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::concat( const char & c ) {
	Size newSize( this -> size + 1 );
	if ( newSize >= this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size = newSize;
	toCString( c, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::concat( const wchar_t & c ) {
	Size newSize( this -> size + 1 );
	if ( newSize >= this -> maxSize ) {
		_extendBuffer( this -> size );
		_updateIterators();
	}

	this -> size = newSize;
	toCString( c, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}



/*
template<typename T>
template<typename Type, unsigned int Base>
BasicString<T> & BasicString<T>::_concatInteger( const Type & i ) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize ){
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCString<Base>( i, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatFloat( const Type & f ) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize ){
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCString<Precision, Base>( f, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}
*/

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatInteger( const Type & i, unsigned int base ) {
	auto newSize = this -> size + 64;
	if ( newSize > this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCString( i, this -> iteratorEnd, base );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatFillInteger( const Type & i, const Size & fillNb, const T & fillChar, unsigned int base ) {
	Size nbChar( _getIntegerLength( i, base ) );

	// Compute the new buffer size.
	Size newSize;
	if ( fillNb > nbChar ) {
		Size nbCharToFill( fillNb - nbChar );

		newSize = this -> size + fillNb;
		if ( newSize > this -> maxSize ) {
			_extendBuffer( newSize );
			_updateIterators();
		}

		if ( i < Type( 0 ) ) {
			*this -> iteratorEnd = T( '-' );
			this -> iteratorEnd++;

			T * itEnd( this -> iteratorEnd + nbCharToFill );
			for ( ; this -> iteratorEnd < itEnd; this -> iteratorEnd++ ) {
				*this -> iteratorEnd = fillChar;
			}

			toCString( -i, this -> iteratorEnd, base );
		} else {
			T * itEnd( this -> iteratorEnd + nbCharToFill );
			for ( ; this -> iteratorEnd < itEnd; this -> iteratorEnd++ ) {
				*this -> iteratorEnd = fillChar;
			}

			toCString( i, this -> iteratorEnd, base );
		}
	} else {
		newSize = this -> size + nbChar;
		if ( newSize > this -> maxSize ) {
			_extendBuffer( newSize );
			_updateIterators();
		}
		toCString( i, this -> iteratorEnd, base );
	}
	this -> size = newSize;
	Vector<T>::_updateIterators();
	return *this;


	/*
	// ------------
	Size nbChar( _getIntegerLength( i, base ) );
	
	// Compute the new buffer size.
	Size newSize;
	if ( fillNb > nbChar ) {
		Size nbCharToFill( fillNb - nbChar );

		newSize = this -> size + fillNb;
		if ( newSize > this -> maxSize ){
			_extendBuffer( newSize );
			_updateIterators();
		}

		T * itEnd( this -> iteratorEnd + nbCharToFill );
		for ( ; this -> iteratorEnd < itEnd; this -> iteratorEnd++ ) {
			*this -> iteratorEnd = fillChar;
		}
	} else {
		newSize = this -> size + nbChar;
		if ( newSize > this -> maxSize ){
			_extendBuffer( newSize );
			_updateIterators();
		}
	}
	toCString( i, this -> iteratorEnd, base );
	this -> size = newSize;
	Vector<T>::_updateIterators();
	return *this;
	*/
}



template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatFloat( const Type & f, unsigned int precision, unsigned int base ) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCString( f, this -> iteratorEnd, precision, base );
	Vector<T>::_updateIterators();
	return *this;
}

/*
template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const unsigned char & uc ) {
	return _concatInteger<unsigned char, Base>( uc );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const unsigned short & us ) {
	return _concatInteger<unsigned short, Base>( us );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const int & i ) {
	return _concatInteger<int, Base>( i );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const unsigned int & ui ) {
	return _concatInteger<unsigned int, Base>( ui );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const long int & l ) {
	return _concatInteger<long int, Base>( l );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const unsigned long int & ul ) {
	return _concatInteger<unsigned long int, Base>( ul );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const long long int & ll ) {
	return _concatInteger<long long int, Base>( ll );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat( const unsigned long long int & ull ) {
	return _concatInteger<unsigned long long int, Base>( ull );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::concat( const double & d ) {
	return _concatFloat<double, Precision, Base>( d );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::concat( const float & f ) {
	return _concatFloat<float, Precision, Base>( f );
}
*/

template<typename T>
BasicString<T> & BasicString<T>::concat( const unsigned char & uc, unsigned int base ) {
	return _concatInteger<unsigned char>( uc, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const unsigned short & us, unsigned int base ) {
	return _concatInteger<unsigned short>( us, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const int & i, unsigned int base ) {
	return _concatInteger<int>( i, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const unsigned int & ui, unsigned int base ) {
	return _concatInteger<unsigned int>( ui, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const long int & l, unsigned int base ) {
	return _concatInteger<long int>( l, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const unsigned long int & ul, unsigned int base ) {
	return _concatInteger<unsigned long int>( ul, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const long long int & ll, unsigned int base ) {
	return _concatInteger<long long int>( ll, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const unsigned long long int & ull, unsigned int base ) {
	return _concatInteger<unsigned long long int>( ull, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const double & d, unsigned int precision, unsigned int base ) {
	return _concatFloat<double>( d, precision, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concat( const float & f, unsigned int precision, unsigned int base ) {
	return _concatFloat<float>( f, precision, base );
}

template<typename T>
BasicString<T> & BasicString<T>::concatFill( const unsigned char & uc, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<unsigned char>( uc, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const unsigned short & us, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<unsigned short>( us, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const int & i, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<int>( i, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const unsigned int & ui, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<unsigned int>( ui, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const long int & l, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<long int>( l, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const unsigned long int & ul, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<unsigned long int>( ul, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const long long int & ll, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<long long int>( ll, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const unsigned long long int & ull, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _concatFillInteger<unsigned long long int>( ull, fillNb, fillChar, base );
}
/*
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const double & d, const Size & fillNb, const T & fillChar, unsigned int precision, unsigned int base ) {
	return _concatFillInteger<int>( d, fillNb, fillChar, base );
}
template<typename T>
BasicString<T> & BasicString<T>::concatFill( const float & f, const Size & fillNb, const T & fillChar, unsigned int precision, unsigned int base ) {
	return _concatFillInteger<int>( f, fillNb, fillChar, base );
}
*/

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat( const BasicString<C> & str ) {
	return concat( str.getData(), str.getSize() );
}

template<typename T>
BasicString<T> & BasicString<T>::concat( const BasicString<T> & str ) {
	return concat( str.getData(), str.getSize() );
}




template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat( const C * buffer, const Size & bufferSize ) {
	_concatWOS( buffer, bufferSize );

	*this -> iteratorEnd = T( '\0' );

	return *this;
}



/************************************************************************/
/* concat() without adding sentinnel                                    */
/************************************************************************/
template<typename T>
template<typename C, size_t N>
BasicString<T> & BasicString<T>::_concatWOS( const C( &str )[ N ] ) {
	this -> concat( str );
	return *this;
}



template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS( C * const & str ) {
	_concatWOS( str, BasicString<T>::getSize( str ) );

	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const bool & b ) {
	auto newMaxSize = this -> size + 6;
	if ( newMaxSize > this -> maxSize ) {
		_extendBuffer( newMaxSize );
		_updateIterators();
	}

	this -> size += toCString( b, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const char & c ) {
	Size newSize( this -> size + 1 );
	if ( newSize >= this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size = newSize;
	toCStringWOS( c, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const wchar_t & c ) {
	Size newSize( this -> size + 1 );
	if ( newSize >= this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size = newSize;
	toCStringWOS( c, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}



/*
template<typename T>
template<typename Type, unsigned int Base>
BasicString<T> & BasicString<T>::_concatIntegerWOS( const Type & i ) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize ){
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCStringWOS<Base>( i, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatFloatWOS( const Type & f ) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize ){
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCStringWOS<Precision, Base>( f, this -> iteratorEnd );
	Vector<T>::_updateIterators();
	return *this;
}
*/

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatIntegerWOS( const Type & i, unsigned int base ) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCStringWOS( i, this -> iteratorEnd, base );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatFloatWOS( const Type & f, unsigned int precision, unsigned int base ) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	this -> size += toCStringWOS( f, this -> iteratorEnd, precision, base );
	Vector<T>::_updateIterators();
	return *this;
}

/*
template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned char & uc ) {
	return _concatIntegerWOS<unsigned char, Base>( uc );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned short & us ) {
	return _concatIntegerWOS<unsigned short, Base>( us );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const int & i ) {
	return _concatIntegerWOS<int, Base>( i );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned int & ui ) {
	return _concatIntegerWOS<unsigned int, Base>( ui );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const long int & l ) {
	return _concatIntegerWOS<long int, Base>( l );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned long int & ul ) {
	return _concatIntegerWOS<unsigned long int, Base>( ul );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const long long int & ll ) {
	return _concatIntegerWOS<long long int, Base>( ll );
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned long long int & ull ) {
	return _concatIntegerWOS<unsigned long long int, Base>( ull );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const double & d ) {
	return _concatFloatWOS<double, Precision, Base>( d );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS( const float & f ) {
	return _concatFloatWOS<float, Precision, Base>( f );
}
*/

template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned char & uc, unsigned int base ) {
	return _concatIntegerWOS<unsigned char>( uc, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned short & us, unsigned int base ) {
	return _concatIntegerWOS<unsigned short>( us, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const int & i, unsigned int base ) {
	return _concatIntegerWOS<int>( i, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned int & ui, unsigned int base ) {
	return _concatIntegerWOS<unsigned int>( ui, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const long int & l, unsigned int base ) {
	return _concatIntegerWOS<long int>( l, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned long int & ul, unsigned int base ) {
	return _concatIntegerWOS<unsigned long int>( ul, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const long long int & ll, unsigned int base ) {
	return _concatIntegerWOS<long long int>( ll, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const unsigned long long int & ull, unsigned int base ) {
	return _concatIntegerWOS<unsigned long long int>( ull, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const double & d, unsigned int precision, unsigned int base ) {
	return _concatFloatWOS<double>( d, precision, base );
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const float & f, unsigned int precision, unsigned int base ) {
	return _concatFloatWOS<float>( f, precision, base );
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS( const BasicString<C> & str ) {
	return _concatWOS( str.getData(), str.getSize() );
}

template<typename T>
BasicString<T> & BasicString<T>::_concatWOS( const BasicString<T> & str ) {
	return _concatWOS( str.getData(), str.getSize() );
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS( C * const & buffer, const Size & bufferSize ) {
	Size newSize = getSize() + bufferSize;

	if ( newSize >= this -> maxSize ) {
		_extendBuffer( newSize );
		_updateIterators();
	}

	Utility::copy( this -> iteratorEnd, buffer, bufferSize );
	this -> size = newSize;
	Vector<T>::_updateIterators();
	return *this;
}

/************************************************************************/
/* CONVERSIONS                                                          */
/************************************************************************/
/*
template<typename T>
template<typename Type, unsigned int Base>
Size BasicString<T>::_convertUI2StringWOS( Type number, T * buffer ) {
	_ASSERT( Base <= 16 && Base > 0 );
	static Type tmpBuffer[ sizeof( Type ) * 8 ];

	T * bufferInit( buffer );
	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type( Base );
		if ( number < Type( Base ) ) break;
		number /= Type( Base );
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, buffer++ ) {
		*buffer = BasicString<T>::numbers[ *tmpP ];
	}
	return static_cast<Size>( buffer - buffer );
}
*/

template<typename T>
template<typename Type>
Size BasicString<T>::_convertUI2StringWOS( Type number, T ** bufferP, unsigned int base ) {
	T * bufferInit( *bufferP );
	__convertUI2StringWOS( number, bufferP, base );

	return static_cast<Size>( *bufferP - bufferInit );
}

template<typename T>
template<typename Type>
typename void BasicString<T>::__convertUI2StringWOS( Type number, T ** bufferP, unsigned int base ) {
	_ASSERT( base <= 16 && base > 0 );
	static Type tmpBuffer[ sizeof( Type ) * 8 ];

	T *& buffer( *bufferP );
	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type( base );
		if ( number < Type( base ) ) break;
		number /= Type( base );
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, buffer++ ) {
		*buffer = BasicString<T>::numbers[ *tmpP ];
	}
}

/*
template<typename T>
template<typename Type, unsigned int Base>
Size BasicString<T>::_convertI2StringWOS( Type number, T * buffer ) {
	_ASSERT( Base <= 16 && Base > 0 );

	static Type tmpBuffer[ sizeof( Type ) * 8 ];

	T * bufferInit( buffer );
	if ( number < Type( 0 ) ) {
		( *buffer ) = T( '-' );
		buffer++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type( Base );
		if ( number < Type( Base ) ) break;
		number /= Type( Base );
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, buffer++ ) {
		*buffer = BasicString<T>::numbers[ *tmpP ];
	}
	return static_cast< Size >( buffer - buffer );
}
*/

template<typename T>
template<typename Type>
Size BasicString<T>::_convertI2StringWOS( Type number, T ** bufferP, unsigned int base ) {
	T * bufferInit( *bufferP );
	__convertI2StringWOS( number, bufferP, base );

	return static_cast< Size >( *bufferP - bufferInit );
}

template<typename T>
template<typename Type>
typename void BasicString<T>::__convertI2StringWOS( Type number, T ** bufferP, unsigned int base ) {
	_ASSERT( base <= 16 && base > 0 );

	static Type tmpBuffer[ sizeof( Type ) * 8 ];

	T *& buffer( *bufferP );
	if ( number < Type( 0 ) ) {
		( *buffer ) = T( '-' );
		buffer++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type( base );
		if ( number < Type( base ) ) break;
		number /= Type( base );
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, buffer++ ) {
		*buffer = BasicString<T>::numbers[ *tmpP ];
	}
}

/*
template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
Size BasicString<T>::_convertFloat2StringWOS( Type number, T * buffer ) {
	_ASSERT( Base <= 16 && Precision < 50 );

	if ( number == INFINITY ) {
		buffer[ 0 ] = T( 'I' );
		buffer[ 1 ] = T( 'N' );
		buffer[ 2 ] = T( 'F' );
		return Size( 3 );
	}


	T * bufferInit( buffer );

	if ( number == Type( 0 ) ) {
		( *buffer ) = T( '0' );
		buffer++;
		( *buffer ) = T( '\0' );
		return 1;
	}

	if ( number < 0 ) {
		( *buffer ) = T( '-' );
		buffer++;
		number = -number;
	}

	int comma = 1;
	while ( number > Type( Base ) ) {
		number /= Type( Base );
		comma++;
	}
	while ( number < Type( 1 ) ) {
		number *= Type( Base );
		comma--;
	}
	int i;
	if ( comma < 1 ) {
		buffer[ 0 ] = T( '0' );
		buffer++;
	} else {
		for ( i = 0; i < comma; i++, buffer++ ) {
			unsigned long long int castedNumber = ( unsigned long long int )number;
			*buffer = BasicString<T>::numbers[ castedNumber % Base ];
			number *= Type( Base );
		}
	}


	*buffer = T( '.' );
	buffer++;

	for ( i = comma; i < ( int ) Precision; i++, buffer++ ) {
		unsigned long long int castedNumber = ( unsigned long long int )number;
		*buffer = BasicString<T>::numbers[ castedNumber % Base ];
		number *= Type( Base );
	}
	return static_cast< Size >( buffer - bufferInit );
}
*/

template<typename T>
template<typename Type>
Size BasicString<T>::_convertFloat2StringWOS( Type number, T ** bufferP, unsigned int precision, unsigned int base ) {
	T * bufferInit( *bufferP );
	__convertFloat2StringWOS( number, bufferP, precision, base );

	return static_cast< Size >( *bufferP - bufferInit );
}

template<typename T>
template<typename Type>
typename void BasicString<T>::__convertFloat2StringWOS( Type number, T ** bufferP, unsigned int precision, unsigned int base ) {
	_ASSERT( base <= 16 && base > 0 );

	T *& buffer( *bufferP );

	// Check if inf.
	if ( Utility::isInf<Type>(number) ) {
		( *buffer++ ) = T('#');
		( *buffer++ ) = T('i');
		( *buffer++ ) = T('n');
		( *buffer++ ) = T('f');
		return;
	}

	// Check if nan.
	if ( Utility::isNan<Type>(number) ) {
		( *buffer++ ) = T('#');
		( *buffer++ ) = T('n');
		( *buffer++ ) = T('a');
		( *buffer++ ) = T('n');
		return;
	}

	if ( number == Type( 0 ) ) {
		( *buffer ) = T( '0' );
		buffer++;
		return;
	}

	if ( number < 0 ) {
		( *buffer ) = T( '-' );
		buffer++;
		number = -number;
	}

	int comma = 1;
	while ( number >= Type( base ) ) {
		number /= Type( base );
		comma++;
	}
	if ( comma < int(10) ) {
		for (int i(0); i < comma; i++, buffer++ ) {
			int castedNumber = static_cast<int>(number);
			*buffer = BasicString<T>::numbers[ castedNumber % base ];
			number *= Type(base);
		}

		*buffer = T('.');
		buffer++;

		int precisionI = ( int ) precision;

		for (int i(0); i < precisionI; i++, buffer++ ) {
			int castedNumber = static_cast< int >( number );
			*buffer = BasicString<T>::numbers[ castedNumber % base ];
			number *= Type(base);
		}
	} else {
		comma--;
		{
			int castedNumber = static_cast< int >( number );
			*buffer = BasicString<T>::numbers[ castedNumber % base ];
			buffer++;
			number *= Type(base);
		}
		*buffer = T('.');
		buffer++;

		int precisionI = ( int ) precision;

		for (int i(1); i < precisionI; i++, buffer++ ) {
			int castedNumber = static_cast< int >( number );
			*buffer = BasicString<T>::numbers[ castedNumber % base ];
			number *= Type(base);
		}
		*buffer = T('E');
		buffer++;

		__convertUI2StringWOS<int>(comma, &buffer, base);
	}
}

template<typename T>
template<typename Type>
static Size BasicString<T>::_convertI2StringWOSFill( Type number, T ** bufferP, const Size & fillNb, const T & fillChar, unsigned int base ) {
	T * bufferInit( *bufferP );
	Size nbChar( _getIntegerLength( number, base ) );

	if ( nbChar < fillNb ) {
		// The output will have less characters than expected, we will have to fill.
		Size nbCharToAdd( fillNb - nbChar );
		T *& buffer( *bufferP );
		T * endIt( buffer + nbCharToAdd );
		for ( ; buffer != endIt; buffer++ ) {
			( *buffer ) = fillChar;
		}
	}

	__convertI2StringWOS( number, bufferP, base );

	return static_cast< Size >( *bufferP - bufferInit );
}

template<typename T>
template<typename Type>
static Size BasicString<T>::_convertUI2StringWOSFill( Type number, T ** bufferP, const Size & fillNb, const T & fillChar, unsigned int base ) {
	T * bufferInit( *bufferP );
	Size nbChar( _getIntegerLength( number, base ) );

	if ( nbChar < fillNb ) {
		// The output will have less characters than expected, we will have to fill.
		for ( Size i( nbChar ); i < fillNb; i++ ) {
			( **bufferP ) = fillChar;
			( *bufferP )++;
		}
	}

	__convertUI2StringWOS( number, bufferP, base );

	return static_cast< Size >( *bufferP - bufferInit );
}

///WITH SENTINEL

/*
template<typename T>
template<typename Type, unsigned int Base>
Size BasicString<T>::_convertUI2String( Type number, T * buffer ) {
	_ASSERT( Base <= 16 && Base > 0 );
	static Type tmpBuffer[ sizeof( Type ) * 8 ];

	auto bufferInit = buffer;
	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type( Base );
		if ( number < Type( Base ) ) break;
		number /= Type( Base );
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, bufferInit++ ) {
		*bufferInit = BasicString<T>::numbers[ *tmpP ];
	}
	( *bufferInit ) = T( '\0' );
	return ( Size )( bufferInit - buffer );
}
*/

template<typename T>
template<typename Type>
Size BasicString<T>::_convertUI2String( Type number, T ** bufferP, unsigned int base ) {
	T * bufferInit( *bufferP );
	__convertUI2StringWOS( number, bufferP, base );
	( **bufferP ) = T( '\0' );

	return static_cast< Size >( *bufferP - bufferInit );
}

/*
template<typename T>
template<typename Type, unsigned int Base>
Size BasicString<T>::_convertI2String( Type number, T * buffer ) {
	_ASSERT( Base <= 16 && Base > 0 );

	static Type tmpBuffer[ sizeof( Type ) * 8 ];

	auto bufferInit = buffer;
	if ( number < Type( 0 ) ) {
		( *bufferInit ) = T( '-' );
		bufferInit++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type( Base );
		if ( number < Type( Base ) ) break;
		number /= Type( Base );
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, bufferInit++ ) {
		*bufferInit = BasicString<T>::numbers[ *tmpP ];
	}
	( *bufferInit ) = T( '\0' );
	return ( Size )( bufferInit - buffer );
}
*/

template<typename T>
template<typename Type>
Size BasicString<T>::_convertI2String( Type number, T ** bufferP, unsigned int base ) {
	T * bufferInit( *bufferP );
	__convertI2StringWOS( number, bufferP, base );
	( **bufferP ) = T( '\0' );

	return static_cast< Size >( *bufferP - bufferInit );
}

/*
template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
Size BasicString<T>::_convertFloat2String( Type number, T * buffer ) {
	_ASSERT( Base <= 16 && Precision < 50 );

	if ( number == INFINITY ) {
		buffer[ 0 ] = T( 'I' );
		buffer[ 1 ] = T( 'N' );
		buffer[ 2 ] = T( 'F' );
		return Size( 3 );
	}


	auto bufferInit = buffer;

	if ( number == Type( 0 ) ) {
		( *bufferInit ) = T( '0' );
		bufferInit++;
		( *bufferInit ) = T( '\0' );
		return 1;
	}

	if ( number < 0 ) {
		( *bufferInit ) = T( '-' );
		bufferInit++;
		number = -number;
	}

	int comma = 1;
	while ( number > Type( Base ) ) {
		number /= Type( Base );
		comma++;
	}
	while ( number < Type( 1 ) ) {
		number *= Type( Base );
		comma--;
	}
	int i;
	if ( comma < 1 ) {
		bufferInit[ 0 ] = T( '0' );
		bufferInit++;
	} else {
		for ( i = 0; i < comma; i++, bufferInit++ ) {
			unsigned long long int castedNumber = ( unsigned long long int )number;
			*bufferInit = BasicString<T>::numbers[ castedNumber % Base ];
			number *= Type( Base );
		}
	}
	*bufferInit = T( '.' );
	bufferInit++;

	for ( i = comma; i < ( int ) Precision; i++, bufferInit++ ) {
		unsigned long long int castedNumber = ( unsigned long long int )number;
		*bufferInit = BasicString<T>::numbers[ castedNumber % Base ];
		number *= Type( Base );
	}
	( *bufferInit ) = T( '\0' );
	return ( Size )( bufferInit - buffer );
}
*/

template<typename T>
template<typename Type>
Size BasicString<T>::_convertFloat2String( Type number, T ** bufferP, unsigned int precision, unsigned int base ) {
	T * bufferInit( *bufferP );
	__convertFloat2StringWOS( number, bufferP, precision, base );
	( **bufferP ) = T( '\0' );

	return static_cast< Size >( *bufferP - bufferInit );
}




/************************************************************************/
/* toCString()                                                          */
/************************************************************************/


template<typename T>
template<typename EndFunc>
inline void BasicString<T>::copy(const BasicString<T>::Iterator* itP, const EndFunc& endFunc) {
	const BasicString<T>::Iterator & it(*itP);

	const typename BasicString<T>::Iterator beginIt(it);
	for ( ; !endFunc(it); it++ );
	const typename BasicString<T>::Iterator endIt(it);

	Size copySize(endIt - beginIt);
	Size bufferSize(copySize + Size(1));

	resize(bufferSize);

	Utility::copy(beginIt, copySize);

	this->dataTable[ copySize ] = BasicString<T>::ElemType('\0');
}

template<typename T>
template<typename C>
Size BasicString<T>::toCString( const C & c, T * buffer ) {
	buffer[ 0 ] = c;
	buffer[ 1 ] = T( '\0' );
	return Size( 1 );
}

template<typename T>
Size BasicString<T>::toCString( const char & c, T * buffer ) {
	buffer[ 0 ] = c;
	buffer[ 1 ] = T( '\0' );
	return Size( 1 );
}

template<typename T>
Size BasicString<T>::toCString( const wchar_t & c, T * buffer ) {
	buffer[ 0 ] = c;
	buffer[ 1 ] = T( '\0' );
	return Size( 1 );
}

/*
template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( unsigned char number, T * buffer ) {
	return _convertUI2String<unsigned char, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( unsigned short number, T * buffer ) {
	return _convertUI2String<unsigned short, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( unsigned int number, T * buffer ) {
	return _convertUI2String<unsigned int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( int number, T * buffer ) {
	return _convertI2String<int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( unsigned long long int number, T * buffer ) {
	return _convertUI2String<unsigned long long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( long long int number, T * buffer ) {
	return _convertI2String<long long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( unsigned long int number, T * buffer ) {
	return _convertUI2String<unsigned long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCString( long int number, T * buffer ) {
	return _convertI2String<long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
Size BasicString<T>::toCString( double number, T * buffer ) {
	return _convertFloat2String<double, Precision, Base>( number, buffer );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
Size BasicString<T>::toCString( float number, T * buffer ) {
	return _convertFloat2String<float, Precision, Base>( number, buffer );
}
*/

template<typename T>
Size BasicString<T>::toCString( unsigned char number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned short number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned int number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( int number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned long long int number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( long long int number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned long int number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( long int number, T * buffer, unsigned int base ) {
	return toCString( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( double number, T * buffer, unsigned int precision, unsigned int base ) {
	return toCString( number, &buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCString( float number, T * buffer, unsigned int precision, unsigned int base ) {
	return toCString( number, &buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCString( bool b, T * buffer ) {
	return toCString( b, &buffer );
}

template<typename T>
inline Size BasicString<T>::toCString( const typename Math::Compare::Value & compareValue, T * buffer ) {
	return toCString( compareValue, &buffer );
}

template<typename T>
Size BasicString<T>::toCString( unsigned char number, T ** buffer, unsigned int base ) {
	return _convertUI2String<unsigned char>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned short number, T ** buffer, unsigned int base ) {
	return _convertUI2String<unsigned short>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned int number, T ** buffer, unsigned int base ) {
	return _convertUI2String<unsigned int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( int number, T ** buffer, unsigned int base ) {
	return _convertI2String<int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned long long int number, T ** buffer, unsigned int base ) {
	return _convertUI2String<unsigned long long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( long long int number, T ** buffer, unsigned int base ) {
	return _convertI2String<long long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( unsigned long int number, T ** buffer, unsigned int base ) {
	return _convertUI2String<unsigned long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( long int number, T ** buffer, unsigned int base ) {
	return _convertI2String<long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCString( double number, T ** buffer, unsigned int precision, unsigned int base ) {
	return _convertFloat2String<double>( number, buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCString( float number, T ** buffer, unsigned int precision, unsigned int base ) {
	return _convertFloat2String<float>( number, buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCString( bool b, T ** buffer ) {
	if ( b ) {
		static const T staticValues[] = { T( 't' ), T( 'r' ), T( 'u' ), T( 'e' ), T( '\0' ) };
		return BasicString<T>::copy( buffer, staticValues ) - Size( 1 );
	} else {
		static const T staticValues[] = { T( 'f' ), T( 'a' ), T( 'l' ), T( 's' ), T( 'e' ), T( '\0' ) };
		return BasicString<T>::copy( buffer, staticValues ) - Size( 1 );
	}
}

template<typename T>
inline Size BasicString<T>::toCString( const typename Math::Compare::Value & compareValue, T ** buffer ) {
	switch ( compareValue ) {
		case Math::Compare::Value::Equal:
			{
				static const T staticValues[] = { T( 'E' ), T( 'Q' ), T( 'U' ), T( 'A' ), T( 'L' ), T( '\0' ) };
				return BasicString<T>::copy( buffer, staticValues ) - Size( 1 );
			}
		case Math::Compare::Value::Greater:
			{
				static const T staticValues[] = { T( 'G' ), T( 'R' ), T( 'E' ), T( 'A' ), T( 'T' ), T( 'E' ), T( 'R' ), T( '\0' ) };
				return BasicString<T>::copy( buffer, staticValues ) - Size( 1 );
			}
		case Math::Compare::Value::Less:
			{
				static const T staticValues[] = { T( 'L' ), T( 'E' ), T( 'S' ), T( 'S' ), T( '\0' ) };
				return BasicString<T>::copy( buffer, staticValues ) - Size( 1 );
			}
		default:
			return Size( 0 );
	}
}


/************************************************************************/
/* toCString() without adding sentinel                                  */
/************************************************************************/



template<typename T>
template<typename C>
Size BasicString<T>::toCStringWOS( const C & c, T * buffer ) {
	buffer[ 0 ] = c;
	return Size( 1 );
}

template<typename T>
Size BasicString<T>::toCStringWOS( const char & c, T * buffer ) {
	buffer[ 0 ] = c;
	return Size( 1 );
}

template<typename T>
Size BasicString<T>::toCStringWOS( const wchar_t & c, T * buffer ) {
	buffer[ 0 ] = c;
	return Size( 1 );
}

/*
template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( unsigned char number, T * buffer ) {
	return _convertUI2StringWOS<unsigned char, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( unsigned short number, T * buffer ) {
	return _convertUI2StringWOS<unsigned short, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( unsigned int number, T * buffer ) {
	return _convertUI2StringWOS<unsigned int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( int number, T * buffer ) {
	return _convertI2StringWOS<int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( unsigned long long int number, T * buffer ) {
	return _convertUI2StringWOS<unsigned long long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( long long int number, T * buffer ) {
	return _convertI2StringWOS<long long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( unsigned long int number, T * buffer ) {
	return _convertUI2StringWOS<unsigned long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Base>
Size BasicString<T>::toCStringWOS( long int number, T * buffer ) {
	return _convertI2StringWOS<long int, Base>( number, buffer );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
Size BasicString<T>::toCStringWOS( double number, T * buffer ) {
	return _convertFloat2StringWOS<double, Precision, Base>( number, buffer );
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
Size BasicString<T>::toCStringWOS( float number, T * buffer ) {
	return _convertFloat2StringWOS<float, Precision, Base>( number, buffer );
}
*/

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned char number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned short number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned int number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( int number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned long long int number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( long long int number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned long int number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( long int number, T * buffer, unsigned int base ) {
	return toCStringWOS( number, &buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( double number, T * buffer, unsigned int precision, unsigned int base ) {
	return toCStringWOS( number, &buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( float number, T * buffer, unsigned int precision, unsigned int base ) {
	return toCStringWOS( number, &buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( bool b, T * buffer ) {
	return toCStringWOS( b, &buffer );
}

template<typename T>
inline Size BasicString<T>::toCStringWOS( const typename Math::Compare::Value & compareValue, T * buffer ) {
	return toCStringWOS( compareValue, &buffer );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned char number, T ** buffer, unsigned int base ) {
	return _convertUI2StringWOS<unsigned char>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned short number, T ** buffer, unsigned int base ) {
	return _convertUI2StringWOS<unsigned short>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned int number, T ** buffer, unsigned int base ) {
	return _convertUI2StringWOS<unsigned int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( int number, T ** buffer, unsigned int base ) {
	return _convertI2StringWOS<int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned long long int number, T ** buffer, unsigned int base ) {
	return _convertUI2StringWOS<unsigned long long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( long long int number, T ** buffer, unsigned int base ) {
	return _convertI2StringWOS<long long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( unsigned long int number, T ** buffer, unsigned int base ) {
	return _convertUI2StringWOS<unsigned long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( long int number, T ** buffer, unsigned int base ) {
	return _convertI2StringWOS<long int>( number, buffer, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( double number, T ** buffer, unsigned int precision, unsigned int base ) {
	return _convertFloat2StringWOS<double>( number, buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( float number, T ** buffer, unsigned int precision, unsigned int base ) {
	return _convertFloat2StringWOS<float>( number, buffer, precision, base );
}

template<typename T>
Size BasicString<T>::toCStringWOS( bool b, T ** bufferP ) {
	if ( b ) {
		static const T staticValues[] = { T( 'T' ), T( 'R' ), T( 'U' ), T( 'E' ) };
		return BasicString<T>::copy( bufferP, staticValues );
	} else {
		static const T staticValues[] = { T( 'F' ), T( 'A' ), T( 'L' ), T( 'S' ), T( 'E' ) };
		return BasicString<T>::copy( bufferP, staticValues );
	}
}

template<typename T>
inline Size BasicString<T>::toCStringWOS( const typename Math::Compare::Value & compareValue, T ** bufferP ) {
	switch ( compareValue ) {
		case Math::Compare::Value::Equal:
			{
				static const T staticValues[] = { T( 'E' ), T( 'Q' ), T( 'U' ), T( 'A' ), T( 'L' ) };
				return BasicString<T>::copy( bufferP, staticValues );
			}
		case Math::Compare::Value::Greater:
			{
				static const T staticValues[] = { T( 'G' ), T( 'R' ), T( 'E' ), T( 'A' ), T( 'T' ), T( 'E' ), T( 'R' ) };
				return BasicString<T>::copy( bufferP, staticValues );
			}
		case Math::Compare::Value::Less:
			{
				static const T staticValues[] = { T( 'L' ), T( 'E' ), T( 'S' ), T( 'S' ) };
				return BasicString<T>::copy( bufferP, staticValues );
			}
	}
}


/************************************************************************/
/* To CStringWOSFill                                                    */
/************************************************************************/

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned char number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned short number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned int number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( int number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );

}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned long long int number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( long long int number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned long int number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( long int number, T * buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return toCStringWOSFill( number, &buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned char number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertUI2StringWOSFill<unsigned char>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned short number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertUI2StringWOSFill<unsigned short>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned int number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertUI2StringWOSFill<unsigned int>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( int number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertI2StringWOSFill<int>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned long long int number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertUI2StringWOSFill<unsigned long long int>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( long long int number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertI2StringWOSFill<long int>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( unsigned long int number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertUI2StringWOSFill<unsigned long int>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
Size BasicString<T>::toCStringWOSFill( long int number, T ** buffer, const Size & fillNb, const T & fillChar, unsigned int base ) {
	return _convertI2StringWOSFill<long int>( number, buffer, fillNb, fillChar, base );
}

template<typename T>
inline void BasicString<T>::toCStringHexadecimal(unsigned char uc, T** itP) {
	T*& it(*itP);

	unsigned char c0(uc >> 4);
	unsigned char c1(uc & 0xF);

	it[ 0 ] = BasicString<T>::numbers[ c0 ];
	it[ 1 ] = BasicString<T>::numbers[ c1 ];

	it += 2;
}


/************************************************************************/
/* From CString                                                         */
/************************************************************************/
/*
template<typename T>
template<typename Type, unsigned int Base, typename EndFunc>
static Type BasicString<T>::_toSignedInteger( const T ** itParam, const EndFunc & endFunc ) {
	const T *& it( *itParam );
	for ( ; *it == T( ' ' ); it++ );		//Spaces are useless

	if ( endFunc(it) )
		return 0;

	Type result;
	if ( *it == T( '-' ) ) {			//Check the sign
		it++;
		if ( !endFunc( it ) ) {
			result = -( *it - 48 );
			it++;
		} else
			return 0;
	} else {
		if ( !endFunc( it ) ) {
			result = *it - 48;
			it++;
		} else
			return 0;
	}

	for ( ; !endFunc( it ) ; it++ ) {	//Start the computation
		result = result * Base + ( *it - T( '0' ) );
	}

	return result;
}


template<typename T>
template<typename Type, unsigned int Base, typename EndFunc>
static Type BasicString<T>::_toUnsignedInteger( const T ** itParam, const EndFunc & endFunc ) {
	const T *& it( *itParam );
	for ( ; *it == T( ' ' ); it++ );		//Spaces are useless

	if ( endFunc( it ) )
		return 0;

	_ASSERT( *it != T( '-' ) );

	Type result;
	if ( !endFunc( it ) ) {
		result = *it - 48;
		it++;
	} else
		return 0;

	for ( ; !endFunc( it ); it++ ) {	//Start the computation
		result = result * Base + ( *it - T( '0' ) );
	}

	return result;
}

template<typename T>
template<typename Type, unsigned int Base, typename EndFunc>
static Type BasicString<T>::_toFloat( const T ** itParam, const EndFunc & endFunc ) {
	const T *& it( *itParam );
	for ( ; *it == T( ' ' ); it++ );		//Spaces are useless

	if ( endFunc( it ) )
		return 0;

	Type result = 0;
	bool negative;
	if ( *it == T( '-' ) ) {			//Check the sign
		it++;
		negative = true;
	} else {
		negative = false;
	}


	for ( ; !endFunc( it ) && *it != T( '.' ); it++ ) {			//Start the computation
		result = result * Type( Base ) + ( Type ) ( *it - T( '0' ) );
	}

	if ( *it == T( '.' ) )
		it++;

	Type exp = Base;
	for ( ; !endFunc( it ) ; it++ ) {
		result += ( Type ) ( *it - T( '0' ) ) / ( exp );
		exp *= Base;
	}

	if ( negative )
		result *= Type( -1 );

	return result;
}
*/


template<typename T>
template<typename Type, typename EndFunc>
static Type BasicString<T>::_toSignedInteger( const T ** itP, unsigned int base, const EndFunc & endFunc ) {
	const T *& it( *itP);
	for ( ; *it == T( ' ' ); it++ );		//Spaces are useless

	if ( endFunc( it ) )
		return 0;

	Type result;
	if ( *it == T( '-' ) ) {			//Check the sign
		it++;
		if ( !endFunc( it ) ) {
			result = -( *it - 48 );
			it++;

			for ( ; !endFunc(it); it++ ) {	//Start the computation
				result = result * base - ( *it - T('0') );
			}

		} else
			return 0;
	} else {
		if ( !endFunc( it ) ) {
			result = *it - 48;
			it++;

			for ( ; !endFunc(it); it++ ) {	//Start the computation
				result = result * base + ( *it - T('0') );
			}

		} else
			return 0;
	}

	return result;
}


template<typename T>
template<typename Type, typename EndFunc>
static Type BasicString<T>::_toUnsignedInteger( const T ** itP, unsigned int base, const EndFunc & endFunc ) {
	const T *& it( *itP);
	for ( ; *it == T( ' ' ); it++ );		//Spaces are useless

	if ( endFunc( it ) )
		return 0;

	_ASSERT( *it != T( '-' ) );

	Type result;
	if ( !endFunc( it ) ) {
		result = *it - 48;
		it++;
	} else
		return 0;

	for ( ; !endFunc( it ) ; it++ ) {	//Start the computation
		result = result * base + ( *it - T( '0' ) );
	}

	return result;
}

template<typename T>
template<typename EndFunc>
inline bool BasicString<T>::_toBool(const T** itP, const EndFunc& endFunc) {
	const T*& it(*itP);

	if ( *it == T('t') || *it == T('1') ) {
		return true;
	} else {
		return false;
	}
}

template<typename T>
template<typename EndFunc>
inline BasicString<T> BasicString<T>::_toString(const T** itP, const EndFunc& endFunc) {
	const T*& it(*itP);

	const typename BasicString<T>::Iterator beginIt(it);
	for ( ; !endFunc(it); it++ );
	const typename BasicString<T>::Iterator endIt(it);

	return BasicString<T>(beginIt, Size(endIt - beginIt));
}

template<typename T>
template<typename Type, typename EndFunc>
static Type BasicString<T>::_toFloat( const T ** itP, unsigned int base, const EndFunc & endFunc ) {
	const T *& it( *itP);
	for ( ; *it == T( ' ' ); it++ );		//Spaces are useless

	if ( endFunc( it ) )
		return Type( 0 );

	Type result( 0 );
	bool negative;
	if ( *it == T( '-' ) ) {			//Check the sign
		it++;
		negative = true;
	} else {
		negative = false;
	}

	const Type baseType(static_cast<Type>(base) );
	for ( ; !endFunc( it ) && *it != T( '.' ); it++ ) {			//Start the computation
		result *= baseType;
		result += Type( *it - T( '0' ) );
	}

	if ( *it == T( '.' ) )
		it++;

	Type oneOnBase( Type( 1.0 ) / baseType );
	Type exp( oneOnBase );
	for ( ; !endFunc( it ) ; it++ ) {
		result += Type( *it - T( '0' ) ) * ( exp );
		exp *= oneOnBase;
	}

	if ( negative )
		result = -result;

	return result;
}


/*
template<typename T>
template<unsigned int Base, typename EndFunc>
char BasicString<T>::toChar( const T * it, const EndFunc & endFunc ) {
	return _toSignedInteger<char, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
short BasicString<T>::toShort( const T * it, const EndFunc & endFunc ) {
	return _toSignedInteger<short, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
int BasicString<T>::toInt( const T * it, const EndFunc & endFunc ) {
	return _toSignedInteger<int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
long int BasicString<T>::toLong( const T * it, const EndFunc & endFunc ) {
	return _toSignedInteger<long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
long long int BasicString<T>::toLongLong( const T * it, const EndFunc & endFunc ) {
	return _toSignedInteger<long long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned char BasicString<T>::toUChar( const T * it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned char, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned short BasicString<T>::toUShort( const T * it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned short, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned int BasicString<T>::toUInt( const T * it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned long int BasicString<T>::toULong( const T * it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned long long int BasicString<T>::toULongLong( const T * it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned long long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
float BasicString<T>::toFloat( const T * buffer, const EndFunc & endFunc ) {
	const T ** tmpBuffer( &buffer );
	return _toFloat<float, Base, EndFunc>( tmpBuffer, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
double BasicString<T>::toDouble( const T * buffer, const EndFunc & endFunc ) {
	return _toFloat<double, Base, EndFunc>( buffer, endFunc );
}
*/










template<typename T>
template<typename C>
inline C BasicString<T>::fromString() const {
	return _fromString(reinterpret_cast< const C* >( NULL ));
}

template<typename T>
template<typename EndFunc>
inline BasicString<T> BasicString<T>::toString(const T* it, const EndFunc& endFunc) {
	const T** itP(&it);
	return _toString<EndFunc>(itP, endFunc);
}

template<typename T>
template<typename EndFunc>
char BasicString<T>::toChar( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toSignedInteger<char, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
short BasicString<T>::toShort( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toSignedInteger<short, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
int BasicString<T>::toInt( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toSignedInteger<int, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
long int BasicString<T>::toLong( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toSignedInteger<long int, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
long long int BasicString<T>::toLongLong( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toSignedInteger<long long int, EndFunc>( itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned char BasicString<T>::toUChar( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toUnsignedInteger<unsigned char, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned short BasicString<T>::toUShort( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toUnsignedInteger<unsigned short, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned int BasicString<T>::toUInt( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toUnsignedInteger<unsigned int, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned long int BasicString<T>::toULong( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toUnsignedInteger<unsigned long int, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned long long int BasicString<T>::toULongLong( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toUnsignedInteger<unsigned long long int, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
float BasicString<T>::toFloat( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toFloat<float, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
double BasicString<T>::toDouble( const T * it, unsigned int base, const EndFunc & endFunc ) {
	const T ** itP( &it );
	return _toFloat<double, EndFunc>(itP, base, endFunc );
}

template<typename T>
template<typename EndFunc>
inline double BasicString<T>::toBool(const T* it, const EndFunc& endFunc) {
	const T** itP(&it);
	return _toBool<EndFunc>(itP, endFunc);
}








/*
template<typename T>
template<unsigned int Base, typename EndFunc>
char BasicString<T>::toChar( const T ** it, const EndFunc & endFunc ) {
	return _toSignedInteger<char, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
short BasicString<T>::toShort( const T ** it, const EndFunc & endFunc ) {
	return _toSignedInteger<short, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
int BasicString<T>::toInt( const T ** it, const EndFunc & endFunc ) {
	return _toSignedInteger<int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
long int BasicString<T>::toLong( const T ** it, const EndFunc & endFunc ) {
	return _toSignedInteger<long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
long long int BasicString<T>::toLongLong( const T ** it, const EndFunc & endFunc ) {
	return _toSignedInteger<long long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned char BasicString<T>::toUChar( const T ** it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned char, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned short BasicString<T>::toUShort( const T ** it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned short, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned int BasicString<T>::toUInt( const T ** it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned long int BasicString<T>::toULong( const T ** it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
unsigned long long int BasicString<T>::toULongLong( const T ** it, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned long long int, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
float BasicString<T>::toFloat( const T ** it, const EndFunc & endFunc ) {
	return _toFloat<float, Base, EndFunc>( it, endFunc );
}

template<typename T>
template<unsigned int Base, typename EndFunc>
double BasicString<T>::toDouble( const T ** it, const EndFunc & endFunc ) {
	return _toFloat<double, Base, EndFunc>( it, endFunc );
}
*/








template<typename T>
template<typename EndFunc>
inline BasicString<T> BasicString<T>::toString(const T** it, const EndFunc& endFunc) {
	return _toString<EndFunc>(it, endFunc);
}

template<typename T>
template<typename EndFunc>
char BasicString<T>::toChar( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toSignedInteger<char, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
short BasicString<T>::toShort( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toSignedInteger<short, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
int BasicString<T>::toInt( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toSignedInteger<int, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
long int BasicString<T>::toLong( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toSignedInteger<long int, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
long long int BasicString<T>::toLongLong( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toSignedInteger<long long int, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned char BasicString<T>::toUChar( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned char, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned short BasicString<T>::toUShort( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned short, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned int BasicString<T>::toUInt( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned int, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned long int BasicString<T>::toULong( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned long int, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
unsigned long long int BasicString<T>::toULongLong( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toUnsignedInteger<unsigned long long int, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
float BasicString<T>::toFloat( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toFloat<float, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
double BasicString<T>::toDouble( const T ** it, unsigned int base, const EndFunc & endFunc ) {
	return _toFloat<double, EndFunc>( it, base, endFunc );
}

template<typename T>
template<typename EndFunc>
inline double BasicString<T>::toBool(const T** it, const EndFunc& endFunc) {
	return _toBool<EndFunc>(it, endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline C BasicString<T>::fromString(const T* it, const EndFunc& endFunc) {
	const T** itP(&it);
	return fromString(itP, endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline C BasicString<T>::fromString(const T** it, const EndFunc& endFunc) {
	return _fromString(it, endFunc, reinterpret_cast< const C* >( NULL ));
}

template<typename T>
template<typename C, typename EndFunc>
inline char BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const char*) {
	return toChar(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline int BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const int*) {
	return toInt(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline short BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const short*) {
	return toShort(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline long int BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const long int*) {
	return toLong(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline long long int BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const long long int*) {
	return toLongLong(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline unsigned char BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const unsigned char*) {
	return toUChar(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline unsigned int BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const unsigned int*) {
	return toUInt(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline unsigned short BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const unsigned short*) {
	return toShort(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline unsigned long int BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const unsigned long int*) {
	return toULong(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline unsigned long long int BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const unsigned long long int*) {
	return toULongLong(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline float BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const float*) {
	return toFloat(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline double BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const double*) {
	return toDouble(it, unsigned int(10), endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline bool BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, const bool*) {
	return toBool(it, endFunc);
}

template<typename T>
template<typename C, typename EndFunc>
inline T* BasicString<T>::_fromString(const T** it, const EndFunc& endFunc, ...) {
	return *it;
}





/************************************************************************/
/* From StringASCII                                                     */
/************************************************************************/
/*
template<typename T>
template<unsigned int Base>
char BasicString<T>::toChar() const {
	return _toSignedInteger<char, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
short BasicString<T>::toShort() const {
	return _toSignedInteger<short, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
int BasicString<T>::toInt() const {
	return _toSignedInteger<int, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
long int BasicString<T>::toLong() const {
	return _toSignedInteger<long int, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
long long int BasicString<T>::toLongLong() const {
	return _toSignedInteger<long long int, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
unsigned char BasicString<T>::toUChar() const {
	return _toUnsignedInteger<unsigned char, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
unsigned short BasicString<T>::toUShort() const {
	return _toUnsignedInteger<unsigned short, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
unsigned int BasicString<T>::toUInt() const {
	return _toUnsignedInteger<unsigned int, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
unsigned long int BasicString<T>::toULong() const {
	return _toUnsignedInteger<unsigned long int, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
unsigned long long int BasicString<T>::toULongLong() const {
	return _toUnsignedInteger<unsigned long long int, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
float BasicString<T>::toFloat() const {
	return _toFloat<float, Base>( this -> dataTable );
}

template<typename T>
template<unsigned int Base>
double BasicString<T>::toDouble() const {
	return _toFloat<double, Base>( this -> dataTable );
}
*/










template<typename T>
char BasicString<T>::toChar( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toSignedInteger<char>( &tmpBuffer, base );
}

template<typename T>
short BasicString<T>::toShort( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toSignedInteger<short>( &tmpBuffer, base );
}

template<typename T>
int BasicString<T>::toInt( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toSignedInteger<int>( &tmpBuffer, base );
}

template<typename T>
long int BasicString<T>::toLong( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toSignedInteger<long int>( &tmpBuffer, base );
}

template<typename T>
long long int BasicString<T>::toLongLong( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toSignedInteger<long long int>( &tmpBuffer, base );
}

template<typename T>
unsigned char BasicString<T>::toUChar( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toUnsignedInteger<unsigned char>( &tmpBuffer, base );
}

template<typename T>
unsigned short BasicString<T>::toUShort( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toUnsignedInteger<unsigned short>( &tmpBuffer, base );
}

template<typename T>
unsigned int BasicString<T>::toUInt( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toUnsignedInteger<unsigned int>( &tmpBuffer, base );
}

template<typename T>
unsigned long int BasicString<T>::toULong( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toUnsignedInteger<unsigned long int>( &tmpBuffer, base );
}

template<typename T>
unsigned long long int BasicString<T>::toULongLong( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toUnsignedInteger<unsigned long long int>( &tmpBuffer, base );
}

template<typename T>
float BasicString<T>::toFloat( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toFloat<float>( &tmpBuffer, base );
}

template<typename T>
double BasicString<T>::toDouble( unsigned int base ) const {
	const T * tmpBuffer( this -> dataTable );
	return _toFloat<double>( &tmpBuffer, base );
}

template<typename T>
inline bool BasicString<T>::toBool() const {
	const T* tmpBuffer(this -> dataTable);
	return _toBool(&tmpBuffer);
}

template<typename T>
inline char BasicString<T>::_fromString(const char*) const {
	return toChar();
}

template<typename T>
inline int BasicString<T>::_fromString(const int*) const {
	return toInt();
}

template<typename T>
inline short BasicString<T>::_fromString(const short*) const {
	return toShort();
}

template<typename T>
inline long int BasicString<T>::_fromString(const long int*) const {
	return toLong();
}

template<typename T>
inline long long int BasicString<T>::_fromString(const long long int*) const {
	return toLongLong();
}

template<typename T>
inline unsigned char BasicString<T>::_fromString(const unsigned char*) const {
	return toUChar();
}

template<typename T>
inline unsigned int BasicString<T>::_fromString(const unsigned int*) const {
	return toUInt();
}

template<typename T>
inline unsigned short BasicString<T>::_fromString(const unsigned short*) const {
	return toUShort();
}

template<typename T>
inline unsigned long int BasicString<T>::_fromString(const unsigned long int*) const {
	return toULong();
}

template<typename T>
inline unsigned long long int BasicString<T>::_fromString(const unsigned long long int*) const {
	return toULongLong();
}

template<typename T>
inline float BasicString<T>::_fromString(const float*) const {
	return toFloat();
}

template<typename T>
inline double BasicString<T>::_fromString(const double*) const {
	return toDouble();
}

template<typename T>
inline bool BasicString<T>::_fromString(const bool*) const {
	return toBool();
}

template<typename T>
inline BasicString<T>& BasicString<T>::_fromString(...) const {
	return *this;
}










/************************************************************************/
/* toString()                                                           */
/************************************************************************/


template<typename T>
inline const BasicString<T>& BasicString<T>::toString(const BasicString<T>& str) {
	return str;
}

template<typename T>
BasicString<T> BasicString<T>::toString( const T & c ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( 2 );
	newStr.size = toCString( c, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

/*
template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( unsigned char number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned char ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( unsigned short number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( short ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( unsigned int number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned int ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( int number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( int ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( unsigned long long int number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned long long int ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( long long int number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( long long int ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( unsigned long int number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned long int ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString( long int number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( long int ) * 8 );
	newStr.size = toCString<Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> BasicString<T>::toString( double number ) {
	BasicString<T> newStr;
	newStr._allocateNoNullDelete( sizeof( double ) * 8 + Precision );
	newStr.size = toCString<Precision, Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> BasicString<T>::toString( float number ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( float ) * 8 + Precision );
	newStr.size = toCString<Precision, Base>( number, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}
*/

template<typename T>
BasicString<T> BasicString<T>::toString( unsigned char number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned char ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( unsigned short number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned short ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}


template<typename T>
BasicString<T> BasicString<T>::toString( unsigned int number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned int ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( int number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( int ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( unsigned long long int number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned long long int ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( long long int number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( long long int ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( unsigned long int number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( unsigned long int ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( long int number, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( long int ) * 8 );
	newStr.size = toCString( number, newStr.dataTable, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( double number, unsigned int precision, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( double ) * 8 + precision );
	newStr.size = toCString( number, newStr.dataTable, precision, base );
	newStr._updateIterators();
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString( float number, unsigned int precision, unsigned int base ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( sizeof( float ) * 8 + precision );
	newStr.size = toCString( number, newStr.dataTable, precision, base );
	newStr._updateIterators();
	return newStr;
}


template<typename T>
BasicString<T> BasicString<T>::toString( bool b ) {
	BasicString<T> newStr( Vector<T>::protectedCtor::null );
	newStr._allocateNoNullDelete( 6 );
	newStr.size = toCString( b, newStr.dataTable );
	newStr._updateIterators();
	return newStr;
}



/************************************************************************/
/* OPERATOR =                                                           */
/************************************************************************/

template<typename T>
BasicString<T> & BasicString<T>::operator=( const unsigned short & ui ) {
	if ( Vector<T>::getMaxSize() < 7 )
		Vector<T>::_allocateNoNull( 7 );
	this -> size = toCString( ui, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::operator=( const unsigned char & ui ) {
	if ( Vector<T>::getMaxSize() < 5 )
		Vector<T>::_allocateNoNull( 5 );
	this -> size = toCString( ui, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const int & i ) {
	if ( Vector<T>::getMaxSize() < 10 )
		Vector<T>::_allocateNoNull( 10 );
	this -> size = toCString( i, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const unsigned int & ui ) {
	if ( Vector<T>::getMaxSize() < 10 )
		Vector<T>::_allocateNoNull( 10 );
	this -> size = toCString( ui, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const long int & l ) {
	if ( Vector<T>::getMaxSize() < 21 )
		Vector<T>::_allocateNoNull( 21 );
	this -> size = toCString( l, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const unsigned long int & ul ) {
	if ( Vector<T>::getMaxSize() < 21 )
		Vector<T>::_allocateNoNull( 21 );
	this -> size = toCString( ul, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const long long int & ll ) {
	if ( Vector<T>::getMaxSize() < 21 )
		Vector<T>::_allocateNoNull( 21 );
	this -> size = toCString( ll, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const unsigned long long int & ull ) {
	if ( Vector<T>::getMaxSize() < 21 )
		Vector<T>::_allocateNoNull( 21 );
	this -> size = toCString( ull, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const double & d ) {
	if ( Vector<T>::getMaxSize() < 11 )
		Vector<T>::_allocateNoNull( 11 );
	this -> size = toCString( d, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const float & d ) {
	if ( Vector<T>::getMaxSize() < 6 )
		Vector<T>::_allocateNoNull( 6 );
	this -> size = toCString( d, this -> dataTable );
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
template<typename C, size_t N>
BasicString<T> & BasicString<T>::operator=( const C( &str )[ N ] ) {
	auto sizePlusOne( N + 1 );
	if ( getMaxSize() < sizePlusOne )
		reserve( sizePlusOne );
	Utility::copy( this -> dataTable, str, sizePlusOne );
	this -> size = N;
	_updateIterators();
	return *this;
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator=( const BasicString<C> & str ) {
	auto sizePlusOne( str.getSize() + 1 );
	if ( getMaxSize() < sizePlusOne )
		reserve( sizePlusOne );
	Utility::copy( this -> dataTable, str.getData(), sizePlusOne );
	this -> size = str.getSize();
	_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=( const BasicString<T> & str ) {
	return operator=<T>( str );
}



template<typename T>
BasicString<T> & BasicString<T>::operator=( BasicString<T> && str ) {
	Vector<T>::operator=( Utility::toRValue( str ) );
	return *this;
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator=( C * const & str ) {
	this -> size = BasicString<C>::getSize( str );
	if ( getMaxSize() < this -> size + 1 ) {
		_allocateNoNull( this -> size + 1 );
	}
	_updateIterators();
	setValueI( this -> size, T( '\0' ) );
	Utility::copy( this->dataTable, str, this -> size );

	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::operator=( const T & c ) {
	this -> size = 1;
	if ( getMaxSize() < 2 ) {
		_allocateNoNull( 2 );
	}
	_updateIterators();
	setValueI( 0, T( c ) );
	setValueI( 1, T( '\0' ) );

	return *this;
}



template<typename T>
BasicString<T> & BasicString<T>::operator=( const bool & b ) {
	if ( getMaxSize() < 6 ) {
		_allocateNoNull( 6 );
	}
	this ->  size = toCString( b, this -> dataTable );
	_updateIterators();
	return *this;
}







/************************************************************************/
/* LOGICALS                                                             */
/************************************************************************/
template<typename T>
bool BasicString<T>::operator<=( const BasicString<T> & text ) const {
	for ( Size i = 0; i < this -> size; i++ ) {
		const T & t1 = this -> dataTable[ i ];
		const T & t2 = text.dataTable[ i ];

		if ( t1 == t2 ) continue;
		else if ( t1 < t2 ) return true;
		else return false;
	}
	return true;
}

template<typename T>
bool BasicString<T>::operator>=( const BasicString<T> & text ) const {
	for ( Size i = 0; i < this -> size; i++ ) {
		const T & t1 = this -> dataTable[ i ];
		const T & t2 = text.dataTable[ i ];

		if ( t1 == t2 ) continue;
		else if ( t1 > t2 ) return true;
		else return false;
	}
	return true;
}

template<typename T>
bool BasicString<T>::operator<( const BasicString<T> & text ) const {
	for ( Size i = 0; i < this -> size; i++ ) {
		const T & t1 = this -> dataTable[ i ];
		const T & t2 = text.dataTable[ i ];

		if ( t1 == t2 ) continue;
		else if ( t1 < t2 ) return true;
		else return false;
	}
	return false;
}

template<typename T>
bool BasicString<T>::operator>( const BasicString<T> & text ) const {
	for ( Size i = 0; i < this -> size; i++ ) {
		const T & t1 = this -> dataTable[ i ];
		const T & t2 = text.dataTable[ i ];

		if ( t1 == t2 ) continue;
		else if ( t1 > t2 ) return true;
		else return false;
	}
	return false;
}

template<typename T>
bool BasicString<T>::operator==( const BasicString<T> & text ) const {
	return Vector<T>::operator==( text );
}

template<typename T>
bool BasicString<T>::operator!=( const BasicString<T> & text ) const {
	return Vector<T>::operator!=( text );
}



template<typename T>
bool BasicString<T>::operator==( const T & c ) const {
	return Vector<T>::operator==( c );
}

template<typename T>
bool BasicString<T>::operator!=( const T & c ) const {
	return Vector<T>::operator!=( c );
}


template<typename T>
bool BasicString<T>::operator<( const T & c ) const {
	return Vector<T>::operator<( c );
}
template<typename T>
bool BasicString<T>::operator>( const T & c ) const {
	return Vector<T>::operator>( c );
}

template<typename T>
bool BasicString<T>::operator<=( const T & c ) const {
	return Vector<T>::operator<=( c );
}
template<typename T>
bool BasicString<T>::operator>=( const T & c ) const {
	return Vector<T>::operator>=( c );
}

/************************************************************************/
/* CONVERSION                                                           */
/************************************************************************/


/************************************************************************/
/* OTHERS                                                               */
/************************************************************************/


template<typename T>
template<typename C>
Size BasicString<T>::getSize( C * const & str ) {
	Size size( 0 );
	constexpr const C end( '\0' );
	for ( size; str[ size ] != end; size++ );
	return size;
}

template<typename T>
template<typename C, size_t N>
Size BasicString<T>::getSize( const C( &str )[ N ] ) {
	return Size( N - 1 );
}


template<typename T>
typename BasicString<T>::Iterator BasicString<T>::getLastIt( const BasicString<T> & str ) const {
	if ( !str.getSize() || this -> size < str.getSize() )
		goto getLastItNOTFOUND;

	auto iteratorSize( getEnd() - str.getSize() + 1 );
	for ( auto it( iteratorSize - 1 ); it >= getBegin();) {
		for ( Size j = 0; j < str.getSize(); j++ ) {
			if ( *( it + j ) != str[ j ] ) {
				goto getLastItENDLOOP;
			}
		}
		return it;
getLastItENDLOOP:it--;
	}
getLastItNOTFOUND:return getEnd();
}

template<typename T>
typename BasicString<T>::Iterator BasicString<T>::getFirstIt( const BasicString<T> & str ) const {
	if ( !str.getSize() || this -> size < str.getSize() )
		goto getFirstItNOTFOUND;

	auto iteratorSize = getEnd() - str.getSize() + 1;
	for ( auto it = getBegin(); it < iteratorSize;) {
		for ( Size j = 0; j < str.getSize(); j++ ) {
			if ( *( it + j ) != str[ j ] ) {
				goto getFirstItENDLOOP;
			}
		}
		return it;
getFirstItENDLOOP:it++;
	}
getFirstItNOTFOUND:return getEnd();
}

template<typename T>
typename BasicString<T>::Iterator BasicString<T>::getLastIt( const T & c ) const {
	for ( auto it = getEnd() - 1; it >= getBegin(); it-- ) {
		if ( *it == c )
			return it;
	}
	return getEnd();
}

template<typename T>
typename BasicString<T>::Iterator BasicString<T>::getFirstIt( const T & c ) const {
	for ( auto it = getBegin(); it < getEnd(); it++ ) {
		if ( *it == c ) {
			return it;
		}
	}
	return getEnd();
}


template<typename T>
Size BasicString<T>::getLast( const BasicString<T> & str ) const {
	return BasicString<T>::getLast( this -> dataTable, this -> size, str.getData(), str.getSize() );
}

template<typename T>
Size BasicString<T>::getFirst( const BasicString<T> & str ) const {
	return BasicString<T>::getFirst( this -> dataTable, this -> size, str.getData(), str.getSize() );
}

template<typename T>
Size BasicString<T>::getLast( const T & c ) const {
	return BasicString<T>::getLast( this -> dataTable, getSize(), c );
}

template<typename T>
Size BasicString<T>::getFirst( const T & c ) const {
	return BasicString<T>::getFirst( this -> dataTable, getSize(), c );
}



template<typename T>
Size BasicString<T>::getLast( const T * buffer, Size bufferSize, const T * toSearch, Size toSearchSize ) {
	if ( !toSearchSize || bufferSize < toSearchSize )
		goto NOTFOUND;

	Size iteratorSize = bufferSize - toSearchSize;
	for ( Size i = iteratorSize; i >= 0;) {
		for ( Size j = 0; j < toSearchSize; j++ ) {
			if ( buffer[ i + j ] != toSearch[ j ] ) {
				goto ENDLOOP;
			}
		}
		return i;

ENDLOOP:i--;
	}
NOTFOUND:return BasicString<T>::overflow;
}

template<typename T>
Size BasicString<T>::getFirst( const T * buffer, Size bufferSize, const T * toSearch, Size toSearchSize ) {
	if ( !toSearchSize || bufferSize < toSearchSize )
		goto NOTFOUND;

	Size iteratorSize = bufferSize - toSearchSize + 1;
	for ( Size i = 0; i < iteratorSize;) {
		for ( Size j = 0; j < toSearchSize; j++ ) {
			if ( buffer[ i + j ] != toSearch[ j ] ) {
				goto ENDLOOP;
			}
		}
		return i;

ENDLOOP:i++;
	}
NOTFOUND:return BasicString<T>::overflow;
}

template<typename T>
Size BasicString<T>::getLast( const T * buffer, Size bufferSize, const T & c ) {
	for ( Size i = bufferSize - 1; i >= 0; i-- ) {
		if ( buffer[ i ] == c ) {
			return i;
		}
	}
	return BasicString<T>::overflow;
}

template<typename T>
Size BasicString<T>::getFirst( const T * buffer, Size bufferSize, const T & c ) {
	for ( Size i = 0; i < bufferSize; i++ ) {
		if ( buffer[ i ] == c ) {
			return i;
		}
	}
	return BasicString<T>::overflow;
}


template<typename T>
Size BasicString<T>::getLast( const T * buffer, const T * toSearch ) {
	return BasicString<T>::getLast( buffer, BasicString<T>::getSize( buffer ), toSearch, BasicString<T>::getSize( toSearch ) );
}

template<typename T>
inline bool BasicString<T>::encodeBase64(const Vector<unsigned char>& dataVector, T** itP) {

	struct EncodeFunctor {
		EncodeFunctor(const T* encodingTable) : encodingTable(encodingTable) {}

		void encode(T* outputIt, const unsigned char* inputIt) const {
			unsigned char c0(( inputIt[ 0 ] & 0xFC ) >> 2);
			unsigned char c1(( inputIt[ 0 ] & 0x3 ) << 4 | ( inputIt[ 1 ] & 0xF0 ) >> 4);
			unsigned char c2(( inputIt[ 1 ] & 0xF ) << 2 | ( inputIt[ 2 ] & 0xC0 ) >> 6);
			unsigned char c3(inputIt[ 2 ] & 0x3F);

			outputIt[ 0 ] = this->encodingTable[ c0 ];
			outputIt[ 1 ] = this->encodingTable[ c1 ];
			outputIt[ 2 ] = this->encodingTable[ c2 ];
			outputIt[ 3 ] = this->encodingTable[ c3 ];
		}

		void encode1(T* outputIt, const unsigned char* inputIt) const {
			unsigned char c0(( inputIt[ 0 ] & 0xFC ) >> 2);
			unsigned char c1(( inputIt[ 0 ] & 0x3 ) << 4);

			outputIt[ 0 ] = this->encodingTable[ c0 ];
			outputIt[ 1 ] = this->encodingTable[ c1 ];
			outputIt[ 2 ] = T('=');
			outputIt[ 3 ] = T('=');
		}

		void encode2(T* outputIt, const unsigned char* inputIt) const {
			unsigned char c0(( inputIt[ 0 ] & 0xFC ) >> 2);
			unsigned char c1(( inputIt[ 0 ] & 0x3 ) << 4 | ( inputIt[ 1 ] & 0xF0 ) >> 4);
			unsigned char c2(( inputIt[ 1 ] & 0xF ) << 2);

			outputIt[ 0 ] = this->encodingTable[ c0 ];
			outputIt[ 1 ] = this->encodingTable[ c1 ];
			outputIt[ 2 ] = this->encodingTable[ c2 ];
			outputIt[ 3 ] = T('=');
		}

		const T* encodingTable;
	};

	static EncodeFunctor encodeFunctor(BasicString<T>::base64CharTable);

	T*& it(*itP);

	const unsigned char* inputIt(dataVector.getBegin());
	const unsigned char* inputEndIt(dataVector.getEnd());
	const unsigned char* inputEndItFloor(dataVector.getBegin() + dataVector.getSize() / Size(3) * Size(3));
	for ( ; inputIt < inputEndItFloor; it += 4, inputIt+=3 ) {
		encodeFunctor.encode(it, inputIt);
	}

	Size remainingBytes(inputEndIt - inputEndItFloor);

	switch ( remainingBytes ) {
		case Size(1):
			{
				encodeFunctor.encode1(it, inputIt);
				it += 4;
				break;
			}
		case Size(2):
			{
				encodeFunctor.encode2(it, inputIt);
				it += 4;
				break;
			}
	}

	return true;
}

template<typename T>
inline BasicString<T> BasicString<T>::encodeBase64(const Vector<unsigned char>& dataVector) {
	BasicString<T> outputStr;
	Size newSize(BasicString<T>::getBase64EncodeSize(dataVector));
	outputStr.resize(newSize);

	T* it(outputStr.dataTable);
	encodeBase64(dataVector, &it);

	return outputStr;
}

template<typename T>
inline bool BasicString<T>::decodeBase64(const BasicString<T>& inputStr, unsigned char** itP) {
	struct DecodeFunctor {
		DecodeFunctor(const T * encodingTable){
			for ( Size i(0); i < Size(256); i++ ) {
				// Use the value 0 as an error.
				this->decodingTable[ i ] = unsigned char(0);
			}

			for ( unsigned char i(0); i < Size(64); i++ ) {
				this->decodingTable[ unsigned char(encodingTable[ i ]) ] = i;
			}
			this->decodingTable[ unsigned char(T('=')) ] = unsigned char(0);
		}

		void decode(unsigned char* outputIt, const T* inputIt) {
			unsigned char c0(this->decodingTable[inputIt[ 0 ]]);
			unsigned char c1(this->decodingTable[ inputIt[ 1 ] ]);
			unsigned char c2(this->decodingTable[ inputIt[ 2 ] ]);
			unsigned char c3(this->decodingTable[ inputIt[ 3 ] ]);

			unsigned char b0(c0 << 2 | c1 >> 4);
			unsigned char b1(c1 << 4 | c2 >> 2);
			unsigned char b2(c2 << 6 | c3);

			outputIt[ 0 ] = b0;
			outputIt[ 1 ] = b1;
			outputIt[ 2 ] = b2;
		}

		void decode2(unsigned char* outputIt, const T* inputIt) {
			unsigned char c0(this->decodingTable[ inputIt[ 0 ] ]);
			unsigned char c1(this->decodingTable[ inputIt[ 1 ] ]);

			unsigned char b0(c0 << 2 | c1 >> 4);

			outputIt[ 0 ] = b0;
		}

		void decode3(unsigned char* outputIt, const T* inputIt) {
			unsigned char c0(this->decodingTable[ inputIt[ 0 ] ]);
			unsigned char c1(this->decodingTable[ inputIt[ 1 ] ]);
			unsigned char c2(this->decodingTable[ inputIt[ 2 ] ]);

			unsigned char b0(c0 << 2 | c1 >> 4);
			unsigned char b1(c1 << 4 | c2 >> 2);

			outputIt[ 0 ] = b0;
			outputIt[ 1 ] = b1;
		}

		unsigned char decodingTable[256];
	};

	static DecodeFunctor decodeFunctor(BasicString<T>::base64CharTable);

	unsigned char*& it(*itP);

	const T* inputIt(inputStr.getBegin());
	const T* inputEndIt(inputStr.getEnd());

	// Remove the padding characters.
	for ( ; inputEndIt > inputStr.getBegin() && *( inputEndIt - Size(1) ) == T('='); inputEndIt-- );

	const T* inputEndItFloor(inputStr.getBegin() + (inputEndIt - inputStr.getBegin() ) / Size(4) * Size(4));

	for ( ; inputIt < inputEndItFloor; inputIt += 4, it += 3 ) {
		decodeFunctor.decode(it, inputIt);
	}

	Size remainingChars(inputEndIt - inputIt);

	switch ( remainingChars ) {
		case Size(1):
			{
				return false;
			}
		case Size(2):
			{
				decodeFunctor.decode2(it, inputIt);
				it += 1;
				break;
			}
		case Size(3):
			{
				decodeFunctor.decode3(it, inputIt);
				it += 2;
				break;
			}
	}

	return true;
}

template<typename T>
inline Vector<unsigned char> BasicString<T>::decodeBase64(const BasicString<T>& inputStr) {
	Vector<unsigned char> outputVector;
	Size reserveSize(BasicString<T>::getBase64DecodeReserveSize(inputStr));
	outputVector.reserve(reserveSize);

	unsigned char* it(outputVector.dataTable);
	if ( !decodeBase64(inputStr, &it) ) {
		outputVector.clear();
		return outputVector;
	}

	Size newSize(it - outputVector.getBegin());
	outputVector.resize(newSize);

	return outputVector;
}

template<typename T>
inline Size BasicString<T>::getBase64EncodeSize(const Vector<unsigned char>& dataVector) {
	return ( dataVector.getSize() + Size(2) ) / Size(3) * Size(4);
}

template<typename T>
inline Size BasicString<T>::getBase64DecodeReserveSize(const BasicString<T>& inputStr) {
	return ( inputStr.getSize() * Size(3) + Size(3) ) / Size(4);
}

template<typename T>
inline bool BasicString<T>::encodeHexadecimal(const Vector<unsigned char>& dataVector, T** itP) {
	
	T*& it(*itP);

	unsigned char* inputIt(dataVector.getBegin());
	const unsigned char* inputEndIt(dataVector.getEnd());

	for ( ; inputIt < inputEndIt; inputIt++ ) {
		BasicString<T>::toCStringHexadecimal(dataVector.getValueIt(inputIt), &it);
	}

	return true;
}

template<typename T>
inline BasicString<T> BasicString<T>::encodeHexadecimal(const Vector<unsigned char>& dataVector) {
	BasicString<T> outputStr;
	outputStr.resize(dataVector.getSize() << 1);

	T* it(outputStr.dataTable);
	if ( !encodeHexadecimal(dataVector, &it) ) {
		outputStr.clear();
	}

	return outputStr;
}

template<typename T>
inline bool BasicString<T>::decodeHexadecimal(const BasicString<T>& inputStr, unsigned char** itP) {
	struct DecodeFunctor {
		DecodeFunctor(const T* encodingTable) {
			for ( Size i(0); i < Size(256); i++ ) {
				// Use the value 0 as an error.
				this->decodingTable[ i ] = unsigned char(0);
			}

			for ( unsigned char i(0); i < Size(16); i++ ) {
				this->decodingTable[ unsigned char(encodingTable[ i ]) ] = i;
			}
		}

		void decode(unsigned char* outputIt, const T* inputIt) {
			unsigned char c0(this->decodingTable[ inputIt[ 0 ] ]);
			unsigned char c1(this->decodingTable[ inputIt[ 1 ] ]);

			unsigned char b0(c0 << 4 | c1);

			outputIt[ 0 ] = b0;
		}

		unsigned char decodingTable[ 256 ];
	};

	static DecodeFunctor decodeFunctor(BasicString<T>::numbers);

	unsigned char*& it(*itP);

	const unsigned char* endIt(it + (inputStr.getSize() >> 1));
	const T* inputIt(inputStr.getBegin());

	for ( ; it < endIt; inputIt += 2, it++ ) {
		decodeFunctor.decode(it, inputIt);
	}

	return true;
}

template<typename T>
inline Vector<unsigned char> BasicString<T>::decodeHexadecimal(const BasicString<T>& inputStr) {
	Vector<unsigned char> outputVector;
	outputVector.resize(inputStr.getSize() >> 1);

	unsigned char* it(outputVector.dataTable);
	if ( !BasicString<T>::decodeHexadecimal(inputStr, &it) ) {
		outputVector.clear();
	}

	return outputVector;
}

template<typename T>
Size BasicString<T>::getFirst( const T * buffer, const T * toSearch ) {
	T c( buffer[ 0 ] );
	for ( Size i = 0; c != T( '\0' );) {

		const T * d = &( toSearch[ 0 ] );
		for ( Size j = 0; *d != T( '\0' ); j++, d = &( toSearch[ j ] ) ) {
			if ( buffer[ i + j ] != *d ) {
				goto ENDLOOP;
			}
		}
		return i;

ENDLOOP:
		i++;
		c = buffer[ i ];
	}
NOTFOUND:return BasicString<T>::overflow;
}

template<typename T>
Size BasicString<T>::getLast( const T * buffer, const T & c ) {
	return BasicString<T>::getLast( buffer, BasicString<T>::getSize( buffer ), c );
}

template<typename T>
Size BasicString<T>::getFirst( const T * buffer, const T & c ) {
	const T * d = &( buffer[ 0 ] );
	for ( Size i = 0; *d != T( '\0' ); i++, d = &( buffer[ i ] ) ) {
		if ( buffer[ i ] == c )
			return i;
	}
	return BasicString<T>::overflow;
}




template<typename T>
void BasicString<T>::clear() {
	this -> size = 0;
	this -> dataTable[ 0 ] = T( '\0' );
	_updateIterators();
}

template<typename T>
Vector<BasicString<T>> BasicString<T>::split( const T & delimiter ) const {
	return BasicString<T>::split( *this, delimiter );
}

template<typename T>
Vector<BasicString<T>> BasicString<T>::split( const BasicString<T> & s, const T & delimiter ) {
	Vector<BasicString<T>> v;
	Size lastIndex = 0;
	Size i;
	for ( i = 0; i < s.getSize(); i++ ) {
		const T & c = s[ i ];
		if ( c == delimiter && i != lastIndex ) {
			v.push( BasicString<T>( s.getData() + lastIndex, i - lastIndex ) );
			lastIndex = i + 1;
		}
	}
	v.push( BasicString<T>( s.getData() + lastIndex, i - lastIndex ) );

	return v;
}


template<typename T>
bool BasicString<T>::isNumeric( const BasicString<T> & v ) {
	for ( Size i( 0 ); i < v.getSize() ; i++ ) {
		const T & c = v[ i ];
		if ( c < 40 || c > 57 )
			return false;
	}
	return true;
}

template<typename T>
bool BasicString<T>::isNumeric() const {
	return BasicString<T>::isNumeric( *this );
}


template<typename T>
const T * BasicString<T>::toCString() const {
	return this -> dataTable;
}



template<typename T>
BasicString<T> BasicString<T>::getSubStr( typename BasicString<T>::Iterator beginIt, const Size size ) const {
	Size newSize;
	if ( beginIt >= getEnd() )
		return BasicString<T>();

	if ( beginIt < getBegin() )
		beginIt = getBegin();
	if ( size > getEnd() - beginIt )
		newSize = getEnd() - beginIt;
	else
		newSize = size;

	return BasicString<T>( beginIt, newSize );
}

template<typename T>
BasicString<T> BasicString<T>::getSubStr( typename BasicString<T>::Iterator beginIt, typename BasicString<T>::Iterator endIt ) const {
	if ( beginIt >= getEnd() || endIt < getBegin() )
		return BasicString<T>();

	if ( beginIt < getBegin() )
		beginIt = getBegin();

	if ( endIt > getEnd() )
		endIt = getEnd();

	return BasicString<T>( beginIt, Size( endIt - beginIt ) );
}

template<typename T>
BasicString<T> BasicString<T>::toLower() const {
	// Pre allocate the new string with the same size.
	BasicString<T> lowerString( BasicString<T>::protectedCtor::null );
	lowerString._allocateNoNullDelete( this -> getMaxSize() );
	lowerString.size = this -> size;
	lowerString._updateIterators();

	static const T offset( BasicString<T>::ElemType( 'a' ) - BasicString<T>::ElemType( 'A' ) );

	// Iterate
	typename BasicString<T>::Iterator itLower( lowerString.getBegin() );
	for ( typename BasicString<T>::Iterator it( this -> getBegin() ) ; it != this -> getEnd() ; it++, itLower++ ) {
		const T & e( *it );
		if ( e >= BasicString<T>::ElemType( 'A' ) && e <= BasicString<T>::ElemType( 'Z' ) ) {
			*itLower = e + offset;
		} else {
			*itLower = e;
		}
	}
	*itLower = T( '\0' );
	return lowerString;
}

template<typename T>
BasicString<T> BasicString<T>::toUpper() const {
	// Pre allocate the new string with the same size.
	BasicString<T> lowerString( BasicString<T>::protectedCtor::null );
	lowerString._allocateNoNullDelete( this -> getMaxSize() );
	lowerString.size = this -> size;
	lowerString._updateIterators();

	static const T offset( BasicString<T>::ElemType( 'a' ) - BasicString<T>::ElemType( 'A' ) );

	// Iterate
	typename BasicString<T>::Iterator itLower( lowerString.getBegin() );
	for ( typename BasicString<T>::Iterator it( this -> getBegin() ) ; it != this -> getEnd() ; it++, itLower++ ) {
		const T & e( *it );
		if ( e >= BasicString<T>::ElemType( 'a' ) && e <= BasicString<T>::ElemType( 'z' ) ) {
			*itLower = e - offset;
		} else {
			*itLower = e;
		}
	}
	*itLower = T( '\0' );
	return lowerString;
}


template<typename T>
BasicString<T> BasicString<T>::getSubStr( const Size index, const Size size ) const {
	Size newSize;
	if ( index > this -> size )
		return BasicString<T>();

	if ( size > this->size - index )
		newSize = this->size - index;
	else
		newSize = size;

	return BasicString<T>( this -> dataTable + index, newSize );
}

template<typename T>
BasicString<T> BasicString<T>::getFileName() const {
	Size lastSlash = getLast( T( '/' ) );
	if ( lastSlash == BasicString<T>::overflow )
		return *this;

	return BasicString<T>( this -> dataTable + lastSlash + 1, this -> size - lastSlash );
}

template<typename T>
BasicString<T> BasicString<T>::getDirectory() const {
	Size lastSlash = getLast( T( '/' ) );
	if ( lastSlash == BasicString<T>::overflow )
		return *this;

	BasicString<T> newString;
	newString.concat( this -> dataTable, lastSlash + 1 );
	return newString;
}







template<typename T>
void BasicString<T>::replace( const BasicString<T> & toReplace, const BasicString<T> & byThis ) {
	BasicString<T> newString;
	newString.allocate( this -> getMaxSize() + byThis.getSize() );

	Size lastIndexSrc = 0;
	Size newFound = 0;
	while ( newFound < getSize() ) {

		newFound = getFirst( this -> dataTable + lastIndexSrc, getSize() - lastIndexSrc, toReplace.getData(), toReplace.getSize() );
		if ( newFound == BasicString<T>::overflow ) {
			newFound = getSize();

			Size cropedSize = newFound - lastIndexSrc;
			newString.concat( this -> dataTable + lastIndexSrc, cropedSize );

			break;
		}

		Size cropedSize = newFound - lastIndexSrc;
		newString.concat( this -> dataTable + lastIndexSrc, cropedSize );

		lastIndexSrc += cropedSize + toReplace.getSize();		//1 is the searchSize

		newString.concat( byThis );
	}

	*this = newString;
}






template<typename T>
void BasicString<T>::replace( const T & toReplace, const BasicString<T> & byThis ) {
	BasicString<T> newString;
	newString.allocate( this -> getMaxSize() + byThis.getSize() );

	Size lastIndexSrc = 0;
	Size newFound = 0;
	while ( newFound < getSize() ) {

		newFound = getFirst( this -> dataTable + lastIndexSrc, getSize() - lastIndexSrc, toReplace );
		if ( newFound == BasicString<T>::overflow ) {
			newFound = getSize();

			Size cropedSize = newFound - lastIndexSrc;
			newString.concat( this -> dataTable + lastIndexSrc, cropedSize );

			break;
		}

		Size cropedSize = newFound - lastIndexSrc;
		newString.concat( this -> dataTable + lastIndexSrc, cropedSize );

		lastIndexSrc += cropedSize + 1;		//1 is the searchSize

		newString += byThis;
	}
	*this = newString;
}

template<typename T>
void BasicString<T>::replace( const T & toReplace, const T & byThis ) {
	for ( auto it = getBegin(); it < getEnd(); it++ ) {
		if ( *it == toReplace )
			*it = byThis;
	}
}





template<typename T>
std::ostream & operator<<( std::ostream & stream, const BasicString<T> & str ) {
	stream << str.toCString();
	return stream;
}

template<typename Stream, typename T>
Stream& operator<<(Stream& stream, const BasicString<T>& str) {
	stream << str.toCString();
	return stream;
}















template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<( C * const & str ) {
	return concat( str );
}


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<( const BasicString<C> & str ) {
	return concat( str );
}

template<typename T>
template<typename C, size_t N>
BasicString<T> & BasicString<T>::operator<<( const C( &str )[ N ] ) {
	return concat( str );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const unsigned char & uc ) {
	return concat( uc );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const unsigned short & us ) {
	return concat( us );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const int & i ) {
	return concat( i );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const unsigned int & ui ) {
	return concat( ui );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const long int & l ) {
	return concat( l );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const unsigned long int & ul ) {
	return concat( ul );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const long long int & ll ) {
	return concat( ll );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const unsigned long long int & ull ) {
	return concat( ull );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const double & d ) {
	return concat( d );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const float & f ) {
	return concat( f );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const bool & b ) {
	return concat( b );
}


/*
template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<(const C & c) {
	return concat(c);
}*/


template<typename T>
BasicString<T> & BasicString<T>::operator<<( const char & c ) {
	return concat( c );
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<( const wchar_t & c ) {
	return concat( c );
}


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<( const Vector<C> & v ) {
	concat( "[ " );
	for ( Size i = 0; i < v.getSize(); i++ ) {
		if ( i ) concat( " | " );
		operator<<( v[ i ] );
	}
	return concat( " ]" );
}








template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=( C * const & str ) {
	return concat( str );
}


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=( const BasicString<C> & str ) {
	Size newSize = getSize() + str.getSize();

	if ( newSize >= this -> maxSize ) {
		_extendBuffer(newSize);
		_updateIterators();
	}

	copy( this -> iteratorEnd, str.getData(), str.getSize() + 1 );
	this -> size = newSize;
	Vector<T>::_updateIterators();
	return *this;
}

template<typename T>
template<typename C, size_t N>
BasicString<T> & BasicString<T>::operator+=( const C( &str )[ N ] ) {
	return concat( str );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const unsigned char & uc ) {
	return concat( uc );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const unsigned short & us ) {
	return concat( us );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const int & i ) {
	return concat( i );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const unsigned int & ui ) {
	return concat( ui );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const long int & l ) {
	return concat( l );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const unsigned long int & ul ) {
	return concat( ul );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const long long int & ll ) {
	return concat( ll );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const unsigned long long int & ull ) {
	return concat( ull );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const double & d ) {
	return concat( d );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const float & f ) {
	return concat( f );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const bool & b ) {
	return concat( b );
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=( const C & c ) {
	return concat( c );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const char & c ) {
	return concat( c );
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=( const wchar_t & c ) {
	return concat( c );
}



template<typename T>
void BasicString<T>::resize( Size newSize ) {
	if ( newSize + 1 > this -> maxSize ) {
		_extendBuffer( newSize + 1 );
	}
	this -> size = newSize;
	_updateIterators();
	*( this -> iteratorEnd ) = T( '\0' );
}


template<typename T>
template<typename Stream>
bool BasicString<T>::read( Stream * stream ) {
	if ( !IO::read( stream, &this -> size ) ) {
		this -> size = 0;
		_allocateNoNull( 1 );
		_updateIterators();
		this -> dataTable[ 0 ] = T( '\0' );
		return false;
	}
	return read( stream, this -> size );
}

template<typename T>
template<typename Stream>
bool BasicString<T>::read(Stream* stream, Size size ) {
	this -> size = size;
	this -> maxSize = this -> size + 1;
	_allocateNoNull( this -> maxSize );
	_updateIterators();


	if ( !IO::read( stream, getData(), getSize() ) ) {
		this -> size = 0;
		_allocateNoNull( 1 );
		_updateIterators();
		this -> dataTable[ 0 ] = T( '\0' );
		return false;
	}
	this -> dataTable[ getSize() ] = T( '\0' );
	return true;
}


template<typename T>
template<typename Stream>
bool BasicString<T>::writeReadable(Stream* stream ) const {
	if ( !IO::writeBuffer( stream, getData(), getSize() ) )
		return false;
	return true;
}


/************************************************************************/
/* format()                                                             */
/************************************************************************/
template<typename T>
template<typename C>
void BasicString<T>::__format( const C * referenceStringBegin, const C * referenceStringEnd, BasicString<T> * newString ) {
	newString -> _concatWOS( referenceStringBegin, Size( referenceStringEnd - referenceStringBegin ) );
}

template<typename T>
template<typename C, typename T1, typename... Types>
void BasicString<T>::__format( const C * referenceStringBegin, const C * referenceStringEnd, BasicString<T> * newString, const T1 & arg1, Types ... args ) {
	for ( auto it = referenceStringBegin; it != referenceStringEnd; it++ ) {
		if ( *it == T( '/' ) && it + 1 < referenceStringEnd ) {
			if ( *( it + 1 ) == T('/') ) {
				newString -> _concatWOS(T('/'));
				it++;
			} else if ( *( it + 1 ) == T('%') ) {
				newString -> _concatWOS(T('%'));
				it++;
			}
		} else if ( *it == T( '%' ) ) {
			newString -> _concatWOS( arg1 );
			return __format( it + 1, referenceStringEnd, newString, args... );
		} else {
			auto itBegin( it );
			for ( ; *it != T( '%' ) && *it != T( '\0' ); it++ );
			newString -> _concatWOS( itBegin, Size( it - itBegin ) );
			it--;
		}
	}
}

template<typename T>
template<typename T1, typename... Types>
BasicString<T> BasicString<T>::format( const BasicString<T> referenceString, const T1 & arg1, Types ... args ) {
	return _format( referenceString.getBegin(), referenceString.getEnd(), arg1, args... );
}

template<typename T>
template<typename C, typename T1, typename... Types>
BasicString<T> BasicString<T>::_format( const C * referenceStringBegin, const C * referenceStringEnd, const T1 & arg1, Types ... args ) {
	BasicString<T> newString(Vector<T>::protectedCtor::null);

	Size referenceStringSize( referenceStringEnd - referenceStringBegin );

	newString.size = 0;
	if ( referenceStringSize == 0 )
		newString._allocateNoNullDelete( 1 );
	else
		newString._allocateNoNullDelete( referenceStringSize * 2 );

	newString.iteratorEnd = newString.dataTable;

	__format( referenceStringBegin, referenceStringEnd, &newString, arg1, args... );
	*( newString.dataTable + newString.size ) = T( '\0' );

	return newString;
}

template<typename T>
template<typename C, typename T1, typename... Types>
BasicString<T> BasicString<T>::format( C * const & str, const T1 & arg1, Types ... args ) {
	const C * referenceStringIteratorBegin( str );
	const C * referenceStringIteratorEnd( referenceStringIteratorBegin + BasicString<C>::getSize( str ) );

	return _format( referenceStringIteratorBegin, referenceStringIteratorEnd, arg1, args... );
}

template<typename T>
template<typename C, size_t N, typename T1, typename... Types>
BasicString<T> BasicString<T>::format( const C( &str )[ N ], const T1 & arg1, Types ... args ) {
	const C * referenceStringIteratorBegin( str );
	const C * referenceStringIteratorEnd( referenceStringIteratorBegin + BasicString<C>::getSize( str ) );

	return _format( referenceStringIteratorBegin, referenceStringIteratorEnd, arg1, args... );
}


template<typename T>
Math::Compare::Value BasicString<T>::compare( const BasicString<T> & x, const BasicString<T> & y ) {
	const Size minSize(Math::min(x.getSize(), y.getSize()));
	for ( Size i( 0 ); i < minSize; i++ ) {
		const T & t1 = x[ i ];
		const T & t2 = y[ i ];

		if ( t1 == t2 ) continue;
		else if ( t1 > t2 ) return Math::Compare::Value::Greater;
		else return Math::Compare::Value::Less;
	}
	if ( x.getSize() < y.getSize() ) {
		return Math::Compare::Value::Less;
	} else if ( x.getSize() > y.getSize() ) {
		return Math::Compare::Value::Greater;
	} else {
		return Math::Compare::Value::Equal;
	}
}


template<typename T>
bool BasicString<T>::IsEndSentinel::operator()( const T * it ) const {
	return ( *it == T( '\0' ) );
}

template<typename T>
BasicString<T>::IsEndIterator::IsEndIterator( const T * endIt ) :
	endIt( endIt ) {
}

template<typename T>
bool BasicString<T>::IsEndIterator::operator()( const T * it ) const {
	return ( it == this -> endIt );
}

template<typename T>
template<typename N, int nbChars, int base>
N BasicString<T>::parseNumber( const T ** c ) {
	return __ParseNumber<N, nbChars, base>::compute( c );
}

template<typename T>
template<size_t N>
Size BasicString<T>::copy( T ** destinationBuffer, const T( &sourceBuffer )[ N ] ) {
	Utility::copy( *destinationBuffer, sourceBuffer, N );
	destinationBuffer += N;
	return static_cast< Size >( N );
}

template<typename T>
template<typename Type>
static Size BasicString<T>::_getIntegerLength( Type i, unsigned int base ) {
	Size nbChar;

	if ( i > Type(0) ) {
		nbChar = Size(1);
		Type tmpI( base );
		while ( tmpI <= i && tmpI >= Type( base ) ) {
			nbChar++;
			tmpI *= base;
		}
	} else if ( i < Type(0) ) {
		nbChar = Size(2);
		Type tmpI( -Type(base) );
		while ( tmpI >= i ) {
			nbChar++;
			tmpI *= base;
		}
	} else {
		nbChar = 1;
	}

	return nbChar;
}

template<typename T>
template<typename Type>
static Size BasicString<T>::_getIntegerPositiveLength( Type i, unsigned int base ) {
	Size nbChar;

	if ( i > Type(0) ) {
		nbChar = Size(0);
		Type tmpI( 1 );
		while ( tmpI <= i ) {
			nbChar++;
			tmpI *= base;
		}
	} else {
		// i == 0 as i is positive.
		nbChar = Size(1);
	}
	return nbChar;
}


