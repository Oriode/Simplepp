
namespace IO {

	template<typename DataType>
	IOManagedResource<DataType>::IOManagedResource( IOManagedResource<DataType> && handler ) :
		manager( Utility::toRValue( handler.manager ) ),
		object( Utility::toRValue( manager.object ) ) {}

	template<typename DataType>
	IOManagedResource<DataType>::IOManagedResource( const IOManagedResource<DataType> & handler ) {
		( *this ) = handler;
	}

	template<typename DataType>
	IOManagedResource<DataType>::IOManagedResource( Manager<DataType> * manager ) :
		manager( manager ),
		object( NULL ) {}

	template<typename DataType>
	IOManagedResource<DataType>::IOManagedResource( DataType * dataObject, Manager<DataType> * manager ) :
		manager( manager ),
		object( dataObject ) {}


	template<typename DataType>
	IOManagedResource<DataType>::~IOManagedResource() {
		// Resource is not handled by a Manager. Delete it.
		if ( !this->manager )
			delete this->object;
	}


	template<typename DataType>
	IOManagedResource<DataType>::operator DataType * ( ) {
		return this->object;
	}
	template<typename DataType>
	IOManagedResource<DataType>::operator const DataType * ( ) const {
		return this->object;
	}

	template<typename DataType>
	IOManagedResource<DataType> & IOManagedResource<DataType>::operator=( const IOManagedResource<DataType> & resource ) {
		_deleteObject();

		if ( resource.object ) {
			if ( resource.manager ) {
				// The resource to copy is handler by a Manager. Increment the counter.
				this->object = resource.object;
				resource.manager->incrUseCounter( resource.managerObjectId );
			} else {
				// The resource is handled internaly, copy it.
				this->object = new DataType( *( resource.object ) );
			}
		} else {
			// Copy the NULL ptr.
			this->object = resource.object;
		}

		this->managerObjectId = resource.managerObjectId;
		this->manager = resource.manager;
		return *this;
	}

	template<typename DataType>
	IOManagedResource<DataType> & IOManagedResource<DataType>::operator=( IOManagedResource<DataType> && handler ) {
		this->manager = Utility::toRValue( handler.manager );
		this->object = Utility::toRValue( handler.object );
		this->managerObjectId = Utility::toRValue( handler.managerObjectId );
	}

	template<typename DataType>
	const DataType * IOManagedResource<DataType>::getObject() const {
		return this->object;
	}
	template<typename DataType>
	DataType * IOManagedResource<DataType>::getObject() {
		return this->object;
	}


	template<typename DataType>
	bool IOManagedResource<DataType>::setObject( const OS::Path & filePath ) {
		_deleteObject();

		if ( this->manager ) {
			this->managerObjectId = this->manager->addObject( filePath );
			if ( this->managerObjectId ) {
				// The Manager succeeded.
				this->object = const_cast< DataType * >( this->manager->getObject( this->managerObjectId ) );
			} else {
				// The Manager failed.
				this->object = NULL;
				return false;
			}
		} else {
			DataType * newObject = new DataType();
			if ( !IO::read( filePath, newObject ) ) {
				delete newObject;
				this->object = NULL;
				return false;
			} else {
				this->object = newObject;
			}
		}

		return true;
	}

	template<typename DataType>
	bool IOManagedResource<DataType>::setObject( DataType * dataObject ) {
		_deleteObject();

		this->object = dataObject;
		this->manager = NULL;

		return true;
	}

	template<typename DataType>
	bool IOManagedResource<DataType>::read( FileStream * fileStream ) {
		if ( this->object==NULL )
			return true;
		return IO::read( fileStream, this->object );
	}

	template<typename DataType>
	bool IOManagedResource<DataType>::write( FileStream * fileStream ) const {
		if ( this->object==NULL )
			return true;
		return IO::write( fileStream, this->object );
	}

	template<typename DataType>
	void IOManagedResource<DataType>::_deleteObject() {
		// Start by handling the actual resource.
		if ( this->object ) {
			if ( this->manager ) {
				this->manager->deleteObject( this->managerObjectId );
			} else {
				// This Resource is not handled by a Manager. Delete it.
				delete this->object;
			}
		}
	}


}