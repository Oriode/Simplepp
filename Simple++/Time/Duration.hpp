#include "Duration.h"

namespace Time {

	/************************************************************************/
	/* CONSTRUCTOR	                                                      */
	/************************************************************************/


	template<class ratio>
	Duration<ratio>::Duration( TimeT d ) {
		this -> d = d;
	}

	template<class ratio>
	Duration<ratio>::Duration( const Tick & ticks ) {
		this -> d = ticks.getValue() * ratio::den / Time::TicksPerSec / ratio::num;
	}


	template<class ratio>
	Duration<ratio>::Duration() {

	}

	template<class ratio>
	template<class ratio2>
	Duration<ratio>::Duration( const Duration<ratio2> & d ) {
		this -> d = ( d.getValue() * ratio::den * ratio2::num ) / ratio2::den / ratio::num;
	}





	/************************************************************************/
	/* OPERATOR LOGICAL                                                     */
	/************************************************************************/






	template<class ratio>
	template<class ratio2>
	bool Duration<ratio>::operator>( const Duration<ratio2> & d ) const {
		return this -> d  * ratio::num * ratio2::den > d.getValue() * ratio2::num * ratio::den;
	}

	template<class ratio>
	template<class ratio2>
	bool Duration<ratio>::operator<( const Duration<ratio2> & d ) const {
		return this -> d  * ratio::num * ratio2::den < d.getValue() * ratio2::num * ratio::den;
	}

	template<class ratio>
	template<class ratio2>
	bool Duration<ratio>::operator<=( const Duration<ratio2> & d ) const {
		return this -> d  * ratio::num * ratio2::den <= d.getValue() * ratio2::num * ratio::den;
	}

	template<class ratio>
	template<class ratio2>
	bool Duration<ratio>::operator>=( const Duration<ratio2> & d ) const {
		return this -> d  * ratio::num * ratio2::den >= d.getValue() * ratio2::num * ratio::den;
	}

	template<class ratio>
	template<class ratio2>
	bool Duration<ratio>::operator!=( const Duration<ratio2> & d ) const {
		return this -> d  * ratio::num * ratio2::den != d.getValue() * ratio2::num * ratio::den;
	}

	template<class ratio>
	template<class ratio2>
	bool Duration<ratio>::operator==( const Duration<ratio2> & d ) const {
		return this -> d  * ratio::num * ratio2::den == d.getValue() * ratio2::num * ratio::den;
	}



	template<class ratio>
	bool Duration<ratio>::operator>( TimeT d ) const {
		return this -> d > d;
	}

	template<class ratio>
	bool Duration<ratio>::operator<( TimeT d ) const {
		return this -> d < d;
	}

	template<class ratio>
	bool Duration<ratio>::operator<=( TimeT d ) const {
		return this -> d > d;
	}

	template<class ratio>
	bool Duration<ratio>::operator>=( TimeT d ) const {
		return this -> d >= d;
	}

	template<class ratio>
	bool Duration<ratio>::operator!=( TimeT d ) const {
		return this -> d != d;
	}

	template<class ratio>
	bool Duration<ratio>::operator==( TimeT d ) const {
		return this -> d == d;
	}



	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<class ratio>
	template<class ratio2>
	Duration<ratio> & Time::Duration<ratio>::operator-=( const Duration<ratio2> & d ) {
		this -> d = ( d.getValue() *ratio::den * ratio2::num ) / ratio2::den / ratio::num;
		return *this;
	}

	template<class ratio>
	template<class ratio2>
	Duration<ratio> & Time::Duration<ratio>::operator=( const Duration<ratio2> & d ) {
		this -> d = ( d.getValue() * ratio::den * ratio2::num ) / ratio2::den / ratio::num;
		return *this;
	}

	template<class ratio>
	template<class ratio2>
	Duration<ratio> & Time::Duration<ratio>::operator+=( const Duration<ratio2> & d ) {
		this -> d += ( d.getValue() * ratio::den * ratio2::num ) / ratio2::den / ratio::num;
		return *this;
	}




	template<class ratio>
	Duration<ratio> & Time::Duration<ratio>::operator-=( TimeT d ) {
		this -> d -= d;
		return *this;
	}

	template<class ratio>
	Duration<ratio> & Time::Duration<ratio>::operator=( TimeT d ) {
		this -> d = d;
		return *this;
	}

	template<class ratio>
	Duration<ratio> & Time::Duration<ratio>::operator+=( TimeT d ) {
		this -> d += d;
		return *this;
	}

	template<class ratio>
	template<typename T>
	Duration<ratio> & Time::Duration<ratio>::operator*=( const T & t ) {
		this -> d *= t;
		return *this;
	}

	template<class ratio>
	template<typename T>
	Duration<ratio> & Time::Duration<ratio>::operator/=( const T & t ) {
		this -> d /= t;
		return *this;
	}





	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<class ratio, class ratio2>
	Duration<ratio> operator+( const Duration<ratio> & d1, const Duration<ratio2> & d2 ) {
		Duration<ratio> d( d1.getValue() );
		return d += d2;
	}


	template<class ratio>
	Duration<ratio> operator+( const Duration<ratio> & d1, TimeT d2 ) {
		Duration<ratio> d( d1.getValue() );
		return d += d2;
	}

	template<class ratio>
	Duration<ratio> operator+( TimeT d1, const Duration<ratio> & d2 ) {
		Duration<ratio> d( d1 );
		return d += d2;
	}


	template<class ratio, class ratio2>
	Duration<ratio> operator-( const Duration<ratio> & d1, const Duration<ratio2> & d2 ) {
		Duration<ratio> d( d1.getValue() );
		return d -= d2;
	}


	template<class ratio>
	Duration<ratio> operator-( const Duration<ratio> & d1, TimeT d2 ) {
		Duration<ratio> d( d1.getValue() );
		d += d2;
		return d;
	}

	template<class ratio>
	Duration<ratio> operator-( TimeT d1, const Duration<ratio> & d2 ) {
		Duration<ratio> d( d1 );
		return d += d2;
	}


	template<class ratio, typename T>
	Duration<ratio> operator/( const Duration<ratio> & d1, const T & v ) {
		Duration<ratio> d( d1 );
		return d /= v;
	}

	template<typename T, class ratio>
	Duration<ratio> operator*( const T & v, const Duration<ratio> & d1 ) {
		Duration<ratio> d( d1 );
		return d *= v;
	}

	template<class ratio, typename T>
	Duration<ratio> operator*( const Duration<ratio> & d1, const T & v ) {
		Duration<ratio> d( d1 );
		return d *= v;
	}


	template<class ratio> TimeT Time::Duration<ratio>::getValue() const {
		return this -> d;
	}


}

