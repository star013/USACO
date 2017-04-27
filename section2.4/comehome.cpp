/*
ID: thustar1
PROG: comehome
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int c2i(char c) {
	int i = c - 'A';
	if (i < 26)
		return i;
	else
		return 26 + c - 'a';
}
int main() {
	ofstream fout("comehome.out");
	ifstream fin("comehome.in");
	// (int)'A' == 65, (int)'a' == 97
	//cout << c2i('A') << " " << c2i('Z') << " " << c2i('a') << " " << c2i('z') << endl;
	int p;
	fin >> p;
	char a, b;
	int d[26 + 26][26 + 26];// d[i][j]<=1000
	int MAX_VALUE = 10000000;
	// Note: MAX_VALUE should be large enough!
	int w;
	// initialize d
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 52; j++) {
			if (i == j)
				d[i][j] = 0;
			else
				d[i][j] = MAX_VALUE;
		}
	}
	for (int i = 0; i < p; i++) {
		fin >> a >> b;
		int ia = c2i(a), ib = c2i(b);
		fin >> w;
		if (w < d[ia][ib]) {
			// update undirected graph, choose smallest weight from input
			d[ia][ib] = w;
			d[ib][ia] = w;
		}
	}

	// Floyd algorithm
	for (int k = 0; k < 52; k++) {
		for (int i = 0; i < 52; i++) {
			for (int j = 0; j < 52; j++) {
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
	}

	/*cout << "result=" << endl;
	for (int i = 0; i < 25; i++)
		cout << d[25][i] << " ";*/
	int res = MAX_VALUE, idx = 0;
	for (int i = 0; i < 25; i++) {
		if (res > d[25][i]) {
			res = d[25][i];
			idx = i;
		}
	}
	fout << (char)('A' + idx) << " " << res << endl;
	return 0;
}