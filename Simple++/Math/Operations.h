#pragma once


namespace Math {

	namespace Operations {

		struct Add {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { return x + y; }
		};
		struct Sub {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { return x - y; }
		};
		struct Mul {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { return x * y; }
		};
		struct Div {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { return x / y; }
		};
		struct Modulus {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { return x % y; }
		};
		struct BinaryShiftRight {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { x >> y; }
		};
		struct BinaryShiftLeft {
			template<typename T> inline T operator() ( const T& x, const T& y ) const { x << y; }
		};
		struct MinusUnary {
			template<typename T> inline T operator() ( T& x ) const { return x = -x; }
		};


		struct AddEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x += y; }
		};
		struct SubEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x -= y; }
		};
		struct MulEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x *= y; }
		};
		struct DivEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x /= y; }
		};
		struct ModulusEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x %= y; }
		};
		struct BinaryShiftRightEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x >>= y; }
		};
		struct BinaryShiftLeftEqual {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x <<= y; }
		};
		struct Assign {
			template<typename T, typename U> inline T & operator() ( T& x, const U& y ) const { return x = y;  }
		};
		struct Increment {
			template<typename T> inline T & operator() ( T& x ) const { return x++; }
		};
		struct Decrement {
			template<typename T> inline T & operator() ( T& x ) const { return x--; }
		};

		struct Identity {
			template<typename T> inline T & operator() ( T & x ) const { return x; }
		};
	}

}
