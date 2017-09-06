#include "SimpleLog.h"





void(*SimpleLog::mErrorHandlerFn)(
	const TCHAR *,
	MessageSeverity,
	const TCHAR *,
	unsigned int) = &SimpleLog::errorHandler;



void SimpleLog::getTimeStr( TCHAR * strBuffer, size_t bufferSize ) {
	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	struct tm timeinfo;
	localtime_s( &timeinfo, &now );
	#ifdef WIN32
		std::wcsftime( strBuffer, bufferSize, TEXT( "%H:%M:%S" ), &timeinfo );
	#else
		std::strftime( strBuffer, bufferSize, TEXT( "%H:%M:%S" ), &timeinfo );
	#endif
}

void SimpleLog::errorHandler( const TCHAR * message, MessageSeverity severity, const TCHAR * fileName, unsigned int lineNumber ) {
	switch ( severity ) {
			case MessageSeverity::Error:
			#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
				setConsoleColor( MessageColor::Red );
			#else
				return;
			#endif
			break;
			case MessageSeverity::Warning:
			#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
				setConsoleColor( MessageColor::Yellow );
			#else
				return;
			#endif
			break;
			case MessageSeverity::Info:
			#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
				setConsoleColor( MessageColor::White );
			#else
				return;
			break;
			#endif
		}


	TCHAR timeBuffer[50];
	getTimeStr( timeBuffer, sizeof( timeBuffer ) );

	TCHAR logBuffer[2048];
	#ifdef WIN32
		if ( wcslen( fileName ) ) {
			_snwprintf_s( logBuffer, 2048, 2048, TEXT( "[%s][%s@%i] : %s\n" ), timeBuffer, fileName, lineNumber, message );
		} else {
			_snwprintf_s( logBuffer, 2048, 2048, TEXT( "[%s] : %s\n" ), timeBuffer, message );
		}
		std::wcout << logBuffer;
	#else
		if ( strlen( fileName ) ) {
			snprintf( logBuffer, 2048, TEXT( "[%s][%s@%i] : %s\n" ), timeBuffer, fileName, lineNumber, message );
		} else {
			snprintf( logBuffer, 2048, TEXT( "[%s] : %s\n" ), timeBuffer, message );
		}
		std::cout << timeBuffer;
	#endif
	
	setConsoleColor();
}






void SimpleLog::callErrorHandler(const TCHAR * message, MessageSeverity severity /*= MessageSeverity::Error*/, const TCHAR * fileName /*= ""*/, unsigned int lineNumber /*= 0 */) {
	mErrorHandlerFn(message, severity, fileName, lineNumber);
}

void SimpleLog::setConsoleColor(MessageColor color /*= MessageColor::White*/) {
#if defined WIN32
	#if defined ENABLE_WIN32
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ( unsigned char ) color );
	#endif
#else
	std::stringstream stream;
	stream << std::hex << color;
	system( std::string(TEXT( "Color " ) + stream.str()).c_str() );
#endif
}


SimpleLog::SimpleLog() {
}


SimpleLog::~SimpleLog(){
}



#if defined WIN32 && defined ENABLE_WIN32
void SimpleLog::displayWindowsDebug(const TCHAR * message, const TCHAR * fileName, unsigned int lineNumber) {
	if (GetLastError()) {
		SimpleLog::callErrorHandler(std::wstring(message + std::wstring(TEXT( " : Code [" )) + std::to_wstring(GetLastError()) + TEXT( "] : " ) + SimpleLog::getWindowsLastError()).c_str(), SimpleLog::MessageSeverity::Error, fileName, lineNumber);
	}
}

const TCHAR * SimpleLog::getWindowsLastError() {
	static TCHAR windowsLastError[500];
	LPTSTR lpMsgBuf;
	DWORD strlen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);


	memcpy(windowsLastError, lpMsgBuf, sizeof( TCHAR ) * strlen);
	LocalFree(lpMsgBuf);

	return windowsLastError;
}
#endif


void SimpleLog::setErrorHandler( void( *errorHandlerFn ) ( const TCHAR * , MessageSeverity, const TCHAR *, unsigned int ) ) {
	SimpleLog::mErrorHandlerFn = errorHandlerFn;
}