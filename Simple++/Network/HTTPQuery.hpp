namespace Network {

	template<typename T>
	inline HTTPQueryT<T>::HTTPQueryT() :
		bHeaderNeedFormat( false ),
		contentType( ContentType::None ) { }

	template<typename T>
	inline HTTPQueryT<T>::~HTTPQueryT() {

	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryContent( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		if ( this->contentType != ContentType::None ) {
			str << this->contentStr;
		}
	}

	template<typename T>
	inline HTTPParam* HTTPQueryT<T>::setHeaderParam( const StringASCII& paramName, const StringASCII& paramValue ) {
		this->bHeaderNeedFormat = true;
		return ParamContainerT<StringASCII, StringASCII>::setParam( paramName, paramValue );
	}

	template<typename T>
	inline const HTTPParam* HTTPQueryT<T>::getHeaderParam( const StringASCII& paramName ) const {
		return ParamContainerT<StringASCII, StringASCII>::getParam( paramName );
	}

	template<typename T>
	inline HTTPParam* HTTPQueryT<T>::getHeaderParam( const StringASCII& paramName ) {
		return ParamContainerT<StringASCII, StringASCII>::getParam( paramName );
	}

	template<typename T>
	inline void HTTPQueryT<T>::setProtocol( const StringASCII& protocol ) {
		this->protocolStr = protocol;
	}

	template<typename T>
	inline void HTTPQueryT<T>::setContent( const StringASCII& content ) {
		if ( content.getSize() > Size( 0 ) || content.getSize() != this->contentStr.getSize() ) {
			// Header need to be recomputed as the Content-Size has changed.
			this->bHeaderNeedFormat = true;
		}

		this->contentStr = content;
	}

	template<typename T>
	inline void HTTPQueryT<T>::clearContent() {
		if ( this->contentStr.getSize() ) {
			this->contentStr.clear();

			// Header need to be recomputed as the Content-Size has changed.
			this->bHeaderNeedFormat = true;
		}
	}

	template<typename T>
	inline typename HTTPQueryT<T>::ContentType HTTPQueryT<T>::getContentType() const {
		return this->contentType;
	}

	template<typename T>
	inline void HTTPQueryT<T>::setContentType( typename HTTPQueryT<T>::ContentType contentType ) {
		this->bHeaderNeedFormat = true;
		this->contentType = contentType;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getProtocol() const {
		return this->protocolStr;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getContent() const {
		return this->contentStr;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getContentTypeString( typename ContentType contentType ) {
		return HTTPQueryT<T>::contentTypeStrTable[ static_cast< unsigned char >( contentType ) ];
	}

	template<typename T>
	inline typename HTTPQueryT<T>::ContentType HTTPQueryT<T>::getContentType( const StringASCII& contentTypeStr ) {

		static const Map<StringASCII, HTTPQueryT<T>::ContentType> contentTypeMap( HTTPQueryT<T>::contentTypeStrTable );

		const HTTPQueryT<T>::ContentType * v( contentTypeMap[ contentTypeStr ] );

		if ( !v ) {
			return HTTPQueryT<T>::ContentType::None;
		}

		return *v;
	}

	template<typename T>
	const StringASCII HTTPQueryT<T>::contentTypeStrTable[] = {
			StringASCII( "none" ),
			StringASCII( "text/plain" ),
			StringASCII( "text/html" ),
			StringASCII( "application/x-www-form-urlencoded" ),
			StringASCII( "multipart/form-data; boundary=boundary" ),
			StringASCII( "application/json" ),
			StringASCII( "application/xml" ),
			StringASCII( "image/png" )
	};

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQuery( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {
		if ( !parseQueryHeader( itP, endFunc, verbose ) ) {
			return false;
		}
		if ( !parseQueryContent( itP, endFunc, verbose ) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQuery( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		const_cast< HTTPQueryT<T>* >( this )->formatQueryHeader();

		str << this->headerStr;
		formatQueryContent( outputStr );
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatHeaderParam( StringASCII* outputStr, const ParamT<StringASCII, StringASCII>& param ) const {
		StringASCII& str( *outputStr );

		str << param.getName();
		str << StringASCII::ElemType( ':' );
		str << StringASCII::ElemType( ' ' );
		str << param.getValue();
		str << StringASCII::ElemType( '\r' );
		str << StringASCII::ElemType( '\n' );
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryHeader() {
		if ( this->bHeaderNeedFormat ) {

			this->headerStr.clear();

			for ( typename Vector<HTTPParam*>::Iterator it( this->paramVector.getBegin() ); it != this->paramVector.getEnd(); this->paramVector.iterate( &it ) ) {
				const HTTPParam* param( this->paramVector.getValueIt( it ) );

				formatHeaderParam( &this->headerStr, *param );
			}

			if ( this->contentType != HTTPQueryT<T>::ContentType::None && this->contentStr.getSize() ) {
				static const StringASCII contentTypeName( "Content-Type" );
				static const StringASCII contentLengthParamName( "Content-Length" );

				formatHeaderParam( &this->headerStr, ParamT<StringASCII, StringASCII>( contentTypeName, HTTPQueryT<T>::getContentTypeString( this->contentType ) ) );
				formatHeaderParam( &this->headerStr, ParamT<StringASCII, StringASCII>( contentLengthParamName, StringASCII::toString( this->contentStr.getSize() ) ) );


			}

			this->headerStr << StringASCII::ElemType( '\r' );
			this->headerStr << StringASCII::ElemType( '\n' );

			this->bHeaderNeedFormat = false;
		}
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQueryHeader( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {
		struct FunctorNewLine {
			FunctorNewLine( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( '\r' ) || *it == StringASCII::ElemType( '\n' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorParamName( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it == StringASCII::ElemType( ':' ) || *it == StringASCII::ElemType( ' ' ) || *it == StringASCII::ElemType( '\r' ) || *it == StringASCII::ElemType( '\n' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace( const EndFunc& endFunc ) :
				endFunc( endFunc ) { }
			bool operator()( const typename StringASCII::ElemType* it ) const { return *it != StringASCII::ElemType( ' ' ) || *it == StringASCII::ElemType( '\r' ) || *it == StringASCII::ElemType( '\n' ) || endFunc( it ); }

			const EndFunc& endFunc;
		};

		FunctorNewLine functorNewLine( endFunc );
		FunctorParamName functorParamName( endFunc );
		FunctorSpace functorSpace( endFunc );

		if ( verbose > 0 ) { Log::startStep( __func__, "Parsing header..." ); }

		clearParams();
		this->contentType = HTTPQueryT<T>::ContentType::None;

		const StringASCII::ElemType*& it( *itP );
		while ( true ) {
			// Skip spaces.
			for ( ; !functorSpace( it ); it++ );

			const StringASCII::ElemType* paramNameBeginIt( it );
			for ( ; !functorParamName( it ); it++ );
			const StringASCII::ElemType* paramNameEndIt( it );

			if ( *it == StringASCII::ElemType( ':' ) ) {
				it++;
			}

			// Skip spaces.
			for ( ; !functorSpace( it ); it++ );

			const StringASCII::ElemType* paramValueBeginIt( it );
			for ( ; !functorNewLine( it ); it++ );
			const StringASCII::ElemType* paramValueEndIt( it );

			if ( paramNameBeginIt == paramNameEndIt || paramValueBeginIt == paramValueEndIt ) {
				if ( verbose > 0 ) { Log::endStep( __func__, "HTTP header syntax error." ); }
				return false;
			}

			StringASCII newParamName( paramNameBeginIt, Size( paramNameEndIt - paramNameBeginIt ) );
			StringASCII newParamValue( paramValueBeginIt, Size( paramValueEndIt - paramValueBeginIt ) );

			HTTPParam* newParam( new HTTPParam( newParamName, newParamValue ) );

			if ( verbose > 1 ) { Log::displayLog( __func__, StringASCII::format( "%: %", newParam->getName(), newParam->getValue() ) ); }

			const StringASCII contentTypeName( "Content-Type" );
			if ( newParam->getName() == contentTypeName ) {
				this->contentType = getContentType( newParam->getValue() );
				delete newParam;
			} else {
				addParam( newParam );
			}

			// End condition.
			if ( *it == StringASCII::ElemType( '\r' ) && !endFunc( it ) ) {
				it++;
				if ( *it == StringASCII::ElemType( '\n' ) && !endFunc( it ) ) {
					it++;
				}
				if ( *it == StringASCII::ElemType( '\r' ) && !endFunc( it ) ) {
					it++;
					if ( *it == StringASCII::ElemType( '\n' ) && !endFunc( it ) ) {
						it++;
					}
					break;
				}
				continue;
			}

			break;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, "Success." ); }

		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQueryContent( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( __func__, "Parsing content..." ); }

		const StringASCII::ElemType*& it( *itP );
		for ( ; ( *it == StringASCII::ElemType( '\n' ) || *it == StringASCII::ElemType( '\r' ) ) && !endFunc( it ); it++ );

		const StringASCII::ElemType* contentStrBeginIt( it );
		for ( ; !endFunc( it ); it++ );
		this->contentStr = StringASCII( contentStrBeginIt, Size( it - contentStrBeginIt ) );

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success parsed % bytes.", this->contentStr.getSize() ) ); }

		return true;
	}
}