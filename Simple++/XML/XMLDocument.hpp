namespace XML {

	template<typename S>
	DocumentT<S>::DocumentT( const S & str ) :
		rootNode( NULL ) {
		_parse( str );
	}

	template<typename S>
	DocumentT<S>::DocumentT( const DocumentT<S> & document ) :
		version( document.version ),
		encoding( document.encoding ),
		rootNode( new NodeT<S>( *document.rootNode ) ) {}

	template<typename S>
	DocumentT<S>::DocumentT( DocumentT<S> && document ) :
		version( Utility::toRValue( document.version ) ),
		encoding( Utility::toRValue( document.encoding ) ),
		rootNode( Utility::toRValue( document.rootNode ) ) {
		document.rootNode = NULL;
	}

	template<typename S>
	DocumentT<S>::DocumentT( const OS::Path & filePath ) {
		_readFileXML( filePath );
	}

	template<typename S>
	DocumentT<S>::DocumentT() :
		version( 0.0 ),
		rootNode( new NodeT<S>( "#document", NodeT<S>::Type::Document ) ) {

	}

	template<typename S>
	DocumentT<S> & DocumentT<S>::operator=( const DocumentT<S> & document ) {
		_unload();

		this -> version = document.version;
		this -> encoding = document.encoding;

		this -> rootNode = new NodeT<S>( *( document.rootNode ) );

		return *this;
	}

	template<typename S>
	DocumentT<S> & DocumentT<S>::operator=( DocumentT<S> && document ) {
		_unload();

		this -> version = Utility::toRValue( document.version );
		this -> encoding = Utility::toRValue( document.encoding );
		this -> rootNode = Utility::toRValue( document.rootNode );
		document.rootNode = NULL;

		return *this;
	}

	template<typename S>
	DocumentT<S>::~DocumentT() {
		_unload();
	}

	template<typename S>
	bool DocumentT<S>::readXML( const S & str ) {
		const typename S::ElemType * buffer( str.toCString() );
		return readXML<S::ElemType>( &buffer );
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool DocumentT<S>::_parseParameterSpecial( const C ** buffer, S * nameP, S * valueP, const EndFunc & endFunc ) {
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
				ERROR( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
				return false;
			}
			if ( !functorName( *it ) )
				break;
			it++;
		}

		if ( iteratorBegin != it ) {
			S & name( *nameP );
			S & value( *valueP );

			name = S( iteratorBegin, Size( it - iteratorBegin ) );

			if ( (*it) == C( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == C( '"' ) ) {
					( it )++; // Skip the quotes too

					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							ERROR( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorValue( *it ) )
							break;
						it++;
					}
					value = S( iteratorBegin, Size( it - iteratorBegin ) );

					if ( ( *it ) == C( '"' ) ) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( true ) {
						if ( endFunc( it ) ) {
							ERROR( TEXT( "[XML ERROR] : Unexpected buffer end." ) );
							return false;
						}
						if ( !functorName( *it ) )
							break;
						it++;
					}
					value = S( iteratorBegin, Size( it - iteratorBegin ) );
				}

			}
			return true;
		}
		return false;
	}


	template<typename S>
	Vector< NodeT<S> * > DocumentT<S>::getElementsById( const S & id ) const {
		return this -> rootNode -> getElementsById( id );
	}

	template<typename S>
	Vector< NodeT<S> * > DocumentT<S>::getElementsByName( const S & name ) const {
		return this -> rootNode -> getElementsByName( name );
	}

	template<typename S>
	NodeT<S> * DocumentT<S>::getRoot() {
		return this -> rootNode;
	}

	template<typename S>
	float DocumentT<S>::getVersion() const {
		return this -> version;
	}

	template<typename S>
	void DocumentT<S>::setVersion( float version ) {
		this -> version = version;
	}

	template<typename S>
	const StringASCII & DocumentT<S>::getEncoding() const {
		return this -> encoding;
	}

	template<typename S>
	void DocumentT<S>::setEncoding( const S & encoding ) {
		this -> encoding = encoding;
	}

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::writeXML( Stream * fileStreamP ) const {
		Stream & stream( *fileStreamP );
		_writeXML<Stream, char>( stream );
		return !( fileStreamP -> hasFailed() );
	}

	template<typename S>
	bool DocumentT<S>::writeFileXML( const OS::Path & filePath ) const {
		IO::FileStream stream( filePath, IO::OpenMode::Write );
		if ( stream.isOpen() ) {
			return writeXML(&stream);
		}
		return false;
	}

	template<typename S>
	bool DocumentT<S>::readFileXML( const OS::Path & filePath ) {
		_clear();

		return _readXML( filePath );
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool DocumentT<S>::readXML( const C ** buffer, const EndFunc & endFunc ) {
		struct FunctorSpace {
			bool operator()( const C & c ) { return c != C( '<' ) && c != C( '\n' ) && c != C( '\t' ) && c != C( ' ' ); }
		};

		static FunctorSpace functorSpace;

		if ( this -> rootNode != NULL ) {
			_clear();
		}

		const C *& it( *buffer );

		S rootName( "#document" );
		this -> rootNode = new NodeT<S>( rootName, NodeT<S>::Type::Document );

		while ( functorSpace( *it ) ) it++;

		if ( !NodeT<S>::_expectChar( &it, C( '<' ) ) ) return false;
		if ( !NodeT<S>::_expectChar( &it, C( '?' ) ) ) {
			// No special node. Directly parse the content.
			it--; // Roll back to the '<'.
			return this -> rootNode -> appendXML( &it, endFunc );
		}


		// We have a special node
		static C xmlFlag[] = { C( 'x' ), C( 'm' ), C( 'l' ) };
		static S encodingStr( "encoding" );
		static S versionStr( "version" );

		if ( DocumentT<S>::cmpStr( it, xmlFlag, 3 ) ) {
			it += 3;
			S paramName;
			S paramValue;

			while ( _parseParameterSpecial( &it, &paramName, &paramValue, endFunc ) ) {
				if ( paramName == encodingStr ) {
					this -> encoding = paramValue;
				} else if ( paramName == versionStr ) {
					this -> version = paramValue.toFloat();
				}
			}
		} else {
			ERROR( TEXT( "[XML ERROR] : expecting \"<xml...\"." ) );
			return false;
		}

		if ( !NodeT<S>::_expectChar( &it, C( '?' ) ) ) return false;
		if ( !NodeT<S>::_expectChar( &it, C( '>' ) ) ) return false;


		return this -> rootNode -> appendXML( &it, endFunc );
	}

	template<typename S>
	template<typename C, typename EndFunc>
	bool DocumentT<S>::readXML( const C * buffer, const EndFunc & endFunc ) {
		return readXML( &buffer, endFunc );
	}

	template<typename S>
	template<typename C>
	bool DocumentT<S>::cmpStr( const C * b1, const C * b2, int size ) {
		for ( int i( 0 ); i < size; i++ ) {
			if ( b1[i] != b2[i] ) return false;
		}
		return true;
	}

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::read( Stream * stream ) {
		_unload();
		this -> rootNode = NULL;

		if ( !IO::read( stream, &this -> version ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &this -> encoding ) ) {
			_clear();
			return false;
		}
		this -> rootNode = new NodeT<S>( S( "#document" ), NodeT<S>::Type::Document );
		if ( !IO::read( stream, this -> rootNode ) ) {
			_clear();
			return false;
		}


		return true;
	}

	template<typename S>
	template<typename Stream>
	bool DocumentT<S>::write( Stream * stream ) const {
		if ( !IO::write( stream, &this -> version ) )
			return false;
		if ( !IO::write( stream, &this -> encoding ) )
			return false;
		if ( !IO::write( stream, this -> rootNode ) )
			return false;

		return true;
	}

	template<typename S>
	void DocumentT<S>::_clear() {
		_unload();
		this -> version = 0.0f;
		this -> encoding.clear();
		this -> rootNode = new NodeT<S>( "#document", NodeT<S>::Type::Document );
	}

	template<typename S>
	void DocumentT<S>::_unload() {
		delete this -> rootNode;
	}

	template<typename S>
	bool DocumentT<S>::_readFileXML( const OS::Path & filePath ) {
		_unload();
		this -> rootNode = NULL;

		S strOut;
		if (IO::readToString(filePath, &strOut) != size_t(-1)) {
			return readXML(strOut);
		}
		else {
			_clear();
			return false;
		}
	}

	template<typename S>
	template<typename S2>
	S2 DocumentT<S>::toString() const {
		S2 newString;
		newString.reserve( 2048 );

		_writeXML<S2, S2::ElemType>( newString );
		return newString;
	}

	template<typename S>
	S DocumentT<S>::toStringDebug() const {
		S newString;
		newString.reserve( 1024 );

		newString << S::ElemType( '<' );
		newString << S::ElemType( 'x' );
		newString << S::ElemType( 'm' );
		newString << S::ElemType( 'l' );
		newString << S::ElemType( ' ' );
		newString << S::ElemType( 'v' );
		newString << S::ElemType( 'e' );
		newString << S::ElemType( 'r' );
		newString << S::ElemType( 's' );
		newString << S::ElemType( 'i' );
		newString << S::ElemType( 'o' );
		newString << S::ElemType( 'n' );
		newString << S::ElemType( '=' );
		newString << S::ElemType( '"' );
		newString << this -> version;
		newString << S::ElemType( '"' );
		newString << S::ElemType( ' ' );
		newString << S::ElemType( 'e' );
		newString << S::ElemType( 'n' );
		newString << S::ElemType( 'c' );
		newString << S::ElemType( 'o' );
		newString << S::ElemType( 'd' );
		newString << S::ElemType( 'i' );
		newString << S::ElemType( 'n' );
		newString << S::ElemType( 'g' );
		newString << S::ElemType( '=' );
		newString << S::ElemType( '"' );
		newString << this->encoding;
		newString << S::ElemType( '"' );

		newString << S::ElemType( '>' );
		newString << S::ElemType( '\n' );

		if ( this -> rootNode ) {
			newString << this->rootNode->toStringDebug( 1 );
			newString << S::ElemType( '\n' );
		}

		newString << S::ElemType( '<' );
		newString << S::ElemType( '/' );
		newString << S::ElemType( 'x' );
		newString << S::ElemType( 'm' );
		newString << S::ElemType( 'l' );
		newString << S::ElemType( '>' );

		return newString;
	}

	template<typename S>
	template<typename C, typename Elem>
	void DocumentT<S>::_writeXML( C & o ) const {
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

