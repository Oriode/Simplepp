/**
 * @file	Time\Duration.h.
 *
 * @brief		Declares the duration class
 * @author	Clément Gerber
 * @date		11/07/2016 (DMY)
 */
#pragma once

#include "../Math/BasicMath.h"
#include "Tick.h"

namespace Time {
	/** @brief	typename for not using this ugly underscore name */
	typedef time_t TimeT;

	/**
	 * @brief				Class representing a time duration,
	 *
	 * @tparam	ratio	fractional number representing the number of seconds of one unit in this object.
	 */
	template<class ratio = Math::Ratio<1, 1>>
	class Duration {
	public:

		/************************************************************************/
		/* CONSTRUCTORS                                                         */
		/************************************************************************/

		/** @brief	Default constructor */
		Duration();

		/**
		 * @brief	Constructor
		 *
		 * @tparam	ratio2	Type of the ratio 2.
		 * @param	d	A Duration<ratio2> to process.
		 */
		template<class ratio2>
		Duration( const Duration<ratio2> & d );
		/**
		 * @brief	Constructor
		 *
		 * @param	d	A TimeT to process.
		 */
		Duration( TimeT d );

		/**
		 * @brief	Constructor
		 *
		 * @param	ticks	The ticks.
		 */
		Duration( const Tick & ticks );


		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/

		/**
		 * @brief	Equality operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */
		template<class ratio2>
		bool operator==( const Duration<ratio2> & d ) const;
		/**
		 * @brief		Inequality operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	True if the parameters are not considered equivalent.
		 */
		template<class ratio2>
		bool operator!=( const Duration<ratio2> & d ) const;
		/**
		 * @brief		Greater-than-or-equal comparison operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		template<class ratio2>
		bool operator>=( const Duration<ratio2> & d ) const;


		template<class ratio2>
		bool operator<=( const Duration<ratio2> & d ) const;
		/**
		 * @brief		Less-than comparison operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	True if the first parameter is less than the second.
		 */
		template<class ratio2>
		bool operator<( const Duration<ratio2> & d ) const;
		/**
		 * @brief	Greater-than comparison operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	True if the first parameter is greater than to the second.
		 */
		template<class ratio2>
		bool operator>( const Duration<ratio2> & d ) const;


		/**
		 * @brief	Equality operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */
		bool operator==( TimeT d ) const;
		/**
		 * @brief	Inequality operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	True if the parameters are not considered equivalent.
		 */
		bool operator!=( TimeT d ) const;
		/**
		 * @brief	Greater-than-or-equal comparison operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		bool operator>=( TimeT d ) const;
		bool operator<=( TimeT d ) const;
		/**
		 * @brief	Less-than comparison operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	True if the first parameter is less than the second.
		 */
		bool operator<( TimeT d ) const;
		/**
		 * @brief	Greater-than comparison operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	True if the first parameter is greater than to the second.
		 */
		bool operator>( TimeT d ) const;


		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/

		/**
		 * @brief	Assignment operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	A shallow copy of this object.
		 */
		template<class ratio2>
		Duration<ratio> & operator=( const Duration<ratio2> & d );
		/**
		 * @brief	Addition assignment operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<class ratio2>
		Duration<ratio> & operator+=( const Duration<ratio2> & d );
		/**
		 * @brief	Subtraction assignment operator
		 *
		 * @param	d	A Duration<ratio2> to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<class ratio2>
		Duration<ratio> & operator-=( const Duration<ratio2> & d );


		/**
		 * @brief	Assignment operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	A shallow copy of this object.
		 */
		Duration<ratio> & operator=( TimeT d );
		/**
		 * @brief	Addition assignment operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	The result of the operation.
		 */
		Duration<ratio> & operator+=( TimeT d );
		/**
		 * @brief	Subtraction assignment operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	The result of the operation.
		 */
		Duration<ratio> & operator-=( TimeT d );


		/**
		 * @brief	Multiplication assignment operator
		 *
		 * @param	d	A T to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<typename T>
		Duration<ratio> & operator*=( const T & d );
		/**
		 * @brief	Division assignment operator
		 *
		 * @param	d	A T to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<typename T>
		Duration<ratio> & operator/=( const T & d );

		/**
		 * @brief	get the number of milliseconds of this duration
		 *
		 * @returns	duration in milliseconds.
		 */
		unsigned long long getMilliSeconds() const;

		/**
		 * @brief	get the number of seconds of this duration
		 *
		 * @returns	seconds.
		 */
		unsigned long long getSeconds() const;

		/**
		 * @brief	get the number of Minutes of this duration
		 *
		 * @returns	minutes.
		 */
		unsigned long long getMinutes() const;

		/**
		 * @brief	get the number of Hours of this duration
		 *
		 * @returns	hours.
		 */
		unsigned long long getHours() const;


		/**
		 * @brief	get the number of Days of this duration
		 *
		 * @returns	duration in days.
		 */
		unsigned long long getDays() const;




		/**
		 * @brief	Get the value of this duration without any conversion
		 *
		 * @returns	number of unit of time of this duration.
		 */
		TimeT getValue() const;


	private:
		/** @brief	A TimeT to process */
		TimeT d;

	};










	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/

	template<class ratio, class ratio2>
	Duration<ratio> operator+( const Duration<ratio> & d1, const Duration<ratio2> & d2 );

	template<class ratio, typename T>
	Duration<ratio> operator+( const Duration<ratio> & d, const T & v );

	template<class ratio, typename T>
	Duration<ratio> operator+( const T & t, const Duration<ratio> & d );

	template<class ratio, class ratio2>
	Duration<ratio> operator-( const Duration<ratio> & d1, const Duration<ratio2> & d2 );

	template<class ratio, typename T>
	Duration<ratio> operator-( const Duration<ratio> & d, const T & v );

	template<class ratio, typename T>
	Duration<ratio> operator-( const T & v, const Duration<ratio> & d );

	template<class ratio, typename T>
	Duration<ratio> operator*( const Duration<ratio> & d1, const T & v );

	template<typename T, class ratio>
	Duration<ratio> operator*( const T & v, const Duration<ratio> & d1 );

	template<class ratio, typename T>
	Duration<ratio> operator/( const Duration<ratio> & d, const T & v );

	template<class ratio, typename T>
	Duration<ratio> operator/( const T & v, const Duration<ratio> & d );




	/** @brief	Defines an alias representing the day */
	typedef Math::Ratio<3600 * 24, 1> Day;
	/** @brief	Defines an alias representing the hour */
	typedef Math::Ratio<3600, 1> Hour;
	/** @brief	Defines an alias representing the minute */
	typedef Math::Ratio<60, 1> Minute;
	/** @brief	Defines an alias representing the second */
	typedef Math::Ratio<1, 1> Second;
	/** @brief	Defines an alias representing the centi second */
	typedef Math::Ratio<1, 100> CentiSecond;
	/** @brief	Defines an alias representing the milli second */
	typedef Math::Ratio<1, 1000> MilliSecond;
	/** @brief	Defines an alias representing the nano second */
	typedef Math::Ratio<1, 1000000> NanoSecond;
	/** @brief	Defines an alias representing the pico second */
	typedef Math::Ratio<1, 1000000000> PicoSecond;
}



#include "Duration.hpp"
