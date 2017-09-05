#pragma once


///
/// @file	Log.h
/// @brief	Logging functions.
/// @author	Clément Gerber
/// @date	20/05/15
/// @version	1.0
///
///

///@function debug
///@brief macro function to write something that will only exists in the DEBUG build.

///@function error
///@brief macro function that will write an error message to the debug output only in the DEBUG build.

///@function log
///@brief macro function that will write an log message to the debug output only in the DEBUG build. The default error handler will only output the log message if the LOG_SEVERITY <= 1

///@function warn
///@brief macro function that will write an warning message to the debug output only in the DEBUG build. The default error handler will only output the warning message if the LOG_SEVERITY <= 2

///@function assert
///@brief macro function that will test the inputed condition and write and error if not true. Works only in DEBUG build. The default error handler will only output the error message if the LOG_SEVERITY <= 3


#include <ctime>
#include <chrono>
#include <string>
#include <iostream>
#include <stdio.h>

#include "BuildConfig.h"

#if defined WIN32 && defined ENABLE_WIN32
#include <Windows.h>
#endif
 

#if defined DEBUG
#undef debug
#define debug(code); code
#define error(msg); Log::callErrorHandler(String(msg), Log::MessageSeverity::Error, __FILE__, __LINE__);
#define log(msg); Log::callErrorHandler(String(msg), Log::MessageSeverity::Info, __FILE__, __LINE__);
#define warn(msg); Log::callErrorHandler(String(msg), Log::MessageSeverity::Warning, __FILE__, __LINE__);

#define assert(condition); if (!(condition)) Log::callErrorHandler("Assertion Failed! : ("#condition") => false", Log::MessageSeverity::Error, __FILE__, __LINE__);
#define assertstr(condition,msg); if (!(condition)) Log::callErrorHandler("Assertion Failed! : "#msg, Log::MessageSeverity::Error, __FILE__, __LINE__);

#if defined WIN32 && defined ENABLE_WIN32
#define windowsDebug(msg); Log::displayWindowsDebug(msg, __FILE__, __LINE__);
#else	
#define windowsDebug(msg);
#endif
#else
#undef debug
#define debug( ... );
#define log( ... );
#define warn( ... );
#define error( ... );
#define windowsDebug( ... );
#define assert( ... );
#define assertstr( ... );

#endif



#include "SimpleLog.h"
#include "String.h"



class Log : public SimpleLog {
public:
	Log( void );
	~Log( void );


	///@brief Display a log message even if we are in debug build or not.
	///@param text Text to display
	static void displayLog( const String & text );

	///@brief Display a warning message even if we are in debug build or not.
	///@param text Text to display
	static void displayWarning( const String & text );



	///@brief Display a error message even if we are in debug build or not.
	///@param text Text to display
	static void displayError( const String & text );

	///@brief Start the chrono, see stopChrono();
	static void startChrono();

	///@brief stop chrono, see displayChrono();
	static void stopChrono();

	///@brief Display the last chrono result computed with startChrono() and displayChrono();
	///@param text Text to display with the time result.
	static void displayChrono( const String & text = "Elapsed Time" );





	static void errorHandler(
		const String &,
		MessageSeverity severity = MessageSeverity::Error,
		const char * fileName = "",
		unsigned int lineNumber = 0 );


	static void callErrorHandler(
		const String & message,
		MessageSeverity severity = MessageSeverity::Error,
		const char * fileName = "",
		unsigned int lineNumber = 0
	);


	#if defined WIN32 && defined ENABLE_WIN32
	static void displayWindowsDebug( const String & message, const char * fileName, unsigned int lineNumber );
	#endif

private:
	static std::chrono::high_resolution_clock::time_point startTime;
	static std::chrono::high_resolution_clock::time_point endTime;
};



