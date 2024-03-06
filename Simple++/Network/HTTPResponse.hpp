namespace Network {

	template<typename T>
	inline HTTPResponseT<T>::HTTPResponseT() { }

	template<typename T>
	template<typename EndFunc>
	inline HTTPResponseT<T>::HTTPResponseT( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {
		parseQuery( itP, endFunc, verbose );
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQuery( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {
		if ( !parseQueryTitle( itP, endFunc, verbose ) ) {
			return false;
		}
		if ( !HTTPQueryT<T>::parseQuery( itP, endFunc, verbose ) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline StringASCII HTTPResponseT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve( 10000 );

		formatQuery( &outputStr );
	}

	template<typename T>
	inline void HTTPResponseT<T>::formatQuery( StringASCII* outputStr ) const {
		formatQueryTitle( outputStr );
		HTTPQueryT<T>::formatQuery( outputStr );
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusCode( Size statusCode ) {
		this->statusCode = statusCode;
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusMessage( const StringASCII& statusMessage ) {
		this->statusMessage = statusMessage;
	}

	template<typename T>
	inline const Size HTTPResponseT<T>::getStatusCode() const {
		return this->statusCode;
	}

	template<typename T>
	inline const StringASCII& HTTPResponseT<T>::getStatusMessage() const {
		return this->statusMessage;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQueryTitle( const StringASCII::ElemType** itP, const EndFunc& endFunc, int verbose ) {
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

		if ( verbose > 0 ) { Log::startStep( __func__, "Parsing title..." ); }

		FunctorNewLine functorNewLine( endFunc );
		FunctorWord functorWord( endFunc );
		FunctorSpace functorSpace( endFunc );

		const StringASCII::ElemType*& it( *itP );
		// Skip spaces.
		for ( ; !functorSpace( it ); it++ );

		const StringASCII::ElemType* protocolStrBeginIt( it );
		for ( ; !functorWord( it ); it++ );
		const StringASCII::ElemType* protocolStrEndIt( it );

		// Skip spaces.
		for ( ; !functorSpace( it ); it++ );

		Size statusCode( StringASCII::toULongLong( &it, 10, functorWord ) );

		// Skip spaces.
		for ( ; !functorSpace( it ); it++ );

		const StringASCII::ElemType* statusMessageBeginIt( it );
		for ( ; !functorNewLine( it ); it++ );
		const StringASCII::ElemType* statusMessageEndIt( it );

		// Skip up to end line.
		for ( ; !functorNewLine( it ); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType( '\r' ) && !endFunc( it ) ) {
			it++;
			if ( *it == StringASCII::ElemType( '\n' ) && !endFunc( it ) ) {
				it++;
			}
		}

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, "HTTP response syntax error : no protocol." ); }
			return false;
		}

		StringASCII protocolStr( protocolStrBeginIt, Size( protocolStrEndIt - protocolStrBeginIt ) );
		StringASCII statusMessage( statusMessageBeginIt, Size( statusMessageEndIt - statusMessageBeginIt ) );

		this->protocolStr = protocolStr;
		this->statusCode = statusCode;
		this->statusMessage = statusMessage;

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success. Code:% Message:%", this->statusCode, this->statusMessage ) ); }

		return true;
	}

	template<typename T>
	inline void HTTPResponseT<T>::formatQueryTitle( StringASCII* outputStr ) const {
		StringASCII& str( *outputStr );

		str << this->protocolStr;
		str << StringASCII::ElemType( ' ' );
		str << this->statusCode;
		str << StringASCII::ElemType( ' ' );
		str << this->statusMessage;
		str << StringASCII::ElemType( '\r' );
		str << StringASCII::ElemType( '\n' );
	}

}