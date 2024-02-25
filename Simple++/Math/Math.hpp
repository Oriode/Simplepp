#include "Math.h"

namespace Math {

	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec2<T>& v1, const Vec2<T>& v2 ) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec3<T>& v1, const Vec3<T>& v2 ) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Vec4<T>& v1, const Vec4<T>& v2 ) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const T* v1, const T* v2, const Size n ) {
		T sumDot( 0 );
		for ( Size i( 0 ); i < n; i++ ) {
			sumDot += v1[ i ] * v2[ i ];
		}
		return sumDot;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T dot( const Table<T>& t1, const Table<T>& t2 ) {
		ASSERT_SPP( t1.getSize() == t2.getSize() );
		return dot( t1.getData(), t2.getData(), t1.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec3<T>& v ) {
		return min( min( v.x, v.y ), v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> min( const Vec3<T>& v, const T& x ) {
		return Vec3<T>( min( v.x, x ), min( v.y, x ), min( v.z, x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> min( const Vec3<T>& v1, const Vec3<T>& v2 ) {
		return Vec3<T>( min( v1.x, v2.x ), min( v1.y, v2.y ), min( v1.z, v2.z ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec4<T>& v ) {
		return min( min( min( v.x, v.y ), v.z ), v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> min( const Vec4<T>& v, const T& x ) {
		return Vec4<T>( min( v.x, x ), min( v.y, x ), min( v.z, x ), min( v.w, x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> min( const Vec4<T>& v1, const Vec4<T>& v2 ) {
		return Vec4<T>( min( v1.x, v2.x ), min( v1.y, v2.y ), min( v1.z, v2.z ), min( v1.w, v2.w ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec<T>& v ) {
		if ( v.getSize() == Size( 0 ) ) {
			return T( 0 );
		}
		else {
			T minV( v[ 0 ] );
			for ( Size i( 0 ); i < v.getSize(); i++ ) {
				const T& value( v[ i ] );
				if ( value < minV ) {
					minV = value;
				}
			}
			return minV;
		}
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> min( const Table<T>& v, const T& x ) {
		return apply( Math::Min(), v, x );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> min( const Table<T>& v1, const Table<T>& v2 ) {
		return apply( Math::Min(), v1, v2 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T min( const Vec2<T>& v ) {
		return min( v.x, v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> min( const Vec2<T>& v, const T& x ) {
		return Vec2<T>( min( v.x, x ), min( v.y, x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> min( const Vec2<T>& v1, const Vec2<T>& v2 ) {
		return Vec2<T>( min( v1.x, v2.x ), min( v1.y, v2.y ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec3<T>& v ) {
		return max( max( v.x, v.y ), v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> max( const Vec3<T>& v, const T& x ) {
		return Vec3<T>( max( v.x, x ), max( v.y, x ), max( v.z, x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> max( const Vec3<T>& v1, const Vec3<T>& v2 ) {
		return Vec3<T>( max( v1.x, v2.x ), max( v1.y, v2.y ), max( v1.z, v2.z ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec4<T>& v ) {
		return max( max( max( v.x, v.y ), v.z ), v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> max( const Vec4<T>& v, const T& x ) {
		return Vec4<T>( max( v.x, x ), max( v.y, x ), max( v.z, x ), max( v.w, x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> max( const Vec4<T>& v1, const Vec4<T>& v2 ) {
		return Vec4<T>( max( v1.x, v2.x ), max( v1.y, v2.y ), max( v1.z, v2.z ), max( v1.w, v2.w ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec<T>& v ) {
		if ( v.getSize() == Size( 0 ) ) {
			return T( 0 );
		}
		else {
			T maxV( v[ 0 ] );
			for ( Size i( 0 ); i < v.getSize(); i++ ) {
				const T& value( v[ i ] );
				if ( value > maxV ) {
					maxV = value;
				}
			}
			return maxV;
		}
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> max( const Table<T>& v, const T& x ) {
		return apply( Math::Max(), v, x );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> max( const Table<T>& v1, const Table<T>& v2 ) {
		return apply( Math::Max(), v1, v2 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T max( const Vec2<T>& v ) {
		return max( v.x, v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> max( const Vec2<T>& v, const T& x ) {
		return Vec2<T>( max( v.x, x ), max( v.y, x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> max( const Vec2<T>& v1, const Vec2<T>& v2 ) {
		return Vec2<T>( max( v1.x, v2.x ), max( v1.y, v2.y ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER  Vec2<T> abs( const Vec2<T>& v ) {
		return Vec2<T>( abs( v.x ), abs( v.y ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> abs( const Vec3<T>& v ) {
		return Vec3<T>( abs( v.x ), abs( v.y ), abs( v.z ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> abs( const Vec4<T>& v ) {
		return Vec4<T>( abs( v.x ), abs( v.y ), abs( v.z ), abs( v.w ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> cross( const Vec2<T>& v1, const Vec2<T>& v2 ) {
		return Vec2<T>( v1.y * v2.x - v2.y * v1.x,
						v1.x * v2.y - v2.x * v1.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> cross( const Vec3<T>& v1, const Vec3<T>& v2 ) {
		return Vec3<T>( v1.y * v2.z - v2.y * v1.z,
						v1.z * v2.x - v2.z * v1.x,
						v1.x * v2.y - v2.x * v1.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> cross( const Vec4<T>& v1, const Vec4<T>& v2 ) {
		return Vec4<T>( v1.y * v2.z - v2.y * v1.z,
						v1.z * v2.w - v2.z * v1.w,
						v1.w * v2.x - v2.w * v1.x,
						v1.x * v2.y - v2.x * v1.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> cross( const Vec<T>& v1, const Vec<T>& v2 ) {
		ASSERT_SPP( v1.getSize() == v2.getSize() );
		Vec<T> crossProduct( v1.getSize() );
		for ( Size i( 0 ); i < v1.getSize(); i++ ) {
			crossProduct[ i ] = v1[ ( i + Size( 1 ) ) % v1.getSize() ] * v2[ ( i + Size( 2 ) ) % v2.getSize() ] - v2[ ( i + Size( 1 ) ) % v2.getSize() ] * v1[ ( i + Size( 2 ) ) % v1.getSize() ];
		}
		return crossProduct;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T normalize( const T& v ) {
		return v > T( 0 ) ? T( 1 ) : T( -1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> normalize( const Vec2<T>& v ) {
		return v / length( v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> normalize( const Vec3<T>& v ) {
		return v / length( v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> normalize( const Vec4<T>& v ) {
		return v / length( v );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec<T> normalize( const Vec<T>& v ) {
		return v / length( v );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> sqrt( const Vec2<T>& v ) {
		v.x = sqrt( v.x );
		v.y = sqrt( v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> sqrt( const Vec3<T>& v ) {
		v.x = sqrt( v.x );
		v.y = sqrt( v.y );
		v.z = sqrt( v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> sqrt( const Vec4<T>& v ) {
		v.x = sqrt( v.x );
		v.y = sqrt( v.y );
		v.z = sqrt( v.z );
		v.w = sqrt( v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void sqrt( T* dataTable, const Size n ) {
		for ( Size i( 0 ); i < n; i++ ) {
			dataTable[ i ] = Math::sqrt( dataTable[ i ] );
		}
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void sqrt( Table<T>* t ) {
		sqrt( t->getData(), t->getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T inverseSqrt( const T& data ) {
		return T( 1 ) / sqrt( data );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> inverseSqrt( const Vec2<T>& v ) {
		v.x = inverseSqrt( v.x );
		v.y = inverseSqrt( v.y );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> inverseSqrt( const Vec3<T>& v ) {
		v.x = inverseSqrt( v.x );
		v.y = inverseSqrt( v.y );
		v.z = inverseSqrt( v.z );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> inverseSqrt( const Vec4<T>& v ) {
		v.x = inverseSqrt( v.x );
		v.y = inverseSqrt( v.y );
		v.z = inverseSqrt( v.z );
		v.w = inverseSqrt( v.w );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleSurface( const Vec3<T>& v1, const Vec3<T>& v2, const Vec3<T>& v3 ) {
		const T a = length( v2 - v1 );
		const T b = length( v3 - v1 );
		const T c = length( v3 - v2 );

		const T s = ( a + b + c ) / T( 2 );
		return sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec3<T>& v ) {
		return sqrt( dot( v, v ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec2<T>& v ) {
		return sqrt( dot( v, v ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Vec4<T>& v ) {
		return sqrt( dot( v, v ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const T* dataTable, const Size n ) {
		const T d( Math::dot( dataTable, dataTable, n ) );
		return Math::sqrt( d );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T length( const Table<T>& v ) {
		return length( v.getData(), v.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T distance( const T& v1, const T& v2 ) {
		return Math::abs( v2 - v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T distance( const Vec3<T>& v1, const Vec3<T>& v2 ) {
		return length( v2 - v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T distance( const Vec2<T>& v1, const Vec2<T>& v2 ) {
		return length( v2 - v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T distance( const Vec4<T>& v1, const Vec4<T>& v2 ) {
		return length( v2 - v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T distance( const Vec<T>& v1, const Vec<T>& v2 ) {
		return length( v2 - v1 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T triangleDot( const Vec3<T>& v1, const Vec3<T>& v2, const Vec3<T>& v3 ) {
		const T dot1 = dot( v1, v2 );
		const T dot2 = dot( v1, v3 );
		const T dot3 = dot( v2, v3 );
		return T( 1 ) - min( min( dot1, dot2 ), dot3 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sum( const Vec2<T>& v ) {
		return v.x + v.y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sum( const Vec3<T>& v ) {
		return v.x + v.y + v.z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sum( const Vec4<T>& v ) {
		return v.x + v.y + v.z + v.w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sum( const T* dataTable, const Size n ) {
		T sumValue( 0 );
		for ( Size i( 0 ); i < n; i++ ) {
			sumValue += dataTable[ i ];
		}
		return sumValue;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sum( const Table<T>& v ) {
		return sum(v.getData(), v.getSize());
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T sum( const Mat<T>& m ) {
		return sum( m.getData(), m.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T mean( const Vec2<T>& v ) {
		return mean( v ) / T( 2 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T mean( const Vec3<T>& v ) {
		return mean( v ) / T( 3 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T mean( const Vec4<T>& v ) {
		return mean( v ) / T( 4 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T mean( const Vec<T>& v ) {
		return mean( v ) / T( v.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T mean( const T* dataTable, const Size n ) {
		T m( 0 );
		for ( Size i( 0 ); i < n; i++ ) {
			m += dataTable[ i ];
		}
		return m / T( n );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T mean( const Table<T>& t ) {
		return mean( t.getData(), t.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T variance( const T* dataTable, const Size n ) {
		T m( mean( dataTable, n ) );
		T deltaSum( 0 );
		for ( Size i( 0 ); i < n; i++ ) {
			const T& v( dataTable[ i ] );
			const T e( v - m );

			deltaSum += e * e;
		}
		return deltaSum / T( n );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T variance( const Table<T>& t ) {
		return variance( t.getData(), t.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation( const Vec2<T>& v ) {
		return Math::abs( v.y - v.x ) / T( 2 );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation( const Vec3<T>& v ) {
		return Math::sqrt( Math::variance( v.getData(), v.getSize() ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation( const Vec4<T>& v ) {
		return Math::sqrt( Math::variance( v.getData(), v.getSize() ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation( const T* dataTable, const Size n ) {
		return Math::sqrt( Math::variance( dataTable, n ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T standardDeviation( const Table<T>& t ) {
		return Math::sqrt( Math::variance( t ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void abs( T* dataTable, const Size n ) {
		for ( Size i( 0 ); i < n; i++ ) {
			dataTable[ i ] = Math::abs( dataTable[ i ] );
		}
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void abs( Table<T>* t ) {
		Math::abs( t->getData(), t->getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp( Line<T>* l, const Rectangle<T>& r ) {
		Line<T>& line = *l;

		// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
		unsigned int outcode0 = r.getZone( line.getP0() );
		unsigned int outcode1 = r.getZone( line.getP1() );
		bool accept = false;

		while ( true ) {
			if ( !( outcode0 | outcode1 ) ) { // Bitwise OR is 0. Trivially accept and get out of loop
				accept = true;
				break;
			}
			else if ( outcode0 & outcode1 ) { // Bitwise AND is not 0. Trivially reject and get out of loop
				break;
			}
			else {
				// failed both tests, so calculate the line segment to clip
				// from an outside point to an intersection with clip edge
				Vec2<T> p;

				// use reference for simpler formulas
				const Vec2<T>& p0 = line.getP0();
				const Vec2<T>& p1 = line.getP1();

				// At least one endpoint is outside the clip rectangle; pick it.
				unsigned int outcodeOut = outcode0 ? outcode0 : outcode1;

				// Now find the intersection point;
				// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
				if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Top ) {           // point is above the clip rectangle
					p.x = p0.x + ( p1.x - p0.x ) * ( r.getTop() - p0.y ) / ( p1.y - p0.y );
					p.y = r.getTop();
				}
				else if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Bottom ) { // point is below the clip rectangle
					p.x = p0.x + ( p1.x - p0.x ) * ( r.getBottom() - p0.y ) / ( p1.y - p0.y );
					p.y = r.getBottom();
				}
				else if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Right ) {  // point is to the right of clip rectangle
					p.y = p0.y + ( p1.y - p0.y ) * ( r.getRight() - p0.x ) / ( p1.x - p0.x );
					p.x = r.getRight();
				}
				else if ( outcodeOut & ( unsigned int ) Rectangle<T>::Position::Left ) {   // point is to the left of clip rectangle
					p.y = p0.y + ( p1.y - p0.y ) * ( r.getLeft() - p0.x ) / ( p1.x - p0.x );
					p.x = r.getLeft();
				}

				// Now we move outside point to intersection point to clip
				// and get ready for next pass.
				if ( outcodeOut == outcode0 ) {
					line.setP0( p );
					outcode0 = r.getZone( line.getP0() );
				}
				else {
					line.setP1( p );
					outcode1 = r.getZone( line.getP1() );
				}
			}
		}
		return accept;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER bool clamp( Vec2<T>* point, const Rectangle<T>& r ) {
		Vec2<T>& p = *point;
		bool result = true;

		if ( p.x < r.getLeft() ) {
			p.x = r.getLeft();
			result = false;
		}
		else if ( p.x > r.getRight() ) {
			p.x = r.getRight();
			result = false;
		}

		if ( p.y < r.getBottom() ) {
			p.y = r.getBottom();
			result = false;
		}
		else if ( p.y > r.getTop() ) {
			p.y = r.getTop();
			result = false;
		}

		return result;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setRandomF( T * v ) {
		*v = Math::randomF();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setRandomF( Vec2<T> * v ) {
		v->randomF();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setRandomF( Vec3<T> * v ) {
		v->randomF();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setRandomF( Vec4<T> * v ) {
		v->randomF();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setRandomF( T* dataTable, const Size n ) {
		for ( Size i( 0 ); i < n; i++ ) {
			dataTable[ i ] = Math::randomF();
		}
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setRandomF( Table<T> * v ) {
		setRandomF( v->getData(), v->getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T coefficientOfDetermination( const Table<T>& Y, const Table<T>& expectedY ) {
		ASSERT_SPP( expectedY.getSize() == Y.getSize() );
		return coefficientOfDetermination( Y.getData(), expectedY.getData(), Y.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T coefficientOfDetermination( const T* YDataTable, const T* expectedYDataTable, const Size n ) {
		T errSum( 0 );
		T meanSum( 0 );

		const T expectedMean( mean( expectedYDataTable, n ) );

		for ( Size i( 0 ); i < n; i++ ) {
			const T& y( YDataTable[ i ] );
			const T& expectedY( expectedYDataTable[ i ] );
			const T e( expectedY - y );
			const T m( expectedY - expectedMean );

			errSum += e * e;
			meanSum += m * m;
		}

		return T( 1 ) - errSum / meanSum;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T covariance( const T* XDataTable, const T* YDataTable, const Size n ) {
		T mX( Math::mean( XDataTable, n ) );
		T mY( Math::mean( YDataTable, n ) );

		T cov( 0 );
		for ( Size i( 0 ); i < n; i++ ) {
			const T& x( XDataTable[ i ] );
			const T& y( YDataTable[ i ] );

			cov += ( x - mX ) * ( y - mY );
		}
		return cov / T(n);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T covariance( const Table<T>& X, const Table<T>& Y ) {
		ASSERT_SPP( X.getSize() == Y.getSize() );
		return covariance( X.getData(), Y.getData(), X.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T correlationCoefficient( const T* XDataTable, const T* YDataTable, const Size n ) {
		const T sdX( standardDeviation( XDataTable, n ) );
		const T sdY( standardDeviation( YDataTable, n ) );
		const T cov( covariance( XDataTable, YDataTable, n ) );

		return cov / ( sdX * sdY );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T correlationCoefficient( const Table<T>& X, const Table<T>& Y ) {
		ASSERT_SPP( X.getSize() == Y.getSize() );
		return correlationCoefficient( X.getData(), Y.getData(), X.getSize() );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> getMinMax( const Vec3<T>& v ) {
		Vec2<T> minMax;
		if ( v.x > v.y ) {
			if ( v.x > v.z )
				minMax.y = ( v.x );
			else
				minMax.y = ( v.z );

			if ( v.y < v.z )
				minMax.x = ( v.y );
			else
				minMax.x = ( v.z );
		}
		else {
			if ( v.x < v.z )
				minMax.x = ( v.x );
			else
				minMax.x = ( v.z );

			if ( v.y > v.z )
				minMax.y = ( v.y );
			else
				minMax.y = ( v.z );
		}
		return minMax;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> getMinMax( const Vec4<T>& v ) {
		return Vec2<T>( min( v ), max( v ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> getMinMax( const Table<T>& t ) {
		if ( t.getSize() == Size( 0 ) ) {
			return Vec2<T>( T( 0 ), T( 0 ) );
		}
		else {
			Vec2<T> minMax( t[ 0 ], t[ 0 ] );

			for ( Size i( 1 ); i < t.getSize(); i++ ) {
				const T& value( t[ i ] );

				if ( value < minMax.x ) {
					minMax.x = value;
				}
				else if ( value > minMax.y ) {
					maxV = minMax.y;
				}
			}

			return minMax;
		}
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T linearInterpolate( const T& a, const T& b, const T& alpha ) {
		return a * ( T( 1 ) - alpha ) + b * alpha;
	}

}
