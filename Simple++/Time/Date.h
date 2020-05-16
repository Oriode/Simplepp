/**
 * @file	Time\Date.h.
 *
 * @brief		Declares the date class
 * @author	Clément Gerber
 * @date		19/04/2016 (DMY)

 */
#pragma once



#include <iostream>
#include <ctime>
#include "TimePoint.h"
#include "Duration.h"
#include "../String.h"


namespace Time {

	/** @brief	Class representing a date in the time (day/month/year hour etc...) */
	class Date {
	public:


		/************************************************************************/
		/* CONSTRUCTOR															*/
		/************************************************************************/
		/** @brief	Empty constructor, not initialized, use Time::getDate() to get the current date */
		Date();


		/**
		 * @brief	copy constructor
		 *
		 * @param	date	Other date to copy.
		 */
		Date( const Date & date );

		/**
		 * @brief	Constructor from a struct tm
		 *
		 * @param	date	Date to copy.
		 */
		Date( const tm & date );


		/**
		 * @brief	Constructor from a time point
		 *
		 * @param	timePoint	Time point to use.
		 */
		Date( const TimePoint & timePoint );


		/************************************************************************/
		/* ARITHMETIC OPERATOR												*/
		/************************************************************************/
		/**
		 * @brief	Addition assignment operator
		 *
		 * @param	duration	The duration.
		 *
		 * @returns	The result of the operation.
		 */
		template<typename ratio>
		Date & operator+=( const Duration<ratio> & duration );

		/**
		 * @brief	Subtraction assignment operator
		 *
		 * @param	duration	The duration.
		 *
		 * @returns	The result of the operation.
		 */
		template<typename ratio>
		Date & operator-=( const Duration<ratio> & duration );

		/**
		 * @brief	Addition assignment operator
		 *
		 * @param	timeT	The time t.
		 *
		 * @returns	The result of the operation.
		 */
		Date & operator+=( TimeT timeT );
		/**
		 * @brief	Subtraction assignment operator
		 *
		 * @param	timeT	The time t.
		 *
		 * @returns	The result of the operation.
		 */
		Date & operator-=( TimeT timeT );

		/************************************************************************/
		/* LOGICAL OPERATOR                                                     */
		/************************************************************************/
		/**
		 * @brief	Equality operator
		 *
		 * @param	d	A Date to process.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */
		bool operator==( const Date & d );
		/**
		 * @brief	Inequality operator
		 *
		 * @param	d	A Date to process.
		 *
		 * @returns	True if the parameters are not considered equivalent.
		 */
		bool operator!=( const Date & d );
		/**
		 * @brief	Less-than comparison operator
		 *
		 * @param	d	A Date to process.
		 *
		 * @returns	True if the first parameter is less than the second.
		 */
		bool operator<( const Date & d );
		/**
		 * @brief	Greater-than comparison operator
		 *
		 * @param	d	A Date to process.
		 *
		 * @returns	True if the first parameter is greater than to the second.
		 */
		bool operator>( const Date & d );
		/**
		 * @brief	Greater-than-or-equal comparison operator
		 *
		 * @param	d	A Date to process.
		 *
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		bool operator>=( const Date & d );
		///< .
		bool operator<=( const Date & d );


		/************************************************************************/
		/* OPERATOR =															*/
		/**
		 * @brief	Assignment operator
		 *
		 * @param	date	The date.
		 *
		 * @returns	A shallow copy of this object.
		 */
		Date & operator=( const Date & date );
		/**
		 * @brief	Assignment operator
		 *
		 * @param	date	The date.
		 *
		 * @returns	A shallow copy of this object.
		 */
		Date & operator=( const tm & date );
		/**
		 * @brief	Assignment operator
		 *
		 * @param	timePoint	The time point.
		 *
		 * @returns	A shallow copy of this object.
		 */
		Date & operator=( const TimePoint & timePoint );


		/**
		 * @brief	get the seconds of this date
		 *
		 * @returns	seconds [0-59].
		 */
		unsigned char getSeconds() const;

		/**
		 * @brief	get the minutes of this date
		 *
		 * @returns	minutes [0-59].
		 */
		unsigned char getMinutes() const;


		/**
		 * @brief	get the hours of this date
		 *
		 * @returns	hours [0-23].
		 */
		unsigned char getHours() const;

		/**
		 * @brief	get the day of the month of this date
		 *
		 * @returns	day of the month [1-31].
		 */
		unsigned char getDay() const;


		/**
		 * @brief	get the month of this date
		 *
		 * @returns	Month [0-11].
		 */
		unsigned char getMonth() const;


		/**
		 * @brief	get the year of this date
		 *
		 * @returns	year.
		 */
		int getYear() const;


		/** @brief	set the date to now */
		void setNow();


		/**
		 * @brief	set the seconds of this date
		 *
		 * @param	s	seconds [0-59].
		 */
		void setSeconds( unsigned char s );

		/**
		 * @brief	set the minutes of this date
		 *
		 * @param	m	minutes [0-59].
		 */
		void setMinutes( unsigned char m );

		/**
		 * @brief	set the hours of this date
		 *
		 * @param	h	hours [0-23].
		 */
		void setHours( unsigned char h );

		/**
		 * @brief	set the day of this date
		 *
		 * @param	d	day of the month [1-31].
		 */
		void setDay( unsigned char d );

