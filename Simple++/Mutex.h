#pragma once

#include "SimpleLog.h"
//#include "Thread.h"
#include "Utility.h"

#include <mutex>

class Mutex {
public:
	Mutex();

	///@brief Copy constructor
	Mutex( const Mutex & mutex );


	~Mutex();

	///@brief Copy operator
	///@param object to be copied
	Mutex & operator=( const Mutex & mutex );



	void lock();
	void unlock();

	bool isLocked() const;


private:
	bool bLocked;
	std::mutex mMutex;
};

