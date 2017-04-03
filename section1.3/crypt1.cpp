/*
ID: thustar1
PROG: crypt1
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int compare(const void*a, const void* b) {
	return *(int*)a > *(int*)b; // if a>b, return >0
}

// step 1 determin abc based on e (or d), e and d are symmetric
bool correct(int* set, int n, string a) {
	for (int i = 0; i < a.size(); i++) {
		int tmp = a[i] - '0';
		bool exist = false;
		for (int j = 0; j < n; j++) {
			if (tmp == set[j]) {
				exist = true;
				break;
			}
		}
		if (!exist)
			return false;
	}
	return true;
}
vector<int> e2cSet(int* set, int n, int e) {
	vector<int> cset;
	for (int i = 0; i < n; i++) {
		int tmp = set[i] * e % 10;
		if (correct(set, n, to_string(tmp)))
			cset.push_back(set[i]);
	}
	return cset;
}
vector<int> ec2bSet(int* set, int n, int e, int c) {
	vector<int> bset;
	for (int i = 0; i < n; i++) {
		int tmp = (c*e+set[i]*e*10)%100;
		if (correct(set, n, to_string(tmp)))
			bset.push_back(set[i]);
	}
	return bset;
}

vector<int> ecb2aSet(int* set, int n, int e, int c, int b) {
	vector<int> bset;
	for (int i = 0; i < n; i++) {
		int tmp = c*e+b*e*10+set[i]*e*100;
		if (correct(set, n, to_string(tmp)))
			bset.push_back(set[i]);
	}
	return bset;
}

int solve(int* set, int n) {
	int res = 0;
	vector<int> multi1, multi2;
	// step1: select valid abc, determined by e
	for (int i = 0; i < n; i++) {
		int e = set[i];
		vector<int> cset = e2cSet(set, n, e);
		if (cset.size() > 0) {
			for (int j = 0; j < cset.size(); j++) {
				int c = cset[j];
				vector<int> bset = ec2bSet(set, n, e, c);
				if (bset.size() > 0) {
					for (int k = 0; k < bset.size(); k++) {
						int b = bset[k];
						vector<int> aset = ecb2aSet(set, n, e, c, b);
						if (aset.size() > 0) {
							for (int m = 0; m < aset.size(); m++) {
								//remove zero head
								// This problem require: The partial products must be three digits long
								string  tmp = to_string((aset[m] * 100 + b * 10 + c)*e);
								if (aset[m] > 0&&tmp.size()==3) {
									multi1.push_back(aset[m] * 100 + b * 10 + c);
									multi2.push_back(e);
								}
							}
						}
					}
				}
			}
		}
	}
	// step2: combine abc and de to see sumation
	for (int i = 0; i < multi1.size(); i++) {
		for (int j = 0; j < multi1.size(); j++) {
			if (multi1[i] != multi1[j])
				continue;
			int a = multi1[i], b = multi2[i] * 10 + multi2[j];
			int tmp = a*b;
			if (correct(set, n, to_string(tmp))) {
				res++;
				// test
				//cout << "abc=" << a << endl;
				//cout << "de=" << b << endl;
				//cout << "abc*e=" << a*multi2[j] << endl;
				//cout << "abc*d=" << a*multi2[i] << endl;
				//cout << "abc*de=" << tmp << endl << endl;
			}
			
		}
	}
	return res;
}
void printVec(vector<int> a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;
}
int main() {
	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");
	int n;
	fin >> n;
	int* sets = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> sets[i];
	}
	// sort
	qsort(sets, n, sizeof(int),compare);
	/*for (int i = 0; i < c; i++) {
		cout << sets[i] << endl;
	}*/
	//vector<int> test = e2cSet(sets, n, 2);
	//printVec(test);
	int result = solve(sets,n);
	fout << result << endl;
	return 0;
}