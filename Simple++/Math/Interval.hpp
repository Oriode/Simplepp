#include "Interval.h"

namespace Math {

	template<typename T>
	Interval<T>::Interval() {

	}

	template<typename T>
	Interval<T>::Interval(const T begin, const T end) :
		Vec2<T>(begin, end) {

	}

	template<typename T>
	inline Interval<T>::Interval(const Vec2<T>& v) :
		Vec2<T>(v)
	{}

	template<typename T>
	const T & Interval<T>::getBegin() const {
		return this -> begin;
	}

	template<typename T>
	const T & Interval<T>::getEnd() const {
		return this -> end;
	}

	template<typename T>
	void Interval<T>::setBegin(const T& begin) {
		this->begin = begin;
	}

	template<typename T>
	void Interval<T>::setEnd(const T& end) {
		this->end = end;
	}

	template<typename T>
	inline T Interval<T>::getMean() const {
		return ( this->begin + this->end ) / T(2.0);
	}

	template<typename T>
	bool Interval<T>::intersect(const Interval<T>& interval) const {
		if ( isInside(interval) ) {
			return true;
		}
		if ( interval.getBegin() < this->begin && interval.getEnd() > this->begin ) {
			return true;
		}
		if ( interval.getBegin() < this->end && interval.getEnd() > this->end ) {
			return true;
		}
		return false;
	}

	template<typename T>
	bool Interval<T>::isInside(const T& v) const {
		return v >= this->begin && v <= this->end;
	}

	template<typename T>
	bool Interval<T>::isInside(const Interval<T>& interval) const {
		if ( interval.getBegin() <= this->begin && interval.getEnd() >= this->end ) {
			return true;
		} else {
			return false;
		}
	}

	template<typename T>
	inline Interval<T> Interval<T>::getIntersect(const Interval<T>& interval) const {
		if ( this->begin > interval.getBegin() ) {
			if ( this->begin < interval.getEnd() ) {
				if ( this->end < interval.getEnd() ) {
					return Interval<T>(this->begin, this->end);
				} else {
					return Interval<T>(this->begin, interval.getEnd());
				}
			} else {
				// No Intersect.
				return Interval<T>(T(0.0), T(0.0));
			}
		} else {
			if ( this->end > interval.getBegin() ) {
				if ( this->end > interval.getEnd() ) {
					return Interval<T>(interval.getBegin(), interval.getEnd());
				} else {
					return Interval<T>(interval.getBegin(), this->end);
				}
			} else {
				// No Intersect.
				return Interval<T>(T(0.0), T(0.0));
			}
		}
	}

	template<typename T>
	inline void Interval<T>::sort() {
		if ( this->begin > this->end ) {
			const T tmpBegin(this->begin);
			this->begin = this->end;
			this->end = tmpBegin;
		}
	}

	template<typename T>
	inline T Interval<T>::scale(const T& v) const {
		const T size(getSize());
		if ( size == T(0) ) {
			return T(0);
		} else {
			return ( v - this->begin ) / getSize();
		}
	}

	template<typename T>
	inline T Interval<T>::unscale(const T& v) const {
		return v * getSize() + this->begin;
	}

	template<typename T>
	inline Vector<Interval<T>> Interval<T>::split(const Size nbSplits) const {

		const Size intervalSize(getSize());

		if ( intervalSize == Size(0) ) {
			return Vector<Interval<T>>();
		}

		Vector<Interval<T>> splitVector;
		const Size nbSplitsSafe(Math::min(nbSplits, intervalSize));

		splitVector.reserve(nbSplitsSafe);

		const double splitSizeF(double(intervalSize) / double(nbSplitsSafe));
		double endIF(static_cast<double>(getBegin()));
		T beginI(getBegin());
		for ( Size i(0); i < nbSplitsSafe; i++ ) {
			endIF += splitSizeF;

			Interval<T> newInterval(beginI, T(endIF));
			splitVector.push(newInterval);

			beginI = T(endIF);
		}

		// To overcome precision issues.
		splitVector.getLast().setEnd(getEnd());

		return splitVector;
	}

	template<typename T>
	template<typename S>
	S Interval<T>::toString() const {
		S outString;
		outString.reserve(20);

		outString << S::ElemType('{');
		outString << this->begin;
		outString << S::ElemType(',');
		outString << S::ElemType(' ');
		outString << this->end;
		outString << S::ElemType('}');

		return outString;
	}

	template<typename T>
	T Interval<T>::getSize() const {
		return this->end - this->begin;
	}

	template<typename T>
	T Interval<T>::getMax(const T i, const T delta) const {
		T max(i + delta);
		if ( max > this->end ) {
			return this->end;
		} else {
			return max;
		}
	}

	template<typename T>
	T Interval<T>::getMin(const T i, const T delta) const {
		if ( i < this->begin + delta ) {
			return this->begin;
		} else {
			return i - delta;
		}
	}

}