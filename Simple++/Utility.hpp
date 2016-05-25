
namespace Utility {

	template<typename T>
	void swap( T & v1,  T & v2){
		T tmp = v1;
		v1 = v2;
		v2 = tmp;
	}


	template<typename T>
	void swap(T * v1, T * v2){
		T tmp = *v1;
		*v1 = *v2;
		*v2 = tmp;
	}


	template<typename T>
	constexpr typename removeReference<T>::Type && toRValue(T && t) {
		return static_cast<typename removeReference<T>::Type &&>( t );
	}

}

