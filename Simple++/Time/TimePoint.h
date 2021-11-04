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
#include "../IO/IO.h"


namespace Time {

	/** @brief	Class representing a precise moment in the time ( extension of std time_t ) */
	template<typename T>
	class TimePointT : public IO::BasicIO {
	public:

		/** @brief	create an uninitialized TimePointT. See getTime() of getting the timepoint of the current time. */
		TimePointT();

		/**
		 * @brief			Create a TimePointT from an old school time_t object
		 *
		 * @param			timeT	The time t.
		 */
		TimePointT( const TimeT & timeT );

		/** @brief	Set this object to store the current moment. */
		void setNow();

		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/
		bool operator==( const TimePointT & timePoint ) const;
		bool operator!=( const TimePointT & timePoint ) const;
		bool operator>=( const TimePointT & timePoint ) const;
		bool operator<=( const TimePointT & timePoint ) const;
		bool operator<( const TimePointT & timePoint ) const;
		bool operator>( const TimePointT & timePoint ) const;


		/************************************************************************/
		/* OPERATOR EQUAL	                                                      */
		/************************************************************************/
		TimePointT & operator=( const TimePointT & timePoint );
		TimePointT & operator=( const TimeT & timeT );


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class ratio>
		TimePointT & operator+=( const Duration<ratio> & d );

		template<class ratio>
		TimePointT & operator-=( const Duration<ratio> & d );

		TimePointT & operator+=( TimeT t );
		TimePointT & operator-=( TimeT t );

		/** @brief	Destructor */
		~TimePointT();


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

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( IO::SimpleFileStream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( IO::SimpleFileStream * fileStream ) const;

		static TimePointT getNow();
	private:
		TimeT t;

	};

	using TimePoint = TimePointT<int>;

	/**
	 * @brief		Get the TimePointT of Now
	 *
	 * @returns	The time.
	 */
	template<typename T>
	TimePointT<T> getTime();


	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<typename T>
	TimePointT<T> operator+( const TimePointT<T> & t1, TimeT t2 );
	template<typename T>
	TimePointT<T> operator+( TimeT t1, const TimePointT<T> & t2 );

	template<typename T, class ratio>
	TimePointT<T> operator+( const TimePointT<T> & t1, const Duration<ratio> & d );

	template<typename T, class ratio>
	TimePointT<T> operator+( const Duration<ratio> & d, const TimePointT<T> & t2 );

	template<typename T>
	TimePointT<T> operator-( const TimePointT<T> & t1, TimeT t2 );
	template<typename T>
	TimePointT<T> operator-( TimeT t1, const TimePointT<T> & t2 );

	template<typename T>
	Duration<Second> operator-( const TimePointT<T> & t1, const TimePointT<T> & t2 );

	template<typename T, class ratio>
	TimePointT<T> operator-( const TimePointT<T> & t1, const Duration<ratio> & d );

	template<typename T, class ratio>
	TimePointT<T> operator*( const TimePointT<T> & t, const Duration<ratio> & d );

	template<typename T, class ratio>
	TimePointT<T> operator/( const TimePointT<T> & t, const Duration<ratio> & d );

}


#include "TimePoint.hpp"



