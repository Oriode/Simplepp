#include "Log.h"

template<typename T>
LogT<T> LogT<T>::INSTANCE;

template<typename T>
LogT<T>::LogT( void ) {
	addHandler( &this->defaultHandler );
}

template<typename T>
LogT<T>::~LogT( void ) { }

template<typename T>
inline void LogT<T>::addHandler( LogHandlerT<T>* handler ) {
	this->handlerVector.push( handler );
}

template<typename T>
inline void LogT<T>::removeHandler( LogHandlerT<T>* handler ) {
	this->handlerVector.eraseAll( handler );
}

template<typename T>
inline void LogT<T>::removeDefaultHandler() {
	removeHandler( &this->defaultHandler );
}

template<typename T>
inline void LogT<T>::callOnMessage( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename SimpleLogT<T>::MessageSeverity severity, typename SimpleLogT<T>::MessageColor color ) {
	for ( Size i( 0 ); i < this->handlerVector.getSize(); i++ ) {
		this->handlerVector.getValueI( i )->message( logTitle, logMessage, severity, color );
	}
}

template<typename T>
inline void LogT<T>::callOnStartStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	for ( Size i( 0 ); i < this->handlerVector.getSize(); i++ ) {
		this->handlerVector.getValueI( i )->startStep( logTitle, logMessage );
	}
}

template<typename T>
inline void LogT<T>::callOnEndStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename SimpleLogT<T>::MessageColor color ) {
	for ( Size i( 0 ); i < this->handlerVector.getSize(); i++ ) {
		this->handlerVector.getValueI( i )->endStep( logTitle, logMessage, color );
	}
}

template<typename T>
inline void LogT<T>::callOnIncreaseIndent() {
	for ( Size i( 0 ); i < this->handlerVector.getSize(); i++ ) {
		this->handlerVector.getValueI( i )->increaseIndent();
	}
}

template<typename T>
inline void LogT<T>::callOnDecreaseIndent() {
	for ( Size i( 0 ); i < this->handlerVector.getSize(); i++ ) {
		this->handlerVector.getValueI( i )->decreaseIndent();
	}
}

template<typename T>
inline void LogT<T>::setDisplayError( bool bDisplayError ) {
	this->bDisplayError = bDisplayError;
}

template<typename T>
inline void LogT<T>::setDisplayWarning( bool bDisplayWarning ) {
	this->bDisplayWarning = bDisplayWarning;
}

template<typename T>
inline void LogT<T>::setDispalyInfo( bool bDisplayInfo ) {
	this->bDisplayInfo = bDisplayInfo;
}

template<typename T>
inline void LogT<T>::setDisplayVerbose( bool bDisplayVerbose ) {
	this->bDisplayVerbose = bDisplayVerbose;
}

template<typename T>
inline void LogT<T>::_displayMessage( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename SimpleLogT<T>::MessageSeverity severity, typename LogT<T>::MessageColor messageColor ) {
	if ( severity == SimpleLogT<T>::MessageSeverity::Verbose && !this->bDisplayVerbose ) {
		return;
	}
	if ( severity == SimpleLogT<T>::MessageSeverity::Info && !this->bDisplayInfo ) {
		return;
	}
	if ( severity == SimpleLogT<T>::MessageSeverity::Warning && !this->bDisplayWarning ) {
		return;
	}
	if ( severity == SimpleLogT<T>::MessageSeverity::Error && !this->bDisplayError ) {
		return;
	}

	callOnMessage( logTitle, logMessage, severity, messageColor );
}

template<typename T>
inline void LogT<T>::_startStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage) {
	if ( !this->bDisplayInfo ) {
		return;
	}
	callOnStartStep( logTitle, logMessage );
}

template<typename T>
inline void LogT<T>::_endStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename SimpleLogT<T>::MessageColor messageColor ) {
	if ( !this->bDisplayInfo ) {
		return;
	}
	callOnEndStep( logTitle, logMessage, messageColor );
}

template<typename T>
inline void LogT<T>::displayVerbose( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor ) {
	LogT<T>::getInstance()->_displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Verbose, messageColor );
}

template<typename T>
inline void LogT<T>::displayVerbose( const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor ) {
	LogT<T>::getInstance()->_displayMessage( BasicString<T>::null, logMessage, SimpleLogT<T>::MessageSeverity::Verbose, messageColor );
}

