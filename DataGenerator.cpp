/**
 * @author:		FZChen
 * @version:	v1.1.0-beta
 * @date:		11/15/2019
 */

#include <iostream>
#include "DataGenerator.h"

using namespace std;

typedef long long ll;

#define DO_NOT_TEST false
#define DO_TEST true

int main() {
	DataGenerator<ll> random_number(Range<>(0, 100));
	DataGenerator<char>random_string;

	if(DO_NOT_TEST){
		cout << "Number Test" << endl;
		cout << "=================================================" << endl;
		
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
		random_number.set_data_row_range_(
			Range<>(random_number.get_data_col_range_().get_max_(), random_number.get_data_col_range_().get_max_())
		);
		random_number.set_data_col_range_(
			Range<>(random_number.get_data_row_range_().get_max_(), random_number.get_data_row_range_().get_max_())
		);
		vector <vector<ll>>arr2 = random_number.get_data();
		for(vector<vector<ll>>::iterator vit=arr2.begin();vit!=arr2.end();++vit){
			for(vector<ll>::iterator vit2=vit->begin();vit2!=vit->end();++vit2){
				cout << *vit2 << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}

	if(DO_NOT_TEST){
		cout << "String Test" << endl;
		cout << "=================================================" << endl;

		cout << "A random char(lowercase): " << random_string.get_data() << endl;

		random_string.set_data_length_range_(Range<>(10, 30));
		cout << "A random string(lowercase): " << random_string.get_data() << endl;
		
		cout << "An random string array:" << endl;
		random_string.set_string_number_range_(random_string.get_data_length_range_());
		vector<string> arr3 = random_string.get_data();
		for(vector<string>::iterator vit=arr3.begin();vit!=arr3.end();vit++){
			cout << *vit << endl;
		}
		cout << endl;
	}

	if(DO_NOT_TEST){
		cout << "String with space Test" << endl;
		cout << "=================================================" << endl;
		
		random_string.set_data_length_range_(Range<>(10, 30));
		cout << "A random string(lowercase add space): " << random_string.get_data(true) << endl;
		
		cout << "An random string array:(add space)" << endl;
		random_string.set_string_number_range_(random_string.get_data_length_range_());
		vector<string> arr4 = random_string.get_data(true);
		for(vector<string>::iterator vit=arr4.begin();vit!=arr4.end();vit++){
			cout << *vit << endl;
		}
	}

	if(DO_TEST){
		cout << "Illegal Situation Test" << endl;
		cout << "=================================================" << endl;
		try{
			random_number.set_data_range_(Range<>(100, 0));
		}catch (_Exception e){
			cerr << e.what();
		}
	}
	return 0;
}