/**
 * @file	Time\DateT.h.
 * @brief		Declares the date class
 * @author	Clément Gerber
 * @date		19/04/2016 (DMY)

 */
#pragma once



#include <iostream>
#include <time.h>
#include "TimePoint.h"
#include "Duration.h"
#include "../String.h"


namespace Time {

	/**
	 * @brief	Class representing a date in the time (day/month/year hour etc...)
	 * @tparam	T	Generic type parameter.
	 */
	template<typename T>
	class DateT {
	public:

		enum class ISOFormat : unsigned char {
			DateOnly = 0,
			DateTime = 1,
			DateTimeOffset = 2
		};


		/************************************************************************/
		/* CONSTRUCTOR															*/
		/************************************************************************/
		/** @brief	Empty constructor, not initialized, use Time::getDate() to get the current date */
		DateT();

		DateT( int year, unsigned char month, unsigned char day, unsigned char hours, unsigned char minutes, unsigned char seconds, TimeT utcBias );

		/**
		 * @brief	copy constructor
		 * @param 	date	Other date to copy.
		 */
		DateT( const DateT & date );

		/**
		 * @brief	Constructor from a struct tm
		 * @param 	date	DateT to copy.
		 * @param	utcBias	Delta in seconds from UTC.
		 */
		DateT( const tm & date, TimeT utcBias );


		/**
		 * @brief	Constructor from a time point
		 * @param 	timePoint	Time point to use.
		 * @param	utcBias	Delta in seconds from UTC.
		 */
		DateT( const TimePoint<Second> & timePoint, TimeT utcBias = 0 );


		/************************************************************************/
		/* ARITHMETIC OPERATOR												*/
		/************************************************************************/
		/**
		 * @brief	Addition assignment operator
		 * @param 	duration	The duration.
		 * @returns	The result of the operation.
		 */
		template<typename ratio>
		DateT & operator+=( const Duration<ratio> & duration );

		/**
		 * @brief	Subtraction assignment operator
		 * @param 	duration	The duration.
		 * @returns	The result of the operation.
		 */
		template<typename ratio>
		DateT & operator-=( const Duration<ratio> & duration );

		/**
		 * @brief	Addition assignment operator
		 * @param 	timeT	The time t.
		 * @returns	The result of the operation.
		 */
		DateT & operator+=( TimeT timeT );
		/**
		 * @brief	Subtraction assignment operator
		 * @param 	timeT	The time t.
		 * @returns	The result of the operation.
		 */
		DateT & operator-=( TimeT timeT );

		/************************************************************************/
		/* LOGICAL OPERATOR                                                     */
		/************************************************************************/
		/**
		 * @brief	Equality operator
		 * @param 	d	A DateT to process.
		 * @returns	True if the parameters are considered equivalent.
		 */
		bool operator==( const DateT & d );
		/**
		 * @brief	Inequality operator
		 * @param 	d	A DateT to process.
		 * @returns	True if the parameters are not considered equivalent.
		 */
		bool operator!=( const DateT & d );
		/**
		 * @brief	Less-than comparison operator
		 * @param 	d	A DateT to process.
		 * @returns	True if the first parameter is less than the second.
		 */
		bool operator<( const DateT & d );
		/**
		 * @brief	Greater-than comparison operator
		 * @param 	d	A DateT to process.
		 * @returns	True if the first parameter is greater than to the second.
		 */
		bool operator>( const DateT & d );
		/**
		 * @brief	Greater-than-or-equal comparison operator
		 * @param 	d	A DateT to process.
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		bool operator>=( const DateT & d );
		/**
		 * @brief	< .
		 * @param 	d	A DateT to process.
		 * @returns	True if the first parameter is less than or equal to the second.
		 */
		bool operator<=( const DateT & d );


		/************************************************************************/
		/* OPERATOR =															*/
		/**
		 * @brief	Assignment operator
		 * @param 	date	The date.
		 * @returns	A shallow copy of this object.
		 */
		DateT & operator=( const DateT & date );
		/**
		 * @brief	Assignment operator
		 * @param 	date	The date.
		 * @returns	A shallow copy of this object.
		 */
		DateT & operator=( const tm & date );
		/**
		 * @brief	Assignment operator
		 * @param 	timePoint	The time point.
		 * @returns	A shallow copy of this object.
		 */
		DateT & operator=( const TimePoint<Second> & timePoint );


		/**
		 * @brief	get the seconds of this date
		 * @returns	seconds [0-59].
		 */
		unsigned char getSeconds() const;

		/**
		 * @brief	get the minutes of this date
		 * @returns	minutes [0-59].
		 */
		unsigned char getMinutes() const;


