#pragma once


#include <thread>
#include "Log.h"
#include "Time/Time.h"
#include "Mutex.h"



#if defined WIN32 && defined ENABLE_WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif


template<typename T>
class ThreadT {
public:
	typedef unsigned long int Id;


	ThreadT();
	~ThreadT();


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


	static typename ThreadT::Id getCurrentThreadId();


	void _run();
	static void _staticRun( ThreadT * t );


private:
	Mutex mutex;
	std::thread * thread;


	bool bIsRunning;

};

using Thread = ThreadT<int>;

#include "Thread.hpp"
