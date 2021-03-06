
template<typename T>
typename Vector<T>::Size Vector<T>::overflow = typename Vector<T>::Size( -1 );



/************************************************************************/
/* CONSTRUCTORS                                                         */
/************************************************************************/

template<typename T>
Vector<T>::Vector( ctor ) {
}


template<typename T>
Vector<T>::Vector( void ) :
	maxSize( 0 ),
	size( 0 ),
	dataTable( NULL ),
	iteratorEnd( NULL ) {

}



template<typename T>
template<typename C>
Vector<T>::Vector( const Vector<C> & vector ) :
	size( vector.getSize() ),
	maxSize( vector.getMaxSize() ),
	dataTable( ( this -> maxSize ) ? new T[this -> maxSize] : NULL ) {
	copy( this -> dataTable, vector.getData(), this -> maxSize );
	_updateIterators();
}



template<typename T>
Vector<T>::Vector( const Vector<T> & vector ) :
	maxSize( vector.maxSize ),
	size( vector.size ),
	dataTable( ( maxSize ) ? new T[this -> maxSize] : NULL ) {
	copy( this -> dataTable, vector.getData(), this -> maxSize );

	_updateIterators();
}



template<typename T>
Vector<T>::Vector( Vector && v ) :
	dataTable( Utility::toRValue( v.dataTable ) ),
	size( Utility::toRValue( v.size ) ),
	maxSize( Utility::toRValue( v.maxSize ) ) {
	_updateIterators();
	v.dataTable = NULL;
}






template<typename T>
Vector<T>::Vector( typename Vector<T>::Size size, typename Vector<T>::Size maxSize ) :
	size( size ),
	maxSize( maxSize ),
	dataTable( new T[maxSize] ) {
	_assert( maxSize );
	_updateIterators();
}

template<typename T>
Vector<T>::Vector( typename Vector<T>::Size maxSize ) :
	maxSize( maxSize ),
	size( maxSize ),
	dataTable( new T[maxSize] ),
	iteratorEnd( dataTable + maxSize ) {
	_assert( maxSize );
}


template<typename T>
template<typename C, size_t N>
Vector<T>::Vector( const C( &data )[N] ) :
	size( N ),
	maxSize( N ),
	dataTable( new T[N] ) {
	copy( data, N );
	_updateIterators();
}

/*
template<typename T>
Vector<T>::Vector(const T * data, typename Vector<T>::Size maxSize) :
maxSize(maxSize),
size(maxSize),
dataTable(new T[size])
{
	copy(data, this -> size);
	_updateIterators();
}

template<typename T>
Vector<T>::Vector(const T * data, typename Vector<T>::Size size, typename Vector<T>::Size maxSize) :
	maxSize(maxSize),
	size(size),
	dataTable(new T[maxSize])
{
	copy(data, this -> size);
	_updateIterators();
}
*/


template<typename T>
template<typename C>
Vector<T>::Vector( const C * data, typename Vector<T>::Size size ) :
	maxSize( size ),
	size( size ),
	dataTable( new T[size] ) {
	copy( data, this -> size );
	_updateIterators();
}


template<typename T>
template<typename C>
Vector<T>::Vector( const C * data, typename Vector<T>::Size size, typename Vector<T>::Size maxSize ) :
	maxSize( maxSize ),
	size( size ),
	dataTable( new T[maxSize] ) {
	_assert( maxSize >= size );
	copy( data, this -> size );
	_updateIterators();
}

template<typename T>
template<typename C>
Vector<T>::Vector( RandomAccessIterator<C> beginIt, RandomAccessIterator<C> endIt ) :
	size( endIt - beginIt ),
	maxSize( this -> size ),
	dataTable( new T[maxSize] ) {
	copy( data, this -> size );
	_updateIterators();
}


template<typename T>
Vector<T>::~Vector( void ) {
	delete[] this -> dataTable;
}











template<typename T>
typename Vector<T>::Size Vector<T>::getSizeBytes() const {
	return this -> size * sizeof( T );
}



