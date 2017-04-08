/*
ID: thustar1
PROG: subset
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	ofstream fout("subset.out");
	ifstream fin("subset.in");
	int n;
	fin >> n;
	// 1+2+...+n = n*(n+1)/2
	if (n*(n + 1) / 2 % 2 == 1) {// n*(n+1)/2 is odd, can not be divided
		fout << 0 << endl;
		return 0;
	}
	// otherwise n*(n+1)/2 is even
	int res[40][800];
	// res[i][j] == # of combinations whose sum == j
	// the maximum number must be i in the combinations;
	// maximum sum = 39*(39+1)/2=780, most memory require 40*800=32k, it is not very large
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 800; j++)
			res[i][j] = 0;
	for (int i = 1; i <= n; i++) {
		int upperBound = i*(i + 1) / 2;
		// only the sum j <= i*(i + 1) / 2 has non-empty set of combinations
		for (int j = i; j <= upperBound; j++) {
			if (i == j) {
				res[i][j] = 1;// The set == {i} i.e. {j} for summation j
			}
			if (i < j) {
				for (int k = 1; k < i; k++)// The set must contain i
					res[i][j] += res[k][j-i];
			}
			// if (i > j), there is no such set that contains i and summation equals j
			// just pass
		}
		//for (int ii = 1; ii <= n; ii++) {
		//	for (int jj = 1; jj <= (n + 1)*n / 2; jj++)
		//		cout << res[ii][jj] << " ";
		//	cout << endl;
		//}
		//cout << endl;
	}
	fout << res[n][n*(n + 1) / 4] << endl;
	return 0;
}