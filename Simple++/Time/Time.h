#pragma once

#include "../BuildConfig.h"

#if defined WIN32
#if defined ENABLE_WIN32
#include <windows.h>
#endif
#else
#include <unistd.h>
#endif // WIN32
#include <chrono>

#include <ctime>

#include "../Math/Math.h"
#include "TimePoint.h"
#include "Tick.h"
#include "Duration.h"
#include "Date.h"

namespace Time {




	void sleep( unsigned long ms );

	template<class ratio>
	void sleep( const Duration<ratio> & d );




	static const TimePoint startingTime;

};

