/*
ID: thustar1
PROG: nocows
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// search without repeat, i.e. dynamic programming
// The tree structure has intrinsic recursive characteristic
int solve(int n, int h) {
	//n==# of nodes, h==height
	//3<=n<200, 1<h<100
	int res[200][100]; // res[n][h] = result of input n and h
	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 100; j++)
			res[i][j] = 0;
	// each node should have 0 or 2 child
	// thus, a legal tree will satisfy:
	// 2*h-1 <= n <= pow(2,h)-1
	res[1][1] = 1;//simplest tree
	
	for (int h0 = 2; h0 <= h; h0++) {
		for (int n0 = 2 * h0 - 1; n0 <= n; n0+=2) {
			// root h0,n0
			// left child h1,n1, right child h2,n2
			// thus h0=max(h1,h2)+1, n0=n1+n2+1
			// suppose h1==h0-1, left and right child are symmetric
			int h1 = h0 - 1;
			int h2 = 1;
			for (h2 = 1; h2 < h1; h2++) {
				for (int n1 = 2 * h1 - 1; n1 <= n0 - 2; n1 += 2) {
					res[n0][h0] = (res[n0][h0] + 2 * res[n1][h1] * res[n0 - 1 - n1][h2]) % 9901;
				}
			}
			//h2==h1, we should be carefull about n1 and n2, because it is symmetric now
			// res[n1][h1]*res[n0-1-n1][h1] equals res[n0-1-n1][h1]*res[n1][h1] when n1 traverse all possible values
			h2 = h1;
			for (int n1 = 2 * h1 - 1; n1 <= n0 - 2; n1 += 2) {
				res[n0][h0] = (res[n0][h0] + res[n1][h1] * res[n0 - 1 - n1][h2]) % 9901;
			}
		}
	}

	//for (int i = 3; i <= n; i+=2) {
	//	for (int j = 2; j <= h; j++)
	//		cout << res[i][j] << " ";
	//	cout << endl;
	//}
	return res[n][h];
}

int main() {
	ofstream fout("nocows.out");
	ifstream fin("nocows.in");
	int n, h;//n==# of nodes, h==height
	//3<=n<200, 1<h<100
	fin >> n >> h;
	fout << solve(n, h) << endl;
	return 0;
}