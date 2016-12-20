template<typename DataType>
IOHandlerLoadable<DataType>::IOHandlerLoadable( IOManagerLoadable<DataType> * manager ) :
	manager( manager ),
	object( NULL ),
	objectId( 0 ),
	bMemoryManaged( false ),
	bUseMemoryManager( ( manager ) ? true : false ) {

}

template<typename DataType>
IOHandlerLoadable<DataType>::IOHandlerLoadable( DataType * dataObject, IOManagerLoadable<DataType> * manager ) {
	lock();
	{
		_setLoaded( dataObject );
		this -> object = dataObject;
		this -> manager = manager;
		this -> objectId = 0;
		this -> bMemoryManaged = false;
	}
	unlock();
}

template<typename DataType>
IOHandlerLoadable<DataType>::IOHandlerLoadable( const UTF8String & filePath, IOManagerLoadable<DataType> * manager ) {
	lock();
	{
		this -> manager = manager;
		this -> filePath = filePath;
		this -> bMemoryManaged = true;
		if ( this -> manager ) {
			this -> objectId = this -> manager -> addObject( filePath );
			if ( this -> objectId ) {
				this -> object = const_cast< DataType * >( this -> manager -> getObject( this -> objectId ) );
			} else {
				// The addObject has failed
				this -> object = NULL;
				this -> objectId = 0;
				this -> filePath.clear();
				this -> bMemoryManaged = false;
			}
			_setLoaded( this -> object );
		} else {
			this -> object = NULL;
		}
	}
	unlock();
}

template<typename DataType>
IOHandlerLoadable<DataType>::IOHandlerLoadable( const IOHandlerLoadable<DataType> & handler ) {
	lock();
	{
		this -> filePath = handler.filePath;
		this -> bMemoryManaged = handler.bMemoryManaged;
		this -> bUseMemoryManager = handler.bUseMemoryManager;

		if ( this -> bMemoryManaged ) {
			if ( this -> bUseMemoryManager ) {
				this -> objectId = handler.objectId;
				this -> manager = handler.manager;
				this -> manager -> incrUseCounter( this -> objectId );
			}
			this -> object = new DataType( handler.object );
		} else {
			this -> object = handler.object;
		}

	}
	unlock();
}





template<typename DataType>
IOHandlerLoadable<DataType>::IOHandlerLoadable( IOHandlerLoadable<DataType> && handler ) :
	manager( Utility::toRValue( handler.manager ) ),
	object( Utility::toRValue( handler.object ) ),
	filePath( Utility::toRValue( handler.filePath ) ),
	objectId( Utility::toRValue( handler.objectId ) ),
	bMemoryManaged( Utility::toRValue( handler.bMemoryManaged ) ),
	bUseMemoryManager( Utility::toRValue( handler.bUseMemoryManager ) ) {
	handler.bMemoryManaged = false;
}



template<typename DataType>
IOHandlerLoadable<DataType>::~IOHandlerLoadable() {
	if ( this -> bMemoryManaged ) {
		// The file is internally handled
		if ( this -> bUseMemoryManager ) {
			assert( this -> manager );
			assert( this -> objectId );
			this -> manager -> deleteObject( this -> objectId );
		} else {
			delete this -> object;
		}
	}
}



template<typename DataType>
IOHandlerLoadable<DataType>::operator DataType * ( ) {
	return this -> object;
}
template<typename DataType>
IOHandlerLoadable<DataType>::operator const DataType * ( ) const {
	return this -> object;
}

template<typename DataType>
IOHandlerLoadable<DataType> & IOHandlerLoadable<DataType>::operator=( const IOHandlerLoadable<DataType> & handler ) {
	lock();
	{
		if ( this -> bMemoryManaged ) {
			// The file is internally handled
			if ( this -> bUseMemoryManager ) {
				assert( this -> manager );
				assert( this -> objectId );
				this -> manager -> deleteObject( this -> objectId );
			} else {
				_unloadObjectLoaded( this -> object );
			}
		}

		this -> filePath = handler.filePath;
		this -> bMemoryManaged = handler.bMemoryManaged;
		this -> bUseMemoryManager = handler.bUseMemoryManager;

		if ( this -> bMemoryManaged ) {
			if ( this -> bUseMemoryManager ) {
				this -> objectId = handler.objectId;
				this -> manager = handler.manager;
				this -> manager -> incrUseCounter( this -> objectId );
			}
			this -> object = new DataType( handler.object );
		} else {
			this -> object = handler.object;
		}
	}
	unlock();
}

