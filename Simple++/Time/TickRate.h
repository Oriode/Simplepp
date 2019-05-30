/**
 * @file	Time\TickRate.h.
 *
 * @brief		Declares the tick rate class
 * @author	Clément Gerber
 */


#pragma once

#include "../Math/Math.h"
#include "Time.h"

 /** @brief	. */
namespace Time {


	/** @brief	A tick rate. */
	class TickRate {
	public:
		/**
		 * @brief		Constructor
		 *
		 * @param		targetTickRate	(Optional) Target tick rate.
		 */
		TickRate( int targetTickRate = 60 );
		/** @brief	Destructor */
		~TickRate( void );


		/**
		 * @brief			Change the targeted tick rate (number of ticks per second)
		 *
		 * @param	tick		Rate	Tick Rate to be set.
		 */
		void setTargetTickRate( unsigned int tickRate );

		/** @brief	Wait function called after each tick */
		void delay();

		/**
		 * @brief		Get the time used for the last frame in millisecond
		 *
		 * @returns	Time used for the last frame in milliseconds.
		 */
		const Time::Duration<Time::MilliSecond> & getTimePerTickMS() const;

		/**
		 * @brief		Get the time used for the last tick in second
		 *
		 * @returns	Get the time used for the last tick in second.
		 */
		float getTimePerTickS() const;

		/**
		 * @brief		Get the number of the last tick
		 *
		 * @returns	Number of the last tick.
		 */
		unsigned long long getTickNum() const;

		/**
		 * @brief		Get the time elapsed from the beginning
		 *
		 * @returns	Time in millisecond.
		 */
		const Time::Duration<Time::MilliSecond> & getElapsedTimeMS() const;

		/**
		 * @brief		Get the time elapsed from the beginning in second
		 *
		 * @returns	Time in second.
		 */
		float getElapsedTimeS() const;

	private:
		/** @brief	Target tick rate, (number of ticks per seconds) */
		unsigned int targetTickRate;
		/** @brief	Target time in MS per tick */
		Time::Duration<Time::MilliSecond> targetTimePerTick;
		/** @brief	Duration of a tick */
		Time::Duration<Time::MilliSecond> timePerTick;
		/** @brief	The time per tick in seconds */
		float timePerTickSeconds;
		/** @brief	The end ticks */
		Time::Tick endTicks;
		/** @brief	The tick number */
		unsigned long long tickNumber;
		/** @brief	The elapsed time s */
		float elapsedTimeS;
		Time::Duration<Time::MilliSecond> elapsedTimeMS;					//Duration of a tick

	};

}
