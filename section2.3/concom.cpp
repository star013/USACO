/*
ID: thustar1
PROG: concom
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	ofstream fout("concom.out");
	ifstream fin("concom.in");
	int n;
	int graph[101][101];//100 companies, use a 2D array is not big, but convenient to represent a graph
	bool own[101][101];
	fin >> n;

	//initialize
	for(int i=1;i<=100;i++)
		for (int j = 1; j <= 100; j++) {
			graph[i][j] = 0;
			if (i == j)
				own[i][j] = true;
			else
				own[i][j] = false;
		}
	for (int m = 1; m <= n; m++) {
		int i, j, p;
		fin >> i >> j >> p;
		graph[i][j] = p;
	}

	/*for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}*/
	// search p>50
	n = 100;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (graph[i][j] > 50)
				own[i][j] = true;
		}
	}
	// search
	bool change = true;
	while (change) {
		change = false;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!own[i][j]) {
					int tmp = 0;
					for (int k = 1; k <= n; k++) {
						if (own[i][k])
							tmp += graph[k][j];
					}
					if (tmp > 50) {
						change = true;
						own[i][j] = true;
					}
				}
			}
		}
	}

	bool none = true;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			// own relationship do not have symmetry, so you should not add j=i+1, because j could be <=i
			if (own[i][j]&&i!=j) {
				fout << i << " " << j << endl;
				none = false;
			}
		}
	}
	if (none)
		fout << 0 << endl;
	
	return 0;
}