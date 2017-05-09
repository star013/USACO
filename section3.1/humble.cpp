/*
ID: thustar1
PROG: humble
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int cmp(const void*a, const void*b) {
	return *(int*)a - *(int*)b;
}

bool isHumble(int a, int p[100], int k) { // a>1
	while (a > 1) {
		bool fail = true;
		for (int i = 0; i < k; i++) {
			if (a%p[i] == 0) {
				fail = false;
				a /= p[i];
				break;
			}
		}
		if (fail)
			return false;
	}
	return true;
}

int solve_v1(int k, int n, int p[100]) {
	// Brute Force
	// Fail at Test 4, too slow
	// if you examine each integer one by one, it will cost much time
	int pos = 0, a = p[0], res = 0;
	while (pos < n) {
		if (isHumble(a, p, k)) {
			pos++;
			res = a;
			//cout << "No." << pos << " humble num=" << a << endl;
		}
		a++;
	}
	return res;
}

struct Node // graph node
{
	int x;
	int nextid;// 0,1,...,k-1
};

void bfs(int p[100], int k, int n, vector<int>& humbles) {
	// broad first search for humble numbers
	vector<Node> edge; // edge represent nodes at the edge of graph
	Node* root=new Node;
	root->x = 1; root->nextid = 0;
	edge.push_back(*root);
	int num = 0;
	while (num < n) {
		int minimal = 2147483647;
		int edgeNodeId = 0, nextId = 0;
		// Still too slow, because finding minimal weight is a waste of computation
		// we can store the result each time
		for (int i = 0; i < edge.size(); i++) {
			if (minimal > edge[i].x*p[edge[i].nextid]) {
				minimal = edge[i].x*p[edge[i].nextid];
				edgeNodeId = i;
				nextId = edge[i].nextid;
			}
		}
		if (nextId == k - 1) {
			edge.erase(edge.begin() + edgeNodeId);
		}
		else {
			edge[edgeNodeId].nextid++;
		}

		Node* nextEdge=new Node;
		nextEdge->x = minimal;
		nextEdge->nextid = nextId;
		// To prevent repeated situation, larger prime can not multiply smaller prime
		edge.push_back(*nextEdge);
		humbles.push_back(minimal);
		num++;

		//cout << "No." << num << " humble=" << minimal << endl;
		/*cout << "edge nodes=" << endl;
		for (int i = 0; i < edge.size(); i++)
			cout << "val=" << edge[i].x << " nextid=" << edge[i].nextid << endl;*/
	}
}

int findPosition(vector<Node>& neighbor, Node& tmp, int beg, int end) {
	// Attention: sometimes, there may have situation like end-1==beg
	// e.g. neighbor={2,3,5,7}, tmp=4
	// round 2, beg=2,end=3,idx=2, tmp>neighbor[idx]
	// round 3, beg=2,end=prev idx - 1 = 1
	if (beg >= end) {
		if (neighbor[beg].x < tmp.x)
			return beg + 1;
		else {
			return beg;
		}
	}
	int idx = (beg + end) / 2;
	if (neighbor[idx].x < tmp.x)
		return findPosition(neighbor, tmp, idx + 1, end);
	if (neighbor[idx].x > tmp.x)
		return findPosition(neighbor, tmp, beg, idx - 1);

}

void findAndInsert(vector<Node>& neighbor, Node& tmp) {
	int pos = findPosition(neighbor, tmp, 0, neighbor.size() - 1);
	neighbor.insert(neighbor.begin() + pos, tmp);
}
void bfs_v2(int p[100], int k, int n, int& res) {
	// broad first search for humble numbers
	vector<Node> neighbor; // edge neighbor nodes at the edge of graph
	// i.e. nodes adjancent to the graph and not in the graph
	Node* root = new Node;
	root->x = 1; root->nextid = 0;
	neighbor.push_back(*root);
	int num = 0;
	while (num < n) {
		for (int i = neighbor[0].nextid; i < k; i++) {
			Node* tmp = new Node;
			tmp->x = neighbor[0].x*p[i]; tmp->nextid = i;
			//Test 5 error, cout negative number
			if (2147483648/p[i]<neighbor[0].x)
				continue;
			findAndInsert(neighbor, *tmp);
		}
		/*cout << "neighbor=" << endl;
		for (int i = 0; i < neighbor.size(); i++)
			cout << neighbor[i].x << " ";
		cout << endl;*/
		neighbor.erase(neighbor.begin());
		//cout << "No." << num << " humble=" << humbles[num] << endl;
		num++;
	}
	//cout << "neighbor size=" << neighbor.size() << endl;
	// Test 6: TLE, neighbor size=15926
	res = neighbor[0].x;
}

