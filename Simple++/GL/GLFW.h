///@file GLFW.h
///@brief Handler for GLFW
///@author Cl�ment Gerber
///@date 15/12/16 (DMY)

#pragma once

#include "../BuildConfig.h"
#ifdef _UI

#include "BasicGL.h"

//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../Log.h"

#if defined DEBUG
#define glfwError(err, description); GLFW::callError(err, description);
#else
#define glfwError(err, description);
#endif


namespace GLFW {
	///@see http://www.glfw.org/docs/latest/group__errors.html
	enum class Error : unsigned int {
		NotInitialized = GLFW_NOT_INITIALIZED,
		NoContext = GLFW_NO_CURRENT_CONTEXT,
		InvalidEnum = GLFW_INVALID_ENUM,
		InvalidValue = GLFW_INVALID_VALUE,
		OutOfMemory = GLFW_OUT_OF_MEMORY,
		APIUnavailable = GLFW_API_UNAVAILABLE,
		VersionUnavailable = GLFW_VERSION_UNAVAILABLE,
		PlatformError = GLFW_PLATFORM_ERROR,
		FormatUnavailable = GLFW_FORMAT_UNAVAILABLE,
		NoWindowContext = GLFW_NO_WINDOW_CONTEXT
	};


	///@brief Get if GLFW is already loaded or not
	bool isLoaded();

	///@brief Get an error code and return the string associated.
	///@param error Error code
	///@return StringASCII representing the error.
	const StringASCII & errorToString( Error error );

	///@brief Static error callback called when an error occurs
	///@param Error code (Can be casted freely into an Error)
	///@param description Additional text for the error.
	void errorCallbackDefault( Error error, const StringASCII & description );

	///@brief Called when the object is gonna be loaded
	///@return True on success, False otherwise.
	bool load();

	///@brief Called when the object is gonna be unloaded
	///@return True on success, False otherwise.
	bool unload();

	///@brief Call the error handler to display an error
	///@param error Type of the error
	///@param description Additional StringASCII 
	void callError( Error error, const StringASCII & description );




	///@brief DO NOT USE THIS
	void _error_callback( int error, const char* description );
}


#endif



