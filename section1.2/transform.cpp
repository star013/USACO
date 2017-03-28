/*
ID: thustar1
PROG: transform
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

void print(const bool* mat, const int& n) {
	// just for test
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i*n + j])
				cout << '@' << ' ';
			else
				cout << '-' << ' ';
		}
		cout << endl;
	}
}

/**
 * You can also use rotate function to generate a new matrix and compare that with template matrix
 * In this way, you can avoid writing 180deg, and 270deg operation
*/
bool one(const bool* mat1,const bool* mat2, const int& n) {
	// 90 deg clockwise
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat1[i*n + j] != mat2[j*n + n-1 - i]) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool two(const bool* mat1, const bool* mat2, const int& n) {
	// 180 deg clockwise
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat1[i*n + j] != mat2[(n-1-i)*n + n-1 - j]) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool three(const bool* mat1, const bool* mat2, const int& n) {
	// 270 deg clockwise
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat1[i*n + j] != mat2[(n - 1 - j)*n + i]) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool four(const bool* mat1, const bool* mat2, const int& n) {
	// reflection
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat1[i*n + j] != mat2[i*n + n-1-j]) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool* reflect(const bool* mat1, const int& n) {
	bool* mat2 = new bool[n*n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat2[i*n + j] = mat1[i*n+n-1-j];
			}
		}
	return mat2;
}

bool six(const bool* mat1, const bool* mat2, const int& n) {
	// equal
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat1[i*n + j] != mat2[i*n+j]) {
				result = false;
				break;
			}
		}
	}
	return result;
}

int main() {
	int yrs;
	ofstream fout("transform.out");
	ifstream fin("transform.in");
	char c;
	int n;
	fin >> n;

	bool* mat1 = new bool[n*n];
	bool* mat2 = new bool[n*n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> c;
			if (c == '@')
				mat1[i*n + j] = true;
			else
				mat1[i*n + j] = false;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> c;
			if (c == '@')
				mat2[i*n + j] = true;
			else
				mat2[i*n + j] = false;
		}
	}
	/*cout << "####################" << endl;
	print(mat1, n);
	print(mat2, n);*/
	int result = 0;
	if (one(mat1, mat2, n)) {
		result = 1;
	}
	else if (two(mat1, mat2, n)) {
		result = 2;
	}
	else if (three(mat1, mat2, n)) {
		result = 3;
	}
	else if (four(mat1, mat2, n)) {
		result = 4;
	}
	else if (six(mat1, mat2, n)) {
		result = 6;
	}
	else {
		bool* mat3 = reflect(mat1, n);
		if (one(mat3, mat2, n) || two(mat3, mat2, n) || three(mat3, mat2, n))
			result = 5;
		else
			result = 7;
	}
	fout <<result<< endl;
	return 0;
}