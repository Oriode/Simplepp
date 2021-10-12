namespace Time {

	template<typename T>
	TimePointT<T>::TimePointT() {}

	template<typename T>
	TimePointT<T>::TimePointT( const TimeT & timeT ) {
		this -> t = timeT;
	}

	template<typename T>
	void TimePointT<T>::setNow() {
		std::time( &this -> t );
	}

	template<typename T>
	bool TimePointT<T>::operator==( const TimePointT<T> & timePoint ) const {
		return this -> t == timePoint.t;
	}

	template<typename T>
	bool TimePointT<T>::operator!=( const TimePointT<T> & timePoint ) const {
		return this -> t != timePoint.t;
	}

	template<typename T>
	bool TimePointT<T>::operator<=( const TimePointT<T> & timePoint ) const {
		return this -> t <= timePoint.t;
	}

	template<typename T>
	bool TimePointT<T>::operator>=( const TimePointT<T> & timePoint ) const {
		return this -> t >= timePoint.t;
	}

	template<typename T>
	bool TimePointT<T>::operator>( const TimePointT<T> & timePoint ) const {
		return this -> t > timePoint.t;
	}

	template<typename T>
	bool TimePointT<T>::operator<( const TimePointT<T> & timePoint ) const {
		return this -> t < timePoint.t;
	}

	template<typename T>
	TimePointT<T> & TimePointT<T>::operator=( const TimePointT<T> & timePoint ) {
		this -> t = timePoint.t;
		return *this;
	}

	template<typename T>
	TimePointT<T> & TimePointT<T>::operator=( const TimeT & timeT ) {
		this -> t = timeT;
		return *this;
	}

	template<typename T>
	void TimePointT<T>::setTime( const TimeT & t ) {
		this -> t = t;
	}

	template<typename T>
	const TimeT & TimePointT<T>::getTime() const {
		return this -> t;
	}

	template<typename T>
	TimePointT<T> TimePointT<T>::getNow() {
		TimePointT<T> newTime;
		newTime.setNow();
		return newTime;
	}

	template<typename T>
	TimePointT<T> & TimePointT<T>::operator+=( TimeT t ) {
		this -> t += t;
		return *this;
	}
	template<typename T>
	TimePointT<T> & TimePointT<T>::operator-=( TimeT t ) {
		this -> t -= t;
		return *this;
	}

	template<typename T>
	template<class ratio>
	TimePointT<T> & TimePointT<T>::operator+=( const Duration<ratio> & d ) {
		this -> t += d.getSeconds();
		return *this;
	}

	template<typename T>
	template<class ratio>
	TimePointT<T> & TimePointT<T>::operator-=( const Duration<ratio> & d ) {
		this -> t -= d.getSeconds();
		return *this;
	}


	template<typename T>
	TimePointT<T>::~TimePointT() {}

	template<typename T>
	TimePointT<T> getTime() {
		return TimePointT<T>::getNow();
	}















	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<typename T>
	TimePointT<T> operator+( const TimePointT<T> & t1, TimeT t2 ) {
		return TimePointT<T>( t1.getTime() + t2 );
	}

	template<typename T>
	TimePointT<T> operator+( TimeT t1, const TimePointT<T> & t2 ) {
		return TimePointT<T>( t1 + t2.getTime() );
	}

	template<typename T>
	TimePointT<T> operator-( const TimePointT<T> & t1, TimeT t2 ) {
		return TimePointT<T>( t1.getTime() - t2 );
	}

	template<typename T>
	TimePointT<T> operator-( TimeT t1, const TimePointT<T> & t2 ) {
		return TimePointT<T>( t1 - t2.getTime() );
	}

	template<typename T>
	Duration<Second> operator-( const TimePointT<T> & t1, const TimePointT<T> & t2 ) {
		return Duration<Second>( t1.getTime() - t2.getTime() );
	}

	template<typename T, class ratio>
	TimePointT<T> operator+( const TimePointT<T> & t1, const Duration<ratio> & d ) {
		return TimePointT<T>( t1.getTime() + d.getSeconds() );
	}

	template<typename T, class ratio>
	TimePointT<T> operator+( const Duration<ratio> & d, const TimePointT<T> & t2 ) {
		return TimePointT<T>( t2.getTime() + d.getSeconds() );
	}

	template<typename T, class ratio>
	TimePointT<T> operator-( const TimePointT<T> & t1, const Duration<ratio> & d ) {
		return TimePointT<T>( t1.getTime() - d.getSeconds() );
	}

	template<typename T, class ratio>
	TimePointT<T> operator*( const TimePointT<T> & t, const Duration<ratio> & d ) {
		return TimePointT<T>( t.getTime() * d.getSeconds() );
	}

	template<typename T, class ratio>
	TimePointT<T> operator/( const TimePointT<T> & t, const Duration<ratio> & d ) {
		return TimePointT<T>( t.getTime() / d.getSeconds() );
	}


}
