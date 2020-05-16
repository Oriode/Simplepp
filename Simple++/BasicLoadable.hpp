template<typename T>
BasicLoadableT<T>::BasicLoadableT() :
	mIsloaded( false ) {}

template<typename T>
BasicLoadableT<T>::BasicLoadableT( const BasicLoadableT<T> & loadable ) {
	*this = loadable;
}

template<typename T>
BasicLoadableT<T>::~BasicLoadableT() {}

template<typename T>
bool BasicLoadableT<T>::load() {
	lock();
	if ( this -> mIsloaded ) {
		unlock();
		// Object already loaded, nothing to do.
		return true;
	}
	this -> bIsLoading = true;
	if ( onLoad() ) {
		this -> bIsLoading = false;
		this -> mIsloaded = true;
		unlock();
		return true;
	} else {
		this -> bIsLoading = false;
		unlock();
		return false;
	}
}

template<typename T>
bool BasicLoadableT<T>::unload() {
	lock();

	if ( !this -> mIsloaded ) {
		unlock();
		// Object not loaded, nothing to do.
		return true;
	}
	if ( onUnload() ) {
		this -> mIsloaded = false;
		unlock();
		return true;
	} else {
		unlock();
		return false;
	}
}

template<typename T>
bool BasicLoadableT<T>::onLoad() {
	return true;
}

template<typename T>
bool BasicLoadableT<T>::onUnload() {
	return true;
}

template<typename T>
bool BasicLoadableT<T>::isLoaded() const {
	return this -> mIsloaded;
}

template<typename T>
void BasicLoadableT<T>::setLoaded( bool loaded ) {
	this -> mIsloaded = loaded;
}

template<typename T>
void BasicLoadableT<T>::setLoading( bool isLoading ) {
	this -> bIsLoading = isLoading;
}

template<typename T>
bool BasicLoadableT<T>::reload() {
	if ( isLoaded() ) {
		if ( unload() && load() )
			return true;
		else
			return false;
	} else {
		return true;
	}
}

template<typename T>
bool BasicLoadableT<T>::isLoading() const {
	return this -> bIsLoading;
}

template<typename T>
void BasicLoadableT<T>::lock() {
	this -> mutex.lock();
}

template<typename T>
void BasicLoadableT<T>::unlock() {
	this -> mutex.unlock();
}

template<typename T>
BasicLoadableT<T> & BasicLoadableT<T>::operator=( const BasicLoadableT<T> & loadable ) {
	lock();

	this ->  bIsLoading = loadable.bIsLoading;
	this ->  mIsloaded = loadable.mIsloaded;

	unlock();
	return *this;
}
