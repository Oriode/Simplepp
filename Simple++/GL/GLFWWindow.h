///@file GLFWWindow 
///@brief A Window handled by GLFW
///@author Clément Gerber
///@date 16/12/2016 (DMY)

#pragma once

#include "../BuildConfig.h"
#ifdef _UI

#include "GLFW.h"
#include "../UTF8String.h"
#include "../IO/BasicIO.h"
#include "../IO/IO.h"
#include "../Math/Vec2.h"
#include "../Graphic/Texture.h"
#include "../Map.h"

namespace GLFW {

	class Window : public IO::BasicIO, public BasicLoadable {
	public:
		enum class VideoMode {
			Fullscreen,
			FullscreenBorderless,
			Windowed
		};
		enum class ClientAPI : unsigned int {
			OpenGL = GLFW_OPENGL_API,
			OpenGLES = GLFW_OPENGL_ES_API,
			NoAPI = GLFW_NO_API
		};
		enum class ContextCreateAPI : unsigned int {
			Native = GLFW_NATIVE_CONTEXT_API,
			EGL = GLFW_EGL_CONTEXT_API
		};
		enum class Robustness : unsigned int {
			NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
			LoseOnReset = GLFW_LOSE_CONTEXT_ON_RESET,
			NoRobustness = GLFW_NO_ROBUSTNESS
		};
		enum class ContextReleaseBehavior : unsigned int {
			Default = GLFW_ANY_RELEASE_BEHAVIOR,
			Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
			None = GLFW_RELEASE_BEHAVIOR_NONE
		};
		enum class OpenGLProfile : unsigned int {
			Any = GLFW_OPENGL_ANY_PROFILE,
			Compatibility = GLFW_OPENGL_COMPAT_PROFILE,
			Core = GLFW_OPENGL_CORE_PROFILE
		};
		enum class EventAction : unsigned int {
			Press = GLFW_PRESS,
			Repeat = GLFW_REPEAT,
			Release = GLFW_RELEASE,
			Unknown = GLFW_KEY_UNKNOWN
		};
		enum class KeyModifier : unsigned int {
			Shift = GLFW_MOD_SHIFT,
			Control = GLFW_MOD_CONTROL,
			Alt = GLFW_MOD_ALT,
			Super = GLFW_MOD_SUPER
		};

