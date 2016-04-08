#pragma once

#include "Log.h"
#include "Thread.h"

class Mutex {
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

	bool isLocked() const;


private:
	bool bLocked;
	std::mutex mMutex;


	Thread::Id lockingThreadId;
};

