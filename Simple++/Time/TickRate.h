///@file TickRate


#pragma once

#include "../Math/Math.h"
#include "Time.h"

namespace Time {


	class TickRate {
	public:
		TickRate( int targetTickRate = 60 );
		~TickRate( void );


		///@brief Change the targeted tick rate (number of ticks per second)
		///@param tickRate Tick Rate to be set
		void setTargetTickRate( unsigned int tickRate );

		///@brief Wait function called after each tick 
		void delay();

		///@brief Get the time used for the last frame in millisecond
		///@return Time used for the last frame in milliseconds
		const Time::Duration<Time::MilliSecond> & getTimePerTickMS() const;

		///@brief Get the time used for the last tick in second
		///@return Get the time used for the last tick in second
		float getTimePerTickS() const;

		///@brief Get the number of the last tick
		///@return Number of the last tick
		unsigned long long getTickNum() const;

		///@brief Get the time elapsed from the beginning
		///@return Time in millisecond
		const Time::Duration<Time::MilliSecond> & getElapsedTimeMS() const;

		///@brief Get the time elapsed from the beginning in second
		///@return Time in second
		float getElapsedTimeS() const;

	private:
		unsigned int targetTickRate;										//Target tick rate, (number of ticks per seconds)
		Time::Duration<Time::MilliSecond> targetTimePerTick;			    //Target time in MS per tick
		Time::Duration<Time::MilliSecond> timePerTick;						//Duration of a tick
		float timePerTickSeconds;
		Time::Tick endTicks;
		unsigned long long tickNumber;
		float elapsedTimeS;
		Time::Duration<Time::MilliSecond> elapsedTimeMS;					//Duration of a tick

	};

}