		/**
		 * @brief	get the hours of this date
		 * @returns	hours [0-23].
		 */
		unsigned char getHours() const;

		/**
		 * @brief	get the day of the month of this date
		 * @returns	day of the month [1-31].
		 */
		unsigned char getDay() const;


		/**
		 * @brief	get the month of this date
		 * @returns	Month [1-12].
		 */
		unsigned char getMonth() const;


		/**
		 * @brief	get the year of this date
		 * @returns	year.
		 */
		int getYear() const;

		/**
		 * @brief	Gets UTC bias
		 * @returns	The UTC bias.
		 */
		TimeT getUtcBias() const;


		/**
		 * @brief	set the date to now
		 * @param 	utcBias	(Optional) The UTC bias.
		 */
		void setNow( TimeT utcBias = getLocalUTCBias() );

		/**
		 * @brief	Sets to time point
		 * @param 	timePoint	The time point.
		 * @param 	utcBias  	(Optional) The UTC bias.
		 */
		void setToTimePoint( const TimePoint<Second> & timePoint, TimeT utcBias = getLocalUTCBias() );

		/**
		 * @brief	set the seconds of this date
		 * @param 	s	seconds [0-59].
		 */
		void setSeconds( unsigned char s );

		/**
		 * @brief	set the minutes of this date
		 * @param 	m	minutes [0-59].
		 */
		void setMinutes( unsigned char m );

		/**
		 * @brief	set the hours of this date
		 * @param 	h	hours [0-23].
		 */
		void setHours( unsigned char h );

		/**
		 * @brief	set the day of this date
		 * @param 	d	day of the month [1-31].
		 */
		void setDay( unsigned char d );

		/**
		 * @brief	set the month of this date
		 * @param 	m	.
		 */
		void setMonth( unsigned char m );

		/**
		 * @brief	set the year of this date
		 * @param 	y	.
		 */
		void setYear( int y );

		/**
		 * @brief	Sets UTC bias
		 * @param 	s	The UTC Bias in seconds.
		 */
		void setUTCBias( TimeT s );


		/**
		 * @brief	Create an human readable string of this date with a default template "<WeekDay> <MonthName> <DayNumber> <Hour>:<Minutes>:<Seconds>"
		 * @tparam	T	Generic type parameter.
		 * @returns	Human readable string of this date.
		 */
		template<typename S = String>
		S toString() const;

		/**
		 * @brief	Create an human readable string of this date using a specified template
		 * @tparam	T	Generic type parameter.
		 * @param 	str	template to be used. Available symbols to be used : Y : Year (four digits)
		 * 				y : Year (two last digits)
		 * 				b : Month Name m : Month number d : Day Number of the month (With zeros)
		 * 				e : Day number of the month (Without zeros)
		 * 				a : Week Day Name u : Day number of the week H : Hours (with zeros)
		 * 				M : Minutes (with zeros)
		 * 				S : Seconds (with zeros)
		 * @returns	Str as a BasicString<T>
		 */
		template<typename S = String>
		S toString( const S & str ) const;

		/**
		 * @brief	Concatenates this date to the given string.
		 *
		 * @tparam	C	Type of the string.
		 * @param [in,out]	str	The string.
		 */
		template<typename S = String>
		void concat( S & str ) const;

		/**
		 * @brief	Concatenates this date to the given string with a template string.
		 *
		 * @tparam	C	Type of the string.
		 * @param [in,out]	str	The string.
		 * @param 		  	tpl	The template.
		 */
		template<typename S = String>
		void concat( S & str, const S & tpl ) const;

		/**
		 * @brief		Generate an ISO 8601 String of this Date.
		 * @return		ISO 8601 String.		  
		 */
		template<typename S = String>
		S toStringISO( DateT<T>::ISOFormat isoFormat = DateT<T>::ISOFormat::DateTimeOffset ) const;

		/**
		 * @brief	Concatenates this date to the given string as ISO 8601.
		 *
		 * @tparam	C	Type of the string.
		 * @param [in,out]	str	The string.
		 */
		template<typename S = String>
		void concatISO( S & str, DateT<T>::ISOFormat isoFormat = DateT<T>::ISOFormat::DateTimeOffset ) const;

		/**
		 * @brief	convert this date to a TimePoint<Second>
		 * @returns	This object as a TimePoint<Second>.
		 */
		TimePoint<Second> toTimePoint() const;

		/**
		 * @brief	get the day number of the week (Monday is the first one)
		 * @param 	date	The date.
		 * @returns	day number of the week [0-6].
		 */
		static unsigned char getWeekDay( const DateT & date );

