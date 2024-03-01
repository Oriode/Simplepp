#include "Url.h"
namespace Network {

	template<typename T>
	const StringASCII UrlT<T>::typeStrTable[] = { StringASCII( "http" ), StringASCII( "https" ) };

	template<typename T>
	inline UrlT<T>::UrlT() { }

	template<typename T>
	inline UrlT<T>::UrlT( const StringASCII& url ) {
		parse( url );
	}

	template<typename T>
	inline UrlT<T>::UrlT( typename UrlT<T>::Sheme sheme, const StringASCII& hostname ) :
		sheme( sheme ),
		hostname( hostname ) { }

	template<typename T>
	inline UrlT<T>::UrlT( typename UrlT<T>::Sheme sheme, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector ) :
		sheme( sheme ),
		hostname( hostname ),
		uriStr( endPointStr ) {
		setParams( paramVector );
	}

	template<typename T>
	inline UrlT<T>::UrlT( const UrlT<T>& url ) :
		ParamContainerT<StringASCII, StringASCII>( url ),
		sheme( url.sheme ),
		hostname( url.hostname ),
		uriStr( url.uriStr ) { }

	template<typename T>
	inline UrlT<T>::UrlT( const UrlT<T>&& url ) :
		ParamContainerT<StringASCII, StringASCII>( Utility::toRValue( url ) ),
		sheme( Utility::toRValue( url.sheme ) ),
		hostname( Utility::toRValue( url.hostname ) ),
		uriStr( Utility::toRValue( url.uriStr ) ) { }

	template<typename T>
	inline UrlT<T>::~UrlT() {

	}

	template<typename T>
	inline UrlT<T>& UrlT<T>::operator=( const UrlT<T>& url ) {
		ParamContainerT<StringASCII, StringASCII>::operator=( url );
		this->sheme = url.sheme;
		this->hostname = url.hostname;
		this->uriStr = url.uriStr;

		return *this;
	}

	template<typename T>
	inline UrlT<T>& UrlT<T>::operator=( const UrlT<T>&& url ) {
		ParamContainerT<StringASCII, StringASCII>::operator=( Utility::toRValue( url ) );
		this->sheme = Utility::toRValue( url.sheme );
		this->hostname = Utility::toRValue( url.hostname );
		this->uriStr = Utility::toRValue( url.uriStr );

		return *this;
	}

	template<typename T>
	inline bool UrlT<T>::parse( const StringASCII& str ) {
		StringASCII::IsEndIterator endFunc( str.getEnd() );
		StringASCII::Iterator it( str.getBegin() );

		return parse( const_cast< const StringASCII::ElemType** >( &it ), endFunc );
	}

	template<typename T>
	inline bool UrlT<T>::parseParams( const StringASCII& str ) {
		StringASCII::IsEndIterator endFunc( str.getEnd() );
		String::Iterator it( str.getBegin() );

		return parseParams( &it, endFunc );
	}