template<typename T>
template<typename C>
void Vector<T>::copy( Vector<C> vector, typename Vector<C>::Size indexSrc, typename Vector<T>::Size indexDst, typename Vector<C>::Size size ) {
	allocate( size + indexDst );
	copy( this -> dataTable + indexDst, vector.getData() + indexSrc, size );
}



template<typename T>
template<typename C>
void Vector<T>::copy( const C * datas, typename Vector<T>::Size index, typename Vector<T>::Size size ) {
	copy( this -> dataTable + index, datas, size );
}




template<typename T>
template<typename C>
void Vector<T>::copy( const C * datas, typename Vector<T>::Size size ) {
	copy( this -> dataTable, datas, size );
}

template<typename T>
void Vector<T>::assign( typename Vector<T>::Size index1, typename Vector<T>::Size index2 ) {
	this -> dataTable[index1] = this -> dataTable[index2];
}

template<typename T>
Vector<T> & Vector<T>::operator+=( const Vector<T> & vector ) {
	concat( vector );
	return *this;
}



template<typename T>
void Vector<T>::concat( const Vector<T> & vector ) {
	typename Vector<T>::Size oldNumValues( this -> size );
	this -> resize( this -> size + vector.size );
	copy( getData() + oldNumValues, vector.getData(), vector.getSize() );
}






template<typename T>
template<typename C>
void Vector<T>::createFromData( const C * dataTable, typename Vector<T>::Size size ) {
	delete[] this -> dataTable;
	this -> dataTable = new T[size];

	copy( this -> dataTable, dataTable, size );


	this -> size = size;
	this -> maxSize = size;
	_updateIterators();
}


template<typename T>
void Vector<T>::reset() {
	resize( 0 );
}


/************************************************************************/
/* LOGICAL                                                              */
/************************************************************************/
template<typename T>
bool Vector<T>::operator<( const Vector<T> & v ) const {
	if ( this -> size < v.size )
		return true;

	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] < v[i] )
			return true;
		else if ( this -> dataTable[i] > v[i] )
			return false;
	}

	return false;
}

template<typename T>
bool Vector<T>::operator>( const Vector<T> & v ) const {
	if ( this -> size > v.size )
		return true;

	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] > v[i] )
			return true;
		else if ( this -> dataTable[i] < v[i] )
			return false;
	}

	return false;
}

template<typename T>
bool Vector<T>::operator<=( const Vector<T> & v ) const {
	if ( this -> size < v.size )
		return true;

	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] < v[i] )
			return true;
		else if ( this -> dataTable[i] > v[i] )
			return false;
	}

	return true;
}

template<typename T>
bool Vector<T>::operator>=( const Vector<T> & v ) const {
	if ( this -> size > v.size )
		return true;

	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] > v[i] )
			return true;
		else if ( this -> dataTable[i] < v[i] )
			return false;
	}

	return true;
}

template<typename T>
bool Vector<T>::operator!=( const Vector<T> & v ) const {
	if ( this -> size != v.size )
		return true;

	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] != v.dataTable[i] )
			return true;
	}
	return false;
}

template<typename T>
bool Vector<T>::operator==( const Vector<T> & v ) const {
	if ( this -> size != v.size )
		return false;

	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] != v.dataTable[i] )
			return false;
	}
	return true;
}


template<typename T>
bool Vector<T>::operator==( const T & v ) const {
	if ( this -> size != 1 )
		return false;

	return this -> dataTable[0] == v;
}

template<typename T>
bool Vector<T>::operator!=( const T & v ) const {
	if ( this -> size != 1 )
		return true;
	return this -> dataTable[0] != v;
}
template<typename T>
bool Vector<T>::operator<( const T & v ) const {
	if ( this -> size < 1 )
		return true;
	return this -> dataTable[0] < v;
}
template<typename T>
bool Vector<T>::operator>( const T & v ) const {
	if ( this -> size < 1 )
		return false;
	return this -> dataTable[0] > v;
}
template<typename T>
bool Vector<T>::operator<=( const T & v ) const {
	if ( this -> size < 1 )
		return true;
	else if ( this -> size == 1 )
		return this -> dataTable[0] <= v;
	return false;
}
template<typename T>
bool Vector<T>::operator>=( const T & v ) const {
	if ( this -> size < 1 )
		return false;
	else if ( this -> size == 1 )
		return this -> dataTable[0] >= v;
	else
		return this -> dataTable[0] == v;
}




