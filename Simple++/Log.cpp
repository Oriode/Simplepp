#include "Log.h"


std::chrono::high_resolution_clock::time_point Log::startTime;
std::chrono::high_resolution_clock::time_point Log::endTime;

void( *Log::mErrorHandlerFn )(
	const String &,
	MessageSeverity,
	const char *,
	unsigned int ) = &Log::errorHandler;



Log::Log( void ) {
}

Log::~Log( void ) {
}


void Log::displayError( const String & message ) {
	#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
	Log::callErrorHandler( message, MessageSeverity::Error );
	#endif
}

void Log::displayWarning( const String & message ) {
	#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
	Log::callErrorHandler( message, MessageSeverity::Warning );
	#endif
}

void Log::displayLog( const String & message ) {
	#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
	Log::callErrorHandler( message, MessageSeverity::Info );
	#endif
}

void Log::startChrono() {
	Log::startTime = std::chrono::high_resolution_clock::now();
}

void Log::stopChrono() {
	Log::endTime = std::chrono::high_resolution_clock::now();
}

void Log::displayChrono( const String & text ) {
	displayLog( text + " : " + ( std::chrono::duration_cast< std::chrono::duration<double> >( Log::endTime - Log::startTime ).count() * 1000.0 ) + " ms" );
}

void Log::errorHandler( const String & message, MessageSeverity severity, const char * fileName, unsigned int lineNumber) {
	#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY

	//Cast the time into a standard C time
	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	struct tm timeinfo;
	localtime_s( &timeinfo, &now );
	char timeBuffer[100];
	std::strftime( timeBuffer, sizeof( timeBuffer ), "%H:%M:%S", &timeinfo );

	switch ( severity ) {

	#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
	case MessageSeverity::Error:
	setConsoleColor( MessageColor::Red );
	getOutStream() << "[ " << timeBuffer << " ] Error : ";
	_printMessage( message.toCString(), fileName, lineNumber );
	setConsoleColor();
	#endif
	break;

	#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
	case MessageSeverity::Warning:
	setConsoleColor( MessageColor::Yellow );
	getOutStream() << "[ " << timeBuffer << " ] Warning : ";
	_printMessage( message.toCString(), fileName, lineNumber );
	setConsoleColor();
	break;
	#endif

	#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
	case MessageSeverity::Info:
	setConsoleColor( MessageColor::White );
	getOutStream() << "[ " << timeBuffer << " ] Info : ";
	_printMessage( message.toCString(), fileName, lineNumber );
	//setConsoleColor();
	break;
	#endif
	}

	#endif
}

void Log::setErrorHandler( void( *errorHandlerFn ) ( const String &, MessageSeverity, const char *, unsigned int ) ) {
	Log::mErrorHandlerFn = errorHandlerFn;
}


void Log::callErrorHandler( const String & message, MessageSeverity severity /*= MessageSeverity::Error*/, const char * fileName /*= ""*/, unsigned int lineNumber /*= 0 */ ) {
	Log::mErrorHandlerFn( message, severity, fileName, lineNumber );
}




#ifdef WIN32
void Log::displayWindowsDebug( const String & message, const char * fileName, unsigned int lineNumber ) {
	if ( GetLastError() ) {
		String str( message );
		str << " : Code [" << GetLastError() << "] : " << Log::getWindowsLastError();
		Log::callErrorHandler( str , Log::MessageSeverity::Error, fileName, lineNumber );
	}
}
#endif