		/**
		 * @brief	set the month of this date
		 *
		 * @param	m	.
		 */
		void setMonth( unsigned char m );

		/**
		 * @brief	set the year of this date
		 *
		 * @param	y	.
		 */
		void setYear( int y );


		/**
		 * @brief	Create an human readable string of this date with a default template "<WeekDay> <MonthName> <DayNumber> <Hour>:<Minutes>:<Seconds>"
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	Human readable string of this date.
		 */
		template<typename T = char>
		BasicString<T> toString() const;

		/**
		 * @brief	Create an human readable string of this date using a specified template
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	str	template to be used. Available symbols to be used : Y : Year (four digits)
		 * 				y : Year (two last digits)
		 * 				b : Month Name m : Month number d : Day Number of the month (With zeros)
		 * 				e : Day number of the month (Without zeros)
		 * 				a : Week Day Name u : Day number of the week H : Hours (with zeros)
		 * 				M : Minutes (with zeros)
		 * 				S : Seconds (with zeros)
		 *
		 * @returns	Str as a BasicString<T>
		 */
		template<typename T = char>
		BasicString<T> toString( const BasicString<T> & str ) const;


		/**
		 * @brief	convert this date to a TimePoint
		 *
		 * @returns	This object as a TimePoint.
		 */
		TimePoint toTimePoint() const;

		/**
		 * @brief	get the day number of the week (Monday is the first one)
		 *
		 * @param	date	The date.
		 *
		 * @returns	day number of the week [0-6].
		 */
		static unsigned char getWeekDay( const Date & date );

		/**
		 * @brief	compute if a year is a leap one
		 *
		 * @param	year	Year to be used.
		 *
		 * @returns	True of the year is a leap one, false instead.
		 */
		static const bool isYearLeapYear( int year );

		/**
		 * @brief	compute the day number of the week from a day number of the month, a month and a year
		 *
		 * @param	day  	day number of the month [1-31].
		 * @param	month	month number [0-11].
		 * @param	year 	year.
		 *
		 * @returns	day number of the week.
		 */
		static const unsigned char getWeekDay( unsigned char day, unsigned char month, int year );


		/**
		 * @brief	get the week day English name from the day number of the week.
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	weekDay	Day number of the week [0-6].
		 *
		 * @returns	Weekday name as a StringASCII<T>
		 */
		template<typename T = char>
		static const BasicString<T> & getWeekDayStr( unsigned char weekDay );


		/**
		 * @brief	get the month English name from the month number
		 *
		 * @tparam	T	Generic type parameter.
		 * @param	month	number [0-11].
		 *
		 * @returns	Month name as a StringASCII<T>
		 */
		template<typename T = char>
		static const BasicString<T> & getMonthStr( unsigned char month );


		/**
		 * @brief	get the number of day in a specified year
		 *
		 * @param	year	Year.
		 *
		 * @returns	number of day of the year.
		 */
		static const unsigned int getNumDays( int year );


		/**
		 * @brief	Gets local UTC bias
		 *
		 * @returns	local time bias.
		 *
		 * ### param	get	the local time bias in seconds.
		 */
		static const long long getLocalUTCBias();

		/** @brief	Destructor */
		~Date();


	private:
		/** @brief	The month table[ 12] */
		static const unsigned char MonthTable[ 12 ];
		/** @brief	The month table leap year[ 12] */
		static const unsigned char MonthTableLeapYear[ 12 ];

		/** @brief	The local UTC bias */
		static const long long localUTCBias;

		/** @brief	Year */
		int year;
		/** @brief	Months since January (0-11) */
		unsigned char month;
		/** @brief	day of the month (1-31) */
		unsigned char dayInMonth;
		/** @brief	Hours since midnight (0-23) */
		unsigned char hours;
		/** @brief	minutes after the hour (0-59) */
		unsigned char minutes;
		/** @brief	seconds after the minute (0-59) */
		unsigned char seconds;



		/**
		 * @brief	Retrieves local UTC bias
		 *
		 * @returns	A const long.
		 */
		static const long long _retrieveLocalUTCBias();
	};




	/**
	 * @brief	Addition operator
	 *
	 * @param	date		The first value.
	 * @param	duration	A value to add to it.
	 *
	 * @returns	The result of the operation.
	 */
	template<typename ratio>
	Date operator+( const Date & date, const Duration<ratio> & duration );
	/**
	 * @brief	Addition operator
	 *
	 * @param	duration	The first value.
	 * @param	date		A value to add to it.
	 *
	 * @returns	The result of the operation.
	 */
	template<typename ratio>
	Date operator+( const Duration<ratio> & duration, const Date & date );
	/**
	 * @brief	Subtraction operator
	 *
	 * @param	date		The first value.
	 * @param	duration	A value to subtract from it.
	 *
	 * @returns	The result of the operation.
	 */
	template<typename ratio>
	Date operator-( const Date & date, const Duration<ratio> & duration );



	/**
	 * @brief	Subtraction operator
	 *
	 * @param	d1	The first value.
	 * @param	d2	A value to subtract from it.
	 *
	 * @returns	The result of the operation.
	 */
	Duration<Second> operator-( const Date & d1, const Date & d2 );



	/**
	 * @brief	Gets the date
	 *
	 * @returns	The date.
	 */
	Date getDate();
}





#include "Date.hpp"
