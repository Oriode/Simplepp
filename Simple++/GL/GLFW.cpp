#include "GLFW.h"

#ifdef _UI

 
namespace GLFW {

	bool bLoaded = false;
	void( *errorCallback )( Error, const String & ) = errorCallbackDefault;



	bool isLoaded() {
		return bLoaded;
	}

	const String & errorToString( Error error ) {
		static String errorNotInitialized( "Not Initialized" );
		static String errorNoContext( "No Context" );
		static String errorInvalidEnum( "Invalid Enum" );
		static String errorInvalidValue( "Invalid Value" );
		static String errorOutOfMemory( "Out of Memory" );
		static String errorAPIUnavailable( "API Unavailable" );
		static String errorVersionUnavailable( " Version Unavailable" );
		static String errorPlatformError( "Platform Error" );
		static String errorFormatUnavailable( "Format Unavailable" );
		static String errorNoWindowContext( "No Context Window" );
		static String errorUnknownErrorCode( "Error code unknown" );

		switch ( error ) {
			case Error::NotInitialized:
				return errorNotInitialized;
			case Error::NoContext:
				return errorNoContext;
			case Error::InvalidEnum:
				return errorInvalidEnum;
			case Error::InvalidValue:
				return errorInvalidValue;
			case Error::OutOfMemory:
				return errorOutOfMemory;
			case Error::APIUnavailable:
				return errorAPIUnavailable;
			case Error::VersionUnavailable:
				return errorVersionUnavailable;
			case Error::PlatformError:
				return errorPlatformError;
			case Error::FormatUnavailable:
				return errorFormatUnavailable;
			case Error::NoWindowContext:
				return errorNoWindowContext;
			default:
				return errorUnknownErrorCode;
		}

	}

	void errorCallbackDefault( Error errorCode, const String & description ) {
		error( String( "[GLFW] " ) << '[' << String( errorToString( errorCode ) ) << ']' << ' ' << description );
	}

	void _error_callback( int error, const char * description ) {
		callError( Error( error ), String( description ) );
	}

	bool load() {
		if ( bLoaded )
			return true;
		if ( !glfwInit() ) {
			// Init has failed.
			callError( Error::NotInitialized, String( " Initialization of GLFW has failed :(" ) );
			return false;
		}
		glfwSetErrorCallback( _error_callback );
		bLoaded = true;
		return true;
	}

	bool unload() {
		if ( !bLoaded )
			return true;
		glfwTerminate();
		bLoaded = false;
		return true;
	}


	void callError( Error error, const String & description ) {
		errorCallback( error, description );
	}



}


#endif
