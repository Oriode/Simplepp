#pragma once

#include "../IO/BasicIO.h"
#include "../String.h"

#include "BasicMath.h"
#include "Vec.h"

namespace Math {

	template<typename T>
	class TensorView;

	template<typename T, bool Static = false>
	class Tensor : public BasicVector<T, Static> {
	public:
		template<typename C, bool Static2>
		friend class Tensor;

		template<typename C>
		friend class TensorView;

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
		Tensor(const Tensor<T, Static>& tensor);
		Tensor(Tensor<T, Static>&& tensor);

		~Tensor();

		/************************************************************************/
		/* ================            COPY OPERATOR           ================ */
		/************************************************************************/

		template<typename C, Size N>
		Tensor<T, Static>& operator=(const C(&v)[ N ]);
		template<typename C, Size M, Size N>
		Tensor<T, Static>& operator=(const C(&v)[ M ][ N ]);
		template<typename C>
		Tensor<T, Static>& operator=(const Tensor<C>& tensor);
		Tensor<T, Static>& operator=(const Tensor<T, Static>& tensor);
		Tensor<T, Static>& operator=(Tensor<T, Static>&& tensor);

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		const TensorView<T> operator[](const Size i) const;
		TensorView<T> operator[](const Size i);

		const T& operator[](const BasicVector<T, Static> & indexes) const;
		T& operator[](const BasicVector<T, Static>& indexes);

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		operator const T& ( ) const;
		operator T& ( );

		using BasicVector<T, Static>::getSize;
		const Size getSize(const Size dim) const;

		const Size getDim() const;

		template<typename S = String>
		S toString() const;

	protected:
		Tensor(const BasicVector<Size, true> & sizes, T* dataTable);

		Size getNbElem(const BasicVector<Size, Static>& sizes) const;

		BasicVector<Size, Static> sizes;

	private:
		template<typename S = String>
		S _toString() const;
	};

	template<typename T>
	class TensorView {
	public:
		TensorView(Tensor<T, false>& tensor, const Size finalIndex, const Size currentDim);

		/************************************************************************/
		/* ================               ACCESS               ================ */
		/************************************************************************/

		const TensorView<T> operator[](const Size i) const;
		TensorView<T> operator[](const Size i);

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		operator const Tensor<T, true>() const;
		operator Tensor<T, true>();

		const Tensor<T, true> toTensor() const;
		Tensor<T, true> toTensor();

		const Size getDim() const;

	private:
		T* getData() const;

		Tensor<T, false>& tensor;
		Size finalIndex;
		Size currentDim;
	};

