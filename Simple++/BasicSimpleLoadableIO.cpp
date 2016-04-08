#include "BasicSimpleLoadableIO.h"





BasicSimpleLoadableIO::BasicSimpleLoadableIO() {
}




BasicSimpleLoadableIO::~BasicSimpleLoadableIO() {
}


bool BasicSimpleLoadableIO::read(std::fstream * fileStream) {
	unload();
	lock();
	setLoading(true);

	if ( onRead(fileStream) ) {
		setLoading(false);
		setLoaded(true);
		unlock();
		return true;
	} else {
		setLoading(false);
		setLoaded(false);
		unlock();
		return false;
	}
}

bool BasicSimpleLoadableIO::write(std::fstream * fileStream) {
	lock();
	_assert(isLoaded());
	if ( !onWrite(fileStream) ) {
		unlock();
		return false;
	}
	unlock();
	return true;
}



bool BasicSimpleLoadableIO::onRead(std::fstream * fileStream) {
	return BasicSimpleIO::read(fileStream);
}

bool BasicSimpleLoadableIO::onWrite(std::fstream * fileStream) const {
	return BasicSimpleIO::write(fileStream);
}
