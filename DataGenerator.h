/**
 * @author:		FZChen
 * @version:	v1.0.1-beta
 * @date:		10/18/2019
 */

#pragma once

#include "Range.h"
#include "ReturnType.h"
#include <chrono>

//UNDONE: No error was reported in the illegal situation

template<class _Ty = ll>
class _Base{
public:
	_RangeCheck<ll> check_;
	_Base(Range<>data_range = Range<>())
		:data_range_(data_range),engine_((std::chrono::high_resolution_clock::now().time_since_epoch()).count()) {}
	Range<_Ty> get_data_range_() const { return data_range_; }
	std::default_random_engine get_engine_() const { return engine_; }
	
	void set_data_range_(const Range<_Ty>& data_range) { data_range_ = data_range; }
	void set_engine(const std::default_random_engine& engine) { engine_ = engine; }
	void set_engine(const std::default_random_engine::result_type& rt) { engine_.seed(rt); }

	
	_Ret<_Ty> get_data() { return _get_random_data(); }

	//get a random data
	_Ret<_Ty> _get_random_data(Range<>range) {
		u_.param(range);
		return static_cast<_Ret<_Ty>>(u_(engine_));
	}
	//if parameter is empty,use data_range_
	_Ret<_Ty> _get_random_data() {
		u_.param(data_range_);
		return static_cast<_Ret<_Ty>>(u_(engine_));
	}
	
private:
	Range<_Ty> data_range_;
	std::default_random_engine engine_; 
	std::uniform_int_distribution<_Ty> u_;

	static void _Check_nonnegative_range(Range<> r){
	if (r.get_min_() < 0)
		throw static_cast<_Exception>("this range can't include negative numbers");
	}
};

template<>
class _Base<char>{
public:
	_RangeCheck<ll> check_;
	_Base(Range<>data_range = Range<>())
		:data_range_(data_range),engine_((std::chrono::high_resolution_clock::now().time_since_epoch()).count()) {}
	
	Range<char> get_data_range_() const { return data_range_; }
	std::default_random_engine get_engine_() const { return engine_; }
	
	void set_data_range_(const Range<char>& data_range){
//		_Check_data_range_(data_range);
		check_(data_range.max_, data_range.min_, CHAR_MAX, CHAR_MIN, "The data_range is in an invalid range");
		data_range_ = data_range;
	}
	void set_engine(const std::default_random_engine& engine) { engine_ = engine; }
	void set_engine(const std::default_random_engine::result_type& rt) { engine_.seed(rt); }

	
	_Ret<char> get_data() { return _get_random_data(); }

	//get a random data
	_Ret<char> _get_random_data(Range<>range) {
		u_.param(range);
		return static_cast<_Ret<char>>(u_(engine_));
	}
	//if parameter is empty,use data_range_
	_Ret<char> _get_random_data() {
		u_.param(data_range_);
		return static_cast<_Ret<char>>(u_(engine_));
	}
	/*
	static void _Check_data_range_(Range<char> data_range){
		if (data_range.get_min_() < CHAR_MIN || data_range.get_max_() > CHAR_MAX)
			throw std::out_of_range{ "The data_range is in an invalid range" };
	}
	static void _Check_nonnegative_range(Range<> r){
	if (r.get_min_() < 0)
		throw static_cast<_Exception>("this range can't include negative numbers");
	}
	*/
	
private:
	Range<char> data_range_;
	std::default_random_engine engine_; 
	std::uniform_int_distribution<ll> u_;
	
};

template<class _Ty = ll>
class DataGenerator : public _Base<_Ty> {
	
public:
	
	DataGenerator(Range<> data_range = Range<>(), Range<> data_row_range = Range<>(1, 1), Range<> data_col_range = Range<>(1, 1)) :
		data_row_range_(data_row_range), data_col_range_(data_col_range){
		this->set_data_range_(data_range);
	}

	Range<> get_data_row_range_() const { return data_row_range_; }
	Range<> get_data_col_range_() const { return data_col_range_; }
	
