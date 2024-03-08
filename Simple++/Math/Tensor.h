#pragma once

#include "../IO/BasicIO.h"
#include "../String.h"
#include "../JSON/Node.h"

#include "BasicMath.h"
#include "Vec.h"

namespace Math {

	template<typename T>
	class Tensor : public BasicVector<T>, public JSON::Jsonable {
	public:
		class View {
		public:
			/************************************************************************/
			/* ================             CONSTRUCTOR            ================ */
			/************************************************************************/

			View(Tensor<T>& tensor, const Size finalIndex, const Size currentDim);

			/************************************************************************/
			/* ================               ACCESS               ================ */
			/************************************************************************/

			const typename Tensor<T>::View operator[](const Size i) const;
			typename Tensor<T>::View operator[](const Size i);

			/************************************************************************/
			/* ================                MISC                ================ */
			/************************************************************************/

			operator const Tensor<T>() const;
			operator Tensor<T>();

			operator const T& ( ) const;
			operator T& ( );

			Tensor<T> toTensor() const;

			const Size getDim() const;

		private:
			T* getData() const;

			Tensor<T>& tensor;
			Size finalIndex;
			Size currentDim;
		};

		template<typename C>
		friend class Tensor;

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
		template<typename C>
		Tensor(const BasicVector<Size>& sizes, const C* dataTable);
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

		const typename Tensor<T>::View operator[](const Size i) const;
		typename Tensor<T>::View operator[](const Size i);

		const T& operator[](const BasicVector<T> & indexes) const;
		T& operator[](const BasicVector<T>& indexes);

		/************************************************************************/
		/* ================                MISC                ================ */
		/************************************************************************/

		using BasicVector<T>::getSize;
		const Size getSize(const Size dim) const;

		const BasicVector<Size>& getSizes() const;

		using BasicVector<T>::resize;
		void resize(const BasicVector<Size>& newSizes);

		using BasicVector<T>::resizeNoCopy;
		void resizeNoCopy(const BasicVector<Size>& newSizes);

		const Size getDim() const;

		template<typename S = String>
		S toString() const;

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
		JSON::BasicNodeT<C>* toJSON() const;

	protected:
		Size getNbElem(const BasicVector<Size>& sizes) const;
		Size getNbElem(const Size dim) const;

		BasicVector<Size> sizes;

	private:
		template<typename S = String>
		S _toString() const;

		template<typename C = UTF8String>
		bool _getSizeJSON(const JSON::BasicNodeT<C>* node, BasicVector<Size> & sizes);

		template<typename C = UTF8String>
		bool _fromJSON(const JSON::BasicNodeT<C>* node, T * dataTable, const Size currentDim = Size(0));

		template<typename C = UTF8String>
		JSON::BasicNodeT<C>* _toJSON(const T* dataTable, const Size currentDim = Size(0)) const;
	};

	template<typename T>
	using STensor = Tensor<T>;

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
	inline typename const Tensor<T>::View Tensor<T>::operator[](const Size i) const {
		return const_cast< Tensor<T> * >( this )->operator[](i);
	}

	template<typename T>
	inline typename Tensor<T>::View Tensor<T>::operator[](const Size i) {
		return Tensor<T>::View(*this, i, Size(1));
	}

	template<typename T>
	inline const T& Tensor<T>::operator[](const BasicVector<T>& indexes) const {
		return const_cast< Tensor<T> * >( this )->operator[](indexes);
	}

	template<typename T>
	inline T& Tensor<T>::operator[](const BasicVector<T>& indexes) {
		ASSERT_SPP(indexes.getSize() <= this->sizes.getSize());

		Size finalIndex(0);

		for ( Size i(0); i < indexes.getSize(); i++ ) {
			const Size& index(indexes[ i ]);
			const Size& size(this->sizes[ i ]);

			ASSERT_SPP(index < size);

			if ( i > Size(0) ) {
				finalIndex *= this->sizes[ i - Size(1) ];
			}
			finaleIndex += index;
		}

		return getValueI(finalIndex);
	}

	template<typename T>
	inline const Size Tensor<T>::getSize(const Size dim) const {
		return this->sizes[ dim ];
	}

