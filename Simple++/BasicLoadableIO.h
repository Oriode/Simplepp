#pragma once

#include "String.h"
#include "Log.h"
#include "BasicSimpleLoadableIO.h"
#include "String.h"

class BasicLoadableIO : public BasicSimpleLoadableIO {
public:
	BasicLoadableIO();
	~BasicLoadableIO();


	///@brief write this object to a file.
	///@param path path to the file where to write.
	///@return Boolean if the function success of not.
	bool writeToFile(const WString & path);

	///@brief load this object from a file.
	///@param path path to the file where to read.
	///@return Boolean if the function success of not.
	bool readFromFile(const WString & path);
};

