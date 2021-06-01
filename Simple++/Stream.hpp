template<typename T>
StreamT<T>::StreamT() : 
	Vector<T>(),
	position( 0 ) {

}

template<typename T>
StreamT<T>::StreamT( const T * data, const typename Vector<T>::Size size ) : 
	Vector<T>(size),
	position(0)
{
	typename Vector<T>::Size sizeBytes( size * Vector<T>::elementSize );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable ), reinterpret_cast< const unsigned char * >( data ), sizeBytes );
}

template<typename T>
template<typename C>
StreamT<T>::StreamT( const C * data, const typename Vector<T>::Size size ) : 
Vector<T>( Vector<T>::ctor::null ),
 position(0) {
	_assert( size );
	typename Vector<T>::Size sizeBytes( size * Vector<C>::elementSize );
	this->size = sizeBytes / Vector<T>::elementSize;
	this->_allocateNoNullDelete( this->size );
	this->_updateIterators();

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this->dataTable ), reinterpret_cast< const unsigned char * >( data ), sizeBytes );

	

}

template<typename T>
StreamT<T> & StreamT<T>::operator<<( const T & data ) {
	if ( this -> position >= this -> maxSize ) {
		this -> reserve( this->position * 2 );
	}
	this->dataTable[ this->position ] = data;
	this->position++;
}

template<typename T>
template<typename C>
StreamT<T> & StreamT<T>::operator<<( const C & data ) {
	constexpr typename Vector<T>::Size bytesToBeAdded( Vector<C>::elementSize );
	constexpr typename Vector<T>::Size offsetToBeAdded( bytesToBeAdded / Vector<T>::elementSize );
	typename Vector<T>::Size positionAfter( this->position + offsetToBeAdded );
	if ( positionAfter > this->maxSize ) {
		this->reserve( positionAfter * 2 );
	}

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( this -> dataTable + this -> position ), reinterpret_cast< const unsigned char * >( &data ), bytesToBeAdded );
	this->position = positionAfter;

	if ( this->position > this->size ) {
		this->size = this->position;
	}

	return *this;
}

template<typename T>
typename Vector<T>::Size StreamT<T>::getPosition() const {
	return this -> position;
}

template<typename T>
const typename Vector<T>::Iterator StreamT<T>::getPositionIt() const {
	return this -> getBegin() + this->position;
}

template<typename T>
typename Vector<T>::Iterator StreamT<T>::getPositionIt() {
	return this->getBegin() + this->position;
}

template<typename T>
void StreamT<T>::setPosition( typename Vector<T>::Size pos ) {
	this->position = pos;
}

template<typename T>
void StreamT<T>::setPosition( typename Vector<T>::Iterator pos ) {
	this->position = pos - getBegin();
}

template<typename T>
void StreamT<T>::concat( const StreamT<T> & stream ) {
	typename Vector<T>::Size bytesToBeAdded( stream.getSize() * Vector<T>::elementSize );
	this->resize( getSize() + bytesToBeAdded );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( getEnd() ), reinterpret_cast< unsigned char * >( stream.getBegin() ), bytesToBeAdded );
}


template<typename T>
template<typename C>
void StreamT<T>::concat( const StreamT<C> & stream ) {
	typename Vector<T>::Size bytesToBeAdded( stream.getSize() * Vector<C>::elementSize );
	this->resize( getSize() + bytesToBeAdded / Vector<T>::elementSize + 1 );

	// Copy bytes directly.
	Vector<unsigned char>::copy( reinterpret_cast< unsigned char * >( getEnd() ), reinterpret_cast< unsigned char * >( stream.getBegin() ), bytesToBeAdded );
}