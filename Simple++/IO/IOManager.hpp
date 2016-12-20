//namespace IO {

	template<typename DataType>
	IOManager<DataType>::IOManager() {
		// DataType has to be a BasicIO
		static_assert( Utility::isBase<BasicSimpleIO, DataType>::value, "DataType should inherit from BasicSimpleIO" );
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
			RBNode<MapObject<UTF8String, ObjectContainer>> * nodeInserted( this -> dataMap.insertNode( filePath, newContainer ) );
			if ( !nodeInserted ) {
				delete newContainer.object;
				clear();
				return false;
			}
			auto objectInserted( this -> dataNodeMap.insert( newContainer.object, nodeInserted ) );
			if ( !objectInserted ) {
				clear();
				return false;
			}
			this -> dataVector.push( &(nodeInserted -> getValue().getValue()) );
		}
		return true;
	}


	template<typename DataType>
	const DataType * IOManager<DataType>::addObject( const UTF8String & filePath ) {
		ObjectContainer * objectFounded( this -> dataMap[filePath] );
		if ( objectFounded ) {
			( objectFounded -> nbUses )++;
			return ( objectFounded -> object );
		} else {
			// Image doesn't exists, we have to add it
			DataType * newData( new DataType() );
			if ( IO::read( filePath, newData ) ) {

				ObjectContainer newContainer;
				newContainer.nbUses = 1;
				newContainer.object = newData;

				RBNode<MapObject<UTF8String, ObjectContainer>> * nodeInserted( this -> dataMap.insertNode( filePath, newContainer ) );
				if ( !nodeInserted ) {
					delete newData;
					// Insert has failed
					return NULL;
				} 
				auto nodeNodeInserted( this -> dataNodeMap.insertNode( newData, nodeInserted ) );
				if ( !nodeNodeInserted ) {
					delete newData;
					this -> dataMap.eraseNode( nodeInserted );
					return NULL;
				}

				this -> dataVector.push( &(nodeInserted -> getValue().getValue()) );
				return newData;
			} else {
				delete newData;
				// Loading has failed
				return NULL;
			}
		}
	}

	/*template<typename DataType>
	const DataType * IOManager<DataType>::getObject( const UTF8String & filePath ) {
		ObjectContainer * objectFounded( this -> dataMap[filePath] );
		if ( objectFounded ) {
			( objectFounded -> nbUses )++;
			return  objectFounded -> object;
		} else {
			// Image doesn't exists, we have to add it
			DataType newData( new DataType() );
			if ( IO::read( filePath, *newImage ) ) {

				ObjectContainer newContainer;
				newContainer.nbUses = 1;
				newContainer.object = newData;


				ObjectContainer * dataInserted( this -> dataMap.insert( filePath, newContainer ) );
				if ( dataInserted ) {
					this -> dataVector.push( dataInserted );
					return newData;
				} else {
					delete newData;
					// Insert has failed
					return NULL;
				}
			} else {
				delete newData;
				// Loading has failed
				return NULL;
			}
		}
	}*/

	/*template<typename DataType>
	void IO::IOManager<DataType>::deleteObject( const UTF8String & filePath ) {
		ObjectContainer * objectFounded( this -> dataMap[filePath] );
		if ( objectFounded ) {
			if ( objectFounded -> nbUses <= 1 ) {
				delete objectFounded -> object; 
				this -> dataMap.eraseIndex( filePath );
				this -> dataVector.eraseFirst( objectFounded );
			} else {
				( objectFounded -> nbUses )--;
			}
		} else {
			// Seems like the object looked for doesn't exists.
		}
	}*/

	template<typename DataType>
	bool IOManager<DataType>::deleteObject( DataType * object ) {
		auto foundedNodeNode( this -> dataNodeMap.getNodeI( object ) );
		if ( foundedNodeNode ) {
			auto foundedNode( foundedNodeNode -> getValue().getValue() );
			ObjectContainer * objectContainer( &( foundedNode -> getValue().getValue() ) );
			this -> dataVector.eraseFirst( objectContainer );
			this -> dataMap.eraseNode( foundedNode );
			this -> dataNodeMap.eraseNode( foundedNodeNode );

		} else {
			// Seems like the object looked for doesn't exists.
		}
		delete object;
		return true;
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
	}



//}
