
template<typename T>
void( *SimpleLogT<T>::mErrorHandlerFn )(
	const T *,
	MessageSeverity,
	const TCHAR *,
	unsigned int ) = &SimpleLogT<T>::errorHandler;


template<typename T>
void SimpleLogT<T>::getTimeStr( T * strBuffer, size_t bufferSize ) {
	// Not Implemented.
}

template<>
void SimpleLogT<char>::getTimeStr( char * strBuffer, size_t bufferSize ) {
	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	struct tm timeinfo;
	localtime_s( &timeinfo, &now );
	std::strftime( strBuffer, bufferSize, "%H:%M:%S", &timeinfo );
}

template<>
void SimpleLogT<wchar_t>::getTimeStr( wchar_t * strBuffer, size_t bufferSize ) {
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
	getTimeStr( timeBuffer, sizeof( timeBuffer ) );

	T logBuffer[ 2048 ];
#ifdef WIN32
	if ( wcslen( fileName ) ) {
		parseMessage( logBuffer, 2048, timeBuffer, fileName, lineNumber, message );
	} else {
		parseMessage( logBuffer, 2048, timeBuffer, message );
	}
	std::wcout << logBuffer;
#else
	if ( strlen( fileName ) ) {
		parseMessage( logBuffer, 2048, timeBuffer, fileName, lineNumber, message );
	} else {
		parseMessage( logBuffer, 2048, timeBuffer, message );
	}
	std::cout << timeBuffer;
#endif

	setConsoleColor();
}

template<typename T>
void SimpleLogT<T>::parseMessage( T * buffer, int bufferSize, T * timeBuffer, const TCHAR * fileName, unsigned int lineNumber, const T * message ) {
	// Not Implemented.
}

template<>
void SimpleLogT<char>::parseMessage( char * buffer, int bufferSize, char * timeBuffer, const TCHAR * fileName, unsigned int lineNumber, const char * message ) {
	snprintf( buffer, bufferSize, "[%s][%s@%i] : %s\n", timeBuffer, fileName, lineNumber, message );
}

template<>
void SimpleLogT<wchar_t>::parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer, const TCHAR * fileName, unsigned int lineNumber, const wchar_t * message ) {
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%s][%s@%i] : %s\n", timeBuffer, fileName, lineNumber, message );
}

template<typename T>
void SimpleLogT<T>::parseMessage( T * buffer, int bufferSize, T * timeBuffer, const T * message ) {
	// Not Implemented.
}

template<>
void SimpleLogT<char>::parseMessage( char * buffer, int bufferSize, char * timeBuffer, const char * message ) {
	snprintf( buffer, bufferSize, "[%s] : %s\n", timeBuffer, message );
}

template<>
void SimpleLogT<wchar_t>::parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer, const wchar_t * message ) {
	_snwprintf_s( buffer, bufferSize, bufferSize, L"[%s] : %s\n", timeBuffer, message );
}


template<typename T>
void SimpleLogT<T>::callErrorHandler( const T * message, typename SimpleLogT<T>::MessageSeverity severity /*= typename SimpleLogT<T>::MessageSeverity::Error*/, const TCHAR * fileName /*= ""*/, unsigned int lineNumber /*= 0 */ ) {
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
void SimpleLogT<T>::displayWindowsDebug( const T * message, const T * fileName, unsigned int lineNumber ) {
	if ( GetLastError() ) {
		SimpleLogT<T>::callErrorHandler( std::wstring( message + std::wstring( TEXT( " : Code [" ) ) + std::to_wstring( GetLastError() ) + TEXT( "] : " ) + SimpleLogT<T>::getWindowsLastError() ).c_str(), SimpleLogT<T>::MessageSeverity::Error, fileName, lineNumber );
	}
}

template<typename T>
const T * SimpleLogT<T>::getWindowsLastError() {
	static T windowsLastError[ 500 ];
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


	memcpy( windowsLastError, lpMsgBuf, sizeof( T ) * strlen );
	LocalFree( lpMsgBuf );

	return windowsLastError;
}
#endif

template<typename T>
void SimpleLogT<T>::setErrorHandler( void( *errorHandlerFn ) ( const T *, typename SimpleLogT<T>::MessageSeverity, const TCHAR *, unsigned int ) ) {
	SimpleLogT<T>::mErrorHandlerFn = errorHandlerFn;
}