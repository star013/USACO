/*
ID: thustar1
PROG: holstein
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

int getType(int* recipe, int g) {
	// get # of types in recipe, recipe[i] means # of scoops for vitermin i
	int res = 0;
	for (int i = 0; i < g; i++)
		if (recipe[i] > 0)
			res++;
	return res;
}

bool ok(int* remain, int v) {
	for (int i = 0; i < v; i++)
		if (remain[i] > 0)
			return false;
	return true;
}

void copy(int* a, int*b, int n) {
	for (int i = 0; i < n; i++)
		b[i] = a[i];
}
void depthFirstSearch(int*remain, int v, int* scoop, int g, int* recipe, int depth, int& sum, int* res) {
	// provide a naive depth first search
	// however, it fails at Test 8, TLE(i.e. time limit exceed), v=20, g=12
	// prune strategy
	if (depth > sum)
		return;
	if (ok(remain, v)) {
		if (depth < sum) {
			sum = depth;
			copy(recipe, res, g);
		}
		else if (depth == sum) {
			if (getType(res, g) > getType(recipe, g)) {
				copy(recipe, res, g);
			}
		}
	}
	for (int i = 0; i < g; i++) {
		if (recipe[i] == 0) {
			// take scoop i
			recipe[i] = 1;
			for (int j = 0; j < v; j++)
				remain[j] -= scoop[i*v + j];
			depthFirstSearch(remain, v, scoop, g, recipe, depth + 1, sum, res);
			// recover state
			for (int j = 0; j < v; j++)
				remain[j] += scoop[i*v + j];
			recipe[i] = 0;
		}
	}
}

int getStateIdx(int* recipe, int g) {
	// O(g)
	int res = 0;
	for (int i = 0; i < g; i++)
		res = 2 * res + recipe[i];
	return res;
}
void dfsrrs(int*remain, int v, int* scoop, int g, int* recipe, int depth, int& sum, int* res, bool* state) {
	// depth first search removing repeated state
	// Attention: Always remember to save and check state, especially the original data is not stored in a tree or a graph
	// when searching, we should eliminate the state which has been examined already
	int idx = getStateIdx(recipe, g);
	if (state[idx])
		return;
	else
		state[idx] = true;
	if (depth > sum)
		return;
	if (ok(remain, v)) {
		if (depth < sum) {
			sum = depth;
			copy(recipe, res, g);
		}
		else if (depth == sum) {
			if (getType(res, g) > getType(recipe, g)) {
				copy(recipe, res, g);
			}
		}
	}
	for (int i = 0; i < g; i++) {// O(vg)
		if (recipe[i] == 0) {
			// take scoop i
			recipe[i] = 1;
			for (int j = 0; j < v; j++)
				remain[j] -= scoop[i*v + j];
			dfsrrs(remain, v, scoop, g, recipe, depth + 1, sum, res, state);
			// recover state
			for (int j = 0; j < v; j++)
				remain[j] += scoop[i*v + j];
			recipe[i] = 0;
		}
	}
}

struct Node// node in search tree
{
	int* remain;
	int* recipe;
	int depth;
};

void broadFirstSearch(vector<Node>& tree, int v, int* scoop, int g, int& sum, int* res) {
	// a naive broad first search
	// however, it comsume too much memory in Test 6, v=5, g=10
	if (tree.size() == 0)// concern about the border condition, if only one node, it will be deleted after the first round search
		return;
	int* remain = tree[0].remain;
	int* recipe = tree[0].recipe;
	int depth = tree[0].depth;
	if (depth > sum)
		return;
	if (ok(remain, v)) {
		if (depth < sum) {
			sum = depth;
			copy(recipe, res, g);
		}
		else if (depth == sum) {
			if (getType(res, g) > getType(recipe, g)) {
				copy(recipe, res, g);
			}
		}
	}
	for (int i = 0; i < g; i++) {
		if (recipe[i] == 0) {
			// take scoop i
			int* nremain = new int[v]();//nremain= new remain array
			int* nrecipe = new int[g]();
			copy(remain, nremain, v);
			copy(recipe, nrecipe, g);
			nrecipe[i] = 1;
			for (int j = 0; j < v; j++)
				nremain[j] -= scoop[i*v + j];
			Node* n = new Node;
			n->remain = nremain; n->recipe = nrecipe;
			n->depth = depth + 1;
			tree.push_back(*n);
		}
	}
	tree.erase(tree.begin());// remove root tree node
	broadFirstSearch(tree, v, scoop, g, sum, res);

}

int main() {
	ofstream fout("holstein.out");
	ifstream fin("holstein.in");
	int v;
	fin >> v;// 1<=v<=25
	int *req = new int[v];// req=requirement
	for (int i = 0; i < v; i++)
		fin >> req[i];
	int g;
	fin >> g; //1<=g<=15
	int* scoop = new int[g*v];// g x v matrix
	for (int i = 0; i < g; i++)
		for (int j = 0; j < v; j++)
			fin >> scoop[i*v + j];


	cout << "test input" << endl;
	printInts(req, v);
	printMat(scoop, v, g);

	int* recipe = new int[g]();//Cows can be fed at most one scoop of any feed type, recipe[i] is 0 or 1
	int* res = new int[g];
	for (int i = 0; i < g; i++)
		res[i] = 1;
	int sum = g;
	//depthFirstSearch(req, v, scoop, g, recipe, 0, sum, res);
	//cout << "test depthFirstSearch" << endl;
	//printInts(res, g);

	//Node* n = new Node;
	//n->remain = req; n->recipe = new int[g](); n->depth = 0;
	//vector<Node> tree;
	//tree.push_back(*n);
	//broadFirstSearch(tree, v, scoop, g, sum, res);
	//cout << "test broadFirstSearch" << endl;
	//printInts(res, g);

	bool* state = new bool[32768];// g<=15, there are at most 2^15=32768 recipe states
	for (int i = 0; i < 32768; i++)
		state[i] = false;
	dfsrrs(req, v, scoop, g, recipe, 0, sum, res, state);
	cout << "test depthFirstSearch removing repeated state" << endl;
	printInts(res, g);

	fout << sum << " ";
	int j = 0;
	for(int i=0;i<g;i++)
		if (res[i] > 0) {
			if (j < sum - 1) {
				fout << i + 1 << " ";
				j++;
			}
			else
				fout << i + 1 << endl;
		}
	return 0;
}