///@file UI/Input.h
///@brief File for handling Input with the user.
///@author Clement Gerber
///@date 29/11/16 (DMY)


#pragma once

#include "../BuildConfig.h"
#ifdef _UI

#include "BasicUI.h"


namespace UI {

	/*class Event {
	public:
		enum class State : bool {
			Pressed = true,
			Released = false
		};
		typedef SDL_Scancode ScanCode;

		///@brief Empty constructor
		Event();

		///@brief Update all the events with the current Hardware Informations
		void update();

		///@brief Virtual function called when a key is pressed.
		///@param key Key that has been pressed since the last update()
		virtual void onKeyDownEvent( ScanCode key ) = 0;

		///@brief Virtual function class when a key is released.
		///@param key Key that has been released since the last update()
		virtual void onKeyUpEvent( ScanCode key ) = 0;

		///@brief Virtual function class when a mouse button is pressed.
		///@param button Mouse button that has been pressed since the last update()
		virtual void onMouseDownEvent( MouseButton button ) = 0;

		///@brief Virtual function class when a mouse button is released.
		///@param button Mouse button that has been released since the last update()
		virtual void onMouseUpEvent( MouseButton button ) = 0;

		///@brief Virtual function called when the mouse is moving
		///@param mousePosition Absolute position of the mouse
		///@param mousePositionRel RelativePosition of the mouse
		virtual void onMouseMotionEvent( const Math::Vec2<unsigned int> & mousePosition, const Math::Vec2<unsigned int> & mousePositionRel ) = 0;

		///@brief Virtual function called when the mouse wheel is moving
		///@param wheelPosition Relative position of the mouse wheel
		virtual void onMouseWheelEvent( Math::Vec2<unsigned int> & wheelPosition ) = 0;

		///@brief Virtual function called when a Window Event is occurring
		///@param mouseEvent Event of the Window
		virtual void onWindowEvent( WindowEvent windowEvent ) = 0;


		static const unsigned int NUM_SCANCODES;
		static const unsigned int NUM_WINDOW_EVENTS;
		static const unsigned int NUM_MOUSE_BUTTONS;
	private:
		SDL_Event SDLEvents;                  //SDL Event Handler
		State keyPressed[SDL_NUM_SCANCODES];   //If the keys are pressed or not
		State mousePressed[8];                 //If the mouse buttons are pressed or not

		Math::Vec2<unsigned int> mousePosition;
		Math::Vec2<unsigned int> mousePositionRel;
		Math::Vec2<unsigned int> mouseWheel;
	};
*/






}
#else
static_assert( false, "Including an UI related header file on a release without UI." );
#endif