template<typename T>
template<typename Compare>
void Vector<T>::quicksort( typename Vector<T>::Iterator start, typename Vector<T>::Iterator end, Compare func ) {
	// Create an auxiliary stack
	typedef struct {
		typename Vector<T>::Iterator start;
		typename Vector<T>::Iterator end;
	} quicksortStackItem;

	quicksortStackItem * stack = new quicksortStackItem[( end - start ) / 2 + 1];


	// push initial values of l and h to stack
	stack[0].start = start;
	stack[0].end = end;

	//initialize stack iterator
	quicksortStackItem * top = &( stack[0] );

	// Keep popping from stack while is not empty
	while ( top >= stack ) {
		end = top -> end;
		start = top -> start;
		top--;

		typename Vector<T>::Iterator storeIndex = start;

		for ( auto i = start; i < end; i++ ) {
			if ( func( *i, *end ) ) {
				Vector::swap( i, storeIndex );
				storeIndex++;
			}
		}
		Vector::swap( end, storeIndex );

		// If there are elements on left side of pivot, then push 
		if ( storeIndex - 1 > start ) {
			top++;
			top -> start = start;
			top -> end = storeIndex - 1;
		}

		// If there are elements on right side of pivot, then push 
		if ( storeIndex + 1 < end ) {
			top++;
			top -> start = storeIndex + 1;
			top -> end = end;
		}
	}

	delete[] stack;
}




template<typename T>
void Vector<T>::swap( typename Vector<T>::Size index1, typename Vector<T>::Size index2 ) {
	Utility::swap<T>( this -> dataTable[index1], this -> dataTable[index2] );
}


template<typename T>
void Vector<T>::swap( typename Vector<T>::Iterator index1, typename Vector<T>::Iterator index2 ) {
	Utility::swap<T>( *index1, *index2 );
}


template<typename T>
bool Vector<T>::eraseAll( const T & value ) {
	bool r( false );
	for ( typename Vector<T>::Size i = 0; i < this -> maxSize; i++ ) {
		if ( value == this -> dataTable[i] ) {
			eraseIndex( i );
			r = true;
		}
	}
	return r;
}

template<typename T>
typename Vector<T>::Size Vector<T>::search( const T & data ) const {
	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] == data )
			return i;
	}
	return Vector<T>::overflow;
}


template<typename T>
const T & Vector<T>::getLast() const {
	return *( this -> iteratorEnd - 1 );
}


template<typename T>
T & Vector<T>::getLast() {
	return *( this -> iteratorEnd - 1 );
}


template<typename T>
const T & Vector<T>::getFirst() const {
	return *dataTable;
}


template<typename T>
T & Vector<T>::getFirst() {
	return *dataTable;
}


template<typename T>
void Vector<T>::sortAsc() {
	sort( Math::Logical::Less<T>() );
}

template<typename T>
void Vector<T>::sortDesc() {
	sort( Math::Logical::Greater<T>() );
}

template<typename T>
template<typename Func>
void Vector<T>::sort( Func & functor ) {
	if ( this -> size ) quicksort( this -> dataTable, this -> iteratorEnd - 1, functor );
}

template<typename T>
void Vector<T>::resize( typename Vector<T>::Size newSize ) {
	if ( newSize > this -> maxSize )
		reserve( newSize );

	this -> size = newSize;
	_updateIterators();
}



template<typename T>
bool Vector<T>::replaceAll( const T & search, const T & data ) {
	bool r( false );
	for ( typename Vector<T>::Size i = 0; i < this -> maxSize; i++ ) {
		if ( this -> dataTable[i] == search ) {
			this -> dataTable[i] = data;
			r = true;
		}
	}
	return r;
}

