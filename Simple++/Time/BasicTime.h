#pragma once

#include "../Math/BasicMath.h"

namespace Time {

	/** @brief	typename for not using this ugly underscore name */
	typedef time_t TimeT;

	template<typename T>
	class BasicTimeT {
	public:
		template<typename RatioOut, typename RatioIn>
		static TimeT convertTime(const TimeT& t);

	private:
		template<typename Ratio>
		static TimeT _convertTime(const TimeT& t, Ratio* rOut, Ratio* rIn);
		template<typename RatioOut, typename RatioIn>
		static TimeT _convertTime(const TimeT& t, RatioOut * rOut, RatioIn * rIn);
	};

	using BasicTime = BasicTimeT<int>;

	template<typename RatioOut, typename RatioIn>
	TimeT convertTime(const TimeT& t) { return BasicTime::convertTime<RatioOut, RatioIn>(t); }

}

#include "BasicTime.hpp"