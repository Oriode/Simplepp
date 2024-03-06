#include "HTTPRequest.h"
namespace Network {

	template<typename T>
	const StringASCII HTTPRequestT<T>::methodStrTable[] = { StringASCII( "GET" ), StringASCII( "POST" ), StringASCII( "DELETE" ) };

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT() :
		verb( Verb::Unknown ) {
		initHostParam();
		initParams();

	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT( typename HTTPRequestT<T>::Verb verb, const UrlT<T>& url ) :
		verb( verb ),
		url( url ) {
		initHostParam();
		updateHostParamValue();
		initParams();


	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT( typename HTTPRequestT<T>::Verb verb, typename UrlT<T>::Sheme type, const StringASCII& hostname ) :
		verb( verb ),
		url( type, hostname ) {
		initHostParam();
		updateHostParamValue();
		initParams();

	}

	template<typename T>
	template<typename EndFunc>
	inline HTTPRequestT<T>::HTTPRequestT( const StringASCII::ElemType** itP, const EndFunc& endFunc ) :
		hostParam( NULL ) {
		parseQuery( itP, endFunc );
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQuery( const StringASCII::ElemType** itP, const EndFunc& endFunc ) {
		if ( !parseQueryTitle( itP, endFunc ) ) {
			return false;
		}
		if ( !parseQueryHeader( itP, endFunc ) ) {
			return false;
		}
		if ( !parseQueryContent( itP, endFunc ) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQueryTitle( const StringASCII::ElemType** itP, const EndFunc& endFunc ) {
		struct FunctorNewLine {
			FunctorNewLine( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( '\r' ) || *it == StringASCII::ElemType( '\n' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorWord {
			FunctorWord( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( ' ' ) || *it == StringASCII::ElemType( '\r' ) || *it == StringASCII::ElemType( '\n' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it != StringASCII::ElemType( ' ' ) || *it == StringASCII::ElemType( '\r' ) || *it == StringASCII::ElemType( '\n' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};

		FunctorNewLine functorNewLine( endFunc );
		FunctorWord functorWord( endFunc );
		FunctorSpace functorSpace( endFunc );

		const StringASCII::ElemType*& it( *itP );

		// Skip spaces.
		for ( ; !functorSpace( it ); it++ );

		const StringASCII::ElemType* methodStrBeginIt( it );
		for ( ; !functorWord( it ); it++ );
		const StringASCII::ElemType* methodStrEndIt( it );

		if ( methodStrBeginIt == methodStrEndIt ) {
			ERROR_SPP( "HTTP request syntax error : no verb." );
			return false;
		}

		StringASCII methodStr( methodStrBeginIt, Size( methodStrEndIt - methodStrBeginIt ) );
		typename HTTPRequestT<T>::Verb verb( HTTPRequestT<T>::getVerb( methodStr ) );

		if ( verb == Verb::Unknown ) {
			ERROR_SPP( "HTTP request syntax error : Unkown verb." );
			return false;
		}

		// Skip spaces.
		for ( ; !functorSpace( it ); it++ );

		if ( !this->url.parse( &it, functorWord ) ) {
			return false;
		}

		// Skip spaces.
		for ( ; !functorSpace( it ); it++ );

		const StringASCII::ElemType* protocolStrBeginIt( it );
		for ( ; !functorWord( it ); it++ );
		const StringASCII::ElemType* protocolStrEndIt( it );

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			ERROR_SPP( "HTTP request syntax error : no protocol." );
			return false;
		}

		// Skip up to end line.
		for ( ; !functorNewLine( it ); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType( '\r' ) && !endFunc( it ) ) {
			it++;
			if ( *it == StringASCII::ElemType( '\n' ) && !endFunc( it ) ) {
				it++;
			}
		}

		StringASCII protocolStr( protocolStrBeginIt, Size( protocolStrEndIt - protocolStrBeginIt ) );

		this->verb = verb;
		this->protocolStr = protocolStr;

		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQueryContent( const StringASCII::ElemType** itP, const EndFunc& endFunc ) {
		if ( this->contentType == HTTPQueryT<T>::ContentType::Params ) {
			if ( !this->url.parseParams( itP, endFunc ) ) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline StringASCII HTTPRequestT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve( 10000 );

		formatQuery( &outputStr );
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQuery( StringASCII* outputStr ) const {
		formatQueryTitle( outputStr );

		if ( this->contentType == HTTPQueryT<T>::ContentType::Params ) {
			StringASCII paramStr;
			this->url.formatParams( &paramStr );
			const_cast< HTTPRequestT<T>* >( this )->setContent( paramStr );
		}

		HTTPQueryT<T>::formatQuery( outputStr );
	}

	template<typename T>
	inline void HTTPRequestT<T>::setVerb( typename HTTPRequestT<T>::Verb verb ) {
		this->verb = verb;
	}

	template<typename T>
	inline void HTTPRequestT<T>::setUrl( const UrlT<T>& url ) {
		this->url = url;

		updateHostParamValue();
	}

	template<typename T>
	inline void HTTPRequestT<T>::setPath( const StringASCII& pathStr ) {
		this->url.setPath( pathStr );
	}

	template<typename T>
	inline void HTTPRequestT<T>::setUrlParams( const Vector<HTTPParam>& paramVector ) {
		this->url.setParams( paramVector );
	}


	template<typename T>
	inline typename HTTPRequestT<T>::Verb HTTPRequestT<T>::getVerb() const {
		return this->verb;
	}

	template<typename T>
	inline const UrlT<T>& HTTPRequestT<T>::getUrl() const {
		return this->url;
	}

	template<typename T>
	inline const StringASCII& HTTPRequestT<T>::getVerbStr( typename HTTPRequestT<T>::Verb verb ) {
		unsigned char methodIndex( static_cast< unsigned char >( verb ) );
		if ( methodIndex < sizeof( HTTPRequestT<T>::methodStrTable ) ) {
			return HTTPRequestT<T>::methodStrTable[ methodIndex ];
		} else {
			return StringASCII::null;
		}
	}

	template<typename T>
	inline typename HTTPRequestT<T>::Verb HTTPRequestT<T>::getVerb( const StringASCII& verbStr ) {
		constexpr Size enumSize( sizeof( HTTPRequestT<T>::methodStrTable ) );
		for ( Size i( 0 ); i < enumSize; i++ ) {
			if ( verbStr == HTTPRequestT<T>::methodStrTable[ i ] ) {
				return static_cast< typename HTTPRequestT<T>::Verb >( i );
			}
		}
		return HTTPRequestT<T>::Verb::Unknown;
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQueryTitle( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		str << HTTPRequestT<T>::getVerbStr( this->verb );
		str << StringASCII::ElemType( ' ' );
		if ( this->contentType == HTTPQueryT<T>::ContentType::Params ) {
			this->url.formatPathWOParams( &str );
		} else {
			this->url.formatPathAndParams( &str );
		}
		str << StringASCII::ElemType( ' ' );
		str << this->protocolStr;
		str << StringASCII::ElemType( '\r' );
		str << StringASCII::ElemType( '\n' );
	}

	template<typename T>
	inline void HTTPRequestT<T>::updateHostParamValue() {
		if ( this->hostParam ) {
			this->hostParam->setValue( this->url.getHostname() );
		} else {
			this->hostParam = setHeaderParam( StringASCII( "Host" ), this->url.getHostname() );
		}
	}

	template<typename T>
	void HTTPRequestT<T>::initHostParam() {
		HTTPParam* hostParam( new HTTPParam( StringASCII( "Host" ) ) );
		addParam( hostParam );
		this->hostParam = hostParam;
	}

	template<typename T>
	inline void HTTPRequestT<T>::initParams() {
		setProtocol( StringASCII( "HTTP/1.1" ) );
		setHeaderParam( StringASCII( "Connection" ), StringASCII( "Keep-Alive" ) );
	}

}