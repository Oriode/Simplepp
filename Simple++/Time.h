#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include <chrono>

#include <ctime>

#include "Math.h"
#include "TimePoint.h"
#include "Tick.h"
#include "Duration.h"
#include "Date.h"

namespace Time {




	void sleep(unsigned long ms);

	template<class ratio>
	void sleep(const Duration<ratio> & d);




	static const TimePoint startingTime;

};

