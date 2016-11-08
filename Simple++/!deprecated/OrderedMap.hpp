template<typename I, typename T, typename Compare>
T * OrderedMap<I, T, Compare>::getValue( const I & index ) {
	if ( !this -> isOrdered )
		_sort();

	if ( this -> size <= 1 ) {
		if ( this -> size == 0 )
			return NULL;
		else {
			return &( getValueI( 0 ) );
		}
	}

	Size maxIndex = getSize() - 1;
	Size minIndex = 0;
	Size deltaIndex = maxIndex - minIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getIndexi( thisIndex ), index ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}


	if ( getIndexi( minIndex ) == index ) {
		return &( getValueI( minIndex ) );
	} else if ( getIndexi( maxIndex ) == index ) {
		return &( getValueI( maxIndex ) );
	}
	return NULL;
}



template<typename I, typename T, typename Compare>
const T * OrderedMap<I, T, Compare>::getValue( const I & index ) const {
	return const_cast< OrderedMap<I, T, Compare> * >( this ) -> getValue( index );
}




template<typename I, typename T, typename Compare>
typename OrderedMap<I, T, Compare>::Size OrderedMap<I, T, Compare>::getNumEntriesIndex( const I & index ) {
	Size thisIndex = searchIndex( index );

	if ( thisIndex == -1 )
		return 0;
	else if ( this -> size == 1 )
		return 1;

	Size numEntries = 1;
	for ( Size i = thisIndex + 1; i < this -> size; i++ ) {
		if ( getIndexi( i ) == index )
			numEntries++;
		else
			break;
	}
	if ( thisIndex > 0 ) {
		for ( Size i = thisIndex - 1; i >= 0; i-- ) {
			if ( getIndexi( i ) == index )
				numEntries++;
			else
				break;
		}
	}

	return numEntries;
}



template<typename I, typename T, typename Compare>
void OrderedMap<I, T, Compare>::_sort() {
	Map<I, T>::sort( this -> sortFunction );
	this -> isOrdered = true;
}

template<typename I, typename T, typename Compare>
void OrderedMap<I, T, Compare>::insertFast( const I & index, const T & data ) {
	Map<I, T>::insert( index, data );
	this -> isOrdered = false;
}



template<typename I, typename T, typename Compare>
void OrderedMap<I, T, Compare>::eraseIndex( const I & index ) {
	if ( !this -> isOrdered )
		_sort();



	if ( this -> size <= 1 ) {
		if ( this -> size == 0 )
			return;
		else
			return _erasei( 0 );
	}

	Size maxIndex = this -> size - 1;
	Size minIndex = 0;
	Size deltaIndex = maxIndex - minIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getIndexi( thisIndex ), index ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}


	if ( getIndexi( minIndex ) == index )
		_erasei( minIndex );
	else if ( getIndexi( maxIndex ) == index )
		_erasei( maxIndex );
}


template<typename I, typename T, typename Compare>
typename OrderedMap<I, T, Compare>::Size OrderedMap<I, T, Compare>::searchIndex( const I & index ) {
	if ( !this -> isOrdered )
		_sort();

	if ( this -> size <= 1 ) {
		if ( this -> size == 0 )
			return -1;
		else
			return ( getIndexi( 0 ) == index ) ? 0 : -1;
	}
	Size maxIndex = this -> size - 1;
	Size minIndex = 0;
	Size deltaIndex = maxIndex - minIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getIndexi( thisIndex ), index ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}


	if ( getIndexi( minIndex ) == index )
		return minIndex;
	else if ( getIndexi( maxIndex ) == index )
		return maxIndex;
	else
		return -1;
}

template<typename I, typename T, typename Compare>
bool OrderedMap<I, T, Compare>::existsIndex( const I & index ) {
	if ( !this -> isOrdered )
		_sort();


	if ( this -> size <= 1 ) {
		if ( this -> size == 0 )
			return false;
		else
			return ( getIndexi( 0 ) == index );
	}


	Size maxIndex = this -> size - 1;
	Size minIndex = 0;
	Size deltaIndex = maxIndex - minIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getIndexi( thisIndex ), index ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}


	if ( getIndexi( minIndex ) == index )
		return true;
	else if ( getIndexi( maxIndex ) == index )
		return true;
	else
		return false;
}


