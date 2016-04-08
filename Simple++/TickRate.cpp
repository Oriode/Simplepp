#include "TickRate.h"


TickRate::TickRate(int targetTickRate) :
	timePerTick(Math::max(1000 / targetTickRate, 1)),
	timePerTickSeconds(float(this -> timePerTick.getValue()) / 1000.0f),
	tickNumber(0),
	elapsedTimeS(0),
	elapsedTimeMS(0)
{
	setTargetTickRate(targetTickRate);
}


TickRate::~TickRate(void){
}


void TickRate::setTargetTickRate(unsigned int tickrate){
	if (tickrate == 0)
		return;
	this -> targetTickRate = tickrate;
	this -> targetTimePerTick = (Time::TimeT) (1000.0f / float(this -> targetTickRate));
}



void TickRate::delay(){
	//wait depending of the actual tickrate
	this -> timePerTick = Time::Duration<Time::MilliSecond>(Time::getClock().getValue() - this -> endTicks.getValue());

	if (this -> timePerTick < this -> targetTimePerTick ){
		Time::sleep(this -> targetTimePerTick.getValue() - this -> timePerTick.getValue());
		this -> timePerTick = this -> targetTimePerTick;
	}

	//increment the number of ticks (its an unsigned int, don't worry for overflow)
	this -> tickNumber++;

	this -> endTicks = Time::getClock();
	this -> timePerTickSeconds = float(this -> timePerTick.getValue()) / 1000.0f;
	this -> elapsedTimeS += this -> timePerTickSeconds;
	this -> elapsedTimeMS += this -> timePerTick;
}


const Time::Duration<Time::MilliSecond> & TickRate::getTimePerTickMS() const{
	return this -> timePerTick;
}

const Time::Duration<Time::MilliSecond> & TickRate::getElapsedTimeMS() const{
	return this -> elapsedTimeMS;
}

float TickRate::getTimePerTickS() const{
	return this -> timePerTickSeconds;
}

unsigned long long TickRate::getTickNum() const{
	return this -> tickNumber;
}

float TickRate::getElapsedTimeS() const{
	return this -> elapsedTimeS;
}