		enum class Key : unsigned int {
			Unknown = GLFW_KEY_UNKNOWN,
			Space = GLFW_KEY_SPACE,
			Apostrophe = GLFW_KEY_APOSTROPHE,
			Comma = GLFW_KEY_COMMA,
			Minus = GLFW_KEY_MINUS,
			Period = GLFW_KEY_PERIOD,
			Slash = GLFW_KEY_SLASH,
			Number0 = GLFW_KEY_0,
			Number1 = GLFW_KEY_1,
			Number2 = GLFW_KEY_2,
			Number3 = GLFW_KEY_3,
			Number4 = GLFW_KEY_4,
			Number5 = GLFW_KEY_5,
			Number6 = GLFW_KEY_6,
			Number7 = GLFW_KEY_7,
			Number8 = GLFW_KEY_8,
			Number9 = GLFW_KEY_9,
			Semicolon = GLFW_KEY_SEMICOLON,
			Equal = GLFW_KEY_EQUAL,
			A = GLFW_KEY_A,
			B = GLFW_KEY_B,
			C = GLFW_KEY_C,
			D = GLFW_KEY_D,
			E = GLFW_KEY_E,
			F = GLFW_KEY_F,
			G = GLFW_KEY_G,
			H = GLFW_KEY_H,
			I = GLFW_KEY_I,
			J = GLFW_KEY_J,
			K = GLFW_KEY_K,
			L = GLFW_KEY_L,
			M = GLFW_KEY_M,
			N = GLFW_KEY_N,
			O = GLFW_KEY_O,
			P = GLFW_KEY_P,
			Q = GLFW_KEY_Q,
			R = GLFW_KEY_R,
			S = GLFW_KEY_S,
			T = GLFW_KEY_T,
			U = GLFW_KEY_V,
			V = GLFW_KEY_V,
			W = GLFW_KEY_W,
			X = GLFW_KEY_X,
			Y = GLFW_KEY_Y,
			Z = GLFW_KEY_Z,
			LeftBracket = GLFW_KEY_LEFT_BRACKET,
			BackSlash = GLFW_KEY_BACKSLASH,
			RightBracket = GLFW_KEY_RIGHT_BRACKET,
			GraveAccent = GLFW_KEY_GRAVE_ACCENT,
			World1 = GLFW_KEY_WORLD_1,
			World2 = GLFW_KEY_WORLD_2,
			Escape = GLFW_KEY_ESCAPE,
			Enter = GLFW_KEY_ENTER,
			Tab = GLFW_KEY_TAB,
			BackSpace = GLFW_KEY_BACKSPACE,
			Insert = GLFW_KEY_INSERT,
			Delete = GLFW_KEY_DELETE,
			Right = GLFW_KEY_RIGHT,
			Left = GLFW_KEY_LEFT,
			Down = GLFW_KEY_DOWN,
			Up = GLFW_KEY_UP,
			PageUp = GLFW_KEY_PAGE_UP,
			PageDown = GLFW_KEY_PAGE_DOWN,
			Home = GLFW_KEY_HOME,
			End = GLFW_KEY_END,
			CapsLock = GLFW_KEY_CAPS_LOCK,
			ScrollLock = GLFW_KEY_SCROLL_LOCK,
			NumLock = GLFW_KEY_NUM_LOCK,
			PrintScreen = GLFW_KEY_PRINT_SCREEN,
			Pause = GLFW_KEY_PAUSE,
			F1 = GLFW_KEY_F1,
			F2 = GLFW_KEY_F2,
			F3 = GLFW_KEY_F3,
			F4 = GLFW_KEY_F4,
			F5 = GLFW_KEY_F5,
			F6 = GLFW_KEY_F6,
			F7 = GLFW_KEY_F7,
			F8 = GLFW_KEY_F8,
			F9 = GLFW_KEY_F9,
			F10 = GLFW_KEY_F10,
			F11 = GLFW_KEY_F11,
			F12 = GLFW_KEY_F12,
			F13 = GLFW_KEY_F13,
			F14 = GLFW_KEY_F14,
			F15 = GLFW_KEY_F15,
			F16 = GLFW_KEY_F16,
			F17 = GLFW_KEY_F17,
			F18 = GLFW_KEY_F18,
			F19 = GLFW_KEY_F19,
			F20 = GLFW_KEY_F20,
			F21 = GLFW_KEY_F21,
			F22 = GLFW_KEY_F22,
			F23 = GLFW_KEY_F23,
			F24 = GLFW_KEY_F24,
			F25 = GLFW_KEY_F25,
			Keypad0 = GLFW_KEY_KP_0,
			Keypad1 = GLFW_KEY_KP_1,
			Keypad2 = GLFW_KEY_KP_2,
			Keypad3 = GLFW_KEY_KP_3,
			Keypad4 = GLFW_KEY_KP_4,
			Keypad5 = GLFW_KEY_KP_5,
			Keypad6 = GLFW_KEY_KP_6,
			Keypad7 = GLFW_KEY_KP_7,
			Keypad8 = GLFW_KEY_KP_8,
			Keypad9 = GLFW_KEY_KP_9,
			KeypadDecimal = GLFW_KEY_KP_DECIMAL,
			KeypadDivide = GLFW_KEY_KP_DIVIDE,
			KeypadMultiply = GLFW_KEY_KP_MULTIPLY,
			KeypadSubstract = GLFW_KEY_KP_SUBTRACT,
			KeypadAdd = GLFW_KEY_KP_ADD,
			KeypadEnter = GLFW_KEY_KP_ENTER,
			KeypadEqual = GLFW_KEY_KP_EQUAL,
			LeftShift = GLFW_KEY_LEFT_SHIFT,
			LeftControl = GLFW_KEY_LEFT_CONTROL,
			LeftAlt = GLFW_KEY_LEFT_ALT,
			LeftSuper = GLFW_KEY_LEFT_SUPER,
			RightShift = GLFW_KEY_RIGHT_SHIFT,
			RightControl = GLFW_KEY_RIGHT_CONTROL,
			RightAlt = GLFW_KEY_RIGHT_ALT,
			RightSuper = GLFW_KEY_RIGHT_SUPER,
			Menu = GLFW_KEY_MENU
		};
		enum class CursorMode : unsigned int {
			///@brief Normal mode of the cursor
			Normal = GLFW_CURSOR_NORMAL,
			///@brief The cursor is now hidden but the position system will still be the same
			Hidden = GLFW_CURSOR_HIDDEN,
			///@brief The cursor is hidden and locked into the window, a virtual position system will be used instead
			Disabled = GLFW_CURSOR_DISABLED
		};
		enum class MouseButton : unsigned int {
			Left = GLFW_MOUSE_BUTTON_1,
			Right = GLFW_MOUSE_BUTTON_2,
			Middle = GLFW_MOUSE_BUTTON_3,
			Button4 = GLFW_MOUSE_BUTTON_4,
			Button5 = GLFW_MOUSE_BUTTON_5,
			Button6 = GLFW_MOUSE_BUTTON_6,
			Button7 = GLFW_MOUSE_BUTTON_7,
			Button8 = GLFW_MOUSE_BUTTON_8,
		};