template<typename I, typename T, typename Compare>
T * OrderedMap<I, T, Compare>::operator[]( const I & index ) {
	return getValue( index );
}


template<typename I, typename T, typename Compare>
const T * OrderedMap<I, T, Compare>::operator[]( const I & index ) const {
	return getValue( index );
}


template<typename I, typename T, typename Compare>
void OrderedMap<I, T, Compare>::insert( const I & index, const T & data ) {
	if ( !this -> isOrdered )
		_sort();


	if ( this -> size == 0 ) {
		Map::insert( index, data );
		return;
	}

	Size maxIndex = this -> size;
	Size minIndex = 0;
	Size deltaIndex = maxIndex;

	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + ( deltaIndex >> 1 );

		if ( this -> sortFunction( getIndexi( thisIndex ), index ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;


		deltaIndex = maxIndex - minIndex;
	}


	if ( this -> sortFunction( getIndexi( minIndex ), index ) ) {
		inserti( maxIndex, index, data );
	} else {
		inserti( minIndex, index, data );
	}

}






template<typename I, typename T, typename Compare>
OrderedMap<I, T, Compare> & OrderedMap<I, T, Compare>::operator=( const OrderedMap<I, T, Compare> & map ) {
	Map<I, T>::operator =( map );
	this -> isOrdered = map.isOrdered;
	this -> sortFunction = map.sortFunction;
	return *this;
}

template<typename I, typename T, typename Compare>
OrderedMap<I, T, Compare> & OrderedMap<I, T, Compare>::operator=( OrderedMap<I, T, Compare> && map ) {
	Map<I, T>::operator =( Utility::toRValue(map) );
	this -> isOrdered = Utility::toRValue( map.isOrdered );
	this -> sortFunction = Utility::toRValue( map.sortFunction );
	return *this;
}


template<typename I, typename T, typename Compare>
OrderedMap<I, T, Compare>::~OrderedMap( void ) {

}

template<typename I, typename T, typename Compare>
OrderedMap<I, T, Compare>::OrderedMap( const Compare & compareFunc ) :
	isOrdered( true ),
	sortFunction( compareFunc ) {
}


template<typename I, typename T, typename Compare>
OrderedMap<I, T, Compare>::OrderedMap( const OrderedMap<I, T, Compare> & map ) : Map<I, T>( map ),
	isOrdered( map.isOrdered ),
	sortFunction( map.sortFunction ) {

}


template<typename I, typename T, typename Compare>
OrderedMap<I, T, Compare>::OrderedMap( OrderedMap<I, T, Compare> && map ) : Map<I, T>( Utility::toRValue( map ) ),
	isOrdered( Utility::toRValue( map.isOrdered ) ),
	sortFunction( Utility::toRValue( map.sortFunction ) ) {

}






template<typename I, typename T, typename Compare>
std::ostream & operator<<( std::ostream & stream, const OrderedMap<I, T, Compare> & map ) {
	stream << "{ ";
	for ( Vector<T>::Size i = 0; i < map.getSize(); i++ ) {
		if ( i )
			stream << ",\n";
		stream << "[" << map.getIndexi( i ) << "] -> " << map.getValueI( i );
	}
	stream << " };";
	return stream;
}



template<typename I, typename T, typename Compare>
bool OrderedMap<I, T, Compare>::write( std::fstream * fileStream ) const {
	if ( !this -> isOrdered )
		_sort();
	if ( !Map::write( fileStream ) )
		return false;
	if ( !IO::write( fileStream, &this -> sortFunction ) ) {
		_clear();
		return false;
	}
	return true;
}

template<typename I, typename T, typename Compare>
bool OrderedMap<I, T, Compare>::read( std::fstream * fileStream ) {
	this -> isOrdered = true;
	if ( !Map::read( fileStream ) )
		return false;
	if ( !IO::read( fileStream, &this -> sortFunction ) )
		return false;
	return true;
}

template<typename I, typename T, typename Compare>
template<typename C>
OrderedMap<I, T, Compare>::operator BasicString<C>() const {
	return static_cast<const Map<I, T> *>(this) -> operator BasicString<C>();
}
