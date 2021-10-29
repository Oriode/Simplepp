
template<typename T>
void( *SimpleLogT<T>::mErrorHandlerFn )(
	const T *,
	MessageSeverity,
	MessageColor,
	unsigned char,
	const TCHAR *,
	unsigned int ) = &SimpleLogT<T>::errorHandler;

template<typename T>
unsigned char SimpleLogT<T>::indent = 0;


template<typename T>
template<typename C>
void SimpleLogT<T>::getTimeStr( C * strBuffer, size_t bufferSize ) {
	char * tmpBuffer = new char[ bufferSize ];
	getTimeStr( tmpBuffer, bufferSize );
	convertMessage<C, char>( strBuffer, tmpBuffer, bufferSize );
	delete[] tmpBuffer;
}

template<typename T>
void SimpleLogT<T>::getTimeStr( char * strBuffer, size_t bufferSize ) {
	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	struct tm timeinfo;
	localtime_s( &timeinfo, &now );
	std::strftime( strBuffer, bufferSize, "%H:%M:%S", &timeinfo );
}

template<typename T>
void SimpleLogT<T>::getTimeStr( wchar_t * strBuffer, size_t bufferSize ) {
	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	struct tm timeinfo;
	localtime_s( &timeinfo, &now );
	std::wcsftime( strBuffer, bufferSize, L"%H:%M:%S", &timeinfo );
}

template<typename T>
void SimpleLogT<T>::errorHandler( const T * message, typename SimpleLogT<T>::MessageSeverity severity, typename SimpleLogT<T>::MessageColor color, unsigned char indent, const TCHAR * fileName, unsigned int lineNumber ) {
	switch ( severity ) {
		case typename SimpleLogT<T>::MessageSeverity::Error:
	#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
	#else
		return;
	#endif
		break;
		case typename SimpleLogT<T>::MessageSeverity::Warning:
	#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
	#else
		return;
	#endif
		break;
		case typename SimpleLogT<T>::MessageSeverity::Info:
	#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
	#else
		return;
	#endif
		break;
	}

	if ( message == NULL ) {
		printChar( '\n' );
		return;
	}

	setConsoleColor( color );

	T timeBuffer[ 50 ];
	getTimeStr<T>( timeBuffer, sizeof( timeBuffer ) );

	T prefixBuffer[ 2048 ];

#if defined LOG_DISPLAY_FILEPATH
	// If we have a fileName.
	if ( fileName != NULL ) {
		T fileNameBuffer[ FILENAME_MAX_SIZE ];

		convertFileName<T, TCHAR>( fileNameBuffer, fileName, 50 );
		//fileNameBuffer[ 10 ] = T( '\0' );


		parseMessage( prefixBuffer, 2048, timeBuffer, fileNameBuffer, lineNumber );
	} else {
		parseMessage( prefixBuffer, 2048, timeBuffer );
	}
#else
	parseMessage( prefixBuffer, 2048, timeBuffer );
#endif

	printMessage( prefixBuffer );

	for ( unsigned char i( 0 ); i < indent; i++ ) {
		printChar( '\t' );
	}

	printMessage( message );
	printChar( '\n' );

	// setConsoleColor();
}

template<typename T>
template<typename C>
void SimpleLogT<T>::parseMessage( C * buffer, int bufferSize, C * timeBuffer, const C * fileName, unsigned int lineNumber ) {
	// Not Implemented.
}

template<typename T>
void SimpleLogT<T>::parseMessage( char * buffer, int bufferSize, char * timeBuffer, const char * fileName, unsigned int lineNumber) {
#if defined LOG_DISPLAY_FILEPATH
	snprintf( buffer, bufferSize, "[%8s][%20s@%5i] : ", timeBuffer, fileName, lineNumber );
#else
	snprintf( buffer, bufferSize, "[%8s] : ", timeBuffer );
#endif
}

template<typename T>
void SimpleLogT<T>::parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer, const wchar_t * fileName, unsigned int lineNumber ) {
#if defined LOG_DISPLAY_FILEPATH
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%8s][%20s@%5i] : ", timeBuffer, fileName, lineNumber );
#else
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%8s] : ", timeBuffer );
#endif
}

template<typename T>
template<typename C>
void SimpleLogT<T>::parseMessage( C * buffer, int bufferSize, C * timeBuffer ) {
	// Not Implemented.
}

template<typename T>
void SimpleLogT<T>::parseMessage( char * buffer, int bufferSize, char * timeBuffer ) {
#if defined LOG_DISPLAY_FILEPATH
	snprintf( buffer, bufferSize, "[%8s][                          ] : ", timeBuffer );
#else
	snprintf( buffer, bufferSize, "[%8s] : ", timeBuffer );
#endif
}

template<typename T>
void SimpleLogT<T>::parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer ) {
#if defined LOG_DISPLAY_FILEPATH
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%8s][                          ] : ", timeBuffer );
#else
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%8s] : ", timeBuffer );
#endif
}


