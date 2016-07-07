#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include <chrono>

#include <ctime>

#include "Math.h"
#include "Time/TimePoint.h"
#include "Time/Tick.h"
#include "Time/Duration.h"
#include "Time/Date.h"

namespace Time {




	void sleep( unsigned long ms );

	template<class ratio>
	void sleep( const Duration<ratio> & d );




	static const TimePoint startingTime;

};

