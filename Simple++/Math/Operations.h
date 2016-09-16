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



		struct AddEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x += y; return x; }
		};
		struct SubEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x -= y; return x; }
		};
		struct MulEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x *= y; return x; }
		};
		struct DivEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x /= y; return x; }
		};
		struct ModulusEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x %= y; return x; }
		};
		struct BinaryShiftRightEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x >>= y; return x; }
		};
		struct BinaryShiftLeftEqual {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x <<= y; return x; }
		};
		struct Assign {
			template<typename T> inline T & operator() ( T& x, const T& y ) const { x = y; return x; }
		};

		struct Identity {
			template<typename T> inline T & operator() ( T & x ) const { return x; }
		};
	}

}
