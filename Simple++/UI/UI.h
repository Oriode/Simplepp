///@file UI/UI.h
///@brief Main file for handling User Interface (constant "UI" should be defined in BuildConfig.h)
///@author Clement Gerber
///@date 29/11/16 (DMY)



#pragma once

#include "../BuildConfig.h"
#include "../Log.h"

#ifdef _UI

#include "BasicUI.h"
#include "Event.h"

#else
	static_assert( false, "Including an UI related header file on a release without UI." );
#endif
