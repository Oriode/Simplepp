
template<typename T>
void( *SimpleLogT<T>::mErrorHandlerFn )(
	const T *,
	MessageSeverity,
	const TCHAR *,
	unsigned int ) = &SimpleLogT<T>::errorHandler;


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
void SimpleLogT<T>::errorHandler( const T * message, typename SimpleLogT<T>::MessageSeverity severity, const TCHAR * fileName, unsigned int lineNumber ) {
	switch ( severity ) {
		case typename SimpleLogT<T>::MessageSeverity::Error:
	#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
		setConsoleColor( typename SimpleLogT<T>::MessageColor::Red );
	#else
		return;
	#endif
		break;
		case typename SimpleLogT<T>::MessageSeverity::Warning:
	#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
		setConsoleColor( typename SimpleLogT<T>::MessageColor::Yellow );
	#else
		return;
	#endif
		break;
		case typename SimpleLogT<T>::MessageSeverity::Info:
	#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
		setConsoleColor( typename SimpleLogT<T>::MessageColor::White );
	#else
		return;
		break;
	#endif
	}

	T timeBuffer[ 50 ];
	getTimeStr<T>( timeBuffer, sizeof( timeBuffer ) );

	T logBuffer[ 2048 ];

	// If we have a fileName.
	if ( fileName[ 0 ] != TCHAR( '\0' ) ) {
		T fileNameBuffer[ FILENAME_MAX_SIZE ];

		convertFileName<T, TCHAR>( fileNameBuffer, fileName, 50 );
		//fileNameBuffer[ 10 ] = T( '\0' );


		parseMessage( logBuffer, 2048, timeBuffer, fileNameBuffer, lineNumber, message );
	} else {
		parseMessage( logBuffer, 2048, timeBuffer, message );
	}

	setConsoleColor();
	printMessage( logBuffer );
}

template<typename T>
template<typename C>
void SimpleLogT<T>::parseMessage( C * buffer, int bufferSize, C * timeBuffer, const C * fileName, unsigned int lineNumber, const C * message ) {
	// Not Implemented.
}

template<typename T>
void SimpleLogT<T>::parseMessage( char * buffer, int bufferSize, char * timeBuffer, const char * fileName, unsigned int lineNumber, const char * message ) {
	snprintf( buffer, bufferSize, "[%8s][%20s@%5i] : %s\n", timeBuffer, fileName, lineNumber, message );
}

template<typename T>
void SimpleLogT<T>::parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer, const wchar_t * fileName, unsigned int lineNumber, const wchar_t * message ) {
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%8s][%20s@%5i] : %s\n", timeBuffer, fileName, lineNumber, message );
}

template<typename T>
template<typename C>
void SimpleLogT<T>::parseMessage( C * buffer, int bufferSize, C * timeBuffer, const C * message ) {
	// Not Implemented.
}

template<typename T>
void SimpleLogT<T>::parseMessage( char * buffer, int bufferSize, char * timeBuffer, const char * message ) {
	snprintf( buffer, bufferSize, "[%8s][                          ] : %s\n", timeBuffer, message );
}

template<typename T>
void SimpleLogT<T>::parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer, const wchar_t * message ) {
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%8s][                          ] : %s\n", timeBuffer, message );
}


template<typename T>
void SimpleLogT<T>::callErrorHandler( const T * message, typename SimpleLogT<T>::MessageSeverity severity, const TCHAR * fileName, unsigned int lineNumber ) {
	mErrorHandlerFn( message, severity, fileName, lineNumber );
}

template<typename T>
void SimpleLogT<T>::setConsoleColor( typename SimpleLogT<T>::MessageColor color /*= typename SimpleLogT<T>::MessageColor::White*/ ) {
#if defined WIN32
#if defined ENABLE_WIN32
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ( unsigned char ) color );
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
		SimpleLogT<T>::callErrorHandler( messageBuffer, SimpleLogT<T>::MessageSeverity::Error, fileName, lineNumber );
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
void SimpleLogT<T>::setErrorHandler( void( *errorHandlerFn ) ( const T *, typename SimpleLogT<T>::MessageSeverity, const TCHAR *, unsigned int ) ) {
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