
namespace IO {

	template<typename DataType>
	Resource<DataType>::Resource( Resource<DataType> && resource ) :
		manager( Utility::toRValue( resource.manager ) ),
		managerObjectId( Utility::toRValue( resource.managerObjectId ) ),
		object( Utility::toRValue( resource.object ) ),
		loadingType( Utility::toRValue( resource.loadingType ) ) {}

	template<typename DataType>
	Resource<DataType>::Resource( const Resource<DataType> & resource ) {
		( *this ) = resource;
	}

	template<typename DataType>
	Resource<DataType>::Resource( Manager<DataType> * manager ) :
		manager( manager ),
		managerObjectId( NULL ),
		object( NULL ),
		loadingType( LoadingType::None ) {}

	template<typename DataType>
	Resource<DataType>::Resource( DataType * dataObject, Manager<DataType> * manager ) :
		manager( manager ),
		object( dataObject ),
		loadingType( ( dataObject ) ? LoadingType::Externaly : LoadingType::None ) {}

	template<typename DataType>
	Resource<DataType>::Resource( const OS::Path & filePath, Manager<DataType> * manager ) :
		manager( manager ) {
		_setObject( filePath );
	}

	template<typename DataType>
	Resource<DataType>::~Resource() {
		_deleteObject();
	}

	template<typename DataType>
	Resource<DataType>::operator DataType * ( ) {
		return this->object;
	}
	template<typename DataType>
	Resource<DataType>::operator const DataType * ( ) const {
		return this->object;
	}

	template<typename DataType>
	Resource<DataType> & Resource<DataType>::operator=( const Resource<DataType> & resource ) {
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
	Resource<DataType> & Resource<DataType>::operator=( Resource<DataType> && resource ) {
		this->manager = Utility::toRValue( resource.manager );
		this->object = Utility::toRValue( resource.object );
		this->managerObjectId = Utility::toRValue( resource.managerObjectId );
		this->loadingType = Utility::toRValue( resource.loadingType );
	}

	template<typename DataType>
	const DataType * Resource<DataType>::getObject() const {
		return this->object;
	}
	template<typename DataType>
	DataType * Resource<DataType>::getObject() {
		return this->object;
	}

	template<typename DataType>
	bool Resource<DataType>::setObject( const OS::Path & filePath ) {
		_deleteObject();
		return _setObject( filePath );
	}

	template<typename DataType>
	bool Resource<DataType>::setObject( DataType * dataObject ) {
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
	template<typename Stream>
	bool Resource<DataType>::read(Stream* stream ) {
		if ( this->object==NULL )
			return true;
		return IO::read( stream, this->object );
	}

	template<typename DataType>
	template<typename Stream>
	bool Resource<DataType>::write(Stream* stream ) const {
		if ( this->object==NULL )
			return true;
		return IO::write( stream, this->object );
	}

	template<typename DataType>
	bool Resource<DataType>::_setObject( const OS::Path & filePath ) {
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
	bool Resource<DataType>::_deleteObject() {
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