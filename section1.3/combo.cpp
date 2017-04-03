/*
ID: thustar1
PROG: combo
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// host and master are symmetric
int solve(int n, int* host, bool* flag) {
	int res = 0;
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			for (int k = -2; k <= 2; k++) {
				int d[3] = { 0 };
				d[0] = (host[0] - 1 + i + n) % n;
				d[1] = (host[1] - 1 + j + n) % n;
				d[2] = (host[2] - 1 + k + n) % n;
				if (flag[d[0] * n*n + d[1] * n + d[2]]) {
					flag[d[0] * n*n + d[1] * n + d[2]] = false;
					res++;
				}

			}
		}
	}

	return res;
}

void print(bool* flag, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (!flag[i*n*n + j*n + k])
					cout << i + 1 << "," << j + 1 << "," << k + 1 << endl;
			}
		}
	}
}
int main() {
	ofstream fout("combo.out");
	ifstream fin("combo.in");
	int n;
	fin >> n;
	int host[3], master[3];
	for (int i = 0; i < 3; i++)
		fin >> host[i];
	for (int i = 0; i < 3; i++)
		fin >> master[i];
	bool* flag = new bool[n*n*n];
	for (int i = 0; i < n*n*n; i++)
		flag[i] = true;
	int res = solve(n, host, flag);
	res += solve(n, master, flag);
	fout << res << endl;
	//print(flag, n);
	return 0;
}