#pragma once

#include "Vec2.h"
#include "../IO/BasicIO.h"
#include "../IO/IO.h"
#include "../String.h"

namespace Math {

	///@brief Representing an Interval between two values.
	///			This class is "unsigned" safe.
	template<typename T>
	class Interval : public Vec2<T>, public IO::BasicIO {
	public:
		Interval();
		Interval(const T begin, const T end);

		const T getBegin() const;
		const T getEnd() const;

		void setBegin(const T& begin);
		void setEnd(const T& end);

		///@brief Get the safe candle index of "i - delta".
		///@param i Current index.
		///@param delta T to rollback.
		///@return Safe index inside the Interval.
		T getMin(const T i, const T delta) const;

		///@brief Get the safe candle index of "i + delta".
		///@param i Current index.
		///@param delta T to add.
		///@return Safe index inside the Interval.
		T getMax(const T i, const T delta) const;

		///@brief Get the size of this Interval.
		///@return Interval size.
		T getSize() const;

		bool intersect(const Interval<T>& interval) const;

		bool isInside(const T& v) const;

		bool isInside(const Interval<T>& interval) const;

		///@brief Get the intersection Interval of another Interval and this one. Return Interval<T>(T(0.0), T(0.0)) if no intersection.
		Interval<T> getIntersect(const Interval<T>& interval) const;

		///@brief Ensure begin < end.
		void sort();

		String toString() const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read(Stream* stream);

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write(Stream* stream) const;

	};

}

#include "Interval.hpp"