		///@brief Empty constructor
		///@param videoMode VideoMode used to draw the window
		Window( VideoMode videoMode = VideoMode::Windowed );

		///@brief Destructor
		~Window();

		///@brief Constructor
		///@param title Title of the window.
		///@param videoMode Video mode used for this window
		///@param size Size in pixels of the specified window.
		///@param monitor Monitor Used.
		///@param share Window used to share resource to.
		Window( const StringASCII & title, VideoMode videoMode = VideoMode::Windowed, const Math::Vec2<unsigned int> & size = Math::Vec2<unsigned int>( 800, 600 ), GLFWmonitor * monitor = NULL, Window * share = NULL, unsigned int flags = 0 );

		///@brief Constructor for a windowed window.
		///@param title Title of the window
		///@param size Size in pixels of the window
		///@param share Window used to share resource to.
		///@param flags Flags to add at its creation
		Window( const StringASCII & title, const Math::Vec2<unsigned int> & size, Window * share = NULL, unsigned int flags = 0 );

		Window( const StringASCII & title, GLFWmonitor * monitor, Window * share = NULL, unsigned int flags = 0 );

		Window( const StringASCII & title, unsigned int refreshRate, GLFWmonitor * monitor, Window * share = NULL, unsigned int flags = 0 );

		///@brief Set the window to be windowed
		void setWindowed();

		///@brief Set the window to be borderless to a monitor
		///@param monitor Monitor to be used (can be NULL for using the defaulted)
		void setBorderless( GLFWmonitor * monitor );

		///@brief Set the window to be fullscreen to a monitor
		///@param monitor Monitor to be used (can be NULL for using the defaulted)
		///@param size Size of the render
		///@param refreshRate Refresh Rate of the new render
		void setFullscreen( GLFWmonitor * monitor, Math::Vec2<unsigned int> & size, unsigned int refreshRate );

		///@brief Set the icon of this window
		///@param icon Pointer to the icon to be used ( RGBA 8bits Top to Bottom and Left to Right )
		void setIcon( const Graphic::Texture<unsigned char> * icon );

		///@brief Get the icon used for this window (NULL if the default one is used)
		///@return Icon used for this window ( RGBA 8bits Top to Bottom and Left to Right )
		const Graphic::Texture<unsigned char> * getIcon() const;

		///@brief Set the cursor for this window
		///@param cursor Pointer to the icon to be used ( RGBA 8bits Top to Bottom and Left to Right )
		///@param pos Cursor hot spot relative to the top left corner
		void setCursor( const Graphic::ImageT<unsigned char> * cursor, const Math::Vec2<unsigned int> & pos = Math::Vec2<unsigned int>::null );

		///@brief Set the cursor mode for this window
		///@param cursorMode Mode of the cursor
		///@see CursorMode
		void setCursorMode( CursorMode cursorMode );

		///@brief get the cursor mode for this window
		CursorMode getCursorMode() const;

		///@brief Set the size of this window (only for windowed)
		///@param size Size of this window in pixels
		void setSize( const Math::Vec2<unsigned int> & size );

		///@brief Get the size of this window
		///@return Size of this window
		const Math::Vec2<unsigned int> & getSize() const;

		///@brief Set the title of this window
		///@param title Title of this window
		void setTitle( const String & title );

		///@brief Get the title of this window
		///@return Title of this window
		const String & getTitle() const;


		///@brief Set if the window will be resizable by the user or not (Only used for windowed window)
		///@param If the window will be resizable or not
		void setResizable( bool resizable = true );

		///@brief Get if the window is resizable by user or not.
		///@return If the window is resizable or not
		bool getResizable() const;

		///@brief Set if the window will be visible directly after it's creation
		///@param True for visible, False otherwise
		void setVisible( bool visible = true );

		///@brief Get if the window will be visible directly after it's creation
		///@return True for visible, False otherwise
		bool getVisible() const;

		///@brief Set if the window will be decorated (only for windowed)
		///@param decorated True or False
		void setDecorated( bool decorated = true );

