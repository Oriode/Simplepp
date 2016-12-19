#include "Window.h"


#ifdef _UI
namespace UI {



	Window::Window() :
		tickRate( 30 )
	{


	}

	bool Window::onUnload() {
		return GLFW::Window::onUnload();
	}

	bool Window::onLoad() {
		

		if ( !GLFW::Window::onLoad() )
			return false;

		return true;
	}

	/*void Window::onKeyDownEvent( ScanCode key ) {

	}

	void Window::onKeyUpEvent( ScanCode key ) {

	}

	void Window::onMouseDownEvent( MouseButton button ) {

	}

	void Window::onMouseUpEvent( MouseButton button ) {

	}

	void Window::onMouseMotionEvent( const Math::Vec2<unsigned int> & mousePosition, const Math::Vec2<unsigned int> & mousePositionRel ) {

	}

	void Window::onMouseWheelEvent( Math::Vec2<unsigned int> & wheelPosition ) {

	}

	void Window::onWindowEvent( WindowEvent windowEvent ) {

	}*/


	void Window::show() {
		while ( !glfwWindowShouldClose( this -> glwfWindow ) ) {

			// Swap the buffers
			glfwSwapBuffers( this -> glwfWindow );

			//Get the events
			glfwPollEvents();

			// Wait for the specified frame rate
			tickRate.delay();
		}
	}












	


}

#endif
