/*
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

/*
* define a cmp function to do quick sort by using qsort
*/
int cmp(const void*a, const void*b) {
	return *(int*)a - *(int*)b; // when a, b are integers
}
