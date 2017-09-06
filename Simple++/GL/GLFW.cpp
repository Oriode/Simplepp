#include "GLFW.h"

#ifdef _UI

 
namespace GLFW {

	bool bLoaded = false;
	void( *errorCallback )( Error, const StringASCII & ) = errorCallbackDefault;



	bool isLoaded() {
		return bLoaded;
	}

	const StringASCII & errorToString( Error error ) {
		static StringASCII errorNotInitialized( "Not Initialized" );
		static StringASCII errorNoContext( "No Context" );
		static StringASCII errorInvalidEnum( "Invalid Enum" );
		static StringASCII errorInvalidValue( "Invalid Value" );
		static StringASCII errorOutOfMemory( "Out of Memory" );
		static StringASCII errorAPIUnavailable( "API Unavailable" );
		static StringASCII errorVersionUnavailable( " Version Unavailable" );
		static StringASCII errorPlatformError( "Platform Error" );
		static StringASCII errorFormatUnavailable( "Format Unavailable" );
		static StringASCII errorNoWindowContext( "No Context Window" );
		static StringASCII errorUnknownErrorCode( "Error code unknown" );

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

	void errorCallbackDefault( Error errorCode, const StringASCII & description ) {
		error( String( TEXT( "[GLFW] " ) ) << TCHAR( '[' ) << String( errorToString( errorCode ) ) << TCHAR( ']' ) << TCHAR( ' ' ) << description );
	}

	void _error_callback( int error, const char * description ) {
		callError( Error( error ), ( description ) );
	}

	bool load() {
		if ( bLoaded )
			return true;
		if ( !glfwInit() ) {
			// Init has failed.
			callError( Error::NotInitialized, String( TEXT( " Initialization of GLFW has failed :(" ) ) );
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


	void callError( Error error, const StringASCII & description ) {
		errorCallback( error, description );
	}



}


#endif
