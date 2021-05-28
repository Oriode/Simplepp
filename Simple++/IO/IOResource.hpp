
namespace IO {

	template<typename DataType>
	IOResource<DataType>::IOResource( IOResource<DataType> && resource ) :
		manager( Utility::toRValue( resource.manager ) ),
		managerObjectId( Utility::toRValue( resource.managerObjectId ) ),
		object( Utility::toRValue( resource.object ) ),
		loadingType( Utility::toRValue( resource.loadingType ) ) {}

	template<typename DataType>
	IOResource<DataType>::IOResource( const IOResource<DataType> & resource ) {
		( *this ) = resource;
	}

	template<typename DataType>
	IOResource<DataType>::IOResource( IOManager<DataType> * manager ) :
		manager( manager ),
		managerObjectId( NULL ),
		object( NULL ),
		loadingType( LoadingType::None ) {}

	template<typename DataType>
	IOResource<DataType>::IOResource( DataType * dataObject, IOManager<DataType> * manager ) :
		manager( manager ),
		object( dataObject ),
		loadingType( ( dataObject ) ? LoadingType::Externaly : LoadingType::None ) {}

	template<typename DataType>
	IOResource<DataType>::IOResource( const OS::Path & filePath, IOManager<DataType> * manager ) :
		manager( manager ) {
		_setObject( filePath );
	}

	template<typename DataType>
	IOResource<DataType>::~IOResource() {
		_deleteObject();
	}

	template<typename DataType>
	IOResource<DataType>::operator DataType * ( ) {
		return this->object;
	}
	template<typename DataType>
	IOResource<DataType>::operator const DataType * ( ) const {
		return this->object;
	}

	template<typename DataType>
	IOResource<DataType> & IOResource<DataType>::operator=( const IOResource<DataType> & resource ) {
		_deleteObject();

		switch ( resource.loadingType ) {
			case LoadingType::None:
				{
					this->object = NULL;
					break;
				}
			case LoadingType::Externaly:
				{
					// The resource is not handled by a Manager nor internaly, just copy the reference.
					this->object = resource.object;
					break;
				}
			case LoadingType::Manager:
				{
					// The resource to copy is handled by a Manager. Increment the counter.
					this->object = resource.object;
					resource.manager->incrUseCounter( resource.managerObjectId );
					break;
				}
			case LoadingType::Internaly:
				{
					// The resource to copy is handled by a Manager. Increment the counter.
					this->object = resource.object;
					resource.manager->incrUseCounter( resource.managerObjectId );
					break;
				}
		}

		this->managerObjectId = resource.managerObjectId;
		this->manager = resource.manager;
		this->loadingType = resource.loadingType;
		return *this;
	}

	template<typename DataType>
	IOResource<DataType> & IOResource<DataType>::operator=( IOResource<DataType> && resource ) {
		this->manager = Utility::toRValue( resource.manager );
		this->object = Utility::toRValue( resource.object );
		this->managerObjectId = Utility::toRValue( resource.managerObjectId );
		this->loadingType = Utility::toRValue( resource.loadingType );
	}

	template<typename DataType>
	const DataType * IOResource<DataType>::getObject() const {
		return this->object;
	}
	template<typename DataType>
	DataType * IOResource<DataType>::getObject() {
		return this->object;
	}

	template<typename DataType>
	bool IOResource<DataType>::setObject( const OS::Path & filePath ) {
		_deleteObject();
		return _setObject( filePath );
	}

	template<typename DataType>
	bool IOResource<DataType>::setObject( DataType * dataObject ) {
		_deleteObject();

		this->object = dataObject;

		if ( this->object ) {
			this->loadingType = LoadingType::Externaly;
		} else {
			this->loadingType = LoadingType::None;
		}

		return true;
	}

	template<typename DataType>
	bool IOResource<DataType>::read( FileStream * fileStream ) {
		if ( this->object==NULL )
			return true;
		return IO::read( fileStream, this->object );
	}

	template<typename DataType>
	bool IOResource<DataType>::write( FileStream * fileStream ) const {
		if ( this->object==NULL )
			return true;
		return IO::write( fileStream, this->object );
	}

	template<typename DataType>
	bool IOResource<DataType>::_setObject( const OS::Path & filePath ) {
		if ( this->manager ) {
			this->managerObjectId = this->manager->addObject( filePath );
			if ( this->managerObjectId ) {
				// The Manager succeeded.
				this->object = const_cast< DataType * >( this->manager->getObject( this->managerObjectId ) );
				this->loadingType = LoadingType::Manager;
			} else {
				// The Manager failed.
				this->object = NULL;
				this->loadingType = LoadingType::None;
				return false;
			}
		} else {
			// No Manager, just create the object internally
			DataType * newResource( new DataType() );
			if ( !IO::read( filePath, newResource ) ) {
				delete newResource;
				this->object = NULL;
				this->loadingType = LoadingType::None;
				return false;
			} else {
				this->object = newResource;
				this->loadingType = LoadingType::Internaly;
			}
		}

		return true;
	}

	template<typename DataType>
	bool IOResource<DataType>::_deleteObject() {
		// Start by handling the actual resource.
		switch ( this->loadingType ) {
			case LoadingType::Internaly:
				delete this->object;
				break;
			case LoadingType::Manager:
				return this->manager->deleteObject( this->managerObjectId );
		}
		return true;
	}


}