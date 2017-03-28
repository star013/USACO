/*
ID: thustar1
PROG: dualpal
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
	while (num>0) {
		s = to_string(num%base) + s;
		num /= base;
	}
	return s;
}

bool multipalin(const int& num) {
	bool result = false, first = false;
	string tmp;
	for (int b = 2; b <= 10; b++) {
		tmp = int2str(num, b);
		if (palin(tmp)) {
			if (!first)
				first = true;
			else {
				result = true;
				break;
			}
		}
	}
	return result;
}
int main() {
	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");
	int n, bound;
	fin >> n >> bound;
	for(int i=0;i<n;i++) {
		bound++;
		while (!multipalin(bound))
			bound++;
		fout << bound << endl;
	}
	
	//fout<< endl;
	return 0;
}