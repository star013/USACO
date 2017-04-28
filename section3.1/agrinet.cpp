/*
ID: thustar1
PROG: agrinet
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


int main() {
	ofstream fout("agrinet.out");
	ifstream fin("agrinet.in");
	int n;
	fin >> n;//n<=100
	int g[100][100];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> g[i][j];
		}
	}

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}*/

	// Prim Algorithm
	int INF = 100 * 100000;// because each weight<=100,000 and n<=100
	bool in[100]; // in[i]==true if i belongs to the min span tree
	int d[100]; // d[i] == distance between i and min span tree
	int res = 0;
	for (int i = 0; i < n; i++) {
		in[i] = false;
		d[i] = INF;
	}
	// select first node
	int num = 1;
	int idx = 0;
	d[0] = 0;
	in[0] = true;
	while (num < n) {
		// update distance
		for (int i = 0; i < n; i++) {
			if (!in[i]) {
				if (d[i] > g[idx][i])
					d[i] = g[idx][i];
			}
		}
		// select nearest vertex
		int tmp = INF;
		for (int i = 0; i < n; i++) {
			if (!in[i]) {
				if (d[i] < tmp) {
					tmp = d[i];
					idx = i;
				}
			}
		}
		// add vertex
		res += tmp;
		in[idx] = true;
		num++;
		
		// show test
		/*cout << num << " nodes in tree" << endl;
		for (int i = 0; i < n; i++) {
			cout << "Node " << i << " d=" << d[i] << " in=" << in[i] << endl;
		}
		cout << "res=" << res << endl;*/
	}
	fout << res << endl;
	return 0;
}