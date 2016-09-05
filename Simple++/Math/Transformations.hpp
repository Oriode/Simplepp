


namespace Math {

	template<typename T>
	MATH_FUNC_QUALIFIER void scaleX( Mat4<T> * mat, const T & x ) {
		( *mat )[0] *= x;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleX( const Mat4<T> & mat, const T & x ) {
		return Mat4<T>( mat[0] * x, mat[1], mat[2], mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleY( Mat4<T> * mat, const T & y ) {
		( *mat )[1] *= y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleY( const Mat4<T> & mat, const T & y ) {
		return Mat4<T>( mat[0], mat[1] * y, mat[2], mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleZ( Mat4<T> * mat, const T & z ) {
		( *mat )[2][2] *= z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleZ( const Mat4<T> & mat, const T & z ) {
		return Mat4<T>( mat[0], mat[1], mat[2] * z, mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateY( Mat4<T> * mat, const T & y ) {
		( *mat )[3] += ( *mat )[1] * y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateY( const Mat4<T> & mat, const T & y ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] + mat[1] * y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZ( Mat4<T> * mat, const T & z ) {
		( *mat )[3] += ( *mat )[2] * z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZ( const Mat4<T> & mat, const T & z ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] + mat[2] * z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateX( Mat4<T> * mat, const T & x ) {
		( *mat )[3] += ( *mat )[0] * x;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateX( const Mat4<T> & mat, const T & x ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] + mat[0] * x );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Vec3<T> & s ) {
		return scale( s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const T & x, const T & y, const T & z ) {

		Mat4<T> result;
		result[0][0] = x;
		result[0][1] = T( 0 );
		result[0][2] = T( 0 );
		result[0][3] = T( 0 );

		result[1][0] = T( 0 );
		result[1][1] = y;
		result[1][2] = T( 0 );
		result[1][3] = T( 0 );

		result[2][0] = T( 0 );
		result[2][1] = T( 0 );
		result[2][2] = z;
		result[2][3] = T( 0 );

		result[3][0] = T( 0 );
		result[3][1] = T( 0 );
		result[3][2] = T( 0 );
		result[3][3] = T( 1 );
		return result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const Vec3<T> & s ) {
		scale( mat, s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const T & x, const T & y, const T & z ) {
		( *mat )[0] *= x;
		( *mat )[1] *= y;
		( *mat )[2] *= z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const Vec3<T> & s ) {
		return 	scale( mat, s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const T & x, const T & y, const T & z ) {
		return Mat4<T>( mat[0] * x, mat[1] * y, mat[2] * z, mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const T &  s ) {
		( *mat )[0] *= s;
		( *mat )[1] *= s;
		( *mat )[2] *= s;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & s ) {
		scale( mat, resultMat, s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z ) {
		( *resultMat )[0] = mat[0] * x;
		( *resultMat )[1] = mat[1] * y;
		( *resultMat )[2] = mat[2] * z;
		( *resultMat )[3] = mat[3];
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Vec2<T> & s ) {
		return scale( s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const T & x, const T & y ) {

		Mat4<T> result;
		result[0][0] = x;
		result[0][1] = T( 0 );
		result[0][2] = T( 0 );
		result[0][3] = T( 0 );

		result[1][0] = T( 0 );
		result[1][1] = y;
		result[1][2] = T( 0 );
		result[1][3] = T( 0 );

		result[2][0] = T( 0 );
		result[2][1] = T( 0 );
		result[2][2] = T( 1 );
		result[2][3] = T( 0 );

		result[3][0] = T( 0 );
		result[3][1] = T( 0 );
		result[3][2] = T( 0 );
		result[3][3] = T( 1 );
		return result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const Vec2<T> & s ) {
		scale( mat, s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( Mat4<T> * mat, const T & x, const T & y ) {
		( *mat )[0] *= x;
		( *mat )[1] *= y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const Vec2<T> & s ) {
		return 	scale( mat, s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scale( const Mat4<T> & mat, const T & x, const T & y ) {
		return Mat4<T>( mat[0] * x, mat[1] * y, mat[2], mat[3] );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & s ) {
		scale( mat, resultMat, s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scale( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y ) {
		( *resultMat )[0] = mat[0] * x;
		( *resultMat )[1] = mat[1] * y;
		( *resultMat )[2] = mat[2];
		( *resultMat )[3] = mat[3];
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Vec3<T> & v ) {
		return translate( v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const T & x, const T & y, const T & z ) {
		Mat4<T> result;
		result[0][0] = T( 1 );
		result[0][1] = T( 0 );
		result[0][2] = T( 0 );
		result[0][3] = T( 0 );

		result[1][0] = T( 0 );
		result[1][1] = T( 1 );
		result[1][2] = T( 0 );
		result[1][3] = T( 0 );

		result[2][0] = T( 0 );
		result[2][1] = T( 0 );
		result[2][2] = T( 1 );
		result[2][3] = T( 0 );

		result[3][0] = x;
		result[3][1] = y;
		result[3][2] = z;
		result[3][3] = T( 1 );
		return result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const Vec3<T> & v ) {
		translate( mat, v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const T & x, const T & y, const T & z ) {
		( *mat )[3] += ( *mat )[0] * x + ( *mat )[1] * y + ( *mat )[2] * z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const Vec3<T> & v ) {
		return translate( mat, v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const T & x, const T & y, const T & z ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] + mat[0] * x + mat[1] * y + mat[2] * z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v ) {
		translate( mat, resultMat, v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3] = mat[3] + mat[0] * x + mat[1] * y + mat[2] * z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Vec2<T> & v ) {
		return translate( v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const T & x, const T & y ) {
		Mat4<T> result;
		result[0][0] = T( 1 );
		result[0][1] = T( 0 );
		result[0][2] = T( 0 );
		result[0][3] = T( 0 );

		result[1][0] = T( 0 );
		result[1][1] = T( 1 );
		result[1][2] = T( 0 );
		result[1][3] = T( 0 );

		result[2][0] = T( 0 );
		result[2][1] = T( 0 );
		result[2][2] = T( 1 );
		result[2][3] = T( 0 );

		result[3][0] = x;
		result[3][1] = y;
		result[3][2] = T( 0 );
		result[3][3] = T( 1 );
		return result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const Vec2<T> & v ) {
		translate( mat, v.x, v.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( Mat4<T> * mat, const T & x, const T & y ) {
		( *mat )[3] += ( *mat )[0] * x + ( *mat )[1] * y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const Vec2<T> & v ) {
		return translate( mat, v.x, v.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translate( const Mat4<T> & mat, const T & x, const T & y ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] + mat[0] * x + mat[1] * y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v ) {
		translate( mat, resultMat, v.x, v.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translate( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3] = mat[3] + mat[0] * x + mat[1] * y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void scaleXInv( Mat4<T> * mat, const T & x ) {
		( *mat )[0] /= x;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleXInv( const Mat4<T> & mat, const T & x ) {
		return Mat4<T>( mat[0] / x, mat[1], mat[2], mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleYInv( Mat4<T> * mat, const T & y ) {
		( *mat )[1] /= y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleYInv( const Mat4<T> & mat, const T & y ) {
		return Mat4<T>( mat[0], mat[1] / y, mat[2], mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleZInv( Mat4<T> * mat, const T & z ) {
		( *mat )[2] /= z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleZInv( const Mat4<T> & mat, const T & z ) {
		return Mat4<T>( mat[0], mat[1], mat[2] / z, mat[3] );
	}
	template<typename T>
	void translateYInv( Mat4<T> * mat, const T & y ) {
		( *mat )[3] -= ( *mat )[1] * y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateYInv( const Mat4<T> & mat, const T & y ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] - mat[1] * y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateZInv( Mat4<T> * mat, const T & z ) {
		( *mat )[3] -= ( *mat )[2] * z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZInv( const Mat4<T> & mat, const T & z ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] - mat[2] * z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateXInv( Mat4<T> * mat, const T & x ) {
		( *mat )[3] -= ( *mat )[0] * x;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateXInv( const Mat4<T> & mat, const T & x ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] - mat[0] * x );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const Vec3<T> & s ) {
		scaleInv( mat, s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const T & x, const T & y, const T & z ) {
		( *mat )[0] /= x;
		( *mat )[1] /= y;
		( *mat )[2] /= z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const Vec3<T> & s ) {
		return scaleInv( mat, s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const T & x, const T & y, const T & z ) {
		return Mat4<T>( mat[0] / x, mat[1] / y, mat[2] / z, mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const T & s ) {
		( *mat )[0] /= s;
		( *mat )[1] /= s;
		( *mat )[2] /= s;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & s ) {
		scaleInv( mat, resultMat, s.x, s.y, s.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z ) {
		( *resultMat )[0] = mat[0] / x;
		( *resultMat )[1] = mat[1] / y;
		( *resultMat )[2] = mat[2] / z;
		( *resultMat )[3] = mat[3];
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const T & s ) {
		return Mat4<T>( mat[0] / s, mat[1] / s, mat[2] / s, mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & s ) {
		( *resultMat )[0] = mat[0] / s;
		( *resultMat )[1] = mat[1] / s;
		( *resultMat )[2] = mat[2] / s;
		( *resultMat )[3] = mat[3];
	}



	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const Vec2<T> & s ) {
		scaleInv( mat, s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( Mat4<T> * mat, const T & x, const T & y ) {
		( *mat )[0] /= x;
		( *mat )[1] /= y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const Vec2<T> & s ) {
		return scaleInv( mat, s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> scaleInv( const Mat4<T> & mat, const T & x, const T & y ) {
		return Mat4<T>( mat[0] / x, mat[1] / y, mat[2], mat[3] );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & s ) {
		scaleInv( mat, resultMat, s.x, s.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void scaleInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y ) {
		( *resultMat )[0] = mat[0] / x;
		( *resultMat )[1] = mat[1] / y;
		( *resultMat )[2] = mat[2];
		( *resultMat )[3] = mat[3];
	}




	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const Vec3<T> & v ) {
		translateInv( mat, v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const T & x, const T & y, const T & z ) {
		( *mat )[3] -= ( *mat )[0] * x + ( *mat )[1] * y + ( *mat )[2] * z;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const Vec3<T> & v ) {
		return translateInv( mat, v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const T & x, const T & y, const T & z ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] - mat[0] * x - mat[1] * y - mat[2] * z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v ) {
		translateInv( mat, resultMat, v.x, v.y, v.z );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3] = mat[3] - mat[0] * x - mat[1] * y - mat[2] * z;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const Vec2<T> & v ) {
		translateInv( mat, v.x, v.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( Mat4<T> * mat, const T & x, const T & y ) {
		( *mat )[3] -= ( *mat )[0] * x + ( *mat )[1] * y;
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const Vec2<T> & v ) {
		return translateInv( mat, v.x, v.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateInv( const Mat4<T> & mat, const T & x, const T & y ) {
		return Mat4<T>( mat[0], mat[1], mat[2], mat[3] - mat[0] * x - mat[1] * y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v ) {
		translateInv( mat, resultMat, v.x, v.y );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER void translateInv( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3] = mat[3] - mat[0] * x - mat[1] * y;
	}




	template<typename T>
	MATH_FUNC_QUALIFIER Mat3<T> getNormalMat( const Mat4<T> & m ) {
		Mat3<T> normalMat;
		normalMat[0][0] = ( m[1][1] * m[2][2] - m[1][2] * m[2][1] );
		normalMat[1][0] = ( m[0][2] * m[2][1] - m[0][1] * m[2][2] );
		normalMat[2][0] = ( m[0][1] * m[1][2] - m[0][2] * m[1][1] );
		normalMat[0][1] = ( m[1][2] * m[2][0] - m[1][0] * m[2][2] );
		normalMat[1][1] = ( m[0][0] * m[2][2] - m[0][2] * m[2][0] );
		normalMat[2][1] = ( m[0][2] * m[1][0] - m[0][0] * m[1][2] );
		normalMat[0][2] = ( m[1][0] * m[2][1] - m[1][1] * m[2][0] );
		normalMat[1][2] = ( m[0][1] * m[2][0] - m[0][0] * m[2][1] );
		normalMat[2][2] = ( m[0][0] * m[1][1] - m[0][1] * m[1][0] );
		return normalMat;
	}





	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> perspective( const T & fovy, const T & aspect, const T & zNear, const T & zFar ) {
		T range = tan( radians( fovy / T( 2 ) ) ) * zNear;
		T left = -range * aspect;
		T right = range * aspect;
		T bottom = -range;
		T top = range;

		Mat4<T> Result( T( 0 ) );
		Result[0][0] = ( T( 2 ) * zNear ) / ( right - left );
		Result[1][1] = ( T( 2 ) * zNear ) / ( top - bottom );
		Result[2][2] = -( zFar + zNear ) / ( zFar - zNear );
		Result[2][3] = -T( 1 );
		Result[3][2] = -( T( 2 ) * zFar * zNear ) / ( zFar - zNear );
		return Result;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAt( const Vec3<T> & position, const Vec3<T> & target ) {
		return lookAtNormalized( position, normalize( target - position ) );
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAtNormalized( const Vec3<T> & position, const Vec3<T> & f ) {
		Vec3<T> s = normalize( Vec3<T>( -f.z, T( 0 ), f.x ) );
		Vec3<T> u = cross( s, f );


		Mat4<T> Result;
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[3][0] = T( 0 );

		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[3][1] = T( 0 );

		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][2] = T( 0 );

		Result[0][3] = T( 0 );
		Result[1][3] = T( 0 );
		Result[2][3] = T( 0 );
		Result[3][3] = T( 1 );

		return translate( Result, -position );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAt( const Vec3<T> & position, const Vec3<T> & target, const Vec3<T> & up ) {
		return lookAtNormalized( position, normalize( target - position ), up );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> lookAtNormalized( const Vec3<T> & position, const Vec3<T> & f, const Vec3<T> & up ) {
		Vec3<T> s = normalize( cross( f, up ) );
		Vec3<T> u = cross( s, f );

		Mat4<T> Result;
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[3][0] = T( 0 );

		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[3][1] = T( 0 );

		Result[0][2] = -f.x;
		Result[1][2] = -f.y;
		Result[2][2] = -f.z;
		Result[3][2] = T( 0 );

		Result[0][3] = T( 0 );
		Result[1][3] = T( 0 );
		Result[2][3] = T( 0 );
		Result[3][3] = T( 1 );

		return translate( Result, -position );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> ortho(
		T const & left,
		T const & right,
		T const & bottom,
		T const & top,
		T const & zNear,
		T const & zFar
	) {


		Mat4<T> Result;

		Result[0][0] = T( 2 ) / ( right - left );
		Result[0][1] = T( 0 );
		Result[0][2] = T( 0 );
		Result[0][3] = T( 0 );

		Result[1][0] = T( 0 );
		Result[1][1] = T( 2 ) / ( top - bottom );
		Result[1][2] = T( 0 );
		Result[1][3] = T( 0 );

		Result[2][0] = T( 0 );
		Result[2][1] = T( 0 );
		Result[2][2] = -T( 2 ) / ( zFar - zNear );
		Result[2][3] = T( 0 );

		Result[3][0] = -( right + left ) / ( right - left );
		Result[3][1] = -( top + bottom ) / ( top - bottom );
		Result[3][2] = -( zFar + zNear ) / ( zFar - zNear );
		Result[3][3] = T( 1 );
		return Result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> ortho( const T & left, const T & right, const T & bottom, const T & top ) {
		Mat4<T> Result;
		Result[0][0] = T( 2 ) / ( right - left );
		Result[0][1] = T( 0 );
		Result[0][2] = T( 0 );
		Result[0][3] = T( 0 );

		Result[1][0] = T( 0 );
		Result[1][1] = T( 2 ) / ( top - bottom );
		Result[1][2] = T( 0 );
		Result[1][3] = T( 0 );

		Result[2][0] = T( 0 );
		Result[2][1] = T( 0 );
		Result[2][2] = -T( 1 );
		Result[2][3] = T( 0 );

		Result[3][0] = -( right + left ) / ( right - left );
		Result[3][1] = -( top + bottom ) / ( top - bottom );
		Result[3][2] = T( 0 );
		Result[3][3] = T( 1 );
		return Result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const Mat4<T> & m, const T & angle, const Vec3<T> & v ) {
		return rotateNormalized( m, angle, normalize( v ) );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const Mat4<T> & m, const T & angle, const Vec3<T> & axis ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );

		Vec3<T> temp = ( T( 1 ) - c ) * axis;

		const T rotate00 = c + temp[0] * axis[0];
		const T rotate01 = temp[0] * axis[1] + s * axis[2];
		const T rotate02 = temp[0] * axis[2] - s * axis[1];

		const T rotate10 = temp[1] * axis[0] - s * axis[2];
		const T rotate11 = c + temp[1] * axis[1];
		const T rotate12 = temp[1] * axis[2] + s * axis[0];

		const T rotate20 = temp[2] * axis[0] + s * axis[1];
		const T rotate21 = temp[2] * axis[1] - s * axis[0];
		const T rotate22 = c + temp[2] * axis[2];

		Mat4<T> Result;
		Result[0] = m[0] * rotate00 + m[1] * rotate01 + m[2] * rotate02;
		Result[1] = m[0] * rotate10 + m[1] * rotate11 + m[2] * rotate12;
		Result[2] = m[0] * rotate20 + m[1] * rotate21 + m[2] * rotate22;
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( Mat4<T> * m, const T & angle, const Vec3<T> & v ) {
		return rotateNormalized( m, angle, normalize( v ) );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void rotateNormalized( Mat4<T> * m, const T & angle, const Vec3<T> & axis ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );

		Vec3<T> temp = ( T( 1 ) - c ) * axis;

		const T rotate00 = c + temp[0] * axis[0];
		const T rotate01 = temp[0] * axis[1] + s * axis[2];
		const T rotate02 = temp[0] * axis[2] - s * axis[1];

		const T rotate10 = temp[1] * axis[0] - s * axis[2];
		const T rotate11 = c + temp[1] * axis[1];
		const T rotate12 = temp[1] * axis[2] + s * axis[0];

		const T rotate20 = temp[2] * axis[0] + s * axis[1];
		const T rotate21 = temp[2] * axis[1] - s * axis[0];
		const T rotate22 = c + temp[2] * axis[2];

		Vec4<T> column0 = ( *m )[0];
		Vec4<T> column1 = ( *m )[1];
		Vec4<T> column2 = ( *m )[2];

		( *m )[0] = column0 * rotate00 + column1 * rotate01 + column2 * rotate02;
		( *m )[1] = column0 * rotate10 + column1 * rotate11 + column2 * rotate12;
		( *m )[2] = column0 * rotate20 + column1 * rotate21 + column2 * rotate22;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( const Mat4<T> & m, Mat4<T> * resultMat, const T & angle, const Vec3<T> & v ) {
		return rotateNormalized( m, resultMat, angle, normalize( v ) );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void rotateNormalized( const Mat4<T> & m, Mat4<T> * resultMat, const T & angle, const Vec3<T> & axis ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );

		Vec3<T> temp = ( T( 1 ) - c ) * axis;

		const T rotate00 = c + temp[0] * axis[0];
		const T rotate01 = temp[0] * axis[1] + s * axis[2];
		const T rotate02 = temp[0] * axis[2] - s * axis[1];

		const T rotate10 = temp[1] * axis[0] - s * axis[2];
		const T rotate11 = c + temp[1] * axis[1];
		const T rotate12 = temp[1] * axis[2] + s * axis[0];

		const T rotate20 = temp[2] * axis[0] + s * axis[1];
		const T rotate21 = temp[2] * axis[1] - s * axis[0];
		const T rotate22 = c + temp[2] * axis[2];

		( *resultMat )[0] = m[0] * rotate00 + m[1] * rotate01 + m[2] * rotate02;
		( *resultMat )[1] = m[0] * rotate10 + m[1] * rotate11 + m[2] * rotate12;
		( *resultMat )[2] = m[0] * rotate20 + m[1] * rotate21 + m[2] * rotate22;
		( *resultMat )[3] = m[3];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const T & angle, const Vec3<T> & v ) {
		return rotateNormalized( angle, normalize( v ) );
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const T & angle, const Vec3<T> & axis ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );


		Vec3<T> temp = ( T( 1 ) - c ) * axis;

		const T rotate00 = c + temp[0] * axis[0];
		const T rotate01 = temp[0] * axis[1] + s * axis[2];
		const T rotate02 = temp[0] * axis[2] - s * axis[1];

		const T rotate10 = temp[1] * axis[0] - s * axis[2];
		const T rotate11 = c + temp[1] * axis[1];
		const T rotate12 = temp[1] * axis[2] + s * axis[0];

		const T rotate20 = temp[2] * axis[0] + s * axis[1];
		const T rotate21 = temp[2] * axis[1] - s * axis[0];
		const T rotate22 = c + temp[2] * axis[2];

		Mat4<T> Result;
		Result[0][0] = rotate00;
		Result[0][1] = rotate01;
		Result[0][2] = rotate02;
		Result[0][3] = T( 0 );

		Result[1][0] = rotate10;
		Result[1][1] = rotate11;
		Result[1][2] = rotate12;
		Result[1][3] = T( 0 );

		Result[2][0] = rotate20;
		Result[2][1] = rotate21;
		Result[2][2] = rotate22;
		Result[2][3] = T( 0 );

		Result[3][0] = T( 0 );
		Result[3][1] = T( 0 );
		Result[3][2] = T( 0 );
		Result[3][3] = T( 1 );
		return Result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const Mat4<T> & m, const T & angle ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );
		const T zTmp = T( 1 ) - c;

		Mat4<T> Result;
		Result[0] = m[0] * c + m[1] * s;
		Result[1] = m[0] * s + m[1] * c;
		Result[2] = m[2] * ( c + zTmp );
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( Mat4<T> * m, const T & angle ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );
		const T zTmp = T( 1 ) - c;

		( *m )[0] = ( *m )[0] * c + ( *m )[1] * s;
		( *m )[1] = ( *m )[0] * s + ( *m )[1] * c;
		( *m )[2] = ( *m )[2] * ( c + zTmp );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void rotate( const Mat4<T> & m, Mat4<T> * resultMat, const T & angle ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );
		const T zTmp = T( 1 ) - c;

		( *resultMat )[0] = ( *m )[0] * c + ( *m )[1] * s;
		( *resultMat )[1] = ( *m )[0] * s + ( *m )[1] * c;
		( *resultMat )[2] = ( *m )[2] * ( c + zTmp );
		( *resultMat )[3] = ( *m )[3];
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotate( const T & angle ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );
		const T zTmp = T( 1 ) - c;

		Mat4<T> result;
		result[0][0] = c;
		result[0][1] = s;
		result[0][2] = T( 0 );
		result[0][3] = T( 0 );

		result[1][0] = s;
		result[1][1] = c;
		result[1][2] = T( 0 );
		result[1][3] = T( 0 );

		result[2][0] = T( 0 );
		result[2][1] = T( 0 );
		result[2][2] = c + zTmp;
		result[2][3] = T( 0 );

		result[3][0] = T( 0 );
		result[3][1] = T( 0 );
		result[3][2] = T( 0 );
		result[3][3] = T( 1 );
		return result;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> rotateNormalized( const Mat4<T> & m, const T & angle, const T & x, const T & y, const T & z ) {
		const T a = radians( angle );
		const T c = cos( a );
		const T s = sin( a );
		const T cInv = T( 1 ) - c;

		Vec3<T> temp;
		temp[0] = cInv * x;
		temp[1] = cInv * y;
		temp[2] = cInv * z;

		const T rotate00 = c + temp[0] * x;
		const T rotate01 = temp[0] * y + s * z;
		const T rotate02 = temp[0] * z - s * y;

		const T rotate10 = temp[1] * x - s * z;
		const T rotate11 = c + temp[1] * y;
		const T rotate12 = temp[1] * z + s * x;

		const T rotate20 = temp[2] * x + s * y;
		const T rotate21 = temp[2] * y - s * x;
		const T rotate22 = c + temp[2] * z;

		Mat4<T> Result;
		Result[0] = m[0] * rotate00 + m[1] * rotate01 + m[2] * rotate02;
		Result[1] = m[0] * rotate10 + m[1] * rotate11 + m[2] * rotate12;
		Result[2] = m[0] * rotate20 + m[1] * rotate21 + m[2] * rotate22;
		Result[3] = m[3];
		return Result;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> right( const Vec3<T> & v ) {
		return normalize( Vec3<T>( -v.z, T( 0 ), v.x ) );
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3][0] = x;
		( *resultMat )[3][1] = y;
		( *resultMat )[3][2] = mat[3][2];
		( *resultMat )[3][3] = mat[3][3];
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3][0] = v.x;
		( *resultMat )[3][1] = v.y;
		( *resultMat )[3][2] = mat[3][2];
		( *resultMat )[3][3] = mat[3][3];
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const T & x, const T & y ) {
		Mat4<T> newMat( mat );
		newMat[0] = mat[0];
		newMat[1] = mat[1];
		newMat[2] = mat[2];
		newMat[3][0] = x;
		newMat[3][1] = y;
		newMat[3][2] = mat[3][2];
		newMat[3][3] = mat[3][3];
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const Vec2<T> & v ) {
		Mat4<T> newMat( mat );
		newMat[0] = mat[0];
		newMat[1] = mat[1];
		newMat[2] = mat[2];
		newMat[3][0] = v.x;
		newMat[3][1] = v.y;
		newMat[3][2] = mat[3][2];
		newMat[3][3] = mat[3][3];
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const T & x, const T & y ) {
		( *mat )[3][0] = x;
		( *mat )[3][1] = y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const Vec2<T> & v ) {
		( *mat )[3][0] = v.x;
		( *mat )[3][1] = v.y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3][0] = x;
		( *resultMat )[3][1] = y;
		( *resultMat )[3][2] = z;
		( *resultMat )[3][3] = mat[3][3];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v ) {
		( *resultMat )[0] = mat[0];
		( *resultMat )[1] = mat[1];
		( *resultMat )[2] = mat[2];
		( *resultMat )[3][0] = v.x;
		( *resultMat )[3][1] = v.y;
		( *resultMat )[3][2] = v.z;
		( *resultMat )[3][3] = mat[3][3];

	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const T & x, const T & y, const T & z ) {
		Mat4<T> newMat( mat );
		newMat[0] = mat[0];
		newMat[1] = mat[1];
		newMat[2] = mat[2];
		newMat[3][0] = x;
		newMat[3][1] = y;
		newMat[3][2] = z;
		newMat[3][3] = mat[3][3];
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPosition( const Mat4<T> & mat, const Vec3<T> & v ) {
		Mat4<T> newMat( mat );
		newMat[3][0] += v.x;
		newMat[3][1] += v.y;
		newMat[3][2] += v.z;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const T & x, const T & y, const T & z ) {
		( *mat )[3][0] = x;
		( *mat )[3][1] = y;
		( *mat )[3][2] = z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionX( const Mat4<T> & mat, const T & x ) {
		Mat4<T> newMat( mat );
		newMat[0] = mat[0];
		newMat[1] = mat[1];
		newMat[2] = mat[2];
		newMat[3][0] = x;
		newMat[3][1] = mat[3][1];
		newMat[3][2] = mat[3][2];
		newMat[3][3] = mat[3][3];
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionY( const Mat4<T> & mat, const T & y ) {
		Mat4<T> newMat( mat );
		newMat[0] = mat[0];
		newMat[1] = mat[1];
		newMat[2] = mat[2];
		newMat[3][0] = mat[3][0];
		newMat[3][1] = y;
		newMat[3][2] = mat[3][2];
		newMat[3][3] = mat[3][3];
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> setPositionZ( const Mat4<T> & mat, const T & z ) {
		Mat4<T> newMat;
		newMat[0] = mat[0];
		newMat[1] = mat[1];
		newMat[2] = mat[2];
		newMat[3][0] = mat[3][0];
		newMat[3][1] = mat[3][1];
		newMat[3][2] = z;
		newMat[3][3] = mat[3][3];
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionX( Mat4<T> * mat, const T & x ) {
		( *mat )[3][0] = x;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionY( Mat4<T> * mat, const T & y ) {
		( *mat )[3][1] = y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPositionZ( Mat4<T> * mat, const T & z ) {
		( *mat )[3][2] = z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void setPosition( Mat4<T> * mat, const Vec3<T> & v ) {
		( *mat )[3][0] = v.x;
		( *mat )[3][1] = v.y;
		( *mat )[3][2] = v.z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y ) {
		*resultMat = mat;
		( *resultMat )[3][0] += x;
		( *resultMat )[3][1] += y;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec2<T> & v ) {
		*resultMat = mat;
		( *resultMat )[3][0] += v.x;
		( *resultMat )[3][1] += v.y;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const T & x, const T & y ) {
		Mat4<T> newMat( mat );
		newMat[3][0] += x;
		newMat[3][1] += y;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const Vec2<T> & v ) {
		Mat4<T> newMat( mat );
		newMat[3][0] += v.x;
		newMat[3][1] += v.y;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const T & x, const T & y ) {
		( *mat )[3][0] += x;
		( *mat )[3][1] += y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const Vec2<T> & v ) {
		( *mat )[3][0] += v.x;
		( *mat )[3][1] += v.y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const T & x, const T & y, const T & z ) {
		*resultMat = mat;
		( *resultMat )[3][0] += x;
		( *resultMat )[3][1] += y;
		( *resultMat )[3][2] += z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( const Mat4<T> & mat, Mat4<T> * resultMat, const Vec3<T> & v ) {
		*resultMat = mat;
		( *resultMat )[3][0] += v.x;
		( *resultMat )[3][1] += v.y;
		( *resultMat )[3][2] += v.z;
	}

	template<typename T> MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const T & x, const T & y, const T & z ) {
		Mat4<T> newMat( mat );
		newMat[3][0] += x;
		newMat[3][1] += y;
		newMat[3][2] += z;
		return newMat;
	}

	template<typename T> MATH_FUNC_QUALIFIER Mat4<T> translateWS( const Mat4<T> & mat, const Vec3<T> & v ) {
		Mat4<T> newMat( mat );
		newMat[3][0] += v.x;
		newMat[3][1] += v.y;
		newMat[3][2] += v.z;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const T & x, const T & y, const T & z ) {
		( *mat )[3][0] += x;
		( *mat )[3][1] += y;
		( *mat )[3][2] += z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateXWS( const Mat4<T> & mat, const T & x ) {
		Mat4<T> newMat( mat );
		newMat[3][0] += x;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateYWS( const Mat4<T> & mat, const T & y ) {
		Mat4<T> newMat( mat );
		newMat[3][1] += y;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> translateZWS( const Mat4<T> & mat, const T & z ) {
		Mat4<T> newMat( mat );
		newMat[3][2] += z;
		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateXWS( Mat4<T> * mat, const T & x ) {
		( *mat )[3][0] += v.x;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateYWS( Mat4<T> * mat, const T & y ) {
		( *mat )[3][1] += v.y;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateZWS( Mat4<T> * mat, const T & y ) {
		( *mat )[3][2] += v.z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER void translateWS( Mat4<T> * mat, const Vec3<T> & v ) {
		( *mat )[3][0] += v.x;
		( *mat )[3][1] += v.y;
		( *mat )[3][2] += v.z;
	}

}
