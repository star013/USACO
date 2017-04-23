/*
ID: thustar1
PROG: maze1
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct P
{
	int h;
	int w;
};

void bfs(P p, char map[201][77], int d[100][38], int w, int h) {
	// broad first search
	int MAX = 10000;
	// d[100][38] distance
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			d[i][j] = MAX;
	d[p.h][p.w] = 1;
	vector<P> queue;
	queue.push_back(p);
	while (queue.size() > 0) {
		p = queue[0];
		queue.erase(queue.begin());
		// d[i][j] at map[2*i+1][2*j+1]
		if (map[2 * p.h][2 * p.w + 1] == ' '&&p.h>0&&d[p.h-1][p.w]==MAX) {
			P tmp; tmp.h = p.h - 1; tmp.w = p.w;
			d[tmp.h][tmp.w] = d[p.h][p.w] + 1;
			queue.push_back(tmp);
		}
		if (map[2 * p.h + 1][2 * p.w] == ' '&&p.w>0&&d[p.h][p.w - 1] == MAX) {
			P tmp; tmp.h = p.h; tmp.w = p.w - 1;
			d[tmp.h][tmp.w] = d[p.h][p.w] + 1;
			queue.push_back(tmp);
		}
		if (map[2 * p.h + 2][2 * p.w + 1] == ' '&&p.h<h&&d[p.h + 1][p.w] == MAX) {
			P tmp; tmp.h = p.h + 1; tmp.w = p.w;
			d[tmp.h][tmp.w] = d[p.h][p.w] + 1;
			queue.push_back(tmp);
		}
		if (map[2 * p.h + 1][2 * p.w + 2] == ' '&&p.w<w&&d[p.h][p.w + 1] == MAX) {
			P tmp; tmp.h = p.h; tmp.w = p.w + 1;
			d[tmp.h][tmp.w] = d[p.h][p.w] + 1;
			queue.push_back(tmp);
		}

	}
}

int min(int a, int b) {
	if (a > b)
		return b;
	else
		return a;
}
int main() {
	ofstream fout("maze1.out");
	ifstream fin("maze1.in");
	int w, h;//w==width, h==height
	fin >> w >> h;//w<=38,h<=100
	char map[201][77];
	int d[100][38];//distance
	char s[78];
	fin.getline(s, 78); // read \n
	for (int i = 0; i < 2 * h + 1; i++) {
		fin.getline(s, 78); // read whitespace
		for (int j = 0; j < 2 * w + 1; j++)
			map[i][j] = s[j];
	}
	// d[i][j] at map[2*i+1][2*j+1]
	P p1, p2;
	p1.h = p1.w = -1; p2.h = p2.w = -1;
	int i = 0, j = 0;
	for(j=0;j<w;j++)
		if (map[2*i][2*j+1] == ' ') {
			if (p1.h == -1) {
				p1.h = i; p1.w = j;
			}
			else {
				p2.h = i; p2.w = j;
			}
			map[2 * i][2 * j + 1] = 'x';
		}
	i = h - 1;
	for (j = 0; j<w; j++)
		if (map[2 * i + 2][2 * j + 1] == ' ') {
			if (p1.h == -1) {
				p1.h = i; p1.w = j;
			}
			else {
				p2.h = i; p2.w = j;
			}
			map[2 * i + 2][2 * j + 1] = 'x';
		}
	j = 0;
	for(i=0;i<h;i++)
		if (map[2 * i + 1][2 * j] == ' ') {
			if (p1.h == -1) {
				p1.h = i; p1.w = j;
			}
			else {
				p2.h = i; p2.w = j;
			}
			map[2 * i + 1][2 * j] = 'x';
		}
	j = w - 1;
	for (i = 0; i<h; i++)
		if (map[2 * i + 1][2 * j + 2] == ' ') {
			if (p1.h == -1) {
				p1.h = i; p1.w = j;
			}
			else {
				p2.h = i; p2.w = j;
			}
			map[2 * i + 1][2 * j + 2] = 'x';
		}

	/*cout << endl;
	for (int i = 0; i < 2 * h + 1; i++) {
		for (int j = 0; j < 2 * w + 1; j++)
			cout << map[i][j];
		cout << endl;
	}
	cout << "p1 = (" << p1.h << "," << p1.w << ")" << endl;
	cout << "p2 = (" << p2.h << "," << p2.w << ")" << endl;*/

	int d1[100][38];
	int d2[100][38];
	bfs(p1, map, d1, w, h);
	bfs(p2, map, d2, w, h);
	//cout << "d1="<< endl;
	//for (int i = 0; i < h; i++) {
	//	for (int j = 0; j < w; j++)
	//		cout << d1[i][j] << " ";
	//	cout << endl;
	//}
	//cout << "d2=" << endl;
	//for (int i = 0; i < h; i++) {
	//	for (int j = 0; j < w; j++)
	//		cout << d2[i][j] << " ";
	//	cout << endl;
	//}

	int res = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (res < min(d1[i][j], d2[i][j]))
				res = min(d1[i][j], d2[i][j]);
		}
	}
	fout << res << endl;
	return 0;
}