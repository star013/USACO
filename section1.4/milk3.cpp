/*
ID: thustar1
PROG: milk3
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int min(int a, int b) {
	if (a < b) return a;
	else return b;
}

void toss(int& a, const int B, int& b) {
	// toss from bucket A to B
	// B is volume of bucket, a,b are volume of milk
	int volume = min(a, B-b);
	a -= volume;
	b += volume;
}

void tosswarp(int& a, int& b, int& c, const int A, const int B, const int C, int i) {
	switch (i)
	{
	case 0:toss(a, B, b);
		break;
	case 1:toss(a, C, c);
		break;
	case 2:toss(b, A, a);
		break;
	case 3:toss(b, C, c);
		break;
	case 4:toss(c, A, a);
		break;
	case 5:toss(c, B, b);
		break;
	default:
		break;
	}
	return;
}

void search(int a, int b, int c, const int A, const int B, const int C, bool* state, vector<int>& result) {
	// there are at most 21*21*21= 9261 states (a,b,c)
	// depth first search
	if (state[21 * 21 * a + 21 * b + c])
		return;
	state[21 * 21 * a + 21 * b + c] = true;
	if (a == 0)
		result.push_back(c);
	int pa = a, pb = b, pc = c;//record previous a,b,c

	for (int i = 0; i < 6; i++) {
		a = pa; b = pb; c = pc;
		tosswarp(a, b, c, A, B, C, i);
		if (!(a == pa&&b == pb&&c == pc))
			search(a, b, c, A, B, C, state, result);
	}

}
int cmp(const void*a, const void*b) {
	return *(int*)a - *(int*)b;
}

void printVec(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;
}

void fprintVec(vector<int> a,ofstream& fout) {
	for (int i = 0; i < a.size()-1; i++)
		fout << a[i] << " ";
	fout <<a[a.size()-1] <<endl;
}

int main() {
	ofstream fout("milk3.out");
	ifstream fin("milk3.in");
	int A, B, C;
	fin >> A >> B >> C;
	bool state[9261];
	for (int i = 0; i < 9261; i++)
		state[i] = false;
	vector<int> result;
	int a = 0, b = 0, c = C;
	search(a, b, c, A, B, C, state, result);
	qsort(&result[0], result.size(), sizeof(int), cmp);
	//printVec(result);
	fprintVec(result, fout);
	return 0;
}