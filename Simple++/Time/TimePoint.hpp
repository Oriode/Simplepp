#include "TimePoint.h"
namespace Time {

	template<typename Ratio>
	TimePoint<Ratio>::TimePoint() {}

	template<typename Ratio>
	TimePoint<Ratio>::TimePoint( const TimeT & timeT ) {
		this -> t = timeT;
	}

	template<typename Ratio>
	inline TimePoint<Ratio>::TimePoint(const TimePoint<Ratio>& tp) :
		t(tp.t)
	{}

	template<typename Ratio>
	template<typename Ratio2>
	inline TimePoint<Ratio>::TimePoint(const TimePoint<Ratio2>& tp) :
		t(tp.toValue<Ratio>()) {}

	template<typename Ratio>
	void TimePoint<Ratio>::setNow() {
		TimePoint<Ratio>::_setNow(reinterpret_cast<Ratio *>(NULL));
	}

	template<typename Ratio>
	bool TimePoint<Ratio>::operator==( const TimePoint<Ratio> & timePoint ) const {
		return this -> t == timePoint.t;
	}

	template<typename Ratio>
	bool TimePoint<Ratio>::operator!=( const TimePoint<Ratio> & timePoint ) const {
		return this -> t != timePoint.t;
	}

	template<typename Ratio>
	bool TimePoint<Ratio>::operator<=( const TimePoint<Ratio> & timePoint ) const {
		return this -> t <= timePoint.t;
	}

	template<typename Ratio>
	bool TimePoint<Ratio>::operator>=( const TimePoint<Ratio> & timePoint ) const {
		return this -> t >= timePoint.t;
	}

	template<typename Ratio>
	bool TimePoint<Ratio>::operator>( const TimePoint<Ratio> & timePoint ) const {
		return this -> t > timePoint.t;
	}

	template<typename Ratio>
	bool TimePoint<Ratio>::operator<( const TimePoint<Ratio> & timePoint ) const {
		return this -> t < timePoint.t;
	}

	template<typename Ratio>
	TimePoint<Ratio> & TimePoint<Ratio>::operator=( const TimePoint<Ratio> & timePoint ) {
		this -> t = timePoint.t;
		return *this;
	}

	template<typename Ratio>
	template<typename Ratio2>
	TimePoint<Ratio>& TimePoint<Ratio>::operator=(const TimePoint<Ratio2>& timePoint) {
		this -> t = timePoint.toValue<Ratio>();
		return *this;
	}

	template<typename Ratio>
	TimePoint<Ratio> & TimePoint<Ratio>::operator=( const TimeT & timeT ) {
		this -> t = timeT;
		return *this;
	}

	template<typename Ratio>
	void TimePoint<Ratio>::setValue( const TimeT & t ) {
		this -> t = t;
	}

	template<typename Ratio>
	const TimeT & TimePoint<Ratio>::getValue() const {
		return this -> t;
	}

	template<typename Ratio>
	template<typename Stream>
	bool TimePoint<Ratio>::read( Stream * stream, int verbose ) {
		if ( !IO::read( stream, &this->t , verbose - 1 ) ) {
			return false;
		}
		return true;
	}

	template<typename Ratio>
	template<typename Stream>
	bool TimePoint<Ratio>::write( Stream * stream ) const {
		if ( !IO::write( stream, &this->t ) ) {
			return false;
		}
		return true;
	}

	template<typename Ratio>
	inline void TimePoint<Ratio>::_setNow(Second * r) {
		static struct timeval tv;
		gettimeofday(&tv, NULL);

		this->t = tv.tv_sec;
	}

