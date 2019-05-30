/**
 * @file		Time\Time.h.
 *
 * @brief		Declares some time related static methods.
 * @author	Clément Gerber
 */

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

	/**
	 * @brief		Sleeps the given milliseconds.
	 *
	 * @param	ms	The milliseconds.
	 */
	void sleep( unsigned long ms );

	/**
	 * @brief		Sleeps the given duration.
	 *
	 * @tparam	ratio	Type of the ratio.
	 * @param	d	A Duration<ratio> The duration to sleep.
	 */
	template<class ratio>
	void sleep( const Duration<ratio> & d );

	/** @brief	Time of the beginning of the software. */
	static const TimePoint startingTime;
};

