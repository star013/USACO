/*
ID: thustar1
PROG: zerosum
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int parse(string s) {
	int res = 0;
	int tmp = s[0]-'0';
	char op = s[1];
	bool first = true;
	for (int i = 2; i < s.size(); i+=2) {
		if (i<s.size()-1){
			//i>0
			if (s[i - 1] == ' ') {
				tmp = tmp * 10 + s[i] - '0';
			}
			else {
				if (first) {
					// it is the first operator
					res = tmp;
					first = false;
				}
				else {
					if (op == '+')
						res += tmp;
					if (op == '-')
						res -= tmp;
				}
				op = s[i - 1];
				tmp = s[i] - '0';
			}
		}
		else {
			//i==s.size()-1
			if (s[i - 1] == ' ') {
				tmp = tmp * 10 + s[i] - '0';
			}
			else {
				if (first) {
					res = tmp;
					first = false;
				}
				else {
					if (op == '+')
						res += tmp;
					if (op == '-')
						res -= tmp;
				}
				op = s[i - 1];
				tmp = s[i] - '0';
			}
			if (op == '+')
				res += tmp;
			if (op == '-')
				res -= tmp;
			if (op == ' ')
				res = tmp;
		}
		
	}
	return res;
}

void solve(int n,int i, string cur, vector<string>& res) {
	if (i == n) {
		if(parse(cur)==0)
			res.push_back(cur);
		return;
	}
	//i<n
	if (i % 2 == 0)
		solve(n, i + 1, cur + to_string(i/2+1), res);
	else {
		solve(n, i + 1, cur + " ", res);
		solve(n, i + 1, cur + "+", res);
		solve(n, i + 1, cur + "-", res);
	}
}

int main() {
	ofstream fout("zerosum.out");
	ifstream fin("zerosum.in");
	int n;
	fin >> n;
	// n<=9, there are at most pow(3,8)=6,561 situations
	// brute force can work, just enumerate each string
	vector<string>res;
	solve(2*n-1, 1, "1", res);
	for (int i = 0; i < res.size(); i++)
		fout << res[i] << endl;
	//string test = "1 2+3 4-5 6";
	//cout << parse(test) << endl;
	return 0;
}