template<typename T>
StreamT<T>::StreamT() :
	Vector<T>(),
	position( 0 ) {}

template<typename T>
StreamT<T>::StreamT( const T * data, const Size size ) :
	StreamT<T>( data, size, size ) {}

template<typename T>
template<typename C>
StreamT<T>::StreamT( const C * data, const Size size ) :
	Vector<T>( Vector<T>::ctor::null ),
	position( 0 ) {
	_assert( size );
	Size sizeBytes( size * Vector<C>::elementSize );
	this->size = sizeBytes / Vector<T>::elementSize;
	this->_allocateNoNullDelete( this -> size );
	this->_updateIterators();

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable ), reinterpret_cast< const unsigned char * >( data ), sizeBytes );
}

template<typename T>
StreamT<T>::StreamT( const T * data, const Size size, const Size maxSize ) :
	Vector<T>( Vector<T>::ctor::null ),
	position( 0 ) {
	_assert( size );
	_assert( maxSize >= size );
	Size sizeBytes( size * Vector<T>::elementSize );
	this->size = size;
	this->_allocateNoNullDelete( maxSize );
	this->_updateIterators();

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable ), reinterpret_cast< const unsigned char * >( data ), sizeBytes );
}

template<typename T>
template<typename C>
StreamT<T>::StreamT( const BasicString<C> & str ) :
	Vector<T>( Vector<T>::ctor::null ),
	position( 0 ) {
	if ( str.getSize() ) {
		Size sizeBytes( str.getSize() * Vector<C>::elementSize );
		this->size = sizeBytes / Vector<T>::elementSize;
		this->_allocateNoNullDelete( this -> size );
		this->_updateIterators();

		// Copy bytes directly.
		Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable ), reinterpret_cast< const unsigned char * >( str.getData() ), sizeBytes );
	} else {
		this -> size = 0;
		this -> maxSize = 0;
		this -> dataTable = NULL;
		this -> iteratorEnd = NULL;
	}
}



template<typename T>
Size StreamT<T>::getPosition() const {
	return this->position;
}

template<typename T>
const typename Vector<T>::Iterator StreamT<T>::getPositionIt() const {
	return this->getBegin() + this->position;
}

template<typename T>
typename Vector<T>::Iterator StreamT<T>::getPositionIt() {
	return this->getBegin() + this->position;
}

template<typename T>
void StreamT<T>::setPosition( Size pos ) {
	_assert( pos >= 0 && pos <= this->size );
	this->position = pos;
}

template<typename T>
void StreamT<T>::setPosition( typename Vector<T>::Iterator pos ) {
	_assert( pos >= getBegin() && pos <= getEnd() );
	this->position = pos - getBegin();
}

template<typename T>
bool StreamT<T>::write( const T & data ) {
	if ( this->position >= this->maxSize ) {
		this->reserve( ( this->position + 1 ) * 2 );
	}
	this->dataTable[ this->position ] = data;
	this->position++;

	return true;
}

template<typename T>
template<typename C>
bool StreamT<T>::write( const C & data ) {
	constexpr Size bytesToBeAdded( Vector<C>::elementSize );
	constexpr Size offsetToBeAdded( bytesToBeAdded / Vector<T>::elementSize );
	Size positionAfter( this->position + offsetToBeAdded );
	if ( positionAfter > this->maxSize ) {
		this->reserve( positionAfter * 2 );
	}

	*reinterpret_cast< C * >( this->dataTable + this->position ) = data;

	// Copy bytes directly.
	this->position = positionAfter;

	if ( this->position > this->size ) {
		this->size = this->position;
	}

	return true;
}

template<typename T>
template<size_t N>
bool StreamT<T>::write( const T( &data )[ N ] ) {
	return write( data, N );
}

template<typename T>
template<typename C, size_t N>
bool StreamT<T>::write( const C( &data )[ N ] ) {
	return write( data, N );
}

