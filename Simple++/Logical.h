#pragma once


namespace Logical {

	
	template <class T> struct or {
		bool operator() (const T& x, const T& y) const {return x||y;}
	};

	template <class T> struct less {
		bool operator() (const T& x, const T& y) const {return x<y;}
	};

	template <class T> struct lessP {
		bool operator() (const T& x, const T& y) const {return *x<*y;}
	};

	template <class T> struct greater {
		bool operator() (const T& x, const T& y) const {return x>y;}
	};

	template <class T> struct greaterP {
		bool operator() (const T& x, const T& y) const {return *x>*y;}
	};

	template <class T> struct and {
		bool operator() (const T& x, const T& y) const {return x&&y;}
	};

	template <class T> struct lessEqual {
		bool operator() (const T& x, const T& y) const {return x<=y;}
	};

	template <class T> struct greaterEqual {
		bool operator() (const T& x, const T& y) const {return x>=y;}
	};

	template <class T> struct lessEqualP {
		bool operator() (const T& x, const T& y) const {return *x<=*y;}
	};

	template <class T> struct greaterEqualP {
		bool operator() (const T& x, const T& y) const {return *x>=*y;}
	};

	template <class T> struct equal {
		bool operator() (const T& x, const T& y) const {return x==y;}
	};

	template <class T> struct notEqual {
		bool operator() (const T& x, const T& y) const {return x!=y;}
	};

	template <class T> struct equalP {
		bool operator() (const T& x, const T& y) const {return *x==*y;}
	};

	template <class T> struct notEqualP {
		bool operator() (const T& x, const T& y) const {return *x!=*y;}
	};
}