#pragma once

#include "../IO/BasicIO.h"
#include "../String.h"

#include "BasicMath.h"
#include "Vec.h"

namespace Math {

	template<typename T>
	class TensorView;

	template<typename T>
	class Tensor : public BasicVector<T> {
	public:
		/************************************************************************/
		/* ================             CONSTRUCTOR            ================ */
		/************************************************************************/

		Tensor();
		Tensor(const Size n);
		Tensor(const Size m, const Size n);
		Tensor(const BasicVector<Size> & sizes);
		template<typename C, Size N>
		Tensor(const C(&v)[ N ]);
		template<typename C, Size M, Size N>
		Tensor(const C(&v)[ M ][ N ]);
		template<typename C, Size X, Size Y, Size Z>
		Tensor(const C(&v)[ X ][ Y ][Z]);
		template<typename C>
		Tensor(const Tensor<C>& tensor);
		Tensor(const Tensor<T>& tensor);
		Tensor(Tensor<T>&& tensor);

		~Tensor();

		/************************************************************************/
		/* ================            COPY OPERATOR           ================ */
		/************************************************************************/

		template<typename C, Size N>
		Tensor<T>& operator=(const C(&v)[ N ]);
		template<typename C, Size M, Size N>
		Tensor<T>& operator=(const C(&v)[ M ][ N ]);
		template<typename C>
		Tensor<T>& operator=(const Tensor<C>& tensor);
		Tensor<T>& operator=(const Tensor<T>& tensor);
		Tensor<T>& operator=(Tensor<T>&& tensor);

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		const TensorView<T> operator[](const Size i) const;
		TensorView<T> operator[](const Size i);

		const T& operator[](const BasicVector<T> & indexes) const;
		T& operator[](const BasicVector<T>& indexes);

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		using BasicVector<T>::getSize;
		const Size getSize(const Size dim) const;

		const Size getDim() const;

		template<typename S = String>
		S toString() const;

	private:
		Size getNbElem(const BasicVector<T>& sizes) const;

		BasicVector<Size> sizes;
	};

	template<typename T>
	class TensorView {
	public:
		TensorView(Tensor<T>& tensor, const Size finalIndex, const Size currentDim);

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		const TensorView<T> operator[](const Size i) const;
		TensorView<T> operator[](const Size i);

		operator const T &() const;
		operator T &();

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		const Size getDim() const;

		template<typename S = String>
		S toString() const;

	private:
		Tensor<T>& tensor;
		Size finalIndex;
		Size currentDim;
	};

	template<typename T>
	inline Tensor<T>::Tensor() {}

	template<typename T>
	inline Tensor<T>::Tensor(const Size n) :
		BasicVector<T>(n),
		sizes(Size(1))
	{
		this->sizes[ 0 ] = n;
	}

	template<typename T>
	inline Tensor<T>::Tensor(const Size m, const Size n) :
		BasicVector<T>(m * n),
		sizes(Size(2))
	{
		this->sizes[ 0 ] = m;
		this->sizes[ 1 ] = n;
	}

	template<typename T>
	inline Tensor<T>::Tensor(const BasicVector<Size>& sizes) :
		BasicVector<T>(getNbElem(sizes)),
		sizes(sizes)
	{}

	template<typename T>
	inline const TensorView<T> Tensor<T>::operator[](const Size i) const {
		return const_cast< Tensor<T> * >( this )->operator[](i);
	}

	template<typename T>
	inline TensorView<T> Tensor<T>::operator[](const Size i) {
		return TensorView<T>(*this, i, Size(1));
	}

	template<typename T>
	inline const T& Tensor<T>::operator[](const BasicVector<T>& indexes) const {
		return const_cast< Tensor<T> * >( this )->operator[](indexes);
	}

