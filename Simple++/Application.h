/**
 * @file	Application.h.
 *
 * @brief	Declares the application class
 * @author Clément Gerber
 * @date 19/04/2016 (DMY)
 */



#pragma once
#include "Log.h"
#include "Vector.h"
#include "String.h"
#include "Map.h"


 /**
  * @brief	Application Class for easy access to args
  *
  * @tparam	T	Generic type parameter.
  */
template<typename T>
class Application {
public:

	/** @brief	Create an empty Application Class without any args */
	Application();

	/**
	 * @brief	Create an Application with args (one character arg should be preceded by an "-" and multiple characters args with "--")
	 *
	 * @param 		  	argc	Number of args (size of the argv table)
	 * @param [in,out]	argv	values of args.
	 */
	Application( int argc, T * argv[] );

	/** @brief	destructor */
	~Application();


	/**
	 * @brief	Operator [] to access an arg using its name
	 *
	 * @param	argName	Name of the arg to retrieve.
	 *
	 * @returns	Pointer to the string representing the value of the arg. (NULL if nothing has been founded)
	 */
	const BasicString<T> * operator[]( const BasicString<T> & argName ) const;

	/**
	 * @brief	Get an arg value using its name (alias of operator[])
	 *
	 * @param	argName	Name of the arg to retrieve.
	 *
	 * @returns	Pointer to the string representing the value of the arg. (NULL if nothing has been founded)
	 */
	const BasicString<T> * getArgValue( const BasicString<T> & argName ) const;


	/**
	 * @brief	get the application name (argv[0])
	 *
	 * @returns	Name of this application.
	 */
	const BasicString<T> & getApplicationName() const;

	/**
	 * @brief	Direct access to the argv table
	 *
	 * @returns	argv table without any modification.
	 */
	const T ** getArgv() const;


	/**
	 * @brief	get the size of the argv table.
	 *
	 * @returns	size of the argv table.
	 */
	int getArgc() const;

	/**
	 * @brief	Direct Access to the args Map
	 *
	 * @returns	Map with all the arguments (Index -> Value)
	 */
	const Map<BasicString<T>, BasicString<T>> & getArgMap() const;
private:
	/** @brief	The argc */
	int argc;
	/** @brief	The argv */
	T ** argv;
	/** @brief	The argument map */
	Map<BasicString<T>, BasicString<T>> argMap;
	BasicString<T> applicationName;
};




#include "Application.hpp"
