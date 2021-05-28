#pragma once

#include "BasicIO.h"


namespace IO {

	///@brief Part of the IOManager.
	template<typename DataType>
	class IOManagedResource : public BasicIO {
	public:
		///@brief Empty Constructor
		///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
		IOManagedResource( IOManager<DataType> * manager = NULL );

		///@brief Constructor from an external object, no memory management will be done.
		///@param dataObject Object to use in this handler (object has to be deleted manually)
		///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
		IOManagedResource( DataType * dataObject, IOManager<DataType> * manager = NULL );

		///@brief Copy Constructor
		///@param handler object to be copied
		IOManagedResource( const IOManagedResource<DataType> & handler );

		///@brief Moved Constructor
		///@param handler object to be moved
		IOManagedResource( IOManagedResource<DataType> && handler );

		///@brief Destructor
		~IOManagedResource();

		///@brief Cast operator into the pointer of the type of the object inside.
		operator DataType * ( );
		operator const DataType * ( ) const;

		///@brief Copy Operator
		///@param handler Object to be copied
		///@return reference to THIS
		IOManagedResource<DataType> & operator=( const IOManagedResource<DataType> & handler );

		///@brief Move operator
		///@param handler Object to be moved
		///@return reference to THIS
		IOManagedResource<DataType> & operator=( IOManagedResource<DataType> && handler );

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
		void _deleteObject();
		IOManager<DataType> * manager;
		DataType * object;
		typename IOManager<DataType>::ObjectId managerObjectId;
	};

}

#include "IOManagedResource.hpp"