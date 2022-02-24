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
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif // !WIN32


#if defined WIN32
#if defined WIN32_WSTRING
#if !defined TEXT
#define __TEXT(str) L##str
#define TEXT(str) __TEXT(str)
#endif

#ifndef TCHAR
#define TCHAR wchar_t
#endif
#else
#if defined TEXT
#undef TEXT
#undef __TEXT
#define __TEXT(str) #str
#define TEXT(str) __TEXT(str)
#endif

#ifndef TCHAR
#define TCHAR char
#endif
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
#define _error(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Error, SimpleLog::MessageColor::Red, TEXT(__FILE__), __LINE__);
#define _log(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Info, SimpleLog::MessageColor::White, TEXT(__FILE__), __LINE__);
#define _warn(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Warning, SimpleLog::MessageColor::Yellow, TEXT(__FILE__), __LINE__);
#define _assert(condition); if (!(condition)) SimpleLog::callErrorHandler(TEXT( "Assertion failed : "#condition ), SimpleLog::MessageSeverity::Error, SimpleLog::MessageColor::Red, TEXT(__FILE__), __LINE__);

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
	static constexpr unsigned int FILENAME_MAX_SIZE = 20;

	SimpleLogT();
	~SimpleLogT();


	enum class MessageSeverity : unsigned char {
		Error,
		Warning,
		Info,
		Verbose
	};

	enum class MessageColor : unsigned char {
		Red = 0xC,
		Yellow = 0xE,
		Green = 0xA,
		LightCyan = 0xB,
		White = 0xF,
		Gray = 0x8
	};


	static void errorHandler( const T * message, typename SimpleLogT<T>::MessageSeverity severity = typename SimpleLogT<T>::MessageSeverity::Error, typename SimpleLogT<T>::MessageColor color = typename SimpleLogT<T>::MessageColor::Red, unsigned char indent = 0, const TCHAR * fileName = NULL, unsigned int lineNumber = 0 );

	static void callErrorHandler(
		const T * message,
		typename SimpleLogT<T>::MessageSeverity severity = typename SimpleLogT<T>::MessageSeverity::Error,
		typename SimpleLogT<T>::MessageColor color = typename SimpleLogT<T>::MessageColor::Red,
		const TCHAR * fileName = NULL,
		unsigned int lineNumber = 0
	);



	///@brief Set the error handler to be called
	///@param msg Message to be displayed
	///@param 
	static void setErrorHandler( void( *errorHandlerFn ) (
		const T * msg,
		typename SimpleLogT<T>::MessageSeverity severity,
		typename SimpleLogT<T>::MessageColor color,
		unsigned char indent,
		const TCHAR * file,
		unsigned int line ) );

	static void setConsoleColor( typename SimpleLogT<T>::MessageColor color = typename SimpleLogT<T>::MessageColor::White );

#if defined WIN32 && defined ENABLE_WIN32
	static void displayWindowsDebug( const T * message, const TCHAR * fileName, unsigned int lineNumber );
	static size_t getWindowsLastError( T * messageBuffer, size_t bufferSize );
#endif

	///@brief Fill a char * buffer with the current time
	///@param strBuffer Buffer to be filled
	///@param bufferSize size of the buffer
	template<typename C>
	static void getTimeStr( C * strBuffer, size_t bufferSize );
	static void getTimeStr( char * strBuffer, size_t bufferSize );
	static void getTimeStr( wchar_t * strBuffer, size_t bufferSize );


	///@brief Print a message to the Console.
	///@param messageBuffer Message to be printed.
	template<typename C>
	static void printMessage( const C * messageBuffer );
	static void printMessage( const char * messageBuffer );
	static void printMessage( const wchar_t * messageBuffer );

	///@brief Print a char to the Console.
	///@param c Char to be printed.
	template<typename C>
	static void printChar( const C c );
	static void printChar( const char c );
	static void printChar( const wchar_t c );

	template<typename C>
	static void endLine(const C* c);
	static void endLine(const char* c);
	static void endLine(const wchar_t* c);

	static void increaseIndent();
	static void lowerIndent();

protected:
	static void( *mErrorHandlerFn ) (
		const T *,
		MessageSeverity,
		MessageColor,
		unsigned char,
		const TCHAR *,
		unsigned int );

private:
	template<typename C>
	static void parseMessage( C * buffer, int bufferSize, C * timeBuffer, const C * fileName, unsigned int lineNumber );
	static void parseMessage( char * buffer, int bufferSize, char * timeBuffer, const char * fileName, unsigned int lineNumber );
	static void parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer, const wchar_t * fileName, unsigned int lineNumber );

	template<typename C>
	static void parseMessage( C * buffer, int bufferSize, C * timeBuffer );
	static void parseMessage( char * buffer, int bufferSize, char * timeBuffer );
	static void parseMessage( wchar_t * buffer, int bufferSize, wchar_t * timeBuffer );


	template<typename O, typename I>
	static void convertMessage( O * outputBuffer, const I * inputBuffer, size_t bufferSize );

	template<typename O, typename I>
	static void convertFileName( O * outputBuffer, const I * inputBuffer, size_t bufferSize );

	static unsigned char indent;
};

using SimpleLog = SimpleLogT<TCHAR>;


#include "SimpleLog.hpp"