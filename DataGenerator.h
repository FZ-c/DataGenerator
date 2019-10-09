#pragma once

#include "Range.h"
#include <random>
#include <chrono>


template<class _Ty = ll>
class _Base{
public:
	_Base(Range<>data_range = Range<>())
		:data_range_(data_range),engine_((std::chrono::high_resolution_clock::now().time_since_epoch()).count()) {}
	
	Range<_Ty> get_data_range_() const { return data_range_; }
	std::default_random_engine get_engine_() const { return engine_; }
	
	void set_data_range_(const Range<_Ty>& data_range) { data_range_ = data_range; }
	void set_engine(const std::default_random_engine& engine) { engine_ = engine; }
	void set_engine(const std::default_random_engine::result_type& X) { engine_.seed(X); }

	
	auto get_data() { _get_random_data(); }
	//get a random data
	const _Ty _get_random_data(Range<>range) {
		u_.param(range);
		return u_(engine_);
	}
	const _Ty _get_random_data() {
		u_.param(data_range_);
		return u_(engine_);
	}
	
private:
	Range<_Ty> data_range_;
	std::default_random_engine engine_; 
	std::uniform_int_distribution<_Ty> u_;
};

//UNDONE: Ty!=char should hide data_length_range_ and other functions
//UNDONE: No error was reported in the illegal situation
template<class _Ty = ll>
class DataGenerator : public _Base<_Ty> {
	
public:
	
	
	DataGenerator(Range<> data_range = Range<>(), Range<> data_row_range = Range<>(1, 1), Range<> data_col_range = Range<>(1, 1)) :
		_Base(static_cast<Range<int> >(data_range)), data_row_range_(data_row_range), data_col_range_(data_col_range){}

	Range<> get_data_row_range_() const { return data_row_range_; }
	Range<> get_data_col_range_() const { return data_col_range_; }
	
	void set_data_row_range_(const Range<>& data_row_range) { data_row_range_ = data_row_range; }
	void set_data_col_range_(const Range<>& data_col_range) { data_col_range_ = data_col_range; }
	
	const auto get_data(){
		if (data_row_range_ != Range<>(1, 1)) return _get_two_dimension_data();
		if (data_col_range_ != Range<>(1, 1)) return _get_a_row_data();
		return _Base<>::_get_random_data();
	}
private:
	Range<> data_row_range_;
	Range<> data_col_range_;
	
	//UNDONE:when _Ty != char , use this function
	const std::vector<std::vector<_Ty> >_get_two_dimension_data(){
		std::vector<std::vector<_Ty> > ret;
		int row_number = _Base<>::_get_random_data(data_row_range_);
		while (row_number--)ret.push_back(_get_a_row_data());
		return ret;
	}
	
	//UNDONE:when _Ty != char , use this function
	const std::vector<_Ty>_get_a_row_data(){
		std::vector<_Ty> ret;
		int col_number = _Base<>::_get_random_data(data_col_range_);
		while (col_number--)ret.push_back(_Base<>::_get_random_data());
		return ret;
	}
};


template<>
class DataGenerator<char> :public _Base<int>
{
public:
	
	
	DataGenerator(Range<char> data_range, Range<> data_length_range = Range<>(1, 1), Range<> data_string_number_range = Range<>(1, 1)) :
		_Base(data_range), data_length_range_(data_length_range),data_string_number_range_(data_string_number_range){}

	Range<> get_data_length_range_() const { return data_length_range_; }
	
	void set_data_length_range_(const Range<>& data_length_range) { data_length_range_ = data_length_range; }

	//TODO:implement different types of returns
	const auto get_data(){
		if (data_string_number_range_ != Range<>(1, 1)) return _get_a_row_string();
		if (data_length_range_ != Range<>(1, 1)) return _get_string();
		return _Base<char>::_get_random_data();
	}
	//get a random vector about string(same as two-dimensional array)
	//UNDONE:Only Ty=char can use
	const std::vector<std::string>_get_a_row_string(){
		std::vector<std::string> ret;
		int string_number = _get_random_data(data_string_number_range_);
		while (string_number--)ret.push_back(_get_string());
		return ret;
	}
	
	//get a random string(same as one-dimensional array)
	//UNDONE:Only Ty=char can use
	const std::string _get_string(){
		std::string ret;
		int string_len = _get_random_data(data_length_range_);
		while (string_len--)ret.push_back(_get_random_data());
		return ret;
	}
	
private:
	
	//UNDONE:Only _Ty = char can use 
	Range<> data_length_range_;
	Range<> data_string_number_range_;
};