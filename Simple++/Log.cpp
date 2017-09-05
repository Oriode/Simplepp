#include "Log.h"


std::chrono::high_resolution_clock::time_point Log::startTime;
std::chrono::high_resolution_clock::time_point Log::endTime;


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
	SimpleLog::errorHandler( message.toCString(), severity, fileName, lineNumber );
}



void Log::callErrorHandler( const String & message, MessageSeverity severity /*= MessageSeverity::Error*/, const char * fileName /*= ""*/, unsigned int lineNumber /*= 0 */ ) {
	Log::mErrorHandlerFn( message.toCString(), severity, fileName, lineNumber );
}

#if defined WIN32 && defined ENABLE_WIN32
void Log::displayWindowsDebug( const String & message, const char * fileName, unsigned int lineNumber ) {
	if ( GetLastError() ) {
		String str( message );
		str << " : Code [" << GetLastError() << "] : " << Log::getWindowsLastError();
		Log::callErrorHandler( str , Log::MessageSeverity::Error, fileName, lineNumber );
	}
}
#endif

