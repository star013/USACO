/*
ID: thustar1
PROG: ariprog
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool* getBiSet(int m) {
	// get all bisquare numbers
	// m<=250, 2*250^2+1=125001
	bool* res=new bool[125001];
	for (int i = 0; i <= 125000; i++)
		res[i] = false;
	for (int p = 0; p <= m; p++) {
		for (int q = p; q <= m; q++) {
			res[p*p + q*q] = true;
		}
	}
	
	return res;
}

int* getInts(bool* set, int m,int& len) {
	len = 0;
	for (int i = 0; i <= 2 * m*m; i++) {
		if (set[i]) {
			len++;
		}
	}
	int* iset = new int[len];
	int tmp = 0;
	for (int i = 0; i <= 2 * m*m; i++) {
		if (set[i]) {
			iset[tmp] = i;
			tmp++;
		}
	}
	return iset;
}

bool correct(int a, int b, int n, int m, bool* set) {
	int tmp = 2 * m*m;
	for (int i = 0; i < n; i++) {
		if (a + i*b > tmp)
			return false;
		if (!set[a + i*b])
			return false;
	}
	return true;
}

//class P {
//public:int a;
//	   int b;
//	   P(int a, int b) { this->a = a; this->b = b; }
//	   P(P& p) { a = p.a; b = p.b; }
//};

struct P
{
	int a;
	int b;
};

vector<P> search_v1(int n, int m) {
	// Version 1.0: Test 8 exceed memory
	// It is because in correct function the index a+i*b exceeds 2*m*m, the length of set, causing memory error
	bool* set = getBiSet(m);
	int len = 0;
	int* iset = getInts(set, m, len);
	vector<P> res;
	int a = 0, b = 0;
	for (int i = 0; i <= len - n; i++) {
		for (int j = i + 1; j <= len - n + 1; j++) {
			a = iset[i];
			b = iset[j] - a;
			if (correct(a, b, n, m, set)) {
				P *p=new P;
				p->a = a;
				p->b = b;
				res.push_back(*p);
			}
		}
	}
	return res;
}



int cmp(const void*a, const void* b) {
	P* p1 = (P*)a;
	P* p2 = (P*)b;
	if (p1->b < p2->b) return -1;
	if (p1->b == p2->b) {
		if (p1->a < p2->a) return -1;
		if (p1->a == p2->a) return 0;
		return 1;
	}
	return 1;
}

void printInts(int* a, int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}


int main() {
	ofstream fout("ariprog.out");
	ifstream fin("ariprog.in");
	int n,m;
	fin >> n >> m;
	// test
	//bool* set = getBiSet(m);
	//cout << set[0] << " " << set[3] << endl;
	//int len = 0;
	//int* iset = getInts(set, m, len);
	//printInts(iset, len);
	vector<P> res = search_v1(n, m);
	if (res.size() == 0)
		fout << "NONE" << endl;
	else {
		qsort(&res[0], res.size(), sizeof(P), cmp);
		for (int i = 0; i < res.size(); i++)
			fout << res[i].a << " " << res[i].b << endl;
	}
	return 0;
}