template<typename T>
bool StreamT<T>::write( const T * data, Size size ) {
	Size sizeInBytes( size * Vector<T>::elementSize );
	Size positionAfter( this->position + size );
	if ( positionAfter >= this->maxSize ) {
		this->reserve( positionAfter * 2 );
	}

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable + this->position ), reinterpret_cast< const unsigned char * >( data ), sizeInBytes );
	this->position = positionAfter;

	if ( this->position > this->size ) {
		this->size = this->position;
	}

	return true;
}

template<typename T>
template<typename C>
bool StreamT<T>::write( const C * data, Size size ) {
	Size bytesToBeAdded( size * Vector<C>::elementSize );
	Size offsetToBeAdded( bytesToBeAdded / Vector<T>::elementSize );
	Size positionAfter( this->position + offsetToBeAdded );
	if ( positionAfter > this->maxSize ) {
		this->reserve( positionAfter * 2 );
	}

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable + this->position ), reinterpret_cast< const unsigned char * >( data ), bytesToBeAdded );
	this->position = positionAfter;

	if ( this->position > this->size ) {
		this->size = this->position;
		this -> _updateIterators();
	}

	return true;
}

template<typename T>
bool StreamT<T>::read( T * data, Size size ) {
	Size sizeInBytes( size * Vector<T>::elementSize );
	Size positionAfter( this->position + size );

	_assert( positionAfter <= this->size );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( data ), reinterpret_cast< const unsigned char * >( this->dataTable + this->position ), sizeInBytes );
	this->position = positionAfter;

	return true;
}

template<typename T>
void StreamT<T>::concat( const StreamT<T> & stream ) {
	Size bytesToBeAdded( stream.getSize() * Vector<T>::elementSize );
	this -> resize( getSize() + stream.getSize() );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( getEnd() ), reinterpret_cast< unsigned char * >( stream.getBegin() ), bytesToBeAdded );
}


template<typename T>
template<typename C>
void StreamT<T>::concat( const StreamT<C> & stream ) {
	Size bytesToBeAdded( stream.getSize() * Vector<C>::elementSize );
	this -> resize( getSize() + bytesToBeAdded / Vector<T>::elementSize + 1 );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( getEnd() ), reinterpret_cast< unsigned char * >( stream.getBegin() ), bytesToBeAdded );
}

template<typename T>
StreamT<T> & StreamT<T>::operator<<( const T & data ) {
	write( data );
	return *this;
}

template<typename T>
template<typename C>
StreamT<T> & StreamT<T>::operator<<( const C & data ) {
	write( data );
	return *this;
}

template<typename T>
template<size_t N>
StreamT<T> & StreamT<T>::operator<<( const T( &data )[ N ] ) {
	write( data, N );
	return *this;
}

template<typename T>
template<typename C, size_t N>
StreamT<T> & StreamT<T>::operator<<( const C( &data )[ N ] ) {
	write( data, N );
	return *this;
}

template<typename T>
template<typename C>
BasicString<C> StreamT<T>::toStringRaw() const {
	Size stringSize( this->size * Vector<T>::elementSize / Vector<C>::elementSize );
	return BasicString<C>(reinterpret_cast<C *>(this->dataTable), stringSize);
}

template<typename T>
template<typename C>
BasicString<C> StreamT<T>::toStringHexa() const {
	Size stringSize( this->size * ( Vector<T>::elementSize * Size( 2 ) + 1 ) ); // Every byte takes 2 characters in hexadecimal display. We add a third for a space.
	BasicString<C> newString;
	newString.resize( stringSize );
	C * newStringData( newString.getData() );

	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		const T & v( getValueIt( it ) );

		Size nbCharWritten( BasicString<C>::toCStringWOSFill( v, &newStringData, Vector<T>::elementSize * Size( 2 ), C('0'), 16));
		if ( nbCharWritten != Vector<T>::elementSize * Size( 2 ) ) {
			int i = 42;
		}
		assert( nbCharWritten == Vector<T>::elementSize * Size( 2 ) );
		*( newStringData++ ) = C( ' ' );
	}

	assert( stringSize == newStringData - newString.getData() );

	return newString;
}