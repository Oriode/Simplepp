#include "BasicLoadable.h"


BasicLoadable::BasicLoadable() :
mIsloaded(false)
{
}

BasicLoadable::BasicLoadable(const BasicLoadable & loadable){
	*this = loadable;
}


BasicLoadable::~BasicLoadable(){
}

void BasicLoadable::load(){
	lock();
	if ( this->mIsloaded ) {
		unlock();
		return;
	}
	this->bIsLoading = true;

	onLoad();

	this->bIsLoading = false;
	this->mIsloaded = true;
	unlock();

}

void BasicLoadable::unload(){
	lock();

	if (!this->mIsloaded) {
		unlock();
		return;
	}
	onUnload();
	this->mIsloaded = false;
	unlock();
}

void BasicLoadable::onLoad(){

}

void BasicLoadable::onUnload(){

}

bool BasicLoadable::isLoaded() const{
	return this -> mIsloaded;
}

void BasicLoadable::setLoaded(bool loaded){
	this -> mIsloaded = loaded;
}

void BasicLoadable::setLoading(bool isLoading) {
	this -> bIsLoading = isLoading;
}

void BasicLoadable::reload() {
	if (isLoaded()){
		unload();
		load();
	}

}

bool BasicLoadable::isLoading() const{
	return this->bIsLoading;
}


void BasicLoadable::lock() {
	this -> mutex.lock();
#ifdef DEBUG
	this -> isLocked = true;
#endif
}

void BasicLoadable::unlock() {
#ifdef DEBUG
	this -> isLocked = false;
#endif
	this -> mutex.unlock();
}

BasicLoadable & BasicLoadable::operator=(const BasicLoadable & loadable) {
	this-> bIsLoading = loadable.bIsLoading;
	this-> mIsloaded = loadable.mIsloaded;
	return *this;
}