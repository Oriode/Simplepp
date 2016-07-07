#include "Mutex.h"


Mutex::Mutex() {

}


Mutex::~Mutex() {

}

void Mutex::lock() {
	if ( this -> bLocked && Thread::getCurrentThreadId() == this -> lockingThreadId ) {
		//log("Trying to lock an already locked mutex on the same thread");
		return;
	}

	this -> mMutex.lock();
	this -> lockingThreadId = Thread::getCurrentThreadId();
	this -> bLocked = true;
}

void Mutex::unlock() {
	if ( this -> bLocked )
		this -> mMutex.unlock();

	this -> bLocked = false;
}

bool Mutex::isLocked() const {
	return this -> bLocked;
}
