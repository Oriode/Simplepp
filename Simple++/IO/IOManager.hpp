//namespace IO {

	template<typename DataType>
	IOManager<DataType>::IOManager() {
		// DataType has to be a BasicIO
		//static_assert( Utility::isBase<BasicSimpleIO, DataType>::value, "DataType should inherit from BasicSimpleIO" );
	}

	template<typename DataType>
	IOManager<DataType>::~IOManager() {
		_unload();
	}

	template<typename DataType>
	bool IOManager<DataType>::write( std::fstream * fileStream ) const {
		Vector<DataType *>::Size nbDatas( this -> dataVector.getSize() );
		if ( !IO::write( fileStream, &nbDatas ) )
			return false;

		for ( auto it( this -> dataMap.getBegin() ); it != this -> dataMap.getEnd(); this -> dataMap.iterate( &it ) ) {
			if ( !IO::write( fileStream, &( this -> dataMap.getIndexIt( it ) ) ) )
				return false;
			if ( !IO::write( fileStream, &(this -> dataMap.getValueIt( it ).nbUses) ) )
				return false;
			if ( !IO::write( fileStream, this -> dataMap.getValueIt( it ).object ) )
				return false;
		}
		return true;
	}

	template<typename DataType>
	bool IOManager<DataType>::read( std::fstream * fileStream ) {
		clear();

		Vector<DataType *>::Size nbDatas;
		if ( !IO::read( fileStream, &nbDatas ) ) {
			clear();
			return false;
		}
		this -> dataVector.reserve( nbDatas );

		for ( Vector<DataType *>::Size i( 0 ); i < nbDatas; i++ ) {
			UTF8String filePath;
			if ( !IO::read( fileStream, &filePath ) ) {
				clear();
				return false;
			}
			ObjectContainer newContainer;
			newContainer.nbUses = 0;
			if ( !IO::read( fileStream, &newContainer.nbUses ) ) {
				clear();
				return false;
			}
			newContainer.object = new DataType();
			if ( !IO::read( fileStream, newContainer.object ) ) {
				delete newContainer.object;
				clear();
				return false;
			}
			if ( !_addObjectContainer( filePath, newContainer ) ) {
				clear();
				return false;
			}
		}
		return true;
	}


	template<typename DataType>
	typename IOManager<DataType>::ObjectId IOManager<DataType>::addObject( const UTF8String & filePath ) {
		ObjectContainer * objectFounded( this -> dataMap[filePath] );
		if ( objectFounded ) {
			( objectFounded -> nbUses )++;
			return ( objectFounded );
		} else {
			// Object doesn't exists, we have to add it
			DataType * newData( new DataType() );
			if ( IO::read( filePath, newData ) ) {

				ObjectContainer newContainer;
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
	void IOManager<DataType>::incrUseCounter( ObjectId objectId ) {
		( const_cast< ObjectContainer * >( objectId ) -> nbUses )++;
	}



	template<typename DataType>
	typename IOManager<DataType>::ObjectId IOManager<DataType>::_addObjectContainer( const UTF8String & filePath, ObjectContainer & objectContainer ) {
		RBNode<MapObject<UTF8String, ObjectContainer>> * nodeInserted( this -> dataMap.insertNode( filePath, objectContainer ) );
		ObjectContainer & objectContainerInserted( nodeInserted -> getValue().getValue() );
		if ( !nodeInserted ) {
			delete objectContainer.object;
			// Insert has failed
			return NULL;
		}
		auto nodeNodeInserted( this -> dataNodeMap.insertNode( &objectContainerInserted, nodeInserted ) );
		if ( !nodeNodeInserted ) {
			delete objectContainer.object;
			this -> dataMap.eraseNode( nodeInserted );
			return NULL;
		}
		objectContainerInserted.filePath = &(nodeInserted -> getValue().getIndex());
		this -> dataVector.push( &( objectContainerInserted ) );
		return &( objectContainerInserted );
	}


	template<typename DataType>
	bool IOManager<DataType>::deleteObject( ObjectId objectId ) {
		auto foundedNodeNode( this -> dataNodeMap.getNodeI( objectId ) );
		if ( foundedNodeNode ) {
			auto foundedNode( foundedNodeNode -> getValue().getValue() );
			ObjectContainer * objectContainer( &( foundedNode -> getValue().getValue() ) );
			this -> dataVector.eraseFirst( objectId );
			this -> dataMap.eraseNode( foundedNode );
			this -> dataNodeMap.eraseNode( foundedNodeNode );

		} else {
			// Seems like the object looked for doesn't exists.
		}
		delete const_cast<ObjectContainer *>(objectId) -> object;
		return true;
	}

	template<typename DataType>
	const DataType * IOManager<DataType>::getObject( ObjectId objectId ) const {
		return objectId -> object;
	}

	template<typename DataType>
	bool IOManager<DataType>::_unload() {
		for ( auto it( this -> dataVector.getBegin() ); it != this -> dataVector.getEnd(); this -> dataVector.iterate( &it ) ) {
			delete this -> dataVector.getValueIt( it ) -> object;
		}
		return true;
	}

	template<typename DataType>
	bool IOManager<DataType>::_load() {
		return true;
	}

	template<typename DataType>
	void IOManager<DataType>::clear() {
		_unload();
		this -> dataMap.clear();
		this -> dataNodeMap.clear();
		this -> dataVector.clear();
	}

	template<typename DataType>
	typename IOManager<DataType>::ObjectContainer * IOManager<DataType>::_getObjectContainer( ObjectId objectId ) {
		return const_cast< ObjectContainer * >( objectId );
	}

//}
