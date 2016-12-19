#include "Event.h"


#ifdef _UI
namespace UI {


/*
	const unsigned int Event::NUM_SCANCODES = SDL_NUM_SCANCODES;
	const unsigned int Event::NUM_WINDOW_EVENTS = 15;
	const unsigned int Event::NUM_MOUSE_BUTTONS = 8;

	Event::Event() :
		mousePosition( 0 ),
		mousePositionRel( 0 ),
		mouseWheel( 0 )
	{
		for ( int i( 0 ); i < Event::NUM_SCANCODES; i++ ) 
			this -> keyPressed[i] = State::Released;
		for ( int i( 0 ); i < Event::NUM_MOUSE_BUTTONS; i++ ) 
			this -> mousePressed[i] = State::Released;
	}






	void Event::update() {
		this -> mouseWheel.x = unsigned int( 0 );
		this -> mouseWheel.y = unsigned int( 0 );

		this -> mousePositionRel.x = unsigned int( 0 );
		this -> mousePositionRel.y = unsigned int( 0 );

		// Until there is no more new events
		while ( SDL_PollEvent( &this -> SDLEvents ) ) {

			switch ( this -> SDLEvents.type ) {
				case SDL_KEYDOWN:
					{
						ScanCode scanCode( this -> SDLEvents.key.keysym.scancode );
						this -> keyPressed[scanCode] = State::Pressed;

						onKeyDownEvent( scanCode );

						break;
					}
				case SDL_KEYUP:
					{
						ScanCode scanCode( this -> SDLEvents.key.keysym.scancode );
						this -> keyPressed[scanCode] = State::Released;

						onKeyUpEvent( scanCode );

						break;
					}
				case SDL_MOUSEBUTTONDOWN:
					{
						MouseButton scanCode( MouseButton( this -> SDLEvents.button.button ) );
						this -> mousePressed[unsigned char( scanCode )] = State::Pressed;
						//this -> mouseEventsRecorded.push( scanCode );

						onMouseDownEvent( scanCode );

						break;
					}
				case SDL_MOUSEBUTTONUP:
					{
						MouseButton scanCode( MouseButton( this -> SDLEvents.button.button ) );
						this -> mousePressed[unsigned char( scanCode )] = State::Released;

						onMouseUpEvent( scanCode );

						break;
					}
				case SDL_MOUSEMOTION:
					{
						this -> mousePositionRel.x = this -> SDLEvents.motion.xrel;
						this -> mousePositionRel.y = this -> SDLEvents.motion.yrel;

						this -> mousePosition.x = this -> SDLEvents.motion.x;
						this -> mousePosition.y = this -> SDLEvents.motion.y;
						
						onMouseMotionEvent( this -> mousePosition, this -> mousePositionRel );

						break;
					}
				case SDL_WINDOWEVENT:
					{
						WindowEvent windowEvent( WindowEvent( this -> SDLEvents.window.event ) );

						onWindowEvent( windowEvent );

						break;
					}
				case SDL_MOUSEWHEEL:
					{
						this -> mouseWheel.x = this -> SDLEvents.wheel.x;
						this -> mouseWheel.y = this -> SDLEvents.wheel.y;

						onMouseWheelEvent( this -> mouseWheel );

						break;
					}
			}
		}
	}


*/

}
#endif
