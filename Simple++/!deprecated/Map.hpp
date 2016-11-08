

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
bool MapObject<I, T>::write( std::fstream * fileStream ) const {
	if ( !SimpleIO::write( fileStream, &this -> index ) )
		return false;
	if ( !SimpleIO::write( fileStream, &this -> value ) )
		return false;
	return true;
}

template<typename I, typename T>
bool MapObject<I, T>::read( std::fstream * fileStream ) {
	if ( !SimpleIO::read( fileStream, &this -> index ) )
		return false;
	if ( !SimpleIO::read( fileStream, &this -> value ) )
		return false;
	return true;
}

template<typename I, typename T>
template<typename C>
MapObject<I, T>::operator BasicString<C>() const {
	BasicString<C> str;
	str.reserve( 50 );
	str << C('[') << C(' ') << BasicString<C>(this -> index) << " => " << BasicString<C>(this -> value) << C(' ') << C(']');
	return str;
}

















template<typename I, typename T>
void Map<I, T>::clear() {
	_unload();
	Vector<MapObject<I, T> *>::clear();
}

template<typename I, typename T>
Map<I, T>::~Map( void ) {
	_unload();
}

template<typename I, typename T>
Map<I, T>::Map( void ) : Vector<MapObject<I, T> *>() {
}

template<typename I, typename T>
Map<I, T>::Map( ctor ) : Vector<MapObject<I, T> *>( ctor::null ) {

}



template<typename I, typename T>
Map<I, T>::Map( const Map<I, T> & map ) : Vector<MapObject<I, T> *>( map ) {

}


template<typename I, typename T>
template<typename I2, typename T2>
Map<I, T>::Map( const Map<I2, T2> & map ) : Vector<MapObject<I, T> *>( getSize(), getSize() ) {
	for ( Size i( 0 ); i < getSize(); i++ ) {
		this -> dataTable[i] = new MapObject<I, T>( map.dataTable[i] );
	}
}


template<typename I, typename T>
Map<I, T>::Map( Map && map ) : Vector<MapObject<I, T> *>( map ) {

}



template<typename I, typename T>
void Map<I, T>::_eraseit( typename Vector<T>::Iterator it ) {
	delete getValueIt( it );
	Vector<MapObject<I, T> *>::_eraseit( it );
}

template<typename I, typename T>
void Map<I, T>::_erasei( Size index ) {
	delete getValueI( index );
	Vector<MapObject<I, T> *>::_erasei( index );
}



template<typename I, typename T>
T * Map<I, T>::getValue( const I & index ) {
	for ( typename Map<I, T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] -> index == index ) {
			return &( this -> dataTable[i] -> value );
		}
	}
	return NULL;
}




template<typename I, typename T>
void Map<I, T>::set( typename Map<I, T>::Size i, const I & index, const T & data ) {
	setIndex( i, index );
	setValue( i, data );
}



template<typename I, typename T>
void Map<I, T>::setIndexi( typename Map<I, T>::Size i, const I & index ) {
	this -> dataTable[i] -> index = index;
}
template<typename I, typename T>
I & Map<I, T>::getIndexi( typename Map<I, T>::Size i ) {
	return this -> dataTable[i] -> index;
}
template<typename I, typename T>
const I & Map<I, T>::getIndexi( typename Map<I, T>::Size i ) const {
	return this -> dataTable[i] -> index;
}




template<typename I, typename T>
bool Map<I, T>::existsIndex( const I & index ) const {
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( getIndexit(it) == index )
			return true;
	}
	return false;
}


template<typename I, typename T>
void Map<I, T>::eraseValueAll( const T & data ) {
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( getValueIt( it ) == data )
			_eraseit( it );
	}
}

template<typename I, typename T>
void Map<I, T>::eraseValueFirst( const T & data ) {
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( getValueIt(it) == data ) {
			_eraseit( it );
			return;
		}
	}
}

template<typename I, typename T>
MapObject<I, T> & Map<I, T>::operator()( typename Map<I, T>::Size i ) {
	return *(this -> dataTable[i]);
}

template<typename I, typename T>
const MapObject<I, T> & Map<I, T>::operator()( typename Map<I, T>::Size i ) const {
	return *(this -> dataTable[i]);
}


template<typename I, typename T>
void Map<I, T>::eraseIndexAll( const I & index ) {
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( getIndexit(it) == index )
			_eraseit( it );
	}
}

template<typename I, typename T>
typename Map<I, T>::Size Map<I, T>::searchIndex( const I & index ) const {
	for ( typename Map<I, T>::Size i = 0; i < this -> size; i++ ) {
		if ( getIndexi( i ) == index ) {
			return i;
		}
	}
	return -1;
}

template<typename I, typename T>
void Map<I, T>::eraseIndexFirst( const I & index ) {
	_erasei( searchIndex( index ) );
}





template<typename I, typename T>
void Map<I, T>::insert( const I & index, const T & data ) {
	Vector<MapObject<I, T> *>::push( new MapObject<I, T>( index, data ) );
}


template<typename I, typename T>
template<typename I2, typename T2>
Map<I, T> & Map<I, T>::operator=( const Map<I2, T2> & map ) {
	_unload();
	_allocateNoNull(map.getSize());
	this -> size = map.size;
	for ( Size i( 0 ); i < getSize(); i++ ) {
		this -> dataTable[i] = new MapObject<I, T>( map.dataTable[i] );
	}
	return *this;
}


