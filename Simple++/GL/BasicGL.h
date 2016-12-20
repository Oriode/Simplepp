#pragma once


#include "../BuildConfig.h"
#ifdef _UI

#include <GL/glew.h>




#else
static_assert( false, "Including an UI related header file on a release without UI." );
#endif
