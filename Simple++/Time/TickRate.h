#pragma once

#include "../Math.h"
#include "../Time.h"


class TickRate {
public:
	TickRate(int targetTickRate = 60);
	~TickRate(void);


	/************************************************************************/
	/* Change the targeted tick rate                                        */
	/************************************************************************/
	void setTargetTickRate(unsigned int tickRate);

	/************************************************************************/
	/* Wait function called after each frame                                */
	/************************************************************************/
	void delay();


	/************************************************************************/
	/* Get the time used for the last frame in ms                           */
	/************************************************************************/
	const Time::Duration<Time::MilliSecond> & getTimePerTickMS() const;


	/************************************************************************/
	/* Get the time used for the last frame in second                       */
	/************************************************************************/
	float getTimePerTickS() const;


	/************************************************************************/
	/* Get the number of the last frame                                     */
	/************************************************************************/
	unsigned long long getTickNum() const;

	const Time::Duration<Time::MilliSecond> & getElapsedTimeMS() const;

	float getElapsedTimeS() const;

private:
	unsigned int targetTickRate;										//Target tickrate, (number of ticks per seconds)
	Time::Duration<Time::MilliSecond> targetTimePerTick;						//Target time in MS per tick
	Time::Duration<Time::MilliSecond> timePerTick;							//Duration of a tick
	float timePerTickSeconds;
	Time::Tick endTicks;
	unsigned long long tickNumber;
	float elapsedTimeS;
	Time::Duration<Time::MilliSecond> elapsedTimeMS;						//Duration of a tick

};