	template<typename Ratio>
	template<typename Ratio2>
	inline void TimePoint<Ratio>::_setNow(Ratio2 * r) {
		static struct timeval tv;
		gettimeofday(&tv, NULL);

		this->t = convertTime<Ratio, MilliSecond>(tv.tv_sec * TimeT(1000) + tv.tv_usec / TimeT(1000));
	}

#ifdef WIN32
	template<typename Ratio>
	inline int TimePoint<Ratio>::gettimeofday(timeval* tv, timezone* tzp) {
		///@see https://stackoverflow.com/questions/10905892/equivalent-of-gettimeday-for-windows
		// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
		// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
		// until 00:00:00 January 1, 1970 
		constexpr uint64_t EPOCH( 116444736000000000ULL );

		SYSTEMTIME  system_time;
		FILETIME    file_time;
		uint64_t    time;

		GetSystemTime(&system_time);
		SystemTimeToFileTime(&system_time, &file_time);
		time = ( uint64_t(file_time.dwLowDateTime) );
		time += ( uint64_t(file_time.dwHighDateTime) ) << 32;

		tv->tv_sec = long int( ( time - EPOCH ) / 10000000L );
		tv->tv_usec = long int( system_time.wMilliseconds * 1000 );
		return 0;
	}
#endif

	template<typename Ratio>
	TimePoint<Ratio> & TimePoint<Ratio>::operator+=( TimeT t ) {
		this -> t += t;
		return *this;
	}
	template<typename Ratio>
	TimePoint<Ratio> & TimePoint<Ratio>::operator-=( TimeT t ) {
		this -> t -= t;
		return *this;
	}

	template<typename Ratio>
	template<class Ratio2>
	TimePoint<Ratio> & TimePoint<Ratio>::operator+=( const Duration<Ratio2> & d ) {
		this -> t += d.toValue<Ratio>();
		return *this;
	}

	template<typename Ratio>
	template<class Ratio2>
	TimePoint<Ratio> & TimePoint<Ratio>::operator-=( const Duration<Ratio2> & d ) {
		this -> t -= d.toValue<Ratio>();
		return *this;
	}

	template<typename Ratio>
	template<typename Ratio2>
	inline TimeT TimePoint<Ratio>::toValue() const {
		return convertTime<Ratio2, Ratio>(this->t);
	}

	template<typename Ratio>
	TimePoint<Ratio> getTime() {
		TimePoint<Ratio> newTime;
		newTime.setNow();
		return newTime;
	}















	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<typename Ratio>
	TimePoint<Ratio> operator+( const TimePoint<Ratio> & t1, TimeT t2 ) {
		return TimePoint<Ratio>( t1.getValue() + t2 );
	}

	template<typename Ratio>
	TimePoint<Ratio> operator+( TimeT t1, const TimePoint<Ratio> & t2 ) {
		return TimePoint<Ratio>( t1 + t2.getValue() );
	}

	template<typename Ratio>
	TimePoint<Ratio> operator-( const TimePoint<Ratio> & t1, TimeT t2 ) {
		return TimePoint<Ratio>( t1.getValue() - t2 );
	}

	template<typename Ratio>
	TimePoint<Ratio> operator-( TimeT t1, const TimePoint<Ratio> & t2 ) {
		return TimePoint<Ratio>( t1 - t2.getValue() );
	}

	template<typename Ratio>
	Duration<Ratio> operator-( const TimePoint<Ratio> & t1, const TimePoint<Ratio> & t2 ) {
		return Duration<Ratio>( t1.getValue() - t2.getValue() );
	}

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator+( const TimePoint<Ratio> & t1, const Duration<Ratio2> & d ) {
		return TimePoint<Ratio>( t1.getValue() + d.toValue<Ratio>() );
	}

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator+( const Duration<Ratio2> & d, const TimePoint<Ratio> & t2 ) {
		return TimePoint<Ratio>( t2.getValue() + d.toValue<Ratio>() );
	}

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator-( const TimePoint<Ratio> & t1, const Duration<Ratio2> & d ) {
		return TimePoint<Ratio>( t1.getValue() - d.toValue<Ratio>() );
	}

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator*( const TimePoint<Ratio> & t, const Duration<Ratio2> & d ) {
		return TimePoint<Ratio>( t.getValue() * d.toValue<Ratio>());
	}

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator/( const TimePoint<Ratio> & t, const Duration<Ratio2> & d ) {
		return TimePoint<Ratio>( t.getValue() / d.toValue<Ratio>());
	}


}
