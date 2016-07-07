///@file Application.h
///@brief Application Class
///@author Clément Gerber
///@date 19/04/2016 (DMY) 

#pragma once
#include "Log.h"
#include "Vector.h"
#include "String.h"
#include "Map.h"


///@brief Application Class for easy access to args
template<typename T>
class Application {
public:

	///@brief Create an empty Application Class without any args
	Application();

	///@brief Create an Application with args (one character arg should be preceded by an "-" and multiple characters args with "--")
	///@param argc Number of args (size of the argv table)
	///@param argv values of args
	Application( int argc, T * argv[] );

	///@brief destructor
	~Application();


	///@brief Operator [] to access an arg using his name
	///@param argName Name of the arg to retrieve.
	///@return Pointer to the string representing the value of the arg.
	const BasicString<T> * operator[]( const BasicString<T> & argName ) const;

	///@brief get the application name (argv[0])
	///@return Name of this application
	const BasicString<T> & getApplicationName() const;

	///@brief Direct access to the argv table
	///@return argv table without any modification.
	const T ** getArgv() const;


	///@brief get the size of the argv table.
	///@return size of the argv table.
	int getArgc() const;

	///@brief Direct Access to the args Map
	///@return Map with all the arguments (Index -> Value)
	const Map<BasicString<T>, BasicString<T>> & getArgMap() const;
private:
	int argc;
	T ** argv;
	Map<BasicString<T>, BasicString<T>> argMap;
	BasicString<T> applicationName;
};




#include "Application.hpp"
