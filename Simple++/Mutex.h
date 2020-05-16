/**
 * @file	MutexT.h.
 *
 * @brief	Declares the mutex class
 */
#pragma once

#include "SimpleLog.h"
#include "Utility.h"

#include <mutex>


 /** @brief	A mutex. */
template<typename T>
class MutexT {
public:
	/** @brief	Default constructor */
	MutexT();

	/**
	 * @brief	Copy constructor
	 *
	 * @param	mutex	The mutex.
	 */
	MutexT( const MutexT & mutex );


	/** @brief	Destructor */
	~MutexT();

	/**
	 * @brief	Copy operator
	 *
	 * @param	mutex	to be copied.
	 *
	 * @returns	A shallow copy of this object.
	 */
	MutexT & operator=( const MutexT & mutex );



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
	T mMutex;
};

using Mutex = MutexT<std::mutex>;

#include "Mutex.hpp"