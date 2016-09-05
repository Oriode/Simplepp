


namespace Time {


	template<class ratio>
	TimePoint & TimePoint::operator+=( const Duration<ratio> & d ) {
		this -> t += d.getSeconds();
	}

	template<class ratio>
	TimePoint & TimePoint::operator-=( const Duration<ratio> & d ) {
		this -> t -= d.getSeconds();
	}

	template<class ratio>
	TimePoint operator+( const TimePoint & t1, const Duration<ratio> & d ) {
		return TimePoint( t1.getTime() + d.getSeconds() );
	}

	template<class ratio>
	TimePoint operator+( const Duration<ratio> & d, const TimePoint & t2 ) {
		return TimePoint( t2.getTime() + d.getSeconds() );
	}

	template<class ratio>
	TimePoint operator-( const TimePoint & t1, const Duration<ratio> & d ) {
		return TimePoint( t1.getTime() - d.getSeconds() );
	}


}
