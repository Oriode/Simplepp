template<typename T>
StreamT<T>::StreamT() :
	Vector<T>(),
	position( 0 ) {}

template<typename T>
StreamT<T>::StreamT( const T * data, const typename Vector<T>::Size size ) :
	StreamT<T>( data, size, size ) {}

template<typename T>
template<typename C>
StreamT<T>::StreamT( const C * data, const typename Vector<T>::Size size ) :
	Vector<T>( Vector<T>::ctor::null ),
	position( 0 ) {
	_assert( size );
	typename Vector<T>::Size sizeBytes( size * Vector<C>::elementSize );
	this->size = sizeBytes / Vector<T>::elementSize;
	this->_allocateNoNullDelete( this -> size );
	this->_updateIterators();

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable ), reinterpret_cast< const unsigned char * >( data ), sizeBytes );
}

template<typename T>
StreamT<T>::StreamT( const T * data, const typename Vector<T>::Size size, const typename Vector<T>::Size maxSize ) :
	Vector<T>( Vector<T>::ctor::null ),
	position( 0 ) {
	_assert( size );
	_assert( maxSize >= size );
	typename Vector<T>::Size sizeBytes( size * Vector<T>::elementSize );
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
		typename Vector<T>::Size sizeBytes( str.getSize() * Vector<C>::elementSize );
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
typename Vector<T>::Size StreamT<T>::getPosition() const {
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
void StreamT<T>::setPosition( typename Vector<T>::Size pos ) {
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
	constexpr typename Vector<T>::Size bytesToBeAdded( Vector<C>::elementSize );
	constexpr typename Vector<T>::Size offsetToBeAdded( bytesToBeAdded / Vector<T>::elementSize );
	typename Vector<T>::Size positionAfter( this->position + offsetToBeAdded );
	if ( positionAfter > this->maxSize ) {
		this->reserve( positionAfter * 2 );
	}

	*reinterpret_cast< C * >( &this->dataTable[ this->position ] ) = data;

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
bool StreamT<T>::write( const T * data, typename Vector<T>::Size size ) {
	typename Vector<T>::Size sizeInBytes( size * Vector<T>::elementSize );
	typename Vector<T>::Size positionAfter( this->position + size );
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
bool StreamT<T>::write( const C * data, typename Vector<T>::Size size ) {
	typename Vector<T>::Size bytesToBeAdded( size * Vector<C>::elementSize );
	typename Vector<T>::Size offsetToBeAdded( bytesToBeAdded / Vector<T>::elementSize );
	typename Vector<T>::Size positionAfter( this->position + offsetToBeAdded );
	if ( positionAfter > this->maxSize ) {
		this->reserve( positionAfter * 2 );
	}

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable + this->position ), reinterpret_cast< const unsigned char * >( data ), bytesToBeAdded );
	this->position = positionAfter;

	if ( this->position > this->size ) {
		this->size = this->position;
	}

	return true;
}

template<typename T>
bool StreamT<T>::read( T * data, typename Vector<T>::Size size ) {
	typename Vector<T>::Size sizeInBytes( size * Vector<T>::elementSize );
	typename Vector<T>::Size positionAfter( this->position + size );

	_assert( positionAfter <= this->size );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( data ), reinterpret_cast< const unsigned char * >( this->dataTable + this->position ), sizeInBytes );
	this->position = positionAfter;

	return true;
}

template<typename T>
void StreamT<T>::concat( const StreamT<T> & stream ) {
	typename Vector<T>::Size bytesToBeAdded( stream.getSize() * Vector<T>::elementSize );
	this -> resize( getSize() + stream.getSize() );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( getEnd() ), reinterpret_cast< unsigned char * >( stream.getBegin() ), bytesToBeAdded );
}


template<typename T>
template<typename C>
void StreamT<T>::concat( const StreamT<C> & stream ) {
	typename Vector<T>::Size bytesToBeAdded( stream.getSize() * Vector<C>::elementSize );
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
	typename Vector<C>::Size stringSize( this->size * Vector<T>::elementSize / Vector<C>::elementSize );
	return BasicString<C>(reinterpret_cast<C *>(this->dataTable), stringSize);
}

template<typename T>
template<typename C>
BasicString<C> StreamT<T>::toStringHexa() const {
	typename Vector<T>::Size stringSize( this->size * ( Vector<T>::elementSize * Vector<T>::Size( 2 ) + 1 ) ); // Every byte takes 2 characters in hexadecimal display. We add a third for a space.
	BasicString<C> newString( stringSize );
	C * newStringData( newString.getData() );

	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		const T & v( getValueIt( it ) );

		typename Vector<C>::Size nbCharWritten( BasicString<C>::toCStringWOS( v, &newStringData, 16 ) );
		assert( nbCharWritten == Vector<T>::elementSize * Vector<T>::Size( 2 ) );
		*( newStringData++ ) = C( ' ' );
	}
	return newString;
}