/*
ID: thustar1
PROG: inflate
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Course
{
	int score;
	int time;
};

int cmp(const void* a, const void* b) {
	Course* c1 = (Course*)a;
	Course* c2 = (Course*)b;
	return c1->time - c2->time;
}
int main() {
	ofstream fout("inflate.out");
	ifstream fin("inflate.in");
	int m, n;
	fin >> m >> n;
	Course c[10000];
	for (int i = 0; i < n; i++) {
		fin >> c[i].score >> c[i].time;
	}
	qsort(c, n, sizeof(Course), cmp);
	/*for (int i = 0; i < n; i++) {
		cout << "score=" << c[i].score << " time=" << c[i].time << endl;
	}*/

	int res[10001];
	// dynamic programming, initialize
	for (int i = 0; i <= m; i++)
		res[i] = 0;
	// F(T) = max{s[i]+F(T-t[i])}
	for (int i = 0; i <= m; i++) {
		// i==total time
		for (int j = 0; j < n; j++) {
			if (i >= c[j].time) {
				if (res[i] < res[i - c[j].time] + c[j].score)
					res[i] = res[i - c[j].time] + c[j].score;
			}
		}
	}
	// test
	/*for (int i = 0; i <= m; i++) {
		cout << "Total time=" << i << " Best score=" << res[i] << endl;
	}*/
	fout << res[m] << endl;
	return 0;
}