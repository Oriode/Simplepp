namespace IO {

	template<typename DataType>
	Manager<DataType>::Manager() {
		// DataType has to be a BasicIO
		//static_assert( Utility::isBase<BasicSimpleIO, DataType>::value, "DataType should inherit from BasicSimpleIO" );
	}

	template<typename DataType>
	Manager<DataType>::~Manager() {
		_unload();
	}

	template<typename DataType>
	bool Manager<DataType>::write( SimpleFileStream * fileStream ) const {
		Vector<DataType *>::Size nbDatas( this->dataVector.getSize() );
		if ( !IO::write( fileStream, &nbDatas ) )
			return false;

		for ( auto it( this->dataMap.getBegin() ); it!=this->dataMap.getEnd(); this->dataMap.iterate( &it ) ) {
			if ( !IO::write( fileStream, &( this->dataMap.getIndexIt( it ) ) ) )
				return false;
			/*
			if ( !IO::write( fileStream, &( this->dataMap.getValueIt( it ).nbUses ) ) )
				return false;
			*/
			if ( !IO::write( fileStream, this->dataMap.getValueIt( it ).object ) )
				return false;
		}
		return true;
	}

	template<typename DataType>
	bool Manager<DataType>::read( SimpleFileStream * fileStream ) {
		clear();

		Vector<DataType *>::Size nbDatas;
		if ( !IO::read( fileStream, &nbDatas ) ) {
			clear();
			return false;
		}
		this->dataVector.reserve( nbDatas );

		for ( Vector<DataType *>::Size i( 0 ); i<nbDatas; i++ ) {
			OS::Path filePath;
			if ( !IO::read( fileStream, &filePath ) ) {
				clear();
				return false;
			}
			MemoryObject newMemoryObject;
			newMemoryObject.nbUses = 0;
			/*
			if ( !IO::read( fileStream, &newMemoryObject.nbUses ) ) {
				clear();
				return false;
			}
			*/
			newMemoryObject.object = new DataType();
			if ( !IO::read( fileStream, newMemoryObject.object ) ) {
				delete newMemoryObject.object;
				clear();
				return false;
			}
			if ( !_addObjectContainer( filePath, newMemoryObject ) ) {
				clear();
				return false;
			}
		}
		return true;
	}


	template<typename DataType>
	typename Manager<DataType>::ObjectId Manager<DataType>::addObject( const OS::Path & filePath ) {
		MemoryObject * objectFounded( this->dataMap[ filePath ] );
		if ( objectFounded ) {
			( objectFounded->nbUses )++;
			return ( objectFounded );
		} else {
			// Object doesn't exists, we have to add it
			DataType * newData( new DataType() );
			if ( IO::read( filePath, newData ) ) {

				MemoryObject newContainer;
				newContainer.nbUses = 1;
				newContainer.object = newData;

				return _addObjectContainer( filePath, newContainer );
			} else {
				delete newData;
				// Loading has failed
				return NULL;
			}
		}
	}


	template<typename DataType>
	void Manager<DataType>::incrUseCounter( ObjectId objectId ) {
		( const_cast< MemoryObject * >( objectId )->nbUses )++;
	}

	template<typename DataType>
	typename Vector<DataType *>::Size Manager<DataType>::getNbUses( ObjectId objectId ) const {
		return const_cast< MemoryObject * >( objectId )->nbUses;
	}

	template<typename DataType>
	typename Vector<DataType *>::Size Manager<DataType>::getNbUses( const OS::Path & filePath ) const {
		const MemoryObject * objectFounded( this->dataMap[ filePath ] );
		if ( objectFounded ) {
			return objectFounded->nbUses;
		} else {
			return Vector<DataType *>::Size( 0 );
		}
	}

	template<typename DataType>
	typename Manager<DataType>::ObjectId Manager<DataType>::_addObjectContainer( const OS::Path & filePath, MemoryObject & objectContainer ) {
		RBNode<MapObject<OS::Path, MemoryObject>> * nodeInserted( this->dataMap.insertNode( filePath, objectContainer ) );
		MemoryObject & objectContainerInserted( nodeInserted->getValue().getValue() );
		if ( !nodeInserted ) {
			delete objectContainer.object;
			// Insert has failed
			return NULL;
		}
		auto nodeNodeInserted( this->dataNodeMap.insertNode( &objectContainerInserted, nodeInserted ) );
		if ( !nodeNodeInserted ) {
			delete objectContainer.object;
			this->dataMap.eraseNode( nodeInserted );
			return NULL;
		}
		objectContainerInserted.filePath = &( nodeInserted->getValue().getIndex() );
		this->dataVector.push( &( objectContainerInserted ) );
		return &( objectContainerInserted );
	}


	template<typename DataType>
	bool Manager<DataType>::deleteObject( ObjectId objectId ) {
		auto foundedNodeNode( this->dataNodeMap.getNodeI( objectId ) );
		if ( foundedNodeNode ) {
			auto foundedNode( foundedNodeNode->getValue().getValue() );
			MemoryObject * memoryObject( &( foundedNode->getValue().getValue() ) );
			if ( memoryObject->nbUses<=1 ) {
				this->dataVector.eraseFirst( objectId );
				// This line handle the memory of the OS::Path and the MemoryObject.
				this->dataMap.eraseNode( foundedNode );
				this->dataNodeMap.eraseNode( foundedNodeNode );
			} else {
				memoryObject->nbUses--;
			}
			

		} else {
			// Seems like the object looked for doesn't exists.
		}
		// Deletion is not necessary as the MemoryObject is not a pointer. so it will be deleted whith the dataMap node.
		// delete const_cast< MemoryObject * >( objectId )-> object;
		return true;
	}

	template<typename DataType>
	const DataType * Manager<DataType>::getObject( ObjectId objectId ) const {
		return objectId->object;
	}

	template<typename DataType>
	bool Manager<DataType>::_unload() {
		for ( auto it( this->dataVector.getBegin() ); it!=this->dataVector.getEnd(); this->dataVector.iterate( &it ) ) {
			delete this->dataVector.getValueIt( it )->object;
		}
		return true;
	}

	template<typename DataType>
	bool Manager<DataType>::_load() {
		return true;
	}

	template<typename DataType>
	void Manager<DataType>::clear() {
		_unload();
		this->dataMap.clear();
		this->dataNodeMap.clear();
		this->dataVector.clear();
	}

	template<typename DataType>
	typename Manager<DataType>::MemoryObject * Manager<DataType>::_getObjectContainer( ObjectId objectId ) {
		return const_cast< MemoryObject * >( objectId );
	}

}
