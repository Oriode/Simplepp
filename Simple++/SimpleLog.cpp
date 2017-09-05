#include "SimpleLog.h"



std::ostream * SimpleLog::Out = &(std::cout);


void(*SimpleLog::mErrorHandlerFn)(
	const char *,
	MessageSeverity,
	const char *,
	unsigned int) = &SimpleLog::errorHandler;


std::ostream & SimpleLog::getOutStream() {
	return *SimpleLog::Out;
}

void SimpleLog::setOutStream( std::ostream * stream ) {
	SimpleLog::Out = stream;
}

void SimpleLog::getTimeStr( char * strBuffer, size_t bufferSize ) {
	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	struct tm timeinfo;
	localtime_s( &timeinfo, &now );
	std::strftime( strBuffer, bufferSize, "%H:%M:%S", &timeinfo );
}

void SimpleLog::errorHandler( const char * message, MessageSeverity severity, const char * fileName, unsigned int lineNumber ) {
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


	char timeBuffer[50];
	getTimeStr( timeBuffer, sizeof( timeBuffer ) );

	char logBuffer[2048];
	if ( strlen( fileName ) ) {
		snprintf( logBuffer, 2048, "[%s][%s@%i] : %s\n", timeBuffer, fileName, lineNumber, message );
		} else {
		snprintf( logBuffer, 2048, "[%s] : %s\n", timeBuffer, message );
		}

	getOutStream() << logBuffer;

	setConsoleColor();
}






void SimpleLog::callErrorHandler(const char * message, MessageSeverity severity /*= MessageSeverity::Error*/, const char * fileName /*= ""*/, unsigned int lineNumber /*= 0 */) {
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
	system( std::string("Color " + stream.str()).c_str() );
#endif
}


SimpleLog::SimpleLog() {
}


SimpleLog::~SimpleLog(){
}



#if defined WIN32 && defined ENABLE_WIN32
void SimpleLog::displayWindowsDebug(const char * message, const char * fileName, unsigned int lineNumber) {
	if (GetLastError()) {
		SimpleLog::callErrorHandler(std::string(message + std::string(" : Code [") + std::to_string(GetLastError()) + "] : " + SimpleLog::getWindowsLastError()).c_str(), SimpleLog::MessageSeverity::Error, fileName, lineNumber);
	}
}

const char * SimpleLog::getWindowsLastError() {
	static char windowsLastError[500];
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


	memcpy(windowsLastError, lpMsgBuf, sizeof(char) * strlen);
	LocalFree(lpMsgBuf);

	return windowsLastError;
}
#endif


void SimpleLog::setErrorHandler( void( *errorHandlerFn ) ( const char * , MessageSeverity, const char *, unsigned int ) ) {
	SimpleLog::mErrorHandlerFn = errorHandlerFn;
}