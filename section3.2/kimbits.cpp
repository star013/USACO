/*
ID: thustar1
PROG: kimbits
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int combine(int n, int k) {
	// C(n,k) = n!/k!/(n-k)!
	if (k > n / 2)
		k = n - k;
	double tn = (double)n;
	double tk = (double)k;
	double res = 1;
	for (int i = 0; i < k; i++)
		res = res*(tn - i) / (i + 1);
	/*for (int i = k; i > 1; i--)
		res = res / i;*/
	return (int)res;
}

int total(int n, int k) {
	// return C(n,0)+C(n,1)+...+C(n,k-1)+C(n,k)
	if (n <= k)
		return (int)pow(2, n);
	// n>k
	int res = 0;
	for (int i = 0; i <= k; i++) {
		res += combine(n, i);
	}
	return res;
}

int main() {
	ofstream fout("kimbits.out");
	ifstream fin("kimbits.in");
	unsigned int n, L, p;//l<=n<=31
	// Test 10:31 31 2147483648 
	// TLE
	// because int maximum is 2147483647, it can not read 2147483648
	// it will be an error!
	fin >> n >> L >> p;
	//cout << n << " " << L << " " << p << endl;
	//cout << combine(20, 4) << endl;
	//cout << combine(20, 0) << endl;
	//cout << total(0, 3) << endl;
	//cout << total(1, 3) << endl;
	//cout << total(2, 3) << endl;

	bool one[32];
	for (int i = 0; i < 32; i++) {
		one[i] = false;
	}
	int pos = n;//tl=l
	while (pos >= 0) {
		int right = 1;// if no "1", all bits are "0", it is one combination
		if (right == p) {
			pos = -1;
			p -= right; 
			break;
		}
		// right<p
		for (int i = 0; i < pos; i++) {
			int tmp = total(i, L - 1);
			if (right+tmp > p) {
				// total(i,L-1)==total combination when the first "1" is at the position i
				// if there are L "1"s, then there are at most L-1 "1"s at the right side of position i
				pos = i;
				break;
			}
			else if (right + tmp == p) {
				// select maximum possible value
				for (int j = 0; j < L; j++) {
					if (i - j >= 0)
						one[i - j] = 1;
				}
				pos = -1;
				break;
			}
			else
				right += tmp;
		}
		if (pos >= 0) {
			one[pos] = true;
			p -= right;
			L--;
		}
	}
	
	for (int i = 0; i < n; i++) {
		fout << (int)one[n - 1 - i];
	}
	fout << endl;
	return 0;
}