///@file Date.h
///@brief Date Class
///@author Cl�ment Gerber
///@date 19/04/2016 (DMY) 

#pragma once



#include <iostream>
#include <ctime>
#include "TimePoint.h"
#include "String.h"
#include "IO.h"


namespace Time {


	class Date {
	public:


		/************************************************************************/
		/* CONSTRUCTOR	                                                      */
		/************************************************************************/
		Date();
		Date(const Date & date);
		Date(const tm & date);
		Date(const TimePoint & timePoint);



		/************************************************************************/
		/* OPERATOR =	                                                      */
		/************************************************************************/
		Date & operator=(const Date & date);
		Date & operator=(const tm & date);
		Date & operator=(const TimePoint & timePoint);



		unsigned char getSeconds() const;
		unsigned char getMinutes() const;
		unsigned char getHours() const;
		unsigned char getDay() const;
		unsigned char getMonth() const;
		int getYear() const;

		void setNow();

		void setSeconds(unsigned char s);
		void setMinutes(unsigned char m);
		void setHours(unsigned char h);
		void setDay(unsigned char d);
		void setMonth(unsigned char m);
		void setYear(int y);



		template<typename T>
		BasicString<T> toString() const;

		template<typename T>
		BasicString<T> toString(const BasicString<T> & str) const;

		/*String toString() const;
		String toString(const String & str) const;


		WString toWString() const;
		WString toWString(const WString & str) const;*/


		//WString toWString() const;
		//WString toWString(const WString & str) const;

		TimePoint toTimePoint() const;

		static unsigned char getWeekDay(const Date & date);
		static const bool isYearLeapYear(int year);
		static const unsigned char getWeekDay(unsigned char day, unsigned char month, int year);


		/*static const String & getWeekDayStr(unsigned char weekDay);
		static const String & getMonthStr(unsigned char month);

		static const WString & getWeekDayWStr(unsigned char weekDay);
		static const WString & getMonthWStr(unsigned char month);
		*/


		template<typename T = char>
		static const BasicString<T> & getWeekDayStr(unsigned char weekDay);
		template<typename T = char>
		static const BasicString<T> & getMonthStr(unsigned char month);



		static const unsigned int getNumDays(int year);
		static const unsigned long long getLocalUTCBias();

		~Date();


	private:
		static const unsigned char MonthTable[12];
		static const unsigned char MonthTableLeapYear[12];
		
		static const unsigned long long localUTCBias;

		int year;								//Year
		unsigned char month;						//Months since January (0-11)
		unsigned char dayInMonth;					//day of the month (1-31)
		unsigned char hours;						//Hours since midnight (0-23)
		unsigned char minutes;						//minutes after the hour (0-59)
		unsigned char seconds;						//seconds after the minute (0-59)


		static const unsigned long long _retrieveLocalUTCBias();
	};



	Date getDate();
}





#include "Date.hpp"