template<typename DataType>
IOHandlerLoadable<DataType> & IOHandlerLoadable<DataType>::operator=( IOHandlerLoadable<DataType> && handler ) {
	this -> manager = Utility::toRValue( handler.manager );
	this -> object = Utility::toRValue( handler.object );
	this -> filePath = Utility::toRValue( handler.filePath );
	this -> objectId = Utility::toRValue( handler.objectId );
	this -> bMemoryManaged = Utility::toRValue( handler.bMemoryManaged );
	this -> bUseMemoryManager = Utility::toRValue( handler.bUseMemoryManager );
	handler.bMemoryManaged = false;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::setObject( const UTF8String & filePath ) {
	lock();
	{
		if ( this -> bMemoryManaged ) {
			delete this -> object;
		} else
			this -> bMemoryManaged = true;

		if ( this -> bUseMemoryManager ) {
			assert( this -> manager );
			assert( this -> objectId );
			this -> filePath.clear();

			// Delete the old one
			this -> manager -> deleteObject( this -> objectId );

			// Now Retrieve the now object
			this -> objectId = this -> manager -> addObject( filePath );

			if ( !this -> objectId ) {
				// The addObject has failed
				this -> object = NULL;
				this -> bMemoryManaged = false;
				unlock();
				return false;
			}
			this -> object = const_cast< DataType * >( this -> manager -> getObject( this -> objectId ) );
			_setLoaded( this -> object );
		} else {
			this -> filePath = filePath;
			if ( isLoaded() ) {
				this -> object = new DataType();
				if ( !IO::read( this -> filePath, this -> object ) ) {
					delete this -> object;
					this -> object = NULL;
					unlock();
					return false;
				}
			} else {
				this -> object = NULL;
			}
		}
	}
	unlock();
	return true;
}


template<typename DataType>
bool IOHandlerLoadable<DataType>::setObject( DataType * dataObject ) {
	lock();
	{
		if ( this -> bMemoryManaged ) {
			this -> bMemoryManaged = false;
			this -> filePath.clear();
			if ( this -> bUseMemoryManager ) {
				assert( this -> manager );
				assert( this -> objectId );
				this -> manager -> deleteObject( this -> objectId );
			} else {
				delete this -> object;
			}
		}

		this -> object = dataObject;

		_setLoaded( dataObject );
	}
	unlock();
	return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::onLoad() {
	if ( this -> bMemoryManaged ) {
		// The file is internally handled
		if ( this -> bUseMemoryManager ) {
			assert( this -> manager );
			assert( this -> objectId );
			if ( this -> manager -> isLoaded() ) {
				this -> object = const_cast< DataType * >( this -> manager -> getObject( this -> objectId ) );
			} else {
				error( "Trying to load an handler before its Manager" );
				return false;
			}
		} else {
			this -> object = new DataType();
			if ( this -> filePath.getSize() ) {
				if ( !IO::read( this -> filePath, this -> object ) ) {
					delete this -> object;
					this -> object = NULL;
					return false;
				}
			} else {
				delete this -> object;
				this -> object = NULL;
				return false;
			}
		}
	} else {
		return _loadObject( this -> object );
	}
	return true;
}


template<typename DataType>
bool IOHandlerLoadable<DataType>::onUnload() {
	if ( this -> bMemoryManaged ) {
		// The file is internally handled
		if ( this -> bUseMemoryManager ) {
			assert( this -> manager );
			assert( this -> objectId );
			// Nothing to do

		} else {
			_unloadObjectLoaded( this -> object );
		}
	} else {
		return _unloadObject( this -> object );
	}
	return true;
}



template<typename DataType>
bool IOHandlerLoadable<DataType>::onRead( std::fstream * fileStream ) {
	if ( this -> bMemoryManaged ) {
		this -> filePath.clear();
		// If the object is memory handled
		if ( this -> bUseMemoryManager ) {
			// If we are using a Manager
			assert( this -> manager );
			this -> manager -> deleteObject( this -> objectId );


			// We won't use it anymore
			this -> bUseMemoryManager = false;
		} else {

		}
		this -> object = new DataType();
		if ( !IO::read( fileStream, this -> object ) ) {
			this -> bMemoryManaged = false;
			this -> bUseMemoryManager = false;
			delete this -> object;
			this -> object = NULL;
			return false;
		}
	} else {
		this -> bMemoryManaged = true;
		if ( this -> object ) {
			if ( !IO::read( fileStream, this -> object ) ) {
				return false;
			}
		}
	}
	return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::onWrite( std::fstream * fileStream ) const {
	if ( this -> object ) {
		if ( !IO::write( fileStream, this -> object ) )
			return false;
	}
	return true;
}



template<typename DataType>
bool IOHandlerLoadable<DataType>::_unloadObjectLoaded( BasicLoadable * object ) {
	//object -> unload();
	delete this -> object;
	this -> object = NULL;
	return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::_unloadObjectLoaded( ... ) {
	delete this -> object;
	this -> object = NULL;
	return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::_loadObject( ... ) {
	return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::_loadObject( BasicLoadable * object ) {
	if ( object )
		return object -> load();
	else
		return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::_unloadObject( ... ) {
	return true;
}

template<typename DataType>
bool IOHandlerLoadable<DataType>::_unloadObject( BasicLoadable * object ) {
	if ( object )
		return object -> unload();
	else
		return true;
}

template<typename DataType>
void IOHandlerLoadable<DataType>::_setLoaded( ... ) {
	this -> setLoaded( true );
}

template<typename DataType>
void IOHandlerLoadable<DataType>::_setLoaded( BasicLoadable * dataObject ) {
	this -> setLoaded( ( dataObject ) ? dataObject -> isLoaded() : false );
}

template<typename DataType>
const DataType * IOHandlerLoadable<DataType>::getObject() const {
	return this -> object;
}
template<typename DataType>
DataType * IOHandlerLoadable<DataType>::getObject() {
	return this -> object;
}
