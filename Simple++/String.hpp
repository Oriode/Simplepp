













template<typename T>
const T BasicString<T>::numbers[16] = { T('0'), T('1'), T('2'), T('3'), T('4'), T('5'), T('6'), T('7'), T('8'), T('9'), T('A'), T('B'), T('C'), T('D'), T('E'), T('F') };














/************************************************************************/
/* Constructors                                                         */
/************************************************************************/





template<typename T>
template<typename C>
BasicString<T>::BasicString(const C * str) :
Vector(null)
{
	this->size = BasicString<C>::getSize(str);
	this->maxSize = this->size + 1;
	this->dataTable = new T[this->maxSize];
	_updateIterators();
	copy(str, getMaxSize());
}


/*
template<typename T>
template<typename C, size_t N>
BasicString<T>::BasicString(const C(&s)[N]) :
Vector(null)
{	
	this -> size = N - 1;
	this -> maxSize = N;
	this -> dataTable = new T[N];
	Vector::copy(this -> dataTable, s, N);
	_updateIterators();
}*/


template<typename T>
template<typename C>
BasicString<T>::BasicString(const C * str, Size size) :
Vector(str, size, size + 1)
{	
	this -> dataTable[size] = T('\0');
}

template<typename T>
BasicString<T>::BasicString() : 
Vector(Size(0), Size(1))
{
	this -> dataTable[0] = T('\0');
}


template<typename T>
BasicString<T>::BasicString(const unsigned char & ui) :
Vector(Vector::null)
{
	this->maxSize = 5;
	this->dataTable = new T[5];
	this->size = toCString(ui, this->dataTable);
	_updateIterators();
}


template<typename T>
BasicString<T>::BasicString(const unsigned short & ui) :
Vector(Vector::null)
{
	this->maxSize = 7;
	this->dataTable = new T[7];
	this->size = toCString(ui, this->dataTable);
	_updateIterators();
}


