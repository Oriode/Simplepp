#include "Tick.h"



namespace Time {




	Time::Tick operator-(const Tick & t1, const Tick & t2) {
		return Tick(t1.getValue() - t2.getValue());
	}

	Tick getClock() {
		return Tick(clock());
	}

	
	Tick::Tick()
	{

	}

	Tick::Tick(const Tick & tick) :
		c(tick.c) 
	{

	}

	Tick::Tick(ClockT tick) :
		c(tick) {

	}

	Tick::Tick(ctor) {

	}


	void Tick::setNow() {
		this -> c = clock();
	}



	Tick & Tick::operator-=(const Tick & tick) {
		this -> c -= tick.c;
		return *this;
	}

	const ClockT & Tick::getValue() const {
		return this -> c;
	}

	Tick & Tick::operator=(const Tick & tick) {
		this -> c = tick.c;
		return *this;
	}


	bool Tick::operator==(const Tick & tick) const {
		return tick.c == this -> c;
	}
	bool Tick::operator<(const Tick & tick) const {
		return tick.c < this -> c;
	}
	bool Tick::operator>(const Tick & tick) const {
		return tick.c > this -> c;
	}
	bool Tick::operator<=(const Tick & tick) const {
		return tick.c <= this -> c;
	}
	bool Tick::operator>=(const Tick & tick) const {
		return tick.c >= this -> c;
	}

	


	Tick::~Tick() {
	}




}