template<typename T>
void LogT<T>::displayError( const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_displayMessage( BasicString<T>::null, logMessage, SimpleLogT<T>::MessageSeverity::Error, SimpleLogT<T>::MessageColor::Red );
}

template<typename T>
inline void LogT<T>::displayError( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Error, SimpleLogT<T>::MessageColor::Red );
}

template<typename T>
void LogT<T>::displayWarning( const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_displayMessage( BasicString<T>::null, logMessage, SimpleLogT<T>::MessageSeverity::Error, SimpleLogT<T>::MessageColor::Red );
}

template<typename T>
inline void LogT<T>::displayWarning( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Warning, SimpleLogT<T>::MessageColor::Yellow );
}

template<typename T>
void LogT<T>::displayLog( const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor ) {
	LogT<T>::getInstance()->_displayMessage( BasicString<T>::null, logMessage, SimpleLogT<T>::MessageSeverity::Info, messageColor );
}

template<typename T>
inline void LogT<T>::displayLog( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor ) {
	LogT<T>::getInstance()->_displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Info, messageColor );
}

template<typename T>
void LogT<T>::displaySuccess( const BasicString<T>& logMessage ) {
	static BasicString<T> logTitle( "SUCCESS" );
	LogT<T>::getInstance()->_displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Info, SimpleLogT<T>::MessageColor::Green );
}

template<typename T>
inline void LogT<T>::displaySuccess( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Info, SimpleLogT<T>::MessageColor::Green );
}

template<typename T>
void LogT<T>::startStep( const BasicString<T>& logMessage ) {
	static BasicString<T> logTitle( "STEP" );
	LogT<T>::getInstance()->_startStep( logTitle, logMessage );
}

template<typename T>
inline void LogT<T>::startStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_startStep( logTitle, logMessage );
}

template<typename T>
void LogT<T>::endStep( const BasicString<T>& logMessage ) {
	static BasicString<T> logTitle( "DONE" );
	LogT<T>::getInstance()->_endStep( logTitle, logMessage, SimpleLogT<T>::MessageColor::White );
}

template<typename T>
inline void LogT<T>::endStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_endStep( logTitle, logMessage, SimpleLogT<T>::MessageColor::White );
}

template<typename T>
void LogT<T>::endStepSuccess( const BasicString<T>& logMessage ) {
	static BasicString<T> logTitle( "SUCCESS" );
	LogT<T>::getInstance()->_endStep( logTitle, logMessage, SimpleLogT<T>::MessageColor::Green );
}

template<typename T>
inline void LogT<T>::endStepSuccess( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_endStep( logTitle, logMessage, SimpleLogT<T>::MessageColor::Green );
}

template<typename T>
void LogT<T>::endStepFailure( const BasicString<T>& logMessage ) {
	static BasicString<T> logTitle( "FAILURE" );
	LogT<T>::getInstance()->_endStep( logTitle, logMessage, SimpleLogT<T>::MessageColor::Red );
}

template<typename T>
inline void LogT<T>::endStepFailure( const BasicString<T>& logTitle, const BasicString<T>& logMessage ) {
	LogT<T>::getInstance()->_endStep( logTitle, logMessage, SimpleLogT<T>::MessageColor::Red );
}

template<typename T>
void LogT<T>::displayNewLine() {
	LogT<T>::getInstance()->_displayMessage( BasicString<T>(), BasicString<T>(), SimpleLogT<T>::MessageSeverity::Info, SimpleLogT<T>::MessageColor::White );
}

template<typename T>
inline void LogT<T>::increaseIndent() {
	LogT<T>::getInstance()->callOnIncreaseIndent();
}

template<typename T>
inline void LogT<T>::lowerIndent() {
	LogT<T>::getInstance()->callOnDecreaseIndent();
}

#if defined WIN32 && defined ENABLE_WIN32
template<typename T>
void LogT<T>::displayWindowsDebug( const BasicString<T>& message, const TCHAR* fileName, unsigned int lineNumber ) {
	static BasicString<T> logTitle( "WINDOWS" );

	if ( GetLastError() ) {
		BasicString<T> logMessage( message );
		logMessage << " : Code [" << GetLastError() << "] : " << LogT<T>::getWindowsLastError();
		LogT<T>::getInstance()->displayMessage( logTitle, logMessage, SimpleLogT<T>::MessageSeverity::Info, SimpleLogT<T>::MessageColor::White );
	}
}
template<typename T>
inline LogT<T>* LogT<T>::getInstance() {
	return &LogT<T>::INSTANCE;
}
#endif

