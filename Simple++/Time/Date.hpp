#pragma once



namespace Time {

	template<typename T>
	const unsigned char DateT<T>::MonthTable[ 12 ] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
	template<typename T>
	const unsigned char DateT<T>::MonthTableLeapYear[ 12 ] = { 6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
	template<typename T>
	const long DateT<T>::localUTCBias = DateT<T>::_retrieveLocalUTCBias();


	/************************************************************************/
	/* CONSTRUCTOR	                                                      */
	/************************************************************************/
	template<typename T>
	DateT<T>::DateT() {

	}
	template<typename T>
	DateT<T>::DateT( const DateT & date ) {
		*this = date;
	}
	template<typename T>
	DateT<T>::DateT( const tm & date ) {
		*this = date;
	}
	template<typename T>
	DateT<T>::DateT( const TimePoint & timePoint ) {
		*this = timePoint;
	}





	/************************************************************************/
	/* OPERATOR =	                                                      */
	/************************************************************************/
	template<typename T>
	DateT<T> & DateT<T>::operator=( const DateT<T> & date ) {

		this -> year = date.year;
		this -> month = date.month;
		this -> dayInMonth = date.dayInMonth;
		this -> hours = date.hours;
		this -> minutes = date.minutes;
		this -> seconds = date.seconds;


		return *this;
	}
	template<typename T>
	DateT<T> & DateT<T>::operator=( const tm & date ) {

		this -> year = date.tm_year + 1900;
		this -> month = date.tm_mon;
		this -> dayInMonth = date.tm_mday;
		this -> hours = date.tm_hour;
		this -> minutes = date.tm_min;
		this -> seconds = date.tm_sec;



		return *this;
	}


	template<typename T>
	DateT<T> & DateT<T>::operator=( const TimePoint & timePoint ) {
		this -> year = 1970;
		this -> month = 0;

		TimeT unixTime = timePoint.getTime() + getLocalUTCBias();
		bool isLeapYear = true;

		//Get the Year Number
		while ( true ) {
			bool isLeapYear = isYearLeapYear( this -> year );
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
			} else {
				break;
			}
		}

		static TimeT numberOfDaysInMonth[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static TimeT numberOfDaysInMonthLeap[ 12 ] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		//Get the Month Number
		while ( true ) {
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * numberOfDaysInMonthLeap[ this -> month ];
			else
				numSeconds = 3600 * 24 * numberOfDaysInMonth[ this -> month ];


			if ( unixTime > numSeconds ) {
				unixTime -= numSeconds;
				this -> month++;
				if ( unixTime < numSeconds )
					break;
			} else {
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

	template<typename T>
	void DateT<T>::setNow() {
		operator=( TimePoint::getNow() );
	}



	template<typename T>
	unsigned char DateT<T>::getSeconds() const {
		return this -> seconds;
	}
	template<typename T>
	unsigned char DateT<T>::getMinutes() const {
		return this -> minutes;
	}
	template<typename T>
	unsigned char DateT<T>::getHours() const {
		return this -> hours;
	}
	template<typename T>
	unsigned char DateT<T>::getDay() const {
		return this -> dayInMonth;
	}
	template<typename T>
	unsigned char DateT<T>::getMonth() const {
		return this -> month;
	}
	template<typename T>
	int DateT<T>::getYear() const {
		return this -> year;
	}
	template<typename T>
	unsigned char DateT<T>::getWeekDay( const DateT & date ) {
		return getWeekDay( date.getDay(), date.getMonth(), date.getYear() );
	}
	template<typename T>
	void DateT<T>::setSeconds( unsigned char s ) {
		this -> seconds = s;
	}
	template<typename T>
	void DateT<T>::setMinutes( unsigned char m ) {
		this -> minutes = m;
	}
	template<typename T>
	void DateT<T>::setHours( unsigned char h ) {
		this -> hours = h;
	}
	template<typename T>
	void DateT<T>::setDay( unsigned char d ) {
		this -> dayInMonth = d;
	}
	template<typename T>
	void DateT<T>::setMonth( unsigned char m ) {
		this -> month = m;
	}
	template<typename T>
	void DateT<T>::setYear( int y ) {
		this -> year = y;
	}


	/*
	template<typename T>
	const StringASCII & DateT<T>::getWeekDayStr(unsigned char weekDay) {
		return weekDayShortStr[weekDay];
	}
	template<typename T>
	const StringASCII & DateT<T>::getMonthStr(unsigned char month) {
		return monthShortStr[month];
	}
	template<typename T>
	const WString & DateT<T>::getWeekDayWStr(unsigned char weekDay) {
		return weekDayShortWStr[weekDay];
	}
	template<typename T>
	const WString & DateT<T>::getMonthWStr(unsigned char month) {
		return monthShortWStr[month];
	}*/




	/*
		template<typename T>
		StringASCII DateT<T>::toString() const {
			StringASCII newString;
			newString.reserve(100);


			newString << getWeekDayStr(DateT<T>::getWeekDay(*this)) << ' ' << getMonthStr(getMonth()) << ' ' << getDay() << ' ';


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

		template<typename T>
		StringASCII DateT<T>::toString(const StringASCII & str) const {

			StringASCII newString;
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
					newString << getWeekDayStr(DateT<T>::getWeekDay(*this));
					break;
				case 'u':
					newString << DateT<T>::getWeekDay(*this);
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



template<typename T>
	TimePoint DateT<T>::toTimePoint() const {

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

		static TimeT numberOfDaysInMonth[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static TimeT numberOfDaysInMonthLeap[ 12 ] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		//Get the Month Number
		while ( true ) {
			unsigned long long numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * numberOfDaysInMonthLeap[ this -> month ];
			else
				numSeconds = 3600 * 24 * numberOfDaysInMonth[ this -> month ];

			t += numSeconds;
		}


		t += ( this -> dayInMonth - 1 ) * ( 3600 * 24 );
		t += ( this -> hours ) * ( 3600 );
		t += ( this -> minutes ) * ( 60 );
		t += ( this -> seconds );

		t -= getLocalUTCBias();

		return t;
	}
	template<typename T>
	const unsigned char DateT<T>::getWeekDay( unsigned char day, unsigned char month, int year ) {
		static int centuryTable[ 4 ] = { 0, 5, 3, 1 };

		bool isLeapYear = isYearLeapYear( year );

		int monthValue;
		if ( isLeapYear )
			monthValue = MonthTableLeapYear[ month ];
		else
			monthValue = MonthTable[ month ];

		int century = year / 100;

		int centuryNumber = centuryTable[ century % 4 ];

		int yearLast2Digit = year % 100;
		return ( day + monthValue + yearLast2Digit + yearLast2Digit / 4 + centuryNumber ) % 7 - 2;
	}

	template<typename T>
	const bool DateT<T>::isYearLeapYear( int year ) {
		//https://en.wikipedia.org/wiki/Leap_year
		if ( year % 4 != 0 ) return false;
		else if ( year % 100 != 0 ) return true;
		else if ( year % 400 != 0 ) return false;
		else return true;
	}
	template<typename T>
	const unsigned int DateT<T>::getNumDays( int year ) {
		if ( isYearLeapYear( year ) )
			return 365;
		else
			return 366;
	}

	template<typename T>
	const long long DateT<T>::getLocalUTCBias() {
		return DateT<T>::localUTCBias;
	}
	template<typename T>
	const long DateT<T>::_retrieveLocalUTCBias() {
		std::time_t timeTNow( std::time(NULL) );
		std::tm tmLocal;
		std::tm tmUtc;
		localtime_s( &tmLocal, &timeTNow );
		gmtime_s( &tmUtc, &timeTNow );

		long utcBias = 0;
		utcBias = tmLocal.tm_sec - tmUtc.tm_sec;
		utcBias += ( tmLocal.tm_min - tmUtc.tm_min ) * 60;
		utcBias += ( tmLocal.tm_hour - tmUtc.tm_hour ) * 3600;
		utcBias += ( tmLocal.tm_yday - tmUtc.tm_yday ) * 3600 * 24;
		for ( int year = tmLocal.tm_year; year < tmUtc.tm_year; year++ ) {
			utcBias += ( tmUtc.tm_year - tmLocal.tm_year ) * 3600 * 24 * DateT<T>::getNumDays(year);
		}
		for ( int year = tmUtc.tm_year; year < tmLocal.tm_year; year++ ) {
			utcBias += ( tmLocal.tm_year - tmUtc.tm_year ) * 3600 * 24 * DateT<T>::getNumDays( year );
		}
		return utcBias;
		/*
	#if defined WIN32
	#if defined ENABLE_WIN32
		DYNAMIC_TIME_ZONE_INFORMATION dtzi;

		DWORD r = GetDynamicTimeZoneInformation( &dtzi );
		return dtzi.Bias * 60l;
	#else
		return 0;
	#endif
	#else
		return localtime;		//Should be present in ctime
	#endif
	*/
	}

	template<typename T>
	DateT<T>::~DateT() {}


	template<typename T>
	DateT<T> getDate() {
		DateT<T> newDate;
		newDate.setNow();
		return newDate;
	}


	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<typename T>
	DateT<T> & DateT<T>::operator+=( TimeT timeT ) {
		bool isLeapYear;

		//Get the Year Number
		while ( true ) {
			isLeapYear = isYearLeapYear( this -> year );
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * 366;
			else
				numSeconds = 3600 * 24 * 365;

			if ( timeT > numSeconds ) {
				timeT -= numSeconds;
				this -> year++;
			} else {
				break;
			}
		}

		static unsigned char numberOfDaysInMonth[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static unsigned char numberOfDaysInMonthLeap[ 12 ] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };




		//Get the Month Number
		TimeT numSecondsOfMonth;
		unsigned char numberOfDaysInThisMonth;
		while ( true ) {
			if ( isLeapYear )
				numberOfDaysInThisMonth = numberOfDaysInMonthLeap[ this -> month ];
			else
				numberOfDaysInThisMonth = numberOfDaysInMonth[ this -> month ];

			numSecondsOfMonth = 3600 * 24 * numberOfDaysInThisMonth;
			if ( timeT > numSecondsOfMonth ) {
				timeT -= numSecondsOfMonth;
				if ( this -> month >= 11 ) {
					this -> month = 0;
					this -> year++;
					isLeapYear = isYearLeapYear( this -> year );
				} else {
					this -> month++;
				}
			} else {
				break;
			}
		}

		unsigned char addedDays = ( unsigned char ) ( timeT / ( 3600 * 24 ) );
		timeT %= ( 3600 * 24 );
		unsigned char addedHours = ( unsigned char ) ( timeT / 3600 );
		timeT %= ( 3600 );
		unsigned char addedMinutes = ( unsigned char ) ( timeT / 60 );
		timeT %= ( 60 );
		unsigned char addedSeconds = ( unsigned char ) ( timeT );


		this -> seconds += addedSeconds;
		if ( this -> seconds >= 60 ) {
			this -> seconds -= 60;
			this -> minutes++;
		}

		this -> minutes += addedMinutes;
		while ( this -> minutes >= 60 ) {
			this -> minutes -= 60;
			this -> hours++;
		}


		this -> hours += addedHours;
		while ( this -> hours >= 24 ) {
			this -> hours -= 24;
			this -> dayInMonth++;
		}

		this -> dayInMonth += addedDays;
		while ( this -> dayInMonth > numberOfDaysInThisMonth ) {
			this -> dayInMonth -= numberOfDaysInThisMonth;
			this -> month++;

			if ( this -> month >= 12 ) {
				this -> month -= 12;
				this -> year++;
				isLeapYear = isYearLeapYear( this -> year );
			}
			if ( isLeapYear )
				numberOfDaysInThisMonth = numberOfDaysInMonthLeap[ this -> month ];
			else
				numberOfDaysInThisMonth = numberOfDaysInMonth[ this -> month ];
		}
		this -> dayInMonth++;
		return *this;
	}


	template<typename T>
	DateT<T> & DateT<T>::operator-=( TimeT timeT ) {
		bool isLeapYear;

		//Get the Year Number
		while ( true ) {
			isLeapYear = isYearLeapYear( this -> year );
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * 366;
			else
				numSeconds = 3600 * 24 * 365;

			if ( timeT > numSeconds ) {
				timeT -= numSeconds;
				this -> year--;
			} else {
				break;
			}
		}

		static unsigned char numberOfDaysInMonth[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static unsigned char numberOfDaysInMonthLeap[ 12 ] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };




		//Get the Month Number
		TimeT numSecondsOfMonth;
		unsigned char numberOfDaysInThisMonth;
		while ( true ) {
			if ( isLeapYear )
				numberOfDaysInThisMonth = numberOfDaysInMonthLeap[ this -> month ];
			else
				numberOfDaysInThisMonth = numberOfDaysInMonth[ this -> month ];

			numSecondsOfMonth = 3600 * 24 * numberOfDaysInThisMonth;
			if ( timeT > numSecondsOfMonth ) {
				timeT -= numSecondsOfMonth;
				if ( this -> month == 0 ) {
					this -> month = 11;
					this -> year--;
					isLeapYear = isYearLeapYear( this -> year );
				} else {
					this -> month--;
				}
			} else {
				break;
			}
		}

		unsigned char subbedDays = ( unsigned char ) ( timeT / ( 3600 * 24 ) );
		timeT %= ( 3600 * 24 );
		unsigned char subbedHours = ( unsigned char ) ( timeT / 3600 );
		timeT %= ( 3600 );
		unsigned char subbedMinutes = ( unsigned char ) ( timeT / 60 );
		timeT %= ( 60 );
		unsigned char subbedSeconds = ( unsigned char ) ( timeT );




		this -> seconds -= subbedSeconds;
		if ( this -> seconds > 60 ) {
			this -> seconds += 60;
			this -> minutes--;
		}

		this -> minutes -= subbedMinutes;
		while ( this -> minutes > 60 ) {
			this -> minutes += 60;
			this -> hours--;
		}


		this -> hours -= subbedHours;
		while ( this -> hours > 24 ) {
			this -> hours += 24;
			this -> dayInMonth--;
		}

		this -> dayInMonth -= subbedDays;
		while ( this -> dayInMonth > numberOfDaysInThisMonth ) {
			this -> dayInMonth += numberOfDaysInThisMonth;
			this -> month--;

			if ( this -> month > 12 ) {
				this -> month += 12;
				this -> year--;
				isLeapYear = isYearLeapYear( this -> year );
			}
			if ( isLeapYear )
				numberOfDaysInThisMonth = numberOfDaysInMonthLeap[ this -> month ];
			else
				numberOfDaysInThisMonth = numberOfDaysInMonth[ this -> month ];
		}
		this -> dayInMonth++;
		return *this;
	}

	template<typename T>
	Duration<Second> operator-( const DateT<T> & d1, const DateT<T> & d2 ) {
		bool isLeapYear;


		TimeT timeT = 0;
		auto tmpYear = d1.getYear();
		auto tmpMonth = d1.getMonth();

		//Get the Year Number
		while ( true ) {
			isLeapYear = DateT<T>::isYearLeapYear( tmpYear );
			TimeT numSeconds;
			if ( isLeapYear )
				numSeconds = 3600 * 24 * 366;
			else
				numSeconds = 3600 * 24 * 365;

			if ( tmpYear > d2.getYear() ) {
				timeT += numSeconds;
				tmpYear--;
			} else {
				break;
			}
		}

		static unsigned char numberOfDaysInMonth[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		static unsigned char numberOfDaysInMonthLeap[ 12 ] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		//Get the Month Number
		TimeT numSecondsOfMonth;
		unsigned char numberOfDaysInThisMonth;
		while ( true ) {
			if ( isLeapYear )
				numberOfDaysInThisMonth = numberOfDaysInMonthLeap[ tmpMonth ];
			else
				numberOfDaysInThisMonth = numberOfDaysInMonth[ tmpMonth ];

			numSecondsOfMonth = 3600 * 24 * numberOfDaysInThisMonth;
			if ( tmpMonth > d2.getMonth() ) {
				timeT += numSecondsOfMonth;
				tmpMonth--;
			} else if ( tmpMonth < d2.getMonth() ) {
				timeT -= numSecondsOfMonth;
				tmpMonth++;
			} else {
				break;
			}
		}


		timeT += ( d1.getDay() - d2.getDay() ) * 3600 * 24;
		timeT += ( d1.getHours() - d2.getHours() ) * 3600;
		timeT += ( d1.getMinutes() - d2.getMinutes() ) * 60;
		timeT += ( d1.getSeconds() - d2.getSeconds() );


		return timeT;
	}


	/************************************************************************/
	/* OPERATOR LOGICAL                                                     */
	/************************************************************************/
	template<typename T>
	bool DateT<T>::operator==( const DateT & d ) {
		return ( this -> getYear() == d.getYear() &&
			this -> getMonth() == d.getMonth() &&
			this -> getDay() == d.getDay() &&
			this -> getHours() == d.getHours() &&
			this -> getMinutes() == d.getMinutes() &&
			this -> getSeconds() == d.getSeconds() );
	}

	template<typename T>
	bool DateT<T>::operator!=( const DateT & d ) {
		return ( this -> getYear() != d.getYear() ||
			this -> getMonth() != d.getMonth() ||
			this -> getDay() != d.getDay() ||
			this -> getHours() != d.getHours() ||
			this -> getMinutes() != d.getMinutes() ||
			this -> getSeconds() != d.getSeconds() );
	}

	template<typename T>
	bool DateT<T>::operator<( const DateT & d ) {
		return ( this -> getYear() < d.getYear() &&
			this -> getMonth() < d.getMonth() &&
			this -> getDay() < d.getDay() &&
			this -> getHours() < d.getHours() &&
			this -> getMinutes() < d.getMinutes() &&
			this -> getSeconds() < d.getSeconds() );
	}

	template<typename T>
	bool DateT<T>::operator>( const DateT & d ) {
		return ( this -> getYear() > d.getYear() &&
			this -> getMonth() > d.getMonth() &&
			this -> getDay() > d.getDay() &&
			this -> getHours() > d.getHours() &&
			this -> getMinutes() > d.getMinutes() &&
			this -> getSeconds() > d.getSeconds() );
	}

	template<typename T>
	bool DateT<T>::operator>=( const DateT & d ) {
		return ( this -> getYear() >= d.getYear() &&
			this -> getMonth() >= d.getMonth() &&
			this -> getDay() >= d.getDay() &&
			this -> getHours() >= d.getHours() &&
			this -> getMinutes() >= d.getMinutes() &&
			this -> getSeconds() >= d.getSeconds() );
	}

	template<typename T>
	bool DateT<T>::operator<=( const DateT & d ) {
		return ( this -> getYear() <= d.getYear() &&
			this -> getMonth() <= d.getMonth() &&
			this -> getDay() <= d.getDay() &&
			this -> getHours() <= d.getHours() &&
			this -> getMinutes() <= d.getMinutes() &&
			this -> getSeconds() <= d.getSeconds() );
	}

	template<typename T>
	template<typename C>
	const BasicString<C> & DateT<T>::getWeekDayStr( unsigned char weekDay ) {
		static const BasicString<C> weekDayShortStr[7] = { "Mon", "Tue", "Wed", "Thu", "Fry", "Sat", "Sun" };
		return weekDayShortStr[weekDay];
	}


	template<typename T>
	template<typename C>
	const BasicString<C> & DateT<T>::getMonthStr( unsigned char month ) {
		static const BasicString<C> monthShortStr[12] = { "Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return monthShortStr[month];
	}



	template<typename T>
	template<typename C>
	BasicString<C> DateT<T>::toString() const {
		BasicString<C> newString;
		newString.reserve( 100 );


		newString << getWeekDayStr( DateT<T>::getWeekDay( *this ) ) << ' ' << getMonthStr( getMonth() ) << ' ' << getDay() << ' ';


		if ( getHours() < 10 )
			newString << C( '0' ) << C( '0' + getHours() );
		else
			newString << getHours();

		newString << C( ':' );

		if ( getMinutes() < 10 )
			newString << C( '0' ) << C( '0' + getMinutes() );
		else
			newString << getMinutes();

		newString << C( ':' );

		if ( getSeconds() < 10 )
			newString << C( '0' ) << C( '0' + getSeconds() );
		else
			newString << getSeconds();

		return newString;
	}

	template<typename T>
	template<typename C>
	BasicString<C> DateT<T>::toString( const BasicString<C> & str ) const {

		BasicString<C> newString;
		newString.reserve( 100 );

		for ( auto it = str.getBegin(); it != str.getEnd(); it++ ) {
			switch ( *it ) {
			case C('\\'):
			it++;
			break;
			//YEAR
			case C('Y'):
			newString << getYear();
			break;
			case C('y'):
			newString << getYear() % 100;
			break;
			//MONTH
			case C('b'):
			newString << getMonthStr( getMonth() );
			break;
			case C('m'):
			if ( getMonth() < 9 ) newString << C( '0' ) << C( '0' + (getMonth() + 1) );
			else newString << (getMonth() + 1);
			break;
			//DAY OF THE MONTH
			case C('d'):
			if ( getDay() < 10 ) newString << C( '0' ) << C( '0' + getDay() );
			else newString << getDay();
			break;
			case C('e'):
			newString << getDay();
			break;
			//DAY OF THE WEEK
			case C('a'):
			newString << getWeekDayStr( DateT<T>::getWeekDay( *this ) );
			break;
			case C('u'):
			newString << (DateT<T>::getWeekDay( *this ) + 1);
			break;
			//HOURS
			case C('H'):
			if ( getHours() < 10 ) newString << C( '0' ) << C( '0' + getHours() );
			else newString << getHours();
			break;
			case C('M'):
			if ( getMinutes() < 10 ) newString << C( '0' ) << C( '0' + getMinutes() );
			else newString << getMinutes();
			break;
			case C('S'):
			if ( getSeconds() < 10 ) newString << C( '0' ) << C( '0' + getSeconds() );
			else newString << getSeconds();
			break;
			default:
			newString << *it;
			}
		}

		return newString;
	}

	template<typename T>
	template<typename C>
	BasicString<C> DateT<T>::toStringISO() const {
		BasicString<C> newString;
		newString.reserve( 100 );

		newString << getYear() << C( '-' ) << getMonth() << C( '-' ) << getDay();
		return newString;
	}


	template<typename ratio, typename T>
	DateT<T> operator+( const DateT<T> & date, const Duration<ratio> & duration ) {
		DateT d( date );
		d += duration;
		return d;
	}

	template<typename ratio, typename T>
	DateT<T> operator+( const Duration<ratio> & duration, const DateT<T> & date ) {
		DateT d( date );
		d += duration;
		return d;
	}

	template<typename ratio, typename T>
	DateT<T> operator-( const DateT<T> & date, const Duration<ratio> & duration ) {
		DateT d( date );
		d -= duration;
		return d;
	}

	template<typename T>
	template<typename ratio>
	DateT<T> & DateT<T>::operator+=( const Duration<ratio> & duration ) {
		return operator+=( Duration<Second>( duration ).getValue() );
	}
	template<typename T>
	template<typename ratio>
	DateT<T> & DateT<T>::operator-=( const Duration<ratio> & duration ) {
		return operator-=( Duration<Second>( duration ).getValue() );
	}

}
