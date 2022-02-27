
template<typename I, typename T>
MapObject<I, T>::~MapObject() {

}

template<typename I, typename T>
MapObject<I, T>::MapObject() {

}


template<typename I, typename T>
MapObject<I, T>::MapObject( const I & index, const T & value ) :
	index( index ),
	value( value ) {

}


template<typename I, typename T>
void MapObject<I, T>::setValue( const T & value ) {
	this -> value = value;
}

template<typename I, typename T>
const T & MapObject<I, T>::getValue() const {
	return this -> value;
}

template<typename I, typename T>
T & MapObject<I, T>::getValue() {
	return this -> value;
}

template<typename I, typename T>
void MapObject<I, T>::setIndex( const I & index ) {
	this -> index = index;
}

template<typename I, typename T>
const I & MapObject<I, T>::getIndex() const {
	return this -> index;
}

template<typename I, typename T>
I & MapObject<I, T>::getIndex() {
	return this -> index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator==( const MapObject & o ) const {
	return this -> index == o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator>=( const MapObject & o ) const {
	return this -> index >= o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator<=( const MapObject & o ) const {
	return this -> index <= o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator>( const MapObject & o ) const {
	return this -> index > o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator<( const MapObject & o ) const {
	return this -> index < o.index;
}




template<typename I, typename T>
template<typename Stream>
bool MapObject<I, T>::write(Stream* stream ) const {
	if ( !IO::write( stream, &this -> index ) )
		return false;
	if ( !IO::write( stream, &this -> value ) )
		return false;
	return true;
}

template<typename I, typename T>
template<typename Stream>
bool MapObject<I, T>::read(Stream* stream ) {
	if ( !IO::read( stream, &this -> index ) )
		return false;
	if ( !IO::read( stream, &this -> value ) )
		return false;
	return true;
}

template<typename I, typename T>
template<typename C>
MapObject<I, T>::operator BasicString<C>() const {
	BasicString<C> str;
	str.reserve( 50 );
	str << C( '[' ) << C( ' ' ) << BasicString<C>( this -> index ) << " => " << BasicString<C>( this -> value ) << C( ' ' ) << C( ']' );
	return str;
}


