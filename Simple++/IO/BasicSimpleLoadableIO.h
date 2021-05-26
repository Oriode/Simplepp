#pragma once

#include "BasicSimpleIO.h"
#include "../BasicLoadable.h"
#include "SimpleFileStream.h"

namespace IO {

	///@brief This class is not intended to be used directly, @see BasicLoadableIO
	template<typename T = int>
	class BasicSimpleLoadableIOT : public virtual BasicSimpleIO, public virtual BasicLoadable {
	public:
		BasicSimpleLoadableIOT();
		~BasicSimpleLoadableIOT();


		///@brief load this object from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read(SimpleFileStream* fileStream);

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write(SimpleFileStream* fileStream);
	protected:
		///@brief function to be overloaded to set the action when reading from a stream.
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onRead(SimpleFileStream* fileStream);

		///@brief function to be overloaded to set the action when writing from a stream.
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onWrite(SimpleFileStream* fileStream) const;
	};

	using BasicSimpleLoadableIO = BasicSimpleLoadableIOT<int>;

}

#include "BasicSimpleLoadableIO.hpp"