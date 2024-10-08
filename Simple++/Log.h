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
#undef DEBUG_SPP


#if defined WIN32 && defined ENABLE_WIN32
#define WINDOWS_INFO_SPP(msg); Log::displayWindowsDebug(msg, TEXT( __FILE__ ), __LINE__);
#else
#define WINDOWS_INFO_SPP(msg);
#endif


#define DEBUG_SPP(code); code
#define ERROR_SPP(msg); Log::displayError( StringASCII(msg) );
#define WARNING_SPP(msg); Log::displayWarning( StringASCII(msg) );
#define INFO_SPP(msg); Log::displayLog( StringASCII(msg) );
#define VERBOSE_SPP(msg); Log::displayVerbose( StringASCII(msg) );

#define ASSERT_SPP(condition); if (!(condition)) Log::displayError(TEXT( "Assertion Failed! : ("#condition") => false" ));
#define ASSERT_STR_SPP(condition,msg); if (!(condition)) Log::displayError(TEXT( "Assertion Failed! : "#msg ));

#else
#undef DEBUG_SPP
#define DEBUG_SPP( ... );
#define INFO_SPP( ... );
#define VERBOSE_SPP( ... );
#define WARNING_SPP( ... );
#define ERROR_SPP( ... );
#define WINDOWS_INFO_SPP( ... );
#define ASSERT_SPP( ... );
#define ASSERT_STR_SPP( ... );

#endif

#include "String.h"
#include "Time/Time.h"
#include "Vector.h"
#include "Time/TimePoint.h"
#include "Time/Date.h"
#include "OS/Path.h"
#include "IO/FileStream.h"

template<typename T>
class LogHandlerT {
public:
	virtual ~LogHandlerT() = default;

	virtual void message( const BasicString<T>& logTitle,
						  const BasicString<T>& logMessage,
						  typename SimpleLogT<T>::MessageSeverity severity,
						  typename SimpleLogT<T>::MessageColor color
	) = 0;

	virtual void startStep( const BasicString<T>& logTitle,
							const BasicString<T>& logMessage
	) = 0;

	virtual void endStep( const BasicString<T>& logTitle,
						  const BasicString<T>& logMessage,
						  typename SimpleLogT<T>::MessageColor color
	) = 0;

	virtual void increaseIndent() = 0;
	virtual void decreaseIndent() = 0;

};

using LogHandler = LogHandlerT<char>;

template<typename T>
class LogDefaultHandlerT : public LogHandlerT<T> {
public:
	~LogDefaultHandlerT();

	virtual void message( const BasicString<T>& logTitle,
						  const BasicString<T>& logMessage,
						  typename SimpleLogT<T>::MessageSeverity severity,
						  typename SimpleLogT<T>::MessageColor color
	) override;

	virtual void startStep( const BasicString<T>& logTitle,
							const BasicString<T>& logMessage
	) override;

	virtual void endStep( const BasicString<T>& logTitle,
						  const BasicString<T>& logMessage,
						  typename SimpleLogT<T>::MessageColor color
	) override;

	virtual void increaseIndent() override;
	virtual void decreaseIndent() override;

	///@brief	Set an output file path to write the resulting logs into a file.
	void setOutFilePath( const OS::Path & outFilePath );

	///@brief	Sync the filestream.
	void sync();

	void setSTDOut( bool bSTDOut );
	void setFileOut( bool bFileOut );


private:
	int indent{ 0 };
	Vector<Time::TimePointMS> stepStartTimeStack;

	bool bSTDOut{ false };
	bool bFileOut{ false };

	IO::FileStream* fileStream{ NULL };
};

using LogDefaultHandler = LogDefaultHandlerT<char>;


template<typename T>
class LogT : public SimpleLogT<T> {
public:
	using SimpleLogT<T>::MessageSeverity;
	using SimpleLogT<T>::MessageColor;

	LogT( void );
	~LogT( void );

	void addHandler( LogHandlerT<T>* handler );
	void removeHandler( LogHandlerT<T>* handler );

