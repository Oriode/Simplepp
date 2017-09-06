#include "Thread.h"


Thread::Thread() :
	bIsRunning( false ) {


}


Thread::~Thread() {
	join();
}

void Thread::start() {
	if ( isRunning() )
		join();


	this -> mutex.lock();
	this -> bIsRunning = true;
	this -> thread = new std::thread( Thread::_staticRun, this );
	this -> mutex.unlock();

	log( "Thread started !" );
}

void Thread::sleep( unsigned int ms ) {
	Time::sleep( ms );
}

bool Thread::isRunning() {
	this -> mutex.lock();
	bool b = this -> bIsRunning;
	this -> mutex.unlock();
	return b;
}

void Thread::join() {
	if ( !isRunning() )
		return;

	this -> mutex.lock();

	this -> thread -> join();
	delete this -> thread;
	this -> thread = NULL;
	this -> bIsRunning = false;

	this -> mutex.unlock();

	log( "Thread stopped." );

}

void Thread::_staticRun( Thread * t ) {
	t -> _run();
}

void Thread::_run() {
	run();

	this -> mutex.lock();
	this -> bIsRunning = false;
	this -> mutex.unlock();
}

void Thread::lock() {
	this -> mutex.lock();
}

void Thread::unlock() {
	this -> mutex.unlock();
}

Thread::Id Thread::getCurrentThreadId() {
	#if defined WIN32
	return GetCurrentThreadId();
	#else
	return std::this_thread::get_id().hash();
	#endif
}

