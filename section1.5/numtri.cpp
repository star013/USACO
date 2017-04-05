/*
ID: thustar1
PROG: numtri
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Tree
{
	int val;
	Tree* left;
	Tree* right;
};

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}
void search_v1(Tree* root, int cur, int& res) {
	// version 1: Test 6 run over time
	// because there are 199 lines and cost too much to build a tree
	if (root->left == NULL) {
		res = max(res, cur + root->val);
		return;
	}
	// depth first search
	search_v1(root->left, cur + root->val, res);
	search_v1(root->right, cur + root->val, res);
}


int main() {
	ofstream fout("numtri.out");
	ifstream fin("numtri.in");
	int n;
	fin >> n;
	//Tree* t = new Tree[n*(n+1)/2];
	//fin >> t[0].val;
	//t[0].left = NULL; t[0].right = NULL;
	//for (int i = 1; i < n; i++) {
	//	for (int j = 0; j <= i; j++) {
	//		// i th row, j th col
	//		fin >> t[i*(i + 1) / 2 + j].val;
	//		t[i*(i + 1) / 2 + j].left = NULL; t[i*(i + 1) / 2 + j].right = NULL;
	//		if(j<i)
	//			t[(i - 1)* i / 2 + j].left = &t[i*(i + 1) / 2 + j];
	//		if(j>0)
	//			t[(i - 1)* i / 2 + j-1].right = &t[i*(i + 1) / 2 + j];
	//	}
	//}
	//Tree* root = &t[0];
	//int res = 0;
	//search_v1(root, 0, res);
	

	// version 2, broad first search
	// succeed
	// Attention, if you can use index to access each elements, then do not build a tree
	// it is time consuming to build a new tree and it is not necessary, because you can trace each element by explicit index
	// Using a vector to keep track for the best temporary test is kind of like dynamic programing
	int *bottom = new int[n];
	int *prev = new int[n];
	int tmp = 0;
	fin >> tmp;
	prev[0] = bottom[0] = tmp;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			fin >> tmp;
			if (j>0&&j<i)
				bottom[j] = max(prev[j], prev[j - 1]) + tmp;
			else if (j == 0) {
				bottom[j] = prev[j] + tmp;
			}
			else {
				bottom[j] = prev[j - 1] + tmp;
			}
		}
		// refresh prev state
		for (int j = 0; j <= i; j++)
			prev[j] = bottom[j];
	}
	int res = 0;
	for (int i = 0; i < n; i++)
		if (bottom[i] > res)
			res = bottom[i];
	fout << res << endl;
	return 0;
}