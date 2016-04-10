namespace Math {	


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(const T * datas){
		memcpy(this -> column, datas, sizeof(T) * 16);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(const Mat4<T> & m) {
		*this = m;
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(const Mat4<U> & m) {
		*this = m;
	}



	template<typename T >
	MATH_FUNC_QUALIFIER const Vec4<T> & Mat4<T>::operator[](unsigned int index) const{
		return this -> column[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Mat4<T>::operator[](unsigned int index){
		return this -> column[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(const colType & col0, const colType & col1, const colType & col2, const colType & col3){
		this -> column[0] = col0;
		this -> column[1] = col1;
		this -> column[2] = col2;
		this -> column[3] = col3;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T Mat4<T>::getDeterminant() const {
		const T & S00 = this -> column[0][0];
		const T & S01 = this -> column[0][1];
		const T & S02 = this -> column[0][2];
		const T & S03 = this -> column[0][3];

		const T & S10 = this -> column[1][0];
		const T & S11 = this -> column[1][1];
		const T & S12 = this -> column[1][2];
		const T & S13 = this -> column[1][3];

		const T & S20 = this -> column[2][0];
		const T & S21 = this -> column[2][1];
		const T & S22 = this -> column[2][2];
		const T & S23 = this -> column[2][3];

		const T & S30 = this -> column[3][0];
		const T & S31 = this -> column[3][1];
		const T & S32 = this -> column[3][2];
		const T & S33 = this -> column[3][3];

		//Compute all subfactors for faster computing
		const T & subFactor00 = S22 * S33 - S32 * S23;
		const T & subFactor01 = S21 * S33 - S31 * S23;
		const T & subFactor02 = S21 * S32 - S31 * S22;
		const T & subFactor03 = S20 * S33 - S30 * S23;
		const T & subFactor04 = S20 * S32 - S30 * S22;
		const T & subFactor05 = S20 * S31 - S30 * S21;


		return S00 * ( S11 * subFactor00 - S12 * subFactor01 + S13 * subFactor02 )
			+ S01 * ( S10 * subFactor00 + S12 * subFactor03 - S13 * subFactor04 )
			+ S02 * ( S10 * subFactor01 - S11 * subFactor03 + S13 * subFactor05 )
			+ S03 * ( S10 * subFactor02 + S11 * subFactor04 - S12 * subFactor05 );
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> Mat4<T>::inverse() const{
		const T & S00 = this -> column[0][0];
		const T & S01 = this -> column[0][1];
		const T & S02 = this -> column[0][2];
		const T & S03 = this -> column[0][3];

		const T & S10 = this -> column[1][0];
		const T & S11 = this -> column[1][1];
		const T & S12 = this -> column[1][2];
		const T & S13 = this -> column[1][3];

		const T & S20 = this -> column[2][0];
		const T & S21 = this -> column[2][1];
		const T & S22 = this -> column[2][2];
		const T & S23 = this -> column[2][3];

		const T & S30 = this -> column[3][0];
		const T & S31 = this -> column[3][1];
		const T & S32 = this -> column[3][2];
		const T & S33 = this -> column[3][3];


		//Compute all subfactors for faster computing
		const T & subFactor00 = S22 * S33 - S32 * S23;
		const T & subFactor01 = S21 * S33 - S31 * S23;
		const T & subFactor02 = S21 * S32 - S31 * S22;
		const T & subFactor03 = S20 * S33 - S30 * S23;
		const T & subFactor04 = S20 * S32 - S30 * S22;
		const T & subFactor05 = S20 * S31 - S30 * S21;
		const T & subFactor06 = S12 * S33 - S32 * S13;
		const T & subFactor07 = S11 * S33 - S31 * S13;
		const T & subFactor08 = S11 * S32 - S31 * S12;
		const T & subFactor09 = S10 * S33 - S30 * S13;
		const T & subFactor10 = S10 * S32 - S30 * S12;
		const T & subFactor11 = S11 * S33 - S31 * S13;
		const T & subFactor12 = S10 * S31 - S30 * S11;
		const T & subFactor13 = S12 * S23 - S22 * S13;
		const T & subFactor14 = S11 * S23 - S21 * S13;
		const T & subFactor15 = S11 * S22 - S21 * S12;
		const T & subFactor16 = S10 * S23 - S20 * S13;
		const T & subFactor17 = S10 * S22 - S20 * S12;
		const T & subFactor18 = S10 * S21 - S20 * S11;

		Mat4<T> inverse(
			+ S11 * subFactor00 - S12 * subFactor01 + S13 * subFactor02,
			- S10 * subFactor00 + S12 * subFactor03 - S13 * subFactor04,
			+ S10 * subFactor01 - S11 * subFactor03 + S13 * subFactor05,
			- S10 * subFactor02 + S11 * subFactor04 - S12 * subFactor05,

			- S01 * subFactor00 + S02 * subFactor01 - S03 * subFactor02,
			+ S00 * subFactor00 - S02 * subFactor03 + S03 * subFactor04,
			- S00 * subFactor01 + S01 * subFactor03 - S03 * subFactor05,
			+ S00 * subFactor02 - S01 * subFactor04 + S02 * subFactor05,

			+ S01 * subFactor06 - S02 * subFactor07 + S03 * subFactor08,
			- S00 * subFactor06 + S02 * subFactor09 - S03 * subFactor10,
			+ S00 * subFactor11 - S01 * subFactor09 + S03 * subFactor12,
			- S00 * subFactor08 + S01 * subFactor10 - S02 * subFactor12,

			- S01 * subFactor13 + S02 * subFactor14 - S03 * subFactor15,
			+ S00 * subFactor13 - S02 * subFactor16 + S03 * subFactor17,
			- S00 * subFactor14 + S01 * subFactor16 - S03 * subFactor18,
			+ S00 * subFactor15 - S01 * subFactor17 + S02 * subFactor18);

		T determinant = 
					+ S00 * inverse[0][0]
					+ S01 * inverse[1][0]
					+ S02 * inverse[2][0]
					+ S03 * inverse[3][0];

		inverse /= determinant;
		return inverse;
	}

	/************************************************************************/
	/* Multiply                                                             */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator*=(const Mat4<T> & m){
		return (*this = *this * m);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator*=(const colType & v){
		this -> column[0] *= v.x;
		this -> column[1] *= v.y;
		this -> column[2] *= v.z;
		this -> column[3] *= v.w;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator*=(const T & v){
		this -> column[0] *= v;
		this -> column[1] *= v;
		this -> column[2] *= v;
		this -> column[3] *= v;
		return *this;
	}


	/************************************************************************/
	/* Divide                                                               */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator/=(const Mat4<T> & m){
		return (*this = *this / m);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator/=(const colType & v){
		this -> column[0] /= v.x;
		this -> column[1] /= v.y;
		this -> column[2] /= v.z;
		this -> column[3] /= v.w;
		return *this;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator/=(const T & v){
		this -> column[0] /= v;
		this -> column[1] /= v;
		this -> column[2] /= v;
		this -> column[3] /= v;
		return *this;
	}


	/************************************************************************/
	/* Add                                                                  */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator+=(const Mat4<T> & m){
		this -> column[0] += m[0];
		this -> column[1] += m[1];
		this -> column[2] += m[2];
		this -> column[3] += m[3];
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator+=(const colType & v){
		this -> column[0] += v.x;
		this -> column[1] += v.y;
		this -> column[2] += v.z;
		this -> column[3] += v.w;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator+=(const T & v){
		this -> column[0] += v;
		this -> column[1] += v;
		this -> column[2] += v;
		this -> column[3] += v;
		return *this;
	}



	/************************************************************************/
	/* Minus                                                                */
	/************************************************************************/

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator-=(const Mat4<T> & m){
		this -> column[0] -= m[0];
		this -> column[1] -= m[1];
		this -> column[2] -= m[2];
		this -> column[3] -= m[3];
		return *this;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator-=(const colType & v){
		this -> column[0] -= v.x;
		this -> column[1] -= v.y;
		this -> column[2] -= v.z;
		this -> column[3] -= v.w;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator-=(const T & v){
		this -> column[0] -= v;
		this -> column[1] -= v;
		this -> column[2] -= v;
		this -> column[3] -= v;
		return *this;
	}

	/************************************************************************/
	/* Binary Shift                                                         */
	/************************************************************************/


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator>>=(const Mat4<T> & m){
		this -> column[0] >>= m[0];
		this -> column[1] >>= m[1];
		this -> column[2] >>= m[2];
		this -> column[3] >>= m[3];
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator>>=(const T & v){
		this -> column[0] >>= v;
		this -> column[1] >>= v;
		this -> column[2] >>= v;
		this -> column[3] >>= v;
		return *this;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator<<=(const Mat4<T> & m){
		this -> column[0] <<= m[0];
		this -> column[1] <<= m[1];
		this -> column[2] <<= m[2];
		this -> column[3] <<= m[2];
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator<<=(const T & v){
		this -> column[0] <<= v;
		this -> column[1] <<= v;
		this -> column[2] <<= v;
		this -> column[3] <<= v;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator++(){
		this -> column[0]++;
		this -> column[1]++;
		this -> column[2]++;
		this -> column[3]++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator--(){
		this -> column[0]--;
		this -> column[1]--;
		this -> column[2]--;
		this -> column[3]--;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator=(const Mat4<T> & m){
		this -> column[0] = m[0];
		this -> column[1] = m[1];
		this -> column[2] = m[2];
		this -> column[3] = m[3];
		//memcpy(this, &m, sizeof(m));
		return *this;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator=(const Mat4<U> & m) {
		this -> column[0] = m[0];
		this -> column[1] = m[1];
		this -> column[2] = m[2];
		this -> column[3] = m[3];
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> & Mat4<T>::operator=(const T & v){
		this -> column[0] = v;
		this -> column[1] = v;
		this -> column[2] = v;
		this -> column[3] = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Mat4<T>::operator==(const Mat4<T> & m) const{
		return _logicalOperatorAND(Logical::equal<colType>(), m);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Mat4<T>::operator!=(const Mat4<T> & m) const{
		return _logicalOperatorOR(Logical::notEqual<colType>(), m);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Mat4<T>::operator<(const Mat4<T> & m) const{
		return _logicalOperatorAND(Logical::less<colType>(), m);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Mat4<T>::operator<=(const Mat4<T> & m) const{
		return _logicalOperatorAND(Logical::lessEqual<colType>(), m);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Mat4<T>::operator>(const Mat4<T> & m) const{
		return _logicalOperatorAND(Logical::greater<colType>(), m);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Mat4<T>::operator>=(const Mat4<T> & m) const{
		return _logicalOperatorAND(Logical::greaterEqual<colType>(), m);
	}


	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Mat4<T>::_logicalOperatorOR(Compare func, const Mat4<T> & m) const{
		return func(this -> column[0], m[0]) || func(this -> column[1], m[1]) || func(this -> column[2], m[2]) || func(this -> column[3], m[3]);
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Mat4<T>::_logicalOperatorAND(Compare func, const Mat4<T> & m) const{
		return func(this -> column[0], m[0]) && func(this -> column[1], m[1]) && func(this -> column[2], m[2]) && func(this -> column[3], m[3]);
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(const T & v){
		this -> column[0].x = v;
		this -> column[0].y = T(0);
		this -> column[0].z = T(0);
		this -> column[0].w = T(0);

		this -> column[1].x = T(0);
		this -> column[1].y = v;
		this -> column[1].z = T(0);
		this -> column[1].w = T(0);

		this -> column[2].x = T(0);
		this -> column[2].y = T(0);
		this -> column[2].z = v;
		this -> column[2].w = T(0);

		this -> column[3].x = T(0);
		this -> column[3].y = T(0);
		this -> column[3].z = T(0);
		this -> column[3].w = v;
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(const T & v11, const T & v21, const T & v31, const T & v41,
				  const T & v12, const T & v22, const T & v32, const T & v42,
				  const T & v13, const T & v23, const T & v33, const T & v43,
				  const T & v14, const T & v24, const T & v34, const T & v44 ){
					  this -> column[0].x = v11;
					  this -> column[0].y = v12;
					  this -> column[0].z = v13;
					  this -> column[0].w = v14;

					  this -> column[1].x = v21;
					  this -> column[1].y = v22;
					  this -> column[1].z = v23;
					  this -> column[1].w = v24;

					  this -> column[2].x = v31;
					  this -> column[2].y = v32;
					  this -> column[2].z = v33;
					  this -> column[2].w = v34;

					  this -> column[3].x = v41;
					  this -> column[3].y = v42;
					  this -> column[3].z = v43;
					  this -> column[3].w = v44;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T>::Mat4(void){

	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*(const Mat4<T> & m1, const Mat4<T> & m2){

		Mat4<T> newMat;



		newMat[0].x = m1[0].x * m2[0].x + m1[1].x * m2[0].y + m1[2].x * m2[0].z + m1[3].x * m2[0].w;
		newMat[0].y = m1[0].y * m2[0].x + m1[1].y * m2[0].y + m1[2].y * m2[0].z + m1[3].y * m2[0].w;
		newMat[0].z = m1[0].z * m2[0].x + m1[1].z * m2[0].y + m1[2].z * m2[0].z + m1[3].z * m2[0].w;
		newMat[0].w = m1[0].w * m2[0].x + m1[1].w * m2[0].y + m1[2].w * m2[0].z + m1[3].w * m2[0].w;

		newMat[1].x = m1[0].x * m2[1].x + m1[1].x * m2[1].y + m1[2].x * m2[1].z + m1[3].x * m2[1].w;
		newMat[1].y = m1[0].y * m2[1].x + m1[1].y * m2[1].y + m1[2].y * m2[1].z + m1[3].y * m2[1].w;
		newMat[1].z = m1[0].z * m2[1].x + m1[1].z * m2[1].y + m1[2].z * m2[1].z + m1[3].z * m2[1].w;
		newMat[1].w = m1[0].w * m2[1].x + m1[1].w * m2[1].y + m1[2].w * m2[1].z + m1[3].w * m2[1].w;

		newMat[2].x = m1[0].x * m2[2].x + m1[1].x * m2[2].y + m1[2].x * m2[2].z + m1[3].x * m2[2].w;
		newMat[2].y = m1[0].y * m2[2].x + m1[1].y * m2[2].y + m1[2].y * m2[2].z + m1[3].y * m2[2].w;
		newMat[2].z = m1[0].z * m2[2].x + m1[1].z * m2[2].y + m1[2].z * m2[2].z + m1[3].z * m2[2].w;
		newMat[2].w = m1[0].w * m2[2].x + m1[1].w * m2[2].y + m1[2].w * m2[2].z + m1[3].w * m2[2].w;

		newMat[3].x = m1[0].x * m2[3].x + m1[1].x * m2[3].y + m1[2].x * m2[3].z + m1[3].x * m2[3].w;
		newMat[3].y = m1[0].y * m2[3].x + m1[1].y * m2[3].y + m1[2].y * m2[3].z + m1[3].y * m2[3].w;
		newMat[3].z = m1[0].z * m2[3].x + m1[1].z * m2[3].y + m1[2].z * m2[3].z + m1[3].z * m2[3].w;
		newMat[3].w = m1[0].w * m2[3].x + m1[1].w * m2[3].y + m1[2].w * m2[3].z + m1[3].w * m2[3].w;







		return newMat;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*(const Mat4<T> & m, const T & v){
		return Mat4<T>(m[0] * v, m[1] * v, m[2] * v, m[3] * v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator*(const T & v, const Mat4<T> & m){
		return Mat4<T>(v * m[0], v * m[1], v * m[2], v * m[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::colType operator*(const Mat4<T> & m, const typename Mat4<T>::colType & v){
		return typename Mat4<T>::colType(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::colType operator*(const Mat4<T> & m, const typename Mat3<T>::colType & v){
		return typename Mat4<T>::colType(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0],
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1],
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2],
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER typename Mat4<T>::colType operator*(const typename Mat4<T>::colType & v, const Mat4<T> & m){
		return typename Mat4<T>::colType(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/(const Mat4<T> & m1, const Mat4<T> & m2){
		return m1 * m2.inverse();
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/(const Mat4<T> & m, const T & v){
		return Mat4<T>(m[0] / v, m[1] / v, m[2] / v, m[3] / v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator/(const T & v, const Mat4<T> & m){
		return Mat4<T>(v / m[0], v / m[1], v / m[2], v / m[3]);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+(const Mat4<T> & m1, const Mat4<T> & m2){
		return Mat4<T>(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+(const Mat4<T> & m, const T & v){
		return Mat4<T>(m[0] + v, m[1] + v, m[2] + v, m[3] + v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator+(const T & v, const Mat4<T> & m){
		return Mat4<T>(v + m[0], v + m[1], v + m[2], v + m[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-(const Mat4<T> & m1, const Mat4<T> & m2){
		return Mat4<T>(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-(const Mat4<T> & m, const T & v){
		return Mat4<T>(m[0] - v, m[1] - v, m[2] - v, m[3] - v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator-(const T & v, const Mat4<T> & m){
		return Mat4<T>(v - m[0], v - m[1], v - m[2], v - m[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator>>(const Mat4<T> & m1, const Mat4<T> & m2){
		return Mat4<T>(m1[0] >> m2[0], m1[1] >> m2[1], m1[2] >> m2[2], m1[3] >> m2[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator>>(const Mat4<T> & m, const T & v){
		return Mat4<T>(m[0] >> v, m[1] >> v, m[2] >> v, m[3] >> v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator>>(const T & v, const Mat4<T> & m){
		return Mat4<T>(v >> m[0], v >> m[1], v >> m[2], v >> m[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<(const Mat4<T> & m1, const Mat4<T> & m2){
		return Mat4<T>(m1[0] << m2[0], m1[1] << m2[1], m1[2] << m2[2], m1[3] << m2[3]);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<(const Mat4<T> & m, const T & v){
		return Mat4<T>(m[0] << v, m[1] << v, m[2] << v, m[3] << v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Mat4<T> operator<<(const T & v, const Mat4<T> & m){
		return Mat4<T>(v << m[0], v << m[1], v << m[2], v << m[3]);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<(std::ostream & stream, const Mat4<T> & v) {
		stream << '[' << v[0].x << '\t' << v[1].x << '\t' << v[2].x << '\t' << v[3].x << ']' << '\n';
		stream << '[' << v[0].y << '\t' << v[1].y << '\t' << v[2].y << '\t' << v[3].y << ']' << '\n';
		stream << '[' << v[0].z << '\t' << v[1].z << '\t' << v[2].z << '\t' << v[3].z << ']' << '\n';
		stream << '[' << v[0].w << '\t' << v[1].w << '\t' << v[2].w << '\t' << v[3].w << ']' << '\n';
		return stream;
	}

	template<typename T /*= float*/>
	template<typename C /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<C> Mat4<T>::toString() const {
		BasicString<C> newString;
		newString.reserve(180);
		newString << C('[') << this -> column[0].x << C('\t') << this -> column[1].x << C('\t') << this -> column[2].x << C('\t') << this -> column[3].x << C(']') << C('\n');
		newString << C('[') << this -> column[0].y << C('\t') << this -> column[1].y << C('\t') << this -> column[2].y << C('\t') << this -> column[3].y << C(']') << C('\n');
		newString << C('[') << this -> column[0].z << C('\t') << this -> column[1].z << C('\t') << this -> column[2].z << C('\t') << this -> column[3].z << C(']') << C('\n');
		newString << C('[') << this -> column[0].w << C('\t') << this -> column[1].w << C('\t') << this -> column[2].w << C('\t') << this -> column[3].w << C(']') << C('\n');
		return newString;
	}

	template<typename T, typename C>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<(BasicString<C> & string, const Mat4<T> & v) {
		string << C('[') << v[0].x << C('\t') << v[1].x << C('\t') << v[2].x << C('\t') << v[3].x << C(']') << C('\n');
		string << C('[') << v[0].y << C('\t') << v[1].y << C('\t') << v[2].y << C('\t') << v[3].y << C(']') << C('\n');
		string << C('[') << v[0].z << C('\t') << v[1].z << C('\t') << v[2].z << C('\t') << v[3].z << C(']') << C('\n');
		string << C('[') << v[0].w << C('\t') << v[1].w << C('\t') << v[2].w << C('\t') << v[3].w << C(']') << C('\n');
		return string;
	}

}