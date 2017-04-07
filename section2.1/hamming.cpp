/*
ID: thustar1
PROG: hamming
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

void printInts(int* a, int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

void printMat(int* mat, int M, int N) {
	// M col, N row
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << mat[i*M + j] << " ";
		cout << endl;
	}
}

int hamming(int* a, int* b, int B) {
	int res = 0;
	for (int i = 0; i < B; i++)
		if (a[i] != b[i])
			res++;
	return res;
}

int* int2code(int a, int B) { // in reverse order just to calculate hamming distance
	int* res = new int[B];
	for (int i = 0; i < B; i++) {
		res[i] = a % 2;
		a /= 2;
	}
	return res;
}

void sieve(int a, bool* state, int n, int B, int D) {
	int* acode = int2code(a, B);
	for (int i = 0; i < n; i++) {
		if (state[i]) {
			if (hamming(acode, int2code(i, B), B) < D)
				state[i] = false;
		}
	}
}
int main() {
	ofstream fout("hamming.out");
	ifstream fin("hamming.in");

	/*int a[3] = { 0,0,1 };
	int b[3] = { 0,1,1 };
	cout << "test hamming=" << hamming(a, b, 3) << endl;
	int c = 10;
	cout << "test int2code" << endl;
	int B = 10;
	printInts(int2code(c, B), B);*/
	
	bool state[256];// B<=8, pow(2,8)=256
	for (int i = 0; i < 256; i++)
		state[i] = true;
	
	int N, B, D;
	fin >> N >> B >> D;
	int* res = new int[N]();
	int num = 0, n = int(pow(2, B));
	state[num] = false;
	sieve(res[num], state, n, B, D);
	for (int i = 1; i<n; i++) {
		if (state[i]) {
			num++;
			state[num] = false;
			res[num] = i;
			sieve(res[num], state, n, B, D);
			if (num == N - 1)
				break;
		}
	}
	//printInts(res, N);
	for (int i = 0; i < N / 10; i++) {
		for (int j = 0; j < 9; j++)
			fout << res[i * 10 + j] << " ";
		fout << res[i * 10 + 9] << endl;
	}
	for (int i = 0; i < N % 10 - 1; i++) {
		fout << res[N - N % 10 + i] << " ";
	}
	if (N % 10 > 0)
		fout << res[N - 1] << endl;
	return 0;
}