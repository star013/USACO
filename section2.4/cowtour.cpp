/*
ID: thustar1
PROG: cowtour
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct P
{
	int x;
	int y;
}; // point

double distance(P p1, P p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void floyd(double d[150][150], int n, int g[150][150], P p[150], int MAX_VALUE) {
	// Floyd-Warshall algorithm
	// initialize
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				d[i][j] = 0;
			else if (g[i][j] > 0)
				d[i][j] = distance(p[i], p[j]);
			else
				d[i][j] = MAX_VALUE;
		}
	}
	// get shortest path for each node
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
	}

	/*cout << "shortest path" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << d[i][j]<<" ";
		cout << endl;
	}*/
}

double max(double a1, double a2, double a3) {
	double res = a1;
	if (res < a2)
		res = a2;
	if (res < a3)
		res = a3;
	return res;
}

int main() {
	ofstream fout("cowtour.out");
	ifstream fin("cowtour.in");
	int n;
	P pts[150];// n<=150
	int g[150][150]; // g == matrix representation of graph
	fin >> n;
	for (int i = 0; i < n; i++)
		fin >> pts[i].x >> pts[i].y;
	char s[160];
	fin.getline(s, 160); // read \n
	for (int i = 0; i < n; i++) {
		fin.getline(s, 160); // read whitespace
		for (int j = 0; j < n; j++)
			g[i][j] = s[j] - '0';
	}

	/*cout << "points" << endl;
	for (int i = 0; i < n; i++)
		cout << pts[i].x << " " << pts[i].y << endl;
	cout << "graph =" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << g[i][j];
		cout << endl;
	}*/
	
	double d[150][150];
	int MAX_VALUE = 1000000 * 2;
	floyd(d, n, g, pts, MAX_VALUE);

	double v[150];// record the longest path at each vertex
	for (int i = 0; i < n; i++) {
		double tmp = 0;
		for (int j = 0; j < n; j++) {
			if (d[i][j] < MAX_VALUE && tmp < d[i][j])
				tmp = d[i][j];
		}
		v[i] = tmp;
	}

	/*cout << "longest path at each vertex" << endl;
	for (int i = 0; i < n; i++) {
		cout << v[i] << endl;
	}*/

	int num = 0;// num == # pastures
	double diameter[150];
	int group[150];
	for (int i = 0; i < n; i++) {
		group[i] = -1;
	}
	int count = 0;
	while (count < n) {
		int tmp = 0;
		while (group[tmp] > -1)
			tmp++;
		for (int i = 0; i < n; i++) {
			if (d[tmp][i] < MAX_VALUE) {
				group[i] = num;
				count++;
			}
			// Note: the first time, I want to get diameter in this block
			// BUT it is wrong
			// because that will be the longest path from a vertex, it is not the diameter for that subgraph
		}
		num++;
	}

	for (int i = 0; i < num; i++) {
		diameter[i] = 0;
		// get diameter for each paster
		for (int j = 0; j < n; j++) {
			if (group[j] == i) {
				if (diameter[i] < v[j])
					diameter[i] = v[j];
			}
		}
	}

	/*cout << "group allocation" << endl;
	for (int i = 0; i < n; i++) {
		cout << group[i] << endl;
	}
	cout << "diameter at each pasture" << endl;
	for (int i = 0; i < num; i++) {
		cout << "group " << i << " diameter = " << diameter[i] << endl;
	}*/

	int tracki = 0, trackj = 0, trackii = 0, trackjj = 0;
	double res = MAX_VALUE;
	if (n == 1) {
		// 1<=N, conquer special case N==1
		res = diameter[0];
	}
	// add a path between pastures
	for (int i = 0; i < num - 1; i++) {
		for (int j = i + 1; j < num; j++) {
			for (int ii = 0; ii < n; ii++) {
				for (int jj = 0; jj < n; jj++) {
					if (group[ii] == i&&group[jj] == j) {
						double tmp = v[ii] + v[jj] + distance(pts[ii], pts[jj]);
						tmp = max(tmp, diameter[i], diameter[j]);
						if (tmp < res) {
							res = tmp;
							tracki = i; trackj = j; trackii = ii; trackjj = jj;
						}
					}
				}
			}
		}
	}
	/*cout << "track i = group " << tracki << endl;
	cout << "track j = group " << trackj << endl;
	cout << "track ii = vertex " << trackii << "(" << pts[trackii].x << "," << pts[trackii].y << ")  longest path = " << v[trackii] << endl;
	cout << "track jj = vertex " << trackjj << "(" << pts[trackjj].x << "," << pts[trackjj].y << ")  longest path = " << v[trackjj] << endl;
	*/
	fout << fixed << setprecision(6) << res << endl;
	return 0;
}