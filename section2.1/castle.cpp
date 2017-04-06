/*
ID: thustar1
PROG: castle
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void printMat(short* mat, short M, short N) {
	// M col, N row
	for (short i = 0; i < N; i++) {
		for (short j = 0; j < M; j++)
			cout << mat[i*M + j] << " ";
		cout << endl;
	}
}

void printInts(short* a, short n) {
	for (short i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

struct Wall
{
	bool w[4];// west, north, east, south
};

Wall* getWall() {
	Wall* res = new Wall[16];
	for (short w = 0; w < 2; w++) {
		for (short n = 0; n < 2; n++) {
			for (short e = 0; e < 2; e++) {
				for (short s = 0; s < 2; s++) {
					res[w + 2 * n + 4 * e + 8 * s].w[0] = w;
					res[w + 2 * n + 4 * e + 8 * s].w[1] = n;
					res[w + 2 * n + 4 * e + 8 * s].w[2] = e;
					res[w + 2 * n + 4 * e + 8 * s].w[3] = s;
				}
			}
		}
	}
	return res;
}

void move(short&i, short& j, short k) {
	switch (k)
	{
	case 0:j--; break;
	case 1:i--; break;
	case 2:j++; break;
	case 3:i++; break;
	default:
		break;
	}
}
bool finishFill_v1(short* mat, short& M, Wall* wall, short i, short j, short* compo) {
	// surround by walls
	if (wall[mat[M*i + j]].w[0] && wall[mat[M*i + j]].w[1] && wall[mat[M*i + j]].w[2] && wall[mat[M*i + j]].w[3])
		return true;
	// not surround by walls
	short previ = i, prevj = j;
	for (short k = 0; k < 4; k++) {
		if (!wall[mat[M*i + j]].w[k]) {
			move(i, j, k);
			if (compo[M*i + j] == 0)
				return false;
			i = previ; j = prevj;// recover previous position
		}
	}
	return true;
}

void floodFill_v1(short* mat, short& M, Wall* wall, short i, short j, short* compo, short num) {
	// depth first search
	if (compo[M*i + j] == 0) {
		compo[M*i + j] = num;
		if (finishFill_v1(mat, M, wall, i, j, compo)) {
			return;
		}
		else {
			short previ = i, prevj = j;
			for (short k = 0; k < 4; k++) {
				if (!wall[mat[M*i + j]].w[k]) {
					move(i, j, k);
					floodFill_v1(mat, M, wall, i, j, compo, num);
					i = previ; j = prevj;// recover previous position
				}
			}
		}
	}
}

bool finishFill_v2(short* mat, short& wallInfo, short& M, Wall* wall, short i, short j) {
	// surround by walls
	if (wall[wallInfo].w[0] && wall[wallInfo].w[1] && wall[wallInfo].w[2] && wall[wallInfo].w[3])
		return true;
	// not surround by walls
	short previ = i, prevj = j;
	for (short k = 0; k < 4; k++) {
		if (!wall[wallInfo].w[k]) {
			move(i, j, k);
			if (mat[i*M+j] < 16) // mat[i]<16 means it does not represent a component number
				return false;
			i = previ; j = prevj;// recover previous position
		}
	}
	return true;
}

void floodFill_v2(short* mat, short& M, Wall* wall, short i, short j, short num) {
	// depth first search
	// share the memory of component matrix with wall info matrix to save memory
	short wallInfo = mat[M*i + j];
	if (mat[M*i + j] <16) {
		mat[M*i + j] = num+16; // because wall information is <=15, we can use number larger than 16 to represent the serial number of component
		if (finishFill_v2(mat, wallInfo, M, wall, i, j)) {
			return;
		}
		else {
			short previ = i, prevj = j;
			for (short k = 0; k < 4; k++) {
				if (!wall[wallInfo].w[k]) {
					move(i, j, k);
					floodFill_v2(mat, M, wall, i, j, num);
					i = previ; j = prevj;// recover previous position
				}
			}
		}
	}
}
short* getComponent(short* mat, short M, short N, short&num) {
	short* compo = new short[M*N]();
	Wall* wall = getWall();
	num = 0;
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++) {
			if (compo[i*M + j] == 0) {
				num++;
				floodFill_v1(mat, M, wall, i, j, compo, num);
			}
		}
	return compo;
}

short* getComponent_v2(short* mat, short M, short N, short&num) {
	Wall* wall = getWall();
	num = 0;
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++) {
			if (mat[i*M + j] < 16) {
				num++;
				floodFill_v2(mat, M, wall, i, j, num);
			}
		}
	return mat;
}

void seeNeighbor(short* compo, short M, short i, short j, short ni, short nj, short* neighbor, short num, short* size, short& sumsize, short& c1, short& c2) {
	if (compo[i*M + j] != compo[ni*M + nj] && neighbor[(compo[i*M + j] - 1)*num + compo[ni*M + nj] - 1] == 0) {
		neighbor[(compo[i*M + j] - 1)*num + compo[ni*M + nj] - 1] = size[compo[i*M + j] - 1] + size[compo[ni*M + nj] - 1];
		neighbor[(compo[ni*M + nj] - 1)*num + compo[i*M + j] - 1] = neighbor[(compo[i*M + j] - 1)*num + compo[ni*M + nj] - 1];
		if (neighbor[(compo[i*M + j] - 1)*num + compo[ni*M + nj] - 1] > sumsize) {
			sumsize = neighbor[(compo[i*M + j] - 1)*num + compo[ni*M + nj] - 1];
			c1 = compo[i*M + j];
			c2 = compo[ni*M + nj];
		}
	}
}

void getNeighbor(short* compo, short M, short N, short num, short* size, short& sumsize, short& c1, short& c2, short* neighbor) {
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++) {
			if (j > 0) {
				// see west
				seeNeighbor(compo, M, i, j, i, j - 1, neighbor, num, size, sumsize, c1, c2);
			}
			if (i > 0) {
				// see north
				seeNeighbor(compo, M, i, j, i - 1, j, neighbor, num, size, sumsize, c1, c2);
			}
			if (j < M - 1) {
				// see east
				seeNeighbor(compo, M, i, j, i, j + 1, neighbor, num, size, sumsize, c1, c2);
			}
			if (i < N - 1) {
				// see south
				seeNeighbor(compo, M, i, j, i + 1, j, neighbor, num, size, sumsize, c1, c2);
			}
		}

}

void seeNeighbor_v2(short* compo, short M, short i, short j, short ni, short nj, short num, short* size, short& sumsize, short& c1, short& c2, short& pi,short& pj) {
	if (compo[i*M + j] != compo[ni*M + nj]) {
		short tmp = size[compo[i*M + j] - 16 - 1] + size[compo[ni*M + nj] - 16 - 1];
		if (tmp > sumsize) {
			sumsize = tmp;
			if (j > nj) {
				swap(j, nj);
				swap(i, ni);
			}
			else if (j == nj&& i<ni) {
				swap(i, ni);
			}
			pi = i;
			pj = j;
			c1 = compo[i*M + j];
			c2 = compo[ni*M + nj];
		}
		if (tmp == sumsize) { // to get the left-est lowest boundary
			if (j > nj) {
				swap(j, nj);
				swap(i, ni);
			}
			else if (j == nj&& i<ni) {
				swap(i, ni);
			}
			if (j < pj) {
				pj = j;
				pi = i;
				c1 = compo[i*M + j];
				c2 = compo[ni*M + nj];
			}
			else if (j == pj&&i > pi) {
				pi = i;
				c1 = compo[i*M + j];
				c2 = compo[ni*M + nj];
			}
		}
	}
}

void getNeighbor_v2(short* compo, short M, short N, short num, short* size, short& sumsize, short& c1, short& c2, short& pi, short& pj) {
	pi = 0, pj = N - 1;
	// if all components only have one unit space, I want to get left lower corner for c1 and c2
	for (short i = 0; i < N; i++)
		for (short j = M-1; j >=0; j--) {
			if (j < M - 1) {
				// see east
				seeNeighbor_v2(compo, M, i, j, i, j + 1, num, size, sumsize, c1, c2, pi, pj);
			}
			if (i < N - 1) {
				// see south
				seeNeighbor_v2(compo, M, i, j, i + 1, j, num, size, sumsize, c1, c2, pi, pj);
			}
		}

}

bool isBorder(short *compo, short M, short N, short c1, short i, short j, short c2, short i2, short j2) {
	if (compo[i*M + j] == c1&&compo[i2*M + j2] == c2)
		return true;
	return false;
}

void solve_v1() {
	// solution 1
	// fail at Test 7: M=50,N=50, memory limit exceed
	// because I allocate new memory for component matrix, in fact I can reuse input matrix to become a component matrix to save some memory
	ofstream fout("castle.out");
	ifstream fin("castle.in");
	short M, N;
	fin >> M >> N;
	short *mat = new short[M*N];
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++)
			fin >> mat[i*M + j];
	//printMat(mat, M, N);
	short num = 0;
	short* compo = getComponent(mat, M, N, num);
	delete mat;
	//printMat(compo, M, N);
	short* size = new short[num](); //Note that you must use the empty parentheses - you cannot, for example, use(0) or any other expression(which is why this is only useful for default initialization).
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++)
			size[compo[M*i + j] - 1]++;
	short maxsize = 0;
	for (short i = 0; i < num; i++) {
		if (size[i] > maxsize)
			maxsize = size[i];
	}


	//printInts(size, num);
	short sumsize = 0;
	short r = 0, c = 0;
	char p;

	// Attention: this num could be VERY LARGE !!!
	// In Test 7, M=N=50, num=M*N=2500
	// adjacency matrix could be too huge!
	short* neighbor = new short[num*num]();
	short c1 = 0, c2 = 0;
	getNeighbor(compo, M, N, num, size, sumsize, c1, c2, neighbor);

	// find border
	if (size[c1 - 1] > size[c2 - 1])
		swap(c1, c2);
	short pi = 0, pj = N - 1, dir = 1;//direction=north, dir=1, direction=east,dir=0
	for (short i = 0; i <N; i++)
		for (short j = 0; j < M; j++) {
			if (compo[i*M + j] == c1) {
				if (j > 0) {
					// see west
					if (isBorder(compo, M, N, c1, i, j, c2, i, j - 1)) {
						if (j - 1 < pj) {
							pj = j - 1;
							pi = i;
						}
						else if (j - 1 == pj&&i > pi) {
							pi = i;
						}
						continue;
					}
				}
				if (j <M - 1) {
					// see east
					if (isBorder(compo, M, N, c1, i, j, c2, i, j + 1)) {
						if (j < pj) {
							pj = j;
							pi = i;
						}
						else if (j == pj&&i > pi) {
							pi = i;
						}
						//continue; this will meet error, should not break at this situation
						// 1 3
						// 3 3
						// look at 1, 1 and 3 is border, but left lower corner 3 is desirable
					}
				}
				if (i > 0) {
					// see north
					if (isBorder(compo, M, N, c1, i, j, c2, i - 1, j)) {
						if (j < pj) {
							pj = j;
							pi = i;
						}
						else if (j == pj&&i > pi) {
							pi = i;
						}
					}
				}
				if (i <N - 1) {
					// see south
					if (isBorder(compo, M, N, c1, i, j, c2, i + 1, j)) {
						if (j < pj) {
							pj = j;
							pi = i + 1;
						}
						else if (j == pj&&i + 1 > pi) {
							pi = i + 1;
						}
						continue;
					}
				}
			}
		}
	//cout << pi << " " << pj << endl;
	if (pi == 0)
		dir = 0;
	else if (pj == N - 1)
		dir = 1;
	else if (compo[pi*M + pj] != compo[(pi - 1)*M + pj]) {
		dir = 1;
	}
	else
		dir = 0;

	char direction;
	if (dir == 1)
		direction = 'N';
	else
		direction = 'E';
	fout << num << endl << maxsize << endl << sumsize << endl << pi + 1 << " " << pj + 1 << " " << direction << endl;

}

void solve_v2() {
	// use trick to share the same memory between initial matrix, which represent wall infomation,
	// and component matrix
	ofstream fout("castle.out");
	ifstream fin("castle.in");
	short M, N;
	fin >> M >> N;
	short *mat = new short[M*N];
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++)
			fin >> mat[i*M + j];
	//printMat(mat, M, N);
	short num = 0;
	short* compo = getComponent_v2(mat, M, N, num);
	printMat(compo, M, N);


	short* size = new short[num](); //Note that you must use the empty parentheses - you cannot, for example, use(0) or any other expression(which is why this is only useful for default initialization).
	for (short i = 0; i < N; i++)
		for (short j = 0; j < M; j++)
			size[compo[M*i + j] -16 - 1]++;
	short maxsize = 0;
	for (short i = 0; i < num; i++) {
		if (size[i] > maxsize)
			maxsize = size[i];
	}

	//printInts(size, num);
	short sumsize = 0;
	short r = 0, c = 0;
	char p;

	// we should AVOID this adjacency matrix because num can be very big like M*N
	//short* neighbor = new short[num*num]();
	// when we examine the adjacent component, we can also get the most left and lowest boundary
	short c1 = 0, c2 = 0, pi = 0, pj = N - 1;
	getNeighbor_v2(compo, M, N, num, size, sumsize, c1, c2, pi, pj);
	
	cout << "c1=" << c1 << " size=" << size[c1 - 17] << "  c2=" << c2 << " size=" << size[c2 - 17] << endl;
	short dir = 1;//direction=north, dir=1, direction=east,dir=0
	if (pi == 0)
		dir = 0;
	else if (pj == N - 1)
		dir = 1;
	else if (compo[pi*M + pj] != compo[(pi - 1)*M + pj]) {
		dir = 1;
	}
	else
		dir = 0;

	char direction;
	if (dir == 1)
		direction = 'N';
	else
		direction = 'E';
	fout << num << endl << maxsize << endl << sumsize << endl << pi + 1 << " " << pj + 1 << " " << direction << endl;

}
int main() {
	solve_v2();
	return 0;
}