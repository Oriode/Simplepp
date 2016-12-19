#include "GLFWWindow.h"

#ifdef _UI

namespace GLFW {

	// Map of created window (i mean loaded)
	Map< GLFWwindow *, GLFW::Window * > Window::createdWindowMap;
	// This will handle the actually on focus window created, if none, NULL
	Window * Window::actuallyOnFocusWindow = NULL;
	// This will handle the actually on mouse over window created, if none, NULL
	Window * Window::actuallyOnMouseOver = NULL;
	

	Window::Window( VideoMode videoMode ) :
		videoMode( videoMode ),
		glfwCursor(NULL)
	{
		reset();


	}


	void Window::setWindowed() {
		this -> videoMode = VideoMode::Windowed;
		this -> glfwMonitor = NULL;
		if ( isLoaded() ) {
			glfwSetWindowMonitor( this -> glwfWindow, NULL, 0, 0, this -> size.x, this -> size.y, 0 );
		}
	}


	void Window::setBorderless( GLFWmonitor * monitor ) {
		this -> videoMode = VideoMode::FullscreenBorderless;
		this -> glfwMonitor = monitor;
		if ( isLoaded() ) {
			if ( this -> glfwMonitor == NULL ) {
				this -> glfwMonitor = glfwGetPrimaryMonitor();

				if ( this -> glfwMonitor == NULL ) {
					glfwError( GLFW::Error::APIUnavailable, "No Monitor has been founded." );
					return;
				}
			}
			const GLFWvidmode * mode = glfwGetVideoMode( this -> glfwMonitor );
			glfwSetWindowMonitor( this -> glwfWindow, this -> glfwMonitor, 0, 0, mode -> width, mode -> height, mode -> refreshRate );
		}

	}


	void Window::setFullscreen( GLFWmonitor * monitor, Math::Vec2<unsigned int> & size, unsigned int refreshRate ) {
		this -> videoMode = VideoMode::Fullscreen;
		this -> glfwMonitor = monitor;
		this -> size = size;
		this -> refreshRate = refreshRate;
		if ( isLoaded() ) {
			if ( this -> glfwMonitor == NULL ) {
				this -> glfwMonitor = glfwGetPrimaryMonitor();

				if ( this -> glfwMonitor == NULL ) {
					glfwError( GLFW::Error::APIUnavailable, "No Monitor has been founded." );
					return;
				}
			}
			glfwSetWindowMonitor( this -> glwfWindow, this -> glfwMonitor, 0, 0, this -> size.x, this -> size.y, this -> refreshRate );
		}

	}


	void Window::setIcon( const Graphic::Texture<unsigned char> * icon ) {
		delete this -> iconLoaded;
		this -> iconLoaded = NULL;
		this -> icon = icon;
		if ( isLoaded() ) {
			if ( this -> icon ) {

				if ( this -> icon -> getFormat() != Graphic::Format::RGBA ) {
					if ( this -> icon == this -> iconLoaded ) {
						Graphic::Texture<unsigned char> * imageRBA = new Graphic::Texture<unsigned char>( this -> iconLoaded -> getMipmap(0).toFormat( Graphic::Format::RGBA) );
						delete this -> iconLoaded;
						this -> iconLoaded = imageRBA;
					} else {
						glfwError( GLFW::Error::InvalidValue, "Image is not RGBA 8 bits" );
						return;
					}
				}

				const Vector<Graphic::ImageT<unsigned char> *> & mipmapVector( this -> icon -> getMipmapVector() );

				GLFWimage * glfwImages = new GLFWimage[mipmapVector.getSize()];

				for ( unsigned int i( 0 ); i < mipmapVector.getSize(); i++ ) {
					glfwImages[i].width = mipmapVector[i] -> getSize().x;
					glfwImages[i].height = mipmapVector[i] -> getSize().y;
					glfwImages[i].pixels = const_cast<unsigned char *>(mipmapVector[i] -> getDatas());
				}

				glfwSetWindowIcon( this -> glwfWindow, mipmapVector.getSize(), glfwImages );
				delete[] glfwImages;
			} else {
				glfwSetWindowIcon( this -> glwfWindow, 0, NULL );
			}
			
		}
	}


	const Graphic::Texture<unsigned char> * Window::getIcon() const {
		return this -> icon;
	}