	template<typename T>
	inline T& Tensor<T>::operator[](const BasicVector<T>& indexes) {
		assert(indexes.getSize() <= this->sizes.getSize());

		Size finalIndex(0);

		for ( Size i(0); i < indexes.getSize(); i++ ) {
			const Size& index(indexes[ i ]);
			const Size& size(this->sizes[ i ]);

			assert(index < size);

			if ( i > Size(0) ) {
				finalIndex *= this->sizes[ i - Size(1) ];
			}
			finaleIndex += index;
		}

		return BasicVector<T>::operator[](finalIndex);
	}

	template<typename T>
	inline const Size Tensor<T>::getSize(const Size dim) const {
		return this->sizes[ dim ];
	}

	template<typename T>
	inline const Size Tensor<T>::getDim() const {
		return this->sizes.getSize();
	}

	template<typename T>
	inline Size Tensor<T>::getNbElem(const BasicVector<T>& sizes) const {
		if ( sizes.getSize() == Size(0) ) {
			return Size(0);
		}

		Size nbElem(sizes[0]);
		for ( Size i(1); i < sizes.getSize(); i++ ) {
			nbElem *= sizes[ i ];
		}

		return nbElem;
	}

	template<typename T>
	template<typename C, Size N>
	inline Tensor<T>::Tensor(const C(&v)[ N ]) :
		BasicVector<T>(v),
		sizes(Size(1))
	{
		this->sizes[ 0 ] = N;
	}

	template<typename T>
	template<typename C, Size M, Size N>
	inline Tensor<T>::Tensor(const C(&v)[ M ][ N ]) :
		BasicVector<T>(reinterpret_cast<const C *>(v), M * N),
		sizes(Size(2))
	{
		this->sizes[ 0 ] = M;
		this->sizes[ 1 ] = N;
	}

	template<typename T>
	template<typename C, Size X, Size Y, Size Z>
	inline Tensor<T>::Tensor(const C(&v)[ X ][ Y ][ Z ]) :
		BasicVector<T>(reinterpret_cast< const C* >( v ), X * Y * Z),
		sizes(Size(3))
	{
		this->sizes[ 0 ] = X;
		this->sizes[ 1 ] = Y;
		this->sizes[ 2 ] = Z;
	}

	template<typename T>
	template<typename C>
	inline Tensor<T>::Tensor(const Tensor<C>& tensor) :
		BasicVector<T>(tensor),
		sizes(tensor.sizes)
	{}

	template<typename T>
	template<typename C, Size N>
	inline Tensor<T>& Tensor<T>::operator=(const C(&v)[ N ]) {
		BasicVector<T>::operator=(v);

		this->sizes.resizeNoCopy(Size(1));
		this->sizes[ 0 ] = N;

		return *this;
	}

	template<typename T>
	template<typename C, Size M, Size N>
	inline Tensor<T>& Tensor<T>::operator=(const C(&v)[ M ][ N ]) {
		resizeNoCopy(M * N);

		Utility::copy(this->dataTable, reinterpret_cast<const C *>(v), this->size);

		this->sizes.resizeNoCopy(Size(1));
		this->sizes[ 0 ] = N;

		return *this;
	}

	template<typename T>
	template<typename C>
	inline Tensor<T>& Tensor<T>::operator=(const Tensor<C>& tensor) {
		BasicVector<T>::operator=(tensor);
		this->sizes = tensor.sizes;

		return *this;
	}

