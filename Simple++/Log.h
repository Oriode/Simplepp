#pragma once


///
/// @file	Log.h
/// @brief	Logging functions.
/// @author	Cl�ment Gerber
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

#ifdef WIN32
#include <Windows.h>
#endif

#if defined DEBUG || !defined NDEBUG
#ifndef debug
#define debug(code); code
#endif
#define error(msg); Log::callErrorHandler(msg, Log::MessageSeverity::Error, __FILE__, __LINE__);
#define log(msg); Log::callErrorHandler(msg, Log::MessageSeverity::Info, __FILE__, __LINE__);
#define warn(msg); Log::callErrorHandler(msg, Log::MessageSeverity::Warning, __FILE__, __LINE__);
#define assert(condition); if (!(condition)) Log::callErrorHandler("Assertion failed : "#condition, Log::MessageSeverity::Error, __FILE__, __LINE__);

#ifdef WIN32
#define windowsDebug(msg); Log::displayWindowsDebug(msg, __FILE__, __LINE__);
#else	
#define windowsDebug(msg);
#endif
#else
#ifndef debug
#define debug(code);
#endif
#define log(msg);
#define warn(msg);
#define error(msg);
#define windowsDebug(msg);
#define assert(condition);
#endif



#include "SimpleLog.h"
#include "String.h"

class Log : public SimpleLog {
public:
	Log( void );
	~Log( void );


	static void displayLog( const String & text );
	static void displayWarning( const String & text );
	static void displayError( const String & text );

	static void startChrono();
	static void stopChrono();

	static void displayChrono( const String & text = "Elapsed Time" );


	static void setErrorHandler( void( *errorHandlerFn ) (
		const String &,
		MessageSeverity,
		const String &,
		unsigned int ) );


	static void errorHandler(
		const String &,
		MessageSeverity severity = MessageSeverity::Error,
		const String & fileName = "",
		unsigned int lineNumber = 0 );


	static void callErrorHandler(
		const String & message,
		MessageSeverity severity = MessageSeverity::Error,
		const String & fileName = "",
		unsigned int lineNumber = 0
	);


	#ifdef WIN32
	static void displayWindowsDebug( const String & message, const String & fileName, unsigned int lineNumber );
	#endif

private:

	static void( *mErrorHandlerFn ) (
		const String &,
		MessageSeverity,
		const String &,
		unsigned int );
	static std::chrono::high_resolution_clock::time_point startTime;
	static std::chrono::high_resolution_clock::time_point endTime;

};



