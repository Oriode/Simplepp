#pragma once

#include "Vector.h"
#include "Utility.h"
#include "JSON/Node.h"
#include "IO/IO.h"

template<typename T>
class P : public IO::BasicIO, public JSON::Jsonable {
public:

	class SharedMemory {
	public:
		SharedMemory() = default;
		SharedMemory( T* data );
		~SharedMemory();

		T* getData();
		Size getNbOccurences() const;
		void setNbOccurences( const Size nbOccurence );

	private:
		T* data{ NULL };
		Size nbOccurence{ 0 };
	};

	// Empty constructor.
	P();

	// Constructor from a pointer.
	P( T* p );

	P( const P<T>& p );
	P( P<T>&& p );

	~P();

	P<T>& operator=( const P<T>& p );
	P<T>& operator=( P<T>&& p );

	const T* getValue() const;
	T* getValue();

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	bool operator==( const T* p ) const;
	bool operator==( const P<T>& p ) const;

	bool operator!=( const T* p ) const;
	bool operator!=( const P<T>& p ) const;

	operator T* ( );

	///@brief read from a file stream
	///@param stream stream used to read load this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>
	bool read( Stream* stream, int verbose = 0 );

	///@brief write this object as binary into a file stream
	///@param stream stream used to write this object
	///@return boolean to know if the operation is a success of not.
	template<typename Stream>
	bool write( Stream* stream ) const;

	///@brief Read a JSON object and set this to the read values.
	///@param nodeArray Pointer to the JSON object to be read.
	///@return true if success, false otherwise.
	template<typename S = UTF8String>
	bool fromJSON( const JSON::BasicNodeT<S>* node, int verbose = 0 );

	///@brief Write this object to a Json object
	///@param o Json node to write to.
	template<typename S = UTF8String>
	JSON::BasicNodeT<S>* toJSON() const;

private:
	void _removeReference();

	SharedMemory* sharedMemory{ NULL };
};

template<typename T>
inline P<T>::P() :
	sharedMemory( NULL ) {}

template<typename T>
inline P<T>::P( T* p ) {
	if ( p == NULL ) {
		this->sharedMemory = NULL;
	} else {
		this->sharedMemory = new SharedMemory( p );
	}
}

template<typename T>
inline P<T>::P( const P<T>& p ) :
	sharedMemory( p.sharedMemory ) {

	if ( this->sharedMemory ) {
		this->sharedMemory->setNbOccurences( this->sharedMemory->getNbOccurences() + Size( 1 ) );
	}
}

template<typename T>
inline P<T>::P( P<T>&& p ) :
	sharedMemory( p.sharedMemory ) {
	p.sharedMemory = NULL;
}

template<typename T>
inline P<T>::~P() {
	_removeReference();
}

template<typename T>
inline P<T>& P<T>::operator=( const P<T>& p ) {
	_removeReference();

	this->sharedMemory = p.sharedMemory;

	if ( this->sharedMemory ) {
		this->sharedMemory->setNbOccurences( this->sharedMemory->getNbOccurences() + Size( 1 ) );
	}

	return *this;
}

template<typename T>
inline P<T>& P<T>::operator=( P<T>&& p ) {
	_removeReference();


	this->sharedMemory = Utility::toRValue( p.sharedMemory );
	p.sharedMemory = NULL;

	return *this;
}

template<typename T>
inline const T* P<T>::getValue() const {
	if ( this->sharedMemory ) {
		return this->sharedMemory->getData();
	} else {
		return NULL;
	}
}

template<typename T>
inline T* P<T>::getValue() {
	if ( this->sharedMemory ) {
		return this->sharedMemory->getData();
	} else {
		return NULL;
	}
}

template<typename T>
inline const T* P<T>::operator->() const {
	return getValue();
}

template<typename T>
inline T* P<T>::operator->() {
	return getValue();
}

template<typename T>
inline const T& P<T>::operator*() const {
	return *getValue();
}

template<typename T>
inline T& P<T>::operator*() {
	return *getValue();
}

template<typename T>
inline bool P<T>::operator==( const T* p ) const {
	return getValue() == p;
}

template<typename T>
inline bool P<T>::operator==( const P<T>& p ) const {
	return getValue() == p.getValue();
}

template<typename T>
inline bool P<T>::operator!=( const T* p ) const {
	return getValue() != p;
}

template<typename T>
inline bool P<T>::operator!=( const P<T>& p ) const {
	return getValue() != p.getValue();
}

template<typename T>
inline P<T>::operator T* ( ) {
	return getValue();
}

template<typename T>
inline void P<T>::_removeReference() {
	if ( this->sharedMemory ) {
		if ( this->sharedMemory->getNbOccurences() > Size( 1 ) ) {
			this->sharedMemory->setNbOccurences( this->sharedMemory->getNbOccurences() - Size( 1 ) );
		} else {
			delete this->sharedMemory;
		}
	}
}

template<typename T>
inline P<T>::SharedMemory::SharedMemory( T* data ) : data( data ), nbOccurence( Size( 1 ) ) {}

template<typename T>
inline P<T>::SharedMemory::~SharedMemory() {
	if ( this->data ) {
		delete this->data;
	}
}

template<typename T>
inline T* P<T>::SharedMemory::getData() {
	return this->data;
}

template<typename T>
inline Size P<T>::SharedMemory::getNbOccurences() const {
	return this->nbOccurence;
}

template<typename T>
inline void P<T>::SharedMemory::setNbOccurences( const Size nbOccurence ) {
	this->nbOccurence = nbOccurence;
}

template<typename T>
template<typename Stream>
inline bool P<T>::read( Stream* stream, int verbose ) {
	_removeReference();
	this->sharedMemory = new SharedMemory( new T() );
	// Simple redirection to the inside type.
	return IO::read<Stream, T>( stream, getValue(), verbose );
}

template<typename T>
template<typename Stream>
inline bool P<T>::write( Stream* stream ) const {
	// Simple redirection to the inside type.
	return IO::write<Stream, T>( stream, getValue() );
}

template<typename T>
template<typename S>
inline bool P<T>::fromJSON( const JSON::BasicNodeT<S>* node, int verbose ) {
	_removeReference();
	this->sharedMemory = new SharedMemory( new T() );
	// Simple redirection to the inside type.
	return JSON::fromJSON<S, T>( node, getValue(), verbose );
}

template<typename T>
template<typename S>
inline JSON::BasicNodeT<S>* P<T>::toJSON() const {
	// Simple redirection to the inside type.
	return JSON::toJSON<S, T>( *getValue() );
}