	template<typename T>
	inline StringASCII UrlT<T>::format() const {
		StringASCII outputStr;
		outputStr.reserve( 1024 );

		format( &outputStr );

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::format( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		formatWOParams( &str );

		if ( this->paramVector.getSize() > Size( 0 ) ) {
			str << StringASCII::ElemType( '?' );
			formatParams( &str );
		}
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatWOParams() const {
		StringASCII outputStr;
		outputStr.reserve( 512 );

		formatWOParams( &outputStr );

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::formatWOParams( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		str << getShemeStr( this->sheme );
		str << StringASCII::ElemType( ':' );
		str << StringASCII::ElemType( '/' );
		str << StringASCII::ElemType( '/' );
		str << this->hostname;
		str << this->uriStr;
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatEndPointWOParams() const {
		StringASCII outputStr;
		outputStr.reserve( 512 );

		formatEndPointWOParams( &outputStr );

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::formatEndPointWOParams( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		str << this->uriStr;
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatEndPoint() const {
		StringASCII outputStr;
		outputStr.reserve( 512 );

		formatEndPoint( &outputStr );

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::formatEndPoint( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		formatEndPointWOParams( &str );

		if ( this->paramVector.getSize() > Size( 0 ) ) {
			str << StringASCII::ElemType( '?' );
			formatParams( &str );
		}
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatParams() const {
		return formatParams( this->paramVector );
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatParams( const Vector<HTTPParam*>& paramVector ) {
		StringASCII outputStr;
		outputStr.reserve( 512 );

		formatParams( &outputStr, paramVector );

		return outputStr;
	}

	template<typename T>
	inline StringASCII UrlT<T>::formatParams( const Vector<HTTPParam>& paramVector ) {
		StringASCII outputStr;
		outputStr.reserve( 512 );

		formatParams( &outputStr, paramVector );

		return outputStr;
	}

	template<typename T>
	inline void UrlT<T>::formatParams( StringASCII* outputStr ) const {
		formatParams( outputStr, this->paramVector );
	}

	template<typename T>
	inline void UrlT<T>::formatParams( StringASCII* outputStr, const Vector<HTTPParam*>& paramVector ) {
		StringASCII& str( *outputStr );

		for ( typename Vector<HTTPParam*>::Iterator it( paramVector.getBegin() ); it < paramVector.getEnd(); paramVector.iterate( &it ) ) {
			const HTTPParam* param( paramVector.getValueIt( it ) );

			if ( it != paramVector.getBegin() ) {
				str << StringASCII::ElemType( '&' );
			}

			str << param->getName();
			if ( param->getValue().getSize() > Size( 0 ) ) {
				str << StringASCII::ElemType( '=' );
				str << param->getValue();
			}
		}
	}

	template<typename T>
	inline void UrlT<T>::formatParams( StringASCII* outputStr, const Vector<HTTPParam>& paramVector ) {
		StringASCII& str( *outputStr );

		for ( typename Vector<HTTPParam>::Iterator it( paramVector.getBegin() ); it < paramVector.getEnd(); paramVector.iterate( &it ) ) {
			const HTTPParam& param( paramVector.getValueIt( it ) );

			if ( it != paramVector.getBegin() ) {
				str << StringASCII::ElemType( '&' );
			}

			str << param.getName();
			if ( param.getValue().getSize() > Size( 0 ) ) {
				str << StringASCII::ElemType( '=' );
				str << param.getValue();
			}
		}
	}

	template<typename T>
	inline void UrlT<T>::setType( const typename UrlT<T>::Sheme sheme ) {
		this->sheme = sheme;
	}

	template<typename T>
	inline void UrlT<T>::setHostname( const StringASCII& hostname ) {
		this->hostname = hostname;
	}

	template<typename T>
	inline void UrlT<T>::setUri( const StringASCII& endPoint ) {
		this->uriStr = endPoint;
	}

	template<typename T>
	inline typename UrlT<T>::Sheme UrlT<T>::getSheme() const {
		return this->sheme;
	}

	template<typename T>
	inline const StringASCII& UrlT<T>::getHostname() const {
		return this->hostname;
	}

	template<typename T>
	inline const StringASCII& UrlT<T>::getUri() const {
		return this->uriStr;
	}

	template<typename T>
	inline const StringASCII& UrlT<T>::getShemeStr( typename UrlT<T>::Sheme sheme ) {
		unsigned char typeIndex( static_cast< unsigned char >( sheme ) );
		if ( typeIndex < sizeof( UrlT<T>::typeStrTable ) ) {
			return UrlT<T>::typeStrTable[ typeIndex ];
		} else {
			return StringASCII::null;
		}
	}

	template<typename T>
	inline typename UrlT<T>::Sheme UrlT<T>::getSheme( const StringASCII& typeStr ) {
		constexpr Size enumSize( sizeof( UrlT<T>::typeStrTable ) );
		for ( Size i( 0 ); i < enumSize; i++ ) {
			if ( typeStr == UrlT<T>::typeStrTable[ i ] ) {
				return static_cast< typename UrlT<T>::Sheme >( i );
			}
		}
		return UrlT<T>::Sheme::Unknown;
	}

	template<typename T>
	template<typename Stream>
	bool UrlT<T>::read( Stream* stream ) {
		if ( !ParamContainerT<StringASCII, StringASCII>::read( stream ) ) {
			return false;
		}
		unsigned char typeChar;
		if ( !IO::read( stream, &typeChar ) ) {
			return false;
		}
		this->sheme = static_cast< UrlT<T>::Sheme >( typeChar );
		if ( !IO::read( stream, &this->hostname ) ) {
			return false;
		}
		if ( !IO::read( stream, &this->uriStr ) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename Stream>
	bool UrlT<T>::write( Stream* stream ) const {
		if ( !ParamContainerT<StringASCII, StringASCII>::write( stream ) ) {
			return false;
		}
		unsigned char typeChar( static_cast< unsigned char >( this->sheme ) );
		if ( !IO::write( stream, &typeChar ) ) {
			return false;
		}
		if ( !IO::write( stream, &this->hostname ) ) {
			return false;
		}
		if ( !IO::write( stream, &this->uriStr ) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline UrlT<T>::UrlT( const StringASCII::ElemType** itP, const EndFunc& endFunc ) {
		parse( itP, endFunc );
	}

	template<typename T>
	template<typename EndFunc>
	inline bool UrlT<T>::parse( const StringASCII::ElemType** itP, const EndFunc& endFunc ) {
		struct FunctorProtocol {
			FunctorProtocol( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( ':' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorHostname {
			FunctorHostname( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( '/' ) || *it == StringASCII::ElemType( '?' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorEndPoint {
			FunctorEndPoint( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( '?' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};

		FunctorProtocol functorProtocol( endFunc );
		FunctorHostname functorHostname( endFunc );
		FunctorEndPoint functorEndPoint( endFunc );

		const StringASCII::ElemType*& it( *itP );

		const StringASCII::ElemType* protocolStrBeginIt( it );
		for ( ; !functorProtocol( it ); it++ );
		const StringASCII::ElemType* protocolStrEndIt( it );

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			ERROR_SPP( "EndPoint syntax error : no protocol." );
			return false;
		}

		typename UrlT<T>::Sheme sheme;
		if ( !endFunc( it ) ) {
			StringASCII protocolStr( protocolStrBeginIt, Size( protocolStrEndIt - protocolStrBeginIt ) );
			sheme = getSheme( protocolStr.toLower() );

			if ( sheme == UrlT<T>::Sheme::Unknown ) {
				ERROR_SPP( "EndPoint syntax error : unknown protocol." );
				return false;
			}

			// Skip :
			it++;

			// Skip /
			for ( ; *it == StringASCII::ElemType( '/' ) && !endFunc( it ); it++ );
		} else {
			sheme = UrlT<T>::Sheme::Unknown;
			// No protocol founded, start over without searching any.
			it = *itP;
		}

		const StringASCII::ElemType* hostnameStrBeginIt( it );
		for ( ; !functorHostname( it ); it++ );
		const StringASCII::ElemType* hostnameStrEndIt( it );

		const StringASCII::ElemType* endPointStrBeginIt( it );
		for ( ; !functorEndPoint( it ); it++ );
		const StringASCII::ElemType* endPointStrEndIt( it );

		if ( endPointStrBeginIt == endPointStrEndIt ) {
			ERROR_SPP( "EndPoint syntax error : no end point." );
			return false;
		}

		StringASCII hostnameStr( hostnameStrBeginIt, Size( hostnameStrEndIt - hostnameStrBeginIt ) );
		StringASCII endPointStr( endPointStrBeginIt, Size( endPointStrEndIt - endPointStrBeginIt ) );

		this->sheme = sheme;
		this->hostname = hostnameStr;
		this->uriStr = endPointStr;
		this->paramVector.clear();
		this->paramMap.clear();

		if ( endFunc( it ) ) {
			return true;
		}

		// Skip ?
		it++;

		// Parse the params
		if ( !parseParams( &it, endFunc ) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool UrlT<T>::parseParams( const StringASCII::ElemType** itP, const EndFunc& endFunc ) {
		struct FunctorParamName {
			FunctorParamName( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( '=' ) || *it == StringASCII::ElemType( '&' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorParamValue {
			FunctorParamValue( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( '&' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};

		FunctorParamName functorParamName( endFunc );
		FunctorParamValue functorParamValue( endFunc );

		const StringASCII::ElemType*& it( *itP );

		while ( true ) {

			if ( endFunc( it ) ) {
				break;
			}

			const StringASCII::ElemType* paramNameBeginIt( it );
			for ( ; !functorParamName( it ); it++ );
			const StringASCII::ElemType* paramNameEndIt( it );

			if ( paramNameBeginIt == paramNameEndIt ) {
				ERROR_SPP( "EndPoint syntax error : param name missing." );
				return false;
			}

			StringASCII paramNameStr( paramNameBeginIt, Size( paramNameEndIt - paramNameBeginIt ) );

			if ( functorParamValue( it ) ) {

				addParam( new HTTPParam( paramNameStr ) );

				if ( endFunc( it ) ) {
					break;
				}

				if ( functorParamValue( it ) ) {
					// Skip &
					it++;
					continue;
				}
			}

			// Skip =
			it++;

			const StringASCII::ElemType* paramValueBeginIt( it );
			for ( ; !functorParamValue( it ); it++ );
			const StringASCII::ElemType* paramValueEndIt( it );

			StringASCII paramValueStr( paramValueBeginIt, Size( paramValueEndIt - paramValueBeginIt ) );

			addParam( new HTTPParam( paramNameStr, paramValueStr ) );
		}

		return true;
	}

}