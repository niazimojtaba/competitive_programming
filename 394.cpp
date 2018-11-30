#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <map>
#include <set>

using namespace std;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
template<typename T>
using tt = typename std::pair<T,T>;
struct My_array {
	int d;
	int base_address;
	int s_byte;
	vector<ii>lower_upper_bound;
	My_array(){}
	My_array(int d, int base_address, int s_byte): d(d), base_address(base_address), s_byte(s_byte){
		lower_upper_bound.resize(d);
	}
	void fill_upper_lower() {
		for (int i = 0 ; i < d ; i++) {
			int l , u;
			cin >> l >> u;
			lower_upper_bound[i] = make_pair<int&, int&>(l, u);
		}	
	}
	int calc(vi index){
		int add = 0;
		for (int i = 0 ; i < d ; i++) {
			int local_add = (index[i] - lower_upper_bound[i].first);
			for (int j = i + 1; j < d ; j++) {
				local_add *= (lower_upper_bound[j].second - lower_upper_bound[j].first + 1);
			}
			add += local_add;
		}
		return add * s_byte;
	}
};

int main() {
	
    //freopen("in.txt", "r", stdin);
    int base_address; // base
    int size_of_each_element_in_byte; // dimension
    int d; // dimension
    int n, r;
    cin >> n >> r;
    map<string, My_array> array_mp;
    for (int i =0 ; i < n ; i++)
    {
		string name; 
		cin >> name;
		cin >> base_address >> size_of_each_element_in_byte >> d;
		array_mp[name] = My_array(d, base_address, size_of_each_element_in_byte);
		array_mp[name].fill_upper_lower();
	}
	
	for (int i = 0; i < r; i++) {
		string name;
		cin >> name;
		int d = array_mp[name].d;
		vi index(d);
		cout << name << "[";
		bool first_time = true;
		for (int j = 0 ; j < d; j++) {
			cin >> index[j];
			if (!first_time) cout << ", ";
			cout << index[j];
			first_time = false;
		}
		cout << "] = " << array_mp[name].base_address + array_mp[name].calc(index) << endl;
	}
    return 0;
}

