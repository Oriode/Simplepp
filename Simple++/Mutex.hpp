template<typename T>
MutexT<T>::MutexT() :
	bLocked( false ) {

}

template<typename T>
MutexT<T>::MutexT( const MutexT & mutex ) :
	bLocked( false ) {
	*this = mutex;
}

template<typename T>
MutexT<T>::~MutexT() {

}

template<typename T>
MutexT<T> & MutexT<T>::operator=( const MutexT & mutex ) {
	if ( mutex.isLocked() && !isLocked() )
		lock();
	else if ( isLocked() && !mutex.isLocked() )
		unlock();

	return *this;
}

template<typename T>
void MutexT<T>::lock() {
	this->mMutex.lock();
	_ASSERT_SPP(!this->bLocked);
	//this -> lockingThreadId = Thread::getCurrentThreadId();
	this->bLocked = true;
}

template<typename T>
void MutexT<T>::unlock() {
	_ASSERT_SPP( this->bLocked );
	this->bLocked = false;
	this->mMutex.unlock();
}

template<typename T>
bool MutexT<T>::isLocked() const {
	return this->bLocked;
}
