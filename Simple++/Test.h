#pragma once

template<typename T>
struct testExplicitCast {
	testExplicitCast() {};
	testExplicitCast( const T & v ) : v( v ) {}
	template<typename U>
	testExplicitCast( const testExplicitCast<U> & v ) : v( v.v ), v1( v.v1 ) {};

	testExplicitCast<T> & operator+=( const testExplicitCast<T> & v ) {
		this -> v += v.v; 
		this -> v1 += v.v1;
		return *this; 
	}

	T v, v1;
};

template<typename T>
struct testImplicitCast {
	testImplicitCast(){}
	testImplicitCast( const T & v ) : v( v ) {}

	template<typename U>
	testImplicitCast & operator+=( const testImplicitCast<U> & v ) {
		this -> v += v.v; 
		this -> v1 += v.v1;
		return *this;
	}

	T v, v1;
};


template<typename T>
struct A {
	static constexpr inline T one();
};

template<typename T>
constexpr T A<T>::one() { return T( 1 ); }

template<typename T>
struct B {
	static constexpr inline T one() { return T( 1 ) };
};
