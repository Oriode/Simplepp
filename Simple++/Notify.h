#pragma once

#include <mutex>
#include <condition_variable>

template<typename T>
class NotifyT {
public:
	NotifyT() { }

	void notify();

	void wait();


private:
	std::mutex mutex;
	std::condition_variable conditionVariable;
};

using Notify = NotifyT<int>;

template<typename T>
inline void NotifyT<T>::notify() {
	std::unique_lock<std::mutex> lock( this->mutex );
	conditionVariable.notify_all();
}

template<typename T>
inline void NotifyT<T>::wait() {
	std::unique_lock<std::mutex> lock( this->mutex );
	conditionVariable.wait( lock );
}
