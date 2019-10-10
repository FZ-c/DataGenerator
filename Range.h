#pragma once

#include <iostream>
#include <random>

typedef long long ll;

template<class _Ty = ll>
class Range{
public:
	_Ty min_;
	_Ty max_;

	explicit Range(_Ty min = 0, _Ty max = (std::numeric_limits<_Ty>::max)()) :min_(min), max_(max){
		_Check();
	};

	//UNDONE: after set,if min_>max_ should reported a error rather than swap then
	void set_min_(_Ty min) { min_ = min; _Check(); }
	void set_max_(_Ty max) { max_ = max; _Check(); }
	_Ty get_min_() { return min_; }
	_Ty get_max_() { return max_; }

	
	template<class _Ty2>
	operator Range<_Ty2>(){
		return Range<_Ty2>(static_cast<_Ty2>(min_), static_cast<_Ty2>(max_));
	}

	operator std::uniform_int_distribution<ll>::param_type(){
		return static_cast<std::uniform_int_distribution<ll>::param_type>(min_, max_);
	}
	
	bool operator !=(Range<_Ty> x){
		return min_ != x.max_ || min_ != x.min_;
	}
	bool operator ==(Range<_Ty> x){
		return min_ == x.max_ && min_ == x.min_;
	}

	
private:
	//guaranteed min<max
	void _Check(){
		if (min_ > max_) std::swap(min_, max_);
	}
};