	template<typename T>
	template<typename S>
	inline S Tensor<T>::toString() const {
		S outputStr;

		outputStr << S::ElemType('\n');
		outputStr << S::ElemType('=');
		outputStr << S::ElemType(' ');
		outputStr << S::ElemType('T');
		outputStr << S::ElemType('E');
		outputStr << S::ElemType('N');
		outputStr << S::ElemType('S');
		outputStr << S::ElemType('O');
		outputStr << S::ElemType('R');
		outputStr << S::ElemType(' ');

		for ( Size i(0); i < this->sizes.getSize(); i++ ) {
			if ( i > Size(0) ) {
				outputStr << S::ElemType('x');
			}
			outputStr << this->sizes[ i ];
		}

		outputStr << S::ElemType(' ');
		outputStr << S::ElemType('=');
		outputStr << S::ElemType('\n');

		if ( this->sizes.getSize() == Size(0) ) {
			outputStr << S::ElemType('0');
		} else if ( this->sizes.getSize() == Size(1) ) {
			outputStr << S::ElemType('[');
			outputStr << S::ElemType(' ');

			for ( Size i(0); i < getSize(Size(0)); i++ ) {
				if ( i > Size(0) ) {
					outputStr << S::ElemType(',');
					outputStr << S::ElemType(' ');
				}
				outputStr << operator[](i);
			}

			outputStr << S::ElemType(' ');
			outputStr << S::ElemType(']');
		} else {

			for ( Size i(0); i < getSize(Size(0)); i++ ) {
				if ( i > Size(0) ) {
					outputStr << S::ElemType('\n');
				}
				outputStr << operator[](i).toString<S>();
			}

		}

		return outputStr;
	}

	template<typename T>
	inline Tensor<T>& Tensor<T>::operator=(const Tensor<T>& tensor) {
		BasicVector<T>::operator=(tensor);
		this->sizes = tensor.sizes;

		return *this;
	}

	template<typename T>
	inline Tensor<T>& Tensor<T>::operator=(Tensor<T>&& tensor) {
		BasicVector<T>::operator=(Utility::toRValue(tensor));
		this->sizes = Utility::toRValue(tensor.sizes);

		return *this;
	}

	template<typename T>
	inline Tensor<T>::Tensor(const Tensor<T>& tensor) :
		BasicVector<T>(tensor),
		sizes(tensor.sizes) {}

	template<typename T>
	inline Tensor<T>::Tensor(Tensor<T>&& tensor) :
		BasicVector<T>(Utility::toRValue(tensor)),
		sizes(Utility::toRValue(tensor))
	{}

	template<typename T>
	inline Tensor<T>::~Tensor() {}

	template<typename T>
	inline TensorView<T>::TensorView(Tensor<T>& tensor, const Size finalIndex, const Size currentDim) :
		tensor(tensor),
		finalIndex(finalIndex),
		currentDim(currentDim)
	{}

	template<typename T>
	inline const TensorView<T> TensorView<T>::operator[](const Size i) const {
		return const_cast< TensorView<T> * >( this )->operator[](i);
	}

	template<typename T>
	inline TensorView<T> TensorView<T>::operator[](const Size i) {

		Size finalIndex(this->finalIndex);

		finalIndex *= this->tensor.getSize(this->currentDim);
		finalIndex += i;

		Size currentDim(this->currentDim + Size(1));

		return TensorView<T>(this->tensor, finalIndex, currentDim);
	}

	template<typename T>
	inline TensorView<T>::operator const T& ( ) const {
		return this->tensor.getValueI(this->finalIndex);
	}

	template<typename T>
	inline TensorView<T>::operator T &() {
		return this->tensor.getValueI(this->finalIndex);
	}

	template<typename T>
	inline const Size TensorView<T>::getDim() const {
		return this->tensor.getDim() - this->currentDim;
	}

	template<typename T>
	template<typename S>
	inline S TensorView<T>::toString() const {
		S outputStr;

		if ( getDim() == Size(0) ) {
			outputStr << this->tensor.getValueI(this->finalIndex);
		} else {
			outputStr << S::ElemType('[');
			outputStr << S::ElemType(' ');

			for ( Size i(0); i < this->tensor.getSize(this->currentDim); i++ ) {
				if ( i > Size(0) ) {
					outputStr << S::ElemType(',');
					outputStr << S::ElemType(' ');
				}
				outputStr << operator[](i).toString<S>();
			}

			outputStr << S::ElemType(' ');
			outputStr << S::ElemType(']');
		}

		return outputStr;
	}

}