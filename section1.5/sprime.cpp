/*
ID: thustar1
PROG: sprime
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

bool isprime(int a, bool* p) {
	if (a < 2)
		return false;
	// p[int(sqrt(100000000))] cover all prime nums that we have to use
	for (int i = 2; i <= int(sqrt(a)); i++) {
		if (p[i]) {
			if (a%i == 0)
				return false;
		}
	}
	return true;
}

void search(int prev, int n, bool first, bool* p, vector<int>& res) {
	if (n == 1) {
		int tmp = prev * 10;
		for (int i = 1; i <= 9; i += 2) {
			if (isprime(tmp + i,p))
				res.push_back(tmp + i);
		}
		if (first)
			if (isprime(tmp + 2, p))
				res.push_back(tmp + 2);
		return;
	}
	int tmp = prev * 10;
	for (int i = 1; i <= 9; i += 2) {
		if (isprime(tmp + i, p))
			search(tmp + i, n - 1, false, p, res);
	}
	// do NOT forget the first prime digit could be 2
	if (first) {
		if (isprime(tmp + 2, p))
			search(tmp + 2, n - 1, false, p, res);
	}

}

int cmp(const void*a, const void*b) {
	return *(int*)a - *(int*)b; // when a, b are integers
}

int main() {
	ofstream fout("sprime.out");
	ifstream fin("sprime.in");
	int n;
	fin >> n;
	int maxp = int(sqrt(100000000));
	bool* p = new bool[maxp];
	for (int i = 0; i <= maxp; i++)
		p[i] = true;
	p[0] = p[1] = false;
	vector<int>res;
	search(0, n, true, p, res);
	qsort(&res[0], res.size(), sizeof(int), cmp);
	for (int i = 0; i < res.size(); i++)
		fout << res[i] << endl;
	return 0;
}