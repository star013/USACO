/*
ID: thustar1
PROG: frac1
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void printMat(short* mat, short M, short N) {
	// M col, N row
	for (short i = 0; i < N; i++) {
		for (short j = 0; j < M; j++)
			cout << mat[i*M + j] << " ";
		cout << endl;
	}
}

void printInts(short* a, short n) {
	for (short i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

bool* numSieve(int n) {
	// number sieve to get prime number
	bool* p = new bool[n + 1];
	for (int i = 0; i <= n; i++)
		p[i] = true;
	p[0] = p[1] = false;
	for (int i = 2; i <= n; i++) {
		if (p[i]) {
			for (int j = 1; j <= n / i - 1; j++)
				p[i + i*j] = false;
		}
	}
	return p;
}

bool coprime(int a, int b, bool* p) {
	// assume a<b
	if (a == 1)
		return true;
	for (int i = 2; i <= a; i++) {
		if (p[i]) {
			if (a%i == 0 && b%i == 0)
				return false;
		}
	}
	return true;
}

struct frac
{
	int a;
	int b;
};

int cmp(const void*a, const void*b) {
	frac* t1 = (frac*)a;
	frac* t2 = (frac*)b;
	if ((double)t1->a / t1->b < (double)t2->a / t2->b) return -1;
	if ((double)t1->a / t1->b == (double)t2->a / t2->b) return 0;
	if ((double)t1->a / t1->b > (double)t2->a / t2->b) return 1;
}

void solve(int n, vector<frac>& res) {
	frac* f = new frac;
	f->a = 0; f->b = 1;
	res.push_back(*f);
	f = new frac;
	f->a = 1; f->b = 1;
	res.push_back(*f);
	if (n == 1)
		return;
	bool* p = numSieve(160);
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i - 1; j++) {
			if (coprime(j, i, p)) {
				f = new frac;
				f->a = j; f->b = i;
				res.push_back(*f);
			}
		}
	}
}
int main() {
	ofstream fout("frac1.out");
	ifstream fin("frac1.in");
	int n;
	fin >> n;
	vector<frac> res;
	solve(n, res);

	qsort(&res[0], res.size(), sizeof(frac), cmp);
	for (int i = 0; i < res.size(); i++)
		fout << res[i].a << "/" << res[i].b << endl;
	return 0;
}