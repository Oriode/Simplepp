/**
 * @file	Mutex.h.
 *
 * @brief	Declares the mutex class
 */
#pragma once

#include "SimpleLog.h"
#include "Utility.h"

#include <mutex>

 /** @brief	A mutex. */
class Mutex {
public:
	/** @brief	Default constructor */
	Mutex();

	/**
	 * @brief	Copy constructor
	 *
	 * @param	mutex	The mutex.
	 */
	Mutex( const Mutex & mutex );


	/** @brief	Destructor */
	~Mutex();

	/**
	 * @brief	Copy operator
	 *
	 * @param	mutex	to be copied.
	 *
	 * @returns	A shallow copy of this object.
	 */
	Mutex & operator=( const Mutex & mutex );



	/** @brief	Locks this object */
	void lock();
	/** @brief	Unlocks this object */
	void unlock();

	/**
	 * @brief	Query if this object is locked
	 *
	 * @returns	True if locked, false if not.
	 */
	bool isLocked() const;


private:
	/** @brief	True to lock, false to unlock */
	/** @brief	True to lock, false to unlock */
	bool bLocked;
	std::mutex mMutex;
};