		///@brief Get if the window will be decorated (only for windowed)
		///@return True or False
		bool getDecorated() const;

		///@brief Set if the window will directly be focused
		///@param focused True or False 
		void setFocused( bool focused = true );

		///@brief Get if the window will directly be focused
		///@return True or False 
		bool getFocused() const;

		///@brief Set if the window will automatically be reduced on focus loss (only for full screen)
		///@param autoIconify True or False
		void setAutoIconify( bool autoIconify = true );

		///@brief Get if the window will automatically be reduced on focus loss (only for full screen)
		///@return True or False
		void getAutoIconify();

		///@brief Set if the window will be always on top
		///@param alwaysOnTop True or False
		void setAlwaysOnTop( bool alwaysOnTop = false );

		///@brief Get if the window will be always on top
		///@return True or False
		bool getAlwaysOnTop() const;

		///@brief Set if the window will directly be maximized
		///@param maximized True or False
		void setMaximized( bool maximized = false );

		///@brief Get if the window will be maximized
		///@return True or False
		bool getMaximized() const;

		///@brief Set the number of bits for the created window
		///@param redBits Number of bits for the red channel
		///@param greenBits Number of bits for the green channel
		///@param blueBits Number of bits for the blue channel
		///@param alphaBits Number of bits for the alpha channel
		///@param depthBits Number of bits for the depth channel
		///@param stencilBits Number of bits for the stencil channel
		void setBits( unsigned int redBits = 8, unsigned int greenBits = 8, unsigned int blueBits = 8, unsigned int alphaBits = 8, unsigned int depthBits = 24, unsigned int stencilBits = 8 );

		///@brief Get the number of red bits 
		///@return number of red bits
		unsigned int getRedBits() const;

		///@brief Get the number of green bits 
		///@return number of green bits
		unsigned int getGreenBits() const;

		///@brief Get the number of blue bits 
		///@return number of blue bits
		unsigned int getBlueBits() const;

		///@brief Get the number of alpha bits 
		///@return number of alpha bits
		unsigned int getAlphaBits() const;

		///@brief Get the number of depth bits 
		///@return number of depth bits
		unsigned int getDepthBits() const;

		///@brief Get the number of stencil bits 
		///@return number of stencil bits
		unsigned int getStencilBits() const;


		///@brief Set the number of bits for the accumulation buffer
		///@param redBits Number of bits for the red channel
		///@param greenBits Number of bits for the green channel
		///@param blueBits Number of bits for the blue channel
		///@param alphaBits Number of bits for the alpha channel
		///@param depthBits Number of bits for the depth channel
		///@param stencilBits Number of bits for the stencil channel
		void setAccumulationBits( unsigned int accumulationRedBits = 8, unsigned int accumulationGreenBits = 8, unsigned int accumulationBlueBits = 8, unsigned int accumulationAlphaBits = 8);

		///@brief Get the number of red bits of the accumulation buffer
		///@return number of red bits
		unsigned int getAccumulationRedBits() const;

		///@brief Get the number of green bits of the accumulation buffer
		///@return number of green bits
		unsigned int getAccumulationGreenBits() const;

		///@brief Get the number of blue bits of the accumulation buffer
		///@return number of blue bits
		unsigned int getAccumulationBlueBits() const;

		///@brief Get the number of alpha bits of the accumulation buffer
		///@return number of alpha bits
		unsigned int getAccumulationAlphaBits() const;


		///@brief Set the number of auxiliary buffers (-1 mean no preference)
		///@param nbAuxiliaryBuffers Number of auxiliary buffers (-1 mean no preference)
		void setNbAuxiliaryBuffers( unsigned int nbAuxiliaryBuffers = 0 );

		///@brief Get the number of auxiliary buffers (-1 mean no preference)
		///@return Number of auxiliary buffers (-1 mean no preference)
		unsigned int getNbAuxiliaryBuffers() const;

		///@brief Set the number of samples for the multisampling (0 will disable multisampling)
		///@param nbSamples Number of samples
		void setNbSamples( unsigned int nbSamples );

		///@brief Get the number of samples for the multisampling
		///@return nbSamples Number of samples
		unsigned int getNbSamples() const;

		///@brief Set the refresh rate (only for fullscreen)
		///@param refreshRate Refresh Rate of the screen if the window will be fullscreen
		void setRefreshRate( unsigned int refreshRate );

		///@brief Get the refresh rate of this window (only for fullscreen)
		///@return refresh rate
		unsigned int getRefreshRate() const;

