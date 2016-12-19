///@file ImageManager.h
///@brief File containing the IOLoadableManager Object, and memory manager for loaded object to preserve from duplicate loading in memory
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "BasicLoadableIO.h"
#include "IOManager.h"
#include "../Utility.h"

//namespace IO {
	
	template<typename DataType>
	class IOLoadableManager : public BasicLoadableIO, public IOManager<DataType> {
	public:
		///@brief Empty Constructor
		IOLoadableManager();

		///@brief Destructor
		~IOLoadableManager();

		///@brief create an object using its filepath
		///@param filePath Path to the file used to load the object (UTF8 Encoded) (If the object doesn't exists, it will be created and added) (Memory management is assured)
		///@return Pointer to the object (May already exists or freshly created) (Can be NULL if the loading has failed)
		const DataType * addObject( const UTF8String & filePath );


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

	template<typename DataType>
	const DataType * IOLoadableManager<DataType>::addObject( const UTF8String & filePath ) {
		DataType * newObject( IOManager::addObject( filePath ) );
		if ( isLoaded() )
			newObject -> load();
		return newObject;
	}

	template<typename DataType>
	bool IO::IOLoadableManager<DataType>::onUnload() {
		for ( auto it( this -> dataVector.getBegin() ); it != this -> dataVector.getEnd(); this -> dataVector.iterate( &it ) ) {
			this -> dataVector.getValueIt( it ) -> object -> unload();
		}
	}

	template<typename DataType>
	bool IO::IOLoadableManager<DataType>::onLoad() {
		for ( auto it( this -> dataVector.getBegin() ); it != this -> dataVector.getEnd(); this -> dataVector.iterate( &it ) ) {
			this -> dataVector.getValueIt( it ) -> object -> load();
		}
	}

	template<typename DataType>
	IOLoadableManager<DataType>::IOLoadableManager() {
		// DataType has to be a loadable
		static_assert( Utility::isBase<BasicLoadable, DataType>::value, "DataType Should inherit from BasicLoadable" );
	}

	template<typename DataType>
	IOLoadableManager<DataType>::~IOLoadableManager() {

	}

	template<typename DataType>
	bool IOLoadableManager<DataType>::onRead( std::fstream * fileStream ) {
		return IOManager<DataType>::read( fileStream );
	}

	template<typename DataType>
	bool IOLoadableManager<DataType>::onWrite( std::fstream * fileStream ) const {
		return IOManager<DataType>::write( fileStream );
	}

//}