	template<typename T>
	inline const BasicVector<Size>& Tensor<T>::getSizes() const {
		return this->sizes;
	}

	template<typename T>
	inline void Tensor<T>::resize(const BasicVector<Size>& newSizes) {
		BasicVector<T>::resize(getNbElem(newSizes));
		this->sizes = newSizes;
	}

	template<typename T>
	inline void Tensor<T>::resizeNoCopy(const BasicVector<Size>& newSizes) {
		BasicVector<T>::resizeNoCopy(getNbElem(newSizes));
		this->sizes = newSizes;
	}

	template<typename T>
	inline const Size Tensor<T>::getDim() const {
		return this->sizes.getSize();
	}

	template<typename T>
	template<typename C>
	inline Tensor<T>::Tensor(const BasicVector<Size>& sizes, const C* dataTable) :
		BasicVector<T>(dataTable, getNbElem(sizes)),
		sizes(sizes)
	{}

	template<typename T>
	inline Size Tensor<T>::getNbElem(const BasicVector<Size>& sizes) const {
		if ( sizes.getSize() == Size(0) ) {
			return Size(1);
		}

		Size nbElem(sizes[0]);
		for ( Size i(1); i < sizes.getSize(); i++ ) {
			nbElem *= sizes[ i ];
		}

		return nbElem;
	}

