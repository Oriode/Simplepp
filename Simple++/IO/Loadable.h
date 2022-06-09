#pragma once

#include "../IO/BasicIO.h"
#include "../BasicLoadable.h"
#include "../OS/Path.h"

namespace IO {

	template<typename DataType>
	class Loadable : public virtual BasicIO, public virtual BasicLoadable {
	public:
		Loadable(const OS::Path & filePath);
		~Loadable();

		///@brief Retrieve the internal Object (may be NULL if not loaded.)
		///@return DataType pointer or NULL if not loaded.
		const DataType * getObject() const;

		///@brief Retrieve the internal Object (may be NULL if not loaded.)
		///@return DataType pointer or NULL if not loaded.
		DataType * getObject();

		///@brief load this object from a file stream. This method as calling load(), will lock/unlock and set the object as loaded if success.
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read(Stream* stream );

		///@brief write this object as binary into a file stream. This method is const but will lock/unlock the object anyway.
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write(Stream* stream ) const;

		///@brief Get the filePath of this Loadable.
		///@return File path.
		const OS::Path getFilePath() const;

	protected:
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

#include "Loadable.hpp"