namespace XML {

	template<typename S>
	ParamT<S>::ParamT( const S & name, const S & value ) : 
		::ParamT<S, S>(name, value)
	{

	}

	template<typename S>
	ParamT<S>::ParamT() {

	}

	template<typename S>
	ParamT<S>::ParamT( const ParamT<S> & param ) :
		::ParamT<S, S>(param)
	{

	}

	template<typename S>
	ParamT<S>::ParamT( ParamT<S> && param ) :
		::ParamT<S, S>(Utility::toRValue(param))
	{

	}

	template<typename S>
	ParamT<S>::operator S() const {
		return toString();
	}

	template<typename S>
	ParamT<S> & ParamT<S>::operator=( const ParamT<S> & param ) {
		::ParamT<S, S>::operator=(param);
		return *this;
	}

	template<typename S>
	ParamT<S> & ParamT<S>::operator=( ParamT<S> && param ) {
		::ParamT<S, S>::operator=(Utility::toRValue(param));
		return *this;
	}

	template<typename S>
	template<typename Stream>
	bool ParamT<S>::writeXML( Stream * fileStreamP ) const {
		Stream & stream( *fileStreamP );
		_writeXML<Stream, char>( stream );
		return !( fileStreamP -> bad() );
	}

	template<typename S>
	void ParamT<S>::_clear() {
		this -> name.clear();
		this -> value.clear();
	}

	template<typename S>
	template<typename C, typename Elem>
	void ParamT<S>::_writeXML( C & o ) const {
		o << this -> name;
		if ( this -> value.getSize() ) {
			o << Elem( '=' );
			o << Elem( '"' );
			o << this -> value;
			o << Elem( '"' );
		}
	}

	template<typename S>
	template<typename S2>
	S2 ParamT<S>::toString() const {
		S2 newString;
		newString.reserve( this -> name.getSize() + this -> value.getSize() + 4 );

		_writeXML<S2, S2::ElemType>( newString );
		return newString;
	}
}