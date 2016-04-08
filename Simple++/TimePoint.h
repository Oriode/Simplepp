#pragma once


#include <ctime>
#include "Duration.h"
#include "IO.h"


namespace Time {


	class TimePoint {
	public:

		TimePoint();
		TimePoint(const TimeT & timeT);

		void setNow();

		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/
		bool operator==(const TimePoint & timePoint) const;
		bool operator!=(const TimePoint & timePoint) const;
		bool operator>=(const TimePoint & timePoint) const;
		bool operator<=(const TimePoint & timePoint) const;
		bool operator<(const TimePoint & timePoint) const;
		bool operator>(const TimePoint & timePoint) const;


		/************************************************************************/
		/* OPERATOR EQUAL	                                                      */
		/************************************************************************/
		TimePoint & operator=(const TimePoint & timePoint);
		TimePoint & operator=(const TimeT & timeT);


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class ratio>
		TimePoint & operator+=(const Duration<ratio> & d);

		template<class ratio>
		TimePoint & operator-=(const Duration<ratio> & d);

		TimePoint & operator+=(TimeT t);
		TimePoint & operator-=(TimeT t);







		~TimePoint();

		void setTime(const TimeT & t);

		const TimeT & getTime() const;

		static TimePoint getNow();
	private:
		TimeT t;

	};


	TimePoint getTime();


	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	TimePoint operator+(const TimePoint & t1, TimeT t2);
	TimePoint operator+(TimeT t1, const TimePoint & t2);

	template<class ratio>
	TimePoint operator+(const TimePoint & t1, const Duration<ratio> & d);

	template<class ratio>
	TimePoint operator+(const Duration<ratio> & d, const TimePoint & t2);


	TimePoint operator-(const TimePoint & t1, TimeT t2);
	TimePoint operator-(TimeT t1, const TimePoint & t2);

	Duration<Second> operator-(const TimePoint & t1, const TimePoint & t2);

	template<class ratio>
	TimePoint operator-(const TimePoint & t1, const Duration<ratio> & d);

}


#include "TimePoint.hpp"



