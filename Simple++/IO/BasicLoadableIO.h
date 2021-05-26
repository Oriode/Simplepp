#pragma once

#include "../String.h"
#include "../Log.h"
#include "BasicSimpleLoadableIO.h"

namespace IO {

	///@brief BasicLodableIO is the base Class for every Class that can be loaded or unloaded dynamically from a file system file.
	template<typename T = int>
	class BasicLoadableIOT : public BasicSimpleLoadableIO {
	public:
		BasicLoadableIOT();
		~BasicLoadableIOT();

		///@brief write this object to a file.
		///@param path path to the file where to write.
		///@return Boolean if the function success of not.
		bool writeToFile(const OS::Path & path);

		///@brief load this object from a file.
		///@param path path to the file where to read.
		///@return Boolean if the function success of not.
		bool readFromFile(const OS::Path & path);
	};

	using BasicLoadableIO = BasicLoadableIOT<int>;

}

#include "BasicLoadableIO.hpp"