template<typename T>
void SimpleLogT<T>::callErrorHandler( const T * message, typename SimpleLogT<T>::MessageSeverity severity, typename SimpleLogT<T>::MessageColor color, const TCHAR * fileName, unsigned int lineNumber ) {
	mErrorHandlerFn( message, severity, color, SimpleLogT<T>::indent, fileName, lineNumber );
}

template<typename T>
void SimpleLogT<T>::setConsoleColor( typename SimpleLogT<T>::MessageColor color /*= typename SimpleLogT<T>::MessageColor::White*/ ) {
#if defined WIN32
#if defined ENABLE_WIN32
	static HANDLE consoleHandle( GetStdHandle( STD_OUTPUT_HANDLE ) );
	SetConsoleTextAttribute( consoleHandle, ( WORD ) color );
#endif
#else
	std::stringstream stream;
	stream << std::hex << color;
	system( std::string( TEXT( "Color " ) + stream.str() ).c_str() );
#endif
}

template<typename T>
SimpleLogT<T>::SimpleLogT() {}

template<typename T>
SimpleLogT<T>::~SimpleLogT() {}



#if defined WIN32 && defined ENABLE_WIN32
template<typename T>
void SimpleLogT<T>::displayWindowsDebug( const T * message, const TCHAR * fileName, unsigned int lineNumber ) {
	if ( GetLastError() ) {
		T messageBuffer[ 2048 ];
		getWindowsLastError( messageBuffer, sizeof( messageBuffer ) );
		SimpleLogT<T>::callErrorHandler( messageBuffer, typename SimpleLogT<T>::MessageSeverity::Error, typename SimpleLogT<T>::MessageColor::Red, fileName, lineNumber );
	}
}

template<typename T>
size_t SimpleLogT<T>::getWindowsLastError( T * messageBuffer, size_t bufferSize ) {
	LPTSTR lpMsgBuf;
	DWORD strlen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		( LPTSTR ) &lpMsgBuf,
		0, NULL );

	size_t sizeToCopy( ( strlen > bufferSize ) ? bufferSize : strlen );
	convertMessage<T, wchar_t>( messageBuffer, lpMsgBuf, sizeToCopy );
	LocalFree( lpMsgBuf );

	return sizeToCopy;
}
#endif

template<typename T>
void SimpleLogT<T>::setErrorHandler( void( *errorHandlerFn ) ( const T *, typename SimpleLogT<T>::MessageSeverity, typename SimpleLogT<T>::MessageColor color, unsigned char indent, const TCHAR *, unsigned int ) ) {
	SimpleLogT<T>::mErrorHandlerFn = errorHandlerFn;
}

template<typename T>
template<typename O, typename I>
void SimpleLogT<T>::convertMessage( O * outputBuffer, const I * inputBuffer, size_t bufferSize ) {
	size_t bufferSizeMinusOne( bufferSize - size_t( 1 ) );
	O * ito( outputBuffer );
	const I * iti( inputBuffer );
	for ( size_t i( 0 ) ; i < bufferSizeMinusOne && *iti != I( '\0' ) ; iti++, ito++, i++ ) {
		O castedChar( static_cast< O >( *iti ) );
		*ito = castedChar;
	}
	*ito = O( '\0' );
}

template<typename T>
template<typename O, typename I>
void SimpleLogT<T>::convertFileName( O * outputBuffer, const I * inputBuffer, size_t bufferSize ) {
	const I * iti( inputBuffer );
	for ( size_t i( 0 ) ; i < bufferSize && *iti != I( '\0' ); i++, iti++ );
	for ( ; iti >= inputBuffer && ( *iti != I( '\\' ) && *iti != I( '/' ) ); iti-- );
	iti++;
	return convertMessage<O, I>( outputBuffer, iti, FILENAME_MAX_SIZE );
}

template<typename T>
template<typename C>
void SimpleLogT<T>::printMessage( const C * messageBuffer ) {
	// Not Implemented.
}

template<typename T>
void SimpleLogT<T>::printMessage( const char * messageBuffer ) {
	std::cout << messageBuffer;
}

template<typename T>
void SimpleLogT<T>::printMessage( const wchar_t * messageBuffer ) {
	std::wcout << messageBuffer;
}

template<typename T>
template<typename C>
void SimpleLogT<T>::printChar( const C c ) {
	// Not Implemented.
}

template<typename T>
void SimpleLogT<T>::printChar( const char c ) {
	std::cout << c;
}

template<typename T>
void SimpleLogT<T>::printChar( const wchar_t c ) {
	std::wcout << c;
}

template<typename T>
void SimpleLogT<T>::increaseIndent() {
	SimpleLogT<T>::indent++;
}

template<typename T>
void SimpleLogT<T>::lowerIndent() {
	if ( SimpleLogT<T>::indent >= 1 ) {
		SimpleLogT<T>::indent--;
	}
}