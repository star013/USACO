/*
ID: thustar1
PROG: runround
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

bool isround(string s) {
	int pos = 0;
	bool* a = new bool[s.size()];
	for (int i = 0; i < s.size(); i++)
		a[i] = false;
	for (int i = 0; i < s.size(); i++) {
		pos = (pos + s[pos] - '0') % s.size();
		a[pos] = true;
	}
	for (int i = 0; i < s.size(); i++)
		if (a[i] == false)
			return false;
	return true;// should visit all digit
}

int s2i(string s) {
	if (s.size() == 0)
		return 0;
	int res = 0;
	for (int i = 0; i < s.size(); i++)
		res = res * 10 + s[i] - '0';
	return res;
}

void dfs(string s, string a, string& res, bool* state, bool prune) {
    // depth first search, generate a candidate one by one
	// state[i-1]==true, i have not been chosen yet
	if (a.size() == s.size()) {
		if (isround(a)&&a!=s)//Test 3, the first a==s
			res = a;
		return;
	}
	if (prune) {
		string tmp = "";// You can NOT initialize a string like
		// tmp=""+s[a.size()];
		tmp+=s[a.size()];
		int init = s2i(tmp);
		for (int i = init; i <= 9; i++) {
			if (state[i - 1]) {
				if (i == init) {
					state[i - 1] = false;
					dfs(s, a + to_string(i), res, state, true);
					if (res.size() == s.size())
						return;
					state[i - 1] = true;// recover state
				}
				else {
					state[i - 1] = false;
					dfs(s, a + to_string(i), res, state, false);
					if (res.size() == s.size())
						return;
					state[i - 1] = true;// recover state
				}
			}
		}
	}
	else {
		for (int i = 1; i <= 9; i++) {
			if (state[i - 1]) {
				state[i - 1] = false;
				dfs(s, a + to_string(i), res, state,false);
				if (res.size() == s.size())
					return;
				state[i - 1] = true;// recover state
			}
		}
	}
}
int main() {
	ofstream fout("runround.out");
	ifstream fin("runround.in");
	int m;
	fin >> m;
	//cout << isround("81362") << endl;
	string res = "";
	bool* state = new bool[9];
	for (int i = 0; i < 9; i++)
		state[i] = true;
	string tmp = to_string(m);
	dfs(to_string(m), "", res, state,true);
	// Test 1: input 99, need more digits to search
	while (res.size() == 0) {
		m = pow(10, to_string(m).size());
		dfs(to_string(m), "", res, state,false);
	}
	fout << stoi(res) << endl;
	//cout << isround("134259") << endl;
	return 0;
}