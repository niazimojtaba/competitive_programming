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
template<typename T>
using tt = typename std::pair<T,T>;

struct Book {
	string name;
	string auther;
	bool exist = true;
	Book(string name, string auther) : name(name), auther(auther) {exist = true;}
	bool operator <( const Book& b) {
		if (auther == b.auther) return name < b.name;
		else return auther < b.auther;
	}
};

void print(vector<Book> library) {
	for (auto l : library) {
		cout << l.name << " " << l.auther << endl;
	}
}

void shelve(vector<Book>& library, vector<Book> returned) {
	//print(library);
	sort(returned.begin(), returned.end());
	for (auto re : returned) {
		auto it = lower_bound(library.begin(), library.end(), Book(re.name, re.auther));
		auto origin = it;
		if (it == library.begin() && !(*it).exist){
			cout << "Put" << re.name << " first" << endl;
			(*origin).exist = true;
			continue;
		}
		while (it > library.begin() && !(*it).exist) it--;
		if (!(*it).exist) {
			cout << "Put" << re.name << " first" << endl;
		}
		else {
			cout << "Put" << re.name << " after" << (*it).name << endl;
		}
		(*origin).exist = true;
	}
}

int main() {
    //freopen("in.txt", "r", stdin);
    vector<Book> library;
    vector<Book> returned;
    map<string, string> name_auther;
    string s;
    getline(cin, s);
    // getting library
    while (s != "END") {
        stringstream ss;
        ss << s;
        string c;
        string book_name;
        string auther;
        while (ss >> c) {
			if (c == "by")break;
			else book_name = book_name + " " + c;
        }
        getline(ss, auther);
        name_auther[book_name] = auther;
        library.push_back(Book(book_name, auther));
        getline(cin, s);
    }
	sort(library.begin(), library.end());
    // getting requests
    getline(cin, s);
    while (s != "END") {
        stringstream ss;
        ss << s;
        string command;
        string book_name;
        ss >> command;
        getline(ss, book_name);
        if (command == "SHELVE")
        {
			shelve(library, returned);
			returned.clear();
            cout << "END" << endl;
        }
        if (command == "BORROW") {
            auto it = lower_bound(library.begin(), library.end(), Book(book_name, name_auther[book_name]));
            (*it).exist = false;
        }
        if (command == "RETURN") {
			returned.push_back(Book(book_name, name_auther[book_name]));

        }
		getline(cin, s);
    }

    return 0;
}

