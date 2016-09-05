///@file Time.h
///@brief Time Class
///@author Clément Gerber
///@date 11/07/2016 (DMY) 

#pragma once




#include "../Math/BasicMath.h"
#include "Tick.h"

namespace Time {
	typedef time_t TimeT;




	///@brief Class representing a time duration, 
	///@template ratio fractional number representing the number of seconds of one unit in this object
	template<class ratio = Math::Ratio<1, 1>>
	class Duration {
	public:
		Duration();

		template<class ratio2>
		Duration( const Duration<ratio2> & d );
		Duration( TimeT d );

		Duration( const Tick & ticks );


		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/
		template<class ratio2>
		bool operator==( const Duration<ratio2> & d ) const;
		template<class ratio2>
		bool operator!=( const Duration<ratio2> & d ) const;
		template<class ratio2>
		bool operator>=( const Duration<ratio2> & d ) const;
		template<class ratio2>
		bool operator<=( const Duration<ratio2> & d ) const;
		template<class ratio2>
		bool operator<( const Duration<ratio2> & d ) const;
		template<class ratio2>
		bool operator>( const Duration<ratio2> & d ) const;


		bool operator==( TimeT d ) const;
		bool operator!=( TimeT d ) const;
		bool operator>=( TimeT d ) const;
		bool operator<=( TimeT d ) const;
		bool operator<( TimeT d ) const;
		bool operator>( TimeT d ) const;


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class ratio2>
		Duration<ratio> & operator=( const Duration<ratio2> & d );
		template<class ratio2>
		Duration<ratio> & operator+=( const Duration<ratio2> & d );
		template<class ratio2>
		Duration<ratio> & operator-=( const Duration<ratio2> & d );


		Duration<ratio> & operator=( TimeT d );
		Duration<ratio> & operator+=( TimeT d );
		Duration<ratio> & operator-=( TimeT d );


		template<typename T>
		Duration<ratio> & operator*=( const T & d );
		template<typename T>
		Duration<ratio> & operator/=( const T & d );

		///@brief get the number of milliseconds of this duration
		///@return duration in milliseconds
		unsigned long long getMilliSeconds() const;

		///@brief get the number of seconds of this duration
		///@return seconds
		unsigned long long getSeconds() const;

		///@brief get the number of Minutes of this duration
		///@return minutes
		unsigned long long getMinutes() const;

		///@brief get the number of Hours of this duration
		///@return hours
		unsigned long long getHours() const;


		///@brief get the number of Days of this duration
		///@return duration in days
		unsigned long long getDays() const;




		///@brief Get the value of this duration without any conversion
		///@return number of unit of time of this duration
		TimeT getValue() const;


	private:
		TimeT d;

	};










	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<class ratio, class ratio2>
	Duration<ratio> operator+( const Duration<ratio> & d1, const Duration<ratio2> & d2 );
	template<class ratio>
	Duration<ratio> operator+( const Duration<ratio> & d1, TimeT d2 );
	template<class ratio>
	Duration<ratio> operator+( TimeT d1, const Duration<ratio> & d2 );

	template<class ratio, class ratio2>
	Duration<ratio> operator-( const Duration<ratio> & d1, const Duration<ratio2> & d2 );
	template<class ratio>
	Duration<ratio> operator-( const Duration<ratio> & d1, TimeT d2 );
	template<class ratio>
	Duration<ratio> operator-( TimeT d1, const Duration<ratio> & d2 );



	template<class ratio, typename T>
	Duration<ratio> operator*( const Duration<ratio> & d1, const T & v );
	template<typename T, class ratio>
	Duration<ratio> operator*( const T & v, const Duration<ratio> & d1 );
	template<class ratio, typename T>
	Duration<ratio> operator/( const Duration<ratio> & d1, const T & v );




	typedef Math::Ratio<3600 * 24, 1> Day;
	typedef Math::Ratio<3600, 1> Hour;
	typedef Math::Ratio<60, 1> Minute;
	typedef Math::Ratio<1, 1> Second;
	typedef Math::Ratio<1, 100> CentiSecond;
	typedef Math::Ratio<1, 1000> MilliSecond;
	typedef Math::Ratio<1, 1000000> NanoSecond;
	typedef Math::Ratio<1, 1000000000> PicoSecond;
}



#include "Duration.hpp"
