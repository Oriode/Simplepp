#pragma once

#include "../IO/BasicIO.h"
#include "../String.h"
#include "../JSON/Node.h"

#include "BasicMath.h"
#include "Vec.h"

namespace Math {

	template<typename T>
	class Mat : public BasicVector<T>, public JSON::Jsonable {
	public:
		class View {
		public:
			/************************************************************************/
			/* ================             CONSTRUCTOR            ================ */
			/************************************************************************/

			View(Mat<T>& mat, const Size m);

			/************************************************************************/
			/* ================               ACCESS               ================ */
			/************************************************************************/

			const T& operator[](const Size n) const;
			T& operator[](const Size n);

			/************************************************************************/
			/* ================                MISC                ================ */
			/************************************************************************/

			operator const Vec<T>() const;
			operator Vec<T>();

			Vec<T> toVec() const;

		private:
			Mat<T>& mat;
			Size m;
		};

		/************************************************************************/
		/* ================             CONSTRUCTOR            ================ */
		/************************************************************************/

		Mat();
		Mat(const Size m, const Size n);
		template<typename C, Size M, Size N>
		Mat(const C(&v)[ M ][N]);
		template<typename C>
		Mat(const Mat<C>& mat);
		Mat(const Mat<T>& mat);
		template<typename C>
		Mat(const Table<C>& v);
		Mat(Mat&& mat);

		~Mat();

		/************************************************************************/
		/* ================            COPY OPERATOR           ================ */
		/************************************************************************/

		template<typename C, Size M, Size N>
		Mat<T>& operator=(const C(&v)[ M ][ N ]);
		template<typename C>
		Mat<T>& operator=(const Mat<C>& mat);
		Mat<T>& operator=(const Mat<T>& mat);
		Mat<T>& operator=(Mat<T>&& mat);

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		const typename Mat<T>::View operator[](const Size m) const;
		typename Mat<T>::View operator[](const Size m);

		using BasicVector<T>::getValueI;
		const T& getValueI(const Size m, const Size n) const;
		T& getValueI(const Size m, const Size n);

		using BasicVector<T>::setValueI;
		void setValueI(const Size m, const Size n, const T & v);

		void setValueM(const Size m, const Table<T>& v);
		void setValueN(const Size n, const Table<T>& v);

		Vec<T> getValueM(const Size m) const;
		Vec<T> getValueN(const Size n) const;

		const T* getDataM(const Size m) const;
		T* getDataM(const Size m);

		/************************************************************************/
		/* ================              LOGICAL               ================ */
		/************************************************************************/

		/**
		 * @brief 	Equality operator
		 * @param 	v	A Mat<T> to process.
		 * @returns	True if the parameters are considered equivalent.
		 */
		bool operator==(const Mat<T>& m) const;
		/**
		 * @brief 	Inequality operator
		 * @param 	v	A Mat<T> to process.
		 * @returns	True if the parameters are not considered equivalent.
		 */
		bool operator!=(const Mat<T>& m) const;
		/**
		 * @brief 	Less-than comparison operator
		 * @param 	v	A Mat<T> to process.
		 * @returns	True if the first parameter is less than the second.
		 */
		bool operator<(const Mat<T>& m) const;
		/**
		 * @brief 	Greater-than comparison operator
		 * @param 	v	A Mat<T> to process.
		 * @returns	True if the first parameter is greater than to the second.
		 */
		bool operator>(const Mat<T>& m) const;
		/**
		 * @brief 	Less-than-or-equal comparison operator
		 * @param 	v	A Mat<T> to process.
		 * @returns	True if the first parameter is less than or equal to the second.
		 */
		bool operator<=(const Mat<T>& m) const;
		/**
		 * @brief 	Greater-than-or-equal comparison operator
		 * @param 	v	A Mat<T> to process.
		 * @returns	True if the first parameter is greater than or equal to the second.
		 */
		bool operator>=(const Mat<T>& m) const;

