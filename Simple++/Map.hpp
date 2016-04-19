

template<typename I, typename T>
MapObject<I, T>::~MapObject() {

}

template<typename I, typename T>
MapObject<I, T>::MapObject() {

}


template<typename I, typename T>
MapObject<I, T>::MapObject(const I & index, const T & value) :
	index(index),
	value(value) {

}


template<typename I, typename T>
void MapObject<I, T>::setValue(const T & value) {
	this -> value = value;
}

template<typename I, typename T>
const T & MapObject<I, T>::getValue() const {
	return this -> value;
}

template<typename I, typename T>
void MapObject<I, T>::setIndex(const I & index) {
	this -> index = index;
}

template<typename I, typename T>
const I & MapObject<I, T>::getIndex() const {
	return this -> index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator==(const MapObject & o) const {
	return this -> index == o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator>=(const MapObject & o) const {
	return this -> index >= o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator<=(const MapObject & o) const {
	return this -> index <= o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator>(const MapObject & o) const {
	return this -> index > o.index;
}

template<typename I, typename T>
bool MapObject<I, T>::operator<(const MapObject & o) const {
	return this -> index < o.index;
}




template<typename I, typename T>
bool MapObject<I, T>::write(std::fstream * fileStream) const {
	if ( !SimpleIO::write(fileStream, &this -> index) )
		return false;
	if ( !SimpleIO::write(fileStream, &this -> value) )
		return false;
	return true;
}

template<typename I, typename T>
bool MapObject<I, T>::read(std::fstream * fileStream) {
	if ( !SimpleIO::read(fileStream, &this -> index) )
		return false;
	if ( !SimpleIO::read(fileStream, &this -> value) )
		return false;
	return true;
}



























template<typename I, typename T>
T * Map<I, T>::getValue(const I & index){
	for (typename Map<I,T>::Size i = 0; i < this -> size; i++){
		if (this -> dataTable[i].index == index){
			return &( this -> dataTable[i].value );
		}
	}
	return NULL;
}




template<typename I, typename T>
void Map<I, T>::set(typename Map<I,T>::Size i, const I & index, const T & data){
	setIndex(i, index);
	setValue(i, data);
}



template<typename I, typename T>
void Map<I, T>::setIndexi(typename Map<I,T>::Size i, const I & index){
	this -> dataTable[i].index = index;
}
template<typename I, typename T>
I & Map<I, T>::getIndexi(typename Map<I,T>::Size i){
	return this -> dataTable[i].index;
}
template<typename I, typename T>
const I & Map<I, T>::getIndexi(typename Map<I,T>::Size i) const{
	return this -> dataTable[i].index;
}




template<typename I, typename T>
bool Map<I, T>::existsIndex(const I & index) const{
	for ( auto it = getBegin(); it != getEnd(); it++) {
		if (it -> index == index)
			return true;
	}
	return false;
}


template<typename I, typename T>
void Map<I, T>::eraseAll(const T & data){
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( it -> value == data )
			_eraseit(it);
	}
}

template<typename I, typename T>
void Map<I, T>::eraseFirst(const T & data){
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( it -> value == data ) {
			_eraseit(it);
			return;
		}

	}
}

template<typename I, typename T>
MapObject<I, T> & Map<I, T>::operator()(typename Map<I,T>::Size i){
	return this -> dataTable[i];
}

template<typename I, typename T>
const MapObject<I, T> & Map<I, T>::operator()(typename Map<I, T>::Size i) const {
	return this -> dataTable[i];
}


template<typename I, typename T>
void Map<I, T>::eraseIndexAll(const I & index){
	for ( auto it = getBegin(); it != getEnd(); it++ ) {
		if ( it -> index == index )
			_eraseit(it);
	}
}

template<typename I, typename T>
typename Map<I,T>::Size Map<I, T>::searchIndex(const I & index) const{
	for (typename Map<I,T>::Size i = 0; i < this -> size; i++){
		if (getIndexi(i) == index){
			return i;
		}
	}
	return -1;
}

template<typename I, typename T>
void Map<I, T>::eraseIndexFirst(const I & index){
	_erasei(searchIndex(index));
}





template<typename I, typename T>
void Map<I, T>::insert(const I & index, const T & data){
	Vector::push(MapObject<I, T>(index, data));
}

template<typename I, typename T>
Map<I, T> & Map<I, T>::operator=(const Map<I, T> & map){
	Vector::operator=( map );
	return *this;
}

template<typename I, typename T>
template<typename I2, typename T2>
Map<I, T> & Map<I, T>::operator=(const Map<I2, T2> & map) {
	Vector::operator=(map);
	return *this;
}


template<typename I, typename T>
Map<I, T> & Map<I, T>::operator=(Map<I, T> && map) {
	Vector::operator=(map);
	return *this;
}





template<typename I, typename T>
T * Map<I, T>::operator[](const I & index){
	return getValue(index);
}

template<typename I, typename T>
const T * Map<I, T>::operator[](const I & index) const {
	return getValue(index);
}



template<typename I, typename T>
Map<I, T>::~Map(void){

}

template<typename I, typename T>
Map<I, T>::Map(void) : 
	Vector<MapObject<I, T>>()
{
}

template<typename I, typename T>
Map<I, T>::Map(ctor) :
	Vector(null) {

}



template<typename I, typename T>
Map<I, T>::Map(const Map<I, T> & map) :
	Vector(map)
{
	
}


template<typename I, typename T>
template<typename I2, typename T2>
Map<I, T>::Map(const Map<I2, T2> & map) :
	Vector(map),
{
	
}


template<typename I, typename T>
Map<I, T>::Map(Map && map) :
	Vector(map)
{

}



template<typename I, typename T>
void Map<I, T>::setIndexit(RandomAccessIterator it, const T & index){
	it -> index = index;
}

template<typename I, typename T>
const I & Map<I, T>::getIndexit(RandomAccessIterator it) const{
	return it -> index;
}

template<typename I, typename T>
I & Map<I, T>::getIndexit(RandomAccessIterator it){
	return it -> index;
}






template<typename I, typename T>
std::ostream & operator<<(std::ostream & stream, const Map<I, T> & map){
	stream << "{ ";
	for (Vector<T>::Size i = 0; i < map.getSize(); i++){
		if (i)
			stream << ",\n";
		stream << "[" << map.getIndexi(i) << "] -> " << map.getValuei(i);
	}
	stream << " };";
	return stream;
}


template<typename I, typename T>
const T & Map<I, T>::getLastValue() const {
	return ( this -> iteratorEnd - 1 ) -> value;
}
template<typename I, typename T>
T & Map<I, T>::getLastValue() {
	return ( this -> iteratorEnd - 1 ) -> value;
}

template<typename I, typename T>
const T & Map<I, T>::getLastIndex() const {
	return ( this -> iteratorEnd - 1 ) -> index;
}
template<typename I, typename T>
T & Map<I, T>::getLastIndex() {
	return ( this -> iteratorEnd - 1 ) -> index;
}

template<typename I, typename T>
T & Map<I, T>::getValuei(Size i) {
	return this -> dataTable[i].value;
}

template<typename I, typename T>
const T & Map<I, T>::getValuei(Size i) const {
	return this -> dataTable[i].value;
}

template<typename I, typename T>
const T & Map<I, T>::getValueit(RandomAccessIterator i) const {
	return i -> value;
}

template<typename I, typename T>
T & Map<I, T>::getValueit(RandomAccessIterator i) {
	return i -> value;
}
template<typename I, typename T>
void Map<I, T>::setValueit(RandomAccessIterator it, const T & value) {
	it -> setValue(value);
}

template<typename I, typename T>
void Map<I, T>::setValuei(Size i, const T & value) {
	this -> dataTable[i].setValue(value);
}





template<typename I, typename T>
template<typename Compare>
void Map<I, T>::_sort(Compare func) {
	if ( getSize() )
		_quicksort(this -> dataTable, this -> iteratorEnd - 1, func);
}



template<typename I, typename T>
template<typename Compare>
void Map<I, T>::_quicksort(RandomAccessIterator start, RandomAccessIterator end, Compare func /*= Logical::less<I>*/) {
	// Create an auxiliary stack
	typedef struct {
		RandomAccessIterator start;
		RandomAccessIterator end;
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

		RandomAccessIterator storeIndex = start;

		for ( auto i = start; i < end; i++ ) {
			if ( func(i -> getIndex(), end -> getIndex()) ) {
				Vector::swap(i, storeIndex);
				storeIndex++;
			}
		}
		Vector::swap(end, storeIndex);

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
