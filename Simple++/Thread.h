#pragma once


#include <thread>
#include <mutex>
#include "Log.h"
#include "Time/Time.h"



#if defined WIN32 && defined ENABLE_WIN32
#include <windows.h>
#endif



class Thread {
public:
	typedef unsigned long Id;


	Thread();
	~Thread();


	/*
	 * Start the thread
	 */
	void start();


	/*
	 * Blocking function, wait the thread to stop.
	 */
	void join();



	/*
	 * Virtual function, should be overloaded to do something with the thread
	 */
	virtual void run() = 0;



	/*
	 * Is the thread running ?
	 */
	bool isRunning();


	void sleep( unsigned int ms );


	void lock();
	void unlock();


	static Thread::Id getCurrentThreadId();


	void _run();
	static void _staticRun( Thread * t );


private:
	std::mutex mutex;
	std::thread * thread;


	bool bIsRunning;

};

