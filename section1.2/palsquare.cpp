/*
ID: thustar1
PROG: palsquare
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool palin(const string& s) {
	if (s.size() == 1)
		return true;
	else {
		bool result = true;
		int len = s.size();
		for (int i = 0; i < len / 2; i++) {
			if (s[i] != s[len - 1 - i]) {
				result = false;
				break;
			}
		}
		return result;
	}
}

string int2str(int num,const int& base) {
	string s = "";
	int tmp = 0;
	while (num>0) {
		tmp = num%base;
		if (tmp < 10) {
			s = to_string(tmp) + s;
		}
		else {
			char c = 'A' + tmp - 10;
			s = c + s;
		}
		num /= base;
	}
	return s;
}

int main() {
	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");
	int base;
	fin >> base;
	for (int num = 1; num <= 300; num++) {
		string s = int2str(num*num, base);
		if (palin(s)) {
			fout << int2str(num, base) << " " << s << endl;
		}
	}
	
	//fout<< endl;
	return 0;
}