void bfs_v3(int p[100], int k, int n, int& res) {
	// broad first search for humble numbers
	vector<Node> neighbor; // edge neighbor nodes at the edge of graph
						   // i.e. nodes adjancent to the graph and not in the graph
	Node* root = new Node;
	root->x = p[0]; root->nextid = 0;
	neighbor.push_back(*root);
	int num = 1;
	while (num < n) {
		// deeper neighbor
		Node* tmp = new Node;
		tmp->x = neighbor[0].x*p[neighbor[0].nextid]; tmp->nextid = neighbor[0].nextid;
		if (2147483648 / p[neighbor[0].nextid]>neighbor[0].x)
			findAndInsert(neighbor, *tmp);
		// broader neighbor
		if (neighbor[0].nextid < k-1) {
			tmp->x = neighbor[0].x/p[neighbor[0].nextid]* p[neighbor[0].nextid+1]; tmp->nextid = neighbor[0].nextid+1;
			if (2147483648 / p[neighbor[0].nextid+1]>neighbor[0].x/p[neighbor[0].nextid])
				findAndInsert(neighbor, *tmp);
		}
		neighbor.erase(neighbor.begin());
		num++;
	}
	cout << "neighbor size=" << neighbor.size() << endl;
	// Test 6: TLE, neighbor size=15926
	res = neighbor[0].x;
}


void swap(Node& a, Node& b) {
	Node c = a;
	a = b;
	b = c;
}
class Heap
{
public:
	int num;// # of elements in heap
	Node a[200000];
	Heap() { num = 0; }
	void insert(Node tmp) {
		a[num] = tmp;
		int idx = num;
		num++;
		while (idx > 0) {
			if (idx % 2 == 1) {
				// idx is left child of (idx-1)/2
				if (a[idx].x < a[(idx - 1) / 2].x) {
					swap(a[idx], a[(idx - 1) / 2]);
					idx = (idx - 1) / 2;
				}
				else
					break;
			}
			else {
				// idx is right child of (idx-2)/2
				if (a[idx].x < a[(idx - 2) / 2].x) {
					swap(a[idx], a[(idx - 2) / 2]);
					idx = (idx - 2) / 2;
				}
				else
					break;
			}
		}
	}
	void removeHead() {
		a[0] = a[num - 1];
		num--;
		int idx = 0;
		while (2 * idx + 1 < num) {
			// left child exist
			if (2 * idx + 2 < num) {
				// right child also exist
				int smallidx = 2 * idx + 1;
				if (a[smallidx].x > a[smallidx + 1].x)
					smallidx++;
				if (a[idx].x > a[smallidx].x) {
					swap(a[idx], a[smallidx]);
					idx = smallidx;
				}
				else
					break;
			}
			else {
				// right child not exist
				int smallidx = 2 * idx + 1;
				if (a[idx].x > a[smallidx].x) {
					swap(a[idx], a[smallidx]);
					idx = smallidx;
				}
				else
					break;
			}
		}
	}
	void print() {
		for (int i = 0; i < num; i++) {
			cout << "idx =" << i << " x=" << a[i].x << " nextid=" << a[i].nextid << endl;
		}
	}
private:

};

void bfs_v4(int p[100], int k, int n, int& res) {
	// broad first search for humble numbers
	Heap neighbor; // edge neighbor nodes at the edge of graph
						   // i.e. nodes adjancent to the graph and not in the graph
	Node* root = new Node;
	root->x = p[0]; root->nextid = 0;
	neighbor.insert(*root);
	int num = 1;
	while (num < n) {
		// deeper neighbor
		Node* tmp = new Node;
		tmp->x = neighbor.a[0].x*p[neighbor.a[0].nextid]; tmp->nextid = neighbor.a[0].nextid;
		if (2147483648 / p[neighbor.a[0].nextid]>neighbor.a[0].x)
			neighbor.insert(*tmp);
		// broader neighbor
		if (neighbor.a[0].nextid < k - 1) {
			tmp->x = neighbor.a[0].x / p[neighbor.a[0].nextid] * p[neighbor.a[0].nextid + 1]; tmp->nextid = neighbor.a[0].nextid + 1;
			if (2147483648 / p[neighbor.a[0].nextid + 1]>neighbor.a[0].x / p[neighbor.a[0].nextid])
				neighbor.insert(*tmp);
		}
		neighbor.removeHead();
		num++;
	}
	cout << "neighbor size=" << neighbor.num << endl;
	// Test 6: TLE, neighbor size=15926
	res = neighbor.a[0].x;
}
int main() {
	ofstream fout("humble.out");
	ifstream fin("humble.in");
	int k, n;
	fin >> k >> n;
	int p[100];
	for (int i = 0; i < k; i++)
		fin >> p[i];

	qsort(p, k, sizeof(int), cmp);

	//cout << solve_v1(k, n, p) << endl;
	vector<int> humbles;
	/*bfs(p, k, n, humbles);
	cout << humbles[n - 1] << endl;*/
	int res = 0;
	bfs_v4(p, k, n, res);
	// Attention:
	// Write a simple HEAP for yourself
	// A fixed memory heap is much faster than vector insert and delete operations
	fout << res << endl;
	return 0;
}