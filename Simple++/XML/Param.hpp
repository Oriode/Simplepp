namespace XML {

	template<typename T>
	ParamT<T>::ParamT( const T & name, const T & value ) : 
		::ParamT<T, T>(name, value)
	{

	}

	template<typename T>
	ParamT<T>::ParamT() {

	}

	template<typename T>
	ParamT<T>::ParamT( const ParamT<T> & param ) :
		::ParamT<T, T>(param)
	{

	}

	template<typename T>
	ParamT<T>::ParamT( ParamT<T> && param ) :
		::ParamT<T, T>(Utility::toRValue(param))
	{

	}

	template<typename T>
	ParamT<T>::operator T() const {
		return toString();
	}

	template<typename T>
	ParamT<T> & ParamT<T>::operator=( const ParamT<T> & param ) {
		::ParamT<T, T>::operator=(param);
		return *this;
	}

	template<typename T>
	ParamT<T> & ParamT<T>::operator=( ParamT<T> && param ) {
		::ParamT<T, T>::operator=(Utility::toRValue(param));
		return *this;
	}

	template<typename T>
	bool ParamT<T>::writeXML( IO::SimpleFileStream * fileStreamP ) const {
		IO::SimpleFileStream & fileStream( *fileStreamP );
		_writeXML<IO::SimpleFileStream, char>( fileStream );
		return !( fileStreamP -> bad() );
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