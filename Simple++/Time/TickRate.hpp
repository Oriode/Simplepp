
namespace Time {

	template<typename T>
	TickRateT<T>::TickRateT( int targetTickRate ) :
		timePerTick( Math::max( int( 1000 ) / targetTickRate, 1 ) ),
		timePerTickSeconds( float( this -> timePerTick.getValue() ) / float( 1000.0 ) ),
		tickNumber( 0 ),
		elapsedTimeS( 0 ),
		elapsedTimeMS( 0 ) {
		setTargetTickRate( targetTickRate );
	}

	template<typename T>
	TickRateT<T>::~TickRateT( void ) {}

	template<typename T>
	void TickRateT<T>::setTargetTickRate( unsigned int tickrate ) {
		if ( tickrate == 0 )
			return;
		this -> targetTickRate = tickrate;
		this -> targetTimePerTick = ( Time::TimeT ) ( float( 1000.0 ) / float( this -> targetTickRate ) );
	}


	template<typename T>
	void TickRateT<T>::delay() {
		//wait depending of the actual tickrate
		this -> timePerTick = Time::Duration<Time::MilliSecond>( Time::getClock().getValue() - this -> endTicks.getValue() );

		if ( this -> timePerTick < this -> targetTimePerTick ) {
			Time::sleep( static_cast< unsigned int >( this -> targetTimePerTick.getValue() - this -> timePerTick.getValue() ) );
			this -> timePerTick = this -> targetTimePerTick;
		}

		//increment the number of ticks (its an unsigned int, don't worry for overflow)
		this -> tickNumber++;

		this -> endTicks = Time::getClock();
		this -> timePerTickSeconds = float( this -> timePerTick.getValue() ) / float( 1000.0 );
		this -> elapsedTimeS += this -> timePerTickSeconds;
		this -> elapsedTimeMS += this -> timePerTick;
	}

	template<typename T>
	const Time::Duration<Time::MilliSecond> & TickRateT<T>::getTimePerTickMS() const {
		return this -> timePerTick;
	}

	template<typename T>
	const Time::Duration<Time::MilliSecond> & TickRateT<T>::getElapsedTimeMS() const {
		return this -> elapsedTimeMS;
	}

	template<typename T>
	float TickRateT<T>::getTimePerTickS() const {
		return this -> timePerTickSeconds;
	}

	template<typename T>
	unsigned long long int TickRateT<T>::getTickNum() const {
		return this -> tickNumber;
	}

	template<typename T>
	float TickRateT<T>::getElapsedTimeS() const {
		return this -> elapsedTimeS;
	}


}

