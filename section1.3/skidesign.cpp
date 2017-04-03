/*
ID: thustar1
PROG: skidesign
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int cmp(const void*a, const void* b) {
	if(*(int*)a < *(int*)b) return -1;
	if (*(int*)a == *(int*)b) return 0;
	if (*(int*)a > *(int*)b) return 1;
}

// (x+y)^2+(x-y)^2 = x^2+y^2 >= x^2
// therefore move equal amount from higheset to lowest is a greedy strategy that works for optimal
// sorry, I seem to misunderstand the meaning of question, it seems that
// the change volume of each hill is independent, so just have to find a common low boundary
// to make the total cost minimum. It is a convex optimization problem
int sum(int*h, int n, int b) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (h[i] < b)
			res += (h[i] - b)*(h[i] - b);
		if (h[i] > b + 17)
			res += (h[i] - b - 17)*(h[i] - b - 17);
	}
	return res;
}
int solve(int*h, int n) {// 1 <= N <= 1,000
	if (h[n-1] - h[0] <= 17)
		return 0;
	else {
		int b = h[0];
		int res = sum(h, n, b);
		// brute force search a optimal result
		// O(N*interval), in this question, N<=1000, interval<=100-0=100
		// in fact, we can also use dichotomy to accelerate convergent rate
		while (b < h[n - 1]) {
			b++;
			int tmp = sum(h, n, b);
			if (tmp < res)
				res = tmp;
		}
		return res;
	}
}

int main() {
	ofstream fout("skidesign.out");
	ifstream fin("skidesign.in");
	int n;
	fin >> n;
	int* h = new int[n];
	for (int i = 0; i < n; i++)
		fin >> h[i];
	qsort(h, n, sizeof(int), cmp);
	// test
	/*cout << "test" << endl;
	for (int i = 0; i < n; i++)
		cout << h[i] << endl;*/
	fout << solve(h, n) << endl;
	return 0;
}