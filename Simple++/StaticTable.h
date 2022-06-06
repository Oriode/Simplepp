#pragma once

#include "Utility.h"

template<typename T, Size N>
class StaticTable {
public:
	StaticTable();
	template<typename C>
	StaticTable(const StaticTable<C, N>& t);
	StaticTable(const StaticTable<T, N>& t);

	template<typename C>
	StaticTable<T, N>& operator=(const StaticTable<C, N>& t);
	StaticTable<T, N>& operator=(const StaticTable<T, N>& t);

	const T& operator[](const Size i) const;
	T& operator[](const Size i);

	constexpr Size getSize() const;

	const T* getData() const;
	T* getData();

private:
	T dataTable[ N ];
};

template<typename T, Size N>
inline StaticTable<T, N>::StaticTable() {}

template<typename T, Size N>
inline constexpr Size StaticTable<T, N>::getSize() const {
	return N;
}

template<typename T, Size N>
inline const T* StaticTable<T, N>::getData() const {
	return this->dataTable;
}

template<typename T, Size N>
inline T* StaticTable<T, N>::getData() {
	return this->dataTable;
}

template<typename T, Size N>
template<typename C>
inline StaticTable<T, N>::StaticTable(const StaticTable<C, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);
}

template<typename T, Size N>
template<typename C>
inline StaticTable<T, N>& StaticTable<T, N>::operator=(const StaticTable<C, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);

	return *this;
}

template<typename T, Size N>
inline StaticTable<T, N>& StaticTable<T, N>::operator=(const StaticTable<T, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);

	return *this;
}

template<typename T, Size N>
inline const T& StaticTable<T, N>::operator[](const Size i) const {
	return this->dataTable[ i ];
}

template<typename T, Size N>
inline T& StaticTable<T, N>::operator[](const Size i) {
	return this->dataTable[ i ];
}

template<typename T, Size N>
inline StaticTable<T, N>::StaticTable(const StaticTable<T, N>& t) {
	Utility::copy(this->dataTable, t.getData(), N);
}
