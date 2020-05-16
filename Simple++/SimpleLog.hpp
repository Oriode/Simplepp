
template<typename T>
void( *SimpleLogT<T>::mErrorHandlerFn )(
	const T *,
	MessageSeverity,
	const T *,
	unsigned int ) = &SimpleLogT<T>::errorHandler;


template<typename T>
void SimpleLogT<T>::getTimeStr ( T * strBuffer, size_t bufferSize ) {
	auto now = std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now () );
	struct tm timeinfo;
	localtime_s ( &timeinfo, &now );
#ifdef WIN32
	std::wcsftime ( strBuffer, bufferSize, TEXT ( "%H:%M:%S" ), &timeinfo );
#else
	std::strftime ( strBuffer, bufferSize, TEXT ( "%H:%M:%S" ), &timeinfo );
#endif
}

template<typename T>
void SimpleLogT<T>::errorHandler ( const T * message, MessageSeverity severity, const T * fileName, unsigned int lineNumber ) {
	switch ( severity ) {
		case MessageSeverity::Error:
	#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
		setConsoleColor ( MessageColor::Red );
	#else
		return;
	#endif
		break;
		case MessageSeverity::Warning:
	#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
		setConsoleColor ( MessageColor::Yellow );
	#else
		return;
	#endif
		break;
		case MessageSeverity::Info:
	#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
		setConsoleColor ( MessageColor::White );
	#else
		return;
		break;
	#endif
	}


	T timeBuffer[ 50 ];
	getTimeStr ( timeBuffer, sizeof ( timeBuffer ) );

	T logBuffer[ 2048 ];
#ifdef WIN32
	if ( wcslen ( fileName ) ) {
		_snwprintf_s ( logBuffer, 2048, 2048, TEXT ( "[%s][%s@%i] : %s\n" ), timeBuffer, fileName, lineNumber, message );
	} else {
		_snwprintf_s ( logBuffer, 2048, 2048, TEXT ( "[%s] : %s\n" ), timeBuffer, message );
	}
	std::wcout << logBuffer;
#else
	if ( strlen ( fileName ) ) {
		snprintf ( logBuffer, 2048, TEXT ( "[%s][%s@%i] : %s\n" ), timeBuffer, fileName, lineNumber, message );
	} else {
		snprintf ( logBuffer, 2048, TEXT ( "[%s] : %s\n" ), timeBuffer, message );
	}
	std::cout << timeBuffer;
#endif

	setConsoleColor ();
}





template<typename T>
void SimpleLogT<T>::callErrorHandler ( const T * message, MessageSeverity severity /*= MessageSeverity::Error*/, const T * fileName /*= ""*/, unsigned int lineNumber /*= 0 */ ) {
	mErrorHandlerFn ( message, severity, fileName, lineNumber );
}

template<typename T>
void SimpleLogT<T>::setConsoleColor ( MessageColor color /*= MessageColor::White*/ ) {
#if defined WIN32
#if defined ENABLE_WIN32
	SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE ), ( unsigned char ) color );
#endif
#else
	std::stringstream stream;
	stream << std::hex << color;
	system ( std::string ( TEXT ( "Color " ) + stream.str () ).c_str () );
#endif
}

template<typename T>
SimpleLogT<T>::SimpleLogT () {}

template<typename T>
SimpleLogT<T>::~SimpleLogT () {}



#if defined WIN32 && defined ENABLE_WIN32
template<typename T>
void SimpleLogT<T>::displayWindowsDebug ( const T * message, const T * fileName, unsigned int lineNumber ) {
	if ( GetLastError () ) {
		SimpleLogT<T>::callErrorHandler ( std::wstring ( message + std::wstring ( TEXT ( " : Code [" ) ) + std::to_wstring ( GetLastError () ) + TEXT ( "] : " ) + SimpleLogT<T>::getWindowsLastError () ).c_str (), SimpleLogT<T>::MessageSeverity::Error, fileName, lineNumber );
	}
}

template<typename T>
const T * SimpleLogT<T>::getWindowsLastError () {
	static T windowsLastError[ 500 ];
	LPTSTR lpMsgBuf;
	DWORD strlen = FormatMessage (
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError (),
		MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		( LPTSTR ) &lpMsgBuf,
		0, NULL );


	memcpy ( windowsLastError, lpMsgBuf, sizeof ( T ) * strlen );
	LocalFree ( lpMsgBuf );

	return windowsLastError;
}
#endif

template<typename T>
void SimpleLogT<T>::setErrorHandler ( void( *errorHandlerFn ) ( const T *, MessageSeverity, const T *, unsigned int ) ) {
	SimpleLogT<T>::mErrorHandlerFn = errorHandlerFn;
}