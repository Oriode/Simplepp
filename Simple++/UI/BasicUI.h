#pragma once

#include "../BuildConfig.h"
#include "../Log.h"

#ifdef _UI

// We need the basics of GL too
#include "../GL/BasicGL.h"


namespace UI {
/*
	enum class WindowEvent : unsigned char {
		Shown = SDL_WINDOWEVENT_SHOWN,
		Hidden = SDL_WINDOWEVENT_HIDDEN,
		Exposed = SDL_WINDOWEVENT_EXPOSED,
		Moved = SDL_WINDOWEVENT_MOVED,
		Resized = SDL_WINDOWEVENT_RESIZED,
		Minimized = SDL_WINDOWEVENT_MINIMIZED,
		Maximizied = SDL_WINDOWEVENT_MAXIMIZED,
		Restored = SDL_WINDOWEVENT_RESTORED,
		MouseEnter = SDL_WINDOWEVENT_ENTER,
		MouseLeave = SDL_WINDOWEVENT_LEAVE,
		FocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,
		Close = SDL_WINDOWEVENT_CLOSE
	};

	enum class MouseButton : unsigned char {
		Left = SDL_BUTTON_LEFT,
		Middle = SDL_BUTTON_MIDDLE,
		Right = SDL_BUTTON_RIGHT,
		X1 = SDL_BUTTON_X1,
		X2 = SDL_BUTTON_X2,
	};

	enum class Key : unsigned char {
		Number0 = SDL_SCANCODE_0,
		Number1 = SDL_SCANCODE_1,
		Number2 = SDL_SCANCODE_2,
		Number3 = SDL_SCANCODE_3
	};

	enum class KeyState : int {
		Press = GLFW_PRESS,
		Repeat = GLFW_REPEAT,
		Release = GLFW_RELEASE,
		Unkown = GLFW_KEY_UNKNOWN,
	};*/
}
#else
static_assert( false, "Including an UI related header file on a release without UI." );
#endif
