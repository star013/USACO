/*
ID: thustar1
PROG: stamps
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int main() {
	ofstream fout("stamps.out");
	ifstream fin("stamps.in");
	int k, n;
	fin >> k >> n;//k<=200,n<=50
	int stamp[50];
	for (int i = 0; i < n; i++)
		fin >> stamp[i];
	qsort(stamp, n, sizeof(int), cmp);

	// dynamic programming
	short num[2000001];//k<=200,largest stamp is 10000, so the possible maximum value is 200*10000
	// num[money] == minimum # of stamps to construct $money
	num[0] = 0; // obviously, $0 use 0 stamp
	int money = 1;
	while (true) {
		int tmp = 400;//because k<=200, tmp==minimum # of stamps to construct $money
		for (int i = 0; i < n; i++) {
			if (money - stamp[i] >= 0) {
				if (tmp > num[money - stamp[i]])
					tmp = num[money - stamp[i]];
			}
		}
		num[money] = tmp + 1;
		if (num[money] > k) // end condition
			break;
		money++;
	}
	/*for (int i = 0; i < money; i++)
		cout << "money="<<i<<" # of stamps="<< num[i] << endl;*/
	fout << money-1<< endl;
	return 0;
}