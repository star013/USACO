/*
ID: thustar1
PROG: money
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int cmp(const void*a, const void*b) {
	return *(int*)a - *(int*)b;
}
int main() {
	ofstream fout("money.out");
	ifstream fin("money.in");
	int v,n;
	fin >> v >> n;
	//1<=v<=25, 1<=n<=10,000
	unsigned long long res[10001];
	unsigned long long prev[10001];
	int coin[25];
	for (int i = 0; i < v; i++)
		fin >> coin[i];
	qsort(coin, v, sizeof(int), cmp);

	res[0] = 1;// 0 only has one way to get
	prev[0] = 1;
	for (int i = 1; i <= n; i++) {
		res[i] = 0;
		prev[i] = 0;
	}
	// dynamic programming
	// version 0.1: have coin 1 and 5, n==10 has equal ways as ways of n==9 + 1 yuan and ways of n==5 + 5 yuan
	// v0.1 is a naive thought, but it is wrong
	// because the subsolution may contain common combinations, for example, 9+1 solution contain (5+1+1+1+1)+1 and 5+5 solution also contain (1+1+1+1+1)+5
	// version 0.2: sort coins, and consider from smallest coin to largest coin one by one
	// use f[i,j] represent money j is composed of coins which are <= coin[i]
	// then we have f[i,j] = f[i,j-coin[i]] + f[i-1,j] (j-coin[i]>=0)
	//                     = f[i-1,j] (j-coin[i]<0)
	// f[i,j-coin[i]] == # of combinations that money j-coin[i] is composed of coins which are <= coin[i]
	// f[i-1,j] == # of combinations that money j is composed of coins which are <= coin[i-1]
	int c = 0;
	for (int i = 1; i <= n; i++) {
		if (i%coin[c] == 0) {
			// only use one kind of coin, only have one combination
			prev[i] = 1;
			res[i] = 1;
		}
	}
	for (c = 1; c < v; c++) {
		for (int i = 1; i <= n; i++) {
			if (i < coin[c])
				// f[i,j] = f[i-1,j] (j-coin[i]<0)
				res[i] = prev[i];
			else
				// f[i,j] = f[i,j-coin[i]] + f[i-1,j] (j-coin[i]>=0)
				res[i] = prev[i] + res[i - coin[c]];
		}
		// update prev, just to save memory, you can save all coin conditions like f[i,j] if you wish
		for (int i = 1; i <= n; i++)
			prev[i] = res[i];
	}
	//for (int i = 1; i <= n; i++)
	//	cout << res[i] << " ";
	fout << res[n] << endl;
	return 0;
}