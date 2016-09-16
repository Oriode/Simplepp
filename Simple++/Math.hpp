
namespace Math {

	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec3<T> & v ) {
		return min( min( v.x, v.y ), v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec2<T> & v ) {
		return min( v.x, v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec3<T> & v ) {
		return max( max( v.x, v.y ), v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec2<T> & v ) {
		return max( v.x, v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER  Vec2<T> abs( const Vec2<T> & v ) {
		return Vec2<T>( abs( v.x ), abs( v.y ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> abs( const Vec3<T> & v ) {
		return Vec3<T>( abs( v.x ), abs( v.y ), abs( v.z ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> abs( const Vec4<T> & v ) {
		return Vec4<T>( abs( v.x ), abs( v.y ), abs( v.z ), abs(v.w) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> cross( const Vec2<T> & v1, const Vec2<T> & v2 ) {
		return Vec2<T>( v1.y * v2.x - v2.y * v1.x,
						v1.x * v2.y - v2.x * v1.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> cross( const Vec3<T> & v1, const Vec3<T> & v2 ) {
		return Vec3<T>( v1.y * v2.z - v2.y * v1.z,
						v1.z * v2.x - v2.z * v1.x,
						v1.x * v2.y - v2.x * v1.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> cross( const Vec4<T> & v1, const Vec4<T> & v2 ) {
		return Vec3<T>( v1.y * v2.z - v2.y * v1.z,
						v1.z * v2.w - v2.z * v1.w,
						v1.w * v2.x - v2.w * v1.x,
						v1.x * v2.y - v2.x * v1.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T normalize( const T & v ) {
		return v > T( 0 ) ? T( 1 ) : T( -1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> normalize( const Vec2<T> & v ) {
		return v / length( v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> normalize( const Vec3<T> & v ) {
		return v / length( v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> normalize( const Vec4<T> & v ) {
		return v / length( v );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> sqrt( const Vec2<T> & v ) {
		v.x = sqrt( v.x );
		v.y = sqrt( v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> sqrt( const Vec3<T> & v ) {
		v.x = sqrt( v.x );
		v.y = sqrt( v.y );
		v.z = sqrt( v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> sqrt( const Vec4<T> & v ) {
		v.x = sqrt( v.x );
		v.y = sqrt( v.y );
		v.z = sqrt( v.z );
		v.w = sqrt( v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T inverseSqrt( const T & data ) {
		return T( 1 ) / sqrt( data );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> inverseSqrt( const Vec2<T> & v ) {
		v.x = inverseSqrt( v.x );
		v.y = inverseSqrt( v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> inverseSqrt( const Vec3<T> & v ) {
		v.x = inverseSqrt( v.x );
		v.y = inverseSqrt( v.y );
		v.z = inverseSqrt( v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> inverseSqrt( const Vec4<T> & v ) {
		v.x = inverseSqrt( v.x );
		v.y = inverseSqrt( v.y );
		v.z = inverseSqrt( v.z );
		v.w = inverseSqrt( v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleSurface( const Vec3<T> & v1, const Vec3<T> & v2, const Vec3<T> & v3 ) {
		const T a = length( v2 - v1 );
		const T b = length( v3 - v1 );
		const T c = length( v3 - v2 );

		const T s = ( a + b + c ) / T( 2 );
		return sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec3<T> & v ) {
		return sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec2<T> & v ) {
		return sqrt( v.x * v.x + v.y * v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec4<T> & v ) {
		return sqrt( v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleDot( const Vec3<T> & v1, const Vec3<T> & v2, const Vec3<T> & v3 ) {
		const T dot1 = dot( v1, v2 );
		const T dot2 = dot( v1, v3 );
		const T dot3 = dot( v2, v3 );
		return T( 1 ) - min( min( dot1, dot2 ), dot3 );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp( Line<T> * l, const Rectangle<T> & r ) {
		Line<T> & line = *l;

		// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
		unsigned int outcode0 = r.getZone( line.getP0() );
		unsigned int outcode1 = r.getZone( line.getP1() );
		bool accept = false;

		while ( true ) {
			if ( !( outcode0 | outcode1 ) ) { // Bitwise OR is 0. Trivially accept and get out of loop
				accept = true;
				break;
			} else if ( outcode0 & outcode1 ) { // Bitwise AND is not 0. Trivially reject and get out of loop
				break;
			} else {
				// failed both tests, so calculate the line segment to clip
				// from an outside point to an intersection with clip edge
				Vec2<T> p;

				// use reference for simpler formulas
				const Vec2<T> & p0 = line.getP0();
				const Vec2<T> & p1 = line.getP1();

				// At least one endpoint is outside the clip rectangle; pick it.
				unsigned int outcodeOut = outcode0 ? outcode0 : outcode1;

				// Now find the intersection point;
				// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
				if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Top ) {           // point is above the clip rectangle
					p.x = p0.x + ( p1.x - p0.x ) * ( r.getTop() - p0.y ) / ( p1.y - p0.y );
					p.y = r.getTop();
				} else if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Bottom ) { // point is below the clip rectangle
					p.x = p0.x + ( p1.x - p0.x ) * ( r.getBottom() - p0.y ) / ( p1.y - p0.y );
					p.y = r.getBottom();
				} else if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Right ) {  // point is to the right of clip rectangle
					p.y = p0.y + ( p1.y - p0.y ) * ( r.getRight() - p0.x ) / ( p1.x - p0.x );
					p.x = r.getRight();
				} else if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Left ) {   // point is to the left of clip rectangle
					p.y = p0.y + ( p1.y - p0.y ) * ( r.getLeft() - p0.x ) / ( p1.x - p0.x );
					p.x = r.getLeft();
				}

				// Now we move outside point to intersection point to clip
				// and get ready for next pass.
				if ( outcodeOut == outcode0 ) {
					line.setP0( p );
					outcode0 = r.getZone( line.getP0() );
				} else {
					line.setP1( p );
					outcode1 = r.getZone( line.getP1() );
				}
			}
		}
		return accept;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp( Vec2<T> * point, const Rectangle<T> & r ) {
		Vec2<T> & p = *point;
		bool result = true;

		if ( p.x < r.getLeft() ) {
			p.x = r.getLeft();
			result = false;
		} else if ( p.x > r.getRight() ) {
			p.x = r.getRight();
			result = false;
		}

		if ( p.y < r.getBottom() ) {
			p.y = r.getBottom();
			result = false;
		} else if ( p.y > r.getTop() ) {
			p.y = r.getTop();
			result = false;
		}

		return result;
	}

}
