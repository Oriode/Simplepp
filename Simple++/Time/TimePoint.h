/**
 * @file		Time\TimePoint.h.
 *
 * @brief		Declares the time point class
 * @author	Clément Gerber
 * @date		11/07/2016 (DMY)
 */
#pragma once

#include <time.h>
#include "Duration.h"


namespace Time {

	/** @brief	Class representing a precise moment in the time ( extension of std time_t ) */
	class TimePoint {
	public:

		/** @brief	create an uninitialized TimePoint. See getTime() of getting the timepoint of the current time. */
		TimePoint();

		/**
		 * @brief			Create a TimePoint from an old school time_t object
		 *
		 * @param			timeT	The time t.
		 */
		TimePoint( const TimeT & timeT );

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
		TimePoint & operator=( const TimePoint & timePoint );
		TimePoint & operator=( const TimeT & timeT );


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class ratio>
		TimePoint & operator+=( const Duration<ratio> & d );

		template<class ratio>
		TimePoint & operator-=( const Duration<ratio> & d );

		TimePoint & operator+=( TimeT t );
		TimePoint & operator-=( TimeT t );

		/** @brief	Destructor */
		~TimePoint();


		/**
		 * @brie	f	Sets an old school time_t.
		 *
		 * @param	t	A TimeT to process.
		 */
		void setTime( const TimeT & t );


		/**
		 * @brief		Gets the time
		 *
		 * @returns	The time.
		 */
		const TimeT & getTime() const;

		static TimePoint getNow();
	private:
		TimeT t;

	};

	/**
	 * @brief		Get the TimePoint of Now
	 *
	 * @returns	The time.
	 */
	TimePoint getTime();


	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	TimePoint operator+( const TimePoint & t1, TimeT t2 );
	TimePoint operator+( TimeT t1, const TimePoint & t2 );

	template<class ratio>
	TimePoint operator+( const TimePoint & t1, const Duration<ratio> & d );

	template<class ratio>
	TimePoint operator+( const Duration<ratio> & d, const TimePoint & t2 );


	TimePoint operator-( const TimePoint & t1, TimeT t2 );
	TimePoint operator-( TimeT t1, const TimePoint & t2 );

	Duration<Second> operator-( const TimePoint & t1, const TimePoint & t2 );

	template<class ratio>
	TimePoint operator-( const TimePoint & t1, const Duration<ratio> & d );

}


#include "TimePoint.hpp"



