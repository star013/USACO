/*
ID: thustar1
PROG: prefix
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void printStr(vector<string> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << endl;
}

bool match(string primitive, string& s, int beg) {
	if (primitive.size() > s.size() - beg)
		return false;
	for (int i = 0; i < primitive.size(); i++)
		if (primitive[i] != s[beg + i])
			return false;
	return true;
}

int solve(vector<string>& p, string &s) {
	int res = 0;
	bool traveled[200001],start[200001];//start[i]==true the next step can begin at index i
	// traveled[i]==true index i has already been start point
	for (int i = 0; i < 200001; i++) {
		traveled[i] = false; start[i] = false;
	}
	start[0] = true;
	int snum = 1;//snum == # of start[i]==true
	// dynamic programming
	while (snum>0) {
		for(int i=res;i<=s.size();i++)
			if (start[i]) {
				res = i;
				snum--;
				start[i] = false;
				break;
			}
		for (int i = 0; i < p.size(); i++) {
			if (!traveled[res + p[i].size()]&&match(p[i], s, res)) {
				traveled[res + p[i].size()] = true;
				start[res + p[i].size()] = true;
				snum++;
			}
		}
		if (res == s.size())
			break;
	}
	return res;
}
int main() {
	ofstream fout("prefix.out");
	ifstream fin("prefix.in");
	string tmp,s="";
	vector<string> p;
	fin >> tmp;
	p.push_back(tmp);// when read in string, it delimite at ' ' automatically
	while (tmp[0] != '.') {
		fin >> tmp;
		if (tmp[0] != '.')
			p.push_back(tmp);
	}
	while(fin >> tmp)
		s += tmp;
	//cin >> tmp;
	//s += tmp;
	//printStr(p);
	//cout << s << endl;

	// V1, just use inputs as primitives, input set may contain useless information
	// Test 4 TLE
	// p.size()=26+100, too many, and there are 26 basic char, additional 100 primitives of length 10 is useless
	// It is because i forgot to test the condition primitives just match the whole thing, it has a dead loop
	// So you should always test some marginal cases, special cases yourself
	int res = solve(p, s);
	fout << res << endl;
	return 0;
}