/*
ID: thustar1
PROG: butter
LANG: C++11
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include <iostream>
//#include <string>
//#include <vector>
//#include <cmath>
//#include <iomanip>
//#include <assert.h>
using namespace std;

#define MAXP 801
#define MAXC 1500
#define DIST_INF 10000
/*
largest possible path 255*800=204,000 >> 65535 largest unsigned short
Thus use int instead of unsigned int
*/

struct Edge
{
	short src;
	short dest;
	short d;
};

int cmp(const void*a, const void*b) {
	Edge* ta = (Edge*)a;
	Edge* tb = (Edge*)b;
	if (ta->src != tb->src)
		return ta->src - tb->src;
	else
		return ta->dest - tb->dest;
}

int main() {
	ofstream fout("butter.out");
	ifstream fin("butter.in");
	int n, p, c;// n<=500, p<=800, c<=1450
	short cow[MAXP];
	//int dist[MAXP][MAXP];
	fin >> n >> p >> c;
	for (int i = 0; i < MAXP; i++) {
		cow[i] = 0;
	}
	
	for (int i = 0; i < n; i++) {
		int tmp;
		fin >> tmp;
		cow[tmp]++;
	}

	// for a very big matrix, new it is a faster way
	short**dist = new short*[MAXP];
	for (int i = 0; i < MAXP; i++) {
		dist[i] = new short[MAXP];
	}
	for (int i = 0; i < MAXP; i++) {
		for (int j = 0; j < MAXP; j++) {
			dist[i][j] = DIST_INF;
		}
		dist[i][i] = 0;
	}

	// for a small array, use static array instead of new an array is faster!
	Edge e[MAXC * 2];
	for (int i = 0; i < c; i++) {
		short src, dest, d;
		fin >> src >> dest >> d;
		e[2 * i].src = src;
		e[2 * i].dest = dest;
		e[2 * i].d = d;
		e[2 * i + 1].src = dest;
		e[2 * i + 1].dest = src;
		e[2 * i + 1].d = d;
	}
	qsort(e, 2 * c, sizeof(Edge), cmp);


	// test
	/*cout << endl << endl << endl << "test edge" << endl;
	for (int i = 0; i < 2 * c; i++) {
		cout << "edge " << i << " src,dest,d= " << e[i].src << "," << e[i].dest << "," << e[i].d << endl;
	}
	cout << endl << endl << endl << endl;*/

	short begidx[MAXP];
	short endidx[MAXP];
	for (int i = 0; i <= p; i++) {
		begidx[i] = endidx[i] = -1;
	}
	short prevsrc = -1;
	for (int i = 0; i < 2 * c; i++) {
		short src = e[i].src;
		if (begidx[src] == -1) {
			begidx[src] = i;
			if (prevsrc != -1) {
				endidx[prevsrc] = i;
			}
			prevsrc = src;
		}
	}
	endidx[prevsrc] = 2*c;

	/*cout << endl << endl << endl << "test begin end index" << endl;
	for (int i = 1; i <= p; i++) {
		cout << "src=" << i << " begin,end= " << begidx[i] << "," << endidx[i] << endl;
	}
	cout << endl << endl << endl << endl;*/


	//// shortest path
	//// Floyd algorithm is O(V^3)
	//// Test 9 TLE
	//short**dist_v1 = new short*[MAXP];
	//for (int i = 0; i < MAXP; i++) {
	//	dist_v1[i] = new short[MAXP];
	//}
	//for (int i = 0; i < MAXP; i++) {
	//	for (int j = 0; j < MAXP; j++) {
	//		dist_v1[i][j] = DIST_INF;
	//	}
	//	dist_v1[i][i] = 0;
	//}
	//for (int i = 0; i < 2 * c; i++) {
	//	dist_v1[e[i].src][e[i].dest] = e[i].d;
	//}

	//bool update = true;
	//int up = 0;
	//while (update) {
	//	update = false;
	//	for (int i = 1; i < p; i++) {
	//		for (int k = 1; k <= p; k++) {
	//			int tmp = dist_v1[i][k];
	//			for (int j = i+1; j <= p; j++) {
	//				int tmp2 = tmp + dist_v1[k][j];
	//				if (dist_v1[i][j] > tmp2) {
	//					dist_v1[j][i] = dist_v1[i][j] = tmp2;
	//					update = true;
	//				}
	//			}
	//		}
	//	}
	//	if (update) {
	//		up++;
	//		cout << "update " << up << endl;
	//	}
	//}

	bool visit[MAXP];
	int remain = MAXP;
	int tmpbeg, tmpend, tmpsum, tmpdist,node,tmp;
	for (int i = 1; i <= p; i++) {
		// use node i as source
		visit[i] = true;
		// update neighbor of i
		tmpbeg = begidx[i];
		tmpend = endidx[i];
		for (int k = tmpbeg; k < tmpend; k++) {
			//assert(i == e[k].src);
			if (dist[i][e[k].dest] > e[k].d) {
				dist[i][e[k].dest] = e[k].d;
			}
		}
		for (int j = 1; j <i; j++) {
			visit[j] = true;
			dist[i][j] = dist[j][i];
			// add node j and update
			tmpbeg = begidx[j];
			tmpend = endidx[j];
			tmpdist = dist[i][j];
			for (int k = tmpbeg; k < tmpend; k++) {
				tmpsum = tmpdist + e[k].d;
				if (dist[i][e[k].dest] > tmpsum) {
					dist[i][e[k].dest] = tmpsum;
				}
			}
		}
		for (int j = i + 1; j <= p; j++) {
			visit[j] = false;
		}
		remain = MAXP - i;
		while (remain > 0) {
			// select nearest node which is not visited
			// because i+1 can be visited, do not initiate node at i+1, it produces wrong result
			node = 0;
			tmp = DIST_INF;
			for (int j = i + 1; j <= p; j++) {
				if (!visit[j] && dist[i][j] < tmp) {
					tmp = dist[i][j];
					node = j;
				}
			}
			visit[node] = true;
			remain--;
			// update dist related to node
			tmpbeg = begidx[node];
			tmpend = endidx[node];
			for (int k = tmpbeg; k < tmpend; k++) {
				tmpsum = dist[i][node] + e[k].d;
				if (dist[i][e[k].dest] > tmpsum) {
					dist[i][e[k].dest] = tmpsum;
				}
			}
		}
	}

	// test dijkstra and floyd algorithm
	/*for (int i = 1; i <= p; i++) {
		for (int j = 1; j <= p; j++) {
			if (dist[i][j] != dist_v1[i][j]) {
				cout << "i,j=" << i << "," << j << " dist=" << dist[i][j] << ", dist_v1=" << dist_v1[i][j] << endl;
			}
		}
	}*/

	int result = DIST_INF*p;
	for (int i = 1; i <= p; i++) {
		int tmp = 0;
		for (int j = 1; j <= p; j++) {
			tmp += cow[j] * dist[i][j];
		}
		if (tmp < result) {
			result = tmp;
		}
	}

	fout << result << endl;

	/*result = DIST_INF*p;
	for (int i = 1; i <= p; i++) {
		int tmp = 0;
		for (int j = 1; j <= p; j++) {
			tmp += cow[j] * dist_v1[i][j];
		}
		if (tmp < result) {
			result = tmp;
		}
	}
	cout << result << endl;*/

	return 0;
}
