/*
ID: thustar1
PROG: msquare
LANG: C++11
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string.h>
using namespace std;

#define STATE_NUM 40400

/*
There are 8! = 40320 states in total
Thus, we can use broadfirst search and remove visited state
*/
void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int transA(int input) {
	int tmp[8];
	for (int i = 0; i < 8; i++) {
		tmp[i] = input % 10;
		input /= 10;
	}
	int res = 0;
	for (int i = 0; i < 8; i++) {
		res = res * 10 + tmp[i];
	}
	return res;
}

int transB(int input) {
	int tmp[8];
	int a[8];
	for (int i = 0; i < 8; i++) {
		a[7-i] = input % 10;
		input /= 10;
	}
	tmp[0] = a[3];
	for (int i = 1; i < 4; i++)
		tmp[i] = a[i - 1];
	tmp[7] = a[4];
	for (int i = 4; i < 7; i++)
		tmp[i] = a[i + 1];
	int res = 0;
	for (int i = 0; i < 8; i++) {
		res = res * 10 + tmp[i];
	}
	return res;
}

int transC(int input) {
	int tmp[8];
	int a[8];
	for (int i = 0; i < 8; i++) {
		a[7 - i] = input % 10;
		input /= 10;
	}
	tmp[0] = a[0];
	tmp[1] = a[6];
	tmp[2] = a[1];
	tmp[3] = a[3];
	tmp[4] = a[4];
	tmp[5] = a[2];
	tmp[6] = a[5];
	tmp[7] = a[7];
	int res = 0;
	for (int i = 0; i < 8; i++) {
		res = res * 10 + tmp[i];
	}
	return res;
}

//void display(int* a) {
//	for (int i = 0; i < 4; i++)
//		fout << a[i] << " ";
//	fout << endl;
//	for (int i = 7; i >= 4; i--)
//		fout << a[i] << " ";
//	fout << endl;
//}

int metric(int*a, int*b) {
	int res = 0;
	for (int i = 0; i < 8; i++)
		res += a[i] == b[i];
	return res;
}

bool equal(int* a, int* b) {
	for (int i = 0; i < 8; i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

int getKey(int* a) {
	int res = 0;
	for (int i = 0; i < 8; i++) {
		res += a[i] * (int)pow(10, i);
	}
	return res;
}

bool findKey(int* a, int beg, int end, int& key) {
	// a is sorted, a[beg],a[end-1] are two ends of considered part
	if (end <= beg)
		return false;
	int tmp = (beg + end) / 2;
	if (a[tmp] == key)
		return true;
	if (a[tmp] < key)
		return findKey(a, tmp+1, end, key);
	else
		return findKey(a, beg, tmp, key);
}

void insertKey(int* a, int& num, int& key) {
	// keep a as sorted array
	a[num] = key;
	for (int i = num - 1; i >= 0; i--) {
		if (a[i] > a[i + 1])
			swap(a[i], a[i + 1]);
		else
			break;
	}
	num++;
}

struct State
{
	int a;
	char transform[128];
};
int main() {
	ofstream fout("msquare.out");
	ifstream fin("msquare.in");
	int origin = 12345678;
	/*fout << "origin" << endl;
	display(origin);
	fout << "A" << endl;
	display(transA(origin));
	fout << "B" << endl;
	display(transB(origin));
	fout << "C" << endl;
	display(transC(origin));*/
	/*
	There are 8! = 40320 states in total
	Thus, we can use broadfirst search and remove visited state
	*/
	int target=0;
	int tmpi;
	for (int i = 0; i < 8; i++) {
		fin >> tmpi;
		target = target * 10 + tmpi;
	}
	/*int* tmp;
	display(origin);
	tmp = transB(origin);
	fout << "B" << endl;
	display(tmp);
	fout <<"metric = "<< metric(tmp, target) << endl;

	tmp = transC(tmp);
	fout << "C" << endl;
	display(tmp);
	fout << "metric = " << metric(tmp, target) << endl;

	tmp = transA(tmp);
	fout << "A" << endl;
	display(tmp);
	fout << "metric = " << metric(tmp, target) << endl;

	tmp = transB(tmp);
	fout << "B" << endl;
	display(tmp);
	fout << "metric = " << metric(tmp, target) << endl;

	tmp = transC(tmp);
	fout << "C" << endl;
	display(tmp);
	fout << "metric = " << metric(tmp, target) << endl;

	tmp = transC(tmp);
	fout << "C" << endl;
	display(tmp);
	fout << "metric = " << metric(tmp, target) << endl;

	tmp = transB(tmp);
	fout << "B" << endl;
	display(tmp);
	fout << "metric = " << metric(tmp, target) << endl;*/

	int table[STATE_NUM];
	for (int i = 0; i < STATE_NUM; i++)
		table[i] = 0;
	int num = 0;
	State s[STATE_NUM];
	int beg = 0;
	State* tmp;
	char* result;
	tmp = &s[num];
	tmp->a = origin;
	strcpy(tmp->transform, "");
	if (!findKey(table, 0, num, tmp->a)) {
		insertKey(table, num, tmp->a);
	}
	if (tmp->a==target) {
		result = tmp->transform;
		beg++;
	}
	// broad first search
	while (num-beg > 0) {
		// trans A
		char* tmpstr = s[beg].transform;
		int len = strlen(tmpstr);
		if ((len > 0 && tmpstr[len - 1] != 'A')||len==0) {
			tmp = &s[num];
			tmp->a = transA(s[beg].a);
			strcpy(tmp->transform,tmpstr);
			strcat(tmp->transform, "A");
			if (tmp->a==target) {
				result = tmp->transform;
				break;
			}
			if (!findKey(table, 0, num, tmp->a)) {
				insertKey(table, num, tmp->a);
			}
		}
		// trans B
		if ((len > 2 && !(tmpstr[len - 1] == 'B'&&tmpstr[len - 2] == 'B'&&tmpstr[len - 3] == 'B'))||len<3) {
			tmp = &s[num];
			tmp->a = transB(s[beg].a);
			strcpy(tmp->transform, tmpstr);
			strcat(tmp->transform, "B");
			if (tmp->a==target) {
				result = tmp->transform;
				break;
			}
			if (!findKey(table, 0, num, tmp->a)) {
				insertKey(table, num, tmp->a);
			}
		}
		// trans C
		if ((len > 2 && !(tmpstr[len - 1] == 'C'&&tmpstr[len - 2] == 'C'&&tmpstr[len - 3] == 'C')) || len < 3) {
			tmp = &s[num];
			tmp->a = transC(s[beg].a);
			strcpy(tmp->transform, tmpstr);
			strcat(tmp->transform, "C");
			if (tmp->a==target) {
				result = tmp->transform;
				break;
			}
			if (!findKey(table, 0, num, tmp->a)) {
				insertKey(table, num, tmp->a);
			}
		}
		//fout << "num=" << num << endl;
		// delete old state
		beg++;
	}
	/*
	Test 7: TLE
	3 4 2 1 5 6 7 8
	maybe it is too slow to allocate 8-int array and transform array to a key

	Yeah, my thought is right!
	After using assigned struct State array instead of vector, it speeds up dramatically!!!
	Remember when the scale of number of states is not large, use fixed length array instead of vector!
	*/
	int reslen = strlen(result);
	fout << reslen << endl;
	int i = 0;
	while (i + 60 < reslen) {
		for (int j = i; j < i + 60; j++)
			fout << result[j];
		fout << endl;
		i += 60;
	}
	for (int j = i; j <reslen; j++)
		fout << result[j];
	fout << endl;
	return 0;
}
