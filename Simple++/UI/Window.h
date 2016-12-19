#pragma once

#include "../BuildConfig.h"

#ifdef _UI

#include "BasicUI.h"
#include "../GL/BasicGL.h"
#include "../Time/TickRate.h"
#include "../GL/GLFWWindow.h"

#include "Event.h"

namespace UI  {

	class Window : public GLFW::Window {
	public:


		///@brief Empty Constructor.
		Window();


		/*///@brief Virtual function called when a key is pressed.
		///@param key Key that has been pressed since the last update()
		virtual void onKeyDownEvent( ScanCode key );

		///@brief Virtual function class when a key is released.
		///@param key Key that has been released since the last update()
		virtual void onKeyUpEvent( ScanCode key );

		///@brief Virtual function class when a mouse button is pressed.
		///@param button Mouse button that has been pressed since the last update()
		virtual void onMouseDownEvent( MouseButton button );

		///@brief Virtual function class when a mouse button is released.
		///@param button Mouse button that has been released since the last update()
		virtual void onMouseUpEvent( MouseButton button );

		///@brief Virtual function called when the mouse is moving
		///@param mousePosition Absolute position of the mouse
		///@param mousePositionRel RelativePosition of the mouse
		virtual void onMouseMotionEvent( const Math::Vec2<unsigned int> & mousePosition, const Math::Vec2<unsigned int> & mousePositionRel );

		///@brief Virtual function called when the mouse wheel is moving
		///@param wheelPosition Relative position of the mouse wheel
		virtual void onMouseWheelEvent( Math::Vec2<unsigned int> & wheelPosition );

		///@brief Virtual function called when a Window Event is occurring
		///@param mouseEvent Event of the Window
		virtual void onWindowEvent( WindowEvent windowEvent );*/

		///@brief When the window is loaded, call this method to start the blocking loop
		void show();

	protected:
		///@brief function to be overloaded to add action during the loading process.
		///@return True if the loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if the unloading has succeeded, False otherwise
		virtual bool onUnload() override;

	private:


		//RenderType renderType;
		Time::TickRate tickRate;


		//SDL_GLContext SDLContext;


	};

}

#else
static_assert( false, "Including an UI related header file on a release without UI." );
#endif
