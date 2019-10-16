#pragma once

#include "Range.h"

template <class _Ty = ll>
class _Ret{
public:
	explicit _Ret(_Ty v = _Ty()) :value_(v) {}
	explicit _Ret(std::vector<_Ty> v) :array_value_(v) {}
	explicit _Ret(std::vector<std::vector<_Ty>>v) :two_dimension_value_(v) {}

	operator _Ty () { return value_; }
	operator std::vector<_Ty> () { return array_value_; }
	operator std::vector<std::vector<_Ty>>() { return two_dimension_value_; }

	friend std::ostream& operator<<(std::ostream& os,const _Ret& r){
		os << r.value_;
		return os;
	}
	
private:
	_Ty value_ = _Ty();
	std::vector<_Ty> array_value_;
	std::vector < std::vector<_Ty> >two_dimension_value_;
};

template <>
class _Ret<char>{
public:
	explicit _Ret(char v = char()) :value_(v) {}
	explicit _Ret(std::string v) :string_value_(v) {}
	explicit _Ret(std::vector<std::string> v) :string_array_value_(v) {}
	explicit _Ret(std::uniform_int_distribution<ll>::result_type r) :value_(static_cast<char>(r)) {}

	operator char () const { return value_; }
	operator std::string () const { return string_value_; }
	operator std::vector<std::string>() const { return string_array_value_; }

	friend std::ostream& operator<<(std::ostream& os,const _Ret& r){
		if (!r.string_value_.empty()) os << r.string_value_;
		else os << r.value_;
		return os;
	}
	
private:
	char value_{};
	std::string string_value_;
	std::vector <std::string>string_array_value_;
};