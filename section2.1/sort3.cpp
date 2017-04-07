/*
ID: thustar1
PROG: sort3
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void printInts(int* a, int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}


int min(int a, int b) {
	if (a < b) return a;
	else return b;
}

void swapState(int& s1, int& s2, int& res) {
	int tmp = min(s1, s2);
	res += tmp;
	s1 -= tmp;
	s2 -= tmp;
}
int solve(int*a, int n) {
	int one = 0, two = 0;// one = # of 1s, three = # of 3s
	for (int i = 0; i < n; i++) {
		if (a[i] == 1)
			one++;
		else if (a[i] == 2)
			two++;
	}
	// because we can count 1s as one and 2s as two
	// we can expect that in the end a[0:one]=1, a[one:one+two]=2, a[one+two:n]=3, this is like python expression
	int state[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			state[i][j] = 0;
	for (int i = 0; i < n; i++) {
		if (i < one) {
			state[0][a[i] - 1]++;
		}
		else if (i < one + two) {
			state[1][a[i] - 1]++;
		}
		else {
			state[2][a[i] - 1]++;
		}
	}

	// we just have to know the number count in each area without even real swap operation
	int res = 0;
	if (state[0][2] > 0 && state[2][0] > 0) {
		// if there are 3s in a[:one] and there are 1s in a[one+two:], it is optimal to swap those 3s and 1s directly to their area
		swapState(state[0][2], state[2][0], res);
	}
	if (state[0][1] > 0 && state[1][0] > 0) {
		// if there are 2s in a[:one] and there are 1s in a[one:one+two], it is optimal to swap those 2s and 1s directly to their area
		swapState(state[0][1], state[1][0], res);
	}
	if (state[1][2] > 0 && state[2][1] > 0) {
		// if there are 3s in a[one:one+two] and there are 2s in a[one+two:], it is optimal to swap those 3s and 2s directly to their area
		swapState(state[1][2], state[2][1], res);
	}
	// now if it is still disorder in three areas, they can only be 2,3,1 or 3,1,2 remain
	// Proof: 1. Each area can only leave 1 kind remain, because 3 areas are symmetrical
	//			Suppose Area 1 remain both 2 and 3, then Area 2 can only remain 3, because if Area 2 remain 1, Area 1 and Area 2 should have swapped them before
	//					But Area 3 can not remain 1 or 2, because both Area 1 and Area 2 remain 3, if Area 3 remain 1 or 2, Area 3 should have swapped them before
	//					However Area 1 and Area 2 remain 3, Area 3 can not hold 3 complete, it is a contradiction, Thus Area 1 can only remain one kind remain, like only 2 or only 3
	//		  2. If Each Area can only have 1 kind remain, then it can only be 2,3,1 or 3,1,2, since they should have swapped exchangable part before
	// Either 2,3,1 and 3,1,2 need at least 2 swaps to sort and the numbers should be the same in each part
	if (state[0][1] > 0)
		res += 2 * state[0][1];
	else if (state[0][2] > 0)
		res += 2 * state[0][2];

	return res;
}
int main() {
	ofstream fout("sort3.out");
	ifstream fin("sort3.in");
	int n;
	fin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		fin >> a[i];
	printInts(a, n);

	int res = solve(a, n);
	fout << res << endl;
	return 0;
}