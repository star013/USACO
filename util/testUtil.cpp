﻿/*
ID: thustar1
PROG: test utility
LANG: C++11
*/

/*
* Print result to test each unit
*/
void printInts(int* a,int n){
    for (int i = 0; i < n; i++)
		cout << a[i]<< " ";
    cout<<endl;
}

void printVec(vector<int> a){
    for (int i = 0; i < a.size(); i++)
		cout << a[i]<< " ";
    cout<<endl;
}

void fprintVec(vector<int> a,ofstream& fout) {
	for (int i = 0; i < a.size()-1; i++)
		fout << a[i] << " ";
	fout <<a[a.size()-1] <<endl;
}

void printMat(int* mat, int M, int N) {
	// M col, N row, i.e. N x M matrix
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cout << mat[i*M + j] << " ";
		cout << endl;
	}
}

int* dpcpyInt(int* a, int n) { // deep copy a int array
	int* res = new int[n];
	for (int i = 0; i < n; i++)
		res[i] = a[i];
	return res;
}

/*
* define a cmp function to do quick sort by using qsort
*/
int cmp(const void*a, const void*b) {
	return *(int*)a - *(int*)b; // when a, b are integers
}
// for a int* array a[n]
qsort(a,n,sizeof(int),cmp)
// for a vector<int> res
qsort(&res[0],res.size(),sizeof(int),cmp)
