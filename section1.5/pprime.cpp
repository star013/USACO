/*
ID: thustar1
PROG: pprime
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void numberSieve(bool* p, int b) {
	// p is bool array, p[prime]=true, p[not prime]=false
	// b is the maximum boundary for problem, p[b]
	int beg = 2;
	while (beg <= b) {
		if (p[beg]) {
			// beg is prime, cancel out all its multiples
			for (int j = 1; j <= b / beg - 1; j++)
				p[beg + j*beg] = false;
		}
		beg++;
	}
}

bool palindrome(int num) {
	string tmp = to_string(num);
	for (int i = 0; i<tmp.size() / 2; i++)
		if (tmp[i] != tmp[tmp.size() - 1 - i])
			return false;
	return true;
}

void solve_v1(bool* p, int a, int b, vector<int>& res) {
	// just use number sieve method fails in Test 9: input 5 100,000,000
	// because it require too much memory
	numberSieve(p, b);
	for (int i = a; i <= b; i++) {
		if (p[i]) {
			if (palindrome(i)) {
				res.push_back(i);
			}
		}
	}
}

bool isprime(int a, bool* p) {
	// p[int(sqrt(100000000))] cover all prime nums that we have to use
	for (int i = 2; i <= int(sqrt(a)); i++) {
		if (p[i]) {
			if (a%i == 0)
				return false;
		}
	}
	return true;
}

void genPalin(vector<int> digits, int cur, const int& len, int num, const int& a, const int& b, bool* p, vector<int>& res) {
	// len is length of number
	if (len % 2 == 0 && cur == len / 2 - 1) {
		for (int i = 0; i < digits.size(); i++) {
			int tmp = digits[i];
			tmp = num + tmp*int(pow(10, cur)) + tmp*int(pow(10, cur + 1));
			//cout << tmp << endl;
			if (tmp>=a && tmp <= b&&isprime(tmp, p))// do not forget upper and lower bound
				res.push_back(tmp);
		}
		return;
	}
	if (len % 2 == 1 && cur == len / 2) {
		for (int i = 0; i < digits.size(); i++) {
			int tmp = digits[i];
			tmp = num + tmp*int(pow(10, cur));
			//cout << tmp << endl;
			if (tmp>=a&&tmp <= b&&isprime(tmp, p))
				res.push_back(tmp);
		}
		return;
	}
	vector<int> nextdigits;
	for (int i = 0; i <= 9; i++)
		nextdigits.push_back(i);
	for (int i = 0; i < digits.size(); i++) {
		int tmp = digits[i];
		tmp = num + tmp*int(pow(10, cur)) + tmp*int(pow(10, len - 1 - cur));
		genPalin(nextdigits, cur + 1, len, tmp, a, b, p, res);
	}
}

void solve_v2(bool*p, int a, int b, vector<int>& res) {
	// first generate palindrome then judge whether it is a prime num
	/**
	* when you meet equal matching problem, first consider the smallest set of one attribution
	* in this problem, the set of palindrome number is much smaller than the whole set to search a prime num
	* always first consider the smallest set to search first!
	*/
	int na = to_string(a).size();
	int nb = to_string(b).size();
	int bega = a/int(pow(10, na - 1));
	int begb = b/int(pow(10, nb - 1));
	for (int len = na; len <= nb; len++) {
		vector<int> digits;
		// you'd better use if {} else if {} else{} structure to prevent the situation
		// in which na==nb, and re-compuation occurs
		if (len == na) {
			for (int i = bega; i <= 9; i++) {
				if (i % 2 == 1) {
					digits.push_back(i);
				}
			}
			genPalin(digits, 0, len, 0, a, b, p, res);
		}else if (len == nb) {
			for (int i = 1; i <= begb; i+=2) {
				digits.push_back(i);
			}
			genPalin(digits, 0, len, 0, a, b, p, res);
		} else {
			for (int i = 1; i <= 9; i += 2) {
				digits.push_back(i);
			}
			genPalin(digits, 0, len, 0, a, b, p, res);
		}
	}
}


int main() {
	ofstream fout("pprime.out");
	ifstream fin("pprime.in");
	int a, b;
	fin >> a >> b;
	//bool* p = new bool[b + 2];
	//for (int i = 0; i <= b; i++)
	//	p[i] = true;
	//p[0] = p[1] = false;
	//cout << palindrome(a) << " " << palindrome(b) << endl;
	//vector<int>res;
	//solve_v1(p, a, b, res);
	//for (int i = 0; i < res.size(); i++)
	//	fout << res[i] << endl;
	int maxp = int(sqrt(100000000));
	bool* p = new bool[maxp];
	for (int i = 0; i <= maxp; i++)
		p[i] = true;
	p[0] = p[1] = false;
	//cout << int(sqrt(b)) << endl;
	//cout << isprime(23, p) << isprime(24, p) << endl;
	// test getPalin
	//vector<int> nextdigits;
	//for (int i = 0; i <= 9; i++)
	//	nextdigits.push_back(i);
	//int len;
	//cin >> len;
	//vector<int>res;
	//cout << "test getPalin" << endl;
	//genPalin(nextdigits, 0, len, 0, res);


	vector<int>res;
	solve_v2(p, a, b, res);
	for (int i = 0; i < res.size(); i++)
		fout << res[i] << endl;
	return 0;
}