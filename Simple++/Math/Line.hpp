

namespace Math {


	template<typename T>
	void Math::Line<T>::setP1( const Vec2<T> & p ) {
		this -> p1 = p;
	}

	template<typename T>
	void Math::Line<T>::setP0( const Vec2<T> & p ) {
		this -> p0 = p;
	}

	template<typename T>
	const Vec2<T> & Math::Line<T>::getP1() const {
		return this -> p1;
	}

	template<typename T>
	const Vec2<T> & Math::Line<T>::getP0() const {
		return this -> p0;
	}


	template<typename T>
	Math::Line<T>::Line() {

	}

	template<typename T>
	Math::Line<T>::Line( const T & x0, const T & y0, const T & x1, const T & y1 ) :
		p0( x0, y0 ),
		p1( x1, y1 ) {

	}

	template<typename T>
	Math::Line<T>::Line( const Vec2<T> & p0, const Vec2<T> & p1 ) :
		p0( p0 ),
		p1( p1 ) {

	}



}
