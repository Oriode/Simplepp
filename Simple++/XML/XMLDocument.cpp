#include "XMLDocument.h"


namespace XML {

	Document::Document( const UTF8String & str ) {
		_parse( str );
	}


	Document::~Document() {
		_unload();
	}



	void Document::_parse( const UTF8String & str ) {

		int deep( 0 );
		Node * activeNode( NULL );
		Vector<Node * > nodeTree;
		nodeTree.reserve( 10 );

		UCodePoint codePoint;
		for ( auto it( str.getBegin() ); str.iterate( &it, &codePoint );) {


			switch ( codePoint ) {
				case UCodePoint( '<' ):
					{

						

						if ( (*it) != char('?') ) {
							
							struct FunctorNodeName {
								bool operator()( const UCodePoint & c ) { return c != UCodePoint( ' ' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' ); }
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
										log( String( "[XML ERROR] : Closing node do not match " ) << activeNode -> getName() << " != " << nodeName );
										//SYNTAX ERROR
									}
								} else {
									log(String("[XML ERROR] : Trying to close ") << nodeName << " without opened it." );
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

								UTF8String paramValue;
								Param * param = new Param();
								while ( _parseParameter( str, &it, &codePoint, const_cast< UTF8String * >( &param -> getName() ), const_cast< UTF8String * >( &param -> getValue() ) ) ) {
									activeNode -> addParam( param );
								}

								if ( deep ) {
									// We already are in an another node
									nodeTree.getLast() -> addChild( activeNode );
								} else {
									// We still are in root
									this -> nodes.push( activeNode );
								}

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

								while ( _parseParameter( str, &it, &codePoint, &paramName, &paramValue ) ) {
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
								log( "[XML ERROR] : Opened a special node with <? but not closing it correctly." );
								//SYNTAX ERROR
							}
						}
						assert( ( *it ) == char( '>' ) );
						it++;


						//Node has been created, maybe we have content inside the active node
						if ( deep ) {
							struct FunctorContent {
								bool operator()( const UCodePoint & c ) { return c != UCodePoint( '<' ); }
							};
							static FunctorContent functorContent;
							auto beginIt( it );
							while ( str.iterate( &it, &codePoint, functorContent ) );
							UTF8String nodeContent( str.getSubStr( beginIt, it ) );
							nodeTree.getLast() -> setContent( nodeContent );
						}



						break;
					}


			}

		}


	}











	

	bool Document::_parseParameter( const UTF8String & str, RandomAccessIterator<char> * itp, UCodePoint * lastCodePoint, UTF8String * name, UTF8String * value ) {
		RandomAccessIterator<char> & it( *itp );
		UCodePoint & codePoint( *lastCodePoint );

		struct FunctorNoQuote {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( '"' );
			}
		};
		struct FunctorNoSpace {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( ' ' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' );
			}
		};
		struct FunctorNoEqual {
			bool operator()( const UCodePoint & c ) {
				return c != UCodePoint( '=' ) && c != UCodePoint( ' ' ) && c != UCodePoint( '>' ) && c != UCodePoint( '/' );
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
			( *name ) = str.getSubStr( iteratorBegin, it );

			if ( codePoint == UCodePoint( '=' ) ) {
				( it )++; // Just to skip the equal sign

				if ( ( *it ) == char( '"' ) ) {
					( it )++; // Skip the quotes too
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoQuote ) );
					( *value ) = str.getSubStr( iteratorBegin, it );
					if (( *it ) == char( '"' )) ( it )++; // Skip the quotes again
				} else {
					iteratorBegin = it;
					while ( str.iterate( &it, &codePoint, functorNoSpace ) );
					( *value ) = str.getSubStr( iteratorBegin, it );
				}
			}
			return true;
		}
		return false;
	}



	bool Document::read( std::fstream * fileStream ) {
		_unload();
		this -> nodes.clear();



		if ( !IO::read( fileStream, &this -> version ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream , &this -> encoding) ) {
			_clear();
			return false;
		}
		Vector<Node *>::Size nbNodes;
		if ( !IO::read( fileStream, &nbNodes ) ) {
			_clear();
			return false;
		}
		for ( Vector<Node *>::Size i( 0 ); i < nbNodes; i++ ) {
			Node * newNode = new Node();
			if ( !IO::read( fileStream, &newNode ) ) {
				_clear();
				delete newNode;
				return false;
			}
			this -> nodes.push(newNode);
		}
		return true;
	}

	void Document::_clear() {
		_unload();
		this -> version = 0.0f;
		this -> encoding.clear();
		this -> nodes.clear();
	}


	void Document::_unload() {
		// Delete one by one all the nodes
		for ( auto it( this -> nodes.getBegin() ); it != this -> nodes.getEnd(); this -> nodes.iterate( &it ) ) {
			delete this -> nodes.getValueIt( it );
		}
	}

}

