template<typename T>
ThreadT<T>::ThreadT() :
	bIsRunning( false ) {


}

template<typename T>
ThreadT<T>::~ThreadT() {
	join();
}

template<typename T>
void ThreadT<T>::start() {
	if ( isRunning() )
		join();


	this -> mutex.lock();
	this -> bIsRunning = true;
	this -> thread = new std::thread( ThreadT<T>::_staticRun, this );
	this -> mutex.unlock();

	// INFO( "ThreadT started !" );
}

template<typename T>
void ThreadT<T>::sleep( unsigned int ms ) {
	Time::sleep( ms );
}

template<typename T>
bool ThreadT<T>::isRunning() {
	this -> mutex.lock();
	bool b = this -> bIsRunning;
	this -> mutex.unlock();
	return b;
}

template<typename T>
void ThreadT<T>::join() {
	if ( !isRunning() )
		return;

	this -> thread -> join();

	this -> mutex.lock();
	delete this -> thread;
	this -> thread = NULL;
	this -> bIsRunning = false;

	this -> mutex.unlock();

	// INFO( "ThreadT stopped." );

}

template<typename T>
void ThreadT<T>::_staticRun( ThreadT * t ) {
	t -> _run();
}

template<typename T>
void ThreadT<T>::_run() {
	run();

	this -> mutex.lock();
	this -> bIsRunning = false;
	this -> mutex.unlock();
}

template<typename T>
void ThreadT<T>::lock() {
	this -> mutex.lock();
}

template<typename T>
void ThreadT<T>::unlock() {
	this -> mutex.unlock();
}

template<typename T>
typename ThreadT<T>::Id ThreadT<T>::getCurrentThreadId() {
#if defined WIN32
	return GetCurrentThreadId();
#else
	return std::this_thread::get_id().hash();
#endif
}

