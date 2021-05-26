///@file IOHandlerLoadable.h
///@brief File containing the IOHandlerLoadable Object, an object containing an object loadable of type DataType, externally loaded or internally
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "BasicLoadableIO.h"
#include "IOHandler.h"
#include "IOManagerLoadable.h"

namespace IO {


	///@brief Part of the IOManagerLoadable.
	template<typename DataType>
	class IOHandlerLoadable : public BasicLoadableIO {
	public:
		///@brief Empty Constructor
		///@param manager Memory Manager used in this object (Cannot be changed afterwards)
		IOHandlerLoadable( IOManagerLoadable<DataType> * manager = NULL );

		///@brief Constructor from an external object, no memory management will be done.
		///@param dataObject Object to use in this handler (object has to be deleted manually)
		///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
		IOHandlerLoadable( DataType * dataObject, IOManagerLoadable<DataType> * manager = NULL );

		///@brief Constructor from File Path (object will be loaded and memory managed)
		///@param filePath Path to the file to be loaded
		///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
		IOHandlerLoadable( const String & filePath, IOManagerLoadable<DataType> * manager = NULL );

		///@brief Copy Constructor
		///@param handler object to be copied
		IOHandlerLoadable( const IOHandlerLoadable<DataType> & handler );

		///@brief Moved Constructor
		///@param handler object to be moved
		IOHandlerLoadable( IOHandlerLoadable<DataType> && handler );

		///@brief Destructor
		~IOHandlerLoadable();

		///@brief Cast operator into the pointer of the type of the object inside.
		operator DataType * ( );
		operator const DataType * ( ) const;

		///@brief Copy Operator
		///@param handler Object to be copied
		///@return reference to THIS
		IOHandlerLoadable<DataType> & operator=( const IOHandlerLoadable<DataType> & handler );

		///@brief Move operator
		///@param handler Object to be moved
		///@return reference to THIS
		IOHandlerLoadable<DataType> & operator=( IOHandlerLoadable<DataType> && handler );

		///@brief Set the object using a file path (memory management is assured) (getObject() will return NULL if the handler is not loaded)
		///@param filePath Path to the file to be loaded.
		///@return Boolean if the init has worked
		bool setObject( const OS::Path & filePath );

		///@brief Set the object using an externally generated object (you still have to handle memory management in this case) (getObject() will return dataObject in every cases)
		///@param dataObject Object already defined to link to this handler
		///@return Boolean if the init has worked
		bool setObject( DataType * dataObject );

		///@brief Get the image inside of this handler (Can be NULL if empty)
		///@return Pointer to the object stored inside this handler
		const DataType * getObject() const;
		DataType * getObject();

	protected:
		///@brief function to be overloaded to set the action when reading from a stream.
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onRead(FileStream* fileStream ) override;

		///@brief function to be overloaded to set the action when writing from a stream.
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onWrite(FileStream* fileStream ) const override;

		///@brief function to be overloaded to add action during the loading process.
		///@return True if the loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if the unloading has succeeded, False otherwise
		virtual bool onUnload() override;

	private:
		bool _unloadObjectLoaded( BasicLoadable * object );
		bool _unloadObjectLoaded( ... );

		void _setLoaded( BasicLoadable * );
		void _setLoaded( ... );

		bool _loadObject( BasicLoadable * object );
		bool _loadObject( ... );

		bool _unloadObject( BasicLoadable * object );
		bool _unloadObject( ... );

		IOManagerLoadable<DataType> * manager;
		DataType * object;
		String filePath;
		typename IOManagerLoadable<DataType>::ObjectId objectId;
		bool bMemoryManaged;
		bool bUseMemoryManager;
	};

}

#include "IOHandlerLoadable.hpp"