	void Window::setCursor( const Graphic::ImageT<unsigned char> * cursor, const Math::Vec2<unsigned int> & pos ) {
		assert( GLFW::isLoaded() );

		GLFWimage image;
		image.width = cursor -> getSize().x;
		image.height = cursor -> getSize().y;
		image.pixels = const_cast< unsigned char* >( cursor -> getDatas() );

		glfwDestroyCursor( this -> glfwCursor );
		this -> glfwCursor = glfwCreateCursor( &image, pos.x, pos.y );

		if ( isLoaded() ) {
			glfwSetCursor( this -> glwfWindow, this -> glfwCursor );
		}
	}


	void Window::setCursorMode( CursorMode cursorMode ) {
		this -> cursorMode = cursorMode;
		if ( isLoaded() ) {
			glfwSetInputMode( this -> glwfWindow, GLFW_CURSOR, unsigned int( cursorMode ) );
		}
	}


	Window::CursorMode Window::getCursorMode() const {
		return this -> cursorMode;
	}

	void Window::setSize( const Math::Vec2<unsigned int> & size ) {
		this -> size = size;
		if ( isLoaded() ) {
			glfwSetWindowSize( this -> glwfWindow, this -> size.x, this -> size.y );
		}
	}

	void Window::setTitle( const UTF8String & title ) {
		this -> title = title;
		if ( isLoaded() ) {
			glfwSetWindowTitle( this -> glwfWindow, this -> title.getData() );
		}
	}

	Window::~Window() {
		onUnload();
	}

	void Window::reset() {
		this -> mouseHover = false;

		this -> icon = NULL;
		this -> iconLoaded = NULL;
		this -> videoMode = VideoMode::Windowed;
		this -> size.x = 800;
		this -> size.y = 600;

		static UTF8String defaultTitle( "Simple++ Window" );
		this -> title = defaultTitle;
		this -> cursorMode = CursorMode::Normal;

		this -> resizable = true;
		this -> visible = true;
		this -> decorated = true;
		this -> focused = true;
		this -> autoIconify = true;
		this -> alwaysOnTop = false;
		this -> maximized = false;

		this -> redBits = 8;
		this -> greenBits = 8;
		this -> blueBits = 8;
		this -> alphaBits = 8;
		this -> depthBits = 24;
		this -> stencilBits = 8;


		this -> accumulationRedBits = 0;
		this -> accumulationGreenBits = 0;
		this -> accumulationBlueBits = 0;
		this -> accumulationAlphaBits = 0;

		this -> nbAuxiliaryBuffers = 0;
		this -> nbSamples = 0;

		this -> refreshRate = -1;
		this -> stereo = false;
		this -> SRGBCapable = false;
		this -> doubleBuffer = true;
		this -> clientAPI = ClientAPI::OpenGL;
		this -> contextAPI = ContextCreateAPI::Native;
		this -> contextMajorVersion = 1;
		this -> contextMinorVersion = 0;
		this -> robustness = Robustness::NoRobustness;
		this -> contextReleaseBehavior = ContextReleaseBehavior::Default;
		this -> openGLFowardCompatible = false;
		this -> openGLDebug = false;
		this -> openGLProfile = OpenGLProfile::Any;

	}


	

	UTF8String Window::getClipboardString() const {
		assert( isLoaded() );
		return UTF8String( glfwGetClipboardString( this -> glwfWindow ) );
	}


	void Window::setClipboardString( const UTF8String & string ) {
		assert( isLoaded() );
		glfwSetClipboardString( this -> glwfWindow , string.getData() );
	}


	bool Window::isMouseHover() const {
		return this -> mouseHover;
	}

