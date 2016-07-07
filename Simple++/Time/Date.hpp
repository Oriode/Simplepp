#pragma once



namespace Time {

	template<typename T>
	const BasicString<T> & Date::getWeekDayStr( unsigned char weekDay ) {
		static const BasicString<T> weekDayShortStr[7] = { "Mon", "Tue", "Wed", "Thu", "Fry", "Sat", "Sun" };
		return weekDayShortStr[weekDay];
	}


	template<typename T>
	const BasicString<T> & Date::getMonthStr( unsigned char month ) {
		static const BasicString<T> monthShortStr[12] = { "Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return monthShortStr[month];
	}




	template<typename T>
	BasicString<T> Date::toString() const {
		BasicString<T> newString;
		newString.reserve( 100 );


		newString << getWeekDayStr( Date::getWeekDay( *this ) ) << ' ' << getMonthStr( getMonth() ) << ' ' << getDay() << ' ';


		if ( getHours() < 10 )
			newString << T( '0' ) << T( '0' + getHours() );
		else
			newString << getHours();

		newString << T( ':' );

		if ( getMinutes() < 10 )
			newString << T( '0' ) << T( '0' + getMinutes() );
		else
			newString << getMinutes();

		newString << T( ':' );

		if ( getSeconds() < 10 )
			newString << T( '0' ) << T( '0' + getSeconds() );
		else
			newString << getSeconds();

		return newString;
	}


	template<typename T>
	BasicString<T> Date::toString( const BasicString<T> & str ) const {

		BasicString<T> newString;
		newString.reserve( 100 );

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
			newString << getMonthStr( getMonth() );
			break;
			case 'm':
			if ( getMonth() < 10 ) newString << T( '0' ) << T( '0' + getMonth() );
			else newString << getMonth();
			break;
			//DAY OF THE YEAR
			case 'd':
			if ( getDay() < 10 ) newString << T( '0' ) << T( '0' + getDay() );
			else newString << getDay();
			break;
			case 'e':
			newString << getDay();
			break;
			//DAY OF THE WEEK
			case 'a':
			newString << getWeekDayStr( Date::getWeekDay( *this ) );
			break;
			case 'u':
			newString << Date::getWeekDay( *this );
			break;
			//HOURS
			case 'H':
			if ( getHours() < 10 ) newString << T( '0' ) << T( '0' + getHours() );
			else newString << getHours();
			break;
			case 'M':
			if ( getMinutes() < 10 ) newString << T( '0' ) << T( '0' + getMinutes() );
			else newString << getMinutes();
			break;
			case 'S':
			if ( getSeconds() < 10 ) newString << T( '0' ) << T( '0' + getSeconds() );
			else newString << getSeconds();
			break;
			default:
			newString << *it;
			}
		}

		return newString;
	}


}
