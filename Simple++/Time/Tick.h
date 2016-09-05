///@file Tick.h
///@brief Tick Class
///@author Clément Gerber
///@date 08/07/2016 (DMY) 

#pragma once



#include <ctime>

namespace Time {



	typedef clock_t ClockT;


	constexpr ClockT TicksPerSec = CLOCKS_PER_SEC;


	///@brief Representing a number of CPU ticks
	class Tick {
	public:
		///@brief Empty constructor, see getClock(); for the actual value
		Tick();


		Tick( const Tick & tick );
		Tick( ClockT tick );

		~Tick();

		void setNow();


		/************************************************************************/
		/* OPERATOR LOGICAL                                                     */
		/************************************************************************/
		bool operator==( const Tick & tick ) const;
		bool operator<( const Tick & tick ) const;
		bool operator>( const Tick & tick ) const;
		bool operator>=( const Tick & tick ) const;
		bool operator<=( const Tick & tick ) const;



		/************************************************************************/
		/* OPERATOR ARITHMETIC                                                  */
		/************************************************************************/
		Tick & operator=( const Tick & tick );
		Tick & operator-=( const Tick & tick );


		

		const ClockT & getValue() const;


	protected:
		enum ctor { null };
		Tick( ctor );
	private:
		ClockT c;
	};


	Tick operator-( const Tick & t1, const Tick & t2 );


	Tick getClock();



}

