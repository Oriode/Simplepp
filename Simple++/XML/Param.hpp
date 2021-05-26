namespace XML {

	template<typename T>
	ParamT<T>::ParamT( const T & name, const T & value ) : name( name ), value( value ) {

	}

	template<typename T>
	ParamT<T>::ParamT() {

	}

	template<typename T>
	ParamT<T>::ParamT( const ParamT<T> & param ) :
		name( param.name ),
		value( param.value ) {

	}

	template<typename T>
	ParamT<T>::ParamT( ParamT<T> && param ) :
		name( Utility::toRValue( param.name ) ),
		value( Utility::toRValue( param.value ) ) {

	}

	template<typename T>
	ParamT<T>::operator T() const {
		return toString();
	}

	template<typename T>
	ParamT<T> & ParamT<T>::operator=( const ParamT<T> & param ) {
		this -> name = param.name;
		this -> value = param.value;
		return *this;
	}

	template<typename T>
	ParamT<T> & ParamT<T>::operator=( ParamT<T> && param ) {
		this -> name = Utility::toRValue( param.name );
		this -> value = Utility::toRValue( param.value );
		return *this;
	}

	template<typename T>
	const T & ParamT<T>::getName() const {
		return this -> name;
	}

	template<typename T>
	void ParamT<T>::setName( const T & name ) {
		this -> name = name;
	}

	template<typename T>
	const T & ParamT<T>::getValue() const {
		return this -> value;
	}

	template<typename T>
	void ParamT<T>::setValue( const T & value ) {
		this -> value = value;
	}

	template<typename T>
	bool ParamT<T>::writeXML( IO::SimpleFileStream * fileStreamP ) const {
		IO::SimpleFileStream & fileStream( *fileStreamP );
		_writeXML<IO::SimpleFileStream, char>( fileStream );
		return !( fileStreamP -> bad() );
	}

	template<typename T>
	bool ParamT<T>::read( IO::SimpleFileStream * fileStream ) {
		if ( !IO::read( fileStream, &this -> name ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}

	template<typename T>
	bool ParamT<T>::write( IO::SimpleFileStream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> name ) )
			return false;
		if ( !IO::write( fileStream, &this -> value ) )
			return false;
		return true;
	}

	template<typename T>
	void ParamT<T>::_clear() {
		this -> name.clear();
		this -> value.clear();
	}

	template<typename T>
	template<typename C, typename Elem>
	void ParamT<T>::_writeXML( C & o ) const {
		o << this -> name;
		if ( this -> value.getSize() ) {
			o << Elem( '=' );
			o << Elem( '"' );
			o << this -> value;
			o << Elem( '"' );
		}
	}

	template<typename T>
	template<typename C>
	C ParamT<T>::toString() const {
		C newString;
		newString.reserve( this -> name.getSize() + this -> value.getSize() + 4 );

		_writeXML<C, C::ElemType>( newString );
		return newString;
	}
}