///@file ImageHandler.h
///@brief File containing the IOHandler Object, an object containing an object of type DataType, externally loaded or internally
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "../BasicLoadable.h"
#include "IOManager.h"
#include "BasicIO.h"

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

			///@brief Constructor from File Path (UTF8) (object will be loaded and memory managed)
			///@param filePath Path to the file to be loaded
			///@param manager Pointer to a IOManager, to dispatch memory management into it and ensure no duplicate (Cannot be changed)
			//IOHandler( const UTF8String & filePath, IOManager<DataType> * manager = NULL );

			///@brief Destructor
			~IOHandler();

			///@brief Cast operator into the pointer of the type of the object inside.
			operator DataType * ( );
			operator const DataType * ( ) const;

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
	};

	template<typename DataType>
	IOHandler<DataType>::IOHandler( IOManager<DataType> * manager ) :
		manager(manager),
		object(NULL),
		objectLoaded(NULL)
	{

	}

	template<typename DataType>
	IOHandler<DataType>::IOHandler( DataType * dataObject, IOManager<DataType> * manager ) :
		manager( manager ),
		object( dataObject ),
		objectLoaded( NULL )
	{

	}


	template<typename DataType>
	IOHandler<DataType>::~IOHandler() {
		if ( this -> manager == NULL )
			delete this -> objectLoaded;
	}


	template<typename DataType>
	IOHandler<DataType>::operator DataType * ( ) {
		return this -> object;
	}
	template<typename DataType>
	IOHandler<DataType>::operator const DataType * ( ) const {
		return this -> object;
	}

	template<typename DataType>
	const DataType * IOHandler<DataType>::getObject() const {
		return this -> object;
	}
	template<typename DataType>
	DataType * IOHandler<DataType>::getObject() {
		return this -> object;
	}


	template<typename DataType>
	bool IOHandler<DataType>::setObject( const UTF8String & filePath ) {
		
		if ( this -> manager ) {
			this -> manager -> deleteObject( this -> objectLoaded );
			this -> objectLoaded = const_cast<DataType *>(this -> manager -> addObject( filePath ));
			this -> object = this -> objectLoaded;
			if ( objectLoaded == NULL )
				return false;
		} else {
			delete this -> objectLoaded;
			this -> objectLoaded = new DataType();
			if ( !IO::read( filePath, this -> objectLoaded ) ) {
				delete this -> objectLoaded;
				this -> object = NULL;
				return false;
			} else {
				this -> object = this -> objectLoaded;
			}
		}

		return true;
	}

	template<typename DataType>
	bool IOHandler<DataType>::setObject( DataType * dataObject ) {
		if ( this -> manager )
			this -> manager -> deleteObject( this -> objectLoaded );
		else 
			delete this -> objectLoaded;

		this -> objectLoaded = NULL;
		this -> object = dataObject;

		return true;
	}

	template<typename DataType>
	bool IOHandler<DataType>::read( std::fstream * fileStream ) {
		if ( this -> object == NULL )
			return true;
		return IO::read( fileStream, this -> object );
	}


	template<typename DataType>
	bool IOHandler<DataType>::write( std::fstream * fileStream ) const {
		if ( this -> object == NULL )
			return true;
		return IO::write( fileStream, this -> object );
	}



//}
