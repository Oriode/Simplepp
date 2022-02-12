namespace Time {

	template<class Ratio>
	void sleep( const Duration<Ratio> & d ) {
		sleep( d.getMilliSeconds() );
	}

	template<typename T>
	void sleep(const T& ms) {
		#if defined WIN32
			#if defined ENABLE_WIN32
				Sleep( ( DWORD ) ms );
			#endif
		#else
		usleep( ms * 1000 );
		#endif
	}

}