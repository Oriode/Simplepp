#pragma once



namespace Time {


	template<class ratio>
	TimePoint & TimePoint::operator+=( const Duration<ratio> & d ) {
		this -> t += Duration<Second>( d ).getValue();
	}

	template<class ratio>
	TimePoint & TimePoint::operator-=( const Duration<ratio> & d ) {
		this -> t -= Duration<Second>( d ).getValue();
	}

	template<class ratio>
	TimePoint operator+( const TimePoint & t1, const Duration<ratio> & d ) {
		return TimePoint( t1.getTime() + Duration<Second>( d ).getValue() );
	}

	template<class ratio>
	TimePoint operator+( const Duration<ratio> & d, const TimePoint & t2 ) {
		return TimePoint( t2.getTime() + Duration<Second>( d ).getValue() );
	}

	template<class ratio>
	TimePoint operator-( const TimePoint & t1, const Duration<ratio> & d ) {
		return TimePoint( t1.getTime() - Duration<Second>( d ).getValue() );
	}


}
