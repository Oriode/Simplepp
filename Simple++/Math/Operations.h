#pragma once


namespace Math {

	template <class T> struct add {
		T operator() (const T& x, const T& y) const {return x+y;}
	};
	template <class T> struct sub {
		T operator() (const T& x, const T& y) const {return x-y;}
	};
	template <class T> struct mul {
		T operator() (const T& x, const T& y) const {return x*y;}
	};
	template <class T> struct div {
		T operator() (const T& x, const T& y) const {return x/y;}
	};
	template <class T> struct modulus {
		T operator() (const T& x, const T& y) const {return x%y;}
	};
	template <class T> struct binaryShiftRight {
		T operator() (const T& x, const T& y) const {x>>y;}
	};
	template <class T> struct binaryShiftLeft {
		T operator() (const T& x, const T& y) const {x<<y;}
	};



	template <class T> struct addEqual {
		T & operator() ( T& x, const T& y) const {x+=y; return x;}
	};
	template <class T> struct subEqual {
		T & operator() ( T& x, const T& y) const {x-=y; return x;}
	};
	template <class T> struct mulEqual {
		T & operator() ( T& x, const T& y) const {x*=y; return x;}
	};
	template <class T> struct divEqual {
		T & operator() ( T& x, const T& y) const {x/=y; return x;}
	};
	template <class T> struct modulusEqual {
		T & operator() ( T& x, const T& y) const {x%=y; return x;}
	};
	template <class T> struct binaryShiftRightEqual {
		T & operator() ( T& x, const T& y) const {x>>=y; return x;}
	};
	template <class T> struct binaryShiftLeftEqual {
		T & operator() ( T& x, const T& y) const {x<<=y; return x;}
	};
	template <class T> struct equal {
		T & operator() ( T& x, const T& y) const {x=y; return x;}
	};


}