		///@brief Set if the context will render in stereo or not
		///@param stereo True for a stereo render or False for a mono one.
		void setStereo( bool stereo );

		///@brief Get if the render is in stereo or not.
		///@return True for a stereo render or False for a mono one.
		bool getStereo() const;

		///@brief Set if the render is SRGB capable or not.
		///@param SRGBCapable True for a SRGB capable render, False otherwise.
		void setSRGBCapable( bool SRGBCapable );

		///@brief Get if the render is SRGB capable or not.
		///@return True for a SRGB capable render, False otherwise.
		bool getSRGBCapable() const;

		///@brief Set if the render should use a double buffer
		///@param doubleBuffer True for a render using a double buffer, False otherwise.
		void setDoubleBuffer( bool doubleBuffer );

		///@brief Get if the render use a double buffer
		///@return True for a render use a double buffer, False otherwise.
		bool getDoubleBuffer() const;

		///@brief Set the API to create the context for
		///@param clientAPI API to create the context for
		void setClientAPI( ClientAPI clientAPI );

		///@brief Get the API to create the context for
		///@return API to create the context for
		ClientAPI getClientAPI() const;

		///@brief Get the creation API to use to create the context
		///@param contextAPI Creation API used to create the context
		void setContextCreateAPI( ContextCreateAPI contextAPI );

		///@brief Get the create API to use to create the context
		///@return Creation API used to create the context
		ContextCreateAPI getContextCreateAPI() const;

		///@brief Set the major version number of the chosen client API 
		///@param majorVersion Major version number of the chosen client API 
		void setContextMajorVersion( unsigned int majorVersion );

		///@brief Get the major version number of the chosen client API 
		///@return Major version number of the chosen client API 
		unsigned int getContextMajorVersion() const;

		///@brief Set the minor version number of the chosen client API 
		///@param minorVersion Minor version number of the chosen client API 
		void setContextMinorVersion( unsigned int minorVersion );

		///@brief Get the minor version number of the chosen client API 
		///@return Minor version number of the chosen client API 
		unsigned int getContextMinorVersion() const;

		///@brief Specifies the robustness strategy to be used by the context
		///@param robustness Robustness strategy to be used by the context
		void setRobustness( Robustness robustness );

		///@brief Get the robustness strategy to be used by the context
		///@return Robustness strategy to be used by the context
		Robustness getRobustness() const;

		///@brief Specifies the release behavior to be used by the context
		///@param releaseBehavior Release behavior to be used by the context
		void setReleaseBehavior( ContextReleaseBehavior releaseBehavior );

		///@brief Get the release behavior to be used by the context
		///@return Release behavior to be used by the context
		ContextReleaseBehavior getReleaseBehavior() const;

		///@brief Specifies whether the OpenGL context should be forward-compatible
		///@param fowardCompatible Whether the OpenGL context should be forward-compatible
		void setFowardCompatible( bool fowardCompatible );

		///@brief Get whether the OpenGL context should be forward-compatible
		///@return Whether the OpenGL context should be forward-compatible
		bool getFowardCompatible() const;

		///@brief Set whether OpenGL should enable debug
		///@param debug True for debugging, False otherwise.
		void setDebug( bool debug );

		///@brief Get if debug is enable on OpenGL
		///@return True for debugging, False otherwise.
		bool getDebug() const;

		///@brief Set the OpenGL profile to be used
		///@param profile OpenGL profile to be used
		void setOpenGLProfile( OpenGLProfile profile );

		///@brief Get the OpenGL profile used
		///@return OpenGL profile used.
		OpenGLProfile getOpenGLProfile() const;


		///@brief Reset all field to default
		void reset();

		
		///@brief Get the StringASCII from the clipboard
		///@return StringASCII from the clipboard
		String getClipboardString() const;

		///@brief Set the Clipboard with a new string
		///@param string StringASCII to set to the clipboard
		void setClipboardString( const String & string );

		///@brief Get if the mouse is actually hover is window
		///@return True if the mouse is actually hover, false otherwise
		bool isMouseHover() const;

		/************************************************************************/
		/* Static                                                               */
		/************************************************************************/
		///@brief Get a human readable string representing a Key
		///@param key Key to convert into a StringASCII
		///@return Human Readable StringASCII
		static StringASCII & key2String( Key key );

		///@brief Get a human readable string representing a MouseButton
		///@param mouseButton MouseButton to convert into a StringASCII
		///@return Human Readable StringASCII
		static StringASCII & mouseButton2String( MouseButton mouseButton );


