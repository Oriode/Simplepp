///@file ImageHandler.h
///@brief File containing the IOResource Object, an object containing an object of type DataType, externally loaded or internally. The goal is to manipulate an object multiple times without having to ensure memory deletion.
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "../BasicLoadable.h"
#include "IOManager.h"
#include "BasicIO.h"
#include "../Utility.h"

namespace IO  {

	///@brief Part of the IOManager.
	template<typename DataType>
	class IOResource : public BasicIO {
		public:

			enum class LoadingType : unsigned char {
				None,
				Internaly,
				Manager,
				Externaly
			};

			///@brief Empty Constructor
			///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
			IOResource( IOManager<DataType> * manager = NULL );

			///@brief Constructor from an external object, no memory management will be done.
			///@param dataObject Object to use in this handler (object has to be deleted manually)
			///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
			IOResource( DataType * dataObject, IOManager<DataType> * manager = NULL );

			///@brief Constructor from a path, the memory management will be using the Manager if any, internally otherwise.
			///@param filePath path to to the file.
			///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
			IOResource( const OS::Path & filePath, IOManager<DataType> * manager = NULL );

			///@brief Copy Constructor
			///@param handler object to be copied
			IOResource( const IOResource<DataType> & handler );

			///@brief Moved Constructor
			///@param handler object to be moved
			IOResource( IOResource<DataType> && handler );

			///@brief Destructor
			~IOResource();

			///@brief Cast operator into the pointer of the type of the object inside.
			operator DataType * ( );
			operator const DataType * ( ) const;

			///@brief Copy Operator
			///@param handler Object to be copied
			///@return reference to THIS
			IOResource<DataType> & operator=( const IOResource<DataType> & handler );

			///@brief Move operator
			///@param handler Object to be moved
			///@return reference to THIS
			IOResource<DataType> & operator=( IOResource<DataType> && handler );

			///@brief Get the image inside of this handler (Can be NULL if empty)
			///@return Pointer to the object stored inside this handler
			const DataType * getObject() const;
			DataType * getObject();

			///@brief Set the object using a file path (memory management is assured)
			///@param filePath Path to the file to be loaded.
			///@return Boolean if the init has worked
			bool setObject( const OS::Path & filePath );

			///@brief Set the object using an externally generated object (you still have to handle memory management in this case). Setting this will remove the link with the Manager.
			///@param dataObject Object already defined to link to this handler
			///@return Boolean if the init has worked
			bool setObject( DataType * dataObject );

			///@brief read from a file stream
			///@param fileStream stream used to read load this object
			///@return boolean to know if the operation is a success of not.
			bool read( FileStream * fileStream );

			///@brief write this object as binary into a file stream
			///@param fileStream stream used to write this object
			///@return boolean to know if the operation is a success of not.
			bool write( FileStream * fileStream ) const;

		private:
			bool _setObject( const OS::Path & filePath );
			bool _deleteObject();
			IOManager<DataType> * manager;
			DataType * object;
			LoadingType loadingType;
			typename IOManager<DataType>::ObjectId managerObjectId;
	};

}

#include "IOResource.hpp"
