///@file ImageHandler.h
///@brief File containing the IOHandler Object, an object containing an object of type DataType, externally loaded or internally
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "../BasicLoadable.h"
#include "IOManager.h"
#include "BasicIO.h"
#include "../Utility.h"

//namespace IO  {

	template<typename DataType>
	class IOHandler : BasicIO {
		public:
			///@brief Empty Constructor
			///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
			IOHandler( IOManager<DataType> * manager = NULL );

			///@brief Constructor from an external object, no memory management will be done.
			///@param dataObject Object to use in this handler (object has to be deleted manually)
			///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
			IOHandler( DataType * dataObject, IOManager<DataType> * manager = NULL );

			///@brief Copy Constructor
			///@param handler object to be copied
			IOHandler( const IOHandler<DataType> & handler );

			///@brief Moved Constructor
			///@param handler object to be moved
			IOHandler( IOHandler<DataType> && handler );

			///@brief Destructor
			~IOHandler();

			///@brief Cast operator into the pointer of the type of the object inside.
			operator DataType * ( );
			operator const DataType * ( ) const;

			///@brief Copy Operator
			///@param handler Object to be copied
			///@return reference to THIS
			IOHandler<DataType> & operator=( const IOHandler<DataType> & handler );

			///@brief Move operator
			///@param handler Object to be moved
			///@return reference to THIS
			IOHandler<DataType> & operator=( IOHandler<DataType> && handler );

			///@brief Get the image inside of this handler (Can be NULL if empty)
			///@return Pointer to the object stored inside this handler
			const DataType * getObject() const;
			DataType * getObject();

			///@brief Set the object using a file path (memory management is assured)
			///@param filePath Path to the file to be loaded.
			///@return Boolean if the init has worked
			bool setObject( const UTF8String & filePath );

			///@brief Set the object using an externally generated object (you still have to handle memory management in this case)
			///@param dataObject Object already defined to link to this handler
			///@return Boolean if the init has worked
			bool setObject( DataType * dataObject );

			///@brief read from a file stream
			///@param fileStream stream used to read load this object
			///@return boolean to know if the operation is a success of not.
			bool read( std::fstream * fileStream );

			///@brief write this object as binary into a file stream
			///@param fileStream stream used to write this object
			///@return boolean to know if the operation is a success of not.
			bool write( std::fstream * fileStream ) const;

		private:
			IOManager<DataType> * manager;
			DataType * object;
			DataType * objectLoaded;
			typename IOManager<DataType>::ObjectId objectId;
	};
//}

#include "IOHandler.hpp"
