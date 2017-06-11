/*
ID: thustar1
PROG: spin
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int gcd(int a, int b) {
	// Greatest Common Divisor
	// Euclidean Algorithm
	if (a < b) {
		int c = a;
		a = b;
		b = c;
	}
	int divisor = a / b;
	int remain = a - divisor*b;
	if (remain == 0)
		return b;
	else if (b == 1)
		return 1;
	else
		return gcd(b, remain);
}

bool judge(int deg, int start, int extend) {
	// tmp = angle difference in clock-wise direction
	int tmp = deg - start;
	if (tmp < 0)
		tmp += 360;
	return tmp <= extend;
}

class Idx {
public:
	int idx;
	int len;
};

int cmp(const void*a, const void* b) {
	Idx* ta = (Idx*)a;
	Idx* tb = (Idx*)b;
	return ta->len - tb->len;
}

int main() {
	ofstream fout("spin.out");
	ifstream fin("spin.in");
	//fout << gcd(60, 360) << " " << gcd(30, 97) << " " << gcd(24, 36)<<" "<<gcd(1,360) << endl;
	int speed[5];
	int start[5][5], extend[5][5];
	int wedge[5],len[5];
	Idx help[5];
	for (int i = 0; i < 5; i++) {
		fin >> speed[i];
		int w;
		fin >> w;
		len[i] = 0;
		for (int j = 0; j < w; j++) {
			fin >> start[i][j] >> extend[i][j];
			len[i] += extend[i][j];
		}
		wedge[i] = w;
	}
	for (int i = 0; i < 5; i++) {
		help[i].idx = i;
		help[i].len = len[i];
	}
	qsort(help, 5, sizeof(Idx), cmp);
	int relativeSpeed[5];
	bool angle[5][360];
	for (int i = 0; i < 5; i++) {
		//fout << "idx=" << help[i].idx << endl;
		relativeSpeed[i] = speed[help[i].idx] - speed[help[0].idx];
		for (int j = 0; j < 360; j++) {
			angle[i][j] = false;
		}
		for (int j = 0; j < wedge[help[i].idx]; j++) {
			for (int k = 0; k <= extend[help[i].idx][j]; k++) {
				angle[i][(start[help[i].idx][j] + k) % 360] = true;
			}
		}
	}
	int num[5];//num[i]== the # of unique positions at the i+1 th wheel
	for (int i = 0; i < 5; i++) {
		num[i] = 360 / gcd(360, speed[i]);
	}
	int maxnum = 1;
	for (int i = 0; i < 5; i++)
		maxnum *= num[i];

    //The key observation for this problem is that after 360 seconds, the wheels have returned to their original locations, so if the wheels don't line up in 360 seconds, they will never line up.
	maxnum = 100000;
	//fout <<"maxnum="<< maxnum << endl;
	
	int degree[5], tmpdeg[5];
	for (int i = 0; i < 5; i++) {
		degree[i] = 0;
		tmpdeg[i] = 0;
	}
	bool exist = false;
	bool flag = true;
	for (int t = 0; t <= maxnum; t++) {
		// Question require that the light can go through from any angle!
		for (int deg = 0; deg < 360; deg++) {
			if (angle[0][deg]) {
				flag = true;
				for (int i = 1; i < 5; i++) {
					tmpdeg[i] = (deg - degree[i] + 360) % 360;
					if (!angle[i][tmpdeg[i]]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					fout << t << endl;
					return 0;
				}
			}
		}
		// increment degree
		for (int i = 1; i < 5; i++) {
			degree[i] += relativeSpeed[i];
			if (degree[i] < 0)
				degree[i] += 360;
			if (degree[i] > 360)
				degree[i] -= 360;
		}
	}
	if (!exist)
		fout << "none" << endl;
	return 0;
}
