#pragma once

#include "../IO/BasicIO.h"
#include "../String.h"

#include "BasicMath.h"
#include "Vec.h"

namespace Math {

	//template<typename T>
	//class MatView {
	//public:
	//	MatView(Mat<T>& M, const Size i);
	//
	//	const Mat<T>& getMat() const;
	//	const Size getI() const;
	//
	//private:
	//	Mat<T>& M;
	//	const Size i;
	//};
	//
	//template<typename T>
	//class MatViewCol : public MatView<T> {
	//public:
	//	MatViewCol(Mat<T>& M, const Size i);
	//};
	//
	//template<typename T>
	//class MatViewRow : public MatView<T> {
	//public:
	//	MatViewRow(Mat<T>& M, const Size i);
	//};

	template<typename T>
	class Mat {
	public:
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

		const Vec<T>& operator[](const Size m) const;
		Vec<T>& operator[](const Size m);

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
		void fill(const T& v);

		template<typename S = String>
		S toString() const;

	private:
		Size m;
		Size n;

		Vec<Vec<T>> v;
	};

	template<typename T>
	inline Mat<T>::Mat() {}

	template<typename T>
	inline Mat<T>::Mat(const Size m, const Size n) :
		m(m),
		n(n),
		v(m)
	{
		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ].resizeNoCopy(m);
		}
	}

	template<typename T>
	inline Mat<T>::Mat(Mat&& mat) :
		m(Utility::toRValue(mat.m)),
		n(Utility::toRValue(mat.n)),
		v(Utility::toRValue(mat.v))
	{}

	template<typename T>
	inline Mat<T>::~Mat() {}

	template<typename T>
	inline const Vec<T>& Mat<T>::operator[](const Size m) const {
		return this->v[ m ];
	}

	template<typename T>
	inline Vec<T>& Mat<T>::operator[](const Size m) {
		return this->v[ m ];
	}

	template<typename T>
	inline void Mat<T>::resize(const Size newM, const Size newN) {
		if ( newM == getSizeM() && newN == getSizeN() ) {
			return;
		}
		this->v.resize(newM);
		this->m = newM;

		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ].resize(newN);
		}

		this->n = newN;
	}

	template<typename T>
	inline void Mat<T>::resizeNoCopy(const Size newM, const Size newN) {
		if ( newM == getSizeM() && newN == getSizeN() ) {
			return;
		}
		this->v.resizeNoCopy(newM);
		this->m = newM;

		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ].resizeNoCopy(newN);
		}

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
		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ].zeros();
		}
	}

	template<typename T>
	inline void Mat<T>::ones() {
		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ].ones();
		}
	}

	template<typename T>
	inline void Mat<T>::identity() {
		for ( Size i(0); i < getSizeM(); i++ ) {
			for ( Size j(0); j < getSizeN(); j++ ) {
				if ( i == j ) {
					this->v[ i ][ j ] = T(1);
				} else {
					this->v[ i ][ j ] = T(0);
				}
			}
		}
	}

	template<typename T>
	inline void Mat<T>::fill(const T& v) {
		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ].fill(v);
		}
	}

	template<typename T>
	template<typename C, Size M, Size N>
	inline Mat<T>::Mat(const C(&v)[ M ][ N ]) :
		m(M),
		n(N),
		v(M)
	{
		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ] = v[ i ];
		}
	}

	template<typename T>
	template<typename C>
	inline Mat<T>::Mat(const Mat<C>& mat) :
		m(mat.m),
		n(mat.n),
		v(mat.v)
	{}

	template<typename T>
	inline Mat<T>::Mat(const Mat<T>& mat) :
		m(mat.m),
		n(mat.n),
		v(mat.v) {}

	template<typename T>
	template<typename C, Size M, Size N>
	inline Mat<T>& Mat<T>::operator=(const C(&v)[ M ][ N ]) {
		this->m = M;
		this->n = N;
		this->v.resizeNoCopy(this->m);

		for ( Size i(0); i < getSizeM(); i++ ) {
			this->v[ i ] = v[ i ];
		}

		return *this;
	}

	template<typename T>
	template<typename C>
	inline Mat<T>& Mat<T>::operator=(const Mat<C>& mat) {
		this->m = mat.m;
		this->n = mat.n;
		this->v = mat.v;

		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator=(const Mat<T>& mat) {
		this->m = mat.m;
		this->n = mat.n;
		this->v = mat.v;

		return *this;
	}

	template<typename T>
	inline Mat<T>& Mat<T>::operator=(Mat<T>&& mat) {
		this->m = Utility::toRValue(mat.m);
		this->n = Utility::toRValue(mat.n);
		this->v = Utility::toRValue(mat.v);

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
			outputStr << this->v[ i ].toString();
		}

		return outputStr;
	}

}