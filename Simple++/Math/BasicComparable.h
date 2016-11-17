#pragma once

namespace Math {


	namespace Compare {

		enum class Value : unsigned int {
			Equal,
			Less,
			Greater
		};

		
		class BasicComparable {
		public:
			///@brief Function to compare two elements
			///@param x First Element
			///@param y Second Element
			///@return Equal (x == y), Less (x < y) or Greater (x > y)
			static Math::Compare::Value compare( const BasicComparable & x, const BasicComparable & y );
		};
	}
}


#include "BasicComparable.hpp"
