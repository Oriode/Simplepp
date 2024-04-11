#pragma once


#include "Utility.h"

///@brief	An Optional is a class encapsulating an another that can be unset.
///			Internaly, it's basicaly a pointer to this type that can be NULL.
///			The pointer is memory managed inside the Optional object.
template<typename T>
class Optional {
public:
	///@brief	Constructors.
	Optional();
	Optional( const T& v );

	Optional( const Optional<T>& o );
	Optional( Optional<T>&& o );

	~Optional();

	///@brief	Conversion operator to the inner pointer.
	operator T* ( ) const;

	Optional<T>& operator=( const Optional<T>& o );
	Optional<T>& operator=( Optional<T>&& o );

	T & getValue();
	const T & getValue() const;

	void setValue( const T& v );

	T* operator->();
	const T* operator->() const;

	///@brief	Get if the Optional is set or not.
	bool isSet() const;

	///@brief	Unset the current value.
	void unset();

	static Optional<T> null;
private:
	T* v{ NULL };
};

template<typename T>
Optional<T> Optional<T>::null;

template<typename T>
inline Optional<T>::Optional() :
	v( NULL ) { }

template<typename T>
inline Optional<T>::Optional( const T& v ) :
	v( new T( v ) ) { }

template<typename T>
inline Optional<T>::Optional( const Optional<T>& o ) :
	v( new T( *o.v ) ) { }

template<typename T>
inline Optional<T>::Optional( Optional<T>&& o ) :
	v( Utility::toRValue( o.v ) ) { }

template<typename T>
inline Optional<T>::~Optional() {
	if ( this->v ) {
		delete this->v;
	}
}

template<typename T>
inline Optional<T>::operator T* ( ) const {
	return this->v;
}

template<typename T>
inline Optional<T>& Optional<T>::operator=( const Optional<T>& o ) {
	if ( this-> v ) {
		delete this->v;
	}

	if ( o.v ) {
		this->v = new T( *o.v );
	} else {
		this->v = NULL;
	}

	return *this;
}

template<typename T>
inline Optional<T>& Optional<T>::operator=( Optional<T>&& o ) {
	this->v = Utility::toRValue( o.v );

	return *this;
}

template<typename T>
inline T&  Optional<T>::getValue() {
	return *this->v;
}

template<typename T>
inline const T & Optional<T>::getValue() const {
	return *this->v;
}

template<typename T>
T* Optional<T>::operator->() {
	return this->v;
}

template<typename T>
const T* Optional<T>::operator->() const {
	return this->v;
}

template<typename T>
inline void Optional<T>::setValue( const T& v ) {
	if ( this->v ) {
		delete this->v;
	}

	this->v = new T( v );
}

template<typename T>
inline bool Optional<T>::isSet() const {
	return this->v != NULL;
}

template<typename T>
inline void Optional<T>::unset() {
	if ( this->v ) {
		delete this->v;
	}

	this->v = NULL;
}


