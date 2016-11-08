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

#ifdef WIN32
#include <windows.h>
#endif // !WIN32




#if defined DEBUG
#undef debug
#define debug(code); code
#define _error(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Error, __FILE__, __LINE__);
#define _log(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Info, __FILE__, __LINE__);
#define _warn(msg); SimpleLog::callErrorHandler(msg, SimpleLog::MessageSeverity::Warning, __FILE__, __LINE__);
#define _assert(condition); if (!(condition)) SimpleLog::callErrorHandler("Assertion failed : "#condition, SimpleLog::MessageSeverity::Error, __FILE__, __LINE__);
#ifdef WIN32
#define _windowsDebug(msg); SimpleLog::displayWindowsDebug(msg, __FILE__, __LINE__);
#else	
#define _windowsDebug(msg);
#endif
#else
#undef debug
#define debug(code);
#define _log(msg);
#define _warn(msg);
#define _error(msg);
#define _windowsDebug(msg);
#define _assert(condition);
#endif


class SimpleLog {
public:
	SimpleLog();
	~SimpleLog();

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


	///@brief retrieve the out stream (by default cout)
	///@return out stream
	static std::ostream & getOutStream();

	///@brief set the output stream
	///@param stream Stream to be used to output the log messages
	static void setOutStream( std::ostream * stream );

	static void errorHandler(
		const char * message,
		MessageSeverity severity = MessageSeverity::Error,
		const char * fileName = "",
		unsigned int lineNumber = 0);

	static void callErrorHandler(
		const char *  message,
		MessageSeverity severity = MessageSeverity::Error,
		const char *  fileName = "",
		unsigned int lineNumber = 0
		);

	static void setConsoleColor(MessageColor color = MessageColor::White);

#ifdef WIN32
	static void displayWindowsDebug(const char * message, const char * fileName, unsigned int lineNumber);
	static const char * getWindowsLastError();
#endif

protected:

	static void _printMessage(const char * message, const char * fileName, unsigned int lineNumber);

	static void(*mErrorHandlerFn) (
		const char *,
		MessageSeverity,
		const char *,
		unsigned int);

private:
	static std::ostream * Out;


};

