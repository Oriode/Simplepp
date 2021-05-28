///@file ImageManager.h
///@brief File containing the IOManager Object, an memory manager for loaded object to preserve from duplicate loading in memory. When a new resource is needed, call the addObject() method to get an identifier of the loaded resource. (loaded automaticaly if necessary). When the use if finished, call the deleteObject() method to remove the use. (unloaded if not used anymore by anyone).
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "../Map.h"
#include "../UTF8String.h"
#include "../Vector.h"
#include "../IO/IO.h"
#include "../Utility.h"
#include "../Log.h"


namespace IO {

	///@tparam DataType Type of the data to be handled inside this structure, (DO NOT USE POINTER)
	///					  DataType must have an empty constructor, and have the read()/write() method for BasicIO or BasicLoadableIO
	template<typename DataType>
	class IOManager : public BasicIO {
	public:
		struct MemoryObject {
			DataType * object;
			typename Vector<DataType *>::Size nbUses;
			const OS::Path * filePath;
		};

		typedef const MemoryObject * ObjectId;


		///@brief Empty Constructor
		IOManager();

		~IOManager();

		///@brief create an object using its filepath
		///@param filePath Path to the file used to load the object (If the object doesn't exists, it will be created and added) (Memory management is assured)
		///@return Unique Object Id of the new object (@see getObject() to retrieve the created object)(NULL (0) if the loading has failed)
		ObjectId addObject( const OS::Path & filePath );

		///@brief Get the object associated to ObjectId
		///@param objectId Object Id to use
		const DataType * getObject( ObjectId objectId ) const;

		///@brief Delete an object using its Pointer (Object will be deleted ONLY when the uses counter reach 0) (each addObject() increment the uses counter and each deleteObject() decrement it)
		///@param objectId Object id of the object to be deleted
		bool deleteObject( ObjectId objectId );

		///@brief Increment the 'uses' counter of an already registered resource (@see deleteObject() for decrementing it)
		///@param object Object to increment uses
		void incrUseCounter( ObjectId object );

		typename Vector<DataType *>::Size getNbUses( ObjectId objectId ) const;
		typename Vector<DataType *>::Size getNbUses( const OS::Path & filePath ) const;


		///@brief Delete all the datas
		void clear();

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( SimpleFileStream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( SimpleFileStream * fileStream ) const;
	protected:
		ObjectId _addObjectContainer( const OS::Path & filePath, MemoryObject & objectContainer );
		bool _load();
		bool _unload();
		MemoryObject * _getObjectContainer( ObjectId objectId );

		Map< OS::Path, MemoryObject> dataMap;
		Map< ObjectId, RBNode< MapObject< OS::Path, MemoryObject> > * > dataNodeMap;
		Vector< ObjectId > dataVector;
	};

}

#include "IOManager.hpp"
