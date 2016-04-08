#pragma once


#include "Log.h"
#include "Vector.h"
#include "String.h"
#include "Map.h"


template<typename T>
class Application {
public:

	Application();
	Application(int argc, T * argv[]);
	~Application();



	const BasicString<T> & getApplicationName() const;
	const T ** getArgv() const;
	int getArgc() const;


	const Map<BasicString<T>, BasicString<T>> & getArgMap() const;

private:
	int argc;
	T ** argv;
	Map<BasicString<T>, BasicString<T>> argMap;
	BasicString<T> applicationName;
};






#include "Application.hpp"
