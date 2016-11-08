#include "BasicLoadableIO.h"



BasicLoadableIO::BasicLoadableIO() {
}




BasicLoadableIO::~BasicLoadableIO() {
}



bool BasicLoadableIO::writeToFile(const WString & path) {
	std::fstream file(path.getData(), std::ios::out | std::ios::binary);
	if ( file.is_open() ) {
		load();
		if ( !write(&file) ) {
			file.close();
			return false;
		}
		file.close();
		log(String("Success writting the file  : ") << path);
		return true;
	} else {
		error(String("Unable to open the file : ") << path);
		return false;
	}
}

bool BasicLoadableIO::readFromFile(const WString & path) {
	std::fstream file(path.getData(), std::ios::in | std::ios::binary);
	if ( file.is_open() ) {
		if ( !read(&file) ) {
			file.close();
			return false;
		}
		file.close();
		log(String("Success writting the file  : ") << path);
		return true;
	} else {
		error(String("Unable to open the file : ") << path);
		return false;
	}
}


