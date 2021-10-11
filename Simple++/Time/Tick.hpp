namespace Time {

	template<typename T>
	TickT<T> operator-( const TickT<T> & t1, const TickT<T> & t2 ) {
		return TickT( t1.getValue() - t2.getValue() );
	}

	template<typename T>
	TickT<T> getClock() {
		return TickT( clock() );
	}

	template<typename T>
	TickT<T>::TickT() {

	}

	template<typename T>
	TickT<T>::TickT( const TickT<T> & tick ) :
		c( tick.c ) {

	}

	template<typename T>
	TickT<T>::TickT( ClockT tick ) :
		c( tick ) {

	}

	template<typename T>
	TickT<T>::TickT( ctor ) {

	}

	template<typename T>
	void TickT<T>::setNow() {
		this -> c = clock();
	}

	template<typename T>
	TickT<T> & TickT<T>::operator-=( const TickT<T> & tick ) {
		this -> c -= tick.c;
		return *this;
	}

	template<typename T>
	const ClockT & TickT<T>::getValue() const {
		return this -> c;
	}

	template<typename T>
	TickT<T> & TickT<T>::operator=( const TickT<T> & tick ) {
		this -> c = tick.c;
		return *this;
	}

	template<typename T>
	bool TickT<T>::operator==( const TickT<T> & tick ) const {
		return tick.c == this -> c;
	}

	template<typename T>
	bool TickT<T>::operator<( const TickT<T> & tick ) const {
		return tick.c < this -> c;
	}

	template<typename T>
	bool TickT<T>::operator>( const TickT<T> & tick ) const {
		return tick.c > this -> c;
	}

	template<typename T>
	bool TickT<T>::operator<=( const TickT<T> & tick ) const {
		return tick.c <= this -> c;
	}

	template<typename T>
	bool TickT<T>::operator>=( const TickT<T> & tick ) const {
		return tick.c >= this -> c;
	}



	template<typename T>
	TickT<T>::~TickT() {}




}

