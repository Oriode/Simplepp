#include "HTTPRequest.h"
namespace Network {

	template<typename T>
	const StringASCII HTTPRequestT<T>::methodStrTable[] = { StringASCII( "GET" ), StringASCII( "POST" ), StringASCII( "DELETE" ) };

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT() :
		method( Method::Unknown ) {
		initHostParam();
		initParams();

		this->contentType = HTTPQueryT<T>::ContentType::Text;
	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT( const UrlT<T>& url ) :
		url( url ) {
		initHostParam();
		initParams();

		if ( this->method == HTTPRequestT<T>::Method::POST ) {
			setContentType( HTTPQueryT<T>::ContentType::Params );
		}

	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT( typename UrlT<T>::Type type, const StringASCII& hostname ) :
		url( type, hostname ) {
		initHostParam();
		initParams();

		if ( this->method == HTTPRequestT<T>::Method::POST ) {
			setContentType( HTTPQueryT<T>::ContentType::Params );
		}

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
			ERROR_SPP( "HTTP request syntax error : no method." );
			return false;
		}

		StringASCII methodStr( methodStrBeginIt, Size( methodStrEndIt - methodStrBeginIt ) );
		typename HTTPRequestT<T>::Method method( HTTPRequestT<T>::getMethod( methodStr ) );

		if ( method == Method::Unknown ) {
			ERROR_SPP( "HTTP request syntax error : Unkown method." );
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

		this->method = method;
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
	inline void HTTPRequestT<T>::setMethod( typename HTTPRequestT<T>::Method method ) {
		this->method = method;
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint( const UrlT<T>& url ) {
		this->url = url;

		updateHostParamValue();
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint( const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector ) {
		this->url.setEndPoint( endPointStr );
		this->url.setParams( paramVector );
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint( typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector ) {
		this->url.setType( type );
		this->url.setHostname( hostname );
		this->url.setEndPoint( endPointStr );
		this->url.setParams( paramVector );

		updateHostParamValue();
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint( const StringASCII& endPointStr ) {
		this->url.setEndPoint( endPointStr );
		this->url.clearParams();
	}

	template<typename T>
	inline typename HTTPRequestT<T>::Method HTTPRequestT<T>::getMethod() const {
		return this->method;
	}

	template<typename T>
	inline const UrlT<T>& HTTPRequestT<T>::getEndPoint() const {
		return this->url;
	}

	template<typename T>
	inline const StringASCII& HTTPRequestT<T>::getMethodString( typename HTTPRequestT<T>::Method method ) {
		unsigned char methodIndex( static_cast< unsigned char >( method ) );
		if ( methodIndex < sizeof( HTTPRequestT<T>::methodStrTable ) ) {
			return HTTPRequestT<T>::methodStrTable[ methodIndex ];
		} else {
			return StringASCII::null;
		}
	}

	template<typename T>
	inline typename HTTPRequestT<T>::Method HTTPRequestT<T>::getMethod( const StringASCII& methodStr ) {
		constexpr Size enumSize( sizeof( HTTPRequestT<T>::methodStrTable ) );
		for ( Size i( 0 ); i < enumSize; i++ ) {
			if ( methodStr == HTTPRequestT<T>::methodStrTable[ i ] ) {
				return static_cast< typename HTTPRequestT<T>::Method >( i );
			}
		}
		return HTTPRequestT<T>::Method::Unknown;
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQueryTitle( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		str << HTTPRequestT<T>::getMethodString( this->method );
		str << StringASCII::ElemType( ' ' );
		if ( this->contentType == HTTPQueryT<T>::ContentType::Params ) {
			this->url.formatEndPointWOParams( &str );
		} else {
			this->url.formatEndPoint( &str );
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