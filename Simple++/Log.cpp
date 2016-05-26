#include "Log.h"

std::chrono::high_resolution_clock::time_point Log::startTime;
std::chrono::high_resolution_clock::time_point Log::endTime;

void(*Log::mErrorHandlerFn)(
	const String &,
	MessageSeverity,
	const String &,
	unsigned int) = &Log::errorHandler;



Log::Log(void){
}

Log::~Log(void){
}


void Log::displayError(const String & message){
	Log::callErrorHandler(message, MessageSeverity::Error);
}


void Log::displayWarning(const String & message){
	Log::callErrorHandler(message, MessageSeverity::Warning);
}

void Log::displayLog(const String & message){
	Log::callErrorHandler(message, MessageSeverity::Info);
}

void Log::startChrono(){
	Log::startTime = std::chrono::high_resolution_clock::now();
}

void Log::stopChrono() {
	Log::endTime = std::chrono::high_resolution_clock::now();
}

void Log::displayChrono(const String & text){
	displayLog(text + " : " + (std::chrono::duration_cast<std::chrono::duration<double>>(Log::endTime - Log::startTime).count() * 1000.0) + " ms");
}


void Log::errorHandler(const String & message, MessageSeverity severity /*= MessageSeverity::Error*/, const String & fileName /*= ""*/, unsigned int lineNumber /*= 0*/){
	//Cast the time into a standard C time
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	char timeBuffer[100];
	std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &timeinfo);

	switch (severity){
		case MessageSeverity::Error:
#if LOG_SEVERITY <= 3 || !defined LOG_SEVERITY
			setConsoleColor(MessageColor::Red);
			Log::Out << "[ " << timeBuffer << " ] Error : ";
			_printMessage(message.toCString(), fileName.toCString(), lineNumber);
			setConsoleColor();
#endif
		break;
		case MessageSeverity::Info:
#if LOG_SEVERITY <= 1 || !defined LOG_SEVERITY


			setConsoleColor(MessageColor::White);
			Log::Out << "[ " << timeBuffer << " ] Info : ";
			_printMessage(message.toCString(), fileName.toCString(), lineNumber);
			//setConsoleColor();
#endif
		break;
		case MessageSeverity::Warning:
#if LOG_SEVERITY <= 2 || !defined LOG_SEVERITY

		

			setConsoleColor(MessageColor::Yellow);
			Log::Out << "[ " << timeBuffer << " ] Warning : ";
			_printMessage(message.toCString(), fileName.toCString(), lineNumber);
			setConsoleColor();
		break;
#endif
	}
}


void Log::setErrorHandler(void(*errorHandlerFn) (const String &, MessageSeverity, const String &, unsigned int)){
	Log::mErrorHandlerFn = errorHandlerFn;
}

void Log::callErrorHandler(const String & message, MessageSeverity severity /*= MessageSeverity::Error*/, const String & fileName /*= ""*/, unsigned int lineNumber /*= 0 */){
	Log::mErrorHandlerFn(message, severity, fileName, lineNumber);
}

#ifdef WIN32
void Log::displayWindowsDebug(const String & message, const String & fileName, unsigned int lineNumber){
	if (GetLastError()){
		Log::callErrorHandler(message + " : Code [" + GetLastError() + "] : " + Log::getWindowsLastError(), Log::MessageSeverity::Error, fileName, lineNumber);
	}
}
#endif
