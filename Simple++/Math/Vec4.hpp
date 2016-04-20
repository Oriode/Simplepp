namespace Math {

	template<typename T>
	const Vec4<T> Vec4<T>::null = Vec4<T>(0);

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec4<T>::_logicalOperatorOR(Compare func, const Vec4 & v) const{
		return func(this -> x, v.x) || func(this -> y, v.y) || func(this -> z, v.z) || func(this -> w, v.w);
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER bool Vec4<T>::_logicalOperatorAND(Compare func, const Vec4 & v) const{
		return func(this -> x, v.x) && func(this  -> y, v.y) && func(this  -> z, v.z) && func(this -> w, v.w);
	}

	template<typename T>
	template<typename Compare, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::_MathOperator(Compare func, const U & v){
		func(this -> x, v);
		func(this -> y, v);
		func(this -> z, v);
		func(this -> w, v);
		return *this;
	}

	template<typename T>
	template<typename Compare>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::_MathOperator(Compare func, const Vec4<T> & v){
		func(this -> x, v.x);
		func(this -> y, v.y);
		func(this -> z, v.z);
		func(this -> w, v.w);
		return *this;
	}



	template<typename T>
	MATH_FUNC_QUALIFIER void Vec4<T>::inverse(){
		this -> x = T(1) / x;
		this -> y = T(1) / y;
		this -> z = T(1) / z;
		this -> w = T(1) / w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec3<T> Vec4<T>::xyz() const{
		return Vec3<T>(this -> x, this -> y, this -> z);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> Vec4<T>::xy() const{
		return Vec2<T>(this -> x, this -> y);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER T & Vec4<T>::operator[](unsigned int index){
		return this -> values[index];
	}

	template<typename T>
	MATH_FUNC_QUALIFIER const T & Vec4<T>::operator[](unsigned int index) const{
		return this -> values[index];
	}


	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec4<T>::operator>=(const Vec4<T> & v) const{
		return _logicalOperatorAND(Logical::greaterEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec4<T>::operator>(const Vec4<T> & v) const{
		return _logicalOperatorAND(Logical::greater<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec4<T>::operator<=(const Vec4<T> & v) const{
		return _logicalOperatorAND(Logical::lessEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec4<T>::operator<(const Vec4<T> & v) const{
		return _logicalOperatorAND(Logical::less<T>(), v);
	}


	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec4<T>::operator!=(const Vec4<T> & v) const{
		return _logicalOperatorOR(Logical::notEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER bool Vec4<T>::operator==(const Vec4<T> & v) const{
		return _logicalOperatorAND(Logical::equal<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const T & x, const T & y, const T & z, const T & w){
		this -> x = x;
		this -> y = y;
		this -> z = z;
		this -> w = w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const Vec4<T> & v){
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const Vec4<U> & v){
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const T & v){
		*this = v;
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const U & v){
		*this = v;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const Vec3<T> & v){
		*this = v;
		this -> w = T(0);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const Vec3<T> & v, const T & w){
		*this = v;
		this -> w = w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const Vec2<T> & v){
		*this = v;
		this -> z = T(0);
		this -> w = T(0);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(const Vec2<T> & v, const T & z, const T & w){
		*this = v;
		this -> z = z;
		this -> w = w;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T>::Vec4(void){

	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator-=(const T & v){
		return _MathOperator(Math::subEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator-=(const Vec4<T> & v){
		return _MathOperator(Math::subEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> Vec4<T>::operator-() const{
		return Vec4<T>(-this -> x, -this -> y, -this -> z, -this -> w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator+=(const T & v){
		return _MathOperator(Math::addEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator+=(const Vec4<T> & v){
		return _MathOperator(Math::addEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator*=(const T & v){
		return _MathOperator(Math::mulEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator*=(const Vec4<T> & v){
		return _MathOperator(Math::mulEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator/=(const T & v){
		return _MathOperator(Math::divEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator/=(const Vec4<T> & v){
		return _MathOperator(Math::divEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator>>=(const T & v){
		return _MathOperator(Math::binaryShiftRightEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator>>=(const Vec4<T> & v){
		return _MathOperator(Math::binaryShiftRightEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator<<=(const T & v){
		return _MathOperator(Math::binaryShiftLeftEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator<<=(const Vec4<T> & v){
		return _MathOperator(Math::binaryShiftLeftEqual<T>(), v);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=(const T & v){
		return _MathOperator(Math::equal<T>(), v);
	}

	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=(const U & v){
		T newValue(v);
		return *this = newValue;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=(const Vec4<T> & v){
		_MathOperator(Math::equal<T>(), v);
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=(const Vec3<T> & v){
		this -> x = v.x;
		this -> y = v.y;
		this -> z = v.z;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=(const Vec2<T> & v){
		this -> x = v.x;
		this -> y = v.y;
		return *this;
	}


	template<typename T>
	template<typename U>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator=(const Vec4<U> & v){
		this -> x = T(v.x);
		this -> y = T(v.y);
		this -> z = T(v.z);
		this -> w = T(v.w);
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator++(){
		this -> x++;
		this -> y++;
		this -> z++;
		this -> w++;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> & Vec4<T>::operator--(){
		this -> x--;
		this -> y--;
		this -> z--;
		this -> w--;
		return *this;
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator+(const Vec4<T> & v1, const Vec4<T> & v2){
		return Vec4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator+(const Vec4<T> & v1, const U & v2){
		return Vec4<T>(v1.x + v2, v1.y + v2, v1.z + v2, v1.w + v2);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator+(const U & v1, const Vec4<T> & v2){
		return Vec4<T>(v1 + v2.x, v1 + v2.y, v1 + v2.z, v1 + v2.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator-(const Vec4<T> & v1, const Vec4<T> & v2){
		return Vec4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator-(const Vec4<T> & v1, const U & v2){
		return Vec4<T>(v1.x - v2, v1.y - v2, v1.z - v2, v1.w - v2);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator-(const U & v1, const Vec4<T> & v2){
		return Vec4<T>(v1 - v2.x, v1 - v2.y, v1 - v2.z, v1 - v2.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator/(const Vec4<T> & v1, const Vec4<T> & v2){
		return Vec4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator/(const Vec4<T> & v1, const U & v2){
		return Vec4<T>(v1.x / v2, v1.y / v2, v1.z / v2, v1.w / v2);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator/(const U & v1, const Vec4<T> & v2){
		return Vec4<T>(v1 / v2.x, v1 / v2.y, v1 / v2.z, v1 / v2.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator*(const Vec4<T> & v1, const Vec4<T> & v2){
		return Vec4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator*(const Vec4<T> & v1, const U & v2){
		return Vec4<T>(v1.x * v2, v1.y * v2, v1.z * v2, v1.w * v2);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator*(const U & v1, const Vec4<T> & v2){
		return Vec4<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z, v1 * v2.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator>>(const Vec4<T> & v1, const Vec4<T> & v2){
		return Vec4<T>(v1.x >> v2.x, v1.y >> v2.y, v1.z >> v2.z, v1.w >> v2.w);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator>>(const Vec4<T> & v1, const U & v2){
		return Vec4<T>(v1.x >> v2, v1.y >> v2, v1.z >> v2, v1.w >> v2);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator>>(const U & v1, const Vec4<T> & v2){
		return Vec4<T>(v1 >> v2.x, v1 >> v2.y, v1 >> v2.z, v1 >> v2.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<(const Vec4<T> & v1, const Vec4<T> & v2){
		return Vec4<T>(v1.x << v2.x, v1.y << v2.y, v1.z << v2.z, v1.w << v2.w);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<(const Vec4<T> & v1, const U & v2){
		return Vec4<T>(v1.x << v2, v1.y << v2, v1.z << v2, v1.w << v2);
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER Vec4<T> operator<<(const U & v1, const Vec4<T> & v2){
		return Vec4<T>(v1 << v2.x, v1 << v2.y, v1 << v2.z, v1 << v2.w);
	}

	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<(std::ostream & stream, const Vec4<T> & v){
		stream << '[' << v.x << '\t' << v.y << '\t' << v.z << '\t' << v.w << ']';
		return stream;
	}


	template<typename T /*= float*/>
	template<typename U /*=char*/>
	MATH_FUNC_QUALIFIER BasicString<U> Vec4<T>::toString() const {
		BasicString<U> newString;
		newString.reserve(80);
		newString << U('[') << this -> x << U('\t') << this -> y << U('\t') << this -> z << U('\t') << this -> w << U(']');
		return newString;
	}

	template<typename T, typename U>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<(BasicString<U> & string, const Vec4<T> & v) {
		string << U('[') << v.x << U('\t') << v.y << U('\t') << v.z << U('\t') << v.w << (']');
		return string;
	}

}
