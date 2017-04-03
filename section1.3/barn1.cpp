/*
ID: thustar1
PROG: barn1
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int compare(const void*a, const void* b) {
	return *(int*)a > *(int*)b; // if a>b, return >0
}

int solve(int* intervals, int end, int m, int result) {
	// intervals[end-1] is last one
	if (m > end) {
		return result;
	}
	else {
		int min = intervals[0];
		int idx = 0;
		for (int i = 0; i < end; i++) {
			if (intervals[i] < min) {
				idx = i;
				min = intervals[i];
			}
		}
		if (idx < end - 1) {
			for (int i = idx; i < end; i++) {
				intervals[i] = intervals[i + 1];
			}
		}
		return solve(intervals, end - 1, m, result + min);
	}
}

int main() {
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");
	int m, s, c;
	fin >> m >> s >> c;
	int* stalls = new int[c];
	for (int i = 0; i < c; i++) {
		fin >> stalls[i];
	}
	// sort
	qsort(stalls, c, sizeof(int),compare);
	/*for (int i = 0; i < c; i++) {
		cout << stalls[i] << endl;
	}*/
	int result = c;
	if (c > 1) {
		int* intervals = new int[c - 1];
		for (int i = 0; i < c-1; i++) {
			intervals[i] = stalls[i + 1] - stalls[i] - 1;
		}
		result = solve(intervals, c-1, m, result);
	}
	fout << result << endl;
	return 0;
}