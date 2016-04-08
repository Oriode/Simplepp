#pragma once




#include "IO.h"
#include "Math.h"
#include "Tick.h"

namespace Time  {
	typedef time_t TimeT;
	
	template<class ratio = Math::Ratio<1, 1>> 
	class Duration {
	public:
		Duration();

		template<class ratio2>
		Duration(const Duration<ratio2> & d);
		Duration(TimeT d);

		Duration(const Tick & ticks);


		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/
		template<class ratio2>
		bool operator==(const Duration<ratio2> & d) const;
		template<class ratio2>
		bool operator!=(const Duration<ratio2> & d) const;
		template<class ratio2>
		bool operator>=(const Duration<ratio2> & d) const;
		template<class ratio2>
		bool operator<=(const Duration<ratio2> & d) const;
		template<class ratio2>
		bool operator<(const Duration<ratio2> & d) const;
		template<class ratio2>
		bool operator>(const Duration<ratio2> & d) const;


		bool operator==(TimeT d) const;
		bool operator!=(TimeT d) const;
		bool operator>=(TimeT d) const;
		bool operator<=(TimeT d) const;
		bool operator<(TimeT d) const;
		bool operator>(TimeT d) const;


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		template<class ratio2>
		Duration<ratio> & operator=(const Duration<ratio2> & d);
		template<class ratio2>
		Duration<ratio> & operator+=(const Duration<ratio2> & d);
		template<class ratio2>
		Duration<ratio> & operator-=(const Duration<ratio2> & d);


		Duration<ratio> & operator=(TimeT d);
		Duration<ratio> & operator+=(TimeT d);
		Duration<ratio> & operator-=(TimeT d);


		template<typename T>
		Duration<ratio> & operator*=(const T & d);
		template<typename T>
		Duration<ratio> & operator/=(const T & d);

		




		TimeT getValue() const;


	private:
		TimeT d;

	};









	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/
	template<class ratio, class ratio2>
	Duration<ratio> operator+(const Duration<ratio> & d1, const Duration<ratio2> & d2);
	template<class ratio>
	Duration<ratio> operator+(const Duration<ratio> & d1, TimeT d2);
	template<class ratio>
	Duration<ratio> operator+(TimeT d1, const Duration<ratio> & d2);

	template<class ratio, class ratio2>
	Duration<ratio> operator-(const Duration<ratio> & d1, const Duration<ratio2> & d2);
	template<class ratio>
	Duration<ratio> operator-(const Duration<ratio> & d1, TimeT d2);
	template<class ratio>
	Duration<ratio> operator-(TimeT d1, const Duration<ratio> & d2);



	template<class ratio, typename T>
	Duration<ratio> operator*(const Duration<ratio> & d1, const T & v);
	template<typename T, class ratio>
	Duration<ratio> operator*(const T & v, const Duration<ratio> & d1);
	template<class ratio, typename T>
	Duration<ratio> operator/(const Duration<ratio> & d1, const T & v);




	typedef Math::Ratio<3600 * 24, 1> Day;
	typedef Math::Ratio<3600, 1> Hour;
	typedef Math::Ratio<60, 1> Minute;
	typedef Math::Ratio<1, 1> Second;
	typedef Math::Ratio<1, 100> CentiSecond;
	typedef Math::Ratio<1, 1000> MilliSecond;
	typedef Math::Ratio<1, 1000000> NanoSecond;
	typedef Math::Ratio<1, 1000000000> PicoSecond;

}



#include "Duration.hpp"