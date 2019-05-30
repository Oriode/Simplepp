/**
 * @file		Time\Tick.h.
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
	class Tick {
	public:
		/** @brief	Empty constructor, see getClock(); for the actual value */
		/** @brief	Default constructor */
		Tick();


		/**
		 * @brief		Copy constructor
		 *
		 * @param		tick	Tick to be copied.
		 */
		Tick( const Tick & tick );


		/**
		 * @brief		Constructor from a ClockT ( from the std lib )
		 *
		 * @param		tick	Tick to be copied.
		 */
		Tick( ClockT tick );


		/** @brief	Destructor */
		~Tick();

		/** @brief	Sets the now */
		void setNow();


		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/

		/**
		 * @brief		Equality operator
		 *
		 * @param		Other Tick to be compared.
		 *
		 * @returns	True if the parameters are considered equivalent.
		 */
		bool operator==( const Tick & tick ) const;

		/**
		 * @brief		Less-than comparison operator
		 *
		 * @param		Other Tick to be compared.
		 *
		 * @returns	True if the first parameter is less than the second.
		 */
		bool operator<( const Tick & tick ) const;

		/**
		 * @brief		Greater-than comparison operator
		 *
		 * @param		Other Tick to be compared.
		 *
		 * @returns	True if the first parameter is greater than to the second.
		 */
		bool operator>( const Tick & tick ) const;

		/**
		 * @brief		Greater-than-or-equal comparison operator
		 *
		 * @param		Other Tick to be compared.
		 *
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		bool operator>=( const Tick & tick ) const;

		/**
		 * @brief		Less-than-or-equal comparison operator
		 *
		 * @param		Other Tick to be compared.
		 *
		 * @returns	True if the first parameter is less than or equal to the second.
		 */
		bool operator<=( const Tick & tick ) const;



		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/

		/**
		 * @brief		Assignment operator
		 *
		 * @param		Other Tick.
		 *
		 * @returns	A shallow copy of this object.
		 */
		Tick & operator=( const Tick & tick );

		/**
		 * @brief		Subtraction assignment operator
		 *
		 * @param		Other Tick.
		 *
		 * @returns	The result of the operation.
		 */
		Tick & operator-=( const Tick & tick );

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
		Tick( ctor );
	private:
		/** @brief	A ClockT to process */
		ClockT c;
	};


	/**
	 * @brief		Subtraction operator
	 *
	 * @param	t1	The first value.
	 * @param	t2	A value to subtract from it.
	 *
	 * @returns	The result of the operation.
	 */
	Tick operator-( const Tick & t1, const Tick & t2 );


	/**
	 * @brief		Gets the clock
	 *
	 * @returns	The clock.
	 */
	Tick getClock();



}