template<typename T>
BasicString<T>::BasicString(const int & i) :
Vector(Vector::null)
{
	this->maxSize = 12;
	this->dataTable = new T[12];
	this->size = toCString(i, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const unsigned int & ui) : 
Vector(Vector::null)
{
	this->maxSize = 11;
	this->dataTable = new T[11];
	this->size = toCString(ui, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const long & l) : 
Vector(Vector::null)
{
	this->maxSize = 21;
	this->dataTable = new T[21];
	this->size = toCString(l, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const unsigned long & ul) :
Vector(Vector::null)
{
	this->maxSize = 21;
	this->dataTable = new T[21];
	this->size = toCString(ul, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const long long & ll) :
Vector(Vector::null)
{
	this->maxSize = 21;
	this->dataTable = new T[21];
	this->size = toCString(ll, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const unsigned long long & ull) :
Vector(Vector::null)
{
	this->maxSize = 21;
	this->dataTable = new T[21];
	this->size = toCString(ull, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const double & d) : 
Vector(Vector::null)
{
	this->maxSize = 50;
	this->dataTable = new T[50];
	this->size = toCString(d, this->dataTable);
	_updateIterators();
}

template<typename T>
BasicString<T>::BasicString(const float & f) : 
Vector(Vector::null)
{
	this->maxSize = 30;
	this->dataTable = new T[30];
	this->size = toCString(f, this->dataTable);
	_updateIterators();
}



template<typename T>
BasicString<T>::BasicString(const bool & b) :
Vector(Vector::null) 
{
	this->maxSize = 6;
	this->dataTable = new T[6];
	this->size = toCString(b, this->dataTable);
	_updateIterators();
}


template<typename T>
BasicString<T>::BasicString(const T & c) :
Vector(1,2)
{
	this->dataTable[0] = T(c);
	this->dataTable[1] = T('\0');
}



template<typename T>
template<typename C>
BasicString<T>::BasicString(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str) :
	Vector(str.data(), str.size(), str.size() + 1) {
	this -> dataTable[size] = T('\0');
}

template<typename T>
template<typename C>
BasicString<T>::BasicString(const BasicString<C> & str) : 
	Vector(str)
{

}

template<typename T>
BasicString<T>::BasicString(const BasicString & str) :
	Vector(str) 
{

}

template<typename T>
BasicString<T>::BasicString(BasicString<T> && str) :
Vector(Utility::toRValue(str))
{

}


template<typename T>
BasicString<T>::BasicString(ctor) : Vector(null){

}

template<typename T>
BasicString<T>::~BasicString(){
}








/************************************************************************/
/* OPERATOR +                                                           */
/************************************************************************/

template<typename T>
BasicString<T> operator+(const BasicString<T> & str1, const BasicString<T> & str2){
	BasicString<T> newStr(str1);
	newStr += str2;
	return newStr;
}


template<typename T, typename C>
BasicString<T> operator+(const BasicString<T> & str1, const BasicString<C> & str2){
	BasicString<T> newStr(str1);
	newStr += str2;
	return newStr;
}



template<typename T, typename C>
BasicString<T> operator+(const BasicString<T> & str1, const C * str2){
	BasicString<T> newStr(str1);
	newStr += str2;
	return newStr;
}

template<typename T, typename C>
BasicString<T> operator+(const C * str1, const BasicString<T> & str2){
	BasicString<T> newStr(str1);
	newStr += str2;
	return newStr;
}


template<typename T>
BasicString<T> operator+(const BasicString<T> & str1, const int & i){
	BasicString<T> newStr(str1);
	newStr += i;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const int & i, const BasicString<T> & str){
	BasicString<T> newStr(i);
	newStr += str;
	return newStr;
}


template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const unsigned char & ui){
	BasicString<T> newStr(str);
	newStr += ui;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const unsigned char & ui, const BasicString<T> & str){
	BasicString<T> newStr(ui);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const unsigned short & ui){
	BasicString<T> newStr(str);
	newStr += ui;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const unsigned short & ui, const BasicString<T> & str){
	BasicString<T> newStr(ui);
	newStr += str;
	return newStr;
}


template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const unsigned int & ui){
	BasicString<T> newStr(str);
	newStr += ui;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const unsigned int & ui, const BasicString<T> & str){
	BasicString<T> newStr(ui);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const long & l){
	BasicString<T> newStr(str);
	newStr += l;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const long & l, const BasicString<T> & str){
	BasicString<T> newStr(l);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const unsigned long & ul){
	BasicString<T> newStr(str);
	newStr += ul;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const unsigned long & ul, const BasicString<T> & str){
	BasicString<T> newStr(ul);
	newStr += str;
	return newStr;
}


template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const long long & ll){
	BasicString<T> newStr(str);
	newStr += ll;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const long long & ll, const BasicString<T> & str){
	BasicString<T> newStr(ll);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const unsigned long long & ull){
	BasicString<T> newStr(str);
	newStr += ull;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const unsigned long long & ull, const BasicString<T> & str){
	BasicString<T> newStr(ull);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const float & f){
	BasicString<T> newStr(str);
	newStr += f;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const float & f, const BasicString<T> & str){
	BasicString<T> newStr(f);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const bool & b) {
	BasicString<T> newStr(str);
	newStr += b;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const bool & b, const BasicString<T> & str) {
	BasicString<T> newStr(b);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const double & d){
	BasicString<T> newStr(str);
	newStr += d;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const double & d, const BasicString<T> & str){
	BasicString<T> newStr(d);
	newStr += str;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const BasicString<T> & str, const T & c){
	BasicString<T> newStr(str);
	newStr += c;
	return newStr;
}

template<typename T>
BasicString<T> operator+(const T & c, const BasicString<T> & str){
	BasicString<T> newStr(c);
	newStr += str;
	return newStr;
}

template<typename T, typename C>
BasicString<T> operator+(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str1, const BasicString<T> & str2){
	BasicString<T> newStr(str1);
	newStr += str2;
	return newStr;
}


template<typename T, typename C>
BasicString<T> operator+(const BasicString<T> & str1, const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str2){
	BasicString<T> newStr(str1);
	newStr += str2;
	return newStr;
}







/************************************************************************/
/* Operator +=                                                          */
/************************************************************************/


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str) {
	this -> concat(str.data(), str.size());
	return *this;
}



template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat(const C * str) {
	for ( ; *str != C('\0'); str++ ) {
		this -> size++;
		if ( this -> size >= this -> maxSize ) {
			_extendBuffer(this -> size);
			this -> iteratorEnd--;
		}
		*this -> iteratorEnd = T(*str);
		this -> iteratorEnd++;
	}
	*this -> iteratorEnd = T('\0');
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::concat(const bool & b) {
	auto newMaxSize = this -> size + 6;
	if ( newMaxSize > this -> maxSize )
		_extendBuffer(newMaxSize);

	this -> size += toCString(b, this -> iteratorEnd);
	_updateIterators();
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::concat(const char & c) {
	this -> size++;
	if ( this -> size >= this -> maxSize ) {
		_extendBuffer(this -> size);
		this -> iteratorEnd--;
	}

	toCString(c, this -> iteratorEnd);
	_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::concat(const wchar_t & c) {
	this -> size++;
	if ( this -> size >= this -> maxSize ) {
		_extendBuffer(this -> size);
		this -> iteratorEnd--;
	}

	toCString(c, this -> iteratorEnd);
	_updateIterators();
	return *this;
}




template<typename T>
template<typename Type, unsigned int Base>
BasicString<T> & BasicString<T>::_concatInteger(const Type & i) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCString<Base>(i, this -> iteratorEnd);
	_updateIterators();
	return *this;
}

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatInteger(const Type & i, unsigned int base) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCString(i, this -> iteratorEnd, base);
	_updateIterators();
	return *this;
}


template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatFloat(const Type & f) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCString<Precision, Base>(f, this -> iteratorEnd);
	_updateIterators();
	return *this;
}

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatFloat(const Type & f, unsigned int precision, unsigned int base) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCString(f, this -> iteratorEnd, precision, base);
	_updateIterators();
	return *this;
}


template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const unsigned char & uc) {
	return _concatInteger<unsigned char, Base>(uc);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const unsigned short & us) {
	return _concatInteger<unsigned short, Base>(us);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const int & i) {
	return _concatInteger<int, Base>(i);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const unsigned int & ui) {
	return _concatInteger<unsigned int, Base>(ui);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const long & l) {
	return _concatInteger<long, Base>(l);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const unsigned long & ul) {
	return _concatInteger<unsigned long, Base>(ul);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const long long & ll) {
	return _concatInteger<long long, Base>(l);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::concat(const unsigned long long & ull) {
	return _concatInteger<unsigned long long, Base>(ull);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::concat(const double & d) {
	return _concatFloat<double, Precision, Base>(d);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::concat(const float & f) {
	return _concatFloat<float, Precision, Base>(f);
}

template<typename T>
BasicString<T> & BasicString<T>::concat(const unsigned char & uc, unsigned int base) {
	return _concatInteger<unsigned char>(uc, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const unsigned short & us, unsigned int base) {
	return _concatInteger<unsigned short>(us, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const int & i, unsigned int base) {
	return _concatInteger<int>(i, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const unsigned int & ui, unsigned int base) {
	return _concatInteger<unsigned int>(ui, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const long & l, unsigned int base) {
	return _concatInteger<long>(l, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const unsigned long & ul, unsigned int base) {
	return _concatInteger<unsigned long>(ul, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const long long & ll, unsigned int base) {
	return _concatInteger<long long>(ll, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const unsigned long long & ull, unsigned int base) {
	return _concatInteger<unsigned long long>(ull, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const double & d, unsigned int precision, unsigned int base) {
	return _concatFloat<double>(d, precision, base);
}
template<typename T>
BasicString<T> & BasicString<T>::concat(const float & f, unsigned int precision, unsigned int base) {
	return _concatFloat<float>(f, precision, base);
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat(const BasicString<C> & str) {
	return concat(str.getData(), str.getSize());
}

template<typename T>
BasicString<T> & BasicString<T>::concat(const BasicString<T> & str) {
	return concat(str.getData(), str.getSize());
}




template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::concat(const C * buffer, typename const BasicString<C>::Size & bufferSize) {
	typename BasicString<T>::Size newSize = getSize() + bufferSize;

	if ( newSize >= this -> maxSize )
		_extendBuffer(newSize);

	copy(this -> iteratorEnd, buffer, bufferSize);
	this -> dataTable[newSize] = T('\0');
	this -> size = newSize;
	_updateIterators();
	return *this;
}



/************************************************************************/
/* concat() without adding sentinnel                                    */
/************************************************************************/
template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str) {
	this -> concat(str.data(), str.size());
	return *this;
}



template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS(const C * str) {
	for ( ; *str != C('\0'); str++ ) {
		this -> size++;
		if ( this -> size >= this -> maxSize ) {
			_extendBuffer(this -> size);
			this -> iteratorEnd--;
		}
		*this -> iteratorEnd = T(*str);
		this -> iteratorEnd++;
	}
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const bool & b) {
	auto newMaxSize = this -> size + 6;
	if ( newMaxSize > this -> maxSize )
		_extendBuffer(newMaxSize);

	this -> size += toCString(b, this -> iteratorEnd);
	_updateIterators();
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const char & c) {
	this -> size++;
	if ( this -> size >= this -> maxSize ) {
		_extendBuffer(this -> size);
		this -> iteratorEnd--;
	}

	toCStringWOS(c, this -> iteratorEnd);
	_updateIterators();
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const wchar_t & c) {
	this -> size++;
	if ( this -> size >= this -> maxSize ) {
		_extendBuffer(this -> size);
		this -> iteratorEnd--;
	}

	toCStringWOS(c, this -> iteratorEnd);
	_updateIterators();
	return *this;
}




template<typename T>
template<typename Type, unsigned int Base>
BasicString<T> & BasicString<T>::_concatIntegerWOS(const Type & i) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCStringWOS<Base>(i, this -> iteratorEnd);
	_updateIterators();
	return *this;
}

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatIntegerWOS(const Type & i, unsigned int base) {
	auto newSize = this -> size + 21;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCStringWOS(i, this -> iteratorEnd, base);
	_updateIterators();
	return *this;
}


template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatFloatWOS(const Type & f) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCStringWOS<Precision, Base>(f, this -> iteratorEnd);
	_updateIterators();
	return *this;
}

template<typename T>
template<typename Type>
BasicString<T> & BasicString<T>::_concatFloatWOS(const Type & f, unsigned int precision, unsigned int base) {
	auto newSize = this -> size + 50;
	if ( newSize > this -> maxSize )
		_extendBuffer(newSize);

	this -> size += toCStringWOS(f, this -> iteratorEnd, precision, base);
	_updateIterators();
	return *this;
}


template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned char & uc) {
	return _concatIntegerWOS<unsigned char, Base>(uc);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned short & us) {
	return _concatIntegerWOS<unsigned short, Base>(us);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const int & i) {
	return _concatIntegerWOS<int, Base>(i);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned int & ui) {
	return _concatIntegerWOS<unsigned int, Base>(ui);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const long & l) {
	return _concatIntegerWOS<long, Base>(l);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned long & ul) {
	return _concatIntegerWOS<unsigned long, Base>(ul);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const long long & ll) {
	return _concatIntegerWOS<long long, Base>(l);
}

template<typename T>
template<unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned long long & ull) {
	return _concatIntegerWOS<unsigned long long, Base>(ull);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const double & d) {
	return _concatFloatWOS<double, Precision, Base>(d);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> & BasicString<T>::_concatWOS(const float & f) {
	return _concatFloatWOS<float, Precision, Base>(f);
}

template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned char & uc, unsigned int base) {
	return _concatIntegerWOS<unsigned char>(uc, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned short & us, unsigned int base) {
	return _concatIntegerWOS<unsigned short>(us, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const int & i, unsigned int base) {
	return _concatIntegerWOS<int>(i, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned int & ui, unsigned int base) {
	return _concatIntegerWOS<unsigned int>(ui, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const long & l, unsigned int base) {
	return _concatIntegerWOS<long>(l, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned long & ul, unsigned int base) {
	return _concatIntegerWOS<unsigned long>(ul, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const long long & ll, unsigned int base) {
	return _concatIntegerWOS<long long>(ll, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const unsigned long long & ull, unsigned int base) {
	return _concatIntegerWOS<unsigned long long>(ull, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const double & d, unsigned int precision, unsigned int base) {
	return _concatFloatWOS<double>(d, precision, base);
}
template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const float & f, unsigned int precision, unsigned int base) {
	return _concatFloatWOS<float>(f, precision, base);
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS(const BasicString<C> & str) {
	return _concatWOS(str.getData(), str.getSize());
}

template<typename T>
BasicString<T> & BasicString<T>::_concatWOS(const BasicString<T> & str) {
	return _concatWOS(str.getData(), str.getSize());
}




template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::_concatWOS(const C * buffer, typename const BasicString<C>::Size & bufferSize) {
	typename BasicString<T>::Size newSize = getSize() + bufferSize;

	if ( newSize >= this -> maxSize )
		_extendBuffer(newSize);

	copy(this -> iteratorEnd, buffer, bufferSize);
	this -> size = newSize;
	_updateIterators();
	return *this;
}




/************************************************************************/
/* CONVERSIONS                                                          */
/************************************************************************/
template<typename T>
template<typename Type, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::_convertUI2StringWOS(Type number, T * buffer){
	_assert(Base <= 16 && Base > 0);
	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	auto tmpP = tmpBuffer;
	while (true){
		*tmpP = number % Type(Base);
		if (number < Type(Base)) break;
		number /= Type(Base);
		tmpP++;
	}

	for (; tmpP >= tmpBuffer; tmpP--, bufferTmp++){
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	return (typename BasicString<T>::Size)(bufferTmp - buffer);
}

template<typename T>
template<typename Type>
typename BasicString<T>::Size BasicString<T>::_convertUI2StringWOS(Type number, T * buffer, unsigned int base){
	_assert(base <= 16 && base > 0);
	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	auto tmpP = tmpBuffer;
	while (true){
		*tmpP = number % Type(base);
		if (number < Type(base)) break;
		number /= Type(base);
		tmpP++;
	}

	for (; tmpP >= tmpBuffer; tmpP--, bufferTmp++){
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	return (typename BasicString<T>::Size)(bufferTmp - buffer);
}


template<typename T>
template<typename Type, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::_convertI2StringWOS(Type number, T * buffer){
	_assert(Base <= 16 && Base > 0);

	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	if (number < Type(0)){
		(*bufferTmp) = T('-');
		bufferTmp++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while (true){
		*tmpP = number % Type(Base);
		if (number < Type(Base)) break;
		number /= Type(Base);
		tmpP++;
	}

	for (; tmpP >= tmpBuffer; tmpP--, bufferTmp++){
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	return (typename BasicString<T>::Size)(bufferTmp - buffer);
}

template<typename T>
template<typename Type>
typename BasicString<T>::Size BasicString<T>::_convertI2StringWOS(Type number, T * buffer, unsigned int base){
	_assert(base <= 16 && base > 0);

	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	if (number < Type(0)){
		(*bufferTmp) = T('-');
		bufferTmp++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while (true){
		*tmpP = number % Type(base);
		if (number < Type(base)) break;
		number /= Type(base);
		tmpP++;
	}

	for (; tmpP >= tmpBuffer; tmpP--, bufferTmp++){
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	return (typename BasicString<T>::Size)(bufferTmp - buffer);
}


template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::_convertFloat2StringWOS(Type number, T * buffer){
	_assert(Base <= 16 && Precision < 50);

	if ( number == INFINITY ) {
		buffer[0] = T('I');
		buffer[1] = T('N');
		buffer[2] = T('F');
		return Size(3);
	}


	auto bufferTmp = buffer;

	if (number == Type(0)){
		(*bufferTmp) = T('0');
		bufferTmp++;
		(*bufferTmp) = T('\0');
		return 1;
	}

	if (number < 0){
		(*bufferTmp) = T('-');
		bufferTmp++;
		number = -number;
	}

	int comma = 1;
	while (number > Type(Base)){
		number /= Type(Base);
		comma++;
	}
	while (number < Type(1)){
		number *= Type(Base);
		comma--;
	}
	int i;
	for (i = 0; i < comma; i++, bufferTmp++){
		unsigned long long castedNumber = (unsigned long long)number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % Base];
		number *= Type(Base);
	}

	*bufferTmp = T('.');
	bufferTmp++;

	for (i = comma; i < (int)Precision; i++, bufferTmp++){
		unsigned long long castedNumber = (unsigned long long)number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % Base];
		number *= Type(Base);
	}
	return (typename BasicString<T>::Size)(bufferTmp - buffer);
}

template<typename T>
template<typename Type>
typename BasicString<T>::Size BasicString<T>::_convertFloat2StringWOS(Type number, T * buffer, unsigned int precision, unsigned int base){
	_assert(base <= 16 && base > 0);

	auto bufferTmp = buffer;

	if (number == Type(0)){
		(*bufferTmp) = T('0');
		bufferTmp++;
		(*bufferTmp) = T('\0');
		return 1;
	}

	if (number < 0){
		(*bufferTmp) = T('-');
		bufferTmp++;
		number = -number;
	}

	int comma = 1;
	while (number > Type(base)){
		number /= Type(base);
		comma++;
	}
	while (number < Type(1)){
		number *= Type(base);
		comma--;
	}
	int i;
	for (i = 0; i < comma; i++, bufferTmp++){
		unsigned long long castedNumber = (unsigned long long)number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % base];
		number *= Type(base);
	}

	*bufferTmp = T('.');
	bufferTmp++;

	int precisionI = (int) precision;
	for (i = comma; i < precisionI; i++, bufferTmp++){
		unsigned long long castedNumber = (unsigned long long)number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % base];
		number *= Type(base);
	}
	return (typename BasicString<T>::Size)(bufferTmp - buffer);
}

///WITH SENTINEL

template<typename T>
template<typename Type, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::_convertUI2String(Type number, T * buffer) {
	_assert(Base <= 16 && Base > 0);
	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type(Base);
		if ( number < Type(Base) ) break;
		number /= Type(Base);
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, bufferTmp++ ) {
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	( *bufferTmp ) = T('\0');
	return ( typename BasicString<T>::Size )( bufferTmp - buffer );
}

template<typename T>
template<typename Type>
typename BasicString<T>::Size BasicString<T>::_convertUI2String(Type number, T * buffer, unsigned int base) {
	_assert(base <= 16 && base > 0);
	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type(base);
		if ( number < Type(base) ) break;
		number /= Type(base);
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, bufferTmp++ ) {
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	( *bufferTmp ) = T('\0');
	return ( typename BasicString<T>::Size )( bufferTmp - buffer );
}


template<typename T>
template<typename Type, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::_convertI2String(Type number, T * buffer) {
	_assert(Base <= 16 && Base > 0);

	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	if ( number < Type(0) ) {
		( *bufferTmp ) = T('-');
		bufferTmp++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type(Base);
		if ( number < Type(Base) ) break;
		number /= Type(Base);
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, bufferTmp++ ) {
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	( *bufferTmp ) = T('\0');
	return ( typename BasicString<T>::Size )( bufferTmp - buffer );
}

template<typename T>
template<typename Type>
typename BasicString<T>::Size BasicString<T>::_convertI2String(Type number, T * buffer, unsigned int base) {
	_assert(base <= 16 && base > 0);

	static Type tmpBuffer[sizeof(Type) * 8];

	auto bufferTmp = buffer;
	if ( number < Type(0) ) {
		( *bufferTmp ) = T('-');
		bufferTmp++;
		number = -number;
	}


	auto tmpP = tmpBuffer;
	while ( true ) {
		*tmpP = number % Type(base);
		if ( number < Type(base) ) break;
		number /= Type(base);
		tmpP++;
	}

	for ( ; tmpP >= tmpBuffer; tmpP--, bufferTmp++ ) {
		*bufferTmp = BasicString<T>::numbers[*tmpP];
	}
	( *bufferTmp ) = T('\0');
	return ( typename BasicString<T>::Size )( bufferTmp - buffer );
}


template<typename T>
template<typename Type, unsigned int Precision, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::_convertFloat2String(Type number, T * buffer) {
	_assert(Base <= 16 && Precision < 50);

	if ( number == INFINITY ) {
		buffer[0] = T('I');
		buffer[1] = T('N');
		buffer[2] = T('F');
		return Size(3);
	}


	auto bufferTmp = buffer;

	if ( number == Type(0) ) {
		( *bufferTmp ) = T('0');
		bufferTmp++;
		( *bufferTmp ) = T('\0');
		return 1;
	}

	if ( number < 0 ) {
		( *bufferTmp ) = T('-');
		bufferTmp++;
		number = -number;
	}

	int comma = 1;
	while ( number > Type(Base) ) {
		number /= Type(Base);
		comma++;
	}
	while ( number < Type(1) ) {
		number *= Type(Base);
		comma--;
	}
	int i;
	for ( i = 0; i < comma; i++, bufferTmp++ ) {
		unsigned long long castedNumber = ( unsigned long long )number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % Base];
		number *= Type(Base);
	}

	*bufferTmp = T('.');
	bufferTmp++;

	for ( i = comma; i < (int) Precision; i++, bufferTmp++ ) {
		unsigned long long castedNumber = ( unsigned long long )number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % Base];
		number *= Type(Base);
	}
	( *bufferTmp ) = T('\0');
	return ( typename BasicString<T>::Size )( bufferTmp - buffer );
}

template<typename T>
template<typename Type>
typename BasicString<T>::Size BasicString<T>::_convertFloat2String(Type number, T * buffer, unsigned int precision, unsigned int base) {
	_assert(base <= 16 && base > 0);

	auto bufferTmp = buffer;

	if ( number == Type(0) ) {
		( *bufferTmp ) = T('0');
		bufferTmp++;
		( *bufferTmp ) = T('\0');
		return 1;
	}

	if ( number < 0 ) {
		( *bufferTmp ) = T('-');
		bufferTmp++;
		number = -number;
	}

	int comma = 1;
	while ( number > Type(base) ) {
		number /= Type(base);
		comma++;
	}
	while ( number < Type(1) ) {
		number *= Type(base);
		comma--;
	}
	int i;
	for ( i = 0; i < comma; i++, bufferTmp++ ) {
		unsigned long long castedNumber = ( unsigned long long )number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % base];
		number *= Type(base);
	}

	*bufferTmp = T('.');
	bufferTmp++;

	int precisionI = (int) precision;
	for ( i = comma; i < precisionI; i++, bufferTmp++ ) {
		unsigned long long castedNumber = ( unsigned long long )number;
		*bufferTmp = BasicString<T>::numbers[castedNumber % base];
		number *= Type(base);
	}
	( *bufferTmp ) = T('\0');
	return ( typename BasicString<T>::Size )( bufferTmp - buffer );
}


/************************************************************************/
/* toCString()                                                          */
/************************************************************************/


template<typename T>
template<typename C>
typename BasicString<T>::Size BasicString<T>::toCString(const C & c, T * buffer) {
	buffer[0] = c;
	buffer[1] = T('\0');
	return Size(1);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(const char & c, T * buffer) {
	buffer[0] = c;
	buffer[1] = T('\0');
	return Size(1);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(const wchar_t & c, T * buffer) {
	buffer[0] = c;
	buffer[1] = T('\0');
	return Size(1);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned char number, T * buffer){
	return _convertUI2String<unsigned char, Base>(number, buffer);
}


template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned short number, T * buffer){
	return _convertUI2String<unsigned short, Base>(number, buffer);
}


template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned int number, T * buffer){
	return _convertUI2String<unsigned int, Base>(number, buffer);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(int number, T * buffer){
	return _convertI2String<int, Base>(number, buffer);

}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned long long number, T * buffer){
	return _convertUI2String<unsigned long long, Base>(number, buffer);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(long long number, T * buffer){
	return _convertI2String<long long, Base>(number, buffer);

}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned long number, T * buffer){
	return _convertUI2String<unsigned long, Base>(number, buffer);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(long number, T * buffer){
	return _convertI2String<long, Base>(number, buffer);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(double number, T * buffer){
	return _convertFloat2String<double, Precision, Base>(number, buffer);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCString(float number, T * buffer){
	return _convertFloat2String<float, Precision, Base>(number, buffer);
}


template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned char number, T * buffer, unsigned int base){
	return _convertUI2String<unsigned char>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned short number, T * buffer, unsigned int base){
	return _convertUI2String<unsigned short>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned int number, T * buffer, unsigned int base){
	return _convertUI2String<unsigned int>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(int number, T * buffer, unsigned int base){
	return _convertI2String<int>(number, buffer, base);

}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned long long number, T * buffer, unsigned int base){
	return _convertUI2String<unsigned long long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(long long number, T * buffer, unsigned int base){
	return _convertI2String<long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(unsigned long number, T * buffer, unsigned int base){
	return _convertUI2String<unsigned long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(long number, T * buffer, unsigned int base){
	return _convertI2String<long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(double number, T * buffer, unsigned int precision, unsigned int base){
	return _convertFloat2String<double, Precision, Base>(number, buffer, precision, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(float number, T * buffer, unsigned int precision, unsigned int base){
	return _convertFloat2String<float, Precision, Base>(number, buffer, precision, base);
}


template<typename T>
typename BasicString<T>::Size BasicString<T>::toCString(bool b, T * buffer){
	if (b) {
		buffer[0] = T('t');
		buffer[1] = T('r');
		buffer[2] = T('u');
		buffer[3] = T('e');
		buffer[4] = T('\0');
		return Size(4);
	} else {
		buffer[0] = T('f');
		buffer[1] = T('a');
		buffer[2] = T('l');
		buffer[3] = T('s');
		buffer[4] = T('e');
		buffer[5] = T('\0');
		return Size(5);
	}
}


/************************************************************************/
/* toCString() without adding sentinel                                  */
/************************************************************************/



template<typename T>
template<typename C>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(const C & c, T * buffer) {
	buffer[0] = c;
	return Size(1);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(const char & c, T * buffer) {
	buffer[0] = c;
	return Size(1);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(const wchar_t & c, T * buffer) {
	buffer[0] = c;
	return Size(1);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned char number, T * buffer) {
	return _convertUI2StringWOS<unsigned char, Base>(number, buffer);
}


template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned short number, T * buffer) {
	return _convertUI2StringWOS<unsigned short, Base>(number, buffer);
}


template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned int number, T * buffer) {
	return _convertUI2StringWOS<unsigned int, Base>(number, buffer);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(int number, T * buffer) {
	return _convertI2StringWOS<int, Base>(number, buffer);

}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned long long number, T * buffer) {
	return _convertUI2StringWOS<unsigned long long, Base>(number, buffer);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(long long number, T * buffer) {
	return _convertI2StringWOS<long long, Base>(number, buffer);

}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned long number, T * buffer) {
	return _convertUI2StringWOS<unsigned long, Base>(number, buffer);
}

template<typename T>
template<unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(long number, T * buffer) {
	return _convertI2StringWOS<long, Base>(number, buffer);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(double number, T * buffer) {
	return _convertFloat2StringWOS<double, Precision, Base>(number, buffer);
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(float number, T * buffer) {
	return _convertFloat2StringWOS<float, Precision, Base>(number, buffer);
}


template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned char number, T * buffer, unsigned int base) {
	return _convertUI2StringWOS<unsigned char>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned short number, T * buffer, unsigned int base) {
	return _convertUI2StringWOS<unsigned short>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned int number, T * buffer, unsigned int base) {
	return _convertUI2StringWOS<unsigned int>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(int number, T * buffer, unsigned int base) {
	return _convertI2StringWOS<int>(number, buffer, base);

}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned long long number, T * buffer, unsigned int base) {
	return _convertUI2StringWOS<unsigned long long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(long long number, T * buffer, unsigned int base) {
	return _convertI2StringWOS<long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(unsigned long number, T * buffer, unsigned int base) {
	return _convertUI2StringWOS<unsigned long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(long number, T * buffer, unsigned int base) {
	return _convertI2StringWOS<long>(number, buffer, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(double number, T * buffer, unsigned int precision, unsigned int base) {
	return _convertFloat2StringWOS<double, Precision, Base>(number, buffer, precision, base);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(float number, T * buffer, unsigned int precision, unsigned int base) {
	return _convertFloat2StringWOS<float, Precision, Base>(number, buffer, precision, base);
}


template<typename T>
typename BasicString<T>::Size BasicString<T>::toCStringWOS(bool b, T * buffer) {
	if ( b ) {
		buffer[0] = T('t');
		buffer[1] = T('r');
		buffer[2] = T('u');
		buffer[3] = T('e');
		return Size(4);
	} else {
		buffer[0] = T('f');
		buffer[1] = T('a');
		buffer[2] = T('l');
		buffer[3] = T('s');
		buffer[4] = T('e');
		return Size(5);
	}
}


/************************************************************************/
/* From CString                                                         */
/************************************************************************/
template<typename T>
template<typename Type, unsigned int Base>
static Type BasicString<T>::_toSignedInteger(T * it) {
	for (; *it == T(' '); it++);		//Spaces are useless

	if (*it == T('\0'))
		return 0;

	Type result;
	if (*it == T('-')) {			//Check the sign
		it++;
		if (*it != T('\0')) {
			result = -(*it - 48);
			it++;
		} else
			return 0;
	} else {
		if (*it != T('\0')) {
			result = *it - 48;
			it++;
		} else
			return 0;
	}

	for (; *it != T('\0'); it++) {	//Start the computation
		result = result * Base + (*it - T('0'));
	}

	return result;
}


template<typename T>
template<typename Type, unsigned int Base>
static Type BasicString<T>::_toUnsignedInteger(T * it) {
	for (; *it == T(' '); it++);		//Spaces are useless

	if (*it == T('\0'))
		return 0;

	_assert(*it != T('-'));

	Type result;
	if (*it != T('\0')) {
		result = *it - 48;
		it++;
	} else
		return 0;

	for (; *it != T('\0'); it++) {	//Start the computation
		result = result * Base + (*it - T('0'));
	}

	return result;
}

template<typename T>
template<typename Type, unsigned int Base>
static Type BasicString<T>::_toFloat(T * it) {
	for (; *it == T(' '); it++);		//Spaces are useless

	if (*it == T('\0'))
		return 0;

	Type result = 0;
	bool negative;
	if (*it == T('-')) {			//Check the sign
		it++;
		negative = true;
	} else {
		negative = false;
	}


	for (; *it != T('\0') && *it != T('.'); it++) {			//Start the computation
		result = result * Type(Base) + (Type)(*it - T('0'));
	}

	if (*it == T('.')) 
		it++;

	Type exp = Base;
	for (; *it != T('\0'); it++) {
		result += (Type)(*it - T('0')) / (exp);
		exp *= Base;
	}

	if (negative)
		result *= Type(-1);

	return result;
}



template<typename T>
template<typename Type>
static Type BasicString<T>::_toSignedInteger(T * it, unsigned int base) {
	for (; *it == T(' '); it++);		//Spaces are useless

	if (*it == T('\0'))
		return 0;

	Type result;
	if (*it == T('-')) {			//Check the sign
		it++;
		if (*it != T('\0')) {
			result = -(*it - 48);
			it++;
		} else
			return 0;
	} else {
		if (*it != T('\0')) {
			result = *it - 48;
			it++;
		} else
			return 0;
	}

	for (; *it != T('\0'); it++) {	//Start the computation
		result = result * base + (*it - T('0'));
	}

	return result;
}


template<typename T>
template<typename Type>
static Type BasicString<T>::_toUnsignedInteger(T * it, unsigned int base) {
	for (; *it == T(' '); it++);		//Spaces are useless

	if (*it == T('\0'))
		return 0;

	_assert(*it != T('-'));

	Type result;
	if (*it != T('\0')) {
		result = *it - 48;
		it++;
	} else
		return 0;

	for (; *it != T('\0'); it++) {	//Start the computation
		result = result * base + (*it - T('0'));
	}

	return result;
}

template<typename T>
template<typename Type>
static Type BasicString<T>::_toFloat(T * it, unsigned int base) {
	for (; *it == T(' '); it++);		//Spaces are useless

	if (*it == T('\0'))
		return 0;

	Type result = 0;
	bool negative;
	if (*it == T('-')) {			//Check the sign
		it++;
		negative = true;
	} else {
		negative = false;
	}


	for (; *it != T('\0') && *it != T('.'); it++) {			//Start the computation
		result = result * Type(base) + (Type)(*it - T('0'));
	}

	if (*it == T('.'))
		it++;

	Type exp = base;
	for (; *it != T('\0'); it++) {
		result += (Type)(*it - T('0')) / (exp);
		exp *= base;
	}

	if (negative)
		result *= Type(-1);

	return result;
}



template<typename T>
template<unsigned int Base>
char BasicString<T>::toChar(T * it) {
	return _toSignedInteger<char, Base>(it);
}

template<typename T>
template<unsigned int Base>
short BasicString<T>::toShort(T * it) {
	return _toSignedInteger<short, Base>(it);
}

template<typename T>
template<unsigned int Base>
int BasicString<T>::toInt(T * it) {
	return _toSignedInteger<int, Base>(it);
}

template<typename T>
template<unsigned int Base>
long BasicString<T>::toLong(T * it) {
	return _toSignedInteger<long, Base>(it);
}

template<typename T>
template<unsigned int Base>
long long BasicString<T>::toLongLong(T * it) {
	return _toSignedInteger<long long, Base>(it);
}

template<typename T>
template<unsigned int Base>
unsigned char BasicString<T>::toUChar(T * it) {
	return _toUnsignedInteger<unsigned char, Base>(it);
}

template<typename T>
template<unsigned int Base>
unsigned short BasicString<T>::toUShort(T * it) {
	return _toUnsignedInteger<unsigned short, Base>(it);
}

template<typename T>
template<unsigned int Base>
unsigned int BasicString<T>::toUInt(T * it) {
	return _toUnsignedInteger<unsigned int, Base>(it);
}

template<typename T>
template<unsigned int Base>
unsigned long BasicString<T>::toULong(T * it) {
	return _toUnsignedInteger<unsigned long, Base>(it);
}

template<typename T>
template<unsigned int Base>
unsigned long long BasicString<T>::toULongLong(T * it) {
	return _toUnsignedInteger<unsigned long long, Base>(it);
}

template<typename T>
template<unsigned int Base>
float BasicString<T>::toFloat(T * buffer) {
	return _toFloat<float, Base>(buffer);
}

template<typename T>
template<unsigned int Base>
double BasicString<T>::toDouble(T * buffer) {
	return _toFloat<double, Base>(buffer);
}











template<typename T>
char BasicString<T>::toChar(T * it, unsigned int base) {
	return _toSignedInteger<char>(it, base);
}

template<typename T>
short BasicString<T>::toShort(T * it, unsigned int base) {
	return _toSignedInteger<short>(it, base);
}

template<typename T>
int BasicString<T>::toInt(T * it, unsigned int base) {
	return _toSignedInteger<int>(it, base);
}

template<typename T>
long BasicString<T>::toLong(T * it, unsigned int base) {
	return _toSignedInteger<long>(it, base);
}

template<typename T>
long long BasicString<T>::toLongLong(T * it, unsigned int base) {
	return _toSignedInteger<long long>(it, base);
}

template<typename T>
unsigned char BasicString<T>::toUChar(T * it, unsigned int base) {
	return _toUnsignedInteger<unsigned char>(it, base);
}

template<typename T>
unsigned short BasicString<T>::toUShort(T * it, unsigned int base) {
	return _toUnsignedInteger<unsigned short>(it, base);
}

template<typename T>
unsigned int BasicString<T>::toUInt(T * it, unsigned int base) {
	return _toUnsignedInteger<unsigned int>(it, base);
}

template<typename T>
unsigned long BasicString<T>::toULong(T * it, unsigned int base) {
	return _toUnsignedInteger<unsigned long>(it, base);
}

template<typename T>
unsigned long long BasicString<T>::toULongLong(T * it, unsigned int base) {
	return _toUnsignedInteger<unsigned long long>(it, base);
}

template<typename T>
float BasicString<T>::toFloat(T * buffer, unsigned int base) {
	return _toFloat<float>(buffer, base);
}

template<typename T>
double BasicString<T>::toDouble(T * buffer, unsigned int base) {
	return _toFloat<double>(buffer, base);
}





/************************************************************************/
/* From String                                                          */
/************************************************************************/
template<typename T>
template<unsigned int Base>
char BasicString<T>::toChar() {
	return _toSignedInteger<char, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
short BasicString<T>::toShort() {
	return _toSignedInteger<short, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
int BasicString<T>::toInt() {
	return _toSignedInteger<int, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
long BasicString<T>::toLong() {
	return _toSignedInteger<long, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
long long BasicString<T>::toLongLong() {
	return _toSignedInteger<long long, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
unsigned char BasicString<T>::toUChar() {
	return _toUnsignedInteger<unsigned char, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
unsigned short BasicString<T>::toUShort() {
	return _toUnsignedInteger<unsigned short, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
unsigned int BasicString<T>::toUInt() {
	return _toUnsignedInteger<unsigned int, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
unsigned long BasicString<T>::toULong() {
	return _toUnsignedInteger<unsigned long, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
unsigned long long BasicString<T>::toULongLong() {
	return _toUnsignedInteger<unsigned long long, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
float BasicString<T>::toFloat() {
	return _toFloat<float, Base>(this -> dataTable);
}

template<typename T>
template<unsigned int Base>
double BasicString<T>::toDouble() {
	return _toFloat<double, Base>(this -> dataTable);
}











template<typename T>
char BasicString<T>::toChar(unsigned int base) {
	return _toSignedInteger<char>(this -> dataTable, base);
}

template<typename T>
short BasicString<T>::toShort(unsigned int base) {
	return _toSignedInteger<short>(this -> dataTable, base);
}

template<typename T>
int BasicString<T>::toInt(unsigned int base) {
	return _toSignedInteger<int>(this -> dataTable, base);
}

template<typename T>
long BasicString<T>::toLong(unsigned int base) {
	return _toSignedInteger<long>(this -> dataTable, base);
}

template<typename T>
long long BasicString<T>::toLongLong(unsigned int base) {
	return _toSignedInteger<long long>(this -> dataTable, base);
}

template<typename T>
unsigned char BasicString<T>::toUChar(unsigned int base) {
	return _toUnsignedInteger<unsigned char>(this -> dataTable, base);
}

template<typename T>
unsigned short BasicString<T>::toUShort(unsigned int base) {
	return _toUnsignedInteger<unsigned short>(this -> dataTable, base);
}

template<typename T>
unsigned int BasicString<T>::toUInt(unsigned int base) {
	return _toUnsignedInteger<unsigned int>(this -> dataTable, base);
}

template<typename T>
unsigned long BasicString<T>::toULong(unsigned int base) {
	return _toUnsignedInteger<unsigned long>(this -> dataTable, base);
}

template<typename T>
unsigned long long BasicString<T>::toULongLong(unsigned int base) {
	return _toUnsignedInteger<unsigned long long>(this -> dataTable, base);
}

template<typename T>
float BasicString<T>::toFloat(unsigned int base) {
	return _toFloat<float>(this -> dataTable, base);
}

template<typename T>
double BasicString<T>::toDouble(unsigned int base) {
	return _toFloat<double>(this -> dataTable, base);
}










/************************************************************************/
/* toString()                                                           */
/************************************************************************/


template<typename T>
BasicString<T> BasicString<T>::toString(const T & c) {
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(2);
	newStr.size = toCString(c, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(unsigned char number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned char) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(unsigned short number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(short) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(unsigned int number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned int) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(int number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(int) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(unsigned long long number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned long long) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(long long number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(long long) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(unsigned long number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned long) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Base>
BasicString<T> BasicString<T>::toString(long number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(long) * 8);
	newStr.size = toCString<Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> BasicString<T>::toString(double number){
	BasicString<T> newStr;
	newStr._allocateNoNullDelete(sizeof(double) * 8 + Precision);
	newStr.size = toCString<Precision, Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
template<unsigned int Precision, unsigned int Base>
BasicString<T> BasicString<T>::toString(float number){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(float) * 8 + Precision);
	newStr.size = toCString<Precision, Base>(number, newStr.dataTable);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(unsigned char number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned char) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(unsigned short number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned short) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}


template<typename T>
BasicString<T> BasicString<T>::toString(unsigned int number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned int) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(int number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(int) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(unsigned long long number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned long long) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(long long number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(long long) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(unsigned long number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(unsigned long) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(long number, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(long) * 8);
	newStr.size = toCString(number, newStr.dataTable, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(double number, unsigned int precision, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(double) * 8 + precision);
	newStr.size = toCString(number, newStr.dataTable, precision, base);
	return newStr;
}

template<typename T>
BasicString<T> BasicString<T>::toString(float number, unsigned int precision, unsigned int base){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(sizeof(float) * 8 + precision);
	newStr.size = toCString(number, newStr.dataTable, precision, base);
	return newStr;
}


template<typename T>
BasicString<T> BasicString<T>::toString(bool b){
	BasicString<T> newStr(ctor::null);
	newStr._allocateNoNullDelete(6);
	newStr.size = toCString(b);
	return newStr;
}



/************************************************************************/
/* OPERATOR =                                                           */
/************************************************************************/

template<typename T>
BasicString<T> & BasicString<T>::operator=(const unsigned short & ui){
	if (getMaxSize() < 7)
		_allocateNoNull(7);
	this->size = toCString(ui, this->dataTable);
	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::operator=(const unsigned char & ui){
	if (getMaxSize() < 5)
		_allocateNoNull(5);
	this->size = toCString(ui, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const int & i){
	if (getMaxSize() < 10)
		_allocateNoNull(10);
	this->size = toCString(i, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const unsigned int & ui){
	if (getMaxSize() < 10)
		_allocateNoNull(10);
	this->size = toCString(ui, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const long & l){
	if (getMaxSize() < 21)
		_allocateNoNull(21);
	this->size = toCString(l, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const unsigned long & ul){
	if (getMaxSize() < 21)
		_allocateNoNull(21);
	this->size = toCString(ul, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const long long & ll){
	if (getMaxSize() < 21)
		_allocateNoNull(21);
	this->size = toCString(ll, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const unsigned long long & ull){
	if (getMaxSize() < 21)
		_allocateNoNull(21);
	this->size = toCString(ull, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const double & d){
	if (getMaxSize() < 11)
		_allocateNoNull(11);
	this->size = toCString(d, this->dataTable);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const float & d){
	if (getMaxSize() < 6)
		_allocateNoNull(6);
	this->size = toCString(d, this->dataTable);
	return *this;
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator=(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str){
	*this = str.c_str();
	return *this;
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator=(const BasicString<C> & str){
	Vector<T>::operator=(str);
	return *this;
}

template<typename T>
BasicString<T> & BasicString<T>::operator=(const BasicString & str) {
	Vector<T>::operator=(str);
	return *this;
}



template<typename T>
BasicString<T> & BasicString<T>::operator=(BasicString<T> && str) {
	Vector<T>::operator=(Utility::toRValue(str));
	return *this;
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator=(const C * str){
	this->size = BasicString<C>::getSize(str);
	if (getMaxSize() < this->size + 1)
		_allocateNoNull(this->size + 1);
	setValuei(this->size, T('\0'));
	copy(str, 0, this->size);

	return *this;
}


template<typename T>
BasicString<T> & BasicString<T>::operator=(const T & c){
	this->size = 1;
	if (getMaxSize() < 2)
		_allocateNoNull(2);
	setValuei(0, T(c));
	setValuei(1, T('\0'));

	return *this;
}



template<typename T>
BasicString<T> & BasicString<T>::operator=(const bool & b){
	if (getMaxSize() < 6)
		_allocateNoNull(6);
	this-> size = toCString(b, this->dataTable);
	return *this;
}







/************************************************************************/
/* LOGICALS                                                             */
/************************************************************************/
template<typename T>
bool BasicString<T>::operator<=(const BasicString<T> & text) const{
	for (Size i = 0; i < this->size; i++){
		const T & t1 = this->dataTable[i];
		const T & t2 = text.dataTable[i];

		if (t1 < t2) return true;
		else if (t1 > t2) return false;
	}
	return true;
}

template<typename T>
bool BasicString<T>::operator>=(const BasicString<T> & text) const{
	for (Size i = 0; i < this->size; i++){
		const T & t1 = this->dataTable[i];
		const T & t2 = text.dataTable[i];

		if (t1 > t2) return true;
		else if (t1 < t2) return false;
	}
	return true;
}

template<typename T>
bool BasicString<T>::operator<(const BasicString<T> & text) const{
	for (Size i = 0; i < this->size; i++){
		const T & t1 = this->dataTable[i];
		const T & t2 = text.dataTable[i];

		if (t1 < t2) return true;
		else if (t1 > t2) return false;
	}
	return false;
}

template<typename T>
bool BasicString<T>::operator>(const BasicString<T> & text) const{
	for (Size i = 0; i < this->size; i++){
		const T & t1 = this->dataTable[i];
		const T & t2 = text.dataTable[i];

		if (t1 > t2) return true;
		else if (t1 < t2) return false;
	}
	return false;
}

template<typename T>
bool BasicString<T>::operator==(const BasicString<T> & text) const{
	return Vector::operator==(text);
}

template<typename T>
bool BasicString<T>::operator!=(const BasicString<T> & text) const{
	return Vector::operator!=(text);
}



template<typename T>
bool BasicString<T>::operator==(const T & c) const {
	return Vector::operator==(c);
}

template<typename T>
bool BasicString<T>::operator!=(const T & c) const {
	return Vector::operator!=(c);
}


template<typename T>
bool BasicString<T>::operator<(const T & c) const {
	return Vector::operator<(c);
}
template<typename T>
bool BasicString<T>::operator>(const T & c) const {
	return Vector::operator>(c);
}

template<typename T>
bool BasicString<T>::operator<=(const T & c) const {
	return Vector::operator<=(c);
}
template<typename T>
bool BasicString<T>::operator>=(const T & c) const {
	return Vector::operator>=(c);
}


/************************************************************************/
/* OTHERS                                                               */
/************************************************************************/


template<typename T>
 typename Vector<T>::Size BasicString<T>::getSize(const T * str){
	typename Vector<T>::Size size(0);
	constexpr const T end('\0');
	for (size; str[size] != end; size++);
	return size;
}


template<typename T>
typename BasicString<T>::RandomAccessIterator BasicString<T>::getLastIt(const BasicString<T> & str) const{
	if (!str.getSize() || this->size < str.getSize())
		goto NOTFOUND;

	auto iteratorSize = getEnd() - str.getSize() + 1;
	for (auto it = iteratorSize - 1; it >= getBegin();){
		for (Size j = 0; j < str.getSize(); j++){
			if (*(it + j) != str[j]){
				goto ENDLOOP;
			}
		}
		return it;
	ENDLOOP:it--;
	}
NOTFOUND:return getEnd();
}

template<typename T>
typename BasicString<T>::RandomAccessIterator BasicString<T>::getFirstIt(const BasicString<T> & str) const{
	if (!str.getSize() || this->size < str.getSize())
		goto NOTFOUND;

	auto iteratorSize = getEnd() - str.getSize() + 1;
	for (auto it = getBegin(); it < iteratorSize;){
		for (Size j = 0; j < str.getSize(); j++){
			if (*(it + j) != str[j]){
				goto ENDLOOP;
			}
		}
		return it;
	ENDLOOP:it++;
	}
NOTFOUND:return getEnd();
}

template<typename T>
typename BasicString<T>::RandomAccessIterator BasicString<T>::getLastIt(const T & c) const{
	for (auto it = getEnd() - 1; it >= getBegin(); it--){
		if (*it == c)
			return it;
	}
	return getEnd();
}

template<typename T>
typename BasicString<T>::RandomAccessIterator BasicString<T>::getFirstIt(const T & c) const{
	for (auto it = getBegin(); it < getEnd(); it++){
		if (*it == c){
			return it;
		}
	}
	return getEnd();
}


template<typename T>
typename BasicString<T>::Size BasicString<T>::getLast(const BasicString<T> & str) const{
	return BasicString<T>::getLast(this->dataTable, this->size, str.getData(), str.getSize());
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getFirst(const BasicString<T> & str) const{
	return BasicString<T>::getFirst(this->dataTable, this->size, str.getData(), str.getSize());
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getLast(const T & c) const{
	return BasicString<T>::getLast(this->dataTable, getSize(), c);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getFirst(const T & c) const{
	return BasicString<T>::getFirst(this->dataTable, getSize(), c);
}



template<typename T>
typename BasicString<T>::Size BasicString<T>::getLast(const T * buffer, const Size & bufferSize, const T * toSearch, const Size & toSearchSize){
	if (!toSearchSize || bufferSize < toSearchSize)
		goto NOTFOUND;

	Size iteratorSize = bufferSize - toSearchSize;
	for (Size i = iteratorSize; i >= 0;){
		for (Size j = 0; j < toSearchSize; j++){
			if (buffer[i + j] != toSearch[j]){
				goto ENDLOOP;
			}
		}
		return i;

	ENDLOOP:i--;
	}
NOTFOUND:return BasicString<T>::overflow;
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getFirst(const T * buffer, const Size & bufferSize, const T * toSearch, const Size & toSearchSize) {
	if (!toSearchSize || bufferSize < toSearchSize)
		goto NOTFOUND;

	Size iteratorSize = bufferSize - toSearchSize + 1;
	for (Size i = 0; i < iteratorSize;){
		for (Size j = 0; j < toSearchSize; j++){
			if (buffer[i + j] != toSearch[j]){
				goto ENDLOOP;
			}
		}
		return i;

	ENDLOOP:i++;
	}
NOTFOUND:return BasicString<T>::overflow;
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getLast(const T * buffer, const Size & bufferSize, const T & c) {
	for (Size i = bufferSize - 1; i >= 0; i--){
		if (buffer[i] == c){
			return i;
		}
	}
	return BasicString<T>::overflow;
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getFirst(const T * buffer, const Size & bufferSize, const T & c) {
	for (Size i = 0; i < bufferSize; i++){
		if (buffer[i] == c){
			return i;
		}
	}
	return BasicString<T>::overflow;
}


template<typename T>
typename BasicString<T>::Size BasicString<T>::getLast(const T * buffer, const T * toSearch){
	return BasicString<T>::getLast(buffer, BasicString<T>::getSize(buffer), toSearch, BasicString<T>::getSize(toSearch));
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getFirst(const T * buffer, const T * toSearch) {
	if (!toSearchSize || bufferSize < toSearchSize)
		goto NOTFOUND;


	Size iteratorSize = bufferSize - toSearchSize + 1;
	const T & c = buffer[0];
	for (Size i = 0; c != T('\0');){

		const T & d = toSearch[0];
		for (Size j = 0; d != T('\0'); j++, d = toSearch[j]){
			if (buffer[i + j] != d){
				goto ENDLOOP;
			}
		}
		return i;

	ENDLOOP:
		i++;
		c = buffer[i];
	}
NOTFOUND:return BasicString<T>::overflow;
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getLast(const T * buffer, const T & c) {
	return BasicString<T>::getLast(buffer, BasicString<T>::getSize(buffer), c);
}

template<typename T>
typename BasicString<T>::Size BasicString<T>::getFirst(const T * buffer, const T & c) {
	const T & d = buffer[0];
	for (Size i = 0; d != T('\0'); i++, d = buffer[i]){
		if (d == c)
			return i;
	}
	return BasicString<T>::overflow;
}




template<typename T>
void BasicString<T>::clear() {
	this -> size = 0;
	this -> dataTable[0] = T('\0');
	_updateIterators();
}

template<typename T>
Vector<BasicString<T>> BasicString<T>::split(const T & delimiter) const{
	return BasicString<T>::split(*this, delimiter);
}

template<typename T>
Vector<BasicString<T>> BasicString<T>::split(const BasicString<T> & s, const T & delimiter){
	Vector<BasicString<T>> v;
	Size lastIndex = 0;
	Size i;
	for (i = 0; i < s.getSize(); i++){
		const T & c = s[i];
		if (c == delimiter && i != lastIndex){
			v.push(BasicString<T>(s.getData() + lastIndex, i - lastIndex));
			lastIndex = i + 1;
		}
	}
	v.push(BasicString<T>(s.getData() + lastIndex, i - lastIndex));

	return v;
}


template<typename T>
bool BasicString<T>::isNumeric(const BasicString<T> & v){
	for (Size i = 0; i < this->size; i++){
		const T & c = this->dataTable[i];
		if (c < 40 || c > 57)
			return false;
	}
	return true;
}

template<typename T>
bool BasicString<T>::isNumeric() const{
	return BasicString<T>::isNumeric(*this);
}


template<typename T>
const T * BasicString<T>::toCString() const{
	return this->dataTable;
}






template<typename T>
BasicString<T> BasicString<T>::getSubStr(const Size & index, const Size & size){
	if (index > this->size)
		return BasicString<T>();

	Size realSize = Math::min(size, this->size - index);
	return BasicString<T>(this->dataTable + index, realSize);
}

template<typename T>
BasicString<T> BasicString<T>::getFileName(){
	Size lastSlash = getLast(T('/'));
	if (lastSlash == BasicString<T>::overflow)
		return *this;

	return BasicString<T>(this->dataTable + lastSlash + 1, this->size - lastSlash);
}

template<typename T>
BasicString<T> BasicString<T>::getDirectory(){
	Size lastSlash = getLast(T('/'));
	if (lastSlash == BasicString<T>::overflow)
		return *this;

	BasicString<T> newString;
	newString.concat(this->dataTable, lastSlash + 1);
	return newString;
}







template<typename T>
void BasicString<T>::replace(const BasicString<T> & toReplace, const BasicString<T> & byThis){
	BasicString<T> newString;
	newString.allocate(this->getMaxSize() + byThis.getSize());

	Size lastIndexSrc = 0;
	Size newFound = 0;
	while (newFound < getSize()){

		newFound = getFirst(this->dataTable + lastIndexSrc, getSize() - lastIndexSrc, toReplace.getData(), toReplace.getSize());
		if (newFound == BasicString<T>::overflow){
			newFound = getSize();

			Size cropedSize = newFound - lastIndexSrc;
			newString.concat(this->dataTable + lastIndexSrc, cropedSize);

			break;
		}

		Size cropedSize = newFound - lastIndexSrc;
		newString.concat(this->dataTable + lastIndexSrc, cropedSize);

		lastIndexSrc += cropedSize + toReplace.getSize();		//1 is the searchSize

		newString.concat(byThis);
	}

	*this = newString;
}






template<typename T>
void BasicString<T>::replace(const T & toReplace, const BasicString<T> & byThis){
	BasicString<T> newString;
	newString.allocate(this->getMaxSize() + byThis.getSize());

	Size lastIndexSrc = 0;
	Size newFound = 0;
	while (newFound < getSize()){

		newFound = getFirst(this->dataTable + lastIndexSrc, getSize() - lastIndexSrc, toReplace);
		if (newFound == BasicString<T>::overflow){
			newFound = getSize();

			Size cropedSize = newFound - lastIndexSrc;
			newString.concat(this->dataTable + lastIndexSrc, cropedSize);

			break;
		}

		Size cropedSize = newFound - lastIndexSrc;
		newString.concat(this->dataTable + lastIndexSrc, cropedSize);

		lastIndexSrc += cropedSize + 1;		//1 is the searchSize

		newString += byThis;
	}
	*this = newString;
}

template<typename T>
void BasicString<T>::replace(const T & toReplace, const T & byThis){
	for (auto it = getBegin(); it < getEnd(); it++){
		if (*it == toReplace)
			*it = byThis;
	}
}





template<typename T>
std::ostream & operator<<(std::ostream & stream, const BasicString<T> & str){
	stream << str.toCString();
	return stream;
}















template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<(const C * str) {
	return concat(str);
}


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<(const BasicString<C> & str) {
	return concat(str);
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str) {
	return concat(str);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const unsigned char & uc) {
	return concat(uc);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const unsigned short & us) {
	return concat(us);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const int & i) {
	return concat(i);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const unsigned int & ui) {
	return concat(ui);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const long & l) {
	return concat(l);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const unsigned long & ul) {
	return concat(ul);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const long long & ll) {
	return concat(ll);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const unsigned long long & ull) {
	return concat(ull);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const double & d) {
	return concat(d);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const float & f) {
	return concat(f);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const bool & b) {
	return concat(b);
}


/*
template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<(const C & c) {
	return concat(c);
}*/


template<typename T>
BasicString<T> & BasicString<T>::operator<<(const char & c) {
	return concat(c);
}

template<typename T>
BasicString<T> & BasicString<T>::operator<<(const wchar_t & c) {
	return concat(c);
}


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator<<(const Vector<C> & v) {
	concat("[ ");
	for ( Vector<T>::Size i = 0; i < v.getSize(); i++ ) {
		if ( i ) concat(" | ");
		operator<<(v[i]);
	}
	return concat(" ]");
}








template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=(const C * str) {
	return concat(str);
}


template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=(const BasicString<C> & str) {
	return concat(str);
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=(const std::basic_string<C, std::char_traits<C>, std::allocator<C> > & str) {
	return concat(str);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const unsigned char & uc) {
	return concat(uc);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const unsigned short & us) {
	return concat(us);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const int & i) {
	return concat(i);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const unsigned int & ui) {
	return concat(ui);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const long & l) {
	return concat(l);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const unsigned long & ul) {
	return concat(ul);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const long long & ll) {
	return concat(ll);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const unsigned long long & ull) {
	return concat(ull);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const double & d) {
	return concat(d);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const float & f) {
	return concat(f);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const bool & b) {
	return concat(b);
}

template<typename T>
template<typename C>
BasicString<T> & BasicString<T>::operator+=(const C & c) {
	return concat(c);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const char & c) {
	return concat(c);
}

template<typename T>
BasicString<T> & BasicString<T>::operator+=(const wchar_t & c) {
	return concat(c);
}



template<typename T>
void BasicString<T>::resize(typename Vector<T>::Size newSize) {
	if ( newSize + 1 > this -> maxSize )
		reserve(newSize + 1);

	this -> size = newSize;
	_updateIterators();
}


template<typename T>
bool BasicString<T>::read(std::fstream * fileStream) {
	fileStream -> read((char*) &this -> size, sizeof(this -> size));
	this -> maxSize = this -> size + 1;
	_allocateNoNull(this -> maxSize);

	//Used to know if the type is inherited from BasicIO
	if ( !SimpleIO::readBuffer(fileStream, getData(), getSize()) )
		return false;
	this -> dataTable[getSize()] = T('\0');
	return true;
}



/************************************************************************/
/* format()                                                             */
/************************************************************************/
template<typename T>
void BasicString<T>::_format(const typename BasicString<T>::RandomAccessIterator & referenceStringBegin, const typename BasicString<T>::RandomAccessIterator & referenceStringEnd, BasicString<T> * newString) {
	newString -> _concatWOS(referenceStringBegin, referenceStringEnd - referenceStringBegin);
}

template<typename T>
template<typename T1, typename... Types>
void BasicString<T>::_format(const typename  BasicString<T>::RandomAccessIterator & referenceStringBegin, const typename BasicString<T>::RandomAccessIterator & referenceStringEnd, BasicString<T> * newString, const T1 & arg1, Types ... args) {


	for ( auto it = referenceStringBegin; it != referenceStringEnd; it++ ) {
		if ( *it == T('%') ) {
			newString -> _concatWOS(arg1);				
			_format(it + 1, referenceStringEnd, newString, args...);
			return;
		} else {
			newString -> _concatWOS(*it);
		}
	}
}

template<typename T>
template<typename T1, typename... Types>
BasicString<T> BasicString<T>::format(const BasicString<T> referenceString, const T1 & arg1, Types ... args) {
	BasicString<T> newString(BasicString<T>::null);

	newString.size = 0;
	if ( referenceString.getSize() == 0 )
		newString._allocateNoNullDelete(1);
	else
		newString._allocateNoNullDelete(referenceString.getSize() * 2);


	_format(referenceString.getBegin(), referenceString.getEnd(), &newString, arg1, args...);
	*( newString.dataTable + newString.size ) = T('\0');

	return newString;
}