		/**
		 * @brief	compute if a year is a leap one
		 * @param 	year	Year to be used.
		 * @returns	True of the year is a leap one, false instead.
		 */
		static bool isYearLeapYear( int year );

		/**
		 * @brief	compute the day number of the week from a day number of the month, a month and a year
		 * @param 	day  	day number of the month [1-31].
		 * @param 	month	month number [0-11].
		 * @param 	year 	year.
		 * @returns	day number of the week.
		 */
		static unsigned char getWeekDay( unsigned char day, unsigned char month, int year );


		/**
		 * @brief	get the week day English name from the day number of the week.
		 * @tparam	T	Generic type parameter.
		 * @param 	weekDay	Day number of the week [0-6].
		 * @returns	Weekday name as a StringASCII<T>
		 */
		template<typename S = String>
		static const S & getWeekDayStr( unsigned char weekDay );


		/**
		 * @brief	get the month English name from the month number
		 * @tparam	T	Generic type parameter.
		 * @param 	month	number [0-11].
		 * @returns	Month name as a StringASCII<T>
		 */
		template<typename S = String>
		static const S & getMonthStr( unsigned char month );


		/**
		 * @brief	get the number of day in a specified year
		 * @param 	year	Year.
		 * @returns	number of day of the year.
		 */
		static unsigned int getNumDays( int year );


		/**
		 * @brief	Parses the given buffer
		 * @param [in,out]	buffer	If non-null, the buffer.
		 * @returns	A DateT.
		 */
		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		static DateT parse( const C ** buffer, const C ** tpl, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		static DateT parse( const C * buffer, const C * tpl, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		static DateT parse( const BasicString<C> & str, const BasicString<C> & tpl, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		static DateT parse( const C ** buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		static DateT parse( const C * buffer, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );

		template<typename C, typename EndFunc = BasicString<C>::IsEndSentinel>
		static DateT parse( const BasicString<C> & str, const EndFunc & endFunc = BasicString<C>::IS_END_SENTINEL );



		/**
		 * @brief	Gets local UTC bias
		 * @returns	local time bias.
		 */
		static TimeT getLocalUTCBias();

		/** @brief	Destructor */
		~DateT();


	private:
		/** @brief	The month table */
		static const unsigned char MonthTable[  ];
		/** @brief	The month table leap year */
		static const unsigned char MonthTableLeapYear[  ];

		/** @brief Number of days in a month in a non-leap year. */
		static const TimeT numberOfDaysInMonth[];
		/** @brief Number of days in a month in a leap year */
		static const TimeT numberOfDaysInMonthLeap[];

		/** @brief	The local UTC bias */
		static const TimeT localUTCBias;

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
		/** @brief UTC bias */
		TimeT utcBias;



		/**
		 * @brief	Retrieves local UTC bias
		 * @returns	A const long int.
		 */
		static TimeT _retrieveLocalUTCBias();

		template<typename C>
		void readUTCBias( const C ** buffer );
	};



	/**
	 * @brief	Addition operator
	 * @param 	date		The first value.
	 * @param 	duration	A value to add to it.
	 * @returns	The result of the operation.
	 */
	template<typename ratio, typename T>
	DateT<T> operator+( const DateT<T> & date, const Duration<ratio> & duration );
	/**
	 * @brief	Addition operator
	 * @param 	duration	The first value.
	 * @param 	date		A value to add to it.
	 * @returns	The result of the operation.
	 */
	template<typename ratio, typename T>
	DateT<T> operator+( const Duration<ratio> & duration, const DateT<T> & date );
	/**
	 * @brief	Subtraction operator
	 * @param 	date		The first value.
	 * @param 	duration	A value to subtract from it.
	 * @returns	The result of the operation.
	 */
	template<typename ratio, typename T>
	DateT<T> operator-( const DateT<T> & date, const Duration<ratio> & duration );

	/**
	 * @brief	Subtraction operator
	 * @param 	d1	The first value.
	 * @param 	d2	A value to subtract from it.
	 * @returns	The result of the operation.
	 */
	template<typename T>
	Duration<Second> operator-( const DateT<T> & d1, const DateT<T> & d2 );

	/**
	 * @brief	Gets the date
	 * @tparam	T	Generic type parameter.
	 * @param 	utcBias	(Optional) The UTC bias.
	 * @returns	The date.
	 */
	template<typename T = char>
	DateT<T> getDate( TimeT utcBias = DateT<T>::getLocalUTCBias() );

	/** @brief	The date */
	using Date = DateT<char>;
}







#include "Date.hpp"
