///@file Date.h
///@brief Date Class
///@author Clément Gerber
///@date 19/04/2016 (DMY) 

#pragma once



#include <iostream>
#include <ctime>
#include "TimePoint.h"
#include "Duration.h"
#include "../String.h"


namespace Time {

	///@brief Class representing a date in the time (day/month/year hour etc...)
	class Date {
	public:


		/************************************************************************/
		/* CONSTRUCTOR															*/
		/************************************************************************/
		///@brief Empty constructor, not initialized, use Time::getDate() to get the current date
		Date();


		///@brief copy constructor
		///@param date Other date to copy
		Date( const Date & date );

		///@brief Constructor from a struct tm
		///@param date Date to copy
		Date( const tm & date );


		///@brief Constructor from a time point
		///@param timePoint Time point to use
		Date( const TimePoint & timePoint );


		/************************************************************************/
		/* ARITHMETIC OPERATOR													*/
		/************************************************************************/
		template<typename ratio>
		Date & operator+=( const Duration<ratio> & duration );

		template<typename ratio>
		Date & operator-=( const Duration<ratio> & duration );

		Date & operator+=( TimeT timeT );
		Date & operator-=( TimeT timeT );

		/************************************************************************/
		/* LOGICAL OPERATOR                                                     */
		/************************************************************************/
		bool operator==( const Date & d );
		bool operator!=( const Date & d );
		bool operator<( const Date & d );
		bool operator>( const Date & d );
		bool operator>=( const Date & d );
		bool operator<=( const Date & d );


		/************************************************************************/
		/* OPERATOR =															*/
		/************************************************************************/
		Date & operator=( const Date & date );
		Date & operator=( const tm & date );
		Date & operator=( const TimePoint & timePoint );


		///@brief get the seconds of this date
		///@return seconds [0-59]
		unsigned char getSeconds() const;

		///@brief get the minutes of this date
		///@return minutes [0-59]
		unsigned char getMinutes() const;


		///@brief get the hours of this date
		///@return hours [0-23]
		unsigned char getHours() const;

		///@brief get the day of the month of this date
		///@return day of the month [1-31]
		unsigned char getDay() const;


		///@brief get the month of this date
		///@return Month [0-11]
		unsigned char getMonth() const;


		///@brief get the year of this date
		///@return year
		int getYear() const;


		///@brief set the date to now
		void setNow();


		///@brief set the seconds of this date
		///@param s seconds [0-59]
		void setSeconds( unsigned char s );

		///@brief set the minutes of this date
		///@param m minutes [0-59]
		void setMinutes( unsigned char m );

		///@brief set the hours of this date
		///@param h hours [0-23]
		void setHours( unsigned char h );

		///@brief set the day of this date
		///@param d day of the month [1-31]
		void setDay( unsigned char d );

		///@brief set the month of this date
		///@param month [0-11]
		void setMonth( unsigned char m );

		///@brief set the year of this date
		///@param year
		void setYear( int y );


		///@brief Create an human readable string of this date with a default template "<WeekDay> <MonthName> <DayNumber> <Hour>:<Minutes>:<Seconds>"
		///@return Human readable string of this date
		template<typename T = char>
		BasicString<T> toString() const;

		///@brief Create an human readable string of this date using a specified template
		///@param str template to be used. Available symbols to be used :
		///		Y : Year (four digits)
		///		y : Year (two last digits)
		///		b : Month Name 
		///		m : Month number
		///		d : Day Number of the month (With zeros)
		///		e : Day number of the month (Without zeros)
		///		a : Week Day Name
		///		u : Day number of the week
		///		H : Hours (with zeros)
		///		M : Minutes (with zeros)
		///		S : Seconds (with zeros)
		template<typename T = char>
		BasicString<T> toString( const BasicString<T> & str ) const;


		///@brief convert this date to a TimePoint
		TimePoint toTimePoint() const;

		///@brief get the day number of the week (Monday is the first one)
		///@return day number of the week [0-6]
		static unsigned char getWeekDay( const Date & date );

		///@brief compute if a year is a leap one
		///@param year Year to be used
		///@return True of the year is a leap one, false instead.
		static const bool isYearLeapYear( int year );

		///@brief compute the day number of the week from a day number of the month, a month and a year
		///@param day day number of the month [1-31]
		///@param month month number [0-11]
		///@param year year
		///@return day number of the week
		static const unsigned char getWeekDay( unsigned char day, unsigned char month, int year );


		///@brief get the week day English name from the day number of the week.
		///@param weekDay Day number of the week [0-6]
		///@return Weekday name as a String<T>
		template<typename T = char>
		static const BasicString<T> & getWeekDayStr( unsigned char weekDay );


		///@brief get the month English name from the month number
		///@param month number [0-11]
		///@return Month name as a String<T>
		template<typename T = char>
		static const BasicString<T> & getMonthStr( unsigned char month );


		///@brief get the number of day in a specified year
		///@param year Year
		///@return number of day of the year
		static const unsigned int getNumDays( int year );


		///@param get the local time bias in seconds
		///@return local time bias
		static const long long getLocalUTCBias();

		~Date();


	private:
		static const unsigned char MonthTable[12];
		static const unsigned char MonthTableLeapYear[12];

		static const long long localUTCBias;

		int year;								    //Year
		unsigned char month;						//Months since January (0-11)
		unsigned char dayInMonth;					//day of the month (1-31)
		unsigned char hours;						//Hours since midnight (0-23)
		unsigned char minutes;						//minutes after the hour (0-59)
		unsigned char seconds;						//seconds after the minute (0-59)



		static const long long _retrieveLocalUTCBias();
	};




	template<typename ratio>
	Date operator+( const Date & date, const Duration<ratio> & duration );
	template<typename ratio>
	Date operator+( const Duration<ratio> & duration, const Date & date );
	template<typename ratio>
	Date operator-( const Date & date, const Duration<ratio> & duration );



	Duration<Second> operator-( const Date & d1, const Date & d2 );



	Date getDate();
}





#include "Date.hpp"
