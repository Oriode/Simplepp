template<typename T>
std::chrono::high_resolution_clock::time_point LogT<T>::startTime;
template<typename T>
std::chrono::high_resolution_clock::time_point LogT<T>::endTime;

template<typename T>
LogT<T>::LogT( void ) {}

template<typename T>
LogT<T>::~LogT( void ) {}

template<typename T>
void LogT<T>::displayError( const BasicString<T> & message ) {
#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
	LogT<T>::callErrorHandler( message, typename LogT<T>::MessageSeverity::Error, typename LogT<T>::MessageColor::Red );
#endif
}

template<typename T>
void LogT<T>::displayWarning( const BasicString<T> & message ) {
#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY
	LogT<T>::callErrorHandler( message, typename LogT<T>::MessageSeverity::Warning, typename LogT<T>::MessageColor::Yellow );
#endif
}

template<typename T>
void LogT<T>::displayLog( const BasicString<T> & message ) {
#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
	LogT<T>::callErrorHandler( message, typename LogT<T>::MessageSeverity::Info, typename LogT<T>::MessageColor::White );
#endif
}

template<typename T>
void LogT<T>::displaySuccess( const BasicString<T> & message ) {
#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY
	LogT<T>::callErrorHandler( message, typename LogT<T>::MessageSeverity::Info, typename LogT<T>::MessageColor::Green );
#endif
}

template<typename T>
void LogT<T>::startChrono() {
	LogT<T>::startTime = std::chrono::high_resolution_clock::now();
}

template<typename T>
void LogT<T>::stopChrono() {
	LogT<T>::endTime = std::chrono::high_resolution_clock::now();
}

template<typename T>
void LogT<T>::displayChrono( const BasicString<T> & text ) {
	displayLog( text + TEXT( " : " ) + ( std::chrono::duration_cast< std::chrono::duration<double> >( LogT<T>::endTime - LogT<T>::startTime ).count() * 1000.0 ) + TEXT( " ms" ) );
}

template<typename T>
void LogT<T>::errorHandler( const BasicString<T> & message, typename LogT<T>::MessageSeverity severity, typename LogT<T>::MessageColor color, const TCHAR * fileName, unsigned int lineNumber ) {
	SimpleLogT<T>::errorHandler( message.toCString(), severity, color, fileName, lineNumber );
}

template<typename T>
void LogT<T>::callErrorHandler( const BasicString<T> & message, typename LogT<T>::MessageSeverity severity /*= typename LogT<T>::MessageSeverity::Error*/, typename LogT<T>::MessageColor color /*= typename LogT<T>::MessageColor::Red*/, const TCHAR * fileName /*= ""*/, unsigned int lineNumber /*= 0 */) {
	LogT<T>::errorHandler( message.toCString(), severity, color, fileName, lineNumber );
}

#if defined WIN32 && defined ENABLE_WIN32
template<typename T>
void LogT<T>::displayWindowsDebug( const BasicString<T> & message, const TCHAR * fileName, unsigned int lineNumber ) {
	if ( GetLastError() ) {
		BasicString<T> str( message );
		str << " : Code [" << GetLastError() << "] : " << LogT<T>::getWindowsLastError();
		LogT<T>::callErrorHandler( str, LogT<T>::typename LogT<T>::MessageSeverity::Error, fileName, lineNumber );
	}
}
#endif