template<typename I, typename T>
Map<I, T> & Map<I, T>::operator=( Map<I, T> && map ) {
	Vector<MapObject<I, T> *>::operator=( map );
	return *this;
}




template<typename I, typename T>
void Map<I, T>::_unload() {
	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		delete ( *it );
	}
}



template<typename I, typename T>
T * Map<I, T>::operator[]( const I & index ) {
	return getValue( index );
}

template<typename I, typename T>
const T * Map<I, T>::operator[]( const I & index ) const {
	return getValue( index );
}

template<typename I, typename T>
void Map<I, T>::reset() {
	_unload();
	Vector<MapObject<I, T> *>::reset();
}





template<typename I, typename T>
void Map<I, T>::setIndexit( typename Map<I,T>::Iterator it, const T & index ) {
	(*it) -> index = index;
}

template<typename I, typename T>
const I & Map<I, T>::getIndexit( typename Map<I,T>::Iterator it ) const {
	return (*it) -> index;
}

template<typename I, typename T>
I & Map<I, T>::getIndexit( typename Map<I,T>::Iterator it ) {
	return (*it) -> index;
}






template<typename I, typename T>
std::ostream & operator<<( std::ostream & stream, const Map<I, T> & map ) {
	stream << "{ ";
	for ( Vector<T>::Size i = 0; i < map.getSize(); i++ ) {
		if ( i )
			stream << ",\n";
		stream << "[" << map.getIndexi( i ) << "] -> " << map.getValueI( i );
	}
	stream << " };";
	return stream;
}


template<typename I, typename T>
const T & Map<I, T>::getLastValue() const {
	return ( *( this -> iteratorEnd - 1 ) ) -> value;
}
template<typename I, typename T>
T & Map<I, T>::getLastValue() {
	return ( *( this -> iteratorEnd - 1 ) ) -> value;
}

template<typename I, typename T>
const T & Map<I, T>::getLastIndex() const {
	return ( *( this -> iteratorEnd - 1 ) ) -> index;
}
template<typename I, typename T>
T & Map<I, T>::getLastIndex() {
	return ( *( this -> iteratorEnd - 1 ) ) -> index;
}

template<typename I, typename T>
T & Map<I, T>::getValueI( Size i ) {
	return this -> dataTable[i] -> value;
}

template<typename I, typename T>
const T & Map<I, T>::getValueI( Size i ) const {
	return this -> dataTable[i] -> value;
}

template<typename I, typename T>
const T & Map<I, T>::getValueIt( typename Map<I,T>::Iterator it ) const {
	return (*it) -> value;
}

template<typename I, typename T>
T & Map<I, T>::getValueIt( typename Map<I,T>::Iterator it ) {
	return (*it) -> value;
}
template<typename I, typename T>
void Map<I, T>::setValueIt( typename Map<I,T>::Iterator it, const T & value ) {
	(*it) -> setValue( value );
}

template<typename I, typename T>
void Map<I, T>::setValueI( Size i, const T & value ) {
	this -> dataTable[i] -> setValue( value );
}


template<typename I, typename T>
void Map<I, T>::inserti( Size i, const I & index, const T & data ) {
	Vector<MapObject<I, T> *>::inserti( i, new MapObject<I, T>( index, data ) );
}


template<typename I, typename T>
template<typename Compare>
void Map<I, T>::sort( Compare & func ) {
	struct CompareFunc {
		CompareFunc( Compare & func ) : func( func ) {}
		bool operator()( MapObject<I, T> * const & o1, MapObject<I, T> * const & o2 ) {
			return this -> func( o1 -> getIndex(), o2 -> getIndex() );
		}
		Compare & func;
	};
	CompareFunc myNewFunctor( func );
	Vector<MapObject<I, T> *>::sort( myNewFunctor );
}






template<typename I, typename T>
void Map<I, T>::_clear() {
	_unload();
	Vector<MapObject<I, T> *>::_clear();
}



template<typename I, typename T>
bool Map<I, T>::read( std::fstream * fileStream ) {
	if ( !SimpleIO::read( fileStream, &this -> size ) ) {
		_clear();
		return false;
	}

	_unload();
	allocate( this -> maxSize );
	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		setValueIt( it, new MapObject<I, T>() );
	}
	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		if ( !IO::read( fileStream, getValueIt( it ) ) ) {
			_clear();
			return false;
		}
	}
	return true;
}

template<typename I, typename T>
bool Map<I, T>::write( std::fstream * fileStream ) const {
	if ( !SimpleIO::write( fileStream, &this -> size ) )
		return false;

	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		if ( !IO::write( fileStream, getValueIt( it ) ) )
			return false;
	}
	return true;
}


template<typename I, typename T>
template<typename C>
Map<I, T>::operator BasicString<C>() const {
	BasicString<C> str;
	str.reserve( 100 );
	str << "Map {\n";
	for ( auto it( getBegin() ); it != getEnd(); iterate( &it ) ) {
		str << C('\t') << String( *(Vector<MapObject<I, T> *>::getValueIt( it )) ) << C('\n');
	}
	str << "}";
	return str;
}
