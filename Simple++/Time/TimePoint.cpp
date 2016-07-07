#include "TimePoint.h"

namespace Time {

	TimePoint::TimePoint() {
	}


	TimePoint::TimePoint( const TimeT & timeT ) {
		this -> t = timeT;
	}


	void TimePoint::setNow() {
		std::time( &this -> t );
	}


	bool TimePoint::operator==( const TimePoint & timePoint ) const {
		return this -> t == timePoint.t;
	}

	bool TimePoint::operator!=( const TimePoint & timePoint ) const {
		return this -> t != timePoint.t;
	}

	bool TimePoint::operator<=( const TimePoint & timePoint ) const {
		return this -> t <= timePoint.t;
	}

	bool TimePoint::operator>=( const TimePoint & timePoint ) const {
		return this -> t >= timePoint.t;
	}

	bool TimePoint::operator>( const TimePoint & timePoint ) const {
		return this -> t > timePoint.t;
	}

	bool TimePoint::operator<( const TimePoint & timePoint ) const {
		return this -> t < timePoint.t;
	}

	TimePoint & TimePoint::operator=( const TimePoint & timePoint ) {
		this -> t = timePoint.t;
		return *this;
	}

	TimePoint & TimePoint::operator=( const TimeT & timeT ) {
		this -> t = timeT;
		return *this;
	}


	void TimePoint::setTime( const TimeT & t ) {
		this -> t = t;
	}

	const TimeT & TimePoint::getTime() const {
		return this -> t;
	}


	TimePoint TimePoint::getNow() {
		TimePoint newTime;
		newTime.setNow();
		return newTime;
	}


	TimePoint & TimePoint::operator+=( TimeT t ) {
		this -> t += t;
		return *this;
	}

	TimePoint & TimePoint::operator-=( TimeT t ) {
		this -> t -= t;
		return *this;
	}

	TimePoint::~TimePoint() {
	}


	TimePoint getTime() {
		return TimePoint::getNow();
	}















	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	TimePoint operator+( const TimePoint & t1, TimeT t2 ) {
		return TimePoint( t1.getTime() + t2 );
	}

	TimePoint operator+( TimeT t1, const TimePoint & t2 ) {
		return TimePoint( t1 + t2.getTime() );
	}

	TimePoint operator-( const TimePoint & t1, TimeT t2 ) {
		return TimePoint( t1.getTime() - t2 );
	}

	TimePoint operator-( TimeT t1, const TimePoint & t2 ) {
		return TimePoint( t1 - t2.getTime() );
	}


	Duration<Second> operator-( const TimePoint & t1, const TimePoint & t2 ) {
		return Duration<Second>( t1.getTime() - t2.getTime() );
	}
}


