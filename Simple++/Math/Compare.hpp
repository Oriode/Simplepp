namespace Math {

	namespace Compare {


		template<typename T>
		inline typename Value Template::operator() ( const T & x, const T & y ) const {
			return _compare( x, y, static_cast< const T * >( NULL ) );
		}

		template<typename T>
		Value _compare( const T & x, const T & y, ... ) {
			if ( x == y )
				return Math::Compare::Value::Equal;
			else if ( x < y )
				return Math::Compare::Value::Less;
			else
				return Math::Compare::Value::Greater;
		}

		template<typename T>
		Value _compare( const T & x, const T & y, const BasicComparable * ) {
			return T::compare( x, y );
		}
		
		template<typename T>
		Value compare( const T & x, const T & y ) {
			return Math::Compare::_compare( x, y, static_cast< const T * >( NULL ) );
		}

	 }



}
