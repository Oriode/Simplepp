/**
 * @file		Time\TimePoint.h.
 *
 * @brief		Declares the time point class
 * @author	Clément Gerber
 * @date		11/07/2016 (DMY)
 */
#pragma once

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include "Duration.h"
#include "../IO/IO.h"


namespace Time {

	/** @brief	Class representing a precise moment in the time ( extension of std time_t ) */
	template<typename Ratio = Second>
	class TimePointT : public IO::BasicIO {
	public:

		/** @brief	create an uninitialized TimePointT. See getValue() of getting the timepoint of the current time. */
		TimePointT();

		/**
		 * @brief			Create a TimePointT from an old school time_t object
		 *
		 * @param			timeT	The time t.
		 */
		TimePointT( const TimeT & timeT );

		TimePointT(const TimePointT<Ratio>& tp);

		template<typename Ratio2>
		TimePointT(const TimePointT<Ratio2>& tp);

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
		TimePointT & operator=( const TimePointT<Ratio> & timePoint );
		template<typename Ratio2>
		TimePointT & operator=( const TimePointT<Ratio2> & timePoint );
		TimePointT & operator=( const TimeT & timeT );


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class Ratio2>
		TimePointT & operator+=( const Duration<Ratio2> & d );

		template<class Ratio2>
		TimePointT & operator-=( const Duration<Ratio2> & d );

		TimePointT & operator+=( TimeT t );
		TimePointT & operator-=( TimeT t );

		/** @brief	Destructor */
		~TimePointT();


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
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( IO::SimpleFileStream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( IO::SimpleFileStream * fileStream ) const;
	private:
		void _setNow(Second * r);
		template<typename Ratio2>
		void _setNow(Ratio2 * r);

#ifdef WIN32
		static int gettimeofday(struct timeval* tv, struct timezone* tzp);
#endif

		TimeT t;

	};

	using TimePoint = TimePointT<Second>;
	using TimePointMS = TimePointT<MilliSecond>;

	/**
	 * @brief		Get the TimePointT of Now
	 *
	 * @returns	The time.
	 */
	template<typename Ratio>
	TimePointT<Ratio> getValue();


	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<typename Ratio>
	TimePointT<Ratio> operator+( const TimePointT<Ratio> & t1, TimeT t2 );
	template<typename Ratio>
	TimePointT<Ratio> operator+( TimeT t1, const TimePointT<Ratio> & t2 );

	template<typename Ratio, class Ratio2>
	TimePointT<Ratio> operator+( const TimePointT<Ratio> & t1, const Duration<Ratio2> & d );

	template<typename Ratio, class Ratio2>
	TimePointT<Ratio> operator+( const Duration<Ratio2> & d, const TimePointT<Ratio> & t2 );

	template<typename Ratio>
	TimePointT<Ratio> operator-( const TimePointT<Ratio> & t1, TimeT t2 );
	template<typename Ratio>
	TimePointT<Ratio> operator-( TimeT t1, const TimePointT<Ratio> & t2 );

	template<typename Ratio>
	Duration<Ratio> operator-( const TimePointT<Ratio> & t1, const TimePointT<Ratio> & t2 );

	template<typename Ratio, class Ratio2>
	TimePointT<Ratio> operator-( const TimePointT<Ratio> & t1, const Duration<Ratio2> & d );

	template<typename Ratio, class Ratio2>
	TimePointT<Ratio> operator*( const TimePointT<Ratio> & t, const Duration<Ratio2> & d );

	template<typename Ratio, class Ratio2>
	TimePointT<Ratio> operator/( const TimePointT<Ratio> & t, const Duration<Ratio2> & d );

}


#include "TimePoint.hpp"



