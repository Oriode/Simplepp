#include "BasicLoadable.h"


BasicLoadable::BasicLoadable() :
	mIsloaded( false ) 
{
}

BasicLoadable::BasicLoadable( const BasicLoadable & loadable ) {
	*this = loadable;
}


BasicLoadable::~BasicLoadable() {
}

bool BasicLoadable::load() {
	lock();
	if ( this -> mIsloaded ) {
		unlock();
		// Object already loaded, nothing to do.
		return true;
	}
	this -> bIsLoading = true;
	if ( onLoad() ) {
		this -> bIsLoading = false;
		this -> mIsloaded = true;
		unlock();
		return true;
	} else {
		this -> bIsLoading = false;
		unlock();
		return false;
	}
}

bool BasicLoadable::unload() {
	lock();

	if ( !this -> mIsloaded ) {
		unlock();
		// Object not loaded, nothing to do.
		return true;
	}
	if ( onUnload() ) {
		this -> mIsloaded = false;
		unlock();
		return true;
	} else {
		unlock();
		return false;
	}
}

bool BasicLoadable::onLoad() {
	return true;
}

bool BasicLoadable::onUnload() {
	return true;
}

bool BasicLoadable::isLoaded() const {
	return this -> mIsloaded;
}

void BasicLoadable::setLoaded( bool loaded ) {
	this -> mIsloaded = loaded;
}

void BasicLoadable::setLoading( bool isLoading ) {
	this -> bIsLoading = isLoading;
}

bool BasicLoadable::reload() {
	if ( isLoaded() ) {
		if ( unload() && load() )
			return true;
		else
			return false;
	} else {
		return true;
	}
}

bool BasicLoadable::isLoading() const {
	return this -> bIsLoading;
}

void BasicLoadable::lock() {
	this -> mutex.lock();
}

void BasicLoadable::unlock() {
	this -> mutex.unlock();
}

BasicLoadable & BasicLoadable::operator=( const BasicLoadable & loadable ) {
	lock();

	this ->  bIsLoading = loadable.bIsLoading;
	this ->  mIsloaded = loadable.mIsloaded;

	unlock();
	return *this;
}