	template<typename T>
	using STensor = Tensor<T, true>;

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor() {}

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor(const Size n) :
		BasicVector<T, Static>(n),
		sizes(Size(1))
	{
		this->sizes[ 0 ] = n;
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor(const Size m, const Size n) :
		BasicVector<T, Static>(m * n),
		sizes(Size(2))
	{
		this->sizes[ 0 ] = m;
		this->sizes[ 1 ] = n;
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor(const BasicVector<Size>& sizes) :
		BasicVector<T, Static>(getNbElem(sizes)),
		sizes(sizes)
	{}

	template<typename T, bool Static>
	inline const TensorView<T> Tensor<T, Static>::operator[](const Size i) const {
		return const_cast< Tensor<T, Static> * >( this )->operator[](i);
	}

	template<typename T, bool Static>
	inline TensorView<T> Tensor<T, Static>::operator[](const Size i) {
		return TensorView<T>(*this, i, Size(1));
	}

	template<typename T, bool Static>
	inline const T& Tensor<T, Static>::operator[](const BasicVector<T, Static>& indexes) const {
		return const_cast< Tensor<T, Static> * >( this )->operator[](indexes);
	}

	template<typename T, bool Static>
	inline T& Tensor<T, Static>::operator[](const BasicVector<T, Static>& indexes) {
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

		return getValueI(finalIndex);
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>::operator const T& ( ) const {
		return this->dataTable[ 0 ];
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>::operator T& ( ) {
		return this->dataTable[ 0 ];
	}

	template<typename T, bool Static>
	inline const Size Tensor<T, Static>::getSize(const Size dim) const {
		return this->sizes[ dim ];
	}

	template<typename T, bool Static>
	inline const Size Tensor<T, Static>::getDim() const {
		return this->sizes.getSize();
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor(const BasicVector<Size, true>& sizes, T* dataTable) :
		BasicVector<T, Static>(getNbElem(sizes), dataTable),
		sizes(sizes)
	{}

	template<typename T, bool Static>
	inline Size Tensor<T, Static>::getNbElem(const BasicVector<Size, Static>& sizes) const {
		if ( sizes.getSize() == Size(0) ) {
			return Size(1);
		}

		Size nbElem(sizes[0]);
		for ( Size i(1); i < sizes.getSize(); i++ ) {
			nbElem *= sizes[ i ];
		}

		return nbElem;
	}

	template<typename T, bool Static>
	template<typename C, Size N>
	inline Tensor<T, Static>::Tensor(const C(&v)[ N ]) :
		BasicVector<T, Static>(v),
		sizes(Size(1))
	{
		this->sizes[ 0 ] = N;
	}

	template<typename T, bool Static>
	template<typename C, Size M, Size N>
	inline Tensor<T, Static>::Tensor(const C(&v)[ M ][ N ]) :
		BasicVector<T, Static>(reinterpret_cast<const C *>(v), M * N),
		sizes(Size(2))
	{
		this->sizes[ 0 ] = M;
		this->sizes[ 1 ] = N;
	}

	template<typename T, bool Static>
	template<typename C, Size X, Size Y, Size Z>
	inline Tensor<T, Static>::Tensor(const C(&v)[ X ][ Y ][ Z ]) :
		BasicVector<T, Static>(reinterpret_cast< const C* >( v ), X * Y * Z),
		sizes(Size(3))
	{
		this->sizes[ 0 ] = X;
		this->sizes[ 1 ] = Y;
		this->sizes[ 2 ] = Z;
	}

	template<typename T, bool Static>
	template<typename C>
	inline Tensor<T, Static>::Tensor(const Tensor<C>& tensor) :
		BasicVector<T, Static>(tensor),
		sizes(tensor.sizes)
	{}

	template<typename T, bool Static>
	template<typename C, Size N>
	inline Tensor<T, Static>& Tensor<T, Static>::operator=(const C(&v)[ N ]) {
		BasicVector<T, Static>::operator=(v);

		this->sizes.resizeNoCopy(Size(1));
		this->sizes[ 0 ] = N;

		return *this;
	}

	template<typename T, bool Static>
	template<typename C, Size M, Size N>
	inline Tensor<T, Static>& Tensor<T, Static>::operator=(const C(&v)[ M ][ N ]) {
		resizeNoCopy(M * N);

		Utility::copy(this->dataTable, reinterpret_cast<const C *>(v), this->size);

		this->sizes.resizeNoCopy(Size(1));
		this->sizes[ 0 ] = N;

		return *this;
	}

	template<typename T, bool Static>
	template<typename C>
	inline Tensor<T, Static>& Tensor<T, Static>::operator=(const Tensor<C>& tensor) {
		BasicVector<T, Static>::operator=(tensor);
		this->sizes = tensor.sizes;

		return *this;
	}

	template<typename T, bool Static>
	template<typename S>
	inline S Tensor<T, Static>::toString() const {
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

		if ( getDim() == Size(0) ) {
			outputStr << S::ElemType('0');
		} else if ( getDim() == Size(1) ) {
			outputStr << S::ElemType('[');
			outputStr << S::ElemType(' ');

			for ( Size i(0); i < getSize(Size(0)); i++ ) {
				if ( i > Size(0) ) {
					outputStr << S::ElemType(',');
					outputStr << S::ElemType(' ');
				}
				outputStr << getValueI(i);
			}

			outputStr << S::ElemType(' ');
			outputStr << S::ElemType(']');
		} else {

			for ( Size i(0); i < getSize(Size(0)); i++ ) {
				if ( i > Size(0) ) {
					outputStr << S::ElemType('\n');
				}
				outputStr << operator[](i).toTensor()._toString<S>();
			}

		}

		return outputStr;
	}

	template<typename T, bool Static>
	template<typename S>
	inline S Tensor<T, Static>::_toString() const {
		S outputStr;

		if ( getDim() == Size(0) ) {
			outputStr << getValueI(Size(0));
		} else {
			outputStr << S::ElemType('[');
			outputStr << S::ElemType(' ');

			for ( Size i(0); i < getSize(Size(0)); i++ ) {
				if ( i > Size(0) ) {
					outputStr << S::ElemType(',');
					outputStr << S::ElemType(' ');
				}
				outputStr << operator[](i).toTensor()._toString<S>();
			}

			outputStr << S::ElemType(' ');
			outputStr << S::ElemType(']');
		}

		return outputStr;
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>& Tensor<T, Static>::operator=(const Tensor<T, Static>& tensor) {
		BasicVector<T, Static>::operator=(tensor);
		this->sizes = tensor.sizes;

		return *this;
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>& Tensor<T, Static>::operator=(Tensor<T, Static>&& tensor) {
		BasicVector<T, Static>::operator=(Utility::toRValue(tensor));
		this->sizes = Utility::toRValue(tensor.sizes);

		return *this;
	}

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor(const Tensor<T, Static>& tensor) :
		BasicVector<T, Static>(tensor),
		sizes(tensor.sizes) {}

	template<typename T, bool Static>
	inline Tensor<T, Static>::Tensor(Tensor<T, Static>&& tensor) :
		BasicVector<T, Static>(Utility::toRValue(tensor)),
		sizes(Utility::toRValue(tensor))
	{}

	template<typename T, bool Static>
	inline Tensor<T, Static>::~Tensor() {

	}

	template<typename T>
	inline TensorView<T>::TensorView(Tensor<T, false>& tensor, const Size finalIndex, const Size currentDim) :
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
	inline TensorView<T>::operator const Tensor<T, true>( ) const {
		return const_cast< TensorView<T> * >( this )->operator Tensor<T, true>();
	}

	template<typename T>
	inline TensorView<T>::operator Tensor<T, true>() {
		return toTensor();
	}

	template<typename T>
	inline const Tensor<T, true> TensorView<T>::toTensor() const {
		return const_cast< TensorView<T> * >( this )->toTensor();
	}

	template<typename T>
	inline Tensor<T, true> TensorView<T>::toTensor() {
		Size offset(this->finalIndex);

		if ( this->currentDim < this->tensor.getDim() ) {
			BasicVector<Size, true> newSizes(this->tensor.getDim() - this->currentDim, this->tensor.sizes.getData() + this->currentDim);
			for ( Size i(this->currentDim); i < this->tensor.getDim(); i++ ) {
				// newSizes[ i - this->currentDim ] = this->tensor.getSize(i);
				offset *= this->tensor.getSize(i);
			}

			return Tensor<T, true>(newSizes, this->tensor.getData() + offset);
		} else {
			return Tensor<T, true>(BasicVector<Size, true>(), this->tensor.getData() + this->finalIndex);
		}
	}

	template<typename T>
	inline const Size TensorView<T>::getDim() const {
		return this->tensor.getDim() - this->currentDim;
	}

	template<typename T>
	inline T* TensorView<T>::getData() const {
		Size offset(this->finalIndex);

		for ( Size i(this->currentDim); i < this->tensor.getDim() - Size(1); i++ ) {
			offset *= this->tensor.getSize(i);
		}

		return this->tensor.getData() + offset;
	}

}