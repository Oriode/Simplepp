namespace Math {

	template<typename T>
	const Vec3<T> Vec3<T>::null = Vec3<T>(0);


	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::_logicalOperatorOR( Compare func, const Vec3<T> & v ) const{
		return func(this -> x, v.x) || func(this -> y, v.y) || func(this -> z, v.z);
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec3<T>::_logicalOperatorAND( Compare func, const Vec3<T> & v )const{
		return func(this -> x, v.x) && func(this  -> y, v.y) && func(this  -> z, v.z);
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::_MathOperator( Compare func, const T & v ){
		func(this -> x, v);
		func(this -> y, v);
		func(this -> z, v);
		return *this;
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::_MathOperator( Compare func, const Vec3<T> & v ){
		func(this -> x, v.x);
		func(this -> y, v.y);
		func(this -> z, v.z);
		return *this;
	}







	template<typename T>
	MATH_FUNC_QUALIFIER void Vec3<T>::inverse(){
		this -> x = T(1) / x;
		this -> y = T(1) / y;
		this -> z = T(1) / z;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const T & x, const T & y, const T & z ){
		this -> x = x;
		this -> y = y;
		this -> z = z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> Vec3<T>::xy() const{
		return Vec2<T>(this -> x, this -> y);
	}



	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator-=( const T & v ){
		return _MathOperator(Math::subEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator-=( const Vec3<T> & v ){
		return _MathOperator(Math::subEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> Vec3<T>::operator-( ) const{
		return Vec3<T>(-this -> x, -this -> y, -this -> z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator+=( const T & v ){
		return _MathOperator(Math::addEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator+=( const Vec3<T> & v ){
		return _MathOperator(Math::addEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator/=( const T & v ){
		return _MathOperator(Math::divEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator/=( const Vec3<T> & v ){
		return _MathOperator(Math::divEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator*=( const T & v ){
		return _MathOperator(Math::mulEqual<T>(), v);
	}		

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator*=( const Vec3<T> & v ){
		return _MathOperator(Math::mulEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator>>=( const T & v ){
		return _MathOperator(Math::binaryShiftRightEqual<T>(), v);
	}		

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator>>=( const Vec3<T> & v ){
		return _MathOperator(Math::binaryShiftRightEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator<<=( const T & v ){
		return _MathOperator(Math::binaryShiftLeftEqual<T>(), v);
	}		

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator<<=( const Vec3<T> & v ){
		return _MathOperator(Math::binaryShiftLeftEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator++(  ){
		this -> x++;
		this -> y++;
		this -> z++;
		return *this;
	}		

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator--(  ){
		this -> x--;
		this -> y--;
		this -> z--;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER T & Vec3<T>::operator[]( unsigned int index ){
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec3<T>::operator[]( unsigned int index ) const{
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec2<T> & v ){
		*this = v;
		this -> z = T(0);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec2<T> & v, const T & z ){
		*this = v;
		this -> z = z;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const Vec2<T> & v ){
		this -> x = v.x;
		this -> y = v.y;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec3<T>::operator>=( const Vec3<T> & v ) const{
		return _logicalOperatorAND(Logical::greaterEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec3<T>::operator>( const Vec3<T> & v ) const{
		return _logicalOperatorAND(Logical::greater<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec3<T>::operator<=( const Vec3<T> & v ) const{
		return _logicalOperatorAND(Logical::lessEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec3<T>::operator<( const Vec3<T> & v ) const{
		return _logicalOperatorAND(Logical::less<T>(), v);
	}



	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec3<T>::operator!=( const Vec3<T> & v ) const{
		return _logicalOperatorOR(Logical::notEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec3<T>::operator==( const Vec3<T> & v ) const{
		return _logicalOperatorAND(Logical::equal<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const T & v ){
		return _MathOperator(Math::equal<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const Vec3<T> & v ){
		return _MathOperator(Math::equal<T>(), v);
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const U & v ){
		const T newValue(v);
		return *this = newValue;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T> & Vec3<T>::operator=( const Vec3<U> & v ){
		this -> x = T(v.x);
		this -> y = T(v.y);
		this -> z = T(v.z);
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec3<T> & v ){
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const T & v ){
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const Vec3<U> & v ){
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( const U & v ){
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T>::Vec3( void ){
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const Vec3<T> & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const Vec3<T> & v1, const T & v2 ){
		return Vec3<T>(v1.x + v2, v1.y + v2, v1.z + v2);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator+( const T & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const Vec3<T> & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const Vec3<T> & v1, const T & v2 ){
		return Vec3<T>(v1.x - v2, v1.y - v2, v1.z - v2);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator-( const T & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const Vec3<T> & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const Vec3<T> & v1, const T & v2 ){
		return Vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator*( const T & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const Vec3<T> & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const Vec3<T> & v1, const T & v2 ){
		return Vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator/( const T & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z);
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator>>( const Vec3<T> & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator>>( const Vec3<T> & v1, const T & v2 ){
		return Vec3<T>(v1.x >> v2, v1.y >> v2, v1.z >> v2);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator>>( const T & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1 >> v2.x, v1 >> v2.y, v1 >> v2.z);
	}
	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const Vec3<T> & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const Vec3<T> & v1, const T & v2 ){
		return Vec3<T>(v1.x << v2, v1.y << v2, v1.z << v2);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> operator<<( const T & v1, const Vec3<T> & v2 ){
		return Vec3<T>(v1 << v2.x, v1 << v2.y, v1 << v2.z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<(std::ostream & stream, const Vec3<T> & v){
		stream << '[' << v.x << '\t' << v.y << '\t' << v.z << ']';
		return stream;
	}

	template<typename T, typename C>
	MATH_FUNC_QUALIFIER BasicString<C> & operator<<(BasicString<C> & string, const Vec3<T> & v) {
		string << C('[') << v.x << C('\t') << v.y << C('\t') << v.z << C(']');
		return string;
	}

	template<typename T /*= float*/>
	template<typename C /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<C> Vec3<T>::toString() const{
		BasicString<C> newString;
		newString.reserve(60);
		newString << C('[') << this -> x << C('\t') << this -> y << C('\t') << this -> z << C(']');
		return newString;
	}

}