		/************************************************************************/
		/* ================             ARITHMETIC             ================ */
		/************************************************************************/

		template<typename Functor, typename C>
		Mat<T>& apply(Functor& functor, const Mat<C>& m);
		template<typename Functor, typename C>
		Mat<T>& apply(Functor& functor, const Table<C>& v);
		template<typename Functor>
		Mat<T>& apply(Functor& functor, const T& s);
		template<typename Functor>
		Mat<T>& apply(Functor& functor);

		template<typename C>
		Mat<T>& operator+=(const Mat<C>& m);
		template<typename C>
		Mat<T>& operator+=(const Table<C>& v);
		Mat<T>& operator+=(const T& s);

		template<typename C>
		Mat<T>& operator-=(const Mat<C>& m);
		template<typename C>
		Mat<T>& operator-=(const Table<C>& v);
		Mat<T>& operator-=(const T& s);

		template<typename C>
		Mat<T>& operator*=(const Mat<C>& m);
		template<typename C>
		Mat<T>& operator*=(const Table<C>& v);
		Mat<T>& operator*=(const T& s);

		Mat<T>& operator/=(const T& s);

		template<typename C>
		Mat<T>& operator%=(const Mat<C>& m);
		template<typename C>
		Mat<T>& operator%=(const Table<C>& v);
		Mat<T>& operator%=(const T& s);

		Mat<T>& operator++();
		Mat<T>& operator--();
		Mat<T> operator-();

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		void resize(const Size newM, const Size newN);
		void resizeNoCopy(const Size newM, const Size newN);

		const Size getSizeM() const;
		const Size getSizeN() const;

		Mat<T>& zeros();
		Mat<T>& ones();
		Mat<T>& identity();
		Mat<T>& randomF();
		Mat<T>& random(const T & min, const T & max);

		Mat<T>& transpose();

		template<typename S = String>
		S toString() const;

		const Size getNbElem(const Size m, const Size n) const;

		/**
		 * @brief 	read from a file stream
		 * @param [in,out]	stream	stream used to read load this object.
		 * @returns	boolean to know if the operation is a success of not.
		 */
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		/**
		 * @brief 	write this object as binary into a file stream
		 * @param [in,out]	stream	stream used to write this object.
		 * @returns	boolean to know if the operation is a success of not.
		 */
		template<typename Stream>
		bool write(Stream* stream) const;

		///@brief Read a JSON object and set this to the read values.
		///@param nodeArray Pointer to the JSON object to be read.
		///@return true if success, false otherwise.
		template<typename C = UTF8String>
		bool fromJSON(const JSON::BasicNodeT<C>* node);

		///@brief Write this object to a Json object
		///@param o Json node to write to.
		template<typename C = UTF8String>
		JSON::NodeArrayT<C>* toJSON() const;

	private:
		Size m;
		Size n;
	};

