#pragma once

#include "../IO/BasicIO.h"
#include "../String.h"

#include "BasicMath.h"
#include "Vec.h"

namespace Math {

	template<typename T>
	class Mat : public BasicVector<T> {
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

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		void resize(const Size newM, const Size newN);
		void resizeNoCopy(const Size newM, const Size newN);

		const Size getSizeM() const;
		const Size getSizeN() const;

		void zeros();
		void ones();
		void identity();

		template<typename S = String>
		S toString() const;

		const Size getNbElem(const Size m, const Size n) const;

	private:
		Size m;
		Size n;
	};

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
	inline void Mat<T>::zeros() {
		BasicVector<T>::fill(T(0));
	}

	template<typename T>
	inline void Mat<T>::ones() {
		BasicVector<T>::fill(T(1));
	}

	template<typename T>
	inline void Mat<T>::identity() {
		for ( Size i(0); i < getSizeM(); i++ ) {
			for ( Size j(0); j < getSizeN(); j++ ) {
				if ( i == j ) {
					operator[](i)[j] = T(1);
				} else {
					operator[](i)[ j ] = T(0);
				}
			}
		}
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

}