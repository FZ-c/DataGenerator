#include <iostream>
#include "DataGenerator.h"

using namespace std;

typedef long long ll;


template<class _Ty = ll>
class JiLei
{
public:
	Range<>p1, p2;
	JiLei(Range<>p1 = Range<>(), Range<>p2 = Range<>()) :p1(p1), p2(p2) {}
};

template<class _Ty = ll>
class C:public JiLei<>
{
public:
	Range<>p3;
	explicit C(Range<> p1 = Range<>(), Range<> p2 = Range<>(), Range<> p3 = Range<>()) :JiLei<>(p1, p2) , p3(p3) {}
};


template<>
class C<char>
{
public:
	Range<>p3;
	C(Range<>p1 = Range<>(), Range<>p2 = Range<>(), Range<>p3 = Range<>())
		:p3(p3){}
};

int x(int a =2)
{
	return a;
}

int main() {
	//output:2
	cout << x();
	//output:5
	cout << x(5);
	return 0;
}