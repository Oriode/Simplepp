#pragma once

#include "IO.h"
#include "../BasicLoadable.h"
#include "SimpleFileStream.h"
#include "../OS/Path.h"

namespace IO {

	template<typename DataType>
	class IOLoadable : protected virtual BasicSimpleIO, public virtual BasicLoadable {
	public:
		IOLoadable(const OS::Path & filePath);
		~IOLoadable();

		const DataType & getObject() const;
		DataType & getObject();

	protected:
		///@brief load this object from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( SimpleFileStream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( SimpleFileStream * fileStream );

		///@brief function to be overloaded to add action during the loading process.
		///@return True if the loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if the unloading has succeeded, False otherwise
		virtual bool onUnload() override;

	private:
		OS::Path filePath;
		DataType * object;

	};

}

#include "IOLoadable.hpp"