template<typename T>
bool Vector<T>::replaceFirst( const T & search, const T & data ) {
	for ( typename Vector<T>::Size i = 0; i < this -> maxSize; i++ ) {
		if ( this -> dataTable[i] == search ) {
			this -> dataTable[i] = data;
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::exists( const T & value ) const {
	for ( typename Vector<T>::Size i = 0; i < this -> size; i++ ) {
		if ( this -> dataTable[i] == value )
			return true;
	}
	return false;
}



template<typename T>
bool Vector<T>::eraseFirst( const T & v ) {
	for ( typename Vector<T>::Size i = 0; i < this -> maxSize; i++ ) {
		if ( v == this -> dataTable[i] ) {
			eraseIndex( i );
			return true;
		}
	}
	return false;
}

template<typename T>
void Vector<T>::eraseIndex( typename Vector<T>::Size index ) {
	for ( typename Vector<T>::Size i = index; i < this -> maxSize - 1; i++ ) {
		this -> dataTable[i] = this -> dataTable[i + 1];
	}
	this -> size--;
	_updateIterators();
}

template<typename T>
T & Vector<T>::pop() {
	this -> size--;
	_updateIterators();
	return *this -> iteratorEnd;
}

template<typename T>
T * Vector<T>::getData() {
	return this -> dataTable;
}

template<typename T>
T * Vector<T>::data() {
	return this -> dataTable;
}

template<typename T>
const T * Vector<T>::getData() const {
	return this -> dataTable;
}

template<typename T>
const T * Vector<T>::data() const {
	return this -> dataTable;
}









/************************************************************************/
/* ITERATIONS                                                           */
/************************************************************************/

template<typename T>
bool Vector<T>::iterate( typename Vector<T>::Iterator * it ) const {
	( *it )++;
	return !( *it == getEnd() );
}

template<typename T>
bool Vector<T>::iterate( typename Vector<T>::Iterator * it, ElemType ** e ) const {
	if ( *it == getEnd() )
		return false;
	*e = *it;
	( *it )++;
	return true;
}

template<typename T>
template<typename TestFunctor>
bool Vector<T>::iterate( typename Vector<T>::Iterator * it, ElemType ** e, TestFunctor & testFunctor ) const {
	if ( *it == getEnd() )
		return false;
	*e = *it;
	if ( testFunctor( *e ) ) {
		( *it )++;
		return true;
	}
	return false;
}



/************************************************************************/
/* OPERATOR =                                                           */
/************************************************************************/
template<typename T>
Vector<T> & Vector<T>::operator=( Vector && v ) {
	delete[] this -> dataTable;
	this -> dataTable = Utility::toRValue( v.dataTable );
	this -> size = Utility::toRValue( v.size );
	this -> maxSize = Utility::toRValue( v.maxSize );
	_updateIterators();

	v.dataTable = NULL;
	return *this;
}

template<typename T>
template<typename C>
Vector<T> & Vector<T>::operator=( const Vector<C> & vector ) {
	this -> maxSize = vector.getMaxSize();
	this -> size = vector.getSize();

	delete[] this -> dataTable;
	this -> dataTable = ( this -> maxSize ) ? new T[this -> maxSize] : NULL;
	copy( this -> dataTable, vector.dataTable, this -> size );
	_updateIterators();

	return *this;
}


template<typename T>
Vector<T> & Vector<T>::operator=( const Vector<T> & vector ) {
	return operator=<T>( vector );
}

template<typename T>
bool Vector<T>::isEmpty() const {
	return ( this -> size == 0 );
}

template<typename T>
void Vector<T>::clear() {
	this -> size = 0;
	_updateIterators();
}

template<typename T>
typename Vector<T>::Size Vector<T>::getMaxSize() const {
	return this -> maxSize;
}

template<typename T>
typename Vector<T>::Size Vector<T>::getSize() const {
	return this -> size;
}

template<typename T>
void Vector<T>::fill( const T & data ) {
	for ( typename Vector<T>::Size i = 0; i < this -> maxSize; i++ ) {
		this -> dataTable[i] = data;
	}
}


template<typename T>
void Vector<T>::reserve( typename Vector<T>::Size newMax ) {
	if ( this -> size > newMax )
		this -> size = newMax;

	if ( newMax == 0 ) {
		delete[] this -> dataTable;
		this -> dataTable = NULL;
	} else {
		T * newTable = new T[newMax];
		//copy old data

		copy( newTable, dataTable, this -> size );

		delete[] this -> dataTable;
		this -> dataTable = newTable;
	}
	this -> maxSize = newMax;
	_updateIterators();
}

template<typename T>
T * Vector<T>::push( const T & data ) {
	if ( this -> maxSize == this -> size ) {
		this -> size++;
		_extendBuffer( this -> size );
		T * valueP( this -> dataTable + ( this -> size - 1 ));
		( *valueP ) = data;
		return valueP;
	} else {
		T * valueP( this -> dataTable + ( this -> size ) );
		( *valueP ) = data;
		this -> size++;
		_updateIterators();
		return valueP;
	}
}

template<typename T>
void Vector<T>::inserti( typename Vector<T>::Size i, const T & v ) {
	if ( this -> maxSize == this -> size ) {
		this -> size++;
		_extendBuffer( this -> size );
	} else {
		this -> size++;
		_updateIterators();
	}
	for ( typename Vector<T>::Size k = this -> size - 1, j = this -> size - 2; k > i; k--, j-- ) 
		setValueI( k, getValueI( j ) );
	this -> dataTable[i] = v;
}


template<typename T>
void Vector<T>::_extendBuffer( typename Vector<T>::Size newSizeNeeded ) {
	this -> maxSize = newSizeNeeded * 2;
	T * newBuffer = new T[this -> maxSize];
	if ( this -> dataTable != NULL ) {
		copy( newBuffer, this -> dataTable, getSize() );
		delete[] this -> dataTable;
	}
	this -> dataTable = newBuffer;
	_updateIterators();
}


template<typename T>
void Vector<T>::allocate( typename Vector<T>::Size newMax ) {
	delete[] this -> dataTable;
	if ( newMax )
		this -> dataTable = new T[newMax];
	else
		this -> dataTable = NULL;

	this -> maxSize = newMax;
	_updateIterators();
}


template<typename T>
void Vector<T>::_allocateNoNullDelete( typename Vector<T>::Size newMax ) {
	this -> dataTable = new T[newMax];
	this -> maxSize = newMax;
}


template<typename T>
void Vector<T>::_allocateNoNull( typename Vector<T>::Size newMax ) {
	delete[] this -> dataTable;
	this -> dataTable = new T[newMax];
	this -> maxSize = newMax;
}


template<typename T>
T & Vector<T>::operator[]( const typename Vector<T>::Size index ) {
	return *( this -> dataTable + index );
}

template<typename T>
const T & Vector<T>::operator[]( const typename Vector<T>::Size index ) const {
	return *( this -> dataTable + index );
}





template<typename T>
std::ostream & operator<<( std::ostream & stream, const Vector<T> & vector ) {
	stream << "[ ";
	for ( typename Vector<T>::Size i = 0; i < vector.getSize(); i++ ) {
		if ( i ) stream << " | ";
		stream << vector[i];
	}
	stream << " ];";
	return stream;
}





template<typename T>
typename Vector<T>::Iterator Vector<T>::end() const {
	return getEnd();
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::begin() const {
	return getBegin();
}

template<typename T>
void Vector<T>::_updateIterators() {
	this -> iteratorEnd = this -> dataTable + this -> size;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::getBegin() const {
	return this -> dataTable;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::getEnd() const {
	return this -> iteratorEnd;
}

/*
template<typename T>
T & Vector<T>::operator[]( typename Vector<T>::RandomAccessIterator i ){
	return *i;
}

template<typename T>
const T & Vector<T>::operator[]( typename Vector<T>::RandomAccessIterator i ) const{
	return *i;
}
*/

template<typename T>
void Vector<T>::setValueI( typename Vector<T>::Size i, const T & data ) {
	this -> dataTable[i] = data;
}


template<typename T>
void Vector<T>::setValueIt( typename Vector<T>::Iterator i, const T & data ) {
	*i = data;
}



template<typename T>
const T & Vector<T>::getValueI( typename Vector<T>::Size i ) const {
	return this -> dataTable[i];
}


template<typename T>
T & Vector<T>::getValueI( typename Vector<T>::Size i ) {
	return this -> dataTable[i];
}


template<typename T>
const T & Vector<T>::getValueIt( typename Vector<T>::Iterator i ) const {
	return *i;
}

template<typename T>
T & Vector<T>::getValueIt( typename Vector<T>::Iterator i ) {
	return *i;
}


template<typename T>
void Vector<T>::_erasei( typename Vector<T>::Size index ) {
	_eraseit(getData() + index);
}


template<typename T>
void Vector<T>::_eraseit( typename Vector<T>::Iterator index ) {
	this -> size--;
	_updateIterators();
	for ( auto it( index ), it != getEnd(); iterate(&it) ) {
		*it = *( it + 1 );
	}
}



//Default implementation with a one per one copy.
template<typename T>
template<typename C, typename D>
void Vector<T>::copy( C * destinationBuffer, const D * sourceBuffer, typename Vector<T>::Size size ) {
	if ( Utility::isSame<C, D>::value ) {
		for ( typename Vector<T>::Size i = 0; i < size; i++ ) {
			destinationBuffer[i] = static_cast<C>( sourceBuffer[i] );
		}
	} else {
		for ( typename Vector<T>::Size i = 0; i < size; i++ ) {
			destinationBuffer[i] = static_cast<C>( sourceBuffer[i] );
		}
	}
}


template<typename T>
template<typename C, typename D>
void Vector<T>::copy( C ** destinationBuffer, D * const * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( C* ) );
}
template<typename T>
void Vector<T>::copy( char * destinationBuffer, const char * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size );
}
template<typename T>
void Vector<T>::copy( unsigned char * destinationBuffer, const unsigned char * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size );
}
template<typename T>
void Vector<T>::copy( short * destinationBuffer, const short * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( short ) );
}
template<typename T>
void Vector<T>::copy( unsigned short * destinationBuffer, const unsigned short * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( short ) );
}
template<typename T>
void Vector<T>::copy( int * destinationBuffer, const int * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( int ) );
}
template<typename T>
void Vector<T>::copy( unsigned int * destinationBuffer, const unsigned int * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( int ) );
}
template<typename T>
void Vector<T>::copy( long * destinationBuffer, const long * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( long ) );
}
template<typename T>
void Vector<T>::copy( unsigned long * destinationBuffer, const unsigned long * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( long ) );
}
template<typename T>
void Vector<T>::copy( long long * destinationBuffer, const long long * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( long long ) );
}
template<typename T>
void Vector<T>::copy( unsigned long long * destinationBuffer, const unsigned long long * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( long long ) );
}
template<typename T>
void Vector<T>::copy( float * destinationBuffer, const float * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( float ) );
}
template<typename T>
void Vector<T>::copy( double * destinationBuffer, const double * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( double ) );
}
template<typename T>
void Vector<T>::copy( wchar_t * destinationBuffer, const wchar_t * sourceBuffer, typename Vector<T>::Size size ) {
	memcpy( destinationBuffer, sourceBuffer, size * sizeof( wchar_t ) );
}
















template<typename T>
bool Vector<T>::write( std::fstream * fileStream ) const {
	if ( !SimpleIO::write( fileStream, &this -> size ) )
		return false;

	for ( typename Vector<T>::Size i( 0 ); i < this -> size; i++ ) {
		if ( !SimpleIO::write( fileStream, &( this -> dataTable[i] ) ) )
			 return false;
	}

	return true;
}

template<typename T>
bool Vector<T>::read( std::fstream * fileStream ) {

	if ( !SimpleIO::read( fileStream, &this -> size ) ) {
		_clear();
		return false;
	}
	allocate( this -> maxSize );

	for ( typename Vector<T>::Size i( 0 ); i < this -> size; i++ ) {
		if ( !SimpleIO::read( fileStream, &( this -> dataTable[i] ) ) ) {
			_clear();
			return false;
		}
	}

	return true;
}

template<typename T>
void Vector<T>::_clear() {
	this -> size = 0;
	this -> maxSize = 0;
	delete[] this -> dataTable;
	this -> dataTable = NULL;
	_updateIterators();
}
