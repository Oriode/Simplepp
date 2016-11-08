#pragma once

namespace Math {

	namespace Logical {

		struct Or {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x || y; }
		};

		struct Less {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x < y; }
		};

		struct LessPointer {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return *x < *y; }
		};

		struct Greater {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x > y; }
		};

		struct GreaterPointer {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return *x > *y; }
		};

		struct And {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x && y; }
		};

		struct LessOrEqual {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x <= y; }
		};

		struct GreaterOrEqual {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x >= y; }
		};

		struct LessOrEqualPointer {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return *x <= *y; }
		};

		struct GreaterOrEqualPointer {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return *x >= *y; }
		};

		struct Equal {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x == y; }
		};

		struct NotEqual {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return x != y; }
		};

		struct EqualPointer {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return *x == *y; }
		};

		struct NotEqualPointer {
			template<typename T, typename U> inline bool operator() ( const T& x, const U& y ) const { return *x != *y; }
		};
	}


}
