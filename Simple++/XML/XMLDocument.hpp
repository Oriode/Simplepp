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
	DocumentT<T>::DocumentT( const WString & fileName ) {
		_readXML( fileName );
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
	void DocumentT<T>::_parse( const T & str ) {

		int deep( 0 );
		Vector<NodeT<T> * > nodeTree;
		nodeTree.reserve( 10 );


		static T rootName( "#document" );
		this -> rootNode = new NodeT<T>( rootName, NodeT<T>::Type::Document );

		NodeT<T> * activeNode( this -> rootNode );
		nodeTree.push( activeNode );

		UCodePoint codePoint;
		for ( auto it( str.getBegin() ); str.iterate( &it, &codePoint );) {


			switch ( codePoint ) {
				case UCodePoint( '<' ):
				{



					if ( ( *it ) != T::ElemType( '?' ) ) {

						struct FunctorNodeName {
							bool operator()( const UCodePoint & c ) { return c != UCodePoint( ' ' ) && c != UCodePoint( '\t' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' ); }
						};
						static FunctorNodeName functorNodeName;


						// If we have a closing node
						if ( ( *it ) == T::ElemType( '/' ) ) {
							it++; // Skip the '/'
							auto beginIt( it );
							while ( str.iterate( &it, &codePoint, functorNodeName ) );
							T nodeName( str.getSubStr( beginIt, it ) );

							if ( deep ) {
								deep--;
								activeNode = nodeTree.pop();
								if ( nodeName != activeNode -> getName() ) {
									error( String( TEXT( "[XML ERROR] : Closing node do not match " ) ) << activeNode -> getName() << TEXT( " != " ) << nodeName );
									//SYNTAX ERROR
								}
							} else {
								error( String( TEXT( "[XML ERROR] : Trying to close " ) ) << nodeName << TEXT( " without opened it." ) );
								//SYNTAX ERROR
							}



							while ( ( *it ) == T::ElemType( ' ' ) || ( *it ) == T::ElemType( '\t' ) || ( *it ) == T::ElemType( '\n' ) ) ( it )++;

						} else {
							// We have an opening node or self closing
							auto beginIt( it );
							while ( str.iterate( &it, &codePoint, functorNodeName ) );
							T nodeName( str.getSubStr( beginIt, it ) );

							// We have a new node ! let's create it !
							activeNode = new NodeT<T>( nodeName );

							while ( _parseParameter( str, &it, &codePoint, activeNode ) );

							// Push the new NodeT<T>
							nodeTree.getLast() -> addChild( activeNode );


							if ( ( *it ) == T::ElemType( '/' ) ) {
								// Self closing node
								it++;
								while ( ( *it ) == T::ElemType( ' ' ) || ( *it ) == T::ElemType( '\t' ) || ( *it ) == T::ElemType( '\n' ) ) ( it )++;
							} else {
								nodeTree.push( activeNode );
								deep++;
							}
						}
					} else {
						it++; // Skip the '?'


						// We have a special node
						static StringASCII xmlFlag( "xml" );
						static StringASCII encodingStr( "encoding" );
						static StringASCII versionStr( "version" );

						static auto xmlFlagBegin( xmlFlag.getBegin() );
						if ( str.cmp( &it, xmlFlag, &xmlFlagBegin, 3 ) ) {
							T paramName;
							T paramValue;

							while ( _parseParameterSpecial( str, &it, &codePoint, &paramName, &paramValue ) ) {
								if ( paramName == encodingStr ) {
									this -> encoding = paramValue;
								} else if ( paramName == versionStr ) {
									this -> version = paramValue.toFloat();
								}

							}
						}
						if ( ( *it ) == T::ElemType( '?' ) ) {
							it++;
						} else {
							error( TEXT( "[XML ERROR] : Opened a special node with <? but not closing it correctly." ) );
							//SYNTAX ERROR
						}
					}

					assert( ( *it ) == T::ElemType( '>' ) );
					it++;
					if ( it == str.getEnd() )
						break;

					//NodeT<T> has been created, maybe we have content inside the active node
					{
						struct FunctorContent {
							bool operator()( const UCodePoint & c ) { return c != UCodePoint( '<' ); }
						};
						struct FunctorNoSpace {
							bool operator()( const UCodePoint & c ) { return c == UCodePoint( '\n' ) || c == UCodePoint( '\t' ) || c == UCodePoint( ' ' ); }
						};
						struct FunctorSpace {
							bool operator()( const UCodePoint & c ) { return c != UCodePoint( '<' ) && c != UCodePoint( '\n' ) && c != UCodePoint( '\t' ) && c != UCodePoint( ' ' ); }
						};
						static FunctorContent functorContent;
						static FunctorNoSpace functorNoSpace;
						static FunctorSpace functorSpace;

						while ( str.iterate( &it, &codePoint, functorNoSpace ) );
						auto beginIt( it );
						auto endIt( it );
						while ( true ) {
							while ( str.iterate( &it, &codePoint, functorSpace ) )
								endIt = it;
							if ( ( *it ) == T::ElemType( '<' ) || it == str.getEnd() )
								break;
							else
								it++;

						}

						//while ( str.iterate( &it, &codePoint, functorContent ) );

						if ( endIt != beginIt ) {
							// We have content, so we gonna create a text node and add the content
							NodeTextT<T> * nodeText( new NodeTextT<T>( str.getSubStr( beginIt, endIt ) ) );

							T & strValue( *( const_cast< T * >( &( nodeText -> getValue() ) ) ) );


							nodeTree.getLast() -> addChild( nodeText );
						}
					}




					break;
				}
			}
		}
	}

	template<typename T>
	bool DocumentT<T>::_parseParameter( const T & str, RandomAccessIterator<char> * itp, UCodePoint * lastCodePoint, NodeT<T> * node ) {
		RandomAccessIterator<char> & it( *itp );
		UCodePoint & codePoint( *lastCodePoint );

		struct FunctorNoQuote {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( '"' );
			}
		};
		struct FunctorNoSpace {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( ' ' ) && c != UCodePoint( '\t' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' );
			}
		};
		struct FunctorNoEqual {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( '=' ) && c != UCodePoint( '\t' ) && c != UCodePoint( ' ' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' );
			}
		};
		static FunctorNoEqual functorNoEqual;
		static FunctorNoSpace functorNoSpace;
		static FunctorNoQuote functorNoQuote;

		//Now lets skip all the blanks
		while ( ( *it ) == T::ElemType( ' ' ) || ( *it ) == T::ElemType( '\t' ) || ( *it ) == T::ElemType( '\n' ) ) ( it )++;

		// ? is a special char
		if ( ( *it ) == T::ElemType( '?' ) || ( *it ) == T::ElemType( '/' ) ) return false;
		auto iteratorBegin( it );
		while ( str.iterate( &it, &codePoint, functorNoEqual ) );


		if ( iteratorBegin != it ) {
			ParamT<T> * param = new ParamT<T>();
			T & name( const_cast< T & >( param -> getName() ) );
			T & value( const_cast< T & >( param -> getValue() ) );

			name = str.getSubStr( iteratorBegin, it );

			if ( codePoint == UCodePoint( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == T::ElemType( '"' ) ) {
					( it )++; // Skip the quotes too
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoQuote ) );
					value = str.getSubStr( iteratorBegin, it );
					if ( ( *it ) == T::ElemType( '"' ) ) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoSpace ) );
					value = str.getSubStr( iteratorBegin, it );
				}
			}

			node -> addParam( param );
			return true;
		}
		return false;
	}


	template<typename T>
	bool DocumentT<T>::_parseParameterSpecial( const T & str, RandomAccessIterator<char> * itp, UCodePoint * lastCodePoint, T * nameP, T * valueP ) {
		RandomAccessIterator<char> & it( *itp );
		UCodePoint & codePoint( *lastCodePoint );

		struct FunctorNoQuote {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( '"' );
			}
		};
		struct FunctorNoSpace {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( ' ' ) && c != UCodePoint( '\t' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' );
			}
		};
		struct FunctorNoEqual {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( '=' ) && c != UCodePoint( '\t' ) && c != UCodePoint( ' ' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' );
			}
		};
		static FunctorNoEqual functorNoEqual;
		static FunctorNoSpace functorNoSpace;
		static FunctorNoQuote functorNoQuote;

		//Now lets skip all the blanks
		while ( ( *it ) == T::ElemType( ' ' ) || ( *it ) == T::ElemType( '\t' ) || ( *it ) == T::ElemType( '\n' ) ) ( it )++;

		// ? is a special char
		if ( ( *it ) == T::ElemType( '?' ) || ( *it ) == T::ElemType( '/' ) ) return false;
		auto iteratorBegin( it );
		while ( str.iterate( &it, &codePoint, functorNoEqual ) );




		if ( iteratorBegin != it ) {
			T & name( *nameP );
			T & value( *valueP );

			name = str.getSubStr( iteratorBegin, it );

			if ( codePoint == UCodePoint( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == T::ElemType( '"' ) ) {
					( it )++; // Skip the quotes too
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoQuote ) );
					value = str.getSubStr( iteratorBegin, it );
					if ( ( *it ) == T::ElemType( '"' ) ) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoSpace ) );
					value = str.getSubStr( iteratorBegin, it );
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
	bool DocumentT<T>::writeXML( std::fstream * fileStreamP ) const {
		std::fstream & fileStream( *fileStreamP );
		_writeXML<std::fstream, char>( fileStream );
		return !( fileStreamP -> bad() );
	}

	template<typename T>
	bool DocumentT<T>::writeXML( const WString & fileName ) const {
		std::fstream fileStream( fileName.getData(), std::ios::out );
		if ( fileStream.is_open() ) {

			if ( !writeXML( &fileStream ) ) {
				fileStream.close();
				return false;
			} else {
				fileStream.close();
				return true;
			}
		}
		return false;

	}

	template<typename T>
	bool DocumentT<T>::readXML( const WString & fileName ) {
		_clear();

		return _readXML( fileName );
	}

	template<typename T>
	bool DocumentT<T>::read( std::fstream * fileStream ) {
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
	bool DocumentT<T>::write( std::fstream * fileStream ) const {
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
	bool DocumentT<T>::_readXML( const WString & fileName ) {
		_unload();
		this -> rootNode = NULL;

		std::fstream fileStream( fileName.getData(), std::ios::in );
		if ( fileStream.is_open() ) {
			auto beginPos( fileStream.tellg() );
			fileStream.seekg( 0, fileStream.end );
			auto endPos( fileStream.tellg() );
			fileStream.seekg( 0, fileStream.beg );

			T buffer;
			if ( !buffer.read( &fileStream, endPos - beginPos ) ) {
				_clear();
				return false;
			}

			fileStream.close();

			_parse( buffer );

			return true;
		} else {
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

		for ( typename Vector< NodeT<T> *>::Size i( 0 ); i < this -> rootNode -> getNbChildren(); i++ ) {
			o << Elem( '\n' ) ;
			this -> rootNode -> getChild( i ) -> _writeXML<C, Elem>( o );
		}
	}

}

