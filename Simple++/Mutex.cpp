#include "Mutex.h"


Mutex::Mutex() {

}

Mutex::Mutex( const Mutex & mutex ) {
	*this = mutex;
}

Mutex::~Mutex() {

}

Mutex & Mutex::operator=( const Mutex & mutex ) {
	if ( mutex.isLocked() && !isLocked() )
		lock();
	else if ( isLocked() && !mutex.isLocked() )
		unlock();

	return *this;
}

void Mutex::lock() {
	_assert( !this -> bLocked );
	this -> mMutex.lock();
	//this -> lockingThreadId = Thread::getCurrentThreadId();
	this -> bLocked = true;
}

void Mutex::unlock() {
	_assert( this -> bLocked );
	this -> mMutex.unlock();
	this -> bLocked = false;
}

bool Mutex::isLocked() const {
	return this -> bLocked;
}
