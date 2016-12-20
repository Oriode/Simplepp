///@file ImageManager.h
///@brief File containing the IOLoadableManager Object, and memory manager loadable for object to preserve from duplicate loading in memory
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "BasicLoadableIO.h"
#include "IOManager.h"
#include "../Utility.h"

//namespace IO {
	
	template<typename DataType>
	class IOManagerLoadable : public BasicLoadableIO, public IOManager<DataType> {
	public:
		using IOManager<DataType>::ObjectId;

		///@brief Empty Constructor
		IOManagerLoadable();

		///@brief Constructor from an IOManager 
		IOManagerLoadable( const IOManager<DataType> & manager );

		///@brief Destructor
		~IOManagerLoadable();

		///@brief create an object using its filepath (If the Manager is no loaded (@see isLoaded()), getObject() will return NULL )
		///@param filePath Path to the file used to load the object (UTF8 Encoded) (If the object doesn't exists, it will be created and added) (Memory management is assured)
		///@return Unique Object Id of the new object (@see getObject() to retrieve the created object) (NULL (0) if the loading has failed)
		ObjectId addObject( const UTF8String & filePath );

		using BasicLoadableIO::read;
		using BasicLoadableIO::write;

	protected:
		///@brief function to be overloaded to set the action when reading from a stream.
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onRead( std::fstream * fileStream ) override;

		///@brief function to be overloaded to set the action when writing from a stream.
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		virtual bool onWrite( std::fstream * fileStream ) const override;

		///@brief function to be overloaded to add action during the loading process.
		///@return True if the loading has succeeded, False otherwise
		virtual bool onLoad() override;

		///@brief function to be overloaded to add action during the unloading process.
		///@return True if the unloading has succeeded, False otherwise
		virtual bool onUnload() override;

	private:

	};
//}

#include "IOManagerLoadable.hpp"