	void set_data_row_range_(const Range<>& data_row_range)
	{
		this->check_(data_row_range.max_, data_row_range.min_, data_row_range.max_, 0, "this range can't include negative numbers");
		data_row_range_ = data_row_range;
	}
	void set_data_col_range_(const Range<>& data_col_range)
	{
		this->check_(data_col_range.max_, data_col_range.min_, data_col_range.max_, 0, "this range can't include negative numbers");
		data_col_range_ = data_col_range;
	}

	_Ret<_Ty> get_data(){
		if (data_row_range_ != Range<>(1, 1)) return _get_two_dimension_data();
		if (data_col_range_ != Range<>(1, 1)) return _get_a_row_data();
		return _Base<>::_get_random_data();
	}
private:
	Range<> data_row_range_;
	Range<> data_col_range_;
	
	_Ret<_Ty> _get_two_dimension_data(){
		std::vector<std::vector<_Ty> > ret;
		int row_number = _Base<>::_get_random_data(data_row_range_);
		while (row_number--)ret.push_back(_get_a_row_data());
		return static_cast<_Ret<_Ty>>(ret);
	}
	
	_Ret<_Ty> _get_a_row_data(){
		std::vector<_Ty> ret;
		int col_number = _Base<>::_get_random_data(data_col_range_);
		while (col_number--)ret.push_back(_Base<>::_get_random_data());
		return static_cast<_Ret<_Ty>>(ret);
	}
};


template<>
class DataGenerator<char> :public _Base<char>
{
public:
	
	DataGenerator(
		Range<char> data_range=Range<char>('a','z'), 
		Range<> data_length_range = Range<>(1, 1), 
		Range<> data_string_number_range = Range<>(1, 1)
	)
	:_Base(data_range), data_length_range_(data_length_range),data_string_number_range_(data_string_number_range){}

	Range<> get_data_length_range_() const { return data_length_range_; }
	
	void set_data_length_range_(const Range<>& data_length_range){
//		_Check_nonnegative_range(data_length_range);
		this->check_(data_length_range.max_, data_length_range.min_, data_length_range.max_, 0, "this range can't include negative numbers");
		data_length_range_ = data_length_range;
	}
	void set_string_number_range_(const Range<>& data_string_number_range){
//		_Check_nonnegative_range(data_string_number_range);
		this->check_(data_string_number_range.max_, data_string_number_range.min_, data_string_number_range.max_, 0, "this range can't include negative numbers");
		data_string_number_range_ = data_string_number_range;
	}

	_Ret<char> get_data(bool add_space = false) {
		if (data_string_number_range_ != Range<>(1, 1)) return _get_a_row_string(add_space);
		if (data_length_range_ != Range<>(1, 1)) return _get_string(add_space);
		return _get_random_data();
	}
	
private:
	Range<> data_length_range_;
	Range<> data_string_number_range_;
	
	//get a random vector about string(same as two-dimensional array)
	_Ret<char> _get_a_row_string(bool add_space = false) {
		std::vector<std::string> ret;
		int string_number = _get_random_data(data_string_number_range_);
		while (string_number--)ret.push_back(_get_string(add_space));
		return static_cast<_Ret<char>>(ret);
	}
	
	//get a random string(same as one-dimensional array)
	_Ret<char> _get_string(bool add_space = false) {
		std::string ret;
		int string_len = _get_random_data(data_length_range_);
		//UNDONE:try to optimize
		if (add_space)
			set_data_range_(Range<>(get_data_range_().get_min_() - 1, get_data_range_().get_max_()));
		for (int i = 0; i < string_len; i++)
			ret.push_back(_get_random_data());
		if(add_space){
			for (int i = 0; i < string_len; i++) {
				if (ret[i] == get_data_range_().get_max_())
					ret[i] = ' ';
			}
			set_data_range_(Range<>(get_data_range_().get_min_() + 1, get_data_range_().get_max_()));
		}
		return static_cast<_Ret<char>>(ret);
	}
};