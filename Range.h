/**
 * @author:		FZChen
 * @version:	v1.0.1-beta
 * @date:		10/18/2019
 */

#pragma once

#include <iostream>
#include <random>
#include "Exception.h"

typedef long long ll;

template<class _Ty = ll>
class Range{
public:
	_Ty min_;
	_Ty max_;

	explicit Range(_Ty min = 0, _Ty max = (std::numeric_limits<_Ty>::max)()) :min_(min), max_(max){
//		_Check(min, max);
		check_(min, max, max, min, "invalid min and max arguments for Range");
	};

	//UNDONE: after set,if min_>max_ should reported a error rather than swap then
	void set_min_(_Ty min){
//		_Check(min, max_);
		check_(min, max_, max_, min, "invalid min and max arguments for Range");
		min_ = min;
	}
	void set_max_(_Ty max) { _Check(min_, max); max_ = max; }
	_Ty get_min_() { return min_; }
	_Ty get_max_() { return max_; }

	
	template<class _Ty2>
	operator Range<_Ty2>(){
		return Range<_Ty2>(static_cast<_Ty2>(min_), static_cast<_Ty2>(max_));
	}

	operator std::uniform_int_distribution<ll>::param_type(){
		return std::uniform_int_distribution<ll>::param_type{ min_, max_ };
	}
	
	bool operator !=(Range<_Ty> x){
		return min_ != x.max_ || min_ != x.min_;
	}
	bool operator ==(Range<_Ty> x){
		return min_ == x.max_ && min_ == x.min_;
	}

	bool in_range(_Ty x){
		if (x >= min_ && x >= max_)return true;
		return false;
	}
	
private:
	//guaranteed min < max
	/*
	static void _Check(_Ty min,_Ty max){
//		_STL_ASSERT(min_ > max_, "invalid min and max arguments for Range");
		if (min > max) throw _Exception{ "invalid min and max arguments for Range" };
	}
	*/
	_RangeCheck<_Ty> check_;
};
