/*
ID: thustar1
PROG: wormhole
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;



class P // a 2D point
{
public:
	int x;
	int y;
	P() { x = 0; y = 0; }
	P(int a, int b) { x = a; y = b; }
	P(P& p) { x = p.x; y = p.y; }
};

int cmp(const void* a, const void* b) {
	P* p1 = (P*)a;
	P* p2 = (P*)b;
	if (p1->y < p2->y) return -1;
	if (p1->y == p2->y) {
		if (p1->x < p2->x) return -1;
		if (p1->x == p2->x) return 0;
		if (p1->x > p2->x) return 1;
	}
	return 1;
}

void combination(int n, int* info, int remain, int beg, vector<int*>& pairs) {
	if (remain == 0) {
		int* res = new int[n];
		for (int i = 0; i < n; i++) {
			res[i] = info[i];
		}
		pairs.push_back(res);
	}
	for (int i = beg; i < n-1; i++) {
		// should begin at the latter part of the pool, because previous combinatioins have already been selected
		for (int j = i+1; j < n; j++) {
			if (info[i] == -1 && info[j] == -1) {
				// select two elements that were not selected before
				info[i] = j;
				info[j] = i;
				combination(n, info, remain - 2, i+1, pairs);
				// remember to recover state
				info[i] = -1;
				info[j] = -1;
			}
		}
	}
}

vector<int*> getCombination(int n) {
	// brute force to get all combinations, 12 choose 2 = C(12,2)*C(10,2)*C(8,2)*C(6,2)*C(4,2)/fact(6)=10395
	// initialize
	int* info = new int[n];
	for (int i = 0; i < n; i++)
		info[i] = -1;
	vector<int*> pairs;
	combination(n, info, n, 0, pairs);
	return pairs;
}

int findRightPoint(P* p, int n, int beg) {
	// find the first right point close to p[beg]
	if (beg == n - 1)
		return -1;
	if (p[beg + 1].y == p[beg].y)
		return beg + 1;
	else
		return -1;
}

bool searchLoop(P* p, int n, int beg, int* info, bool* travel) {
	// Attention, even a euclidean loop is not enough
	// consider 4 points in line y=0,  (0,2),(1,3) pair
	// cow start at 2, then go 2-->3-->1-->2-->0-->1-->3-->inf
	// we should confirm that the path is traveled twice in the same direction!
	int next = findRightPoint(p, n, beg);
	if (next == -1)// without a right point, must not conform a loop
		return false;
	next = info[next];
	if (travel[next])
		return true;
	else {
		travel[next] = true; // travel[i] means cow go through path i-->info[i], it should go twice the path
		return searchLoop(p, n, next, info, travel);
	}
}

void print(const P* p, int n) {
	// test
	for (int i = 0; i < n; i++)
		cout << p[i].x << "," << p[i].y << endl;
}

void printCombination(const vector<int*> pairs, int n) {
	// test
	bool* flag = new bool[n];
	for (int i = 0; i < pairs.size(); i++) {
		cout << "combinatioin " << i + 1 << endl;
		for (int j = 0; j < n; j++)
			flag[j] = true;
		for (int j = 0; j < n; j++) {
			if (flag[j]) {
				flag[j] = false;
				flag[pairs[i][j]] = false;
				cout << "(" << j << "," << pairs[i][j] << ") ";
			}
		}
		cout << endl;
	}
}

void printResult(int* info, int n) {
	// test
	bool* flag = new bool[n];
	for (int j = 0; j < n; j++)
		flag[j] = true;
	for (int j = 0; j < n; j++) {
		if (flag[j]) {
			flag[j] = false;
			flag[info[j]] = false;
			cout << "(" << j << "," << info[j] << ") ";
		}
	}
	cout << endl;
	
}

int solve(P* p, int n) {
	int res = 0;
	int* info = new int[n];
	for (int i = 0; i < n; i++)
		info[i] = -1;
	vector<int*> pairs;
	combination(n, info, n, 0, pairs);
	for (int i = 0; i < pairs.size(); i++) {
		info = pairs[i];
		for (int j = 0; j < n; j++) {
			bool* travel = new bool[n];
			for (int k = 0; k < n; k++)
				travel[k] = false;
			if (searchLoop(p, n, j, info, travel)) {
				res++;
				//printResult(info, n);
				break;
			}
		}
	}
	return res;
}
int main() {
	ofstream fout("wormhole.out");
	ifstream fin("wormhole.in");
	int n;
	fin >> n;
	P* p = new P[n];
	for (int i = 0; i < n; i++)
		fin >> p[i].x >> p[i].y;
	qsort(p, n, sizeof(P), cmp);
	//print(p, n);
	/*vector<int*>pairs = getCombination(n);
	printCombination(pairs, n);*/
	fout << solve(p, n) << endl;
	return 0;
}