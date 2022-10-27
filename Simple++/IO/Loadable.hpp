namespace IO {

	template<typename DataType>
	Loadable<DataType>::Loadable( const OS::Path & filePath ) :
		filePath( filePath ),
		object( NULL ) {}

	template<typename DataType>
	Loadable<DataType>::~Loadable() {
		if ( !this->object ) {
			delete this->object;
		}
	}

	template<typename DataType>
	template<typename Stream>
	bool Loadable<DataType>::read(Stream* stream ) {
		unload();
		lock();
		setLoading( true );

		_ASSERT_SPP( !this->object );
		this->object = new DataType();

		if ( IO::read( stream, this->object ) ) {
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
	template<typename Stream>
	bool Loadable<DataType>::write(Stream* stream ) const {
		const_cast< Loadable<DataType> * >( this )->lock();
		if ( !isLoaded() ) {
			const_cast< Loadable<DataType> * >( this )->unlock();
			return false;
		}
		if ( !IO::write( stream, this->object ) ) {
			const_cast< Loadable<DataType> * >( this )->unlock();
			return false;
		}
		const_cast< Loadable<DataType> * >( this )->unlock();
		return true;
	}

	template<typename DataType>
	bool Loadable<DataType>::onUnload() {
		_ASSERT_SPP( this->object );
		delete this->object;
		this->object = NULL;
		return true;
	}

	template<typename DataType>
	bool Loadable<DataType>::onLoad() {
		_ASSERT_SPP( !this->object );
		this->object = new DataType();
		return IO::read( this->filePath, this->object );
	}

	template<typename DataType>
	const DataType * Loadable<DataType>::getObject() const {
		return this->object;
	}

	template<typename DataType>
	DataType * Loadable<DataType>::getObject() {
		return this->object;
	}

	template<typename DataType>
	const OS::Path Loadable<DataType>::getFilePath() const {
		return this->filePath;
	}

}