#include "XMLDocument.h"


namespace XML {

	Document::Document( const UTF8String & str ) : 
		rootNode( NULL )
	{
		_parse( str );
	}


	Document::Document( const Document & document ) : 
		version( document.version ),
		encoding( document.encoding ),
		rootNode( new Node( *document.rootNode ) )
	{
	}


	Document::Document( Document && document ) : 
		version( Utility::toRValue( document.version ) ),
		encoding( Utility::toRValue( document.encoding ) ),
		rootNode( Utility::toRValue( document.rootNode ) )
	{
		document.rootNode = NULL;
	}


	Document::Document( const WString & fileName ) {
		_readXML( fileName );
	}


	Document::Document() :
		version(0.0),
		rootNode( new Node( "#document", Node::Type::Document ) )
	{

	}

	Document & Document::operator=( const Document & document ) {
		_unload();

		this -> version = document.version;
		this -> encoding = document.encoding;

		this -> rootNode = new Node( *( document.rootNode ) );
		
		return *this;
	}

	Document & Document::operator=( Document && document ) {
		_unload();

		this -> version = Utility::toRValue( document.version );
		this -> encoding = Utility::toRValue( document.encoding );
		this -> rootNode = Utility::toRValue( document.rootNode );
		document.rootNode = NULL;

		return *this;
	}

	Document::~Document() {
		_unload();
	}



	void Document::_parse( const UTF8String & str ) {

		int deep( 0 );
		Vector<Node * > nodeTree;
		nodeTree.reserve( 10 );


		static UTF8String rootName( "#document" );
		this -> rootNode = new Node( rootName, Node::Type::Document );

		Node * activeNode( this -> rootNode );
		nodeTree.push( activeNode );

		UCodePoint codePoint;
		for ( auto it( str.getBegin() ); str.iterate( &it, &codePoint );) {


			switch ( codePoint ) {
				case UCodePoint( '<' ):
					{

						

						if ( (*it) != char('?') ) {
							
							struct FunctorNodeName {
								bool operator()( const UCodePoint & c ) { return c != UCodePoint( ' ' ) && c != UCodePoint( '\t' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' ); }
							};
							static FunctorNodeName functorNodeName;


							// If we have a closing node
							if ( ( *it ) == char( '/' ) ) {
								it++; // Skip the '/'
								auto beginIt( it );
								while ( str.iterate( &it, &codePoint, functorNodeName ) );
								UTF8String nodeName( str.getSubStr( beginIt, it ) );
								
								if ( deep ) {
									deep--;
									activeNode = nodeTree.pop();
									if ( nodeName != activeNode -> getName() ) {
										error( String( "[XML ERROR] : Closing node do not match " ) << activeNode -> getName() << " != " << nodeName );
										//SYNTAX ERROR
									}
								} else {
									error(String("[XML ERROR] : Trying to close ") << nodeName << " without opened it." );
									//SYNTAX ERROR
								}
								


								while ( ( *it ) == char( ' ' ) || ( *it ) == char( '\t' ) || ( *it ) == char( '\n' ) ) ( it )++;

							} else {
								// We have an opening node or self closing
								auto beginIt( it );
								while ( str.iterate( &it, &codePoint, functorNodeName ) );
								UTF8String nodeName( str.getSubStr( beginIt, it ) );

								// We have a new node ! let's create it !
								activeNode = new Node( nodeName );

								while ( _parseParameter( str, &it, &codePoint, activeNode ) );
								
								// Push the new Node
								nodeTree.getLast() -> addChild( activeNode );
								

								if ( ( *it ) == char( '/' ) ) {
									// Self closing node
									it++;
									while ( ( *it ) == char( ' ' ) || ( *it ) == char( '\t' ) || ( *it ) == char( '\n' ) ) ( it )++;
								} else {
									nodeTree.push( activeNode );
									deep++;
								}
							}	
						} else {
							it++; // Skip the '?'

							
							// We have a special node
							static String xmlFlag( "xml" );
							static String encodingStr( "encoding" );
							static String versionStr( "version" );

							static auto xmlFlagBegin( xmlFlag.getBegin() );
							if ( str.cmp( &it, xmlFlag, &xmlFlagBegin, 3 ) ) {
								UTF8String paramName;
								UTF8String paramValue;

								while ( _parseParameterSpecial( str, &it, &codePoint, &paramName, &paramValue ) ) {
									if ( paramName == encodingStr ) {
										this -> encoding = paramValue;
									} else if ( paramName == versionStr ) {
										this -> version = paramValue.toFloat();
									}
								
								}
							}
							if ( ( *it ) == char( '?' ) ) {
								it++;
							} else {
								error( "[XML ERROR] : Opened a special node with <? but not closing it correctly." );
								//SYNTAX ERROR
							}
						}

						assert( ( *it ) == char( '>' ) );
						it++;
						if ( it == str.getEnd() )
							break;

						//Node has been created, maybe we have content inside the active node
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
								if ( ( *it ) == char( '<' ) || it == str.getEnd() )
									break;
								else 
									it++;
								
							}

							//while ( str.iterate( &it, &codePoint, functorContent ) );

							if ( endIt != beginIt ) {
								// We have content, so we gonna create a text node and add the content
								NodeText * nodeText( new NodeText( str.getSubStr( beginIt, endIt ) ) );

								UTF8String & strValue( *( const_cast< UTF8String * >( &( nodeText -> getValue() ) ) ) );
								

								nodeTree.getLast() -> addChild( nodeText );
							}
						}
						



						break;
					}
			}
		}
	}


