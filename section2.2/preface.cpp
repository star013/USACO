/*
ID: thustar1
PROG: preface
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int* rome(int n) {
	// M
	int* res = new int[7]();
	res[6] = n / 1000;
	n -= res[6] * 1000;
	int tmp = n / 100;
	if (tmp == 4) {
		// 400=CD
		res[5] += 1;//D
		res[4] += 1;//C
	}
	if (tmp > 4 && tmp < 9) {
		res[5] += 1;//D
		res[4] += tmp - 5;//C
	}
	if (tmp == 9) {
		// 900=CM
		res[6] += 1;//M
		res[4] += 1;//C
	}
	if (tmp <= 3)
		res[4] += tmp;//C
	n -= tmp * 100;

	tmp = n / 10;
	if (tmp == 4) {
		// 40=XL
		res[3] += 1;//L
		res[2] += 1;//X
	}
	if (tmp > 4 && tmp < 9) {
		res[3] += 1;//L
		res[2] += tmp - 5;//X
	}
	if (tmp == 9) {
		// 90=XC
		res[4] += 1;//C
		res[2] += 1;//X
	}
	if (tmp <= 3)
		res[2] += tmp;//X
	n -= tmp * 10;

	tmp = n;
	if (tmp == 4) {
		// 4=IV
		res[1] += 1;//V
		res[0] += 1;//I
	}
	if (tmp > 4 && tmp < 9) {
		res[1] += 1;//V
		res[0] += tmp - 5;//I
	}
	if (tmp == 9) {
		// 9=IX
		res[2] += 1;//X
		res[0] += 1;//I
	}
	if (tmp <= 3)
		res[0] += tmp;//I
	return res;
}
int main() {
	ofstream fout("preface.out");
	ifstream fin("preface.in");
	int n;
	fin >> n;//1<=N<3500
	int* res = new int[7]();
	for (int i = 1; i <= n; i++) {
		int* tmp = rome(i);
		for (int j = 0; j < 7; j++)
			res[j] += tmp[j];
	}

	char c[7] = { 'I','V','X','L','C','D','M' };
	for (int i = 0; i < 7; i++)
		if (res[i] > 0)
			fout << c[i] << " " << res[i] << endl;
	return 0;
}