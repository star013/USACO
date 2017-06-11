/*
ID: thustar1
PROG: ratios
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
	ofstream fout("ratios.out");
	ifstream fin("ratios.in");
	int goal[3];
	int mix[3][3];// mix[i][j], i th mixture, j th component, for cache optimize
	for (int i = 0; i < 3; i++) {
		fin >> goal[i];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fin >> mix[i][j];
		}
	}
	/*for (int i = 0; i < 3; i++) {
		fout << goal[i] << " ";
	}
	fout << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fout << mix[i][j] << " ";
		}
		fout << endl;
	}*/
	int TOTAL_INIT = 100000;
	int total = TOTAL_INIT;
	int sol[3];
	int tmp[3];
	int ratio;

	// The number of units of each type of feed in the mixture must be less than 100.
	// brute force
	for (int i = 0; i < 100; i++) {
		int ti[3];// for cache optimize
		for (int w = 0; w < 3; w++) {
			ti[w] = i*mix[0][w];
		}
		for (int j = 0; j < 100; j++) {
			int tj[3];// for cache optimize
			for (int w = 0; w < 3; w++) {
				tj[w] = j*mix[1][w];
			}
			for (int k = 0; k < 100; k++) {
				if (i + j + k < total && i+j+k>0) {
					for (int w = 0; w < 3; w++) {
						tmp[w] = ti[w] + tj[w] + k*mix[2][w];
					}
					// Test 5 error!
					/*
					99 99 99 
					1 0 0 
					0 1 0 
					0 0 1
					Attention that should have a positive interger ratio
					*/
					if (tmp[0] * goal[1] == tmp[1] * goal[0] && tmp[0] * goal[2] == tmp[2] * goal[0]&&tmp[0]/goal[0]>0) {
						// match!
						total = i + j + k;
						sol[0] = i;
						sol[1] = j;
						sol[2] = k;
						/*fout << "i,j,k= " << i << "," << j << "," << k << endl;
						fout << "tmp= " << tmp[0] << "," << tmp[1] << "," << tmp[2] << endl;
						fout<<"tmp/goal= " << tmp[0]/goal[0] << "," << tmp[1]/goal[1] << "," << tmp[2]/goal[2] << endl;
						*/
						ratio = tmp[0] / goal[0];
					}
				}
			}
		}
	}
	if (total == TOTAL_INIT)
		fout << "NONE" << endl;
	else {
		for (int w = 0; w < 3; w++)
			fout << sol[w] << " ";
		fout << ratio << endl;
	}
	return 0;
}
