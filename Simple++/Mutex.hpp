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
	_assert( !this->bLocked );
	this->mMutex.lock();
	//this -> lockingThreadId = Thread::getCurrentThreadId();
	this->bLocked = true;
}

template<typename T>
void MutexT<T>::unlock() {
	_assert( this->bLocked );
	this->mMutex.unlock();
	this->bLocked = false;
}

template<typename T>
bool MutexT<T>::isLocked() const {
	return this->bLocked;
}