	bool Document::_parseParameter( const UTF8String & str, RandomAccessIterator<char> * itp, UCodePoint * lastCodePoint, Node * node ) {
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
		while ( ( *it ) == char( ' ' ) || ( *it ) == char( '\t' ) || ( *it ) == char( '\n' ) ) ( it )++;

		// ? is a special char
		if ( ( *it ) == char( '?' ) || ( *it ) == char( '/' ) ) return false;
		auto iteratorBegin( it );
		while ( str.iterate( &it, &codePoint, functorNoEqual ) );


		if ( iteratorBegin != it ) {
			Param * param = new Param();
			UTF8String & name( const_cast< UTF8String & >( param -> getName() ) );
			UTF8String & value( const_cast< UTF8String & >( param -> getValue() ) );

			name = str.getSubStr( iteratorBegin, it );

			if ( codePoint == UCodePoint( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == char( '"' ) ) {
					( it )++; // Skip the quotes too
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoQuote ) );
					value = str.getSubStr( iteratorBegin, it );
					if (( *it ) == char( '"' )) ( it )++; // Skip the quotes again
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



	bool Document::_parseParameterSpecial( const UTF8String & str, RandomAccessIterator<char> * itp, UCodePoint * lastCodePoint, UTF8String * nameP, UTF8String * valueP ) {
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
		while ( ( *it ) == char( ' ' ) || ( *it ) == char( '\t' ) || ( *it ) == char( '\n' ) ) ( it )++;

		// ? is a special char
		if ( ( *it ) == char( '?' ) || ( *it ) == char( '/' ) ) return false;
		auto iteratorBegin( it );
		while ( str.iterate( &it, &codePoint, functorNoEqual ) );




		if ( iteratorBegin != it ) {
			UTF8String & name( *nameP );
			UTF8String & value( *valueP );

			name = str.getSubStr( iteratorBegin, it );

			if ( codePoint == UCodePoint( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == char( '"' ) ) {
					( it )++; // Skip the quotes too
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoQuote ) );
					value = str.getSubStr( iteratorBegin, it );
					if ( ( *it ) == char( '"' ) ) ( it )++; // Skip the quotes again
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



	Vector< Node * > Document::getElementsById( const UTF8String & id ) const {
		return this -> rootNode -> getElementsById( id );
	}


	Vector< Node * > Document::getElementsByName( const UTF8String & name ) const {
		return this -> rootNode -> getElementsByName( name );
	}


	Node * Document::getRoot() {
		return this -> rootNode;
	}


	float Document::getVersion() const {
		return this -> version;
	}


	void Document::setVersion( float version ) {
		this -> version = version;
	}


	const UTF8String & Document::getEncoding() const {
		return this -> encoding;
	}


	void Document::setEncoding( const UTF8String & encoding ) {
		this -> encoding = encoding;
	}

	bool Document::writeXML( std::fstream * fileStream ) const {
		fileStream -> put( char( '<' ) );
		fileStream -> put( char( '?' ) );
		fileStream -> put( char( 'x' ) );
		fileStream -> put( char( 'm' ) );
		fileStream -> put( char( 'l' ) );
		fileStream -> put( char( ' ' ) );

		fileStream -> put( char( 'v' ) );
		fileStream -> put( char( 'e' ) );
		fileStream -> put( char( 'r' ) );
		fileStream -> put( char( 's' ) );
		fileStream -> put( char( 'i' ) );
		fileStream -> put( char( 'o' ) );
		fileStream -> put( char( 'n' ) );
		fileStream -> put( char( '=' ) );
		fileStream -> put( char( '"' ) );
		String::toString<2,10>( this -> version ).writeReadable( fileStream );
		fileStream -> put( char( '"' ) );
		fileStream -> put( char( ' ' ) );
		fileStream -> put( char( 'e' ) );
		fileStream -> put( char( 'n' ) );
		fileStream -> put( char( 'c' ) );
		fileStream -> put( char( 'o' ) );
		fileStream -> put( char( 'd' ) );
		fileStream -> put( char( 'i' ) );
		fileStream -> put( char( 'n' ) );
		fileStream -> put( char( 'g' ) );
		fileStream -> put( char( '=' ) );
		fileStream -> put( char( '"' ) );
		this -> encoding.writeReadable( fileStream );
		fileStream -> put( char( '"' ) );
		fileStream -> put( char( '?' ) );
		fileStream -> put( char( '>' ) );


		for ( typename Vector< Node *>::Size i( 0 ); i < this -> rootNode -> getNbChildren(); i++ ) {
			fileStream -> put( char( '\n' ) );
			this -> rootNode -> getChild( i ).writeXML( fileStream );
		}

		return !( fileStream -> bad() );
	}


	bool Document::writeXML( const WString & fileName ) const {
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

	bool Document::readXML( const WString & fileName ) {
		_clear();

		return _readXML( fileName );
	}

	bool Document::read( std::fstream * fileStream ) {
		_unload();
		this -> rootNode = NULL;

		if ( !IO::read( fileStream, &this -> version ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream , &this -> encoding) ) {
			_clear();
			return false;
		}
		this -> rootNode = new Node( UTF8String( "#document" ), Node::Type::Document );
		if ( !IO::read( fileStream, this -> rootNode ) ) {
			_clear();
			return false;
		}
		
		
		return true;
	}


	bool Document::write( std::fstream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> version ) )
			return false;
		if ( !IO::write( fileStream, &this -> encoding ) ) 
			return false;
		if ( !IO::write( fileStream, this -> rootNode ) ) 
			return false;

		return true;
	}

	void Document::_clear() {
		_unload();
		this -> version = 0.0f;
		this -> encoding.clear();
		this -> rootNode = new Node( "#document", Node::Type::Document );
	}


	void Document::_unload() {
		delete this -> rootNode;
	}


	bool Document::_readXML( const WString & fileName ) {
		_unload();
		this -> rootNode = NULL;

		std::fstream fileStream( fileName.getData(), std::ios::in );
		if ( fileStream.is_open() ) {
			auto beginPos( fileStream.tellg() );
			fileStream.seekg( 0, fileStream.end );
			auto endPos( fileStream.tellg() );
			fileStream.seekg( 0, fileStream.beg );

			UTF8String buffer;
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

}

