/**
 * @file		Time\TimePoint.h.
 *
 * @brief		Declares the time point class
 * @author	Clément Gerber
 * @date		11/07/2016 (DMY)
 */
#pragma once

#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include "Duration.h"
#include "../IO/IO.h"


namespace Time {

	/** @brief	Class representing a precise moment in the time ( extension of std time_t ) */
	template<typename Ratio = Second>
	class TimePoint : public IO::BasicIO {
	public:

		/** @brief	create an uninitialized TimePoint. See getValue() of getting the timepoint of the current time. */
		TimePoint();

		/**
		 * @brief			Create a TimePoint from an old school time_t object
		 *
		 * @param			timeT	The time t.
		 */
		TimePoint( const TimeT & timeT );

		TimePoint(const TimePoint<Ratio>& tp);

		template<typename Ratio2>
		TimePoint(const TimePoint<Ratio2>& tp);

		/** @brief	Set this object to store the current moment. */
		void setNow();

		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/
		bool operator==( const TimePoint & timePoint ) const;
		bool operator!=( const TimePoint & timePoint ) const;
		bool operator>=( const TimePoint & timePoint ) const;
		bool operator<=( const TimePoint & timePoint ) const;
		bool operator<( const TimePoint & timePoint ) const;
		bool operator>( const TimePoint & timePoint ) const;


		/************************************************************************/
		/* OPERATOR EQUAL	                                                      */
		/************************************************************************/
		TimePoint & operator=( const TimePoint<Ratio> & timePoint );
		template<typename Ratio2>
		TimePoint & operator=( const TimePoint<Ratio2> & timePoint );
		TimePoint & operator=( const TimeT & timeT );


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class Ratio2>
		TimePoint & operator+=( const Duration<Ratio2> & d );

		template<class Ratio2>
		TimePoint & operator-=( const Duration<Ratio2> & d );

		TimePoint & operator+=( TimeT t );
		TimePoint & operator-=( TimeT t );


		/**
		 * @brie	f	Sets an old school time_t.
		 *
		 * @param	t	A TimeT to process.
		 */
		void setValue( const TimeT & t );


		/**
		 * @brief		Gets the time
		 *
		 * @returns	The time.
		 */
		const TimeT & getValue() const;

		///@brief Get the value by converting it to the specified Ratio.
		///@template Ratio2 Ratio to be used for the conversion.
		///@return value converted from Ratio to Ratio2.
		template<typename Ratio2>
		TimeT toValue() const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;
	private:
		void _setNow(Second * r);
		template<typename Ratio2>
		void _setNow(Ratio2 * r);

#ifdef WIN32
		static int gettimeofday(struct timeval* tv, struct timezone* tzp);
#endif

		TimeT t;

	};

	using TimePointS = TimePoint<Second>;
	using TimePointMS = TimePoint<MilliSecond>;

	/**
	 * @brief		Get the TimePoint of Now
	 *
	 * @returns	The time.
	 */
	template<typename Ratio = Second>
	TimePoint<Ratio> getTime();


	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<typename Ratio>
	TimePoint<Ratio> operator+( const TimePoint<Ratio> & t1, TimeT t2 );
	template<typename Ratio>
	TimePoint<Ratio> operator+( TimeT t1, const TimePoint<Ratio> & t2 );

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator+( const TimePoint<Ratio> & t1, const Duration<Ratio2> & d );

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator+( const Duration<Ratio2> & d, const TimePoint<Ratio> & t2 );

	template<typename Ratio>
	TimePoint<Ratio> operator-( const TimePoint<Ratio> & t1, TimeT t2 );
	template<typename Ratio>
	TimePoint<Ratio> operator-( TimeT t1, const TimePoint<Ratio> & t2 );

	template<typename Ratio>
	Duration<Ratio> operator-( const TimePoint<Ratio> & t1, const TimePoint<Ratio> & t2 );

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator-( const TimePoint<Ratio> & t1, const Duration<Ratio2> & d );

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator*( const TimePoint<Ratio> & t, const Duration<Ratio2> & d );

	template<typename Ratio, class Ratio2>
	TimePoint<Ratio> operator/( const TimePoint<Ratio> & t, const Duration<Ratio2> & d );

}


#include "TimePoint.hpp"



