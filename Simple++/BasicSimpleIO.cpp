#include "BasicSimpleIO.h"






bool BasicSimpleIO::read(std::fstream * fileStream) {
	_assert(fileStream -> is_open());
	return true;
}

bool BasicSimpleIO::write(std::fstream * fileStream) const {
	_assert(fileStream -> is_open());
	return true;
}