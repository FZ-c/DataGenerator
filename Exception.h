/**
 * @author:		FZChen
 * @version:	v1.1.0-beta
 * @date:		11/15/2019
 */
#pragma once

#include<string>

typedef long long ll;

class _Exception :std::exception {
public:
	_Exception(std::string &msg) :msg_(msg) {}

	void set_msg_(std::string& msg) { msg_ = msg; }
	
	const char * what()const noexcept override{
		return msg_.c_str();
	}
private:
	std::string msg_;
};

template <class _Ty = ll>
class  _RangeCheck{
public:
	bool operator()(_Ty checkmax,_Ty checkmin,_Ty max,_Ty min,std::string msg){
		if (checkmax > max || checkmin < min) {
			throw _Exception{ msg };
		}
		return true;
	}
};