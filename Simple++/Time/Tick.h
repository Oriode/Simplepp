/**
 * @file		Time\TickT.h.
 *
 * @brief		Declares the tick class
 * @author	Clément Gerber
 * @date		08/07/2016 (DMY)
 */
#pragma once

#include <ctime>

 /** @brief	. */
namespace Time {

	/** @brief	Defines an alias representing the clock t */
	typedef clock_t ClockT;
	/** @brief	The ticks per security */
	constexpr ClockT TicksPerSec = CLOCKS_PER_SEC;


	/** @brief	Representing a CPU tick */
	template<typename T>
	class TickT {
	public:
		/** @brief	Empty constructor, see getClock(); for the actual value */
		/** @brief	Default constructor */
		TickT();


		/**
		 * @brief		Copy constructor
		 *
		 * @param		tick	TickT to be copied.
		 */
		TickT( const TickT & tick );


		/**
		 * @brief		Constructor from a ClockT ( from the std lib )
		 *
		 * @param		tick	TickT to be copied.
		 */
		TickT( ClockT tick );


		/** @brief	Destructor */
		~TickT();

		/** @brief	Sets the now */
		void setNow();


		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/

		/**
		 * @brief		Equality operator
		 *
		 * @param		Other TickT to be compared.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */
		bool operator==( const TickT & tick ) const;

		/**
		 * @brief		Less-than comparison operator
		 *
		 * @param		Other TickT to be compared.
		 *
		 * @returns	True if the first parameter is less than the second.
		 */
		bool operator<( const TickT & tick ) const;

		/**
		 * @brief		Greater-than comparison operator
		 *
		 * @param		Other TickT to be compared.
		 *
		 * @returns	True if the first parameter is greater than to the second.
		 */
		bool operator>( const TickT & tick ) const;

		/**
		 * @brief		Greater-than-or-equal comparison operator
		 *
		 * @param		Other TickT to be compared.
		 *
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		bool operator>=( const TickT & tick ) const;

		/**
		 * @brief		Less-than-or-equal comparison operator
		 *
		 * @param		Other TickT to be compared.
		 *
		 * @returns	True if the first parameter is less than or equal to the second.
		 */
		bool operator<=( const TickT & tick ) const;



		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/

		/**
		 * @brief		Assignment operator
		 *
		 * @param		Other TickT.
		 *
		 * @returns	A shallow copy of this object.
		 */
		TickT & operator=( const TickT & tick );

		/**
		 * @brief		Subtraction assignment operator
		 *
		 * @param		Other TickT.
		 *
		 * @returns	The result of the operation.
		 */
		TickT & operator-=( const TickT & tick );

		/**
		 * @brief		Gets the value
		 *
		 * @returns	The value.
		 */
		const ClockT & getValue() const;


	protected:
		/** @brief	Values that represent Constructors */
		enum ctor {
			null
		};
		/**
		 * @brief				Constructor
		 *
		 * @param	parameter1	The first parameter.
		 */
		TickT( ctor );
	private:
		/** @brief	A ClockT to process */
		ClockT c;
	};

	using Tick = TickT<int>;


	/**
	 * @brief		Subtraction operator
	 *
	 * @param	t1	The first value.
	 * @param	t2	A value to subtract from it.
	 *
	 * @returns	The result of the operation.
	 */
	template<typename T>
	TickT<T> operator-( const TickT<T> & t1, const TickT<T> & t2 );


	/**
	 * @brief		Gets the clock
	 *
	 * @returns	The clock.
	 */
	template<typename T>
	TickT<T> getClock();



}



#include "Tick.hpp"