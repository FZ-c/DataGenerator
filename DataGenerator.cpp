#include <iostream>
#include "DataGenerator.h"

using namespace std;

typedef long long ll;


int main() {

	cout << "Number Test" << endl;
	cout << "=================================================" << endl;
	
	DataGenerator<ll> random_number;
	random_number.set_data_range_(Range<>(0, 100));
	
	cout << "A random number: " << random_number.get_data() << endl;
	
	cout << "An array random number:" << endl;
	random_number.set_data_col_range_(Range<>(20, 50));
	vector <ll> arr1 = random_number.get_data();
	for(vector<ll>::iterator vit=arr1.begin();vit!=arr1.end();++vit){
		cout << *vit << ' ';
	}
	cout << endl;

	cout << "A two-dimension random number:" << endl;
	random_number.set_data_row_range_(random_number.get_data_col_range_());
	vector <vector<ll>>arr2 = random_number.get_data();
	for(vector<vector<ll>>::iterator vit=arr2.begin();vit!=arr2.end();++vit){
		for(vector<ll>::iterator vit2=vit->begin();vit2!=vit->end();++vit){
			cout << *vit2 << ' ';
		}
		cout << endl;
	}
	cout << endl;

	
	cout << "String Test" << endl;
	cout << "=================================================" << endl;

	DataGenerator<char>random_string;

	cout << "A random char(lowercase): " << random_string.get_data() << endl;

	random_string.set_data_length_range_(Range<>(10, 30));
	cout << "A random string(lowercase): " << random_string.get_data() << endl;

	random_string.set_string_number_range_(random_string.get_data_length_range_());
	vector<string> arr3 = random_string.get_data();
	for(vector<string>::iterator vit=arr3.begin();vit!=arr3.end();vit++){
		cout << *vit << endl;
	}

	return 0;
}