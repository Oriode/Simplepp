#include "Application.h"


template<typename T>
Application<T>::Application() : 
argc(0),
argv(NULL)
{
}


template<typename T>
Application<T>::Application(int argc, T * argv[]) :
	argc(argc),
	argv(argv),
	applicationName(argv[0]) {

	bool isNewArg = true;

	//for each arg
	for ( size_t i = 1; i < argc; i++ ) {
		auto it = argv[i];

		if ( *it == T('-') ) {
			it++;
			if ( *it == T('-') ) {		//EXTENDED
				it++;
				isNewArg = false;
				this -> argMap.insert(BasicString<T>(it), BasicString<T>());
			} else {				//SIMPLE
				isNewArg = true;
				//for each char
				for ( ; *it != T('\0'); it++ ) {
					this -> argMap.insert(BasicString<T>(*it), BasicString<T>());
				}
			}
		} else {
			if ( isNewArg ) {
				this -> argMap.insert(BasicString<T>(), BasicString<T>(it));
			} else {
				this -> argMap.getLastValue() = it;
			}
		}
	}
}


template<typename T>
const Map<BasicString<T>, BasicString<T>> & Application<T>::getArgMap() const {
	return this -> argMap;
}


template<typename T>
int Application<T>::getArgc() const {
	return this -> argc;
}

template<typename T>
const T ** Application<T>::getArgv() const {
	return this -> argv;
}


template<typename T>
const BasicString<T> & Application<T>::getApplicationName() const {
	return this -> applicationName;
}


template<typename T>
Application<T>::~Application() {
}

template<typename T>
const BasicString<T> * Application<T>::operator[](const BasicString<T> & argName) const {
	return this -> argMap[argName];
}
