#include "Date.h"



namespace Time {
	const unsigned char Date::MonthTable[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
	const unsigned char Date::MonthTableLeapYear[12] = { 6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };


	const unsigned long long Date::localUTCBias = Date::_retrieveLocalUTCBias();


	/************************************************************************/
	/* CONSTRUCTOR	                                                      */
	/************************************************************************/
	Date::Date() {

	}
	Date::Date( const Date & date ) {
		*this = date;
	}
	Date::Date( const tm & date ) {
		*this = date;
	}
	Date::Date( const TimePoint & timePoint ) {
		*this = timePoint;
	}



	/************************************************************************/
	/* OPERATOR =	                                                      */
	/************************************************************************/
	Date & Date::operator=( const Date & date ) {

		this -> year = date.year;
		this -> month = date.month;
		this -> dayInMonth = date.dayInMonth;
		this -> hours = date.hours;
		this -> minutes = date.minutes;
		this -> seconds = date.seconds;

		return *this;
	}
	Date & Date::operator=( const tm & date ) {

		this -> year = date.tm_year + 1900;
		this -> month = date.tm_mon;
		this -> dayInMonth = date.tm_mday;
		this -> hours = date.tm_hour;
		this -> minutes = date.tm_min;
		this -> seconds = date.tm_sec;

		return *this;
	}



	Date & Date::operator=( const TimePoint & timePoint ) {
		this -> year = 1970;
		this -> month = 0;


		TimeT unixTime = timePoint.getTime() - getLocalUTCBias();
		bool isLeapYear = false;

		//Get the Year Number
		while ( true ) {
			isLeapYear = isYearLeapYear( this -> year );
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * 366;
			else
				numSeconds = 3600 * 24 * 365;

			if ( unixTime > numSeconds ) {
				unixTime -= numSeconds;
				this -> year++;
				if ( unixTime < numSeconds )
					break;
			}
		}

		static TimeT numberOfDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static TimeT numberOfDaysInMonthLeap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		//Get the Month Number
		while ( true ) {
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * numberOfDaysInMonthLeap[this -> month];
			else
				numSeconds = 3600 * 24 * numberOfDaysInMonth[this -> month];


			if ( unixTime > numSeconds ) {
				unixTime -= numSeconds;
				this -> month++;
				if ( unixTime < numSeconds )
					break;
			}
		}



		this -> dayInMonth = ( unsigned char ) ( unixTime / ( 3600 * 24 ) + 1 );
		unixTime %= ( 3600 * 24 );
		this -> hours = ( unsigned char ) ( unixTime / 3600 );
		unixTime %= ( 3600 );
		this -> minutes = ( unsigned char ) ( unixTime / 60 );
		unixTime %= ( 60 );
		this -> seconds = ( unsigned char ) ( unixTime );


		return *this;
	}

	void Date::setNow() {
		operator=( TimePoint::getNow() );
	}

	unsigned char Date::getSeconds() const {
		return this -> seconds;
	}
	unsigned char Date::getMinutes() const {
		return this -> minutes;
	}
	unsigned char Date::getHours() const {
		return this -> hours;
	}
	unsigned char Date::getDay() const {
		return this -> dayInMonth;
	}
	unsigned char Date::getMonth() const {
		return this -> month;
	}
	int Date::getYear() const {
		return this -> year;
	}

	unsigned char Date::getWeekDay( const Date & date ) {
		return getWeekDay( date.getDay(), date.getMonth(), date.getYear() );
	}

	void Date::setSeconds( unsigned char s ) {
		this -> seconds = s;
	}
	void Date::setMinutes( unsigned char m ) {
		this -> minutes = m;
	}
	void Date::setHours( unsigned char h ) {
		this -> hours = h;
	}
	void Date::setDay( unsigned char d ) {
		this -> dayInMonth = d;
	}
	void Date::setMonth( unsigned char m ) {
		this -> month = m;
	}
	void Date::setYear( int y ) {
		this -> year = y;
	}


	/*const String & Date::getWeekDayStr(unsigned char weekDay) {
		return weekDayShortStr[weekDay];
	}

	const String & Date::getMonthStr(unsigned char month) {
		return monthShortStr[month];
	}
	const WString & Date::getWeekDayWStr(unsigned char weekDay) {
		return weekDayShortWStr[weekDay];
	}

	const WString & Date::getMonthWStr(unsigned char month) {
		return monthShortWStr[month];
	}*/




	/*
		String Date::toString() const {
			String newString;
			newString.reserve(100);


			newString << getWeekDayStr(Date::getWeekDay(*this)) << ' ' << getMonthStr(getMonth()) << ' ' << getDay() << ' ';


			if ( getHours() < 10 )
				newString << char('0') << char('0' + getHours());
			else
				newString << getHours();

			newString << char(':');

			if ( getMinutes() < 10 )
				newString << char('0') << char('0' + getMinutes());
			else
				newString << getMinutes();

			newString << char(':');

			if ( getSeconds() < 10 )
				newString << char('0') << char('0' + getSeconds());
			else
				newString << getSeconds();

			return newString;
		}


		String Date::toString(const String & str) const {

			String newString;
			newString.reserve(100);

			for ( auto it = str.getBegin(); it != str.getEnd(); it++ ) {
				switch ( *it ) {
				case '\\':
					it++;
					break;
					//YEAR
				case 'Y':
					newString << getYear();
					break;
				case 'y':
					newString << getYear() % 100;
					break;
					//MONTH
				case 'b':
					newString << getMonthStr(getMonth());
					break;
				case 'm':
					if ( getMonth() < 10 ) newString << char('0') << char('0' + getMonth());
					else newString << getMonth();
					break;
					//DAY OF THE YEAR
				case 'd':
					if ( getDay() < 10 ) newString << T('0') << T('0' + getDay());
					else newString << getDay();
					break;
				case 'e':
					newString << getDay();
					break;
					//DAY OF THE WEEK
				case 'a':
					newString << getWeekDayStr(Date::getWeekDay(*this));
					break;
				case 'u':
					newString << Date::getWeekDay(*this);
					break;
					//HOURS
				case 'H':
					if ( getHours() < 10 ) newString << T('0') << T('0' + getHours());
					else newString << getHours();
					break;
				case 'M':
					if ( getMinutes() < 10 ) newString << T('0') << T('0' + getMinutes());
					else newString << getMinutes();
					break;
				case 'S':
					if ( getSeconds() < 10 ) newString << T('0') << T('0' + getSeconds());
					else newString << getSeconds();
					break;
				default:
					newString << *it;
				}
			}

			return newString;
		}
	*/




	TimePoint Date::toTimePoint() const {

		TimeT t( 0 );

		bool isLeapYear = false;

		for ( int year = 1970; year < this -> year; year++ ) {
			isLeapYear = isYearLeapYear( year );
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * 366;
			else
				numSeconds = 3600 * 24 * 365;

			t += numSeconds;
		}

		static TimeT numberOfDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static TimeT numberOfDaysInMonthLeap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		//Get the Month Number
		while ( true ) {
			unsigned long long numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * numberOfDaysInMonthLeap[this -> month];
			else
				numSeconds = 3600 * 24 * numberOfDaysInMonth[this -> month];

			t += numSeconds;
		}


		t += ( this -> dayInMonth - 1 ) * ( 3600 * 24 );
		t += ( this -> hours ) * ( 3600 );
		t += ( this -> minutes ) * ( 60 );
		t += ( this -> seconds );

		return t;
	}

	const unsigned char Date::getWeekDay( unsigned char day, unsigned char month, int year ) {
		static int centuryTable[4] = { 0, 5, 3, 1 };

		bool isLeapYear = isYearLeapYear( year );

		int monthValue;
		if ( isLeapYear )
			monthValue = MonthTableLeapYear[month];
		else
			monthValue = MonthTable[month];

		int century = year / 100;

		int centuryNumber = centuryTable[century % 4];

		int yearLast2Digit = year % 100;
		return ( day + monthValue + yearLast2Digit + yearLast2Digit / 4 + centuryNumber ) % 7 - 2;
	}


	const bool Date::isYearLeapYear( int year ) {
		//https://en.wikipedia.org/wiki/Leap_year
		if ( year % 4 != 0 ) return false;
		else if ( year % 100 != 0 ) return true;
		else if ( year % 400 != 0 ) return false;
		else return true;
	}

	const unsigned int Date::getNumDays( int year ) {
		if ( isYearLeapYear( year ) )
			return 365;
		else
			return 366;
	}


	const unsigned long long Date::getLocalUTCBias() {
		return localUTCBias;
	}

	const unsigned long long Date::_retrieveLocalUTCBias() {
		#ifdef WIN32
		TIME_ZONE_INFORMATION tzi;

		DWORD r = GetTimeZoneInformation( &tzi );
		return tzi.Bias * 60;


		#else
		return localtime;		//Should be present in ctime

		#endif
	}


	Date::~Date() {
	}



	Date getDate() {
		Date newDate;
		newDate.setNow();
		return newDate;
	}

}