	/************************************************************************/
	/* ================             ARITHMETIC             ================ */
	/************************************************************************/

	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const Mat<T>& m1, const Mat<T>& m2);
	template<typename T, typename Functor, typename C>
	Mat<T> apply(Functor& functor, const Mat<T>& m, const Table<C>& v);
	template<typename T, typename Functor, typename C>
	Mat<T> apply(Functor& functor, const Table<C>& v, const Mat<T>& m);
	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const Mat<T>& m, const T& s);
	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const T& s, const Mat<T>& m);
	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const Mat<T>& m);

	template<typename T>
	Mat<T> operator+(const Mat<T>& m1, const Mat<T>& m2);
	template<typename T>
	Mat<T> operator+(const Mat<T>& m, const Table<T>& v);
	template<typename T>
	Mat<T> operator+(const Table<T>& v, const Mat<T>& m);
	template<typename T>
	Mat<T> operator+(const Mat<T>& m, const T& s);
	template<typename T>
	Mat<T> operator+(const T& s, const Mat<T>& m);

	template<typename T>
	Mat<T> operator-(const Mat<T>& m1, const Mat<T>& m2);
	template<typename T>
	Mat<T> operator-(const Mat<T>& m, const Table<T>& v);
	template<typename T>
	Mat<T> operator-(const Table<T>& v, const Mat<T>& m);
	template<typename T>
	Mat<T> operator-(const Mat<T>& m, const T& s);
	template<typename T>
	Mat<T> operator-(const T& s, const Mat<T>& m);

	template<typename T>
	Mat<T> operator*(const Mat<T>& m1, const Mat<T>& m2);
	template<typename T>
	Mat<T> operator*(const Mat<T>& m, const Table<T>& v);
	template<typename T>
	Mat<T> operator*(const Table<T>& v, const Mat<T>& m);
	template<typename T>
	Mat<T> operator*(const Mat<T>& m, const T& s);
	template<typename T>
	Mat<T> operator*(const T& s, const Mat<T>& m);

	template<typename T>
	Mat<T> operator/(const Mat<T>& m, const T& s);
	template<typename T>
	Mat<T> operator/(const T& s, const Mat<T>& m);

	template<typename T>
	inline Mat<T>::Mat() :
		m(Size(0)),
		n(Size(0))
	{}

	template<typename T>
	inline Mat<T>::Mat(const Size m, const Size n) :
		BasicVector<T>(getNbElem(m, n)),
		m(m),
		n(n)
	{
	}

	template<typename T>
	inline Mat<T>::Mat(Mat&& mat) :
		BasicVector<T>(Utility::toRValue(mat)),
		m(Utility::toRValue(mat.m)),
		n(Utility::toRValue(mat.n))
	{}

	template<typename T>
	inline Mat<T>::~Mat() {}

	template<typename T>
	inline const typename Mat<T>::View Mat<T>::operator[](const Size m) const {
		return const_cast<Mat<T> *>(this )->operator[](m);
	}

	template<typename T>
	inline typename Mat<T>::View Mat<T>::operator[](const Size m) {
		return Mat<T>::View(*this, m);
	}

	template<typename T>
	inline const T& Mat<T>::getValueI(const Size m, const Size n) const {
		return const_cast< Mat<T> * >( this )->getValueI(m, n);
	}

	template<typename T>
	inline T& Mat<T>::getValueI(const Size m, const Size n) {
		return getValueI(m * getSizeN() + n);
	}

	template<typename T>
	inline void Mat<T>::setValueI(const Size m, const Size n, const T& v) {
		getValueI(m, n) = v;
	}

	template<typename T>
	inline void Mat<T>::setValueM(const Size m, const Table<T>& v) {
		ASSERT_SPP(getSizeN() == v.getSize());
		Utility::copy(this->dataTable + m * getSizeN(), v.getData(), getSizeN());
	}

	template<typename T>
	inline void Mat<T>::setValueN(const Size n, const Table<T>& v) {
		ASSERT_SPP(getSizeM() == v.getSize());
		for ( Size i(0); i < getSizeM(); i++ ) {
			setValueI(i, n, v[ i ]);
		}
	}

	template<typename T>
	inline Vec<T> Mat<T>::getValueM(const Size m) const {
		Vec<T> outputVec(getSizeN());
		Utility::copy(outputVec.getData(), this->dataTable, getSizeN());
		return outputVec;
	}

	template<typename T>
	inline Vec<T> Mat<T>::getValueN(const Size n) const {
		Vec<T> outputVec(getSizeN());
		for ( Size i(0); i < getSizeM(); i++ ) {
			outputVec.setValueI(i, getValueI(i, n));
		}
		return outputVec;
	}

	template<typename T>
	inline const T* Mat<T>::getDataM(const Size m) const {
		return const_cast<Mat<T> *>(this )->getDataM(m);
	}

	template<typename T>
	inline T* Mat<T>::getDataM(const Size m) {
		return this->dataTable + m * getSizeN();
	}

	template<typename T>
	inline bool Mat<T>::operator==(const Mat<T>& m) const {
		if ( getSizeM() != m.getSizeM() || getSizeN() != m.getSizeN() ) {
			return false;
		}
		for ( Size i(0); i < this-> size; i++ ) {
			if ( getValueI(i) != m.getValueI(i) ) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool Mat<T>::operator!=(const Mat<T>& m) const {
		return !Mat<T>::operator%=(m);
	}

	template<typename T>
	inline bool Mat<T>::operator<(const Mat<T>& m) const {
		if ( getSizeM() != m.getSizeM() || getSizeN() != m.getSizeN() ) {
			return false;
		}
		for ( Size i(0); i < this-> size; i++ ) {
			if ( getValueI(i) < m.getValueI(i) ) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool Mat<T>::operator>(const Mat<T>& m) const {
		if ( getSizeM() != m.getSizeM() || getSizeN() != m.getSizeN() ) {
			return false;
		}
		for ( Size i(0); i < this-> size; i++ ) {
			if ( getValueI(i) > m.getValueI(i) ) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool Mat<T>::operator<=(const Mat<T>& m) const {
		if ( getSizeM() != m.getSizeM() || getSizeN() != m.getSizeN() ) {
			return false;
		}
		for ( Size i(0); i < this-> size; i++ ) {
			if ( getValueI(i) <= m.getValueI(i) ) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool Mat<T>::operator>=(const Mat<T>& m) const {
		if ( getSizeM() != m.getSizeM() || getSizeN() != m.getSizeN() ) {
			return false;
		}
		for ( Size i(0); i < this-> size; i++ ) {
			if ( getValueI(i) >= m.getValueI(i) ) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline void Mat<T>::resize(const Size newM, const Size newN) {
		if ( newM == getSizeM() && newN == getSizeN() ) {
			return;
		}

		BasicVector<T>::resize(getNbElem(newM, newN));

		this->m = newM;
		this->n = newN;
	}

	template<typename T>
	inline void Mat<T>::resizeNoCopy(const Size newM, const Size newN) {
		if ( newM == getSizeM() && newN == getSizeN() ) {
			return;
		}

		BasicVector<T>::resizeNoCopy(getNbElem(newM, newN));

		this->m = newM;
		this->n = newN;
	}

	template<typename T>
	inline const Size Mat<T>::getSizeM() const {
		return this->m;
	}

	template<typename T>
	inline const Size Mat<T>::getSizeN() const {
		return this->n;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::zeros() {
		BasicVector<T>::fill(T(0));
		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::ones() {
		BasicVector<T>::fill(T(1));
		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::identity() {
		for ( Size i(0); i < getSizeM(); i++ ) {
			for ( Size j(0); j < getSizeN(); j++ ) {
				if ( i == j ) {
					setValueI(i, j, T(1));
				} else {
					setValueI(i, j, T(0));
				}
			}
		}
		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::randomF() {
		set(Math::RandomF());

		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::random(const T& min, const T& max) {
		set(Math::Random<T>(min, max));

		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::transpose() {
		if ( this->size > Size(0) ) {
			T* newBuffer(new T[ this->size ]);
			for ( Size i(0); i < getSizeM(); i++ ) {
				for ( Size j(0); j < getSizeN(); j++ ) {
					newBuffer[ j * getSizeM() + i ] = getValueI(i, j);
				}
			}
			delete[] this->dataTable;
			this->dataTable = newBuffer;

			Utility::swap(this->m, this->n);
		}

		return *this;
	}

	template<typename T>
	inline const Size Mat<T>::getNbElem(const Size m, const Size n) const {
		return m * n;
	}

	template<typename T>
	template<typename C, Size M, Size N>
	inline Mat<T>::Mat(const C(&v)[ M ][ N ]) :
		BasicVector<T>(reinterpret_cast<const C *>(v), getNbElem(M, N)),
		m(M),
		n(N)
	{
	}

	template<typename T>
	template<typename C>
	inline Mat<T>::Mat(const Mat<C>& mat) :
		BasicVector<T>(mat),
		m(mat.m),
		n(mat.n)
	{}

	template<typename T>
	template<typename C>
	inline Mat<T>::Mat(const Table<C>&v) :
		BasicVector<T>(v),
		m(v.getSize()),
		n(Size(1))
	{}

	template<typename T>
	inline Mat<T>::Mat(const Mat<T>& mat) :
		BasicVector<T>(mat),
		m(mat.m),
		n(mat.n)
	{}

	template<typename T>
	template<typename C, Size M, Size N>
	inline Mat<T>& Mat<T>::operator=(const C(&v)[ M ][ N ]) {
		resizeNoCopy(M, N);

		Utility::copy(this->dataTable, reinterpret_cast< const C* >( v ), this->size);

		this->m = M;
		this->n = N;

		return *this;
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator=(const Mat<C>& mat) {
		BasicVector<T>::operator=(mat);

		this->m = mat.m;
		this->n = mat.n;

		return *this;
	}

	template<typename T>
	template<typename Functor, typename C>
	inline Mat<T>& Mat<T>::apply(Functor& functor, const Mat<C>& m) {
		ASSERT_SPP(getSizeM() == m.getSizeM() && getSizeN() == m.getSizeN());
		Table<T>::apply(functor, m);

		return *this;
	}

	template<typename T>
	template<typename Functor, typename C>
	inline Mat<T>& Mat<T>::apply(Functor& functor, const Table<C>& v) {
		Table<T>::apply(functor, v);

		return *this;
	}

	template<typename T>
	template<typename Functor>
	inline Mat<T>& Mat<T>::apply(Functor& functor, const T& s) {
		Table<T>::apply(functor, s);

		return *this;
	}

	template<typename T>
	template<typename Functor>
	inline Mat<T>& Mat<T>::apply(Functor& functor) {
		Table<T>::apply(functor);

		return *this;
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator+=(const Mat<C>& m) {
		return apply(Math::Operations::AddEqual(), m);
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator+=(const Table<C>& v) {
		return apply(Math::Operations::AddEqual(), v);
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator+=(const T& s) {
		return apply(Math::Operations::AddEqual(), s);
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator-=(const Mat<C>& m) {
		return apply(Math::Operations::SubEqual(), m);
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator-=(const Table<C>& v) {
		return apply(Math::Operations::SubEqual(), v);
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator*=(const Mat<C>& m) {
		return *this = *this * m;
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator*=(const Table<C>& v) {
		return *this = *this * v;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator-=(const T& s) {
		return apply(Math::Operations::SubEqual(), s);
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator*=(const T& s) {
		return apply(Math::Operations::MulEqual(), s);
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator/=(const T& s) {
		return apply(Math::Operations::DivEqual(), s);
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator%=(const Mat<C>& m) {
		return apply(Math::Operations::ModulusEqual(), m);
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator%=(const Table<C>& v) {
		return apply(Math::Operations::ModulusEqual(), v);
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator%=(const T& s) {
		return apply(Math::Operations::ModulusEqual(), s);
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator++() {
		return apply(Math::Operations::Increment());
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator--() {
		return apply(Math::Operations::Decrement());
	}

	template<typename T>
	inline Mat<T> Mat<T>::operator-() {
		return ::Math::apply(Math::Operations::MinusUnary(), *this);
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator=(const Mat<T>& mat) {
		BasicVector<T>::operator=(mat);

		this->m = mat.m;
		this->n = mat.n;

		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator=(Mat<T>&& mat) {
		BasicVector<T>::operator=(Utility::toRValue(mat));

		this->m = Utility::toRValue(mat.m);
		this->n = Utility::toRValue(mat.n);

		return *this;
	}

	template<typename T>
	template<typename S>
	inline S Mat<T>::toString() const {
		S outputStr;

		outputStr << S::ElemType('\n');
		outputStr << S::ElemType('=');
		outputStr << S::ElemType(' ');
		outputStr << S::ElemType('M');
		outputStr << S::ElemType('A');
		outputStr << S::ElemType('T');
		outputStr << S::ElemType(' ');
		outputStr << getSizeM();
		outputStr << S::ElemType('x');
		outputStr << getSizeN();
		outputStr << S::ElemType(' ');
		outputStr << S::ElemType('=');
		outputStr << S::ElemType('\n');

		if ( getSizeM() == Size(0) ) {
			outputStr << S::ElemType('[');
			outputStr << S::ElemType(']');
			return outputStr;
		}

		for ( Size i(0); i < getSizeM(); i++ ) {
			if ( i > Size(0) ) {
				outputStr << S::ElemType('\n');
			}

			outputStr << S::ElemType('[');
			outputStr << S::ElemType(' ');

			for ( Size j(0); j < getSizeN(); j++ ) {
				if ( j > Size(0) ) {
					outputStr << S::ElemType(',');
					outputStr << S::ElemType(' ');
				}
				outputStr << getValueI(i, j);
			}

			outputStr << S::ElemType(' ');
			outputStr << S::ElemType(']');
		}

		return outputStr;
	}

	template<typename T>
	template<typename Stream>
	inline bool Mat<T>::read( Stream * stream, int verbose ) {
		if ( !BasicVector<T>::read(stream) ) {
			return false;
		}

		if ( !IO::read( stream, &this->m, verbose - 1 ) ) {
			return false;
		}
		if ( !IO::read( stream, &this->n, verbose - 1 ) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename Stream>
	inline bool Mat<T>::write(Stream* stream) const {
		if ( !BasicVector<T>::write(stream) ) {
			return false;
		}

		if ( !IO::write(stream, &this->m) ) {
			return false;
		}
		if ( !IO::write(stream, &this->n) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename C>
	inline bool Mat<T>::fromJSON(const JSON::BasicNodeT<C>* node) {
		if ( node->getType() != JSON::BasicNodeT<C>::Type::Array ) {
			return false;
		}

		if ( node->getNbChildren() == Size(0) ) {
			return false;
		}

		if ( node->getChild(Size(0))->getNbChildren() == Size(0) ) {
			return false;
		}

		resizeNoCopy(node->getNbChildren(), node->getChild(Size(0))->getNbChildren());

		for ( Size i(0); i < node->getNbChildren(); i++ ) {
			const JSON::BasicNodeT<C>* childNode(node->getChild(i));
			if ( childNode->getType() != JSON::BasicNodeT<C>::Type::Array ) {
				return false;
			}
			if ( childNode->getNbChildren() != getSizeN() ) {
				return false;
			}
			for ( Size j(0); j < childNode->getNbChildren(); j++ ) {
				const JSON::BasicNodeT<C>* nodeValue(childNode->getChild(j));
				if ( !JSON::fromJSON<C>(nodeValue, &getValueI(i, j)) ) {
					return false;
				}
			}
		}

		return true;
	}

	template<typename T>
	template<typename C>
	inline JSON::NodeArrayT<C>* Mat<T>::toJSON() const {
		JSON::NodeArrayT<C>* nodeArrayM(new JSON::NodeArrayT<C>());

		for ( Size i(0); i < getSizeM(); i++ ) {
			JSON::NodeArrayT<C>* nodeArrayN(new JSON::NodeArrayT<C>());
			for ( Size j(0); j < getSizeN(); j++ ) {
				JSON::BasicNodeT<C>* nodeValue(JSON::toJSON(getValueI(i, j)));
				nodeArrayN->addChild(nodeValue);
			}
			nodeArrayM->addChild(nodeArrayN);
		}

		return nodeArrayM;
	}

	template<typename T>
	inline Mat<T>::View::View(Mat<T>& mat, const Size m) :
		mat(mat),
		m(m)
	{}

	template<typename T>
	const T& Mat<T>::View::operator[](const Size n) const {
		return const_cast<Mat<T>::View *>(this )->operator[](n);
	}

	template<typename T>
	T& Mat<T>::View::operator[](const Size n) {
		return this->mat.getValueI(this->m * this->mat.getSizeN() + n);
	}

	template<typename T>
	inline Vec<T> Mat<T>::View::toVec() const {
		return Vec<T>(this->mat.getData() + this->m * this->mat.getSizeN(), this->mat.getSizeN());
	}

	template<typename T>
	inline Mat<T>::View::operator const Vec<T>() const {
		return const_cast<Mat<T>::View *>(this )->operator Vec<T>();
	}

	template<typename T>
	inline Mat<T>::View::operator Vec<T>() {
		return toVec();
	}

	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const Mat<T>& m1, const Mat<T>& m2) {
		ASSERT_SPP(m1.getSizeM() == m2.getSizeM() && m1.getSizeN() == m2.getSizeN());
		Mat<T> r(m1.getSizeM(), m1.getSizeN());
		for ( Size i(0); i < m1.getSize(); i++ ) {
			r.setValueI(i, functor(m1.getValueI(i), m2.getValueI(i)));
		}
		return r;
	}

	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const Mat<T>& m, const T& s) {
		Mat<T> r(m.getSizeM(), m.getSizeN());
		for ( Size i(0); i < m.getSize(); i++ ) {
			r.setValueI(i, functor(m.getValueI(i), s));
		}
		return r;
	}

	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const T& s, const Mat<T>& m) {
		Mat<T> r(m.getSizeM(), m.getSizeN());
		for ( Size i(0); i < m.getSize(); i++ ) {
			r.setValueI(i, functor(s, m.getValueI(i)));
		}
		return r;
	}

	template<typename T, typename Functor, typename C>
	Mat<T> apply(Functor& functor, const Mat<T>& m, const Table<C>& v) {
		ASSERT_SPP(m.getSizeN() == v.getSize());
		Mat<T> r(m.getSizeM(), m.getSizeN());
		for ( Size i(0); i < m.getSizeM(); i++ ) {
			for ( Size j(0); j < m.getSizeN(); j++ ) {
				T& value(m.getValueI(i, j));
				value = functor(value, v[ j ]);
			}
		}
		return r;
	}

	template<typename T, typename Functor, typename C>
	Mat<T> apply(Functor& functor, const Table<C>& v1, const Mat<T>& v2) {
		ASSERT_SPP(m.getSizeM() == v.getSize());
		Mat<T> r(m.getSizeM(), m.getSizeN());
		for ( Size i(0); i < m.getSizeM(); i++ ) {
			for ( Size j(0); j < m.getSizeN(); j++ ) {
				T& value(m.getValueI(i, j));
				value = functor(value, v[ i ]);
			}
		}
		return r;
	}

	template<typename T, typename Functor>
	Mat<T> apply(Functor& functor, const Mat<T>& v) {
		Mat<T> r(m.getSizeM(), m.getSizeN());
		for ( Size i(0); i < m.getSize(); i++ ) {
			r.setValueI(i, functor(m.getValueI(i)));
		}
		return r;
	}

	template<typename T>
	Mat<T> operator+(const Mat<T>& m1, const Mat<T>& m2) {
		return apply(Math::Operations::Add(), m1, m2);
	}

	template<typename T>
	Mat<T> operator+(const Mat<T>& m, const Table<T>& v) {
		return apply(Math::Operations::Add(), m, v);
	}

	template<typename T>
	Mat<T> operator+(const Table<T>& v, const Mat<T>& m) {
		return apply(Math::Operations::Add(), v, m);
	}

	template<typename T>
	Mat<T> operator+(const Mat<T>& m, const T& s) {
		return apply(Math::Operations::Add(), m, s);
	}

	template<typename T>
	Mat<T> operator+(const T& s, const Mat<T>& m) {
		return apply(Math::Operations::Add(), s, m);
	}

	template<typename T>
	Mat<T> operator-(const Mat<T>& m1, const Mat<T>& m2) {
		return apply(Math::Operations::Sub(), m1, m2);
	}

	template<typename T>
	Mat<T> operator-(const Mat<T>& m, const Table<T>& v) {
		return apply(Math::Operations::Sub(), m, v);
	}

	template<typename T>
	Mat<T> operator-(const Table<T>& v, const Mat<T>& m) {
		return apply(Math::Operations::Sub(), v, m);
	}

	template<typename T>
	Mat<T> operator-(const Mat<T>& m, const T& s) {
		return apply(Math::Operations::Sub(), m, s);
	}

	template<typename T>
	Mat<T> operator-(const T& s, const Mat<T>& m) {
		return apply(Math::Operations::Sub(), s, m);
	}

	template<typename T>
	Mat<T> operator*(const Mat<T>& m1, const Mat<T>& m2) {
		ASSERT_SPP(m1.getSizeN() == m2.getSizeM());
		Mat<T> r(m1.getSizeM(), m2.getSizeN());
		for ( Size i(0); i < r.getSizeM(); i++ ) {
			for ( Size j(0); j < r.getSizeN(); j++ ) {
				T value(0);

				for ( Size k(0); k < m1.getSizeN(); k++ ) {
					value += m1.getValueI(i, k) * m2.getValueI(k, j);
				}

				r.setValueI(i, j, value);
			}
		}
		return r;
	}

	template<typename T>
	Mat<T> operator*(const Mat<T>& m, const Table<T>& v) {
		ASSERT_SPP(m.getSizeN() == v.getSize() || m.getSizeN() == Size(1));

		if ( m.getSizeN() == v.getSize() ) {
			// Vector is set vertically.
			Mat<T> r(m.getSizeM(), Size(1));
			for ( Size i(0); i < r.getSizeM(); i++ ) {
				T value(0);

				for ( Size k(0); k < m.getSizeN(); k++ ) {
					value += m.getValueI(i, k) * v.getValueI(k);
				}

				r.setValueI(i, Size(0), value);
			}
			return r;
		} else {
			// Vector is set horizontally.
			Mat<T> r(m.getSizeM(), v.getSize());
			for ( Size i(0); i < r.getSizeM(); i++ ) {
				for ( Size j(0); j < r.getSizeN(); j++ ) {
					r.setValueI(i, j, m.getValueI(i, Size(0)) * v.getValueI(j));
				}
			}
			return r;
		}
	}

	template<typename T>
	Mat<T> operator*(const Table<T>& v, const Mat<T>& m) {
		ASSERT_SPP(v.getSize() == m.getSizeM() || Size(1) == m.getSizeM());

		if ( v.getSize() == m.getSizeM() ) {
			// Vector is set horizontally.
			Mat<T> r(Size(1), m.getSizeN());
			for ( Size j(0); j < r.getSizeN(); j++ ) {
				T value(0);

				for ( Size k(0); k < m1.getSizeN(); k++ ) {
					value += v.getValueI(k) * m.getValueI(k, j);
				}

				r.setValueI(Size(0), j, value);
			}
			return r;
		} else {
			// Vector is set vertically.
			Mat<T> r(v.getSize(), m.getSizeM());
			for ( Size i(0); i < r.getSizeM(); i++ ) {
				for ( Size j(0); j < r.getSizeN(); j++ ) {
					r.setValueI(i, j, v.getValueI(i) * m.getValueI(Size(0), j));
				}
			}
			return r;
		}
	}

	template<typename T>
	Mat<T> operator*(const Mat<T>& m, const T& s) {
		return apply(Math::Operations::Mul(), m, s);
	}

	template<typename T>
	Mat<T> operator*(const T& s, const Mat<T>& m) {
		return apply(Math::Operations::Mul(), s, m);
	}

	template<typename T>
	Mat<T> operator/(const Mat<T>& m, const T& s) {
		return apply(Math::Operations::Div(), m, s);
	}

	template<typename T>
	Mat<T> operator/(const T& s, const Mat<T>& m) {
		return apply(Math::Operations::Div(), s, m);
	}

}