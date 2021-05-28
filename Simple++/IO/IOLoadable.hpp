namespace IO {

	template<typename DataType>
	IOLoadable<DataType>::IOLoadable( const OS::Path & filePath ) : 
	filePath(filePath),
	object(NULL) {}

	template<typename DataType>
	IOLoadable<DataType>::~IOLoadable() {
		if ( !this->object ) {
			delete this->object;
		}
	}

	template<typename DataType>
	bool IOLoadable<DataType>::read( SimpleFileStream * fileStream ) {
		unload();
		lock();
		setLoading( true );

		if ( SimpleIO::read( fileStream, this->object ) ) {
			setLoading( false );
			setLoaded( true );
			unlock();
			return true;
		} else {
			setLoading( false );
			setLoaded( false );
			unlock();
			return false;
		}
	}

	template<typename DataType>
	bool IOLoadable<DataType>::write( SimpleFileStream * fileStream ) {
		lock();
		_assert( isLoaded() );
		if ( !SimpleIO::write( fileStream, this->object ) ) {
			unlock();
			return false;
		}
		unlock();
		return true;
	}

	template<typename DataType>
	bool IOLoadable<DataType>::onUnload() {
		delete this->object;
		this->object = NULL;
	}

	template<typename DataType>
	bool IOLoadable<DataType>::onLoad() {
		return IO::read( this->filePath, this->object );
	}

	template<typename DataType>
	const DataType & IOLoadable<DataType>::getObject() const {
		return this->object;
	}

	template<typename DataType>
	DataType & IOLoadable<DataType>::getObject() {
		return this->object;
	}

}