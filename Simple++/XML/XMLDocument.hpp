namespace XML {

	template<typename T>
	DocumentT<T>::DocumentT( const T & str ) :
		rootNode( NULL ) {
		_parse( str );
	}

	template<typename T>
	DocumentT<T>::DocumentT( const DocumentT<T> & document ) :
		version( document.version ),
		encoding( document.encoding ),
		rootNode( new NodeT<T>( *document.rootNode ) ) {}

	template<typename T>
	DocumentT<T>::DocumentT( DocumentT<T> && document ) :
		version( Utility::toRValue( document.version ) ),
		encoding( Utility::toRValue( document.encoding ) ),
		rootNode( Utility::toRValue( document.rootNode ) ) {
		document.rootNode = NULL;
	}

	template<typename T>
	DocumentT<T>::DocumentT( const OS::Path & filePath ) {
		_readFileXML( filePath );
	}

	template<typename T>
	DocumentT<T>::DocumentT() :
		version( 0.0 ),
		rootNode( new NodeT<T>( "#document", NodeT<T>::Type::Document ) ) {

	}

	template<typename T>
	DocumentT<T> & DocumentT<T>::operator=( const DocumentT<T> & document ) {
		_unload();

		this -> version = document.version;
		this -> encoding = document.encoding;

		this -> rootNode = new NodeT<T>( *( document.rootNode ) );

		return *this;
	}

	template<typename T>
	DocumentT<T> & DocumentT<T>::operator=( DocumentT<T> && document ) {
		_unload();

		this -> version = Utility::toRValue( document.version );
		this -> encoding = Utility::toRValue( document.encoding );
		this -> rootNode = Utility::toRValue( document.rootNode );
		document.rootNode = NULL;

		return *this;
	}

	template<typename T>
	DocumentT<T>::~DocumentT() {
		_unload();
	}

	template<typename T>
	bool DocumentT<T>::readXML( const T & str ) {
		const typename T::ElemType * buffer( str.toCString() );
		return readXML<T::ElemType>( &buffer );
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool DocumentT<T>::_parseParameterSpecial( const C ** buffer, T * nameP, T * valueP, const EndFunc & endFunc ) {
		const C *& it( *buffer );

		struct FunctorValue {
			bool operator()( const C & c ) { return c != C( '"' ); }
		};
		struct FunctorSpace {
			bool operator()( const C & c ) { return c == C( '\n' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		struct FunctorName {
			bool operator()( const C & c ) { return c != C( '=' ) && c != C( '\t' ) && c != C( ' ' ) && c != C( '>' ) && c != C( '/' ); }
		};
		static FunctorName functorName;
		static FunctorSpace functorSpace;
		static FunctorValue functorValue;

		// Now lets skip all the blanks
		while ( functorSpace(*it) ) it++;

		// ? is a special char
		if ( ( *it ) == C( '?' ) || ( *it ) == C( '/' ) || endFunc(it) ) return false;
		auto iteratorBegin( it );
		while ( true ) {
			if ( endFunc( it ) ) {
				error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
				return false;
			}
			if ( !functorName( *it ) )
				break;
			it++;
		}

		if ( iteratorBegin != it ) {
			T & name( *nameP );
			T & value( *valueP );

			name = T( iteratorBegin, Size( it - iteratorBegin ) );

			if ( (*it) == C( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == C( '"' ) ) {
					( it )++; // Skip the quotes too

					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorValue( *it ) )
							break;
						it++;
					}
					value = T( iteratorBegin, Size( it - iteratorBegin ) );

					if ( ( *it ) == C( '"' ) ) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							error( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorName( *it ) )
							break;
						it++;
					}
					value = T( iteratorBegin, Size( it - iteratorBegin ) );
				}

			}
			return true;
		}
		return false;
	}


	template<typename T>
	Vector< NodeT<T> * > DocumentT<T>::getElementsById( const T & id ) const {
		return this -> rootNode -> getElementsById( id );
	}

	template<typename T>
	Vector< NodeT<T> * > DocumentT<T>::getElementsByName( const T & name ) const {
		return this -> rootNode -> getElementsByName( name );
	}

	template<typename T>
	NodeT<T> * DocumentT<T>::getRoot() {
		return this -> rootNode;
	}

	template<typename T>
	float DocumentT<T>::getVersion() const {
		return this -> version;
	}

	template<typename T>
	void DocumentT<T>::setVersion( float version ) {
		this -> version = version;
	}

	template<typename T>
	const StringASCII & DocumentT<T>::getEncoding() const {
		return this -> encoding;
	}

	template<typename T>
	void DocumentT<T>::setEncoding( const T & encoding ) {
		this -> encoding = encoding;
	}

	template<typename T>
	bool DocumentT<T>::writeXML( IO::SimpleFileStream * fileStreamP ) const {
		IO::SimpleFileStream & fileStream( *fileStreamP );
		_writeXML<IO::SimpleFileStream, char>( fileStream );
		return !( fileStreamP -> hasFailed() );
	}

	template<typename T>
	bool DocumentT<T>::writeFileXML( const OS::Path & filePath ) const {
		IO::FileStream fileStream( filePath, IO::OpenMode::Write );
		if ( fileStream.isOpen() ) {
			return writeXML(&fileStream);
		}
		return false;
	}

	template<typename T>
	bool DocumentT<T>::readFileXML( const OS::Path & filePath ) {
		_clear();

		return _readXML( filePath );
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool DocumentT<T>::readXML( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorSpace {
			bool operator()( const C & c ) { return c != C( '<' ) && c != C( '\n' ) && c != C( '\t' ) && c != C( ' ' ); }
		};

		static FunctorSpace functorSpace;

		if ( this -> rootNode != NULL ) {
			_clear();
		}

		const C *& it( *buffer );

		T rootName( "#document" );
		this -> rootNode = new NodeT<T>( rootName, NodeT<T>::Type::Document );

		while ( functorSpace( *it ) ) it++;

		if ( !NodeT<T>::_expectChar( &it, C( '<' ) ) ) return false;
		if ( !NodeT<T>::_expectChar( &it, C( '?' ) ) ) {
			// No special node. Directly parse the content.
			it--; // Roll back to the '<'.
			return this -> rootNode -> appendXML( &it, endFunc );
		}


		// We have a special node
		static C xmlFlag[] = { C( 'x' ), C( 'm' ), C( 'l' ) };
		static T encodingStr( "encoding" );
		static T versionStr( "version" );

		if ( DocumentT<T>::cmpStr( it, xmlFlag, 3 ) ) {
			it += 3;
			T paramName;
			T paramValue;

			while ( _parseParameterSpecial( &it, &paramName, &paramValue, endFunc ) ) {
				if ( paramName == encodingStr ) {
					this -> encoding = paramValue;
				} else if ( paramName == versionStr ) {
					this -> version = paramValue.toFloat();
				}
			}
		} else {
			error( TEXT( "[XML ERROR] : expecting \"<xml...\"." ) );
			return false;
		}

		if ( !NodeT<T>::_expectChar( &it, C( '?' ) ) ) return false;
		if ( !NodeT<T>::_expectChar( &it, C( '>' ) ) ) return false;


		return this -> rootNode -> appendXML( &it, endFunc );
	}

	template<typename T>
	template<typename C, typename EndFunc>
	bool DocumentT<T>::readXML( const C * buffer, const EndFunc & endFunc ) {
		return readXML( &buffer, endFunc );
	}

	template<typename T>
	template<typename C>
	bool DocumentT<T>::cmpStr( const C * b1, const C * b2, int size ) {
		for ( int i( 0 ); i < size; i++ ) {
			if ( b1[i] != b2[i] ) return false;
		}
		return true;
	}

	template<typename T>
	bool DocumentT<T>::read( IO::SimpleFileStream * fileStream ) {
		_unload();
		this -> rootNode = NULL;

		if ( !IO::read( fileStream, &this -> version ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> encoding ) ) {
			_clear();
			return false;
		}
		this -> rootNode = new NodeT<T>( T( "#document" ), NodeT<T>::Type::Document );
		if ( !IO::read( fileStream, this -> rootNode ) ) {
			_clear();
			return false;
		}


		return true;
	}

	template<typename T>
	bool DocumentT<T>::write( IO::SimpleFileStream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> version ) )
			return false;
		if ( !IO::write( fileStream, &this -> encoding ) )
			return false;
		if ( !IO::write( fileStream, this -> rootNode ) )
			return false;

		return true;
	}

	template<typename T>
	void DocumentT<T>::_clear() {
		_unload();
		this -> version = 0.0f;
		this -> encoding.clear();
		this -> rootNode = new NodeT<T>( "#document", NodeT<T>::Type::Document );
	}

	template<typename T>
	void DocumentT<T>::_unload() {
		delete this -> rootNode;
	}

	template<typename T>
	bool DocumentT<T>::_readFileXML( const OS::Path & filePath ) {
		_unload();
		this -> rootNode = NULL;

		T strOut;
		if (IO::readToString(filePath, &strOut) != size_t(-1)) {
			return readXML(strOut);
		}
		else {
			_clear();
			return false;
		}
	}

	template<typename T>
	template<typename C>
	C DocumentT<T>::toString() const {
		C newString;
		newString.reserve( 2048 );

		_writeXML<C, C::ElemType>( newString );
		return newString;
	}

	template<typename T>
	T DocumentT<T>::toStringDebug() const {
		T newString;
		newString.reserve( 1024 );

		newString << T::ElemType( '<' );
		newString << T::ElemType( 'x' );
		newString << T::ElemType( 'm' );
		newString << T::ElemType( 'l' );
		newString << T::ElemType( ' ' );
		newString << T::ElemType( 'v' );
		newString << T::ElemType( 'e' );
		newString << T::ElemType( 'r' );
		newString << T::ElemType( 's' );
		newString << T::ElemType( 'i' );
		newString << T::ElemType( 'o' );
		newString << T::ElemType( 'n' );
		newString << T::ElemType( '=' );
		newString << T::ElemType( '"' );
		newString << this -> version;
		newString << T::ElemType( '"' );
		newString << T::ElemType( ' ' );
		newString << T::ElemType( 'e' );
		newString << T::ElemType( 'n' );
		newString << T::ElemType( 'c' );
		newString << T::ElemType( 'o' );
		newString << T::ElemType( 'd' );
		newString << T::ElemType( 'i' );
		newString << T::ElemType( 'n' );
		newString << T::ElemType( 'g' );
		newString << T::ElemType( '=' );
		newString << T::ElemType( '"' );
		newString << this->encoding;
		newString << T::ElemType( '"' );

		newString << T::ElemType( '>' );
		newString << T::ElemType( '\n' );

		if ( this -> rootNode ) {
			newString << this->rootNode->toStringDebug( 1 );
			newString << T::ElemType( '\n' );
		}

		newString << T::ElemType( '<' );
		newString << T::ElemType( '/' );
		newString << T::ElemType( 'x' );
		newString << T::ElemType( 'm' );
		newString << T::ElemType( 'l' );
		newString << T::ElemType( '>' );

		return newString;
	}

	template<typename T>
	template<typename C, typename Elem>
	void DocumentT<T>::_writeXML( C & o ) const {
		o << Elem( '<' );
		o << Elem( '?' );
		o << Elem( 'x' );
		o << Elem( 'm' );
		o << Elem( 'l' );
		o << Elem( ' ' );

		o << Elem( 'v' );
		o << Elem( 'e' );
		o << Elem( 'r' );
		o << Elem( 's' );
		o << Elem( 'i' );
		o << Elem( 'o' );
		o << Elem( 'n' );
		o << Elem( '=' );
		o << Elem( '"' );
		o << BasicString<Elem>::toString( this -> version, 2 );
		o << Elem( '"' );
		o << Elem( ' ' );
		o << Elem( 'e' );
		o << Elem( 'n' );
		o << Elem( 'c' );
		o << Elem( 'o' );
		o << Elem( 'd' );
		o << Elem( 'i' );
		o << Elem( 'n' );
		o << Elem( 'g' );
		o << Elem( '=' );
		o << Elem( '"' );
		o << this -> encoding;
		o << Elem( '"' );
		o << Elem( '?' );
		o << Elem( '>' );

		for ( Size i( 0 ); i < this -> rootNode -> getNbChildren(); i++ ) {
			o << Elem( '\n' ) ;
			this -> rootNode -> getChild( i ) -> _writeXML<C, Elem>( o );
		}
	}

}