	String & Window::key2String( Key key ) {
		class KeyStrMap {
		public:
			KeyStrMap() {
				keyStrMap.insert( Key::Unknown, "Unknown" );
				keyStrMap.insert( Key::Space, "Space" );
				keyStrMap.insert( Key::Apostrophe, '\'' );
				keyStrMap.insert( Key::Comma, ',' );
				keyStrMap.insert( Key::Minus, '-' );
				keyStrMap.insert( Key::Slash, '/' );
				keyStrMap.insert( Key::Number0, '0' );
				keyStrMap.insert( Key::Number1, '1' );
				keyStrMap.insert( Key::Number2, '2' );
				keyStrMap.insert( Key::Number3, '3' );
				keyStrMap.insert( Key::Number4, '4' );
				keyStrMap.insert( Key::Number5, '5' );
				keyStrMap.insert( Key::Number6, '6' );
				keyStrMap.insert( Key::Number7, '7' );
				keyStrMap.insert( Key::Number8, '8' );
				keyStrMap.insert( Key::Number9, '9' );
				keyStrMap.insert( Key::Semicolon, ';' );
				keyStrMap.insert( Key::Equal, '=' );
				keyStrMap.insert( Key::A, 'A' );
				keyStrMap.insert( Key::B, 'B' );
				keyStrMap.insert( Key::C, 'C' );
				keyStrMap.insert( Key::D, 'D' );
				keyStrMap.insert( Key::E, 'E' );
				keyStrMap.insert( Key::F, 'F' );
				keyStrMap.insert( Key::G, 'G' );
				keyStrMap.insert( Key::H, 'H' );
				keyStrMap.insert( Key::I, 'I' );
				keyStrMap.insert( Key::J, 'J' );
				keyStrMap.insert( Key::K, 'K' );
				keyStrMap.insert( Key::L, 'L' );
				keyStrMap.insert( Key::M, 'M' );
				keyStrMap.insert( Key::N, 'N' );
				keyStrMap.insert( Key::O, 'O' );
				keyStrMap.insert( Key::P, 'P' );
				keyStrMap.insert( Key::Q, 'Q' );
				keyStrMap.insert( Key::R, 'R' );
				keyStrMap.insert( Key::S, 'S' );
				keyStrMap.insert( Key::T, 'T' );
				keyStrMap.insert( Key::U, 'U' );
				keyStrMap.insert( Key::V, 'V' );
				keyStrMap.insert( Key::W, 'W' );
				keyStrMap.insert( Key::X, 'X' );
				keyStrMap.insert( Key::Y, 'Y' );
				keyStrMap.insert( Key::Z, 'Z' );
				keyStrMap.insert( Key::LeftBracket, '[' );
				keyStrMap.insert( Key::BackSlash, '\\' );
				keyStrMap.insert( Key::RightBracket, ']' );
				keyStrMap.insert( Key::GraveAccent, '`' );
				keyStrMap.insert( Key::World1, "World 1" );
				keyStrMap.insert( Key::World2, "World 2" );
				keyStrMap.insert( Key::Escape, "Escape" );
				keyStrMap.insert( Key::Enter, "Enter" );
				keyStrMap.insert( Key::Tab, "Tab" );
				keyStrMap.insert( Key::BackSpace, "Backspace" );
				keyStrMap.insert( Key::Insert, "Insert" );
				keyStrMap.insert( Key::Delete, "Delete" );
				keyStrMap.insert( Key::Right, "Right" );
				keyStrMap.insert( Key::Left, "Left" );
				keyStrMap.insert( Key::Right, "Right" );
				keyStrMap.insert( Key::Down, "Down" );
				keyStrMap.insert( Key::Up, "Up" );
				keyStrMap.insert( Key::PageUp, "Page Up" );
				keyStrMap.insert( Key::PageDown, "Page Down" );
				keyStrMap.insert( Key::Home, "Home" );
				keyStrMap.insert( Key::End, "End" );
				keyStrMap.insert( Key::CapsLock, "CapsLock" );
				keyStrMap.insert( Key::ScrollLock, "ScrollLock" );
				keyStrMap.insert( Key::NumLock, "NumLock" );
				keyStrMap.insert( Key::PrintScreen, "Print Screen" );
				keyStrMap.insert( Key::Pause, "Pause" );
				keyStrMap.insert( Key::F1, "F1" );
				keyStrMap.insert( Key::F2, "F2" );
				keyStrMap.insert( Key::F3, "F3" );
				keyStrMap.insert( Key::F4, "F4" );
				keyStrMap.insert( Key::F5, "F5" );
				keyStrMap.insert( Key::F6, "F6" );
				keyStrMap.insert( Key::F7, "F7" );
				keyStrMap.insert( Key::F8, "F8" );
				keyStrMap.insert( Key::F9, "F9" );
				keyStrMap.insert( Key::F10, "F10" );
				keyStrMap.insert( Key::F11, "F11" );
				keyStrMap.insert( Key::F12, "F12" );
				keyStrMap.insert( Key::F13, "F13" );
				keyStrMap.insert( Key::F14, "F14" );
				keyStrMap.insert( Key::F15, "F15" );
				keyStrMap.insert( Key::F16, "F16" );
				keyStrMap.insert( Key::F17, "F17" );
				keyStrMap.insert( Key::F18, "F18" );
				keyStrMap.insert( Key::F19, "F19" );
				keyStrMap.insert( Key::F20, "F20" );
				keyStrMap.insert( Key::F21, "F21" );
				keyStrMap.insert( Key::F22, "F122" );
				keyStrMap.insert( Key::F23, "F23" );
				keyStrMap.insert( Key::F24, "F24" );
				keyStrMap.insert( Key::F25, "F25" );
				keyStrMap.insert( Key::Keypad0, "KP0" );
				keyStrMap.insert( Key::Keypad1, "KP1" );
				keyStrMap.insert( Key::Keypad2, "KP2" );
				keyStrMap.insert( Key::Keypad3, "KP3" );
				keyStrMap.insert( Key::Keypad4, "KP4" );
				keyStrMap.insert( Key::Keypad5, "KP5" );
				keyStrMap.insert( Key::Keypad6, "KP6" );
				keyStrMap.insert( Key::Keypad7, "KP7" );
				keyStrMap.insert( Key::Keypad8, "KP8" );
				keyStrMap.insert( Key::Keypad9, "KP9" );
				keyStrMap.insert( Key::KeypadDecimal, "KP." );
				keyStrMap.insert( Key::KeypadDivide, "KP/" );
				keyStrMap.insert( Key::KeypadMultiply, "KP*" );
				keyStrMap.insert( Key::KeypadSubstract, "KP-" );
				keyStrMap.insert( Key::KeypadAdd, "KP+" );
				keyStrMap.insert( Key::KeypadEnter, "KP Enter" );
				keyStrMap.insert( Key::KeypadEqual, "KP=" );
				keyStrMap.insert( Key::LeftShift, "Left Shift" );
				keyStrMap.insert( Key::LeftControl, "Left Control" );
				keyStrMap.insert( Key::LeftAlt, "Left Alt" );
				keyStrMap.insert( Key::LeftSuper, "Left Super" );
				keyStrMap.insert( Key::RightShift, "Right Shift" );
				keyStrMap.insert( Key::RightControl, "Right Control" );
				keyStrMap.insert( Key::RightAlt, "Right Alt" );
				keyStrMap.insert( Key::RightSuper, "Right Super" );
				keyStrMap.insert( Key::Menu, "Menu" );
			}

			Map<Key, String> keyStrMap;
		};

		static KeyStrMap keyMap;
		static String errorStr( "Unknown" );

		String * foundedStr = keyMap.keyStrMap[key];
		if ( foundedStr ) {
			return *foundedStr;
		} else {
			return errorStr;
		}
	}


