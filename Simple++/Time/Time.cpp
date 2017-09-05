#include "Time.h"


namespace Time {



	template<class ratio>
	void sleep( const Duration<ratio> & d ) {
		sleep( Duration<MilliSecond>( d ).getValue() );
	}


	void Time::sleep( unsigned long ms ) {
		#if defined WIN32
		Sleep( ( DWORD ) ms );
		#else
		usleep( ms * 1000 );
		#endif
	}





}





