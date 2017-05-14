/*
ID: thustar1
PROG: fact4
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

#define DIGIT 1100

void multi(short* a, short end, short m, short* res, short pos) {
	// end == start position of multiplication
	// m == 0-9
	// pos == start position of result
	short carry = 0; // describe carry number
	for (short i = end; i < DIGIT-pos; i++) {
		res[i+pos] = a[i] * m + carry;
		carry = res[i + pos] / 10;
		res[i + pos] = res[i + pos] % 10;
	}
}

void add(short* a , short* b, short end, short* res) {
	short carry = 0;
	for (short i = end; i < DIGIT; i++) {
		res[i] = a[i] + b[i] + carry;
		carry = res[i] / 10;
		res[i] = res[i] % 10;
	}
}

void multiply(short* a, short end, short m, short* res) {
	// end == start position of multiplication
	// m == a number with arbitrary digit
	short mres[DIGIT] = { 0 };
	short i = 0;
	while (m > 0) {
		multi(a, end, m % 10, mres, i);
		add(res, mres, end, res);
		mres[end+i] = 0; // recover
		i++;
		m /= 10;
	}
}
int main() {
	ofstream fout("fact4.out");
	ifstream fin("fact4.in");
	short n;//n<=4220
	fin >> n;
	// 4220! has 4220/5+4220/25+4220/125+4220/625+4220/3125=1054 < 1100 zeros
	// It is why choose DIGIT as 1100
	short a[DIGIT] = { 0 };
	a[0] = 1;
	short end = 0;
	short tmp[DIGIT] = { 0 };
	for (short i = 2; i <= n; i++) {
		multiply(a, end, i, tmp);
		if (i % 5 == 0) {
			while (tmp[end] == 0)
				end++;
		}
		for (short j = 0; j < DIGIT; j++) {
			a[j] = tmp[j];
			tmp[j] = 0; // recover tmp
		}
		/*cout << "i=" << i << endl;
		for (short j = 0; j < 10; j++)
			cout << a[9 - j];
		cout << endl << endl;*/
	}
	fout << a[end] << endl;
	/*short a[DIGIT] = { 9,9,2,0,0 };
	short b[DIGIT];
	multi(a, 0, 7, b, 1);
	for (short i = 0; i < DIGIT; i++) {
		cout << b[DIGIT - 1 - i]<<" ";
	}
	cout << endl;
	multi(a, 0, 8, b, 0);
	for (short i = 0; i < DIGIT; i++) {
		cout << b[DIGIT - 1 - i] << " ";
	}
	cout << endl;
	short c[DIGIT] = { 9,8,7,6,0 };
	short d[DIGIT];
	add(a, c, 0, d);
	for (short i = 0; i < DIGIT; i++) {
		cout << d[DIGIT - 1 - i] << " ";
	}
	cout << endl;
	short e[DIGIT] = { 0 };
	multiply(a, 0, 678, e);
	for (short i = 0; i < DIGIT; i++) {
		cout << e[DIGIT - 1 - i] << " ";
	}
	cout << endl;*/
	return 0;
}