		/************************************************************************/
		/* IO                                                                   */
		/************************************************************************/
		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;



		/************************************************************************/
		/* EVENTS                                                               */
		/************************************************************************/
		///@brief Event handler when the focus of the window is gained or lost.
		///@param focus True for : 'The window has now the focus' and False 'The window has lost the focus'
		virtual void onFocus( bool focus );

		///@brief Event handler for the sizing of the window
		///@param size New Size freshly
		virtual void onResize( const Math::Vec2<unsigned int> & size );

		///@brief Event handler when a key event is captured
		///@param key Key of the event
		///@param action Action of the key
		///@param mods Unsigned int created with binary OR (|) of deferents KeyModifier)
		virtual void onKey( Key key, EventAction action, unsigned int mods );

		///@brief Event handler when a Mouse Button event is captured
		///@param mouseButton Mouse Button of the event
		///@param action Action of the key
		///@param mods Unsigned int created with binary OR (|) of deferents KeyModifier)
		virtual void onMouseButton( MouseButton mouseButton, EventAction action, unsigned int mods );

		///@brief Event handler when a text is input
		///@param unicodeCodePoint Unicode Code Point Received
		virtual void onText( UTF8String::CodePoint unicodeCodePoint );

		///@brief Event handler when files are dropped into the window
		///@param filePathsVector Vector of UTF8String representing the files dropped into the window
		virtual void onDrop( Vector<String> filePathsVector );

		///@brief Event handler when the mouse enter or leave the window
		///@param entered Boolean if the mouse is now hover the window or not
		virtual void onMouseEnter( bool entered );

		///@brief Event handler when the mouse move over the window
		///@param position Position of the mouse relative to the top-left corner of the window client area
		virtual void onMouseMove( const Math::Vec2<double> & position );

	protected:
		bool createContext();
		bool deleteContext();

		///@brief function to be overloaded to add action during the loading process.
		///@return True if the loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if the unloading has succeeded, False otherwise
		virtual bool onUnload() override;



	protected:
		bool mouseHover;



		Math::Vec2<unsigned int> size;
		String title;
		VideoMode videoMode;
		const Graphic::Texture<unsigned char> * icon;
		Graphic::Texture<unsigned char> * iconLoaded;
		CursorMode cursorMode;

		bool resizable;
		bool visible;
		bool decorated;
		bool focused;
		bool autoIconify;
		bool alwaysOnTop;
		bool maximized;

		unsigned int redBits;
		unsigned int greenBits;
		unsigned int blueBits;
		unsigned int alphaBits;
		unsigned int depthBits;
		unsigned int stencilBits;


		unsigned int accumulationRedBits;
		unsigned int accumulationGreenBits;
		unsigned int accumulationBlueBits;
		unsigned int accumulationAlphaBits;

		unsigned int nbAuxiliaryBuffers;
		unsigned int nbSamples;

		unsigned int refreshRate;
		bool stereo;
		bool SRGBCapable;
		bool doubleBuffer;
		ClientAPI clientAPI;
		ContextCreateAPI contextAPI;
		unsigned int contextMajorVersion;
		unsigned int contextMinorVersion;
		Robustness robustness;
		ContextReleaseBehavior contextReleaseBehavior;
		bool openGLFowardCompatible;
		bool openGLDebug;
		OpenGLProfile openGLProfile;


		GLFWmonitor * glfwMonitor;
		GLFWwindow * glwfWindow;
		GLFWcursor * glfwCursor;
		Window * sharedWindow;


	private:
		static void _window_focus_callback( GLFWwindow * glfwWindow, int focused );
		static void _window_size_callback( GLFWwindow * glfwWindow, int width, int height );
		static void _key_callback( GLFWwindow * glfwWindow, int key, int scancode, int action, int mods );
		static void _character_callback( GLFWwindow * glfwWindow, unsigned int codepoint );
		static void _drop_callback( GLFWwindow * glfwWindow, int count, const char** paths );
		static void _cursor_enter_callback( GLFWwindow * glfwWindow, int entered );
		static void _cursor_position_callback( GLFWwindow * glfwWindow, double xpos, double ypos );
		static void _mouse_button_callback( GLFWwindow * glfwWindow, int button, int action, int mods );

		static Map< GLFWwindow *, GLFW::Window * > createdWindowMap;
		static Window * actuallyOnFocusWindow;
		static Window * actuallyOnMouseOver;
	};

	void glTraceFunction( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void * userParam );

}




#endif


