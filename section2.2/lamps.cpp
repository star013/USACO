/*
ID: thustar1
PROG: lamps
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void printVec(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;
}

void printInts(int* a,int n) {
	for (int i = 0; i < n; i++)
		cout << a[i];
	cout << endl;
}
void pressButton(int* lamp, int n, int b) {
	// b is button
	if (b == 1) {
		for (int i = 1; i <= n; i++)
			lamp[i-1] = (lamp[i-1] + 1) % 2;
	}
	if (b == 2) {
		for (int i = 1; i <= n; i++)
			if (i % 2 == 1)
				lamp[i-1] = (lamp[i-1] + 1) % 2;
	}
	if (b == 3) {
		for (int i = 1; i <= n; i++)
			if (i % 2 == 0)
				lamp[i-1] = (lamp[i-1] + 1) % 2;
	}
	if (b == 4) {
		for (int i = 1; i <= n; i++)
			if (i % 3 == 1)
				lamp[i-1] = (lamp[i-1] + 1) % 2;
	}
}

bool isok(int* lamp, int n, vector<int>& on, vector<int>& off) {
	for (int i = 0; i < on.size(); i++)
		if (lamp[on[i] - 1] == 0)
			return false;
	for (int i = 0; i < off.size(); i++)
		if (lamp[off[i] - 1] == 1)
			return false;
	return true;
}

int* dpcpyInt(int* a, int n) {
	int* res = new int[n];
	for (int i = 0; i < n; i++)
		res[i] = a[i];
	return res;
}

void dfs(int* lamp, int n, vector<int>& on, vector<int>& off, int b, int c,vector<int*>& res) {
	// depth first search, enumerate all button conditions
	// b = button, c=# of different press
	if (c == 0) {
		if (isok(lamp, n, on, off))
			res.push_back(dpcpyInt(lamp, n));
		return;
	}
	// c>0
	if (5 - b < c) // change all buttons left will still be smaller than c
		return;
	// press button b
	pressButton(lamp, n, b);
	dfs(lamp, n, on, off, b + 1, c - 1, res);
	pressButton(lamp, n, b);// recover state, not press button b
	dfs(lamp, n, on, off, b + 1, c, res);
}

struct my {
	int n;
	int val;
};

int cmp(int*a, int*b, int n) {
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return -1;
	}
	return 0;
}

int partition(vector<int*>& a, int n, int beg, int end) {
	// end-beg>=3
	int i = beg, j = end - 1;
	while (i < j) {
		while (cmp(a[i], a[end], n) <= 0)
			i++;
		while (cmp(a[j], a[end], n) >= 0)
			j--;
		if (i < j)
			swap(a[i], a[j]);
	}
	swap(a[i], a[end]);
	return i;
}
void mysort(vector<int*>& a, int n, int beg, int end) {
	if (beg >= end)
		return;
	int mid = (beg + end) / 2;
	if (cmp(a[beg], a[mid], n) == 1) swap(a[beg], a[mid]);
	if (cmp(a[mid], a[end], n) == 1) swap(a[mid], a[end]);
	if (cmp(a[beg], a[mid], n) == 1) swap(a[beg], a[mid]);
	//printInts(a[beg], n);
	//printInts(a[mid], n);
	//printInts(a[end], n);
	if (end - beg < 3)
		return;
	swap(a[mid], a[end]);
	//cout << "after swap" << endl;
	//printInts(a[mid], n);
	//printInts(a[end], n);
	int idx = partition(a, n, beg, end);
	mysort(a, n, beg, idx - 1);
	mysort(a, n, idx + 1, end);

}
int main() {
	ofstream fout("lamps.out");
	ifstream fin("lamps.in");
	int n, c;//10<=N<=100, 0<=C<=10000
	fin >> n >> c;
	int* lamp = new int[n]();
	for (int i = 0; i < n; i++)
		lamp[i] = 1;
	vector<int> on, off;
	int tmp = 0;
	while (tmp != -1) {
		fin >> tmp;
		if (tmp != -1)
			on.push_back(tmp);
	}
	tmp = 0;
	while (tmp != -1) {
		fin >> tmp;
		if (tmp != -1)
			off.push_back(tmp);
	}
	//printVec(on);
	//printVec(off);

	//pressButton(lamp, n, 1);
	//cout << isok(lamp, n, on, off) << endl;

	vector<int*>res;
	// Although 0<=C<=10000 is a large range, the effective C is very limited
	// because press 2 times on one button equals not doing anything
	// if c==4, means press 4 buttons, or press 2 buttons(since 2 press on the same button), or Do not press any button
	if (c % 2 == 0 && c >= 4) {
		dfs(lamp, n, on, off, 1, 4, res);
		dfs(lamp, n, on, off, 1, 2, res);
		dfs(lamp, n, on, off, 1, 0, res);
	}
	// if c==3, means press 3 buttons, or press 1 buttons(since 2 press on the same button)
	if (c % 2 == 1&& c >= 3) {
		dfs(lamp, n, on, off, 1, 3, res);
		dfs(lamp, n, on, off, 1, 1, res);
	}
	// if c==2, means press 2 buttons, or press 0 buttons
	if (c == 2) {
		dfs(lamp, n, on, off, 1, 2, res);
		dfs(lamp, n, on, off, 1, 0, res);
	}
	// if c==1, means press 1 button
	// if c==0, means press 0 button
	if (c <= 1) {
		dfs(lamp, n, on, off, 1, c, res);
	}

	if (res.size() == 0)
		fout << "IMPOSSIBLE" << endl;
	else {
		mysort(res, n, 0, res.size() - 1);
		for (int i = 0; i < res.size(); i++) {
			for (int j = 0; j < n; j++)
				fout << res[i][j];
			fout << endl;
		}
	}
	return 0;
}