	void removeDefaultHandler();

	void callOnMessage( const BasicString<T>& logTitle,
						const BasicString<T>& logMessage,
						typename SimpleLogT<T>::MessageSeverity severity,
						typename SimpleLogT<T>::MessageColor color );

	void callOnStartStep( const BasicString<T>& logTitle,
						  const BasicString<T>& logMessage );

	void callOnEndStep( const BasicString<T>& logTitle,
						const BasicString<T>& logMessage,
						typename SimpleLogT<T>::MessageColor color );

	void callOnIncreaseIndent();
	void callOnDecreaseIndent();

	void setDisplayError( bool bDisplayError );
	void setDisplayWarning( bool bDisplayWarning );
	void setDispalyInfo( bool bDisplayInfo );
	void setDisplayVerbose( bool bDisplayVerbose );

	void _displayMessage( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename SimpleLogT<T>::MessageSeverity severity, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::Gray );

	void _startStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage );
	void _endStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename SimpleLogT<T>::MessageColor messageColor );



	/**
		* @brief 	Display a log message even if we are in debug build or not.
		* @param 	text	Text to display.
		* @param	messageColor Color to be used.
		*/
	static void displayVerbose( const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::Gray );
	static void displayVerbose( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::Gray );

	/**
		* @brief 	Display a log message even if we are in debug build or not.
		* @param 	text	Text to display.
		* @param	messageColor Color to be used.
		*/
	static void displayLog( const BasicString<T>& text, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::White );
	static void displayLog( const BasicString<T>& logTitle, const BasicString<T>& logMessage, typename LogT<T>::MessageColor messageColor = LogT<T>::MessageColor::White );


	/**
	* @brief 	Display a success log message even if we are in debug build or not.
	* @param 	text	Text to display.
	*/
	static void displaySuccess( const BasicString<T>& text );
	static void displaySuccess( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
		* @brief 	Display a warning message even if we are in debug build or not.
		* @param 	text	Text to display.
		*/
	static void displayWarning( const BasicString<T>& text );
	static void displayWarning( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
		* @brief 	Display a error message even if we are in debug build or not.
		* @param 	text	Text to display.
		*/
	static void displayError( const BasicString<T>& text );
	static void displayError( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
	 * @brief Display a special message representing the opening of a new step & increase the indent.
	 * @param text Text to be displayed
	 */
	static void startStep( const BasicString<T>& text );
	static void startStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
	 * @brief Display a special message representing the ending of a new step & lower the indent.
	 * @param text Text to be displayed
	 */
	static void endStep( const BasicString<T>& text );
	static void endStep( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
	 * @brief Display a special message representing the success ending of a new step & lower the indent.
	 * @param text Text to be displayed
	 */
	static void endStepSuccess( const BasicString<T>& text );
	static void endStepSuccess( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
	 * @brief Display a special message representing the failure ending of a new step & lower the indent.
	 * @param text Text to be displayed
	 */
	static void endStepFailure( const BasicString<T>& text );
	static void endStepFailure( const BasicString<T>& logTitle, const BasicString<T>& logMessage );

	/**
	 * @brief Display a new line.
	 */
	static void displayNewLine();

	static void increaseIndent();
	static void lowerIndent();

	const LogDefaultHandlerT<T> & getDefaultHandler() const;
	LogDefaultHandlerT<T> & getDefaultHandler();


#if defined WIN32 && defined ENABLE_WIN32
	static void displayWindowsDebug( const BasicString<T>& message, const TCHAR* fileName, unsigned int lineNumber );
#endif


	static LogT<T>* getInstance();
private:
	static LogT<T> INSTANCE;

	LogDefaultHandlerT<T> defaultHandler;

	Vector<LogHandlerT<T>*> handlerVector;

	bool bDisplayError{ true };
	bool bDisplayWarning{ true };
	bool bDisplayInfo{ true };
	bool bDisplayVerbose{ true };
};

using Log = LogT<char>;


#include "Log.hpp"


