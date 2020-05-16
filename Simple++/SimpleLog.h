#pragma once

///
/// @file	Log.h
/// @brief	Simple Logging functions with no other dependencies to be used in the library itself.
/// @author	Cl�ment Gerber
/// @date	20/05/15
/// @version	1.0
///
/// Logging functions.
/// use log(""); warning(""); error(""); macros to write inside the stdout.
///


#include <iostream>
#include <ctime>
#include <chrono>
#include <string>

#include "BuildConfig.h"

#if defined WIN32 && defined ENABLE_WIN32
#include <windows.h>
#endif // !WIN32


#if defined WIN32
#ifndef TEXT
#define __TEXT(str) L##str
#define TEXT(str) __TEXT(str)
#endif
#ifndef TCHAR
#define TCHAR wchar_t
#endif

#else
#ifndef TEXT
#define TEXT(str) str
#endif
#ifndef TEXT2
#define TEXT2(str) str
#endif
#ifndef TCHAR
#define TCHAR char
#endif
#endif

#if defined DEBUG
#undef debug

#if defined WIN32 && defined ENABLE_WIN32
#define _windowsDebug(msg); SimpleLog::displayWindowsDebug(msg, TEXT(__FILE__), __LINE__);
#else
#define _windowsDebug(msg);
#endif

#define debug(code); code
#define _error(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Error, TEXT(__FILE__), __LINE__);
#define _log(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Info, TEXT(__FILE__), __LINE__);
#define _warn(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Warning, TEXT(__FILE__), __LINE__);
#define _assert(condition); if (!(condition)) SimpleLog::callErrorHandler(TEXT( "Assertion failed : "#condition ), SimpleLog::MessageSeverity::Error, TEXT(__FILE__), __LINE__);

#else
#undef debug
#define debug(code);
#define _log(msg);
#define _warn(msg);
#define _error(msg);
#define _windowsDebug(msg);
#define _assert(condition);
#endif

template<typename T>
class SimpleLogT {
public:
	SimpleLogT();
	~SimpleLogT();

	enum class MessageSeverity : unsigned char {
		Error,
		Warning,
		Info
	};

	enum class MessageColor : unsigned char {
		Red = 0xC,
		Yellow = 0xE,
		Green = 0xA,
		White = 0xF
	};


	static void errorHandler( const T * message, MessageSeverity severity = MessageSeverity::Error, const T * fileName = TEXT( "" ), unsigned int lineNumber = 0 );

	static void callErrorHandler(
		const T * message,
		MessageSeverity severity = MessageSeverity::Error,
		const T * fileName = TEXT( "" ),
		unsigned int lineNumber = 0
	);



	///@brief Set the error handler to be called
	///@param msg Message to be displayed
	///@param 
	static void setErrorHandler( void( *errorHandlerFn ) (
		const T * msg,
		MessageSeverity severity,
		const T * file,
		unsigned int line ) );

	static void setConsoleColor( MessageColor color = MessageColor::White );

#if defined WIN32 && defined ENABLE_WIN32
	static void displayWindowsDebug( const T * message, const T * fileName, unsigned int lineNumber );
	static const T * getWindowsLastError();
#endif

	///@brief Fill a char * buffer with the current time
	///@param strBuffer Buffer to be filled
	///@param bufferSize size of the buffer
	static void getTimeStr( T * strBuffer, size_t bufferSize );


protected:
	static void( *mErrorHandlerFn ) (
		const T *,
		MessageSeverity,
		const T *,
		unsigned int );

private:


};

using SimpleLog = SimpleLogT<TCHAR>;


#include "SimpleLog.hpp"