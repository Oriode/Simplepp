

template<typename DataType>
IOManagerLoadable<DataType>::IOManagerLoadable( const IOManager<DataType> & manager ) {
	setLoaded( true );

	for ( auto it( manager.dataMap.getBegin() ); it != manager.dataMap.getEnd(); manager.dataMap.iterate( &it ) ) {
		ObjectContainer newContainer;
		newContainer.object = new DataType( *( manager.dataMap.getValueIt( it ).object ) );
		newContainer.nbUses = manager.dataMap.getValueIt( it ).nbUses;

		_addObjectContainer( manager.dataMap.getIndexIt( it ), newContainer );
	}


}

template<typename DataType>
typename IOManagerLoadable<DataType>::ObjectId IOManagerLoadable<DataType>::addObject( const UTF8String & filePath ) {
	ObjectContainer * objectFounded( this -> dataMap[filePath] );
	if ( objectFounded ) {
		( objectFounded -> nbUses )++;
		return objectFounded;
	} else {
		// Object doesn't exists, we have to add it
		if ( isLoaded() ) {
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
		} else {
			ObjectContainer newContainer;
			newContainer.nbUses = 1;
			newContainer.object = NULL;

			return _addObjectContainer( filePath, newContainer );
		}
	}
}


template<typename DataType>
bool IOManagerLoadable<DataType>::onUnload() {
	for ( auto it( this -> dataVector.getBegin() ); it != this -> dataVector.getEnd(); this -> dataVector.iterate( &it ) ) {
		ObjectContainer * objectContainer( _getObjectContainer( this -> dataVector.getValueIt( it ) ) );
		delete objectContainer -> object;
		objectContainer -> object = NULL;
	}
	return true;
}

template<typename DataType>
bool IOManagerLoadable<DataType>::onLoad() {
	for ( auto it( this -> dataVector.getBegin() ); it != this -> dataVector.getEnd(); this -> dataVector.iterate( &it ) ) {
		ObjectContainer * objectContainer( _getObjectContainer( this -> dataVector.getValueIt( it ) ) );
		objectContainer -> object = new DataType();
		if ( !IO::read( *( objectContainer -> filePath ), objectContainer -> object ) ) {
			for ( auto it2( this -> dataVector.getBegin() ); it2 != this -> dataVector.getEnd(); this -> dataVector.iterate( &it2 ) ) {
				ObjectContainer * objectContainer2( _getObjectContainer( this -> dataVector.getValueIt( it ) ) );
				delete objectContainer2 -> object;
				objectContainer2 -> object = NULL;
			}
			return false;
		}
	}
	return true;
}

template<typename DataType>
IOManagerLoadable<DataType>::IOManagerLoadable() {
}

template<typename DataType>
IOManagerLoadable<DataType>::~IOManagerLoadable() {

}

template<typename DataType>
bool IOManagerLoadable<DataType>::onRead( std::fstream * fileStream ) {
	return IOManager<DataType>::read( fileStream );
}

template<typename DataType>
bool IOManagerLoadable<DataType>::onWrite( std::fstream * fileStream ) const {
	return IOManager<DataType>::write( fileStream );
}