	template<typename T>
	inline Size Tensor<T>::getNbElem(const Size dim) const {
		if ( dim >= this->sizes.getSize() ) {
			return Size(1);
		}

		Size nbElem(this->sizes[ dim ]);
		for ( Size i(dim + Size(1)); i < sizes.getSize(); i++ ) {
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

	template<typename T>
	template<typename Stream>
	inline bool Tensor<T>::read( Stream * stream, int verbose ) {
		if ( !BasicVector<T>::read(stream) ) {
			return false;
		}

		if ( !IO::read( stream, &this->size, verbose - 1 ) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename Stream>
	inline bool Tensor<T>::write(Stream* stream) const {
		if ( !BasicVector<T>::write(stream) ) {
			return false;
		}

		if ( !IO::write(stream, &this->size) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename C>
	inline bool Tensor<T>::fromJSON(const JSON::BasicNodeT<C>* node) {

		BasicVector<Size> newSizes;
		if ( !_getSizeJSON(node, newSizes) ) {
			return false;
		}

		resizeNoCopy(newSizes);

		if ( !_fromJSON(node, this->dataTable, Size(0)) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	template<typename C>
	inline JSON::BasicNodeT<C>* Tensor<T>::toJSON() const {
		return _toJSON(this->dataTable, Size(0));
	}

	template<typename T>
	template<typename S>
	inline S Tensor<T>::_toString() const {
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

	template<typename T>
	template<typename C>
	inline bool Tensor<T>::_getSizeJSON(const JSON::BasicNodeT<C>* node, BasicVector<Size>& sizes) {

		Size nbDim(0);
		{
			const JSON::BasicNodeT<C>* tmpNode(node);
			while ( true ) {
				if ( tmpNode->getType() == JSON::BasicNodeT<C>::Type::Value ) {
					break;
				}
				if ( tmpNode->getType() != JSON::BasicNodeT<C>::Type::Array ) {
					return false;
				}
				if ( tmpNode->getNbChildren() == Size(0) ) {
					return false;
				}

				nbDim++;
				tmpNode = tmpNode->getChild(0);
			}
		}

		sizes.resizeNoCopy(nbDim);

		{
			Size dimI(0);
			const JSON::BasicNodeT<C>* tmpNode(node);
			while ( true ) {
				if ( tmpNode->getType() == JSON::BasicNodeT<C>::Type::Value ) {
					break;
				}
				if ( tmpNode->getType() != JSON::BasicNodeT<C>::Type::Array ) {
					return false;
				}
				if ( tmpNode->getNbChildren() == Size(0) ) {
					return false;
				}

				sizes[ dimI ] = tmpNode->getNbChildren();
				tmpNode = tmpNode->getChild(0);
				dimI++;
			}
		}

		return true;
	}

	template<typename T>
	template<typename C>
	inline bool Tensor<T>::_fromJSON(const JSON::BasicNodeT<C>* node, T* dataTable, const Size currentDim) {
		// If scalar
		if ( currentDim >= getDim() ) {
			if ( node->getType() != JSON::BasicNodeT<C>::Type::Value ) {
				return false;
			}
			if ( !JSON::fromJSON(node, dataTable) ) {
				return false;
			}

			return true;
		}

		if ( node->getNbChildren() != getSize(currentDim) ) {
			return false;
		}

		for ( Size i(0); i < getSize(currentDim); i++ ) {
			const JSON::BasicNodeT<C>* nodeChild(node->getChild(i));
			const Size nextDim(currentDim + Size(1));
			if ( !_fromJSON(nodeChild, dataTable + getNbElem(nextDim) * i, nextDim) ) {
				return false;
			}
		}

		return true;
	}

	template<typename T>
	template<typename C>
	inline JSON::BasicNodeT<C>* Tensor<T>::_toJSON(const T* dataTable, const Size currentDim) const {
		// If scalar
		if ( currentDim >= getDim() ) {
			return JSON::toJSON(*dataTable);
		}

		JSON::NodeArrayT<C>* newNodeArray(new JSON::NodeArrayT<C>());

		for ( Size i(0); i < getSize(currentDim); i++ ) {
			const Size nextDim(currentDim + Size(1));
			JSON::BasicNodeT<C>* newNode(_toJSON(dataTable + getNbElem(nextDim) * i, nextDim));

			newNodeArray->addChild(newNode);
		}

		return newNodeArray;
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
	inline Tensor<T>::~Tensor() {

	}

	template<typename T>
	inline Tensor<T>::View::View(Tensor<T>& tensor, const Size finalIndex, const Size currentDim) :
		tensor(tensor),
		finalIndex(finalIndex),
		currentDim(currentDim)
	{}

	template<typename T>
	inline typename const Tensor<T>::View Tensor<T>::View::operator[](const Size i) const {
		return const_cast< Tensor<T>::View * >( this )->operator[](i);
	}

	template<typename T>
	inline typename Tensor<T>::View Tensor<T>::View::operator[](const Size i) {
		Size finalIndex(this->finalIndex);

		finalIndex *= this->tensor.getSize(this->currentDim);
		finalIndex += i;

		Size currentDim(this->currentDim + Size(1));

		return Tensor<T>::View(this->tensor, finalIndex, currentDim);
	}

	template<typename T>
	inline Tensor<T>::View::operator const Tensor<T>( ) const {
		return const_cast< Tensor<T>::View * >( this )->operator Tensor<T>();
	}

	template<typename T>
	inline Tensor<T>::View::operator Tensor<T>() {
		return toTensor();
	}

	template<typename T>
	inline Tensor<T>::View::operator const T& ( ) const {
		return this->tensor.getValueI(this->finalIndex);
	}

	template<typename T>
	inline Tensor<T>::View::operator T& ( ) {
		return this->tensor.getValueI(this->finalIndex);
	}

	template<typename T>
	inline Tensor<T> Tensor<T>::View::toTensor() const {
		Size offset(this->finalIndex);

		if ( this->currentDim < this->tensor.getDim() ) {
			BasicVector<Size> newSizes(this->tensor.sizes.getData() + this->currentDim, this->tensor.getDim() - this->currentDim);
			for ( Size i(this->currentDim); i < this->tensor.getDim(); i++ ) {
				offset *= this->tensor.getSize(i);
			}

			return Tensor<T>(newSizes, this->tensor.getData() + offset);
		} else {
			return Tensor<T>(BasicVector<Size>(), this->tensor.getData() + this->finalIndex);
		}
	}

	template<typename T>
	inline const Size Tensor<T>::View::getDim() const {
		return this->tensor.getDim() - this->currentDim;
	}

	template<typename T>
	inline T* Tensor<T>::View::getData() const {
		Size offset(this->finalIndex);

		for ( Size i(this->currentDim); i < this->tensor.getDim() - Size(1); i++ ) {
			offset *= this->tensor.getSize(i);
		}

		return this->tensor.getData() + offset;
	}

}