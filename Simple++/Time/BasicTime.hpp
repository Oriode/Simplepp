namespace Time {

	template<class T>
	template<typename RatioOut, typename RatioIn>
	inline TimeT BasicTimeT<T>::convertTime(const TimeT& t) {
		return _convertTime(t, reinterpret_cast< RatioOut* >( NULL ), reinterpret_cast< RatioIn* >( NULL ));
	}

	template<class T>
	template<typename RatioOut, typename RatioIn>
	inline TimeT BasicTimeT<T>::_convertTime(const TimeT& t, RatioOut* rOut, RatioIn* rIn) {
		return ( t * RatioOut::den * RatioIn::num ) / RatioIn::den / RatioOut::num;
	}

	template<class T>
	template<typename Ratio>
	inline TimeT BasicTimeT<T>::_convertTime(const TimeT& t, Ratio* rOut, Ratio* rIn) {
		return t;
	}

}