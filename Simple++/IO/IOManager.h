///@file ImageManager.h
///@brief File containing the IOManager Object, and memory manager for loaded object to preserve from duplicate loading in memory
///@author Clement Gerber
///@date 19/12/16 (DMY)
#pragma once

#include "../Map.h"
#include "../UTF8String.h"
#include "../Vector.h"
#include "../IO/IO.h"
#include "../Utility.h"
#include "../Log.h"


//namespace IO {

	///@tparam DataType Type of the data to be handled inside this structure, (DO NOT USE POINTER)
	///					  DataType must have an empty constructor, and have the read()/write() method for BasicIO or BasicLoadableIO
	template<typename DataType>
	class IOManager : public BasicIO {
	public:
		struct ObjectContainer {
			DataType * object;
			typename Vector<DataType *>::Size nbUses;
			const String * filePath;
		};

		typedef const ObjectContainer * ObjectId;

		
		///@brief Empty Constructor
		IOManager();

		~IOManager();

		///@brief create an object using its filepath
		///@param filePath Path to the file used to load the object (If the object doesn't exists, it will be created and added) (Memory management is assured)
		///@return Unique Object Id of the new object (@see getObject() to retrieve the created object)(NULL (0) if the loading has failed)
		ObjectId addObject( const String & filePath );

		///@brief Get the object associated to ObjectId
		///@param objectId Object Id to use
		const DataType * getObject( ObjectId objectId ) const;

		///@brief Delete an object using its Pointer (Object will be deleted ONLY when the uses counter reach 0) (each addObject() increment the uses counter and each deleteObject() decrement it)
		///@param objectId Object id of the object to be deleted
		bool deleteObject( ObjectId objectId );

		///@brief Increment the 'uses' counter of an already registered resource (@see deleteObject() for decrementing it)
		///@param object Object to increment uses
		void incrUseCounter( ObjectId object );

		///@brief Delete all the datas
		void clear();

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;
	protected:
		ObjectId _addObjectContainer( const String & filePath, ObjectContainer & objectContainer );
		bool _load();
		bool _unload();
		ObjectContainer * _getObjectContainer( ObjectId objectId );

		Map< String, ObjectContainer > dataMap;
		Map< ObjectId , RBNode< MapObject< String, ObjectContainer > > * > dataNodeMap;
		Vector< ObjectId > dataVector;
	};

//}

#include "IOManager.hpp"
