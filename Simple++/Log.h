/**
 * @file		LogT.h.
 *
 * @brief 	Logging functions.
 * @author	Clément Gerber
 * @date		20/05/15 (DMY)
 */
#pragma once



 ///@fn debug
 ///@brief macro function to write something that will only exists in the DEBUG build.

 ///@fn error
 ///@brief macro function that will write an error message to the debug output only in the DEBUG build.

 ///@fn log
 ///@brief macro function that will write an log message to the debug output only in the DEBUG build. The default error handler will only output the log message if the LOG_SEVERITY <= 1

 ///@fn warn
 ///@brief macro function that will write an warning message to the debug output only in the DEBUG build. The default error handler will only output the warning message if the LOG_SEVERITY <= 2

 ///@fn assert
 ///@brief macro function that will test the inputed condition and write and error if not true. Works only in DEBUG build. The default error handler will only output the error message if the LOG_SEVERITY <= 3

#include <ctime>
#include <chrono>
#include <string>
#include <iostream>
#include <stdio.h>

#include "BuildConfig.h"
#include "SimpleLog.h"

#if defined WIN32 && defined ENABLE_WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif

#if defined DEBUG
#undef debug


#if defined WIN32 && defined ENABLE_WIN32
#define windowsDebug(msg); Log::displayWindowsDebug(msg, TEXT( __FILE__ ), __LINE__);
#else
#define windowsDebug(msg);
#endif


#define debug(code); code
#define error(msg); Log::callErrorHandler( StringASCII(msg), Log::MessageSeverity::Error, Log::MessageColor::Red, TEXT( __FILE__ ), __LINE__ );
#define warn(msg); Log::callErrorHandler( StringASCII(msg), Log::MessageSeverity::Warning, Log::MessageColor::Yellow, TEXT( __FILE__ ), __LINE__ );
#define info(msg); Log::callErrorHandler( StringASCII(msg), Log::MessageSeverity::Info, Log::MessageColor::White, TEXT( __FILE__ ), __LINE__ );
#define verbose(msg); Log::callErrorHandler( StringASCII(msg), Log::MessageSeverity::Verbose, Log::MessageColor::Gray, TEXT( __FILE__ ), __LINE__ );

#define assert(condition); if (!(condition)) Log::callErrorHandler(TEXT( "Assertion Failed! : ("#condition") => false" ), Log::MessageSeverity::Error, Log::MessageColor::Red, TEXT( __FILE__ ), __LINE__);
#define assertstr(condition,msg); if (!(condition)) Log::callErrorHandler(TEXT( "Assertion Failed! : "#msg ), Log::MessageSeverity::Error, Log::MessageColor::Red, TEXT( __FILE__ ), __LINE__);

#else
#undef debug
#define debug( ... );
#define info( ... );
#define verbose( ... );
#define warn( ... );
#define error( ... );
#define windowsDebug( ... );
#define assert( ... );
#define assertstr( ... );

#endif

#include "String.h"

template<typename T>
class LogT : public SimpleLogT<T> {
public:
	using SimpleLogT<T>::MessageSeverity;
	using SimpleLogT<T>::MessageColor;

	/** @brief	Default constructor */
	LogT( void );

	/** @brief	Destructor */
	~LogT( void );

	/**
		* @brief 	Display a log message even if we are in debug build or not.
		* @param 	text	Text to display.
		* @param	messageColor Color to be used.
		*/
	static void displayVerbose(const BasicString<T>& text, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::Gray);

	/**
		* @brief 	Display a log message even if we are in debug build or not.
		* @param 	text	Text to display.
		* @param	messageColor Color to be used.
		*/
	static void displayLog( const BasicString<T> & text, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::White );

	/**
	* @brief 	Display a success log message even if we are in debug build or not.
	* @param 	text	Text to display.
	*/
	static void displaySuccess( const BasicString<T> & text );

	/**
		* @brief 	Display a warning message even if we are in debug build or not.
		* @param 	text	Text to display.
		*/
	static void displayWarning( const BasicString<T> & text );

	/**
		* @brief 	Display a error message even if we are in debug build or not.
		* @param 	text	Text to display.
		*/
	static void displayError( const BasicString<T> & text );

	/**
	 * @brief Display a special message representing the opening of a new step & increase the indent.
	 * @param text Text to be displayed
	 */
	static void startStep( const BasicString<T> & text );

	/**
	 * @brief Display a special message representing the ending of a new step & lower the indent.
	 * @param text Text to be displayed
	 */
	static void endStep( const BasicString<T> & text );

	/**
	 * @brief Display a special message representing the success ending of a new step & lower the indent.
	 * @param text Text to be displayed
	 */
	static void endStepSuccess( const BasicString<T> & text );

	/**
	 * @brief Display a special message representing the failure ending of a new step & lower the indent.
	 * @param text Text to be displayed
	 */
	static void endStepFailure( const BasicString<T> & text );

	/**
	 * @brief Display a new line.
	 */
	static void displayNewLine();

	/** @brief	Start the chrono, see stopChrono(); */
	static void startChrono();

	/** @brief	stop chrono, see displayChrono(); */
	static void stopChrono();

	/**
		* @brief 	Display the last chrono result computed with startChrono() and displayChrono();
		* @param 	text	(Optional) Text to display with the time result.
		*/
	static void displayChrono( const BasicString<T> & text = "Elapsed Time" );

	/**
		* @brief 	Handler, called when the error
		*
		* @param 	parameter1	BasicString<T> to be displayed.
		* @param 	severity  	(Optional) The severity.
		* @param 	fileName  	(Optional) Filename of the file.
		* @param 	lineNumber	(Optional) The line number.
		*/
	static void errorHandler(
		const BasicString<T> &,
		typename LogT<T>::MessageSeverity severity = typename LogT<T>::MessageSeverity::Error,
		typename LogT<T>::MessageColor color = typename LogT<T>::MessageColor::Red,
		const TCHAR * fileName = NULL,
		unsigned int lineNumber = 0 );


	static void callErrorHandler(
		const BasicString<T> & message,
		typename LogT<T>::MessageSeverity severity = typename LogT<T>::MessageSeverity::Error,
		typename LogT<T>::MessageColor color = typename LogT<T>::MessageColor::Red,
		const TCHAR * fileName = NULL,
		unsigned int lineNumber = 0
	);


#if defined WIN32 && defined ENABLE_WIN32
	static void displayWindowsDebug( const BasicString<T> & message, const TCHAR * fileName, unsigned int lineNumber );
#endif

private:
	static std::chrono::high_resolution_clock::time_point startTime;
	static std::chrono::high_resolution_clock::time_point endTime;
};

using Log = LogT<char>;


#include "Log.hpp"