	String & Window::mouseButton2String( MouseButton mouseButton ) {
		class MouseButtonMap {
		public:
			MouseButtonMap() {
				strMap.insert( MouseButton::Left, "Left Button" );
				strMap.insert( MouseButton::Right, "Right Button" );
				strMap.insert( MouseButton::Middle, "Middle Button" );
				strMap.insert( MouseButton::Button4, "Button 4" );
				strMap.insert( MouseButton::Button5, "Button 5" );
				strMap.insert( MouseButton::Button6, "Button 6" );
				strMap.insert( MouseButton::Button7, "Button 7" );
				strMap.insert( MouseButton::Button8, "Button 8" );
			}
			Map<MouseButton, String> strMap;
		};

		static MouseButtonMap mouseButtonMap;
		static String errorStr( "Unknown" );

		String * foundedStr = mouseButtonMap.strMap[mouseButton];
		if ( foundedStr ) {
			return *foundedStr;
		} else {
			return errorStr;
		}
	}

	bool Window::createContext() {

		assert( GLFW::isLoaded() );

		glfwWindowHint( GLFW_RESIZABLE, (this -> resizable ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_VISIBLE, (this -> visible ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_DECORATED, (this -> decorated ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_FOCUSED, (this -> focused ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_AUTO_ICONIFY, (this -> autoIconify ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_FLOATING, (this -> alwaysOnTop ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_MAXIMIZED, (this -> maximized ) ? GLFW_TRUE : GLFW_FALSE );



		glfwWindowHint( GLFW_ALPHA_BITS, this -> alphaBits );
		glfwWindowHint( GLFW_DEPTH_BITS, this -> depthBits );
		glfwWindowHint( GLFW_STENCIL_BITS, this -> stencilBits );

		glfwWindowHint( GLFW_ACCUM_RED_BITS, this -> accumulationRedBits );
		glfwWindowHint( GLFW_ACCUM_GREEN_BITS, this -> accumulationGreenBits );
		glfwWindowHint( GLFW_ACCUM_BLUE_BITS, this -> accumulationBlueBits );
		glfwWindowHint( GLFW_ACCUM_ALPHA_BITS, this -> accumulationAlphaBits );
		glfwWindowHint( GLFW_AUX_BUFFERS, this -> nbAuxiliaryBuffers );
		glfwWindowHint( GLFW_SAMPLES, this -> nbSamples );
		glfwWindowHint( GLFW_STEREO, (this -> stereo ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_SRGB_CAPABLE, (this -> SRGBCapable ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_DOUBLEBUFFER, (this -> doubleBuffer ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_CLIENT_API, (unsigned int) this -> clientAPI );
		glfwWindowHint( GLFW_CONTEXT_CREATION_API, (unsigned int) this -> contextAPI );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, this -> contextMajorVersion );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, this -> contextMinorVersion );
		glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, (unsigned int) this -> robustness );
		glfwWindowHint( GLFW_CONTEXT_RELEASE_BEHAVIOR, (unsigned int) this -> contextReleaseBehavior );
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, (this -> openGLFowardCompatible ) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, (this -> openGLDebug) ? GLFW_TRUE : GLFW_FALSE );
		glfwWindowHint( GLFW_OPENGL_PROFILE, (unsigned int) this -> openGLProfile );


		if ( this -> videoMode == VideoMode::Windowed ) {
			this -> glfwMonitor = NULL;
		} else {
			if ( this -> glfwMonitor == NULL ) {
				this -> glfwMonitor = glfwGetPrimaryMonitor();

				if ( this -> glfwMonitor == NULL ) {
					glfwError( GLFW::Error::APIUnavailable, "No Monitor has been founded." );
					return false;
				}
			}
		}

		if ( this -> videoMode == VideoMode::FullscreenBorderless ) {
			const GLFWvidmode * mode = glfwGetVideoMode( this -> glfwMonitor );
			glfwWindowHint( GLFW_RED_BITS, mode -> redBits );
			glfwWindowHint( GLFW_GREEN_BITS, mode -> greenBits );
			glfwWindowHint( GLFW_BLUE_BITS, mode -> blueBits );
			glfwWindowHint( GLFW_REFRESH_RATE, mode -> refreshRate );
		} else {
			glfwWindowHint( GLFW_RED_BITS, this -> redBits );
			glfwWindowHint( GLFW_GREEN_BITS, this -> greenBits );
			glfwWindowHint( GLFW_BLUE_BITS, this -> blueBits );
			glfwWindowHint( GLFW_REFRESH_RATE, this -> refreshRate );
		}
		
		this -> glwfWindow = glfwCreateWindow( this -> size.x, 
											   this -> size.y,
											   this -> title.getData(),
											   this -> glfwMonitor, 
											   (sharedWindow && sharedWindow -> isLoaded()) ? sharedWindow -> glwfWindow : NULL );

		if ( glwfWindow == NULL ) {
			glfwError( GLFW::Error::APIUnavailable, "Window creation has failed." );
			return false;
		}
		if ( this -> visible ) {
			GLFW::Window::actuallyOnFocusWindow = this;
			onFocus( true );
		}
		onResize( this -> size );

		glfwSetInputMode( this -> glwfWindow, GLFW_CURSOR, unsigned int( this -> cursorMode ) );

		GLFW::Window::createdWindowMap.insert( this -> glwfWindow, this );

		// Now register all the callbacks
		glfwSetWindowFocusCallback( this -> glwfWindow, _window_focus_callback );
		glfwSetWindowSizeCallback( this -> glwfWindow, _window_size_callback );
		glfwSetKeyCallback( this -> glwfWindow, _key_callback );
		glfwSetCharCallback( this -> glwfWindow, _character_callback );
		glfwSetDropCallback( this -> glwfWindow, _drop_callback );
		glfwSetCursorEnterCallback( this -> glwfWindow, _cursor_enter_callback );
		glfwSetCursorPosCallback( this -> glwfWindow, _cursor_position_callback );
		glfwSetMouseButtonCallback( this -> glwfWindow, _mouse_button_callback );

		if ( this -> glfwCursor ) {
			glfwSetCursor( this -> glwfWindow, this -> glfwCursor );
		}
		setIcon( this -> icon );



		if ( this -> contextMajorVersion > 3 || ( this -> contextMajorVersion == 3 && this -> contextMinorVersion >= 3 ) ) {
			if ( this -> openGLDebug && ( this -> contextMajorVersion > 4 || ( this -> contextMajorVersion == 4 && this -> contextMinorVersion >= 2 ) ) ) {
				if ( glDebugMessageCallback ) {
					glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );

					glDebugMessageCallback( ( GLDEBUGPROC ) glTraceFunction, NULL );

					GLuint unusedIds = 0;
					glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true );

					log( "glDebugMessageCallback registered !" );
				} else {
					glfwError( GLFW::Error::NotInitialized, "glDebugMessageCallback not available" );
				}
			}
			glEnable( GL_CULL_FACE );
			glPatchParameteri( GL_PATCH_VERTICES, 3 );
			glCullFace( GL_BACK );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glDepthFunc( GL_LEQUAL );
			glLineWidth( 2.0f );
		}
		return true;
	}


	bool Window::deleteContext() {
		GLFW::Window::createdWindowMap.eraseIndex( this -> glwfWindow );

		glfwDestroyWindow( this -> glwfWindow );
		glfwDestroyCursor( this -> glfwCursor );
		return true;
	}

	bool Window::onLoad() {
		return createContext();
	}


	bool Window::onUnload() {
		bool r( deleteContext() );
		delete this -> iconLoaded;
		return r;
	}




	bool Window::read( std::fstream * fileStream ) {
		if ( !IO::read( fileStream, &this -> size ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> title ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> resizable ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> visible ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> decorated ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> focused ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> autoIconify ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> alwaysOnTop ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> maximized ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> redBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> greenBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> blueBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> alphaBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> depthBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> stencilBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> accumulationRedBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> accumulationGreenBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> accumulationBlueBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> accumulationAlphaBits ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> nbAuxiliaryBuffers ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> nbSamples ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> refreshRate ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> stereo ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> SRGBCapable ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> doubleBuffer ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> clientAPI ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> contextAPI ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> contextMajorVersion ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> contextMinorVersion ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> robustness ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> contextReleaseBehavior ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> openGLFowardCompatible ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> openGLDebug ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> openGLProfile ) ) {
			reset();
			return false;
		}
		if ( !IO::read( fileStream, &this -> cursorMode ) ) {
			reset();
			return false;
		}
		return true;
	}


	bool Window::write( std::fstream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> size ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> title ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> resizable ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> visible ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> decorated ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> focused ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> autoIconify ) ) 	
			return false;
		if ( !IO::write( fileStream, &this -> alwaysOnTop ) ) 	
			return false;
		if ( !IO::write( fileStream, &this -> maximized ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> redBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> greenBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> blueBits ) ) 	
			return false;
		if ( !IO::write( fileStream, &this -> alphaBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> depthBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> stencilBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> accumulationRedBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> accumulationGreenBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> accumulationBlueBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> accumulationAlphaBits ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> nbAuxiliaryBuffers ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> nbSamples ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> refreshRate ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> stereo ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> SRGBCapable ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> doubleBuffer ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> clientAPI ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> contextAPI ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> contextMajorVersion ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> contextMinorVersion ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> robustness ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> contextReleaseBehavior ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> openGLFowardCompatible ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> openGLDebug ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> openGLProfile ) ) 
			return false;
		if ( !IO::write( fileStream, &this -> cursorMode ) )
			return false;
		return true;
	}


	void Window::onFocus( bool focus ) {
		// Virtual function to be overloaded
	}
	void Window::onResize( const Math::Vec2<unsigned int> & size ) {
		// Virtual function to be overloaded
	}
	void Window::onKey( Key key, EventAction action, unsigned int mods ) {
		// Virtual function to be overloaded
	}

	void Window::onMouseButton( MouseButton mouseButton, EventAction action, unsigned int mods ) {
		// Virtual function to be overloaded
		log( mouseButton2String( mouseButton ) );
	}

	void Window::onText( UTF8String::CodePoint unicodeCodePoint ) {
		// Virtual function to be overloaded
		log( getClipboardString() );
	}

	void Window::onDrop( Vector<UTF8String> filePathsVector ) {
		// Virtual function to be overloaded
	}

	void Window::onMouseEnter( bool entered ) {
		// Virtual function to be overloaded
	}

	void Window::onMouseMove( const Math::Vec2<double> & position ) {
		// Virtual function to be overloaded
	}

	void glTraceFunction( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void * userParam ) {
		switch ( severity ) {
			case GL_DEBUG_SEVERITY_LOW:
				if ( LOG_SEVERITY > 1 ) return;
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				if ( LOG_SEVERITY > 2 ) return;
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				if ( LOG_SEVERITY > 3 ) return;
				break;
			default:
				if ( LOG_SEVERITY > 0 ) return;
				break;
		}

		String severityMsg;
		String typeMsg;
		String sourceMsg;

		switch ( source ) {
			case GL_DEBUG_CATEGORY_API_ERROR_AMD:
			case GL_DEBUG_SOURCE_API:
				{
					sourceMsg = "API";
					break;
				}
			case GL_DEBUG_CATEGORY_APPLICATION_AMD:
			case GL_DEBUG_SOURCE_APPLICATION:
				{
					sourceMsg = "Application";
					break;
				}
			case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				{
					sourceMsg = "Window System";
					break;
				}
			case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				{
					sourceMsg = "Shader Compiler";
					break;
				}
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				{
					sourceMsg = "Third Party";
					break;
				}
			case GL_DEBUG_CATEGORY_OTHER_AMD:
			case GL_DEBUG_SOURCE_OTHER:
				{
					sourceMsg = "Other";
					break;
				}
			default:
				{
					sourceMsg = "Unknown";
					break;
				}
		}
		switch ( type ) {
			case GL_DEBUG_TYPE_ERROR:
				{
					typeMsg = "Error";
					break;
				}
			case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				{
					typeMsg = "Deprecated Behavior";
					break;
				}
			case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				{
					typeMsg = "Undefined Behavior";
					break;
				}
			case GL_DEBUG_TYPE_PORTABILITY_ARB:
				{
					typeMsg = "Portability";
					break;
				}
			case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
			case GL_DEBUG_TYPE_PERFORMANCE:
				{
					typeMsg = "Performance";
					break;
				}
			case GL_DEBUG_CATEGORY_OTHER_AMD:
			case GL_DEBUG_TYPE_OTHER:
				{
					typeMsg = "Other";
					break;
				}
			default:
				{
					typeMsg = "Unknown";
					break;
				}
		}
		switch ( severity ) {
			case GL_DEBUG_SEVERITY_LOW:
				Log::displayLog( "[OpenGL][LOW] [" + sourceMsg + "] [" + typeMsg + "] " + message );
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				Log::displayWarning( "[OpenGL][MEDIUM] [" + sourceMsg + "] [" + typeMsg + "] " + message );
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				Log::displayError( "[OpenGL][HIGH] [" + sourceMsg + "] [" + typeMsg + "] " + message );
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				Log::displayLog( "[OpenGL][LOG] [" + sourceMsg + "] [" + typeMsg + "] " + message );
				break;
			default:
				Log::displayLog( "[OpenGL][INFO] [" + sourceMsg + "] [" + typeMsg + "] " + message );
				break;
		}
	}


	void Window::_window_focus_callback( GLFWwindow * glfwWindow, int focused ) {
		if ( focused ) {
			GLFW::Window ** foundedWindow( GLFW::Window::createdWindowMap[glfwWindow] );
			if ( foundedWindow ) {
				GLFW::Window::actuallyOnFocusWindow = *foundedWindow;
				GLFW::Window::actuallyOnFocusWindow -> focused = true;
				GLFW::Window::actuallyOnFocusWindow -> onFocus( true );
			} else {
				glfwError( GLFW::Error::InvalidValue, "An unknown window has been focused." );
			}
		} else {
			if ( GLFW::Window::actuallyOnFocusWindow ) {
				GLFW::Window::actuallyOnFocusWindow -> focused = false;
				GLFW::Window::actuallyOnFocusWindow -> onFocus( false );
				GLFW::Window::actuallyOnFocusWindow = NULL;
			}
		}
	}

	void Window::_window_size_callback( GLFWwindow * glfwWindow, int width, int height ) {
		GLFW::Window ** foundedWindow( GLFW::Window::createdWindowMap[glfwWindow] );
		if ( foundedWindow ) {
			( *foundedWindow ) -> size.x = width;
			( *foundedWindow ) -> size.y = height;
			( *foundedWindow ) -> onResize( ( *foundedWindow ) -> size );
		} else {
			glfwError( GLFW::Error::InvalidValue, "An unknown window has been resized." );
		}
	}

	void Window::_key_callback( GLFWwindow * glfwWindow, int key, int scancode, int action, int mods ) {
		//assert( GLFW::Window::actuallyOnFocusWindow );
		//GLFW::Window::actuallyOnFocusWindow -> onKey( Key( key ), EventKeyAction( action ), mods );

		if ( GLFW::Window::actuallyOnFocusWindow ) {
			GLFW::Window::actuallyOnFocusWindow -> onKey( Key( key ), EventAction( action ), mods );
		} else {
			glfwError( GLFW::Error::InvalidValue, "An unknown window has received a key event." );
		}
	}

	void Window::_character_callback( GLFWwindow * glfwWindow, unsigned int codepoint ) {
		//assert( GLFW::Window::actuallyOnFocusWindow );
		//GLFW::Window::actuallyOnFocusWindow -> onText( UTF8String::CodePoint( codepoint ) );
		if ( GLFW::Window::actuallyOnFocusWindow ) {
			GLFW::Window::actuallyOnFocusWindow -> onText( UTF8String::CodePoint( codepoint ) );
		} else {
			glfwError( GLFW::Error::InvalidValue, "An unknown window has received a key event." );
		}
	}


	void Window::_drop_callback( GLFWwindow * glfwWindow, int count, const char ** paths ) {
		if ( count <= 0 )
			return;
		GLFW::Window ** foundedWindow( GLFW::Window::createdWindowMap[glfwWindow] );
		if ( foundedWindow ) {
			Vector<UTF8String> filePathVector;
			filePathVector.reserve( count );
			for ( int i( 0 ); i < count; i++ ) {
				filePathVector.push( UTF8String( paths[i] ) );
			}
			( *foundedWindow ) -> onDrop( filePathVector );
		} else {
			glfwError( GLFW::Error::InvalidValue, "An unknown window has recieved a file drop event." );
		}
	}


	void Window::_cursor_enter_callback( GLFWwindow * glfwWindow, int entered ) {
		GLFW::Window ** foundedWindow( GLFW::Window::createdWindowMap[glfwWindow] );
		if ( foundedWindow ) {
			bool b( entered );
			if ( entered ) {
				GLFW::Window::actuallyOnMouseOver = ( *foundedWindow );
			} else {
				GLFW::Window::actuallyOnMouseOver = NULL;
			}
			( *foundedWindow ) -> mouseHover = b;
			( *foundedWindow ) -> onMouseEnter( b );
		} else {
			GLFW::Window::actuallyOnMouseOver = NULL;
			glfwError( GLFW::Error::InvalidValue, "An unknown window has recieved a mouse enter event." );
		}
	}


	void Window::_cursor_position_callback( GLFWwindow * glfwWindow, double xpos, double ypos ) {
		if ( GLFW::Window::actuallyOnMouseOver )
			GLFW::Window::actuallyOnMouseOver -> onMouseMove( Math::Vec2<double>( xpos, ypos ) );
		else {
			GLFW::Window ** foundedWindow( GLFW::Window::createdWindowMap[glfwWindow] );
			if ( foundedWindow ) {
				GLFW::Window::actuallyOnMouseOver = *foundedWindow;
				GLFW::Window::actuallyOnMouseOver -> onMouseMove( Math::Vec2<double>( xpos, ypos ) );
			} else {
				glfwError( GLFW::Error::InvalidValue, "An unknown window has recieved a mouse move event." );
			}
		}
	}


	void Window::_mouse_button_callback( GLFWwindow * glfwWindow, int button, int action, int mods ) {
		assert( GLFW::Window::actuallyOnMouseOver );
		GLFW::Window::actuallyOnMouseOver -> onMouseButton( MouseButton(button), EventAction(action), mods);
	}

}

#endif
