
namespace Utility {

	template<typename T>
	void swap( T & v1, T & v2 ) {
		T tmp = v1;
		v1 = v2;
		v2 = tmp;
	}


	template<typename T>
	void swap( T * v1, T * v2 ) {
		T tmp = *v1;
		*v1 = *v2;
		*v2 = tmp;
	}


	template<typename T>
	constexpr typename removeReference<T>::Type && toRValue( T && t ) {
		return static_cast< typename removeReference<T>::Type && >( t );
	}

	//Default implementation with a one per one copy.
	template<typename T>
	template<typename C, typename D>
	void UtilityT<T>::copy(C* destinationBuffer, const D* sourceBuffer, const Size size) {
		if ( isSame<C, D>::value ) {
			for ( Size i(0); i < size; i++ ) {
				destinationBuffer[ i ] = sourceBuffer[ i ];
			}
		} else {
			for ( Size i(0); i < size; i++ ) {
				destinationBuffer[ i ] = static_cast< C >( sourceBuffer[ i ] );
			}
		}
	}


	template<typename T>
	template<typename C, typename D>
	void UtilityT<T>::copy(C** destinationBuffer, D* const* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(C*));
	}
	template<typename T>
	void UtilityT<T>::copy(char* destinationBuffer, const char* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size);
	}
	template<typename T>
	void UtilityT<T>::copy(unsigned char* destinationBuffer, const unsigned char* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size);
	}
	template<typename T>
	void UtilityT<T>::copy(short* destinationBuffer, const short* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(short));
	}
	template<typename T>
	void UtilityT<T>::copy(unsigned short* destinationBuffer, const unsigned short* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(short));
	}
	template<typename T>
	void UtilityT<T>::copy(int* destinationBuffer, const int* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(int));
	}
	template<typename T>
	void UtilityT<T>::copy(unsigned int* destinationBuffer, const unsigned int* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(int));
	}
	template<typename T>
	void UtilityT<T>::copy(long int* destinationBuffer, const long int* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(long int));
	}
	template<typename T>
	void UtilityT<T>::copy(unsigned long int* destinationBuffer, const unsigned long int* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(long int));
	}
	template<typename T>
	void UtilityT<T>::copy(long long int* destinationBuffer, const long long int* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(long long int));
	}
	template<typename T>
	void UtilityT<T>::copy(unsigned long long int* destinationBuffer, const unsigned long long int* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(long long int));
	}
	template<typename T>
	void UtilityT<T>::copy(float* destinationBuffer, const float* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(float));
	}
	template<typename T>
	void UtilityT<T>::copy(double* destinationBuffer, const double* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(double));
	}
	template<typename T>
	void UtilityT<T>::copy(wchar_t* destinationBuffer, const wchar_t* sourceBuffer, const Size size) {
		memcpy(destinationBuffer, sourceBuffer, size * sizeof(wchar_t));
	}

}

