#pragma once

#include "BasicSimpleIO.h"
#include "BasicLoadable.h"

class BasicSimpleLoadableIO : public BasicSimpleIO, public BasicLoadable {
public:
	BasicSimpleLoadableIO();
	~BasicSimpleLoadableIO();


	///@brief load this object from a file stream
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	bool read(std::fstream * fileStream);

	///@brief write this object as binary into a file stream
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	bool write(std::fstream * fileStream);
protected:
	///@brief function to be overloaded to set the action when reading from a stream.
	///@param fileStream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	virtual bool onRead(std::fstream * fileStream);

	///@brief function to be overloaded to set the action when writing from a stream.
	///@param fileStream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	virtual bool onWrite(std::fstream * fileStream) const;
};

