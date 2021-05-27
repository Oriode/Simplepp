
namespace IO {

	template<typename DataType>
	IOHandler<DataType>::IOHandler(IOHandler<DataType>&& handler) :
		manager(Utility::toRValue(handler.manager)),
		object(Utility::toRValue(manager.object)),
		objectLoaded(Utility::toRValue(manager.objectLoaded)) {
		handler.objectLoaded = NULL;
	}

	template<typename DataType>
	IOHandler<DataType>::IOHandler(const IOHandler<DataType>& handler) {
		(*this) = handler;
	}

	template<typename DataType>
	IOHandler<DataType>::IOHandler(IOManager<DataType>* manager) :
		manager(manager),
		object(NULL),
		objectLoaded(NULL) {

	}

	template<typename DataType>
	IOHandler<DataType>::IOHandler(DataType* dataObject, IOManager<DataType>* manager) :
		manager(manager),
		object(dataObject),
		objectLoaded(NULL) {

	}


	template<typename DataType>
	IOHandler<DataType>::~IOHandler() {
		if (this->manager == NULL)
			delete this->objectLoaded;
	}


	template<typename DataType>
	IOHandler<DataType>::operator DataType* () {
		return this->object;
	}
	template<typename DataType>
	IOHandler<DataType>::operator const DataType* () const {
		return this->object;
	}

	template<typename DataType>
	IOHandler<DataType>& IOHandler<DataType>::operator=(const IOHandler<DataType>& handler) {
		if (this->objectLoaded) {
			if (this->manager) {
				this->manager->deleteObject(this->objectId);
			}
			else {
				delete this->objectLoaded;
			}
		}

		if (handler.objectLoaded) {
			if (handler.manager) {
				this->objectLoaded = handler.objectLoaded;
				handler.manager->incrUseCounter(handler.objectId);
			}
			else {
				this->objectLoaded = new DataType(*(handler.objectLoaded));
			}
		}
		else
			this->objectLoaded = handler.objectLoaded;

		this->objectId = handler.objectId;
		this->manager = handler.manager;
		this->object = this->objectLoaded;
		return *this;
	}

	template<typename DataType>
	IOHandler<DataType>& IOHandler<DataType>::operator=(IOHandler<DataType>&& handler) {
		this->manager = Utility::toRValue(handler.manager);
		this->object = Utility::toRValue(handler.object);
		this->objectId = Utility::toRValue(handler.objectId);
		this->objectLoaded = Utility::toRValue(handler.objectLoaded);
		handler.objectLoaded = NULL;
	}

	template<typename DataType>
	const DataType* IOHandler<DataType>::getObject() const {
		return this->object;
	}
	template<typename DataType>
	DataType* IOHandler<DataType>::getObject() {
		return this->object;
	}


	template<typename DataType>
	bool IOHandler<DataType>::setObject(const OS::Path & filePath) {

		if (this->manager) {
			if ( this->objectLoaded ) {
				this->manager->deleteObject( this->objectId );
			}
			this->objectId = this->manager->addObject(filePath);
			if (this->objectId) {
				this->objectLoaded = const_cast<DataType*>(this->manager->getObject(this->objectId));
				this->object = this->objectLoaded;
			}
			else {
				this->objectLoaded = NULL;
				this->object = NULL;
				return false;
			}
		}
		else {
			if ( this->objectLoaded ) {
				delete this->objectLoaded;
			}
			this->objectLoaded = new DataType();
			if (!IO::read(filePath, this->objectLoaded)) {
				delete this->objectLoaded;
				this->object = NULL;
				return false;
			}
			else {
				this->object = this->objectLoaded;
			}
		}

		return true;
	}

	template<typename DataType>
	bool IOHandler<DataType>::setObject(DataType* dataObject) {
		if ( this->objectLoaded ) {
			if ( this->manager )
				this->manager->deleteObject( this->objectId );
			else
				delete this->objectLoaded;
		}
		
		this->objectLoaded = NULL;
		this->object = dataObject;

		return true;
	}

	template<typename DataType>
	bool IOHandler<DataType>::read(FileStream* fileStream) {
		if (this->object == NULL)
			return true;
		return IO::read(fileStream, this->object);
	}


	template<typename DataType>
	bool IOHandler<DataType>::write(FileStream* fileStream) const {
		if (this->object == NULL)
			return true;
		return IO::write(fileStream, this->object);
	}

}