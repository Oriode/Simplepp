/**
 * @file	Time\Duration.h.
 *
 * @brief		Declares the duration class
 * @author	Clément Gerber
 * @date		11/07/2016 (DMY)
 */
#pragma once

#include "../IO/IO.h"
#include "BasicTime.h"
#include "Tick.h"

namespace Time {

	/**
	 * @brief				Class representing a time duration,
	 *
	 * @tparam	Ratio	fractional number representing the number of seconds of one unit in this object.
	 */
	template<class Ratio = Math::Ratio<1, 1>>
	class Duration : public IO::BasicIO {
	public:

		/************************************************************************/
		/* CONSTRUCTORS                                                         */
		/************************************************************************/

		/** @brief	Default constructor */
		Duration();

		/**
		 * @brief	Constructor
		 *
		 * @tparam	Ratio2	Type of the Ratio 2.
		 * @param	d	A Duration<Ratio2> to process.
		 */
		template<class Ratio2>
		Duration( const Duration<Ratio2> & d );
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
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */
		template<class Ratio2>
		bool operator==( const Duration<Ratio2> & d ) const;
		/**
		 * @brief		Inequality operator
		 *
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	True if the parameters are not considered equivalent.
		 */
		template<class Ratio2>
		bool operator!=( const Duration<Ratio2> & d ) const;
		/**
		 * @brief		Greater-than-or-equal comparison operator
		 *
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		template<class Ratio2>
		bool operator>=( const Duration<Ratio2> & d ) const;


		template<class Ratio2>
		bool operator<=( const Duration<Ratio2> & d ) const;
		/**
		 * @brief		Less-than comparison operator
		 *
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	True if the first parameter is less than the second.
		 */
		template<class Ratio2>
		bool operator<( const Duration<Ratio2> & d ) const;
		/**
		 * @brief	Greater-than comparison operator
		 *
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	True if the first parameter is greater than to the second.
		 */
		template<class Ratio2>
		bool operator>( const Duration<Ratio2> & d ) const;


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
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	A shallow copy of this object.
		 */
		template<class Ratio2>
		Duration<Ratio> & operator=( const Duration<Ratio2> & d );
		/**
		 * @brief	Addition assignment operator
		 *
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<class Ratio2>
		Duration<Ratio> & operator+=( const Duration<Ratio2> & d );
		/**
		 * @brief	Subtraction assignment operator
		 *
		 * @param	d	A Duration<Ratio2> to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<class Ratio2>
		Duration<Ratio> & operator-=( const Duration<Ratio2> & d );


		/**
		 * @brief	Assignment operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	A shallow copy of this object.
		 */
		Duration<Ratio> & operator=( TimeT d );
		/**
		 * @brief	Addition assignment operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	The result of the operation.
		 */
		Duration<Ratio> & operator+=( TimeT d );
		/**
		 * @brief	Subtraction assignment operator
		 *
		 * @param	d	A TimeT to process.
		 *
		 * @returns	The result of the operation.
		 */
		Duration<Ratio> & operator-=( TimeT d );


		/**
		 * @brief	Multiplication assignment operator
		 *
		 * @param	d	A T to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<typename T>
		Duration<Ratio> & operator*=( const T & d );
		/**
		 * @brief	Division assignment operator
		 *
		 * @param	d	A T to process.
		 *
		 * @returns	The result of the operation.
		 */
		template<typename T>
		Duration<Ratio> & operator/=( const T & d );

		/**
		 * @brief	get the number of milliseconds of this duration
		 *
		 * @returns	duration in milliseconds.
		 */
		unsigned long long int getMilliSeconds() const;

		/**
		 * @brief	get the number of seconds of this duration
		 *
		 * @returns	seconds.
		 */
		unsigned long long int getSeconds() const;

		/**
		 * @brief	get the number of Minutes of this duration
		 *
		 * @returns	minutes.
		 */
		unsigned long long int getMinutes() const;

		/**
		 * @brief	get the number of Hours of this duration
		 *
		 * @returns	hours.
		 */
		unsigned long long int getHours() const;


		/**
		 * @brief	get the number of Days of this duration
		 *
		 * @returns	duration in days.
		 */
		unsigned long long int getDays() const;




		/**
		 * @brief	Get the value of this duration without any conversion
		 *
		 * @returns	number of unit of time of this duration.
		 */
		const TimeT & getValue() const;

		///@brief Get the value by converting it to the specified Ratio.
		///@template Ratio2 Ratio to be used for the conversion.
		///@return value converted from Ratio to Ratio2.
		template<typename Ratio2>
		TimeT toValue() const;

		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( IO::SimpleFileStream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( IO::SimpleFileStream * fileStream ) const;

	private:
		/** @brief	A TimeT to process */
		TimeT d;

	};










	/************************************************************************/
	/* OPERATOR ARITHMETIC                                                  */
	/************************************************************************/

	template<class Ratio, class Ratio2>
	Duration<Ratio> operator+( const Duration<Ratio> & d1, const Duration<Ratio2> & d2 );

	template<class Ratio, typename T>
	Duration<Ratio> operator+( const Duration<Ratio> & d, const T & v );

	template<class Ratio, typename T>
	Duration<Ratio> operator+( const T & t, const Duration<Ratio> & d );

	template<class Ratio, class Ratio2>
	Duration<Ratio> operator-( const Duration<Ratio> & d1, const Duration<Ratio2> & d2 );

	template<class Ratio, typename T>
	Duration<Ratio> operator-( const Duration<Ratio> & d, const T & v );

	template<class Ratio, typename T>
	Duration<Ratio> operator-( const T & v, const Duration<Ratio> & d );

	template<class Ratio, typename T>
	Duration<Ratio> operator*( const Duration<Ratio> & d1, const T & v );

	template<typename T, class Ratio>
	Duration<Ratio> operator*( const T & v, const Duration<Ratio> & d1 );

	template<class Ratio>
	Duration<Ratio> operator/( const Duration<Ratio> & d1, const Duration<Ratio> & d2 );

	template<class Ratio, typename T>
	Duration<Ratio> operator/( const Duration<Ratio> & d, const T & v );

	template<class Ratio, typename T>
	Duration<Ratio> operator/( const T & v, const Duration<Ratio> & d );




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
