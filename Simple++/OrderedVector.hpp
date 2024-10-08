template<typename T, typename Compare>
typename OrderedSize OrderedVector<T, Compare>::getNumEntries( const T & value ) {
	Size thisIndex = searchI( value );

	if ( thisIndex == -1 )
		return 0;
	else if ( this -> size == 1 )
		return 1;

	Size numEntries = 1;
	for ( Size i = thisIndex + 1; i < this -> size; i++ ) {
		if ( getValueI( i ) == value )
			numEntries++;
		else
			break;
	}
	if ( thisIndex > 0 ) {
		for ( Size i = thisIndex - 1; i >= 0; i-- ) {
			if ( getValueI( i ) == value )
				numEntries++;
			else
				break;
		}
	}

	return numEntries;
}

template<typename T, typename Compare>
bool OrderedVector<T, Compare>::exists( const T & data ) {
	if ( !this -> isOrdered )
		_sort();

	if ( this -> size == 0 )
		return false;
	else if ( this -> size == 1 )
		return ( getValueI( 0 ) == data );


	Size maxIndex = getSize() - 1;
	Size minIndex = 0;
	Size deltaIndex = maxIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getValueI( thisIndex ), data ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}


	if ( getValueI( minIndex ) == data || getValueI( maxIndex ) == data )
		return true;
	return false;
}

template<typename T, typename Compare>
void OrderedVector<T, Compare>::insertFast( const T & data ) {
	Vector::push( data );
	this -> isOrdered = false;
}

template<typename T, typename Compare>
void OrderedVector<T, Compare>::_sort() {
	Vector::sort( this -> sortFunction );
	this -> isOrdered = true;
}

template<typename T, typename Compare>
OrderedVector<T, Compare> & OrderedVector<T, Compare>::operator=( const OrderedVector<T, Compare> & vector ) {
	Vector::operator =( vector );
	this -> isOrdered = vector.isOrdered;
	this -> sortFunction = vector.sortFunction;
	return *this;
}

template<typename T, typename Compare /*= Math::Logical::less*/>
OrderedVector<T, Compare> & OrderedVector<T, Compare>::operator=( OrderedVector<T, Compare> && vector ) {
	Vector::operator=( Utility::toRValue( vector ) );
	this -> isOrdered = Utility::toRValue( vector.isOrdered );
	this -> sortFunction = Utility::toRValue( vector.sortFunction );
	return *this;
}

template<typename T, typename Compare /*= Math::Logical::less*/>
OrderedVector<T, Compare>::OrderedVector( const OrderedVector & vector ) :
	Vector( vector ),
	isOrdered( isOrdered ),
	sortFunction( vector.sortFunction ) {
}


template<typename T, typename Compare>
OrderedVector<T, Compare>::OrderedVector( const OrderedVector<T, Compare> & v ) :
	Vector( v ),
	isOrdered( v.isOrdered ),
	sortFunction( sortFunction ) {

}

template<typename T, typename Compare>
OrderedVector<T, Compare>::OrderedVector( OrderedVector<T, Compare> && v ) :
	Vector( Utility::toRValue( v ) ),
	isOrdered( Utility::toRValue( v.isOrdered ) ) {

}


template<typename T, typename Compare>
typename OrderedSize OrderedVector<T, Compare>::searchI( const T & data ) {
	if ( !this -> isOrdered )
		_sort();


	if ( this -> size == 0 )
		return Vector<T>::overflow;
	else if ( this -> size == 1 )
		return ( getValueI( 0 ) == data ) ? 0 : -1;



	Size maxIndex = getSize() - 1;
	Size minIndex = 0;
	Size deltaIndex = maxIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getValueI( thisIndex ), data ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}


	if ( getValueI( minIndex ) == data )
		return minIndex;
	else if ( getValueI( maxIndex ) == data )
		return maxIndex;
	else
		return Vector<T>::overflow;
}




template<typename T, typename Compare>
void OrderedVector<T, Compare>::insert( Size index, const T & data ) {
	if ( this -> maxSize == this -> size ) {
		if ( this -> maxSize < 100 )
			reserve( this -> maxSize + 1 );
		else
			reserve( this -> maxSize * 2 );
	}

	for ( Size i = getSize(), Size j = getSize() - 1; i > index; i--, j-- )
		setValueI( i, getValueI( j ) );

	this -> size++;
	setValueI( index, data );
}

template<typename T, typename Compare>
void OrderedVector<T, Compare>::insert( const T & data ) {
	if ( !this -> isOrdered )
		_sort();

	if ( this -> size == 0 ) {
		Vector::push( data );
		return;
	}

	Size maxIndex = this -> size;
	Size minIndex = 0;
	Size deltaIndex = maxIndex;


	while ( deltaIndex > 1 ) {
		Size thisIndex = minIndex + deltaIndex / 2;
		if ( this -> sortFunction( getValueI( thisIndex ), data ) )
			minIndex = thisIndex;
		else
			maxIndex = thisIndex;
		deltaIndex = maxIndex - minIndex;
	}

	if ( this -> sortFunction( getValueI( minIndex ), data ) )
		insert( maxIndex, data );
	else
		insert( minIndex, data );
}


template<typename T, typename Compare>
OrderedVector<T, Compare>::OrderedVector( const Compare & compareFunc ) : 
	isOrdered(true),
	sortFunction( compareFunc )
{

}

template<typename T, typename Compare>
OrderedVector<T, Compare>::~OrderedVector( void ) {

}

template<typename T, typename Compare>
template<typename Stream>
bool OrderedVector<T, Compare>::write(Stream* stream ) const {
	if ( !this -> isOrdered )
		_sort();
	if ( !Vector<T>::write( stream ) )
		return false;
	if ( !IO::write( stream, &this -> sortFunction ) )
		return false;
	return true;
}

template<typename T, typename Compare>
template<typename Stream>
bool OrderedVector<T, Compare>::read( Stream * stream, int verbose ) {
	this -> isOrdered = true;

	// In this case already clear
	if ( !Vector<T>::read( stream ) ) 
		return false;
	
	if ( !IO::read( stream, &this -> sortFunction , verbose - 1 ) ) {
		_clear();
		return false;
	}
	return true;
}
